#ifndef SemiLepEventFilter_h
#define SemiLepEventFilter_h

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "TopAnalysis/TopFilter/interface/PtFilter.h"
#include "TopAnalysis/TopFilter/interface/EtaFilter.h"
#include "TopAnalysis/TopFilter/interface/IsolationFilter.h"
#include "TopAnalysis/TopFilter/interface/JetIsolationFilter.h"

template <typename Lep> 
class SemiLepEventFilter : public edm::EDFilter {

 public:
  
  typedef IsolationFilter <Lep> LepIsolationFilter;
  typedef JetIsolationFilter <Lep> LepJetIsolationFilter;
  
 public:

  explicit SemiLepEventFilter(const edm::ParameterSet&);
  ~SemiLepEventFilter(){};
  
 private:
  
  virtual void beginJob(const edm::EventSetup&) ;
  virtual bool filter(edm::Event&, const edm::EventSetup&);
  virtual void endJob();
  
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

  PtFilter  jetPt_;
  PtFilter  lepPt_;
  EtaFilter jetEta_; 
  EtaFilter lepEta_; 
  LepIsolationFilter trkIso_;
  LepIsolationFilter calIso_;
  LepJetIsolationFilter jetIso_;
};

template <typename Lep> 
SemiLepEventFilter<Lep>::SemiLepEventFilter(const edm::ParameterSet& cfg):
  leps_( cfg.template getParameter<std::vector<edm::InputTag> >("leps" ) ),
  jets_( cfg.template getParameter<std::vector<edm::InputTag> >("jets" ) ),
  useJetEta_( cfg.template getParameter<bool>("useJetEta" ) ),
  useJetPt_ ( cfg.template getParameter<bool>("useJetPt"  ) ),
  useLepEta_( cfg.template getParameter<bool>("useLepEta" ) ),
  useLepPt_ ( cfg.template getParameter<bool>("useLepPt"  ) ),
  useTrkIso_( cfg.template getParameter<bool>("useTrkIso" ) ),
  useCalIso_( cfg.template getParameter<bool>("useCalIso" ) ),
  useJetIso_( cfg.template getParameter<bool>("useJetIso" ) ),
  jetPt_ ( cfg.template getParameter<edm::ParameterSet> ("jetPt" ) ), 
  lepPt_ ( cfg.template getParameter<edm::ParameterSet> ("lepPt" ) ),
  jetEta_( cfg.template getParameter<edm::ParameterSet> ("jetEta") ), 
  lepEta_( cfg.template getParameter<edm::ParameterSet> ("lepEta") ), 
  trkIso_( cfg.template getParameter<edm::ParameterSet> ("trkIso") ), 
  calIso_( cfg.template getParameter<edm::ParameterSet> ("calIso") ), 
  jetIso_( cfg.template getParameter<edm::ParameterSet> ("jetIso") )
{
}

template <typename Lep> 
bool SemiLepEventFilter<Lep>::filter(edm::Event& evt, const edm::EventSetup& setup)
{
  // receive input tags for lepton kinematic
  std::vector<edm::View<reco::Candidate> > kinLeps;
  for(std::vector<edm::InputTag>::const_iterator tag = leps_.begin(); 
      tag!=leps_.end(); ++tag){
    edm::Handle<edm::View<reco::Candidate> > src;
    evt.getByLabel(*tag, src);
    kinLeps.push_back(*src);
  }

  // receive input tags for lepton isolation
  std::vector<Lep> isoLeps;
  for(std::vector<edm::InputTag>::const_iterator tag = leps_.begin(); 
      tag!=leps_.end(); ++tag){
    edm::Handle<Lep> src;
    evt.getByLabel(*tag, src);
    isoLeps.push_back(*src);
  }

  // receive input tags for jet kinematic
  std::vector<edm::View<reco::Candidate> > kinJets;
  for(std::vector<edm::InputTag>::const_iterator tag = jets_.begin(); 
      tag!=jets_.end(); ++tag){
    edm::Handle<edm::View<reco::Candidate> > src;
    evt.getByLabel(*tag, src);
    kinJets.push_back(*src);
  }

  // do the event selection
  bool passed=true;
  if(passed && useLepEta_) passed=lepEta_(evt, kinLeps);
  if(passed && useLepPt_ ) passed=lepPt_ (evt, kinLeps);
  if(passed && useTrkIso_) passed=trkIso_(evt, isoLeps);
  if(passed && useCalIso_) passed=calIso_(evt, isoLeps);
  if(passed && useJetIso_) passed=jetIso_(evt, isoLeps);
  if(passed && useJetEta_) passed=jetEta_(evt, kinJets);
  if(passed && useJetPt_ ) passed=jetPt_ (evt, kinJets);
  return passed;
}

template <typename Lep> 
void SemiLepEventFilter<Lep>::beginJob(const edm::EventSetup&)
{
}

template <typename Lep> 
void SemiLepEventFilter<Lep>::endJob()
{
  using std::cout;
  using std::endl;

  cout << "----------------------------------" << endl;
  cout << " useLepEta_ [" << useLepEta_ << "]" << endl;
  cout << " useLepPt_  [" << useLepPt_  << "]" << endl;
  cout << " useTrkIso_ [" << useTrkIso_ << "]" << endl;
  cout << " useCalIso_ [" << useCalIso_ << "]" << endl;
  cout << " useJetIso_ [" << useJetIso_ << "]" << endl;
  cout << " useJetEta_ [" << useJetEta_ << "]" << endl;
  cout << " useJetPt_  [" << useJetPt_  << "]" << endl;
  cout << "----------------------------------" << endl;

  if( !useLepEta_ && !useLepPt_ && !useTrkIso_ && !useCalIso_ && !useJetIso_
      && !useJetEta_ && !useJetPt_ )
    cout << "no cuts were applied..." << endl;
  else {
    if(useLepEta_) lepEta_.summarize();
    if(useLepPt_ ) lepPt_ .summarize();
    if(useTrkIso_) trkIso_.summarize();
    if(useCalIso_) calIso_.summarize();
    if(useJetIso_) jetIso_.summarize();
    if(useJetEta_) jetEta_.summarize();
    if(useJetPt_ ) jetPt_ .summarize();
  }
}

#endif
