#include "TLorentzVector.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "TopAnalysis/TopFilter/plugins/FullLepHypothesesFilter.h"

FullLepHypothesesFilter::FullLepHypothesesFilter(const edm::ParameterSet& cfg):
  hypoKey_    (cfg.getParameter<edm::InputTag>(       "hypoKey"        )),
  FullLepEvt_ (cfg.getParameter<edm::InputTag>(       "FullLepEvent"   )),
  jets_       (cfg.getParameter<edm::InputTag>(       "jets"           )),         
  bAlgo_      (cfg.getParameter<std::string >(        "bAlgorithm"     )),  
  bDisc_      (cfg.getParameter<std::vector<double> >("bDiscriminator" ))
{
}

bool FullLepHypothesesFilter::filter(edm::Event& evt, const edm::EventSetup& setup)
{
  edm::Handle<TtFullLeptonicEvent> FullLepEvt;
  evt.getByLabel(FullLepEvt_, FullLepEvt);

  edm::Handle<int> hypoKeyHandle;
  evt.getByLabel(hypoKey_, hypoKeyHandle);
  TtEvent::HypoClassKey& hypoKey = (TtEvent::HypoClassKey&) *hypoKeyHandle;
 
  edm::Handle<std::vector<pat::Jet> > jets; 
  evt.getByLabel(jets_, jets);   

  // -----------------------
  // check if hypothesis is valid in this event
  // and if it satisfies some quality criteria
  // -----------------------
         
  if( !FullLepEvt->isHypoAvailable(hypoKey) ){
    edm::LogInfo ( "NonValidHyp" ) << "Hypothesis not available for this event";
    return false;
  }
  if( !FullLepEvt->isHypoValid(hypoKey) ){
    edm::LogInfo ( "NonValidHyp" ) << "Hypothesis not valid for this event";
    return false; 
  }
  
  int bJetIdx    = FullLepEvt->jetLeptonCombination(hypoKey)[0];
  int bBarJetIdx = FullLepEvt->jetLeptonCombination(hypoKey)[1];  

  const pat::Jet B    = jets->at(bJetIdx);   
  const pat::Jet BBar = jets->at(bBarJetIdx);   
 
  // make cut(s) on b-tag discriminator
  if(bDisc_.size()==1){
    if(!(B.bDiscriminator(bAlgo_)>=bDisc_[0] || BBar.bDiscriminator(bAlgo_)>=bDisc_[0])) return false;
  }
  else if(bDisc_.size()==2){
    if((B.bDiscriminator(bAlgo_)<bDisc_[0] || BBar.bDiscriminator(bAlgo_)<bDisc_[1]) 
      && (B.bDiscriminator(bAlgo_)<bDisc_[1] || BBar.bDiscriminator(bAlgo_)<bDisc_[0])) return false;
  } 
  
  edm::LogInfo log( "FullLepJets" );
  log << "-------------------------------------------\n";
  log << "   pt1 = " << B.pt()                   << "\n";
  log << "  eta1 = " << B.eta()                  << "\n";
  log << "  phi1 = " << B.phi()                  << "\n";
  log << "b-tag1 = " << B.bDiscriminator(bAlgo_) << "\n";
  
  log << "   pt2 = " << BBar.pt()                << "\n";
  log << "  eta2 = " << BBar.eta()               << "\n";
  log << "  phi2 = " << BBar.phi()               << "\n";  
  log << "b-tag2 = " << BBar.bDiscriminator(bAlgo_)<< "\n";
  log << "-------------------------------------------\n";

  return true;
}

void FullLepHypothesesFilter::beginJob()
{   
  edm::LogVerbatim log("topFilter");
  log << "ValidityFullLepHyp\n";
  
  for(unsigned int idx=0; idx<bDisc_.size(); ++idx){
    log << ::std::setw( 20 ) << ::std::left;
    if(idx==0) log << "bTagFullLepHyp"; else log << " ";
    log << ": " << "tag >= " <<  bDisc_[idx] << "\n";
  }    
}

void FullLepHypothesesFilter::endJob()
{

}
