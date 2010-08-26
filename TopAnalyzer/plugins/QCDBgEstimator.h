#ifndef QCDBgEstimator_h
#define QCDBgEstimator_h

#include "TH1.h"
#include "TString.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

/**
   \class   QCDBgEstimator QCDBgEstimator.h "TopAnalysis/TopAnalyzer/plugins/QCDBgEstimator.h"

   \brief   EDAnalyzer to estimate the QCD and fake muon background with the wrong charge method

   The invariant mass of the leading muons is plotted in bins of the worse isolated muon's isolation.
   This is done separately for events with same charge and oppositely charged muons. By dividing the 
   number of entries for right and wrong charge events in each bin one gets a normalization factor 
   for each bin.
*/

class QCDBgEstimator : public edm::EDAnalyzer {

  public:
    /// default constructor
    explicit QCDBgEstimator(const edm::ParameterSet&);
    /// default destructor
    ~QCDBgEstimator();
    
  private:
    /// everything which has to be done before the event loop: book fileservice and histograms
    virtual void beginJob();
    /// everything which has to be done during the event loop: analyze and fill histos
    virtual void analyze(const edm::Event&, const edm::EventSetup&);
    /// everything which has to be done after the event loop: bin-wise calculation of norm factor
    virtual void endJob();

    /// input muon collection
    edm::InputTag muons_;
    /// combined isolation bins of both muons from config
    std::vector<double> isoBins_;
    /// bins of the invariant dimuon mass
    std::vector<double> massBins_;
    /// define a PatMuonCollection as a vector of PatMuons      
    typedef std::vector<pat::Muon> PatMuonCollection;
    /// true if leading muons have same charge
    bool isWrongCharge; 
    
    /// histograms for the right charge dimuon mass in bins of di-combined isolation
    std::vector<TH1D*> dimassRCIsoBinsLowMass_;
    std::vector<TH1D*> dimassRCIsoBinsPeakMass_;    
    std::vector<TH1D*> dimassRCIsoBinsHighMass_;    
    
    /// histograms for the wrong charge dimuon mass in bins of di-combined isolation
    std::vector<TH1D*> dimassWCIsoBinsLowMass_;  
    std::vector<TH1D*> dimassWCIsoBinsPeakMass_;    
    std::vector<TH1D*> dimassWCIsoBinsHighMass_;     
};

#endif
