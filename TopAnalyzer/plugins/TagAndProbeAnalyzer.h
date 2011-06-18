#include "TH1.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"

#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"


/**
   \class   TagAndProbeAnalyzer TagAndProbeAnalyzer.h "TopAnalysis/TopAnalyzer/plugins/TagAndProbeAnalyzer.h"

   \brief   Plugin to fill histograms for the determination of tag and probe efficiencies

   Can be used for muons or electrons
*/

class TagAndProbeAnalyzer : public edm::EDAnalyzer {
 public:
  /// default constructor
   explicit TagAndProbeAnalyzer(const edm::ParameterSet& cfg);
  /// default destructor
    ~TagAndProbeAnalyzer();
  
  
 private:
  /// ...
  virtual void beginJob();
  /// ...
  virtual void analyze(const edm::Event& evt, const edm::EventSetup& setup);
  /// ...
  virtual void endJob();
  /// ...
  double minDR(edm::View<reco::Candidate>::const_iterator firstJet, edm::View<reco::Candidate>::const_iterator lastJet, edm::View<reco::Candidate>::const_iterator muon);

 private:
  /// ...
  edm::InputTag probes_;
  edm::InputTag tests_;
  edm::InputTag jets_;  

  /// tag and probe histogram
  std::map<std::string, TH1F*> hists_;
  /// counts number of events
  double evtNum_;
  /// variable (true) or fixed (false) bins
  //bool varBins_;
  /// variables for cut on pt and eta: pt cut is not applied on pt-histo, eta cut is not applied on eta-histo
  /// both cuts are applied on all other histos 
  double ptCut_;
  double etaCut_;
  /// nBins of histos
  int nBinsPt_;
  int nBinsEta_;
  int nBinsPhi_;
  int nBinsMult_;
  int nBinsRelIso_;
  int nBinsMinDR_;
  int nBinsLepMult_;
  /// in case of fixed bins: 1st vector entry=xlow, 2nd vector entry=xup (left and right edges of histo)
  /// in case of variable bins: vector of low-edges for each bin
  std::vector<double> binsPt_;
  std::vector<double> binsEta_;
  std::vector<double> binsPhi_;
  std::vector<double> binsMult_;
  std::vector<double> binsRelIso_;
  std::vector<double> binsMinDR_;
  std::vector<double> binsLepMult_;
};

inline
double TagAndProbeAnalyzer::minDR(edm::View<reco::Candidate>::const_iterator firstJet, edm::View<reco::Candidate>::const_iterator lastJet, edm::View<reco::Candidate>::const_iterator muon)
{
  double minDR=-1;
  for(edm::View<reco::Candidate>::const_iterator jet=firstJet; jet!=lastJet; ++jet){
    if(minDR<0 || deltaR(jet->eta(), jet->phi(), muon->eta(), muon->phi())<minDR){
      minDR=deltaR(jet->eta(), jet->phi(), muon->eta(), muon->phi());
    }
  }
  return minDR;
}
