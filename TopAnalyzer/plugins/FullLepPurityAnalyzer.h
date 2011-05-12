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
  // initiate a vector of counters with 0
  void initiateCounter(const std::vector<double>&, std::vector<int>&, std::vector<int>&, std::vector<int>&);
  /// count events with a given quantity generated AND reconstructed inside a certain bin
  void countRecGen(const double&, const double&, std::vector<double>&, std::vector<int>&);
  /// count events with a given quantity generated inside a certain bin
  void countGen(const double&, std::vector<double>&, std::vector<int>&); 
  // count events with a given quantity reconstructed inside a certain bin
  void countRec(const double&, std::vector<double>&, std::vector<int>&);
  /// evaluates purity and stability from counters and fill hists
  void evaluate(TH1D&, std::vector<int>&, std::vector<int>& );

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
  std::vector<int> lepEtaRecGenCounters_;      
  std::vector<int> lepRapidityRecGenCounters_; 
  std::vector<int> lepPhiRecGenCounters_;      
  std::vector<int> lepPtRecGenCounters_;       
  
  std::vector<int> lepBarEtaRecGenCounters_;	  
  std::vector<int> lepBarRapidityRecGenCounters_; 
  std::vector<int> lepBarPhiRecGenCounters_;	  
  std::vector<int> lepBarPtRecGenCounters_;	   

  std::vector<int> lepPairEtaRecGenCounters_;    
  std::vector<int> lepPairRapidityRecGenCounters_;
  std::vector<int> lepPairPhiRecGenCounters_;    
  std::vector<int> lepPairPtRecGenCounters_;     
  std::vector<int> lepPairMassRecGenCounters_; 
  
  std::vector<int> bEtaRecGenCounters_;      
  std::vector<int> bRapidityRecGenCounters_; 
  std::vector<int> bPhiRecGenCounters_;      
  std::vector<int> bPtRecGenCounters_;       
  
  std::vector<int> bBarEtaRecGenCounters_;     
  std::vector<int> bBarRapidityRecGenCounters_; 
  std::vector<int> bBarPhiRecGenCounters_;     
  std::vector<int> bBarPtRecGenCounters_;      
  
  std::vector<int> topEtaRecGenCounters_;     
  std::vector<int> topRapidityRecGenCounters_; 
  std::vector<int> topPhiRecGenCounters_;     
  std::vector<int> topPtRecGenCounters_;      
  
  std::vector<int> topBarEtaRecGenCounters_;	  
  std::vector<int> topBarRapidityRecGenCounters_; 
  std::vector<int> topBarPhiRecGenCounters_;	  
  std::vector<int> topBarPtRecGenCounters_;	 
  
  std::vector<int> TtBarEtaRecGenCounters_;    
  std::vector<int> TtBarRapidityRecGenCounters_;
  std::vector<int> TtBarPhiRecGenCounters_;    
  std::vector<int> TtBarPtRecGenCounters_;     
  std::vector<int> TtBarMassRecGenCounters_;  
  
  // RecCounter for objects reconstructed in bin
  std::vector<int> lepEtaRecCounters_;         
  std::vector<int> lepRapidityRecCounters_; 
  std::vector<int> lepPhiRecCounters_;         
  std::vector<int> lepPtRecCounters_;	       
  
  std::vector<int> lepBarEtaRecCounters_;      
  std::vector<int> lepBarRapidityRecCounters_; 
  std::vector<int> lepBarPhiRecCounters_;      
  std::vector<int> lepBarPtRecCounters_;	 	

  std::vector<int> lepPairEtaRecCounters_;       
  std::vector<int> lepPairRapidityRecCounters_;
  std::vector<int> lepPairPhiRecCounters_;       
  std::vector<int> lepPairPtRecCounters_;        
  std::vector<int> lepPairMassRecCounters_; 
  
  std::vector<int> bEtaRecCounters_;	  
  std::vector<int> bRapidityRecCounters_; 
  std::vector<int> bPhiRecCounters_;	  
  std::vector<int> bPtRecCounters_;	  
  
  std::vector<int> bBarEtaRecCounters_;        
  std::vector<int> bBarRapidityRecCounters_; 
  std::vector<int> bBarPhiRecCounters_;        
  std::vector<int> bBarPtRecCounters_;         
  
  std::vector<int> topEtaRecCounters_;        
  std::vector<int> topRapidityRecCounters_; 
  std::vector<int> topPhiRecCounters_;        
  std::vector<int> topPtRecCounters_;	      
  
  std::vector<int> topBarEtaRecCounters_;      
  std::vector<int> topBarRapidityRecCounters_; 
  std::vector<int> topBarPhiRecCounters_;      
  std::vector<int> topBarPtRecCounters_;	 
  
  std::vector<int> TtBarEtaRecCounters_;       
  std::vector<int> TtBarRapidityRecCounters_;
  std::vector<int> TtBarPhiRecCounters_;       
  std::vector<int> TtBarPtRecCounters_;        
  std::vector<int> TtBarMassRecCounters_;    
  
  // GenCounter for objects generated in bin
  std::vector<int> lepEtaGenCounters_;         
  std::vector<int> lepRapidityGenCounters_; 
  std::vector<int> lepPhiGenCounters_;         
  std::vector<int> lepPtGenCounters_;	       
  
  std::vector<int> lepBarEtaGenCounters_;      
  std::vector<int> lepBarRapidityGenCounters_; 
  std::vector<int> lepBarPhiGenCounters_;      
  std::vector<int> lepBarPtGenCounters_;	 	

  std::vector<int> lepPairEtaGenCounters_;       
  std::vector<int> lepPairRapidityGenCounters_;
  std::vector<int> lepPairPhiGenCounters_;       
  std::vector<int> lepPairPtGenCounters_;        
  std::vector<int> lepPairMassGenCounters_;
  
  std::vector<int> bEtaGenCounters_;	  
  std::vector<int> bRapidityGenCounters_; 
  std::vector<int> bPhiGenCounters_;	  
  std::vector<int> bPtGenCounters_;	  
  
  std::vector<int> bBarEtaGenCounters_;        
  std::vector<int> bBarRapidityGenCounters_; 
  std::vector<int> bBarPhiGenCounters_;        
  std::vector<int> bBarPtGenCounters_;         
  
  std::vector<int> topEtaGenCounters_;        
  std::vector<int> topRapidityGenCounters_; 
  std::vector<int> topPhiGenCounters_;        
  std::vector<int> topPtGenCounters_;	      
  
  std::vector<int> topBarEtaGenCounters_;      
  std::vector<int> topBarRapidityGenCounters_; 
  std::vector<int> topBarPhiGenCounters_;      
  std::vector<int> topBarPtGenCounters_;	 
  
  std::vector<int> TtBarEtaGenCounters_;       
  std::vector<int> TtBarRapidityGenCounters_;
  std::vector<int> TtBarPhiGenCounters_;       
  std::vector<int> TtBarPtGenCounters_;        
  std::vector<int> TtBarMassGenCounters_;
  
  // purity hists
  TH1D* lepEtaPurity_;	  
  TH1D* lepRapidityPurity_; 
  TH1D* lepPhiPurity_;	  
  TH1D* lepPtPurity_;	  
  
  TH1D* lepBarEtaPurity_;      
  TH1D* lepBarRapidityPurity_; 
  TH1D* lepBarPhiPurity_;      
  TH1D* lepBarPtPurity_;	      

  TH1D* lepPairEtaPurity_;	  
  TH1D* lepPairRapidityPurity_;
  TH1D* lepPairPhiPurity_;	  
  TH1D* lepPairPtPurity_;	  
  TH1D* lepPairMassPurity_; 
  
  TH1D* bEtaPurity_;      
  TH1D* bRapidityPurity_; 
  TH1D* bPhiPurity_;      
  TH1D* bPtPurity_;       
  
  TH1D* bBarEtaPurity_;	  
  TH1D* bBarRapidityPurity_; 
  TH1D* bBarPhiPurity_;	  
  TH1D* bBarPtPurity_;	  
  
  TH1D* topEtaPurity_;	 
  TH1D* topRapidityPurity_; 
  TH1D* topPhiPurity_;	 
  TH1D* topPtPurity_;	 
  
  TH1D* topBarEtaPurity_;      
  TH1D* topBarRapidityPurity_; 
  TH1D* topBarPhiPurity_;      
  TH1D* topBarPtPurity_;	    
  
  TH1D* TtBarEtaPurity_;	  
  TH1D* TtBarRapidityPurity_;
  TH1D* TtBarPhiPurity_;	  
  TH1D* TtBarPtPurity_;	  
  TH1D* TtBarMassPurity_;  
  
  // stability hists
  TH1D* lepEtaStability_;	  
  TH1D* lepRapidityStability_; 
  TH1D* lepPhiStability_;	  
  TH1D* lepPtStability_;	  
  
  TH1D* lepBarEtaStability_;      
  TH1D* lepBarRapidityStability_; 
  TH1D* lepBarPhiStability_;      
  TH1D* lepBarPtStability_;	    
  
  TH1D* lepPairEtaStability_;      
  TH1D* lepPairRapidityStability_; 
  TH1D* lepPairPhiStability_;
  TH1D* lepPairPtStability_;        
  TH1D* lepPairMassStability_;     
  
  TH1D* bEtaStability_;      
  TH1D* bRapidityStability_; 
  TH1D* bPhiStability_;      
  TH1D* bPtStability_;       
  
  TH1D* bBarEtaStability_;	  
  TH1D* bBarRapidityStability_; 
  TH1D* bBarPhiStability_;	  
  TH1D* bBarPtStability_;	  
  
  TH1D* topEtaStability_;	 
  TH1D* topRapidityStability_; 
  TH1D* topPhiStability_;	 
  TH1D* topPtStability_;	 
  
  TH1D* topBarEtaStability_;      
  TH1D* topBarRapidityStability_; 
  TH1D* topBarPhiStability_;      
  TH1D* topBarPtStability_;	    
  
  TH1D* TtBarEtaStability_;	  
  TH1D* TtBarRapidityStability_;
  TH1D* TtBarPhiStability_;	  
  TH1D* TtBarPtStability_;	  
  TH1D* TtBarMassStability_;           
};

#endif
