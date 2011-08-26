#include "TopAnalysis/TopAnalyzer/interface/MetAnalyzer.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "TopAnalysis/TopAnalyzer/interface/DileptonEventWeight.h"

MetAnalyzer::MetAnalyzer(const edm::ParameterSet& cfg):
  METs_       (cfg.getParameter<edm::InputTag> ( "METs"       )),
  puWeight_   (cfg.getParameter<edm::InputTag> ( "weightPU"   )),
  lepSfWeight_(cfg.getParameter<edm::InputTag> ( "weightLepSF"))
{
}

MetAnalyzer::~MetAnalyzer()
{
}

void
MetAnalyzer::analyze(const edm::Event& evt, const edm::EventSetup& setup)
{
  double weight = getDileptonEventWeight(evt, puWeight_, lepSfWeight_);
  edm::Handle<PatMETCollection> METs;
  evt.getByLabel(METs_, METs);

  for(PatMETCollection::const_iterator met = METs->begin(); met!= METs->end(); ++met) {
    et_ ->Fill(met->et(), weight);
    phi_->Fill(met->phi(), weight);
  }
}

void
MetAnalyzer::beginJob()
{
  edm::Service<TFileService> fs;
  if( !fs ){
    throw edm::Exception( edm::errors::Configuration,
                          "TFile Service is not registered in cfg file" );
  }

  et_= fs->make<TH1D>( "et" , "Missing Transverse Energy", 200, 0., 400.);
  et_->GetXaxis()->SetTitle("#slash{E}_{T} [GeV]");
  et_->GetYaxis()->SetTitle("N_{evts}");

  phi_= fs->make<TH1D>( "phi" , "#phi of MET", 64, -3.2, 3.2);
  phi_->GetXaxis()->SetTitle("#phi_{MET}");
  phi_->GetYaxis()->SetTitle("N_{evts}");
}


void
MetAnalyzer::endJob()
{
}

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE( MetAnalyzer );
