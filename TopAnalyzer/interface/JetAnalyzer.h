#ifndef JetAnalyzer_h
#define JetAnalyzer_h

#include <vector>

#include "TH1D.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

class JetAnalyzer : public edm::EDAnalyzer {

 public:

  explicit JetAnalyzer(const edm::ParameterSet&);
  ~JetAnalyzer();
  
 private:

  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob();

  edm::InputTag jets_;  
  std::vector<int> fromTo_;

  TH1D* multi_;  
  TH1D* pt_;
  TH1D* et_;  
  TH1D* eta_; 
  
  TH1D* chargedHadronFrac_;
  TH1D* neutralHadronFrac_;
  TH1D* chargedEmFrac_;
  TH1D* neutralEmFrac_;
  TH1D* chargedMulti_;
  TH1D* nConst_;
  
  TH1D* bDiscTCHE_;  
  TH1D* bDiscTCHP_;     
  TH1D* bDiscSSVHP_;
  TH1D* bDiscSSVHE_;     
  TH1D* multiTCHEL_;
  TH1D* multiTCHEM_;  
  TH1D* multiTCHET_;
  TH1D* multiTCHPL_;
  TH1D* multiTCHPM_;  
  TH1D* multiTCHPT_;    
  TH1D* multiSSVHEM_;
  TH1D* multiSSVHET_;
  TH1D* multiSSVHPM_;          
};

#endif
