#include "DataFormats/PatCandidates/interface/Jet.h"
#include "TopAnalysis/TopFilter/plugins/JetIdFunctorFilter.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

JetIdFunctorFilter::JetIdFunctorFilter(const edm::ParameterSet& cfg):
  jets_    ( cfg.getParameter<edm::InputTag>("jets" ) ),
  type_    ( cfg.getParameter<std::string>("jetType") ),
  version_ ( cfg.getParameter<std::string>("version") ),
  quality_ ( cfg.getParameter<std::string>("quality") )
{
  produces< std::vector<pat::Jet> >();
}

void
JetIdFunctorFilter::beginJob()
{
  if(type_=="CALO" || type_=="JPT"){
    if      ( quality_ == "MINIMAL" )   quality = JetIDSelectionFunctor::MINIMAL;
    else if ( quality_ == "LOOSE_AOD" ) quality = JetIDSelectionFunctor::LOOSE_AOD;
    else if ( quality_ == "LOOSE" )     quality = JetIDSelectionFunctor::LOOSE;
    else if ( quality_ == "TIGHT" )     quality = JetIDSelectionFunctor::TIGHT;
    else       
      throw cms::Exception("InvalidInput") << "Expect quality to be one of MINIMAL, LOOSE_AOD, LOOSE,TIGHT" << std::endl;

    if      ( version_ == "CRAFT08" ) version = JetIDSelectionFunctor::CRAFT08;
    else if ( version_ == "PURE09"  ) version = JetIDSelectionFunctor::PURE09;  
    else if ( version_ == "DQM09"   ) version = JetIDSelectionFunctor::DQM09;    
    else {
      throw cms::Exception("InvalidInput") << "Expect version to be one of CRAFT08, PURE09, DQM09" << std::endl;      
    }
  }
  else if(type_=="PF"){
    if      ( quality_ == "LOOSE" )     qualityPF = PFJetIDSelectionFunctor::LOOSE;
    else if ( quality_ == "TIGHT" )     qualityPF = PFJetIDSelectionFunctor::TIGHT;
    else       
      throw cms::Exception("InvalidInput") << "Expect quality to be one of MINIMAL, LOOSE_AOD, LOOSE,TIGHT" << std::endl;

    if      ( version_ == "FIRSTDATA" ) versionPF = PFJetIDSelectionFunctor::FIRSTDATA; 
    else {
      throw cms::Exception("InvalidInput") << "Expect version to be FIRSTDATA" << std::endl;
    }  
  }
  else throw cms::Exception("InvalidInput") << "Unknown jet type specified" << std::endl;
}

void
JetIdFunctorFilter::produce(edm::Event& evt, const edm::EventSetup& setup)
{  
  edm::Handle<edm::View< pat::Jet > > jets; 
  evt.getByLabel(jets_, jets );

  std::auto_ptr< std::vector<pat::Jet> > goodJets( new std::vector<pat::Jet>() );  

  if(type_=="CALO" || type_=="JPT"){
    // create selection functor
    JetIDSelectionFunctor jetIDFunctor(version,quality);
    pat::strbitset ret = jetIDFunctor.getBitTemplate();
    // loop over inut jets
    for ( edm::View<pat::Jet>::const_iterator jet = jets->begin();jet != jets->end(); ++jet ) {      
      ret.set(false);
      bool passed = jetIDFunctor( *jet, ret );
      // append jets fulfilling selection criteria to output collection
      if(passed) goodJets->push_back(*jet);
    }
  }
  else if(type_=="PF"){
    // create selection functor
    PFJetIDSelectionFunctor jetIDFunctor(versionPF,qualityPF);
    pat::strbitset ret = jetIDFunctor.getBitTemplate();
    // loop over inut jets
    for ( edm::View<pat::Jet>::const_iterator jet = jets->begin();jet != jets->end(); ++jet ) {      
      ret.set(false);
      bool passed = jetIDFunctor( *jet, ret );
      // append jets fulfilling selection criteria to output collection
      if(passed) goodJets->push_back(*jet);
    }
  }   
  
  evt.put(goodJets);  
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( JetIdFunctorFilter );
