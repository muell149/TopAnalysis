// -*- C++ -*-
//
// Package:    GeneratorHiggsFilter
// Class:      GeneratorHiggsFilter
// 
/**\class GeneratorHiggsFilter GeneratorHiggsFilter.cc TopAnalysis/HiggsUtils/plugins/GeneratorHiggsFilter.cc

 Description: EDFilter to select Higgs decays on generator level


 Implementation:
     filter for Higgs decay channels on generator level.
     decay channels are internally coded by integer numbers.
     since it might be important to implement further selections on the decay chain of the Higgs decay particles, several numbers are kept free:
     0  decay mode not implemented or strange generator behaviour
     1  stands for decay to d quarks
     2  to u quarks
     3  to s quarks
     4  to c quarks
     5  to b quarks
     30 stands for decay to tau leptons (could use eg. 31-39 for further decay chains)
     40 stands for decay to W bosons (could use eg. 41-49 for further decay chains)
*/
//
// Original Author:  Johannes Hauk,,,DESY
//         Created:  Mon Feb 18 16:24:42 CET 2013
// $Id: GeneratorHiggsFilter.cc,v 1.2 2013/02/19 20:03:05 hauk Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "TopAnalysis/HiggsUtils/interface/HiggsGenEvent.h"

//
// class declaration
//

class GeneratorHiggsFilter : public edm::EDFilter {
   public:
      explicit GeneratorHiggsFilter(const edm::ParameterSet&);
      ~GeneratorHiggsFilter();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      virtual bool beginRun(edm::Run&, edm::EventSetup const&);
      virtual bool endRun(edm::Run&, edm::EventSetup const&);
      virtual bool beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
      virtual bool endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);

      // ----------member data ---------------------------
      
      /// as source the genEventHiggs shoud be used
      edm::InputTag src_;
      
      /// string to save channel short cut from config
      std::vector<std::string> v_channel_;
      
      /// bool from config: invert the selection?
      bool invertSelection_;
      
      /// vector to store the index numbers of the channels to be selected
      std::vector<int> v_selectedChannel_;
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
GeneratorHiggsFilter::GeneratorHiggsFilter(const edm::ParameterSet& iConfig):
src_(iConfig.getParameter<edm::InputTag>("src")),
v_channel_(iConfig.getParameter<std::vector<std::string> >("channels")),
invertSelection_(iConfig.getParameter<bool>("invert_selection"))
{
    produces<int>("higgsDecayMode");
}


GeneratorHiggsFilter::~GeneratorHiggsFilter()
{
}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
GeneratorHiggsFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    bool passed = true;
    bool blocked = false;
    
    if(invertSelection_){
        blocked = true;
        passed  = false;    
    }
    
    int decayMode(0);
    
    const reco::Candidate *d(0), *dbar(0);
    const reco::Candidate *u(0), *ubar(0);
    const reco::Candidate *s(0), *sbar(0);
    const reco::Candidate *c(0), *cbar(0);
    const reco::Candidate *b(0), *bbar(0);
    const reco::Candidate *tauMinus(0), *tauPlus(0);
    const reco::Candidate *wMinus(0), *wPlus(0);
    const reco::Candidate *unknown(0), *unknownBar(0);
    
    edm::Handle<HiggsGenEvent> genEvt;
    iEvent.getByLabel(src_, genEvt);
    
    const std::vector<reco::GenParticle>* v_genParticle = &(genEvt->particles());
    for(reco::GenParticleCollection::const_iterator cand = v_genParticle->begin(); cand!=v_genParticle->end(); ++cand){
        if(cand->pdgId()!=25)continue;
        edm::LogVerbatim log("GeneratorHiggsFilter");
        log <<"\n";
        log << "--------------------------------------\n"
            << "- Dump Higgs Filter Information      -\n"
            << "--------------------------------------\n";
        
        log << "Particle ID: " << cand->pdgId()  << "\n";
        log << "Status     : " << cand->status() << "\n";
        log << "# daughters: " << cand->numberOfDaughters() << "\n";
        
        for(size_t i=0; i<cand->numberOfDaughters(); ++i){
            log << "     Daughter PID  : " << cand->daughter(i)->pdgId()  << "\n";
            log << "     Dauther Status: " << cand->daughter(i)->status() << "\n";
            if(cand->daughter(i)->pdgId()==1)d = cand->daughter(i);
            else if(cand->daughter(i)->pdgId()==-1)dbar = cand->daughter(i);
            else if(cand->daughter(i)->pdgId()==2)u = cand->daughter(i);
            else if(cand->daughter(i)->pdgId()==-2)ubar = cand->daughter(i);
            else if(cand->daughter(i)->pdgId()==3)s = cand->daughter(i);
            else if(cand->daughter(i)->pdgId()==-3)sbar = cand->daughter(i);
            else if(cand->daughter(i)->pdgId()==4)c = cand->daughter(i);
            else if(cand->daughter(i)->pdgId()==-4)cbar = cand->daughter(i);
            else if(cand->daughter(i)->pdgId()==5)b = cand->daughter(i);
            else if(cand->daughter(i)->pdgId()==-5)bbar = cand->daughter(i);
            else if(cand->daughter(i)->pdgId()==15)tauMinus = cand->daughter(i);
            else if(cand->daughter(i)->pdgId()==-15)tauPlus = cand->daughter(i);
            else if(cand->daughter(i)->pdgId()==24)wPlus = cand->daughter(i);
            else if(cand->daughter(i)->pdgId()==-24)wMinus = cand->daughter(i);
            else cand->daughter(i)->pdgId()>0 ? unknown = cand->daughter(i) : unknownBar = cand->daughter(i);
        }
        
    }
    if(d && dbar)decayMode = 1;
    if(u && ubar)decayMode = 2;
    if(s && sbar)decayMode = 3;
    if(c && cbar)decayMode = 4;
    if(b && bbar)decayMode = 5;
    if(tauMinus && tauPlus)decayMode = 30;
    if(wMinus && wPlus)decayMode = 40;
    
    if(decayMode == 0){
        edm::LogVerbatim log("GeneratorHiggsFilter");
        log <<"\n";
        log <<"  --->\n";
        log <<"\tNo decayMode assigned to this Higgs decay\n";
        if(unknown || unknownBar){
            log << "\tHowever, particle or antiparticle is stored in decay chain.\n";
            if(unknown)   log << "\tUnknown particle has ID     : " << unknown->pdgId() << "\n";
            if(unknownBar)log << "\tUnknown anti-particle has ID: " << unknownBar->pdgId() << "\n";
        }
    }
    
    // store the decay mode
    std::auto_ptr<int> decay(new int);
    *decay = decayMode;
    iEvent.put(decay, "higgsDecayMode");
    
    for(std::vector<int>::const_iterator i_selectedChannel = v_selectedChannel_.begin(); i_selectedChannel != v_selectedChannel_.end(); ++i_selectedChannel){
        if(decayMode == *i_selectedChannel)return passed;
    }
    
    return blocked;
}

// ------------ method called once each job just before starting event loop  ------------
void 
GeneratorHiggsFilter::beginJob()
{
    // check if channel short cuts are given in config
    if(v_channel_.size()>0){
        for(std::vector<std::string>::const_iterator i_channel = v_channel_.begin(); i_channel != v_channel_.end(); ++i_channel){
            const std::string channel(*i_channel);
            if(channel=="b"){
                v_selectedChannel_.push_back(5);
            }
            else if(channel=="tau"){
                v_selectedChannel_.push_back(30);
            }
            else if(channel=="W"){
                v_selectedChannel_.push_back(40);
            }
            else if(channel=="none"){
                // empty
            }
            else{
	            edm::LogError("GeneratorHiggsFilter") << "Unknown Higgs decay channel short cut in configuration: " << channel;
	            throw cms::Exception("Configuration Error");
            }
        }
    }
    else{
        // At present no other selection way than the one above is implemented, so require selection there
        edm::LogError("GeneratorHiggsFilter") << "No Higgs decay channel specified in config, change needed";
	    throw cms::Exception("Configuration Error");
    }
    
    // FIXME: put here printout of what exactly is selected in this filter
}

// ------------ method called once each job just after ending the event loop  ------------
void 
GeneratorHiggsFilter::endJob() {
}

// ------------ method called when starting to processes a run  ------------
bool 
GeneratorHiggsFilter::beginRun(edm::Run&, edm::EventSetup const&)
{ 
  return true;
}

// ------------ method called when ending the processing of a run  ------------
bool 
GeneratorHiggsFilter::endRun(edm::Run&, edm::EventSetup const&)
{
  return true;
}

// ------------ method called when starting to processes a luminosity block  ------------
bool 
GeneratorHiggsFilter::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
  return true;
}

// ------------ method called when ending the processing of a luminosity block  ------------
bool 
GeneratorHiggsFilter::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
  return true;
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
GeneratorHiggsFilter::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.add<edm::InputTag>("src");
  desc.add<std::vector<std::string> >("channels");
  desc.add<bool>("invert_selection");
  descriptions.add("generatorHiggsFilter", desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(GeneratorHiggsFilter);
