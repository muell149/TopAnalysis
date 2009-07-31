#ifndef TopKinematics_h
#define TopKinematics_h

#include "DataFormats/Math/interface/deltaPhi.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "TopAnalysis/TopUtils/interface/NameScheme.h"
#include "TopAnalysis/TopAnalyzer/interface/SingleAnalyzer.h"

//
// top kinematics analyzer equally usable for full 
// framework or framework lite
//

template <typename Collection> 
class TopKinematics : public SingleAnalyzer<Collection> {

 public:
  /// default constructor for fw lite
  explicit TopKinematics(){};
  /// default constructor for full fw
  explicit TopKinematics(const edm::ParameterSet& configFile){};
  /// default destructor
  ~TopKinematics(){};

  /// histogramm booking for fwlite 
  void book();
  /// histogramm booking for full fw
  void book(edm::Service<TFileService>& fileService);
  /// histogram filling interface for rec or gen level for access with fwlite or full framework
  virtual void fill(Collection& tops, const double& weight=1.) = 0;
  /// histogram filling for fwlite and for full fw
  void fill(const reco::Candidate* topA, const reco::Candidate* topB, const double& weight=1.);
  /// histogram filling for fwlite and for full fw (for stability and purity calculation)
  void fill(const reco::Candidate* genTopA, const reco::Candidate* genTopB, const reco::Candidate* recTopA, const reco::Candidate* recTopB, const double& weight=1.);
  /// helper function to determine stability and purity
  void fillHistogramMatched(TH1F* hist, const double& genTop, const double& recTop, const double& weight);
  /// everything which needs to be done after the event loop
  void process(){};
};

template <typename Collection> 
void TopKinematics<Collection>::book()
{
  NameScheme kin("kin");
  SingleAnalyzer<Collection>::hists_["topPt"      ] = new TH1F(kin("topPt"      ), "topPt"      ,   15,     0.,    150.);
  SingleAnalyzer<Collection>::hists_["topEta"     ] = new TH1F(kin("topEta"     ), "topEta"     ,   10,   -3.5,     3.5);
  SingleAnalyzer<Collection>::hists_["topPhi"     ] = new TH1F(kin("topPhi"     ), "topPhi"     ,   10,   -3.5,     3.5);
  SingleAnalyzer<Collection>::hists_["ttbarPt"    ] = new TH1F(kin("ttbarPt"    ), "ttbarPt"    ,   15,     0.,    150.);
  SingleAnalyzer<Collection>::hists_["ttbarEta"   ] = new TH1F(kin("ttbarEta"   ), "ttbarEta"   ,   10,   -3.5,     3.5);
  SingleAnalyzer<Collection>::hists_["ttbarPhi"   ] = new TH1F(kin("ttbarPhi"   ), "ttbarPhi"   ,   10,   -3.5,     3.5);
  SingleAnalyzer<Collection>::hists_["ttbarMass"  ] = new TH1F(kin("ttbarMass"  ), "ttbarMass"  ,   15,   300.,   1000.);
  SingleAnalyzer<Collection>::hists_["ttbarDelPhi"] = new TH1F(kin("ttbarDelPhi"), "ttbarDelPhi",   10,   -3.5,     3.5);
}

template <typename Collection> 
void TopKinematics<Collection>::book(edm::Service<TFileService>& fs)
{
  NameScheme kin("kin");
  SingleAnalyzer<Collection>::hists_["topPt"      ] = fs->make<TH1F>(kin("topPt"      ), "topPt"      ,   15,     0.,    150.);
  SingleAnalyzer<Collection>::hists_["topEta"     ] = fs->make<TH1F>(kin("topEta"     ), "topEta"     ,   10,   -3.5,     3.5);
  SingleAnalyzer<Collection>::hists_["topPhi"     ] = fs->make<TH1F>(kin("topPhi"     ), "topPhi"     ,   10,   -3.5,     3.5);
  SingleAnalyzer<Collection>::hists_["ttbarPt"    ] = fs->make<TH1F>(kin("ttbarPt"    ), "ttbarPt"    ,   15,     0.,    150.);
  SingleAnalyzer<Collection>::hists_["ttbarEta"   ] = fs->make<TH1F>(kin("ttbarEta"   ), "ttbarEta"   ,   10,   -3.5,     3.5);
  SingleAnalyzer<Collection>::hists_["ttbarPhi"   ] = fs->make<TH1F>(kin("ttbarPhi"   ), "ttbarPhi"   ,   10,   -3.5,     3.5);
  SingleAnalyzer<Collection>::hists_["ttbarMass"  ] = fs->make<TH1F>(kin("ttbarMass"  ), "ttbarMass"  ,   15,   300.,   1000.);
  SingleAnalyzer<Collection>::hists_["ttbarDelPhi"] = fs->make<TH1F>(kin("ttbarDelPhi"), "ttbarDelPhi",   10,   -3.5,     3.5);
}

/// histogram filling for fwlite and for full fw
template <typename Collection>
void
TopKinematics<Collection>::fill(const reco::Candidate* topA, const reco::Candidate* topB, const double& weight)
{
  // fill basic kinematics for top&topBar candidate
  SingleAnalyzer<Collection>::hists_["topPt"      ]->Fill( topA->pt()  ,   weight );
  SingleAnalyzer<Collection>::hists_["topPt"      ]->Fill( topB->pt()  ,   weight );
  SingleAnalyzer<Collection>::hists_["topEta"     ]->Fill( topA->eta() ,   weight );
  SingleAnalyzer<Collection>::hists_["topEta"     ]->Fill( topB->eta() ,   weight );
  SingleAnalyzer<Collection>::hists_["topPhi"     ]->Fill( topA->phi() ,   weight );
  SingleAnalyzer<Collection>::hists_["topPhi"     ]->Fill( topB->phi() ,   weight );

  // fill basic kinematics for ttbar system
  reco::Particle::LorentzVector ttbar = topA->p4() + topB->p4();
  SingleAnalyzer<Collection>::hists_["ttbarPt"    ]->Fill( ttbar.pt()  ,   weight );
  SingleAnalyzer<Collection>::hists_["ttbarEta"   ]->Fill( ttbar.eta() ,   weight );
  SingleAnalyzer<Collection>::hists_["ttbarPhi"   ]->Fill( ttbar.phi() ,   weight );
  SingleAnalyzer<Collection>::hists_["ttbarMass"  ]->Fill( ttbar.mass(),   weight );
  SingleAnalyzer<Collection>::hists_["ttbarDelPhi"]->Fill( deltaPhi(topA->phi(), topB->phi()), weight );
}

/// histogram filling for fwlite and for full fw (for stability and purity calculation)
template <typename Collection>
void 
TopKinematics<Collection>::fill(const reco::Candidate* genTopA, const reco::Candidate* genTopB, const reco::Candidate* recTopA, const reco::Candidate* recTopB, const double& weight)
{
  // fill basic kinematics for top&topBar candidate
  fillHistogramMatched(SingleAnalyzer<Collection>::hists_["topPt"      ], genTopA->pt()  , recTopA->pt()  ,   weight );
  fillHistogramMatched(SingleAnalyzer<Collection>::hists_["topPt"      ], genTopB->pt()  , recTopB->pt()  ,   weight );
  fillHistogramMatched(SingleAnalyzer<Collection>::hists_["topEta"     ], genTopA->eta() , recTopA->eta() ,   weight );
  fillHistogramMatched(SingleAnalyzer<Collection>::hists_["topEta"     ], genTopB->eta() , recTopB->eta() ,   weight );
  fillHistogramMatched(SingleAnalyzer<Collection>::hists_["topPhi"     ], genTopA->phi() , recTopA->phi() ,   weight );
  fillHistogramMatched(SingleAnalyzer<Collection>::hists_["topPhi"     ], genTopB->phi() , recTopB->phi() ,   weight );

  // fill basic kinematics for ttbar system
  reco::Particle::LorentzVector genTtbar = genTopA->p4() + genTopB->p4();
  reco::Particle::LorentzVector recTtbar = recTopA->p4() + recTopB->p4();
  fillHistogramMatched(SingleAnalyzer<Collection>::hists_["ttbarPt"    ], genTtbar.pt()  , recTtbar.pt()  ,   weight );
  fillHistogramMatched(SingleAnalyzer<Collection>::hists_["ttbarEta"   ], genTtbar.eta() , recTtbar.eta() ,   weight );
  fillHistogramMatched(SingleAnalyzer<Collection>::hists_["ttbarPhi"   ], genTtbar.phi() , recTtbar.phi() ,   weight );
  fillHistogramMatched(SingleAnalyzer<Collection>::hists_["ttbarMass"  ], genTtbar.mass(), recTtbar.mass(),   weight );
  fillHistogramMatched(SingleAnalyzer<Collection>::hists_["ttbarDelPhi"], deltaPhi(genTopA->phi(), genTopB->phi()), deltaPhi(recTopA->phi(), recTopB->phi()),   weight );
}

template <typename Collection>
void 
TopKinematics<Collection>::fillHistogramMatched(TH1F* hist, const double& genTop, const double& recTop, const double& weight)
{
  for(int bin=1; bin<=hist->GetNbinsX(); ++bin){
    double lowerEdge = hist->GetBinLowEdge(bin);
    double upperEdge = hist->GetBinLowEdge(bin)+hist->GetBinWidth(bin);
    if( (lowerEdge<genTop && genTop<=upperEdge) && (lowerEdge<recTop && recTop<=upperEdge) ){
      hist->Fill(recTop, weight);
      break;
    }
  }
}

#endif
