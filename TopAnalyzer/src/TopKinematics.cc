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
  hists_["topPt"       ] = new TH1F( "topPt"       , "topPt"       ,   9, CrossSection::topPt       );
  // top y (at the moment both top candidates are filled in one histogram)
  hists_["topY"        ] = new TH1F( "topY"        , "topY"        ,  10, CrossSection::topY        );
  // top phi (at the moment both top candidates are filled in one histogram)
  hists_["topPhi"      ] = new TH1F( "topPhi"      , "topPhi"      ,   6, CrossSection::topPhi      );
  // angle between top and the corresponding W in lab frame
  hists_["topWAnglelab"] = new TH1F( "topWAnglelab", "topWAnglelab",   6, CrossSection::topWAnglelab);
  // angle between top and the corresponding W in top rest frame
  hists_["topWAngletop"] = new TH1F( "topWAngletop", "topWAngletop",   6, CrossSection::topWAngletop);
  // ttbar pair pt
  hists_["ttbarPt"     ] = new TH1F( "ttbarPt"     , "ttbarPt"     ,   8, CrossSection::ttbarPt     );
  // ttbar pair y
  hists_["ttbarY"      ] = new TH1F( "ttbarY"      , "ttbarY"      ,  10, CrossSection::ttbarY      );
  // ttbar pair phi
  hists_["ttbarPhi"    ] = new TH1F( "ttbarPhi"    , "ttbarPhi"    ,   6, CrossSection::ttbarPhi    );
  // ttbar pair invariant mass
  hists_["ttbarMass"   ] = new TH1F( "ttbarMass"   , "ttbarMass"   ,   6, CrossSection::ttbarMass   );
  // deltaPhi between both top quarks
  hists_["ttbarDelPhi" ] = new TH1F( "ttbarDelPhi" , "ttbarDelPhi" ,   6, CrossSection::ttbarDelPhi );
  // deltaY between both top quarks
  hists_["ttbarDelY"   ] = new TH1F( "ttbarDelY"   , "ttbarDelY"   ,  10,     -5.,      5.          );
  // sum of y of both top quarks
  hists_["ttbarSumY"   ] = new TH1F( "ttbarSumY"   , "ttbarSumY"   ,  10,     -5.,      5.          );


  /**
     Top Variables for Cross Checks
  **/
  // pt of the hadronically decaying top candidate
  hists_["topPtHad_"   ] = new TH1F( "topPtHad_"   , "topPtHad_"  ,  9 , CrossSection::topPt     );
  // y  of the hadronically decaying top candidate
  hists_["topYHad_"    ] = new TH1F( "topYHad_"    , "topYHad_"   , 10 , CrossSection::topY      );
  // y  of the hadronically decaying top candidate
  hists_["topPhiHad_"  ] = new TH1F( "topPhiHad_"  , "topPhiHad_" ,  6 , CrossSection::topPhi    );
  // pt of the leptonically decaying top candidate
  hists_["topPtLep_"   ] = new TH1F( "topPtLep_"   , "topPtLep_"  ,  9 , CrossSection::topPt     );
  // y  of the leptonically decaying top candidate
  hists_["topYLep_"    ] = new TH1F( "topYLep_"    , "topYLep_"   , 10 , CrossSection::topY      );
  // y  of the leptonically decaying top candidate
  hists_["topPhiLep_"  ] = new TH1F( "topPhiLep_"  , "topPhiLep_" ,  6 , CrossSection::topPhi    );

  /** 
      Correlation Plots
  **/
  // gen-rec level correlation top pt
  corrs_["topPt_"       ] = new TH2F( "topPt_"       , "topPt_"       ,  400,    0.,  400.,     400,   0.,  400.);
  // gen-rec level correlation top y
  corrs_["topY_"        ] = new TH2F( "topY_"        , "topY_"        ,  800,   -4.,    4.,     800,  -4.,    4.);
  // gen-rec level correlation top phi
  corrs_["topPhi_"      ] = new TH2F( "topPhi_"      , "topPhi_"      ,  628, -3.14,  3.14,     628,-3.14,  3.14);
  // gen-rec level correlation angle between top and the corresponding W in lab frame
  corrs_["topWAnglelab_"] = new TH2F( "topWAnglelab_", "topWAnglelab_",  314,    0.,  3.14,     314,   0.,  3.14);
  // gen-rec level correlation angle between top and the corresponding W in top rest frame
  corrs_["topWAngletop_"] = new TH2F( "topWAngletop_", "topWAngletop_",  314,    0.,  3.14,     314,   0.,  3.14);
  // gen-rec level correlation ttbar pt
  corrs_["ttbarPt_"     ] = new TH2F( "ttbarPt_"     , "ttbarPt_"     ,  200,    0.,  200.,     200,   0.,  200.);
  // gen-rec level correlation ttbar y
  corrs_["ttbarY_"      ] = new TH2F( "ttbarY_"      , "ttbarY_"      , 1000,   -5.,    5.,    1000,  -5.,    5.);
  // gen-rec level correlation ttbar mass
  corrs_["ttbarMass_"   ] = new TH2F( "ttbarMass_"   , "ttbarMass_"   ,  700,  300., 1000.,     700, 300., 1000.);
}

/// histogramm booking for fw
void TopKinematics::book(edm::Service<TFileService>& fs)
{
  /** 
      Top Variables for Cross Section Measurement
  **/
  // top pt (at the moment both top candidates are filled in one histogram)
  hists_["topPt"       ] = fs->make<TH1F>( "topPt"       , "topPt"       ,   9, CrossSection::topPt       );
  // top y (at the moment both top candidates are filled in one histogram)
  hists_["topY"        ] = fs->make<TH1F>( "topY"        , "topY"        ,  10, CrossSection::topY        );
  // top phi (at the moment both top candidates are filled in one histogram)
  hists_["topPhi"      ] = fs->make<TH1F>( "topPhi"      , "topPhi"      ,   6, CrossSection::topPhi      );
  // top angle between top and the corresponding W in lab frame
  hists_["topWAnglelab"] = fs->make<TH1F>( "topWAnglelab", "topWAnglelab",   6, CrossSection::topWAnglelab);
  // top angle between top and the corresponding W in top rest frame
  hists_["topWAngletop"] = fs->make<TH1F>( "topWAngletop", "topWAngletop",   6, CrossSection::topWAngletop);
  // ttbar pair pt
  hists_["ttbarPt"     ] = fs->make<TH1F>( "ttbarPt"     , "ttbarPt"     ,   8, CrossSection::ttbarPt     );
  // ttbar pair y
  hists_["ttbarY"      ] = fs->make<TH1F>( "ttbarY"      , "ttbarY"      ,  10, CrossSection::ttbarY      );
  // ttbar pair phi
  hists_["ttbarPhi"    ] = fs->make<TH1F>( "ttbarPhi"    , "ttbarPhi"    ,   6, CrossSection::ttbarPhi    );
  // ttbar pair invariant mass
  hists_["ttbarMass"   ] = fs->make<TH1F>( "ttbarMass"   , "ttbarMass"   ,   6, CrossSection::ttbarMass   );
  // deltaPhi between both top quarks
  hists_["ttbarDelPhi" ] = fs->make<TH1F>( "ttbarDelPhi" , "ttbarDelPhi" ,   6, CrossSection::ttbarDelPhi );
  // deltaY between both top quarks
  hists_["ttbarDelY"   ] = fs->make<TH1F>( "ttbarDelY"   , "ttbarDelY"   ,  10,     -5.,      5.          );
  // sum of y of both top quarks
  hists_["ttbarSumY"   ] = fs->make<TH1F>( "ttbarSumY"   , "ttbarSumY"   ,  10,     -5.,      5.          );

  /**
     Top Variables for Cross Checks
  **/
  // pt of the hadronically decaying top candidate
  hists_["topPtHad_"   ] = fs->make<TH1F>( "topPtHad_"   , "topPtHad_"  ,   9 , CrossSection::topPt     );
  // y  of the hadronically decaying top candidate
  hists_["topYHad_"    ] = fs->make<TH1F>( "topYHad_"    , "topYHad_"   ,  10 , CrossSection::topY      );
  // y  of the hadronically decaying top candidate
  hists_["topPhiHad_"  ] = fs->make<TH1F>( "topPhiHad_"  , "topPhiHad_" ,   6 , CrossSection::topPhi    );

  // pt of the leptonically decaying top candidate
  hists_["topPtLep_"   ] = fs->make<TH1F>( "topPtLep_"   , "topPtLep_"  ,   9 , CrossSection::topPt     );
  // y  of the leptonically decaying top candidate
  hists_["topYLep_"    ] = fs->make<TH1F>( "topYLep_"    , "topYLep_"   ,  10 , CrossSection::topY      );
  // y  of the leptonically decaying top candidate
  hists_["topPhiLep_"  ] = fs->make<TH1F>( "topPhiLep_"  , "topPhiLep_" ,   6 , CrossSection::topPhi    );


  /** 
      Correlation Plots
  **/
  // gen-rec level correlation top pt
  corrs_["topPt_"       ] = fs->make<TH2F>( "topPt_"       , "topPt_"       ,  400,    0.,  400.,     400,   0.,  400.);
  // gen-rec level correlation top y
  corrs_["topY_"        ] = fs->make<TH2F>( "topY_"        , "topY_"        ,  800,   -4.,    4.,     800,  -4.,    4.);
  // gen-rec level correlation top phi
  corrs_["topPhi_"      ] = fs->make<TH2F>( "topPhi_"      , "topPhi_"      ,  628, -3.14,  3.14,     628,-3.14,  3.14);
  // gen-rec level correlation angle between top and the corresponding W in lab frame
  corrs_["topWAnglelab_"] = fs->make<TH2F>( "topWAnglelab_", "topWAnglelab_",  314,    0.,  3.14,     314,   0.,  3.14);
  // gen-rec level correlation angle between top and the corresponding W in top rest frame
  corrs_["topWAngletop_"] = fs->make<TH2F>( "topWAngletop_", "topWAngletop_",  314,    0.,  3.14,     314,   0.,  3.14);
  // gen-rec level correlation ttbar pt
  corrs_["ttbarPt_"     ] = fs->make<TH2F>( "ttbarPt_"     , "ttbarPt_"     ,  200,    0.,  200.,     200,   0.,  200.);
  // gen-rec level correlation ttbar y
  corrs_["ttbarY_"      ] = fs->make<TH2F>( "ttbarY_"      , "ttbarY_"      , 1000,   -5.,    5.,    1000,  -5.,    5.);
  // gen-rec level correlation ttbar mass
  corrs_["ttbarMass_"   ] = fs->make<TH2F>( "ttbarMass_"   , "ttbarMass_"   ,  700,  300., 1000.,     700, 300., 1000.);
}


/// histogram filling interface for generator level for access with fwlite or full framework
void
TopKinematics::fill(const TtGenEvent& tops, const double& weight)
{
  // make sure to have a ttbar pair belonging to the semi-leptonic decay channel with 
  // a muon in the final state
  if( tops.isSemiLeptonic(WDecay::kMuon) ){
    fill(tops.leptonicDecayTop(), tops.hadronicDecayTop(), tops.leptonicDecayW(), tops.hadronicDecayW(), weight);
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
    if( tops.genEvent().isAvailable() && tops.genEvent()->isSemiLeptonic(WDecay::kMuon) && matchForStabilityAndPurity_){
      fill(tops.leptonicDecayTop(hypoKey_), tops.leptonicDecayTop(), tops.hadronicDecayTop(hypoKey_), tops.hadronicDecayTop(), tops.leptonicDecayW(hypoKey_), tops.leptonicDecayW(), tops.hadronicDecayW(hypoKey_), tops.hadronicDecayW(), weight);

      // fill rec versus gen level correlation plots
      reco::Particle::LorentzVector genTtbar = tops.hadronicDecayTop(        )->p4()+tops.leptonicDecayTop(        )->p4();
      reco::Particle::LorentzVector recTtbar = tops.hadronicDecayTop(hypoKey_)->p4()+tops.leptonicDecayTop(hypoKey_)->p4();

      /** 
	  filling 2dim correlation plots ttbar
      **/
      corrs_.find("ttbarPt_"   )->second->Fill( genTtbar.pt()        , recTtbar.pt()       , weight );
      // fill y correlation plot for ttbar pair
      corrs_.find("ttbarY_"    )->second->Fill( genTtbar.Rapidity()  , recTtbar.Rapidity() , weight );
      // fill mass correlation plot for ttbar pair
      corrs_.find("ttbarMass_" )->second->Fill( genTtbar.mass()      , recTtbar.mass()     , weight );    
      // fill pt correlation plot for hadronic top candidate
      corrs_.find("topPt_"    )->second->Fill( tops.hadronicDecayTop()->pt()      , tops.hadronicDecayTop(hypoKey_)->pt()      , weight );
      // fill pt correlation plot for leptonic top candidate
      corrs_.find("topPt_"    )->second->Fill( tops.leptonicDecayTop()->pt()      , tops.leptonicDecayTop(hypoKey_)->pt()      , weight );
      // fill y correlation plot for hadronic top candidate
      corrs_.find("topY_"     )->second->Fill( tops.hadronicDecayTop()->rapidity(), tops.hadronicDecayTop(hypoKey_)->rapidity(), weight );
      // fill y correlation plot for leptonic top candidate
      corrs_.find("topY_"     )->second->Fill( tops.leptonicDecayTop()->rapidity(), tops.leptonicDecayTop(hypoKey_)->rapidity(), weight );
      // fill phi correlation plot for hadronic top candidate
      corrs_.find("topPhi_"     )->second->Fill( tops.hadronicDecayTop()->phi()   , tops.hadronicDecayTop(hypoKey_)->phi()     , weight );
      // fill phi correlation plot for leptonic top candidate
      corrs_.find("topPhi_"     )->second->Fill( tops.leptonicDecayTop()->phi()   , tops.leptonicDecayTop(hypoKey_)->phi()     , weight );
      // fill topWanglelab correlation plot for hadronic top candidate
      corrs_.find("topWAnglelab_")->second->Fill( ROOT::Math::VectorUtil::Angle(tops.hadronicDecayTop()->p4(), tops.hadronicDecayW()->p4()), ROOT::Math::VectorUtil::Angle(tops.hadronicDecayTop(hypoKey_)->p4(), tops.hadronicDecayW(hypoKey_)->p4()), weight );
      // fill topWanglelab correlation plot for leptonic top candidate
      corrs_.find("topWAnglelab_")->second->Fill( ROOT::Math::VectorUtil::Angle(tops.leptonicDecayTop()->p4(), tops.leptonicDecayW()->p4()), ROOT::Math::VectorUtil::Angle(tops.leptonicDecayTop(hypoKey_)->p4(), tops.leptonicDecayW(hypoKey_)->p4()), weight );

      // boost the W to the top rest frame
      ROOT::Math::Boost CoMBoostRecHadTop(tops.hadronicDecayTop(hypoKey_)->p4().BoostToCM());
      ROOT::Math::Boost CoMBoostGenHadTop(tops.hadronicDecayTop()->p4().BoostToCM());
      ROOT::Math::Boost CoMBoostRecLepTop(tops.leptonicDecayTop(hypoKey_)->p4().BoostToCM());
      ROOT::Math::Boost CoMBoostGenLepTop(tops.leptonicDecayTop()->p4().BoostToCM());
      reco::Particle::LorentzVector recHadronicDecayWBoosted = tops.hadronicDecayW(hypoKey_)->p4();
      reco::Particle::LorentzVector genHadronicDecayWBoosted = tops.hadronicDecayW()->p4();
      reco::Particle::LorentzVector recLeptonicDecayWBoosted = tops.leptonicDecayW(hypoKey_)->p4();
      reco::Particle::LorentzVector genLeptonicDecayWBoosted = tops.leptonicDecayW()->p4();
      recHadronicDecayWBoosted = CoMBoostRecHadTop(recHadronicDecayWBoosted);
      genHadronicDecayWBoosted = CoMBoostGenHadTop(genHadronicDecayWBoosted);
      recLeptonicDecayWBoosted = CoMBoostRecLepTop(recLeptonicDecayWBoosted);
      genLeptonicDecayWBoosted = CoMBoostGenLepTop(genLeptonicDecayWBoosted);

      // fill topWangletop correlation plot for hadronic top candidate
      corrs_.find("topWAngletop_")->second->Fill( ROOT::Math::VectorUtil::Angle(tops.hadronicDecayTop()->p4(), genHadronicDecayWBoosted), ROOT::Math::VectorUtil::Angle(tops.hadronicDecayTop(hypoKey_)->p4(), recHadronicDecayWBoosted), weight );
      // fill topWangletop correlation plot for leptonic top candidate
      corrs_.find("topWAngletop_")->second->Fill( ROOT::Math::VectorUtil::Angle(tops.leptonicDecayTop()->p4(), genLeptonicDecayWBoosted), ROOT::Math::VectorUtil::Angle(tops.leptonicDecayTop(hypoKey_)->p4(), recLeptonicDecayWBoosted), weight );

    } 
    else{
      fill(tops.leptonicDecayTop(hypoKey_), tops.hadronicDecayTop(hypoKey_), tops.leptonicDecayW(hypoKey_), tops.hadronicDecayW(hypoKey_), weight);
    }
  }
}

/// histogram filling for topA, topB candidate
void
TopKinematics::fill(const reco::Candidate* leptonicTop, const reco::Candidate* hadronicTop, const reco::Candidate* leptonicW, const reco::Candidate* hadronicW, const double& weight)
{
  /** 
      Fill Top Variables for Cross Section Measurement
  **/
  reco::Particle::LorentzVector ttBar = leptonicTop->p4() + hadronicTop->p4();
  // boost the W to the top rest frame
  ROOT::Math::Boost CoMBoostHadTop(hadronicTop->p4().BoostToCM());
  ROOT::Math::Boost CoMBoostLepTop(leptonicTop->p4().BoostToCM());
  reco::Particle::LorentzVector HadronicDecayWBoosted = hadronicW->p4();
  reco::Particle::LorentzVector LeptonicDecayWBoosted = leptonicW->p4();
  HadronicDecayWBoosted = CoMBoostHadTop(HadronicDecayWBoosted);
  LeptonicDecayWBoosted = CoMBoostLepTop(LeptonicDecayWBoosted);

  // fill top pt for leptonicTop candidate in combined histogram
  hists_.find("topPt"       )->second->Fill( leptonicTop->p4().pt ()      , weight );
  // fill top y for leptonicTop candidate in combined histogram
  hists_.find("topY"        )->second->Fill( leptonicTop->p4().Rapidity() , weight );
  // fill top phi for leptonicTop candidate in combined histogram
  hists_.find("topPhi"      )->second->Fill( leptonicTop->p4().phi()      , weight );
  // fill angle between top and the corresponding W in lab frame for leptonicTop candidate in combined histogram
  hists_.find("topWAnglelab")->second->Fill( ROOT::Math::VectorUtil::Angle(leptonicTop->p4(), leptonicW->p4()), weight );
  // fill angle between top and the corresponding W in top rest frame for leptonicTop candidate in combined histogram
  hists_.find("topWAngletop")->second->Fill( ROOT::Math::VectorUtil::Angle(leptonicTop->p4(), LeptonicDecayWBoosted), weight );
  // fill top pt for hadronicTop candidate in combined histogram
  hists_.find("topPt"       )->second->Fill( hadronicTop->p4().pt ()      , weight );
  // fill top y for hadronicTop candidate in combined histogram
  hists_.find("topY"        )->second->Fill( hadronicTop->p4().Rapidity() , weight );
  // fill top phi for hadronicTop candidate in combined histogram
  hists_.find("topPhi"      )->second->Fill( hadronicTop->p4().phi()      , weight );
  // fill angle between top and the corresponding W in lab frame for hadronicTop candidate in combined histogram
  hists_.find("topWAnglelab")->second->Fill( ROOT::Math::VectorUtil::Angle(hadronicTop->p4(), hadronicW->p4()), weight );
  // fill angle between top and the corresponding W in top rest frame for hadronicTop candidate in combined histogram
  hists_.find("topWAngletop")->second->Fill( ROOT::Math::VectorUtil::Angle(hadronicTop->p4(), HadronicDecayWBoosted), weight );
  // fill top pt for leptonicTop candidate in separate histogram
  hists_.find("topPtLep_"       )->second->Fill( leptonicTop->p4().pt ()      , weight );
  // fill top y for leptonicTop candidate in separate histogram
  hists_.find("topYLep_"        )->second->Fill( leptonicTop->p4().Rapidity() , weight );
  // fill top phi for leptonicTop candidate in separate histogram
  hists_.find("topPhiLep_"      )->second->Fill( leptonicTop->p4().phi()      , weight );
  // fill top pt for hadronicTop candidate in separate histogram
  hists_.find("topPtHad_"       )->second->Fill( hadronicTop->p4().pt ()      , weight );
  // fill top y for hadronicTop candidate in separate histogram
  hists_.find("topYHad_"        )->second->Fill( hadronicTop->p4().Rapidity() , weight );
  // fill top phi for hadronicTop candidate in separate histogram
  hists_.find("topPhiHad_"      )->second->Fill( hadronicTop->p4().phi()      , weight );
  // fill ttbar pt
  hists_.find("ttbarPt"     )->second->Fill( ttBar.pt  ()          , weight );
  // fill ttbar y
  hists_.find("ttbarY"      )->second->Fill( ttBar.Rapidity()      , weight );
  // fill ttbar phi
  hists_.find("ttbarPhi"    )->second->Fill( ttBar.phi ()          , weight );
  // fill ttbar invariant mass
  hists_.find("ttbarMass"   )->second->Fill( ttBar.mass()          , weight );
  // fill deltaPhi between both top quarks 
  hists_.find("ttbarDelPhi" )->second->Fill( deltaPhi(leptonicTop->phi(), hadronicTop->phi()) , weight );
  // fill deltaY between both top quarks 
  hists_.find("ttbarDelY"   )->second->Fill( leptonicTop->rapidity()-hadronicTop->rapidity()  , weight );
  // fill sum of y of both top quarks 
  hists_.find("ttbarSumY"   )->second->Fill( leptonicTop->rapidity()+hadronicTop->rapidity()  , weight );
}

/// histogram filling for candidate topA and topB (for stability and purity calculation)
void 
TopKinematics::fill(const reco::Candidate* leptonicTopRec, const reco::Candidate* leptonicTopGen, const reco::Candidate* hadronicTopRec, const reco::Candidate* hadronicTopGen, const reco::Candidate* leptonicWRec, const reco::Candidate* leptonicWGen, const reco::Candidate* hadronicWRec, const reco::Candidate* hadronicWGen, const double& weight)
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
  reco::Particle::LorentzVector recHadronicDecayWBoosted = hadronicWRec->p4();
  reco::Particle::LorentzVector genHadronicDecayWBoosted = hadronicWGen->p4();
  reco::Particle::LorentzVector recLeptonicDecayWBoosted = leptonicWRec->p4();
  reco::Particle::LorentzVector genLeptonicDecayWBoosted = leptonicWGen->p4();
  recHadronicDecayWBoosted = CoMBoostRecHadTop(recHadronicDecayWBoosted);
  genHadronicDecayWBoosted = CoMBoostGenHadTop(genHadronicDecayWBoosted);
  recLeptonicDecayWBoosted = CoMBoostRecLepTop(recLeptonicDecayWBoosted);
  genLeptonicDecayWBoosted = CoMBoostGenLepTop(genLeptonicDecayWBoosted);

  // fill top pt for topA candidate in combined histogram
  match( hists_.find("topPt"       )->second , leptonicTopRec->p4().pt ()      , leptonicTopGen->p4().pt ()      , weight );
  // fill top y for topA candidate in combined histogram
  match( hists_.find("topY"        )->second , leptonicTopRec->p4().Rapidity() , leptonicTopGen->p4().Rapidity() , weight );
  // fill top phi for topA candidate in combined histogram
  match( hists_.find("topPhi"      )->second , leptonicTopRec->p4().phi()      , leptonicTopGen->p4().phi()      , weight );
  // fill angle between top and the corresponding W in lab frame for topA candidate in combined histogram
  match( hists_.find("topWAnglelab")->second , ROOT::Math::VectorUtil::Angle(leptonicTopRec->p4(), leptonicWRec->p4()), ROOT::Math::VectorUtil::Angle(leptonicTopGen->p4(), leptonicWGen->p4()), weight );
  // fill angle between top and the corresponding W in top rest frame for topA candidate in combined histogram
  match( hists_.find("topWAngletop")->second , ROOT::Math::VectorUtil::Angle(leptonicTopRec->p4(), recLeptonicDecayWBoosted), ROOT::Math::VectorUtil::Angle(leptonicTopGen->p4(), genLeptonicDecayWBoosted), weight );
  // fill top pt for topB candidate in combined histogram
  match( hists_.find("topPt"       )->second , hadronicTopRec->p4().pt ()      , hadronicTopGen->p4().pt ()      , weight );
  // fill top y for topB candidate in combined histogram
  match( hists_.find("topY"        )->second , hadronicTopRec->p4().Rapidity() , hadronicTopGen->p4().Rapidity() , weight );
  // fill top phi for topB candidate in combined histogram
  match( hists_.find("topPhi"      )->second , hadronicTopRec->p4().phi()      , hadronicTopGen->p4().phi()      , weight );
  // fill angle between top and the corresponding W in lab frame for topB candidate in combined histogram
  match( hists_.find("topWAnglelab")->second , ROOT::Math::VectorUtil::Angle(hadronicTopRec->p4(), hadronicWRec->p4()), ROOT::Math::VectorUtil::Angle(hadronicTopGen->p4(), hadronicWGen->p4()), weight );
  // fill angle between top and the corresponding Win top rest frame for topB candidate in combined histogram
  match( hists_.find("topWAngletop")->second , ROOT::Math::VectorUtil::Angle(hadronicTopRec->p4(), recHadronicDecayWBoosted), ROOT::Math::VectorUtil::Angle(hadronicTopGen->p4(), genHadronicDecayWBoosted), weight );
  // fill top pt for topA candidate in separate histogram
  match( hists_.find("topPtLep_"       )->second , leptonicTopRec->p4().pt ()      , leptonicTopGen->p4().pt ()      , weight );
  // fill top y for topA candidate in separate histogram
  match( hists_.find("topYLep_"        )->second , leptonicTopRec->p4().Rapidity() , leptonicTopGen->p4().Rapidity() , weight );
  // fill top phi for topA candidate in separate histogram
  match( hists_.find("topPhiLep_"      )->second , leptonicTopRec->p4().phi()      , leptonicTopGen->p4().phi()      , weight );
  // fill top pt for topB candidate in separate histogram
  match( hists_.find("topPtHad_"       )->second , hadronicTopRec->p4().pt ()      , hadronicTopGen->p4().pt ()      , weight );
  // fill top y for topB candidate in separate histogram
  match( hists_.find("topYHad_"        )->second , hadronicTopRec->p4().Rapidity() , hadronicTopGen->p4().Rapidity() , weight );
  // fill top phi for topB candidate in separate histogram
  match( hists_.find("topPhiHad_"      )->second , hadronicTopRec->p4().phi()      , hadronicTopGen->p4().phi()      , weight );
  // fill ttbar pt
  match( hists_.find("ttbarPt"     )->second , recTtBar.pt  ()          , genTtBar.pt  ()          , weight );
  // fill ttbar y
  match( hists_.find("ttbarY"      )->second , recTtBar.Rapidity ()     , genTtBar.Rapidity ()     , weight );
  // fill ttbar phi
  match( hists_.find("ttbarPhi"    )->second , recTtBar.phi ()          , genTtBar.phi ()          , weight );
  // fill ttbar invariant mass
  match( hists_.find("ttbarMass"   )->second , recTtBar.mass()          , genTtBar.mass()          , weight );
  // fill deltaPhi between both top quarks 
  match( hists_.find("ttbarDelPhi" )->second , deltaPhi(leptonicTopRec->phi(), hadronicTopRec->phi()), deltaPhi(leptonicTopGen->phi(), hadronicTopGen->phi()), weight );
  // fill deltaY between both top quarks 
  match( hists_.find("ttbarDelY"   )->second , leptonicTopRec->rapidity()-hadronicTopRec->rapidity() , leptonicTopGen->rapidity()-hadronicTopGen->rapidity() , weight );
  // fill sum of y of both top quarks 
  match( hists_.find("ttbarSumY"   )->second , leptonicTopRec->rapidity()+hadronicTopRec->rapidity() , leptonicTopGen->rapidity()+hadronicTopGen->rapidity() , weight );
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
