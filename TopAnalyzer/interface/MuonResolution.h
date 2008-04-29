#ifndef MuonResolution_h
#define MuonResolution_h

#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "TH1F.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "TopAnalysis/TopUtils/interface/NameScheme.h"
#include "DataFormats/PatCandidates/interface/Muon.h"


class MuonResolution{

 public:

  explicit MuonResolution(const edm::ParameterSet&);
  ~MuonResolution(){};

  void book();
  void book(ofstream&);
  void fill(const edm::Event&, const std::vector<pat::Muon>&, const double&);

 private:

  std::vector<double> binsPt_;
  double matchDR_;

  TH1F *calPt_, *resPt_;
  std::vector<TH1F*> relPt_;
};

#endif
