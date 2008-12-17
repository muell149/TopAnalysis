#ifndef TtDiMuonTopObjAna_h
#define TtDiMuonTopObjAna_h

#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"

class TH1F;
class pat::Muon;
class pat::Jet;
class pat::MET;
class edm::Event;

class TtDiMuonTopObjAna{

 public:

  explicit TtDiMuonTopObjAna(const edm::ParameterSet& cfg);
  ~TtDiMuonTopObjAna();

  void book(ofstream& file);
  void fill(const  edm::Event& evt, 
	    double weight=1.); 
    
 private:
  
  typedef std::vector<pat::Muon> PatMuonCollection;
  typedef std::vector<pat::Jet>  PatJetCollection;  
  typedef std::vector<pat::MET>  PatMETCollection;  
  
  double leptonPtCut_;
  double jetPtCut_;
  double metCut_; 
  
  edm::InputTag muons_;
  edm::InputTag jets_; 
  edm::InputTag mets_; 
      
  TH1F * muPt_;
  TH1F * muP_;  
  TH1F * muEta_;  
  TH1F * muPhi_; 
  TH1F * muN_; 

  TH1F * jetPt_ ;  
  TH1F * jetEt_ ;
  TH1F * jetE_  ;  
  TH1F * jetEta_;  
  TH1F * jetPhi_; 
  TH1F * jetN_; 
  
  TH1F * met_;
  TH1F * metPhi_;
};

#endif
