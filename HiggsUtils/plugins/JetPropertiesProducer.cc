// -*- C++ -*-
//
// Package:    JetPropertiesProducer
// Class:      JetPropertiesProducer
// 
/**\class JetPropertiesProducer JetPropertiesProducer.cc TopAnalysis/HiggsUtils/plugins/JetPropertiesProducer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Johannes Hauk,,,DESY
//         Created:  Tue Mar 12 14:29:43 CET 2013
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"

#include "TopAnalysis/HiggsUtils/interface/JetProperties.h"

//my include files....
#include <iostream>
#include <sstream>


//
// class declaration
//

typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<double> > LV;
typedef std::vector<LV> VLV;

class JetPropertiesProducer : public edm::EDProducer {
   public:
      explicit JetPropertiesProducer(const edm::ParameterSet&);
      ~JetPropertiesProducer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() ;
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      virtual void beginRun(edm::Run&, edm::EventSetup const&);
      virtual void endRun(edm::Run&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);

      // ----------member data ---------------------------
      
      const edm::ParameterSet parameterSet_;
};

//
// constants, enums and typedefs
//


//
// static data member definitions
//

//
// constructors and destructor
//
JetPropertiesProducer::JetPropertiesProducer(const edm::ParameterSet& iConfig):
parameterSet_(iConfig)
{
    produces<std::vector<JetProperties> >();
}


JetPropertiesProducer::~JetPropertiesProducer()
{}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
JetPropertiesProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup){
    std::auto_ptr<std::vector<JetProperties> > v_jetProperties(new std::vector<JetProperties>);
    
    
    edm::InputTag jets(parameterSet_.getParameter<edm::InputTag>("src"));
    
    edm::Handle<pat::JetCollection> jetHandle;
    //edm::Handle<edm::View< pat::Jet > > jetHandle;
    iEvent.getByLabel(jets, jetHandle);
    
// 	std::vector<int> jetTrackIndex;
    
	for(std::vector<pat::Jet>::const_iterator i_jet = jetHandle->begin(); i_jet != jetHandle->end(); ++i_jet){
        
	std::vector<LV> jetTrack;
	std::vector<int> jetTrackCharge;
        // Jet charge as given by PAT (weighted by global pt)
        const double jetChargeGlobalPtWeighted(i_jet->jetCharge());
        
        
        // Jet charge as weighted sum
   	    // weight = projection of charged pflow object momentum on jet axis 
        double jetPx = i_jet->px();
    	double jetPy = i_jet->py();
    	double jetPz = i_jet->pz();
        
        const std::vector<reco::PFCandidatePtr> pfConstituents = i_jet->getPFConstituents();
        
        double sumMomentum = 0;
        double sumMomentumQ = 0; 

	
        for(std::vector<reco::PFCandidatePtr>::const_iterator i_candidate = pfConstituents.begin(); i_candidate != pfConstituents.end(); ++i_candidate){
            const int charge = (*i_candidate)->charge();
	    
	    if(charge == 0) continue;
	    
	    jetTrack.push_back( (*i_candidate)->polarP4());
	    jetTrackCharge.push_back(charge);
// 	    jetTrackIndex.push_back(i_jet-jetHandle->begin());
	    
            const double constituentPx = (*i_candidate)->px();
            const double constituentPy = (*i_candidate)->py();
            const double constituentPz = (*i_candidate)->pz();
            const double product = constituentPx*jetPx + constituentPy*jetPy + constituentPz*jetPz;
            
            sumMomentum += product;
            sumMomentumQ += static_cast<double>(charge)*product;
        }//end looping over PF candidates
        
	    std::cout<<"The jet charge size for jet "<<i_jet-jetHandle->begin()<<" is = "<<jetTrackCharge.size()<<std::endl;
        const double jetChargeRelativePtWeighted(sumMomentum>0 ? sumMomentumQ/sumMomentum : 0);
        
        
        // Access Lorentz vector and PDG ID of parton associated to jet by PAT
        // If it does not exist, this can be identified by PDG ID =0
        int jetAssociatedPartonPdgId(0);
        math::PtEtaPhiMLorentzVectorD jetAssociatedParton(0,0,0,0);
        const reco::GenParticle * genParton = i_jet->genParton();
        if(genParton){
            jetAssociatedPartonPdgId = genParton->pdgId();
            jetAssociatedParton = genParton->polarP4();
        }
        
        JetProperties jetProperties(jetChargeGlobalPtWeighted, jetChargeRelativePtWeighted, jetAssociatedPartonPdgId, jetAssociatedParton, jetTrack, jetTrackCharge/*,jetTrackIndex*/);
        v_jetProperties->push_back(jetProperties);
        
        edm::LogVerbatim log("JetPropertiesProducer");
        log<<"   ---   Jet Properties   ---   \n";
        log<<"Jet charge global pt weighted:   "<<jetProperties.jetChargeGlobalPtWeighted()<<"\n";
        log<<"Jet charge relative pt weighted: "<<jetProperties.jetChargeRelativePtWeighted()<<"\n";
        log<<"Jet associated parton PDG ID:    "<<jetProperties.jetAssociatedPartonPdgId()<<"\n";
        log<<"Jet associated parton pt: "<<jetProperties.jetAssociatedParton().pt()<<"\n";
        log<<"Jet associated parton eta: "<<jetProperties.jetAssociatedParton().eta()<<"\n";
        log<<"Jet associated parton phi: "<<jetProperties.jetAssociatedParton().phi()<<"\n";
        log<<"Jet associated parton mass: "<<jetProperties.jetAssociatedParton().M()<<"\n";
        log<<"   --------------------------   \n\n";
    
       jetTrackCharge.clear();
       jetTrack.clear();
		
	}
    
    iEvent.put(v_jetProperties);
    
}

// ------------ method called once each job just before starting event loop  ------------
void 
JetPropertiesProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
JetPropertiesProducer::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void 
JetPropertiesProducer::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
JetPropertiesProducer::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
JetPropertiesProducer::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
JetPropertiesProducer::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
JetPropertiesProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
    // prefer to set the parameters without a default value:
    // an exception is thrown when the parameter is not defined in the config files, instead of silently using the default given here
    edm::ParameterSetDescription desc;
    desc.add<edm::InputTag>("src");
    descriptions.add("jetProperties", desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(JetPropertiesProducer);
