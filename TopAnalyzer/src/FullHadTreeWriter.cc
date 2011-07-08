#include <stdio.h>

#include "TopAnalysis/TopAnalyzer/interface/TopAngles.h"
#include "TopAnalysis/TopAnalyzer/interface/FullHadTreeWriter.h"
#include "TopQuarkAnalysis/TopEventSelection/interface/TtFullHadSignalSel.h"

#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/Common/interface/View.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
//#include "DataFormats/Candidate/interface/Candidate.h"
//#include "DataFormats/Candidate/interface/LeafCandidate.h"
#include "AnalysisDataFormats/TopObjects/interface/TtFullHadEvtPartons.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

/// default constructor
FullHadTreeWriter::FullHadTreeWriter(const edm::ParameterSet& cfg) :
  JetSrc_            (cfg.getParameter<edm::InputTag>("JetSrc")),
  METSrc_            (cfg.getParameter<edm::InputTag>("METSrc")),
  FitSrc_            (cfg.getParameter<edm::InputTag>("FitSrc")),
  MultiJetMVADiscSrc_(cfg.getParameter<edm::InputTag>("MultiJetMVADiscSrc")),
  GenSrc_            (cfg.getParameter<edm::InputTag>("GenSrc")),
  PUSrc_             (cfg.getParameter<edm::InputTag>("PUSrc")),
  VertexSrc_         (cfg.getParameter<edm::InputTag>("VertexSrc")),
  PUWeightSrc_       (cfg.getParameter<edm::InputTag>("PUweightSrc")),
  MCweight_(cfg.getParameter<double>("MCweight")),
  bTagName_(cfg.getParameter<std::vector<std::string> >("bTagName")),
  bTagVal_ (cfg.getParameter<std::vector<std::string> >("bTagVal" )),
  kMAX(50),
  kBTagMAX(cfg.getParameter<unsigned int>("bTagParams")),
  doPDFUncertainty(false)
{
}

/// default destructor
FullHadTreeWriter::~FullHadTreeWriter()
{
}

/// initiate histograms
void
FullHadTreeWriter::beginJob()
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
  //weight = -1.;
  //tree->Branch("weight", &weight, "weight/D");
  MCweight = MCweight_;
  PUweight = -10.;
  tree->Branch("MCweight", &MCweight, "MCweight/D");
  tree->Branch("PUweight", &PUweight, "PUweight/D");

  /// MET

  // 4-vector of MET
  MET = new TClonesArray("TLorentzVector", 1);
  tree->Branch("MET", &MET, 32000, -1);
  MET->BypassStreamer();

  /// jets

  // 4-vectors of jets
  jets = new TClonesArray("TLorentzVector", kMAX);
  tree->Branch("jets", &jets, 32000, -1);
  jets->BypassStreamer();

  // number of jets in events
  Njet = -1;
  tree->Branch("Njet", &Njet, "Njet/I");

  // b-tag discriminators of jets
  bTag_TCHE     = new float[(kBTagMAX+1)*kMAX];
  bTag_TCHP     = new float[(kBTagMAX+1)*kMAX];
  bTag_SSVHE    = new float[(kBTagMAX+1)*kMAX];
  bTag_SSVHP    = new float[(kBTagMAX+1)*kMAX];
  bTag_CSV      = new float[kMAX];
  bTag_CSVMVA   = new float[kMAX];
  charge        = new float[kMAX];
  pdgId         = new short[kMAX];
  partonFlavour = new short[kMAX];
  for(unsigned short i = 0; i < kMAX; ++i) {
    for(unsigned short j = 0; j < kBTagMAX+1; ++j) {
      bTag_TCHE  [i*j+j] = -100.;
      bTag_TCHP  [i*j+j] = -100.;
      bTag_SSVHE [i*j+j] = -100.;
      bTag_SSVHP [i*j+j] = -100.;
    }
    bTag_CSV     [i] = -100.;
    bTag_CSVMVA  [i] = -100.;
    charge       [i] = -100.;
    pdgId        [i] =    0 ;
    partonFlavour[i] =    0 ;
  }
  char buffer[7];
  sprintf(buffer, "[%i]/F", kBTagMAX+1);
  //std::cout << (std::string("bTag_TCHE[Njet]") + std::string(buffer)).c_str() << std::endl;
  tree->Branch("bTag_TCHE"    , bTag_TCHE    , (std::string("bTag_TCHE[Njet]" ) + std::string(buffer)).c_str() );
  tree->Branch("bTag_TCHP"    , bTag_TCHP    , (std::string("bTag_TCHP[Njet]" ) + std::string(buffer)).c_str() );
  tree->Branch("bTag_SSVHE"   , bTag_SSVHE   , (std::string("bTag_SSVHE[Njet]") + std::string(buffer)).c_str() );
  tree->Branch("bTag_SSVHP"   , bTag_SSVHP   , (std::string("bTag_SSVHP[Njet]") + std::string(buffer)).c_str() );
  tree->Branch("bTag_CSV"     , bTag_CSV     , "bTag_CSV[Njet]/F"     );
  tree->Branch("bTag_CSVMVA"  , bTag_CSVMVA  , "bTag_CSVMVA[Njet]/F"  );
  tree->Branch("charge"       , charge       , "charge[Njet]/F"       );
  tree->Branch("pdgId"        , pdgId        , "pdgId[Njet]/S"        );
  tree->Branch("partonFlavour", partonFlavour, "partonFlavour[Njet]/S");

  measureMap["BTAGBEFF"]=PerformanceResult::BTAGBEFF;
  measureMap["BTAGBERR"]=PerformanceResult::BTAGBERR;
  measureMap["BTAGCEFF"]=PerformanceResult::BTAGCEFF;
  measureMap["BTAGCERR"]=PerformanceResult::BTAGCERR;
  measureMap["BTAGLEFF"]=PerformanceResult::BTAGLEFF;
  measureMap["BTAGLERR"]=PerformanceResult::BTAGLERR;
  measureMap["BTAGNBEFF"]=PerformanceResult::BTAGNBEFF;
  measureMap["BTAGNBERR"]=PerformanceResult::BTAGNBERR;
  measureMap["BTAGBEFFCORR"]=PerformanceResult::BTAGBEFFCORR;
  measureMap["BTAGBERRCORR"]=PerformanceResult::BTAGBERRCORR;
  measureMap["BTAGCEFFCORR"]=PerformanceResult::BTAGCEFFCORR;
  measureMap["BTAGCERRCORR"]=PerformanceResult::BTAGCERRCORR;
  measureMap["BTAGLEFFCORR"]=PerformanceResult::BTAGLEFFCORR;
  measureMap["BTAGLERRCORR"]=PerformanceResult::BTAGLERRCORR;
  measureMap["BTAGNBEFFCORR"]=PerformanceResult::BTAGNBEFFCORR;
  measureMap["BTAGNBERRCORR"]=PerformanceResult::BTAGNBERRCORR;
  measureMap["BTAGNBERRCORR"]=PerformanceResult::BTAGNBERRCORR;
  measureMap["MUEFF"]=PerformanceResult::MUEFF;
  measureMap["MUERR"]=PerformanceResult::MUERR;
  measureMap["MUFAKE"]=PerformanceResult::MUFAKE; 
  measureMap["MUEFAKE"]=PerformanceResult::MUEFAKE;

  H      = -1.;
  Ht     = -1.;
  Ht123  = -1.;
  Ht3jet = -1.;
  sqrt_s = -1.;
  Et56   = -1.;
  M3     = -1.;

  tree->Branch("H"     , &H     , "H/F"     );
  tree->Branch("Ht"    , &Ht    , "Ht/F"    );
  tree->Branch("Ht123" , &Ht123 , "Ht123/F" );
  tree->Branch("Ht3jet", &Ht3jet, "Ht3jet/F");
  tree->Branch("sqrt_s", &sqrt_s, "sqrt_s/F");
  tree->Branch("Et56"  , &Et56  , "Et56/F"  );
  tree->Branch("M3"    , &M3    , "M3/F"    );
  
  EtSin2Theta  = new float[kMAX];
  theta        = new float[kMAX];
  sinTheta     = new float[kMAX];
  EtStar       = new float[kMAX];
  thetaStar    = new float[kMAX];
  sinThetaStar = new float[kMAX];
  for(unsigned short i = 0; i < kMAX; ++i) {
    EtSin2Theta [i] = -1.;
    theta       [i] = -100.;
    sinTheta    [i] = -100 ;
    EtStar      [i] = -1.;
    thetaStar   [i] = -100.;
    sinThetaStar[i] = -100 ;
  }

  tree->Branch("EtSin2Theta" , EtSin2Theta , "EtSin2Theta[Njet]/F" );
  tree->Branch("theta"       , theta       , "theta[Njet]/F"       );
  tree->Branch("sinTheta"    , sinTheta    , "sinTheta[Njet]/F"    );
  tree->Branch("EtStar"      , EtStar      , "EtStar[Njet]/F"      );
  tree->Branch("thetaStar"   , thetaStar   , "thetaStar[Njet]/F"   );
  tree->Branch("sinThetaStar", sinThetaStar, "sinThetaStar[Njet]/F");

  EtSin2Theta3jet  = -1.  ;
  theta3jet        = -100.;
  sinTheta3jet     = -100.;
  EtStar3jet       = -1.  ;
  thetaStar3jet    = -100.;
  sinThetaStar3jet = -100.;

  tree->Branch("EtSin2Theta3jet" , &EtSin2Theta3jet , "EtSin2Theta3jet/F" );
  tree->Branch("theta3jet"       , &theta3jet       , "theta3jet/F"       );
  tree->Branch("sinTheta3jet"    , &sinTheta3jet    , "sinTheta3jet/F"    );
  tree->Branch("EtStar3jet"      , &EtStar3jet      , "EtStar3jet/F"      );
  tree->Branch("thetaStar3jet"   , &thetaStar3jet   , "thetaStar3jet/F"   );
  tree->Branch("sinThetaStar3jet", &sinThetaStar3jet, "sinThetaStar3jet/F");

  pt1_pt6 = -1.;
  pt1_pt5 = -1.;
  pt1_pt4 = -1.;
  pt1_pt3 = -1.;
  pt1_pt2 = -1.;
  pt2_pt6 = -1.;
  pt2_pt5 = -1.;
  pt2_pt4 = -1.;
  pt2_pt3 = -1.;
  pt3_pt6 = -1.;
  pt3_pt5 = -1.;
  pt3_pt4 = -1.;
  pt4_pt6 = -1.;
  pt4_pt5 = -1.;
  pt5_pt6 = -1.;

  tree->Branch("pt1_pt6", &pt1_pt6, "pt1_pt6/F");
  tree->Branch("pt1_pt5", &pt1_pt5, "pt1_pt5/F");
  tree->Branch("pt1_pt4", &pt1_pt4, "pt1_pt4/F");
  tree->Branch("pt1_pt3", &pt1_pt3, "pt1_pt3/F");
  tree->Branch("pt1_pt2", &pt1_pt2, "pt1_pt2/F");
  tree->Branch("pt2_pt6", &pt2_pt6, "pt2_pt6/F");
  tree->Branch("pt2_pt5", &pt2_pt5, "pt2_pt5/F");
  tree->Branch("pt2_pt4", &pt2_pt4, "pt2_pt4/F");
  tree->Branch("pt2_pt3", &pt2_pt3, "pt2_pt3/F");
  tree->Branch("pt3_pt6", &pt3_pt6, "pt3_pt6/F");
  tree->Branch("pt3_pt5", &pt3_pt5, "pt3_pt5/F");
  tree->Branch("pt3_pt4", &pt3_pt4, "pt3_pt4/F");
  tree->Branch("pt4_pt6", &pt4_pt6, "pt4_pt6/F");
  tree->Branch("pt4_pt5", &pt4_pt5, "pt4_pt5/F");
  tree->Branch("pt5_pt6", &pt5_pt6, "pt5_pt6/F");

  pt1_pt6_norm = -1.;
  pt1_pt5_norm = -1.;
  pt1_pt4_norm = -1.;
  pt1_pt3_norm = -1.;
  pt1_pt2_norm = -1.;
  pt2_pt6_norm = -1.;
  pt2_pt5_norm = -1.;
  pt2_pt4_norm = -1.;
  pt2_pt3_norm = -1.;
  pt3_pt6_norm = -1.;
  pt3_pt5_norm = -1.;
  pt3_pt4_norm = -1.;
  pt4_pt6_norm = -1.;
  pt4_pt5_norm = -1.;
  pt5_pt6_norm = -1.;

  tree->Branch("pt1_pt6_norm", &pt1_pt6_norm, "pt1_pt6_norm/F");
  tree->Branch("pt1_pt5_norm", &pt1_pt5_norm, "pt1_pt5_norm/F");
  tree->Branch("pt1_pt4_norm", &pt1_pt4_norm, "pt1_pt4_norm/F");
  tree->Branch("pt1_pt3_norm", &pt1_pt3_norm, "pt1_pt3_norm/F");
  tree->Branch("pt1_pt2_norm", &pt1_pt2_norm, "pt1_pt2_norm/F");
  tree->Branch("pt2_pt6_norm", &pt2_pt6_norm, "pt2_pt6_norm/F");
  tree->Branch("pt2_pt5_norm", &pt2_pt5_norm, "pt2_pt5_norm/F");
  tree->Branch("pt2_pt4_norm", &pt2_pt4_norm, "pt2_pt4_norm/F");
  tree->Branch("pt2_pt3_norm", &pt2_pt3_norm, "pt2_pt3_norm/F");
  tree->Branch("pt3_pt6_norm", &pt3_pt6_norm, "pt3_pt6_norm/F");
  tree->Branch("pt3_pt5_norm", &pt3_pt5_norm, "pt3_pt5_norm/F");
  tree->Branch("pt3_pt4_norm", &pt3_pt4_norm, "pt3_pt4_norm/F");
  tree->Branch("pt4_pt6_norm", &pt4_pt6_norm, "pt4_pt6_norm/F");
  tree->Branch("pt4_pt5_norm", &pt4_pt5_norm, "pt4_pt5_norm/F");
  tree->Branch("pt5_pt6_norm", &pt5_pt6_norm, "pt5_pt6_norm/F");

  jet1_etaetaMoment = -100.;
  jet2_etaetaMoment = -100.;
  jet3_etaetaMoment = -100.;
  jet4_etaetaMoment = -100.;
  jet5_etaetaMoment = -100.;
  jet6_etaetaMoment = -100.;
  jet1_etaphiMoment = -100.;
  jet2_etaphiMoment = -100.;
  jet3_etaphiMoment = -100.;
  jet4_etaphiMoment = -100.;
  jet5_etaphiMoment = -100.;
  jet6_etaphiMoment = -100.;
  jet1_phiphiMoment = -100.;
  jet2_phiphiMoment = -100.;
  jet3_phiphiMoment = -100.;
  jet4_phiphiMoment = -100.;
  jet5_phiphiMoment = -100.;
  jet6_phiphiMoment = -100.;

  tree->Branch("jet1_etaetaMoment", &jet1_etaetaMoment, "jet1_etaetaMoment/F");
  tree->Branch("jet2_etaetaMoment", &jet2_etaetaMoment, "jet2_etaetaMoment/F");
  tree->Branch("jet3_etaetaMoment", &jet3_etaetaMoment, "jet3_etaetaMoment/F");
  tree->Branch("jet4_etaetaMoment", &jet4_etaetaMoment, "jet4_etaetaMoment/F");
  tree->Branch("jet5_etaetaMoment", &jet5_etaetaMoment, "jet5_etaetaMoment/F");
  tree->Branch("jet6_etaetaMoment", &jet6_etaetaMoment, "jet6_etaetaMoment/F");
  tree->Branch("jet1_etaphiMoment", &jet1_etaphiMoment, "jet1_etaphiMoment/F");
  tree->Branch("jet2_etaphiMoment", &jet2_etaphiMoment, "jet2_etaphiMoment/F");
  tree->Branch("jet3_etaphiMoment", &jet3_etaphiMoment, "jet3_etaphiMoment/F");
  tree->Branch("jet4_etaphiMoment", &jet4_etaphiMoment, "jet4_etaphiMoment/F");
  tree->Branch("jet5_etaphiMoment", &jet5_etaphiMoment, "jet5_etaphiMoment/F");
  tree->Branch("jet6_etaphiMoment", &jet6_etaphiMoment, "jet6_etaphiMoment/F");
  tree->Branch("jet1_phiphiMoment", &jet1_phiphiMoment, "jet1_phiphiMoment/F");
  tree->Branch("jet2_phiphiMoment", &jet2_phiphiMoment, "jet2_phiphiMoment/F");
  tree->Branch("jet3_phiphiMoment", &jet3_phiphiMoment, "jet3_phiphiMoment/F");
  tree->Branch("jet4_phiphiMoment", &jet4_phiphiMoment, "jet4_phiphiMoment/F");
  tree->Branch("jet5_phiphiMoment", &jet5_phiphiMoment, "jet5_phiphiMoment/F");
  tree->Branch("jet6_phiphiMoment", &jet6_phiphiMoment, "jet6_phiphiMoment/F");

  jet1_etaetaMomentMoment = -100.;
  jet2_etaetaMomentMoment = -100.;
  jet3_etaetaMomentMoment = -100.;
  jet4_etaetaMomentMoment = -100.;
  jet5_etaetaMomentMoment = -100.;
  jet6_etaetaMomentMoment = -100.;
  jet1_etaphiMomentMoment = -100.;
  jet2_etaphiMomentMoment = -100.;
  jet3_etaphiMomentMoment = -100.;
  jet4_etaphiMomentMoment = -100.;
  jet5_etaphiMomentMoment = -100.;
  jet6_etaphiMomentMoment = -100.;
  jet1_phiphiMomentMoment = -100.;
  jet2_phiphiMomentMoment = -100.;
  jet3_phiphiMomentMoment = -100.;
  jet4_phiphiMomentMoment = -100.;
  jet5_phiphiMomentMoment = -100.;
  jet6_phiphiMomentMoment = -100.;

  tree->Branch("jet1_etaetaMomentMoment", &jet1_etaetaMomentMoment, "jet1_etaetaMomentMoment/F");
  tree->Branch("jet2_etaetaMomentMoment", &jet2_etaetaMomentMoment, "jet2_etaetaMomentMoment/F");
  tree->Branch("jet3_etaetaMomentMoment", &jet3_etaetaMomentMoment, "jet3_etaetaMomentMoment/F");
  tree->Branch("jet4_etaetaMomentMoment", &jet4_etaetaMomentMoment, "jet4_etaetaMomentMoment/F");
  tree->Branch("jet5_etaetaMomentMoment", &jet5_etaetaMomentMoment, "jet5_etaetaMomentMoment/F");
  tree->Branch("jet6_etaetaMomentMoment", &jet6_etaetaMomentMoment, "jet6_etaetaMomentMoment/F");
  tree->Branch("jet1_etaphiMomentMoment", &jet1_etaphiMomentMoment, "jet1_etaphiMomentMoment/F");
  tree->Branch("jet2_etaphiMomentMoment", &jet2_etaphiMomentMoment, "jet2_etaphiMomentMoment/F");
  tree->Branch("jet3_etaphiMomentMoment", &jet3_etaphiMomentMoment, "jet3_etaphiMomentMoment/F");
  tree->Branch("jet4_etaphiMomentMoment", &jet4_etaphiMomentMoment, "jet4_etaphiMomentMoment/F");
  tree->Branch("jet5_etaphiMomentMoment", &jet5_etaphiMomentMoment, "jet5_etaphiMomentMoment/F");
  tree->Branch("jet6_etaphiMomentMoment", &jet6_etaphiMomentMoment, "jet6_etaphiMomentMoment/F");
  tree->Branch("jet1_phiphiMomentMoment", &jet1_phiphiMomentMoment, "jet1_phiphiMomentMoment/F");
  tree->Branch("jet2_phiphiMomentMoment", &jet2_phiphiMomentMoment, "jet2_phiphiMomentMoment/F");
  tree->Branch("jet3_phiphiMomentMoment", &jet3_phiphiMomentMoment, "jet3_phiphiMomentMoment/F");
  tree->Branch("jet4_phiphiMomentMoment", &jet4_phiphiMomentMoment, "jet4_phiphiMomentMoment/F");
  tree->Branch("jet5_phiphiMomentMoment", &jet5_phiphiMomentMoment, "jet5_phiphiMomentMoment/F");
  tree->Branch("jet6_phiphiMomentMoment", &jet6_phiphiMomentMoment, "jet6_phiphiMomentMoment/F");

  jets_etaetaMoment = -100.;
  jets_etaphiMoment = -100.;
  jets_phiphiMoment = -100.;

  tree->Branch("jets_etaetaMoment", &jets_etaetaMoment, "jets_etaetaMoment/F");
  tree->Branch("jets_etaphiMoment", &jets_etaphiMoment, "jets_etaphiMoment/F");
  tree->Branch("jets_phiphiMoment", &jets_phiphiMoment, "jets_phiphiMoment/F");

  jet1_etaetaMomentLogEt = -100.;
  jet2_etaetaMomentLogEt = -100.;
  jet3_etaetaMomentLogEt = -100.;
  jet4_etaetaMomentLogEt = -100.;
  jet5_etaetaMomentLogEt = -100.;
  jet6_etaetaMomentLogEt = -100.;
  jet1_etaphiMomentLogEt = -100.;
  jet2_etaphiMomentLogEt = -100.;
  jet3_etaphiMomentLogEt = -100.;
  jet4_etaphiMomentLogEt = -100.;
  jet5_etaphiMomentLogEt = -100.;
  jet6_etaphiMomentLogEt = -100.;
  jet1_phiphiMomentLogEt = -100.;
  jet2_phiphiMomentLogEt = -100.;
  jet3_phiphiMomentLogEt = -100.;
  jet4_phiphiMomentLogEt = -100.;
  jet5_phiphiMomentLogEt = -100.;
  jet6_phiphiMomentLogEt = -100.;

  tree->Branch("jet1_etaetaMomentLogEt", &jet1_etaetaMomentLogEt, "jet1_etaetaMomentLogEt/F");
  tree->Branch("jet2_etaetaMomentLogEt", &jet2_etaetaMomentLogEt, "jet2_etaetaMomentLogEt/F");
  tree->Branch("jet3_etaetaMomentLogEt", &jet3_etaetaMomentLogEt, "jet3_etaetaMomentLogEt/F");
  tree->Branch("jet4_etaetaMomentLogEt", &jet4_etaetaMomentLogEt, "jet4_etaetaMomentLogEt/F");
  tree->Branch("jet5_etaetaMomentLogEt", &jet5_etaetaMomentLogEt, "jet5_etaetaMomentLogEt/F");
  tree->Branch("jet6_etaetaMomentLogEt", &jet6_etaetaMomentLogEt, "jet6_etaetaMomentLogEt/F");
  tree->Branch("jet1_etaphiMomentLogEt", &jet1_etaphiMomentLogEt, "jet1_etaphiMomentLogEt/F");
  tree->Branch("jet2_etaphiMomentLogEt", &jet2_etaphiMomentLogEt, "jet2_etaphiMomentLogEt/F");
  tree->Branch("jet3_etaphiMomentLogEt", &jet3_etaphiMomentLogEt, "jet3_etaphiMomentLogEt/F");
  tree->Branch("jet4_etaphiMomentLogEt", &jet4_etaphiMomentLogEt, "jet4_etaphiMomentLogEt/F");
  tree->Branch("jet5_etaphiMomentLogEt", &jet5_etaphiMomentLogEt, "jet5_etaphiMomentLogEt/F");
  tree->Branch("jet6_etaphiMomentLogEt", &jet6_etaphiMomentLogEt, "jet6_etaphiMomentLogEt/F");
  tree->Branch("jet1_phiphiMomentLogEt", &jet1_phiphiMomentLogEt, "jet1_phiphiMomentLogEt/F");
  tree->Branch("jet2_phiphiMomentLogEt", &jet2_phiphiMomentLogEt, "jet2_phiphiMomentLogEt/F");
  tree->Branch("jet3_phiphiMomentLogEt", &jet3_phiphiMomentLogEt, "jet3_phiphiMomentLogEt/F");
  tree->Branch("jet4_phiphiMomentLogEt", &jet4_phiphiMomentLogEt, "jet4_phiphiMomentLogEt/F");
  tree->Branch("jet5_phiphiMomentLogEt", &jet5_phiphiMomentLogEt, "jet5_phiphiMomentLogEt/F");
  tree->Branch("jet6_phiphiMomentLogEt", &jet6_phiphiMomentLogEt, "jet6_phiphiMomentLogEt/F");

  jet1_etaetaMomentMomentLogEt = -100.;
  jet2_etaetaMomentMomentLogEt = -100.;
  jet3_etaetaMomentMomentLogEt = -100.;
  jet4_etaetaMomentMomentLogEt = -100.;
  jet5_etaetaMomentMomentLogEt = -100.;
  jet6_etaetaMomentMomentLogEt = -100.;
  jet1_etaphiMomentMomentLogEt = -100.;
  jet2_etaphiMomentMomentLogEt = -100.;
  jet3_etaphiMomentMomentLogEt = -100.;
  jet4_etaphiMomentMomentLogEt = -100.;
  jet5_etaphiMomentMomentLogEt = -100.;
  jet6_etaphiMomentMomentLogEt = -100.;
  jet1_phiphiMomentMomentLogEt = -100.;
  jet2_phiphiMomentMomentLogEt = -100.;
  jet3_phiphiMomentMomentLogEt = -100.;
  jet4_phiphiMomentMomentLogEt = -100.;
  jet5_phiphiMomentMomentLogEt = -100.;
  jet6_phiphiMomentMomentLogEt = -100.;

  tree->Branch("jet1_etaetaMomentMomentLogEt", &jet1_etaetaMomentMomentLogEt, "jet1_etaetaMomentMomentLogEt/F");
  tree->Branch("jet2_etaetaMomentMomentLogEt", &jet2_etaetaMomentMomentLogEt, "jet2_etaetaMomentMomentLogEt/F");
  tree->Branch("jet3_etaetaMomentMomentLogEt", &jet3_etaetaMomentMomentLogEt, "jet3_etaetaMomentMomentLogEt/F");
  tree->Branch("jet4_etaetaMomentMomentLogEt", &jet4_etaetaMomentMomentLogEt, "jet4_etaetaMomentMomentLogEt/F");
  tree->Branch("jet5_etaetaMomentMomentLogEt", &jet5_etaetaMomentMomentLogEt, "jet5_etaetaMomentMomentLogEt/F");
  tree->Branch("jet6_etaetaMomentMomentLogEt", &jet6_etaetaMomentMomentLogEt, "jet6_etaetaMomentMomentLogEt/F");
  tree->Branch("jet1_etaphiMomentMomentLogEt", &jet1_etaphiMomentMomentLogEt, "jet1_etaphiMomentMomentLogEt/F");
  tree->Branch("jet2_etaphiMomentMomentLogEt", &jet2_etaphiMomentMomentLogEt, "jet2_etaphiMomentMomentLogEt/F");
  tree->Branch("jet3_etaphiMomentMomentLogEt", &jet3_etaphiMomentMomentLogEt, "jet3_etaphiMomentMomentLogEt/F");
  tree->Branch("jet4_etaphiMomentMomentLogEt", &jet4_etaphiMomentMomentLogEt, "jet4_etaphiMomentMomentLogEt/F");
  tree->Branch("jet5_etaphiMomentMomentLogEt", &jet5_etaphiMomentMomentLogEt, "jet5_etaphiMomentMomentLogEt/F");
  tree->Branch("jet6_etaphiMomentMomentLogEt", &jet6_etaphiMomentMomentLogEt, "jet6_etaphiMomentMomentLogEt/F");
  tree->Branch("jet1_phiphiMomentMomentLogEt", &jet1_phiphiMomentMomentLogEt, "jet1_phiphiMomentMomentLogEt/F");
  tree->Branch("jet2_phiphiMomentMomentLogEt", &jet2_phiphiMomentMomentLogEt, "jet2_phiphiMomentMomentLogEt/F");
  tree->Branch("jet3_phiphiMomentMomentLogEt", &jet3_phiphiMomentMomentLogEt, "jet3_phiphiMomentMomentLogEt/F");
  tree->Branch("jet4_phiphiMomentMomentLogEt", &jet4_phiphiMomentMomentLogEt, "jet4_phiphiMomentMomentLogEt/F");
  tree->Branch("jet5_phiphiMomentMomentLogEt", &jet5_phiphiMomentMomentLogEt, "jet5_phiphiMomentMomentLogEt/F");
  tree->Branch("jet6_phiphiMomentMomentLogEt", &jet6_phiphiMomentMomentLogEt, "jet6_phiphiMomentMomentLogEt/F");

  jets_etaetaMomentLogEt = -100.;
  jets_etaphiMomentLogEt = -100.;
  jets_phiphiMomentLogEt = -100.;

  tree->Branch("jets_etaetaMomentLogEt", &jets_etaetaMomentLogEt, "jets_etaetaMomentLogEt/F");
  tree->Branch("jets_etaphiMomentLogEt", &jets_etaphiMomentLogEt, "jets_etaphiMomentLogEt/F");
  tree->Branch("jets_phiphiMomentLogEt", &jets_phiphiMomentLogEt, "jets_phiphiMomentLogEt/F");

  aplanarity  = -1.;
  sphericity  = -1.;
  circularity = -1.;
  isotropy    = -1.;
  C           = -1.;
  D           = -1.;

  tree->Branch("aplanarity" , &aplanarity , "aplanarity/F" );
  tree->Branch("sphericity" , &sphericity , "sphericity/F" );
  tree->Branch("circularity", &circularity, "circularity/F");
  tree->Branch("isotropy"   , &isotropy   , "isotropy/F"   );
  tree->Branch("C"          , &C          , "C/F"          );
  tree->Branch("D"          , &D          , "D/F"          );

  aplanarityAll  = -1.;
  sphericityAll  = -1.;
  circularityAll = -1.;
  isotropyAll    = -1.;
  CAll           = -1.;
  DAll           = -1.;

  tree->Branch("aplanarityAll" , &aplanarityAll , "aplanarityAll/F" );
  tree->Branch("sphericityAll" , &sphericityAll , "sphericityAll/F" );
  tree->Branch("circularityAll", &circularityAll, "circularityAll/F");
  tree->Branch("isotropyAll"   , &isotropyAll   , "isotropyAll/F"   );
  tree->Branch("CAll"          , &CAll          , "CAll/F"          );
  tree->Branch("DAll"          , &DAll          , "DAll/F"          );

  aplanarityAllCMS  = -1.;
  sphericityAllCMS  = -1.;
  circularityAllCMS = -1.;
  isotropyAllCMS    = -1.;
  CAllCMS           = -1.;
  DAllCMS           = -1.;

  tree->Branch("aplanarityAllCMS" , &aplanarityAllCMS , "aplanarityAllCMS/F" );
  tree->Branch("sphericityAllCMS" , &sphericityAllCMS , "sphericityAllCMS/F" );
  tree->Branch("circularityAllCMS", &circularityAllCMS, "circularityAllCMS/F");
  tree->Branch("isotropyAllCMS"   , &isotropyAllCMS   , "isotropyAllCMS/F"   );
  tree->Branch("CAllCMS"          , &CAllCMS          , "CAllCMS/F"          );
  tree->Branch("DAllCMS"          , &DAllCMS          , "DAllCMS/F"          );

  centrality    = -1.;
  centralityAlt = -1.;
 
  tree->Branch("centrality"   , &centrality   , "centrality/F"   );
  tree->Branch("centralityAlt", &centralityAlt, "centralityAlt/F");

  thrust    = -1.;
  thrustCMS = -1.;

  tree->Branch("thrust"    , &thrust    , "thrust/F"   );
  tree->Branch("thrustCMS" , &thrustCMS , "thrustCMS/F");

  /// kinFit properties

  // probability and chi2 of kinematic fit
  prob    = -1.;
  chi2    = -1.;
  topMass = -1.;
  ttMass  = -1.;
  comboTypeValue = 0;
  tree->Branch("prob"     , &prob          , "prob/D"     );
  tree->Branch("chi2"     , &chi2          , "chi2/D"     );
  tree->Branch("topMass"  , &topMass       , "topMass/D"  );
  tree->Branch("ttMass"   , &ttMass        , "ttMass/D"   );
  tree->Branch("comboType", &comboTypeValue, "comboType/s");

  // pt asymmetry of b and W boson
  ptAsy    = -100.;
  ptAsyBar = -100.;
  tree->Branch("ptAsy"    , &ptAsy    , "ptAsy/F"   );
  tree->Branch("ptAsyBar" , &ptAsyBar , "ptAsyBar/F");

  // angles of ttbar system
  ttDetFrame                          = -100.;
  bbDetFrame                          = -100.;
  bbTtbarFrame                        = -100.;
  WWTtbarFrame                        = -100.;
  tBBranch1TtbarFrame                 = -100.;
  tBBranch2TtbarFrame                 = -100.;
  bWBranch1TtbarFrame                 = -100.;
  bWBranch2TtbarFrame                 = -100.;
  tWBranch1TopInTtbarFrameWInTopFrame = -100.;
  tWBranch2TopInTtbarFrameWInTopFrame = -100.;
  qQbarTopFrame                       = -100.;
  qQbarDetFrame                       = -100.;
  pPbarTopFrame                       = -100.;
  pQbarTtbarFrame                     = -100.;
  pQTtbarFrame                        = -100.;
  pbarQbarTtbarFrame                  = -100.;
  pbarQTtbarFrame                     = -100.;
  bhad1QTopFrame                      = -100.;
  bhad1QbarTopFrame                   = -100.;
  bhad1PTtbarFrame                    = -100.;
  bhad1PbarTtbarFrame                 = -100.;
  bhad2QTtbarFrame                    = -100.;
  bhad2QbarTtbarFrame                 = -100.;
  bhad2PTopFrame                      = -100.;
  bhad2PbarTopFrame                   = -100.;
  qInW1FrameW1InDetFrame              = -100.;
  qbarInW1FrameW1InDetFrame           = -100.;
  pInW2FrameW2InDetFrame              = -100.;
  pbarInW2FrameW2InDetFrame           = -100.;

  tree->Branch("ttDetFrame"                         , &ttDetFrame                         , "ttDetFrame/F"                         );
  tree->Branch("bbDetFrame"                         , &bbDetFrame                         , "bbDetFrame/F"                         );
  tree->Branch("bbTtbarFrame"                       , &bbTtbarFrame                       , "bbTtbarFrame/F"                       );
  tree->Branch("WWTtbarFrame"                       , &WWTtbarFrame                       , "WWTtbarFrame/F"                       );
  tree->Branch("tBBranch1TtbarFrame"                , &tBBranch1TtbarFrame                , "tBBranch1TtbarFrame/F"                );
  tree->Branch("tBBranch2TtbarFrame"                , &tBBranch2TtbarFrame                , "tBBranch2TtbarFrame/F"                );
  tree->Branch("bWBranch1TtbarFrame"                , &bWBranch1TtbarFrame                , "bWBranch1TtbarFrame/F"                );
  tree->Branch("bWBranch2TtbarFrame"                , &bWBranch2TtbarFrame                , "bWBranch2TtbarFrame/F"                );
  tree->Branch("tWBranch1TopInTtbarFrameWInTopFrame", &tWBranch1TopInTtbarFrameWInTopFrame, "tWBranch1TopInTtbarFrameWInTopFrame/F");
  tree->Branch("tWBranch2TopInTtbarFrameWInTopFrame", &tWBranch2TopInTtbarFrameWInTopFrame, "tWBranch2TopInTtbarFrameWInTopFrame/F");
  tree->Branch("qQbarTopFrame"                      , &qQbarTopFrame                      , "qQbarTopFrame/F"                      );
  tree->Branch("qQbarDetFrame"                      , &qQbarDetFrame                      , "qQbarDetFrame/F"                      );
  tree->Branch("pPbarTopFrame"                      , &pPbarTopFrame                      , "pPbarTopFrame/F"                      );
  tree->Branch("pQbarTtbarFrame"                    , &pQbarTtbarFrame                    , "pQbarTtbarFrame/F"                    );
  tree->Branch("pQTtbarFrame"                       , &pQTtbarFrame                       , "pQTtbarFrame/F"                       );
  tree->Branch("pbarQbarTtbarFrame"                 , &pbarQbarTtbarFrame                 , "pbarQbarTtbarFrame/F"                 );
  tree->Branch("pbarQTtbarFrame"                    , &pbarQTtbarFrame                    , "pbarQTtbarFrame/F"                    );
  tree->Branch("bhad1QTopFrame"                     , &bhad1QTopFrame                     , "bhad1QTopFrame/F"                     );
  tree->Branch("bhad1QbarTopFrame"                  , &bhad1QbarTopFrame                  , "bhad1QbarTopFrame/F"                  );
  tree->Branch("bhad1PTtbarFrame"                   , &bhad1PTtbarFrame                   , "bhad1PTtbarFrame/F"                   );
  tree->Branch("bhad1PbarTtbarFrame"                , &bhad1PbarTtbarFrame                , "bhad1PbarTtbarFrame/F"                );
  tree->Branch("bhad2QTtbarFrame"                   , &bhad2QTtbarFrame                   , "bhad2QTtbarFrame/F"                   );
  tree->Branch("bhad2QbarTtbarFrame"                , &bhad2QbarTtbarFrame                , "bhad2QbarTtbarFrame/F"                );
  tree->Branch("bhad2PTopFrame"                     , &bhad2PTopFrame                     , "bhad2PTopFrame/F"                     );
  tree->Branch("bhad2PbarTopFrame"                  , &bhad2PbarTopFrame                  , "bhad2PbarTopFrame/F"                  );
  tree->Branch("qInW1FrameW1InDetFrame"             , &qInW1FrameW1InDetFrame             , "qInW1FrameW1InDetFrame/F"             );
  tree->Branch("qbarInW1FrameW1InDetFrame"          , &qbarInW1FrameW1InDetFrame          , "qbarInW1FrameW1InDetFrame/F"          );
  tree->Branch("pInW2FrameW2InDetFrame"             , &pInW2FrameW2InDetFrame             , "pInW2FrameW2InDetFrame/F"             );
  tree->Branch("pbarInW2FrameW2InDetFrame"          , &pbarInW2FrameW2InDetFrame          , "pbarInW2FrameW2InDetFrame/F"          );

  // jet-parton assignments
  fitAssigns = new short[6];
  for(short i = 0; i < 6; ++i){
    fitAssigns[i] = -1;
  }
  tree->Branch("fitAssigns", fitAssigns , "fitAssigns[6]/S");

  // 4-vectors of kinFit
  fitVecs = new TClonesArray("TLorentzVector", 6);
  tree->Branch("fitVecs", &fitVecs, 32000, -1);
  fitVecs->BypassStreamer();

  // discriminator of mva method
  multiJetMVADisc = -10.;
  tree->Branch("multiJetMVADisc", &multiJetMVADisc, "multiJetMVADisc/D");
  
  // number of pile up interactions
  nPU = -1;
  tree->Branch("nPU", &nPU, "nPU/S");

  // number of vertices
  nVertex = -1;
  tree->Branch("nVertex", &nVertex, "nVertex/S");
  
  /// genEvent information for PDF uncertainty

  id1 = -100;
  id2 = -100;
  Q   = -1.;
  x1  = -1.;
  x2  = -1.;

  // genEvent information not saved to tree if not needed
  if(GenSrc_.label() == "") return;

  doPDFUncertainty = true;

  tree->Branch("id1", &id1, "id1/I");
  tree->Branch("id2", &id2, "id2/I");
  tree->Branch("Q"  , &Q  , "Q/F"  );
  tree->Branch("x1" , &x1 , "x1/D" );
  tree->Branch("x2" , &x2 , "x2/D" );

}

/// produce n-tuple
void
FullHadTreeWriter::analyze(const edm::Event& event, const edm::EventSetup& iSetup)
{
  // Event
  edm::EventAuxiliary aux = event.eventAuxiliary();
  runNumber             = aux.run();
  luminosityBlockNumber = aux.luminosityBlock();
  eventNumber           = aux.event();

  edm::Handle<edm::View< pat::MET > > MET_h;
  event.getByLabel(METSrc_, MET_h);
  
  edm::Handle<edm::View< pat::Jet > > jets_h;
  event.getByLabel(JetSrc_, jets_h);
  
  edm::Handle<TtFullHadronicEvent> fullHadEvent_h;
  event.getByLabel(FitSrc_, fullHadEvent_h);
  
  edm::Handle<GenEventInfoProduct> genEventInfo_h;
  event.getByLabel(GenSrc_, genEventInfo_h);
  
  edm::Handle<double> multiJetMVADisc_h;
  event.getByLabel(MultiJetMVADiscSrc_, multiJetMVADisc_h);
  
  edm::Handle<edm::View<PileupSummaryInfo> > PU_h;
  event.getByLabel(PUSrc_, PU_h);
  
  edm::Handle<std::vector<reco::Vertex> > vertecies_h;
  event.getByLabel(VertexSrc_, vertecies_h);
  
  edm::Handle<double> PUWeightSrc_h;
  event.getByLabel(PUWeightSrc_, PUWeightSrc_h);

  PUweight = PUWeightSrc_h.isValid() ? *PUWeightSrc_h : -100.;

  edm::ESHandle<BtagPerformance> bTagPerf_h;

  if(MET_h.isValid()){
    MET->Clear();
    for(edm::View< pat::MET >::const_iterator met = MET_h->begin(); met != MET_h->end(); ++met){
      new((*MET)[0]) TLorentzVector(met->px(), met->py(), met->pz(), met->energy());
      break;
    }
  }

  if(jets_h.isValid()){
    Njet = (int)jets_h->size();

    std::vector<pat::Jet> jets_v;

    unsigned short i = 0;
    jets->Clear();
    for(edm::View< pat::Jet >::const_iterator jet = jets_h->begin(); jet != jets_h->end(); ++jet, ++i){
      jets_v.push_back(*jet);
      new((*jets)[i]) TLorentzVector(jet->px(), jet->py(), jet->pz(), jet->energy());
      bTag_TCHE  [i*(kBTagMAX+1)] = jet->bDiscriminator("trackCountingHighEffBJetTags");
      bTag_TCHP  [i*(kBTagMAX+1)] = jet->bDiscriminator("trackCountingHighPurBJetTags");
      bTag_SSVHE [i*(kBTagMAX+1)] = jet->bDiscriminator("simpleSecondaryVertexHighEffBJetTags");
      bTag_SSVHP [i*(kBTagMAX+1)] = jet->bDiscriminator("simpleSecondaryVertexHighPurBJetTags");
      bTag_CSV     [i]            = jet->bDiscriminator("combinedSecondaryVertexBJetTags");
      bTag_CSVMVA  [i]            = jet->bDiscriminator("combinedSecondaryVertexMVABJetTags");
      charge       [i]            = jet->jetCharge();
      pdgId        [i]            = (jet->genParticle()) ? jet->genParticle()->pdgId() : 0;
      partonFlavour[i]            = jet->partonFlavour();
      
      if(kBTagMAX > 0){ 
	unsigned short arrayCount = 0;
	for( size_t ibTag = 0; ibTag < bTagName_.size(); ++ibTag , ++arrayCount ){

	  if(arrayCount == kBTagMAX) arrayCount = 0;

	  iSetup.get<BTagPerformanceRecord>().get( bTagName_[ibTag],bTagPerf_h);
	  const BtagPerformance & bTagPerf = *(bTagPerf_h.product());

	  BinningPointByMap measurePoint;
	  measurePoint.insert(BinningVariables::JetEt, jet->et());
	  measurePoint.insert(BinningVariables::JetAbsEta, std::abs(jet->eta()));

	  if     (bTagName_[ibTag].find("TCHEM" )!=std::string::npos) bTag_TCHE [i*(kBTagMAX+1)+arrayCount+1] = bTagPerf.getResult( measureMap[bTagVal_[ibTag]], measurePoint);
	  else if(bTagName_[ibTag].find("TCHPT" )!=std::string::npos) bTag_TCHP [i*(kBTagMAX+1)+arrayCount+1] = bTagPerf.getResult( measureMap[bTagVal_[ibTag]], measurePoint);
	  else if(bTagName_[ibTag].find("SSVHEM")!=std::string::npos) bTag_SSVHE[i*(kBTagMAX+1)+arrayCount+1] = bTagPerf.getResult( measureMap[bTagVal_[ibTag]], measurePoint);
	  else if(bTagName_[ibTag].find("SSVHPT")!=std::string::npos) bTag_SSVHP[i*(kBTagMAX+1)+arrayCount+1] = bTagPerf.getResult( measureMap[bTagVal_[ibTag]], measurePoint);

	}
      }
      /*
      //////////
      

      for( size_t ibTag = 0; ibTag < bTagName_.size(); ++ibTag )
	{
	  std::cout << "Testing: " << bTagName_[ ibTag ] << " of type " << bTagVal_[ ibTag ] << std::endl;

	  //Setup our measurement
	  iSetup.get<BTagPerformanceRecord>().get( bTagName_[ ibTag ],bTagPerf_h);
	  const BtagPerformance & bTagPerf = *(bTagPerf_h.product());

	  //Working point
	  std::cout << "Working point: " << bTagPerf.workingPoint().cut() << std::endl;
	  //Setup the point we wish to test!
	  BinningPointByMap measurePoint;
	  measurePoint.insert(BinningVariables::JetEt,jet->pt());
	  measurePoint.insert(BinningVariables::JetAbsEta,std::abs(jet->eta()));

	  std::cout << "Is it OK? " << bTagPerf.isResultOk( measureMap[ bTagVal_[ ibTag] ], measurePoint)
		    << " result at "<< jet->pt() << " GeV, " << std::abs(jet->eta()) << " |eta| " << bTagPerf.getResult( measureMap[ bTagVal_[ ibTag] ], measurePoint)
		    << std::endl;

	  std::cout << "Error checking!" << std::endl;
	  measurePoint.reset();
	  measurePoint.insert(BinningVariables::JetEt,0);
	  measurePoint.insert(BinningVariables::JetAbsEta,10);

	  std::cout << "Is it OK? " << bTagPerf.isResultOk( measureMap[ bTagVal_[ ibTag] ], measurePoint)
		    << " result at 0 GeV, 10 |eta| " << bTagPerf.getResult( measureMap[ bTagVal_[ ibTag] ], measurePoint)
		    << std::endl;
	  std::cout << std::endl;
	}

      //std::cout << "Values: " << PerformanceResult::BTAGNBEFF << " " << PerformanceResult::MUERR << " " << std::endl;

      
      //////////
      */
    }
    TtFullHadSignalSel mvaVariables = TtFullHadSignalSel(jets_v);

    H      = mvaVariables.H();
    Ht     = mvaVariables.Ht();
    Ht123  = mvaVariables.Ht123();
    Ht3jet = mvaVariables.Ht3jet();
    sqrt_s = mvaVariables.sqrt_s();
    Et56   = mvaVariables.Et56();
    M3     = mvaVariables.M3();
    
    for(int i = 0 ; i < Njet ; ++i){
      EtSin2Theta[i]  = mvaVariables.EtSin2Theta(i+1);
      theta[i]        = mvaVariables.theta(i+1);	    
      sinTheta[i]     = mvaVariables.sinTheta(i+1);   
      EtStar[i]       = mvaVariables.EtSin2Theta(i+1,true);
      thetaStar[i]    = mvaVariables.theta(i+1, true);
      sinThetaStar[i] = mvaVariables.sinTheta(i+1,true);
    }
    EtSin2Theta3jet  = mvaVariables.EtSin2Theta3jet();
    theta3jet        = mvaVariables.theta3jet();      
    sinTheta3jet     = mvaVariables.sinTheta3jet();   
    EtStar3jet       = mvaVariables.EtSin2Theta3jet(true);
    thetaStar3jet    = mvaVariables.theta3jet(true);
    sinThetaStar3jet = mvaVariables.sinTheta3jet(true);
    
    pt1_pt6 = mvaVariables.pti_ptj(1,6);
    pt1_pt5 = mvaVariables.pti_ptj(1,5);
    pt1_pt4 = mvaVariables.pti_ptj(1,4);
    pt1_pt3 = mvaVariables.pti_ptj(1,3);
    pt1_pt2 = mvaVariables.pti_ptj(1,2);
    pt2_pt6 = mvaVariables.pti_ptj(2,6);
    pt2_pt5 = mvaVariables.pti_ptj(2,5);
    pt2_pt4 = mvaVariables.pti_ptj(2,4);
    pt2_pt3 = mvaVariables.pti_ptj(2,3);
    pt3_pt6 = mvaVariables.pti_ptj(3,6);
    pt3_pt5 = mvaVariables.pti_ptj(3,5);
    pt3_pt4 = mvaVariables.pti_ptj(3,4);
    pt4_pt6 = mvaVariables.pti_ptj(4,6);
    pt4_pt5 = mvaVariables.pti_ptj(4,5);
    pt5_pt6 = mvaVariables.pti_ptj(5,6);

    pt1_pt6_norm = mvaVariables.pti_ptj(1,6,true);
    pt1_pt5_norm = mvaVariables.pti_ptj(1,5,true);
    pt1_pt4_norm = mvaVariables.pti_ptj(1,4,true);
    pt1_pt3_norm = mvaVariables.pti_ptj(1,3,true);
    pt1_pt2_norm = mvaVariables.pti_ptj(1,2,true);
    pt2_pt6_norm = mvaVariables.pti_ptj(2,6,true);
    pt2_pt5_norm = mvaVariables.pti_ptj(2,5,true);
    pt2_pt4_norm = mvaVariables.pti_ptj(2,4,true);
    pt2_pt3_norm = mvaVariables.pti_ptj(2,3,true);
    pt3_pt6_norm = mvaVariables.pti_ptj(3,6,true);
    pt3_pt5_norm = mvaVariables.pti_ptj(3,5,true);
    pt3_pt4_norm = mvaVariables.pti_ptj(3,4,true);
    pt4_pt6_norm = mvaVariables.pti_ptj(4,6,true);
    pt4_pt5_norm = mvaVariables.pti_ptj(4,5,true);
    pt5_pt6_norm = mvaVariables.pti_ptj(5,6,true);
    
    jet1_etaetaMoment = mvaVariables.jet_etaetaMoment(1);
    jet2_etaetaMoment = mvaVariables.jet_etaetaMoment(2);
    jet3_etaetaMoment = mvaVariables.jet_etaetaMoment(3);
    jet4_etaetaMoment = mvaVariables.jet_etaetaMoment(4);
    jet5_etaetaMoment = mvaVariables.jet_etaetaMoment(5);
    jet6_etaetaMoment = mvaVariables.jet_etaetaMoment(6);
    jet1_etaphiMoment = mvaVariables.jet_etaphiMoment(1);
    jet2_etaphiMoment = mvaVariables.jet_etaphiMoment(2);
    jet3_etaphiMoment = mvaVariables.jet_etaphiMoment(3);
    jet4_etaphiMoment = mvaVariables.jet_etaphiMoment(4);
    jet5_etaphiMoment = mvaVariables.jet_etaphiMoment(5);
    jet6_etaphiMoment = mvaVariables.jet_etaphiMoment(6);
    jet1_phiphiMoment = mvaVariables.jet_phiphiMoment(1);
    jet2_phiphiMoment = mvaVariables.jet_phiphiMoment(2);
    jet3_phiphiMoment = mvaVariables.jet_phiphiMoment(3);
    jet4_phiphiMoment = mvaVariables.jet_phiphiMoment(4);
    jet5_phiphiMoment = mvaVariables.jet_phiphiMoment(5);
    jet6_phiphiMoment = mvaVariables.jet_phiphiMoment(6);

    jet1_etaetaMomentMoment = mvaVariables.jet_etaetaMomentMoment(1);
    jet2_etaetaMomentMoment = mvaVariables.jet_etaetaMomentMoment(2);
    jet3_etaetaMomentMoment = mvaVariables.jet_etaetaMomentMoment(3);
    jet4_etaetaMomentMoment = mvaVariables.jet_etaetaMomentMoment(4);
    jet5_etaetaMomentMoment = mvaVariables.jet_etaetaMomentMoment(5);
    jet6_etaetaMomentMoment = mvaVariables.jet_etaetaMomentMoment(6);
    jet1_etaphiMomentMoment = mvaVariables.jet_etaphiMomentMoment(1);
    jet2_etaphiMomentMoment = mvaVariables.jet_etaphiMomentMoment(2);
    jet3_etaphiMomentMoment = mvaVariables.jet_etaphiMomentMoment(3);
    jet4_etaphiMomentMoment = mvaVariables.jet_etaphiMomentMoment(4);
    jet5_etaphiMomentMoment = mvaVariables.jet_etaphiMomentMoment(5);
    jet6_etaphiMomentMoment = mvaVariables.jet_etaphiMomentMoment(6);
    jet1_phiphiMomentMoment = mvaVariables.jet_phiphiMomentMoment(1);
    jet2_phiphiMomentMoment = mvaVariables.jet_phiphiMomentMoment(2);
    jet3_phiphiMomentMoment = mvaVariables.jet_phiphiMomentMoment(3);
    jet4_phiphiMomentMoment = mvaVariables.jet_phiphiMomentMoment(4);
    jet5_phiphiMomentMoment = mvaVariables.jet_phiphiMomentMoment(5);
    jet6_phiphiMomentMoment = mvaVariables.jet_phiphiMomentMoment(6);

    jets_etaetaMoment = mvaVariables.jets_etaetaMoment();
    jets_etaphiMoment = mvaVariables.jets_etaphiMoment();
    jets_phiphiMoment = mvaVariables.jets_phiphiMoment();

    jet1_etaetaMomentLogEt = mvaVariables.jet_etaetaMomentLogEt(1);
    jet2_etaetaMomentLogEt = mvaVariables.jet_etaetaMomentLogEt(2);
    jet3_etaetaMomentLogEt = mvaVariables.jet_etaetaMomentLogEt(3);
    jet4_etaetaMomentLogEt = mvaVariables.jet_etaetaMomentLogEt(4);
    jet5_etaetaMomentLogEt = mvaVariables.jet_etaetaMomentLogEt(5);
    jet6_etaetaMomentLogEt = mvaVariables.jet_etaetaMomentLogEt(6);
    jet1_etaphiMomentLogEt = mvaVariables.jet_etaphiMomentLogEt(1);
    jet2_etaphiMomentLogEt = mvaVariables.jet_etaphiMomentLogEt(2);
    jet3_etaphiMomentLogEt = mvaVariables.jet_etaphiMomentLogEt(3);
    jet4_etaphiMomentLogEt = mvaVariables.jet_etaphiMomentLogEt(4);
    jet5_etaphiMomentLogEt = mvaVariables.jet_etaphiMomentLogEt(5);
    jet6_etaphiMomentLogEt = mvaVariables.jet_etaphiMomentLogEt(6);
    jet1_phiphiMomentLogEt = mvaVariables.jet_phiphiMomentLogEt(1);
    jet2_phiphiMomentLogEt = mvaVariables.jet_phiphiMomentLogEt(2);
    jet3_phiphiMomentLogEt = mvaVariables.jet_phiphiMomentLogEt(3);
    jet4_phiphiMomentLogEt = mvaVariables.jet_phiphiMomentLogEt(4);
    jet5_phiphiMomentLogEt = mvaVariables.jet_phiphiMomentLogEt(5);
    jet6_phiphiMomentLogEt = mvaVariables.jet_phiphiMomentLogEt(6);

    jet1_etaetaMomentMomentLogEt = mvaVariables.jet_etaetaMomentMomentLogEt(1);
    jet2_etaetaMomentMomentLogEt = mvaVariables.jet_etaetaMomentMomentLogEt(2);
    jet3_etaetaMomentMomentLogEt = mvaVariables.jet_etaetaMomentMomentLogEt(3);
    jet4_etaetaMomentMomentLogEt = mvaVariables.jet_etaetaMomentMomentLogEt(4);
    jet5_etaetaMomentMomentLogEt = mvaVariables.jet_etaetaMomentMomentLogEt(5);
    jet6_etaetaMomentMomentLogEt = mvaVariables.jet_etaetaMomentMomentLogEt(6);
    jet1_etaphiMomentMomentLogEt = mvaVariables.jet_etaphiMomentMomentLogEt(1);
    jet2_etaphiMomentMomentLogEt = mvaVariables.jet_etaphiMomentMomentLogEt(2);
    jet3_etaphiMomentMomentLogEt = mvaVariables.jet_etaphiMomentMomentLogEt(3);
    jet4_etaphiMomentMomentLogEt = mvaVariables.jet_etaphiMomentMomentLogEt(4);
    jet5_etaphiMomentMomentLogEt = mvaVariables.jet_etaphiMomentMomentLogEt(5);
    jet6_etaphiMomentMomentLogEt = mvaVariables.jet_etaphiMomentMomentLogEt(6);
    jet1_phiphiMomentMomentLogEt = mvaVariables.jet_phiphiMomentMomentLogEt(1);
    jet2_phiphiMomentMomentLogEt = mvaVariables.jet_phiphiMomentMomentLogEt(2);
    jet3_phiphiMomentMomentLogEt = mvaVariables.jet_phiphiMomentMomentLogEt(3);
    jet4_phiphiMomentMomentLogEt = mvaVariables.jet_phiphiMomentMomentLogEt(4);
    jet5_phiphiMomentMomentLogEt = mvaVariables.jet_phiphiMomentMomentLogEt(5);
    jet6_phiphiMomentMomentLogEt = mvaVariables.jet_phiphiMomentMomentLogEt(6);

    jets_etaetaMomentLogEt = mvaVariables.jets_etaetaMomentLogEt();
    jets_etaphiMomentLogEt = mvaVariables.jets_etaphiMomentLogEt();
    jets_phiphiMomentLogEt = mvaVariables.jets_phiphiMomentLogEt();

    aplanarity  = mvaVariables.aplanarity ();
    sphericity  = mvaVariables.sphericity ();
    circularity = mvaVariables.circularity();
    isotropy    = mvaVariables.isotropy   ();
    C           = mvaVariables.C          ();
    D           = mvaVariables.D          ();

    aplanarityAll  = mvaVariables.aplanarity (true);
    sphericityAll  = mvaVariables.sphericity (true);
    circularityAll = mvaVariables.circularity(true);
    isotropyAll    = mvaVariables.isotropy   (true);
    CAll           = mvaVariables.C          (true);
    DAll           = mvaVariables.D          (true);

    aplanarityAllCMS  = mvaVariables.aplanarityAllCMS ();
    sphericityAllCMS  = mvaVariables.sphericityAllCMS ();
    circularityAllCMS = mvaVariables.circularityAllCMS();
    isotropyAllCMS    = mvaVariables.isotropyAllCMS   ();
    CAllCMS           = mvaVariables.CAllCMS          ();
    DAllCMS           = mvaVariables.DAllCMS          ();

    centrality    = mvaVariables.centrality();
    centralityAlt = mvaVariables.centrality(true);

    thrust    = mvaVariables.thrust();
    thrustCMS = mvaVariables.thrust(true);

  }
  
  // reset variables of kinFit
  prob    = -1.;
  chi2    = -1.;
  topMass = -1.;
  ttMass  = -1.;
  comboTypeValue = 0;

  ptAsy    = -100.;
  ptAsyBar = -100.;
 
  ttDetFrame                          = -100.;
  bbDetFrame                          = -100.;
  bbTtbarFrame                        = -100.;
  WWTtbarFrame                        = -100.;
  tBBranch1TtbarFrame                 = -100.;
  tBBranch2TtbarFrame                 = -100.;
  bWBranch1TtbarFrame                 = -100.;
  bWBranch2TtbarFrame                 = -100.;
  tWBranch1TopInTtbarFrameWInTopFrame = -100.;
  tWBranch2TopInTtbarFrameWInTopFrame = -100.;
  qQbarTopFrame                       = -100.;
  qQbarDetFrame                       = -100.;
  pPbarTopFrame                       = -100.;
  pQbarTtbarFrame                     = -100.;
  pQTtbarFrame                        = -100.;
  pbarQbarTtbarFrame                  = -100.;
  pbarQTtbarFrame                     = -100.;
  bhad1QTopFrame                      = -100.;
  bhad1QbarTopFrame                   = -100.;
  bhad1PTtbarFrame                    = -100.;
  bhad1PbarTtbarFrame                 = -100.;
  bhad2QTtbarFrame                    = -100.;
  bhad2QbarTtbarFrame                 = -100.;
  bhad2PTopFrame                      = -100.;
  bhad2PbarTopFrame                   = -100.;
  qInW1FrameW1InDetFrame              = -100.;
  qbarInW1FrameW1InDetFrame           = -100.;
  pInW2FrameW2InDetFrame              = -100.;
  pbarInW2FrameW2InDetFrame           = -100.;

  for(short i = 0; i < 6; ++i){
    fitAssigns[i] = -1;
  }
  fitVecs->Clear();

  if( fullHadEvent_h.isValid() && fullHadEvent_h->isHypoValid("kKinFit") ){
    prob    = fullHadEvent_h->fitProb();
    chi2    = fullHadEvent_h->fitChi2();
    topMass = fullHadEvent_h->top("kKinFit")->mass();
    ttMass  = (fullHadEvent_h->top("kKinFit")->p4() + fullHadEvent_h->topBar("kKinFit")->p4()).mass();

    fitAssigns[TtFullHadEvtPartons::LightQ   ] = fullHadEvent_h->jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::LightQ   ];
    fitAssigns[TtFullHadEvtPartons::LightQBar] = fullHadEvent_h->jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::LightQBar];
    fitAssigns[TtFullHadEvtPartons::B        ] = fullHadEvent_h->jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::B        ];
    fitAssigns[TtFullHadEvtPartons::LightP   ] = fullHadEvent_h->jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::LightP   ];
    fitAssigns[TtFullHadEvtPartons::LightPBar] = fullHadEvent_h->jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::LightPBar];
    fitAssigns[TtFullHadEvtPartons::BBar     ] = fullHadEvent_h->jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::BBar     ];

    new((*fitVecs)[TtFullHadEvtPartons::LightQ   ]) TLorentzVector(fullHadEvent_h->lightQ   ("kKinFit")->px(),
								   fullHadEvent_h->lightQ   ("kKinFit")->py(),
								   fullHadEvent_h->lightQ   ("kKinFit")->pz(),
								   fullHadEvent_h->lightQ   ("kKinFit")->energy());
    new((*fitVecs)[TtFullHadEvtPartons::LightQBar]) TLorentzVector(fullHadEvent_h->lightQBar("kKinFit")->px(),
								   fullHadEvent_h->lightQBar("kKinFit")->py(),
								   fullHadEvent_h->lightQBar("kKinFit")->pz(),
								   fullHadEvent_h->lightQBar("kKinFit")->energy());
    new((*fitVecs)[TtFullHadEvtPartons::B        ]) TLorentzVector(fullHadEvent_h->b        ("kKinFit")->px(),
								   fullHadEvent_h->b        ("kKinFit")->py(),
								   fullHadEvent_h->b        ("kKinFit")->pz(),
								   fullHadEvent_h->b        ("kKinFit")->energy());
    new((*fitVecs)[TtFullHadEvtPartons::LightP   ]) TLorentzVector(fullHadEvent_h->lightP   ("kKinFit")->px(),
								   fullHadEvent_h->lightP   ("kKinFit")->py(),
								   fullHadEvent_h->lightP   ("kKinFit")->pz(),
								   fullHadEvent_h->lightP   ("kKinFit")->energy());
    new((*fitVecs)[TtFullHadEvtPartons::LightPBar]) TLorentzVector(fullHadEvent_h->lightPBar("kKinFit")->px(),
								   fullHadEvent_h->lightPBar("kKinFit")->py(),
								   fullHadEvent_h->lightPBar("kKinFit")->pz(),
								   fullHadEvent_h->lightPBar("kKinFit")->energy());
    new((*fitVecs)[TtFullHadEvtPartons::BBar     ]) TLorentzVector(fullHadEvent_h->bBar     ("kKinFit")->px(),
								   fullHadEvent_h->bBar     ("kKinFit")->py(),
								   fullHadEvent_h->bBar     ("kKinFit")->pz(),
								   fullHadEvent_h->bBar     ("kKinFit")->energy());
    if( fullHadEvent_h->isHypoValid("kGenMatch") )
      comboTypeValue = comboType(fullHadEvent_h);
    if( !fullHadEvent_h->isHypoValid("kGenMatch") )
      comboTypeValue = 5;

    ptAsy    = (fullHadEvent_h->b   ("kKinFit")->pt()-fullHadEvent_h->wPlus ("kKinFit")->pt())/(fullHadEvent_h->b   ("kKinFit")->pt()+fullHadEvent_h->wPlus ("kKinFit")->pt());
    ptAsyBar = (fullHadEvent_h->bBar("kKinFit")->pt()-fullHadEvent_h->wMinus("kKinFit")->pt())/(fullHadEvent_h->bBar("kKinFit")->pt()+fullHadEvent_h->wMinus("kKinFit")->pt());

    // calculate angles from the 4 momentum vectors
    TopAngles angles = TopAngles::TopAngles(fullHadEvent_h->b   ("kKinFit")->p4(), fullHadEvent_h->lightQ("kKinFit")->p4(), fullHadEvent_h->lightQBar("kKinFit")->p4(),
					    fullHadEvent_h->bBar("kKinFit")->p4(), fullHadEvent_h->lightP("kKinFit")->p4(), fullHadEvent_h->lightPBar("kKinFit")->p4());

    ttDetFrame                          =  angles.ttDetFrame()                         ;			
    bbDetFrame                          =  angles.bbDetFrame()                         ;			
    bbTtbarFrame                        =  angles.bbTtbarFrame()                       ;			
    WWTtbarFrame                        =  angles.WWTtbarFrame()                       ;			
    tBBranch1TtbarFrame                 =  angles.tBBranch1TtbarFrame()                ;			
    tBBranch2TtbarFrame                 =  angles.tBBranch2TtbarFrame()                ;			
    bWBranch1TtbarFrame                 =  angles.bWBranch1TtbarFrame()                ;			
    bWBranch2TtbarFrame                 =  angles.bWBranch2TtbarFrame()                ;			
    tWBranch1TopInTtbarFrameWInTopFrame =  angles.tWBranch1TopInTtbarFrameWInTopFrame();	
    tWBranch2TopInTtbarFrameWInTopFrame =  angles.tWBranch2TopInTtbarFrameWInTopFrame();	
    qQbarTopFrame                       =  angles.qQbarTopFrame()                      ;			
    qQbarDetFrame                       =  angles.qQbarDetFrame()                      ;			
    pPbarTopFrame                       =  angles.pPbarTopFrame()                      ;			
    pQbarTtbarFrame                     =  angles.pQbarTtbarFrame()                    ;			
    pQTtbarFrame                        =  angles.pQTtbarFrame()                       ;			
    pbarQbarTtbarFrame                  =  angles.pbarQbarTtbarFrame()                 ;			
    pbarQTtbarFrame                     =  angles.pbarQTtbarFrame()                    ;			
    bhad1QTopFrame                      =  angles.bhad1QTopFrame()                     ;			
    bhad1QbarTopFrame                   =  angles.bhad1QbarTopFrame()                  ;			
    bhad1PTtbarFrame                    =  angles.bhad1PTtbarFrame()                   ;			
    bhad1PbarTtbarFrame                 =  angles.bhad1PbarTtbarFrame()                ;			
    bhad2QTtbarFrame                    =  angles.bhad2QTtbarFrame()                   ;			
    bhad2QbarTtbarFrame                 =  angles.bhad2QbarTtbarFrame()                ;			
    bhad2PTopFrame                      =  angles.bhad2PTopFrame()                     ;			
    bhad2PbarTopFrame                   =  angles.bhad2PbarTopFrame()                  ;			
    qInW1FrameW1InDetFrame              =  angles.qInW1FrameW1InDetFrame()             ;		
    qbarInW1FrameW1InDetFrame           =  angles.qbarInW1FrameW1InDetFrame()          ;		
    pInW2FrameW2InDetFrame              =  angles.pInW2FrameW2InDetFrame()             ; 		
    pbarInW2FrameW2InDetFrame           =  angles.pbarInW2FrameW2InDetFrame()          ;                

  }
  
  multiJetMVADisc = multiJetMVADisc_h.isValid() ? *multiJetMVADisc_h : -10.;

  nPU = -1;

  if(PU_h.isValid()){
    for(edm::View<PileupSummaryInfo>::const_iterator iterPU = PU_h->begin(); iterPU != PU_h->end(); ++iterPU){  // vector size is 3
      if(iterPU->getBunchCrossing()==0){ // -1: previous BX, 0: current BX,  1: next BX
	nPU = iterPU->getPU_NumInteractions();
	break;
      }
    }
  }

  nVertex = vertecies_h.isValid() ? vertecies_h->size() : -1;

  if(doPDFUncertainty && genEventInfo_h.isValid()){

    Q   = genEventInfo_h->pdf()->scalePDF;
    id1 = genEventInfo_h->pdf()->id.first;
    id2 = genEventInfo_h->pdf()->id.second;
    x1  = genEventInfo_h->pdf()->x.first;
    x2  = genEventInfo_h->pdf()->x.second;

  }

  tree->Fill();
}

/// function to find types of jet-combinations in KinFits (1 right, 2 branches right, but inner-branche particles mixup, 3 inter-branch mixup, 4 missing jet)
int
FullHadTreeWriter::comboType(edm::Handle<TtFullHadronicEvent> fullHadEvent_h)
{
  /// vector to store the jet indices
  std::vector<int> jetIndex(12);
  /// store position in jetIndex vector with corresponding particle name
  enum whichParticle{LQ, LQBar, B, BBar, LP, LPBar, LQ_Gen, LQBar_Gen, B_Gen, BBar_Gen, LP_Gen, LPBar_Gen};

  int lightQFit    = fullHadEvent_h->jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::LightQ   ];
  int lightQBarFit = fullHadEvent_h->jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::LightQBar];
  int bFit         = fullHadEvent_h->jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::B        ];
  int bBarFit      = fullHadEvent_h->jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::BBar     ];
  int lightPFit    = fullHadEvent_h->jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::LightP   ];
  int lightPBarFit = fullHadEvent_h->jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::LightPBar];

  int lightQGen    = fullHadEvent_h->jetLeptonCombination("kGenMatch")[TtFullHadEvtPartons::LightQ   ];
  int lightQBarGen = fullHadEvent_h->jetLeptonCombination("kGenMatch")[TtFullHadEvtPartons::LightQBar];
  int bGen         = fullHadEvent_h->jetLeptonCombination("kGenMatch")[TtFullHadEvtPartons::B        ];
  int bBarGen      = fullHadEvent_h->jetLeptonCombination("kGenMatch")[TtFullHadEvtPartons::BBar     ];
  int lightPGen    = fullHadEvent_h->jetLeptonCombination("kGenMatch")[TtFullHadEvtPartons::LightP   ];
  int lightPBarGen = fullHadEvent_h->jetLeptonCombination("kGenMatch")[TtFullHadEvtPartons::LightPBar];

  jetIndex[LQ   ] = lightQFit;
  jetIndex[LQBar] = lightQBarFit;
  jetIndex[B    ] = bFit;
  jetIndex[BBar ] = bBarFit;
  jetIndex[LP   ] = lightPFit;
  jetIndex[LPBar] = lightPBarFit;

  jetIndex[LQ_Gen   ] = lightQGen;
  jetIndex[LQBar_Gen] = lightQBarGen;
  jetIndex[B_Gen    ] = bGen;
  jetIndex[BBar_Gen ] = bBarGen;
  jetIndex[LP_Gen   ] = lightPGen;
  jetIndex[LPBar_Gen] = lightPBarGen;

  std::list<int> fit;
  std::list<int> fitBar;
  std::list<int> gen;
  std::list<int> genBar;

  fit.push_back(jetIndex[LQ]);
  fit.push_back(jetIndex[LQBar]);
  fit.push_back(jetIndex[B]);

  fitBar.push_back(jetIndex[LP]);
  fitBar.push_back(jetIndex[LPBar]);
  fitBar.push_back(jetIndex[BBar]);

  gen.push_back(jetIndex[LQ_Gen]);
  gen.push_back(jetIndex[LQBar_Gen]);
  gen.push_back(jetIndex[B_Gen]);

  genBar.push_back(jetIndex[LP_Gen]);
  genBar.push_back(jetIndex[LPBar_Gen]);
  genBar.push_back(jetIndex[BBar_Gen]);

  if( ( bFit == bGen && bBarFit == bBarGen ) || ( bFit == bBarGen && bBarFit == bGen ) ) {

    if( bFit == bGen &&
	( ( lightQFit == lightQGen    && lightQBarFit == lightQBarGen ) ||
	  ( lightQFit == lightQBarGen && lightQBarFit == lightQGen    ) ) &&
	( ( lightPFit == lightPGen    && lightPBarFit == lightPBarGen ) ||
	  ( lightPFit == lightPBarGen && lightPBarFit == lightPGen    ) ) )
      return 1;
    
    if( bBarFit == bGen &&
	( ( lightPFit == lightQGen    && lightPBarFit == lightQBarGen ) ||
	  ( lightPFit == lightQBarGen && lightPBarFit == lightQGen    ) ) &&
	( ( lightQFit == lightPGen    && lightQBarFit == lightPBarGen ) ||
	  ( lightQFit == lightPBarGen && lightQBarFit == lightPGen    ) ) )
      return 1;
  }

  fit.sort();
  fitBar.sort();
  gen.sort();
  genBar.sort();

  if( ( fit == gen && fitBar == genBar ) || ( fit == genBar && fitBar == gen ) ) return 2;

  fit.splice(fit.end(),fitBar);
  gen.splice(gen.end(),genBar);

  fit.sort();
  fitBar.sort();

  if( fit == gen ) return 3;

  return 4;
}

void
FullHadTreeWriter::endJob()
{
  delete[] bTag_TCHE;
  delete[] bTag_TCHP;
  delete[] bTag_SSVHE;
  delete[] bTag_SSVHP;
  delete[] bTag_CSV;
  delete[] bTag_CSVMVA;

  delete[] fitAssigns;
  delete[] pdgId;
  delete[] partonFlavour;

  delete[] EtSin2Theta;
  delete[] theta;
  delete[] sinTheta;
  delete[] EtStar;
  delete[] thetaStar;
  delete[] sinThetaStar;

  jets->Delete();
  MET->Delete();
  fitVecs->Delete();
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( FullHadTreeWriter );
