#ifndef MuonKinematics_h
#define MuonKinematics_h

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "TopAnalysis/TopAnalyzer/interface/SingleObject.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

/**
   \class   MuonKinematics MuonKinematics.h "TopAnalysis/TopAnalyzer/interface/MuonKinematics.h"

   \brief   Derived class to analyze the kinematics of muons on reconstruction and generator level

   This class keeps histograms for the kinematics of muons only(!). These histograms can 
   be filled from edm::View<reco::Candidate> collections. The class is derived from the 
   SingleObject<Collection> interface, which makes it usable in fwfull or fwlite. 
*/

class MuonKinematics : public SingleObject<const edm::View<pat::Muon> > {

 public:
  /// default constructor for fw lite
  explicit MuonKinematics(const int index);
  /// default constructor for full fw
  explicit MuonKinematics(const edm::ParameterSet& configFile);
  /// default destructor
  ~MuonKinematics(){};

  /**
     The following functions have to be implemented for any class
     derived from SingleObject<Collection>
  **/
  /// histogramm booking for fwlite 
  void book();
  /// histogramm booking for fwfull
  void book(edm::Service<TFileService>& fileService);
  /// histogram filling for fwlite and for fwfull
  void fill(const edm::View<pat::Muon>& muons, const double& weight=1.);
  /// everything which needs to be done after the event loop
  void process(){}

 private:
  /// check if histogram was booked in the corresponding map. Note that the 
  /// template C is needed to make this function accessible for maps that 
  /// contain any kind of type keyed via strings
  template<typename C> 
  bool booked(std::map<std::string, C> map, const std::string histName) const { return map.find(histName.c_str())!=map.end(); }
  /// fill 1-dimensional histogram if it had been booked before
  void fill(const std::string histName, double valueA, double weight) const { if(booked(hists_, histName)) hists_.find(histName)->second->Fill(valueA, weight); }
  /// fill 2-dimensional histogram if it had been booked before
  void fill(const std::string histName, double valueA, double valueB, double weight) const { if(booked(hists2D_, histName)) hists2D_.find(histName)->second->Fill(valueA, valueB, weight); }

 private:
   /// produce a TTree as output instead of histograms
   bool useTree_;
  /// index of jet to be plotted
  int index_;
};

#endif
