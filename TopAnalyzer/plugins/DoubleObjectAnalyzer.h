#ifndef DoubleObjectAnalyzer_h
#define DoubleObjectAnalyzer_h

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
// template pluging to be used for the analysis of relations of 
// two different object types like with the full framework:
//
// CollectionA :  input collection for object type A
// CollectionB :  input collection for object type B
// Analyze     :  analyzer class for two object types A & B
//

template <typename CollectionA, typename CollectionB, typename Analyze> 
class DoubleObjectAnalyzer : public edm::EDAnalyzer {

 public:
  /// default contstructor
  explicit DoubleObjectAnalyzer(const edm::ParameterSet& configFile);
  /// default destructor
  ~DoubleObjectAnalyzer();
  

 private:
  /// everything which has to be done before the event loop  
  virtual void beginJob(const edm::EventSetup& setup) ;
  /// everything which has to be done during the event loop 
  virtual void analyze(const edm::Event& event, const edm::EventSetup& setup);
  /// everything which has to be done after the event loop 
  virtual void endJob();
  

 private:
  /// input collection for object type A
  edm::InputTag srcA_;
  /// input collection for object type B
  edm::InputTag srcB_;
  /// event weight
  edm::InputTag wgt_;

  /// run with weights or not
  bool useWgt_;
  /// common analzyer class
  Analyze* analyze_;
};

/// default constructor
template <typename CollectionA, typename CollectionB, typename Analyze> 
DoubleObjectAnalyzer<CollectionA, CollectionB, Analyze>::DoubleObjectAnalyzer(const edm::ParameterSet& cfg) :
  srcA_( cfg.getParameter<edm::InputTag>( "inputA"  ) ),
  srcB_( cfg.getParameter<edm::InputTag>( "inputB"  ) ),
  wgt_( cfg.getParameter<edm::InputTag>( "weight" ) ),
  useWgt_( cfg.getParameter<bool>( "useWeight" ) )
{
  // construct the common analyzer class with
  // corresponding parameter sets as input 
  analyze_ = new Analyze( cfg.getParameter<edm::ParameterSet>("analyze") );
}

/// default destructor
template <typename CollectionA, typename CollectionB, typename Analyze> 
DoubleObjectAnalyzer<CollectionA, CollectionB, Analyze>::~DoubleObjectAnalyzer()
{
  // release the allocated space
  delete analyze_;
}

/// everything which has to be done during the event loop 
template <typename CollectionA, typename CollectionB, typename Analyze> 
void DoubleObjectAnalyzer<CollectionA, CollectionB, Analyze>::analyze(const edm::Event& event, const edm::EventSetup& setup)
{
  // fetch the input collection for object 
  // type A from the event content
  edm::Handle<CollectionA> srcA; 
  event.getByLabel(srcA_, srcA);

  // fetch the input collection for object 
  // type B from the event content
  edm::Handle<CollectionB> srcB; 
  event.getByLabel(srcB_, srcB);

  // prepare the event weight
  double weight = 1;
  if(useWgt_) {
    edm::Handle<double> wgt;
    event.getByLabel(wgt_, wgt);
    weight = *wgt;
  }
  // hand over to the common analyzer function
  analyze_->fill(*srcA, *srcB, weight);
}

/// everything which has to be done before the event loop  
template <typename CollectionA, typename CollectionB, typename Analyze> 
void DoubleObjectAnalyzer<CollectionA, CollectionB, Analyze>::beginJob(const edm::EventSetup& setup)
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
template <typename CollectionA, typename CollectionB, typename Analyze> 
void DoubleObjectAnalyzer<CollectionA, CollectionB, Analyze>::endJob()
{
  // perform whatever post processing is 
  // meant to take place after the filling
  analyze_->process();
}

#endif
