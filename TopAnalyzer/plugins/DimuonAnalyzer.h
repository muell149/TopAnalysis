#ifndef DimuonAnalyzer_h
#define DimuonAnalyzer_h

#include <iostream>

#include "TH1D.h"
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
    /// plot for right-charge dimuon mass    
    TH1D * dimassRC_;
    /// plot for wrong-charge dimuon mass
    TH1D * dimassWC_;
 
    /// number of muons    
    TH1D * nMu_;
    /// dr between leading muons
    TH1D * drMu_;
    
    /// isolation efficiency for absolute cut
    TH1D * absCount_;
    /// isolation efficiency for relative cut
    TH1D * relCount_;
    /// isolation efficiency for combined cut
    TH1D * combCount_;
    /// isolation efficiency for quadratically added combined isolation
    TH1D * diCombCount_;
     
    /// counts number of entries in given bins of invariant mass (will be used for DY BG estiamtion)
    TH1D * nEntries_;
};

#endif
