#include <memory>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "AnalysisDataFormats/TopObjects/interface/TtGenEvent.h"
#include "TopQuarkAnalysis/TopSkimming/interface/TtDecayChannelSelector.h"

/**
  \class   GeneratorTtDileptonFilter GeneratorTtDileptonFilter.cc "TopAnalysis/TopFilter/plugins/GeneratorTtDileptonFilter.cc"

  \brief   EDFilter to make cuts on generator level particles in dileptonic ttbar events. Should be used in path behind GeneratorTopFilter
*/

using namespace std;

class GeneratorTtDileptonFilter : public edm::EDFilter {
 public:
  /// default constructor
  explicit GeneratorTtDileptonFilter(const edm::ParameterSet&);
  /// default destructor
  ~GeneratorTtDileptonFilter();

 private:
  /// read in which channels are going to be selected and print out
  virtual void beginJob();
  /// the real filtering procedure is implemendted in analyze(), wDecay() and tauDecay()
  virtual bool filter(edm::Event&, const edm::EventSetup&);
  /// gives a summary how many events have been selected
  virtual void endJob();

  /// input
  edm::InputTag src_;

  /// generator level cuts
  double lepPt_;
  double centralLeptonEta_;
  double lepEta_;
  double bPt_;
  double bEta_;
  double met_;
  double invLepLepMass_;
  std::vector<double> zVeto_;

  // mehtod to get lepton from tau
  const reco::Candidate* getTauDaughter(const reco::Candidate*);
};


GeneratorTtDileptonFilter::GeneratorTtDileptonFilter(const edm::ParameterSet& cfg) :
  src_             (cfg.getParameter<edm::InputTag>("src"           )),
  lepPt_           (cfg.getParameter<double>( "leptonPt"	    )),
  centralLeptonEta_(cfg.getParameter<double>( "centralLeptonEta"    )),
  lepEta_	   (cfg.getParameter<double>( "leptonEta"	    )),
  bPt_ 	           (cfg.getParameter<double>( "bPt"	            )),
  bEta_	           (cfg.getParameter<double>( "bEta"	            )),
  met_ 	           (cfg.getParameter<double>( "met"	            )),
  invLepLepMass_   (cfg.getParameter<double>( "invariantLepLepMass" )),
  zVeto_           (cfg.getParameter<std::vector<double> >( "zVeto" ))
{
}


GeneratorTtDileptonFilter::~GeneratorTtDileptonFilter() {
}

bool GeneratorTtDileptonFilter::filter(edm::Event& evt, const edm::EventSetup& es) {

  edm::Handle<TtGenEvent> genEvt;
  evt.getByLabel(src_, genEvt );
  const std::vector<reco::GenParticle> *genParticles = &(genEvt->particles()); 

  const reco::Candidate* topQuark = 0;
  const reco::Candidate* topBarQuark = 0;
  const reco::Candidate* bQuark = 0;
  const reco::Candidate* bBarQuark = 0;
  const reco::Candidate* wPlus = 0;
  const reco::Candidate* wMinus = 0;
  const reco::Candidate* lepton = 0;
  const reco::Candidate* leptonBar = 0;
  const reco::Candidate* nu = 0;
  const reco::Candidate* nuBar = 0;

  // reconstruct ttbar decay chain
  for(reco::GenParticleCollection::const_iterator cand = genParticles->begin(); cand!=genParticles->end(); ++cand) {
    if(abs(cand->pdgId())!=6)         continue;
    if(topQuark!=0 && topBarQuark!=0) break; //stop loop if ttbar pair already found

    if(cand->pdgId()==6){
      topQuark = &(*cand);
      for(size_t i=0; i<topQuark->numberOfDaughters(); ++i){
        if(topQuark->daughter(i)->pdgId()==5){
	  bQuark = topQuark->daughter(i);
        }
        else if(topQuark->daughter(i)->pdgId()==24){
	  wPlus = topQuark->daughter(i);
        }
      }
    }
    if(wPlus!=0){
      for(size_t i=0; i<wPlus->numberOfDaughters(); ++i){
        if(wPlus->daughter(i)->pdgId()==-11 || wPlus->daughter(i)->pdgId()==-13){
	  leptonBar = wPlus->daughter(i);
	}
        else if(wPlus->daughter(i)->pdgId()==-15){
          leptonBar = getTauDaughter(wPlus->daughter(i));
	}
        else if(wPlus->daughter(i)->pdgId()==12 || wPlus->daughter(i)->pdgId()==14 || wPlus->daughter(i)->pdgId()==16){
	  nu = wPlus->daughter(i);
	}
      }
    }

    if(cand->pdgId()==-6){
      topBarQuark = &(*cand);
      for(size_t i=0; i<topBarQuark->numberOfDaughters(); ++i){
        if(topBarQuark->daughter(i)->pdgId()==-5){
	  bBarQuark = topBarQuark->daughter(i);
        }
        else if(topBarQuark->daughter(i)->pdgId()==-24){
	  wMinus = topBarQuark->daughter(i);
        }
      }
    }
    if(wMinus!=0){
      for(size_t i=0; i<wMinus->numberOfDaughters(); ++i){
        if(wMinus->daughter(i)->pdgId()==11 || wMinus->daughter(i)->pdgId()==13){
	  lepton = wMinus->daughter(i);
	}
        else if(wMinus->daughter(i)->pdgId()==15){
          lepton = getTauDaughter(wMinus->daughter(i));
	}
        else if(wMinus->daughter(i)->pdgId()==-12 || wMinus->daughter(i)->pdgId()==-14 || wMinus->daughter(i)->pdgId()==-16){
	  nuBar = wMinus->daughter(i);
	}
      }
    }
  }

  // test for dileptons
  if(bQuark==0){
    std::cout << "bQuark not found" << std::endl;
    return false;
  }
  if(bBarQuark==0){
    std::cout << "bBarQuark not found" << std::endl;
    return false;
  }
  if(lepton==0){
    std::cout << "lepton not found" << std::endl;
    return false;
  }
  if(leptonBar==0){
    std::cout << "leptonBar not found" << std::endl;
    return false;
  }
  if(nu==0){
    std::cout << "nu not found" << std::endl;
    return false;
  }
  if(nuBar==0){
    std::cout << "nuBar not found" << std::endl;
    return false;
  }

  // apply cuts
  if(lepton ->pt()<lepPt_        || leptonBar->pt()<lepPt_        ) return false;
  if(fabs(lepton->eta())>lepEta_ || fabs(leptonBar->eta())>lepEta_) return false;
  if(bQuark ->pt()<bPt_          || bBarQuark->pt()<bPt_        )  return false;
  if(fabs(bQuark->eta())>bEta_   || fabs(bBarQuark->eta())>bEta_) return false;
  if(fabs(lepton->eta()) > centralLeptonEta_ && fabs(leptonBar->eta()) > centralLeptonEta_) return false;  
  
  // calculate generated MET from neutrinos
  double x = (nu->momentum()+nuBar->momentum()).x();
  double y = (nu->momentum()+nuBar->momentum()).y();
  double genMET = sqrt(x*x+y*y);

  if(genMET<met_) return false;

  // calculate invariant mass of lepton pair
  reco::Particle::LorentzVector diLepP4 = lepton->p4() + leptonBar->p4();
  double dilepMass = sqrt( diLepP4.Dot(diLepP4) );

  if(dilepMass<invLepLepMass_) return false;

  if(dilepMass>zVeto_[0] && dilepMass<zVeto_[1]) return false;

  return true;
}


void GeneratorTtDileptonFilter::beginJob()
{
}

void GeneratorTtDileptonFilter::endJob()
{
}


const reco::Candidate*
GeneratorTtDileptonFilter::getTauDaughter(const reco::Candidate* tau)
{
  for(size_t i=0; i<tau->numberOfDaughters(); ++i){
    if(fabs(tau->daughter(i)->pdgId())==11 || fabs(tau->daughter(i)->pdgId())==13) return tau->daughter(i);
    else if(fabs(tau->daughter(i)->pdgId())==15) return getTauDaughter(tau->daughter(i));
  }
  //return orgiginal tau if nothing found
  edm::LogWarning ( "No Tau Daughter" ) << "neither electron nor muon daughter found.";  
  return tau;
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(GeneratorTtDileptonFilter);
