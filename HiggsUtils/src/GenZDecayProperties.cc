#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "TopAnalysis/HiggsUtils/interface/GenZDecayProperties.h"




GenZDecayProperties::GenZDecayProperties():
z_(0),
meDaughterParticle_(0),
meDaughterAntiParticle_(0),
stableLepton_(0),
stableAntiLepton_(0),
decayMode_(-999)
{}


GenZDecayProperties::GenZDecayProperties(const reco::GenParticle* z,
                               const reco::GenParticle* meDaughterParticle, const reco::GenParticle* meDaughterAntiParticle,
                               const reco::GenParticle* stableLepton, const reco::GenParticle* stableAntiLepton,
                               const int decayMode):
z_(z),
meDaughterParticle_(meDaughterParticle),
meDaughterAntiParticle_(meDaughterAntiParticle),
stableLepton_(stableLepton),
stableAntiLepton_(stableAntiLepton),
decayMode_(decayMode)
{}




void
GenZDecayProperties::print()const 
{
    // Values of stable leptons, if existing
    const int l1pdg = stableLepton_ ? stableLepton_->pdgId() : 0;
    const int l1stat = stableLepton_ ? stableLepton_->status() : 0;
    const int l2pdg = stableAntiLepton_ ? stableAntiLepton_->pdgId() : 0;
    const int l2stat = stableAntiLepton_ ? stableAntiLepton_->status() : 0;
    
    edm::LogVerbatim log("GenZDecay");
    log<<"\n"
       <<"--------------------------------------\n"
       <<"- Dump GenZDecay Content             -\n"
       <<"--------------------------------------\n";
    log<<"     Particle (PDG ID, Status)\n";
    log<<"Z:                        "<<z_->pdgId()<<" , "<<z_->status()<<"\n";
    log<<"ME daughter particle:     "<<meDaughterParticle_->pdgId()<<" , "<<meDaughterParticle_->status()<<"\n";
    log<<"ME daughter antiparticle: "<<meDaughterAntiParticle_->pdgId()<<" , "<<meDaughterAntiParticle_->status()<<"\n";
    log<<"Stable lepton:            "<<l1pdg<<" , "<<l1stat<<"\n";
    log<<"Stable antilepton:        "<<l2pdg<<" , "<<l2stat<<"\n";
    log<<"Decay ID:                 "<<decayMode_<<"\n";
}






