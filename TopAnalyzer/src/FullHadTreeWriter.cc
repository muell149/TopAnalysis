#include <stdio.h>

#include <TMath.h>

#include "TopAnalysis/TopAnalyzer/interface/TopAngles.h"
#include "TopAnalysis/TopAnalyzer/interface/FullHadTreeWriter.h"
#include "TopQuarkAnalysis/TopEventSelection/interface/TtFullHadSignalSel.h"

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

#include "AnalysisDataFormats/TopObjects/interface/TtFullHadEvtPartons.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

/// default constructor
FullHadTreeWriter::FullHadTreeWriter(const edm::ParameterSet& cfg) :
  JetSrc_            (cfg.getParameter<edm::InputTag>("JetSrc")),
  METSrc_            (cfg.getParameter<edm::InputTag>("METSrc")),
  MuonSrc_           (cfg.getParameter<edm::InputTag>("MuonSrc")),
  ElectronSrc_       (cfg.getParameter<edm::InputTag>("ElectronSrc")),
  GluonTagSrc_       (cfg.getParameter<edm::InputTag>("GluonTagSrc")),
  //GenJetSrc_         (cfg.getParameter<edm::InputTag>("GenJetSrc")),
  //GenPartonSrc_      (cfg.getParameter<edm::InputTag>("GenPartonSrc")),
  FitSrc_            (cfg.getParameter<edm::InputTag>("FitSrc")),
  GenMatch2Src_      (cfg.getParameter<edm::InputTag>("GenMatch2Src")),
  MultiJetMVADiscSrc_(cfg.getParameter<edm::InputTag>("MultiJetMVADiscSrc")),
  GenSrc_            (cfg.getParameter<edm::InputTag>("GenSrc")),
  PUSrc_             (cfg.getParameter<edm::InputTag>("PUSrc")),
  VertexSrc_         (cfg.getParameter<edm::InputTag>("VertexSrc")),
  PUWeightSrc_       (cfg.getParameter<edm::InputTag>("PUweightSrc")),
  MCweight_          (cfg.getParameter<double>("MCweight")),
  bTagName_          (cfg.getParameter<std::vector<std::string> >("bTagName")),
  bTagVal_           (cfg.getParameter<std::vector<std::string> >("bTagVal" )),
  DoPDFUncertainty_  (cfg.getParameter<bool>("DoPDFUncertainty")),
  kMAX(50), kMAXCombo(10000), checkedIsPFJet(false), isPFJet(false), checkedHasL7PartonCor(false), hasL7PartonCor(false), checkedQGTag(false), hasQGTag(false)
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
  //TEST();

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

  if(FitSrc_.label() != ""){
    // identify event by the following number coding:
    // -10 : undefined
    //  -1 : non ttbar MC
    //   0 : DATA
    //   1 : fully hadronic        ttbar MC
    //  21 : semileptonic electron ttbar MC
    //  22 : semileptonic muon     ttbar MC
    //  23 : semileptonic tau      ttbar MC
    // 311 : dileptonic e   e      ttbar MC
    // 312 : dileptonic e   mu     ttbar MC
    // 313 : dileptonic e   tau    ttbar MC
    // 322 : dileptonic mu  mu     ttbar MC
    // 323 : dileptonic mu  tau    ttbar MC
    // 333 : dileptonic tau tau    ttbar MC
    eventType = -10;
    tree->Branch("eventType", &eventType, "eventType/S");
  }

  // event weight
  MCweight = MCweight_;
  tree->Branch("MCweight", &MCweight, "MCweight/D");

  if(PUWeightSrc_.label() != ""){
    PUweight = -10.;
    tree->Branch("PUweight", &PUweight, "PUweight/D");
  }

  /// MET

  // 4-vector of MET
  if(METSrc_.label() != ""){
    MET = new TClonesArray("TLorentzVector", 1);
    tree->Branch("MET", &MET, 32000, -1);
    MET->BypassStreamer();
  }

  /// muons

  // 4-vector of muons
  if(MuonSrc_.label() != ""){
    muons = new TClonesArray("TLorentzVector", 5);
    tree->Branch("muons", &muons, 32000, -1);
    muons->BypassStreamer();
  }

  /// electrons

  // 4-vector of electrons
  if(ElectronSrc_.label() != ""){
    electrons = new TClonesArray("TLorentzVector", 5);
    tree->Branch("electrons", &electrons, 32000, -1);
    electrons->BypassStreamer();
  }

  /// jets

  // 4-vectors of jets
  if(JetSrc_.label() != ""){
    jets = new TClonesArray("TLorentzVector", kMAX);
    tree->Branch("jets", &jets, 32000, -1);
    jets->BypassStreamer();

    genJets = new TClonesArray("TLorentzVector", kMAX);
    tree->Branch("genJets", &genJets, 32000, -1);
    genJets->BypassStreamer();

    genPartons = new TClonesArray("TLorentzVector", kMAX);
    tree->Branch("genPartons", &genPartons, 32000, -1);
    genPartons->BypassStreamer();

    // number of jets in events
    Njet = -1;
    tree->Branch("Njet", &Njet, "Njet/I");

    // b-tag discriminators of jets
    bTag_TCHE        = new float[kMAX];
    bTag_TCHP        = new float[kMAX];
    bTag_SSVHE       = new float[kMAX];
    bTag_SSVHP       = new float[kMAX];
    bTag_CSV         = new float[kMAX];
    bTag_CSVMVA      = new float[kMAX];
    bTag_TCHE_SF     = new float[kMAX];
    bTag_TCHP_SF     = new float[kMAX];
    bTag_SSVHE_SF    = new float[kMAX];
    bTag_SSVHP_SF    = new float[kMAX];
    bTag_CSV_SF      = new float[kMAX];
    bTag_TCHE_SF_Un  = new float[kMAX];
    bTag_TCHP_SF_Un  = new float[kMAX];
    bTag_SSVHE_SF_Un = new float[kMAX];
    bTag_SSVHP_SF_Un = new float[kMAX];
    bTag_CSV_SF_Un   = new float[kMAX];
    mTag_TCHE_SF     = new float[kMAX];
    mTag_TCHP_SF     = new float[kMAX];
    mTag_SSVHE_SF    = new float[kMAX];
    mTag_SSVHP_SF    = new float[kMAX];
    mTag_CSV_SF      = new float[kMAX];
    mTag_TCHE_SF_Un  = new float[kMAX];
    mTag_TCHP_SF_Un  = new float[kMAX];
    mTag_SSVHE_SF_Un = new float[kMAX];
    mTag_SSVHP_SF_Un = new float[kMAX];
    mTag_CSV_SF_Un   = new float[kMAX];
    
    // additional jet variables
    charge           = new float[kMAX];
    fChHad           = new float[kMAX];
    fNeHad           = new float[kMAX];
    fChEm            = new float[kMAX];
    fNeEm            = new float[kMAX];
    //fElec            = new float[kMAX];
    //fPhot            = new float[kMAX];
    fMuon            = new float[kMAX];
    jetConst         = new short[kMAX];
    chargeMulti      = new short[kMAX];
    pdgId            = new short[kMAX];
    partonFlavour    = new short[kMAX];

    gluonTag         = new float[kMAX];
    
    EtSin2Theta      = new float[kMAX];
    theta            = new float[kMAX];
    sinTheta         = new float[kMAX];
    EtStar           = new float[kMAX];
    thetaStar        = new float[kMAX];
    sinThetaStar     = new float[kMAX];
    L7PartonCorrection = new double[kMAX];

    for(unsigned short i = 0; i < kMAX; ++i) {
      bTag_TCHE_SF     [i] = -100.;
      bTag_TCHP_SF     [i] = -100.;
      bTag_SSVHE_SF    [i] = -100.;
      bTag_SSVHP_SF    [i] = -100.;
      bTag_CSV_SF      [i] = -100.;
      bTag_TCHE_SF_Un  [i] = -100.;
      bTag_TCHP_SF_Un  [i] = -100.;
      bTag_SSVHE_SF_Un [i] = -100.;
      bTag_SSVHP_SF_Un [i] = -100.;
      bTag_CSV_SF_Un   [i] = -100.;
      mTag_TCHE_SF     [i] = -100.;
      mTag_TCHP_SF     [i] = -100.;
      mTag_SSVHE_SF    [i] = -100.;
      mTag_SSVHP_SF    [i] = -100.;
      mTag_CSV_SF      [i] = -100.;
      mTag_TCHE_SF_Un  [i] = -100.;
      mTag_TCHP_SF_Un  [i] = -100.;
      mTag_SSVHE_SF_Un [i] = -100.;
      mTag_SSVHP_SF_Un [i] = -100.;
      mTag_CSV_SF_Un   [i] = -100.;
      
      bTag_TCHE        [i] = -100.;
      bTag_TCHP        [i] = -100.;
      bTag_SSVHE       [i] = -100.;
      bTag_SSVHP       [i] = -100.;
      bTag_CSV         [i] = -100.;
      bTag_CSVMVA      [i] = -100.;
      charge           [i] = -100.;
      fChHad           [i] =   -2.;
      fNeHad           [i] =   -2.;
      fChEm            [i] =   -2.;
      fNeEm            [i] =   -2.;
      //fElec            [i] =   -2.;
      //fPhot            [i] =   -2.;
      fMuon            [i] =   -2.;
      jetConst         [i] =   -2 ;
      chargeMulti      [i] =   -2 ;
      pdgId            [i] =    0 ;
      partonFlavour    [i] =    0 ;
      
      gluonTag         [i] = -999.;

      EtSin2Theta      [i] = -1.;
      theta            [i] = -100.;
      sinTheta         [i] = -100 ;
      EtStar           [i] = -1.;
      thetaStar        [i] = -100.;
      sinThetaStar     [i] = -100 ;
      L7PartonCorrection[i] = -100.;
    }
    //char buffer[7];
    //sprintf(buffer, "[%i]/F", kBTagMAX);
    //std::cout << (std::string("bTag_TCHE[Njet]") + std::string(buffer)).c_str() << std::endl;
    tree->Branch("bTag_TCHE"       , bTag_TCHE       , "bTag_TCHE[Njet]"       );
    tree->Branch("bTag_TCHP"       , bTag_TCHP       , "bTag_TCHP[Njet]"       );
    tree->Branch("bTag_SSVHE"      , bTag_SSVHE      , "bTag_SSVHE[Njet]"      );
    tree->Branch("bTag_SSVHP"      , bTag_SSVHP      , "bTag_SSVHP[Njet]"      );
    tree->Branch("bTag_CSV"        , bTag_CSV        , "bTag_CSV[Njet]/F"      );
    tree->Branch("bTag_CSVMVA"     , bTag_CSVMVA     , "bTag_CSVMVA[Njet]/F"   );
    tree->Branch("bTag_TCHE_SF"    , bTag_TCHE_SF    , "bTag_TCHE_SF[Njet]"    );
    tree->Branch("bTag_TCHP_SF"    , bTag_TCHP_SF    , "bTag_TCHP_SF[Njet]"    );
    tree->Branch("bTag_SSVHE_SF"   , bTag_SSVHE_SF   , "bTag_SSVHE_SF[Njet]"   );
    tree->Branch("bTag_SSVHP_SF"   , bTag_SSVHP_SF   , "bTag_SSVHP_SF[Njet]"   );
    tree->Branch("bTag_CSV_SF"     , bTag_CSV_SF     , "bTag_CSV_SF[Njet]"     );
    tree->Branch("bTag_TCHE_SF_Un" , bTag_TCHE_SF_Un , "bTag_TCHE_SF_Un[Njet]" );
    tree->Branch("bTag_TCHP_SF_Un" , bTag_TCHP_SF_Un , "bTag_TCHP_SF_Un[Njet]" );
    tree->Branch("bTag_SSVHE_SF_Un", bTag_SSVHE_SF_Un, "bTag_SSVHE_SF_Un[Njet]");
    tree->Branch("bTag_SSVHP_SF_Un", bTag_SSVHP_SF_Un, "bTag_SSVHP_SF_Un[Njet]");
    tree->Branch("bTag_CSV_SF_Un"  , bTag_CSV_SF_Un  , "bTag_CSV_SF_Un[Njet]"  );
    tree->Branch("mTag_TCHE_SF"    , mTag_TCHE_SF    , "mTag_TCHE_SF[Njet]"    );
    tree->Branch("mTag_TCHP_SF"    , mTag_TCHP_SF    , "mTag_TCHP_SF[Njet]"    );
    tree->Branch("mTag_SSVHE_SF"   , mTag_SSVHE_SF   , "mTag_SSVHE_SF[Njet]"   );
    tree->Branch("mTag_SSVHP_SF"   , mTag_SSVHP_SF   , "mTag_SSVHP_SF[Njet]"   );
    tree->Branch("mTag_CSV_SF"     , mTag_CSV_SF     , "mTag_CSV_SF[Njet]"     );
    tree->Branch("mTag_TCHE_SF_Un" , mTag_TCHE_SF_Un , "mTag_TCHE_SF_Un[Njet]" );
    tree->Branch("mTag_TCHP_SF_Un" , mTag_TCHP_SF_Un , "mTag_TCHP_SF_Un[Njet]" );
    tree->Branch("mTag_SSVHE_SF_Un", mTag_SSVHE_SF_Un, "mTag_SSVHE_SF_Un[Njet]");
    tree->Branch("mTag_SSVHP_SF_Un", mTag_SSVHP_SF_Un, "mTag_SSVHP_SF_Un[Njet]");
    tree->Branch("mTag_CSV_SF_Un"  , mTag_CSV_SF_Un  , "mTag_CSV_SF_Un[Njet]"  );
    tree->Branch("charge"          , charge          , "charge[Njet]/F"        );
    tree->Branch("fChHad"          , fChHad          , "fChHad[Njet]/F"        );
    tree->Branch("fNeHad"          , fNeHad          , "fNeHad[Njet]/F"        );
    tree->Branch("fChEm"           , fChEm           , "fChEm[Njet]/F"         );
    tree->Branch("fNeEm"           , fNeEm           , "fNeEm[Njet]/F"         );
    //tree->Branch("fElec"           , fElec           , "fElec[Njet]/F"         );
    //tree->Branch("fPhot"           , fPhot           , "fPhot[Njet]/F"         );
    tree->Branch("fMuon"           , fMuon           , "fMuon[Njet]/F"         );
    tree->Branch("jetConst"        , jetConst        , "jetConst[Njet]/S"      );
    tree->Branch("chargeMulti"     , chargeMulti     , "chargeMulti[Njet]/S"   );
    tree->Branch("pdgId"           , pdgId           , "pdgId[Njet]/S"         );
    tree->Branch("partonFlavour"   , partonFlavour   , "partonFlavour[Njet]/S" );
    tree->Branch("gluonTag"        , gluonTag        , "gluonTag[Njet]/F"   );
    tree->Branch("EtSin2Theta"     , EtSin2Theta     , "EtSin2Theta[Njet]/F"   );
    tree->Branch("theta"           , theta           , "theta[Njet]/F"         );
    tree->Branch("sinTheta"        , sinTheta        , "sinTheta[Njet]/F"      );
    tree->Branch("EtStar"          , EtStar          , "EtStar[Njet]/F"        );
    tree->Branch("thetaStar"       , thetaStar       , "thetaStar[Njet]/F"     );
    tree->Branch("sinThetaStar"    , sinThetaStar    , "sinThetaStar[Njet]/F"  );
    tree->Branch("L7PartonCorrection", L7PartonCorrection, "L7PartonCorrection[Njet]/D");

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
    measureMap["MUEFF"]=PerformanceResult::MUEFF;
    measureMap["MUERR"]=PerformanceResult::MUERR;
    measureMap["MUFAKE"]=PerformanceResult::MUFAKE; 
    measureMap["MUEFAKE"]=PerformanceResult::MUEFAKE;
    
    // event variables
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
  }

  /// kinFit properties

  if(FitSrc_.label() != ""){
    // probability and chi2 of kinematic fit
    prob    = -1.;
    chi2    = -1.;
    topMass = -1.;
    ttMass  = -1.;
    comboTypeID = -99;
    comboTypeValue = -99;
    tree->Branch("prob"       , &prob          , "prob/D"       );
    tree->Branch("chi2"       , &chi2          , "chi2/D"       );
    tree->Branch("topMass"    , &topMass       , "topMass/D"    );
    tree->Branch("ttMass"     , &ttMass        , "ttMass/D"     );
    tree->Branch("comboTypeID", &comboTypeID   , "comboTypeID/S");
    tree->Branch("comboType"  , &comboTypeValue, "comboType/S"  );

    // all masses, probs etc. needed fo mass measurment
    nCombos      = 0;
    probs        = new double[kMAXCombo];
    chi2s        = new double[kMAXCombo];
    topMasses    = new double[kMAXCombo];
    w1Mass       = new double[kMAXCombo];
    w2Mass       = new double[kMAXCombo];
    comboTypeIDs = new short [kMAXCombo];
    comboTypes   = new short [kMAXCombo];

    for(unsigned int i = 0; i < kMAXCombo; ++i) {
      probs[i]        = -1.;
      chi2s[i]        = -1.;
      topMasses[i]    = -1.;
      w1Mass[i]       = -1.; 
      w2Mass[i]       = -1.;
      comboTypeIDs[i] = -99;
      comboTypes[i]   = -99;
    }
    tree->Branch("nCombos"     , &nCombos     , "nCombos/i"              );
    tree->Branch("probs"       ,  probs       , "probs[nCombos]/D"       );
    tree->Branch("chi2s"       ,  chi2s       , "chi2s[nCombos]/D"       );
    tree->Branch("topMasses"   ,  topMasses   , "topMasses[nCombos]/D"   );
    tree->Branch("w1Mass"      ,  w1Mass      , "w1Mass[nCombos]/D"      );
    tree->Branch("w2Mass"      ,  w2Mass      , "w2Mass[nCombos]/D"      );
    tree->Branch("comboTypeIDs",  comboTypeIDs, "comboTypeIDs[nCombos]/S");
    tree->Branch("comboTypes"  ,  comboTypes  , "comboTypes[nCombos]/S"  );

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

    dRbb = -100;
    tree->Branch("dRbb", &dRbb, "dRbb/F");

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
  }

  // discriminator of mva method
  if(MultiJetMVADiscSrc_.label() != ""){
    multiJetMVADisc = -10.;
    tree->Branch("multiJetMVADisc", &multiJetMVADisc, "multiJetMVADisc/D");
  }
  
  // number of pile up interactions
  if(PUWeightSrc_.label() != ""){
    nPU        = -1;
    nPUnext    = -1;
    nPUprev    = -1;
    nPUTru     = -1;
    nPUnextTru = -1;
    nPUprevTru = -1;
    tree->Branch("nPU"    , &nPU    , "nPU/S"    );
    tree->Branch("nPUnext", &nPUnext, "nPUnext/S");
    tree->Branch("nPUprev", &nPUprev, "nPUprev/S");
    tree->Branch("nPUTru"    , &nPUTru    , "nPUTru/S"    );
    tree->Branch("nPUnextTru", &nPUnextTru, "nPUnextTru/S");
    tree->Branch("nPUprevTru", &nPUprevTru, "nPUprevTru/S");
  }

  // number of vertices
  if(VertexSrc_.label() != ""){
    nVertex = -1;
    tree->Branch("nVertex", &nVertex, "nVertex/S");
  }

  /// genEvent information

  ptHat = -1.;
  tree->Branch("ptHat", &ptHat, "ptHat/D");

  /// infos for PDF uncertainty

  id1 = -100;
  id2 = -100;
  Q   = -1.;
  x1  = -1.;
  x2  = -1.;

  // pdf information not saved to tree if not needed
  if(!DoPDFUncertainty_) return;

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
  
  edm::Handle<edm::View< pat::Muon > > muons_h;
  event.getByLabel(MuonSrc_, muons_h);
  
  edm::Handle<edm::View< pat::Electron > > electrons_h;
  event.getByLabel(ElectronSrc_, electrons_h);
  
  edm::Handle<edm::View< pat::Jet > > jets_h;
  event.getByLabel(JetSrc_, jets_h);
  
  //edm::Handle<edm::ValueMap<float> >  gluonTagsHandle;
  //event.getByLabel(GluonTagSrc_, gluonTagsHandle);
  std::string gluonTagName = GluonTagSrc_.encode();

  //edm::Handle<edm::View< reco::GenJet > > genJets_h;
  //event.getByLabel(GenJetSrc_, genJets_h);
  
  //edm::Handle<edm::View< reco::GenParticle > > genPartons_h;
  //event.getByLabel(GenPartonSrc_, genPartons_h);
  
  edm::Handle<TtFullHadronicEvent> fullHadEvent_h;
  event.getByLabel(FitSrc_, fullHadEvent_h);

  edm::Handle<TtFullHadronicEvent> fullHadEvent2_h;
  event.getByLabel(GenMatch2Src_, fullHadEvent2_h);

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
  if(muons_h.isValid()){
    unsigned short i = 0;
    muons->Clear();
    for(edm::View< pat::Muon >::const_iterator muon = muons_h->begin(); muon != muons_h->end(); ++muon, ++i){
      new((*muons)[i]) TLorentzVector(muon->px(), muon->py(), muon->pz(), muon->energy());
    }
  }
  if(electrons_h.isValid()){
    unsigned short i = 0;
    electrons->Clear();
    for(edm::View< pat::Electron >::const_iterator elec = electrons_h->begin(); elec != electrons_h->end(); ++elec, ++i){
      new((*electrons)[i]) TLorentzVector(elec->px(), elec->py(), elec->pz(), elec->energy());
    }
  }

  if(jets_h.isValid()){
    Njet = (int)jets_h->size();

    std::vector<pat::Jet> jets_v;

    unsigned short i = 0;
    jets->Clear();
    genJets->Clear();
    genPartons->Clear();
    for(edm::View< pat::Jet >::const_iterator jet = jets_h->begin(); jet != jets_h->end(); ++jet, ++i){
      
      //std::cout << jet->jecFactor("Uncorrected") << jet->jecFactor("L1FastJet") << " " << jet->jecFactor("L2Relative") << " " << jet->jecFactor("L3Absolute") << std::endl;
      //std::cout << jet->jecFactor(0) << " " << jet->jecFactor(1) << " " << jet->jecFactor(2) << " " << jet->jecFactor(3) << std::endl;
      jets_v.push_back(*jet);
      new((*jets)[i]) TLorentzVector(jet->px(), jet->py(), jet->pz(), jet->energy());
      if(jet->genJet()) new((*genJets)[i]) TLorentzVector(jet->genJet()->px(), jet->genJet()->py(), jet->genJet()->pz(), jet->genJet()->energy());
      else              new((*genJets)[i]) TLorentzVector();
      if(jet->genParticle()) new((*genPartons)[i]) TLorentzVector(jet->genParticle()->px(), jet->genParticle()->py(), jet->genParticle()->pz(), jet->genParticle()->energy());
      else                   new((*genPartons)[i]) TLorentzVector();
      bTag_TCHE    [i] = jet->bDiscriminator("trackCountingHighEffBJetTags");
      bTag_TCHP    [i] = jet->bDiscriminator("trackCountingHighPurBJetTags");
      bTag_SSVHE   [i] = jet->bDiscriminator("simpleSecondaryVertexHighEffBJetTags");
      bTag_SSVHP   [i] = jet->bDiscriminator("simpleSecondaryVertexHighPurBJetTags");
      bTag_CSV     [i] = jet->bDiscriminator("combinedSecondaryVertexBJetTags");
      bTag_CSVMVA  [i] = jet->bDiscriminator("combinedSecondaryVertexMVABJetTags");
      charge       [i] = jet->jetCharge();
      if(!checkedIsPFJet){
	isPFJet = jet->isPFJet();
	checkedIsPFJet = true;
      }
      if(isPFJet){
	fChHad       [i] = jet->chargedHadronEnergyFraction();
	fNeHad       [i] = jet->neutralHadronEnergyFraction();
	fChEm        [i] = jet->chargedEmEnergyFraction();
	fNeEm        [i] = jet->neutralEmEnergyFraction();
	//fElec        [i] = jet->electronEnergyFraction();
	//fPhot        [i] = jet->photonEnergyFraction();
	fMuon        [i] = jet->muonEnergyFraction();
	jetConst     [i] = jet->nConstituents();
	chargeMulti  [i] = jet->chargedMultiplicity();
	pdgId        [i] = (jet->genParticle()) ? jet->genParticle()->pdgId() : 0;
	partonFlavour[i] = jet->partonFlavour();
      }
      if(!checkedHasL7PartonCor){
	const std::vector<std::string> jecLevels = jet->availableJECLevels();
	for(std::vector<std::string>::const_iterator jec = jecLevels.begin(); jec != jecLevels.end(); ++jec){
	  if(*jec == "L7Parton") hasL7PartonCor = true;
	}
	checkedHasL7PartonCor = true;
      }

      L7PartonCorrection[i] = hasL7PartonCor ? jet->jecFactor("L7Parton", "uds") : 1.0;

      //if (gluonTagsHandle.isValid()){
      //	edm::RefToBase<pat::Jet> jetRef(edm::Ref<edm::View<pat::Jet> >(jets_h,i));
      //	gluonTag[i] = (*gluonTagsHandle)[jetRef];
      //}
      //else
      //	gluonTag[i] = -999.;
      
      if(!checkedQGTag){
	if(jet->hasUserFloat(gluonTagName)) hasQGTag = true;
	checkedHasL7PartonCor = true;
      }
      if(hasQGTag) gluonTag[i] = jet->userFloat(gluonTagName);
      else gluonTag[i] = -999.;

      for(size_t ibTag = 0; ibTag < bTagName_.size(); ++ibTag){

	iSetup.get<BTagPerformanceRecord>().get(bTagName_[ibTag],bTagPerf_h);
	const BtagPerformance & bTagPerf = *(bTagPerf_h.product());

	BinningPointByMap measurePoint;
	measurePoint.insert(BinningVariables::JetEt, jet->et());
	measurePoint.insert(BinningVariables::JetAbsEta, std::abs(jet->eta()));

	if(measureMap[bTagVal_[ibTag]] == PerformanceResult::BTAGBEFFCORR){
	  if(bTagName_[ibTag].find("TCHEM")!=std::string::npos)
	    bTag_TCHE_SF [i] = bTagPerf.getResult(measureMap[bTagVal_[ibTag]], measurePoint);
	  else if(bTagName_[ibTag].find("TCHPT")!=std::string::npos)
	    bTag_TCHP_SF [i] = bTagPerf.getResult(measureMap[bTagVal_[ibTag]], measurePoint);
	  else if(bTagName_[ibTag].find("SSVHEM")!=std::string::npos)
	    bTag_SSVHE_SF[i] = bTagPerf.getResult(measureMap[bTagVal_[ibTag]], measurePoint);
	  else if(bTagName_[ibTag].find("SSVHPT")!=std::string::npos)
	    bTag_SSVHP_SF[i] = bTagPerf.getResult(measureMap[bTagVal_[ibTag]], measurePoint);
	  else if(bTagName_[ibTag].find("CSVT")!=std::string::npos)
	    bTag_CSV_SF  [i] = bTagPerf.getResult(measureMap[bTagVal_[ibTag]], measurePoint);
	}
	else if(measureMap[bTagVal_[ibTag]] == PerformanceResult::BTAGLEFFCORR){
	  if(bTagName_[ibTag].find("TCHEM")!=std::string::npos)
	    mTag_TCHE_SF [i] = bTagPerf.getResult(measureMap[bTagVal_[ibTag]], measurePoint);
	  else if(bTagName_[ibTag].find("TCHPT")!=std::string::npos)
	    mTag_TCHP_SF [i] = bTagPerf.getResult(measureMap[bTagVal_[ibTag]], measurePoint);
	  else if(bTagName_[ibTag].find("SSVHEM")!=std::string::npos)
	    mTag_SSVHE_SF[i] = bTagPerf.getResult(measureMap[bTagVal_[ibTag]], measurePoint);
	  else if(bTagName_[ibTag].find("SSVHPT")!=std::string::npos)
	    mTag_SSVHP_SF[i] = bTagPerf.getResult(measureMap[bTagVal_[ibTag]], measurePoint);
	  else if(bTagName_[ibTag].find("CSVT")!=std::string::npos)
	    mTag_CSV_SF  [i] = bTagPerf.getResult(measureMap[bTagVal_[ibTag]], measurePoint);
	}
	else if(measureMap[bTagVal_[ibTag]] == PerformanceResult::BTAGBERRCORR){
	  if(bTagName_[ibTag].find("TCHEM")!=std::string::npos)
	    bTag_TCHE_SF_Un [i] = bTagPerf.getResult(measureMap[bTagVal_[ibTag]], measurePoint);
	  else if(bTagName_[ibTag].find("TCHPT")!=std::string::npos)
	    bTag_TCHP_SF_Un [i] = bTagPerf.getResult(measureMap[bTagVal_[ibTag]], measurePoint);
	  else if(bTagName_[ibTag].find("SSVHEM")!=std::string::npos)
	    bTag_SSVHE_SF_Un[i] = bTagPerf.getResult(measureMap[bTagVal_[ibTag]], measurePoint);
	  else if(bTagName_[ibTag].find("SSVHPT")!=std::string::npos)
	    bTag_SSVHP_SF_Un[i] = bTagPerf.getResult(measureMap[bTagVal_[ibTag]], measurePoint);
	  else if(bTagName_[ibTag].find("CSVT")!=std::string::npos)
	    bTag_CSV_SF_Un  [i] = bTagPerf.getResult(measureMap[bTagVal_[ibTag]], measurePoint);
	}
	else if(measureMap[bTagVal_[ibTag]] == PerformanceResult::BTAGLERRCORR){
	  if(bTagName_[ibTag].find("TCHEM")!=std::string::npos)
	    mTag_TCHE_SF_Un [i] = bTagPerf.getResult(measureMap[bTagVal_[ibTag]], measurePoint);
	  else if(bTagName_[ibTag].find("TCHPT")!=std::string::npos)
	    mTag_TCHP_SF_Un [i] = bTagPerf.getResult(measureMap[bTagVal_[ibTag]], measurePoint);
	  else if(bTagName_[ibTag].find("SSVHEM")!=std::string::npos)
	    mTag_SSVHE_SF_Un[i] = bTagPerf.getResult(measureMap[bTagVal_[ibTag]], measurePoint);
	  else if(bTagName_[ibTag].find("SSVHPT")!=std::string::npos)
	    mTag_SSVHP_SF_Un[i] = bTagPerf.getResult(measureMap[bTagVal_[ibTag]], measurePoint);
	  else if(bTagName_[ibTag].find("CSVT")!=std::string::npos)
	    mTag_CSV_SF_Un  [i] = bTagPerf.getResult(measureMap[bTagVal_[ibTag]], measurePoint);
	}
      }
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
      theta[i]        = mvaVariables.theta      (i+1);	    
      sinTheta[i]     = mvaVariables.sinTheta   (i+1);   
      EtStar[i]       = mvaVariables.EtSin2Theta(i+1,true);
      thetaStar[i]    = mvaVariables.theta      (i+1,true);
      sinThetaStar[i] = mvaVariables.sinTheta   (i+1,true);
    }
    EtSin2Theta3jet  = mvaVariables.EtSin2Theta3jet();
    theta3jet        = mvaVariables.theta3jet      ();      
    sinTheta3jet     = mvaVariables.sinTheta3jet   ();   
    EtStar3jet       = mvaVariables.EtSin2Theta3jet(true);
    thetaStar3jet    = mvaVariables.theta3jet      (true);
    sinThetaStar3jet = mvaVariables.sinTheta3jet   (true);
    
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
  eventType = -10;
  prob      = -1.;
  chi2      = -1.;
  topMass   = -1.;
  ttMass    = -1.;
  comboTypeID = -99;
  comboTypeValue = -99;

  nCombos = 0;
  for(unsigned int i = 0; i < kMAXCombo; ++i) {
    probs       [i] = -1.;
    chi2s       [i] = -1.;
    topMasses   [i] = -1.;
    w1Mass      [i] = -1.; 
    w2Mass      [i] = -1.;
    comboTypeIDs[i] = -99;
    comboTypes  [i] = -99;
  }

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

  dRbb = -100.;

  if(FitSrc_.label() != ""){
    for(short i = 0; i < 6; ++i){
      fitAssigns[i] = -1;
    }
    fitVecs->Clear();
  }

  if( fullHadEvent_h.isValid() ){
    // identify event by the following number coding:
    // -10 : undefined
    //  -1 : non ttbar MC
    //   0 : DATA
    //   1 : fully hadronic        ttbar MC
    //   2 : semileptonic unknown  ttbar MC
    //  21 : semileptonic electron ttbar MC
    //  22 : semileptonic muon     ttbar MC
    //  23 : semileptonic tau      ttbar MC
    //   3 : dileptonic unknown    ttbar MC
    // 311 : dileptonic e   e      ttbar MC
    // 312 : dileptonic e   mu     ttbar MC
    // 313 : dileptonic e   tau    ttbar MC
    // 322 : dileptonic mu  mu     ttbar MC
    // 323 : dileptonic mu  tau    ttbar MC
    // 333 : dileptonic tau tau    ttbar MC
    if(      !fullHadEvent_h->genEvent().isAvailable()     ) eventType =  0;
    else if( !fullHadEvent_h->genEvent()->isTtBar()        ) eventType = -1;
    else if(  fullHadEvent_h->genEvent()->isFullHadronic() ) eventType =  1;
    else if(  fullHadEvent_h->genEvent()->isSemiLeptonic() ) {
      switch( fullHadEvent_h->genEvent()->semiLeptonicChannel() ) {
      case WDecay::kElec : eventType = 21; break;
      case WDecay::kMuon : eventType = 22; break;
      case WDecay::kTau  : eventType = 23; break;
      default            : eventType =  2; break;
      }
    }
    else if( fullHadEvent_h->genEvent()->isFullLeptonic() ) {
      if     (  fullHadEvent_h->genEvent()->fullLeptonicChannel().first == WDecay::kElec && fullHadEvent_h->genEvent()->fullLeptonicChannel().second == WDecay::kElec  ) eventType = 311;
      else if( (fullHadEvent_h->genEvent()->fullLeptonicChannel().first == WDecay::kElec && fullHadEvent_h->genEvent()->fullLeptonicChannel().second == WDecay::kMuon) ||
	       (fullHadEvent_h->genEvent()->fullLeptonicChannel().first == WDecay::kMuon && fullHadEvent_h->genEvent()->fullLeptonicChannel().second == WDecay::kElec) ) eventType = 312;
      else if( (fullHadEvent_h->genEvent()->fullLeptonicChannel().first == WDecay::kElec && fullHadEvent_h->genEvent()->fullLeptonicChannel().second == WDecay::kTau ) ||
	       (fullHadEvent_h->genEvent()->fullLeptonicChannel().first == WDecay::kTau  && fullHadEvent_h->genEvent()->fullLeptonicChannel().second == WDecay::kElec) ) eventType = 313;
      else if(  fullHadEvent_h->genEvent()->fullLeptonicChannel().first == WDecay::kMuon && fullHadEvent_h->genEvent()->fullLeptonicChannel().second == WDecay::kMuon  ) eventType = 322;
      else if( (fullHadEvent_h->genEvent()->fullLeptonicChannel().first == WDecay::kMuon && fullHadEvent_h->genEvent()->fullLeptonicChannel().second == WDecay::kTau ) ||
	       (fullHadEvent_h->genEvent()->fullLeptonicChannel().first == WDecay::kTau  && fullHadEvent_h->genEvent()->fullLeptonicChannel().second == WDecay::kMuon) ) eventType = 323;
      else if(  fullHadEvent_h->genEvent()->fullLeptonicChannel().first == WDecay::kTau  && fullHadEvent_h->genEvent()->fullLeptonicChannel().second == WDecay::kTau   ) eventType = 333;
      else eventType = 3;
    }

    if( fullHadEvent_h->isHypoValid("kKinFit") ){
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

      bool genMatch1Valid = fullHadEvent_h->isHypoValid("kGenMatch");
      bool genMatch2Valid = (fullHadEvent2_h.isValid() && fullHadEvent2_h->isHypoValid("kGenMatch"));

      if( genMatch1Valid ){
	comboTypeID    = comboTypeIDCalculator(fullHadEvent_h);
	comboTypeValue = comboType(comboTypeID);
      }
      else{
	if( genMatch2Valid ){
	  comboTypeID    = -55;
	  comboTypeValue =   5;
	}
	else{
	  comboTypeID    = -66;
	  comboTypeValue =   6;
	}
      }

      ptAsy    = (fullHadEvent_h->b   ("kKinFit")->pt()-fullHadEvent_h->wPlus ("kKinFit")->pt())/(fullHadEvent_h->b   ("kKinFit")->pt()+fullHadEvent_h->wPlus ("kKinFit")->pt());
      ptAsyBar = (fullHadEvent_h->bBar("kKinFit")->pt()-fullHadEvent_h->wMinus("kKinFit")->pt())/(fullHadEvent_h->bBar("kKinFit")->pt()+fullHadEvent_h->wMinus("kKinFit")->pt());

      // calculate angles from the 4 momentum vectors
      TopAngles angles = TopAngles(fullHadEvent_h->b   ("kKinFit")->p4(), fullHadEvent_h->lightQ("kKinFit")->p4(), fullHadEvent_h->lightQBar("kKinFit")->p4(),
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

      dRbb = deltaR( fullHadEvent_h->b   ("kKinFit")->eta(), fullHadEvent_h->b   ("kKinFit")->phi(),
		     fullHadEvent_h->bBar("kKinFit")->eta(), fullHadEvent_h->bBar("kKinFit")->phi());

      nCombos = fullHadEvent_h->numberOfAvailableHypos("kKinFit");
      for(unsigned int i = 0; i < nCombos; ++i){
	if(i >= kMAXCombo){
	  std::cout << "Maximum number of combinations per event (" <<  kMAXCombo << ") reached, stopping and continuing with next event!" << std::endl;
	  break;
	}
	probs       [i] = fullHadEvent_h->fitProb(i);
	chi2s       [i] = fullHadEvent_h->fitChi2(i);
	topMasses   [i] = fullHadEvent_h->top("kKinFit",i)->mass();
	int lQID    = fullHadEvent_h->jetLeptonCombination("kKinFit",i)[TtFullHadEvtPartons::LightQ];
	int lQBarID = fullHadEvent_h->jetLeptonCombination("kKinFit",i)[TtFullHadEvtPartons::LightQBar];
	int lPID    = fullHadEvent_h->jetLeptonCombination("kKinFit",i)[TtFullHadEvtPartons::LightP];
	int lPBarID = fullHadEvent_h->jetLeptonCombination("kKinFit",i)[TtFullHadEvtPartons::LightPBar];
	TLorentzVector lQ    = ((TLorentzVector*)jets->At(lQID   ))->operator*(L7PartonCorrection[lQID]);
	TLorentzVector lQBar = ((TLorentzVector*)jets->At(lQBarID))->operator*(L7PartonCorrection[lQBarID]);
	TLorentzVector lP    = ((TLorentzVector*)jets->At(lPID   ))->operator*(L7PartonCorrection[lPID]);
	TLorentzVector lPBar = ((TLorentzVector*)jets->At(lPBarID))->operator*(L7PartonCorrection[lPBarID]);
	w1Mass      [i] = (lQ + lQBar).M();
	w2Mass      [i] = (lP + lPBar).M();
	// will be 80.4 by definition
	//w1Mass      [i] = fullHadEvent_h->wPlus ("kKinFit",i)->mass();
	//w2Mass      [i] = fullHadEvent_h->wMinus("kKinFit",i)->mass();
	if(genMatch1Valid){
	  comboTypeIDs[i] = comboTypeIDCalculator(fullHadEvent_h,i);
	  comboTypes  [i] = comboType(comboTypeIDs[i] );
	}
	else{
	  if( genMatch2Valid ){
	    comboTypeID    = -55;
	    comboTypeValue =   5;
	  }
	  else{
	    comboTypeIDs[i] = -66;
	    comboTypes  [i] =   6;
	  }
	}
      }
    }
  }
  
  multiJetMVADisc = multiJetMVADisc_h.isValid() ? *multiJetMVADisc_h : -10.;

  nPU     = -1;
  nPUnext = -1;
  nPUprev = -1;

  if(PU_h.isValid()){
    for(edm::View<PileupSummaryInfo>::const_iterator iterPU = PU_h->begin(); iterPU != PU_h->end(); ++iterPU){  // vector size is 3
      if(iterPU->getBunchCrossing()==-1){ // -1: previous BX, 0: current BX,  1: next BX
	nPUprev    = iterPU->getPU_NumInteractions();
	nPUprevTru = iterPU->getTrueNumInteractions ();
      }
      else if(iterPU->getBunchCrossing()==0){ // -1: previous BX, 0: current BX,  1: next BX
	nPU    = iterPU->getPU_NumInteractions();
	nPUTru = iterPU->getTrueNumInteractions();
      }
      else if(iterPU->getBunchCrossing()==1){ // -1: previous BX, 0: current BX,  1: next BX
	nPUnext    = iterPU->getPU_NumInteractions();
	nPUnextTru = iterPU->getTrueNumInteractions();
      }
    }
  }

  nVertex = vertecies_h.isValid() ? vertecies_h->size() : -1;

  if(genEventInfo_h.isValid()){

    // save ptHat if available
    if(genEventInfo_h->hasBinningValues() && genEventInfo_h->binningValues().size() > 0)
      ptHat = genEventInfo_h->binningValues()[0];

    // get mc event weight, needed for MC@NLO
    if(MCweight_ == -1.)
      MCweight = genEventInfo_h->weight();
      
    if(DoPDFUncertainty_){

      // variables needed for PDF uncertainties
      Q   = genEventInfo_h->pdf()->scalePDF;
      id1 = genEventInfo_h->pdf()->id.first;
      id2 = genEventInfo_h->pdf()->id.second;
      x1  = genEventInfo_h->pdf()->x.first;
      x2  = genEventInfo_h->pdf()->x.second;

    }
  }

  tree->Fill();
}
/*
/// function to find types of jet-combinations in KinFits (1 right, 2 branches right, but inner-branche particles mixup, 3 inter-branch mixup, 4 missing jet)
int
FullHadTreeWriter::comboType(edm::Handle<TtFullHadronicEvent> fullHadEvent_h, unsigned int whichCombo)
{
  /// vector to store the jet indices
  std::vector<int> jetIndex(12);
  /// store position in jetIndex vector with corresponding particle name
  enum whichParticle{LQ, LQBar, B, BBar, LP, LPBar, LQ_Gen, LQBar_Gen, B_Gen, BBar_Gen, LP_Gen, LPBar_Gen};

  int lightQFit    = fullHadEvent_h->jetLeptonCombination("kKinFit",whichCombo)[TtFullHadEvtPartons::LightQ   ];
  int lightQBarFit = fullHadEvent_h->jetLeptonCombination("kKinFit",whichCombo)[TtFullHadEvtPartons::LightQBar];
  int bFit         = fullHadEvent_h->jetLeptonCombination("kKinFit",whichCombo)[TtFullHadEvtPartons::B        ];
  int bBarFit      = fullHadEvent_h->jetLeptonCombination("kKinFit",whichCombo)[TtFullHadEvtPartons::BBar     ];
  int lightPFit    = fullHadEvent_h->jetLeptonCombination("kKinFit",whichCombo)[TtFullHadEvtPartons::LightP   ];
  int lightPBarFit = fullHadEvent_h->jetLeptonCombination("kKinFit",whichCombo)[TtFullHadEvtPartons::LightPBar];

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
*/

short
FullHadTreeWriter::TESTHelper(int *jetIndexGenHelperPtr)
{
  int jetIndexFitHelper[6] = {1,2,3,4,5,6};
  int jetIndexGenHelper[6] = {jetIndexGenHelperPtr[0],jetIndexGenHelperPtr[1],jetIndexGenHelperPtr[2],jetIndexGenHelperPtr[3],jetIndexGenHelperPtr[4],jetIndexGenHelperPtr[5]};

  std::vector<int> jetIndexFit(jetIndexFitHelper, jetIndexFitHelper + sizeof(jetIndexFitHelper)/sizeof(int));
  std::vector<int> jetIndexGen(jetIndexGenHelper, jetIndexGenHelper + sizeof(jetIndexGenHelper)/sizeof(int));

  int comboTypeID = comboTypeAlgo(jetIndexFit, jetIndexGen);

  std::vector<int> jetIndexFitTest = comboTypeAlgoInverted(jetIndexGen, comboTypeID);

  std::cout << "TEST: ";
  for(unsigned int i = 0; i < jetIndexFitTest.size(); ++i){
    std::cout << jetIndexFitTest[i] << ",";
  }
  std::cout << std::endl;

  return comboTypeID;
}

void
FullHadTreeWriter::TEST()
{
  std::vector<short> correctTypeIDs;
  std::vector<short> innerBranchMixingTypeIDs;
  std::vector<short> crossBranchMixingTypeIDs;

  int jetIndexFitHelper[]  = {1,2,3,4,5,6};
  std::vector<int> jetIndexFit(jetIndexFitHelper, jetIndexFitHelper + sizeof(jetIndexFitHelper)/sizeof(int));

  int jetIndexGenHelper1[] = {1,2,3,4,5,6}; // 0
  correctTypeIDs.push_back(TESTHelper(jetIndexGenHelper1));

  int jetIndexGenHelper2[] = {1,3,2,4,5,6}; // 24
  correctTypeIDs.push_back(TESTHelper(jetIndexGenHelper2));

  int jetIndexGenHelper3[] = {1,2,3,4,6,5}; // 1
  correctTypeIDs.push_back(TESTHelper(jetIndexGenHelper3));

  int jetIndexGenHelper4[] = {1,3,2,4,6,5}; // 25
  correctTypeIDs.push_back(TESTHelper(jetIndexGenHelper4));

  int jetIndexGenHelper5[] = {4,5,6,1,2,3}; // 450
  correctTypeIDs.push_back(TESTHelper(jetIndexGenHelper5));

  int jetIndexGenHelper6[] = {4,6,5,1,2,3}; // 451
  correctTypeIDs.push_back(TESTHelper(jetIndexGenHelper6));

  int jetIndexGenHelper7[] = {4,5,6,1,3,2}; // 474
  correctTypeIDs.push_back(TESTHelper(jetIndexGenHelper7));

  int jetIndexGenHelper8[] = {4,6,5,1,3,2}; // 475
  correctTypeIDs.push_back(TESTHelper(jetIndexGenHelper8));

  int jetIndexGenHelper9[] = {1,2,3,5,4,6}; // 2
  innerBranchMixingTypeIDs.push_back(TESTHelper(jetIndexGenHelper9));

  int jetIndexGenHelper10[] = {1,2,3,6,4,5}; // 3
  innerBranchMixingTypeIDs.push_back(TESTHelper(jetIndexGenHelper10));

  int jetIndexGenHelper11[] = {1,2,3,5,6,4}; // 4
  innerBranchMixingTypeIDs.push_back(TESTHelper(jetIndexGenHelper11));

  int jetIndexGenHelper12[] = {1,2,3,6,5,4}; // 5
  innerBranchMixingTypeIDs.push_back(TESTHelper(jetIndexGenHelper12));

  int jetIndexGenHelper100[] = {1,2,4,3,5,6}; // 6
  crossBranchMixingTypeIDs.push_back(TESTHelper(jetIndexGenHelper100));

  int jetIndexGenHelper101[] = {1,2,4,3,6,5}; // 7
  crossBranchMixingTypeIDs.push_back(TESTHelper(jetIndexGenHelper101));

  int jetIndexGenHelper102[] = {1,2,4,5,3,6}; // 8
  crossBranchMixingTypeIDs.push_back(TESTHelper(jetIndexGenHelper102));

  int jetIndexGenHelper103[] = {1,2,6,3,4,5}; // 9
  crossBranchMixingTypeIDs.push_back(TESTHelper(jetIndexGenHelper103));

  int jetIndexGenHelper107[] = {1,2,4,6,3,5}; // 13
  crossBranchMixingTypeIDs.push_back(TESTHelper(jetIndexGenHelper107));

  for(int idx = 0; idx < 721; ++idx){
    std::vector<int> jetIndexGenTest1 = comboTypeAlgoInverted(jetIndexFit, idx);
    std::cout << "combo for " << idx << ": ";
    for(unsigned int i = 0; i < jetIndexGenTest1.size(); ++i){
      std::cout << jetIndexGenTest1[i] << ",";
    }
    std::cout << std::endl;
  }

  std::cout << "correct comboTypes: ";
  for(unsigned int i = 0; i < correctTypeIDs.size(); ++i){
    std::cout << correctTypeIDs[i] << ", ";
  }
  std::cout << std::endl;
  std::cout << "innerBranchMixing comboTypes: ";
  for(unsigned int i = 0; i < innerBranchMixingTypeIDs.size(); ++i){
    std::cout << innerBranchMixingTypeIDs[i] << ", ";
  }
  std::cout << std::endl;
  std::cout << "crossBranchMixing comboTypes: ";
  for(unsigned int i = 0; i < crossBranchMixingTypeIDs.size(); ++i){
    std::cout << crossBranchMixingTypeIDs[i] << ", ";
  }
  std::cout << std::endl;
}

/// function to find types of jet-combinations in KinFits (1 right, 2 one branche right, other branch inner-branch mixup, 3 both branches inner-branch mixup, 4 cross-branch mixup, -1 to -6 number of falsely picked jets)
short
FullHadTreeWriter::comboType(short comboTypeID)
{
  // falsely picked jets
  if(comboTypeID < 0)
    return comboTypeID;

  // correct permutations
  if(comboTypeID ==   0 || comboTypeID ==   1 || comboTypeID ==  24 || comboTypeID ==  25 || 
     comboTypeID == 450 || comboTypeID == 451 || comboTypeID == 474 || comboTypeID == 475)
    return 1;

  // one branch mixup
  if((comboTypeID >=   2 && comboTypeID <=   5) || (comboTypeID >=  26 && comboTypeID <=  29) || 
      comboTypeID == 120 || comboTypeID == 121  ||  comboTypeID == 144 || comboTypeID == 145  || 
      comboTypeID == 240 || comboTypeID == 241  ||  comboTypeID == 264 || comboTypeID == 265  || 
     (comboTypeID >= 452 && comboTypeID <= 455) || (comboTypeID >= 476 && comboTypeID <= 479) || 
      comboTypeID == 570 || comboTypeID == 571  ||  comboTypeID == 594 || comboTypeID == 595  || 
      comboTypeID == 690 || comboTypeID == 691  ||  comboTypeID == 714 || comboTypeID == 715)
    return 2;

  // both branches mixup
  if((comboTypeID >= 122 && comboTypeID <= 125) || (comboTypeID >= 146 && comboTypeID <= 149) || 
     (comboTypeID >= 242 && comboTypeID <= 245) || (comboTypeID >= 266 && comboTypeID <= 269) || 
     (comboTypeID >= 572 && comboTypeID <= 575) || (comboTypeID >= 596 && comboTypeID <= 599) || 
     (comboTypeID >= 692 && comboTypeID <= 695) || (comboTypeID >= 716 && comboTypeID <= 719))
    return 3;
     
  // mixup cross branches
  if((comboTypeID >=   6 && comboTypeID <=  23) || (comboTypeID >=  30 && comboTypeID <= 119) || 
     (comboTypeID >= 126 && comboTypeID <= 143) || (comboTypeID >= 150 && comboTypeID <= 239) || 
     (comboTypeID >= 246 && comboTypeID <= 263) || (comboTypeID >= 270 && comboTypeID <= 449) || 
     (comboTypeID >= 456 && comboTypeID <= 473) || (comboTypeID >= 480 && comboTypeID <= 569) || 
     (comboTypeID >= 576 && comboTypeID <= 593) || (comboTypeID >= 600 && comboTypeID <= 689) || 
     (comboTypeID >= 696 && comboTypeID <= 713) )
    return 4;

  return -37;
}

/// assign unique ID to every permutation type
short
FullHadTreeWriter::comboTypeIDCalculator(edm::Handle<TtFullHadronicEvent> fullHadEvent_h, unsigned int whichCombo)
{
  /// vector to store the jet indices
  std::vector<int> jetIndexFit;
  std::vector<int> jetIndexGen;

  int lightQFit    = fullHadEvent_h->jetLeptonCombination("kKinFit",whichCombo)[TtFullHadEvtPartons::LightQ   ];
  int lightQBarFit = fullHadEvent_h->jetLeptonCombination("kKinFit",whichCombo)[TtFullHadEvtPartons::LightQBar];
  int bFit         = fullHadEvent_h->jetLeptonCombination("kKinFit",whichCombo)[TtFullHadEvtPartons::B        ];
  int bBarFit      = fullHadEvent_h->jetLeptonCombination("kKinFit",whichCombo)[TtFullHadEvtPartons::BBar     ];
  int lightPFit    = fullHadEvent_h->jetLeptonCombination("kKinFit",whichCombo)[TtFullHadEvtPartons::LightP   ];
  int lightPBarFit = fullHadEvent_h->jetLeptonCombination("kKinFit",whichCombo)[TtFullHadEvtPartons::LightPBar];

  int lightQGen    = fullHadEvent_h->jetLeptonCombination("kGenMatch")[TtFullHadEvtPartons::LightQ   ];
  int lightQBarGen = fullHadEvent_h->jetLeptonCombination("kGenMatch")[TtFullHadEvtPartons::LightQBar];
  int bGen         = fullHadEvent_h->jetLeptonCombination("kGenMatch")[TtFullHadEvtPartons::B        ];
  int bBarGen      = fullHadEvent_h->jetLeptonCombination("kGenMatch")[TtFullHadEvtPartons::BBar     ];
  int lightPGen    = fullHadEvent_h->jetLeptonCombination("kGenMatch")[TtFullHadEvtPartons::LightP   ];
  int lightPBarGen = fullHadEvent_h->jetLeptonCombination("kGenMatch")[TtFullHadEvtPartons::LightPBar];

  jetIndexFit.push_back(bFit);
  jetIndexFit.push_back(lightQFit);
  jetIndexFit.push_back(lightQBarFit);
  jetIndexFit.push_back(bBarFit);
  jetIndexFit.push_back(lightPFit);
  jetIndexFit.push_back(lightPBarFit);

  jetIndexGen.push_back(bGen);
  jetIndexGen.push_back(lightQGen);
  jetIndexGen.push_back(lightQBarGen);
  jetIndexGen.push_back(bBarGen);
  jetIndexGen.push_back(lightPGen);
  jetIndexGen.push_back(lightPBarGen);

  //std::cout << "Fit: " << bFit << ", " << lightQFit << ", " << lightQBarFit << ", " << bBarFit << ", " << lightPFit << ", " << lightPBarFit << std::endl;
  //std::cout << "Gen: " << bGen << ", " << lightQGen << ", " << lightQBarGen << ", " << bBarGen << ", " << lightPGen << ", " << lightPBarGen << std::endl;

  return comboTypeAlgo(jetIndexFit, jetIndexGen);
}

short
FullHadTreeWriter::comboTypeAlgo(std::vector<int> jetIndexFit, std::vector<int> jetIndexGen)
{
  short result = 0;
  short wrongJets = 0;
  for(unsigned short iFit = 0; iFit < jetIndexFit.size(); ++iFit){
    short fact = TMath::Factorial(jetIndexFit.size()-iFit-1);
    //std::cout << "result = " << result;
    bool foundPair = false;
    for(unsigned short jGen = 0, jGenCount = 0; jGen < jetIndexGen.size(); ++jGen, ++jGenCount){
      if(jetIndexGen.at(jGen) == -37){
	--jGenCount;
	continue;
      }
      if(jetIndexFit.at(iFit) == jetIndexGen.at(jGen)){
	foundPair = true;
	result += fact*(jGenCount);
	//std::cout << " (" << iFit << "," << jGen << "," << jGenCount << ")";
	jetIndexGen[jGen] = -37;
      }
    }
    if(!foundPair){
      ++wrongJets;
    }
    //std::cout << " -> " << result << std::endl;
  }
  if(wrongJets){
    result = 0-wrongJets;
  }

  //std::cout << "result: " << result << std::endl;

  return result;
}

std::vector<int>
FullHadTreeWriter::comboTypeAlgoInverted(std::vector<int> jetIndexGen, short comboType)
{
  unsigned int lGen = jetIndexGen.size();
  if(comboType<0 || comboType>=TMath::Factorial(lGen)) return std::vector<int>(0);
  std::vector<int> result(lGen);
  for(unsigned short iGen = 0; iGen < lGen; ++iGen){
    int idx = lGen-iGen-1;
    short fact = TMath::Factorial(idx);
    short calc = comboType/fact;
    result[iGen] = jetIndexGen.at(calc);
    jetIndexGen.erase(jetIndexGen.begin()+calc);
    comboType -= calc*fact;
  }
  return result;
}

void
FullHadTreeWriter::endJob()
{
  if(JetSrc_.label() != ""){
    delete[] bTag_TCHE;
    delete[] bTag_TCHP;
    delete[] bTag_SSVHE;
    delete[] bTag_SSVHP;
    delete[] bTag_CSV;
    delete[] bTag_CSVMVA;

    delete[] bTag_TCHE_SF;
    delete[] bTag_TCHP_SF;
    delete[] bTag_SSVHE_SF;
    delete[] bTag_SSVHP_SF;
    delete[] bTag_CSV_SF;
    delete[] bTag_TCHE_SF_Un;
    delete[] bTag_TCHP_SF_Un;
    delete[] bTag_SSVHE_SF_Un;
    delete[] bTag_SSVHP_SF_Un;
    delete[] bTag_CSV_SF_Un;
    delete[] mTag_TCHE_SF;
    delete[] mTag_TCHP_SF;
    delete[] mTag_SSVHE_SF;
    delete[] mTag_SSVHP_SF;
    delete[] mTag_CSV_SF;
    delete[] mTag_TCHE_SF_Un;
    delete[] mTag_TCHP_SF_Un;
    delete[] mTag_SSVHE_SF_Un;
    delete[] mTag_SSVHP_SF_Un;
    delete[] mTag_CSV_SF_Un;

    delete[] charge;
    delete[] fChHad;
    delete[] fNeHad;
    delete[] fChEm;
    delete[] fNeEm;
    //delete[] fElec;
    //delete[] fPhot;
    delete[] fMuon;

    delete[] jetConst;
    delete[] chargeMulti;
    delete[] pdgId;
    delete[] partonFlavour;

    delete[] gluonTag;

    delete[] EtSin2Theta;
    delete[] theta;
    delete[] sinTheta;
    delete[] EtStar;
    delete[] thetaStar;
    delete[] sinThetaStar;
 
    delete[] probs;
    delete[] chi2s;
    delete[] topMasses;
    delete[] w1Mass;
    delete[] w2Mass;
    delete[] comboTypeIDs;
    delete[] comboTypes;
 }

  if(JetSrc_     .label() != ""){
    jets->Delete();
    genJets->Delete();
    genPartons->Delete();
  }
  if(METSrc_     .label() != "") MET->Delete();
  if(MuonSrc_    .label() != "") muons->Delete();
  if(ElectronSrc_.label() != "") electrons->Delete();

  if(FitSrc_.label() != "") {
    delete[] fitAssigns;
    fitVecs->Delete();
  }
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( FullHadTreeWriter );
