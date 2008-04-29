#ifndef JetResolution_h
#define JetResolution_h

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
#include "DataFormats/PatCandidates/interface/Jet.h"

class JetResolution{
  
 public:
  
  explicit JetResolution(const edm::ParameterSet&);
  ~JetResolution(){};

  void book();
  void book(ofstream&);
  void fill(const edm::Event&, const std::vector<pat::Jet>&, const double&);

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
