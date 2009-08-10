#ifndef FWLiteSingleObjectAnalyzer_h
#define FWLiteSingleObjectAnalyzer_h

#include <cstdlib>
#include "TopAnalysis/TopAnalyzer/interface/FWLiteLooper.h"

/**
   \class   FWLiteSingleObjectAnalyzer FWLiteSingleObjectAnalyzer.h "TopAnalysis/TopAnalyzer/bin/FWLiteSingleObjectAnalyzer.h"

   \brief   Base class interface to analyze objects of a single type in fwlite

   The following templates have to be expanded:
   Collection  :  input collection   
   Analyze     :  analyzer class for a single object type
*/

template <typename Collection, typename Analyze> 
class FWLiteSingleObjectAnalyzer : public FWLiteLooper {
  
 public:
  /// default contstructor  
  explicit FWLiteSingleObjectAnalyzer(const char* src, const char* wgt, bool useWgt);
  /// default contstructor for reco top type derived classes 
    explicit FWLiteSingleObjectAnalyzer(const char* src, const char* wgt, bool useWgt, const std::string& hypoClass, const bool& matchForStabilityAndPurity);
  /// default contstructor for resolution type derived classes 
  explicit FWLiteSingleObjectAnalyzer(const char* src, const char* wgt, bool useWgt, double matchDR, std::vector<double>& binsPt, std::vector<double>& binsEta, std::vector<double>& binsPhi);
  /// default destructor
  ~FWLiteSingleObjectAnalyzer();

  /// everything which has to be done before the event loop  
  void beginJob(std::string& configFile);
  /// everything which has to be done during the event loop 
  void analyze(fwlite::Event& event);
  /// everything which has to be done after the event loop 
  void endJob(const char* fileName, const char* directoryName);

 private:
  /// input collection
  const char* src_;
  /// event weight
  const char* wgt_;

  /// run with weights or not
  bool useWgt_;
  /// common analyzer class
  Analyze* analyze_; 
};

/// default constructor
template <typename Collection, typename Analyze> 
  FWLiteSingleObjectAnalyzer<Collection, Analyze>::FWLiteSingleObjectAnalyzer(const char* src, const char* wgt, bool useWgt) : 
  src_ ( src ),
  wgt_ ( wgt ),
  useWgt_ ( useWgt )
{
  // construct the common analyzer class
  analyze_ = new Analyze();
}

/// default contstructor for reco top type derived classes 
template <typename Collection, typename Analyze> 
  FWLiteSingleObjectAnalyzer<Collection, Analyze>::FWLiteSingleObjectAnalyzer(const char* src, const char* wgt, bool useWgt, const std::string& hypoClass, const bool& matchForStabilityAndPurity) : 
  src_ ( src ),
  wgt_ ( wgt ),
  useWgt_ ( useWgt )
{
  // construct the common analyzer class
  analyze_ = new Analyze(hypoClass, matchForStabilityAndPurity);
}

/// default contstructor for resolution type derived classes 
template <typename Collection, typename Analyze> 
  FWLiteSingleObjectAnalyzer<Collection, Analyze>::FWLiteSingleObjectAnalyzer(const char* src, const char* wgt, bool useWgt, double matchDR, std::vector<double>& binsPt, std::vector<double>& binsEta, std::vector<double>& binsPhi) : 
  src_ ( src ),
  wgt_ ( wgt ),
  useWgt_ ( useWgt )
{
  // construct the common analyzer class
  analyze_ = new Analyze(matchDR, binsPt, binsEta, binsPhi);
}

/// default destructor
template <typename Collection, typename Analyze> 
FWLiteSingleObjectAnalyzer<Collection, Analyze>::~FWLiteSingleObjectAnalyzer()
{
  // release allocated space
  delete analyze_;
}

/// everything which has to be done during the event loop 
template <typename Collection, typename Analyze> 
void FWLiteSingleObjectAnalyzer<Collection, Analyze>::analyze(fwlite::Event& event)
{
  // fetch the input collection from the event content
  fwlite::Handle<Collection> src;
  src.getByLabel(event, src_);

  // prepare the event weight
  double weight = 1;
  if(useWgt_) {
    fwlite::Handle<double> wgt;
    wgt.getByLabel(event, wgt_);
    weight = *wgt;
  }
  // hand over to the common analyzer function
  analyze_->fill(*src, weight); 
}

/// everything which has to be done before the event loop  
template <typename Collection, typename Analyze> 
void FWLiteSingleObjectAnalyzer<Collection, Analyze>::beginJob(std::string& configFile)
{
  // read necessary parameters from cfg file
  ConfigFile file(configFile, "=", "#");  
  config(file);

  // book histograms
  analyze_->book(); 
}

/// everything which has to be done before the event loop  
template <typename Collection, typename Analyze> 
void FWLiteSingleObjectAnalyzer<Collection, Analyze>::endJob(const char* fileName, const char* directoryName)
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
