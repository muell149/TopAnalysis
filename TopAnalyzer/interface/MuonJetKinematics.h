#ifndef MuonJetKinematics_h
#define MuonJetKinematics_h

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "TopAnalysis/TopAnalyzer/interface/DoubleObject.h"

/**
   \class   MuonJetKinematics MuonJetKinematics.h "TopAnalysis/TopAnalyzer/interface/MuonJetKinematics.h"

   \brief   Derived class to analyze the relations in muon jet kinematocs on reconstruction level

   The structure keeps histograms to analyze the releation between muon and jet kinematics. These 
   histograms can be filled from std::vector<pat::Muon> only. The class is derived from the DoubleObject 
   interface, which makes it usable in full framework (fw) or fwlite. 
*/

class MuonJetKinematics : public DoubleObject<const std::vector<pat::Muon>, const std::vector<pat::Jet> > {

 public:
  /// default constructor for fw lite
  explicit MuonJetKinematics();
  /// default constructor for full fw
  explicit MuonJetKinematics(const edm::ParameterSet& configFile);
  /// default destructor
  ~MuonJetKinematics(){};

  /// histogramm booking for fwlite 
  void book();
  /// histogramm booking for full fw
  void book(edm::Service<TFileService>& fileService);
  /// histogram filling for fwlite and for full fw
  void fill(const std::vector<pat::Muon>& muons, const std::vector<pat::Jet>& jets, const double& weight=1.);
  /// everything which needs to be done after the event loop
  void process();

 private:
  /// number of histogram fills for normalization (weighted)
  double norm_;
};

#endif
