// -*- C++ -*-
//
// Package:    DiLeptonCountFilter
// Class:      DiLeptonCountFilter
// 
/**\class DiLeptonCountFilter DiLeptonCountFilter.cc Test/DiLeptonCountFilter/src/DiLeptonCountFilter.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Jan Kieseler,,,DESY
//         Created:  Thu Aug  4 13:26:48 CEST 2011
// $Id$
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


#include "DataFormats/Candidate/interface/CompositeCandidate.h"

#include "DataFormats/Candidate/interface/CandidateFwd.h"

//
// class declaration
//

class DiLeptonCountFilter : public edm::EDFilter {
   public:
      explicit DiLeptonCountFilter(const edm::ParameterSet&);
      ~DiLeptonCountFilter();

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

  edm::InputTag dileptons_;
  int minnumber_;
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
DiLeptonCountFilter::DiLeptonCountFilter(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed

   dileptons_       =iConfig.getParameter<edm::InputTag>    ( "dileptons"            );
   minnumber_       =iConfig.getParameter<int>              ( "minnumber"            );

}


DiLeptonCountFilter::~DiLeptonCountFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
DiLeptonCountFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

  edm::Handle<reco::CandidateView> DiLeptons;
  iEvent.getByLabel(dileptons_, DiLeptons);


  bool ok=false;
  if(DiLeptons->size() >= (unsigned int)minnumber_) ok=true;

  return ok;
}

// ------------ method called once each job just before starting event loop  ------------
void 
DiLeptonCountFilter::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
DiLeptonCountFilter::endJob() {
}

// ------------ method called when starting to processes a run  ------------
bool 
DiLeptonCountFilter::beginRun(edm::Run&, edm::EventSetup const&)
{ 
  return true;
}

// ------------ method called when ending the processing of a run  ------------
bool 
DiLeptonCountFilter::endRun(edm::Run&, edm::EventSetup const&)
{
  return true;
}

// ------------ method called when starting to processes a luminosity block  ------------
bool 
DiLeptonCountFilter::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
  return true;
}

// ------------ method called when ending the processing of a luminosity block  ------------
bool 
DiLeptonCountFilter::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
  return true;
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
DiLeptonCountFilter::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(DiLeptonCountFilter);
