#include "DataFormats/PatCandidates/interface/Muon.h"
#include "TopAnalysis/TopFilter/plugins/DiMuonFilter.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

/// default constructor 
DiMuonFilter::DiMuonFilter(const edm::ParameterSet& cfg):
  muons_    (cfg.getParameter<edm::InputTag>(       "muons"  )),
  isVeto_   (cfg.getParameter<bool>(                "isVeto" )),
  Cut_      (cfg.getParameter<std::vector<double> >("Cut"    )),
  fltrChrg_ (cfg.getParameter<int> (       "filterCharge"    ))  
{
}

/// default destructor
DiMuonFilter::~DiMuonFilter()
{
}

/// sanity check
void 
DiMuonFilter::beginJob()
{ 
  if(Cut_.size()!=2)  edm::LogError("topFilter") << "Cut has wrong size. Size has to be 2!\n";
  if(Cut_[0]>Cut_[1]) edm::LogError("topFilter") << "Lower cut value is higher than upper one!\n";
}

/// event veto
bool
DiMuonFilter::filter(edm::Event& event, const edm::EventSetup& setup)
{   
  // fetch the input collection from the event content  
  edm::Handle<std::vector<pat::Muon> > muons;
  event.getByLabel(muons_, muons);
  
  // skip events with less than 2 muons
  if(muons->size()<=1) return false;
  
  // filter on like or unlike sign if configured
  if(fltrChrg_<0 && (*muons)[0].charge()*(*muons)[1].charge()>0)      return false;
  else if(fltrChrg_>0 && (*muons)[0].charge()*(*muons)[1].charge()<0) return false;
  
  // reconstruct invariant mass of leading 2 muons
  reco::Particle::LorentzVector diMuon = (*muons)[0].p4() + (*muons)[1].p4();
  double diMuonMass = sqrt( diMuon.Dot(diMuon) );
    
  // check if events in mass window are to be selected or vetoed
  if(isVeto_){
    if(diMuonMass < Cut_[0] || diMuonMass > Cut_[1]) return true;
    return false;
  }  
  else{ // no veto but selection of mass window
    if(diMuonMass > Cut_[0] && diMuonMass < Cut_[1]) return true;
    return false;  
  }         
}
