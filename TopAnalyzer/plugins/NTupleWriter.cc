// -*- C++ -*-
//
// Package:    NTupleWriter_two
// Class:      NTupleWriter_two
// 
/**\class NTupleWriter_two NTupleWriter_two.cc TopAnalysis/NTupleWriter_two/src/NTupleWriter_two.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Jan Kieseler,,,DESY
//         Created:  Thu Aug 11 16:37:05 CEST 2011
// $Id: NTupleWriter.cc,v 1.1 2011/10/11 11:33:31 jkiesele Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "TopAnalysis/TopAnalyzer/plugins/FullLepHypothesesAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TTree.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"

#include "DataFormats/Candidate/interface/CompositeCandidate.h"
#include "TopAnalysis/TopAnalyzer/interface/PUEventWeight.h"

#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include <string>
#include "TopAnalysis/TopAnalyzer/interface/DileptonEventWeight.h"

#include "TopAnalysis/TopAnalyzer/plugins/FullLepGenAnalyzer.h"
#include "TopAnalysis/TopUtils/interface/NameScheme.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "CommonTools/CandUtils/interface/AddFourMomenta.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "TopAnalysis/TopAnalyzer/interface/DileptonEventWeight.h"
#include "AnalysisDataFormats/TopObjects/interface/TtGenEvent.h"
#include "TopQuarkAnalysis/TopSkimming/interface/TtDecayChannelSelector.h"

//
// class declaration
//

class NTupleWriter : public edm::EDAnalyzer {
   public:
      explicit NTupleWriter(const edm::ParameterSet&);
      ~NTupleWriter();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      const reco::Candidate* getTauDaughter(const reco::Candidate*);
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

      // ----------member data ---------------------------

  edm::InputTag jets_, met_, puWeight_, lepSFWeight_, trigResults_, dType_ , elecs_, muons_, vertices_, src_ , FullLepEvt_, hypoKey_;
  bool includeTrig_, useLeadingJets_, useBtagging_;
  std::string bAlgo_;
  edm::ParameterSet conf_;
  double bCut_;


  TTree* Ntuple;

  int runno;
  int lumibl;
  int eventno;

  std::vector<std::string> datatype;

  ////////dileptons and leptons/////
  std::vector<double> VlepPt;
  std::vector<double> VlepEta ;
  std::vector<double> VlepPhi ;
  std::vector<double> VlepE ;
  std::vector<double> VlepPx ;
  std::vector<double> VlepPy ;
  std::vector<double> VlepPz ;
  std::vector<int>    VlepQ ; //and more possible
  std::vector<int>    VlepType; // -1 for electron, 1 for muon
  std::vector<double> VlepPfIso;
  std::vector<double> VlepCombIso;
  
  double GenTopE, GenTopPx, GenTopPy, GenTopPz, GenTopEta, GenTopRapidity, GenTopPhi, GenTopMass;
  double GenAntiTopE, GenAntiTopPx, GenAntiTopPy, GenAntiTopPz,GenAntiTopEta, GenAntiTopRapidity, GenAntiTopPhi, GenAntiTopMass;
  double GenLepE, GenLepPx, GenLepPy, GenLepPz,GenLepEta, GenLepRapidity, GenLepPhi, GenLepMass;
  double GenAntiLepE, GenAntiLepPx, GenAntiLepPy, GenAntiLepPz,GenAntiLepEta, GenAntiLepRapidity, GenAntiLepPhi, GenAntiLepMass;
  double GenNuE, GenNuPx, GenNuPy, GenNuPz,GenNuEta, GenNuRapidity, GenNuPhi, GenNuMass;
  double GenAntiNuE, GenAntiNuPx, GenAntiNuPy, GenAntiNuPz,GenAntiNuEta, GenAntiNuRapidity, GenAntiNuPhi, GenAntiNuMass;
  double GenBE, GenBPx, GenBPy, GenBPz,GenBEta, GenBRapidity, GenBPhi, GenBMass;
  double GenAntiBE, GenAntiBPx, GenAntiBPy, GenAntiBPz, GenAntiBEta, GenAntiBRapidity, GenAntiBPhi, GenAntiBMass;

  double HypTopE, HypTopPx, HypTopPy, HypTopPz,HypTopEta, HypTopRapidity, HypTopPhi, HypTopMass;
  double HypAntiTopE, HypAntiTopPx, HypAntiTopPy, HypAntiTopPz,HypAntiTopEta, HypAntiTopRapidity, HypAntiTopPhi, HypAntiTopMass;
  double HypLepE, HypLepPx, HypLepPy, HypLepPz,HypLepEta, HypLepRapidity, HypLepPhi, HypLepMass;
  double HypAntiLepE, HypAntiLepPx, HypAntiLepPy, HypAntiLepPz,HypAntiLepEta, HypAntiLepRapidity, HypAntiLepPhi, HypAntiLepMass;
  double HypNuE, HypNuPx, HypNuPy, HypNuPz,HypNuEta, HypNuRapidity, HypNuPhi, HypNuMass;
  double HypAntiNuE, HypAntiNuPx, HypAntiNuPy, HypAntiNuPz,HypAntiNuEta, HypAntiNuRapidity, HypAntiNuPhi, HypAntiNuMass;
  double HypBE, HypBPx, HypBPy, HypBPz,HypBEta, HypBRapidity, HypBPhi, HypBMass;
  double HypAntiBE, HypAntiBPx, HypAntiBPy, HypAntiBPz,HypAntiBEta, HypAntiBRapidity, HypAntiBPhi, HypAntiBMass;


  /////////jets///////////
  std::vector<double> VjetPt;
  std::vector<double> VjetEta;


  std::vector<double> VjetPhi;

  std::vector<double> VjetBTagTCHE;
  std::vector<double> VjetBTagSSVHE;

  int jetMulti;

  /////////met///////////
  std::vector<double> VmetEt;

  std::vector<double> VmetPhi;

  ////////triggers/////////
  std::vector<std::string> VfiredTriggers;

  ///////////weight//////////
  double PUweight;
  double Lepweight;
  double weight;
  ////Vertices////

  int vertMulti;





};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
NTupleWriter::NTupleWriter(const edm::ParameterSet& iConfig):
  conf_(iConfig)
{

  muons_             =iConfig.getParameter<edm::InputTag>    ( "muons"      );
  elecs_             =iConfig.getParameter<edm::InputTag>    ( "elecs"      );
  jets_              =iConfig.getParameter<edm::InputTag>    ( "jets"           );
  met_               =iConfig.getParameter<edm::InputTag>    ( "met"            );
  vertices_          =iConfig.getParameter<edm::InputTag>    ( "vertices"            );
  src_               =iConfig.getParameter<edm::InputTag>    ("src"       );
  FullLepEvt_        =iConfig.getParameter<edm::InputTag>    ("FullLepEvent"    );
  hypoKey_           =iConfig.getParameter<edm::InputTag>    ("hypoKey"         ); 
  useLeadingJets_    =iConfig.getParameter<bool>             ("useLeadingJets"         ); 
  useBtagging_       =iConfig.getParameter<bool>             ("useBtagging"         ); 
  bAlgo_             =iConfig.getParameter<std::string>      ("bAlgorithm"     );      
  bCut_              =iConfig.getParameter<double>           ("bCut"        );

  puWeight_          =iConfig.getParameter<edm::InputTag>    ("weightPU"          );
  lepSFWeight_        =iConfig.getParameter<edm::InputTag>    ("weightLepSF"       );
  dType_             =iConfig.getParameter<edm::InputTag>    ("datatype"          );
  includeTrig_       =iConfig.getParameter<bool>             ("includeTrigger"          );
  trigResults_       =iConfig.getParameter<edm::InputTag>    ( "triggerResults" );


}


NTupleWriter::~NTupleWriter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
NTupleWriter::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   weight = getDileptonEventWeight(iEvent, puWeight_, lepSFWeight_);
   PUweight = getPUEventWeight(iEvent, puWeight_);
   //Lepweight = get
   /////////////clear vectors!!////////////////////////////////////
  edm::Handle<TtFullLeptonicEvent> FullLepEvt;
  iEvent.getByLabel(FullLepEvt_, FullLepEvt);

  edm::Handle<int> hypoKeyHandle;
  iEvent.getByLabel(hypoKey_, hypoKeyHandle);
  TtEvent::HypoClassKey& hypoKey = (TtEvent::HypoClassKey&) *hypoKeyHandle;

   runno=0;
   lumibl=0;
   eventno=0;

   datatype.clear();

   ////////dileptons and leptons/////
   VlepPt.clear();
   VlepEta.clear() ;
   VlepPhi.clear() ;
   VlepE.clear() ;
   VlepPx.clear() ;
   VlepPy.clear() ;
   VlepPz.clear() ;
   VlepQ.clear() ; 
   VlepType.clear() ;
   VlepPfIso.clear();
   VlepCombIso.clear();


   /////////jets///////////
   VjetPt.clear();
   VjetEta.clear();
   VjetPhi.clear();

   VjetBTagTCHE.clear();
   VjetBTagSSVHE.clear();


   /////////met///////////
   VmetEt.clear();
   VmetPhi.clear();


   /////////Triggers/////////
   VfiredTriggers.clear();

   //////vertices
   vertMulti=-1;
   GenTopPx=-1; GenTopPy=-1; GenTopPz=-1;
   GenAntiTopPx=-1; GenAntiTopPy=-1; GenAntiTopPz=-1;
   GenLepPx=-1; GenLepPy=-1; GenLepPz=-1;
   GenAntiLepPx=-1; GenAntiLepPy=-1; GenAntiLepPz=-1;
   GenNuPx=-1; GenNuPy=-1; GenNuPz=-1;
   GenAntiNuPx=-1; GenAntiNuPy=-1; GenAntiNuPz=-1;
   GenBPx=-1; GenBPy=-1; GenBPz=-1;
   GenAntiBPx=-1; GenAntiBPy=-1; GenAntiBPz=-1;

   HypTopPx=-1; HypTopPy=-1; HypTopPz=-1;
   HypAntiTopPx=-1; HypAntiTopPy=-1; HypAntiTopPz=-1;
   HypLepPx=-1; HypLepPy=-1; HypLepPz=-1;
   HypAntiLepPx=-1; HypAntiLepPy=-1; HypAntiLepPz=-1;
   HypNuPx=-1; HypNuPy=-1; HypNuPz=-1;
   HypAntiNuPx=-1; HypAntiNuPy=-1; HypAntiNuPz=-1;
   HypBPx=-1; HypBPy=-1; HypBPz=-1;
   HypAntiBPx=-1; HypAntiBPy=-1; HypAntiBPz=-1;

   GenTopE=-1; GenTopEta=-1;   GenTopRapidity=-1;   GenTopPhi=-1;   GenTopMass=-1;
   GenAntiTopE=-1;   GenAntiTopEta=-1;   GenAntiTopRapidity=-1;   GenAntiTopPhi=-1;   GenAntiTopMass=-1;
   GenLepE=-1;   GenLepEta=-1;   GenLepRapidity=-1;   GenLepPhi=-1;   GenLepMass=-1;
   GenAntiLepE=-1;   GenAntiLepEta=-1;   GenAntiLepRapidity=-1;   GenAntiLepPhi=-1;   GenAntiLepMass=-1;
   GenNuE=-1;   GenNuEta=-1;   GenNuRapidity=-1;   GenNuPhi=-1;   GenNuMass=-1;
   GenAntiNuE=-1;   GenAntiNuEta=-1;   GenAntiNuRapidity=-1;   GenAntiNuPhi=-1;   GenAntiNuMass=-1;
   GenBE=-1;   GenBEta=-1;   GenBRapidity=-1;   GenBPhi=-1;   GenBMass=-1;
   GenAntiBE=-1;   GenAntiBEta=-1;   GenAntiBRapidity=-1;   GenAntiBPhi=-1;   GenAntiBMass=-1;

   HypTopE=-1;HypTopEta=-1;   HypTopRapidity=-1;   HypTopPhi=-1;   HypTopMass=-1;
   HypAntiTopE=-1;   HypAntiTopEta=-1;   HypAntiTopRapidity=-1;   HypAntiTopPhi=-1;   HypAntiTopMass=-1;
   HypLepE=-1;   HypLepEta=-1;   HypLepRapidity=-1;   HypLepPhi=-1;   HypLepMass=-1;
   HypAntiLepE=-1;   HypAntiLepEta=-1;   HypAntiLepRapidity=-1;   HypAntiLepPhi=-1;   HypAntiLepMass=-1;
   HypNuE=-1;   HypNuEta=-1;   HypNuRapidity=-1;   HypNuPhi=-1;   HypNuMass=-1;
   HypAntiNuE=-1;   HypAntiNuEta=-1;   HypAntiNuRapidity=-1;   HypAntiNuPhi=-1;   HypAntiNuMass=-1;
   HypBE=-1;   HypBEta=-1;   HypBRapidity=-1;   HypBPhi=-1;   HypBMass=-1;
   HypAntiBE=-1;   HypAntiBEta=-1;   HypAntiBRapidity=-1;   HypAntiBPhi=-1;   HypAntiBMass=-1;


  datatype.push_back(dType_.encode());


  Handle<edm::View< pat::Jet > > jets;
  iEvent.getByLabel(jets_, jets);

  Handle<edm::View<pat::MET> > met;
  iEvent.getByLabel(met_, met);

  Handle<std::vector<pat::Muon> > muons;
  iEvent.getByLabel(muons_, muons);

  Handle<std::vector<pat::Electron> > electrons;
  iEvent.getByLabel(elecs_, electrons);

  //////////////////////////////dilepton and lepton properties/////////////////////

  //////Generator info
    Handle<TtGenEvent> genEvt;
  iEvent.getByLabel(src_, genEvt );

  int cmb = 0;
  if( !FullLepEvt->isHypoAvailable(hypoKey) || !FullLepEvt->isHypoValid(hypoKey)){
    //edm::LogInfo ( "NonValidHyp" ) << "Hypothesis not available for this event";
  }
  else if(useLeadingJets_==false && useBtagging_==false){//temp until I figure out what to do with ttbarbg sample
  }
  else{
    if(useLeadingJets_){
      bool foundSolution = false;
      for(size_t i=0;i<FullLepEvt->numberOfAvailableHypos(hypoKey);++i){
	int idx1 = FullLepEvt->jetLeptonCombination(hypoKey,i)[0];
	int idx2 = FullLepEvt->jetLeptonCombination(hypoKey,i)[1];      
	
	if((idx1==0 && idx2==1) || (idx1==1 && idx2==0)){
	  cmb = i;
	  //foundSolution = true;
	  break;
	}
      }
      //      if(!foundSolution){
      //	TopKin_[4]->SetBinContent(1,TopKin_[4]->GetBinContent(1)+1);
      //	return;
      //}
    }else if(useBtagging_){  // find best solution taking into account the b-tagging discriminators
      
      std::vector<int> bidcs;
      int idx=0;
      // find indices of b-tagged jets
      for(edm::View<pat::Jet>::const_iterator jet = jets->begin();jet != jets->end(); ++jet) {
	if(jet->bDiscriminator(bAlgo_) > bCut_) { 
	  bidcs.push_back(idx);
	}
	idx++;
      }
      
      int btagsinhypo;
      bool foundOneTagSolution = false;
      for(size_t i=0;i<FullLepEvt->numberOfAvailableHypos(hypoKey);++i){
	btagsinhypo = 0;
	for(size_t j=0; j<bidcs.size(); ++j){
	  if(FullLepEvt->jetLeptonCombination(hypoKey,i)[0]==bidcs[j]) btagsinhypo++;
	  if(FullLepEvt->jetLeptonCombination(hypoKey,i)[1]==bidcs[j]) btagsinhypo++;		
	}
	if(btagsinhypo==2){ // stop if hypothesis has two b-jets
	  cmb = i;
	  break;
	} else if(btagsinhypo==1 && !foundOneTagSolution){ // if one b-tag in hypothesis store index but go on and look for solution with 2 tags
	  cmb = i;
	  foundOneTagSolution = true;
	}
      }        
    }
    

    
    const reco::Candidate* Top    = FullLepEvt->top(hypoKey);
    const reco::Candidate* Wplus  = FullLepEvt->wPlus(hypoKey);
    const reco::Candidate* B      = FullLepEvt->b(hypoKey);
    const reco::Candidate* LepBar = FullLepEvt->leptonBar(hypoKey);
    const reco::Candidate* Nu     = FullLepEvt->neutrino(hypoKey);
    
    const reco::Candidate* TopBar = FullLepEvt->topBar(hypoKey);
    const reco::Candidate* Wminus = FullLepEvt->wMinus(hypoKey);
    const reco::Candidate* BBar   = FullLepEvt->bBar(hypoKey);
    const reco::Candidate* Lep    = FullLepEvt->lepton(hypoKey);
    const reco::Candidate* NuBar  = FullLepEvt->neutrinoBar(hypoKey); 
    
    

    HypTopE=Top->energy();HypTopPx=Top->px();HypTopPy=Top->py();HypTopPz=Top->pz();
    HypTopEta=Top->eta();
    HypTopRapidity=Top->rapidity();
    HypTopPhi=Top->phi();
    HypTopMass=Top->mass();
      
    HypAntiTopE=TopBar->energy();HypAntiTopPx=TopBar->px();HypAntiTopPy=TopBar->py();HypAntiTopPz=TopBar->pz();
    HypAntiTopEta=TopBar->eta();
    HypAntiTopRapidity=TopBar->rapidity();
    HypAntiTopPhi=TopBar->phi();
    HypAntiTopMass=TopBar->mass();
    
    HypLepE=Lep->energy();HypLepPx=Lep->px();HypLepPy=Lep->py();HypLepPz=Lep->pz();
    HypLepEta=Lep->eta();
    HypLepRapidity=Lep->rapidity();
    HypLepPhi=Lep->phi();
    HypLepMass=Lep->mass();
    
    HypAntiLepE=LepBar->energy();HypAntiLepPx=LepBar->px();HypAntiLepPy=LepBar->py();HypAntiLepPz=LepBar->pz();
    HypAntiLepEta=LepBar->eta();
    HypAntiLepRapidity=LepBar->rapidity();
    HypAntiLepPhi=LepBar->phi();
    HypAntiLepMass=LepBar->mass();
    
    HypNuE=Nu->energy();HypNuPx=Nu->px();HypNuPy=Nu->py();HypNuPz=Nu->pz();
    HypNuEta=Nu->eta();
    HypNuRapidity=Nu->rapidity();
    HypNuPhi=Nu->phi();
    HypNuMass=Nu->mass();
    
    HypAntiNuE=NuBar->energy();HypAntiNuPx=NuBar->px();HypAntiNuPy=NuBar->py();HypAntiNuPz=NuBar->pz();
    HypAntiNuEta=NuBar->eta();
    HypAntiNuRapidity=NuBar->rapidity();
    HypAntiNuPhi=NuBar->phi();
    HypAntiNuMass=NuBar->mass();
    
    HypBE=B->energy();HypBPx=B->px();HypBPy=B->py();HypBPz=B->pz();
    HypBEta=B->eta();
    HypBRapidity=B->rapidity();
    HypBPhi=B->phi();
    HypBMass=B->mass();
    
    HypAntiBE=BBar->energy();HypAntiBPx=BBar->px();HypAntiBPy=BBar->py();HypAntiBPz=BBar->pz();
    HypAntiBEta=BBar->eta();
    HypAntiBRapidity=BBar->rapidity();
    HypAntiBPhi=BBar->phi();
    HypAntiBMass=BBar->mass();
  }



  if( !FullLepEvt->genEvent() ){cout<<"NO GEN EVENT!!"<<endl;}
  else if(useLeadingJets_==false && useBtagging_==false){}
  else{
    //    if( FullLepEvt->genEvent()->isFullLeptonic() ){

    const reco::Candidate* genTop    = FullLepEvt->genTop();
    const reco::Candidate* genWplus  = FullLepEvt->genWPlus();
    const reco::Candidate* genB      = FullLepEvt->genB();
    const reco::Candidate* genLepBar = FullLepEvt->genLeptonBar();
    const reco::Candidate* genNu     = FullLepEvt->genNeutrino();
    
    const reco::Candidate* genTopBar = FullLepEvt->genTopBar();
    const reco::Candidate* genWminus = FullLepEvt->genWMinus();
    const reco::Candidate* genBBar   = FullLepEvt->genBBar();
    const reco::Candidate* genLep    = FullLepEvt->genLepton();
    const reco::Candidate* genNuBar  = FullLepEvt->genNeutrinoBar();
    
    GenTopE=genTop->energy();GenTopPx=genTop->px();GenTopPy=genTop->py();GenTopPz=genTop->pz();
    GenTopEta=genTop->eta();
    GenTopRapidity=genTop->rapidity();
    GenTopPhi=genTop->phi();
    GenTopMass=genTop->mass();
      
      GenAntiTopE=genTopBar->energy();GenAntiTopPx=genTopBar->px();GenAntiTopPy=genTopBar->py();GenAntiTopPz=genTopBar->pz();
      GenAntiTopEta=genTopBar->eta();
      GenAntiTopRapidity=genTopBar->rapidity();
      GenAntiTopPhi=genTopBar->phi();
      GenAntiTopMass=genTopBar->mass();
      
      GenLepE=genLep->energy();GenLepPx=genLep->px();GenLepPy=genLep->py();GenLepPz=genLep->pz();
      GenLepEta=genLep->eta();
      GenLepRapidity=genLep->rapidity();
      GenLepPhi=genLep->phi();
      GenLepMass=genLep->mass();
      
      GenAntiLepE=genLepBar->energy();GenAntiLepPx=genLepBar->px();GenAntiLepPy=genLepBar->py();GenAntiLepPz=genLepBar->pz();
      GenAntiLepEta=genLepBar->eta();
      GenAntiLepRapidity=genLepBar->rapidity();
      GenAntiLepPhi=genLepBar->phi();
      GenAntiLepMass=genLepBar->mass();
      
      GenNuE=genNu->energy();GenNuPx=genNu->px();GenNuPy=genNu->py();GenNuPz=genNu->pz();
      GenNuEta=genNu->eta();
      GenNuRapidity=genNu->rapidity();
      GenNuPhi=genNu->phi();
      GenNuMass=genNu->mass();

      GenAntiNuE=genNuBar->energy();GenAntiNuPx=genNuBar->px();GenAntiNuPy=genNuBar->py();GenAntiNuPz=genNuBar->pz();
      GenAntiNuEta=genNuBar->eta();
      GenAntiNuRapidity=genNuBar->rapidity();
      GenAntiNuPhi=genNuBar->phi();
      GenAntiNuMass=genNuBar->mass();
      
      GenBE=genB->energy();GenBPx=genB->px();GenBPy=genB->py();GenBPz=genB->pz();
      GenBEta=genB->eta();
      GenBRapidity=genB->rapidity();
      GenBPhi=genB->phi();
      GenBMass=genB->mass();
      
      GenAntiBE=genBBar->energy();GenAntiBPx=genBBar->px();GenAntiBPy=genBBar->py();GenAntiBPz=genBBar->pz();
      GenAntiBEta=genBBar->eta();
      GenAntiBRapidity=genBBar->rapidity();
      GenAntiBPhi=genBBar->phi();
      GenAntiBMass=genBBar->mass();
   
  }

   //////fill pfiso///maybe other iso??

  std::vector<pat::Muon>::const_iterator amuon  = muons->begin();
  std::vector<pat::Electron>::const_iterator anelectron  = electrons->begin();

  bool writemuon=false;
  bool writeelec=false;

  while(amuon < muons->end() || anelectron < electrons->end()){ //sort input leptons by pt

    writemuon=false;
    writeelec=false;

    if(amuon < muons->end() && anelectron < electrons->end()){
      if( amuon->pt() > anelectron->pt()) writemuon=true ;
      else writeelec=true;
    }
    if(anelectron == electrons->end())  writemuon=true ;
    if(amuon == muons->end())           writeelec=true;

    if(writemuon){
      //Fill muonstuff
      VlepPt.push_back(amuon->pt());
      VlepEta.push_back(amuon->eta()) ;
      VlepPhi.push_back(amuon->phi()) ;
      VlepE.push_back(amuon->energy()) ;
      VlepPx.push_back(amuon->px()) ;
      VlepPy.push_back(amuon->py()) ;
      VlepPz.push_back(amuon->pz()) ;
      VlepQ.push_back(amuon->charge()) ; 
      VlepType.push_back(1) ;
      VlepPfIso.push_back(((amuon->chargedHadronIso()+amuon->neutralHadronIso()+amuon->photonIso()) / amuon->pt()));
      VlepCombIso.push_back((amuon->trackIso()+amuon->caloIso())/amuon->pt());

      amuon++;
      
    }
    if(writeelec){
      //Fill elestuff 
      VlepPt.push_back(anelectron->pt());
      VlepEta.push_back(anelectron->eta()) ;
      VlepPhi.push_back(anelectron->phi()) ;
      VlepE.push_back(anelectron->energy()) ;
      VlepPx.push_back(anelectron->px()) ;
      VlepPy.push_back(anelectron->py()) ;
      VlepPz.push_back(anelectron->pz()) ;
      VlepQ.push_back(anelectron->charge()) ; 
      VlepType.push_back(-1) ;
      VlepPfIso.push_back(((anelectron->chargedHadronIso()+anelectron->neutralHadronIso()+anelectron->photonIso()) / anelectron->pt()));

      if( fabs(anelectron->superCluster()->eta()) > 1.479 ){
	VlepCombIso.push_back((anelectron->dr03TkSumPt()+anelectron->dr03EcalRecHitSumEt()+anelectron->dr03HcalTowerSumEt())/TMath::Max(20.,anelectron->pt()));
      }
      if( fabs(anelectron->superCluster()->eta()) <= 1.479 ){
	VlepCombIso.push_back((anelectron->dr03TkSumPt()+TMath::Max(0.,anelectron->dr03EcalRecHitSumEt()-1.)+anelectron->dr03HcalTowerSumEt())/TMath::Max(20.,anelectron->pt()));
      }

      anelectron++;
      
    }
  }

//   if(VlepPt.size() >2){
//     for(unsigned int i=0; i< VlepPt.size(); i++){
//       std::cout << VlepPt[i] << "    " << VlepType[i] << std::endl;
//     }
//     std::cout << '\n' << std::endl;
//   }


   ///////////////////////////////////Jet properties/////////////////////////

   jetMulti=jets->size();

   for (edm::View<pat::Jet>::const_iterator ajet  = jets->begin() ; ajet != jets->end(); ajet++)
    {
        VjetPt.push_back(ajet->pt());
	VjetEta.push_back(ajet->eta());
	VjetPhi.push_back(ajet->phi());

	VjetBTagTCHE.push_back(ajet->bDiscriminator("trackCountingHighEffBJetTags"));
	VjetBTagSSVHE.push_back(ajet->bDiscriminator("simpleSecondaryVertexHighEffBJetTags"));
    }








   ///////////////////////////////////Met properties///////////////////////////

   for (edm::View<pat::MET>::const_iterator Met  = met->begin() ; Met != met->end(); Met++)
     {
       VmetEt.push_back(Met->et());
       VmetPhi.push_back(Met->phi());
     }


   //////////////////////////////Event Info/////////////////////
  runno= iEvent.id().run();
  lumibl=iEvent.id().luminosityBlock();
  eventno=iEvent.id().event();


  //////////////////Trigger Stuff///////////////hltPaths_[i].c_str()



  if(includeTrig_){
    Handle<TriggerResults> trigResults;
    iEvent.getByLabel(trigResults_, trigResults);



    if(!trigResults.failedToGet()){
      int n_Triggers = trigResults->size();
      TriggerNames trigName = iEvent.triggerNames(*trigResults);

      for(int i_Trig = 0; i_Trig<n_Triggers; ++i_Trig){
	if(trigResults.product()->accept(i_Trig)){
	  VfiredTriggers.push_back(trigName.triggerName(i_Trig));
	}
      }
    }
  }

  edm::Handle<std::vector<reco::Vertex> > vertices;
  iEvent.getByLabel(vertices_, vertices);


  vertMulti=vertices->size();

  Ntuple ->Fill();

}


// ------------ method called once each job just before starting event loop  ------------
void 
NTupleWriter::beginJob()
{
  edm::Service<TFileService> fs;

  if( !fs ){
    throw edm::Exception( edm::errors::Configuration,
                          "TFile Service is not registered in cfg file" );
  }
  TFileDirectory NTupDir = fs->mkdir("../NTupDir");
  

  Ntuple=NTupDir.make<TTree>("NTuple","NTuple");


  ///////////////dilepton and lepton properties//////////
  Ntuple->Branch("lepPt",&VlepPt);
  Ntuple->Branch("lepEta",&VlepEta);
  Ntuple->Branch("lepPhi",&VlepPhi);
  Ntuple->Branch("lepE",&VlepE);
  Ntuple->Branch("lepPx",&VlepPx);
  Ntuple->Branch("lepPy",&VlepPy);
  Ntuple->Branch("lepPz",&VlepPz);
  Ntuple->Branch("lepQ",&VlepQ);
  Ntuple->Branch("lepType",&VlepType);
  Ntuple->Branch("lepPfIso",&VlepPfIso);
  Ntuple->Branch("lepCombIso",&VlepCombIso);


  /////////////jet properties////////////
  Ntuple->Branch("jetPt",&VjetPt);
  Ntuple->Branch("jetEta",&VjetEta);
  Ntuple->Branch("jetPhi",&VjetPhi);

  Ntuple->Branch("jetBTagTCHE",&VjetBTagTCHE);
  Ntuple->Branch("jetBTagSSVHE",&VjetBTagSSVHE);

  Ntuple->Branch("jetMulti",&jetMulti, "jetMulti/I");

  /////////////met properties///////////
  Ntuple->Branch("metEt",&VmetEt);

  Ntuple->Branch("metPhi",&VmetPhi);


  ///////////event info///////////
  Ntuple->Branch("runNumber",&runno, "runNumber/I");
  Ntuple->Branch("lumiBlock",&lumibl,"lumiBlock/I");
  Ntuple->Branch("eventNumber",&eventno, "eventNumber/I");

  Ntuple->Branch("dataType",&datatype);


  ////////////triggers//////////////////
  if(includeTrig_) Ntuple->Branch("firedTriggers",&VfiredTriggers);

  ////////////weight////////////
  Ntuple->Branch("PUweight",&PUweight, "PUweight/D");
  Ntuple->Branch("weight",&weight, "weight/D");

  /////////vertices

  Ntuple->Branch("vertMulti",&vertMulti, "vertMulti/I");

  ////////Gen Info
  Ntuple->Branch("GenTopE",&GenTopE, "GenTopE/D");Ntuple->Branch("GenTopPx",&GenTopPx, "GenTopPx/D");Ntuple->Branch("GenTopPy",&GenTopPy, "GenTopPy/D");Ntuple->Branch("GenTopPz",&GenTopPz, "GenTopPz/D");
  Ntuple->Branch("GenAntiTopE",&GenAntiTopE, "GenAntiTopE/D");Ntuple->Branch("GenAntiTopPx",&GenAntiTopPx, "GenAntiTopPx/D");Ntuple->Branch("GenAntiTopPy",&GenAntiTopPy, "GenAntiTopPy/D");Ntuple->Branch("GenAntiTopPz",&GenAntiTopPz, "GenAntiTopPz/D");
  Ntuple->Branch("GenLepE",&GenLepE, "GenLepE/D");Ntuple->Branch("GenLepPx",&GenLepPx, "GenLepPx/D");Ntuple->Branch("GenLepPy",&GenLepPy, "GenLepPy/D");Ntuple->Branch("GenLepPz",&GenLepPz, "GenLepPz/D");
  Ntuple->Branch("GenAntiLepE",&GenAntiLepE, "GenAntiLepE/D");Ntuple->Branch("GenAntiLepPx",&GenAntiLepPx, "GenAntiLepPx/D");Ntuple->Branch("GenAntiLepPy",&GenAntiLepPy, "GenAntiLepPy/D");Ntuple->Branch("GenAntiLepPz",&GenAntiLepPz, "GenAntiLepPz/D");
  Ntuple->Branch("GenNuE",&GenNuE, "GenNuE/D");Ntuple->Branch("GenNuPx",&GenNuPx, "GenNuPx/D");Ntuple->Branch("GenNuPy",&GenNuPy, "GenNuPy/D");Ntuple->Branch("GenNuPz",&GenNuPz, "GenNuPz/D");
  Ntuple->Branch("GenAntiNuE",&GenAntiNuE, "GenAntiNuE/D");Ntuple->Branch("GenAntiNuPx",&GenAntiNuPx, "GenAntiNuPx/D");Ntuple->Branch("GenAntiNuPy",&GenAntiNuPy, "GenAntiNuPy/D");Ntuple->Branch("GenAntiNuPz",&GenAntiNuPz, "GenAntiNuPz/D");
  Ntuple->Branch("GenBE",&GenBE, "GenBE/D");Ntuple->Branch("GenBPx",&GenBPx, "GenBPx/D");Ntuple->Branch("GenBPy",&GenBPy, "GenBPy/D");Ntuple->Branch("GenBPz",&GenBPz, "GenBPz/D");
  Ntuple->Branch("GenAntiBE",&GenAntiBE, "GenAntiBE/D");Ntuple->Branch("GenAntiBPx",&GenAntiBPx, "GenAntiBPx/D");Ntuple->Branch("GenAntiBPy",&GenAntiBPy, "GenAntiBPy/D");Ntuple->Branch("GenAntiBPz",&GenAntiBPz, "GenAntiBPz/D");

  Ntuple->Branch("GenTopEta",&GenTopEta, "GenTopEta/D");  Ntuple->Branch("GenTopRapidity",&GenTopRapidity, "GenTopRapidity/D");  Ntuple->Branch("GenTopPhi",&GenTopPhi, "GenTopPhi/D");  Ntuple->Branch("GenTopMass",&GenTopMass, "GenTopMass/D");



 Ntuple->Branch("GenAntiTopEta",&GenAntiTopEta, "GenAntiTopEta/D");  Ntuple->Branch("GenAntiTopRapidity",&GenAntiTopRapidity, "GenAntiTopRapidity/D");  Ntuple->Branch("GenAntiTopPhi",&GenAntiTopPhi, "GenAntiTopPhi/D");  Ntuple->Branch("GenAntiTopMass",&GenAntiTopMass, "GenAntiTopMass/D");


  Ntuple->Branch("GenLepEta",&GenLepEta, "GenLepEta/D");  Ntuple->Branch("GenLepRapidity",&GenLepRapidity, "GenLepRapidity/D");  Ntuple->Branch("GenLepPhi",&GenLepPhi, "GenLepPhi/D");  Ntuple->Branch("GenLepMass",&GenLepMass, "GenLepMass/D");


 Ntuple->Branch("GenAntiLepEta",&GenAntiLepEta, "GenAntiLepEta/D");  Ntuple->Branch("GenAntiLepRapidity",&GenAntiLepRapidity, "GenAntiLepRapidity/D");  Ntuple->Branch("GenAntiLepPhi",&GenAntiLepPhi, "GenAntiLepPhi/D");  Ntuple->Branch("GenAntiLepMass",&GenAntiLepMass, "GenAntiLepMass/D");


 Ntuple->Branch("GenNuEta",&GenNuEta, "GenNuEta/D");  Ntuple->Branch("GenNuRapidity",&GenNuRapidity, "GenNuRapidity/D");  Ntuple->Branch("GenNuPhi",&GenNuPhi, "GenNuPhi/D");  Ntuple->Branch("GenNuMass",&GenNuMass, "GenNuMass/D");


 Ntuple->Branch("GenAntiNuEta",&GenAntiNuEta, "GenAntiNuEta/D");  Ntuple->Branch("GenAntiNuRapidity",&GenAntiNuRapidity, "GenAntiNuRapidity/D");  Ntuple->Branch("GenAntiNuPhi",&GenAntiNuPhi, "GenAntiNuPhi/D");  Ntuple->Branch("GenAntiNuMass",&GenAntiNuMass, "GenAntiNuMass/D");


Ntuple->Branch("GenBEta",&GenBEta, "GenBEta/D");  Ntuple->Branch("GenBRapidity",&GenBRapidity, "GenBRapidity/D");  Ntuple->Branch("GenBPhi",&GenBPhi, "GenBPhi/D");  Ntuple->Branch("GenBMass",&GenBMass, "GenBMass/D");


Ntuple->Branch("GenAntiBEta",&GenAntiBEta, "GenAntiBEta/D");  Ntuple->Branch("GenAntiBRapidity",&GenAntiBRapidity, "GenAntiBRapidity/D");  Ntuple->Branch("GenAntiBPhi",&GenAntiBPhi, "GenAntiBPhi/D");  Ntuple->Branch("GenAntiBMass",&GenAntiBMass, "GenAntiBMass/D");
  

  //Hypothesis Info
  Ntuple->Branch("HypTopE",&HypTopE, "HypTopE/D");Ntuple->Branch("HypTopPx",&HypTopPx, "HypTopPx/D");Ntuple->Branch("HypTopPy",&HypTopPy, "HypTopPy/D");Ntuple->Branch("HypTopPz",&HypTopPz, "HypTopPz/D");
  Ntuple->Branch("HypAntiTopE",&HypAntiTopE, "HypAntiTopE/D");Ntuple->Branch("HypAntiTopPx",&HypAntiTopPx, "HypAntiTopPx/D");Ntuple->Branch("HypAntiTopPy",&HypAntiTopPy, "HypAntiTopPy/D");Ntuple->Branch("HypAntiTopPz",&HypAntiTopPz, "HypAntiTopPz/D");
  Ntuple->Branch("HypLepE",&HypLepE, "HypLepE/D");Ntuple->Branch("HypLepPx",&HypLepPx, "HypLepPx/D");Ntuple->Branch("HypLepPy",&HypLepPy, "HypLepPy/D");Ntuple->Branch("HypLepPz",&HypLepPz, "HypLepPz/D");
  Ntuple->Branch("HypAntiLepE",&HypAntiLepE, "HypAntiLepE/D");Ntuple->Branch("HypAntiLepPx",&HypAntiLepPx, "HypAntiLepPx/D");Ntuple->Branch("HypAntiLepPy",&HypAntiLepPy, "HypAntiLepPy/D");Ntuple->Branch("HypAntiLepPz",&HypAntiLepPz, "HypAntiLepPz/D");
  Ntuple->Branch("HypNuE",&HypNuE, "HypNuE/D");Ntuple->Branch("HypNuPx",&HypNuPx, "HypNuPx/D");Ntuple->Branch("HypNuPy",&HypNuPy, "HypNuPy/D");Ntuple->Branch("HypNuPz",&HypNuPz, "HypNuPz/D");
  Ntuple->Branch("HypAntiNuE",&HypAntiNuE, "HypAntiNuE/D");Ntuple->Branch("HypAntiNuPx",&HypAntiNuPx, "HypAntiNuPx/D");Ntuple->Branch("HypAntiNuPy",&HypAntiNuPy, "HypAntiNuPy/D");Ntuple->Branch("HypAntiNuPz",&HypAntiNuPz, "HypAntiNuPz/D");
  Ntuple->Branch("HypBE",&HypBE, "HypBE/D");Ntuple->Branch("HypBPx",&HypBPx, "HypBPx/D");Ntuple->Branch("HypBPy",&HypBPy, "HypBPy/D");Ntuple->Branch("HypBPz",&HypBPz, "HypBPz/D");
  Ntuple->Branch("HypAntiBE",&HypAntiBE, "HypAntiBE/D");Ntuple->Branch("HypAntiBPx",&HypAntiBPx, "HypAntiBPx/D");Ntuple->Branch("HypAntiBPy",&HypAntiBPy, "HypAntiBPy/D");Ntuple->Branch("HypAntiBPz",&HypAntiBPz, "HypAntiBPz/D");


Ntuple->Branch("HypTopEta",&HypTopEta, "HypTopEta/D");  Ntuple->Branch("HypTopRapidity",&HypTopRapidity, "HypTopRapidity/D");  Ntuple->Branch("HypTopPhi",&HypTopPhi, "HypTopPhi/D");  Ntuple->Branch("HypTopMass",&HypTopMass, "HypTopMass/D");


Ntuple->Branch("HypAntiTopEta",&HypAntiTopEta, "HypAntiTopEta/D");  Ntuple->Branch("HypAntiTopRapidity",&HypAntiTopRapidity, "HypAntiTopRapidity/D");  Ntuple->Branch("HypAntiTopPhi",&HypAntiTopPhi, "HypAntiTopPhi/D");  Ntuple->Branch("HypAntiTopMass",&HypAntiTopMass, "HypAntiTopMass/D");


 Ntuple->Branch("HypLepEta",&HypLepEta, "HypLepEta/D");  Ntuple->Branch("HypLepRapidity",&HypLepRapidity, "HypLepRapidity/D");  Ntuple->Branch("HypLepPhi",&HypLepPhi, "HypLepPhi/D");  Ntuple->Branch("HypLepMass",&HypLepMass, "HypLepMass/D");

Ntuple->Branch("HypAntiLepEta",&HypAntiLepEta, "HypAntiLepEta/D");  Ntuple->Branch("HypAntiLepRapidity",&HypAntiLepRapidity, "HypAntiLepRapidity/D");  Ntuple->Branch("HypAntiLepPhi",&HypAntiLepPhi, "HypAntiLepPhi/D");  Ntuple->Branch("HypAntiLepMass",&HypAntiLepMass, "HypAntiLepMass/D");

Ntuple->Branch("HypNuEta",&HypNuEta, "HypNuEta/D");  Ntuple->Branch("HypNuRapidity",&HypNuRapidity, "HypNuRapidity/D");  Ntuple->Branch("HypNuPhi",&HypNuPhi, "HypNuPhi/D");  Ntuple->Branch("HypNuMass",&HypNuMass, "HypNuMass/D");

Ntuple->Branch("HypAntiNuEta",&HypAntiNuEta, "HypAntiNuEta/D");  Ntuple->Branch("HypAntiNuRapidity",&HypAntiNuRapidity, "HypAntiNuRapidity/D");  Ntuple->Branch("HypAntiNuPhi",&HypAntiNuPhi, "HypAntiNuPhi/D");  Ntuple->Branch("HypAntiNuMass",&HypAntiNuMass, "HypAntiNuMass/D");

 Ntuple->Branch("HypBEta",&HypBEta, "HypBEta/D");  Ntuple->Branch("HypBRapidity",&HypBRapidity, "HypBRapidity/D");  Ntuple->Branch("HypBPhi",&HypBPhi, "HypBPhi/D");  Ntuple->Branch("HypBMass",&HypBMass, "HypBMass/D");

Ntuple->Branch("HypAntiBEta",&HypAntiBEta, "HypAntiBEta/D");  Ntuple->Branch("HypAntiBRapidity",&HypAntiBRapidity, "HypAntiBRapidity/D");  Ntuple->Branch("HypAntiBPhi",&HypAntiBPhi, "HypAntiBPhi/D");  Ntuple->Branch("HypAntiBMass",&HypAntiBMass, "HypAntiBMass/D");
  
}

// ------------ method called once each job just after ending the event loop  ------------
void 
NTupleWriter::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
NTupleWriter::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
NTupleWriter::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
NTupleWriter::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
NTupleWriter::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
NTupleWriter::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

const reco::Candidate* 
NTupleWriter::getTauDaughter(const reco::Candidate* tau)
{
  for(size_t i=0; i<tau->numberOfDaughters(); ++i){
    if(fabs(tau->daughter(i)->pdgId())==11 || fabs(tau->daughter(i)->pdgId())==13) return tau->daughter(i);
    else if(fabs(tau->daughter(i)->pdgId())==15) return getTauDaughter(tau->daughter(i));
  }
  //return orgiginal tau if nothing found
  edm::LogWarning ( "No Tau Daughter" ) << "neither electron nor muon daughter found.";
  return tau;
} 


//define this as a plug-in
DEFINE_FWK_MODULE(NTupleWriter);
