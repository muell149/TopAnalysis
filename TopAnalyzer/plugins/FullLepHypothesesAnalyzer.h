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
  void bookKinResHistos   (edm::Service<TFileService>&, ofstream&);
  void bookQualityHistos  (edm::Service<TFileService>&, ofstream&);

  void fillKinHistos      (std::vector<TH1F*>&, const reco::Candidate&, const double&);
  void fillKinResHistos   (std::vector<TH1F*>&, const reco::Candidate&, const reco::Candidate&, const double&);
  void fillQualityHistos  (const TtFullLeptonicEvent&, const double&);

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
  
  std::vector<TH1F*> TopKinRes_;
  std::vector<TH1F*> WplusKinRes_;
  std::vector<TH1F*> BKinRes_;
  std::vector<TH1F*> LepBarKinRes_;
  std::vector<TH1F*> NuKinRes_;  
  std::vector<TH1F*> TopBarKinRes_;
  std::vector<TH1F*> WminusKinRes_;
  std::vector<TH1F*> BBarKinRes_;
  std::vector<TH1F*> LepKinRes_;
  std::vector<TH1F*> NuBarKinRes_;  
  
  TH1F* goodHypo_;
  
  TH1F* genMatchSumDR_;
  TH1F* genMatchSumPt_;  
};

#endif
