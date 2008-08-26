#ifndef PtFilter_h
#define PtFilter_h

#include <memory>
#include <string>
#include <vector>

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/Utilities/interface/EDMException.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"


class PtFilter {

 public:

  explicit PtFilter(const edm::ParameterSet&);
  ~PtFilter(){};
 
 public:

  bool operator()(edm::Event&, const std::vector<edm::View<reco::Candidate> >&, const double&);
  bool filter(const std::vector<edm::View<reco::Candidate> >&);
  void summarize();

 private:

  std::string name_;
  std::vector<double> minPt_;
  std::vector<double> maxPt_;

 private:

  unsigned int beforeCut_, afterCut_;
  double beforeCutWeighted_, afterCutWeighted_;
};

#endif
  
