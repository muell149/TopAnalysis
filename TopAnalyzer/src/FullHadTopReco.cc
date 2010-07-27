#include "TopAnalysis/TopAnalyzer/interface/FullHadTopReco.h"
#include "AnalysisDataFormats/TopObjects/interface/TtFullHadEvtPartons.h"

/// default constructor for fw lite
FullHadTopReco::FullHadTopReco()
{
}

/// default constructor for full fw
FullHadTopReco::FullHadTopReco(const edm::ParameterSet& cfg) :
  hypo_    ( cfg.getParameter<std::string>( "hypo" ) ),
  bTagAlgo_( cfg.getParameter<std::string>( "bTagAlgo" ) )
{
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
  hists_["bQuarkPt"      ] = fs->make<TH1F>( "bQuarkPt"       , "bQuarkPt"       ,   50,  0. , 1000. );
  // b eta
  hists_["bQuarkEta"     ] = fs->make<TH1F>( "bQuarkEta"      , "bQuarkEta"      ,   30, -3. , 3.    );
  // b phi
  hists_["bQuarkPhi"     ] = fs->make<TH1F>( "bQuarkPhi"      , "bQuarkPhi"      ,   32, -3.2, 3.2   );
  // b mass
  hists_["bQuarkMass"    ] = fs->make<TH1F>( "bQuarkMass"     , "bQuarkMass"     ,   50,  0. , 100.  );
  // lightQuark pt
  hists_["lightQuarkPt"  ] = fs->make<TH1F>( "lightQuarkPt"   , "lightQuarkPt"   ,   50,  0. , 500.  );
  // lightQuark eta
  hists_["lightQuarkEta" ] = fs->make<TH1F>( "lightQuarkEta"  , "lightQuarkEta"  ,   30, -3. , 3.    );
  // lightQuark phi
  hists_["lightQuarkPhi" ] = fs->make<TH1F>( "lightQuarkPhi"  , "lightQuarkPhi"  ,   32, -3.2, 3.2   );
  // lightQuark mass
  hists_["lightQuarkMass"] = fs->make<TH1F>( "lightQuarkMass" , "lightQuarkMass" ,   50,  0. , 100.  );
  // top pt
  hists_["topQuarkPt"    ] = fs->make<TH1F>( "topQuarkPt"     , "topQuarkPt"     ,  100,  0. , 1000. );
  // top eta
  hists_["topQuarkEta"   ] = fs->make<TH1F>( "topQuarkEta"    , "topQuarkEta"    ,   30, -3. , 3.    );
  // top phi
  hists_["topQuarkPhi"   ] = fs->make<TH1F>( "topQuarkPhi"    , "topQuarkPhi"    ,   32, -3.2, 3.2   );
  // top mass
  hists_["topQuarkMass"  ] = fs->make<TH1F>( "topQuarkMass"   , "topQuarkMass"   ,   500,  0. , 1000.  );
  // top mass of hypothesis
  hists_["topQuarkMassHypo"] = fs->make<TH1F>( "topQuarkMassHypo" , "topQuarkMassHypo" ,   500,  0. , 1000.  );
  /// mtop hypo vs. mtop reco
  hists2D_["topMassHypoReco"] = fs->make<TH2F>( "topMassHypoReco" , "topMassHypoReco" ,  150, 100.,  400. , 150, 100., 400. );
  // W pt
  hists_["wPt"           ] = fs->make<TH1F>( "wPt"           , "wPt"             ,  100,  0. , 1000. );
  // W eta
  hists_["wEta"          ] = fs->make<TH1F>( "wEta"          , "wEta"            ,   30, -3. , 3.    );
  // W phi
  hists_["wPhi"          ] = fs->make<TH1F>( "wPhi"          , "wPhi"            ,   32, -3.2, 3.2   );
  // W mass
  hists_["wMass"         ] = fs->make<TH1F>( "wMass"         , "wMass"           ,  300,  0. , 600.  );
  // btag of b-jet with lower btag vs. di-jet-mass of corresponding w candidate
  hists2D_["bTagVsMjjW"    ] = fs->make<TH2F>( "bTagVsMjjW"    , "bTagVsMjjW"      ,  120, 74.4,  86.4, 50, 0. , 5.  );
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
    hists_.find("topQuarkMassHypo")->second->Fill( tops.top(hypo_)->mass() );
    // topBar mass of hypothesis
    hists_.find("topQuarkMassHypo")->second->Fill( tops.topBar(hypo_)->mass() );

    // make sure the b-jet index is in the range of the jet collection
    if( b >=0 && b < (int)jets.size() ){
      // b pt
      hists_.find("bQuarkPt"  )->second->Fill( jets[b].pt()   );
      // b eta
      hists_.find("bQuarkEta" )->second->Fill( jets[b].eta()  );
      // b phi
      hists_.find("bQuarkPhi" )->second->Fill( jets[b].phi()  );
      // b mass
      hists_.find("bQuarkMass")->second->Fill( jets[b].mass() );
    }
   // make sure the bBar-jet index is in the range of the jet collection
    if( bBar >= 0 && bBar< (int)jets.size() ){
      // bBar pt
      hists_.find("bQuarkPt"  )->second->Fill( jets[bBar].pt()   );
      // bBar eta
      hists_.find("bQuarkEta" )->second->Fill( jets[bBar].eta()  );
      // bBar phi
      hists_.find("bQuarkPhi" )->second->Fill( jets[bBar].phi()  );
      // bBar mass
      hists_.find("bQuarkMass")->second->Fill( jets[bBar].mass() );
    }
   // make sure the light quark index is in the range of the jet collection
    if( lightQ >= 0 && lightQ < (int)jets.size() ){
      // lightQuark pt
      hists_.find("lightQuarkPt"  )->second->Fill( jets[lightQ].pt()   );
      // lightQuark eta
      hists_.find("lightQuarkEta" )->second->Fill( jets[lightQ].eta()  );
      // lightQuark phi
      hists_.find("lightQuarkPhi" )->second->Fill( jets[lightQ].phi()  );
      // lightQuark mass
      hists_.find("lightQuarkMass")->second->Fill( jets[lightQ].mass() );
    }
    // make sure the light quark bar index is in the range of the jet collection
    if( lightQBar >= 0 && lightQBar< (int)jets.size() ){
      // lightQuark pt
      hists_.find("lightQuarkPt"  )->second->Fill( jets[lightQBar].pt()   );
      // lightQuark eta
      hists_.find("lightQuarkEta" )->second->Fill( jets[lightQBar].eta()  );
      // lightQuark phi
      hists_.find("lightQuarkPhi" )->second->Fill( jets[lightQBar].phi()  );
      // lightQuark mass
      hists_.find("lightQuarkMass")->second->Fill( jets[lightQBar].mass() );
    }
   // make sure the light quark index is in the range of the jet collection
    if( lightP >= 0 && lightP < (int)jets.size() ){
      // lightQuark pt
      hists_.find("lightQuarkPt"  )->second->Fill( jets[lightP].pt()   );
      // lightQuark eta
      hists_.find("lightQuarkEta" )->second->Fill( jets[lightP].eta()  );
      // lightQuark phi
      hists_.find("lightQuarkPhi" )->second->Fill( jets[lightP].phi()  );
      // lightQuark mass
      hists_.find("lightQuarkMass")->second->Fill( jets[lightP].mass() );
    }
    // make sure the light quark bar index is in the range of the jet collection
    if( lightPBar >= 0 && lightPBar < (int)jets.size() ){
      // lightQuark pt
      hists_.find("lightQuarkPt"  )->second->Fill( jets[lightPBar].pt()   );
      // lightQuark eta
      hists_.find("lightQuarkEta" )->second->Fill( jets[lightPBar].eta()  );
      // lightQuark phi
      hists_.find("lightQuarkPhi" )->second->Fill( jets[lightPBar].phi()  );
      // lightQuark mass
      hists_.find("lightQuarkMass")->second->Fill( jets[lightPBar].mass() );
    }
    // make sure all the light quark indecies for W are in the range of the jet collection
    if( lightQ >= 0 && lightQ < (int)jets.size() && lightQBar >= 0 && lightQBar < (int)jets.size() ){
      // W pt
      hists_.find("wPt"  )->second->Fill( (jets[lightQ].p4() + jets[lightQBar].p4()).pt()   );
      // W eta
      hists_.find("wEta" )->second->Fill( (jets[lightQ].p4() + jets[lightQBar].p4()).eta()  );
      // W phi
      hists_.find("wPhi" )->second->Fill( (jets[lightQ].p4() + jets[lightQBar].p4()).phi()  );
      // W mass
      hists_.find("wMass")->second->Fill( (jets[lightQ].p4() + jets[lightQBar].p4()).mass() );
      // make sure the b quark index is in the range of the jet collection
      if( b >= 0 && b < (int)jets.size() ){
      	// top pt
	hists_.find("topQuarkPt"  )->second->Fill( (jets[lightQ].p4() + jets[lightQBar].p4() + jets[b].p4()).pt()   );
	// top eta
	hists_.find("topQuarkEta" )->second->Fill( (jets[lightQ].p4() + jets[lightQBar].p4() + jets[b].p4()).eta()  );
	// top phi
	hists_.find("topQuarkPhi" )->second->Fill( (jets[lightQ].p4() + jets[lightQBar].p4() + jets[b].p4()).phi()  );
	// top mass
	hists_.find("topQuarkMass")->second->Fill( (jets[lightQ].p4() + jets[lightQBar].p4() + jets[b].p4()).mass() );
	// top mass hypo vs. reco
	hists2D_.find("topMassHypoReco")->second->Fill( (jets[lightQ].p4() + jets[lightQBar].p4() + jets[b].p4()).mass(), tops.top(hypo_)->mass() );
	// btag of b-jet with lower btag vs. di-jet-mass of corresponding w candidate
	if( jets[b].bDiscriminator(bTagAlgo_) < jets[bBar].bDiscriminator(bTagAlgo_)){
	  hists2D_.find("bTagVsMjjW")->second->Fill( (jets[lightQ].p4() + jets[lightQBar].p4()).mass(), jets[b].bDiscriminator("trackCountingHighPurBJetTags") );
	}
      }
    }
    // make sure all the light quark indecies are in the range of the jet collection
    if( lightP >= 0 && lightP < (int)jets.size() && lightPBar >= 0 && lightPBar < (int)jets.size() ){
      // W pt
      hists_.find("wPt"  )->second->Fill( (jets[lightP].p4() + jets[lightPBar].p4()).pt()   );
      // W eta
      hists_.find("wEta" )->second->Fill( (jets[lightP].p4() + jets[lightPBar].p4()).eta()  );
      // W phi
      hists_.find("wPhi" )->second->Fill( (jets[lightP].p4() + jets[lightPBar].p4()).phi()  );
      // W mass
      hists_.find("wMass")->second->Fill( (jets[lightP].p4() + jets[lightPBar].p4()).mass() );
      // make sure the b quark index is in the range of the jet collection
      if( bBar >= 0 && bBar < (int)jets.size() ){
      	// top pt
	hists_.find("topQuarkPt"  )->second->Fill( (jets[lightP].p4() + jets[lightPBar].p4() + jets[bBar].p4()).pt()   );
	// top eta
	hists_.find("topQuarkEta" )->second->Fill( (jets[lightP].p4() + jets[lightPBar].p4() + jets[bBar].p4()).eta()  );
	// top phi
	hists_.find("topQuarkPhi" )->second->Fill( (jets[lightP].p4() + jets[lightPBar].p4() + jets[bBar].p4()).phi()  );
	// top mass
	hists_.find("topQuarkMass")->second->Fill( (jets[lightP].p4() + jets[lightPBar].p4() + jets[bBar].p4()).mass() );
	// top mass hypo vs. reco
	hists2D_.find("topMassHypoReco")->second->Fill( (jets[lightP].p4() + jets[lightPBar].p4() + jets[bBar].p4()).mass(), tops.topBar(hypo_)->mass() );
	// btag of b-jet with lower btag vs. di-jet-mass of corresponding w candidate
	if( jets[bBar].bDiscriminator(bTagAlgo_) < jets[b].bDiscriminator(bTagAlgo_)){
	  hists2D_.find("bTagVsMjjW")->second->Fill( (jets[lightP].p4() + jets[lightPBar].p4()).mass(), jets[bBar].bDiscriminator("trackCountingHighPurBJetTags") );
	}
      }
    }
  }
}
