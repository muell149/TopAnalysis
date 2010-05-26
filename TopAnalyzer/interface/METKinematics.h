#ifndef METKinematics_h
#define METKinematics_h

#include "TopAnalysis/TopAnalyzer/interface/DoubleObject.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/Candidate/interface/Candidate.h"

/**
   \class   METKinematics METKinematics.h "TopAnalysis/TopAnalyzer/interface/METKinematics.h"

  \brief   Derived class to analyze basic missing Et distributions for caloMET, pfMET and all MET classes inheriting from reco::MET, may also be used to see correlations between MET and Kinematic quantities of a specific particle collection

   The structure keeps histograms for met. These histograms are filled from edm::View<reco::MET>. The 
   class is derived from the DoubleObject<Collection> interface, which makes it usable in fwfull  or 
   fwlite. When supplied with two input collections (given by the parameters _srcA_ and _srcB_ in the 
   module configuration) 2-dimensional correlation plots of MET and Kinematic quantities of the chosen 
   input collection of type reco::Candidate will be filled. The parameter _srcB_ is optional and can 
   be filled for example with pat::muon to see the relation between muon impuls and MET from the 
   corresponding neutrino. The parameters of the module are: 

    _srcA_         : first input collection. This may be of any type derived from reco::MET. It 
                     coult be patMETs or patMETsPF.

    _srcB_         : second input collection. This parameter is optional. It does not have to be present 
                     in the configuration of the module. If it is present, the 1-dimensional histograms for the 
		     met kinematics will still be filled from the input collection given by parameter
		     _srcA_ (expected to be of reco::MET type). In addition 2-dimensional correlation 
		     histograms will be booked and filled to see MET(pt/eta/phi of object).

    _eventWeight_  : event weight. This parameter is optional. It does not have to be present in the in
                     configuration of the module. If given all histograms will not be filled with the 
		     weight 1. but with the weight as given by this parameter. 
  
    _index_        : this parameter is only needed when using this module with two Objet Classes (srcA AND srcB).
                     It is the index of the srcB Object that is considered for the correlation plot. 0 means the 
		     leading Object of this class and -1 all Objects.



*/

class METKinematics : public DoubleObject<const edm::View<reco::MET>, const edm::View<reco::Candidate> > {

public:
  /// default constructor for fw lite
  explicit METKinematics();
  /// default constructor for fw full
  explicit METKinematics(const edm::ParameterSet&);
  /// default destructor
  ~METKinematics(){};

  /// histogram booking for fw lite 
  void book();
  /// histogram booking for fw full
  void book(edm::Service<TFileService>& fileService);
  /// histogram filling for basic MET plots
  void fill(const edm::View<reco::MET>& met, const double& weight=1.);
  /// histogram filling for pt - MET correlation
  void fill(const edm::View<reco::MET>& metCollection, const edm::View<reco::Candidate>& particleCollection, const double& weight=1.);
  /// everything after the filling of the histograms
  void process();
  
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
  /// index of srcB object to be plotted
  int index_;
};

#endif
