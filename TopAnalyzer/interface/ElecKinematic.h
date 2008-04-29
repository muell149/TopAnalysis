#ifndef ElecKinematic_h
#define ElecKinematic_h

#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "TH1F.h"
#include "TH2F.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/CaloTowers/interface/CaloTower.h"

#include "TopAnalysis/TopUtils/interface/NameScheme.h"
#include "DataFormats/PatCandidates/interface/Electron.h"


class ElecKinematic{

 public:

  explicit ElecKinematic(const edm::ParameterSet&);
  ~ElecKinematic(){};

  void book();
  void book(ofstream&);
  void fill(const edm::Event&, const std::vector<pat::Electron>&, const double&);
  
 private:

  // additional evt content/steerings
  edm::InputTag towers_, tracks_;
  double dRMax_;

  TH1F *en_;
  TH1F *pt_;
  TH1F *eta_;
  TH1F *phi_;

  TH1F *isoTrk_;
  TH1F *isoCal_;
  TH1F *isoEcal_;
  TH1F *isoHcal_;
  TH1F *dRTrkPt_;
  TH1F *dRTrkN_;
  TH1F *dRCalPt_;
  TH1F *dRCalN_;
  TH1F *isoCalN_;
  TH1F *isoTrkN_;
  TH1F *closestCtf_;

  TH2F *ptVsTrkIso_;
  TH2F *ptVsCalIso_;
  TH2F *ptVsEcalIso_;
  TH2F *ptVsHcalIso_;
};

#endif
