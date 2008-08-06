#include <cstdlib>

#include "DataFormats/FWLite/interface/Handle.h"
#include "FWCore/FWLite/interface/AutoLibraryLoader.h"

#include "TopAnalysis/TopAnalyzer/interface/FWAnalyzer.h"
#include "TopAnalysis/TopAnalyzer/interface/MuonId.h"
#include "TopAnalysis/TopAnalyzer/interface/MuonKinematic.h"
#include "TopAnalysis/TopAnalyzer/interface/MuonResolution.h"

using namespace std;


class FWMuonAnalyzer : public FWAnalyzer{
  
 public:
  
  explicit FWMuonAnalyzer();
  virtual ~FWMuonAnalyzer();
  virtual void readConfig(std::string& name){
    ConfigFile cfg( name, "=", "$" );  
    configBlockIO  ( cfg );
    configBlockHist( cfg );
  };

  void config (){
    if(doMuid_ ){ muid_ ->book(); }
    if(doMures_){ mukin_->book(); }
    if(doMures_){
      mures_->setMatchDR(matchDR_);
      mures_->setBinsPt (binsPt_ );  
      mures_->book();
    }
  };
  void fill(const std::vector<pat::Jet>& jets, 
	    const std::vector<pat::Muon>& muons, const double& weight) 
  { if(doMuid_ ) muid_ ->fill(       muons, weight); 
    if(doMukin_) mukin_->fill( jets, muons, weight); 
    if(doMures_) mures_->fill(       muons, weight); 
  };
  void norm() 
  { if(doMuid_ ) muid_ ->norm(); 
    if(doMukin_) mukin_->norm(); 
    if(doMures_) mures_->norm(); 
  };
  void write() 
  {
    TFile file( outputFile_.c_str(), "recreate" );
    file.mkdir( outputDirectory_.c_str() );
    if(doMuid_ ) muid_ ->write( file, outputDirectory_.c_str() ); 
    if(doMukin_) mukin_->write( file, outputDirectory_.c_str() ); 
    if(doMures_) mures_->write( file, outputDirectory_.c_str() ); 
    file.Close();
  };
  
 protected:

  virtual void analyze(fwlite::Event&);
  void configBlockHist(ConfigFile&);

 private:
  
  bool doMuid_;
  bool doMukin_;
  bool doMures_;
  double matchDR_;
  std::vector<double> binsPt_;

  MuonId* muid_; 
  MuonKinematic* mukin_; 
  MuonResolution* mures_; 
};


FWMuonAnalyzer::FWMuonAnalyzer()
{
  if(doMuid_ ) muid_ = new MuonId();
  if(doMukin_) mukin_= new MuonKinematic();
  if(doMures_) mures_= new MuonResolution();
}

FWMuonAnalyzer::~FWMuonAnalyzer()
{
  if(doMuid_ ) {delete muid_ ; muid_ =0;};
  if(doMukin_) {delete mukin_; mukin_=0;};
  if(doMures_) {delete mures_; mures_=0;};
}

void FWMuonAnalyzer::configBlockHist(ConfigFile& cfg)
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
    doMuid_ = cfg.read<bool>( "doMuid"  );
    doMukin_= cfg.read<bool>( "doMukin" );
    doMures_= cfg.read<bool>( "doMures" );
    matchDR_= cfg.read<double>( "matchDR" );
    readVector( cfg.read<std::string>( "binsPt" ), binsPt_ ); 
  }
  catch(...) {
    std::cerr << "ERROR during reading of config file" << std::endl;
    std::cerr << "      misspelled variables in cfg ?" << std::endl;
    std::cerr << "      [--called in configBlockHist--]" << std::endl;
    std::exit(1);
  }
}

void FWMuonAnalyzer::analyze(fwlite::Event& event)
{
  //fwlite::Handle<double> weight;
  //weight.getByLabel(event, "csa07:weight");
  
  fwlite::Handle<std::vector<pat::Jet> > jets;
  jets.getByLabel(event, "selectedLayer1Jets");
  
  fwlite::Handle<std::vector<pat::Muon> > muons;
  muons.getByLabel(event, "selectedLayer1Muons");
  
  fill( *(jets.ptr()), *(muons.ptr()), 1.);
  //fill( *(jets.ptr()), *(muons.ptr()), *(weight.ptr()));
}

int main(int argc, char* argv[]) 
{
  if( argc<2 ){
    // ------------------------------------------------- 
    std::cerr << "ERROR:: " 
	      << "Wrong number of arguments! Please specify:" << std::endl
	      << "        * configfile" << std::endl;
    // -------------------------------------------------  
    return -1;
  }
  std::string cfgFile(argv[1]); 

  // load framework libraries
  gSystem->Load( "libFWCoreFWLite" );
  AutoLibraryLoader::enable();
  
  // set nice style for histograms
  setNiceStyle();

  // define worker class
  FWMuonAnalyzer muana; 
  muana.readConfig(cfgFile);
  muana.config();
  muana.loop ();
  muana.norm ();
  muana.write();
  return 0;
}
