#ifndef MuonResolution_h
#define MuonResolution_h

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
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "TopAnalysis/TopUtils/interface/NameScheme.h"


class MuonResolution{

 public:

  explicit MuonResolution(std::vector<double>, double);
  explicit MuonResolution(const edm::ParameterSet&);
  ~MuonResolution(){};

  void book();
  void book(edm::Service<TFileService>&);
  void book(edm::Service<TFileService>&, ofstream&);
  void fill(const edm::Event&, const std::vector<pat::Muon>&, const double&);
  void fill(const std::vector<pat::Muon>&, const double&);
  void norm(){};
  void write(const char*, const char*);

 private:

  std::vector<double> binsPt_;
  double matchDR_;

  TH1F *calPt_, *resPt_;
  std::vector<TH1F*> relPt_;
};

#endif
