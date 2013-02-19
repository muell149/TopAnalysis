#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "TopAnalysis/HiggsUtils/interface/HiggsGenEvent.h"

// default constructor
HiggsGenEvent::HiggsGenEvent(reco::GenParticleRefProd& decaySubset){
  parts_ = decaySubset;
}


int
HiggsGenEvent::numberOfBQuarks(bool fromHiggs) const
{
  int bq=0;
  const reco::GenParticleCollection & partsColl = *parts_;
  for (unsigned int i = 0; i < partsColl.size(); ++i) {
   //depend if radiation qqbar are included or not
    if(std::abs(partsColl[i].pdgId())==5){
      if(fromHiggs){
	if(partsColl[i].mother() &&  partsColl[i].mother()->pdgId()==25){
	  ++bq;
	}
      }
      else{
	++bq;
      }
    }
  }  
  return bq;
}


std::vector<const reco::GenParticle*> 
HiggsGenEvent::higgsSisters() const
{
  std::vector<const reco::GenParticle*> sisters;
  for(reco::GenParticleCollection::const_iterator part = parts_->begin(); part<parts_->end(); ++part){
    // choose Higgs sister which do not have a 
    // mother and are not Higgs itself
    if( part->numberOfMothers()==0 && part->pdgId()!=25){
      if( dynamic_cast<const reco::GenParticle*>( &(*part) ) == 0){
        throw edm::Exception( edm::errors::InvalidReference, "Not a GenParticle" );
      }
      sisters.push_back( part->clone() );
    }
  }  
  return sisters;
}


const reco::GenParticle*
HiggsGenEvent::candidate(int id, unsigned int parentId) const
{
  const reco::GenParticle* cand=0;
  const reco::GenParticleCollection & partsColl = *parts_;
  for( unsigned int i = 0; i < partsColl.size(); ++i ) {
    if( partsColl[i].pdgId()==id ){
      if(parentId==0 ? true : partsColl[i].mother()&&std::abs(partsColl[i].mother()->pdgId())==(int)parentId){
	cand = &partsColl[i];
      }
    }
  }  
  return cand;
}


void
HiggsGenEvent::print() const 
{
  edm::LogVerbatim log("HiggsGenEvent");
  log << "\n"
      << "--------------------------------------\n"
      << "- Dump HiggsGenEvent Content           -\n"
      << "--------------------------------------\n";
  for (reco::GenParticleCollection::const_iterator part = parts_->begin(); 
       part<parts_->end(); ++part) {
    log << "pdgId:"  << std::setw(5)  << part->pdgId()     << ", "
	<< "mass:"   << std::setw(11) << part->p4().mass() << ", "
	<< "energy:" << std::setw(11) << part->energy()    << ", " 
	<< "pt:"     << std::setw(11) << part->pt()        << "\n"; 
  }
}






