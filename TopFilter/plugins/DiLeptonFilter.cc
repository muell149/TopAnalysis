#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "TopAnalysis/TopFilter/plugins/DiLeptonFilter.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include <vector>
using namespace std;

/// default constructor

DiLeptonFilter::DiLeptonFilter(const edm::ParameterSet& cfg):
  muons_    (cfg.getParameter<edm::InputTag>( "muons"     )),
  elecs_    (cfg.getParameter<edm::InputTag>( "elecs"     )),
  isVeto_   (cfg.getParameter<bool>(          "isVeto"    )),
  Cut_      (cfg.getParameter<std::vector<double> >("Cut" )),
  fltrChrg_ (cfg.getParameter<int> (       "filterCharge" ))
{
}

/// default destructor
DiLeptonFilter::~DiLeptonFilter()
{
}

/// sanity check
void
DiLeptonFilter::beginJob() {

  if( Cut_.size() != 2  ) edm::LogError("topFilter") << "Cut has wrong size. Size has to be 2!\n";
  if( Cut_[0] > Cut_[1] ) edm::LogError("topFilter") << "Lower cut value is higher than upper one!\n";

}

/// event veto
bool
DiLeptonFilter::filter(edm::Event& event, const edm::EventSetup& setup) {

  edm::Handle<std::vector<pat::Muon> > muons;
  event.getByLabel(muons_, muons);

  edm::Handle<std::vector<pat::Electron> > elecs;
  event.getByLabel(elecs_, elecs);

  // skip events with less than 2 leptons
  if( ( muons->size() + elecs->size() ) <= 1 ) return false;

  //  cout << "N_muons : " << muons->size() << endl;
  //  cout << "N_elecs : " << elecs->size() << endl;

  //  vector<reco::RecoCandidate> lepts;
  reco::CandidateCollection lepts;

  // Di-muon case

  if( muons->size() > 1 && elecs->size() == 0 ) {

    lepts.push_back( (*muons)[0] );
    lepts.push_back( (*muons)[1] );

  }

  // Di-electron case

  if( elecs->size() > 1 && muons->size() == 0 ) {

    lepts.push_back( (*elecs)[0] );
    lepts.push_back( (*elecs)[1] );

  }

  if( elecs->size() > 0 && muons->size() > 0 ) {

    // Muon-electron case

    if( muons->size() == 1 && elecs->size() == 1 ) {

      lepts.push_back( (*muons)[0] );
      lepts.push_back( (*elecs)[0] );

    }

    // Tri-lepton case

    if( elecs->size() == 1 && muons->size() > 1 ) {

      if( (*muons)[1].pt() > (*elecs)[0].pt() ) {

	lepts.push_back( (*muons)[0] );
	lepts.push_back( (*muons)[1] );

      }

      else {

	lepts.push_back( (*muons)[0] );
	lepts.push_back( (*elecs)[0] );

      }

    }


    if( muons->size() == 1 && elecs->size() > 1 ) {

      if( (*elecs)[1].pt() > (*muons)[0].pt() ) {

	lepts.push_back( (*elecs)[0] );
	lepts.push_back( (*elecs)[1] );

      }

      else {

	lepts.push_back( (*muons)[0] );
	lepts.push_back( (*elecs)[0] );

      }

    }

    // Multi-lepton case

    if( elecs->size() > 1 && muons->size() > 1 ) {

      if( (*muons)[1].pt() > (*elecs)[0].pt() ) {

	lepts.push_back( (*muons)[0] );
	lepts.push_back( (*muons)[1] );

      }

      if( (*elecs)[1].pt() > (*muons)[0].pt() ) {

	lepts.push_back( (*elecs)[0] );
	lepts.push_back( (*elecs)[1] );

      }

      if( (*muons)[1].pt() < (*elecs)[0].pt() && (*elecs)[1].pt() < (*muons)[0].pt() ) {

	lepts.push_back( (*muons)[0] );
	lepts.push_back( (*elecs)[0] );

      }

    }

  }

  //  cout << "N_lepts : " << lepts.size() << endl << endl;

  if( lepts.size() != 2 )  cout << "!!!!ALAAAAAARM!!! N_lepts : " << lepts.size() << endl << endl;

  if( lepts.size() > 1 ) {

    // filter on like or unlike sign if configured
    if(      fltrChrg_ < 0 && lepts[0].charge() * lepts[1].charge() > 0 ) return false;
    else if( fltrChrg_ > 0 && lepts[0].charge() * lepts[1].charge() < 0 ) return false;
  
    // reconstruct invariant mass of leading 2 leptons
    reco::Particle::LorentzVector diLepton = lepts[0].p4() + lepts[1].p4();
    double diLeptonMass = sqrt( diLepton.Dot(diLepton) );
    
    // check if events in mass window are to be selected or vetoed
    if(isVeto_) {

      if(diLeptonMass < Cut_[0] || diLeptonMass > Cut_[1]) return true;
      return false;

    }

    // no veto but selection of mass window
    else {

      if(diLeptonMass > Cut_[0] && diLeptonMass < Cut_[1]) return true;
      return false;  
    }

  }

  else return false;

}
