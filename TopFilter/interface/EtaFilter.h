#ifndef EtaFilter_h
#define EtaFilter_h

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


class EtaFilter {

 public:

  explicit EtaFilter(const edm::ParameterSet&);
  ~EtaFilter(){};

 public:

  bool operator()(edm::Event&, const std::vector<edm::View<reco::Candidate> >&);
  bool filter(const std::vector<edm::View<reco::Candidate> >&);
  void summarize();
  
 private:

  std::string name_;
  std::vector<double> minEta_;
  std::vector<double> maxEta_;

 private:

  unsigned int beforeCut_, afterCut_;
};

#endif
  
