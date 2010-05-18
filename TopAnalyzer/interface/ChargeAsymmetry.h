#ifndef ChargeAsymmetry_h
#define ChargeAsymmetry_h

#include "TMath.h"
#include "TopAnalysis/TopAnalyzer/interface/SingleObject.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

/**
   \class   ChargeAsymmetry ChargeAsymmetry.h "TopAnalysis/TopAnalyzer/interface/chargeAsymmetry.h"

   \brief   Derived class to calculate charge asymmetry parameter for estimation of W+jet and other events being asymmetric in charge.

   This class keeps histogramms of the tranverse momentum of leptons. This is done for all, positive 
   and negative charged particles. This histogramms are used to calculate the charge asymmetry parameter
   R via R = (N+ + N-) / (N+ - N-) with N+/- as the entries of the pos./neg. charged lepton. R can be 
   used later to determine the Number of W-Boson events via N_W = R* (N+_all -N-_all). The basic idea 
   behind this is that W+jets, single to and some few other event types are pruduced charge asymmetric 
   because of differnt product mechanisms in a pp collider. On the other Hand the signal - top and others
   like Z+jets are produced symmetric in charge. The input collection (given by parameter _src_) is 
   expected to be of type reco::GenParticle. To do the job, it should be leptons coming from Wboson.
   The parameters of the module are: 
   
   _src_         : input collection. This may be of any type derived from reco::GenParticle.

   _lepton_      : pdgId of the lepton you would like to include into your histograms. -1. 
                   corresponds to all: muons, taus and electrons.

   _eventWeight_ : event weight. This parameter is optional. It does not have to be present in the in
                   configuration of the module. If given all histograms will not be filled with the 
	           weight 1. but with the weight as given by this parameter. 

   _index_       : index of the lepton in consideration for the measurement. If -1. all objects in the 
                   given collection will be filled. For leading and subleading objects this parameter 
		   follows C++ conventions. 

   The binning of the histograms is determined from the array within the namespace _chargeAsymmetry_ 
   as given in the class definition. It should correspond to the binning used in the measurement where 
   you want to use the W+jets estimation. The class is derived from the SingleObject<Collection> 
   interface, which makes it usable in full framework or fwlite. 
*/

namespace chargeAsymmetry{
  // binning for all histograms
  double leptonPt[]  = {   0. ,    20. ,    35.,    50. ,   70. ,    95.,   200. };
}

class  ChargeAsymmetry : public SingleObject<const edm::View<reco::GenParticle> > {
  
 public:
  /// default constructor for fw lite
  explicit ChargeAsymmetry(int index, int lepton);
  /// default constructor for full framework
  explicit ChargeAsymmetry(const edm::ParameterSet& configFile);
  /// default destructor
  ~ChargeAsymmetry(){};

  /**
     The following functions have to be implemented for any class
     derived from SingleObject<Collection>.
  **/

  /// histogram booking for fwlite 
  void book();
  /// histogram booking for full fw
  void book(edm::Service<TFileService>& fileService);
  /// fill correlation histograms for later stability and purity calculation 
  void fill(const edm::View<reco::GenParticle>& leptons, const double& weight=1.);
  /// everything which needs to be done after the event loop
  void process(){}

 private:
  /// derive whether a + or a - histograms is to be filled and add the corres-
  /// ponding ending to label. This function expects charge to be unequal zero
  /// and the histogram name extension for charged quantities to be 'p'/'m' 
  /// for plus/minus for the internal histogram management
  std::string charged(std::string label, int charge){ if(charge>0) label+="p"; else label+="m"; return label;}
  /// check if histogram was booked in the corresponding map. Note that the 
  /// template C is needed to make this function accessible for maps that 
  /// contain any kind of type keyed via strings
  template<typename C> 
  bool booked(std::map<std::string, C> map, const std::string histName) const { return map.find(histName.c_str())!=map.end(); }
  /// fill histogram if it had been booked before
  void fill(const std::string histName, double valueA, double weight) const { if(booked(hists_, histName)) hists_.find(histName)->second->Fill(valueA, weight); }

 private:
  /// index of lepton to be plotted
  int index_; 
  /// pdgId of lepton to be plotted
  int lepton_;
};

#endif
