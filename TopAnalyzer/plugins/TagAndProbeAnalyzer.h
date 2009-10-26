#include <memory>

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"


#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include <DataFormats/PatCandidates/interface/Jet.h>
#include <DataFormats/PatCandidates/interface/MET.h>
#include <DataFormats/PatCandidates/interface/Muon.h>
#include <DataFormats/PatCandidates/interface/Electron.h>
#include <DataFormats/PatCandidates/interface/GenericParticle.h>
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include <map> 
#include "TH2.h"
#include "TTree.h"
#include "TString.h"

/**
   \class   TagAndProbeAnalyzer TagAndProbeAnalyzer.h "TopAnalysis/TopAnalyzer/plugins/TagAndProbeAnalyzer.h"

   \brief   Plugin to fill histograms for the determination of tag and probe efficiencies

   Add some more detailed documentation here...
*/

class TagAndProbeAnalyzer : public edm::EDAnalyzer {
 public:
  explicit TagAndProbeAnalyzer(const edm::ParameterSet&);
  ~TagAndProbeAnalyzer();
  
  
 private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  // int GetHistoBin(const edm::Event&, const pat::Muon&);
  double GetVariable(const edm::Event&, double eta,double phi,double pt,std::string);
  //  int GetHistoBin(const edm::Event&, double eta,double phi,double pt,int,std::string,double,double);
  // int GetHistoBin2D(const edm::Event&, double, double, double);
  struct EffCalculator_ {
    EffCalculator_(): total(0), passed(0), failed(0),eff(0) {} 
    unsigned int getTotal(){ return total; };
    unsigned int getPassed(){ return passed; };
    unsigned int getFailed(){ return failed; };
    double getEff(){ if (total!=0 )return double(passed)*100/total;else return 0; };
    /*
      double getErr(){ //Poisson Errors
      
      if (total!=0 )
      {
      return 100 * sqrt(passed * passed (total + passed)/(total * total * total)) ; 
      }
      else return 1; 
      };
    */
    
    double getErr(){   //Binominal Errors
      if (total!=0 )
	{
	  std::cout<< 100 *(1./total) * sqrt(double(passed)*(1. - double(passed)/total))<<std::endl ; 
	  return 100 *(1./total) * sqrt(double(passed)*(1. - double(passed)/total)) ; 
	}
      else return 1; 
    };
    
    unsigned int total;
    unsigned int passed;
    unsigned int failed;
    double eff;
    
  };
  
  // ----------member data ---------------------------
  edm::InputTag muonTag_;
  edm::InputTag elecTag_;
  edm::InputTag muonMCTag_;
  edm::InputTag jetTag_;
  edm::InputTag metTag_;
  edm::InputTag genTag_;
  edm::InputTag trackTag_;
  int numberOfBins_;
  std::string variable_;
  bool equiBins_;
  double minValue_;
  double maxValue_;
  int numberOfBins_2_;
  std::string variable_2_;
  bool equiBins_2_;
  double minValue_2_;
  double maxValue_2_;
  double matchingRadius_;
  double staTrackMatchingRadius_;
  bool getIsolationEff_;
  bool getElectronIsolationEff_;
  bool getGlobalPromtTightEff_;
  bool getGlobalEff_;
  bool getStandaloneEff_;
  std::map<int,TagAndProbeAnalyzer::EffCalculator_> binnedEff_;
  std::map<int,TagAndProbeAnalyzer::EffCalculator_> binnedMCEff_;
  std::map<int,TagAndProbeAnalyzer::EffCalculator_> binnedEff2D_;
  std::map<int,TagAndProbeAnalyzer::EffCalculator_> binnedMCEff2D_;
  TH1F *hEff;
  TH1F *hMCEff;
  TH2F *hEff2D;
  TH2F *hMCEff2D;
};

