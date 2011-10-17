#include "TopAnalysis/TopAnalyzer/plugins/TemplateTreeWriter.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/Utilities/interface/EDMException.h"

TemplateTreeWriter::TemplateTreeWriter(const ParameterSet& cfg)
{
  MET_      = cfg.getParameter<InputTag> ("MET"     ),
  muons_    = cfg.getParameter<InputTag> ("muons"   ),
  allMuons_ = cfg.getParameter<InputTag> ("allMuons");
  //ndof_     = cfg.getParameter<unsigned int>("ndof"    )  
}

TemplateTreeWriter::~TemplateTreeWriter()
{
}

void
TemplateTreeWriter::beginJob()
{
  edm::Service<TFileService> fs;
  if( !fs ){
    throw edm::Exception( edm::errors::Configuration,
                          "TFile Service is not registered in cfg file" ); 
  }
  
  tree = fs->make<TTree>("templateTree","templateTree",0);
  tree->Branch("MET", &MET, "MET/F");
  tree->Branch("genMET", &genMET, "genMET/F");
  tree->Branch("lepET", &lepET, "lepET/F");
  tree->Branch("lepEta", &lepEta, "lepEta/F");
  tree->Branch("lepPhi", &lepPhi, "lepPhi/F");
  tree->Branch("HTlep", &HTlep, "HTlep/F");
  tree->Branch("relIso", &relIso, "relIso/F");
  tree->Branch("MT", &MT, "MT/F");
  tree->Branch("mMuMu", &mMuMu, "mMuMu/F");
}

void
TemplateTreeWriter::analyze(const Event& evt, const EventSetup&)
{

  edm::Handle<edm::View<pat::MET> > METHandle;
  evt.getByLabel(MET_, METHandle);
  edm::View<pat::MET> met = *METHandle;

  edm::Handle<edm::View<pat::Muon> > muonHandle;
  evt.getByLabel(muons_, muonHandle);
  edm::View<pat::Muon> muon = *muonHandle;

  edm::Handle<edm::View<pat::Muon> > allMuonHandle;
  evt.getByLabel(allMuons_, allMuonHandle);
  edm::View<pat::Muon> allMuons = *allMuonHandle;

  if(met.begin()->et() && muon.size() && muon.begin()->pt()){
    MET = met.begin()->et();
    genMET = 0.;
    if(met.begin()->genMET())genMET = met.begin()->genMET()->et();
    lepET = muon.begin()->pt();
    lepEta = muon.begin()->eta();
    lepPhi = muon.begin()->phi();
    HTlep = MET+lepET;
    relIso = (muon.begin()->trackIso()+muon.begin()->ecalIso()+muon.begin()->hcalIso())/muon.begin()->pt();
    MT = sqrt((MET+muon.begin()->et())*(MET+muon.begin()->et())-((met.begin()->px()+muon.begin()->px())*(met.begin()->px()+muon.begin()->px())+(met.begin()->py()+muon.begin()->py())*(met.begin()->py()+muon.begin()->py())));
    mMuMu = 0.;
    for(edm::View<pat::Muon>::const_iterator muon_iter = allMuons.begin(); muon_iter!=allMuons.end(); ++muon_iter){
      if(muon_iter->charge()==muon.begin()->charge())continue;
      float mMuMuTemp = (muon_iter->p4()+muon.begin()->p4()).mass();
      if(fabs(mMuMuTemp-91.188)<fabs(mMuMu-91.188))mMuMu = mMuMuTemp;
    }

    tree->Fill();
  }
}

void
TemplateTreeWriter::endJob()
{
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( TemplateTreeWriter );
