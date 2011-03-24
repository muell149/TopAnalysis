#include "DataFormats/Math/interface/deltaPhi.h"
#include <Math/VectorUtil.h>
#include <Math/Boost.h>
#include "TopAnalysis/TopAnalyzer/interface/TopKinematics.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

/// default constructor for generator level analysis in fw lite
TopKinematics::TopKinematics() : hypoKey_(""), matchForStabilityAndPurity_(false) 
{
  tree = 0;
  useTree_=false;
  ttbarInsteadOfLepHadTop_ = false;
}

/// default constructor for reco level analysis in fw lite
TopKinematics::TopKinematics(const std::string& hypoKey, const bool& matchForStabilityAndPurity) : hypoKey_(hypoKey), matchForStabilityAndPurity_(matchForStabilityAndPurity)
{
  tree = 0;
  useTree_=false;
  ttbarInsteadOfLepHadTop_ = false;
}

/// default constructor for full fw
TopKinematics::TopKinematics(const edm::ParameterSet& cfg) :
  hypoKey_( cfg.getParameter<std::string>("hypoKey") ),
  useTree_( cfg.getParameter<bool>       ("useTree") ),
  matchForStabilityAndPurity_( cfg.getParameter<bool>("matchForStabilityAndPurity") ),
  ttbarInsteadOfLepHadTop_   ( cfg.getParameter<bool>("ttbarInsteadOfLepHadTop"   ) )
{
  tree = 0;
}

/// histogramm booking for fwlite 
void TopKinematics::book()
{

  /** 
      KinFit Monitoring Variables
  **/
  // fit probability of the best fit hypothesis
  hists_["prob"       ] = new TH1F( "prob"       , "prob"       ,   1000,   0.,    1.           );
  // chi2 of the best fit hypothesis
  hists_["chi2"       ] = new TH1F( "chi2"       , "chi2"       ,   100,    0.,   10.           );
  // delta chi2 between best and second best fit hyothesis
  hists_["delChi2"    ] = new TH1F( "delChi2"    , "delChi2"    ,   100,    0.,   10.           );

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
  hists_["topPtHad"  ] = new TH1F( "topPtHad"  , "topPtHad"  ,  9 , CrossSection::topPt     );
  // y  of the hadronically decaying top candidate
  hists_["topYHad"   ] = new TH1F( "topYHad"   , "topYHad"   , 10 , CrossSection::topY      );
  // y  of the hadronically decaying top candidate
  hists_["topPhiHad" ] = new TH1F( "topPhiHad" , "topPhiHad" ,  6 , CrossSection::topPhi    );
  // pt of the leptonically decaying top candidate
  hists_["topPtLep"  ] = new TH1F( "topPtLep"  , "topPtLep"  ,  9 , CrossSection::topPt     );
  // y  of the leptonically decaying top candidate
  hists_["topYLep"   ] = new TH1F( "topYLep"   , "topYLep"   , 10 , CrossSection::topY      );
  // y  of the leptonically decaying top candidate
  hists_["topPhiLep" ] = new TH1F( "topPhiLep" , "topPhiLep" ,  6 , CrossSection::topPhi    );
  // hadronic Top mass
  hists_["hadTopMass"] = new TH1F( "hadTopMass", "hadTopMass", 400,  100.,  300.            );
  // leptonic Top mass
  hists_["lepTopMass"] = new TH1F( "lepTopMass", "lepTopMass", 400,  100.,  300.            );
  // Top mass
  hists_["topMass"   ] = new TH1F( "topMass"   , "topMass"   , 400,  100.,  300.            );
  // angle between b jets
  hists_["bbbarAngle"] = new TH1F( "bbbarAngle", "bbbarAngle", 315,  0.  ,  3.15            );
  // angle between the leptonically decaying top candidate and the corresponding W
  hists_["topWAngleLep"] = new TH1F( "topWAngleLep", "topWAngleLep",   6, CrossSection::topWAngle  );
  // angle between the hadronically decaying top candidate and the corresponding W
  hists_["topWAngleHad"] = new TH1F( "topWAngleHad", "topWAngleHad",   6, CrossSection::topWAngle  );

  /** 
      Correlation Plots
  **/
  // gen-rec level correlation top pt
  corrs_["topPt_"      ] = new TH2F( "topPt_"      , "topPt_"       , 400 ,    0.,  400.,     400,   0.,  400.);
  // gen-rec level correlation top y
  corrs_["topY_"       ] = new TH2F( "topY_"       , "topY_"        , 800 ,   -4.,    4.,     800,  -4.,    4.);
  // gen-rec level correlation top phi
  corrs_["topPhi_"     ] = new TH2F( "topPhi_"     , "topPhi_"      , 628 , -3.14,  3.14,     628,-3.14,  3.14);
  // gen-rec level correlation angle between top and the corresponding W
  corrs_["topWAngle_"  ] = new TH2F( "topWAngle_"  , "topWAngle_"   , 314 ,    0.,  3.14,     314,   0.,  3.14);
  // gen-rec level correlation ttbar pt
  corrs_["ttbarPt_"    ] = new TH2F( "ttbarPt_"    , "ttbarPt_"     , 200 ,    0.,  200.,     200,   0.,  200.);
  // gen-rec level correlation ttbar y
  corrs_["ttbarY_"     ] = new TH2F( "ttbarY_"     , "ttbarY_"      , 1000,   -5.,    5.,    1000,  -5.,    5.);
  // gen-rec level correlation ttbar mass
  corrs_["ttbarMass_"  ] = new TH2F( "ttbarMass_"  , "ttbarMass_"   , 700 ,  300., 1000.,     700, 300., 1000.);
  // gen-rec level correlation HT of the 4 jets assigned to the ttbar decay
  corrs_["ttbarHT_"    ] = new TH2F( "ttbarHT_"    , "ttbarHT_"     , 1000,    0., 1000.,    1000,   0., 1000.);
  // gen-rec level correlation ttbar deltaPhi
  corrs_["ttbarDelPhi_"] = new TH2F( "ttbarDelPhi_", "ttbarDelPhi_" , 628 , -3.14,  3.14,     628,-3.14,  3.14);
  // gen-rec level correlation ttbar deltaY
  corrs_["ttbarDelY_"  ] = new TH2F( "ttbarDelY_"  , "ttbarDelY_"   , 1000,   -5.,    5.,    1000,  -5.,    5.);
  // gen-rec level correlation ttbar sumY
  corrs_["ttbarSumY_"  ] = new TH2F( "ttbarSumY_"  , "ttbarSumY_"   , 1000,   -5.,    5.,    1000,  -5.,    5.);
  // gen-rec level correlation angle between b jets
  corrs_["bbbarAngle"  ] = new TH2F( "bbbarAngle"  , "bbbarAngle"   ,  315,    0.,  3.15,     315,   0.,  3.15);
  // gen-rec level correlation for lepton charge
  corrs_["lepCharge_"  ] = new TH2F( "lepCharge_"  , "lepCharge_"   ,    3,  -1.5,   1.5,       3, -1.5,   1.5);
}

/// histogramm booking for fw
void TopKinematics::book(edm::Service<TFileService>& fs)
{
  /** 
      KinFit Monitoring Variables
  **/
  // fit probability of the best fit hypothesis
  hists_["prob"       ] = fs->make<TH1F>( "prob"        , "prob"        , 1000,   0.,    1. );
  // chi2 of the best fit hypothesis
  hists_["chi2"       ] = fs->make<TH1F>( "chi2"        , "chi2"        , 100,    0.,   10. );
  // delta chi2 between best and second best fit hyothesis
  hists_["delChi2"    ] = fs->make<TH1F>( "delChi2"     , "delChi2"     , 100,    0.,   10. );

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
  hists_["topPtHad"  ] = fs->make<TH1F>( "topPtHad"   , "topPtHad"  ,   9 , CrossSection::topPt     );
  // y  of the hadronically decaying top candidate
  hists_["topYHad"   ] = fs->make<TH1F>( "topYHad"    , "topYHad"   ,  10 , CrossSection::topY      );
  // y  of the hadronically decaying top candidate
  hists_["topPhiHad" ] = fs->make<TH1F>( "topPhiHad"  , "topPhiHad" ,   6 , CrossSection::topPhi    );
  // pt of the leptonically decaying top candidate
  hists_["topPtLep"  ] = fs->make<TH1F>( "topPtLep"   , "topPtLep"  ,   9 , CrossSection::topPt     );
  // y  of the leptonically decaying top candidate
  hists_["topYLep"   ] = fs->make<TH1F>( "topYLep"    , "topYLep"   ,  10 , CrossSection::topY      );
  // y  of the leptonically decaying top candidate
  hists_["topPhiLep" ] = fs->make<TH1F>( "topPhiLep"  , "topPhiLep" ,   6 , CrossSection::topPhi    );
  // hadronic Top mass of the hadronically decaying top candidate
  hists_["hadTopMass"] = fs->make<TH1F>( "hadTopMass" , "hadTopMass",  400,  100.,  300.            );
  // leptonic Top mass of the leptonically decaying top candidate
  hists_["lepTopMass"] = fs->make<TH1F>( "lepTopMass" , "lepTopMass",  400,  100.,  300.            );
  // Top mass
  hists_["topMass"   ] = fs->make<TH1F>( "topMass"    , "topMass"   ,  400,  100.,  300.            );
  // angle between b jets
  hists_["bbbarAngle"] = fs->make<TH1F>( "bbbarAngle" , "bbbarAngle",  315,  0.  ,  3.15            );
  // angle between the leptonically decaying top candidate and the corresponding W
  hists_["topWAngleLep"] = fs->make<TH1F>( "topWAngleLep", "topWAngleLep",   6, CrossSection::topWAngle  );
  // angle between the hfs->make<TH1F> decaying top candidate and the corresponding W
  hists_["topWAngleHad"] = fs->make<TH1F>( "topWAngleHad", "topWAngleHad",   6, CrossSection::topWAngle  );

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
  // gen-rec level correlation angle between b jets
  corrs_["bbbarAngle_"] = fs->make<TH2F>( "bbbarAngle_" , "bbbarAngle_",  315,    0.,  3.15,     315,   0.,  3.15);
  // gen-rec level correlation for lepton charge
  corrs_["lepCharge_" ] = fs->make<TH2F>( "lepCharge_"  , "lepCharge_" ,    3,  -1.5,   1.5,       3, -1.5,   1.5);

  // book ttree entries
  if(useTree_){
    // Kinfit performance
    bookVariable(fs, "prob"   );
    bookVariable(fs, "chi2"   );
    bookVariable(fs, "delChi2");
    // ttbar quantities
    bookVariable(fs, "ttbarPt"    );
    bookVariable(fs, "ttbarY"     );
    bookVariable(fs, "ttbarPhi"   );
    bookVariable(fs, "ttbarMass"  );
    bookVariable(fs, "ttbarDelPhi");
    bookVariable(fs, "ttbarDelY"  );
    bookVariable(fs, "ttbarSumY"  );
    bookVariable(fs, "ttbarHT"    );
    // hadronic top quantities
    bookVariable(fs, "topPtHad"  );
    bookVariable(fs, "topYHad"   );
    bookVariable(fs, "topPhiHad" );
    bookVariable(fs, "hadTopMass");
    bookVariable(fs, "topWAngleHad");
    // leptonic top quantities
    bookVariable(fs, "topPtLep"  );
    bookVariable(fs, "topYLep"   );  
    bookVariable(fs, "topPhiLep" );
    bookVariable(fs, "lepTopMass");
    bookVariable(fs, "topWAngleLep");
    // others
    bookVariable(fs, "bbbarAngle");  
    bookVariable(fs, "lepCharge"); 

  }
}


/// histogram filling interface for generator level for access with fwlite or full framework
void
TopKinematics::fill(const TtGenEvent& tops, const double& weight)
{
  // make sure to have a ttbar pair belonging to the semi-leptonic decay channel with 
  // a muon in the final state and neglect events where top decay is not via Vtb
  if( tops.isSemiLeptonic(WDecay::kMuon) && tops.leptonicDecayB() && tops.hadronicDecayB() ){
    // define leptonic/hadronic or positive/negative charged objects (B,W,t)
    bool switchLepAndHadTop = false;
    // if ttbarInsteadOfLepHadTop_ == true:
    // lepTop = Top     (positive charge)
    // lepTop = AntiTop (negative charge)
    if((ttbarInsteadOfLepHadTop_==true)&&(((reco::LeafCandidate*)(tops.singleLepton()))->charge()<0)){
      switchLepAndHadTop=true;
    }
    const reco::GenParticle *lepTop= switchLepAndHadTop ? tops.hadronicDecayTop() : tops.leptonicDecayTop();
    const reco::GenParticle *hadTop= switchLepAndHadTop ? tops.leptonicDecayTop() : tops.hadronicDecayTop();
    const reco::GenParticle *lepW  = switchLepAndHadTop ? tops.hadronicDecayW  () : tops.leptonicDecayW();
    const reco::GenParticle *hadW  = switchLepAndHadTop ? tops.leptonicDecayW  () : tops.hadronicDecayW();
    const reco::GenParticle *lepB  = switchLepAndHadTop ? tops.hadronicDecayB  () : tops.leptonicDecayB(); 
    const reco::GenParticle *hadB  = switchLepAndHadTop ? tops.leptonicDecayB  () : tops.hadronicDecayB();
    // define generated scalar sum of all jet pts
    double HT = lepB->pt() + hadB->pt()+tops.hadronicDecayQuark()->pt()+tops.hadronicDecayQuarkBar()->pt();
    // fill all 1D histos
    fill(lepTop, hadTop, lepW, hadW, HT, weight);
    // define ttbar four momentum vector
    reco::Particle::LorentzVector genttbar = lepTop->p4()+hadTop->p4();
    // define boost to ttbar system
    ROOT::Math::Boost CoMBoostGenTtbar(genttbar.BoostToCM());
    // get b and bbar four momentum
    reco::Particle::LorentzVector genLeptonicDecayBBoosted = lepB->p4();
    reco::Particle::LorentzVector genHadronicDecayBBoosted = hadB->p4();
    // apply boost to ttbar system
    genLeptonicDecayBBoosted = CoMBoostGenTtbar(genLeptonicDecayBBoosted);
    genHadronicDecayBBoosted = CoMBoostGenTtbar(genHadronicDecayBBoosted);
    // fill 1D b-bbar angle plot
    fillValue( "bbbarAngle", ROOT::Math::VectorUtil::Angle(genLeptonicDecayBBoosted, genHadronicDecayBBoosted), weight );
    // save lepton charge
    fillValue( "lepCharge", ((reco::LeafCandidate*)(tops.singleLepton()))->charge(), weight );
    // fill the tree, if any variable should be put in
    if(treeVars_.size()) tree->Fill();
  }
}

/// histogram filling interface for reconstruction level for access with fwlite or full framework
void
TopKinematics::fill(const TtSemiLeptonicEvent& tops, const double& weight)
{
  // make sure to have a valid hypothesis on reconstruction level.
  if( tops.isHypoValid(hypoKey_) ){
    // define leptonic/hadronic or positive/negative charged objects (B,W,t)
    bool switchLepAndHadTop = false;
    // if ttbarInsteadOfLepHadTop_ == true:
    // lepTop = Top     (positive charge)
    // lepTop = AntiTop (negative charge)
    if((ttbarInsteadOfLepHadTop_==true)&&(((reco::LeafCandidate*)(tops.singleLepton(hypoKey_)))->charge()<0)){
      switchLepAndHadTop=true;
    }
    const reco::Candidate *lepTopRec= switchLepAndHadTop ? tops.hadronicDecayTop(hypoKey_) : tops.leptonicDecayTop(hypoKey_);
    const reco::Candidate *hadTopRec= switchLepAndHadTop ? tops.leptonicDecayTop(hypoKey_) : tops.hadronicDecayTop(hypoKey_);
    const reco::Candidate *lepWRec  = switchLepAndHadTop ? tops.hadronicDecayW  (hypoKey_) : tops.leptonicDecayW  (hypoKey_);
    const reco::Candidate *hadWRec  = switchLepAndHadTop ? tops.leptonicDecayW  (hypoKey_) : tops.hadronicDecayW  (hypoKey_);
    const reco::Candidate *lepBRec  = switchLepAndHadTop ? tops.hadronicDecayB  (hypoKey_) : tops.leptonicDecayB  (hypoKey_); 
    const reco::Candidate *hadBRec  = switchLepAndHadTop ? tops.leptonicDecayB  (hypoKey_) : tops.hadronicDecayB  (hypoKey_);

    // define reconstructed scalar sum of all jet pts
    double HTrec = lepBRec->pt() + hadBRec->pt() + tops.hadronicDecayQuark(hypoKey_)->pt() + tops.hadronicDecayQuarkBar(hypoKey_)->pt();
    // if the kinFit hypothesis is valid, fill KinFit quantities 
    if(hypoKey_=="kKinFit"){
      // fit probability of the best fit hypothesis
      fillValue( "prob", tops.fitProb(), weight );
      // chi2 of the best fit hypothesis
      fillValue( "chi2", tops.fitChi2(), weight );
      // make sure that a second best fit hypothesis exists to be able to fill these plots
      if( tops.fitChi2(1) >= 0 ){
	// delta chi2 between best and second best fit hyothesis
	fillValue( "delChi2", tops.fitChi2(1)-tops.fitChi2(0), weight );
      }
    }
    // check if matchForStabilityAndPurity_ is true and a generated ttbar semileptonic #mu event exists
    // neglect events where top decay is not via Vtb
    if( tops.genEvent().isAvailable() && tops.genEvent()->isSemiLeptonic(WDecay::kMuon) && lepBRec && hadBRec && matchForStabilityAndPurity_ ){
      const reco::GenParticle *lepTopGen= switchLepAndHadTop ? tops.hadronicDecayTop() : tops.leptonicDecayTop();
      const reco::GenParticle *hadTopGen= switchLepAndHadTop ? tops.leptonicDecayTop() : tops.hadronicDecayTop();
      const reco::GenParticle *lepWGen  = switchLepAndHadTop ? tops.hadronicDecayW  () : tops.leptonicDecayW  ();
      const reco::GenParticle *hadWGen  = switchLepAndHadTop ? tops.leptonicDecayW  () : tops.hadronicDecayW  ();
      const reco::GenParticle *lepBGen  = switchLepAndHadTop ? tops.hadronicDecayB  () : tops.leptonicDecayB  (); 
      const reco::GenParticle *hadBGen  = switchLepAndHadTop ? tops.leptonicDecayB  () : tops.hadronicDecayB  ();
      // define generated scalar sum of all jet pts
      double HTgen = lepBGen->pt() + hadBGen->pt() + tops.hadronicDecayQuark()->pt() + tops.hadronicDecayQuarkBar()->pt();

      /**
         fill 1D histos and N(gen&&rec)-histo for the determination of stability and purity
      **/
      fill(lepTopRec, lepTopGen, hadTopRec, hadTopGen, lepWRec, lepWGen, hadWRec, hadWGen, HTrec, HTgen, weight);

      /**
	 fill 2D histos (rec versus gen level correlation plots)
      **/
      // create combined ttbar lorentz vector
      reco::Particle::LorentzVector genTtbar = hadTopGen->p4()+lepTopGen->p4();
      reco::Particle::LorentzVector recTtbar = hadTopRec->p4()+lepTopRec->p4();
 
      // fill pt correlation plot for ttbar pair
      corrs_.find("ttbarPt_"  )->second->Fill( genTtbar.pt()      , recTtbar.pt()       , weight );
      // fill y correlation plot for ttbar pair
      corrs_.find("ttbarY_"   )->second->Fill( genTtbar.Rapidity(), recTtbar.Rapidity() , weight );
      // fill mass correlation plot for ttbar pair
      corrs_.find("ttbarMass_")->second->Fill( genTtbar.mass()    , recTtbar.mass()     , weight );    
      // fill HT correlation plot for the 4 jets assigned to the ttbar decay
      corrs_.find("ttbarHT_"  )->second->Fill( HTgen              , HTrec               , weight ); 

      // fill pt correlation plot for hadronic top candidate
      corrs_.find("topPt_")->second->Fill( hadTopGen->pt(), hadTopRec->pt(), weight );
      // fill pt correlation plot for leptonic top candidate
      corrs_.find("topPt_")->second->Fill( lepTopGen->pt(), lepTopRec->pt(), weight );

      // fill y correlation plot for hadronic top candidate
      corrs_.find("topY_")->second->Fill( hadTopGen->rapidity(), hadTopRec->rapidity(), weight );
      // fill y correlation plot for leptonic top candidate
      corrs_.find("topY_")->second->Fill( lepTopGen->rapidity(), lepTopRec->rapidity(), weight );

      // fill phi correlation plot for hadronic top candidate
      corrs_.find("topPhi_"   )->second->Fill( hadTopGen->phi(), hadTopRec->phi(), weight );
      // fill phi correlation plot for leptonic top candidate							     
      corrs_.find("topPhi_"   )->second->Fill( lepTopGen->phi(), lepTopRec->phi(), weight );

       // fill deltaPhi correlation plot for ttbar pair
      corrs_.find("ttbarDelPhi_")->second->Fill(deltaPhi(lepTopGen->phi(), hadTopGen->phi()), 
						deltaPhi(lepTopRec->phi(), hadTopRec->phi()), weight );
      // fill deltaY correlation plot for ttbar
      corrs_.find("ttbarDelY_"  )->second->Fill(lepTopGen->rapidity()-hadTopGen->rapidity(), 
						lepTopRec->rapidity()-hadTopRec->rapidity(), weight);
      // fill sumY correlation plot for ttbar pair
      corrs_.find("ttbarSumY_"  )->second->Fill(lepTopGen->rapidity()+hadTopGen->rapidity(),
						lepTopRec->rapidity()+hadTopRec->rapidity(),
						weight );
      // fill charge correlation plot for lepton
      corrs_.find("lepCharge_" )->second->Fill( ((reco::LeafCandidate*)(tops.singleLepton(        )))->charge(), 
						((reco::LeafCandidate*)(tops.singleLepton(hypoKey_)))->charge(), weight);
    
      /**
	 fill  fill 2D histos (angle correlation plots)
      **/
      // create boost into reconstructed/generated top quarks/ttbar system
      ROOT::Math::Boost CoMBoostRecHadTop(hadTopRec->p4().BoostToCM());
      ROOT::Math::Boost CoMBoostGenHadTop(hadTopGen->p4().BoostToCM());
      ROOT::Math::Boost CoMBoostRecLepTop(lepTopRec->p4().BoostToCM());
      ROOT::Math::Boost CoMBoostGenLepTop(lepTopGen->p4().BoostToCM());
      ROOT::Math::Boost CoMBoostRecTtbar (recTtbar       .BoostToCM());
      ROOT::Math::Boost CoMBoostGenTtbar (genTtbar       .BoostToCM());
      // get lorentz vectors of W and Top without boost
      reco::Particle::LorentzVector recHadronicDecayWBoosted   = hadWRec  ->p4();
      reco::Particle::LorentzVector genHadronicDecayWBoosted   = hadWGen  ->p4();
      reco::Particle::LorentzVector recLeptonicDecayWBoosted   = lepWRec  ->p4();
      reco::Particle::LorentzVector genLeptonicDecayWBoosted   = lepWGen  ->p4();
      reco::Particle::LorentzVector recHadronicDecayTopBoosted = hadTopRec->p4();
      reco::Particle::LorentzVector genHadronicDecayTopBoosted = hadTopGen->p4();
      reco::Particle::LorentzVector recLeptonicDecayTopBoosted = lepTopRec->p4();
      reco::Particle::LorentzVector genLeptonicDecayTopBoosted = lepTopGen->p4();
      reco::Particle::LorentzVector genLeptonicDecayBBoosted   = lepBGen  ->p4();
      reco::Particle::LorentzVector recLeptonicDecayBBoosted   = lepBRec  ->p4();
      reco::Particle::LorentzVector genHadronicDecayBBoosted   = hadBGen  ->p4();
      reco::Particle::LorentzVector recHadronicDecayBBoosted   = hadBRec  ->p4();

      // recalculate Lorent vectors using boosts defined above
      // boost W into top rest frame and and top and b-quarks into the ttbar rest frame
      recHadronicDecayWBoosted   = CoMBoostRecHadTop(recHadronicDecayWBoosted  );
      genHadronicDecayWBoosted   = CoMBoostGenHadTop(genHadronicDecayWBoosted  );
      recLeptonicDecayWBoosted   = CoMBoostRecLepTop(recLeptonicDecayWBoosted  );
      genLeptonicDecayWBoosted   = CoMBoostGenLepTop(genLeptonicDecayWBoosted  );
      recHadronicDecayTopBoosted = CoMBoostRecTtbar (recHadronicDecayTopBoosted);
      genHadronicDecayTopBoosted = CoMBoostGenTtbar (genHadronicDecayTopBoosted);
      recLeptonicDecayTopBoosted = CoMBoostRecTtbar (recLeptonicDecayTopBoosted);
      genLeptonicDecayTopBoosted = CoMBoostGenTtbar (genLeptonicDecayTopBoosted);
      genLeptonicDecayBBoosted   = CoMBoostGenTtbar (genLeptonicDecayBBoosted  );
      recLeptonicDecayBBoosted   = CoMBoostRecTtbar (recLeptonicDecayBBoosted  );
      genHadronicDecayBBoosted   = CoMBoostGenTtbar (genHadronicDecayBBoosted  );
      recHadronicDecayBBoosted   = CoMBoostRecTtbar (recHadronicDecayBBoosted  );

      // fill topWangletop correlation plot for hadronic top candidate
      corrs_.find("topWAngle_")->second->Fill( ROOT::Math::VectorUtil::Angle(genHadronicDecayTopBoosted, genHadronicDecayWBoosted), 
					       ROOT::Math::VectorUtil::Angle(recHadronicDecayTopBoosted, recHadronicDecayWBoosted), 
					       weight );
      // fill topWangletop correlation plot for leptonic top candidate
      corrs_.find("topWAngle_")->second->Fill( ROOT::Math::VectorUtil::Angle(genLeptonicDecayTopBoosted, genLeptonicDecayWBoosted), 
					       ROOT::Math::VectorUtil::Angle(recLeptonicDecayTopBoosted, recLeptonicDecayWBoosted), 
					       weight );
      // fill correlation plot for the angle between b jets
      corrs_.find("bbbarAngle_")->second->Fill( ROOT::Math::VectorUtil::Angle(genLeptonicDecayBBoosted, genHadronicDecayBBoosted), 
						ROOT::Math::VectorUtil::Angle(recLeptonicDecayBBoosted, recHadronicDecayBBoosted),
						weight);
      // fill correlation plot for angle between b-jets
      match( "bbbarAngle", ROOT::Math::VectorUtil::Angle(recLeptonicDecayBBoosted, recHadronicDecayBBoosted),
	                   ROOT::Math::VectorUtil::Angle(genLeptonicDecayBBoosted, genHadronicDecayBBoosted), 
	                   weight);
    }
    // if matchForStabilityAndPurity_ is false or no generated ttbar semileptonic #mu event exists
    else{
      // fill only 1D histos
      fill(lepTopRec, hadTopRec, lepWRec, hadWRec, HTrec, weight);
      // define ttbar four momentum vector
      reco::Particle::LorentzVector recttbar = hadTopRec->p4()+lepTopRec->p4();
      // define boost to ttbar system
      ROOT::Math::Boost CoMBoostRecTtbar(recttbar.BoostToCM());
      // get b and bbar four momentum
      reco::Particle::LorentzVector recLeptonicDecayBBoosted = lepBRec->p4();
      reco::Particle::LorentzVector recHadronicDecayBBoosted = hadBRec->p4();
      // apply boost to ttbar system
      recLeptonicDecayBBoosted = CoMBoostRecTtbar(recLeptonicDecayBBoosted);
      recHadronicDecayBBoosted = CoMBoostRecTtbar(recHadronicDecayBBoosted);
      // fill 1D b-bbar angle plot
      fillValue( "bbbarAngle", ROOT::Math::VectorUtil::Angle(recLeptonicDecayBBoosted, recHadronicDecayBBoosted), weight );
    }
    // save lepton charge
    fillValue( "lepCharge", ((reco::LeafCandidate*)(tops.singleLepton(hypoKey_)))->charge(), weight );
    // fill the tree, if any variable should be put in
    if(treeVars_.size()) tree->Fill();
  }
}

/// histogram filling for 1D histos (no genmatch)
void
TopKinematics::fill(const reco::Candidate* leptonicTop, const reco::Candidate* hadronicTop, 
		    const reco::Candidate* leptonicW  , const reco::Candidate* hadronicW, 
		    double HT, const double& weight)
{
  /** 
      calculate boosted Lorentz vectors
  **/
  // define lorentz vectors for ttbar system
  reco::Particle::LorentzVector ttBar = leptonicTop->p4() + hadronicTop->p4();
  // create boost into reconstructed top quarks/ttbar system
  ROOT::Math::Boost CoMBoostHadTop(hadronicTop->p4().BoostToCM());
  ROOT::Math::Boost CoMBoostLepTop(leptonicTop->p4().BoostToCM());
  ROOT::Math::Boost CoMBoostTtbar (ttBar            .BoostToCM());
  // get lorentz vectors of W and Top without boost
  reco::Particle::LorentzVector HadronicDecayWBoosted   = hadronicW  ->p4();
  reco::Particle::LorentzVector LeptonicDecayWBoosted   = leptonicW  ->p4();
  reco::Particle::LorentzVector HadronicDecayTopBoosted = hadronicTop->p4();
  reco::Particle::LorentzVector LeptonicDecayTopBoosted = leptonicTop->p4();
  // recalculate Lorent vectors using boosts defined above
  // boost W into top rest frame and
  // and top into ttbar rest frame
  HadronicDecayWBoosted   = CoMBoostHadTop(HadronicDecayWBoosted  );
  LeptonicDecayWBoosted   = CoMBoostLepTop(LeptonicDecayWBoosted  );
  HadronicDecayTopBoosted = CoMBoostTtbar (HadronicDecayTopBoosted);
  LeptonicDecayTopBoosted = CoMBoostTtbar (LeptonicDecayTopBoosted);
      
  /** 
      Fill Top Variables for Cross Section Measurement
  **/

  // ---
  //    top variables (as no branch is created, they exist only as plot)
  // ---
  // fill top pt for leptonicTop candidate in combined histogram
  fillValue( "topPt", leptonicTop->p4().pt()     , weight );
  // fill top pt for hadronicTop candidate in combined histogram
  fillValue( "topPt", hadronicTop->p4().pt()     , weight );
  // fill top y for leptonicTop candidate in combined histogram
  fillValue( "topY", leptonicTop->p4().Rapidity(), weight );
  // fill top y for hadronicTop candidate in combined histogram
  fillValue( "topY", hadronicTop->p4().Rapidity(), weight );
  // fill top phi for leptonicTop candidate in combined histogram
  fillValue( "topPhi", leptonicTop->p4().phi()   , weight );
  // fill top phi for hadronicTop candidate in combined histogram
  fillValue( "topPhi", hadronicTop->p4().phi()   , weight );
  // fill leptonic Top mass in combined histogram
  fillValue( "topMass", leptonicTop->mass()      , weight );
  // fill hadronic Top mass in combined histogram
  fillValue( "topMass", hadronicTop->mass()      , weight );
  // fill angle between top and the corresponding W in top rest frame for leptonicTop candidate in combined histogram
  fillValue( "topWAngle", ROOT::Math::VectorUtil::Angle(LeptonicDecayTopBoosted, LeptonicDecayWBoosted), weight );
  // fill angle between top and the corresponding W in top rest frame for hadronicTop candidate in combined histogram
  fillValue( "topWAngle", ROOT::Math::VectorUtil::Angle(HadronicDecayTopBoosted, HadronicDecayWBoosted), weight );

  // ---
  //    top variables for leptonic top
  // ---
  // fill top pt for leptonicTop candidate in separate histogram
  fillValue( "topPtLep", leptonicTop->p4().pt()     , weight );
  // fill top y for leptonicTop candidate in separate histogram
  fillValue( "topYLep", leptonicTop->p4().Rapidity(), weight );
  // fill top phi for leptonicTop candidate in separate histogram
  fillValue( "topPhiLep", leptonicTop->p4().phi()   , weight );
  // fill leptonic Top mass in separate histogram
  fillValue( "lepTopMass", leptonicTop->mass()      , weight );
  // fill angle between top and the corresponding W in top rest frame for leptonicTop candidate in separate histogram
  fillValue( "topWAngleLep", ROOT::Math::VectorUtil::Angle(LeptonicDecayTopBoosted, LeptonicDecayWBoosted), weight );

  // ---
  //    top variables for hadronic top
  // ---
  // fill top pt for hadronicTop candidate in separate histogram
  fillValue( "topPtHad", hadronicTop->p4().pt(), weight );
  // fill top y for hadronicTop candidate in separate histogram
  fillValue( "topYHad", hadronicTop->p4().Rapidity(), weight );
  // fill top phi for hadronicTop candidate in separate histogram
  fillValue( "topPhiHad", hadronicTop->p4().phi(), weight );
  // fill hadronic Top mass in separate histogram
  fillValue( "hadTopMass", hadronicTop->mass(), weight );
  // fill angle between top and the corresponding W in top rest frame for hadronicTop candidate in separate histogram
  fillValue( "topWAngleHad", ROOT::Math::VectorUtil::Angle(HadronicDecayTopBoosted, HadronicDecayWBoosted), weight );


  // ---
  //    ttbar variables
  // ---
  // fill ttbar pt
  fillValue( "ttbarPt", ttBar.pt(), weight );
  // fill ttbar y
  fillValue( "ttbarY", ttBar.Rapidity(), weight );
  // fill ttbar phi
  fillValue( "ttbarPhi", ttBar.phi(), weight );
  // fill ttbar invariant mass
  fillValue( "ttbarMass", ttBar.mass(), weight );
  // fill deltaPhi between both top quarks 
  fillValue( "ttbarDelPhi", deltaPhi(leptonicTop->phi(), hadronicTop->phi()), weight );
  // fill deltaY between both top quarks 
  fillValue( "ttbarDelY", leptonicTop->rapidity()-hadronicTop->rapidity(), weight );
  // fill sum of y of both top quarks 
  fillValue( "ttbarSumY", leptonicTop->rapidity()+hadronicTop->rapidity(), weight );
  // fill HT of the 4 jets assigned to the ttbar decay
  fillValue( "ttbarHT", HT, weight );
}

/// histogram filling for 1D histos using only events with existing genmatch
void 
TopKinematics::fill(const reco::Candidate* leptonicTopRec, const reco::Candidate* leptonicTopGen, 
		    const reco::Candidate* hadronicTopRec, const reco::Candidate* hadronicTopGen, 
		    const reco::Candidate* leptonicWRec  , const reco::Candidate* leptonicWGen, 
		    const reco::Candidate* hadronicWRec  , const reco::Candidate* hadronicWGen,
		    double HTrec, double HTgen, const double& weight)
{
  /** 
      calculate boosted Lorentz vectors
  **/
  // define lorentz vectors for ttbar system
  reco::Particle::LorentzVector genTtBar = leptonicTopGen->p4() + hadronicTopGen->p4();
  reco::Particle::LorentzVector recTtBar = leptonicTopRec->p4() + hadronicTopRec->p4();
  // create boost into reconstructed/generated top quarks/ttbar system
  ROOT::Math::Boost CoMBoostRecHadTop(hadronicTopRec->p4().BoostToCM());
  ROOT::Math::Boost CoMBoostGenHadTop(hadronicTopGen->p4().BoostToCM());
  ROOT::Math::Boost CoMBoostRecLepTop(leptonicTopRec->p4().BoostToCM());
  ROOT::Math::Boost CoMBoostGenLepTop(leptonicTopGen->p4().BoostToCM());
  ROOT::Math::Boost CoMBoostRecTtbar (recTtBar            .BoostToCM());
  ROOT::Math::Boost CoMBoostGenTtbar (genTtBar            .BoostToCM());
  // get lorentz vectors of W and Top without boost
  reco::Particle::LorentzVector recHadronicDecayWBoosted   = hadronicWRec  ->p4();
  reco::Particle::LorentzVector genHadronicDecayWBoosted   = hadronicWGen  ->p4();
  reco::Particle::LorentzVector recLeptonicDecayWBoosted   = leptonicWRec  ->p4();
  reco::Particle::LorentzVector genLeptonicDecayWBoosted   = leptonicWGen  ->p4();
  reco::Particle::LorentzVector recHadronicDecayTopBoosted = hadronicTopRec->p4();
  reco::Particle::LorentzVector genHadronicDecayTopBoosted = hadronicTopGen->p4();
  reco::Particle::LorentzVector recLeptonicDecayTopBoosted = leptonicTopRec->p4();
  reco::Particle::LorentzVector genLeptonicDecayTopBoosted = leptonicTopGen->p4();
  // recalculate Lorent vectors using boosts defined above
  // boost W into top rest frame and top into ttbar rest frame
  recHadronicDecayWBoosted   = CoMBoostRecHadTop(recHadronicDecayWBoosted  );
  genHadronicDecayWBoosted   = CoMBoostGenHadTop(genHadronicDecayWBoosted  );
  recLeptonicDecayWBoosted   = CoMBoostRecLepTop(recLeptonicDecayWBoosted  );
  genLeptonicDecayWBoosted   = CoMBoostGenLepTop(genLeptonicDecayWBoosted  );
  recHadronicDecayTopBoosted = CoMBoostRecTtbar (recHadronicDecayTopBoosted);
  genHadronicDecayTopBoosted = CoMBoostGenTtbar (genHadronicDecayTopBoosted);
  recLeptonicDecayTopBoosted = CoMBoostRecTtbar (recLeptonicDecayTopBoosted);
  genLeptonicDecayTopBoosted = CoMBoostGenTtbar (genLeptonicDecayTopBoosted);

  /** 
      Fill 1D histos for events gen&&rec in the same bin, using function match()
  **/

  // fill top pt for topA candidate in combined histogram
  match( "topPt"       , leptonicTopRec->p4().pt ()     , leptonicTopGen->p4().pt ()      , weight );
  // fill top pt for topA candidate in separate histogram
  match( "topPtLep"    , leptonicTopRec->p4().pt ()      , leptonicTopGen->p4().pt ()     , weight );
  // fill top y for topA candidate in combined histogram
  match( "topY"        , leptonicTopRec->p4().Rapidity(), leptonicTopGen->p4().Rapidity() , weight );
  // fill top y for topA candidate in separate histogram
  match( "topYLep"     , leptonicTopRec->p4().Rapidity() , leptonicTopGen->p4().Rapidity(), weight );
  // fill top phi for topA candidate in combined histogram
  match( "topPhi"      , leptonicTopRec->p4().phi()     , leptonicTopGen->p4().phi()      , weight );
  // fill top phi for topA candidate in separate histogram
  match( "topPhiLep"   , leptonicTopRec->p4().phi()      , leptonicTopGen->p4().phi()     , weight );
  // fill leptonic Top mass for topB candidate in seperate histogram
  match( "lepTopMass"  , leptonicTopRec->mass()         , leptonicTopGen->mass()          , weight );
  // fill leptonic Top mass for topB candidate in combined histogram
  match( "topMass"     , leptonicTopRec->mass()         , leptonicTopGen->mass()          , weight );
  // fill angle between top and the corresponding W in top rest frame for topA candidate in combined histogram
  match( "topWAngle"   , ROOT::Math::VectorUtil::Angle(recLeptonicDecayTopBoosted, recLeptonicDecayWBoosted), 
	                 ROOT::Math::VectorUtil::Angle(genLeptonicDecayTopBoosted, genLeptonicDecayWBoosted), 
	                 weight );
  //match( "topWAngleLep", ROOT::Math::VectorUtil::Angle(recLeptonicDecayTopBoosted, recLeptonicDecayWBoosted), 
  //	                 ROOT::Math::VectorUtil::Angle(genLeptonicDecayTopBoosted, genLeptonicDecayWBoosted), 
  //	                 weight );
  // fill top pt for topB candidate in combined histogram
  match( "topPt"       , hadronicTopRec->p4().pt ()      , hadronicTopGen->p4().pt ()      , weight );
  // fill top pt for topB candidate in separate histogram
  match( "topPtHad"    , hadronicTopRec->p4().pt ()      , hadronicTopGen->p4().pt ()      , weight );
  // fill top y for topB candidate in combined histogram
  match( "topY"        , hadronicTopRec->p4().Rapidity() , hadronicTopGen->p4().Rapidity() , weight );
  // fill top y for topB candidate in separate histogram
  match( "topYHad"     , hadronicTopRec->p4().Rapidity() , hadronicTopGen->p4().Rapidity() , weight );
  // fill top phi for topB candidate in combined histogram
  match( "topPhi"      , hadronicTopRec->p4().phi()      , hadronicTopGen->p4().phi()      , weight );
  // fill top phi for topB candidate in separate histogram
  match( "topPhiHad"   , hadronicTopRec->p4().phi()      , hadronicTopGen->p4().phi()      , weight );
  // fill hadronic Top mass for topB candidate in seperate histogram
  match( "hadTopMass"  , hadronicTopRec->mass()          , hadronicTopGen->mass()          , weight );
  // fill hadronic Top mass for topB candidate in combined histogram
  match( "topMass"     , hadronicTopRec->mass()          , hadronicTopGen->mass()          , weight );
  // fill angle between top and the corresponding Win top rest frame for topB candidate in combined histogram
  match( "topWAngle"   , ROOT::Math::VectorUtil::Angle(recHadronicDecayTopBoosted, recHadronicDecayWBoosted), 
                         ROOT::Math::VectorUtil::Angle(genHadronicDecayTopBoosted, genHadronicDecayWBoosted), 
                         weight );
  // fill angle between top and the corresponding Win top rest frame for topB candidate in combined histogram
  //  match( "topWAngleHad", ROOT::Math::VectorUtil::Angle(recHadronicDecayTopBoosted, recHadronicDecayWBoosted), 
  //                      ROOT::Math::VectorUtil::Angle(genHadronicDecayTopBoosted, genHadronicDecayWBoosted), 
  //                      weight );
  // fill ttbar pt
  match( "ttbarPt"     , recTtBar.pt  ()          , genTtBar.pt  ()          , weight );
  // fill ttbar y
  match( "ttbarY"      , recTtBar.Rapidity ()     , genTtBar.Rapidity ()     , weight );
  // fill ttbar phi
  match( "ttbarPhi"    , recTtBar.phi ()          , genTtBar.phi ()          , weight );
  // fill ttbar invariant mass
  match( "ttbarMass"   , recTtBar.mass()          , genTtBar.mass()          , weight );

  // fill deltaPhi between both top quarks 
  match( "ttbarDelPhi" , deltaPhi(leptonicTopRec->phi(), hadronicTopRec->phi()), 
	                                      deltaPhi(leptonicTopGen->phi(), hadronicTopGen->phi()), weight );
  // fill deltaY between both top quarks 
  match( "ttbarDelY"   , leptonicTopRec->rapidity()-hadronicTopRec->rapidity() , 
                                              leptonicTopGen->rapidity()-hadronicTopGen->rapidity() , weight );

  // fill sum of y of both top quarks 
  match( "ttbarSumY"   , leptonicTopRec->rapidity()+hadronicTopRec->rapidity() , 
	                                      leptonicTopGen->rapidity()+hadronicTopGen->rapidity() , weight );
  // fill HT of the 4 jets assigned to the ttbar decay
  match( "ttbarHT"     , HTrec , HTgen , weight );
}

/// helper function to provid N(gen&&rec)-histo for the determination of stability and purity
void 
TopKinematics::match(const std::string& histo, const double& recValue, const double& genValue, const double& weight)
{
  TH1* hist = hists_.find(histo)->second;
  // loop the bins of histogram 'hist'; note that the first bin
  // starts with '1' and not with '0'
  for(int bin=1; bin<=hist->GetNbinsX(); ++bin){
    // determine lower and upper edge of the corresponding bin
    double lowerEdge = hist->GetBinLowEdge(bin);
    double upperEdge = hist->GetBinLowEdge(bin)+hist->GetBinWidth(bin);
    // only fill the histogram when the genValue & recValue fall into the same bin ('<=' for upper edge)
    if( (lowerEdge<genValue && genValue<=upperEdge) && (lowerEdge<recValue && recValue<=upperEdge) ){
      fillValue( histo, recValue, weight );
      break;
    }
  }
}
