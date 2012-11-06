#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "AnalysisDataFormats/TopObjects/interface/TtFullHadEvtPartons.h"

#include "TopAnalysis/TopAnalyzer/interface/TopAngles.h"
#include "TopAnalysis/TopAnalyzer/interface/FullHadEventMixer.h"
#include "TopAnalysis/TopAnalyzer/interface/FullHadTopReco.h"

/// default constructor
FullHadEventMixer::FullHadEventMixer(const edm::ParameterSet& cfg) :
  JetSrc_             ( cfg.getParameter<edm::InputTag>("JetSrc") ),
  METSrc_             ( cfg.getParameter<edm::InputTag>("METSrc") ),
  MuonSrc_            ( cfg.getParameter<edm::InputTag>("MuonSrc") ),
  ElectronSrc_        ( cfg.getParameter<edm::InputTag>("ElectronSrc") ),
  VertexSrc_          ( cfg.getParameter<edm::InputTag>("VertexSrc") ),
//MultiJetMVADiscSrc_ ( cfg.getParameter<edm::InputTag>("MultiJetMVADiscSrc") ),
//useTree_            ( cfg.getParameter<bool>( "useTree" ) ),
  bTagAlgo_           ( cfg.getParameter<std::string>( "bTagAlgo" ) ),
  minBTagValueBJet_   ( cfg.getParameter<double>( "minBTagValueBJet" ) ),
  maxBTagValueNonBJet_( cfg.getParameter<double>( "maxBTagValueNonBJet" ) ),
  jetEnergyResolutionScaleFactors_(cfg.getParameter<std::vector<double> >( "jetEnergyResolutionScaleFactors" ) ),
  jetEnergyResolutionEtaBinning_  (cfg.getParameter<std::vector<double> >( "jetEnergyResolutionEtaBinning" ) ),
  jetCorrectionLevel_ ( cfg.getParameter<std::string>( "jetCorrectionLevel" ) ),
  nMix_               ( cfg.getParameter<unsigned int>( "nMix" ) ),
  speedUp_            ( cfg.getParameter<double>( "speedUp" ) ),
  MCweight_           ( cfg.getParameter<double>("MCweight") ),
  myRand(0),
  //tree(0),
  kMAX(50), kMAXCombo(10000)
{

  myRand = new TRandom3(0);

  if(cfg.exists("udscResolutions") && cfg.exists("bResolutions")){
    udscResolutions_ = cfg.getParameter <std::vector<edm::ParameterSet> >("udscResolutions");
    bResolutions_    = cfg.getParameter <std::vector<edm::ParameterSet> >("bResolutions");
  }
  else if(cfg.exists("udscResolutions") || cfg.exists("bResolutions")){
    if(cfg.exists("udscResolutions")) throw cms::Exception("WrongConfig") << "Parameter 'bResolutions' is needed if parameter 'udscResolutions' is defined!\n";
    else                              throw cms::Exception("WrongConfig") << "Parameter 'udscResolutions' is needed if parameter 'bResolutions' is defined!\n";
  }

  // define kinematic fit interface
  unsigned constr[] = {1,2,5};
  std::vector<unsigned> constraints_(constr, constr + sizeof(constr) / sizeof(unsigned));
  // define kinematic fit interface
  //TtFullHadKinFitter::KinFit(bool useBTagging, unsigned int bTags, std::string bTagAlgo, double minBTagValueBJet, double maxBTagValueNonBJet,
  //			       std::vector<edm::ParameterSet> udscResolutions, std::vector<edm::ParameterSet> bResolutions,
  //                           std::vector<double> jetEnergyResolutionScaleFactors, std::vector<double> jetEnergyResolutionEtaBinning,
  //			       std::string jetCorrectionLevel, int maxNJets, int maxNComb,
  //			       unsigned int maxNrIter, double maxDeltaS, double maxF, unsigned int jetParam, std::vector<unsigned> constraints, double mW, double mTop)
  kinFitter = new TtFullHadKinFitter::KinFit(true, 2, bTagAlgo_, minBTagValueBJet_, maxBTagValueNonBJet_,
					     udscResolutions_, bResolutions_, 
					     jetEnergyResolutionScaleFactors_, jetEnergyResolutionEtaBinning_,
					     jetCorrectionLevel_, -1, -1,
					     500, 5e-5, 0.0001, 1, constraints_, 80.4, 173.);
  
  //tree = 0;
}

/// histogramm booking
void
FullHadEventMixer::beginJob()
{
  std::cout << "ATTENTION !!! WARNING >> !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! << WARNING !!! ATTENTION" << std::endl;
  std::cout << "ATTENTION !!! WARNING >> Pt cuts are hard-coded to be: 60,60,60,60,50,40 GeV << WARNING !!! ATTENTION" << std::endl;
  std::cout << "ATTENTION !!! WARNING >> !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! << WARNING !!! ATTENTION" << std::endl;

  std::cout << "ATTENTION !!! >> !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! << !!! ATTENTION" << std::endl;
  std::cout << "ATTENTION !!! >> Analysis speed up with factor 1:" << speedUp_ << " << !!! ATTENTION" << std::endl;
  std::cout << "ATTENTION !!! >> !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! << !!! ATTENTION" << std::endl;

  // define TFileService which takes care of writing contents to root file
  edm::Service<TFileService> fs;
  if( !fs ) throw edm::Exception( edm::errors::Configuration, "TFile Service is not registered in cfg file" );

  /** 
      Kinematic Variables
  **/

  /*
  // event weight needed for QCD samples
  bookVariable( fs, "MCweight" );
  fillValue( "MCweight" , MCweight_ );

  // properties of kinematic fit for the tree
  bookVariable( fs, "topMass" );
  bookVariable( fs, "prob" );
  bookVariable( fs, "chi2" );
  bookVariable( fs, "ttbarPt" );
  bookVariable( fs, "ttbarMass" );
  bookVariable( fs, "bAngle" );
  //bookVariable( fs, "multiJetMVADisc" );

  // fit exit code
  bookVariable( fs, "fitExitCode" , 2, -1.5 , 0.5 , useTree_ );

  for(std::map<std::string, TH1*>::const_iterator hist = hists_.begin(); hist != hists_.end(); ++hist){
    hist->second->Sumw2();
  }
  */

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
  MCweight = MCweight_;
  tree->Branch("MCweight", &MCweight, "MCweight/D");
  
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
  // number of jets in events
  if(JetSrc_.label() != ""){
    Njet = -1;
    tree->Branch("Njet", &Njet, "Njet/I");

    // 4-vectors of jets
    jets = new TClonesArray("TLorentzVector", kMAX);
    tree->Branch("jets", &jets, 32000, -1);
    jets->BypassStreamer();

    // b-tag discriminators of jets
    bTag_TCHE        = new float[kMAX];
    bTag_TCHP        = new float[kMAX];
    bTag_SSVHE       = new float[kMAX];
    bTag_SSVHP       = new float[kMAX];
    bTag_CSV         = new float[kMAX];
    bTag_CSVMVA      = new float[kMAX];
    for(unsigned short i = 0; i < kMAX; ++i) {
      bTag_TCHE        [i] = -100.;
      bTag_TCHP        [i] = -100.;
      bTag_SSVHE       [i] = -100.;
      bTag_SSVHP       [i] = -100.;
      bTag_CSV         [i] = -100.;
      bTag_CSVMVA      [i] = -100.;
    }

    tree->Branch("bTag_TCHE"  , bTag_TCHE  , "bTag_TCHE[Njet]"    );
    tree->Branch("bTag_TCHP"  , bTag_TCHP  , "bTag_TCHP[Njet]"    );
    tree->Branch("bTag_SSVHE" , bTag_SSVHE , "bTag_SSVHE[Njet]"   );
    tree->Branch("bTag_SSVHP" , bTag_SSVHP , "bTag_SSVHP[Njet]"   );
    tree->Branch("bTag_CSV"   , bTag_CSV   , "bTag_CSV[Njet]/F"   );
    tree->Branch("bTag_CSVMVA", bTag_CSVMVA, "bTag_CSVMVA[Njet]/F");

    // probability and chi2 of kinematic fit
    fitExitCode    = -66;
    prob           =  -1.;
    chi2           =  -1.;
    topMass        =  -1.;
    ttMass         =  -1.;
    ttPt           =  -1.;
    tree->Branch("prob"   , &prob   , "prob/D"   );
    tree->Branch("chi2"   , &chi2   , "chi2/D"   );
    tree->Branch("topMass", &topMass, "topMass/D");
    tree->Branch("ttMass" , &ttMass , "ttMass/D" );
    tree->Branch("ttPt"   , &ttMass , "ttPt/D"   );

    // all masses, probs etc. needed fo mass measurment
    nCombos    = 0;
    probs      = new double[kMAXCombo];
    chi2s      = new double[kMAXCombo];
    topMasses  = new double[kMAXCombo];
    w1Mass     = new double[kMAXCombo];
    w2Mass     = new double[kMAXCombo];

    // angles of ttbar system
    dRbb                                = new float[kMAXCombo];
    ttDetFrame                          = new float[kMAXCombo];
    bbDetFrame                          = new float[kMAXCombo];
    bbTtbarFrame                        = new float[kMAXCombo];
    WWTtbarFrame                        = new float[kMAXCombo];
    tBBranch1TtbarFrame                 = new float[kMAXCombo];
    tBBranch2TtbarFrame                 = new float[kMAXCombo];
    bWBranch1TtbarFrame                 = new float[kMAXCombo];
    bWBranch2TtbarFrame                 = new float[kMAXCombo];
    tWBranch1TopInTtbarFrameWInTopFrame = new float[kMAXCombo];
    tWBranch2TopInTtbarFrameWInTopFrame = new float[kMAXCombo];
    qQbarTopFrame                       = new float[kMAXCombo];
    qQbarDetFrame                       = new float[kMAXCombo];
    pPbarTopFrame                       = new float[kMAXCombo];
    pQbarTtbarFrame                     = new float[kMAXCombo];
    pQTtbarFrame                        = new float[kMAXCombo];
    pbarQbarTtbarFrame                  = new float[kMAXCombo];
    pbarQTtbarFrame                     = new float[kMAXCombo];
    bhad1QTopFrame                      = new float[kMAXCombo];
    bhad1QbarTopFrame                   = new float[kMAXCombo];
    bhad1PTtbarFrame                    = new float[kMAXCombo];
    bhad1PbarTtbarFrame                 = new float[kMAXCombo];
    bhad2QTtbarFrame                    = new float[kMAXCombo];
    bhad2QbarTtbarFrame                 = new float[kMAXCombo];
    bhad2PTopFrame                      = new float[kMAXCombo];
    bhad2PbarTopFrame                   = new float[kMAXCombo];
    qInW1FrameW1InDetFrame              = new float[kMAXCombo];
    qbarInW1FrameW1InDetFrame           = new float[kMAXCombo];
    pInW2FrameW2InDetFrame              = new float[kMAXCombo];
    pbarInW2FrameW2InDetFrame           = new float[kMAXCombo];

    for(unsigned int i = 0; i < kMAXCombo; ++i) {
      probs     [i] = -1.;
      chi2s     [i] = -1.;
      topMasses [i] = -1.;
      w1Mass    [i] = -1.; 
      w2Mass    [i] = -1.;
      dRbb                               [i] =   -1.;
      ttDetFrame                         [i] = -100.;
      bbDetFrame                         [i] = -100.;
      bbTtbarFrame                       [i] = -100.;
      WWTtbarFrame                       [i] = -100.;
      tBBranch1TtbarFrame                [i] = -100.;
      tBBranch2TtbarFrame                [i] = -100.;
      bWBranch1TtbarFrame                [i] = -100.;
      bWBranch2TtbarFrame                [i] = -100.;
      tWBranch1TopInTtbarFrameWInTopFrame[i] = -100.;
      tWBranch2TopInTtbarFrameWInTopFrame[i] = -100.;
      qQbarTopFrame                      [i] = -100.;
      qQbarDetFrame                      [i] = -100.;
      pPbarTopFrame                      [i] = -100.;
      pQbarTtbarFrame                    [i] = -100.;
      pQTtbarFrame                       [i] = -100.;
      pbarQbarTtbarFrame                 [i] = -100.;
      pbarQTtbarFrame                    [i] = -100.;
      bhad1QTopFrame                     [i] = -100.;
      bhad1QbarTopFrame                  [i] = -100.;
      bhad1PTtbarFrame                   [i] = -100.;
      bhad1PbarTtbarFrame                [i] = -100.;
      bhad2QTtbarFrame                   [i] = -100.;
      bhad2QbarTtbarFrame                [i] = -100.;
      bhad2PTopFrame                     [i] = -100.;
      bhad2PbarTopFrame                  [i] = -100.;
      qInW1FrameW1InDetFrame             [i] = -100.;
      qbarInW1FrameW1InDetFrame          [i] = -100.;
      pInW2FrameW2InDetFrame             [i] = -100.;
      pbarInW2FrameW2InDetFrame          [i] = -100.;
    }

    tree->Branch("nCombos"  , &nCombos  , "nCombos/i"           );
    tree->Branch("probs"    ,  probs    , "probs[nCombos]/D"    );
    tree->Branch("chi2s"    ,  chi2s    , "chi2s[nCombos]/D"    );
    tree->Branch("topMasses",  topMasses, "topMasses[nCombos]/D");
    tree->Branch("w1Mass"   ,  w1Mass   , "w1Mass[nCombos]/D"   );
    tree->Branch("w2Mass"   ,  w2Mass   , "w2Mass[nCombos]/D"   );

    tree->Branch("dRbb"                               , dRbb                               , "dRbb[nCombos]/F"                              );
    tree->Branch("ttDetFrame"                         , ttDetFrame                         , "ttDetFrame[nCombos]/F"                         );
    tree->Branch("bbDetFrame"                         , bbDetFrame                         , "bbDetFrame[nCombos]/F"                         );
    tree->Branch("bbTtbarFrame"                       , bbTtbarFrame                       , "bbTtbarFrame[nCombos]/F"                       );
    tree->Branch("WWTtbarFrame"                       , WWTtbarFrame                       , "WWTtbarFrame[nCombos]/F"                       );
    tree->Branch("tBBranch1TtbarFrame"                , tBBranch1TtbarFrame                , "tBBranch1TtbarFrame[nCombos]/F"                );
    tree->Branch("tBBranch2TtbarFrame"                , tBBranch2TtbarFrame                , "tBBranch2TtbarFrame[nCombos]/F"                );
    tree->Branch("bWBranch1TtbarFrame"                , bWBranch1TtbarFrame                , "bWBranch1TtbarFrame[nCombos]/F"                );
    tree->Branch("bWBranch2TtbarFrame"                , bWBranch2TtbarFrame                , "bWBranch2TtbarFrame[nCombos]/F"                );
    tree->Branch("tWBranch1TopInTtbarFrameWInTopFrame", tWBranch1TopInTtbarFrameWInTopFrame, "tWBranch1TopInTtbarFrameWInTopFrame[nCombos]/F");
    tree->Branch("tWBranch2TopInTtbarFrameWInTopFrame", tWBranch2TopInTtbarFrameWInTopFrame, "tWBranch2TopInTtbarFrameWInTopFrame[nCombos]/F");
    tree->Branch("qQbarTopFrame"                      , qQbarTopFrame                      , "qQbarTopFrame[nCombos]/F"                      );
    tree->Branch("qQbarDetFrame"                      , qQbarDetFrame                      , "qQbarDetFrame[nCombos]/F"                      );
    tree->Branch("pPbarTopFrame"                      , pPbarTopFrame                      , "pPbarTopFrame[nCombos]/F"                      );
    tree->Branch("pQbarTtbarFrame"                    , pQbarTtbarFrame                    , "pQbarTtbarFrame[nCombos]/F"                    );
    tree->Branch("pQTtbarFrame"                       , pQTtbarFrame                       , "pQTtbarFrame[nCombos]/F"                       );
    tree->Branch("pbarQbarTtbarFrame"                 , pbarQbarTtbarFrame                 , "pbarQbarTtbarFrame[nCombos]/F"                 );
    tree->Branch("pbarQTtbarFrame"                    , pbarQTtbarFrame                    , "pbarQTtbarFrame[nCombos]/F"                    );
    tree->Branch("bhad1QTopFrame"                     , bhad1QTopFrame                     , "bhad1QTopFrame[nCombos]/F"                     );
    tree->Branch("bhad1QbarTopFrame"                  , bhad1QbarTopFrame                  , "bhad1QbarTopFrame[nCombos]/F"                  );
    tree->Branch("bhad1PTtbarFrame"                   , bhad1PTtbarFrame                   , "bhad1PTtbarFrame[nCombos]/F"                   );
    tree->Branch("bhad1PbarTtbarFrame"                , bhad1PbarTtbarFrame                , "bhad1PbarTtbarFrame[nCombos]/F"                );
    tree->Branch("bhad2QTtbarFrame"                   , bhad2QTtbarFrame                   , "bhad2QTtbarFrame[nCombos]/F"                   );
    tree->Branch("bhad2QbarTtbarFrame"                , bhad2QbarTtbarFrame                , "bhad2QbarTtbarFrame[nCombos]/F"                );
    tree->Branch("bhad2PTopFrame"                     , bhad2PTopFrame                     , "bhad2PTopFrame[nCombos]/F"                     );
    tree->Branch("bhad2PbarTopFrame"                  , bhad2PbarTopFrame                  , "bhad2PbarTopFrame[nCombos]/F"                  );
    tree->Branch("qInW1FrameW1InDetFrame"             , qInW1FrameW1InDetFrame             , "qInW1FrameW1InDetFrame[nCombos]/F"             );
    tree->Branch("qbarInW1FrameW1InDetFrame"          , qbarInW1FrameW1InDetFrame          , "qbarInW1FrameW1InDetFrame[nCombos]/F"          );
    tree->Branch("pInW2FrameW2InDetFrame"             , pInW2FrameW2InDetFrame             , "pInW2FrameW2InDetFrame[nCombos]/F"             );
    tree->Branch("pbarInW2FrameW2InDetFrame"          , pbarInW2FrameW2InDetFrame          , "pbarInW2FrameW2InDetFrame[nCombos]/F"          );

    //// jet-parton assignments
    //fitAssigns = new short[6*kMAXCombo];
    //for(unsigned int i = 0; i < 6*kMAXCombo; ++i){
    //  fitAssigns[i] = -1;
    //}
    //tree->Branch("fitAssigns", fitAssigns , "fitAssigns[nCombos][6]/S");
    //
    //// 4-vectors of kinFit
    //fitVecs = new TClonesArray("TLorentzVector", 6*kMAXCombo);
    //tree->Branch("fitVecs", &fitVecs, 32000, -1);
    //fitVecs->BypassStreamer();
  }

  // number of vertices
  if(VertexSrc_.label() != ""){
    nVertex = -1;
    tree->Branch("nVertex", &nVertex, "nVertex/S");
  }
}

/// histogram filling for fwlite and for full fw
void
FullHadEventMixer::analyze(const edm::Event& event, const edm::EventSetup& iSetup)
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

  edm::Handle<std::vector<reco::Vertex> > vertecies_h;
  event.getByLabel(VertexSrc_, vertecies_h);
  
  //edm::Handle<double> multiJetMVADisc_h;
  //event.getByLabel(MultiJetMVADiscSrc_, multiJetMVADisc_h);
  
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

  nVertex = vertecies_h.isValid() ? vertecies_h->size() : -1;

  /** 
      Fill Kinematic Variables
  **/
  
  //double weight = 1.;

  if(jets_h.isValid()){
    edm::View<pat::Jet> jet_view = *jets_h;
    if(jet_view.size() < 6) return;

    std::vector<pat::Jet> theJets;
    unsigned short bJetCounter = 0, jetCounter = 0;
    for(edm::View<pat::Jet>::const_iterator jet = jet_view.begin(); jet != jet_view.end(); ++jet, ++jetCounter){
      theJets.push_back(*jet);
      if(bJetCounter < 2 && jet->bDiscriminator(bTagAlgo_) > minBTagValueBJet_){
	if(bJetCounter != jetCounter) std::swap(theJets[bJetCounter], theJets[jetCounter]);
	++bJetCounter;
      }
    }

    //std::cout << "oldJets_.size(), nMix: " << oldJets_.size() << ", " << nMix_ << std::endl;

    if(oldJets_.size() != nMix_){
      // jets
      oldJets_.push_back(theJets);
      // multiJet MVA discriminator
      //currMVADiscs_.push_back(multiJetMVADisc_h.isValid() ? *multiJetMVADisc_h : -10.);
    }
    else{
      unsigned long counter = 0;
      for(unsigned short j0 = 0; j0 < nMix_; ++j0){
	if(j0 >= oldJets_[j0].size()) continue;
	for(unsigned short j1 = 0; j1 < nMix_; ++j1){
	  if(j1 >= oldJets_[j1].size()) continue;
	  if(j1 == j0) continue;
	  for(unsigned short j2 = 0; j2 < nMix_; ++j2){
	    if(j2 >= oldJets_[j2].size()) continue;
	    if(j2 == j0 || j2 == j1) continue;
	    for(unsigned short j3 = 0; j3 < nMix_; ++j3){
	      if(j3 >= oldJets_[j3].size()) continue;
	      if(j3 == j0 || j3 == j1 || j3 == j2) continue;
	      for(unsigned short j4 = 0; j4 < nMix_; ++j4){
		if(j4 >= oldJets_[j4].size()) continue;
		if(j4 == j0 || j4 == j1 || j4 == j2 || j4 == j3) continue;
		for(unsigned short j5 = 0; j5 < nMix_; ++j5){
		  if(j5 >= oldJets_[j5].size()) continue;
		  if(j5 == j0 || j5 == j1 || j5 == j2 || j5 == j3 || j5 == j4) continue;
		  for(unsigned short j6 = 0; j6 < nMix_; ++j6){
		    if(j6 >= oldJets_[j6].size()) continue;
		    if(j6 == j0 || j6 == j1 || j6 == j2 || j6 == j3 || j6 == j4 || j6 == j5) continue;
		    for(unsigned short j7 = 0; j7 < nMix_; ++j7){
		      if(j7 >= oldJets_[j7].size()) continue;
		      if(j7 == j0 || j7 == j1 || j7 == j2 || j7 == j3 || j7 == j4 || j7 == j5 || j7 == j6) continue;
		      for(unsigned short j8 = 0; j8 < nMix_; ++j8){
			if(j8 >= oldJets_[j8].size()) continue;
			if(j8 == j0 || j8 == j1 || j8 == j2 || j8 == j3 || j8 == j4 || j8 == j5 || j8 == j6 || j8 == j7) continue;
			for(unsigned short j9 = 0; j9 < nMix_; ++j9){
			  if(j9 >= oldJets_[j9].size()) continue;
			  if(j9 == j0 || j9 == j1 || j9 == j2 || j9 == j3 || j9 == j4 || j9 == j5 || j9 == j6 || j9 == j7 || j9 == j8) continue;
			  if(oldJets_[j0].size() > 0 && 
			     oldJets_[j1].size() > 1 && 
			     oldJets_[j2].size() > 2 && 
			     oldJets_[j3].size() > 3 && 
			     oldJets_[j4].size() > 4 && 
			     oldJets_[j5].size() > 5 && 
			     oldJets_[j6].size() > 6 && 
			     oldJets_[j7].size() > 7 && 
			     oldJets_[j8].size() > 8 && 
			     oldJets_[j9].size() > 9 ){

			    // only take 1 out of speedUp_ events
			    if(myRand->Uniform(speedUp_) > 1.0) continue;

			    // create jets for fit
			    std::vector<pat::Jet> myJets(10);
			    myJets[0] = oldJets_[j0][0];
			    myJets[1] = oldJets_[j1][1];
			    myJets[2] = oldJets_[j2][2];
			    myJets[3] = oldJets_[j3][3];
			    myJets[4] = oldJets_[j4][4];
			    myJets[5] = oldJets_[j5][5];
			    myJets[6] = oldJets_[j6][6];
			    myJets[7] = oldJets_[j7][7];
			    myJets[8] = oldJets_[j8][8];
			    myJets[9] = oldJets_[j9][9];
			    // sort the new jet collection
			    std::sort(myJets.begin(), myJets.end(), pTComparator_);
			    // fit
			    doFitting(myJets);
			    ++counter;
			  }
			}
			if(oldJets_[j0].size() > 0 && 
			   oldJets_[j1].size() > 1 && 
			   oldJets_[j2].size() > 2 && 
			   oldJets_[j3].size() > 3 && 
			   oldJets_[j4].size() > 4 && 
			   oldJets_[j5].size() > 5 && 
			   oldJets_[j6].size() > 6 && 
			   oldJets_[j7].size() > 7 && 
			   oldJets_[j8].size() > 8 ){

			  // only take 1 out of speedUp_ events
			  if(myRand->Uniform(speedUp_) > 1.0) continue;

			  // create jets for fit
			  std::vector<pat::Jet> myJets(9);
			  myJets[0] = oldJets_[j0][0];
			  myJets[1] = oldJets_[j1][1];
			  myJets[2] = oldJets_[j2][2];
			  myJets[3] = oldJets_[j3][3];
			  myJets[4] = oldJets_[j4][4];
			  myJets[5] = oldJets_[j5][5];
			  myJets[6] = oldJets_[j6][6];
			  myJets[7] = oldJets_[j7][7];
			  myJets[8] = oldJets_[j8][8];
			  // sort the new jet collection
			  std::sort(myJets.begin(), myJets.end(), pTComparator_);
			  // fit
			  doFitting(myJets);
			  ++counter;
			}
		      }
		      if(oldJets_[j0].size() > 0 && 
			 oldJets_[j1].size() > 1 && 
			 oldJets_[j2].size() > 2 && 
			 oldJets_[j3].size() > 3 && 
			 oldJets_[j4].size() > 4 && 
			 oldJets_[j5].size() > 5 && 
			 oldJets_[j6].size() > 6 && 
			 oldJets_[j7].size() > 7 ){

			// only take 1 out of speedUp_ events
			if(myRand->Uniform(speedUp_) > 1.0) continue;

			// create jets for fit
			std::vector<pat::Jet> myJets(8);
			myJets[0] = oldJets_[j0][0];
			myJets[1] = oldJets_[j1][1];
			myJets[2] = oldJets_[j2][2];
			myJets[3] = oldJets_[j3][3];
			myJets[4] = oldJets_[j4][4];
			myJets[5] = oldJets_[j5][5];
			myJets[6] = oldJets_[j6][6];
			myJets[7] = oldJets_[j7][7];
			// sort the new jet collection
			std::sort(myJets.begin(), myJets.end(), pTComparator_);
			// fit
			doFitting(myJets);
			++counter;
		      }
		    }
		    if(oldJets_[j0].size() > 0 && 
		       oldJets_[j1].size() > 1 && 
		       oldJets_[j2].size() > 2 && 
		       oldJets_[j3].size() > 3 && 
		       oldJets_[j4].size() > 4 && 
		       oldJets_[j5].size() > 5 && 
		       oldJets_[j6].size() > 6 ){
		  
		      // only take 1 out of speedUp_ events
		      if(myRand->Uniform(speedUp_) > 1.0) continue;

		      // create jets for fit
		      std::vector<pat::Jet> myJets(7);
		      myJets[0] = oldJets_[j0][0];
		      myJets[1] = oldJets_[j1][1];
		      myJets[2] = oldJets_[j2][2];
		      myJets[3] = oldJets_[j3][3];
		      myJets[4] = oldJets_[j4][4];
		      myJets[5] = oldJets_[j5][5];
		      myJets[6] = oldJets_[j6][6];
		      // sort the new jet collection
		      std::sort(myJets.begin(), myJets.end(), pTComparator_);
		      // fit
		      doFitting(myJets);
		      ++counter;
		    }
		  }
		  if(oldJets_[j0].size() > 0 && 
		     oldJets_[j1].size() > 1 && 
		     oldJets_[j2].size() > 2 && 
		     oldJets_[j3].size() > 3 && 
		     oldJets_[j4].size() > 4 && 
		     oldJets_[j5].size() > 5 ){

		    // only take 1 out of speedUp_ events
		    if(myRand->Uniform(speedUp_) > 1.0) continue;

		    // create jets for fit
		    std::vector<pat::Jet> myJets(6);
		    myJets[0] = oldJets_[j0][0];
		    myJets[1] = oldJets_[j1][1];
		    myJets[2] = oldJets_[j2][2];
		    myJets[3] = oldJets_[j3][3];
		    myJets[4] = oldJets_[j4][4];
		    myJets[5] = oldJets_[j5][5];
		    // sort the new jet collection
		    std::sort(myJets.begin(), myJets.end(), pTComparator_);
		    // fit
		    doFitting(myJets);
		    ++counter;
		  }
		}
	      }
	    }
	  }
	}
      }
      //std::cout << "Counter: " << counter << std::endl;
      for(std::vector<std::vector<pat::Jet> >::iterator oldJets = oldJets_.begin(); oldJets != oldJets_.end(); ++oldJets){
	oldJets->clear();
      }
      oldJets_.clear();
    }
  }
}

/// do the kinematic fit and save results
void
FullHadEventMixer::doFitting(const std::vector<pat::Jet>& myJets)
{
  // skip events not compatible with pt requirements
  if(myJets[3].pt() < 60 || myJets[4].pt() < 50 || myJets[5].pt() < 40) return;

  //std::cout << "do fitting" << std::endl;
  unsigned short i = 0;
  jets->Clear();
  Njet = myJets.size();
  for(std::vector< pat::Jet >::const_iterator jet = myJets.begin(); jet != myJets.end(); ++jet, ++i){
    new((*jets)[i]) TLorentzVector(jet->px(), jet->py(), jet->pz(), jet->energy());
    bTag_TCHE    [i] = jet->bDiscriminator("trackCountingHighEffBJetTags");
    bTag_TCHP    [i] = jet->bDiscriminator("trackCountingHighPurBJetTags");
    bTag_SSVHE   [i] = jet->bDiscriminator("simpleSecondaryVertexHighEffBJetTags");
    bTag_SSVHP   [i] = jet->bDiscriminator("simpleSecondaryVertexHighPurBJetTags");
    bTag_CSV     [i] = jet->bDiscriminator("combinedSecondaryVertexBJetTags");
    bTag_CSVMVA  [i] = jet->bDiscriminator("combinedSecondaryVertexMVABJetTags");
  }

  // reset variables of kinFit
  prob      = -1.;
  chi2      = -1.;
  topMass   = -1.;
  ttMass    = -1.;

  nCombos = 0;
  for(unsigned int i = 0; i < kMAXCombo; ++i) {
    probs     [i] = -1.;
    chi2s     [i] = -1.;
    topMasses [i] = -1.;
    w1Mass    [i] = -1.; 
    w2Mass    [i] = -1.;
    dRbb                               [i] =   -1.;
    ttDetFrame                         [i] = -100.;
    bbDetFrame                         [i] = -100.;
    bbTtbarFrame                       [i] = -100.;
    WWTtbarFrame                       [i] = -100.;
    tBBranch1TtbarFrame                [i] = -100.;
    tBBranch2TtbarFrame                [i] = -100.;
    bWBranch1TtbarFrame                [i] = -100.;
    bWBranch2TtbarFrame                [i] = -100.;
    tWBranch1TopInTtbarFrameWInTopFrame[i] = -100.;
    tWBranch2TopInTtbarFrameWInTopFrame[i] = -100.;
    qQbarTopFrame                      [i] = -100.;
    qQbarDetFrame                      [i] = -100.;
    pPbarTopFrame                      [i] = -100.;
    pQbarTtbarFrame                    [i] = -100.;
    pQTtbarFrame                       [i] = -100.;
    pbarQbarTtbarFrame                 [i] = -100.;
    pbarQTtbarFrame                    [i] = -100.;
    bhad1QTopFrame                     [i] = -100.;
    bhad1QbarTopFrame                  [i] = -100.;
    bhad1PTtbarFrame                   [i] = -100.;
    bhad1PbarTtbarFrame                [i] = -100.;
    bhad2QTtbarFrame                   [i] = -100.;
    bhad2QbarTtbarFrame                [i] = -100.;
    bhad2PTopFrame                     [i] = -100.;
    bhad2PbarTopFrame                  [i] = -100.;
    qInW1FrameW1InDetFrame             [i] = -100.;
    qbarInW1FrameW1InDetFrame          [i] = -100.;
    pInW2FrameW2InDetFrame             [i] = -100.;
    pbarInW2FrameW2InDetFrame          [i] = -100.;

    //for(unsigned int i = 0; i < 6*kMAXCombo; ++i){
    //  fitAssigns[i] = -1;
    //}
    //fitVecs->Clear();
  }

  std::list<TtFullHadKinFitter::KinFitResult> result = kinFitter->fit(myJets);
  if(result.size() == 0){
    //std::cout << "filling empty" << std::endl;
    tree->Fill();
    return;
  }
  
  for(std::list<TtFullHadKinFitter::KinFitResult>::const_iterator res = result.begin(); res != result.end(); ++res){
    /*
    fillValue( "fitExitCode" , (double)res->Status , 1. );
    */
    fitExitCode = res->Status;
    if(res->Status != 0) continue;
    ++nCombos;
    if(nCombos > kMAXCombo){
      std::cout << "Maximum number of combinations per event (" <<  kMAXCombo << ") reached, stopping and continuing with next event!" << std::endl;
      break;
    }
  
    /*
    // kinfitted mass of top quark
    double topMass = (res->B.p4()+res->LightQ.p4()+res->LightQBar.p4()).mass();
    // invariant mass of ttbar system
    double invTTBarMass = (res->B.p4()+res->LightQ.p4()+res->LightQBar.p4()+res->BBar.p4()+res->LightP.p4()+res->LightPBar.p4()).mass();
    // pt of ttbar system
    double ttbarPt      = (res->B.p4()+res->LightQ.p4()+res->LightQBar.p4()+res->BBar.p4()+res->LightP.p4()+res->LightPBar.p4()).pt();
    // angle between b-quark candidates from hypothesis
    TLorentzVector bCandidate    = TLorentzVector( res->B   .px(), res->B   .py(), res->B   .pz(), res->B   .energy() );
    TLorentzVector bBarCandidate = TLorentzVector( res->BBar.px(), res->BBar.py(), res->BBar.pz(), res->BBar.energy() );
    double bAngle = bCandidate.Angle( bBarCandidate.Vect() );
    */
    TopAngles angles = TopAngles::TopAngles(res->B   .p4(), res->LightQ.p4(), res->LightQBar.p4(),
					    res->BBar.p4(), res->LightP.p4(), res->LightPBar.p4());

    if(nCombos == 1){
      prob    = res->Prob;												    
      chi2    = res->Chi2;												    
      topMass = (res->B.p4()+res->LightQ.p4()+res->LightQBar.p4()).mass();						    
      ttMass  = (res->B.p4()+res->LightQ.p4()+res->LightQBar.p4()+res->BBar.p4()+res->LightP.p4()+res->LightPBar.p4()).mass();
      ttPt    = (res->B.p4()+res->LightQ.p4()+res->LightQBar.p4()+res->BBar.p4()+res->LightP.p4()+res->LightPBar.p4()).pt();
    }

    probs    [nCombos-1] = res->Prob;
    chi2s    [nCombos-1] = res->Chi2;
    topMasses[nCombos-1] = (res->B.p4()+res->LightQ.p4()+res->LightQBar.p4()).mass();
    w1Mass   [nCombos-1] = (((TLorentzVector*)jets->At(res->JetCombi[TtFullHadEvtPartons::LightQ]))->operator+(*(TLorentzVector*)jets->At(res->JetCombi[TtFullHadEvtPartons::LightQBar]))).M();
    w2Mass   [nCombos-1] = (((TLorentzVector*)jets->At(res->JetCombi[TtFullHadEvtPartons::LightP]))->operator+(*(TLorentzVector*)jets->At(res->JetCombi[TtFullHadEvtPartons::LightPBar]))).M();

    dRbb[nCombos-1] = deltaR(res->B.eta(), res->B.phi(), res->BBar.eta(), res->BBar.phi());
    ttDetFrame                         [nCombos-1] = angles.ttDetFrame()                         ;			
    bbDetFrame                         [nCombos-1] = angles.bbDetFrame()                         ;			
    bbTtbarFrame                       [nCombos-1] = angles.bbTtbarFrame()                       ;			
    WWTtbarFrame                       [nCombos-1] = angles.WWTtbarFrame()                       ;			
    tBBranch1TtbarFrame                [nCombos-1] = angles.tBBranch1TtbarFrame()                ;			
    tBBranch2TtbarFrame                [nCombos-1] = angles.tBBranch2TtbarFrame()                ;			
    bWBranch1TtbarFrame                [nCombos-1] = angles.bWBranch1TtbarFrame()                ;			
    bWBranch2TtbarFrame                [nCombos-1] = angles.bWBranch2TtbarFrame()                ;			
    tWBranch1TopInTtbarFrameWInTopFrame[nCombos-1] = angles.tWBranch1TopInTtbarFrameWInTopFrame();	
    tWBranch2TopInTtbarFrameWInTopFrame[nCombos-1] = angles.tWBranch2TopInTtbarFrameWInTopFrame();	
    qQbarTopFrame                      [nCombos-1] = angles.qQbarTopFrame()                      ;			
    qQbarDetFrame                      [nCombos-1] = angles.qQbarDetFrame()                      ;			
    pPbarTopFrame                      [nCombos-1] = angles.pPbarTopFrame()                      ;			
    pQbarTtbarFrame                    [nCombos-1] = angles.pQbarTtbarFrame()                    ;			
    pQTtbarFrame                       [nCombos-1] = angles.pQTtbarFrame()                       ;			
    pbarQbarTtbarFrame                 [nCombos-1] = angles.pbarQbarTtbarFrame()                 ;			
    pbarQTtbarFrame                    [nCombos-1] = angles.pbarQTtbarFrame()                    ;			
    bhad1QTopFrame                     [nCombos-1] = angles.bhad1QTopFrame()                     ;			
    bhad1QbarTopFrame                  [nCombos-1] = angles.bhad1QbarTopFrame()                  ;			
    bhad1PTtbarFrame                   [nCombos-1] = angles.bhad1PTtbarFrame()                   ;			
    bhad1PbarTtbarFrame                [nCombos-1] = angles.bhad1PbarTtbarFrame()                ;			
    bhad2QTtbarFrame                   [nCombos-1] = angles.bhad2QTtbarFrame()                   ;			
    bhad2QbarTtbarFrame                [nCombos-1] = angles.bhad2QbarTtbarFrame()                ;			
    bhad2PTopFrame                     [nCombos-1] = angles.bhad2PTopFrame()                     ;			
    bhad2PbarTopFrame                  [nCombos-1] = angles.bhad2PbarTopFrame()                  ;			
    qInW1FrameW1InDetFrame             [nCombos-1] = angles.qInW1FrameW1InDetFrame()             ;		
    qbarInW1FrameW1InDetFrame          [nCombos-1] = angles.qbarInW1FrameW1InDetFrame()          ;		
    pInW2FrameW2InDetFrame             [nCombos-1] = angles.pInW2FrameW2InDetFrame()             ; 		
    pbarInW2FrameW2InDetFrame          [nCombos-1] = angles.pbarInW2FrameW2InDetFrame()          ;                

    /*
    // properties of kinematic fit for the tree
    fillValue( "topMass"        , topMass      );
    fillValue( "prob"           , res->Prob    );
    fillValue( "chi2"           , res->Chi2    );
    fillValue( "ttbarPt"        , ttbarPt      );
    fillValue( "ttbarMass"      , invTTBarMass );
    fillValue( "bAngle"         , bAngle       );
    //fillValue( "multiJetMVADisc", multiJetMVADisc );
    
    // fill the tree, if any variable should be put in
    if(treeVars_.size()) tree->Fill();
    */
    /*
    // stop after first (lowest chi2) event was found
    if(res->Status == 0) return;
    */
  }
  //std::cout << "filling full" << std::endl;
  tree->Fill();
}

void
FullHadEventMixer::endJob()
{
  if(JetSrc_.label() != ""){
    delete[] bTag_TCHE;
    delete[] bTag_TCHP;
    delete[] bTag_SSVHE;
    delete[] bTag_SSVHP;
    delete[] bTag_CSV;
    delete[] bTag_CSVMVA;

    delete[] probs;
    delete[] chi2s;
    delete[] topMasses;
    delete[] w1Mass;
    delete[] w2Mass;

    //delete[] fitAssigns;
    //fitVecs->Delete();
 }

  if(JetSrc_     .label() != "") jets->Delete();
  if(METSrc_     .label() != "") MET->Delete();
  if(MuonSrc_    .label() != "") muons->Delete();
  if(ElectronSrc_.label() != "") electrons->Delete();

  delete myRand;
  delete kinFitter;
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( FullHadEventMixer );

