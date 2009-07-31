#include "TopAnalysis/TopUtils/bin/NiceStyle.cc"
#include "TopAnalysis/TopAnalyzer/interface/MuonResolution.h"
#include "TopAnalysis/TopAnalyzer/bin/FWLiteSingleObjectAnalyzer.h"

typedef FWLiteSingleObjectAnalyzer<std::vector<pat::Muon>, MuonResolution> FWLiteMuonResolutionAnalyzer;


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

  // set input parameters for Resolution class
  double matchDR = 0.3;
  std::vector<double> binsPt (0);
  std::vector<double> binsEta(0);
  std::vector<double> binsPhi(0);

  // define worker class
  FWLiteMuonResolutionAnalyzer muana("selectedLayer1Muons", "eventWeight", true, matchDR, binsPt, binsEta, binsPhi); 
  // configure
  muana.beginJob(cfgFile);
  // keep this! It's the event loop
  // analyze is called internally
  muana.event();
  // clean up 
  muana.endJob("rootFile", "rootDirectory");

  return 0;
}
