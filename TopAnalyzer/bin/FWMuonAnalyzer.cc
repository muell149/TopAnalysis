#include <memory>
#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <iostream>

#include "DataFormats/FWLite/interface/Handle.h"
#include "FWCore/FWLite/interface/AutoLibraryLoader.h"

#include "TopAnalysis/TopUtils/bin/NiceStyle.cc"
#include "TopAnalysis/TopUtils/interface/RootSystem.h"
#include "TopAnalysis/TopUtils/interface/RootHistograms.h"
#include "TopAnalysis/TopUtils/interface/RootPostScript.h"
#include "TopAnalysis/TopAnalyzer/interface/MuonKinematic.h"

int main(int argc, char* argv[]) 
{
  if( argc<3 ){
    // ------------------------------------------------- 
    std::cerr << "ERROR:: " 
	      << "Wrong number of arguments! Please specify:" << std::endl
	      << "        * filepath" << std::endl
	      << "        * process name" << std::endl; 
    // -------------------------------------------------  
    return -1;
  }
  
  // load framework libraries
  gSystem->Load( "libFWCoreFWLite" );
  AutoLibraryLoader::enable();
  
  // set nice style for histograms
  setNiceStyle();

  // define some histograms 
  MuonKinematic mukin(0.3);  
  mukin.book();

  // -------------------------------------------------  
  std::cout << "open  file: " << argv[1] << std::endl;
  // -------------------------------------------------
  TFile* inFile = TFile::Open(argv[1]);
  
  int ievt=0;
  fwlite::Event event(inFile);
  for(event.toBegin(); !event.atEnd(); ++event, ++ievt) {
    fwlite::Handle<std::vector<pat::Muon> > muons;
    muons.getByLabel(event, "selectedLayer1Muons");

    fwlite::Handle<std::vector<pat::Jet> > jets;
    jets.getByLabel(event, "selectedLayer1Jets");

    fwlite::Handle<reco::TrackCollection> tracks;
    tracks.getByLabel(event, "ctfWithMaterialTracks");    

    fwlite::Handle<reco::CandidateCollection> towers;
    towers.getByLabel(event, "caloTowers");
    
    // -------------------------------------------------  
    if(ievt>0 && ievt%100==0) std::cout << "  processing event: " << ievt << std::endl;
    // -------------------------------------------------  
    
    mukin.fill( *(jets.ptr()), *(tracks.ptr()), *(towers.ptr()), *(muons.ptr()), 1.);
  }
  // -------------------------------------------------  
  std::cout << "close file" << std::endl;
  // -------------------------------------------------
  inFile->Close();
  
  mukin.norm();
  mukin.write("analyzeMuons.root", "analyzeMuon");
  return 0;
}
