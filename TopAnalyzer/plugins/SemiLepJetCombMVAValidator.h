#ifndef SemiLepJetCombMVAValidator_h
#define SemiLepJetCombMVAValidator_h

#include "TH1F.h"

#include "FWCore/Framework/interface/EDAnalyzer.h"

class SemiLepJetCombMVAValidator : public edm::EDAnalyzer {

 public:

  explicit SemiLepJetCombMVAValidator(const edm::ParameterSet&);
  ~SemiLepJetCombMVAValidator(){};
  
 private:

  virtual void beginJob(const edm::EventSetup&);
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob();

  bool isValid(const std::vector<int>& vec)
    const { for(unsigned int i=0; i<vec.size(); i++) if(vec[i]<0) return false; return true; }

 private:

  edm::InputTag match_;
  edm::InputTag combs_;
  edm::InputTag discs_;

  TH1F* valid_match;  // number of events with valid jet-parton matching
  TH1F* valid_combs;  // number of events with valid jetCombs from MVAComputer
  TH1F* hyp_disc_sig; // discriminators of all true jetCombs
  TH1F* hyp_disc_bkg; // discriminators of all false jetCombs
  TH1F* evt_disc_sig; // discriminators of best jetCombs per event if best one is the true one
  TH1F* evt_disc_bkg; // discriminators of best jetCombs per event if best one is a false one
};

#endif
