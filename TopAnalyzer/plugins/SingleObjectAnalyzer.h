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
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/Utilities/interface/EDMException.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

/**
   \class   SingleObjectAnalyzer SingleObjectAnalyzer.h "TopAnalysis/TopAnalyzer/plugins/SingleObjectAnalyzer.h"

   \brief   Template plugin to be used for the analysis of single objects within the full framework

   The class is a template to be used for the analysis of objects of a single object 
   type, like electrons, muons, jets but also for reconstructed ttbar pairs (TtEvent 
   like classes) or ttbar pairs on generator level (TopGenEvent like classes). The 
   class expects the following arguments:

      - Collection  :  input collection or class 
      - Analyze     :  analyzer class for a single object type

   The Analyze class is expected to contain all analysis implementation to be applied 
   on the Collection (or class). The class Analyze is expected to be of the type 
   SingleObject<Collection>, where Collection is the same Collection (or class) as for 
   this class. It calls the  Analyze::book method using the TFileService at the 
   beginning of cmsRun the Analyze::analyze method during the event loop and the 
   Analyze::process method from Analyze at the end of the job. 

   It provides a fixed interface for the following tasks:

      - receive the input collection/class from the event content (parameter: 'src')
      - receive a potential event weight (parameter: 'weight')
      - a flag to determine whether this event weight should be used or not (parameter:
        'useWeight')

   requiring the correspongin parameters in the initializing configuration file (cfi).
   Additinal parameters required by the class Analyze may be added using an arbitary 
   edm::ParameterSet 'analyze'.
*/

template <typename Collection, typename Analyze> 
class SingleObjectAnalyzer : public edm::EDAnalyzer {

 public:
  /// default contstructor
  explicit SingleObjectAnalyzer(const edm::ParameterSet& configFile);
  /// default destructor
  ~SingleObjectAnalyzer();
  
 private:
  /// everything which has to be done before the event loop  
  virtual void beginJob() ;
  /// everything which has to be done during the event loop 
  virtual void analyze(const edm::Event& event, const edm::EventSetup& setup);
  /// everything which has to be done after the event loop 
  virtual void endJob();
  
 private:
  /// input collection
  edm::InputTag src_;
  /// event weight
  edm::InputTag wgt_;

  /// common analzyer class
  Analyze* analyze_;
};

/// default constructor
template <typename Collection, typename Analyze> 
SingleObjectAnalyzer<Collection, Analyze>::SingleObjectAnalyzer(const edm::ParameterSet& cfg) :
  src_( cfg.getParameter<edm::InputTag>( "src"  ) )
{
  // weight is an optional parameter; if not present 
  // in the module the used weight will be 1.
  if(cfg.exists("weight" )) wgt_= cfg.getParameter<edm::InputTag>("weight" );
  // construct the common analyzer class with
  // corresponding parameter sets as input 
  cfg.exists("analyze") ? analyze_ = new Analyze( cfg.getParameter<edm::ParameterSet>("analyze") ) : analyze_ = new Analyze( edm::ParameterSet() );
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
  if(!wgt_.label().empty()) {
    edm::Handle<double> wgt;
    event.getByLabel(wgt_, wgt);
    weight = *wgt;
  }
  edm::EventAuxiliary aux = event.eventAuxiliary();
  double runNumber             = aux.run();
  double luminosityBlockNumber = aux.luminosityBlock();
  double eventNumber           = aux.event();
  // hand over to the common analyzer function
  analyze_->fill2(*src, runNumber, luminosityBlockNumber, eventNumber, weight);
}

/// everything which has to be done before the event loop  
template <typename Collection, typename Analyze> 
void SingleObjectAnalyzer<Collection, Analyze>::beginJob()
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
