#ifndef JetResolution_h
#define JetResolution_h

#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "TH1F.h"
#include "TFile.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "TopAnalysis/TopUtils/interface/NameScheme.h"


class JetResolution{
  
 public:
  
  explicit JetResolution(int, double, std::vector<double>);
  explicit JetResolution(const edm::ParameterSet&);
  ~JetResolution(){};

  void book();
  void book(edm::Service<TFileService>&);
  void book(edm::Service<TFileService>&, ofstream&);
  void fill(const edm::Event&, const std::vector<pat::Jet>&, const double&);
  void fill(const std::vector<pat::Jet>&, const double&);
  void norm(){};
  void write(const char*, const char*);

 private:

  // additional evt content/steerings
  int nJets_;
  std::vector<double> binsPt_;
  double matchDR_;

  TH1F *calPtAll_, *resPtAll_;
  std::vector<TH1F*> relPtAll_;
  std::vector<TH1F*> calPtJet_, resPtJet_;
  std::vector< std::vector<TH1F*> > relPtJet_;
};

#endif
