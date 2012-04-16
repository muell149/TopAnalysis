#include "TopAnalysis/TopAnalyzer/interface/TopAngles.h"
#include "TopAnalysis/TopAnalyzer/interface/FullHadTopReco.h"
#include "AnalysisDataFormats/TopObjects/interface/TtFullHadEvtPartons.h"

#include "TLorentzVector.h"
#include "TVector3.h"

/// default constructor for fw lite
FullHadTopReco::FullHadTopReco()
{
  tree = 0;
}

/// default constructor for full fw
FullHadTopReco::FullHadTopReco(const edm::ParameterSet& cfg) :
  useTree_ ( cfg.getParameter<bool>( "useTree" ) ),
  hypo_    ( cfg.getParameter<std::string>( "hypo" ) ),
  bTagAlgo_( cfg.getParameter<std::string>( "bTagAlgo" ) ),
  topMass_ ( cfg.getParameter<double>( "topMass" ) ),
  window_  ( cfg.getParameter<double>( "window" ) )
{
  tree = 0;
}

/// histogramm booking for fwlite 
void FullHadTopReco::book()
{
  /** 
      Add needed histogramms from full fw list of histogramms
  **/
}

/// histogramm booking for fw
void FullHadTopReco::book(edm::Service<TFileService>& fs)
{
  /** 
      kinematic quantities of hypothesis particles
  **/

  // b pt
  bookVariable( fs, "bQuarkPt"        ,  200,  0. , 1000. , false );
  // b eta			        
  bookVariable( fs, "bQuarkEta"       ,   70, -3.5,   3.5 , false );
  // b phi			        
  bookVariable( fs, "bQuarkPhi"       ,   70, -M_PI, M_PI , false );
  // b mass			        
  bookVariable( fs, "bQuarkMass"      ,   50,  0. , 100.  , false );
  // lightQuark pt		        
  bookVariable( fs, "lightQuarkPt"    ,  100,  0. , 500.  , false );
  // lightQuark eta		        
  bookVariable( fs, "lightQuarkEta"   ,   70, -3.5, 3.5   , false );
  // lightQuark phi		        
  bookVariable( fs, "lightQuarkPhi"   ,   70, -M_PI, M_PI , false );
  // lightQuark mass		        
  bookVariable( fs, "lightQuarkMass"  ,   50,  0. , 100.  , false );

  // top pt
  bookVariable( fs, "topQuarkPt"      ,  200,  0. , 1000. , false );
  // top eta
  bookVariable( fs, "topQuarkEta"     ,   70, -3.5, 3.5   , false );
  // top Y
  bookVariable( fs, "topQuarkY"       ,  100, -5. , 5.    , false );
  // top phi
  bookVariable( fs, "topQuarkPhi"     ,   70, -M_PI, M_PI , false );
  // top mass
  bookVariable( fs, "topQuarkMass"    , 1000,  0. , 1000. , useTree_ );
  // topBar mass
  bookVariable( fs, "topBarQuarkMass" , 1000,  0. , 1000. , useTree_ );
  // top pt of hypothesis
  bookVariable( fs, "topQuarkPtHypo"  ,  200,  0. , 1000. , false );
  // top eta of hypothesis
  bookVariable( fs, "topQuarkEtaHypo" ,   70, -3.5, 3.5   , false );
  // top Y of hypothesis
  bookVariable( fs, "topQuarkYHypo"   ,  100, -5. , 5.    , false );
  // top phi of hypothesis
  bookVariable( fs, "topQuarkPhiHypo" ,   70, -M_PI, M_PI , false );
  // top mass of hypothesis
  bookVariable( fs, "topQuarkMassHypo", 1000,  0. , 1000. , useTree_ );
  // top mass of hypothesis
  bookVariable( fs, "topQuarkMassHypo" );
  /// mtop hypo vs. mtop reco
  bookVariable( fs, "topMassHypoReco",   300, 100.,  400. , 300, 100., 400. );

  // W pt
  bookVariable( fs, "wPt"      ,  200,  0. , 1000. , false );
  // W eta
  bookVariable( fs, "wEta"     ,   70, -3.5, 3.5   , false );
  // W Y
  bookVariable( fs, "wY"       ,  100, -5. , 5.    , false );
  // W phi
  bookVariable( fs, "wPhi"     ,   70, -M_PI, M_PI , false );
  // W mass
  bookVariable( fs, "wMass"    ,  600,  0. , 600.  , false );
  // W pt of hypothesis
  bookVariable( fs, "wPtHypo"  ,  200,  0. , 1000. , false );
  // W eta of hypothesis
  bookVariable( fs, "wEtaHypo" ,   70, -3.5, 3.5   , false );
  // W Y of hypothesis
  bookVariable( fs, "wYHypo"   ,  100, -5. , 5.    , false );
  // W phi of hypothesis
  bookVariable( fs, "wPhiHypo" ,   70, -M_PI, M_PI , false );
  // W mass of hypothesis
  bookVariable( fs, "wMassHypo",  600,  0. , 600.  , false );

  // btag of b-jet with lower btag vs. di-jet-mass of corresponding w candidate
  bookVariable( fs, "bTagVsMjjW",  60, 60.4, 120.4, 100, 0. , 10. );

  // invariant ttbar mass
  bookVariable( fs, "ttbarInvMass"    , 750, 0. , 1500. , useTree_ );
  // invariant ttbar mass of hypothesis
  bookVariable( fs, "ttbarInvMassHypo", 750, 0. , 1500. , useTree_ );

  // pt of ttbar system
  bookVariable( fs, "ttbarPt"    , 750, 0. , 1500. , useTree_ );
  // pt of ttbar system of hypothesis
  bookVariable( fs, "ttbarPtHypo", 750, 0. , 1500. , useTree_ );

  // invariant ttbar mass
  bookVariable( fs, "ttbarInvMass_topMass"    , 750, 0. , 1500. , false );
  // invariant ttbar mass of hypothesis
  bookVariable( fs, "ttbarInvMassHypo_topMass", 750, 0. , 1500. , false );

  // pt of ttbar system
  bookVariable( fs, "ttbarPt_topMass"    , 750, 0. , 1500. , false );
  // pt of ttbar system of hypothesis
  bookVariable( fs, "ttbarPtHypo_topMass", 750, 0. , 1500. , false );

  // theta* of W plus boson
  bookVariable( fs, "thetaStarPlus"     , 320, 0. , M_PI , useTree_ );
  // theta* of W minus boson
  bookVariable( fs, "thetaStarMinus"    , 320, 0. , M_PI , useTree_ );
  // theta* of W plus boson of hypothesis
  bookVariable( fs, "thetaStarHypoPlus" , 320, 0. , M_PI , useTree_ );
  // theta* of W minus boson of hypothesis
  bookVariable( fs, "thetaStarHypoMinus", 320, 0. , M_PI , useTree_ );

  // theta* of W bosons
  bookVariable( fs, "thetaStar"     , 320, 0. , M_PI , false );
  // theta* of W bosons of hypothesis
  bookVariable( fs, "thetaStarHypo" , 320, 0. , M_PI , false );

  // cos(theta*) of W plus boson
  bookVariable( fs, "cosThetaStarPlus"     , 200, -1. , 1. , useTree_ );
  // cos(theta*) of W minus boson
  bookVariable( fs, "cosThetaStarMinus"    , 200, -1. , 1. , useTree_ );
  // cos(theta*) of W plus boson of hypothesis
  bookVariable( fs, "cosThetaStarHypoPlus" , 200, -1. , 1. , useTree_ );
  // cos(theta*) of W minus boson of hypothesis
  bookVariable( fs, "cosThetaStarHypoMinus", 200, -1. , 1. , useTree_ );

  // cos(theta*) of W bosons
  bookVariable( fs, "cosThetaStar"     , 200, -1. , 1. , false );
  // cos(theta*) of W bosons of hypothesis
  bookVariable( fs, "cosThetaStarHypo" , 200, -1. , 1. , false );

  // angle between b-tagged jets
  bookVariable( fs, "bAngle"    , 315, 0. , M_PI , useTree_ );
  // angle between b-quark candidates from hypothesis
  bookVariable( fs, "bAngleHypo", 315, 0. , M_PI , useTree_ );

  // cosine of angle between b-tagged jets
  bookVariable( fs, "cosBAngle"    , 400, -1. , 1. , useTree_ );
  // cosine of angle between b-tagged jets
  bookVariable( fs, "cosBAngle" );
  // cosine of angle between b-tagged jets prob < 0.01
  bookVariable( fs, "cosBAngleBackground" );
  // cosine of angle between b-quark candidates from hypothesis
  bookVariable( fs, "cosBAngleHypo", 400, -1. , 1. , useTree_ );

  // sine of angle between b-tagged jets
  bookVariable( fs, "sinBAngle"    , 200, 0. , 1. , useTree_ );
  // sine ofangle between b-quark candidates from hypothesis
  bookVariable( fs, "sinBAngleHypo", 200, 0. , 1. , useTree_ );

  // angle between top quark and W boson
  bookVariable( fs, "topWAngle"    , 315, 0. , M_PI , false );
  // angle between top quark and W boson from hypothesis
  bookVariable( fs, "topWAngleHypo", 315, 0. , M_PI , false );

  // book angles off ttbar system
  bookVariable( fs, "ttDetFrame"                          , 315, 0. , M_PI , useTree_ );			
  bookVariable( fs, "bbDetFrame"                          , 315, 0. , M_PI , useTree_ );			
  bookVariable( fs, "bbTtbarFrame"                        , 315, 0. , M_PI , useTree_ );			
  bookVariable( fs, "WWTtbarFrame"                        , 315, 0. , M_PI , useTree_ );			
  bookVariable( fs, "tBBranch1TtbarFrame"                 , 315, 0. , M_PI , useTree_ );			
  bookVariable( fs, "tBBranch2TtbarFrame"                 , 315, 0. , M_PI , useTree_ );			
  bookVariable( fs, "bWBranch1TtbarFrame"                 , 315, 0. , M_PI , useTree_ );			
  bookVariable( fs, "bWBranch2TtbarFrame"                 , 315, 0. , M_PI , useTree_ );			
  bookVariable( fs, "tWBranch1TopInTtbarFrameWInTopFrame" , 315, 0. , M_PI , useTree_ );	
  bookVariable( fs, "tWBranch2TopInTtbarFrameWInTopFrame" , 315, 0. , M_PI , useTree_ );	
  bookVariable( fs, "qQbarTopFrame"                       , 315, 0. , M_PI , useTree_ );			
  bookVariable( fs, "qQbarDetFrame"                       , 315, 0. , M_PI , useTree_ );			
  bookVariable( fs, "pPbarTopFrame"                       , 315, 0. , M_PI , useTree_ );			
  bookVariable( fs, "pQbarTtbarFrame"                     , 315, 0. , M_PI , useTree_ );			
  bookVariable( fs, "pQTtbarFrame"                        , 315, 0. , M_PI , useTree_ );			
  bookVariable( fs, "pbarQbarTtbarFrame"                  , 315, 0. , M_PI , useTree_ );			
  bookVariable( fs, "pbarQTtbarFrame"                     , 315, 0. , M_PI , useTree_ );			
  bookVariable( fs, "bhad1QTopFrame"                      , 315, 0. , M_PI , useTree_ );			
  bookVariable( fs, "bhad1QbarTopFrame"                   , 315, 0. , M_PI , useTree_ );			
  bookVariable( fs, "bhad1PTtbarFrame"                    , 315, 0. , M_PI , useTree_ );			
  bookVariable( fs, "bhad1PbarTtbarFrame"                 , 315, 0. , M_PI , useTree_ );			
  bookVariable( fs, "bhad2QTtbarFrame"                    , 315, 0. , M_PI , useTree_ );			
  bookVariable( fs, "bhad2QbarTtbarFrame"                 , 315, 0. , M_PI , useTree_ );			
  bookVariable( fs, "bhad2PTopFrame"                      , 315, 0. , M_PI , useTree_ );			
  bookVariable( fs, "bhad2PbarTopFrame"                   , 315, 0. , M_PI , useTree_ );			
  bookVariable( fs, "qInW1FrameW1InDetFrame"              , 315, 0. , M_PI , useTree_ );		
  bookVariable( fs, "qbarInW1FrameW1InDetFrame"           , 315, 0. , M_PI , useTree_ );		
  bookVariable( fs, "pInW2FrameW2InDetFrame"              , 315, 0. , M_PI , useTree_ ); 		
  bookVariable( fs, "pbarInW2FrameW2InDetFrame"           , 315, 0. , M_PI , useTree_ );

}

// calculating theta* of W boson
double FullHadTopReco::thetaStar(const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > wBoson,
				 const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > lightQ,
				 const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > lightQBar){

  // define TLorentzVectors and 3D vector for W boson, light quarks and boost vector
  TLorentzVector w = TLorentzVector(wBoson.Px(),wBoson.Py(),wBoson.Pz(),wBoson.E());
  TVector3 boostVec = w.BoostVector(); boostVec = TVector3(0-boostVec.Px(),0-boostVec.Py(),0-boostVec.Pz());
  TLorentzVector lQ    = TLorentzVector(lightQ   .Px(),lightQ   .Py(),lightQ   .Pz(),lightQ   .E());
  TLorentzVector lQBar = TLorentzVector(lightQBar.Px(),lightQBar.Py(),lightQBar.Pz(),lightQBar.E());
  
  // boost light quarks to cms of W boson
  lQ.Boost(boostVec);
  lQBar.Boost(boostVec);

  // theta* of W boson
  double thetaStar1 = w.Angle(lQ.Vect());
  double thetaStar2 = w.Angle(lQBar.Vect());
  return ((thetaStar1 < thetaStar2) ? thetaStar1 : thetaStar2);
}

// calculating angle of W boson in top rest frame to top direction of flight
double FullHadTopReco::topWAngle(const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > topQuark,
				 const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > wBoson){

  // define TLorentzVectors and 3D vector for top quark, W boson and boost vector
  TLorentzVector top = TLorentzVector(topQuark.Px(),topQuark.Py(),topQuark.Pz(),topQuark.E());
  TVector3 boostVec  = top.BoostVector(); boostVec = TVector3(0-boostVec.Px(),0-boostVec.Py(),0-boostVec.Pz());
  TLorentzVector w   = TLorentzVector(w.Px(),w.Py(),w.Pz(),w.E());

  // boost W boson to cms of top quark
  w.Boost(boostVec);

  // angle of W boson in cms of top top top direction of flight
  double angle = top.Angle(w.Vect());
  return angle;
}

/// histogram filling interface for reconstruction level for access with fwlite or full framework
void
FullHadTopReco::fill(const TtFullHadronicEvent& tops, const edm::View<pat::Jet>& jets, const double& weight)
{
  // make sure to have a valid hypothesis on reconstruction level
  if( tops.isHypoValid(hypo_) ){
    /** 
	Fill the Pull Distributions (Relative to the Reco Input)
    **/
    // define indices in pat::Jet collection

    int lightQ    = tops.jetLeptonCombination(hypo_)[TtFullHadEvtPartons::LightQ   ];
    int lightQBar = tops.jetLeptonCombination(hypo_)[TtFullHadEvtPartons::LightQBar];
    int b         = tops.jetLeptonCombination(hypo_)[TtFullHadEvtPartons::B        ];
    int bBar      = tops.jetLeptonCombination(hypo_)[TtFullHadEvtPartons::BBar     ];
    int lightP    = tops.jetLeptonCombination(hypo_)[TtFullHadEvtPartons::LightP   ];
    int lightPBar = tops.jetLeptonCombination(hypo_)[TtFullHadEvtPartons::LightPBar];

    // top properties of hypothesis
    fillValue("topQuarkPtHypo"  , tops.top(hypo_)->pt()      , weight);
    fillValue("topQuarkEtaHypo" , tops.top(hypo_)->eta()     , weight);
    fillValue("topQuarkYHypo"   , tops.top(hypo_)->rapidity(), weight);
    fillValue("topQuarkPhiHypo" , tops.top(hypo_)->phi()     , weight);
    fillValue("topQuarkMassHypo", tops.top(hypo_)->mass()    , weight);

    // topBar properties of hypothesis
    if(hypo_!="kKinFit") fillValue("topBarQuarkMassHypo", tops.topBar(hypo_)->mass(), weight);
    fillValue("topQuarkPtHypo"  , tops.topBar(hypo_)->pt()      , weight);
    fillValue("topQuarkEtaHypo" , tops.topBar(hypo_)->eta()     , weight);
    fillValue("topQuarkYHypo"   , tops.topBar(hypo_)->rapidity(), weight);
    fillValue("topQuarkPhiHypo" , tops.topBar(hypo_)->phi()     , weight);

    // w plus properties of hypothesis
    fillValue("wPtHypo"  , tops.wPlus(hypo_)->pt()      , weight);
    fillValue("wEtaHypo" , tops.wPlus(hypo_)->eta()     , weight);
    fillValue("wYHypo"   , tops.wPlus(hypo_)->rapidity(), weight);
    fillValue("wPhiHypo" , tops.wPlus(hypo_)->phi()     , weight);
    fillValue("wMassHypo", tops.wPlus(hypo_)->mass()    , weight);

    // w minus properties of hypothesis
    fillValue("wMassHypo", tops.wMinus(hypo_)->mass()    , weight);
    fillValue("wPtHypo"  , tops.wMinus(hypo_)->pt()      , weight);
    fillValue("wEtaHypo" , tops.wMinus(hypo_)->eta()     , weight);
    fillValue("wYHypo"   , tops.wMinus(hypo_)->rapidity(), weight);
    fillValue("wPhiHypo" , tops.wMinus(hypo_)->phi()     , weight);

    // invariant ttbar mass of hypothesis
    fillValue("ttbarInvMassHypo", (tops.top(hypo_)->p4() + tops.topBar(hypo_)->p4()).mass(), weight);

    // pt of ttbar system of hypothesis
    fillValue("ttbarPtHypo", (tops.top(hypo_)->p4() + tops.topBar(hypo_)->p4()).pt(), weight);
    
    if(std::abs(tops.top(hypo_)->mass() - topMass_) < window_ && std::abs(tops.topBar(hypo_)->mass() - topMass_) < window_ ){
      // invariant ttbar mass of hypothesis
      fillValue("ttbarInvMassHypo_topMass", (tops.top(hypo_)->p4() + tops.topBar(hypo_)->p4()).mass(), weight);
      // pt of ttbar system of hypothesis
      fillValue("ttbarPtHypo_topMass", (tops.top(hypo_)->p4() + tops.topBar(hypo_)->p4()).pt(), weight);
    }
    
    // calculate angles from the 4 momentum vectors
    TopAngles angles = TopAngles(tops.b   (hypo_)->p4(), tops.lightQ(hypo_)->p4(), tops.lightQBar(hypo_)->p4(),
				 tops.bBar(hypo_)->p4(), tops.lightP(hypo_)->p4(), tops.lightPBar(hypo_)->p4());

    fillValue( "ttDetFrame"                         , angles.ttDetFrame()                          , weight );			
    fillValue( "bbDetFrame"                         , angles.bbDetFrame()                          , weight );			
    fillValue( "bbTtbarFrame"                       , angles.bbTtbarFrame()                        , weight );			
    fillValue( "WWTtbarFrame"                       , angles.WWTtbarFrame()                        , weight );			
    fillValue( "tBBranch1TtbarFrame"                , angles.tBBranch1TtbarFrame()                 , weight );			
    fillValue( "tBBranch2TtbarFrame"                , angles.tBBranch2TtbarFrame()                 , weight );			
    fillValue( "bWBranch1TtbarFrame"                , angles.bWBranch1TtbarFrame()                 , weight );			
    fillValue( "bWBranch2TtbarFrame"                , angles.bWBranch2TtbarFrame()                 , weight );			
    fillValue( "tWBranch1TopInTtbarFrameWInTopFrame", angles.tWBranch1TopInTtbarFrameWInTopFrame() , weight );	
    fillValue( "tWBranch2TopInTtbarFrameWInTopFrame", angles.tWBranch2TopInTtbarFrameWInTopFrame() , weight );	
    fillValue( "qQbarTopFrame"                      , angles.qQbarTopFrame()                       , weight );			
    fillValue( "qQbarDetFrame"                      , angles.qQbarDetFrame()                       , weight );			
    fillValue( "pPbarTopFrame"                      , angles.pPbarTopFrame()                       , weight );			
    fillValue( "pQbarTtbarFrame"                    , angles.pQbarTtbarFrame()                     , weight );			
    fillValue( "pQTtbarFrame"                       , angles.pQTtbarFrame()                        , weight );			
    fillValue( "pbarQbarTtbarFrame"                 , angles.pbarQbarTtbarFrame()                  , weight );			
    fillValue( "pbarQTtbarFrame"                    , angles.pbarQTtbarFrame()                     , weight );			
    fillValue( "bhad1QTopFrame"                     , angles.bhad1QTopFrame()                      , weight );			
    fillValue( "bhad1QbarTopFrame"                  , angles.bhad1QbarTopFrame()                   , weight );			
    fillValue( "bhad1PTtbarFrame"                   , angles.bhad1PTtbarFrame()                    , weight );			
    fillValue( "bhad1PbarTtbarFrame"                , angles.bhad1PbarTtbarFrame()                 , weight );			
    fillValue( "bhad2QTtbarFrame"                   , angles.bhad2QTtbarFrame()                    , weight );			
    fillValue( "bhad2QbarTtbarFrame"                , angles.bhad2QbarTtbarFrame()                 , weight );			
    fillValue( "bhad2PTopFrame"                     , angles.bhad2PTopFrame()                      , weight );			
    fillValue( "bhad2PbarTopFrame"                  , angles.bhad2PbarTopFrame()                   , weight );			
    fillValue( "qInW1FrameW1InDetFrame"             , angles.qInW1FrameW1InDetFrame()              , weight );		
    fillValue( "qbarInW1FrameW1InDetFrame"          , angles.qbarInW1FrameW1InDetFrame()           , weight );		
    fillValue( "pInW2FrameW2InDetFrame"             , angles.pInW2FrameW2InDetFrame()              , weight ); 		
    fillValue( "pbarInW2FrameW2InDetFrame"          , angles.pbarInW2FrameW2InDetFrame()           , weight );                

    // theta* of W boson of hypothesis
    double thetaStarPlus  = thetaStar(tops.wPlus (hypo_)->p4(), tops.lightQ(hypo_)->p4(), tops.lightQBar(hypo_)->p4());
    double thetaStarMinus = thetaStar(tops.wMinus(hypo_)->p4(), tops.lightP(hypo_)->p4(), tops.lightPBar(hypo_)->p4());
    fillValue("thetaStarHypoPlus" , thetaStarPlus , weight);
    fillValue("thetaStarHypoMinus", thetaStarMinus, weight);

    fillValue("thetaStarHypo", thetaStarPlus , weight);
    fillValue("thetaStarHypo", thetaStarMinus, weight);
 
    // cos(theta*) of W boson of hypothesis
    fillValue("cosThetaStarHypoPlus" , cos(thetaStarPlus) , weight);
    fillValue("cosThetaStarHypoMinus", cos(thetaStarMinus), weight);

    fillValue("cosThetaStarHypo", cos(thetaStarPlus) , weight);
    fillValue("cosThetaStarHypo", cos(thetaStarMinus), weight);
    
    // angle between b-quark candidates from hypothesis
    TLorentzVector bCandidate    = TLorentzVector( tops.b   (hypo_)->px(), tops.b   (hypo_)->py(), tops.b   (hypo_)->pz(), tops.b   (hypo_)->energy() );
    TLorentzVector bBarCandidate = TLorentzVector( tops.bBar(hypo_)->px(), tops.bBar(hypo_)->py(), tops.bBar(hypo_)->pz(), tops.bBar(hypo_)->energy() );
    double bAngleHypo = bCandidate.Angle( bBarCandidate.Vect() );
    fillValue(   "bAngleHypo",     bAngleHypo , weight);
    fillValue("cosBAngleHypo", cos(bAngleHypo), weight);
    fillValue("sinBAngleHypo", sin(bAngleHypo), weight);
 
    // angle between W boson in top cms and top direction of flight
    fillValue("topWAngleHypo", topWAngle( tops.top   (hypo_)->p4(), tops.wPlus (hypo_)->p4() ), weight);
    fillValue("topWAngleHypo", topWAngle( tops.topBar(hypo_)->p4(), tops.wMinus(hypo_)->p4() ), weight);

    // make sure the b-jet index is in the range of the jet collection
    if( b >=0 && b < (int)jets.size() ){
      // b pt
      fillValue("bQuarkPt"  , jets[b].pt()  , weight);
      // b eta
      fillValue("bQuarkEta" , jets[b].eta() , weight);
      // b phi
      fillValue("bQuarkPhi" , jets[b].phi() , weight);
      // b mass
      fillValue("bQuarkMass", jets[b].mass(), weight);
    }
   // make sure the bBar-jet index is in the range of the jet collection
    if( bBar >= 0 && bBar< (int)jets.size() ){
      // bBar pt
      fillValue("bQuarkPt"  , jets[bBar].pt()  , weight);
      // bBar eta
      fillValue("bQuarkEta" , jets[bBar].eta() , weight);
      // bBar phi
      fillValue("bQuarkPhi" , jets[bBar].phi() , weight);
      // bBar mass
      fillValue("bQuarkMass", jets[bBar].mass(), weight);

      if( b >=0 && b < (int)jets.size() ){
	// angle between b-tagged jets
	TLorentzVector bJet    = TLorentzVector( jets[b]   .px(), jets[b]   .py(), jets[b]   .pz(), jets[b]   .energy() );
	TLorentzVector bBarJet = TLorentzVector( jets[bBar].px(), jets[bBar].py(), jets[bBar].pz(), jets[bBar].energy() );
	double bAngle = bJet.Angle( bBarJet.Vect() );
	fillValue(   "bAngle",     bAngle , weight);
	fillValue("cosBAngle", cos(bAngle), weight);
	fillValue("sinBAngle", sin(bAngle), weight);
	if(tops.fitProb() <= 0.01) fillValue("cosBAngleBackground", cos(bAngle), weight);
	else                       fillValue("cosBAngleBackground", -100., weight);
      }
    }
   // make sure the light quark index is in the range of the jet collection
    if( lightQ >= 0 && lightQ < (int)jets.size() ){
      // lightQuark pt
      fillValue("lightQuarkPt"   , jets[lightQ].pt()   , weight);
      // lightQuark eta
      fillValue("lightQuarkEta"  , jets[lightQ].eta()  , weight);
      // lightQuark phi
      fillValue("lightQuarkPhi"  , jets[lightQ].phi()  , weight);
      // lightQuark mass
      fillValue("lightQuarkMass" , jets[lightQ].mass() , weight);
    }
    // make sure the light quark bar index is in the range of the jet collection
    if( lightQBar >= 0 && lightQBar< (int)jets.size() ){
      // lightQuark pt
      fillValue("lightQuarkPt"   , jets[lightQBar].pt()   , weight);
      // lightQuark eta
      fillValue("lightQuarkEta"  , jets[lightQBar].eta()  , weight);
      // lightQuark phi
      fillValue("lightQuarkPhi"  , jets[lightQBar].phi()  , weight);
      // lightQuark mass
      fillValue("lightQuarkMass" , jets[lightQBar].mass() , weight);
    }
   // make sure the light quark index is in the range of the jet collection
    if( lightP >= 0 && lightP < (int)jets.size() ){
      // lightQuark pt
      fillValue("lightQuarkPt"   , jets[lightP].pt()   , weight);
      // lightQuark eta
      fillValue("lightQuarkEta"  , jets[lightP].eta()  , weight);
      // lightQuark phi
      fillValue("lightQuarkPhi"  , jets[lightP].phi()  , weight);
      // lightQuark mass
      fillValue("lightQuarkMass" , jets[lightP].mass() , weight);
    }
    // make sure the light quark bar index is in the range of the jet collection
    if( lightPBar >= 0 && lightPBar < (int)jets.size() ){
      // lightQuark pt
      fillValue("lightQuarkPt"   , jets[lightPBar].pt()   , weight);
      // lightQuark eta
      fillValue("lightQuarkEta"  , jets[lightPBar].eta()  , weight);
      // lightQuark phi
      fillValue("lightQuarkPhi"  , jets[lightPBar].phi()  , weight);
      // lightQuark mass
      fillValue("lightQuarkMass" , jets[lightPBar].mass() , weight);
    }
    // make sure all the light quark indecies for W are in the range of the jet collection
    if( lightQ >= 0 && lightQ < (int)jets.size() && lightQBar >= 0 && lightQBar < (int)jets.size() ){
      // W pt
      fillValue("wPt"   , (jets[lightQ].p4() + jets[lightQBar].p4()).pt()       , weight);
      // W eta
      fillValue("wEta"  , (jets[lightQ].p4() + jets[lightQBar].p4()).eta()      , weight);
      // W Y
      double energy = (jets[lightQ].p4() + jets[lightQBar].p4()).energy();
      double pz     = (jets[lightQ].p4() + jets[lightQBar].p4()).pz();
      double rapidity = 0.5 * log(( energy + pz ) / ( energy - pz ));
      fillValue("wY"    , rapidity , weight);
      // W phi
      fillValue("wPhi"  , (jets[lightQ].p4() + jets[lightQBar].p4()).phi()      , weight);
      // W mass
      fillValue("wMass" , (jets[lightQ].p4() + jets[lightQBar].p4()).mass()     , weight);

      // theta* of W boson
      double thetaStar1 = thetaStar(jets[lightQ].p4() + jets[lightQBar].p4(), jets[lightQ].p4(), jets[lightQBar].p4());
      fillValue("thetaStarPlus",thetaStar1 , weight);
      fillValue("thetaStar"    ,thetaStar1 , weight);
      // cos(theta*) of W boson
      fillValue("cosThetaStarPlus", cos(thetaStar1) , weight);
      fillValue("cosThetaStar"    , cos(thetaStar1) , weight);

      // make sure the b quark index is in the range of the jet collection
      if( b >= 0 && b < (int)jets.size() ){
      	// top pt
	fillValue("topQuarkPt"   , (jets[lightQ].p4() + jets[lightQBar].p4() + jets[b].p4()).pt()       , weight);
	// top eta
	fillValue("topQuarkEta"  , (jets[lightQ].p4() + jets[lightQBar].p4() + jets[b].p4()).eta()      , weight);
	// top Y
	double energy = (jets[lightQ].p4()+jets[lightQBar].p4()+jets[b].p4()).energy();
	double pz     = (jets[lightQ].p4()+jets[lightQBar].p4()+jets[b].p4()).pz();
	double rapidity = 0.5 * log(( energy + pz ) / ( energy - pz ));
	fillValue("topQuarkY"    , rapidity , weight);
	// top phi
	fillValue("topQuarkPhi"  , (jets[lightQ].p4() + jets[lightQBar].p4() + jets[b].p4()).phi()      , weight);
	// top mass
	fillValue("topQuarkMass" , (jets[lightQ].p4() + jets[lightQBar].p4() + jets[b].p4()).mass()     , weight);
	// top mass hypo vs. reco
	fillValue("topMassHypoReco" , (jets[lightQ].p4() + jets[lightQBar].p4() + jets[b].p4()).mass() , tops.top(hypo_)->mass() , weight);

	// angle between W boson in top cms and top direction of flight
	fillValue("topWAngle", topWAngle( (jets[lightQ].p4() + jets[lightQBar].p4() + jets[b].p4()), (jets[lightQ].p4() + jets[lightQBar].p4()) ), weight);

	// btag of b-jet with lower btag vs. di-jet-mass of corresponding w candidate
	if( jets[b].bDiscriminator(bTagAlgo_) < jets[bBar].bDiscriminator(bTagAlgo_) ){
	  fillValue("bTagVsMjjW" , (jets[lightQ].p4() + jets[lightQBar].p4()).mass(), jets[b].bDiscriminator(bTagAlgo_) , weight);
	}
      }
    }
    // make sure all the light quark indecies are in the range of the jet collection
    if( lightP >= 0 && lightP < (int)jets.size() && lightPBar >= 0 && lightPBar < (int)jets.size() ){
      // W pt
      fillValue("wPt"   , (jets[lightP].p4() + jets[lightPBar].p4()).pt()       , weight);
      // W eta
      fillValue("wEta"  , (jets[lightP].p4() + jets[lightPBar].p4()).eta()      , weight);
      // W Y
      double energy = (jets[lightP].p4() + jets[lightPBar].p4()).energy();
      double pz     = (jets[lightP].p4() + jets[lightPBar].p4()).pz();
      double rapidity = 0.5 * log(( energy + pz ) / ( energy - pz ));
      fillValue("wY"    , rapidity , weight);
      // W phi
      fillValue("wPhi"  , (jets[lightP].p4() + jets[lightPBar].p4()).phi()      , weight);
      // W mass
      fillValue("wMass" , (jets[lightP].p4() + jets[lightPBar].p4()).mass()     , weight);

      // theta* of W boson
      double thetaStar1 = thetaStar(jets[lightP].p4() + jets[lightPBar].p4(), jets[lightP].p4(), jets[lightPBar].p4());
      fillValue("thetaStarMinus",thetaStar1 , weight);
      fillValue("thetaStar"     ,thetaStar1 , weight);
      // cos(theta*) of W boson
      fillValue("cosThetaStarMinus", cos(thetaStar1) , weight);
      fillValue("cosThetaStar"     , cos(thetaStar1) , weight);

      // make sure the b quark index is in the range of the jet collection
      if( bBar >= 0 && bBar < (int)jets.size() ){
      	// top pt
	fillValue("topQuarkPt"   , (jets[lightP].p4() + jets[lightPBar].p4() + jets[bBar].p4()).pt()       , weight);
	// top eta
	fillValue("topQuarkEta"  , (jets[lightP].p4() + jets[lightPBar].p4() + jets[bBar].p4()).eta()      , weight);
	// top Y
	double energy = (jets[lightP].p4()+jets[lightPBar].p4()+jets[bBar].p4()).energy();
	double pz     = (jets[lightP].p4()+jets[lightPBar].p4()+jets[bBar].p4()).pz();
	double rapidity = 0.5 * log(( energy + pz ) / ( energy - pz ));
	fillValue("topQuarkY"    , rapidity , weight);
	// top phi
	fillValue("topQuarkPhi"  , (jets[lightP].p4() + jets[lightPBar].p4() + jets[bBar].p4()).phi()      , weight);
	// top mass
	fillValue("topBarQuarkMass" , (jets[lightP].p4() + jets[lightPBar].p4() + jets[bBar].p4()).mass() , weight);
	if(!useTree_) fillValue("topQuarkMass", (jets[lightP].p4() + jets[lightPBar].p4() + jets[bBar].p4()).mass() , weight);
	// top mass hypo vs. reco
	fillValue("topMassHypoReco" , (jets[lightP].p4() + jets[lightPBar].p4() + jets[bBar].p4()).mass() , tops.topBar(hypo_)->mass() , weight);

	// angle between W boson in top cms and top direction of flight
	fillValue("topWAngle", topWAngle( (jets[lightP].p4()+jets[lightPBar].p4()+jets[bBar].p4()), (jets[lightP].p4()+jets[lightPBar].p4()) ), weight);

	// btag of b-jet with lower btag vs. di-jet-mass of corresponding w candidate
	if( jets[bBar].bDiscriminator(bTagAlgo_) < jets[b].bDiscriminator(bTagAlgo_) ){
	  fillValue("bTagVsMjjW" , (jets[lightP].p4() + jets[lightPBar].p4()).mass(), jets[bBar].bDiscriminator(bTagAlgo_) , weight);
	}
      }
    }
    if( lightQ >= 0 && lightQ < (int)jets.size() && lightQBar >= 0 && lightQBar < (int)jets.size() && b    >= 0 && b    < (int)jets.size() &&
	lightP >= 0 && lightP < (int)jets.size() && lightPBar >= 0 && lightPBar < (int)jets.size() && bBar >= 0 && bBar < (int)jets.size() ){
      // invariant ttbar mass of hypothesis
      fillValue("ttbarInvMass", (jets[lightQ].p4() + jets[lightQBar].p4() + jets[b   ].p4() +
				 jets[lightP].p4() + jets[lightPBar].p4() + jets[bBar].p4()).mass(), weight);

      fillValue("ttbarPt", (jets[lightQ].p4() + jets[lightQBar].p4() + jets[b   ].p4() +
			    jets[lightP].p4() + jets[lightPBar].p4() + jets[bBar].p4()).pt(), weight);

      if(std::abs((jets[lightQ].p4() + jets[lightQBar].p4() + jets[b   ].p4()).mass() - topMass_) < window_ &&
	 std::abs((jets[lightP].p4() + jets[lightPBar].p4() + jets[bBar].p4()).mass() - topMass_) < window_ ){
	// invariant ttbar mass of hypothesis
	fillValue("ttbarInvMass_topMass", (jets[lightQ].p4() + jets[lightQBar].p4() + jets[b   ].p4() +
					   jets[lightP].p4() + jets[lightPBar].p4() + jets[bBar].p4()).mass(), weight);
	
	// pt of ttbar system of hypothesis
	fillValue("ttbarPt_topMass", (jets[lightQ].p4() + jets[lightQBar].p4() + jets[b   ].p4() +
				      jets[lightP].p4() + jets[lightPBar].p4() + jets[bBar].p4()).pt(), weight);
      }
    }
    // fill the tree, if any variable should be put in
    if(treeVars_.size()) tree->Fill();
  }
}
