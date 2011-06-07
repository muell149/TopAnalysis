#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "TopAnalysis/TopFilter/plugins/SecondElectronFilter.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include <vector>
using namespace std;



/// default constructor
SecondElectronFilter::SecondElectronFilter(const edm::ParameterSet& cfg):
  elecsTight_ (cfg.getParameter<edm::InputTag>(        "elecsTight" )),
  elecsLoose_ (cfg.getParameter<edm::InputTag>(        "elecsLoose" )),
  massWindow_ (cfg.getParameter<std::vector<double> >( "massWindow" ))
{
}



/// default destructor
SecondElectronFilter::~SecondElectronFilter()
{
}



/// sanity check
void SecondElectronFilter::beginJob() {

  if( massWindow_.size() != 2         ) edm::LogError("filterSecondElectron") << "Mass window incorrectly defined; has to contain exactly 2 values!\n"            ;
  if( massWindow_[0] > massWindow_[1] ) edm::LogError("filterSecondElectron") << "Mass window incorrectly defined; minimum value is higher than maximum value!\n" ;

}



/// event veto
bool SecondElectronFilter::filter(edm::Event& event, const edm::EventSetup& setup) {

  edm::Handle<std::vector<pat::Electron> > elecsTight ; event.getByLabel(elecsTight_, elecsTight);
  edm::Handle<std::vector<pat::Electron> > elecsLoose ; event.getByLabel(elecsLoose_, elecsLoose);

  /// check if we have indeed only 1 tight (isolated) electron after selection
  if (elecsTight->size() != 1) edm::LogError("filterSecondElectron") << "Number of tight electrons is not 1; check selection criteria!\n" ;
 
  /// check all loose electrons against the isolated one
  for (unsigned int i = 0; i < elecsLoose->size(); i++ ) {
 
    /// check that the loose one is not just the same electron that also passed the tight criteria
    if ( (*elecsTight)[0].p4() != (*elecsLoose)[i].p4() ) {
 
      /// check the invariant mass 
      reco::Particle::LorentzVector diElectron = (*elecsTight)[0].p4() + (*elecsLoose)[i].p4() ;
      double diElectronMass = sqrt( diElectron.Dot( diElectron ) ) ; 

      /// veto event if in mass window
      if ( (diElectronMass > massWindow_[0]) && (diElectronMass < massWindow_[1]) ) return false ;

    }

  }

  return true;

}
