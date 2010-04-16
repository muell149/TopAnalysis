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
#include "CommonTools/UtilAlgos/interface/TFileService.h"

/**
   \class   DoubleObjectAnalyzer DoubleObjectAnalyzer.h "TopAnalysis/TopAnalyzer/plugins/DoubleObjectAnalyzer.h"

   \brief   Template plugin to be used for the analysis of two object types within the full framework

   The class is a template to be used for the analysis of objects of two object types, 
   like muons & jets or others. The class expects the following arguments:

      - CollectionA  :  input collection or class A
      - CollectionB  :  input collection or class B
      - Analyze     :  analyzer class for a single object type

   The Analyze class is expected to contain all analysis implementation to be applied 
   on the Collections (or classes). The class Analyze is expected to be of the type 
   DoubleObject<CollectionA, CollectionB>, where CollectionA and CollectionB are the 
   same Collections (or classes) as for this class. It calls the  Analyze::book method 
   using the TFileService at the beginning of cmsRun the Analyze::analyze method 
   during the event loop and the Analyze::process method from Analyze at the end of 
   the job. 

   It provides a fixed interface for the following tasks:

      - receive the input collectionA/classA from the event content (parameter: 'srcA')
      - receive the input collectionB/classB from the event content (parameter: 'srcB')
      - receive a potential event weight (parameter: 'weight')
      - a flag to determine whether this event weight should be used or not (parameter:
        'useWeight')

   requiring the correspongin parameters in the initializing configuration file (cfi). 
   Additinal parameters required by the class Analyze may be added using an arbitary 
   edm::ParameterSet 'analyze'.
*/

template <typename CollectionA, typename CollectionB, typename Analyze> 
class DoubleObjectAnalyzer : public edm::EDAnalyzer {

 public:
  /// default contstructor
  explicit DoubleObjectAnalyzer(const edm::ParameterSet& configFile);
  /// default destructor
  ~DoubleObjectAnalyzer();
  
 private:
  /// everything which has to be done before the event loop  
  virtual void beginJob();
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
  srcA_( cfg.getParameter<edm::InputTag>( "srcA"  ) )
{
  // srcB is an optional parameter; if not present in the module
  // definition an analyze function for srcA only will be called 
  if(cfg.exists("srcB" )) srcB_= cfg.getParameter<edm::InputTag>("srcB" );
  // weight is an optional parameter; if not present in the module
  // the used weight will be 1.
  if(cfg.exists("weight" )) wgt_= cfg.getParameter<edm::InputTag>("weight" );
  // construct the common analyzer class with corresponding 
  // parameter sets as input 
  cfg.exists("analyze") ? analyze_ = new Analyze( cfg.getParameter<edm::ParameterSet>("analyze") ) : analyze_ = new Analyze( edm::ParameterSet() );
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
  if(!srcB_.label().empty()) event.getByLabel(srcB_, srcB);

  // prepare the event weight
  double weight = 1;
  if(!wgt_.label().empty()) {
    edm::Handle<double> wgt;
    event.getByLabel(wgt_, wgt);
    weight = *wgt;
  }
  // hand over to the common analyzer function
  (!srcB_.label().empty()) ? analyze_->fill(*srcA, weight) : analyze_->fill(*srcA, *srcB, weight);
}

/// everything which has to be done before the event loop  
template <typename CollectionA, typename CollectionB, typename Analyze> 
void DoubleObjectAnalyzer<CollectionA, CollectionB, Analyze>::beginJob()
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
