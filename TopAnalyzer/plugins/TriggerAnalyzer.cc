#include "TopAnalysis/TopAnalyzer/plugins/TriggerAnalyzer.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"

using namespace std;
using namespace edm;

TriggerAnalyzer::TriggerAnalyzer(const edm::ParameterSet& cfg)
{
  trigResults_ = cfg.getParameter<edm::InputTag>       ("TriggerResults");
  muons_       = cfg.getParameter<edm::InputTag>       ("muons"         );  
  hltPaths_    = cfg.getParameter<vector<string> >("hltPaths"      );
  mainTrigger_ = cfg.getParameter<string>         ("mainTrigger"   );  
}

TriggerAnalyzer::~TriggerAnalyzer()
{
}

void
TriggerAnalyzer::beginJob()
{
    n_TrigPaths = hltPaths_.size();
    Service<TFileService> fs;
    if( !fs ){
      throw edm::Exception( edm::errors::Configuration,
                          "TFile Service is not registered in cfg file" );
    }
    
    FiredTrigs_ = fs->make<TH1D>("FiredTrigs", "Trigger Efficiencies", n_TrigPaths, -0.5, n_TrigPaths-0.5);
    FiredTrigs_->GetXaxis()->SetTitle( "Trigger Path" );
    FiredTrigs_->GetYaxis()->SetTitle( "#epsilon" );       
    for(int i=1; i<=n_TrigPaths; ++i){  
      FiredTrigs_->GetXaxis()->SetBinLabel( i, hltPaths_[i-1].c_str() );
    }  
    
    Passed_ = fs->make<TH1D>("Passed", "Total Efficiency", 2, -0.5, 1.5);
    Passed_->GetYaxis()->SetTitle( "#epsilon_{tot}" );       
    Passed_->GetXaxis()->SetBinLabel( 1, "failed");
    Passed_->GetXaxis()->SetBinLabel( 2, "passed");
    
    Correlations_ = fs->make<TH2D>("Correlations", "Trigger Correlations", 
      n_TrigPaths, -0.5, n_TrigPaths-0.5, n_TrigPaths, -0.5, n_TrigPaths-0.5);
    Correlations_->GetXaxis()->SetTitle( "Trigger Path" );
    Correlations_->GetYaxis()->SetTitle( "Trigger Path" ); 
    for(int i=1; i<=n_TrigPaths; ++i){  
      Correlations_->GetXaxis()->SetBinLabel( i, hltPaths_[i-1].c_str() );
      Correlations_->GetYaxis()->SetBinLabel( i, hltPaths_[i-1].c_str() );
    }
            
    n_evts=0;     
}

void
TriggerAnalyzer::analyze(const edm::Event& evt, const edm::EventSetup&)
{
  n_evts++;

  Handle<TriggerResults> trigResults; 
  evt.getByLabel(trigResults_, trigResults); 

  if(trigResults.failedToGet()) return;
  
  bool trigFired = false;
  bool mainTrigFired = false;
  int n_Triggers = trigResults->size();

  TriggerNames trigName = evt.triggerNames(*trigResults);

  for(int i_Trig = 0; i_Trig<n_Triggers; ++i_Trig){  
    //cout <<  trigName.triggerName(i_Trig) << endl;
    
    // check if main trigger has fired
    if(trigName.triggerName(i_Trig)==mainTrigger_ && trigResults.product()->accept(i_Trig)){ 
      mainTrigFired=true;	
    }
    
    if(!trigResults.product()->accept(i_Trig)) continue;        
    for(int i = 0; i<n_TrigPaths; i++){
      if(!(trigName.triggerName(i_Trig)==hltPaths_[i])) continue; 	    	    	    	    
      trigFired = true;
      FiredTrigs_->Fill(i);
      
     // correlation plot 
     for(int j_Trig = 0; j_Trig<n_Triggers; ++j_Trig){    
       if(!trigResults.product()->accept(j_Trig)) continue;         
        for(int j = 0; j<n_TrigPaths; j++){
	  if(!(trigName.triggerName(j_Trig)== hltPaths_[j])) continue;
	  Correlations_->Fill(i,j);	      
        }
      }	
        
    }      
  }  
  Passed_->Fill(trigFired);
}

void
TriggerAnalyzer::endJob()
{   
}

double
TriggerAnalyzer::binomialError(double numerator, double denominator)
{      
  if(numerator>denominator) return 999999.;
  
  double error;
  error=sqrt((1-numerator/denominator)
   *numerator/denominator/denominator);
     
  return error;
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( TriggerAnalyzer );
