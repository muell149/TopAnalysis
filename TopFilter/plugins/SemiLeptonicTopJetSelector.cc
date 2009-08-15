#include "FWCore/Utilities/interface/EDMException.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "AnalysisDataFormats/TopObjects/interface/TtSemiLeptonicEvent.h"
#include "AnalysisDataFormats/TopObjects/interface/TtSemiLepEvtPartons.h"

#include "TopAnalysis/TopFilter/plugins/SemiLeptonicTopJetSelector.h"

/// default constructor
SemiLeptonicTopJetSelector::SemiLeptonicTopJetSelector(const edm::ParameterSet& cfg):
  src_( cfg.getParameter<edm::InputTag>("src") ),
  genMatch_ ( cfg.getParameter<edm::InputTag>("generatorMatch" ) ),
  topEvent_ ( cfg.getParameter<edm::InputTag>("ttSemiLeptonicEvent") ),
  hypoKey_  ( cfg.getParameter<std::string>("hypoKey") ),
  jetType_  ( cfg.getParameter<std::string>("jetType") ),
  partOfHyp_( cfg.getParameter<bool>("partOfTheHypothesis") )
{
  if( !(jetType_.compare("bJet")==0 || jetType_.compare("lightQuark")==0 || jetType_.compare("all")==0) ){
    throw cms::Exception("UnknownParamerterValue") 
      << "Parameter jetType specified with unknown type '" << jetType_ << "'. Available types are 'bJet', 'lightQuark', 'all'.";
  }
  // register selected jet collection on reconstruction level
  produces<std::vector<pat::Jet> >();
  // register selected jet collection on generator level 
  produces<std::vector<pat::Jet> >("gen");
}

/// default destructor
SemiLeptonicTopJetSelector::~SemiLeptonicTopJetSelector()
{
}

/// produce selected muon collections
void
SemiLeptonicTopJetSelector::produce(edm::Event& event, const edm::EventSetup& setup)
{
  // fetch the input collection from the event content
  edm::Handle<std::vector<pat::Jet> > jets; 
  event.getByLabel(src_, jets);

  // fetch TtSemiLeptonicEvent from the event content
  edm::Handle<TtSemiLeptonicEvent> tops; 
  event.getByLabel(topEvent_, tops);

  // fetch TtSemiLeptonicEvent from the event content
  edm::Handle<std::vector<std::vector<int> > > match; 
  event.getByLabel(genMatch_, match);

  // declare output vectors
  std::auto_ptr<std::vector<pat::Jet> > recJets(new std::vector<pat::Jet>);  
  std::auto_ptr<std::vector<pat::Jet> > genJets(new std::vector<pat::Jet>);  

  unsigned int idx=0;
  for(std::vector<pat::Jet>::const_iterator jet=jets->begin(); jet!=jets->end(); ++jet, ++idx){
    // add match on reconstruction level from TtSemiLeptonicEvent (if it exists)
    if( tops->isHypoValid(hypoKey_) ){
      if( pushElement(idx, tops->jetLeptonCombination(hypoKey_)) ) recJets->push_back(*jet);
    }
    // add match on generator level from TtSemiLeptonicEvent (if it exists)
    if( tops->genEvent()->isSemiLeptonic(WDecay::kMuon) && !match->empty() ){
      if( pushElement(idx, match->front()) ) genJets->push_back(*jet);
    }
  }
  // write the selected collections to the event  
  event.put(recJets);  
  event.put(genJets, "gen");  
}

/// helper function to decide whether the element should be pushed or not
bool
SemiLeptonicTopJetSelector::pushElement(const int& idx, const std::vector<int>& match)
{
  bool push = false;
  if( jetType_.compare("bJet")==0 || jetType_.compare("all")==0 ){
    if(idx == match[TtSemiLepEvtPartons::HadB] ) push = partOfHyp_;
    if(idx == match[TtSemiLepEvtPartons::LepB] ) push = partOfHyp_;
  }
  if( jetType_.compare("lighQuark")==0 || jetType_.compare("all")==0 ){
    if(idx == match[TtSemiLepEvtPartons::LightQ] ) push = partOfHyp_;
    if(idx == match[TtSemiLepEvtPartons::LightQBar] ) push = partOfHyp_;
  }
  return push;
}
