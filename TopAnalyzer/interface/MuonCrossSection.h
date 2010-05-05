#ifndef MuonCrossSection_h
#define MuonCrossSection_h

#include "TMath.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "TopAnalysis/TopAnalyzer/interface/DoubleObject.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/Candidate/interface/Candidate.h"

/**
   \class   MuonCrossSection MuonCrossSection.h "TopAnalysis/TopAnalyzer/interface/MuonCrossSection.h"

   \brief   Derived class to determine differential cross section for top production in semimuonic decay channel

   This class keeps histograms for the kinematics of muons originating from semileptonic ttbar decays
   for the derivation of differential cross sections in these quantities. It may equally be applied 
   to particles on reco or on generator level. In both cases the input needs to be fully preselected 
   to the sample and phasespace of consideration. No other selection steps then whether to choose a 
   leading/subleading or all muons with a collection are applied within the module. When supplied 
   with two input collections (given by the parameters _srcA_ and _srcB_ in the module configuration) 
   2-dimensional correlation plots will be filled to derive stability/purity plots from these. The 
   parameter _srcB_ is optional and should be filled with the generator particle if given. The parame-
   ters of the module are: 

    _srcA_         : first input collection. This may be of any type derived from reco::Candidate. It 
                     is expected though that it is of pat::Muon (reco) or reco::GenParticle (gen) type 
                     depending on the function the histograms top be filled should play in the further 
                     analysis steps. When the optional partameter _srcB_ is given it is expected to be 
                     of type pat::Muon (reco).

    _srcB_         : second input collection. This parameter is optional. It does not have to be present 
                     in the configuration of the module. If given the 1-dimensional histograms for the 
		     muon kinematics will still be filled from the input collection given by parameter
		     _srcA_ (expected to be of reco type). In addition 2-dimensional correlation histo-
		     grams will be booked and filled to derive purity/stability from these histograms.

    _eventWeight_  : event weight. This parameter is optional. It does not have to be present in the in
                     configuration of the module. If given all histograms will not be filled with the 
		     weight 1. but with the weight as given by this parameter. 

    _index_        : index of the muon in consideration in for the measurement. If -1. all muons in the 
                     given collection will be filled. For leading and subleading muons this parameter 
		     follows C++ conventions. 

   The binning of the histograms is determined from the a set of arrays within the namespace _CrossSection_ 
   as given in the class definition. The class is derived from the DoubleObject<CollectionA, CollectionB> 
   interface, which makes it usable in full framework or fwlite. 
*/

namespace CrossSection{
  // binning for cross section histograms
  double muonPt[]  = {   0. ,    20. ,    35.,    50. ,   70. ,    95.,   200. };
  double muonEta[] = {  -2.1,   -0.75,    0.0,    0.75,   2.1                  };
  double muonPhi[] = {  -3.0,   -2.0 ,   -1.0,    0.0 ,   1.0 ,   2.0 ,   3.0  };
}

class MuonCrossSection : public DoubleObject<const edm::View<reco::Candidate>, const edm::View<reco::GenParticle> > {
  
 public:
  /// default constructor for fw lite
  explicit MuonCrossSection(int index);
  /// default constructor for full framework
  explicit MuonCrossSection(const edm::ParameterSet& configFile);
  /// default destructor
  ~MuonCrossSection(){};

  /**
     The following functions have to be implemented for any class
     derived from SingleObject<Collection>. The fill function is
     overloaded to serve both for the TtGenEvent class directoy or 
     the TtSemiLeptonicEvent class.
  **/
  /// histogram booking for fwlite 
  void book();
  /// histogram booking for full fw
  void book(edm::Service<TFileService>& fileService);
  /// fill histograms for reco or gen level particles
  void fill(const edm::View<reco::Candidate>& muons, const double& weight=1.);
  /// fill correlation histograms for later stability and purity calculation 
  void fill(const edm::View<reco::Candidate>& recs, const edm::View<reco::GenParticle>& gens, const double& weight=1.);
  /// everything which needs to be done after the event loop
  void process(){}

 private:
  /// derive whether a + or a - histograms is to be filled and add the corres-
  /// ponding ending to label. This function expects charge to be unequal zero
  /// and the histogram name extension for chagred quantities to be 'p'/'m' 
  /// for plus/minus for the internal histogram management
  std::string charged(std::string label, int charge){ if(charge>0) label+="p"; else label+="m"; return label;}
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
  /// index of jet to be plotted
  int index_; 
};

#endif
