#include "TopAnalysis/TopFilter/plugins/DiLeptonFilter.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

/// default constructor
DiLeptonFilter::DiLeptonFilter(const edm::ParameterSet& cfg):
  electrons_ (cfg.getParameter<edm::InputTag>(       "electrons"    )),
  muons_     (cfg.getParameter<edm::InputTag>(       "muons"        )),
  isVeto_    (cfg.getParameter<bool>(                "isVeto"       )),
  Cut_       (cfg.getParameter<std::vector<double> >("Cut"          )),
  fltrChrg_  (cfg.getParameter<int> (                "filterCharge" ))
{

  produces<std::vector<pat::Electron> >();
  produces<std::vector<pat::Muon> >();

}

/// default destructor
DiLeptonFilter::~DiLeptonFilter()
{
}

/// sanity check
void
DiLeptonFilter::beginJob()
{
  if(Cut_.size()!=2)  edm::LogError("DiLeptonFilter") << "Cut has wrong size. Size has to be 2!\n";
  if(Cut_[0]>Cut_[1]) edm::LogError("DiLeptonFilter") << "Lower cut value is higher than upper one!\n";
}

/// event veto
bool
DiLeptonFilter::filter(edm::Event& event, const edm::EventSetup& setup)
{
  // fetch the input collections from the event content
  edm::Handle<std::vector<pat::Electron> > electrons;
  event.getByLabel(electrons_, electrons);

  edm::Handle<std::vector<pat::Muon> > muons;
  event.getByLabel(muons_, muons);


  // skip events with less than 2 leptons
  if(electrons->size() + muons->size() < 2) return false;


  // prepare result vectors
  std::auto_ptr<std::vector<pat::Electron> > selectedElectrons(new std::vector<pat::Electron>);
  std::auto_ptr<std::vector<pat::Muon> > selectedMuons(new std::vector<pat::Muon>);


  std::vector<pat::Electron>::const_iterator electronIter = (*electrons).begin();
  std::vector<pat::Muon>::const_iterator muonIter = (*muons).begin();

  int firstCharge = 0;
  std::vector<reco::Particle::LorentzVector> lVecs;

  while (    ( lVecs.size() < 2 )
             && ( electronIter != (*electrons).end() || muonIter != (*muons).end() ) ) {

    bool useElectron = false;

    if ( electronIter != (*electrons).end() && muonIter != (*muons).end() ) { // we have both electrons and muons

      if ( electronIter->pt() > muonIter->pt() )  useElectron = true;

    }
    else if ( electronIter != (*electrons).end() ) useElectron = true;   // we have only electrons (left)


    if (useElectron) {

      if (lVecs.size() == 0) { // first lepton
        firstCharge = electronIter->charge();
        lVecs.push_back( electronIter->p4() );
        selectedElectrons->push_back(*electronIter);
      }
      else if ( fltrChrg_ == 0 ||  electronIter->charge() * firstCharge == fltrChrg_ )  { // further leptons
        lVecs.push_back( electronIter->p4() );
        selectedElectrons->push_back(*electronIter);
      }

      ++electronIter;

    }
    else {
      if (lVecs.size() == 0) { // first lepton
        firstCharge = muonIter->charge();
        lVecs.push_back( muonIter->p4() );
        selectedMuons->push_back(*muonIter);
      }
      else if ( fltrChrg_ == 0 || muonIter->charge() * firstCharge == fltrChrg_ ) { // further leptons
        lVecs.push_back( muonIter->p4() );
        selectedMuons->push_back(*muonIter);
      }

      ++muonIter;
    }

  }

  if ( lVecs.size() < 2 ) return false; // no two leptons of right charge pairing found


  // reconstruct invariant mass of lepton pair
  reco::Particle::LorentzVector diLepton = lVecs[0] + lVecs[1];
  double diLeptonMass = sqrt( diLepton.Dot(diLepton) );

  // check if events in mass window are to be selected or vetoed
  if( isVeto_ ) {
    if  (diLeptonMass >= Cut_[0] && diLeptonMass <= Cut_[1]) return false;
  }
  else if( diLeptonMass < Cut_[0] || diLeptonMass > Cut_[1]) return false;

  event.put(selectedElectrons);
  event.put(selectedMuons);

  return true;
}
