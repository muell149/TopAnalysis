#include "DataFormats/Math/interface/deltaPhi.h"
#include <Math/VectorUtil.h>
#include <Math/Boost.h>
#include "TopAnalysis/TopAnalyzer/interface/TopKinematics.h"

/// default constructor for generator level analysis in fw lite
TopKinematics::TopKinematics() : hypoKey_(""), matchForStabilityAndPurity_(false) 
{
}

/// default constructor for reco level analysis in fw lite
TopKinematics::TopKinematics(const std::string& hypoKey, const bool& matchForStabilityAndPurity) : hypoKey_(hypoKey), matchForStabilityAndPurity_(matchForStabilityAndPurity) 
{
}

/// default constructor for full fw
TopKinematics::TopKinematics(const edm::ParameterSet& cfg) :
  hypoKey_( cfg.getParameter<std::string>("hypoKey") ),
  matchForStabilityAndPurity_( cfg.getParameter<bool>("matchForStabilityAndPurity") )
{
}

/// histogramm booking for fwlite 
void TopKinematics::book()
{
  /** 
      Top Variables for Cross Section Measurement
  **/
  // top pt (at the moment both top candidates are filled in one histogram)
  hists_["topPt"      ] = new TH1F( "topPt"      , "topPt"      ,   9, CrossSection::topPt      );
  // top y (at the moment both top candidates are filled in one histogram)
  hists_["topY"       ] = new TH1F( "topY"       , "topY"       ,  10, CrossSection::topY       );
  // top phi (at the moment both top candidates are filled in one histogram)
  hists_["topPhi"     ] = new TH1F( "topPhi"     , "topPhi"     ,   6, CrossSection::topPhi     );
  // angle between top and the corresponding W
  hists_["topWAngle"  ] = new TH1F( "topWAngle"  , "topWAngle"  ,   6, CrossSection::topWAngle  );
  // ttbar pair pt
  hists_["ttbarPt"    ] = new TH1F( "ttbarPt"    , "ttbarPt"    ,   8, CrossSection::ttbarPt    );
  // ttbar pair y
  hists_["ttbarY"     ] = new TH1F( "ttbarY"     , "ttbarY"     ,  10, CrossSection::ttbarY     );
  // ttbar pair phi
  hists_["ttbarPhi"   ] = new TH1F( "ttbarPhi"   , "ttbarPhi"   ,   6, CrossSection::ttbarPhi   );
  // ttbar pair invariant mass
  hists_["ttbarMass"  ] = new TH1F( "ttbarMass"  , "ttbarMass"  ,   6, CrossSection::ttbarMass  );
  // deltaPhi between both top quarks
  hists_["ttbarDelPhi"] = new TH1F( "ttbarDelPhi", "ttbarDelPhi",   6, CrossSection::ttbarDelPhi);
  // deltaY between both top quarks
  hists_["ttbarDelY"  ] = new TH1F( "ttbarDelY"  , "ttbarDelY"  ,  10,     -5.,      5.         );
  // sum of y of both top quarks
  hists_["ttbarSumY"  ] = new TH1F( "ttbarSumY"  , "ttbarSumY"  ,  10,     -5.,      5.         );
  // HT of the 4 jets assigned to the ttbar decay
  hists_["ttbarHT"    ] = new TH1F( "ttbarHT"    , "ttbarHT"    ,   6, CrossSection::ttbarHT    );


  /**
     Top Variables for Cross Checks
  **/
  // pt of the hadronically decaying top candidate
  hists_["topPtHad_"  ] = new TH1F( "topPtHad_"  , "topPtHad_"  ,  9 , CrossSection::topPt     );
  // y  of the hadronically decaying top candidate
  hists_["topYHad_"   ] = new TH1F( "topYHad_"   , "topYHad_"   , 10 , CrossSection::topY      );
  // y  of the hadronically decaying top candidate
  hists_["topPhiHad_" ] = new TH1F( "topPhiHad_" , "topPhiHad_" ,  6 , CrossSection::topPhi    );
  // pt of the leptonically decaying top candidate
  hists_["topPtLep_"  ] = new TH1F( "topPtLep_"  , "topPtLep_"  ,  9 , CrossSection::topPt     );
  // y  of the leptonically decaying top candidate
  hists_["topYLep_"   ] = new TH1F( "topYLep_"   , "topYLep_"   , 10 , CrossSection::topY      );
  // y  of the leptonically decaying top candidate
  hists_["topPhiLep_" ] = new TH1F( "topPhiLep_" , "topPhiLep_" ,  6 , CrossSection::topPhi    );

  /** 
      Correlation Plots
  **/
  // gen-rec level correlation top pt
  corrs_["topPt_"    ] = new TH2F( "topPt_"    , "topPt_"    ,  400,    0.,  400.,     400,   0.,  400.);
  // gen-rec level correlation top y
  corrs_["topY_"     ] = new TH2F( "topY_"     , "topY_"     ,  800,   -4.,    4.,     800,  -4.,    4.);
  // gen-rec level correlation top phi
  corrs_["topPhi_"   ] = new TH2F( "topPhi_"   , "topPhi_"   ,  628, -3.14,  3.14,     628,-3.14,  3.14);
  // gen-rec level correlation angle between top and the corresponding W
  corrs_["topWAngle_"] = new TH2F( "topWAngle_", "topWAngle_",  314,    0.,  3.14,     314,   0.,  3.14);
  // gen-rec level correlation ttbar pt
  corrs_["ttbarPt_"  ] = new TH2F( "ttbarPt_"  , "ttbarPt_"  ,  200,    0.,  200.,     200,   0.,  200.);
  // gen-rec level correlation ttbar y
  corrs_["ttbarY_"   ] = new TH2F( "ttbarY_"   , "ttbarY_"   , 1000,   -5.,    5.,    1000,  -5.,    5.);
  // gen-rec level correlation ttbar mass
  corrs_["ttbarMass_"] = new TH2F( "ttbarMass_", "ttbarMass_",  700,  300., 1000.,     700, 300., 1000.);
  // gen-rec level correlation HT of the 4 jets assigned to the ttbar decay
  corrs_["ttbarHT_"  ] = new TH2F( "ttbarHT_"  , "ttbarHT_"  , 1000,    0., 1000.,    1000,   0., 1000.);
  // gen-rec level correlation ttbar deltaPhi
  corrs_["ttbarDelPhi_"]= new TH2F( "ttbarDelPhi_", "ttbarDelPhi_", 628, -3.14,  3.14,     628,-3.14,  3.14);
  // gen-rec level correlation ttbar deltaY
  corrs_["ttbarDelY_" ] = new TH2F( "ttbarDelY_"  , "ttbarDelY_" , 1000,   -5.,    5.,    1000,  -5.,    5.);
  // gen-rec level correlation ttbar sumY
  corrs_["ttbarSumY_" ] = new TH2F( "ttbarSumY_"  , "ttbarSumY_" , 1000,   -5.,    5.,    1000,  -5.,    5.);

}

/// histogramm booking for fw
void TopKinematics::book(edm::Service<TFileService>& fs)
{
  /** 
      Top Variables for Cross Section Measurement
  **/
  // top pt (at the moment both top candidates are filled in one histogram)
  hists_["topPt"      ] = fs->make<TH1F>( "topPt"       , "topPt"       ,   9, CrossSection::topPt      );
  // top y (at the moment both top candidates are filled in one histogram)
  hists_["topY"       ] = fs->make<TH1F>( "topY"        , "topY"        ,  10, CrossSection::topY       );
  // top phi (at the moment both top candidates are filled in one histogram)
  hists_["topPhi"     ] = fs->make<TH1F>( "topPhi"      , "topPhi"      ,   6, CrossSection::topPhi     );
  // top angle between top and the corresponding W in top rest frame
  hists_["topWAngle"  ] = fs->make<TH1F>( "topWAngle"   , "topWAngle"   ,   6, CrossSection::topWAngle  );
  // ttbar pair pt
  hists_["ttbarPt"    ] = fs->make<TH1F>( "ttbarPt"     , "ttbarPt"     ,   8, CrossSection::ttbarPt    );
  // ttbar pair y
  hists_["ttbarY"     ] = fs->make<TH1F>( "ttbarY"      , "ttbarY"      ,  10, CrossSection::ttbarY     );
  // ttbar pair phi
  hists_["ttbarPhi"   ] = fs->make<TH1F>( "ttbarPhi"    , "ttbarPhi"    ,   6, CrossSection::ttbarPhi   );
  // ttbar pair invariant mass
  hists_["ttbarMass"  ] = fs->make<TH1F>( "ttbarMass"   , "ttbarMass"   ,   6, CrossSection::ttbarMass  );
  // deltaPhi between both top quarks
  hists_["ttbarDelPhi"] = fs->make<TH1F>( "ttbarDelPhi" , "ttbarDelPhi" ,   6, CrossSection::ttbarDelPhi);
  // deltaY between both top quarks
  hists_["ttbarDelY"  ] = fs->make<TH1F>( "ttbarDelY"   , "ttbarDelY"   ,  10,     -5.,      5.         );
  // sum of y of both top quarks
  hists_["ttbarSumY"  ] = fs->make<TH1F>( "ttbarSumY"   , "ttbarSumY"   ,  10,     -5.,      5.         );
  // HT of the 4 jets assigned to the ttbar decay
  hists_["ttbarHT"    ] = fs->make<TH1F>( "ttbarHT"     , "ttbarHT"     ,   6, CrossSection::ttbarHT    );

  /**
     Top Variables for Cross Checks
  **/
  // pt of the hadronically decaying top candidate
  hists_["topPtHad_"  ] = fs->make<TH1F>( "topPtHad_"   , "topPtHad_"  ,   9 , CrossSection::topPt     );
  // y  of the hadronically decaying top candidate
  hists_["topYHad_"   ] = fs->make<TH1F>( "topYHad_"    , "topYHad_"   ,  10 , CrossSection::topY      );
  // y  of the hadronically decaying top candidate
  hists_["topPhiHad_" ] = fs->make<TH1F>( "topPhiHad_"  , "topPhiHad_" ,   6 , CrossSection::topPhi    );

  // pt of the leptonically decaying top candidate
  hists_["topPtLep_"  ] = fs->make<TH1F>( "topPtLep_"   , "topPtLep_"  ,   9 , CrossSection::topPt     );
  // y  of the leptonically decaying top candidate
  hists_["topYLep_"   ] = fs->make<TH1F>( "topYLep_"    , "topYLep_"   ,  10 , CrossSection::topY      );
  // y  of the leptonically decaying top candidate
  hists_["topPhiLep_" ] = fs->make<TH1F>( "topPhiLep_"  , "topPhiLep_" ,   6 , CrossSection::topPhi    );


  /** 
      Correlation Plots
  **/
  // gen-rec level correlation top pt
  corrs_["topPt_"     ] = fs->make<TH2F>( "topPt_"      , "topPt_"     ,  400,    0.,  400.,     400,   0.,  400.);
  // gen-rec level correlation top y
  corrs_["topY_"      ] = fs->make<TH2F>( "topY_"       , "topY_"      ,  800,   -4.,    4.,     800,  -4.,    4.);
  // gen-rec level correlation top phi
  corrs_["topPhi_"    ] = fs->make<TH2F>( "topPhi_"     , "topPhi_"    ,  628, -3.14,  3.14,     628,-3.14,  3.14);
  // gen-rec level correlation angle between top and the corresponding W in top rest frame
  corrs_["topWAngle_" ] = fs->make<TH2F>( "topWAngle_"  , "topWAngle_" ,  314,    0.,  3.14,     314,   0.,  3.14);
  // gen-rec level correlation ttbar pt
  corrs_["ttbarPt_"   ] = fs->make<TH2F>( "ttbarPt_"    , "ttbarPt_"   ,  200,    0.,  200.,     200,   0.,  200.);
  // gen-rec level correlation ttbar y
  corrs_["ttbarY_"    ] = fs->make<TH2F>( "ttbarY_"     , "ttbarY_"    , 1000,   -5.,    5.,    1000,  -5.,    5.);
  // gen-rec level correlation ttbar mass
  corrs_["ttbarMass_" ] = fs->make<TH2F>( "ttbarMass_"  , "ttbarMass_" ,  700,  300., 1000.,     700, 300., 1000.);
  // gen-rec level correlation HT of the 4 jets assigned to the ttbar decay
  corrs_["ttbarHT_"   ] = fs->make<TH2F>( "ttbarHT_"    , "ttbarHT_"   , 1000,    0., 1000.,    1000,   0., 1000.);
  // gen-rec level correlation ttbar deltaPhi
  corrs_["ttbarDelPhi_"]= fs->make<TH2F>( "ttbarDelPhi_", "ttbarDelPhi_", 628, -3.14,  3.14,     628,-3.14,  3.14);
  // gen-rec level correlation ttbar deltaY
  corrs_["ttbarDelY_" ] = fs->make<TH2F>( "ttbarDelY_"  , "ttbarDelY_" , 1000,   -5.,    5.,    1000,  -5.,    5.);
  // gen-rec level correlation ttbar sumY
  corrs_["ttbarSumY_" ] = fs->make<TH2F>( "ttbarSumY_"  , "ttbarSumY_" , 1000,   -5.,    5.,    1000,  -5.,    5.);

}


/// histogram filling interface for generator level for access with fwlite or full framework
void
TopKinematics::fill(const TtGenEvent& tops, const double& weight)
{
  // make sure to have a ttbar pair belonging to the semi-leptonic decay channel with 
  // a muon in the final state
  if( tops.isSemiLeptonic(WDecay::kMuon) && tops.leptonicDecayB()){
    double HT = tops.leptonicDecayB()->pt() + tops.hadronicDecayB()->pt() + tops.hadronicDecayQuark()->pt() + tops.hadronicDecayQuarkBar()->pt();
    fill(tops.leptonicDecayTop(), tops.hadronicDecayTop(), tops.leptonicDecayW(), tops.hadronicDecayW(), HT, weight);
  }
}

/// histogram filling interface for reconstruction level for access with fwlite or full framework
void
TopKinematics::fill(const TtSemiLeptonicEvent& tops, const double& weight)
{
  // make sure to have a valid hypothesis on reconstruction level. If this is the case
  // fill matched (for stability & purity determination) or normal depending on the 
  // value of matchForStabilityAndPurity_
  if( tops.isHypoValid(hypoKey_) ){
    double HTrec = tops.leptonicDecayB(hypoKey_)->pt() + tops.hadronicDecayB(hypoKey_)->pt() + tops.hadronicDecayQuark(hypoKey_)->pt() + tops.hadronicDecayQuarkBar(hypoKey_)->pt();
    if( tops.genEvent().isAvailable() && tops.genEvent()->isSemiLeptonic(WDecay::kMuon) && tops.leptonicDecayB() && matchForStabilityAndPurity_){
      double HTgen = tops.leptonicDecayB()->pt() + tops.hadronicDecayB()->pt() + tops.hadronicDecayQuark()->pt() + tops.hadronicDecayQuarkBar()->pt();
      fill(tops.leptonicDecayTop(hypoKey_), tops.leptonicDecayTop(), tops.hadronicDecayTop(hypoKey_), tops.hadronicDecayTop(), tops.leptonicDecayW(hypoKey_), tops.leptonicDecayW(), tops.hadronicDecayW(hypoKey_), tops.hadronicDecayW(), HTrec, HTgen, weight);

      // fill rec versus gen level correlation plots
      reco::Particle::LorentzVector genTtbar = tops.hadronicDecayTop(        )->p4()+tops.leptonicDecayTop(        )->p4();
      reco::Particle::LorentzVector recTtbar = tops.hadronicDecayTop(hypoKey_)->p4()+tops.leptonicDecayTop(hypoKey_)->p4();

      /** 
	  filling 2dim correlation plots ttbar
      **/
      corrs_.find("ttbarPt_"  )->second->Fill( genTtbar.pt()        , recTtbar.pt()       , weight );
      // fill y correlation plot for ttbar pair
      corrs_.find("ttbarY_"   )->second->Fill( genTtbar.Rapidity()  , recTtbar.Rapidity() , weight );
      // fill mass correlation plot for ttbar pair
      corrs_.find("ttbarMass_")->second->Fill( genTtbar.mass()      , recTtbar.mass()     , weight );    
      // fill HT correlation plot for the 4 jets assigned to the ttbar decay
      corrs_.find("ttbarHT_"  )->second->Fill( HTgen                , HTrec               , weight ); 
      // fill pt correlation plot for hadronic top candidate
      corrs_.find("topPt_"    )->second->Fill( tops.hadronicDecayTop()->pt()      , tops.hadronicDecayTop(hypoKey_)->pt()      , weight );
      // fill pt correlation plot for leptonic top candidate
      corrs_.find("topPt_"    )->second->Fill( tops.leptonicDecayTop()->pt()      , tops.leptonicDecayTop(hypoKey_)->pt()      , weight );
      // fill y correlation plot for hadronic top candidate
      corrs_.find("topY_"     )->second->Fill( tops.hadronicDecayTop()->rapidity(), tops.hadronicDecayTop(hypoKey_)->rapidity(), weight );
      // fill y correlation plot for leptonic top candidate
      corrs_.find("topY_"     )->second->Fill( tops.leptonicDecayTop()->rapidity(), tops.leptonicDecayTop(hypoKey_)->rapidity(), weight );
      // fill phi correlation plot for hadronic top candidate
      corrs_.find("topPhi_"   )->second->Fill( tops.hadronicDecayTop()->phi()     , tops.hadronicDecayTop(hypoKey_)->phi()     , weight );
      // fill phi correlation plot for leptonic top candidate
      corrs_.find("topPhi_"   )->second->Fill( tops.leptonicDecayTop()->phi()     , tops.leptonicDecayTop(hypoKey_)->phi()     , weight );
      // fill deltaPhi correlation plot for ttbar pair
      corrs_.find("ttbarDelPhi_")->second->Fill( deltaPhi(tops.leptonicDecayTop()->phi(), tops.hadronicDecayTop()->phi()), deltaPhi(tops.leptonicDecayTop(hypoKey_)->phi(), tops.hadronicDecayTop(hypoKey_)->phi()), weight );
      // fill deltaY correlation plot for ttbar
      corrs_.find("ttbarDelY_"  )->second->Fill( tops.leptonicDecayTop()->rapidity()-tops.hadronicDecayTop()->rapidity(), tops.leptonicDecayTop(hypoKey_)->rapidity()-tops.hadronicDecayTop(hypoKey_)->rapidity(), weight );
      // fill sumY correlation plot for ttbar p
      corrs_.find("ttbarSumY_"  )->second->Fill( tops.leptonicDecayTop()->rapidity()+tops.hadronicDecayTop()->rapidity(), tops.leptonicDecayTop(hypoKey_)->rapidity()+tops.hadronicDecayTop(hypoKey_)->rapidity(), weight );

      // boost the W to the top rest frame
      ROOT::Math::Boost CoMBoostRecHadTop(tops.hadronicDecayTop(hypoKey_)->p4().BoostToCM());
      ROOT::Math::Boost CoMBoostGenHadTop(tops.hadronicDecayTop()->p4().BoostToCM());
      ROOT::Math::Boost CoMBoostRecLepTop(tops.leptonicDecayTop(hypoKey_)->p4().BoostToCM());
      ROOT::Math::Boost CoMBoostGenLepTop(tops.leptonicDecayTop()->p4().BoostToCM());
      ROOT::Math::Boost CoMBoostRecTtbar(recTtbar.BoostToCM());
      ROOT::Math::Boost CoMBoostGenTtbar(genTtbar.BoostToCM());
      reco::Particle::LorentzVector recHadronicDecayWBoosted = tops.hadronicDecayW(hypoKey_)->p4();
      reco::Particle::LorentzVector genHadronicDecayWBoosted = tops.hadronicDecayW()->p4();
      reco::Particle::LorentzVector recLeptonicDecayWBoosted = tops.leptonicDecayW(hypoKey_)->p4();
      reco::Particle::LorentzVector genLeptonicDecayWBoosted = tops.leptonicDecayW()->p4();
      reco::Particle::LorentzVector recHadronicDecayTopBoosted = tops.hadronicDecayTop(hypoKey_)->p4();
      reco::Particle::LorentzVector genHadronicDecayTopBoosted = tops.hadronicDecayTop()->p4();
      reco::Particle::LorentzVector recLeptonicDecayTopBoosted = tops.leptonicDecayTop(hypoKey_)->p4();
      reco::Particle::LorentzVector genLeptonicDecayTopBoosted = tops.leptonicDecayTop()->p4();
      recHadronicDecayWBoosted = CoMBoostRecHadTop(recHadronicDecayWBoosted);
      genHadronicDecayWBoosted = CoMBoostGenHadTop(genHadronicDecayWBoosted);
      recLeptonicDecayWBoosted = CoMBoostRecLepTop(recLeptonicDecayWBoosted);
      genLeptonicDecayWBoosted = CoMBoostGenLepTop(genLeptonicDecayWBoosted);
      recHadronicDecayTopBoosted = CoMBoostRecTtbar(recHadronicDecayTopBoosted);
      genHadronicDecayTopBoosted = CoMBoostGenTtbar(genHadronicDecayTopBoosted);
      recLeptonicDecayTopBoosted = CoMBoostRecTtbar(recLeptonicDecayTopBoosted);
      genLeptonicDecayTopBoosted = CoMBoostGenTtbar(genLeptonicDecayTopBoosted);

      // fill topWangletop correlation plot for hadronic top candidate
      corrs_.find("topWAngle_")->second->Fill( ROOT::Math::VectorUtil::Angle(genHadronicDecayTopBoosted, genHadronicDecayWBoosted), ROOT::Math::VectorUtil::Angle(recHadronicDecayTopBoosted, recHadronicDecayWBoosted), weight );
      // fill topWangletop correlation plot for leptonic top candidate
      corrs_.find("topWAngle_")->second->Fill( ROOT::Math::VectorUtil::Angle(genLeptonicDecayTopBoosted, genLeptonicDecayWBoosted), ROOT::Math::VectorUtil::Angle(recLeptonicDecayTopBoosted, recLeptonicDecayWBoosted), weight );

    } 
    else{
      fill(tops.leptonicDecayTop(hypoKey_), tops.hadronicDecayTop(hypoKey_), tops.leptonicDecayW(hypoKey_), tops.hadronicDecayW(hypoKey_), HTrec, weight);
    }
  }
}

/// histogram filling for topA, topB candidate
void
TopKinematics::fill(const reco::Candidate* leptonicTop, const reco::Candidate* hadronicTop, const reco::Candidate* leptonicW, const reco::Candidate* hadronicW, double HT, const double& weight)
{
  /** 
      Fill Top Variables for Cross Section Measurement
  **/
  reco::Particle::LorentzVector ttBar = leptonicTop->p4() + hadronicTop->p4();
  // boost the W to the top rest frame
  ROOT::Math::Boost CoMBoostHadTop(hadronicTop->p4().BoostToCM());
  ROOT::Math::Boost CoMBoostLepTop(leptonicTop->p4().BoostToCM());
  ROOT::Math::Boost CoMBoostTtbar(ttBar.BoostToCM());
  reco::Particle::LorentzVector HadronicDecayWBoosted = hadronicW->p4();
  reco::Particle::LorentzVector LeptonicDecayWBoosted = leptonicW->p4();
  reco::Particle::LorentzVector HadronicDecayTopBoosted = hadronicTop->p4();
  reco::Particle::LorentzVector LeptonicDecayTopBoosted = leptonicTop->p4();
  HadronicDecayWBoosted = CoMBoostHadTop(HadronicDecayWBoosted);
  LeptonicDecayWBoosted = CoMBoostLepTop(LeptonicDecayWBoosted);
  HadronicDecayTopBoosted = CoMBoostTtbar(HadronicDecayTopBoosted);
  LeptonicDecayTopBoosted = CoMBoostTtbar(LeptonicDecayTopBoosted);

  // fill top pt for leptonicTop candidate in combined histogram
  hists_.find("topPt"      )->second->Fill( leptonicTop->p4().pt ()      , weight );
  // fill top y for leptonicTop candidate in combined histogram
  hists_.find("topY"       )->second->Fill( leptonicTop->p4().Rapidity() , weight );
  // fill top phi for leptonicTop candidate in combined histogram
  hists_.find("topPhi"     )->second->Fill( leptonicTop->p4().phi()      , weight );
  // fill angle between top and the corresponding W in top rest frame for leptonicTop candidate in combined histogram
  hists_.find("topWAngle"  )->second->Fill( ROOT::Math::VectorUtil::Angle(LeptonicDecayTopBoosted, LeptonicDecayWBoosted), weight );
  // fill top pt for hadronicTop candidate in combined histogram
  hists_.find("topPt"      )->second->Fill( hadronicTop->p4().pt ()      , weight );
  // fill top y for hadronicTop candidate in combined histogram
  hists_.find("topY"       )->second->Fill( hadronicTop->p4().Rapidity() , weight );
  // fill top phi for hadronicTop candidate in combined histogram
  hists_.find("topPhi"     )->second->Fill( hadronicTop->p4().phi()      , weight );
  // fill angle between top and the corresponding W in top rest frame for hadronicTop candidate in combined histogram
  hists_.find("topWAngle"  )->second->Fill( ROOT::Math::VectorUtil::Angle(HadronicDecayTopBoosted, HadronicDecayWBoosted), weight );
  // fill top pt for leptonicTop candidate in separate histogram
  hists_.find("topPtLep_"  )->second->Fill( leptonicTop->p4().pt ()      , weight );
  // fill top y for leptonicTop candidate in separate histogram
  hists_.find("topYLep_"   )->second->Fill( leptonicTop->p4().Rapidity() , weight );
  // fill top phi for leptonicTop candidate in separate histogram
  hists_.find("topPhiLep_" )->second->Fill( leptonicTop->p4().phi()      , weight );
  // fill top pt for hadronicTop candidate in separate histogram
  hists_.find("topPtHad_"  )->second->Fill( hadronicTop->p4().pt ()      , weight );
  // fill top y for hadronicTop candidate in separate histogram
  hists_.find("topYHad_"   )->second->Fill( hadronicTop->p4().Rapidity() , weight );
  // fill top phi for hadronicTop candidate in separate histogram
  hists_.find("topPhiHad_" )->second->Fill( hadronicTop->p4().phi()      , weight );
  // fill ttbar pt
  hists_.find("ttbarPt"    )->second->Fill( ttBar.pt  ()          , weight );
  // fill ttbar y
  hists_.find("ttbarY"     )->second->Fill( ttBar.Rapidity()      , weight );
  // fill ttbar phi
  hists_.find("ttbarPhi"   )->second->Fill( ttBar.phi ()          , weight );
  // fill ttbar invariant mass
  hists_.find("ttbarMass"  )->second->Fill( ttBar.mass()          , weight );
  // fill deltaPhi between both top quarks 
  hists_.find("ttbarDelPhi")->second->Fill( deltaPhi(leptonicTop->phi(), hadronicTop->phi()) , weight );
  // fill deltaY between both top quarks 
  hists_.find("ttbarDelY"  )->second->Fill( leptonicTop->rapidity()-hadronicTop->rapidity()  , weight );
  // fill sum of y of both top quarks 
  hists_.find("ttbarSumY"  )->second->Fill( leptonicTop->rapidity()+hadronicTop->rapidity()  , weight );
  // fill HT of the 4 jets assigned to the ttbar decay
  hists_.find("ttbarHT"    )->second->Fill( HT  , weight );
}

/// histogram filling for candidate topA and topB (for stability and purity calculation)
void 
TopKinematics::fill(const reco::Candidate* leptonicTopRec, const reco::Candidate* leptonicTopGen, const reco::Candidate* hadronicTopRec, const reco::Candidate* hadronicTopGen, const reco::Candidate* leptonicWRec, const reco::Candidate* leptonicWGen, const reco::Candidate* hadronicWRec, const reco::Candidate* hadronicWGen, double HTrec, double HTgen, const double& weight)
{
  /** 
      Fill Top Variables for Cross Section Measurement
  **/
  reco::Particle::LorentzVector genTtBar = leptonicTopGen->p4() + hadronicTopGen->p4();
  reco::Particle::LorentzVector recTtBar = leptonicTopRec->p4() + hadronicTopRec->p4();
  // boost the W to the top rest frame
  ROOT::Math::Boost CoMBoostRecHadTop(hadronicTopRec->p4().BoostToCM());
  ROOT::Math::Boost CoMBoostGenHadTop(hadronicTopGen->p4().BoostToCM());
  ROOT::Math::Boost CoMBoostRecLepTop(leptonicTopRec->p4().BoostToCM());
  ROOT::Math::Boost CoMBoostGenLepTop(leptonicTopGen->p4().BoostToCM());
  ROOT::Math::Boost CoMBoostRecTtbar(recTtBar.BoostToCM());
  ROOT::Math::Boost CoMBoostGenTtbar(genTtBar.BoostToCM());
  reco::Particle::LorentzVector recHadronicDecayWBoosted = hadronicWRec->p4();
  reco::Particle::LorentzVector genHadronicDecayWBoosted = hadronicWGen->p4();
  reco::Particle::LorentzVector recLeptonicDecayWBoosted = leptonicWRec->p4();
  reco::Particle::LorentzVector genLeptonicDecayWBoosted = leptonicWGen->p4();
  reco::Particle::LorentzVector recHadronicDecayTopBoosted = hadronicTopRec->p4();
  reco::Particle::LorentzVector genHadronicDecayTopBoosted = hadronicTopGen->p4();
  reco::Particle::LorentzVector recLeptonicDecayTopBoosted = leptonicTopRec->p4();
  reco::Particle::LorentzVector genLeptonicDecayTopBoosted = leptonicTopGen->p4();
  recHadronicDecayWBoosted = CoMBoostRecHadTop(recHadronicDecayWBoosted);
  genHadronicDecayWBoosted = CoMBoostGenHadTop(genHadronicDecayWBoosted);
  recLeptonicDecayWBoosted = CoMBoostRecLepTop(recLeptonicDecayWBoosted);
  genLeptonicDecayWBoosted = CoMBoostGenLepTop(genLeptonicDecayWBoosted);
  recHadronicDecayTopBoosted = CoMBoostRecTtbar(recHadronicDecayTopBoosted);
  genHadronicDecayTopBoosted = CoMBoostGenTtbar(genHadronicDecayTopBoosted);
  recLeptonicDecayTopBoosted = CoMBoostRecTtbar(recLeptonicDecayTopBoosted);
  genLeptonicDecayTopBoosted = CoMBoostGenTtbar(genLeptonicDecayTopBoosted);

  // fill top pt for topA candidate in combined histogram
  match( hists_.find("topPt"      )->second , leptonicTopRec->p4().pt ()      , leptonicTopGen->p4().pt ()      , weight );
  // fill top y for topA candidate in combined histogram
  match( hists_.find("topY"       )->second , leptonicTopRec->p4().Rapidity() , leptonicTopGen->p4().Rapidity() , weight );
  // fill top phi for topA candidate in combined histogram
  match( hists_.find("topPhi"     )->second , leptonicTopRec->p4().phi()      , leptonicTopGen->p4().phi()      , weight );
  // fill angle between top and the corresponding W in top rest frame for topA candidate in combined histogram
  match( hists_.find("topWAngle"  )->second , ROOT::Math::VectorUtil::Angle(recLeptonicDecayTopBoosted, recLeptonicDecayWBoosted), ROOT::Math::VectorUtil::Angle(genLeptonicDecayTopBoosted, genLeptonicDecayWBoosted), weight );
  // fill top pt for topB candidate in combined histogram
  match( hists_.find("topPt"      )->second , hadronicTopRec->p4().pt ()      , hadronicTopGen->p4().pt ()      , weight );
  // fill top y for topB candidate in combined histogram
  match( hists_.find("topY"       )->second , hadronicTopRec->p4().Rapidity() , hadronicTopGen->p4().Rapidity() , weight );
  // fill top phi for topB candidate in combined histogram
  match( hists_.find("topPhi"     )->second , hadronicTopRec->p4().phi()      , hadronicTopGen->p4().phi()      , weight );
  // fill angle between top and the corresponding Win top rest frame for topB candidate in combined histogram
  match( hists_.find("topWAngle"  )->second , ROOT::Math::VectorUtil::Angle(recHadronicDecayTopBoosted, recHadronicDecayWBoosted), ROOT::Math::VectorUtil::Angle(genHadronicDecayTopBoosted, genHadronicDecayWBoosted), weight );
  // fill top pt for topA candidate in separate histogram
  match( hists_.find("topPtLep_"  )->second , leptonicTopRec->p4().pt ()      , leptonicTopGen->p4().pt ()      , weight );
  // fill top y for topA candidate in separate histogram
  match( hists_.find("topYLep_"   )->second , leptonicTopRec->p4().Rapidity() , leptonicTopGen->p4().Rapidity() , weight );
  // fill top phi for topA candidate in separate histogram
  match( hists_.find("topPhiLep_" )->second , leptonicTopRec->p4().phi()      , leptonicTopGen->p4().phi()      , weight );
  // fill top pt for topB candidate in separate histogram
  match( hists_.find("topPtHad_"  )->second , hadronicTopRec->p4().pt ()      , hadronicTopGen->p4().pt ()      , weight );
  // fill top y for topB candidate in separate histogram
  match( hists_.find("topYHad_"   )->second , hadronicTopRec->p4().Rapidity() , hadronicTopGen->p4().Rapidity() , weight );
  // fill top phi for topB candidate in separate histogram
  match( hists_.find("topPhiHad_" )->second , hadronicTopRec->p4().phi()      , hadronicTopGen->p4().phi()      , weight );
  // fill ttbar pt
  match( hists_.find("ttbarPt"    )->second , recTtBar.pt  ()          , genTtBar.pt  ()          , weight );
  // fill ttbar y
  match( hists_.find("ttbarY"     )->second , recTtBar.Rapidity ()     , genTtBar.Rapidity ()     , weight );
  // fill ttbar phi
  match( hists_.find("ttbarPhi"   )->second , recTtBar.phi ()          , genTtBar.phi ()          , weight );
  // fill ttbar invariant mass
  match( hists_.find("ttbarMass"  )->second , recTtBar.mass()          , genTtBar.mass()          , weight );
  // fill deltaPhi between both top quarks 
  match( hists_.find("ttbarDelPhi")->second , deltaPhi(leptonicTopRec->phi(), hadronicTopRec->phi()), deltaPhi(leptonicTopGen->phi(), hadronicTopGen->phi()), weight );
  // fill deltaY between both top quarks 
  match( hists_.find("ttbarDelY"  )->second , leptonicTopRec->rapidity()-hadronicTopRec->rapidity() , leptonicTopGen->rapidity()-hadronicTopGen->rapidity() , weight );
  // fill sum of y of both top quarks 
  match( hists_.find("ttbarSumY"  )->second , leptonicTopRec->rapidity()+hadronicTopRec->rapidity() , leptonicTopGen->rapidity()+hadronicTopGen->rapidity() , weight );
  // fill HT of the 4 jets assigned to the ttbar decay
  match( hists_.find("ttbarHT"    )->second , HTrec , HTgen , weight );
}

/// helper function to determine stability and purity
void 
TopKinematics::match(TH1* hist, const double& recValue, const double& genValue, const double& weight)
{
  // loop the bins of histogram 'hist'; note that the first bin
  // startsa with '1' and not with '0'
  for(int bin=1; bin<=hist->GetNbinsX(); ++bin){
    // determine lower and upper edge of the corresponding bin
    double lowerEdge = hist->GetBinLowEdge(bin);
    double upperEdge = hist->GetBinLowEdge(bin)+hist->GetBinWidth(bin);
    // only fill the histogram when the genValue & recValue fall into the same bin ('<=' for upper edge)
    if( (lowerEdge<genValue && genValue<=upperEdge) && (lowerEdge<recValue && recValue<=upperEdge) ){
      hist->Fill(recValue, weight);
      break;
    }
  }
}
