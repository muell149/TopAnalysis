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
  /// histogramm booking for fw
  void book(edm::Service<TFileService>& fileService);
  /// everything which needs to be done after the event loop
  void process(){};

  /// histogram filling interface for rec or gen level for access with fw or fwlite; 
  /// take care that all relevant parts of the top kinematics get properly filled here 
  virtual void fill(const Collection& tops, const double& weight=1.) = 0;

  /// histogram filling for candidate of special type (used for histogram booking)
  void fill(const reco::Candidate* cand, const char* candidateType, const double& weight=1.);
  /// histogram filling for candidate of special type (used for histogram booking) for stability and purity calculation
  void fill(const reco::Candidate* recCand, const reco::Candidate* genCand, const char* candidateType, const double& weight=1.);
  /// histogram filling for candidate of special type (used for histogram booking)
  void fill(const reco::Particle::LorentzVector& cand, const char* candidateType, const double& weight=1.);
  /// histogram filling for candidate of special type (used for histogram booking) for stability and purity calculation
  void fill(const reco::Particle::LorentzVector& recCand, const reco::Particle::LorentzVector& genCand, const char* candidateType, const double& weight=1.);
  /// histogram filling for topA, topB candidate
  void fill(const reco::Candidate* topA, const reco::Candidate* topB, const double& weight=1.);
  /// histogram filling for topA, topB candidate (for stability and purity calculation)
  void fill(const reco::Candidate* recTopA, const reco::Candidate* genTopA, const reco::Candidate* recTopB, const reco::Candidate* genTopB, const double& weight=1.);

 protected:
  /// helper function to determine stability and purity
  void matched(TH1F* hist, const double& genValue, const double& recTop, const double& weight);
};

template <typename Collection> 
void TopKinematics<Collection>::book()
{
  NameScheme kin("kin");
  SingleAnalyzer<Collection>::hists_["muonPt"     ] = new TH1F(kin("muonPt"     ), "muonPt"     ,   30,     0.,    150.);
  SingleAnalyzer<Collection>::hists_["muonEta"    ] = new TH1F(kin("muonEta"    ), "muonEta"    ,   70,    -3.5,    3.5);
  SingleAnalyzer<Collection>::hists_["muonPhi"    ] = new TH1F(kin("muonPhi"    ), "muonPhi"    ,   70,    -3.5,    3.5);
  SingleAnalyzer<Collection>::hists_["bottomPt"   ] = new TH1F(kin("bottomPt"   ), "bottomPt"   ,   30,     0.,    150.);
  SingleAnalyzer<Collection>::hists_["bottomEta"  ] = new TH1F(kin("bottomEta"  ), "bottomEta"  ,   70,    -3.5,    3.5);
  SingleAnalyzer<Collection>::hists_["bottomPhi"  ] = new TH1F(kin("bottomPhi"  ), "bottomPhi"  ,   70,    -3.5,    3.5);
  SingleAnalyzer<Collection>::hists_["lightPt"    ] = new TH1F(kin("lightPt"    ), "lightPt"    ,   30,     0.,    150.);
  SingleAnalyzer<Collection>::hists_["lightEta"   ] = new TH1F(kin("lightEta"   ), "lightEta"   ,   70,    -3.5,    3.5);
  SingleAnalyzer<Collection>::hists_["lightPhi"   ] = new TH1F(kin("lightPhi"   ), "lightPhi"   ,   70,    -3.5,    3.5);
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
  SingleAnalyzer<Collection>::hists_["muonPt"     ] = fs->make<TH1F>(kin("muonPt"     ), "muonPt"     ,   30,     0.,    150.);
  SingleAnalyzer<Collection>::hists_["muonEta"    ] = fs->make<TH1F>(kin("muonEta"    ), "muonEta"    ,   70,    -3.5,    3.5);
  SingleAnalyzer<Collection>::hists_["muonPhi"    ] = fs->make<TH1F>(kin("muonPhi"    ), "muonPhi"    ,   70,    -3.5,    3.5);
  SingleAnalyzer<Collection>::hists_["bottomPt"   ] = fs->make<TH1F>(kin("bottomPt"   ), "bottomPt"   ,   30,     0.,    150.);
  SingleAnalyzer<Collection>::hists_["bottomEta"  ] = fs->make<TH1F>(kin("bottomEta"  ), "bottomEta"  ,   70,    -3.5,    3.5);
  SingleAnalyzer<Collection>::hists_["bottomPhi"  ] = fs->make<TH1F>(kin("bottomPhi"  ), "bottomPhi"  ,   70,    -3.5,    3.5);
  SingleAnalyzer<Collection>::hists_["lightPt"    ] = fs->make<TH1F>(kin("lightPt"    ), "lightPt"    ,   30,     0.,    150.);
  SingleAnalyzer<Collection>::hists_["lightEta"   ] = fs->make<TH1F>(kin("lightEta"   ), "lightEta"   ,   70,    -3.5,    3.5);
  SingleAnalyzer<Collection>::hists_["lightPhi"   ] = fs->make<TH1F>(kin("lightPhi"   ), "lightPhi"   ,   70,    -3.5,    3.5);
  SingleAnalyzer<Collection>::hists_["topPt"      ] = fs->make<TH1F>(kin("topPt"      ), "topPt"      ,   15,     0.,    150.);
  SingleAnalyzer<Collection>::hists_["topEta"     ] = fs->make<TH1F>(kin("topEta"     ), "topEta"     ,   10,   -3.5,     3.5);
  SingleAnalyzer<Collection>::hists_["topPhi"     ] = fs->make<TH1F>(kin("topPhi"     ), "topPhi"     ,   10,   -3.5,     3.5);
  SingleAnalyzer<Collection>::hists_["ttbarPt"    ] = fs->make<TH1F>(kin("ttbarPt"    ), "ttbarPt"    ,   15,     0.,    150.);
  SingleAnalyzer<Collection>::hists_["ttbarEta"   ] = fs->make<TH1F>(kin("ttbarEta"   ), "ttbarEta"   ,   10,   -3.5,     3.5);
  SingleAnalyzer<Collection>::hists_["ttbarPhi"   ] = fs->make<TH1F>(kin("ttbarPhi"   ), "ttbarPhi"   ,   10,   -3.5,     3.5);
  SingleAnalyzer<Collection>::hists_["ttbarMass"  ] = fs->make<TH1F>(kin("ttbarMass"  ), "ttbarMass"  ,   15,   300.,   1000.);
  SingleAnalyzer<Collection>::hists_["ttbarDelPhi"] = fs->make<TH1F>(kin("ttbarDelPhi"), "ttbarDelPhi",   10,   -3.5,     3.5);
}

/// histogram filling for candidate of special type (used for histogram booking)
template <typename Collection>
void
TopKinematics<Collection>::fill(const reco::Candidate* cand, const char* candidateName, const double& weight)
{
  fill(cand->p4(), candidateName, weight);  
}

/// histogram filling for candidate of special type (used for histogram booking) for stability and purity calculation
template <typename Collection>
void
TopKinematics<Collection>::fill(const reco::Candidate* recCand, const reco::Candidate* genCand, const char* candidateName, const double& weight)
{
  fill(recCand->p4(), genCand->p4(), candidateName, weight);  
}

/// histogram filling for candidate of special type (used for histogram booking)
template <typename Collection>
void
TopKinematics<Collection>::fill(const reco::Particle::LorentzVector& cand, const char* candidateName, const double& weight)
{
  std::string histName(candidateName);
  SingleAnalyzer<Collection>::hists_.find(histName+"Pt" )->second->Fill( cand.pt()  , weight );
  SingleAnalyzer<Collection>::hists_.find(histName+"Eta")->second->Fill( cand.eta() , weight );
  SingleAnalyzer<Collection>::hists_.find(histName+"Phi")->second->Fill( cand.phi() , weight );
}

/// histogram filling for candidate of special type (used for histogram booking)
template <typename Collection>
void
TopKinematics<Collection>::fill(const reco::Particle::LorentzVector& recCand, const reco::Particle::LorentzVector& genCand, const char* candidateName, const double& weight)
{
  std::string histName(candidateName);
  matched( SingleAnalyzer<Collection>::hists_.find(histName+"Pt" )->second , recCand.pt () , genCand.pt () , weight );
  matched( SingleAnalyzer<Collection>::hists_.find(histName+"Eta")->second , recCand.eta() , genCand.eta() , weight );
  matched( SingleAnalyzer<Collection>::hists_.find(histName+"Phi")->second , recCand.phi() , genCand.phi() , weight );
}

/// histogram filling for topA, topB candidate (for stability and purity calculation)
template <typename Collection>
void
TopKinematics<Collection>::fill(const reco::Candidate* topA, const reco::Candidate* topB, const double& weight)
{
  fill( topA->p4()+topB->p4(), "ttbar" ,  weight );  
  SingleAnalyzer<Collection>::hists_.find("ttbarMass"  )->second->Fill( (topA->p4()+topB->p4()).mass()     , weight );
  SingleAnalyzer<Collection>::hists_.find("ttbarDelPhi")->second->Fill( deltaPhi(topA->phi(), topB->phi()) , weight );
}

/// histogram filling for topA, topB candidate (for stability and purity calculation)
template <typename Collection>
void 
TopKinematics<Collection>::fill(const reco::Candidate* recTopA, const reco::Candidate* genTopA, const reco::Candidate* recTopB, const reco::Candidate* genTopB, const double& weight)
{
  reco::Particle::LorentzVector genTtbar = genTopA->p4()+genTopB->p4();
  reco::Particle::LorentzVector recTtbar = recTopA->p4()+recTopB->p4();
  fill( recTtbar, genTtbar, "ttbar" ,  weight );  
  matched(SingleAnalyzer<Collection>::hists_.find("ttbarMass"  )->second, genTtbar.mass(), recTtbar.mass(),   weight );
  matched(SingleAnalyzer<Collection>::hists_.find("ttbarDelPhi")->second, deltaPhi(genTopA->phi(), genTopB->phi()), deltaPhi(recTopA->phi(), recTopB->phi()),   weight );
}

/// helper function to determine stability and purity
template <typename Collection>
void 
TopKinematics<Collection>::matched(TH1F* hist, const double& genValue, const double& recValue, const double& weight)
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

#endif
