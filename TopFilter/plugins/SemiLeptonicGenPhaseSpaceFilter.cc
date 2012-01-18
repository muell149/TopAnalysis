#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "TopAnalysis/TopFilter/plugins/SemiLeptonicGenPhaseSpaceFilter.h"
#include "AnalysisDataFormats/TopObjects/interface/TtSemiLepEvtPartons.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

SemiLeptonicGenPhaseSpaceFilter::SemiLeptonicGenPhaseSpaceFilter(const edm::ParameterSet& cfg):
  src_           ( cfg.getParameter<edm::InputTag>("src"    ) ),
  leptonMinPt_   ( cfg.getParameter<double       >("leptonMinPt") ),
  leptonMaxEta_  ( cfg.getParameter<double       >("leptonMaxEta") ),
  partonMinPt_   ( cfg.getParameter<double       >("partonMinPt") ),
  partonMaxEta_  ( cfg.getParameter<double       >("partonMaxEta") ),
  topMinPt_      ( cfg.getParameter<double       >("topMinPt") ),
  topMaxPt_      ( cfg.getParameter<double       >("topMaxPt") ),
  topMaxY_       ( cfg.getParameter<double       >("topMaxY") ),
  ttbarMinPt_    ( cfg.getParameter<double       >("ttbarMinPt") ),
  ttbarMaxPt_    ( cfg.getParameter<double       >("ttbarMaxPt") ),
  ttbarMaxY_     ( cfg.getParameter<double       >("ttbarMaxY") ),
  decayLevelCuts_( cfg.getParameter<bool         >("decayLevelCuts") ),
  topLevelCuts_  ( cfg.getParameter<bool         >("topLevelCuts") ),
  ttbarLevelCuts_( cfg.getParameter<bool         >("ttbarLevelCuts") )
{
}

bool SemiLeptonicGenPhaseSpaceFilter::filter(edm::Event& event, const edm::EventSetup& setup)
{

  edm::Handle<TtGenEvent> src;
  event.getByLabel(src_, src);
  
  const TtGenEvent& tops = *src;

  /// tops
  const reco::GenParticle *lepTop= tops.leptonicDecayTop();
  const reco::GenParticle *hadTop= tops.hadronicDecayTop();
  //const reco::GenParticle *lepW  = tops.leptonicDecayW();
  //const reco::GenParticle *hadW  = tops.hadronicDecayW();
  //const reco::GenParticle *neutrino = tops.singleNeutrino();
  
  /// create combined ttbar lorentz vector
  reco::Particle::LorentzVector ttbar = hadTop->p4()+lepTop->p4();

  /// top decay products
  const reco::GenParticle *lep   = tops.singleLepton();
  const reco::GenParticle *lepB  = tops.leptonicDecayB(); 
  const reco::GenParticle *hadB  = tops.hadronicDecayB();
  const reco::GenParticle *q     = tops.hadronicDecayQuark();
  const reco::GenParticle *qbar  = tops.hadronicDecayQuarkBar();
  
//   std::cout<<"lepPt ="<< lep->pt()<<"; lepEta ="<<lep->eta()<<"; lepBPt="<<lepB->pt()<<"; lepBEta="<<lepB->eta()
//       <<"; hadBPt="<<hadB->pt()<<"; hadBEta="<<hadB->eta()
//       <<"; qPt = "<<q->pt()<<"; qEta=" << q->eta()<<"; qbarPt = "<<qbar->pt()<<"; qbarEta=" << qbar->eta()
//   <<std::endl;

  /// tau->lepton events 
  // decay chain is: tau(status 3)->tau(status 2)->e/mu(status 1)
  reco::GenParticle *lep2 = (reco::GenParticle *) tops.singleLepton();
  if(tops.isSemiLeptonic(WDecay::kTau)) lep2 = getFinalStateLepton(*lep);

  if(decayLevelCuts_){
    /// cut on lepton pt and eta
    if(lep2->pt()  < leptonMinPt_ || std::abs(lep2->eta())  > leptonMaxEta_)   return false;
    /// cut on b quark pt and eta 
    if(lepB->pt() < partonMinPt_ || std::abs(lepB->eta()) > partonMaxEta_ ||
      hadB->pt() < partonMinPt_ || std::abs(hadB->eta()) > partonMaxEta_)   return false;
    /// cut on light quark pt and eta
    if(q->pt()    < partonMinPt_ || std::abs(q->eta())    > partonMaxEta_ ||
      qbar->pt() < partonMinPt_ || std::abs(qbar->eta()) > partonMaxEta_)   return false;
  }
  
  if(topLevelCuts_){
    /// cut on top pt and Y
    if(lepTop->pt() < topMinPt_ || lepTop->pt() > topMaxPt_ || std::abs(lepTop->rapidity()) > topMaxY_ ||
       hadTop->pt() < topMinPt_ || hadTop->pt() > topMaxPt_ || std::abs(hadTop->rapidity()) > topMaxY_ ) return false;
  }
  
  if(ttbarLevelCuts_){
    /// cut on ttbar pt and Y
    if(ttbar.pt() < ttbarMinPt_ || ttbar.pt() > ttbarMaxPt_ || std::abs(ttbar.Rapidity()) > ttbarMaxY_) return false;
  }
  
  /// if all cuts are passed: return true
  return true;
}

void SemiLeptonicGenPhaseSpaceFilter::beginJob()
{
}

void SemiLeptonicGenPhaseSpaceFilter::endJob()
{
}

reco::GenParticle* SemiLeptonicGenPhaseSpaceFilter::getFinalStateLepton(const reco::GenParticle& particle){
  //std::cout << "getFinalStateLepton called!" << std::endl;
  //std::cout << "which has " << particle.numberOfDaughters() << " daughters" << std::endl; 
  // loop daughters
  for(unsigned int i=0; i<particle.numberOfDaughters(); ++i){
    //std::cout << "daughter #" << i << std::endl;
    reco::GenParticle *daughter = (reco::GenParticle *) particle.daughter(i);
    //std::cout << daughter << std::endl;
    if(daughter){
      int ID=daughter->pdgId();
      //std::cout << "ID: " << ID << ", status: " << daughter->status() << std::endl;
      // if daughter is tau
      if(ID==15||ID==-15){
	//std::cout << "tau daughter found!" << std::endl;
	// bubble up
	return getFinalStateLepton(*daughter);
      }
      // if daughter is muon or electron return
      if(ID==-13||ID==13||ID==-11||ID==11){
	//std::cout << "e/#mu found!" << std::endl;
	return daughter;
      }
    }
  }
  return 0;
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( SemiLeptonicGenPhaseSpaceFilter );
