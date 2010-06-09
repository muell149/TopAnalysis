#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

#include "TopAnalysis/TopFilter/plugins/MuonJetOverlapSelector.h"

/// default constructor
MuonJetOverlapSelector::MuonJetOverlapSelector(const edm::ParameterSet& cfg):
  muons_( cfg.getParameter<edm::InputTag>("muons") ),
  jets_( cfg.getParameter<edm::InputTag>("jets") ),
  deltaR_ ( cfg.getParameter<double>("deltaR") ),
  overlap_( cfg.getParameter<bool>("overlap") )
{
  // register selected muon collection
  produces<std::vector<pat::Muon> >();
}

/// default destructor
MuonJetOverlapSelector::~MuonJetOverlapSelector()
{
}

/// produce selected muon collections
void
MuonJetOverlapSelector::produce(edm::Event& event, const edm::EventSetup& setup)
{
  // fetch the input collection from the event content
  edm::Handle<std::vector<pat::Muon> > muons; 
  event.getByLabel(muons_, muons);

  // fetch the input collection from the event content
  edm::Handle<std::vector<pat::Jet> > jets; 
  event.getByLabel(jets_, jets);

  // declare output vector
  std::auto_ptr<std::vector<pat::Muon> > outMuons(new std::vector<pat::Muon>);  

  for(std::vector<pat::Muon>::const_iterator muon=muons->begin(); muon!=muons->end(); ++muon){
    double minDR = 1000.;
    for(std::vector<pat::Jet>::const_iterator jet=jets->begin(); jet!=jets->end(); ++jet){
      double dR = deltaR<const pat::Muon, const pat::Jet>(*muon, *jet); 
      if( dR<minDR )minDR = dR;
    }
    if( pushElement(minDR) ){
      outMuons->push_back(*muon);
    }
  }
  // write the selected collection to the event  
  event.put(outMuons);  
}
