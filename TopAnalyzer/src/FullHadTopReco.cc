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
  bookVariable( fs, "bQuarkPt"        ,  50,  0. , 1000. , false );
  // b eta			      
  bookVariable( fs, "bQuarkEta"       ,  30, -3. , 3.    , false );
  // b phi			      
  bookVariable( fs, "bQuarkPhi"       ,  32, -M_PI, M_PI   , false );
  // b mass			      
  bookVariable( fs, "bQuarkMass"      ,  50,  0. , 100.  , false );
  // lightQuark pt		      
  bookVariable( fs, "lightQuarkPt"    ,  50,  0. , 500.  , false );
  // lightQuark eta		      
  bookVariable( fs, "lightQuarkEta"   ,  30, -3. , 3.    , false );
  // lightQuark phi		      
  bookVariable( fs, "lightQuarkPhi"   ,  32, -M_PI, M_PI   , false );
  // lightQuark mass		      
  bookVariable( fs, "lightQuarkMass"  ,  50,  0. , 100.  , false );
  // top pt			      
  bookVariable( fs, "topQuarkPt"      , 100,  0. , 1000. , false );
  // top eta			      
  bookVariable( fs, "topQuarkEta"     ,  30, -3. , 3.    , false );
  // top phi			      
  bookVariable( fs, "topQuarkPhi"     ,  32, -M_PI, M_PI   , false );
  // top mass
  bookVariable( fs, "topQuarkMass"    , 500,  0. , 1000. , useTree_ );
  // topBar mass
  bookVariable( fs, "topBarQuarkMass" , 500,  0. , 1000. , useTree_ );
  // top mass of hypothesis
  bookVariable( fs, "topQuarkMassHypo", 500,  0. , 1000. , useTree_ );
  /// mtop hypo vs. mtop reco
  bookVariable( fs, "topMassHypoReco",  300, 100.,  400. , 300, 100., 400. );
  // W pt
  bookVariable( fs, "wPt"  ,  100,  0. , 1000. , false );
  // W eta
  bookVariable( fs, "wEta" ,   30, -3. , 3.    , false );
  // W phi
  bookVariable( fs, "wPhi" ,   32, -M_PI, M_PI   , false );
  // W mass
  bookVariable( fs, "wMass",  300,  0. , 600.  , false );

  // btag of b-jet with lower btag vs. di-jet-mass of corresponding w candidate
  bookVariable( fs, "bTagVsMjjW",  120, 74.4,  86.4, 50, 0. , 5. );

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
  bookVariable( fs, "thetaStarPlus"     , 315, 0. , M_PI , useTree_ );
  // theta* of W minus boson
  bookVariable( fs, "thetaStarMinus"    , 315, 0. , M_PI , useTree_ );
  // theta* of W plus boson of hypothesis
  bookVariable( fs, "thetaStarHypoPlus" , 315, 0. , M_PI , useTree_ );
  // theta* of W minus boson of hypothesis
  bookVariable( fs, "thetaStarHypoMinus", 315, 0. , M_PI , useTree_ );

  // cos(theta*) of W plus boson
  bookVariable( fs, "cosThetaStarPlus"     , 200, -1. , 1. , useTree_ );
  // cos(theta*) of W minus boson
  bookVariable( fs, "cosThetaStarMinus"    , 200, -1. , 1. , useTree_ );
  // cos(theta*) of W plus boson of hypothesis
  bookVariable( fs, "cosThetaStarHypoPlus" , 200, -1. , 1. , useTree_ );
  // cos(theta*) of W minus boson of hypothesis
  bookVariable( fs, "cosThetaStarHypoMinus", 200, -1. , 1. , useTree_ );

  // angle between b-tagged jets
  bookVariable( fs, "bAngle"    , 315, 0. , M_PI , useTree_ );
  // angle between b-quark candidates from hypothesis
  bookVariable( fs, "bAngleHypo", 315, 0. , M_PI , useTree_ );

}

// calculating theta* of W boson
double thetaStar(const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > wBoson,
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

    // top mass of hypothesis
    fillValue("topQuarkMassHypo", tops.top(hypo_)->mass(), weight);

    // topBar mass of hypothesis
    //if(hypo_!="kKinFit") hists_.find("topQuarkMassHypo")->second->Fill( tops.topBar(hypo_)->mass() );
    //mTopBarHypo = tops.topBar(hypo_)->mass();
    //fillValue("topBarQuarkMassHypo", tops.topBar(hypo_)->mass(), weight);

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
    
    // theta* of W boson of hypothesis
    double thetaStarPlus  = thetaStar(tops.wPlus (hypo_)->p4(), tops.lightQ(hypo_)->p4(), tops.lightQBar(hypo_)->p4());
    double thetaStarMinus = thetaStar(tops.wMinus(hypo_)->p4(), tops.lightP(hypo_)->p4(), tops.lightPBar(hypo_)->p4());
    fillValue("thetaStarHypoPlus", thetaStarPlus , weight);
    fillValue("thetaStarHypoMinus", thetaStarMinus, weight);
    // cos(theta*) of W boson of hypothesis
    fillValue("cosThetaStarHypoPlus" , cos(thetaStarPlus) , weight);
    fillValue("cosThetaStarHypoMinus", cos(thetaStarMinus), weight);
    
    // angle between b-quark candidates from hypothesis
    TLorentzVector bCandidate    = TLorentzVector( tops.b   (hypo_)->px(), tops.b   (hypo_)->py(), tops.b   (hypo_)->pz(), tops.b   (hypo_)->energy() );
    TLorentzVector bBarCandidate = TLorentzVector( tops.bBar(hypo_)->px(), tops.bBar(hypo_)->py(), tops.bBar(hypo_)->pz(), tops.bBar(hypo_)->energy() );
    
    fillValue("bAngleHypo", bCandidate.Angle( bBarCandidate.Vect() ), weight);
 
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

	fillValue("bAngle", bJet.Angle( bBarJet.Vect() ), weight);
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
      fillValue("wPt"   , (jets[lightQ].p4() + jets[lightQBar].p4()).pt()   , weight);
      // W eta
      fillValue("wEta"  , (jets[lightQ].p4() + jets[lightQBar].p4()).eta()  , weight);
      // W phi
      fillValue("wPhi"  , (jets[lightQ].p4() + jets[lightQBar].p4()).phi()  , weight);
      // W mass
      fillValue("wMass" , (jets[lightQ].p4() + jets[lightQBar].p4()).mass() , weight);

      // theta* of W boson
      double thetaStar1 = thetaStar(jets[lightQ].p4() + jets[lightQBar].p4(), jets[lightQ].p4(), jets[lightQBar].p4());
      fillValue("thetaStarPlus",thetaStar1 , weight);
      // cos(theta*) of W boson
      fillValue("cosThetaStarPlus", cos(thetaStar1) , weight);

      // make sure the b quark index is in the range of the jet collection
      if( b >= 0 && b < (int)jets.size() ){
      	// top pt
	fillValue("topQuarkPt"   , (jets[lightQ].p4() + jets[lightQBar].p4() + jets[b].p4()).pt()   , weight);
	// top eta
	fillValue("topQuarkEta"  , (jets[lightQ].p4() + jets[lightQBar].p4() + jets[b].p4()).eta()  , weight);
	// top phi
	fillValue("topQuarkPhi"  , (jets[lightQ].p4() + jets[lightQBar].p4() + jets[b].p4()).phi()  , weight);
	// top mass
	fillValue("topQuarkMass" , (jets[lightQ].p4() + jets[lightQBar].p4() + jets[b].p4()).mass() , weight);
	// top mass hypo vs. reco
	fillValue("topMassHypoReco" , (jets[lightQ].p4() + jets[lightQBar].p4() + jets[b].p4()).mass() , tops.top(hypo_)->mass() , weight);
	// btag of b-jet with lower btag vs. di-jet-mass of corresponding w candidate
	if( jets[b].bDiscriminator(bTagAlgo_) < jets[bBar].bDiscriminator(bTagAlgo_) ){
	  fillValue("bTagVsMjjW" , (jets[lightQ].p4() + jets[lightQBar].p4()).mass(), jets[b].bDiscriminator(bTagAlgo_) , weight);
	}
      }
    }
    // make sure all the light quark indecies are in the range of the jet collection
    if( lightP >= 0 && lightP < (int)jets.size() && lightPBar >= 0 && lightPBar < (int)jets.size() ){
      // W pt
      fillValue("wPt"   , (jets[lightP].p4() + jets[lightPBar].p4()).pt()   , weight);
      // W eta
      fillValue("wEta"  , (jets[lightP].p4() + jets[lightPBar].p4()).eta()  , weight);
      // W phi
      fillValue("wPhi"  , (jets[lightP].p4() + jets[lightPBar].p4()).phi()  , weight);
      // W mass
      fillValue("wMass" , (jets[lightP].p4() + jets[lightPBar].p4()).mass() , weight);

      // theta* of W boson
      double thetaStar1 = thetaStar(jets[lightP].p4() + jets[lightPBar].p4(), jets[lightP].p4(), jets[lightPBar].p4());
      fillValue("thetaStarMinus",thetaStar1 , weight);
      // cos(theta*) of W boson
      fillValue("cosThetaStarMinus", cos(thetaStar1) , weight);

      // make sure the b quark index is in the range of the jet collection
      if( bBar >= 0 && bBar < (int)jets.size() ){
      	// top pt
	fillValue("topQuarkPt"   , (jets[lightP].p4() + jets[lightPBar].p4() + jets[bBar].p4()).pt()   , weight);
	// top eta
	fillValue("topQuarkEta"  , (jets[lightP].p4() + jets[lightPBar].p4() + jets[bBar].p4()).eta()  , weight);
	// top phi
	fillValue("topQuarkPhi"  , (jets[lightP].p4() + jets[lightPBar].p4() + jets[bBar].p4()).phi()  , weight);
	// top mass
	fillValue("topBarQuarkMass" , (jets[lightP].p4() + jets[lightPBar].p4() + jets[bBar].p4()).mass() , weight);
	// top mass hypo vs. reco
	fillValue("topMassHypoReco" , (jets[lightP].p4() + jets[lightPBar].p4() + jets[bBar].p4()).mass() , tops.topBar(hypo_)->mass() , weight);
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
