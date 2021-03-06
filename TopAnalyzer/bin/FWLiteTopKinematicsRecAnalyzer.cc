#include "TopAnalysis/TopUtils/bin/NiceStyle.cc"
#include "TopAnalysis/TopAnalyzer/interface/TopKinematics.h"
#include "TopAnalysis/TopAnalyzer/bin/FWLiteSingleObjectAnalyzer.h"

typedef FWLiteSingleObjectAnalyzer<const TtSemiLeptonicEvent, TopKinematics> FWLiteTopKinematicsRecAnalyzer;


int main(int argc, char* argv[]) 
{
  if( argc<2 ){
    std::cerr << "ERROR:: " << "Wrong number of arguments! Please specify:" << std::endl;
    return -1;
  }
  std::string cfgFile(argv[1]); 

  // load framework libraries
  gSystem->Load( "libFWCoreFWLite" );
  AutoLibraryLoader::enable();
  
  // set nice style for histograms
  setNiceStyle();

  // define worker class
  std::string hypoKey("kGenMatch");
  std::string lepton("muon") ;
  FWLiteTopKinematicsRecAnalyzer topana("ttSemiLepEvent", "eventWeight", true, hypoKey, lepton, false); 
  // configure
  topana.beginJob(cfgFile);
  // keep this! It's the event loop
  // analyze is called internally
  topana.event();
  // clean up 
  topana.endJob("rootFile", "rootDirectory");

  return 0;
}
