#include "TH1.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"

#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"


/**
   \class   TagAndProbeAnalyzer TagAndProbeAnalyzer.h "TopAnalysis/TopAnalyzer/plugins/TagAndProbeAnalyzer.h"

   \brief   Plugin to fill histograms for the determination of tag and probe efficiencies

   Add some more detailed documentation here...
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
