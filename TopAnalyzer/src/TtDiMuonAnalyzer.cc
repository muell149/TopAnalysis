#include "TopAnalysis/TopAnalyzer/interface/TtDiMuonAnalyzer.h"
#include "TopAnalysis/TopUtils/interface/NameScheme.h"

TtDiMuonAnalyzer::TtDiMuonAnalyzer(const edm::ParameterSet& cfg):
  hist_            ( cfg.getParameter<std::string>  ( "hist"             ) ),
  doTopObj_        ( cfg.getParameter<bool>         ( "show_Top_Objects" ) ),   
  doGenEvt_        ( cfg.getParameter<bool>         ( "show_Gen_Event"   ) ),      
  doKin_           ( cfg.getParameter<bool>         ( "show_Kin_Solution") ),  
  doKinFit_        ( cfg.getParameter<bool>         ( "fit_Top_Mass"     ) )
{
  if(doTopObj_)  obj_ = new TtDiMuonTopObjAna(cfg);
  if(doGenEvt_)  gen_ = new TtDiMuonGenEvtAna(cfg);
  if(doKin_   )  kin_ = new TtDiMuonKinSolAna(cfg);
}


TtDiMuonAnalyzer::~TtDiMuonAnalyzer()
{
  if(doTopObj_) delete obj_;
  if(doGenEvt_) delete gen_;
  if(doKin_   ) delete kin_;      
}


void
TtDiMuonAnalyzer::analyze(const edm::Event& evt, const edm::EventSetup& setup)
{  
  double weight = 1.;
  
  edm::Handle<double> weightHandle; 
  evt.getByLabel("eventWeight", weightHandle); 
  weight = *weightHandle;
  
  //std::cout << "weight = " << weight << std::endl;
  
  if(doTopObj_) obj_->fill(evt, weight);   
  if(doGenEvt_) gen_->fill(evt, weight);      
  if(doKin_)    kin_->fill(evt, weight);    
}


void 
TtDiMuonAnalyzer::beginJob(const edm::EventSetup&)
{
  if( hist_.empty() )
    return;

  edm::Service<TFileService> fs;
  if( !fs ){
    throw edm::Exception( edm::errors::Configuration,
                          "TFile Service is not registered in cfg file" );
  }

  ofstream hist(hist_.c_str(), std::ios::out);
  
  if( doTopObj_)  obj_ ->book(hist);  
  if( doGenEvt_)  gen_ ->book(hist);
  if(doKin_    )  kin_ ->book(hist);
}


void 
TtDiMuonAnalyzer::endJob() 
{
  if( doGenEvt_          )  gen_->normSpectrum();
  if( doKin_ && doKinFit_)  kin_->fithists();
}

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_ANOTHER_FWK_MODULE( TtDiMuonAnalyzer );
