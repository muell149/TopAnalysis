#ifndef DoubleObject_h
#define DoubleObject_h

#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

/**
   \class   DoubleObject DoubleObject.h "TopAnalysis/TopAnalyzer/interface/DoubleObject.h"

   \brief   Interface class to analyze the relation of two object types within full framework of fwlite

   The class is an interface to a common analyer or a corresponding fwlite mimic
   in TopAnalysis/TopAnalzyer/bin. It takes a two object classes as argument. An 
   interface to a common book, fill & process function is expected by the common 
   analyzer (mimic) class. Each derived class has to be provided these.
*/

template <typename CollectionA, typename CollectionB> 
class DoubleObject{

 public:
  /// default constructor for fw lite
  explicit DoubleObject(){};
  /// default constructor for fwfull
  explicit DoubleObject(const edm::ParameterSet& configFile){};
  /// default destructor
  virtual ~DoubleObject(){};
  /// write histograms to file for fwlite
  void write(TFile& file, const char* directory);

  /**
     The following functions have to be implemented for any class
     derived from DoubleObject<CollectionA, CollectionB>
  **/
  /// histogramm booking for fwlite 
  virtual void book() = 0;
  /// histogramm booking for fwfull
  virtual void book(edm::Service<TFileService>& fileService) = 0;
  /// histogram filling for fwlite and for fwfull
  virtual void fill(const CollectionA& inputCollectionA, const CollectionB& inputCollectionB, const double& weight=1.) = 0;
  /// everything which needs to be done after the event loop
  virtual void process() = 0;

 protected:
  /// histogram container
  std::map<std::string, TH1*> hists_;
  std::map<std::string, TH2*> hists2D_;
};


/// writing histograms to file in fwlite
template <typename CollectionA, typename CollectionB> 
  void DoubleObject<CollectionA, CollectionB>::write(TFile& file, const char* directory)
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
