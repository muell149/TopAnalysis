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
  //double test[] = {0., 13., 100.};
  //hists_["muonPt"] = new TH1F( "muonPt" , "muonPt" , 2, test);
  hists_["topPt"      ] = new TH1F( "topPt"       , "topPt"      ,   15,     0.,    150. );
  hists_["topEta"     ] = new TH1F( "topEta"      , "topEta"     ,   10,   -3.5,     3.5 );
  hists_["topPhi"     ] = new TH1F( "topPhi"      , "topPhi"     ,   10,   -3.5,     3.5 );
  hists_["ttbarPt"    ] = new TH1F( "ttbarPt"     , "ttbarPt"    ,   15,     0.,    150. );
  hists_["ttbarEta"   ] = new TH1F( "ttbarEta"    , "ttbarEta"   ,   10,   -3.5,     3.5 );
  hists_["ttbarPhi"   ] = new TH1F( "ttbarPhi"    , "ttbarPhi"   ,   10,   -3.5,     3.5 );
  hists_["ttbarMass"  ] = new TH1F( "ttbarMass"   , "ttbarMass"  ,   15,   300.,   1000. );
  hists_["ttbarDelPhi"] = new TH1F( "ttbarDelPhi" , "ttbarDelPhi",   10,   -3.5,     3.5 );
}

/// histogramm booking for fw
void TopKinematics::book(edm::Service<TFileService>& fs)
{
  //double test[] = {0., 13., 100.};
  //hists_["muonPt"] = fs->make<TH1F>( "muonPt" , "muonPt",   2, test);
  hists_["topPt"      ] = fs->make<TH1F>( "topPt"       , "topPt"      ,   15,     0.,    150.);
  hists_["topEta"     ] = fs->make<TH1F>( "topEta"      , "topEta"     ,   10,   -3.5,     3.5);
  hists_["topPhi"     ] = fs->make<TH1F>( "topPhi"      , "topPhi"     ,   10,   -3.5,     3.5);
  hists_["ttbarPt"    ] = fs->make<TH1F>( "ttbarPt"     , "ttbarPt"    ,   15,     0.,    150.);
  hists_["ttbarEta"   ] = fs->make<TH1F>( "ttbarEta"    , "ttbarEta"   ,   10,   -3.5,     3.5);
  hists_["ttbarPhi"   ] = fs->make<TH1F>( "ttbarPhi"    , "ttbarPhi"   ,   10,   -3.5,     3.5);
  hists_["ttbarMass"  ] = fs->make<TH1F>( "ttbarMass"   , "ttbarMass"  ,   15,   300.,   1000.);
  hists_["ttbarDelPhi"] = fs->make<TH1F>( "ttbarDelPhi" , "ttbarDelPhi",   10,   -3.5,     3.5);
}


/// histogram filling interface for rec level for access with fwlite or full framework
void
TopKinematics::fill(const TtGenEvent& tops, const double& weight)
{
  if( tops.isSemiLeptonic(WDecay::kMuon) ){
    fill(tops.hadronicDecayTop(), tops.leptonicDecayTop(), weight);
  }    
}

/// histogram filling interface for rec level for access with fwlite or full framework
void
TopKinematics::fill(const TtSemiLeptonicEvent& tops, const double& weight)
{
  if( tops.isHypoValid(hypoKey_) ){
    if(matchForStabilityAndPurity_){
      fill(tops.hadronicDecayTop(hypoKey_), tops.genEvent()->hadronicDecayTop(), tops.leptonicDecayTop(hypoKey_), tops.genEvent()->leptonicDecayTop(), weight);
    } 
    else{
      fill(tops.hadronicDecayTop(hypoKey_), tops.leptonicDecayTop(hypoKey_), weight);
    }
  }
}

/// histogram filling for topA, topB candidate
void
TopKinematics::fill(const reco::Candidate* topA, const reco::Candidate* topB, const double& weight)
{
  reco::Particle::LorentzVector ttBar = topA->p4() + topB->p4();
  hists_.find( "topPt"       )->second->Fill( topA->p4().pt () , weight );
  hists_.find( "topEta"      )->second->Fill( topA->p4().eta() , weight );
  hists_.find( "topPhi"      )->second->Fill( topA->p4().phi() , weight );
  hists_.find( "topPt"       )->second->Fill( topB->p4().pt () , weight );
  hists_.find( "topEta"      )->second->Fill( topB->p4().eta() , weight );
  hists_.find( "topPhi"      )->second->Fill( topB->p4().phi() , weight );
  hists_.find( "ttbarPt"     )->second->Fill( ttBar.pt  ()     , weight );
  hists_.find( "ttbarEta"    )->second->Fill( ttBar.eta ()     , weight );
  hists_.find( "ttbarPhi"    )->second->Fill( ttBar.phi ()     , weight );
  hists_.find( "ttbarMass"   )->second->Fill( ttBar.mass()     , weight );
  hists_.find( "ttbarDelPhi" )->second->Fill( deltaPhi(topA->phi(), topB->phi()) , weight );
}

/// histogram filling for candidate topA and topB (for stability and purity calculation)
void 
TopKinematics::fill(const reco::Candidate* recTopA, const reco::Candidate* genTopA, const reco::Candidate* recTopB, const reco::Candidate* genTopB, const double& weight)
{
  reco::Particle::LorentzVector genTtBar = genTopA->p4() + genTopB->p4();
  reco::Particle::LorentzVector recTtBar = recTopA->p4() + recTopB->p4();
  match( hists_.find( "topPt"       )->second , recTopA->p4().pt () , genTopA->p4().pt () , weight );
  match( hists_.find( "topEta"      )->second , recTopA->p4().eta() , genTopA->p4().eta() , weight );
  match( hists_.find( "topPhi"      )->second , recTopA->p4().phi() , genTopA->p4().phi() , weight );
  match( hists_.find( "topPt"       )->second , recTopB->p4().pt () , genTopB->p4().pt () , weight );
  match( hists_.find( "topEta"      )->second , recTopB->p4().eta() , genTopB->p4().eta() , weight );
  match( hists_.find( "topPhi"      )->second , recTopB->p4().phi() , genTopB->p4().phi() , weight );
  match( hists_.find( "ttbarPt"     )->second , recTtBar.pt  ()     , genTtBar.pt  ()     , weight );
  match( hists_.find( "ttbarEta"    )->second , recTtBar.eta ()     , genTtBar.eta ()     , weight );
  match( hists_.find( "ttbarPhi"    )->second , recTtBar.phi ()     , genTtBar.phi ()     , weight );
  match( hists_.find( "ttbarMass"   )->second , recTtBar.mass()     , genTtBar.mass()     , weight );
  match( hists_.find( "ttbarDelPhi" )->second , deltaPhi(recTopA->phi(), recTopB->phi()), deltaPhi(genTopA->phi(), genTopB->phi()), weight );
}


/// helper function to determine stability and purity
void 
TopKinematics::match(TH1F* hist, const double& recValue, const double& genValue, const double& weight)
{
  for(int bin=1; bin<=hist->GetNbinsX(); ++bin){
    double lowerEdge = hist->GetBinLowEdge(bin);
    double upperEdge = hist->GetBinLowEdge(bin)+hist->GetBinWidth(bin);
    if( (lowerEdge<genValue && genValue<=upperEdge) && (lowerEdge<recValue && recValue<=upperEdge) ){
      hist->Fill(recValue, weight);
      break;
    }
  }
}
