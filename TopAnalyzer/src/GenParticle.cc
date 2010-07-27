#include "TopAnalysis/TopAnalyzer/interface/GenParticle.h"

/// default constructor for generator level analysis in fw lite
GenParticle::GenParticle()
{
}

/// default constructor for full fw
GenParticle::GenParticle(const edm::ParameterSet& cfg) :
  status_( cfg.getParameter<int>( "status" ) )
{
  if(status_ > 3 || status_ < -1 || status_ == 0) 
    throw cms::Exception("Configuration") << "Error: genParticle status ( " << status_ << " ) unknown, please choose: 1,2,3 or -1 for all!\n";
}

/// histogramm booking for fwlite 
void GenParticle::book()
{
  hists_["genParticles"] = new TH1F( "genParticles" , "genParticles" ,   40, -0.5 , 39.5 );
}

/// histogramm booking for fw
void GenParticle::book(edm::Service<TFileService>& fs)
{
  hists_["genParticles"] = fs->make<TH1F>( "genParticles" , "genParticles" ,   40, -0.5 , 39.5 );
}


/// histogram filling interface for reconstruction level for access with fwlite or full framework
void
GenParticle::fill(const edm::View<reco::GenParticle>& parts, const double& weight)
{
  for(edm::View<reco::GenParticle>::const_iterator part=parts.begin(); part!=parts.end(); ++part){
    if( status_ == -1 ){
      if(part->pdgId()>=0) hists_.find("genParticles")->second->Fill(  part->pdgId() , weight );
      else                 hists_.find("genParticles")->second->Fill( -part->pdgId() , weight );
    }
    else if( status_ == 1 || status_ == 2 || status_ == 3 ){
      if( part->status() == status_ ){
	if( part->pdgId() >= 0 ) hists_.find("genParticles")->second->Fill(  part->pdgId() , weight );
	else                     hists_.find("genParticles")->second->Fill( -part->pdgId() , weight );
      }
    }
  }
}
