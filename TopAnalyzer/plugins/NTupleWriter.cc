// -*- C++ -*-
//
// Package:    NTupleWriter_two
// Class:      NTupleWriter_two
//
/* *\class NTupleWriter_two NTupleWriter_two.cc TopAnalysis/NTupleWriter_two/src/NTupleWriter_two.cc

Description: [one line class summary]

Implementation:
[Notes on implementation]
*/
//
// Original Author:  Jan Kieseler,,,DESY
//         Created:  Thu Aug 11 16:37:05 CEST 2011
// $Id: NTupleWriter.cc,v 1.29 2012/09/18 11:34:33 iasincru Exp $
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
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"

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
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h" //###############


#include <TLorentzVector.h>

//
// class declaration
//
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > LV;
const char * LVstr = "ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> >";
const char * VLVstr = "std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >";



class NTupleWriter : public edm::EDAnalyzer
{
public:
  explicit NTupleWriter ( const edm::ParameterSet& );
  ~NTupleWriter();

  static void fillDescriptions ( edm::ConfigurationDescriptions& descriptions );


private:
  virtual void beginJob() ;
  virtual void analyze ( const edm::Event&, const edm::EventSetup& );
  virtual void endJob() ;

  virtual void beginRun ( edm::Run const&, edm::EventSetup const& );
  virtual void endRun ( edm::Run const&, edm::EventSetup const& );
  virtual void beginLuminosityBlock ( edm::LuminosityBlock const&, edm::EventSetup const& );
  virtual void endLuminosityBlock ( edm::LuminosityBlock const&, edm::EventSetup const& );
  void clearVariables();
  int getTriggerBits ( const edm::Event& iEvent, const edm::Handle< edm::TriggerResults >& trigResults );
  int getTriggerBits (const std::vector< std::string > &trigName );
  int getJetType ( const pat::Jet *jet );

  void AssignLeptonAndTau ( const reco::GenParticle* lepton, LV &GenLepton, int &pdgid, LV &GenTau );
  bool isTau( const reco::GenParticle* lepton);
  const reco::GenParticle* getTauDaughter(const reco::GenParticle* tau);
  // ----------member data ---------------------------

  std::map<std::string, int> triggerMap_;
  edm::InputTag inTag_PUSource;
  edm::InputTag weightPU_, weightPU3D_, weightPU_Up_, weightPU_Down_, weightLepSF_, weightKinFit_;
  edm::InputTag elecs_, muons_, jets_, met_;
  edm::InputTag vertices_, genEvent_ , FullLepEvt_, hypoKey_;
  edm::InputTag genParticles_;
  edm::InputTag genJets_;
  edm::InputTag bIndex_;
  edm::InputTag antiBIndex_;

  edm::InputTag bHadJetIdx_, antibHadJetIdx_;
  edm::InputTag BHadrons_, AntiBHadrons_;
  edm::InputTag BHadronFromTopB_, AntiBHadronFromTopB_;
  edm::InputTag BHadronVsJet_, AntiBHadronVsJet_;

  bool includeTrig_, isTtBarSample_;
  edm::InputTag dType_ , trigResults_, decayMode_;
  std::string directory_;

  TTree* Ntuple;

  unsigned int runno;
  unsigned int lumibl;
  unsigned int eventno;
  unsigned int triggerBits;

  std::vector<std::string> datatype;

  ////////dileptons and leptons/////
  std::vector<LV>     Vlep;
  std::vector<int>    VlepQ ; //and more possible
  std::vector<int>    VlepType; // -1 for electron, 1 for muon
  std::vector<double> VlepPfIso;
  std::vector<double> VlepCombIso;
  std::vector<int>    VlepTrigger;

  //True level info from FullLepGenEvent
  LV GenTop, GenAntiTop;
  LV GenLepton, GenAntiLepton;
  int GenLeptonPdgId, GenAntiLeptonPdgId;
  LV GenTau, GenAntiTau;
  LV GenNeutrino, GenAntiNeutrino;
  LV GenB, GenAntiB;
  //  LV HadronGenB, HadronGenAntiB;
  LV GenWPlus, GenWMinus;

  std::vector<int>      VBHadJetIdx;
  std::vector<int>      VAntiBHadJetIdx;
  std::vector<LV>       VBHadron, VAntiBHadron;
  std::vector<bool>     VBHadFromTop, VAntiBHadFromTop;
  std::vector<int>      VBHadVsJet, VAntiBHadVsJet;


  //Complete true level info
  std::vector<LV> GenParticleP4;
  std::vector<int> GenParticlePdgId;
  std::vector<int> GenParticleStatus;

  std::vector<LV> HypTop;
  std::vector<LV> HypAntiTop;
  std::vector<LV> HypLepton;
  std::vector<LV> HypAntiLepton;
  std::vector<LV> HypNeutrino;
  std::vector<LV> HypAntiNeutrino;
  std::vector<LV> HypB;
  std::vector<LV> HypAntiB;
  std::vector<LV> HypWPlus;
  std::vector<LV> HypWMinus;
  std::vector<int> HypJet0index;
  std::vector<int> HypJet1index;


  int decayMode;

  /////////jets///////////

  std::vector<LV> VallGenJets;
  std::vector<LV> VgenJet;
  std::vector<LV> Vjet;
  std::vector<int> VjetType;
  std::vector<double> VjetBTagTCHE;
  std::vector<double> VjetBTagTCHP;
  std::vector<double> VjetBTagJetProbability;
  std::vector<double> VjetBTagJetBProbability;
  std::vector<double> VjetBTagSSVHE;
  std::vector<double> VjetBTagSSVHP;
  std::vector<double> VjetBTagCSV;
  std::vector<double> VjetBTagCSVMVA;


  /////////met///////////
  std::vector<double> VmetEt;
  std::vector<double> VmetPhi;

  ////////triggers/////////
  std::vector<std::string> VfiredTriggers;

  ///////////weight//////////
  double weightMCatNLO;
  double weightPU;
  double weightPU3D;
  double weightPU_Down;
  double weightPU_Up;
  double weightLepSF;
  double weightKinFit;
  double weightTotal;

  ////Vertices////
  int vertMulti;
  int vertMultiTrue;

  const LV dummy;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

void NTupleWriter::AssignLeptonAndTau ( const reco::GenParticle* lepton, LV& GenLepton, int& pdgid, LV& GenTau )
{
  const reco::GenParticle *finalLepton;
  if (isTau(lepton)) {
    GenTau = lepton->p4();
    finalLepton = getTauDaughter(lepton);
  } else {
    GenTau = dummy;
    finalLepton = lepton;
  }
  GenLepton = finalLepton->p4();
  pdgid = finalLepton->pdgId();
}


//
// constructors and destructor
//
NTupleWriter::NTupleWriter ( const edm::ParameterSet& iConfig ) :
  inTag_PUSource(iConfig.getParameter<edm::InputTag>("PUSource") ),
  weightPU_ ( iConfig.getParameter<edm::InputTag> ( "weightPU" ) ),
  //  weightPU3D_(iConfig.getParameter<edm::InputTag> ( "weightPU3D" ) ),
  weightPU_Up_ ( iConfig.getParameter<edm::InputTag> ( "weightPU_Up" ) ),
  weightPU_Down_ ( iConfig.getParameter<edm::InputTag> ( "weightPU_Down" ) ),
  weightLepSF_ ( iConfig.getParameter<edm::InputTag> ( "weightLepSF" ) ),
  weightKinFit_( iConfig.getParameter<edm::InputTag> ( "weightKinFit" ) ),
  elecs_ ( iConfig.getParameter<edm::InputTag> ( "elecs" ) ),
  muons_ ( iConfig.getParameter<edm::InputTag> ( "muons" ) ),
  jets_ ( iConfig.getParameter<edm::InputTag> ( "jets" ) ),
  met_ ( iConfig.getParameter<edm::InputTag> ( "met" ) ),

  vertices_ ( iConfig.getParameter<edm::InputTag> ( "vertices" ) ),
  genEvent_ ( iConfig.getParameter<edm::InputTag> ( "src" ) ),
  FullLepEvt_ ( iConfig.getParameter<edm::InputTag> ( "FullLepEvent" ) ),
  hypoKey_ ( iConfig.getParameter<edm::InputTag> ( "hypoKey" ) ),
  genParticles_( iConfig.getParameter<edm::InputTag> ( "genParticles" ) ),

  genJets_   (iConfig.getParameter<edm::InputTag>("genJets")),
  bIndex_    (iConfig.getParameter<edm::InputTag>("BJetIndex")),
  antiBIndex_(iConfig.getParameter<edm::InputTag>("AntiBJetIndex")),

  //Input from GenLevelBJetProducer
  bHadJetIdx_(iConfig.getParameter<edm::InputTag> ("BHadJetIndex")),
  antibHadJetIdx_(iConfig.getParameter<edm::InputTag> ("AntiBHadJetIndex")),
  BHadrons_(iConfig.getParameter<edm::InputTag> ("BHadrons")),
  AntiBHadrons_(iConfig.getParameter<edm::InputTag> ("AntiBHadrons")),
  BHadronFromTopB_ (iConfig.getParameter<edm::InputTag> ("BHadronFromTopB")),
  AntiBHadronFromTopB_(iConfig.getParameter<edm::InputTag> ("AntiBHadronFromTopB")),
  BHadronVsJet_(iConfig.getParameter<edm::InputTag> ("BHadronVsJet")),
  AntiBHadronVsJet_(iConfig.getParameter<edm::InputTag> ("AntiBHadronVsJet")),

  includeTrig_ ( iConfig.getParameter<bool> ( "includeTrigger" ) ),
  isTtBarSample_ ( iConfig.getParameter<bool> ( "isTtBarSample" ) ),

  dType_ ( iConfig.getParameter<edm::InputTag> ( "datatype" ) ),
  trigResults_ ( iConfig.getParameter<edm::InputTag> ( "triggerResults" ) ),
  decayMode_ ( iConfig.getParameter<edm::InputTag> ( "decayMode" ) ),

  directory_ ( iConfig.getParameter<std::string>("directory")),

  dummy(0, 0, 0, 0)
{
  
  //WARNING: The trigger map can be used either for a specific version, e.g. Trig_v6
  //or for any version, Trig_v*. NOT supported: Trig_v1* - the star captures ALL digits!
  //use first 8 bits for mumu
  triggerMap_["HLT_DoubleMu6_v*"] = 1;
  triggerMap_["HLT_DoubleMu7_v*"] = 2;
  triggerMap_["HLT_Mu13_Mu8_v*"] = 4;
  triggerMap_["HLT_Mu17_Mu8_v*"] = 8;
  triggerMap_["HLT_DoubleMu45_v*"] = 0x10;
  triggerMap_["HLT_Mu17_TkMu8_v*"] = 0x20;

  //use bits 9 to 16 for mu e
  triggerMap_["HLT_Mu8_Ele17_CaloIdL_v*"] = 0x100;
  triggerMap_["HLT_Mu17_Ele8_CaloIdL_v*"] = 0x200;
  triggerMap_["HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_v*"] = 0x400;
  triggerMap_["HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_v*"] = 0x800;
  triggerMap_["HLT_Mu10_Ele10_CaloIdL_v*"] = 0x1000;
  triggerMap_["HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v*"] = 0x2000;
  triggerMap_["HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v*"] = 0x4000;


  //use bits 17-24 for ee
  triggerMap_["HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v*"] = 0x10000;
  triggerMap_["HLT_Ele17_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_v*"] = 0x20000;
  triggerMap_["HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v*"] = 0x40000;
  triggerMap_["HLT_DoubleEle45_CaloIdL_v*"] = 0x80000;


  //use bit 32 for general trigger to avoid false for unmatched triggers
  triggerMap_["general"] = 0x80000000;
}


NTupleWriter::~NTupleWriter()
{

  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}

bool NTupleWriter::isTau(const reco::GenParticle *lepton) {
  return std::abs(lepton->pdgId()) == 15;
}

const reco::GenParticle*
NTupleWriter::getTauDaughter(const reco::GenParticle* tau)
{
  for (size_t i = 0; i < tau->numberOfDaughters(); ++i) {
    const reco::GenParticle* daughter = dynamic_cast<const reco::GenParticle*>(tau->daughter(i));
    if (std::abs(daughter->pdgId()) == 11 || std::abs(daughter->pdgId()) == 13)
      return daughter;
    else if (isTau(daughter))
      return getTauDaughter(daughter);
  }
  return tau;
}



//
// member functions
//

// ------------ method called for each event  ------------
void
NTupleWriter::analyze ( const edm::Event& iEvent, const edm::EventSetup& iSetup )
{
  clearVariables();

  //##################### MC weights for MCatNLO ###############
  if ( ! iEvent.isRealData() ) {
    edm::Handle<GenEventInfoProduct> evt_info;
    iEvent.getByType(evt_info);
    weightMCatNLO = evt_info->weight();
  }
  else weightMCatNLO = 0.;

  //#############################################################

  weightPU = getPUEventWeight( iEvent, weightPU_ ); //#######

  //std::cout << "[NTupleWriter::analyze] weightPU = " << getPUEventWeight(iEvent, weightPU_) << " weightMC = " << weightMC << " weightPU*weightMC = " << weightPU << std::endl; //#######

  //weightPU3D = getPUEventWeight( iEvent, weightPU3D_);
  weightPU_Up = getPUEventWeight( iEvent, weightPU_Up_ );
  weightPU_Down = getPUEventWeight( iEvent, weightPU_Down_ );
  weightLepSF = 0; weightKinFit = 0; weightTotal = 0;
  try {
    weightLepSF = getDileptonSFWeight(iEvent, weightLepSF_);
    weightKinFit = getWeight(iEvent, weightKinFit_);
    weightTotal = getDileptonEventWeight ( iEvent, weightPU_, weightLepSF_ );
  } catch (cms::Exception e_dummy) {};

  edm::Handle<int> decayModeH;
  iEvent.getByLabel ( decayMode_, decayModeH );
  decayMode = decayModeH.failedToGet() ? 0 : *decayModeH;

  datatype.push_back ( dType_.encode() );

  edm::Handle<TtFullLeptonicEvent> FullLepEvt;
  iEvent.getByLabel ( FullLepEvt_, FullLepEvt );

  edm::Handle<int> hypoKeyHandle;
  iEvent.getByLabel ( hypoKey_, hypoKeyHandle );
  if (! hypoKeyHandle.failedToGet()) {
    TtEvent::HypoClassKey& hypoKey = ( TtEvent::HypoClassKey& ) *hypoKeyHandle;

    //////////////////////////////dilepton and lepton properties/////////////////////

    if (FullLepEvt->isHypoAvailable(hypoKey) && FullLepEvt->isHypoValid(hypoKey))
      {
        for ( size_t i=0; i<FullLepEvt->numberOfAvailableHypos (hypoKey); ++i )
          {
            const reco::Candidate* Top    = FullLepEvt->top ( hypoKey, i );
            const reco::Candidate* TopBar = FullLepEvt->topBar ( hypoKey, i );
            const reco::Candidate* Lep    = FullLepEvt->lepton ( hypoKey, i );
            const reco::Candidate* LepBar = FullLepEvt->leptonBar ( hypoKey, i );
            const reco::Candidate* Nu     = FullLepEvt->neutrino ( hypoKey, i );
            const reco::Candidate* NuBar  = FullLepEvt->neutrinoBar ( hypoKey, i );
            const reco::Candidate* B      = FullLepEvt->b ( hypoKey, i );
            const reco::Candidate* BBar   = FullLepEvt->bBar ( hypoKey, i );
            const reco::Candidate* Wplus  = FullLepEvt->wPlus ( hypoKey, i );
            const reco::Candidate* Wminus = FullLepEvt->wMinus ( hypoKey, i );

            HypTop.push_back(Top->p4());
            HypAntiTop.push_back( TopBar->p4() );
            HypLepton.push_back( Lep->p4() );
            HypAntiLepton.push_back( LepBar->p4() );
            HypNeutrino.push_back( Nu->p4() );
            HypAntiNeutrino.push_back( NuBar->p4() );
            HypB.push_back( B->p4() );
            HypAntiB.push_back( BBar->p4() );
            HypWPlus.push_back( Wplus->p4());
            HypWMinus.push_back(Wminus->p4());

            HypJet0index.push_back(FullLepEvt->jetLeptonCombination ( hypoKey,i ) [0]);
            HypJet1index.push_back(FullLepEvt->jetLeptonCombination ( hypoKey,i ) [1]);

          }
      }

  }

  if ( isTtBarSample_ )
    {

      //Generator info
      edm::Handle<TtGenEvent> genEvt;
      iEvent.getByLabel ( genEvent_, genEvt );
      if (! genEvt.failedToGet())
        {
          GenTop = genEvt->top()->p4(); GenAntiTop = genEvt->topBar()->p4();
          AssignLeptonAndTau(genEvt->lepton(), GenLepton, GenLeptonPdgId, GenTau);
          AssignLeptonAndTau(genEvt->leptonBar(), GenAntiLepton, GenAntiLeptonPdgId, GenAntiTau);
          GenB = genEvt->b()->p4(); GenAntiB = genEvt->bBar()->p4();
          GenNeutrino = genEvt->neutrino()->p4(); GenAntiNeutrino = genEvt->neutrinoBar()->p4();
          GenWPlus = genEvt->wPlus()->p4(); GenWMinus = genEvt->wMinus()->p4();


          edm::Handle<reco::GenJetCollection> genJets;
          iEvent.getByLabel(genJets_, genJets);

          for ( std::vector< reco::GenJet >::const_iterator aJet = genJets->begin(); aJet != genJets->end(); ++aJet) {
            VallGenJets.push_back(aJet->p4());
          }

          //find the b jets corresponding to b QUARKS (DeltaR selection)
          //         edm::Handle<int> BJetIndex;
          //         iEvent.getByLabel(bIndex_, BJetIndex );
          //         edm::Handle<int> AntiBJetIndex;
          //         iEvent.getByLabel(antiBIndex_, AntiBJetIndex);
          //    HadronGenAntiB = dummy;
          //    HadronGenB = dummy;
          //         if (*BJetIndex >= 0) (HadronGenB = genJets->at(*BJetIndex).p4());
          //         if (*AntiBJetIndex >= 0) (HadronGenAntiB = genJets->at(*AntiBJetIndex).p4());


          edm::Handle<std::vector<int> > BHadJetIndex;
          iEvent.getByLabel(bHadJetIdx_, BHadJetIndex);
          edm::Handle<std::vector<int> > AntiBHadJetIndex;
          iEvent.getByLabel(antibHadJetIdx_, AntiBHadJetIndex);

          for (int i=0; i<(int) BHadJetIndex->size(); ++i){  VBHadJetIdx.push_back(BHadJetIndex->at(i));};
          for (int i=0; i<(int) AntiBHadJetIndex->size(); ++i){  VAntiBHadJetIdx.push_back(AntiBHadJetIndex->at(i));};


          edm::Handle<std::vector<reco::GenParticle> > BHadrons;
          iEvent.getByLabel(BHadrons_, BHadrons);
          edm::Handle<std::vector<reco::GenParticle> > AntiBHadrons;
          iEvent.getByLabel(AntiBHadrons_, AntiBHadrons);


          for (std::vector<reco::GenParticle>::const_iterator it=BHadrons->begin(); it!=BHadrons->end(); ++it){VBHadron.push_back(it->p4());}
          for (std::vector<reco::GenParticle>::const_iterator it=AntiBHadrons->begin(); it!=AntiBHadrons->end(); ++it){VAntiBHadron.push_back(it->p4());}
          //    for (int i=0; i< (int) BHadrons->size(); ++i){  VBHadron.push_back(BHadrons->at(i).p4());}
          //    for (int i=0; i< (int) AntiBHadrons->size(); ++i){      VAntiBHadron.push_back(AntiBHadrons->at(i).p4());}


          edm::Handle<std::vector<bool> > BHadronFromTopB;
          iEvent.getByLabel(BHadronFromTopB_, BHadronFromTopB);
          edm::Handle<std::vector<bool> > AntiBHadronFromTopB;
          iEvent.getByLabel(AntiBHadronFromTopB_, AntiBHadronFromTopB);
          for (int i=0; i<(int) BHadronFromTopB->size(); ++i){  VBHadFromTop.push_back(BHadronFromTopB->at(i));}
          for (int i=0; i<(int) AntiBHadronFromTopB->size(); ++i){VAntiBHadFromTop.push_back(AntiBHadronFromTopB->at(i));}

          edm::Handle<std::vector<int> > BHadronVsJet;
          iEvent.getByLabel(BHadronVsJet_, BHadronVsJet);
          edm::Handle<std::vector<int> > AntiBHadronVsJet;
          iEvent.getByLabel(AntiBHadronVsJet_, AntiBHadronVsJet);

          for (int i=0; i<(int) BHadronVsJet->size(); ++i){VBHadVsJet.push_back(BHadronVsJet->at(i));}
          for (int i=0; i<(int) AntiBHadronVsJet->size(); ++i){VAntiBHadVsJet.push_back(AntiBHadronVsJet->at(i));}


        }
      else
        {
          std::cerr << "Error: no gen event?!\n";
          GenTop = dummy; GenAntiTop = dummy;
          GenLepton = dummy; GenAntiLepton = dummy;
          GenTau = dummy; GenAntiTau = dummy;
          GenLeptonPdgId = 0; GenAntiLeptonPdgId = 0;
          GenB = dummy; GenAntiB = dummy;
          GenNeutrino = dummy; GenAntiNeutrino = dummy;
          GenWMinus = dummy; GenWPlus = dummy;
        }

      //put more true info
      //         edm::Handle<std::vector<reco::GenParticle> > genParticles;
      //         iEvent.getByLabel(genParticles_, genParticles);
      //         for ( vector< reco::GenParticle >::const_iterator p = genParticles->begin(); p != genParticles->end(); ++p) {
      //             GenParticleP4.push_back(p->p4());
      //             GenParticlePdgId.push_back(p->pdgId());
      //             GenParticleStatus.push_back(p->status());
      //         }
    }

  //////fill pfiso///maybe other iso??
  edm::Handle<std::vector<pat::Muon> > muons;
  iEvent.getByLabel ( muons_, muons );

  edm::Handle<std::vector<pat::Electron> > electrons;
  iEvent.getByLabel ( elecs_, electrons );

  std::vector<pat::Muon>::const_iterator amuon  = muons->begin();
  std::vector<pat::Electron>::const_iterator anelectron  = electrons->begin();


  while ( amuon < muons->end() || anelectron < electrons->end() ) //sort input leptons by pt
    {

      bool writemuon=false;
      bool writeelec=false;

      if ( anelectron == electrons->end() )  writemuon=true;
      else if ( amuon == muons->end() )      writeelec=true;
      else if ( amuon->pt() > anelectron->pt() ) writemuon=true;
      else writeelec=true;


      if ( writemuon )
        {
          //Fill muonstuff
          Vlep.push_back( amuon->p4());
          VlepQ.push_back ( amuon->charge() ) ;
          VlepType.push_back ( 1 ) ;
          VlepPfIso.push_back ( ( ( amuon->chargedHadronIso() +amuon->neutralHadronIso() +amuon->photonIso() ) / amuon->pt() ) );
          VlepCombIso.push_back ( ( amuon->trackIso() +amuon->caloIso() ) /amuon->pt() );


          int triggerResult = 0;

          //          std::cout << "processing muon, is lepton object: " << Vlep.size() << std::endl;

          pat::TriggerObjectStandAloneCollection triggers = amuon->triggerObjectMatches();
          if (triggers.size() > 0) triggerResult = triggerMap_["general"];
          for (unsigned int i = 0; i < triggers.size(); ++i)
            triggerResult |= getTriggerBits ( triggers[i].pathNames() );
          VlepTrigger.push_back(triggerResult);

          //          std::cout << "trigger result: " << std::hex << triggerResult << std::dec << std::endl;
          amuon++;


        }
      if ( writeelec )
        {
          //Fill elestuff
          Vlep.push_back ( anelectron->p4() ) ;
          VlepQ.push_back ( anelectron->charge() ) ;
          VlepType.push_back ( -1 ) ;
          VlepPfIso.push_back ( ( ( anelectron->chargedHadronIso() +anelectron->neutralHadronIso() +anelectron->photonIso() ) / anelectron->pt() ) );

          if ( fabs ( anelectron->superCluster()->eta() ) <= 1.479 ) //barrel region
            {
              VlepCombIso.push_back ( ( anelectron->dr03TkSumPt() +TMath::Max ( 0.,anelectron->dr03EcalRecHitSumEt()-1. ) +anelectron->dr03HcalTowerSumEt() ) /TMath::Max ( 20.,anelectron->pt() ) );
            }
          else   //endcap
            {
              VlepCombIso.push_back ( ( anelectron->dr03TkSumPt() +anelectron->dr03EcalRecHitSumEt() +anelectron->dr03HcalTowerSumEt() ) /TMath::Max ( 20.,anelectron->pt() ) );
            }

          int triggerResult = 0;

          //          std::cout << "processing electron, is lepton object: " << Vlep.size() << std::endl;

          pat::TriggerObjectStandAloneCollection triggers = anelectron->triggerObjectMatches();
          if (triggers.size() > 0) triggerResult = triggerMap_["general"];
          for (unsigned int i = 0; i < triggers.size(); ++i)
            triggerResult |= getTriggerBits ( triggers[i].pathNames() );
          VlepTrigger.push_back(triggerResult);

          //          std::cout << "trigger result: " << std::hex << triggerResult << std::dec << std::endl;

          anelectron++;

        }
    }

  ///////////////////////////////////Jet properties/////////////////////////

  edm::Handle<edm::View< pat::Jet > > jets;
  iEvent.getByLabel ( jets_, jets );

  for ( edm::View<pat::Jet>::const_iterator ajet  = jets->begin() ; ajet != jets->end(); ajet++ )
    {
      Vjet.push_back ( ajet->p4() );
      if (! iEvent.isRealData()) {
        VjetType.push_back( getJetType( &(*ajet) ) ); // I hate this &(* ... ) CMSSW design
        if (ajet->genJet()) {
          VgenJet.push_back(ajet->genJet()->p4());
        } else {
          VgenJet.push_back(dummy);
        }
      }
      VjetBTagTCHE.push_back ( ajet->bDiscriminator ( "trackCountingHighEffBJetTags" ) );
      VjetBTagTCHP.push_back(ajet->bDiscriminator("trackCountingHighPurBJetTags") );
      VjetBTagJetProbability.push_back(ajet->bDiscriminator("jetProbabilityBJetTags"));
      VjetBTagJetBProbability.push_back(ajet->bDiscriminator("jetBProbabilityBJetTags"));
      VjetBTagSSVHE.push_back ( ajet->bDiscriminator ( "simpleSecondaryVertexHighEffBJetTags" ) );
      VjetBTagSSVHP.push_back ( ajet->bDiscriminator ( "simpleSecondaryVertexHighPurBJetTags" ) );
      VjetBTagCSV.push_back(ajet->bDiscriminator("combinedSecondaryVertexBJetTags"));
      VjetBTagCSVMVA.push_back(ajet->bDiscriminator("combinedSecondaryVertexMVABJetTags"));

    }

  ///////////////////////////////////Met properties///////////////////////////

  edm::Handle<edm::View<pat::MET> > met;
  iEvent.getByLabel ( met_, met );

  for ( edm::View<pat::MET>::const_iterator Met  = met->begin() ; Met != met->end(); Met++ )
    {
      VmetEt.push_back ( Met->et() );
      VmetPhi.push_back ( Met->phi() );
    }

  //////////////////////////////Event Info/////////////////////
  runno = iEvent.id().run();
  lumibl = iEvent.id().luminosityBlock();
  eventno = iEvent.id().event();


  //////////////////Trigger Stuff///////////////hltPaths_[i].c_str()

  edm::Handle<edm::TriggerResults> trigResults;
  iEvent.getByLabel ( trigResults_, trigResults );
  triggerBits = getTriggerBits(iEvent, trigResults);

  edm::Handle<std::vector<reco::Vertex> > vertices;
  iEvent.getByLabel ( vertices_, vertices );
  vertMulti = vertices->size();

  // default values to allow for tracing errors
  if (! iEvent.isRealData()) {
    edm::Handle<edm::View<PileupSummaryInfo> > pPUInfo;
    iEvent.getByLabel(inTag_PUSource, pPUInfo);
    edm::View<PileupSummaryInfo>::const_iterator iterPU;
    for(iterPU = pPUInfo->begin(); iterPU != pPUInfo->end(); ++iterPU)  // vector size is 3
      {
        if (iterPU->getBunchCrossing() == 0) // -1: previous BX, 0: current BX,  1: next BX
          vertMultiTrue = iterPU->getTrueNumInteractions();
      }
  } else{
    vertMultiTrue = vertices->size();
  }


  Ntuple->Fill();

}


int NTupleWriter::getJetType( const pat::Jet *jet ) {

  if      (jet->partonFlavour() == 5 || jet->partonFlavour() == -5) return 2;
  else if (jet->partonFlavour() == 4 || jet->partonFlavour() == -4) return 1;
  else return 0;

}

int NTupleWriter::getTriggerBits (const edm::Event &iEvent, const edm::Handle< edm::TriggerResults > &trigResults ) {

  int n_Triggers = trigResults->size();
  edm::TriggerNames trigName = iEvent.triggerNames ( *trigResults );
  int result = 0;

  for ( int i_Trig = 0; i_Trig<n_Triggers; ++i_Trig )
    {
      if ( trigResults.product()->accept ( i_Trig ) )
        {
          if (includeTrig_) VfiredTriggers.push_back ( trigName.triggerName ( i_Trig ) );
          std::string triggerName = trigName.triggerName ( i_Trig );
	  std::string triggerNameWithoutVersion(triggerName);
          while (triggerNameWithoutVersion.length() > 0
                 && triggerNameWithoutVersion[triggerNameWithoutVersion.length()-1] >= '0'
                 && triggerNameWithoutVersion[triggerNameWithoutVersion.length()-1] <= '9')
            {
              triggerNameWithoutVersion.replace(triggerNameWithoutVersion.length()-1, 1, "");
            }
          result |= triggerMap_[triggerNameWithoutVersion + "*"];
	  result |= triggerMap_[triggerName];
        }
    }
  return result;
}

int NTupleWriter::getTriggerBits ( const std::vector< std::string > &trigName ) {

  int result = 0;

  for ( unsigned int i_Trig = 0; i_Trig < trigName.size(); ++i_Trig ) {

    std::string triggerName = trigName.at( i_Trig );
    std::string triggerNameWithoutVersion(triggerName);
    while (triggerNameWithoutVersion.length() > 0
	    && triggerNameWithoutVersion[triggerNameWithoutVersion.length()-1] >= '0'
	    && triggerNameWithoutVersion[triggerNameWithoutVersion.length()-1] <= '9')
      {
	triggerNameWithoutVersion.replace(triggerNameWithoutVersion.length()-1, 1, "");
      }
    result |= triggerMap_[triggerNameWithoutVersion + "*"];
    result |= triggerMap_[triggerName];
  }
  return result;
}


// ------------ method called once each job just before starting event loop  ------------
void
NTupleWriter::beginJob()
{
  edm::Service<TFileService> fs;

  if ( !fs ) throw edm::Exception ( edm::errors::Configuration, "TFile Service is not registered in cfg file" );

  if (directory_.size()) {
    TFileDirectory NTupDir = fs->mkdir (directory_);
    Ntuple = NTupDir.make<TTree> ( "NTuple","NTuple" );
  } else {
    Ntuple = fs->make<TTree>("NTuple","NTuple");
  }

  ///////////////dilepton and lepton properties//////////
  Ntuple->Branch ( "lepton",&Vlep );
  Ntuple->Branch ( "lepQ",&VlepQ );
  Ntuple->Branch ( "lepType",&VlepType );
  Ntuple->Branch ( "lepPfIso",&VlepPfIso );
  Ntuple->Branch ( "lepCombIso",&VlepCombIso );
  Ntuple->Branch ( "lepTrigger",&VlepTrigger );


  /////////////jet properties////////////
  Ntuple->Branch ( "jet",&Vjet );
  Ntuple->Branch ( "jetBTagTCHE",&VjetBTagTCHE );
  Ntuple->Branch ( "jetBTagTCHP",&VjetBTagTCHP );
  Ntuple->Branch ( "jetBTagSSVHE",&VjetBTagSSVHE );
  Ntuple->Branch ( "jetBTagSSVHP",&VjetBTagSSVHP );
  Ntuple->Branch ( "jetBTagJetProbability", &VjetBTagJetProbability );
  Ntuple->Branch ( "jetBTagJetBProbability", &VjetBTagJetBProbability );
  Ntuple->Branch ( "jetBTagCSV", &VjetBTagCSV);
  Ntuple->Branch ( "jetBTagCSVMVA", &VjetBTagCSVMVA);
  Ntuple->Branch ( "allGenJets", &VallGenJets);
  Ntuple->Branch ( "jetType",&VjetType );
  Ntuple->Branch ( "genJet", &VgenJet);

  /////////////met properties///////////
  Ntuple->Branch ( "metEt",&VmetEt );
  Ntuple->Branch ( "metPhi",&VmetPhi );


  ///////////event info///////////
  Ntuple->Branch ( "runNumber",&runno, "runNumber/i" );
  Ntuple->Branch ( "lumiBlock",&lumibl,"lumiBlock/i" );
  Ntuple->Branch ( "eventNumber",&eventno, "eventNumber/i" );
  Ntuple->Branch ( "triggerBits", &triggerBits, "triggerBits/i");
  Ntuple->Branch ( "dataType",&datatype );


  ////////////triggers//////////////////
  if ( includeTrig_ ) Ntuple->Branch ( "firedTriggers",&VfiredTriggers );

  ////////////weight////////////
  Ntuple->Branch ( "weightMCatNLO",&weightMCatNLO, "weightMCatNLO/D" );
  Ntuple->Branch ( "weightPU",&weightPU, "weightPU/D" );
  //Ntuple->Branch ( "weightPU3D", &weightPU3D, "weightPU3D/D");
  Ntuple->Branch ( "weightPU_Up",&weightPU_Up, "weightPU_Up/D" );
  Ntuple->Branch ( "weightPU_Down",&weightPU_Down, "weightPU_Down/D" );
  Ntuple->Branch ( "weightLepSF",&weightLepSF, "weightLepSF/D" );
  Ntuple->Branch ( "weightKinFit",&weightKinFit, "weightKinFit/D" );
  Ntuple->Branch ( "weightTotal",&weightTotal, "weightTotal/D" );

  /////////vertices

  Ntuple->Branch ( "vertMulti",&vertMulti, "vertMulti/I" );
  Ntuple->Branch ( "vertMultiTrue",&vertMultiTrue, "vertMultiTrue/I" );

  ////////Gen Info
  if (isTtBarSample_) {
    Ntuple->Branch("GenTop.", &GenTop);
    Ntuple->Branch("GenAntiTop.", &GenAntiTop);
    Ntuple->Branch("GenLepton.", &GenLepton);
    Ntuple->Branch("GenAntiLepton.", &GenAntiLepton);
    Ntuple->Branch("GenLeptonPdgId", &GenLeptonPdgId, "GenLeptonPdgId/I");
    Ntuple->Branch("GenAntiLeptonPdgId", &GenAntiLeptonPdgId, "GenAntiLeptonPdgId/I");
    Ntuple->Branch("GenTau.", &GenTau);
    Ntuple->Branch("GenAntiTau.", &GenAntiTau);
    Ntuple->Branch("GenNeutrino.", &GenNeutrino);
    Ntuple->Branch("GenAntiNeutrino.", &GenAntiNeutrino);
    Ntuple->Branch("GenB.", &GenB);
    Ntuple->Branch("GenAntiB.", &GenAntiB);
    Ntuple->Branch("GenWPlus.", &GenWPlus);
    Ntuple->Branch("GenWMinus.", &GenWMinus);
    Ntuple->Branch("GenParticleP4.", &GenParticleP4);
    Ntuple->Branch("GenParticlePdgId.", &GenParticlePdgId);
    Ntuple->Branch("GenParticleStatus.", &GenParticleStatus);
    //     Ntuple->Branch("GenJetHadronB",&HadronGenB);
    //     Ntuple->Branch("GenJetHadronAntiB",&HadronGenAntiB);

    Ntuple->Branch("BHadJetIndex", &VBHadJetIdx);
    Ntuple->Branch("AntiBHadJetIndex", &VAntiBHadJetIdx);
    Ntuple->Branch("BHadrons", &VBHadron);
    Ntuple->Branch("AntiBHadrons", &VAntiBHadron);
    Ntuple->Branch("BHadronFromTop", &VBHadFromTop);
    Ntuple->Branch("AntiBHadronFromTopB", &VAntiBHadFromTop);
    Ntuple->Branch("BHadronVsJet", &VBHadVsJet);
    Ntuple->Branch("AntiBHadronVsJet", &VAntiBHadVsJet);

  }

  //Hypothesis Info
  Ntuple->Branch("HypTop", &HypTop);
  Ntuple->Branch("HypAntiTop", &HypAntiTop);
  Ntuple->Branch("HypLepton", &HypLepton);
  Ntuple->Branch("HypAntiLepton", &HypAntiLepton);
  Ntuple->Branch("HypNeutrino", &HypNeutrino);
  Ntuple->Branch("HypAntiNeutrino", &HypAntiNeutrino);
  Ntuple->Branch("HypB", &HypB);
  Ntuple->Branch("HypAntiB", &HypAntiB);
  Ntuple->Branch("HypWPlus", &HypWPlus);
  Ntuple->Branch("HypWMinus", &HypWMinus);
  Ntuple->Branch("HypJet0index", &HypJet0index);
  Ntuple->Branch("HypJet1index", &HypJet1index);

  Ntuple->Branch ( "decayMode", &decayMode, "decayMode/I" );
}

// ------------ method called once each job just after ending the event loop  ------------
void
NTupleWriter::endJob()
{
}

// ------------ method called when starting to processes a run  ------------
void
NTupleWriter::beginRun ( edm::Run const&, edm::EventSetup const& )
{
}

// ------------ method called when ending the processing of a run  ------------
void
NTupleWriter::endRun ( edm::Run const&, edm::EventSetup const& )
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void
NTupleWriter::beginLuminosityBlock ( edm::LuminosityBlock const&, edm::EventSetup const& )
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void
NTupleWriter::endLuminosityBlock ( edm::LuminosityBlock const&, edm::EventSetup const& )
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
NTupleWriter::fillDescriptions ( edm::ConfigurationDescriptions& descriptions )
{
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault ( desc );
}

void NTupleWriter::clearVariables()
{
  runno = 0;
  lumibl = 0;
  eventno = 0;
  triggerBits = 0;

  datatype.clear();

  ////////dileptons and leptons/////
  Vlep.clear() ;
  VlepQ.clear() ;
  VlepType.clear() ;
  VlepPfIso.clear();
  VlepCombIso.clear();
  VlepTrigger.clear();

  GenParticleP4.clear();
  GenParticlePdgId.clear();
  GenParticleStatus.clear();

  /////////jets///////////
  Vjet.clear();
  VjetType.clear();
  VjetBTagTCHE.clear();
  VjetBTagTCHP.clear();
  VjetBTagSSVHE.clear();
  VjetBTagSSVHP.clear();
  VjetBTagJetProbability.clear();
  VjetBTagJetBProbability.clear();
  VjetBTagCSV.clear();
  VjetBTagCSVMVA.clear();
  VallGenJets.clear();
  VgenJet.clear();

  VBHadJetIdx.clear();
  VAntiBHadJetIdx.clear();
  VBHadron.clear();
  VAntiBHadron.clear();
  VBHadFromTop.clear();
  VAntiBHadFromTop.clear();
  VBHadVsJet.clear();
  VAntiBHadVsJet.clear();

  /////////met///////////
  VmetEt.clear();
  VmetPhi.clear();


  /////////Triggers/////////
  VfiredTriggers.clear();

  //////vertices
  vertMulti=0;
  vertMultiTrue=0;

  HypTop.clear();
  HypAntiTop.clear();
  HypLepton.clear();
  HypAntiLepton.clear();
  HypNeutrino.clear();
  HypAntiNeutrino.clear();
  HypB.clear();
  HypAntiB.clear();
  HypWPlus.clear();
  HypWMinus.clear();

  HypJet0index.clear();
  HypJet1index.clear();

}


//define this as a plug-in
DEFINE_FWK_MODULE ( NTupleWriter );
