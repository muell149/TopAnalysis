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
    /// return Higgs sisters
    std::vector<const reco::GenParticle*> higgsSisters() const;

    
    /// get candidate with given pdg id if available; 0 else 
    const reco::GenParticle* candidate(int id, unsigned int parentId=0) const;
    /// return tau if available; 0 else
    const reco::GenParticle* tauMinus() const { return candidate(15, 25);}
    /// return anti-tau if available; 0 else
    const reco::GenParticle* tauPlus() const  { return candidate(-15, 25);}
    /// return W minus if available; 0 else
    const reco::GenParticle* wMinus() const   { return candidate(-24, 25);}
    /// return W plus if available; 0 else
    const reco::GenParticle* wPlus() const    { return candidate( 24, 25);}
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
