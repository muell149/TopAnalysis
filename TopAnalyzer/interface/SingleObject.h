#ifndef SingleObject_h
#define SingleObject_h

#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TFile.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

/**
   \class   SingleObject SingleObject.h "TopAnalysis/TopAnalyzer/interface/SingleObject.h"

   \brief   Interface class to analyze single objects within full framework of fwlite

   Ths class is an interface to a common analyer or a corresponding fwlite mimic
   in TopAnalysis/TopAnalzyer/bin. It takes a single object class as argument. 
   An interface to a common book, fill & process function is expected by the common 
   analyzer (mimic) class. Each derived class has to provide these functions. It 
   provides containers for one and 2-dimensional histogram management and corres-
   ponding fill functions. The fill functions are of type:

   fill("name", valueA, weight)         (to fill 1-dimensional histograms)
   fill("name", valueA, valueB, weight) (to fill 2-dimensional histograms)

   where _name_ is expectec to be to be the name of the histogram under which it
   has been booked for module internal histogram management (i.e. the std::string
   in the map container), _valueA_ and _valueB_ are the values of the quantities 
   to be filled (e.g. muon->pt()) and weight is the weight with which the histo-
   grams is to be filled.
*/

template <typename Collection> 
class SingleObject{

 public:
  /// default constructor for fwlite
  explicit SingleObject(){};
  /// default constructor for fwfull
  explicit SingleObject(const edm::ParameterSet& configFile){};
  /// default destructor
  virtual ~SingleObject(){};
  /// write histograms to file for fwlite
  void write(TFile& file, const char* directory);
  /// book histograms or tree variables
  void bookVariable(edm::Service<TFileService>& fs, const char * variable,
		    unsigned int binsX, float lowX, float upX, unsigned int binsY, float lowY, float upY,
		    bool useTree);
  void bookVariable(edm::Service<TFileService>& fs, const char * variable, unsigned int binsX, float lowX, float upX, bool useTree);
  /// fill values into map for histograms or tree
  void fillValue(std::string variable, float value1, float value2, const double& weight);
  void fillValue(std::string variable, float value1, const double& weight);

  /**
     The following functions have to be implemented for any class
     derived from SingleObject<Collection>
  **/
  /// histogramm booking for fwlite 
  virtual void book() = 0;
  /// histogramm booking for fwfull
  virtual void book(edm::Service<TFileService>& fileService) = 0;
  /// histogram filling for fwlite and for fwfull
  virtual void fill(const Collection& inputCollection, const double& weight=1.) = 0;
  /// everything which needs to be done after the event loop
  virtual void process() = 0;

 protected:
  /// check if histogram was booked in the corresponding map
  bool booked(std::map<std::string, TH1*> map, const std::string histName) const { return map.find(histName.c_str())!=map.end(); };
  /// fill 1-dimensional histogram if it had been booked before
  void fill(const std::string histName, double valueA, double weight) const { if(booked(hists_, histName)) hists_.find(histName)->second->Fill(valueA, weight); };
  /// fill 2-dimensional histogram if it had been booked before
  void fill(const std::string histName, double valueA, double valueB, double weight) const { if(booked(hists2D_, histName)) hists2D_.find(histName)->second->Fill(valueA, valueB, weight); };

 protected:
  /// histogram container
  std::map<std::string, TH1*> hists_;
  std::map<std::string, TH2*> hists2D_;
  std::map<std::string, float> treeVars_;
  TTree * tree;
};

/// book histograms or tree variables
template <typename Collection>
  void SingleObject<Collection>::bookVariable(edm::Service<TFileService>& fs, const char * variable,
					      unsigned int binsX, float lowX, float upX, unsigned int binsY, float lowY, float upY,
					      bool useTree=false)
{
  if(useTree && !binsY){
    //std::cout << "Adding *" << variable << "* to TTree" << std::endl;
    if(!tree){
      tree = fs->make<TTree>("TTree","TTree",0);
      //treeVars_["weight"];
      //tree->Branch("weight", &treeVars_["weight"], ("weight" + *"/F"));
    }
    treeVars_[variable];
    tree->Branch(variable, &treeVars_[variable], (std::string(variable) + "/F").c_str());
  }
  else{
    //std::cout << "Adding *" << variable << "* to Histograms" << std::endl;
    if     (!binsY &&  !lowY && !upY )  hists_  [variable] = fs->make<TH1F>( variable, variable, binsX, lowX, upX );
    else if( binsY && ( lowY ||  upY )) hists2D_[variable] = fs->make<TH2F>( variable, variable, binsX, lowX, upX, binsY, lowY, upY );
  }
}

template <typename Collection>
  void SingleObject<Collection>::bookVariable(edm::Service<TFileService>& fs, const char * variable,
					      unsigned int binsX, float lowX, float upX, bool useTree=false)
{
  bookVariable( fs, variable, binsX, lowX, upX, 0, 0, 0, useTree);
}

/// fill values into map for histograms or tree
template <typename Collection>
  void SingleObject<Collection>::fillValue(std::string variable, float value1, float value2, const double& weight=1.)
{
  if(hists2D_.find(variable) != hists2D_.end()) hists2D_.find(variable)->second->Fill(value1, value2, weight);
}

template <typename Collection>
  void SingleObject<Collection>::fillValue(std::string variable, float value, const double& weight=1.)
{
  if(treeVars_.find(variable) != treeVars_.end()){
    treeVars_.find(variable)->second = value;
  }
  else{
    hists_.find(variable)->second->Fill(value, weight);
  }
}

/// writing histograms to file in fwlite
template <typename Collection> 
void SingleObject<Collection>::write(TFile& file, const char* directory)
{
  file.cd( directory );
  for(std::map<std::string, TH1*>::const_iterator hist = hists_.begin(); hist !=hists_.end(); ++hist){
    hist->second->Write( );
  }
  for(std::map<std::string, TH2*>::const_iterator hist = hists2D_.begin(); hist !=hists2D_.end(); ++hist){
    hist->second->Write( );
  }
}

#endif
