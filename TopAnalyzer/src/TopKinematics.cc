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
  // this is for docummentation how to book histograms with variable binning
  // double ptBinning[] = {0., 10., 30., 50., 80., 120.};
  // hists_["topPt"] = new TH1F( "topPt" , "topPt" , 5, topBinning);

  // top pt (at the moment both top candidates are filled in one histogram)
  hists_["topPt"      ] = new TH1F( "topPt"       , "topPt"      ,   15,     0.,    150. );
  // top eta (at the moment both top candidates are filled in one histogram)
  hists_["topEta"     ] = new TH1F( "topEta"      , "topEta"     ,   10,   -3.5,     3.5 );
  // top phi (at the moment both top candidates are filled in one histogram)
  hists_["topPhi"     ] = new TH1F( "topPhi"      , "topPhi"     ,   10,  -3.14,    3.14 );
  // ttbar pair pt
  hists_["ttbarPt"    ] = new TH1F( "ttbarPt"     , "ttbarPt"    ,   15,     0.,    150. );
  // ttbar pair eta
  hists_["ttbarEta"   ] = new TH1F( "ttbarEta"    , "ttbarEta"   ,   10,   -3.5,     3.5 );
  // ttbar pair phi
  hists_["ttbarPhi"   ] = new TH1F( "ttbarPhi"    , "ttbarPhi"   ,   10,  -3.14,    3.14 );
  // ttbar pair invariant mass
  hists_["ttbarMass"  ] = new TH1F( "ttbarMass"   , "ttbarMass"  ,   15,   300.,   1000. );
  // deltaPhi between both top quarks
  hists_["ttbarDelPhi"] = new TH1F( "ttbarDelPhi" , "ttbarDelPhi",   10,  -3.14,    3.14 );
}

/// histogramm booking for fw
void TopKinematics::book(edm::Service<TFileService>& fs)
{
  /** 
      Top Variables for Cross Section Measurement
  **/
  // binning for top variables
  double ptTopBinning    [] = {  0.,    9.,  33.,   63., 99.,  135., 171.,  216., 300.};
  double etaTopBinning   [] = { -3., -1.92, -1.2, -0.48,  0.,  0.48,  1.2,  1.92,   3.};
  // binning for ttbar variables
  //double massTtBarBinning[] = {300., 342., 398., 489., 615., 790., 1000.  };
  //double ptTtbarBinning  [] = {0., 10., 20., 30., 40., 60., 80., 130., 200.};
  //double etaTtBarBinning [] = { -3., -2.3, -1.6, 0., 1.6, 2.3, 3. };

  // top pt (at the moment both top candidates are filled in one histogram)
  hists_["topPt"      ] = fs->make<TH1F>( "topPt"       , "topPt"      ,    8, ptTopBinning  );
  // top eta (at the moment both top candidates are filled in one histogram)
  hists_["topEta"     ] = fs->make<TH1F>( "topEta"      , "topEta"     ,    8, etaTopBinning );
  // top phi (at the moment both top candidates are filled in one histogram)
  hists_["topPhi"     ] = fs->make<TH1F>( "topPhi"      , "topPhi"     ,   10,  -3.14,    3.14 );
  // ttbar pair pt
  hists_["ttbarPt"    ] = fs->make<TH1F>( "ttbarPt"     , "ttbarPt"    ,   15,     0.,    150. );
  // ttbar pair eta
  hists_["ttbarEta"   ] = fs->make<TH1F>( "ttbarEta"    , "ttbarEta"   ,   10,   -3.5,     3.5 );
  // ttbar pair phi
  hists_["ttbarPhi"   ] = fs->make<TH1F>( "ttbarPhi"    , "ttbarPhi"   ,   10,  -3.14,    3.14 );
  // ttbar pair invariant mass
  hists_["ttbarMass"  ] = fs->make<TH1F>( "ttbarMass"   , "ttbarMass"  ,   15,   300.,   1000. );
  // deltaPhi between both top quarks
  hists_["ttbarDelPhi"] = fs->make<TH1F>( "ttbarDelPhi" , "ttbarDelPhi",   10,  -3.14,    3.14 );

//2 D Hist
  hists_["genRecTopPt"] = (TH2F*)(fs->make<TH2F>)("genRecTopPt", "genRecTopPt",  100,   0.,     300., 100,   0.,     300.);
//   hists_["genRecTopEta"] = fs->make<TH2F>("genRecTopEta", "genRecTopEta", 100,   -3.,     3., 100,   -3.,     3.);
//   hists_["genRecTtbarEta"] = fs->make<TH2F>("genRecTtbarEta", "genRecTtbarEta", 100,   -3.,     3., 100,   -3., 3.);
//   hists_["genRecTtbarPt"] = fs->make<TH2F>("genRecTtbarPt", "genRecTtbarPt",  100,   0.,     200., 100,   0.,     200.);
//   hists_["genRecTtbarMass"] = fs->make<TH2F>("genRecTtbarMass", "genRecTtbarMass",  100,   300.,     1000., 100,   300.,     1000.);
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
  //value of matchForStabilityAndPurity_
  if( tops.isHypoValid(hypoKey_) ){
    if(matchForStabilityAndPurity_){
      fill(tops.hadronicDecayTop(hypoKey_), tops.genEvent()->hadronicDecayTop(), tops.leptonicDecayTop(hypoKey_), tops.genEvent()->leptonicDecayTop(), weight);
    } 
    else{
      fill(tops.hadronicDecayTop(hypoKey_), tops.leptonicDecayTop(hypoKey_), weight);
    }

    if( dynamic_cast<TH2F*>(hists_.find("genRecTopPt" )->second) ){
      dynamic_cast<TH2F*>(hists_.find("genRecTopPt")->second)->Fill( tops.hadronicDecayTop(hypoKey_)->pt(), tops.hadronicDecayTop()->pt() , weight );
    }
//    hists_.find("genRecTopPt" )->second->Fill( tops.leptonicDecayTop(hypoKey_)->pt() , tops.leptonicDecayTop()->pt(), weight );
    
//     hists_.find("genRecTopEta" )->second->Fill( genTopA->eta(), recTopA->eta() , weight );
//     hists_.find("genRecTopEta" )->second->Fill( genTopB->eta() , recTopB->eta(), weight );

//     reco::Particle::LorentzVector genTtbar = genTopA->p4()+genTopB->p4();
//     reco::Particle::LorentzVector recTtbar = recTopA->p4()+recTopB->p4();
    
//     hists_.find("genRecTtbarEta" )->second->Fill( genTtbar.eta(), recTtbar.eta() , weight );
//     hists_.find("genRecTtbarEta" )->second->Fill( genTtbar.eta() , recTtbar.eta(), weight );
//     hists_.find("genRecTtbarPt" )->second->Fill( genTtbar.pt() , recTtbar.pt(), weight );
//     hists_.find("genRecTtbarMass" )->second->Fill( genTtbar.mass() , recTtbar.mass(), weight );    
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
