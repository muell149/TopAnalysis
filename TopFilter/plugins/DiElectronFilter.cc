#include "DataFormats/PatCandidates/interface/Electron.h"
#include "TopAnalysis/TopFilter/plugins/DiElectronFilter.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

/// default constructor 
DiElectronFilter::DiElectronFilter(const edm::ParameterSet& cfg):
  electrons_    (cfg.getParameter<edm::InputTag>(       "electrons"  )),
  isVeto_   (cfg.getParameter<bool>(                "isVeto" )),
  Cut_      (cfg.getParameter<std::vector<double> >("Cut"    )),
  fltrChrg_ (cfg.getParameter<int> (       "filterCharge"    ))  
{
}

/// default destructor
DiElectronFilter::~DiElectronFilter()
{
}

/// sanity check
void 
DiElectronFilter::beginJob()
{ 
  if(Cut_.size()!=2)  edm::LogError("topFilter") << "Cut has wrong size. Size has to be 2!\n";
  if(Cut_[0]>Cut_[1]) edm::LogError("topFilter") << "Lower cut value is higher than upper one!\n";
}

/// event veto
bool
DiElectronFilter::filter(edm::Event& event, const edm::EventSetup& setup)
{   
  // fetch the input collection from the event content  
  edm::Handle<std::vector<pat::Electron> > electrons;
  event.getByLabel(electrons_, electrons);
  
  // skip events with less than 2 electrons
  if(electrons->size()<=1) return false;
  
  // filter on like or unlike sign if configured
  if(fltrChrg_<0 && (*electrons)[0].charge()*(*electrons)[1].charge()>0)      return false;
  else if(fltrChrg_>0 && (*electrons)[0].charge()*(*electrons)[1].charge()<0) return false;
  
  // reconstruct invariant mass of leading 2 electrons
  reco::Particle::LorentzVector diElectron = (*electrons)[0].p4() + (*electrons)[1].p4();
  double diElectronMass = sqrt( diElectron.Dot(diElectron) );
    
  // check if events in mass window are to be selected or vetoed
  if(isVeto_){
    if(diElectronMass < Cut_[0] || diElectronMass > Cut_[1]) return true;
    return false;
  }  
  else{ // no veto but selection of mass window
    if(diElectronMass > Cut_[0] && diElectronMass < Cut_[1]) return true;
    return false;  
  }         
}
