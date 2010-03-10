#include "TopAnalysis/TopUtils/bin/NiceStyle.cc"
#include "TopAnalysis/TopAnalyzer/interface/MuonJetKinematics.h"
#include "TopAnalysis/TopAnalyzer/bin/FWLiteDoubleObjectAnalyzer.h"

typedef FWLiteDoubleObjectAnalyzer<edm::View<pat::Muon>, edm::View<pat::Jet>, MuonJetKinematics> FWLiteMuonJetKinematicsAnalyzer;


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
  FWLiteMuonJetKinematicsAnalyzer muana("selectedPatMuons", "selectedPatJets", "eventWeight", true); 
  // configure
  muana.beginJob(cfgFile);
  // keep this! It's the event loop
  // analyze is called internally
  muana.event();
  // clean up 
  muana.endJob("rootFile", "rootDirectory");

  return 0;
}
