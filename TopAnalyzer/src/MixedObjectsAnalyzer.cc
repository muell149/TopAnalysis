#include "TopAnalysis/TopAnalyzer/interface/MixedObjectsAnalyzer.h"
//#include "TopQuarkAnalysis/TopEventSelection/interface/TtFullHadSignalSel.h"

#include "stdio.h"

#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
//#include "FWCore/Utilities/interface/EDMException.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

/// default constructor
MixedObjectsAnalyzer::MixedObjectsAnalyzer(const edm::ParameterSet& cfg) :
  JetSrc_            (cfg.getParameter<edm::InputTag>("JetSrc"     )),
  METSrc_            (cfg.getParameter<edm::InputTag>("METSrc"     )),
  MuonSrc_           (cfg.getParameter<edm::InputTag>("MuonSrc"    )),
  ElectronSrc_       (cfg.getParameter<edm::InputTag>("ElectronSrc")),
  weight_            (cfg.getParameter<edm::InputTag>("weight"     )),
  VertexSrc_         (cfg.getParameter<edm::InputTag>("VertexSrc"  ))
{
}

/// default destructor
MixedObjectsAnalyzer::~MixedObjectsAnalyzer()
{
}

/// initiate histograms
void
MixedObjectsAnalyzer::beginJob()
{
  // define TFileService which takes care of writing contents to root file
  edm::Service<TFileService> fs;
  if( !fs ) throw edm::Exception( edm::errors::Configuration, "TFile Service is not registered in cfg file" );

  // define the tree and make it known to the TFileService
  tree = fs->make<TTree>("tree","tree",0);

  // event identifiers
  runNumber = 0;
  tree->Branch("runNumber", &runNumber, "runNumber/i");
  luminosityBlockNumber = 0;
  tree->Branch("luminosityBlockNumber", &luminosityBlockNumber, "luminosityBlockNumber/i");
  eventNumber= 0;
  tree->Branch("eventNumber", &eventNumber, "eventNumber/i");

  // event weight
  if(weight_.label() != ""){
    weight = 1;
    tree->Branch("weight", &weight, "weight/D");
  }
  
  // invariant mass from lepton, neutrino and leading jets
  MuNu4J=-1;
  ElNu4J=-1;
  mJJ=-1; 
  mWJJ=-1;
  tree->Branch("MuNu4J"    , &MuNu4J    , "MuNu4J/D"    );
  tree->Branch("ElNu4J"    , &ElNu4J    , "MuNu4J/D"    );                
  tree->Branch("MWJJ"      , &mWJJ      , "MWJJ/D"      );  

  hists_["MuNu4J"] = fs->make<TH1F>( "MuNu4J"  , "MuNu4J"  , 2500,  0. , 2500 );
  hists_["ElNu4J"] = fs->make<TH1F>( "ElNu4J"  , "ElNu4J"  , 2500,  0. , 2500 );
  hists_["MJJ"   ] = fs->make<TH1F>( "MJJ"     , "MJJ"     , 2500,  0. , 2500 );        
  hists_["MWJJ"  ] = fs->make<TH1F>( "MWJJ"    , "MWJJ"    , 160 ,  0. , 160  );  
  

}

/// fill variables
void
MixedObjectsAnalyzer::analyze(const edm::Event& event, const edm::EventSetup& iSetup)
{
  // Event
  edm::EventAuxiliary aux = event.eventAuxiliary();
  runNumber             = aux.run();
  luminosityBlockNumber = aux.luminosityBlock();
  eventNumber           = aux.event();

  //std::cout << runNumber << ":" << luminosityBlockNumber << ":" << eventNumber << std::endl;

  edm::Handle<edm::View< pat::MET > > MET_h;
  event.getByLabel(METSrc_, MET_h);
  
  edm::Handle<edm::View< pat::Muon > > muons_h;
  event.getByLabel(MuonSrc_, muons_h);
  
  edm::Handle<edm::View< pat::Electron > > electrons_h;
  event.getByLabel(ElectronSrc_, electrons_h);
  
  edm::Handle<edm::View< pat::Jet > > jets_h;
  event.getByLabel(JetSrc_, jets_h);
  
  edm::Handle<std::vector<reco::Vertex> > vertecies_h;
  event.getByLabel(VertexSrc_, vertecies_h);
  
  edm::Handle<double> weight_h;
  event.getByLabel(weight_, weight_h);

  // event weight
  weight = weight_h.isValid() ? *weight_h : 1.;

  // invariant masses (measure for mttbar)
  MuNu4J=-1;
  ElNu4J=-1;
  if(jets_h->size()>3&&MET_h->size()>0){
    if(muons_h->size()>0){
      MuNu4J=(muons_h->at(0).p4()+MET_h->at(0).p4()+jets_h->at(0).p4()+jets_h->at(1).p4()+jets_h->at(2).p4()+jets_h->at(3).p4()).mass();
      hists_["MuNu4J"]->Fill(MuNu4J, weight);
      //std::cout << "mu: " << MuNu4J << std::endl;
    }
    if(electrons_h->size()>0){ 
      ElNu4J=(electrons_h->at(0).p4()+MET_h->at(0).p4()+jets_h->at(0).p4()+jets_h->at(1).p4()+jets_h->at(2).p4()+jets_h->at(3).p4()).mass();
      hists_["ElNu4J"]->Fill(ElNu4J, weight);
      //std::cout << "el: " << ElNu4J << std::endl;
    }
  }
  // invariant jet-jet mass (measure for W mass)
  mJJ=-1;
  mWJJ=-1;
  for(edm::View< pat::Jet>::const_iterator jetsA=jets_h->begin(); jetsA!=jets_h->end(); ++jetsA){
    for(edm::View< pat::Jet>::const_iterator jetsB=jets_h->begin(); jetsB!=jets_h->end(); ++jetsB){      
      // take care of double counting
      if(jetsB>jetsA){
	mJJ=(jetsA->p4()+jetsB->p4()).mass();
	if(mWJJ==-1) mWJJ=mJJ;
	else if(std::abs(mJJ-80.4)<std::abs(mWJJ-80.4)) mWJJ=mJJ;
	// all invariant masses
	hists_["MJJ"]->Fill(mJJ, weight);
      }
    }
  }
  // jet-jet invariant mass closest to w mass
  if(mWJJ!=-1) hists_["MWJJ"]->Fill(mWJJ, weight);   

  tree->Fill();
}

void
MixedObjectsAnalyzer::endJob()
{

}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( MixedObjectsAnalyzer );
