#ifndef FullLepPurityAnalyzer_h
#define FullLepPurityAnalyzer_h

#include "TH1D.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "AnalysisDataFormats/TopObjects/interface/TtFullLeptonicEvent.h"

/**
   \class   FullLepPurityAnalyzer FullLepPurityAnalyzer.h "TopAnalysis/TopAnalyzer/plugins/FullLepPurityAnalyzer.h"

   \brief   EDAnalyzer for purity and stability of dileptonic events
*/

class FullLepPurityAnalyzer : public edm::EDAnalyzer {
 public:
  /// default constructor
  explicit FullLepPurityAnalyzer(const edm::ParameterSet&);
  /// default destructor
  ~FullLepPurityAnalyzer();
  
 private:
  /// everything that has to be done before the event loop: books histograms
  virtual void beginJob() ;
  /// everything that has to be done during the event loop: count events generated/reconstructed in each bin
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  /// everything that has to be done after the event loop: calculate purity/stability from counters
  virtual void endJob();
  /// count events with a given quantity generated AND reconstructed inside a certain bin
  void countRecGen(const double&, const double&, TH1D&);

  /// input given in config has to be TtFullLeptonicEvent
  edm::InputTag FullLepEvt_;
  /// keyword for hypothesis from config: ttFullLepHypKinSolution:Key or ttFullLepHypGenMatch:Key
  edm::InputTag hypoKey_;

  std::vector<double> lepEtaBins_;	  
  std::vector<double> lepRapidityBins_; 
  std::vector<double> lepPhiBins_;	  
  std::vector<double> lepPtBins_;	  
  
  std::vector<double> lepBarEtaBins_;      
  std::vector<double> lepBarRapidityBins_; 
  std::vector<double> lepBarPhiBins_;      
  std::vector<double> lepBarPtBins_;	        

  std::vector<double> lepPairEtaBins_;	  
  std::vector<double> lepPairRapidityBins_;
  std::vector<double> lepPairPhiBins_;	  
  std::vector<double> lepPairPtBins_;	      
  std::vector<double> lepPairMassBins_;
  
  std::vector<double> bEtaBins_;      
  std::vector<double> bRapidityBins_; 
  std::vector<double> bPhiBins_;      
  std::vector<double> bPtBins_;       
  
  std::vector<double> bBarEtaBins_;	  
  std::vector<double> bBarRapidityBins_; 
  std::vector<double> bBarPhiBins_;	  
  std::vector<double> bBarPtBins_;	  
  
  std::vector<double> topEtaBins_;	 
  std::vector<double> topRapidityBins_; 
  std::vector<double> topPhiBins_;	 
  std::vector<double> topPtBins_;	 
  
  std::vector<double> topBarEtaBins_;      
  std::vector<double> topBarRapidityBins_; 
  std::vector<double> topBarPhiBins_;      
  std::vector<double> topBarPtBins_;	    
  
  std::vector<double> TtBarEtaBins_;	  
  std::vector<double> TtBarRapidityBins_;
  std::vector<double> TtBarPhiBins_;	  
  std::vector<double> TtBarPtBins_;	  
  std::vector<double> TtBarMassBins_;
  
  // RecGenCounter for objects generated and reconstructed in bin
  TH1D* lepEtaRecGenCounters_;      
  TH1D* lepRapidityRecGenCounters_; 
  TH1D* lepPhiRecGenCounters_;      
  TH1D* lepPtRecGenCounters_;       
  
  TH1D* lepBarEtaRecGenCounters_;	  
  TH1D* lepBarRapidityRecGenCounters_; 
  TH1D* lepBarPhiRecGenCounters_;	  
  TH1D* lepBarPtRecGenCounters_;	   

  TH1D* lepPairEtaRecGenCounters_;    
  TH1D* lepPairRapidityRecGenCounters_;
  TH1D* lepPairPhiRecGenCounters_;    
  TH1D* lepPairPtRecGenCounters_;     
  TH1D* lepPairMassRecGenCounters_; 
  
  TH1D* bEtaRecGenCounters_;      
  TH1D* bRapidityRecGenCounters_; 
  TH1D* bPhiRecGenCounters_;      
  TH1D* bPtRecGenCounters_;       
  
  TH1D* bBarEtaRecGenCounters_;     
  TH1D* bBarRapidityRecGenCounters_; 
  TH1D* bBarPhiRecGenCounters_;     
  TH1D* bBarPtRecGenCounters_;      
  
  TH1D* topEtaRecGenCounters_;     
  TH1D* topRapidityRecGenCounters_; 
  TH1D* topPhiRecGenCounters_;     
  TH1D* topPtRecGenCounters_;      
  
  TH1D* topBarEtaRecGenCounters_;	  
  TH1D* topBarRapidityRecGenCounters_; 
  TH1D* topBarPhiRecGenCounters_;	  
  TH1D* topBarPtRecGenCounters_;	 
  
  TH1D* TtBarEtaRecGenCounters_;    
  TH1D* TtBarRapidityRecGenCounters_;
  TH1D* TtBarPhiRecGenCounters_;    
  TH1D* TtBarPtRecGenCounters_;     
  TH1D* TtBarMassRecGenCounters_;  
  
  // RecCounter for objects reconstructed in bin
  TH1D* lepEtaRecCounters_;         
  TH1D* lepRapidityRecCounters_; 
  TH1D* lepPhiRecCounters_;         
  TH1D* lepPtRecCounters_;	       
  
  TH1D* lepBarEtaRecCounters_;      
  TH1D* lepBarRapidityRecCounters_; 
  TH1D* lepBarPhiRecCounters_;      
  TH1D* lepBarPtRecCounters_;	 	

  TH1D* lepPairEtaRecCounters_;       
  TH1D* lepPairRapidityRecCounters_;
  TH1D* lepPairPhiRecCounters_;       
  TH1D* lepPairPtRecCounters_;        
  TH1D* lepPairMassRecCounters_; 
  
  TH1D* bEtaRecCounters_;	  
  TH1D* bRapidityRecCounters_; 
  TH1D* bPhiRecCounters_;	  
  TH1D* bPtRecCounters_;	  
  
  TH1D* bBarEtaRecCounters_;        
  TH1D* bBarRapidityRecCounters_; 
  TH1D* bBarPhiRecCounters_;        
  TH1D* bBarPtRecCounters_;         
  
  TH1D* topEtaRecCounters_;        
  TH1D* topRapidityRecCounters_; 
  TH1D* topPhiRecCounters_;        
  TH1D* topPtRecCounters_;	      
  
  TH1D* topBarEtaRecCounters_;      
  TH1D* topBarRapidityRecCounters_; 
  TH1D* topBarPhiRecCounters_;      
  TH1D* topBarPtRecCounters_;	 
  
  TH1D* TtBarEtaRecCounters_;       
  TH1D* TtBarRapidityRecCounters_;
  TH1D* TtBarPhiRecCounters_;       
  TH1D* TtBarPtRecCounters_;        
  TH1D* TtBarMassRecCounters_;    
  
  // GenCounter for objects generated in bin
  TH1D* lepEtaGenCounters_;         
  TH1D* lepRapidityGenCounters_; 
  TH1D* lepPhiGenCounters_;         
  TH1D* lepPtGenCounters_;	       
  
  TH1D* lepBarEtaGenCounters_;      
  TH1D* lepBarRapidityGenCounters_; 
  TH1D* lepBarPhiGenCounters_;      
  TH1D* lepBarPtGenCounters_;	 	

  TH1D* lepPairEtaGenCounters_;       
  TH1D* lepPairRapidityGenCounters_;
  TH1D* lepPairPhiGenCounters_;       
  TH1D* lepPairPtGenCounters_;        
  TH1D* lepPairMassGenCounters_;
  
  TH1D* bEtaGenCounters_;	  
  TH1D* bRapidityGenCounters_; 
  TH1D* bPhiGenCounters_;	  
  TH1D* bPtGenCounters_;	  
  
  TH1D* bBarEtaGenCounters_;        
  TH1D* bBarRapidityGenCounters_; 
  TH1D* bBarPhiGenCounters_;        
  TH1D* bBarPtGenCounters_;         
  
  TH1D* topEtaGenCounters_;        
  TH1D* topRapidityGenCounters_; 
  TH1D* topPhiGenCounters_;        
  TH1D* topPtGenCounters_;	      
  
  TH1D* topBarEtaGenCounters_;      
  TH1D* topBarRapidityGenCounters_; 
  TH1D* topBarPhiGenCounters_;      
  TH1D* topBarPtGenCounters_;	 
  
  TH1D* TtBarEtaGenCounters_;       
  TH1D* TtBarRapidityGenCounters_;
  TH1D* TtBarPhiGenCounters_;       
  TH1D* TtBarPtGenCounters_;        
  TH1D* TtBarMassGenCounters_;
};

#endif
