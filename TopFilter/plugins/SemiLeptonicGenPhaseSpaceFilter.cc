#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "TopAnalysis/TopFilter/plugins/SemiLeptonicGenPhaseSpaceFilter.h"
#include "AnalysisDataFormats/TopObjects/interface/TtSemiLepEvtPartons.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

SemiLeptonicGenPhaseSpaceFilter::SemiLeptonicGenPhaseSpaceFilter(const edm::ParameterSet& cfg):
  src_          ( cfg.getParameter<edm::InputTag>("src"    ) ),
  leptonMinPt_  ( cfg.getParameter<double       >("leptonMinPt") ),
  leptonMaxEta_ ( cfg.getParameter<double       >("leptonMaxEta") ),
  partonMinPt_  ( cfg.getParameter<double       >("partonMinPt") ),
  partonMaxEta_ ( cfg.getParameter<double       >("partonMaxEta") )
{
}

bool SemiLeptonicGenPhaseSpaceFilter::filter(edm::Event& event, const edm::EventSetup& setup)
{

  edm::Handle<TtGenEvent> src;
  event.getByLabel(src_, src);
  
  const TtGenEvent& tops = *src;

  //const reco::GenParticle *lepTop= tops.leptonicDecayTop();
  //const reco::GenParticle *hadTop= tops.hadronicDecayTop();
  //const reco::GenParticle *lepW  = tops.leptonicDecayW();
  //const reco::GenParticle *hadW  = tops.hadronicDecayW();
  //const reco::GenParticle *neutrino = tops.singleNeutrino();

  const reco::GenParticle *lep   = tops.singleLepton();
  const reco::GenParticle *lepB  = tops.leptonicDecayB(); 
  const reco::GenParticle *hadB  = tops.hadronicDecayB();
  const reco::GenParticle *q     = tops.hadronicDecayQuark();
  const reco::GenParticle *qbar  = tops.hadronicDecayQuarkBar();
  
//   std::cout<<"lepPt ="<< lep->pt()<<"; lepEta ="<<lep->eta()<<"; lepBPt="<<lepB->pt()<<"; lepBEta="<<lepB->eta()
//       <<"; hadBPt="<<hadB->pt()<<"; hadBEta="<<hadB->eta()
//       <<"; qPt = "<<q->pt()<<"; qEta=" << q->eta()<<"; qbarPt = "<<qbar->pt()<<"; qbarEta=" << qbar->eta()
//   <<std::endl;

  // cut on lepton pt and eta
  if(lep->pt()  < leptonMinPt_ || std::abs(lep->eta())  > leptonMaxEta_)   return false;
  // cut on b quark pt and eta 
  if(lepB->pt() < partonMinPt_ || std::abs(lepB->eta()) > partonMaxEta_ ||
     hadB->pt() < partonMinPt_ || std::abs(hadB->eta()) > partonMaxEta_)   return false;
  // cut on light quark pt and eta
  if(q->pt()    < partonMinPt_ || std::abs(q->eta())    > partonMaxEta_ ||
     qbar->pt() < partonMinPt_ || std::abs(qbar->eta()) > partonMaxEta_)   return false;
  
  // fill histos if desired
//     hists_["lepPt"     ]-> Fill(lep->pt());
//     hists_["lepEta"    ]-> Fill(lep->eta());
//     hists_["bPt"       ]-> Fill(lepB->pt());  hists_["bPt"     ]-> Fill(hadB->pt());
//     hists_["bEta"      ]-> Fill(lepB->eta()); hists_["bEta"    ]-> Fill(hadB->eta());
//     hists_["qPt"       ]-> Fill(q->pt());     hists_["qPt"     ]-> Fill(qbar->pt());
//     hists_["qEta"      ]-> Fill(q->eta());    hists_["qEta"    ]-> Fill(qbar->eta()); 
  
  // if no cut is done return true

  return true;
}

void SemiLeptonicGenPhaseSpaceFilter::beginJob()
{
//  edm::Service<TFileService> fs;
//   if( !fs ){
//     throw edm::Exception( edm::errors::Configuration,
// 			  "TFile Service is not registered in cfg file" );
//   }
  
  // number of valid hits in silicon tracker
//     
//     hists_["lepPt"     ] =fs->make<TH1F>( "lepPt"    ,  "lepPt"     ,   500,   0.,  500. );
//     hists_["lepEta"    ] =fs->make<TH1F>( "lepEta"   ,  "lepEta"    ,   100,   -5.,  5.  );
//     // contains both letB and hadB
//     hists_["bPt"    ] =fs->make<TH1F>( "bPt"   ,  "bPt"    ,   500,   0.,  500. );
//     hists_["bEta"   ] =fs->make<TH1F>( "bEta"  ,  "bEta"   ,   100,   -5.,  5.  );
//     // contains both q and qbar
//     hists_["qPt"    ] =fs->make<TH1F>( "qPt"   ,  "qPt"    ,   500,   0.,  500. );
//     hists_["qEta"   ] =fs->make<TH1F>( "qEta"  ,  "qEta"   ,   100,   -5.,  5.  );
}

void SemiLeptonicGenPhaseSpaceFilter::endJob()
{
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( SemiLeptonicGenPhaseSpaceFilter );
