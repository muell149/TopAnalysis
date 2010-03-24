#ifndef FullHadHypothesisAnalyzer_h
#define FullHadHypothesisAnalyzer_h

#include "TH1F.h"
#include "TH2F.h"

#include "FWCore/Framework/interface/EDAnalyzer.h"

class FullHadHypothesisAnalyzer : public edm::EDAnalyzer {

 public:

  explicit FullHadHypothesisAnalyzer(const edm::ParameterSet&);
  ~FullHadHypothesisAnalyzer(){};
  
 private:

  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob();

  edm::InputTag fullHadEvt_;
  edm::InputTag hypoClassKey_;

  TH1F* WPt_;
  TH1F* WEta_;
  TH1F* WMass_;

  TH1F* WPullPt_;
  TH1F* WPullEta_;
  TH1F* WPullMass_;

  TH1F* TopPt_;
  TH1F* TopEta_;
  TH1F* TopMass_;

  TH1F* TopPullPt_;
  TH1F* TopPullEta_;
  TH1F* TopPullMass_;

  TH1F* genMatchDr_;
  TH1F* mvaDisc_;

  TH2F* genMatchDrVsTopPullMass_;
  TH2F* mvaDiscVsTopPullMass_;

};

#endif
