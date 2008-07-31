#ifndef MuonKinematic_h
#define MuonKinematic_h

#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/CaloTowers/interface/CaloTower.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "TopAnalysis/TopUtils/interface/NameScheme.h"


class MuonKinematic{

 public:

  explicit MuonKinematic(double);
  explicit MuonKinematic(const edm::ParameterSet&);
  ~MuonKinematic(){};

  void book();
  void book(edm::Service<TFileService>&);
  void book(edm::Service<TFileService>&, ofstream&);
  void fill(const edm::Event&, const std::vector<pat::Muon>&, const double&);
  void fill(const std::vector<pat::Jet>& jets,
	    const std::vector<pat::Muon>& muons, const double&);
  void norm(){ 
    dRTrkPt_->Scale(1./dRTrkPt_->GetEntries()); 
    dRTrkN_ ->Scale(1./dRTrkN_ ->GetEntries()); 
    dRCalPt_->Scale(1./dRCalPt_->GetEntries()); 
    dRCalN_ ->Scale(1./dRCalN_ ->GetEntries()); 
  };
  void write(const char*, const char*);
  
 private:

  // additional evt content/steerings
  edm::InputTag jets_;
  double dRMax_;

  TH1F *en_;
  TH1F *pt_;
  TH1F *eta_;
  TH1F *phi_;

  TH1F *isoJet_;
  TH1F *isoJet5_;
  TH1F *isoJet10_;
  TH1F *isoJet15_;
  TH1F *isoJet20_;
  TH1F *isoTrkPt_;
  TH1F *isoCalPt_;
  TH1F *isoTrkN_;
  TH1F *isoCalN_;
  TH1F *dRTrkPt_;
  TH1F *dRCalPt_;
  TH1F *dRTrkN_;
  TH1F *dRCalN_;

  TH2F *ptVsTrkIso_;
  TH2F *ptVsCalIso_;
};

#endif
