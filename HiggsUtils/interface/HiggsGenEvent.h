// analog to AnalysisDataFormats/TopObjects/interface/TopGenEvent.h
#ifndef HiggsGenEvent_h
#define HiggsGenEvent_h

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"


class HiggsGenEvent {
  
  public:
    
    /// empty constructor
    HiggsGenEvent(){};
    /// default constructor
    HiggsGenEvent(reco::GenParticleRefProd&);
    /// default destructor
    virtual ~HiggsGenEvent(){};
    
    /// return particles of decay chain
    const reco::GenParticleCollection& particles() const { return *parts_; }
    /// return number of b quarks in the decay chain
    int numberOfBQuarks(bool fromHiggs=true) const;
    
    /// get candidate with given pdg id if available; 0 else 
    const reco::GenParticle* candidate(int id, unsigned int parentId=0) const;
    
    /// return b quark if available; 0 else
    const reco::GenParticle* b() const { return candidate(5, 25);}
    /// return anti-b quark if available; 0 else
    const reco::GenParticle* bBar() const { return candidate(-5, 25);}
    // return Higgs if available; 0 else
    const reco::GenParticle* higgs() const { return candidate(25);}
    
    /// print content of the top decay chain as formated 
    /// LogInfo to the MessageLogger output for debugging
    void print() const;
    
  private:
    
    /// reference to the Higgs decay chain (has to be kept in the event!)
    reco::GenParticleRefProd parts_;
    
};


#endif
