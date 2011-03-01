#ifndef FWLiteLooper_h
#define FWLiteLooper_h

#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

#include "DataFormats/FWLite/interface/Event.h"
#include "DataFormats/FWLite/interface/Handle.h"
#include "FWCore/FWLite/interface/AutoLibraryLoader.h"

#include "TopAnalysis/TopUtils/interface/ConfigFile.h"
#include "TopAnalysis/TopUtils/interface/RootSystem.h"
#include "TopAnalysis/TopUtils/interface/RootHistograms.h"
#include "TopAnalysis/TopUtils/interface/RootPostScript.h"

//
//
//
//
//

class FWLiteLooper{

 public:
  /// default constructor
  FWLiteLooper(){};
  /// default destructor
  virtual ~FWLiteLooper(){};

  /// event loop
  virtual void event();
  /// everything which has to be done before the event loop  
  virtual void beginJob(std::string& config) = 0;
  /// everything which has to be done during the event loop 
  virtual void analyze(fwlite::Event& event) = 0;
  /// everything which has to be done after the event loop 
  virtual void endJob(const char* fileName, const char* directoryName) = 0;


 protected:
  /// read io block from cfg file
  void config(ConfigFile& configFile);
  /// return input files
  std::vector<std::string> inputFiles() { return inputFiles_; };
  /// break event loop after max events
  bool stop(int evt) { return (maxEvt_>0 ? evt>maxEvt_ : false); };


 protected:
  /// maximal number of event tro loop over
  int maxEvt_;
  /// name of the output file
  std::string outputFile_;
  /// name of the output directory
  std::string outputDirectory_;
  /// vector of input file names
  std::vector<std::string> inputFiles_;
};

#endif
