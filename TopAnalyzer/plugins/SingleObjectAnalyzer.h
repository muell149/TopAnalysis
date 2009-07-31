#ifndef SingleObjectAnalyzer_h
#define SingleObjectAnalyzer_h

#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/Utilities/interface/EDMException.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"

//
// template pluging to be used for the analysis of objects like 
// electrons, muons, jets, or reconstructed top candidates with 
// the full framework:
//
// Collection  :  input collection   
// Analyze     :  analyzer class for a single object type
//

template <typename Collection, typename Analyze> 
class SingleObjectAnalyzer : public edm::EDAnalyzer {

 public:
  /// default contstructor
  explicit SingleObjectAnalyzer(const edm::ParameterSet& configFile);
  /// default destructor
  ~SingleObjectAnalyzer();
  

 private:
  /// everything which has to be done before the event loop  
  virtual void beginJob(const edm::EventSetup& setup) ;
  /// everything which has to be done during the event loop 
  virtual void analyze(const edm::Event& event, const edm::EventSetup& setup);
  /// everything which has to be done after the event loop 
  virtual void endJob();
  

 private:
  /// input collection
  edm::InputTag src_;
  /// event weight
  edm::InputTag wgt_;

  /// run with weights or not
  bool useWgt_;
  /// common analzyer class
  Analyze* analyze_;
};

/// default constructor
template <typename Collection, typename Analyze> 
SingleObjectAnalyzer<Collection, Analyze>::SingleObjectAnalyzer(const edm::ParameterSet& cfg) :
  src_( cfg.getParameter<edm::InputTag>( "input"  ) ),
  wgt_( cfg.getParameter<edm::InputTag>( "weight" ) ),
  useWgt_( cfg.getParameter<bool>( "useWeight" ) )
{
  // construct the common analyzer class with
  // corresponding parameter sets as input 
  analyze_ = new Analyze( cfg.getParameter<edm::ParameterSet>("analyze") );
}

/// default destructor
template <typename Collection, typename Analyze> 
SingleObjectAnalyzer<Collection, Analyze>::~SingleObjectAnalyzer()
{
  // release the allocated space
  delete analyze_;
}

/// everything which has to be done during the event loop 
template <typename Collection, typename Analyze> 
void SingleObjectAnalyzer<Collection, Analyze>::analyze(const edm::Event& event, const edm::EventSetup& setup)
{
  // fetch the input collection from the event content
  edm::Handle<Collection> src; 
  event.getByLabel(src_, src);

  // prepare the event weight
  double weight = 1;
  if(useWgt_) {
    edm::Handle<double> wgt;
    event.getByLabel(wgt_, wgt);
    weight = *wgt;
  }
  // hand over to the common analyzer function
  analyze_->fill(*src, weight);
}

/// everything which has to be done before the event loop  
template <typename Collection, typename Analyze> 
void SingleObjectAnalyzer<Collection, Analyze>::beginJob(const edm::EventSetup& setup)
{
  // check for the existence of the TFileService
  edm::Service<TFileService> fs;
  if( !fs ){
    throw edm::Exception( edm::errors::Configuration, "TFile Service is not registered in cfg file" );
  }
  // book the histograms
  analyze_->book(fs);
}

/// everything which has to be done after the event loop 
template <typename Collection, typename Analyze> 
void SingleObjectAnalyzer<Collection, Analyze>::endJob()
{
  // perform whatever post processing is 
  // meant to take place after the filling
  analyze_->process();
}

#endif
