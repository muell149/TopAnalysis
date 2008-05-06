#ifndef JetId_h
#define JetId_h

#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "TH1F.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "TopAnalysis/TopUtils/interface/NameScheme.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

class JetId{

 public:

  explicit JetId(const edm::ParameterSet&);
  ~JetId(){};

  void book();
  void book(ofstream&);
  void fill(const edm::Event&, const std::vector<pat::Jet>&, const double&);
  void norm(){
    aProfEta_->Scale(1./normJet_);
    aProfPhi_->Scale(1./normJet_); 
    for(unsigned int idx=0; idx<profEta_.size(); ++idx)
      profEta_[idx]->Scale(1./normEvt_);
    for(unsigned int idx=0; idx<profPhi_.size(); ++idx)
      profPhi_[idx]->Scale(1./normEvt_);
  };

 private:

  // additional evt content/steerings  
  int nJets_;
  double normEvt_;
  double normJet_;

  TH1F *aEmf_;
  TH1F *aHad_;
  TH1F *aHof_;
  TH1F* nTwr_;
  TH1F *aProfEta_;
  TH1F *aProfPhi_;

  std::vector<TH1F*> emf_;
  std::vector<TH1F*> had_;
  std::vector<TH1F*> hof_;
  std::vector<TH1F*> profEta_;
  std::vector<TH1F*> profPhi_;
};

#endif
