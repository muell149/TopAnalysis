#ifndef FWLiteDoubleObjectAnalyzer_h
#define FWLiteDoubleObjectAnalyzer_h

#include <cstdlib>
#include "TopAnalysis/TopAnalyzer/interface/FWLiteLooper.h"

/**
   \class   FWLiteDoubleObjectAnalyzer FWLiteDoubleObjectAnalyzer.h "TopAnalysis/TopAnalyzer/bin/FWLiteDoubleObjectAnalyzer.h"

   \brief   Base class interface to analyze the relation of two different objects in fwlite

   The following templates have to be expanded:
   CollectionA :  input collection for object type A
   CollectionB :  input collection for object type B
   Analyze     :  analyzer class for two object types A & B
*/

template <typename CollectionA, typename CollectionB, typename Analyze> 
class FWLiteDoubleObjectAnalyzer : public FWLiteLooper {
  
 public:
  /// default contstructor  
  explicit FWLiteDoubleObjectAnalyzer(const char* srcA, const char* srcB, const char* wgt, bool useWgt);
  /// default destructor
  ~FWLiteDoubleObjectAnalyzer();

  /// everything which has to be done before the event loop  
  void beginJob(std::string& configFile);
  /// everything which has to be done during the event loop 
  void analyze(fwlite::Event& event);
  /// everything which has to be done after the event loop 
  void endJob(const char* fileName, const char* directoryName);

 private:
  /// input collection for object type A
  const char* srcA_;
  /// input collection for object type B
  const char* srcB_;
  /// event weight
  const char* wgt_;

  /// run with weights or not
  bool useWgt_;
  /// common analyzer class
  Analyze* analyze_; 
};

/// default constructor
template <typename CollectionA, typename CollectionB, typename Analyze> 
  FWLiteDoubleObjectAnalyzer<CollectionA, CollectionB, Analyze>::FWLiteDoubleObjectAnalyzer(const char* srcA, const char* srcB, const char* wgt, bool useWgt) : 
  srcA_ ( srcA ),
  srcB_ ( srcB ),
  wgt_  ( wgt  ),
  useWgt_( useWgt )
{
  // construct the common analyzer class
  analyze_ = new Analyze();
}

/// default destructor
template <typename CollectionA, typename CollectionB, typename Analyze> 
FWLiteDoubleObjectAnalyzer<CollectionA, CollectionB, Analyze>::~FWLiteDoubleObjectAnalyzer()
{
  // release the allocated space
  delete analyze_;
}

/// everything which has to be done during the event loop 
template <typename CollectionA, typename CollectionB, typename Analyze> 
void FWLiteDoubleObjectAnalyzer<CollectionA, CollectionB, Analyze>::analyze(fwlite::Event& event)
{
  // fetch the input collection for object 
  // type A from the event content
  fwlite::Handle<CollectionA> srcA;
  srcA.getByLabel(event, srcA_);

  // fetch the input collection for object 
  // type B from the event content
  fwlite::Handle<CollectionB> srcB;
  srcB.getByLabel(event, srcB_);

  // fetch the input collection from the 
  // event content
  double weight = 1;
  if(useWgt_) {
    fwlite::Handle<double> wgt;
    wgt.getByLabel(event, wgt_);
    weight = *wgt;
  }
  // hand over to the common analyzer function
  analyze_->fill(*srcA, *srcB, weight); 
}

/// everything which has to be done before the event loop  
template <typename CollectionA, typename CollectionB, typename Analyze> 
void FWLiteDoubleObjectAnalyzer<CollectionA, CollectionB, Analyze>::beginJob(std::string& configFile)
{
  // read necessary parameters from cfg file
  ConfigFile file(configFile, "=", "#");  
  config(file);
  // book histograms
  analyze_->book(); 
}

/// everything which has to be done before the event loop  
template <typename CollectionA, typename CollectionB, typename Analyze> 
void FWLiteDoubleObjectAnalyzer<CollectionA, CollectionB, Analyze>::endJob(const char* fileName, const char* directoryName)
{
  // perform whatever post processing is 
  // meant to take place after the filling
  analyze_->process(); 
  
  // write output to file
  TFile file( fileName, "recreate" );
  file.mkdir( directoryName );
  analyze_->write( file, directoryName ); 
  file.Close();
}

#endif
