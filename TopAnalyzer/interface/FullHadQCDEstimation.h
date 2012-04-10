#ifndef FullHadQCDEstimation_h
#define FullHadQCDEstimation_h

#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

//#include "DataFormats/PatCandidates/interface/Jet.h"
//#include "TopAnalysis/TopAnalyzer/interface/SingleObject.h"
//#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "TopQuarkAnalysis/TopKinFitter/interface/TtFullHadKinFitter.h"

/**
   \class   FullHadQCDEstimation FullHadQCDEstimation.h "TopAnalysis/TopAnalyzer/interface/FullHadQCDEstimation.h"

   \brief   Derived class to analyze the kinematics of jets on reconstruction and generator level

   The structure keeps histograms for the kinematics of jets only(!). These histograms can be 
   filled from edm::View<pat::Jet>'s or from std::vector<reco::GenParticles>'s. The class is
   derived from the SingleObject<Collection> interface, which makes it usable in fwfull  or 
   fwlite. 
*/

class FullHadQCDEstimation : public edm::EDAnalyzer {
  //class FullHadQCDEstimation : public SingleObject<const edm::View<pat::Jet> > {

 public:
  /// default constructor for fw lite
  //explicit FullHadQCDEstimation();
  /// default constructor for full fw
  explicit FullHadQCDEstimation(const edm::ParameterSet& configFile);
  /// default destructor
  ~FullHadQCDEstimation(){};

  ///**
  //   The following functions have to be implemented for any class
  //   derived from SingleObject<Collection>
  //**/
  ///// histogramm booking for fwlite 
  //void book();
  ///// histogramm booking for fwfull
  //void book(edm::Service<TFileService>& fileService);
  ///// histogram filling for fwlite and for fwfull from reco objects
  //void fill(const edm::View<pat::Jet>& jets, const double& weight=1.);
  ///// everything which needs to be done after the event loop
  //void process() {};

 private:
  /// initiate histograms
  virtual void beginJob();
  /// produce n-tuple
  virtual void analyze(const edm::Event& event, const edm::EventSetup& iSetup);
  /// empty
  virtual void endJob();

  /// book histograms or tree variables
  void bookVariable(edm::Service<TFileService>& fs, const char * variable,
		    unsigned int binsX, float lowX, float upX, unsigned int binsY, float lowY, float upY,
		    bool useTree);
  void bookVariable(edm::Service<TFileService>& fs, const char * variable, unsigned int binsX, float lowX, float upX, bool useTree);
  void bookVariable(edm::Service<TFileService>& fs, const char * variable);
  /// fill values into map for histograms or tree
  void fillValue(std::string variable, double value1, const double& weight);

  /// src's for the different infos
  edm::InputTag JetSrc_, FitSrc_, MultiJetMVADiscSrc_;

  /// produce a TTree as output instead of histograms
  bool useTree_;
  /// b-tagging algo and working point to be emulated
  std::string bTagAlgoWP_;
  /// store resolutions for the kinematic fit
  std::vector<edm::ParameterSet> udscResolutions_;
  std::vector<edm::ParameterSet> bResolutions_;

  /// weight of MC sample
  double MCweight_;

  /// store the resolution scale factors for the kinematic fit
  std::vector<double> jetEnergyResolutionScaleFactors_, jetEnergyResolutionEtaBinning_;

  /// kinematic fit interface
  TtFullHadKinFitter::KinFit* kinFitter;

  /// histogram container
  std::map<std::string, TH1*> hists_;
  std::map<std::string, TH2*> hists2D_;
  std::map<std::string, double> treeVars_;
  TTree * tree;
};

/// book histograms or tree variables
void FullHadQCDEstimation::bookVariable(edm::Service<TFileService>& fs, const char * variable,
					unsigned int binsX, float lowX, float upX, unsigned int binsY, float lowY, float upY,
					bool useTree=false)
{
  if(useTree && !binsY){
    //std::cout << "Adding *" << variable << "* to TTree" << std::endl;
    if(!tree){
      tree = fs->make<TTree>("tree","tree",0);
      treeVars_["weight"];
      tree->Branch("weight", &treeVars_["weight"], (std::string("weight") + "/D").c_str());
    }
    treeVars_[variable];
    tree->Branch(variable, &treeVars_[variable], (std::string(variable) + "/D").c_str());
  }
  else{
    //std::cout << "Adding *" << variable << "* to Histograms" << std::endl;
    if     (!binsY &&  !lowY && !upY )  hists_  [variable] = fs->make<TH1F>( variable, variable, binsX, lowX, upX );
    else if( binsY && ( lowY ||  upY )) hists2D_[variable] = fs->make<TH2F>( variable, variable, binsX, lowX, upX, binsY, lowY, upY );
  }
}

void FullHadQCDEstimation::bookVariable(edm::Service<TFileService>& fs, const char * variable,
					unsigned int binsX, float lowX, float upX, bool useTree=false)
{
  bookVariable( fs, variable, binsX, lowX, upX, 0, 0, 0, useTree);
}

void FullHadQCDEstimation::bookVariable(edm::Service<TFileService>& fs, const char * variable)
{
  bookVariable( fs, variable, 0, 0, 0, 0, 0, 0, true);
}

void FullHadQCDEstimation::fillValue(std::string variable, double value, const double& weight=1.)
{
  if(treeVars_.find(variable) != treeVars_.end()){
    treeVars_.find(variable)->second = value;
    treeVars_.find("weight")->second = weight;
  }
  if(hists_.find(variable) != hists_.end()){
    hists_.find(variable)->second->Fill(value, weight);
  }
}

#endif
