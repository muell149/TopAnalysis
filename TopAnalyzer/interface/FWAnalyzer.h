#ifndef FWAnalyzer_h
#define FWAnalyzer_h

#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

#include "TopAnalysis/TopUtils/bin/NiceStyle.cc"
#include "TopAnalysis/TopUtils/interface/ConfigFile.h"
#include "TopAnalysis/TopUtils/interface/RootSystem.h"
#include "TopAnalysis/TopUtils/interface/RootHistograms.h"
#include "TopAnalysis/TopUtils/interface/RootPostScript.h"


template <class T> 
void readVector(std::string s, std::vector<T>& vec)
{
  std::stringstream stream( s );
  T buffer;
  while (!stream.eof()) {
    stream >> buffer;
    if(!stream.str().empty()){
      vec.push_back( buffer );
    }
  }
}

class FWAnalyzer{

 public:

  FWAnalyzer(){};
  virtual ~FWAnalyzer(){};
  virtual void readConfig(std::string&)=0;

  virtual void loop();
  std::vector<std::string> inputFiles() { return inputFiles_; };
  bool breakLoop(int evt) { return (maxEvt_>0 ? evt>maxEvt_ : false); };

 protected:

  virtual void analyze(fwlite::Event&)=0;
  void configBlockIO(ConfigFile&);

 protected:

  int maxEvt_;

  std::vector<std::string> inputFiles_;
  std::string outputFile_;
  std::string outputDirectory_;
};

#endif
