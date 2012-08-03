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
  JetSrc_            (cfg.getParameter<edm::InputTag>("JetSrc"     )),
  METSrc_            (cfg.getParameter<edm::InputTag>("METSrc"     )),
  MuonSrc_           (cfg.getParameter<edm::InputTag>("MuonSrc"    )),
  ElectronSrc_       (cfg.getParameter<edm::InputTag>("ElectronSrc")),
  weight_            (cfg.getParameter<edm::InputTag>("weight"     )),
  VertexSrc_         (cfg.getParameter<edm::InputTag>("VertexSrc"  )),
  semiLepEvt_        (cfg.getParameter<edm::InputTag>("semiLepEvent")),
  hypoKey_           (cfg.getParameter<std::string>  ("hypoKey"     )),
  btagAlgo_          (cfg.getParameter<std::string>  ("btagAlgo"    )),
  btagDiscr_         (cfg.getParameter<double>       ("btagDiscr"   ))
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
  
  // different invariant masses
  MuNu4J=-1;
  ElNu4J=-1;
  mJJ=-1; 
  mWJJ=-1;
  mWFitJJ=-1;
  mHbb=-1;         
  tree->Branch("MWJJ"      , &mWJJ      , "MWJJ/D"      );
  tree->Branch("MWFitJJ"   , &mWFitJJ   , "MWFitJJ/D"   );
  tree->Branch("MuNu4J"    , &MuNu4J    , "MuNu4J/D"    );
  tree->Branch("ElNu4J"    , &ElNu4J    , "MuNu4J/D"    );                
  tree->Branch("mHbb"      , &mHbb      , "MHbb/D"      ); 

  // multiplicities
  Nbjets=-1;
  Njets=-1;
  tree->Branch("Nbjets"    , &Nbjets    , "Nbjets/I"    );              
  tree->Branch("Njets"     , &Njets     , "Njets/I"     );  
 
  // leading jet which is not associated with the ttbar system
  leadNonttjetPt=leadNonttjetY=leadNonttjetEta=-999;
  tree->Branch("leadNonttjetPt" , &leadNonttjetPt , "leadNonttjetPt/D" );   
  tree->Branch("leadNonttjetY"  , &leadNonttjetY  , "leadNonttjetY/D"  );   
  tree->Branch("leadNonttjetEta", &leadNonttjetEta, "leadNonttjetEta/D");   
  
  // object kinematics to check kinfit shift
  bqhadPtPre=bqhadEtaPre=bqhadPhiPre=bqlepPtPre=bqlepEtaPre=bqlepPhiPre=lqPtPre=lqEtaPre=lqPhiPre=lqbarPtPre=lqbarEtaPre=lqbarPhiPre=bqhadPtFit=bqhadEtaFit=bqhadPhiFit=bqlepPtFit=bqlepEtaFit=bqlepPhiFit=lqPtFit=lqEtaFit=lqPhiFit=lqbarPtFit=lqbarEtaFit=lqbarPhiFit=-999;
  tree->Branch("bqhadPtPre"      ,&bqhadPtPre    , "bqhadPtPre/D"    ); 
  tree->Branch("bqhadEtaPre"     ,&bqhadEtaPre   , "bqhadEtaPre/D"   ); 
  tree->Branch("bqhadPhiPre"     ,&bqhadPhiPre   , "bqhadEtaPre/D"   ); 
  tree->Branch("bqlepPtPre"   ,&bqlepPtPre , "bqlepPtPre/D" ); 
  tree->Branch("bqlepEtaPre"  ,&bqlepEtaPre, "bqlepEtaPre/D"); 
  tree->Branch("bqlepPhiPre"  ,&bqlepPhiPre, "bqlepPhiPre/D"); 
  tree->Branch("lqPtPre"      ,&lqPtPre    , "lqPtPre/D"    ); 
  tree->Branch("lqEtaPre"     ,&lqEtaPre   , "lqEtaPre/D"   ); 
  tree->Branch("lqPhiPre"     ,&lqPhiPre   , "lqPhiPre/D"   ); 
  tree->Branch("lqbarPtPre"   ,&lqbarPtPre , "lqbarPtPre/D" ); 
  tree->Branch("lqbarEtaPre"  ,&lqbarEtaPre, "lqbarEtaPre/D"); 
  tree->Branch("lqbarPhiPre"  ,&lqbarPhiPre, "lqbarPhiPre/D"); 
  tree->Branch("bqhadPtFit"      ,&bqhadPtFit    , "bqhadPtFit/D"    ); 
  tree->Branch("bqhadEtaFit"     ,&bqhadEtaFit   , "bqhadEtaFit/D"   ); 
  tree->Branch("bqhadPhiFit"     ,&bqhadPhiFit   , "bqhadPhiFit/D"   ); 
  tree->Branch("bqlepPtFit"   ,&bqlepPtFit , "bqlepPtFit/D" ); 
  tree->Branch("bqlepEtaFit"  ,&bqlepEtaFit, "bqlepEtaFit/D"); 
  tree->Branch("bqlepPhiFit"  ,&bqlepPhiFit, "bqlepPhiFit/D"); 
  tree->Branch("lqPtFit"      ,&lqPtFit    , "lqPtFit/D"    ); 
  tree->Branch("lqEtaFit"     ,&lqEtaFit   , "lqEtaFit/D"   ); 
  tree->Branch("lqPhiFit"     ,&lqPhiFit   , "lqPhiFit/D"   ); 
  tree->Branch("lqbarPtFit"   ,&lqbarPtFit , "lqbarPtFit/D" ); 
  tree->Branch("lqbarEtaFit"  ,&lqbarEtaFit, "lqbarEtaFit/D"); 
  tree->Branch("lqbarPhiFit"  ,&lqbarPhiFit, "lqbarPhiFit/D"); 
  nuPtPre=nuEtaPre=nuPhiPre=-999;
  tree->Branch("nuPtPre"      ,&nuPtPre    , "nuPtPre/D"    ); 
  tree->Branch("nuEtaPre"     ,&nuEtaPre   , "nuEtaPre/D"   ); 
  tree->Branch("nuPhiPre"     ,&nuPhiPre   , "nuEtaPre/D"   ); 
  lepPtPre=lepEtaPre=lepPhiPre=-999;
  tree->Branch("lepPtPre"      ,&lepPtPre    , "lepPtPre/D"    ); 
  tree->Branch("lepEtaPre"     ,&lepEtaPre   , "lepEtaPre/D"   ); 
  tree->Branch("lepPhiPre"     ,&lepPhiPre   , "lepEtaPre/D"   );

  // histos
  hists_["MuNu4J" ] = fs->make<TH1F>( "MuNu4J"  , "MuNu4J"  , 2500,  0. , 2500 );
  hists_["ElNu4J" ] = fs->make<TH1F>( "ElNu4J"  , "ElNu4J"  , 2500,  0. , 2500 );
  hists_["MJJ"    ] = fs->make<TH1F>( "MJJ"     , "MJJ"     , 2500,  0. , 2500 );        
  hists_["MWJJ"   ] = fs->make<TH1F>( "MWJJ"    , "MWJJ"    , 160 ,  0. , 160  );        
  hists_["MWFitJJ"] = fs->make<TH1F>( "MWFitJJ" , "MWFitJJ" , 160 ,  0. , 160  );       
  hists_["mHbb"   ] = fs->make<TH1F>( "mHbb"    , "mHbb"    , 500 ,  0. , 500  );      
  hists_["mbb"    ] = fs->make<TH1F>( "mbb"     , "mbb"     , 500 ,  0. , 500  );  
  hists_["Nbjets" ] = fs->make<TH1F>( "Nbjets"  , "Nbjets"  , 10  ,  -0.5, 9.5 ); 
  hists_["Njets"  ] = fs->make<TH1F>( "Njets"   , "Njets"   , 15  ,  -0.5, 14.5);   
  hists_["leadNonttjetPt" ] = fs->make<TH1F>( "leadNonttjetPt" , "leadNonttjetPt" , 1500, 0 , 1500.);
  hists_["leadNonttjetY"  ] = fs->make<TH1F>( "leadNonttjetY"  , "leadNonttjetY"  , 100 ,-5., 5    );
  hists_["leadNonttjetEta"] = fs->make<TH1F>( "leadNonttjetEta", "leadNonttjetEta", 100 ,-5., 5    );
  hists_["shiftBqPt"    ] = fs->make<TH1F>( "shiftBqPt" , "shiftBqPt" , 2000,  -1000. , 1000);
  hists_["shiftLqPt"    ] = fs->make<TH1F>( "shiftLqPt" , "shiftLqPt" , 2000,  -1000. , 1000);
  hists_["shiftBqEta"   ] = fs->make<TH1F>( "shiftBqEta", "shiftBqEta", 1000,  -5. , 5);
  hists_["shiftLqEta"   ] = fs->make<TH1F>( "shiftLqEta", "shiftLqEta", 1000,  -5. , 5);
  hists_["shiftBqPhi"   ] = fs->make<TH1F>( "shiftBqPhi", "shiftBqPhi", 1400,  -7  , 7);
  hists_["shiftLqPhi"   ] = fs->make<TH1F>( "shiftLqPhi", "shiftLqPhi", 1400,  -7. , 7);
  hists_["shiftLepPt"   ] = fs->make<TH1F>( "shiftLepPt" , "shiftLepPt" , 2000,  -1000. , 1000);
  hists_["shiftLepEta"  ] = fs->make<TH1F>( "shiftLepEta", "shiftLepEta", 1000,  -5. , 5);
  hists_["shiftLepPhi"  ] = fs->make<TH1F>( "shiftLepPhi", "shiftLepPhi", 1400,  -7. , 7);
  hists_["shiftNuPt"    ] = fs->make<TH1F>( "shiftNuPt" , "shiftNuPt" , 2000,  -1000. , 1000);
  hists_["shiftNuEta"   ] = fs->make<TH1F>( "shiftNuEta", "shiftNuEta", 1000,  -5. , 5);
  hists_["shiftNuPhi"   ] = fs->make<TH1F>( "shiftNuPhi", "shiftNuPhi", 1400,  -7. , 7);
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

  edm::Handle<TtSemiLeptonicEvent> semiLepEvt_h;
  event.getByLabel(semiLepEvt_, semiLepEvt_h);

  // event weight
  weight = weight_h.isValid() ? *weight_h : 1.;

  // collect information from KinFitHypothesis
  int lepBIndex=-1, hadBIndex=-1, lightQIndex=-1, lightQBarIndex=-1;
  bqhadPtFit=bqhadEtaFit=bqhadPhiFit=bqlepPtFit=bqlepEtaFit=bqhadPhiFit=lqPtFit=lqEtaFit=lqPhiFit=lqbarPtFit=lqbarEtaFit=lqbarPhiFit=-999;
  lepPtFit=lepEtaFit=lepPhiFit=nuPtFit=nuEtaFit=nuPhiFit=-999;

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

  mJJ=-1;
  mWJJ=-1;
  mWFitJJ=-1;
  mHbb=-1;
  BindexA=-1;
  BindexB=-1;
  BindexC=-1;
  BindexD=-1;
  Nbjets=0;
  Njets=0;
  leadNonttjet=-1;
  leadNonttjetPt=leadNonttjetY=leadNonttjetEta=-999;
  bqhadPtPre=bqhadEtaPre=bqhadPhiPre=bqlepPtPre=bqlepEtaPre=bqhadPhiPre=lqPtPre=lqEtaPre=lqPhiPre=lqbarPtPre=lqbarEtaPre=lqbarPhiPre=-999;
  // loop jets
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
	leadNonttjet=tempindex;
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
  // fill multiplicity plots
  hists_["Nbjets"]->Fill(Nbjets, weight);
  hists_["Nbjets"]->GetXaxis()->SetTitle("N("+TString(btagAlgo_)+" b-jets)");
  hists_["Njets" ]->Fill(Njets , weight);  

  // lead non ttbar jet
  if(leadNonttjet!=-1){
    hists_["leadNonttjetPt" ]->Fill(leadNonttjetPt , weight);
    hists_["leadNonttjetY"  ]->Fill(leadNonttjetY  , weight);
    hists_["leadNonttjetEta"]->Fill(leadNonttjetEta, weight);
  }
  
  // jet-jet invariant mass closest to w mass
  if(mWJJ!=-1   ) hists_["MWJJ"   ]->Fill(mWJJ, weight);   
  // jet-jet invariant mass from jets associated to W decay by kinfit
  if(lightQIndex!=-1&&lightQBarIndex!=-1) mWFitJJ=(jets_h->at(lightQIndex).p4()+jets_h->at(lightQBarIndex).p4()).mass();
  if(mWFitJJ!=-1) hists_["MWFitJJ"]->Fill(mWFitJJ, weight);  

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
    if(mHbb!=-1) hists_["mHbb"]->Fill(mHbb, weight); 
  }
  
  // fill kinfit shift histos
  if(bqhadPtFit!=-999&&bqhadPtPre!=-999) hists_["shiftBqPt" ]->Fill( bqhadPtFit-bqhadPtPre, weight);
  if(bqlepPtFit!=-999&&bqlepPtPre!=-999) hists_["shiftBqPt" ]->Fill( bqlepPtFit-bqlepPtPre, weight);
  if(lqPtFit!=-999&&lqPtPre!=-999&&lqbarPtFit!=-999&&lqbarPtPre!=-999){
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
  if(bqhadEtaFit!=-999&&bqhadEtaPre!=-999) hists_["shiftBqEta" ]->Fill( bqhadEtaFit-bqhadEtaPre, weight);
  if(bqlepEtaFit!=-999&&bqlepEtaPre!=-999) hists_["shiftBqEta" ]->Fill( bqlepEtaFit-bqlepEtaPre, weight);
  if(lqEtaFit!=-999&&lqEtaPre!=-999&&lqbarEtaFit!=-999&&lqbarEtaPre!=-999){
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
  if(bqhadPhiFit!=-999&&bqhadPhiPre!=-999) hists_["shiftBqPhi" ]->Fill( bqhadPhiFit-bqhadPhiPre, weight);
  if(bqlepPhiFit!=-999&&bqlepPhiPre!=-999) hists_["shiftBqPhi" ]->Fill( bqlepPhiFit-bqlepPhiPre, weight);
  if(lqPhiFit!=-999&&lqPhiPre!=-999&&lqbarPhiFit!=-999&&lqbarPhiPre!=-999){
    // consider ambiguity for light jets
    if(std::abs(lqPhiFit-lqPhiPre)+std::abs(lqbarPhiFit-lqbarPhiPre)<std::abs(lqPhiFit-lqbarPhiPre)+std::abs(lqbarPhiFit-lqPhiPre)){
      hists_["shiftLqPhi"    ]->Fill( lqPhiFit-lqPhiPre, weight);
      hists_["shiftLqPhi"    ]->Fill( lqbarPhiFit-lqbarPhiPre, weight);
    }
    else{
      hists_["shiftLqPhi"    ]->Fill( lqPhiFit-lqbarPhiPre, weight);
      hists_["shiftLqPhi"    ]->Fill( lqbarPhiFit-lqPhiPre, weight);
    }
  }
  lepPtPre=lepEtaPre=lepPhiPre=nuPtPre=nuEtaPre=nuPhiPre=-999;
  if(muons_h->end()-muons_h->begin()>0){
    lepPtPre  =muons_h->at(0).pt();
    lepEtaPre =muons_h->at(0).eta();
    lepPhiPre =muons_h->at(0).phi();
  }
  else if(electrons_h->end()-electrons_h->begin()>0){
    nuPtPre   =electrons_h->at(0).pt();
    nuEtaPre  =electrons_h->at(0).eta();
    nuPhiPre  =electrons_h->at(0).phi();
  }
  if(MET_h->end()-MET_h->begin()>0){
    nuPtPre   =MET_h->at(0).pt();
    nuEtaPre  =MET_h->at(0).eta();
    nuPhiPre  =MET_h->at(0).phi();
  }
  if(lepPtFit!=-999&&lepPtPre!=-999  ) hists_["shiftLepPt" ]->Fill( lepPtFit -lepPtPre , weight);  
  if(nuPtFit!=-999 &&nuPtPre!=-999   ) hists_["shiftNuPt"  ]->Fill( nuPtFit  -nuPtPre  , weight);
  if(lepEtaFit!=-999&&lepEtaPre!=-999) hists_["shiftLepEta"]->Fill( lepEtaFit-lepEtaPre, weight);  
  if(nuEtaFit!=-999 &&nuEtaPre!=-999 ) hists_["shiftNuEta" ]->Fill( nuEtaFit -nuEtaPre , weight);
  if(lepPhiFit!=-999&&lepPhiPre!=-999) hists_["shiftLepPhi"]->Fill( lepPhiFit-lepPhiPre, weight);  
  if(nuPhiFit!=-999 &&nuPhiPre!=-999 ) hists_["shiftNuPhi" ]->Fill( nuPhiFit -nuPhiPre , weight);

  tree->Fill();
}

void
MixedObjectsAnalyzer::endJob()
{

}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( MixedObjectsAnalyzer );
