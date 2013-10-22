
#include "TopAnalysis/TopAnalyzer/interface/MixedObjectsAnalyzer.h"

#include "stdio.h"
#include <TString.h>

#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "AnalysisDataFormats/TopObjects/interface/TtSemiLepEvtPartons.h"
#include "AnalysisDataFormats/TopObjects/interface/TtSemiLeptonicEvent.h"

/// default constructor
MixedObjectsAnalyzer::MixedObjectsAnalyzer(const edm::ParameterSet& cfg) :
  JetSrc_            (cfg.getParameter<edm::InputTag>("JetSrc"      )),
  METSrc_            (cfg.getParameter<edm::InputTag>("METSrc"      )),
  MuonSrc_           (cfg.getParameter<edm::InputTag>("MuonSrc"     )),
  ElectronSrc_       (cfg.getParameter<edm::InputTag>("ElectronSrc" )),
  GenJetSrc_         (cfg.getParameter<edm::InputTag>("GenJetSrc"   )),
  addGenJetSrc_      (cfg.getParameter<edm::InputTag>("addGenJetSrc")),
  GenMETSrc_         (cfg.getParameter<edm::InputTag>("GenMETSrc"   )),
  GenLepSrc_         (cfg.getParameter<edm::InputTag>("GenLepSrc"   )),
  ingenPS_           (cfg.getParameter<edm::InputTag>("ingenPS"     )),
  weight_            (cfg.getParameter<edm::InputTag>("weight"      )),
  VertexSrc_         (cfg.getParameter<edm::InputTag>("VertexSrc"   )),
  semiLepEvt_        (cfg.getParameter<edm::InputTag>("semiLepEvent")),
  hypoKey_           (cfg.getParameter<std::string>  ("hypoKey"     )),
  btagAlgo_          (cfg.getParameter<std::string>  ("btagAlgo"    )),
  btagDiscr_         (cfg.getParameter<double>       ("btagDiscr"   )),
  addJetPt_          (cfg.getParameter<double>       ("addJetPt"    ))
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
  tree->Branch("weight", &weight, "weight/D");
  
  // different invariant masses
  MuNu4J=-1000;
  ElNu4J=-1000;
  mJJ=-1000; 
  mWJJ=-1000;
  mWFitJJ=-1000;
  mHbb=-1000;         
  tree->Branch("MWJJ"      , &mWJJ      , "MWJJ/D"      );
  tree->Branch("MWFitJJ"   , &mWFitJJ   , "MWFitJJ/D"   );
  tree->Branch("MuNu4J"    , &MuNu4J    , "MuNu4J/D"    );
  tree->Branch("ElNu4J"    , &ElNu4J    , "MuNu4J/D"    );                
  tree->Branch("mHbb"      , &mHbb      , "MHbb/D"      ); 

  // multiplicities
  Nbjets=-1000;
  Njets=-1000;
  NjetsTrue=-1000;
  tree->Branch("Nbjets"    , &Nbjets    , "Nbjets/I"    );
  tree->Branch("Njets"     , &Njets     , "Njets/I"     );
  tree->Branch("NjetsTrue" , &NjetsTrue , "NjetsTrue/I" );
 
  // leading jet which is not associated with the ttbar system
  tree->Branch("leadNonttjetPt" , &leadNonttjetPt , "leadNonttjetPt/D" );   
  tree->Branch("leadNonttjetY"  , &leadNonttjetY  , "leadNonttjetY/D"  );   
  tree->Branch("leadNonttjetEta", &leadNonttjetEta, "leadNonttjetEta/D"); 
  tree->Branch("leadNonttjetPtTrue" , &leadNonttjetPtTrue , "leadNonttjetPtTrue/D" );   
  tree->Branch("leadNonttjetYTrue"  , &leadNonttjetYTrue  , "leadNonttjetYTrue/D"  );   
  tree->Branch("leadNonttjetEtaTrue", &leadNonttjetEtaTrue, "leadNonttjetEtaTrue/D");  
  // m(ttbar+jet)
  tree->Branch("ttbarJetMass"    , &ttbarJetMass    , "ttbarJetMass/D"    ); 
  tree->Branch("ttbarJetMassTrue", &ttbarJetMassTrue, "ttbarJetMassTrue/D"); 
  tree->Branch("rhos"            , &rhos            , "rhos/D"            ); 
  tree->Branch("rhosTrue"        , &rhosTrue        , "rhosTrue/D"        ); 

  // object kinematics to check kinfit shift
  tree->Branch("bqhadPtPre"   ,&bqhadPtPre , "bqhadPtPre/D" ); 
  tree->Branch("bqhadEtaPre"  ,&bqhadEtaPre, "bqhadEtaPre/D"); 
  tree->Branch("bqhadPhiPre"  ,&bqhadPhiPre, "bqhadEtaPre/D"); 
  tree->Branch("bqlepPtPre"   ,&bqlepPtPre , "bqlepPtPre/D" ); 
  tree->Branch("bqlepEtaPre"  ,&bqlepEtaPre, "bqlepEtaPre/D"); 
  tree->Branch("bqlepPhiPre"  ,&bqlepPhiPre, "bqlepPhiPre/D"); 
  tree->Branch("lqPtPre"      ,&lqPtPre    , "lqPtPre/D"    ); 
  tree->Branch("lqEtaPre"     ,&lqEtaPre   , "lqEtaPre/D"   ); 
  tree->Branch("lqPhiPre"     ,&lqPhiPre   , "lqPhiPre/D"   ); 
  tree->Branch("lqbarPtPre"   ,&lqbarPtPre , "lqbarPtPre/D" ); 
  tree->Branch("lqbarEtaPre"  ,&lqbarEtaPre, "lqbarEtaPre/D"); 
  tree->Branch("lqbarPhiPre"  ,&lqbarPhiPre, "lqbarPhiPre/D"); 
  tree->Branch("bqhadPtFit"   ,&bqhadPtFit , "bqhadPtFit/D" ); 
  tree->Branch("bqhadEtaFit"  ,&bqhadEtaFit, "bqhadEtaFit/D"); 
  tree->Branch("bqhadPhiFit"  ,&bqhadPhiFit, "bqhadPhiFit/D"); 
  tree->Branch("bqlepPtFit"   ,&bqlepPtFit , "bqlepPtFit/D" ); 
  tree->Branch("bqlepEtaFit"  ,&bqlepEtaFit, "bqlepEtaFit/D"); 
  tree->Branch("bqlepPhiFit"  ,&bqlepPhiFit, "bqlepPhiFit/D"); 
  tree->Branch("lqPtFit"      ,&lqPtFit    , "lqPtFit/D"    ); 
  tree->Branch("lqEtaFit"     ,&lqEtaFit   , "lqEtaFit/D"   ); 
  tree->Branch("lqPhiFit"     ,&lqPhiFit   , "lqPhiFit/D"   ); 
  tree->Branch("lqbarPtFit"   ,&lqbarPtFit , "lqbarPtFit/D" ); 
  tree->Branch("lqbarEtaFit"  ,&lqbarEtaFit, "lqbarEtaFit/D"); 
  tree->Branch("lqbarPhiFit"  ,&lqbarPhiFit, "lqbarPhiFit/D"); 
  tree->Branch("nuPtPre"      ,&nuPtPre    , "nuPtPre/D"    ); 
  tree->Branch("nuEtaPre"     ,&nuEtaPre   , "nuEtaPre/D"   ); 
  tree->Branch("nuPhiPre"     ,&nuPhiPre   , "nuEtaPre/D"   ); 
  tree->Branch("nuPtTrue"     ,&nuPtTrue   , "nuPtTrue/D"   ); 
  tree->Branch("nuEtaTrue"    ,&nuEtaTrue  , "nuEtaTrue/D"  ); 
  tree->Branch("nuPhiTrue"    ,&nuPhiTrue  , "nuEtaTrue/D"  ); 
  tree->Branch("nuPtFit"      ,&nuPtFit    , "nuPtFit/D"    ); 
  tree->Branch("nuEtaFit"     ,&nuEtaFit   , "nuEtaFit/D"   ); 
  tree->Branch("nuPhiFit"     ,&nuPhiFit   , "nuEtaFit/D"   ); 
  tree->Branch("lepPtPre"     ,&lepPtPre   , "lepPtPre/D"   ); 
  tree->Branch("lepEtaPre"    ,&lepEtaPre  , "lepEtaPre/D"  ); 
  tree->Branch("lepPhiPre"    ,&lepPhiPre  , "lepEtaPre/D"  );
  tree->Branch("lepPtTrue"    ,&lepPtTrue  , "lepPtTrue/D"  ); 
  tree->Branch("lepEtaTrue"   ,&lepEtaTrue , "lepEtaTrue/D" ); 
  tree->Branch("lepPhiTrue"   ,&lepPhiTrue , "lepEtaTrue/D" );
  tree->Branch("lepPtFit"     ,&lepPtFit   , "lepPtFit/D"   ); 
  tree->Branch("lepEtaFit"    ,&lepEtaFit  , "lepEtaFit/D"  ); 
  tree->Branch("lepPhiFit"    ,&lepPhiFit  , "lepEtaFit/D"  );
  tree->Branch("sumEtPre"     ,&sumEtPre   , "sumEtPre/D"   ); 
  tree->Branch("sumEtTrue"    ,&sumEtTrue  , "sumEtTrue/D"  ); 
  // top and ttbar quantities
  tree->Branch("topPtLepFit"  ,&topPtLepFit , "topPtLepFit/D" );
  tree->Branch("topPtHadFit"  ,&topPtHadFit , "topPtHadFit/D" );
  tree->Branch("topYLepFit"   ,&topYLepFit  , "topYLepFit/D"  );
  tree->Branch("topYHadFit"   ,&topYHadFit  , "topYHadFit/D"  );
  tree->Branch("ttbarMassFit" ,&ttbarMassFit, "ttbarMassFit/D");
  tree->Branch("ttbarYFit"    ,&ttbarYFit   , "ttbarYFit/D"   );
  tree->Branch("ttbarPtFit"   ,&ttbarPtFit  , "ttbarPtFit/D"  );
  tree->Branch("topPtLepTrue"  ,&topPtLepTrue , "topPtLepTrue/D" );
  tree->Branch("topPtHadTrue"  ,&topPtHadTrue , "topPtHadTrue/D" );
  tree->Branch("topYLepTrue"   ,&topYLepTrue  , "topYLepTrue/D"  );
  tree->Branch("topYHadTrue"   ,&topYHadTrue  , "topYHadTrue/D"  );
  tree->Branch("ttbarMassTrue" ,&ttbarMassTrue, "ttbarMassTrue/D");
  tree->Branch("ttbarYTrue"    ,&ttbarYTrue   , "ttbarYTrue/D"   );
  tree->Branch("ttbarPtTrue"   ,&ttbarPtTrue  , "ttbarPtTrue/D"  );

  // nPV
  nPV=-1000;
  tree->Branch("nPV",&nPV, "nPV/D");
  // within visible phase space?
  tree->Branch("inVisPS"       , &inVisPS       , "inVisPS/O"      );

  // histos
  // 1D
  hists_["MuNu4J" ] = fs->make<TH1F>( "MuNu4J"  , "MuNu4J"  , 2500,  0. , 2500 );
  hists_["ElNu4J" ] = fs->make<TH1F>( "ElNu4J"  , "ElNu4J"  , 2500,  0. , 2500 );
  hists_["MJJ"    ] = fs->make<TH1F>( "MJJ"     , "MJJ"     , 2500,  0. , 2500 );        
  hists_["MWJJ"   ] = fs->make<TH1F>( "MWJJ"    , "MWJJ"    , 160 ,  0. , 160  );        
  hists_["MWFitJJ"] = fs->make<TH1F>( "MWFitJJ" , "MWFitJJ" , 160 ,  0. , 160  );       
  hists_["mHbb"   ] = fs->make<TH1F>( "mHbb"    , "mHbb"    , 500 ,  0. , 500  );      
  hists_["mbb"    ] = fs->make<TH1F>( "mbb"     , "mbb"     , 500 ,  0. , 500  );  
  hists_["Nbjets" ] = fs->make<TH1F>( "Nbjets"  , "Nbjets"  , 10  ,  -0.5, 9.5 ); 
  hists_["Njets"  ] = fs->make<TH1F>( "Njets"   , "Njets"   , 15  ,  -0.5, 14.5);  
  hists_["Ngenjets"]= fs->make<TH1F>( "Ngenjets", "Ngenjets", 15  ,  -0.5, 14.5);  
  hists_["leadNonttjetPt" ] = fs->make<TH1F>( "leadNonttjetPt" , "leadNonttjetPt" , 1500, 0 , 1500.);
  hists_["leadNonttjetY"  ] = fs->make<TH1F>( "leadNonttjetY"  , "leadNonttjetY"  , 100 ,-5., 5    );
  hists_["leadNonttjetEta"] = fs->make<TH1F>( "leadNonttjetEta", "leadNonttjetEta", 100 ,-5., 5    );
  hists_["leadNonttjetPtTrue" ] = fs->make<TH1F>( "leadNonttjetPtTrue" , "leadNonttjetPtTrue" , 1500, 0 , 1500.);
  hists_["leadNonttjetYTrue"  ] = fs->make<TH1F>( "leadNonttjetYTrue"  , "leadNonttjetYTrue"  , 100 ,-5., 5    );
  hists_["leadNonttjetEtaTrue"] = fs->make<TH1F>( "leadNonttjetEtaTrue", "leadNonttjetEtaTrue", 100 ,-5., 5    );
  hists_["shiftBqPt"    ] = fs->make<TH1F>( "shiftBqPt" , "shiftBqPt"   , 2000,  -100. , 100 );
  hists_["shiftLqPt"    ] = fs->make<TH1F>( "shiftLqPt" , "shiftLqPt"   , 2000,  -100. , 100 );
  hists_["shiftBqEta"   ] = fs->make<TH1F>( "shiftBqEta", "shiftBqEta"  , 1000,  -1.   , 1.  );
  hists_["shiftLqEta"   ] = fs->make<TH1F>( "shiftLqEta", "shiftLqEta"  , 1000,  -1.   , 1.  );
  hists_["shiftBqPhi"   ] = fs->make<TH1F>( "shiftBqPhi", "shiftBqPhi"  , 1000,  -0.5  , 0.5 );
  hists_["shiftLqPhi"   ] = fs->make<TH1F>( "shiftLqPhi", "shiftLqPhi"  , 1000,  -0.5  , 0.5 );
  hists_["shiftLepPt"   ] = fs->make<TH1F>( "shiftLepPt" , "shiftLepPt" , 2000,  -50.  , 50  );
  hists_["shiftLepEta"  ] = fs->make<TH1F>( "shiftLepEta", "shiftLepEta", 1000,  -0.05 , 0.05);
  hists_["shiftLepPhi"  ] = fs->make<TH1F>( "shiftLepPhi", "shiftLepPhi", 1000,  -0.05 , 0.05);
  hists_["shiftNuPt"    ] = fs->make<TH1F>( "shiftNuPt" , "shiftNuPt"   , 2000,  -200. , 200 );
  hists_["shiftNuEta"   ] = fs->make<TH1F>( "shiftNuEta", "shiftNuEta"  , 1000,  -5.   , 5   );
  hists_["shiftNuPhi"   ] = fs->make<TH1F>( "shiftNuPhi", "shiftNuPhi"  , 1200,  -3.   , 3   );
  hists_["nPV"          ] = fs->make<TH1F>("nPV"          , "nPV"          , 50, 0., 50.);
  hists_["nPVunweighted"] = fs->make<TH1F>("nPVunweighted", "nPVunweighted", 50, 0., 50.);
  hists_["nPV"          ]->GetXaxis()->SetTitle(VertexSrc_.label().c_str());
  hists_["nPVunweighted"]->GetXaxis()->SetTitle(VertexSrc_.label().c_str());
  hists_["rhos"         ] = fs->make<TH1F>("rhos"   , "rhos"   , 110,  0. , 1.1);
  hists_["rhosGen"      ] = fs->make<TH1F>("rhosGen", "rhosGen", 110,  0. , 1.1);

  // 2D
  hists2D_["Njets_"  ] = fs->make<TH2F>( "Njets_" , "Njets_" , 15, -0.5, 14.5, 15, -0.5, 14.5);  
  hists2D_["rhos_"   ] = fs->make<TH2F>( "rhos_"  , "rhos_"  , 110,  0. , 1.1, 110,  0. , 1.1);
}

/// fill variables
void
MixedObjectsAnalyzer::analyze(const edm::Event& event, const edm::EventSetup& iSetup)
{
  // activate debug printout
  bool debug=false;

  // Event
  edm::EventAuxiliary aux = event.eventAuxiliary();
  runNumber             = aux.run();
  luminosityBlockNumber = aux.luminosityBlock();
  eventNumber           = aux.event();

  if(debug) std::cout << runNumber << ":" << luminosityBlockNumber << ":" << eventNumber << std::endl;

  edm::Handle<edm::View< pat::MET > > MET_h;
  event.getByLabel(METSrc_, MET_h);
  
  edm::Handle<edm::View< pat::Muon > > muons_h;
  event.getByLabel(MuonSrc_, muons_h);
  
  edm::Handle<edm::View< pat::Electron > > electrons_h;
  event.getByLabel(ElectronSrc_, electrons_h);
  
  edm::Handle<edm::View< pat::Jet > > jets_h;
  event.getByLabel(JetSrc_, jets_h);
  
  edm::Handle<edm::View< reco::GenJet > > genJets_h;
  event.getByLabel(GenJetSrc_, genJets_h);

  edm::Handle<edm::View< reco::GenJet > > addGenJets_h;
  event.getByLabel(addGenJetSrc_, addGenJets_h);

  edm::Handle<edm::View< reco::GenMET > > genMET_h;
  event.getByLabel(GenMETSrc_, genMET_h);
  
  edm::Handle<edm::View< reco::GenParticle > > genLep_h;
  event.getByLabel(GenLepSrc_, genLep_h);
  
  edm::Handle<std::vector<reco::Vertex> > vertecies_h;
  event.getByLabel(VertexSrc_, vertecies_h);
  
  edm::Handle<double> weight_h;
  event.getByLabel(weight_, weight_h);

  edm::Handle<TtSemiLeptonicEvent> semiLepEvt_h;
  event.getByLabel(semiLepEvt_, semiLepEvt_h);

  edm::Handle<bool > visPS;
  if(genLep_h.isValid()) event.getByLabel(ingenPS_, visPS);
  inVisPS=!genLep_h.isValid()||!*visPS ? false : true;
  
  // event weight
  weight = weight_h.isValid() ? *weight_h : 1.;

  // information concerning PU/NPV   
  nPV = vertecies_h.isValid() ? vertecies_h->size() : -1000;
  hists_["nPV"          ]->Fill(nPV, weight);
  hists_["nPVunweighted"]->Fill(nPV, 1.    );
  
  // collect information from KinFitHypothesis
  int lepBIndex=-1, hadBIndex=-1, lightQIndex=-1, lightQBarIndex=-1;
  bqhadPtFit=bqhadEtaFit=bqhadPhiFit=bqlepPtFit=bqlepEtaFit=bqlepPhiFit=lqPtFit=lqEtaFit=lqPhiFit=lqbarPtFit=lqbarEtaFit=lqbarPhiFit=-1000;
  lepPtFit=lepEtaFit=lepPhiFit=lepPtTrue=lepEtaTrue=lepPhiTrue=nuPtFit=nuEtaFit=nuPhiFit=nuPtTrue=nuEtaTrue=nuPhiTrue=-1000;
  if( semiLepEvt_h.isValid()&&semiLepEvt_h->isHypoValid(hypoKey_) ){
    // jet indices
    lepBIndex      = semiLepEvt_h->jetLeptonCombination(hypoKey_)[TtSemiLepEvtPartons::LepB     ];
    hadBIndex      = semiLepEvt_h->jetLeptonCombination(hypoKey_)[TtSemiLepEvtPartons::HadB     ];
    lightQIndex    = semiLepEvt_h->jetLeptonCombination(hypoKey_)[TtSemiLepEvtPartons::LightQ   ];
    lightQBarIndex = semiLepEvt_h->jetLeptonCombination(hypoKey_)[TtSemiLepEvtPartons::LightQBar];
    // jet kinematics after fit
    bqhadPtFit  =semiLepEvt_h->hadronicDecayB(hypoKey_)->pt();
    bqhadEtaFit =semiLepEvt_h->hadronicDecayB(hypoKey_)->eta();
    bqhadPhiFit =semiLepEvt_h->hadronicDecayB(hypoKey_)->phi();
    bqlepPtFit  =semiLepEvt_h->leptonicDecayB(hypoKey_)->pt();
    bqlepEtaFit =semiLepEvt_h->leptonicDecayB(hypoKey_)->eta();
    bqlepPhiFit =semiLepEvt_h->leptonicDecayB(hypoKey_)->phi();
    lqPtFit     =semiLepEvt_h->hadronicDecayQuark(hypoKey_)->pt();
    lqEtaFit    =semiLepEvt_h->hadronicDecayQuark(hypoKey_)->eta();
    lqPhiFit    =semiLepEvt_h->hadronicDecayQuark(hypoKey_)->phi();
    lqbarPtFit  =semiLepEvt_h->hadronicDecayQuarkBar(hypoKey_)->pt();
    lqbarEtaFit =semiLepEvt_h->hadronicDecayQuarkBar(hypoKey_)->eta();
    lqbarPhiFit =semiLepEvt_h->hadronicDecayQuarkBar(hypoKey_)->phi();
    lepPtFit  =semiLepEvt_h->singleLepton(hypoKey_)->pt();
    lepEtaFit =semiLepEvt_h->singleLepton(hypoKey_)->eta();
    lepPhiFit =semiLepEvt_h->singleLepton(hypoKey_)->phi();
    nuPtFit   =semiLepEvt_h->singleNeutrino(hypoKey_)->pt();
    nuEtaFit  =semiLepEvt_h->singleNeutrino(hypoKey_)->eta();
    nuPhiFit  =semiLepEvt_h->singleNeutrino(hypoKey_)->phi();
  }
  if( semiLepEvt_h.isValid()&&semiLepEvt_h->singleLepton()&&semiLepEvt_h->singleNeutrino() ){
    lepPtTrue =semiLepEvt_h->singleLepton()->pt();
    lepEtaTrue=semiLepEvt_h->singleLepton()->eta();
    lepPhiTrue=semiLepEvt_h->singleLepton()->phi();
    nuPtTrue  =semiLepEvt_h->singleNeutrino()->pt();
    nuEtaTrue =semiLepEvt_h->singleNeutrino()->eta();
    nuPhiTrue =semiLepEvt_h->singleNeutrino()->phi();
  }

  // invariant masses (measure for mttbar)
  MuNu4J=-1000;
  ElNu4J=-1000;
  if(jets_h.isValid()&&MET_h.isValid()&&muons_h.isValid()&&electrons_h.isValid()){
    if(jets_h->size()>3&&MET_h->size()>0){
      if(muons_h->size()>0){
	MuNu4J=(muons_h->at(0).p4()+MET_h->at(0).p4()+jets_h->at(0).p4()+jets_h->at(1).p4()+jets_h->at(2).p4()+jets_h->at(3).p4()).mass();
	hists_["MuNu4J"]->Fill(MuNu4J, weight);
	if(debug) std::cout << "mu: " << MuNu4J << std::endl;
      }
      if(electrons_h->size()>0){ 
	ElNu4J=(electrons_h->at(0).p4()+MET_h->at(0).p4()+jets_h->at(0).p4()+jets_h->at(1).p4()+jets_h->at(2).p4()+jets_h->at(3).p4()).mass();
	hists_["ElNu4J"]->Fill(ElNu4J, weight);
	if(debug) std::cout << "el: " << ElNu4J << std::endl;
      }
    }
  }
  mJJ=-1000;
  mWJJ=-1000;
  mWFitJJ=-1000;
  mHbb=-1000;
  BindexA=-1000;
  BindexB=-1000;
  BindexC=-1000;
  BindexD=-1000;
  Nbjets=-1000;
  Njets=-1000;
  leadNonttjetIX=-1;
  leadNonttjetPt=leadNonttjetY=leadNonttjetEta=-1000;
  bqhadPtPre=bqhadEtaPre=bqhadPhiPre=bqlepPtPre=bqlepEtaPre=bqlepPhiPre=lqPtPre=lqEtaPre=lqPhiPre=lqbarPtPre=lqbarEtaPre=lqbarPhiPre=-1000;
  // loop jets
  if(jets_h.isValid()){
    Nbjets=0;
    Njets=0;
    for(edm::View< pat::Jet>::const_iterator jetsA=jets_h->begin(); jetsA!=jets_h->end(); ++jetsA){
      int tempindex=jetsA-jets_h->begin();
      // check if kinfit information is available
      if(semiLepEvt_h.isValid()&&semiLepEvt_h->isHypoValid(hypoKey_)){
	// jet kinematics before the fit
	if(tempindex==hadBIndex){
	  bqhadPtPre =jetsA->pt();
	  bqhadEtaPre=jetsA->eta();
	  bqhadPhiPre=jetsA->phi();
	}
	else if(tempindex==lepBIndex){
	  bqlepPtPre =jetsA->pt();
	  bqlepEtaPre=jetsA->eta();
	  bqlepPhiPre=jetsA->phi();
	}
	else if(tempindex==lightQIndex){
	  lqPtPre =jetsA->pt();
	  lqEtaPre=jetsA->eta();
	  lqPhiPre=jetsA->phi();
	}
	else if(tempindex==lightQBarIndex){
	  lqbarPtPre =jetsA->pt();
	  lqbarEtaPre=jetsA->eta();
	  lqbarPhiPre=jetsA->phi();
	}
	// search for leading non ttbar jet within the 5 leading jets
	if(tempindex<=5&&tempindex!=lepBIndex&&tempindex!=hadBIndex&&tempindex!=lightQIndex&&tempindex!=lightQBarIndex){
	  leadNonttjetIX=tempindex;
	  leadNonttjetPt=jetsA->pt();
	  leadNonttjetY =jetsA->rapidity();
	  leadNonttjetEta =jetsA->eta();
	}
      }
      // count jet multiplicity
      ++Njets;
      // count b jet multiplicity (CSVM algo)
      if(jetsA->bDiscriminator(btagAlgo_) >btagDiscr_){
	++Nbjets;
	// store b-jet index 
	if(BindexA==-1) BindexA=tempindex;
	else if(BindexB==-1) BindexB=tempindex;
	else if(BindexC==-1) BindexC=tempindex;
	else if(BindexD==-1) BindexD=tempindex;
      }
      // 2nd loop for jet-jet masses
      for(edm::View< pat::Jet>::const_iterator jetsB=jets_h->begin(); jetsB!=jets_h->end(); ++jetsB){      
	// take care of double counting
	if(jetsB>jetsA){
	  // a) invariant jet-jet mass for all combinations
	  mJJ=(jetsA->p4()+jetsB->p4()).mass();
	  // b) for combination closest to w mass
	  if(mWJJ==-1) mWJJ=mJJ;
	  else if(std::abs(mJJ-80.4)<std::abs(mWJJ-80.4)) mWJJ=mJJ;
	  // c) for invariant bjet-bjet masses
	  if(jetsA->bDiscriminator(btagAlgo_) >btagDiscr_&&jetsB->bDiscriminator(btagAlgo_) >btagDiscr_){
	    hists_["mbb"]->Fill((jetsA->p4()+jetsB->p4()).mass(), weight);
	  }
	  // d) for all invariant masses
	  hists_["MJJ"]->Fill(mJJ, weight);
	}
      }
    }
  }
  //std::cout << "loping genjets" << std::endl;

  // calculate N(genjets)
  NjetsTrue=-1000;
  if(genJets_h.isValid()&&inVisPS){
    NjetsTrue=0;
    // loop gen Jets
    for(edm::View< reco::GenJet >::const_iterator genJets=genJets_h->begin(); genJets!=genJets_h->end(); ++genJets){
      if(genJets->pt()>30&&genJets->eta()<2.4){
	++NjetsTrue;
      }
    }
  }

  // fill multiplicity plots
  if(Nbjets>-1   ) hists_["Nbjets"]->Fill(Nbjets, weight);
  hists_["Nbjets"]->GetXaxis()->SetTitle("N("+TString(btagAlgo_)+" b-jets)");
  if(Njets>-1    ) hists_["Njets" ]->Fill(Njets , weight);
  if(debug) std::cout << "fill gen jet plot" << std::endl;
  if(NjetsTrue>-1) hists_["Ngenjets"]->Fill(NjetsTrue, weight); 
  if(debug) std::cout << "fill gen-reco jet plot" << std::endl;
  if(Njets>-1    ) hists2D_["Njets_"]->Fill(NjetsTrue, Njets, weight); 
  if(debug) std::cout << "done" << std::endl;

  // lead non ttbar jet
  if(leadNonttjetIX!=-1){
    hists_["leadNonttjetPt" ]->Fill(leadNonttjetPt , weight);
    hists_["leadNonttjetY"  ]->Fill(leadNonttjetY  , weight);
    hists_["leadNonttjetEta"]->Fill(leadNonttjetEta, weight);
  }
  
  // jet-jet invariant mass closest to w mass
  if(mWJJ>0   ) hists_["MWJJ"   ]->Fill(mWJJ, weight);   
  // jet-jet invariant mass from jets associated to W decay by kinfit
  if(lightQIndex!=-1&&lightQBarIndex!=-1) mWFitJJ=(jets_h->at(lightQIndex).p4()+jets_h->at(lightQBarIndex).p4()).mass();
  if(mWFitJJ>0) hists_["MWFitJJ"]->Fill(mWFitJJ, weight);  

  // bjet-bjet invariant mass for bjet pair comming NOT from ttbar decay (using kinfit information) in 4 b events
  if(Nbjets>=4&&lepBIndex!=-1&&hadBIndex!=-1){
    // search non ttbar bjets
    int HbbindexA=-1, HbbindexB=-1;
    if(BindexA!=lepBIndex&&BindexA!=hadBIndex){
      if(HbbindexA==-1) HbbindexA=BindexA;
      else if(HbbindexB==-1) HbbindexB=BindexA;
    }
    if(BindexB!=lepBIndex&&BindexB!=hadBIndex){
      if(HbbindexA==-1) HbbindexA=BindexB;
      else if(HbbindexB==-1) HbbindexB=BindexB;
    }
    if(BindexC!=lepBIndex&&BindexC!=hadBIndex){
      if(HbbindexA==-1) HbbindexA=BindexC;
      else if(HbbindexB==-1) HbbindexB=BindexC;
    }
    if(BindexD!=lepBIndex&&BindexD!=hadBIndex){
      if(HbbindexA==-1) HbbindexA=BindexD;
      else if(HbbindexB==-1) HbbindexB=BindexD;
    }
    if(HbbindexA!=-1&&HbbindexB!=-1) mHbb=(jets_h->at(HbbindexA).p4()+jets_h->at(HbbindexB).p4()).mass();
    if(mHbb>-1) hists_["mHbb"]->Fill(mHbb, weight); 
  }
  
  // fill kinfit shift histos
  if(bqhadPtFit!=-1000&&bqhadPtPre!=-1000) hists_["shiftBqPt" ]->Fill( bqhadPtFit-bqhadPtPre, weight);
  if(bqlepPtFit!=-1000&&bqlepPtPre!=-1000) hists_["shiftBqPt" ]->Fill( bqlepPtFit-bqlepPtPre, weight);
  if(lqPtFit!=-1000&&lqPtPre!=-1000&&lqbarPtFit!=-1000&&lqbarPtPre!=-1000){
    // consider ambiguity for light jets
    if(std::abs(lqPtFit-lqPtPre)+std::abs(lqbarPtFit-lqbarPtPre)<std::abs(lqPtFit-lqbarPtPre)+std::abs(lqbarPtFit-lqPtPre)){
      hists_["shiftLqPt"    ]->Fill( lqPtFit-lqPtPre, weight);
      hists_["shiftLqPt"    ]->Fill( lqbarPtFit-lqbarPtPre, weight);
    }
    else{
      hists_["shiftLqPt"    ]->Fill( lqPtFit-lqbarPtPre, weight);
      hists_["shiftLqPt"    ]->Fill( lqbarPtFit-lqPtPre, weight);
    }
  }
  if(bqhadEtaFit!=-1000&&bqhadEtaPre!=-1000) hists_["shiftBqEta" ]->Fill( bqhadEtaFit-bqhadEtaPre, weight);
  if(bqlepEtaFit!=-1000&&bqlepEtaPre!=-1000) hists_["shiftBqEta" ]->Fill( bqlepEtaFit-bqlepEtaPre, weight);
  if(lqEtaFit!=-1000&&lqEtaPre!=-1000&&lqbarEtaFit!=-1000&&lqbarEtaPre!=-1000){
    // consider ambiguity for light jets
    if(std::abs(lqEtaFit-lqEtaPre)+std::abs(lqbarEtaFit-lqbarEtaPre)<std::abs(lqEtaFit-lqbarEtaPre)+std::abs(lqbarEtaFit-lqEtaPre)){
      hists_["shiftLqEta"    ]->Fill( lqEtaFit-lqEtaPre, weight);
      hists_["shiftLqEta"    ]->Fill( lqbarEtaFit-lqbarEtaPre, weight);
    }
    else{
      hists_["shiftLqEta"    ]->Fill( lqEtaFit-lqbarEtaPre, weight);
      hists_["shiftLqEta"    ]->Fill( lqbarEtaFit-lqEtaPre, weight);
    }
  }
  if(bqhadPhiFit!=-1000&&bqhadPhiPre!=-1000) hists_["shiftBqPhi" ]->Fill( modTwoPi(bqhadPhiFit-bqhadPhiPre), weight);
  if(bqlepPhiFit!=-1000&&bqlepPhiPre!=-1000) hists_["shiftBqPhi" ]->Fill( modTwoPi(bqlepPhiFit-bqlepPhiPre), weight);
  if(lqPhiFit!=-1000&&lqPhiPre!=-1000&&lqbarPhiFit!=-1000&&lqbarPhiPre!=-1000){
    // consider ambiguity for light jets
    if(std::abs(modTwoPi(lqPhiFit-lqPhiPre))+std::abs(modTwoPi(lqbarPhiFit-lqbarPhiPre))<std::abs(modTwoPi(lqPhiFit-lqbarPhiPre))+std::abs(modTwoPi(lqbarPhiFit-lqPhiPre))){
      hists_["shiftLqPhi"    ]->Fill( modTwoPi(lqPhiFit-lqPhiPre), weight);
      hists_["shiftLqPhi"    ]->Fill( modTwoPi(lqbarPhiFit-lqbarPhiPre), weight);
    }
    else{
      hists_["shiftLqPhi"    ]->Fill( modTwoPi(lqPhiFit-lqbarPhiPre), weight);
      hists_["shiftLqPhi"    ]->Fill( modTwoPi(lqbarPhiFit-lqPhiPre), weight);
    }
  }
  lepPtPre=lepEtaPre=lepPhiPre=nuPtPre=nuEtaPre=nuPhiPre=sumEtPre=sumEtTrue=-1000;
  if(muons_h.isValid()&&(muons_h->end()-muons_h->begin()>0)){
    lepPtPre  =muons_h->at(0).pt();
    lepEtaPre =muons_h->at(0).eta();
    lepPhiPre =muons_h->at(0).phi();
  }
  else if(electrons_h.isValid()&&(electrons_h->end()-electrons_h->begin()>0)){
    lepPtPre  =electrons_h->at(0).pt();
    lepEtaPre =electrons_h->at(0).eta();
    lepPhiPre =electrons_h->at(0).phi();
  }
  if(MET_h.isValid()&&(MET_h->end()-MET_h->begin()>0)){
    nuPtPre   =MET_h->at(0).pt();
    nuEtaPre  =MET_h->at(0).eta();
    nuPhiPre  =MET_h->at(0).phi();
    sumEtPre  =MET_h->at(0).sumEt();
    if(MET_h->begin()->genMET()&&inVisPS){
      sumEtTrue=MET_h->begin()->genMET()->sumEt();
    }
  }
  if(lepPtFit!=-1000&&lepPtPre!=-1000  ) hists_["shiftLepPt" ]->Fill( lepPtFit -lepPtPre , weight);  
  if(nuPtFit!=-1000 &&nuPtPre!=-1000   ) hists_["shiftNuPt"  ]->Fill( nuPtFit  -nuPtPre  , weight);
  if(lepEtaFit!=-1000&&lepEtaPre!=-1000) hists_["shiftLepEta"]->Fill( lepEtaFit-lepEtaPre, weight);  
  if(nuEtaFit!=-1000 &&nuEtaPre!=-1000 ) hists_["shiftNuEta" ]->Fill( nuEtaFit -nuEtaPre , weight);
  if(lepPhiFit!=-1000&&lepPhiPre!=-1000) hists_["shiftLepPhi"]->Fill( modTwoPi(lepPhiFit-lepPhiPre), weight);  
  if(nuPhiFit!=-1000 &&nuPhiPre!=-1000 ) hists_["shiftNuPhi" ]->Fill( modTwoPi( nuPhiFit -nuPhiPre), weight);

  // top and ttbar distributions
  // a) reco
  topPtLepFit=topPtHadFit=topYLepFit=topYHadFit=ttbarMassFit=ttbarYFit=ttbarPtFit=-1000;
  if(semiLepEvt_h.isValid()&&semiLepEvt_h->isHypoValid(hypoKey_) ){
    topPtLepFit=semiLepEvt_h->leptonicDecayTop(hypoKey_)->pt();
    topPtHadFit=semiLepEvt_h->hadronicDecayTop(hypoKey_)->pt();
    topYLepFit =semiLepEvt_h->leptonicDecayTop(hypoKey_)->rapidity();
    topYHadFit =semiLepEvt_h->hadronicDecayTop(hypoKey_)->rapidity();
    ttbarMassFit=(semiLepEvt_h->hadronicDecayTop(hypoKey_)->p4()+semiLepEvt_h->leptonicDecayTop(hypoKey_)->p4()).mass();
    ttbarYFit   =(semiLepEvt_h->hadronicDecayTop(hypoKey_)->p4()+semiLepEvt_h->leptonicDecayTop(hypoKey_)->p4()).Rapidity();
    ttbarPtFit  =(semiLepEvt_h->hadronicDecayTop(hypoKey_)->p4()+semiLepEvt_h->leptonicDecayTop(hypoKey_)->p4()).pt();
  }
  // b) gen
  topPtLepTrue=topPtHadTrue=topYLepTrue=topYHadTrue=ttbarMassTrue=ttbarYTrue=ttbarPtTrue=-1000;
  if(semiLepEvt_h.isValid()&&semiLepEvt_h->leptonicDecayTop()&&semiLepEvt_h->hadronicDecayTop()){  
    topPtLepTrue=semiLepEvt_h->leptonicDecayTop()->pt();
    topPtHadTrue=semiLepEvt_h->hadronicDecayTop()->pt();
    topYLepTrue =semiLepEvt_h->leptonicDecayTop()->rapidity();
    topYHadTrue =semiLepEvt_h->hadronicDecayTop()->rapidity();
    ttbarMassTrue=(semiLepEvt_h->hadronicDecayTop()->p4()+semiLepEvt_h->leptonicDecayTop()->p4()).mass();
    ttbarYTrue   =(semiLepEvt_h->hadronicDecayTop()->p4()+semiLepEvt_h->leptonicDecayTop()->p4()).Rapidity();
    ttbarPtTrue  =(semiLepEvt_h->hadronicDecayTop()->p4()+semiLepEvt_h->leptonicDecayTop()->p4()).pt();
  }


  // tt+jet distribution
  // scale value chosen
  double mtop=170.0;
  // initialize tree entries
  ttbarJetMass=ttbarJetMassTrue=-1000;
  rhos=rhosTrue=-1000;
  // calculate quantity
  if(semiLepEvt_h.isValid()){
    if(debug) std::cout << "hypothesis valid" << std::endl;
    // gen level
    if(semiLepEvt_h->hadronicDecayTop()&&semiLepEvt_h->leptonicDecayTop()&&inVisPS){
      if(addGenJets_h.isValid()&&(addGenJets_h->size()>0)&&inVisPS){
	ttbarJetMassTrue=(semiLepEvt_h->hadronicDecayTop()->p4()+semiLepEvt_h->leptonicDecayTop()->p4()+(addGenJets_h->at(0)).p4()).mass();
	rhosTrue=2*mtop/ttbarJetMassTrue;
	if(debug) std::cout << "ttbarJetMassTrue=" << ttbarJetMassTrue << std::endl;
      }
      else if(debug){
	std::cout << "addGenJets_h.isValid(): " << addGenJets_h.isValid() << std::endl;
	std::cout << "addGenJets_h->size(): " << addGenJets_h->size() << std::endl;
	if(addGenJets_h->size()>0) std::cout << "addGenJets_h->at(0).pt(): " << addGenJets_h->at(0).pt() << std::endl;
      }
    }
    // reco level
    if(semiLepEvt_h->hadronicDecayTop(hypoKey_)&&semiLepEvt_h->leptonicDecayTop(hypoKey_)){
      if( (semiLepEvt_h->isHypoValid(hypoKey_))&&(leadNonttjetIX!=-1) ){
	ttbarJetMass=(semiLepEvt_h->hadronicDecayTop(hypoKey_)->p4()+semiLepEvt_h->leptonicDecayTop(hypoKey_)->p4()+(jets_h->at(leadNonttjetIX)).p4()).mass();
	rhos=2*mtop/ttbarJetMass;
	if(debug) std::cout << "ttbarJetMass=" << ttbarJetMass << std::endl;
      }
      else if(debug){
	std::cout << "semiLepEvt_h->isHypoValid(hypoKey_): " << semiLepEvt_h->isHypoValid(hypoKey_) << std::endl;
	std::cout << "leadNonttjetIX: "   << leadNonttjetIX   << std::endl;
	std::cout << "leadNonttjetPt: " << leadNonttjetPt << std::endl;
      }
    }
  }

  if(rhos    !=-1000&&leadNonttjetPt          >addJetPt_) hists_  ["rhos"   ]->Fill( rhos    , weight);
  if(rhosTrue!=-1000&&addGenJets_h->at(0).pt()>addJetPt_) hists_  ["rhosGen"]->Fill( rhosTrue, weight);
  if(rhos    !=-1000&&leadNonttjetPt          >addJetPt_) hists2D_["rhos_"  ]->Fill( rhosTrue, rhos, weight );
  
  leadNonttjetPtTrue=leadNonttjetYTrue=leadNonttjetEtaTrue=-1000;
  if(addGenJets_h.isValid()&&(addGenJets_h->size()>0)&&inVisPS){
    leadNonttjetPtTrue=addGenJets_h->at(0).pt();
    leadNonttjetEtaTrue=addGenJets_h->at(0).eta();
    leadNonttjetYTrue=addGenJets_h->at(0).rapidity();
  }
  // lead non ttbar jet GEN
  if(leadNonttjetPtTrue>=0){
    hists_["leadNonttjetPtTrue" ]->Fill(leadNonttjetPtTrue , weight);
    hists_["leadNonttjetYTrue"  ]->Fill(leadNonttjetYTrue  , weight);
    hists_["leadNonttjetEtaTrue"]->Fill(leadNonttjetEtaTrue, weight);
  }

  tree->Fill();
}

void
MixedObjectsAnalyzer::endJob()
{

}

/// helper funtion to take care that delta phi is < pi
double
MixedObjectsAnalyzer::modTwoPi(double DeltaPhi){
  const double pi=TMath::Pi();
  if(DeltaPhi>pi){
    double output=std::abs(2*pi-std::abs(DeltaPhi));
    if(DeltaPhi>0) output*=-1.;
  }
  return DeltaPhi;
}


bool
MixedObjectsAnalyzer::findAncestor(const reco::Candidate* cand, TString decaychain){
  //static int calls = 0;
  //int calls = decaychain.CountChar('<');
  if(cand->numberOfMothers()==0){
    decaychain.Remove(decaychain.Sizeof()-3, 2);
    //resetCount=true;
    //std::cout << decaychain << std::endl;
    // check for light quark candiates hadrons
    TString decaychain2=decaychain;
    int index=decaychain.Index("6");
    decaychain2.Remove(index+1,decaychain.Sizeof()-index-1);
    if((decaychain.Contains("1<-24<-6")&&!decaychain2.Contains("21"))||
       (decaychain.Contains("2<-24<-6")&&!decaychain2.Contains("21"))||
       (decaychain.Contains("3<-24<-6")&&!decaychain2.Contains("21"))||
       (decaychain.Contains("4<-24<-6")&&!decaychain2.Contains("21"))||
       (decaychain.Contains("5<-6")&&!decaychain2.Contains("21")
	&&(decaychain.Contains("511")||
	   decaychain.Contains("521")||
	   decaychain.Contains("513")||
	   decaychain.Contains("523")||
	   decaychain.Contains("515")||
	   decaychain.Contains("525")||
	   decaychain.Contains("531")||
	   decaychain.Contains("533")||
	   decaychain.Contains("535")||
	   decaychain.Contains("541")||
	   decaychain.Contains("543")||
	   decaychain.Contains("545")||
	   decaychain.Contains("551")||
	   decaychain.Contains("553")||
	   decaychain.Contains("555")||
	   decaychain.Contains("557")||
	   decaychain.Contains("5122")||
	   decaychain.Contains("5112")||
	   decaychain.Contains("5212")||
	   decaychain.Contains("5222")||
	   decaychain.Contains("5114")||
	   decaychain.Contains("5214")||
	   decaychain.Contains("5132")||
	   decaychain.Contains("5232")||
	   decaychain.Contains("5312")||
	   decaychain.Contains("5322")||
	   decaychain.Contains("5314")||
	   decaychain.Contains("5324")||
	   decaychain.Contains("5332")||
	   decaychain.Contains("5334")||
	   decaychain.Contains("5142")||
	   decaychain.Contains("5242")||
	   decaychain.Contains("5412")||
	   decaychain.Contains("5422")||
	   decaychain.Contains("5414")||
	   decaychain.Contains("5424")||
	   decaychain.Contains("5342")||
	   decaychain.Contains("5432")||
	   decaychain.Contains("5434")||
	   decaychain.Contains("5442")||
	   decaychain.Contains("5444")||
	   decaychain.Contains("5512")||
	   decaychain.Contains("5522")||
	   decaychain.Contains("5514")||
	   decaychain.Contains("5524")||
	   decaychain.Contains("5532")||
	   decaychain.Contains("5534")||
	   decaychain.Contains("5542")||
	   decaychain.Contains("5544")||
	   decaychain.Contains("5554")
	   ))
       ){
      //std::cout << "possible ttbar jet!" << std::endl;
      std::cout << decaychain << std::endl;
      return true;
    }
  }
  
  // pdgid original particle
  //std::cout.width(5*calls);
  //if(calls==0) std::cout << " " << cand->pdgId() << "(" << cand->numberOfMothers() << " ancestors)" << std::endl;
  // check mothers
  if(cand->numberOfMothers()>0){
    
    // pdgid mothers
    //for(unsigned int numMother=0; numMother<cand->numberOfMothers(); ++numMother){
      //if(numMother==0) { std::cout.width(5*calls); std::cout << " "; std::cout << " <- " << cand->mother(numMother)->pdgId(); }
      //else             { std::cout << ", " << cand->mother(numMother)->pdgId(); }
      //if(numMother==cand->numberOfMothers()-1) std::cout << std::endl; 
      
    //}
    // bubble up mothers
    for(unsigned int numMother=0; numMother<cand->numberOfMothers(); ++numMother){
      TString newchain=decaychain;
      newchain+=std::abs(cand->mother(numMother)->pdgId());
      newchain+="<-";
      findAncestor(cand->mother(numMother), newchain);
    }
  }
  return false;
}


#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( MixedObjectsAnalyzer );
