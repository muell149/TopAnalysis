#include "DataFormats/FWLite/interface/Handle.h"
#include "FWCore/FWLite/interface/AutoLibraryLoader.h"
#include "TopAnalysis/TopAnalyzer/interface/FWAnalyzer.h"


void FWAnalyzer::configBlockIO(ConfigFile& cfg)
{
  //-----------------------------------------------
  // read configurables defined in FWAnalyzer from 
  // config file. Throw human readable exception 
  // when misspellings occure
  //-----------------------------------------------
  try {
    //-----------------------------------------------
    // input/output files
    //-----------------------------------------------
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

void FWAnalyzer::loop()
{
  // commented as not capable of reading from dcach
  //std::vector<std::string> buffer = muana.inputFiles();
  //fwlite::ChainEvent event(const_cast<std::vector<std::string>&>(buffer));
  
  unsigned ievt=0;  
  for(unsigned int i=0; i<inputFiles().size(); ++i){
    std::cout << "open  file: " << inputFiles()[i].c_str() << std::endl;
    TFile* inFile = TFile::Open( inputFiles()[i].c_str() );
    fwlite::Event event(inFile);
    for(event.toBegin(); !event.atEnd(); ++event, ++ievt) {
      if( breakLoop(ievt) ) break;
      
      if(ievt>0 && ievt%100==0) 
	std::cout << "  processing event: " << ievt << std::endl;
      analyze(event);
    }
    std::cout << "close file: " <<  inputFiles()[i].c_str() << std::endl;
    inFile->Close();
    if( breakLoop(ievt) ) break;
  }
}
