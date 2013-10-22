#include "TopAnalysis/TopUtils/plugins/visiblePhaseSpaceFilter.h"

visiblePhaseSpaceFilter::visiblePhaseSpaceFilter(const edm::ParameterSet& cfg):
  genLeptons_    ( cfg.getParameter<edm::InputTag>("genLeptons"  )),
  nLeptonsMin_   ( cfg.getParameter<int>("nLeptonsMin"  )),
  nLeptonsMax_   ( cfg.getParameter<int>("nLeptonsMax"  )),
  genJets_       ( cfg.getParameter<edm::InputTag>("genJets"     )),
  nJetsMin_      ( cfg.getParameter<int>("nJetsMin"     )),
  nJetsMax_      ( cfg.getParameter<int>("nJetsMax"     )),
  genbJets_      ( cfg.getParameter<edm::InputTag>("genbJets"    )),
  nbJetsMin_     ( cfg.getParameter<int>("nbJetsMin"    )),
  nbJetsMax_     ( cfg.getParameter<int>("nbJetsMax"    )),
  genlightJets_  ( cfg.getParameter<edm::InputTag>("genlightJets")),
  nlightJetsMin_ ( cfg.getParameter<int>("nlightJetsMin")),
  nlightJetsMax_ ( cfg.getParameter<int>("nlightJetsMax"))
{
  // register output
  produces<bool>("inVisiblePS");

  // load TFile Service
  edm::Service<TFileService> fs;
  if( !fs ){
    throw edm::Exception( edm::errors::Configuration,
			  "TFile Service is not registered in cfg file" );
  }
  // define multiplicity plots
  hists_["Nlep"      ] = fs->make<TH1F>( "Nlep"      , "Nlep"      , 9, -1., 3.);
  hists_["Njets"     ] = fs->make<TH1F>( "Njets"     , "Njets"     , 9, -1., 8.);
  hists_["Nbjets"    ] = fs->make<TH1F>( "Nbjets"    , "Nbjets"    , 9, -1., 8.);
  hists_["Nlightjets"] = fs->make<TH1F>( "Nlightjets", "Nlightjets", 9, -1., 8.);
  hists_["Naddjets30"] = fs->make<TH1F>( "Naddjets30", "Naddjets30", 9, -1., 8.);
  hists_["Naddjets50"] = fs->make<TH1F>( "Naddjets50", "Naddjets50", 9, -1., 8.);
}

void
visiblePhaseSpaceFilter::produce(edm::Event& evt, const edm::EventSetup& setup)
{
  // switch on/off debug output
  bool debug=false;

  // initialize tree entries
  nLeptons  =-1;
  nJets     =-1;
  nbJets    =-1;
  nlightJets=-1;
  naddJets30=-1;
  naddJets50=-1;
  inVisiblePS=false;

  // read collections from file
  edm::Handle<edm::View< reco::GenParticle > > genLeptonsCollection  ; 
  evt.getByLabel(genLeptons_  , genLeptonsCollection  );
  edm::Handle<edm::View< reco::GenJet > >      genJetsCollection     ; 
  evt.getByLabel(genJets_     , genJetsCollection     );
  edm::Handle<edm::View< reco::GenJet > >      genbJetsCollection    ; 
  evt.getByLabel(genbJets_    , genbJetsCollection    );
  edm::Handle<edm::View< reco::GenJet > >      genlightJetsCollection; 
  evt.getByLabel(genlightJets_, genlightJetsCollection);
  
  // prepare output
  std::auto_ptr<bool > out (new bool);

  // info output
  if(debug) {
    std::cout << std::endl << "processing visiblePhaseSpaceFilter" << std::endl;
    std::cout << "a) input:" << std::endl;
    std::cout << nLeptonsMin_   << "<=N(leptons)   <=" << nLeptonsMax_   << std::endl;
    std::cout << nJetsMin_      << "<=N(jets)      <=" << nJetsMax_      << std::endl;
    std::cout << nbJetsMin_     << "<=N(bjets)     <=" << nbJetsMax_     << std::endl;
    std::cout << nlightJetsMin_ << "<=N(light jets)<=" << nlightJetsMax_ << std::endl;
  }

  // get multiplicities from collections
  if(!genLeptonsCollection.failedToGet()&&genLeptonsCollection  .isValid()){
    nLeptons=0;
    for(edm::View< reco::GenParticle >::const_iterator p=genLeptonsCollection->begin(); p!=genLeptonsCollection->end()  ; ++p){
      ++nLeptons;
    }
  }
  if(!genJetsCollection.failedToGet()&&genJetsCollection     .isValid()){
    nJets=0;
    for(edm::View< reco::GenJet >::const_iterator p=genJetsCollection->begin()        ; p!=genJetsCollection->end()     ; ++p){
      ++nJets;
      if(nJets==4){ naddJets30=0; naddJets50=0; }
      else if(nJets>4){
	++naddJets30;
	if(p->pt()>=50) ++naddJets50; 
      }
    }
  }
  if(!genbJetsCollection.failedToGet()&&genbJetsCollection    .isValid()){
    nbJets=0;
    if(genbJetsCollection->begin()!=genJetsCollection->end()){
      for(edm::View< reco::GenJet >::const_iterator p=genbJetsCollection->begin()     ; p!=genbJetsCollection->end()    ; ++p){
	++nbJets;
      }
    }
  }
  if(!genlightJetsCollection.failedToGet()&&genlightJetsCollection.isValid()){
    nlightJets=0;
    for(edm::View< reco::GenJet >::const_iterator p=genlightJetsCollection->begin()   ; p!=genlightJetsCollection->end(); ++p){
      ++nlightJets;
    }
  }

  // info outpt
  if(debug) {
    std::cout << "b) values:" << std::endl;
    std::cout << "N(leptons)   =" << nLeptons   << std::endl;
    std::cout << "N(jets)      =" << nJets      << std::endl;
    std::cout << "N(bjets)     =" << nbJets     << std::endl;
    std::cout << "N(light jets)=" << nlightJets << std::endl;
    std::cout << "N(add.jets, pT>30)=" << naddJets30 << std::endl;
    std::cout << "N(add.jets, pT>50)=" << naddJets50 << std::endl;
  }

  // check if PS requirements are fulfilled and fill plots successively
  // fill lepton  multiplicity
  hists_.find("Nlep" )->second->Fill(nLeptons);
  // check lepton multiplicity
  if(nLeptons>=nLeptonsMin_&&nLeptons<=nLeptonsMax_){
    // fill jet multiplicity
    hists_.find("Njets" )->second->Fill(nJets);
    // check jet multiplicity
    if(nJets>=nJetsMin_&&nJets<=nJetsMax_){
      // fill bjet multiplicity
      hists_.find("Nbjets" )->second->Fill(nbJets);
      // check bjet multiplicity
      if(nbJets>=nbJetsMin_&&nbJets<=nbJetsMax_){
	// fill light multiplicity
	hists_.find("Nlightjets")->second->Fill(nlightJets);
	// check light multiplicity
	if(nlightJets>=nlightJetsMin_&&nlightJets<=nlightJetsMax_){
	  // set visible gen hadron phase space indicator to true
	  inVisiblePS=true;
	  // fill additional jet multiplicity plots
	  hists_.find("Naddjets30")->second->Fill(naddJets30);
	  hists_.find("Naddjets50")->second->Fill(naddJets50);
	}
      }
    }
  }
  
  // info output
  if(debug) std::cout << "c) is in visible PS?: " << inVisiblePS << std::endl;

  // push out information (if event is within visible gen hadron PS) into the event
  *out=inVisiblePS;
  evt.put(out, "inVisiblePS");
}


#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(visiblePhaseSpaceFilter);
