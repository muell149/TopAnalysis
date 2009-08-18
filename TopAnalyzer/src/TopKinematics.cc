#include "DataFormats/Math/interface/deltaPhi.h"
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
  hists_["topPt"      ] = new TH1F( "topPt"       , "topPt"      ,    8, CrossSection::topPt     );
  // top eta (at the moment both top candidates are filled in one histogram)
  hists_["topEta"     ] = new TH1F( "topEta"      , "topEta"     ,    8, CrossSection::topEta    );
  // top phi (at the moment both top candidates are filled in one histogram)
  hists_["topPhi"     ] = new TH1F( "topPhi"      , "topPhi"     ,   10,   -3.14,    3.14        );
  // ttbar pair pt
  hists_["ttbarPt"    ] = new TH1F( "ttbarPt"     , "ttbarPt"    ,    8, CrossSection::ttbarPt   );
  // ttbar pair eta
  hists_["ttbarEta"   ] = new TH1F( "ttbarEta"    , "ttbarEta"   ,    6, CrossSection::ttbarEta  );
  // ttbar pair phi
  hists_["ttbarPhi"   ] = new TH1F( "ttbarPhi"    , "ttbarPhi"   ,   10,   -3.14,    3.14        );
  // ttbar pair invariant mass
  hists_["ttbarMass"  ] = new TH1F( "ttbarMass"   , "ttbarMass"  ,    6, CrossSection::ttbarMass );
  // deltaPhi between both top quarks
  hists_["ttbarDelPhi"] = new TH1F( "ttbarDelPhi" , "ttbarDelPhi",   10,   -3.14,    3.14        );
}

/// histogramm booking for fw
void TopKinematics::book(edm::Service<TFileService>& fs)
{
  /** 
      Top Variables for Cross Section Measurement
  **/
  // top pt (at the moment both top candidates are filled in one histogram)
  hists_["topPt"       ] = fs->make<TH1F>( "topPt"       , "topPt"      ,    8, CrossSection::topPt     );
  // top eta (at the moment both top candidates are filled in one histogram)
  hists_["topEta"      ] = fs->make<TH1F>( "topEta"      , "topEta"     ,    8, CrossSection::topEta    );
  // top phi (at the moment both top candidates are filled in one histogram)
  hists_["topPhi"      ] = fs->make<TH1F>( "topPhi"      , "topPhi"     ,   10,   -3.14,    3.14        );
  // ttbar pair pt
  hists_["ttbarPt"     ] = fs->make<TH1F>( "ttbarPt"     , "ttbarPt"    ,    8, CrossSection::ttbarPt   );
  // ttbar pair eta
  hists_["ttbarEta"    ] = fs->make<TH1F>( "ttbarEta"    , "ttbarEta"   ,    6, CrossSection::ttbarEta  );
  // ttbar pair phi
  hists_["ttbarPhi"    ] = fs->make<TH1F>( "ttbarPhi"    , "ttbarPhi"   ,   10,   -3.14,    3.14        );
  // ttbar pair invariant mass
  hists_["ttbarMass"   ] = fs->make<TH1F>( "ttbarMass"   , "ttbarMass"  ,    6, CrossSection::ttbarMass );
  // deltaPhi between both top quarks
  hists_["ttbarDelPhi" ] = fs->make<TH1F>( "ttbarDelPhi" , "ttbarDelPhi",   10,   -3.14,    3.14        );

  /** 
      Correlation Plots
  **/
  // gen-rec level correlation top pt
  corrs_["topPt_"      ] = fs->make<TH2F>( "topPt_"      ,  "topPt_"    ,  100,    0.,  300.,    100,   0.,  300.);
  // gen-rec level correlation top eta
  corrs_["topEta_"     ] = fs->make<TH2F>( "topEta_"     ,  "topEta_"   ,  100,   -3.,    3.,    100,  -3.,    3.);
  // gen-rec level correlation ttbar pt
  corrs_["ttbarPt_"    ] = fs->make<TH2F>( "ttbarPt_"    ,  "ttbarPt_"  ,  100,    0.,  200.,    100,   0.,  200.);
  // gen-rec level correlation ttbar eta
  corrs_["ttbarEta_"   ] = fs->make<TH2F>( "ttbarEta_"   ,  "ttbarEta_" ,  100,   -3.,    3.,    100,  -3.,    3.);
  // gen-rec level correlation ttbar mass
  corrs_["ttbarMass_"  ] = fs->make<TH2F>( "ttbarMass_"  ,  "ttbarMass_",  100,  300., 1000.,    100, 300., 1000.);
}


/// histogram filling interface for generator level for access with fwlite or full framework
void
TopKinematics::fill(const TtGenEvent& tops, const double& weight)
{
  // make sure to have a ttbar pair belonging to the semi-leptonic decay channel with 
  // a muon in the final state
  if( tops.isSemiLeptonic(WDecay::kMuon) ){
    fill(tops.hadronicDecayTop(), tops.leptonicDecayTop(), weight);
  }
}

/// histogram filling interface for reconstruction level for access with fwlite or full framework
void
TopKinematics::fill(const TtSemiLeptonicEvent& tops, const double& weight)
{
  // make sure to have a valid hypothesis on reconstruction level. If this is the case
  // fill matched (for stability & purity determination) or normal depending on the 
  // value of matchForStabilityAndPurity_
  if( tops.genEvent().isAvailable() && tops.genEvent()->isSemiLeptonic(WDecay::kMuon) && tops.isHypoValid(hypoKey_) ){
    if(matchForStabilityAndPurity_){
      fill(tops.hadronicDecayTop(hypoKey_), tops.hadronicDecayTop(), tops.leptonicDecayTop(hypoKey_), tops.leptonicDecayTop(), weight);
    } 
    else{
      fill(tops.hadronicDecayTop(hypoKey_), tops.leptonicDecayTop(hypoKey_), weight);
    }

    // fill rec-gen level correlation plots
    reco::Particle::LorentzVector genTtbar = tops.hadronicDecayTop()->p4()+tops.leptonicDecayTop()->p4();
    reco::Particle::LorentzVector recTtbar = tops.hadronicDecayTop(hypoKey_)->p4()+tops.leptonicDecayTop(hypoKey_)->p4();
    // fill pt correlation plot for ttbar pair    
    corrs_.find("ttbarPt_"   )->second->Fill( genTtbar.pt()   , recTtbar.pt()  , weight );
    // fill eta correlation plot for ttbar pair
    corrs_.find("ttbarEta_"  )->second->Fill( genTtbar.eta()  , recTtbar.eta() , weight );
    // fill mass correlation plot for ttbar pair
    corrs_.find("ttbarMass_" )->second->Fill( genTtbar.mass() , recTtbar.mass(), weight );    
    // fill pt correlation plot for hadronic top candidate
    corrs_.find("topPt_"    )->second->Fill( tops.hadronicDecayTop()->pt() , tops.hadronicDecayTop(hypoKey_)->pt() , weight );
    // fill pt correlation plot for hadronic top candidate
    corrs_.find("topPt_"    )->second->Fill( tops.leptonicDecayTop()->pt() , tops.leptonicDecayTop(hypoKey_)->pt() , weight );    
    // fill eta correlation plot for hadronic top candidate
    corrs_.find("topEta_"   )->second->Fill( tops.leptonicDecayTop()->eta(), tops.leptonicDecayTop(hypoKey_)->eta(), weight );
    // fill eta correlation plot for hadronic top candidate
    corrs_.find("topEta_"   )->second->Fill( tops.leptonicDecayTop()->eta(), tops.leptonicDecayTop(hypoKey_)->eta(), weight );
  }
}

/// histogram filling for topA, topB candidate
void
TopKinematics::fill(const reco::Candidate* topA, const reco::Candidate* topB, const double& weight)
{
  /** 
      Fill Top Variables for Cross Section Measurement
  **/
  reco::Particle::LorentzVector ttBar = topA->p4() + topB->p4();
  // fill top pt for topA candidate
  hists_.find("topPt"       )->second->Fill( topA->p4().pt () , weight );
  // fill top eta for topA candidate
  hists_.find("topEta"      )->second->Fill( topA->p4().eta() , weight );
  // fill top phi for topA candidate
  hists_.find("topPhi"      )->second->Fill( topA->p4().phi() , weight );
  // fill top pt for topB candidate
  hists_.find("topPt"       )->second->Fill( topB->p4().pt () , weight );
  // fill top eta for topB candidate
  hists_.find("topEta"      )->second->Fill( topB->p4().eta() , weight );
  // fill top phi for topB candidate
  hists_.find("topPhi"      )->second->Fill( topB->p4().phi() , weight );
  // fill ttbar pt
  hists_.find("ttbarPt"     )->second->Fill( ttBar.pt  ()     , weight );
  // fill ttbar eta
  hists_.find("ttbarEta"    )->second->Fill( ttBar.eta ()     , weight );
  // fill ttbar phi
  hists_.find("ttbarPhi"    )->second->Fill( ttBar.phi ()     , weight );
  // fill ttbar invariant mass
  hists_.find("ttbarMass"   )->second->Fill( ttBar.mass()     , weight );
  // fill deltaPhi between both top quarks 
  hists_.find("ttbarDelPhi" )->second->Fill( deltaPhi(topA->phi(), topB->phi()) , weight );
}

/// histogram filling for candidate topA and topB (for stability and purity calculation)
void 
TopKinematics::fill(const reco::Candidate* recTopA, const reco::Candidate* genTopA, const reco::Candidate* recTopB, const reco::Candidate* genTopB, const double& weight)
{
  /** 
      Fill Top Variables for Cross Section Measurement
  **/
  reco::Particle::LorentzVector genTtBar = genTopA->p4() + genTopB->p4();
  reco::Particle::LorentzVector recTtBar = recTopA->p4() + recTopB->p4();
  // fill top pt for topA candidate
  match( hists_.find("topPt"       )->second , recTopA->p4().pt () , genTopA->p4().pt () , weight );
  // fill top eta for topA candidate
  match( hists_.find("topEta"      )->second , recTopA->p4().eta() , genTopA->p4().eta() , weight );
  // fill top phi for topA candidate
  match( hists_.find("topPhi"      )->second , recTopA->p4().phi() , genTopA->p4().phi() , weight );
  // fill top pt for topB candidate
  match( hists_.find("topPt"       )->second , recTopB->p4().pt () , genTopB->p4().pt () , weight );
  // fill top eta for topB candidate
  match( hists_.find("topEta"      )->second , recTopB->p4().eta() , genTopB->p4().eta() , weight );
  // fill top phi for topB candidate
  match( hists_.find("topPhi"      )->second , recTopB->p4().phi() , genTopB->p4().phi() , weight );
  // fill ttbar pt
  match( hists_.find("ttbarPt"     )->second , recTtBar.pt  ()     , genTtBar.pt  ()     , weight );
  // fill ttbar eta
  match( hists_.find("ttbarEta"    )->second , recTtBar.eta ()     , genTtBar.eta ()     , weight );
  // fill ttbar phi
  match( hists_.find("ttbarPhi"    )->second , recTtBar.phi ()     , genTtBar.phi ()     , weight );
  // fill ttbar invariant mass
  match( hists_.find("ttbarMass"   )->second , recTtBar.mass()     , genTtBar.mass()     , weight );
  // fill deltaPhi between both top quarks 
  match( hists_.find("ttbarDelPhi" )->second , deltaPhi(recTopA->phi(), recTopB->phi()), deltaPhi(genTopA->phi(), genTopB->phi()), weight );
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
