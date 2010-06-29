#ifndef FullHadKinFit_h
#define FullHadKinFit_h

#include <string>
#include <cstring>
#include <vector>
#include <map>

#include "TH1.h"
#include "TH2.h"
#include "TTree.h"
#include "TRandom3.h"
#include "TLorentzVector.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/LeafCandidate.h"

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

/**
   \class   FullHadKinFit FullHadKinFit.h "TopAnalysis/TopAnalyzer/interface/FullHadKinFit.h"

   \brief   Class to analyze fully hadronic kinFit

   The structure keeps histograms for fully hadronic kinFit analysis.
   These histograms can be filled from reco::Candidate class. 
*/

class FullHadKinFit : public edm::EDAnalyzer {

 public:
  /// default constructor
  explicit FullHadKinFit(const edm::ParameterSet& configFile);
  /// default destructor
  ~FullHadKinFit(){};

 private:

  /// initiate histograms
  virtual void beginJob();
  /// analyze triggers and fill histograms
  virtual void analyze(const edm::Event& event, const edm::EventSetup&);
  /// empty
  virtual void endJob();

  /// dynamic cast a whole vector of reco::LeafCandidate* at once to a vector of any derived class
  template < class T > std::vector<const  T* > dynCastVector(const edm::View<reco::LeafCandidate>& src);
  
  /// do generator matching
  void genMatcher(const edm::View<reco::LeafCandidate>& src);

  /// find ME level partons not belonging to top decay directly
  int foundRadiation(const edm::View<reco::LeafCandidate>& src, std::vector<const reco::GenParticle*>& genParts);

  /// function to do PseudoBTagging with no / one / two BTags
  bool doPseudoBTagging(std::vector< unsigned int > combi);

  /// smear input vectors for kinematic fit
  void smear(std::vector< TLorentzVector >& vecs);

  /// function to find types of jet-combinations in KinFits (1 right, 2 branches right, but inner-branche particles mixup, 3 inter-branch mixup, 4 missing jet)
  int comboType( std::vector< unsigned int > combi );

  /// function to do lower pt cut
  bool cutPt(std::vector< TLorentzVector >& vecs, double ptCut);

  /// stucture to store kinFit resolutions
  struct KinFitResolutions {
    Double_t Et;
    Double_t Eta;
    Double_t Phi;
  };

  /// structure to store all relevant infos from a kinematic fit
  struct KinFitResult {
    std::vector< TLorentzVector > GenVecs;
    std::vector< TLorentzVector > IniVecs;
    std::vector< TLorentzVector > FitVecs;
    double Chi2;
    double NDF;
    double Prob;
    std::vector<unsigned int> JetCombi;
    bool operator< (const KinFitResult& rhs) { return Chi2 < rhs.Chi2; };
  };
  
  /// do the fitting
  std::list< KinFitResult > fit(std::vector< TLorentzVector >& vecs);

  /// definition of resolutions to be used in kinematic fit
  std::vector<KinFitResolutions> getResolutions(const std::vector< TLorentzVector >* cand, const std::string whichResolution);

  /// input tag of src collection
  edm::InputTag src_;

  /// configuration of smearing strength and resolution
  double smear_;
  double resol_;
  std::string smearType_;
  std::string resolType_;

  /// configuration which jets should get smeared (set to -1 for all)
  int smearOnly_;

  /// number of bTags to be used in kinematic fit
  unsigned int bTags_;

  /// only the right combination should be evalutated
  bool onlyGenMatch_;

  /// do plots for all combinations instead of only the best one
  bool saveAllCombo_;

  /// exchange lowest pt genParticle with one radiated particle (if more than 1 available exchange -> do it again)
  bool exchangePart_;

  /// use fitted event as input for another fit
  bool fitAsFitInpt_;

  /// only take those events, with no Non-Top-ME-genParticles
  bool noRadiations_;

  /// lower pt cut applied on all (pseudo) reco particles, genParticles
  double recoPtCut_, genPtCut_;

  /// vector of strings for the binning of the resolutions
  std::vector<std::string> binsUdsc_, binsB_;
  /// vectors for the resolution functions
  std::vector<std::string> funcEtUdsc_, funcEtaUdsc_, funcPhiUdsc_, funcEtB_, funcEtaB_, funcPhiB_;

  /// vector to store the genParticles
  std::vector<const reco::GenParticle*> genParticles;
  /// store positions of particles in vectors
  enum whichGenParticle{B, LQ, LQBar, BBar, LP, LPBar};

  /// counter variables
  unsigned int eventCounter, fullHadCounter, fitCounter;

  /// random numbers generator for smearing
  TRandom3 rnd;

  /// container to keep all histogramms
  std::map<std::string, TH1*> hists_;

  template<typename T> class F {
  public:
    const T* operator()(const reco::LeafCandidate& x) {
      return dynamic_cast<const T* >(&x);
    }
  };

  /// a functor for determination of negative Chi2 values in list of all KinFitResults
  struct negativeChi2 
  { 
    bool operator() ( const KinFitResult & rhs ) { return (rhs.Chi2 < 0.); }
  };
};


template < class T >
std::vector<const T* >
FullHadKinFit::dynCastVector(const edm::View<reco::LeafCandidate>& src)
{
  std::vector<const T* > output;

  for(edm::View<reco::LeafCandidate>::const_iterator item = src.begin(); item != src.end(); ++item){
    const T* newItem = dynamic_cast<const T* >(&(*item));
    if(newItem) output.push_back( newItem );
    //delete newItem;
  }
  return output;
}

#endif
