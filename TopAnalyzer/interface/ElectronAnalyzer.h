#ifndef ElectronAnalyzer_h
#define ElectronAnalyzer_h

#include <vector>

#include "TH1D.h"

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

class ElectronAnalyzer : public edm::EDAnalyzer {

public:

  explicit ElectronAnalyzer(const edm::ParameterSet&);
  ~ElectronAnalyzer();

private:

  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob();

  edm::InputTag electrons_;
  edm::InputTag jets_;

  bool verbosity_;
  std::vector<int> fromTo_;

  typedef std::vector<pat::Electron> PatElectronCollection;
  typedef std::vector<pat::Jet>  PatJetCollection;

  TH1D* multi_;
  TH1D* pt_;
  TH1D* eta_;
  TH1D* phi_;
  TH1D* supercluster_energy_;
  TH1D* hcaloverecal_;
  TH1D* fbrem_;
  TH1D* eoverp_;
  TH1D* iso_combEE_;
  TH1D* iso_combEB_;
  TH1D* iso_combEE2_;
  TH1D* iso_combEB2_;
  TH1D* jet_dist_;
  TH1D* dB_;
  TH1D* d0_;
  TH1D* deltaphi_;
  TH1D* deltaeta_;
  TH1D* sigmaietaieta_;
  TH1D* electronmap_;
  TH1D* nlost_;
  TH1D* convDcot_;
  TH1D* convDist_;

    edm::InputTag weight_;

};

#endif
