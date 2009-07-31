#include "TopAnalysis/TopAnalyzer/interface/FWLiteLooper.h"

/// event loop
void FWLiteLooper::event()
{
  unsigned iEvt=0;  
  // loop the vector of input files
  for(unsigned int iFile=0; iFile<inputFiles_.size(); ++iFile){
    // open the file (dcach save)
    TFile* inFile = TFile::Open( inputFiles_[iFile].c_str() );
    if( inFile ){
      fwlite::Event event(inFile);
      // loop the event in the file
      for(event.toBegin(); !event.atEnd(); ++event, ++iEvt){
	// break loop if maximal number 
	// of events is reached 
	if( stop(iEvt) ) break;
	
	// simple event counter
	if(iEvt>0 && iEvt%100==0) 
	  std::cout << "  processing event: " << iEvt << std::endl;
	
	// analyze
	analyze(event);
      }
      // close the input file
      inFile->Close();
    }
    // break loop if maximal number of events is reached:
    // this has to be done twice stop the file loop as well
    if( stop(iEvt) ) break;
  }
}

void FWLiteLooper::config(ConfigFile& cfg)
{
  // read configurables defined in FWLiteLooper from config file
  // & throw a human readable exception when misspellings occure
  try {
    // input/output files
    readVector( cfg.read<std::string>( "inputFiles" ), inputFiles_ );
    maxEvt_ =  cfg.read<int>( "maxEvt" );
    outputFile_= cfg.read<std::string>( "outputFile" );
    outputDirectory_= cfg.read<std::string>( "outputDirectory" );
  }
  catch(...) {
    std::cerr << "ERROR during reading of config file" << std::endl;
    std::cerr << "      misspelled variables in cfg ?" << std::endl;
    std::cerr << "      [--called in configBlockIO--]" << std::endl;
    std::exit(1);
  }
}
