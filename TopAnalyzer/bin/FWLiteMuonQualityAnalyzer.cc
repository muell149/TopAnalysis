#include "TopAnalysis/TopUtils/bin/NiceStyle.cc"
#include "TopAnalysis/TopAnalyzer/interface/MuonQuality.h"
#include "TopAnalysis/TopAnalyzer/bin/FWLiteSingleObjectAnalyzer.h"

typedef FWLiteSingleObjectAnalyzer<std::vector<pat::Muon>, MuonQuality> FWLiteMuonQualityAnalyzer;


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
  FWLiteMuonQualityAnalyzer muana("selectedLayer1Muons", "eventWeight", true); 
  // configure
  muana.beginJob(cfgFile);
  // keep this! It's the event loop
  // analyze is called internally
  muana.event();
  // clean up 
  muana.endJob("rootFile", "rootDirectory");

  return 0;
}
