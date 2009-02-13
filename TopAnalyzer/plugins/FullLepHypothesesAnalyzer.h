#ifndef FullLepHypothesesAnalyzer_h
#define FullLepHypothesesAnalyzer_h

#include "TH1F.h"
#include "TH2F.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/Candidate/interface/Candidate.h"

#include "AnalysisDataFormats/TopObjects/interface/TtFullLeptonicEvent.h"

class FullLepHypothesesAnalyzer : public edm::EDAnalyzer {

 public:

  explicit FullLepHypothesesAnalyzer(const edm::ParameterSet&);
  ~FullLepHypothesesAnalyzer(){};
  
 private:

  virtual void beginJob(const edm::EventSetup&) ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob();

  edm::InputTag FullLepEvt_;
  edm::InputTag hypoKey_;
  edm::InputTag wgt_;
  unsigned int nJetsMax_;
  double maxSumDRGenMatch_;
  double minProbKinFit_;
  std::string hist_;

  void bookKinHistos      (edm::Service<TFileService>&, ofstream&);
//  void bookKinResHistos   (edm::Service<TFileService>&, ofstream&);
//  void bookJetCorrelHistos(edm::Service<TFileService>&, ofstream&);
//  void bookQualityHistos  (edm::Service<TFileService>&, ofstream&);

  void fillKinHistos      (std::vector<TH1F*>&, const reco::Candidate&, const double&);
//  void fillKinResHistos   (std::vector<TH1F*>&, const reco::Candidate&, const reco::Candidate&, const double&);
//  void fillJetCorrelHistos(const std::vector<int>&, const std::vector<int>&, const double&);
//  void fillQualityHistos  (const TtFullLeptonicEvent&, const double&);

  std::vector<TH1F*> TopKin_;
  std::vector<TH1F*> WplusKin_;
  std::vector<TH1F*> BKin_;
  std::vector<TH1F*> LepBarKin_;
  std::vector<TH1F*> NuKin_;
  
  std::vector<TH1F*> TopBarKin_;
  std::vector<TH1F*> WminusKin_;
  std::vector<TH1F*> BBarKin_;
  std::vector<TH1F*> LepKin_;
  std::vector<TH1F*> NuBarKin_;
  
  TH1F* recNuMetMatching_;
  TH1F* recNuBarMetMatching_;

//   TH2F* hadBJetCorrel_;
//   TH2F* hadQJetCorrel_;
//   TH2F* hadPJetCorrel_;
//   TH2F* lepBJetCorrel_;
 
//   TH1F* goodHypo_;
 
//   TH1F* genMatchSumDR_;
//   TH1F* genMatchSumPt_;
//   TH1F* mvaDisc_;
//   TH1F* fitChi2_;
//   TH1F* fitProb_;

//   TH2F* genMatchSumDRVsSumPt_;
//   TH2F* genMatchSumDRVsHadWMass_;
//   TH2F* genMatchSumDRVsHadTopMass_;
//   TH2F* genMatchSumDRVsMVADisc_;
//   TH2F* genMatchSumDRVsFitProb_;
//   TH2F* mvaDiscVsHadWMass_;
//   TH2F* mvaDiscVsHadTopMass_;
//   TH2F* mvaDiscVsFitProb_;
//   TH2F* fitProbVsHadWMass_;
//   TH2F* fitProbVsHadTopMass_;

};

#endif
