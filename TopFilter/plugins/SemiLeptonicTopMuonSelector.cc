#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "AnalysisDataFormats/TopObjects/interface/TtSemiLeptonicEvent.h"
#include "AnalysisDataFormats/TopObjects/interface/TtSemiLepEvtPartons.h"

#include "TopAnalysis/TopFilter/plugins/SemiLeptonicTopMuonSelector.h"

/// default constructor
SemiLeptonicTopMuonSelector::SemiLeptonicTopMuonSelector(const edm::ParameterSet& cfg):
  src_( cfg.getParameter<edm::InputTag>("src") ),
  topEvent_( cfg.getParameter<edm::InputTag>("ttSemiLeptonicEvent") ),
  hypoKey_ ( cfg.getParameter<std::string>("hypoKey") )
{
  // register selected muon collection on reconstruction level
  produces<std::vector<pat::Muon> >();
  // register selected muon collection on generator level 
  produces<std::vector<pat::Muon> >("gen");
}

/// default destructor
SemiLeptonicTopMuonSelector::~SemiLeptonicTopMuonSelector()
{
}

/// produce selected muon collections
void
SemiLeptonicTopMuonSelector::produce(edm::Event& event, const edm::EventSetup& setup)
{
  // fetch the input collection from the event content
  edm::Handle<std::vector<pat::Muon> > muons; 
  event.getByLabel(src_, muons);

  // fetch TtSemiLeptonicEvent from the event content
  edm::Handle<TtSemiLeptonicEvent> tops; 
  event.getByLabel(topEvent_, tops);

  // declare output vectors
  std::auto_ptr<std::vector<pat::Muon> > recMuon(new std::vector<pat::Muon>);  
  std::auto_ptr<std::vector<pat::Muon> > genMuon(new std::vector<pat::Muon>);  

  // add match on reconstruction level from TtSemiLeptonicEvent (if it exists)
  if( tops->isHypoValid(hypoKey_) ){
    int index = tops->jetLeptonCombination(hypoKey_)[TtSemiLepEvtPartons::Lepton];
    if( index<= (int)muons->size() ){ recMuon->push_back( (*muons)[index] ); }
  }
  // add match on generator level from TtSemiLeptonicEvent (if it exists)
  if( tops->genEvent()->isSemiLeptonic(WDecay::kMuon) ){
    int index = -1;
    double minDR = -1.;
    for(unsigned int i=0; i<muons->size(); ++i){
      double dR = deltaR<const pat::Muon, const reco::GenParticle>( (*muons)[i], *tops->singleLepton() ); 
      if( minDR<0 || dR<minDR ){ minDR = dR; index = i; }
    }
    if(index>=0){ genMuon->push_back( (*muons)[index] ); }
  }  
  // write the selected collections to the event
  event.put(recMuon);  
  event.put(genMuon, "gen");  
}
