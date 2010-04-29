#ifndef METKinematics_h
#define METKinematics_h

#include "TopAnalysis/TopAnalyzer/interface/SingleObject.h"
#include "DataFormats/PatCandidates/interface/MET.h"

/**
   \class   METKinematics METKinematics.h "TopAnalysis/TopAnalyzer/interface/METKinematics.h"

  \brief   Derived class to analyze basic missing Et distributions for caloMET, pfMET and all MET classes inheriting from reco::MET

   The structure keeps histograms for met. These histograms are filled from edm::View<reco::MET>. The class 
   is derived from the SingleObject<Collection> interface, which makes it usable in fwfull  or 
   fwlite.
*/

class METKinematics : public SingleObject<const edm::View<reco::MET> > {

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
  /// histogram filling for fw lite and for fw full 
  void fill(const edm::View<reco::MET>& met, const double& weight=1.);
  /// everything after the filling of the histograms
  void process();
  
};

#endif
