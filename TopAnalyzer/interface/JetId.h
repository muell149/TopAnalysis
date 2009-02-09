#ifndef JetId_h
#define JetId_h

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

#include "TopAnalysis/TopUtils/interface/NameScheme.h"
#include "DataFormats/PatCandidates/interface/Jet.h"


class JetId{

 public:

  explicit JetId(int);
  explicit JetId(const edm::ParameterSet&);
  ~JetId(){};

  void book();
  void book(edm::Service<TFileService>&);
  void book(edm::Service<TFileService>&, ofstream&);
  void fill(const edm::Event&, const std::vector<pat::Jet>&, const double&);
  void fill(const std::vector<pat::Jet>&, const double&);
  void norm(){
    for(unsigned int idx=0; idx<profEta_eJetBins_.size(); ++idx)
      profEta_eJetBins_[idx]->Scale(1./normJet_);
    for(unsigned int idx=0; idx<profPhi_eJetBins_.size(); ++idx)
      profPhi_eJetBins_[idx]->Scale(1./normJet_); 
    for(unsigned int idx=0; idx<profEta_.size(); ++idx)
      profEta_[idx]->Scale(1./normEvt_);
    for(unsigned int idx=0; idx<profPhi_.size(); ++idx)
      profPhi_[idx]->Scale(1./normEvt_);
  };
  void write(const char*, const char*);

 private:

  // additional evt content/steerings  
  int nJets_;
  double normEvt_;
  double normJet_;

  TH1F *aEmf_;
  TH1F *aHad_;
  TH1F *aHof_;
  
  int eJetBins_;
  std::vector<double> eJetLimits_;

  std::vector<TH1F*> nTwr_eJetBins_;
  std::vector<TH1F*> profEta_eJetBins_;
  std::vector<TH1F*> profPhi_eJetBins_;
  std::vector<TH1F*> eTwrJet_eJetBins_;

  std::vector<TH1F*> emf_;
  std::vector<TH1F*> had_;
  std::vector<TH1F*> hof_;
  std::vector<TH1F*> profEta_;
  std::vector<TH1F*> profPhi_;
};

#endif
