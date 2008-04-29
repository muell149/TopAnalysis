#ifndef JetKinematic_h
#define JetKinematic_h

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


class JetKinematic{

 public:

  explicit JetKinematic(const edm::ParameterSet&);
  ~JetKinematic(){};

  void book();
  void book(ofstream&);
  void fill(const edm::Event&, const std::vector<pat::Jet>&, const double&);
  
 private:

  // additional evt content/steerings
  int nJets_;

  TH1F *mult_;
  TH1F *n10_;
  TH1F *n20_;
  TH1F *n30_;
  TH1F *n40_;

  TH1F *allEn_;
  TH1F *allEt_;
  TH1F *allEta_;
  TH1F *allPhi_;
  TH1F *scalSum4_;
  TH1F *scalSum6_;

  std::vector<TH1F*> en_;
  std::vector<TH1F*> et_;
  std::vector<TH1F*> eta_;
  std::vector<TH1F*> phi_;
};

#endif
