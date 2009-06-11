#ifndef BSMKinematic_h
#define BSMKinematic_h

#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TMath.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"

#include "AnalysisDataFormats/TopObjects/interface/TtDilepEvtSolution.h"
#include "TopAnalysis/TopAnalyzer/interface/TtDiMuonTopObjAna.h"
#include "TopAnalysis/TopAnalyzer/interface/TtDiMuonGenEvtAna.h"
#include "TopAnalysis/TopAnalyzer/interface/TtDiMuonKinSolAna.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/angle.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/CaloTowers/interface/CaloTower.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "TopAnalysis/TopUtils/interface/NameScheme.h"
#include "TopAnalysis/TopUtils/interface/RootSystem.h"
#include "TopAnalysis/TopUtils/interface/RootHistograms.h"


class BSMKinematic{

 public:

  explicit BSMKinematic(const edm::ParameterSet&,int);
  explicit BSMKinematic(const edm::ParameterSet&);
  ~BSMKinematic(){
    // free allocated space
    if(fwLite_){

      delete isoJet_;
      delete isoJet5_;
      delete isoJet10_;
      delete isoJet15_;
      delete isoJet20_;
      delete isoJet25_;
      delete isoJet30_;
      delete isoJet35_;
      delete isoJet40_;
      delete isoTrkPt_;
      delete isoCalPt_;
      delete isoRelPt_;
      delete isoTrkN_;
      delete isoEcalN_;
      delete isoHcalN_;
      delete dREcalPt_;
      delete dREcalN_;
      delete dRHcalPt_;
      delete dRHcalN_;
      delete dRTrkPt_;
      delete dRTrkN_;
      delete dREcalPt2_;
      delete dREcalN2_;
      delete dRHcalPt2_;
      delete dRHcalN2_;
      delete dRTrkPt2_;
      delete dRTrkN2_;
      delete ptVsTrkIso_;
      delete ptVsCalIso_;
    }
  };
 
  void book();
  void book(edm::Service<TFileService>&);
  void book(edm::Service<TFileService>&, ofstream&);
  void fill(const edm::Event&, const std::vector<pat::Muon>&, const double&);
  void fill(const edm::Event&, const std::vector<pat::Jet>& jets,
	    const std::vector<pat::Muon>& muons,const std::vector<pat::MET>& mets, const double&);
  void norm(){
    double totalNumberOfMuons = allEn_->GetEntries();
    dREcalPt_->Scale( 1./totalNumberOfMuons ); 
    dREcalN_ ->Scale( 1./totalNumberOfMuons ); 
    dRHcalPt_->Scale( 1./totalNumberOfMuons ); 
    dRHcalN_ ->Scale( 1./totalNumberOfMuons ); 
    dRTrkPt_ ->Scale( 1./totalNumberOfMuons ); 
    dRTrkN_  ->Scale( 1./totalNumberOfMuons );
    
    int idx=0;
    for( ;idx<4 ;++idx)
      {
	muon_dREcalPt_[idx]->Scale( 1./(en_[idx]->GetEntries()) );
	muon_dREcalN_[idx]->Scale( 1./(en_[idx]->GetEntries()) );
	muon_dRHcalPt_[idx]->Scale( 1./(en_[idx]->GetEntries()) );
	muon_dRHcalN_[idx]->Scale( 1./(en_[idx]->GetEntries()) );
	muon_dRTrkPt_[idx]->Scale( 1./(en_[idx]->GetEntries()) );
	muon_dRTrkN_[idx]->Scale( 1./(en_[idx]->GetEntries()) );
      }
  };
  void write(TFile&, const char*);
  
 private:

  bool fwLite_;
  edm::InputTag jets_;
  edm::InputTag metSource_;

  int nMuons_;

  TH1F *angle_mu1mu2_;
  TH1F *angle_mu1MET_;
  TH1F *angle_mu2MET_;

  TH1F *allEn_;
  TH1F *allPt_;
  TH1F *allEta_;
  TH1F *allPhi_;

  TH1F* DeltaPhi_;

  std::vector<TH1F*> en_;
  std::vector<TH1F*> pt_;
  std::vector<TH1F*> eta_;
  std::vector<TH1F*> phi_;

  std::vector<TH1F*> DeltaPhi_Jet_muon_;
  std::vector<TH1F*> DeltaPhi_farJet_muon_;
  std::vector<TH1F*> DeltaPhi_nearJet_muon_;

  TH1F *dR_muon_jet_[4][4];
  TH2F *dimuon_isoRelPt_[4][4];
  TH2F *dimuon_isoRelPt2_[4][4];
 
  std::vector<TH1F*> muon_dREcalPt_;
  std::vector<TH1F*> muon_dREcalN_;
  std::vector<TH1F*> muon_dRHcalPt_;
  std::vector<TH1F*> muon_dRHcalN_;
  std::vector<TH1F*> muon_dRTrkPt_;
  std::vector<TH1F*> muon_dRTrkN_;

  std::vector<TH1F*> muon_dREcalPt2_;
  std::vector<TH1F*> muon_dREcalN2_;
  std::vector<TH1F*> muon_dRHcalPt2_;
  std::vector<TH1F*> muon_dRHcalN2_;
  std::vector<TH1F*> muon_dRTrkPt2_;
  std::vector<TH1F*> muon_dRTrkN2_;

  std::vector<TH2F*> muon_isoRelPt2d_;

  std::vector<TH1F*> muon_isoTrkPt_;
  std::vector<TH1F*> muon_isoCalPt_;
  std::vector<TH1F*> muon_isoRelPt_;
  std::vector<TH1F*> muon_isoRelPt2_;
  std::vector<TH1F*> muon_isoTrkN_;
  std::vector<TH1F*> muon_isoEcalN_;
  std::vector<TH1F*> muon_isoHcalN_;

  std::vector<TH2F*> muon_ptVsTrkIso_;
  std::vector<TH2F*> muon_ptVsCalIso_;

  TH1F *isoJet_;
  TH1F *isoJet5_;
  TH1F *isoJet10_;
  TH1F *isoJet15_;
  TH1F *isoJet20_;
  TH1F *isoJet25_;
  TH1F *isoJet30_;
  TH1F *isoJet35_;
  TH1F *isoJet40_;
  TH1F *isoTrkPt_;
  TH1F *isoCalPt_;
  TH1F *isoRelPt_;
  TH1F *isoTrkN_;
  TH1F *isoEcalN_;
  TH1F *isoHcalN_;
  TH1F *dREcalPt_;
  TH1F *dREcalN_;
  TH1F *dRHcalPt_;
  TH1F *dRHcalN_;
  TH1F *dRTrkPt_;
  TH1F *dRTrkN_;
  TH1F *dREcalPt2_;
  TH1F *dREcalN2_;
  TH1F *dRHcalPt2_;
  TH1F *dRHcalN2_;
  TH1F *dRTrkPt2_;
  TH1F *dRTrkN2_;

  TH2F *ptVsTrkIso_;
  TH2F *ptVsCalIso_;

  TH1F *Di_muon_mass_;
  TH1F *Di_muon_di_jet_mass_;
  TH1F *Quad_jet_mass_;

  TH1F *Missing_energy_;

};

#endif
