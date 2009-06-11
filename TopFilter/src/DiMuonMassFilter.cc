#include "TopAnalysis/TopFilter/interface/DiMuonMassFilter.h"

 
DiMuonMassFilter::DiMuonMassFilter(const edm::ParameterSet& cfg):
  muons_(cfg.getParameter<edm::InputTag>("muons"))
{
  std::cout << "ok i'm in" << std::endl;   
}

DiMuonMassFilter::~DiMuonMassFilter()
{
}

bool
DiMuonMassFilter::filter(edm::Event& evt, const edm::EventSetup& setup)
{   

  bool M=true;
  
  edm::Handle<std::vector<pat::Muon> > muons;
  evt.getByLabel(muons_, muons);
  
  if(muons->size()>1)
    { 
      reco::Particle::LorentzVector DiMuonP4=(*muons)[0].p4()+(*muons)[1].p4();
      double DiMuonMass = sqrt( DiMuonP4.Dot(DiMuonP4) );
      if(DiMuonMass > 84 && DiMuonMass <= 98) 
	{
	  M=false;
	  std::cout << "Z-Veto" << std::endl;
	}
    }
      
  return M;
}

void DiMuonMassFilter::beginJob(const edm::EventSetup&)
{  
} 

void DiMuonMassFilter::endJob()
{
}









