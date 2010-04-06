#ifndef DimuonAnalyzer_h
#define DimuonAnalyzer_h

#include <iostream>

#include "TH1.h"
#include "TH2.h"
#include "TString.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

/**
   \class   DimuonAnalyzer DimuonAnalyzer.h "TopAnalysis/TopAnalyzer/plugins/DimuonAnalyzer.h"

   \brief   EDAnalyzer for the dimuon mass and some isolation plots

   The main histograms plot the invariant mass of the two leading muons separately for like and 
   unlike charge in events with at least two muons. Other histograms show the cut efficiency for 
   different kinds of isolation cuts on both muons. 
*/

class DimuonAnalyzer : public edm::EDAnalyzer {

  public:
    /// default constructor
    explicit DimuonAnalyzer(const edm::ParameterSet&);
    /// default destructor
    ~DimuonAnalyzer();
    
  private:
    /// everything which has to be done before the event loop: book fileservice and histograms
    virtual void beginJob();
    /// everything which has to be done during the event loop: analyze and fill histos
    virtual void analyze(const edm::Event&, const edm::EventSetup&);
    /// everything which has to be done after the event loop: empty 
    virtual void endJob();

    /// input muon collection
    edm::InputTag muons_;
    /// mass bins in which number of entries is counted 
    std::vector<double> massBins_;
    /// input bool: use a event weight?     
    bool useEvtWgt_;
    /// input bool: correct histos to width of log bins?     
    bool correct2width_;    
    /// define a PatMuonCollection as a vector of PatMuons      
    typedef std::vector<pat::Muon> PatMuonCollection;
    /// true if leading muons have same charge
    bool isWrongCharge; 
    /// plots for right-charge dimuon mass    
    TH1F * dimassRC_;
    /// plots for wrong-charge dimuon mass
    TH1F * dimassWC_;
      
    /// correlation between dimuon mass and isolation        
    TH2F * isoDimassCorrelation_;   
    
    /// isolation efficiency for absolute cut
    TH1F * absCount_;
    /// isolation efficiency for relative cut
    TH1F * relCount_;
    /// isolation efficiency for combined cut
    TH1F * combCount_;
    /// isolation efficiency for quadratically added combined isolation
    TH1F * diCombCount_; 
    /// counts number of entries in given bins of invariant mass
    TH1F * nEntries_;
};

#endif
