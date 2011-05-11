#ifndef MuonAnalyzer_h
#define MuonAnalyzer_h

#include <vector>

#include "TH1D.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

class MuonAnalyzer : public edm::EDAnalyzer {

 public:

  explicit MuonAnalyzer(const edm::ParameterSet&);
  ~MuonAnalyzer();
  
 private:

  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob();

  edm::InputTag muons_;
  edm::InputTag jets_;
  
  bool verbosity_;
  std::vector<int> fromTo_;

  typedef std::vector<pat::Muon> PatMuonCollection; 
  typedef std::vector<pat::Jet>  PatJetCollection; 

  TH1D* multi_;
  TH1D* pt_;
  TH1D* eta_;  
  TH1D* dep_ecal_;  
  TH1D* dep_hcal_;  
  TH1D* iso_comb_;
  TH1D* iso_comb2_;   
  TH1D* jet_dist_;    
  TH1D* nhits_;  
  TH1D* n_pixhits_;
  TH1D* n_trackerhits_;
  TH1D* n_mustations_;
  TH1D* n_validmuhits_;  
  TH1D* chi_norm_;
  TH1D* d0_;
  TH1D* dB_;
  TH1D* type_;  
  TH1D* phi_;
};

#endif
