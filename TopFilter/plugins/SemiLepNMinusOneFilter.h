#ifndef SemiLepNMinusOneFilter_h
#define SemiLepNMinusOneFilter_h

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "TopAnalysis/TopFilter/interface/PtFilter.h"
#include "TopAnalysis/TopFilter/interface/EtaFilter.h"
#include "TopAnalysis/TopFilter/interface/JetIsolationFilter.h"
#include "TopAnalysis/TopFilter/interface/CaloIsolationFilter.h"
#include "TopAnalysis/TopFilter/interface/TrackIsolationFilter.h"

template <typename Leps, typename Jets> 
class SemiLepNMinusOneFilter : public edm::EDFilter {

 public:
  
  typedef PtFilter <Jets> JetPtFilter;
  typedef EtaFilter<Jets> JetEtaFilter;
  typedef PtFilter <Leps> LepPtFilter;
  typedef EtaFilter<Leps> LepEtaFilter;
  typedef JetIsolationFilter  <Leps> LepJetIsolationFilter;
  typedef CaloIsolationFilter <Leps> LepCalIsolationFilter;
  typedef TrackIsolationFilter<Leps> LepTrkIsolationFilter;
  
 public:

  explicit SemiLepNMinusOneFilter(const edm::ParameterSet&);
  ~SemiLepNMinusOneFilter(){};
  
 private:
  
  virtual void beginJob(const edm::EventSetup&) ;
  virtual bool filter(edm::Event&, const edm::EventSetup&);
  
 private:

  std::vector<edm::InputTag> leps_;
  std::vector<edm::InputTag> jets_;

  bool useJetEta_;
  bool useJetPt_;
  bool useLepEta_;
  bool useLepPt_;
  bool useTrkIso_;
  bool useCalIso_;
  bool useJetIso_;

  JetPtFilter  jetPt_;
  JetEtaFilter jetEta_; 
  LepPtFilter  lepPt_;
  LepEtaFilter lepEta_;
  LepTrkIsolationFilter trkIso_;
  LepCalIsolationFilter calIso_;
  LepJetIsolationFilter jetIso_;
};

template <typename Leps, typename Jets> 
SemiLepNMinusOneFilter<Leps, Jets>::SemiLepNMinusOneFilter(const edm::ParameterSet& cfg):
  leps_( cfg.template getParameter<std::vector<edm::InputTag> >("leptons" ) ),
  jets_( cfg.template getParameter<std::vector<edm::InputTag> >("jets"    ) ),
  useJetEta_( cfg.template getParameter<bool>("useJetEta" ) ),
  useJetPt_ ( cfg.template getParameter<bool>("useJetPt"  ) ),
  useLepEta_( cfg.template getParameter<bool>("useLepEta" ) ),
  useLepPt_ ( cfg.template getParameter<bool>("useLepPt"  ) ),
  useTrkIso_( cfg.template getParameter<bool>("useTrkIso" ) ),
  useCalIso_( cfg.template getParameter<bool>("useCalIso" ) ),
  useJetIso_( cfg.template getParameter<bool>("useJetIso" ) ),
  jetPt_ (cfg), jetEta_(cfg), lepPt_(cfg), lepEta_(cfg), 
  trkIso_(cfg), calIso_(cfg), jetIso_(cfg)
{
}

template <typename Leps, typename Jets> 
bool SemiLepNMinusOneFilter<Leps, Jets>::filter(edm::Event& evt, const edm::EventSetup& setup)
{
  // receive lepton input tags
  std::vector<Leps> leps;
  for(std::vector<edm::InputTag>::const_iterator tag = leps_.begin(); 
      tag!=leps_.end(); ++tag){
    edm::Handle<Leps> src;
    evt.getByLabel(*tag, src);
    leps.push_back(*src);
  }

  // receive jet input tags
  std::vector<Jets> jets;
  for(std::vector<edm::InputTag>::const_iterator tag = jets_.begin(); 
      tag!=jets_.end(); ++tag){
    edm::Handle<Jets> src;
    evt.getByLabel(*tag, src);
    jets.push_back(*src);
  }

  // do the event selection
  bool passed=true;
  if(useLepEta_) passed=lepEta_(evt, leps);
  if(useLepPt_ ) passed=lepPt_ (evt, leps);
  if(useTrkIso_) passed=trkIso_(evt, leps);
  if(useCalIso_) passed=calIso_(evt, leps);
  if(useJetIso_) passed=jetIso_(evt, leps);
  if(useJetEta_) passed=jetEta_(evt, jets);
  if(useJetPt_ ) passed=jetPt_ (evt, jets);
  return passed;
}

template <typename Leptons, typename Jets> 
void SemiLepNMinusOneFilter<Leptons, Jets>::beginJob(const edm::EventSetup&)
{
}

#endif
