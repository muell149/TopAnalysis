#include "TopAnalysis/TopAnalyzer/plugins/TriggerAnalyzer.h"

TriggerAnalyzer::TriggerAnalyzer(const ParameterSet& cfg)
{
  trigResults_ = cfg.getParameter<InputTag>       ("TriggerResults");
  hltPaths_L3_ = cfg.getParameter<vector<string> >("hltPaths_L3"   );
}

TriggerAnalyzer::~TriggerAnalyzer()
{
}

void
TriggerAnalyzer::beginJob(const EventSetup&)
{
    n_TrigPaths = hltPaths_L3_.size();
    Service<TFileService> fs;
    if( !fs ){
      throw edm::Exception( edm::errors::Configuration,
                          "TFile Service is not registered in cfg file" );
    }
    
    FiredTrigs_ = fs->make<TH1F>("FiredTrigs", "Fired Triggers", n_TrigPaths, -0.5, n_TrigPaths-0.5);
    FiredTrigs_->GetXaxis()->SetTitle( "Trigger Path" );
    FiredTrigs_->GetYaxis()->SetTitle( "N_{Fired}" );       
    for(int i=1; i<=n_TrigPaths; ++i){  
      FiredTrigs_->GetXaxis()->SetBinLabel( i, hltPaths_L3_[i-1].c_str() );
    }  
    
    Passed_ = fs->make<TH1F>("Passed", "Triggered Events", 2, -0.5, 1.5);
    Passed_->GetYaxis()->SetTitle( "N" );       
    Passed_->GetXaxis()->SetBinLabel( 1, "failed");
    Passed_->GetXaxis()->SetBinLabel( 2, "passed");
    
    Correlations_ = fs->make<TH2F>("Correlations", "Trigger Correlations", 
      n_TrigPaths, -0.5, n_TrigPaths-0.5, n_TrigPaths, -0.5, n_TrigPaths-0.5);
    Correlations_->GetXaxis()->SetTitle( "Trigger Path" );
    Correlations_->GetYaxis()->SetTitle( "Trigger Path" ); 
    for(int i=1; i<=n_TrigPaths; ++i){  
      Correlations_->GetXaxis()->SetBinLabel( i, hltPaths_L3_[i-1].c_str() );
      Correlations_->GetYaxis()->SetBinLabel( i, hltPaths_L3_[i-1].c_str() );
    }      
}

void
TriggerAnalyzer::analyze(const Event& evt, const EventSetup&)
{
  Handle<TriggerResults> trigResults; 
  evt.getByLabel(trigResults_, trigResults); 

  if(trigResults.failedToGet()) return;
  
  bool trigFired = false;
  int n_Triggers = trigResults->size();

  TriggerNames trigName;
  trigName.init(*trigResults);

  for(int i_Trig = 0; i_Trig<n_Triggers; ++i_Trig){  
    //cout <<  trigName.triggerName(i_Trig) << endl;
    if(!trigResults.product()->accept(i_Trig)) continue;        
    for(int i = 0; i<n_TrigPaths; i++){
      if(!(trigName.triggerName(i_Trig)== hltPaths_L3_[i])) continue; 	    	    	    	    
      trigFired = true;
      FiredTrigs_->Fill(i);
      
     for(int j_Trig = 0; j_Trig<n_Triggers; ++j_Trig){    
       if(!trigResults.product()->accept(j_Trig)) continue;         
        for(int j = 0; j<n_TrigPaths; j++){
	  if(!(trigName.triggerName(j_Trig)== hltPaths_L3_[j])) continue;
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

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( TriggerAnalyzer );
