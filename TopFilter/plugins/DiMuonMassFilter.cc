#include "DataFormats/PatCandidates/interface/Muon.h"
#include "TopAnalysis/TopFilter/plugins/DiMuonMassFilter.h"

/// default constructor 
DiMuonMassFilter::DiMuonMassFilter(const edm::ParameterSet& cfg):
  muons_(cfg.getParameter<edm::InputTag>("muons"))
{
}

/// default destructor
DiMuonMassFilter::~DiMuonMassFilter()
{
}

/// event veto
bool
DiMuonMassFilter::filter(edm::Event& event, const edm::EventSetup& setup)
{   
  // fetch the input collection from the event content  
  edm::Handle<std::vector<pat::Muon> > muons;
  event.getByLabel(muons_, muons);
  
  bool pass=true;  
  if( muons->size()>1 ){ 
    reco::Particle::LorentzVector diMuon = (*muons)[0].p4() + (*muons)[1].p4();
    double diMuonMass = sqrt( diMuon.Dot(diMuon) );
    if( diMuonMass>84 && diMuonMass<=98 ){ pass=false; }
  }    
  return pass;
}
