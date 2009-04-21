#include "TopAnalysis/TopAnalyzer/plugins/SemiLepJetCombMVAValidator.h"

#include "FWCore/Utilities/interface/EDMException.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"

#include "AnalysisDataFormats/TopObjects/interface/TtGenEvent.h"

SemiLepJetCombMVAValidator::SemiLepJetCombMVAValidator(const edm::ParameterSet& cfg):
  match_(cfg.getParameter<edm::InputTag>("match")),
  combs_(cfg.getParameter<edm::InputTag>("combs")),
  discs_(cfg.getParameter<edm::InputTag>("discs"))
{
}

void
SemiLepJetCombMVAValidator::analyze(const edm::Event& evt, const edm::EventSetup& setup)
{
  edm::Handle<TtGenEvent> genEvt;
  evt.getByLabel("genEvt", genEvt);

  edm::Handle<std::vector<std::vector<int> > > matchHandle;
  std::vector<int> match;
  // get jet-parton matching if signal channel
  if(genEvt->semiLeptonicChannel() == WDecay::kMuon) {
    evt.getByLabel(match_, matchHandle);
    match = *(matchHandle->begin());
    // skip events that were affected by the outlier 
    // rejection in the jet-parton matching
    if( !isValid(match) ) {
      valid_match->Fill(0.);
      return;
    }
    valid_match->Fill(1.);
  }

  // take into account indistinguishability of the two jets from the hadr. W decay,
  // reduces combinatorics by a factor of 2
  if(match[TtSemiLepEvtPartons::LightQ] > match[TtSemiLepEvtPartons::LightQBar]) {
    int iTemp = match[TtSemiLepEvtPartons::LightQ];
    match[TtSemiLepEvtPartons::LightQ] = match[TtSemiLepEvtPartons::LightQBar];
    match[TtSemiLepEvtPartons::LightQBar] = iTemp;
  }

  // get jetCombs and discriminators from MVAComputer
  edm::Handle<std::vector<std::vector<int> > > combs;
  evt.getByLabel(combs_, combs);

  edm::Handle<std::vector<double> > discs;
  evt.getByLabel(discs_, discs);

  if( combs->size() != discs->size() )
    throw edm::Exception( edm::errors::Configuration,
			  "Array sizes of jetCombs and discriminators provided by the JetCombMVA differ!" );

  std::vector<std::vector<int> >::const_iterator comb = combs->begin();
  std::vector<double>           ::const_iterator disc = discs->begin();

  if( isValid(*comb) ) {
    // check if the best jetComb (first element in the combs vector) was the true one
    if( *comb==match )
      evt_disc_sig->Fill(*disc);
    else
      evt_disc_bkg->Fill(*disc);
  }

  bool validCombs = true;

  for( ; comb != combs->end() && disc != discs->end(); ++comb, ++disc) {
    if( !isValid(*comb) ) {
      validCombs = false;
      break;
    }
    if( *comb==match )
      hyp_disc_sig->Fill(*disc);
    else
      hyp_disc_bkg->Fill(*disc);
  }

  if(validCombs) valid_combs->Fill(1.);
  else {
    valid_combs->Fill(0.);
    return;
  }
}

void 
SemiLepJetCombMVAValidator::beginJob(const edm::EventSetup&)
{
  edm::Service<TFileService> fs;
  if( !fs )
    throw edm::Exception( edm::errors::Configuration, "TFile Service is not registered in cfg file!" );

  valid_match  = fs->make<TH1F>("valid_match" , "valid_match" ,  2, 0.00,  2.00);
  valid_combs  = fs->make<TH1F>("valid_combs" , "valid_combs" ,  2, 0.00,  2.00);

  hyp_disc_sig = fs->make<TH1F>("hyp_disc_sig", "hyp_disc_sig", 21, 0.00,  1.05);
  hyp_disc_bkg = fs->make<TH1F>("hyp_disc_bkg", "hyp_disc_bkg", 21, 0.00,  1.05);
  evt_disc_sig = fs->make<TH1F>("evt_disc_sig", "evt_disc_sig", 21, 0.00,  1.05);
  evt_disc_bkg = fs->make<TH1F>("evt_disc_bkg", "evt_disc_bkg", 21, 0.00,  1.05);
}

void 
SemiLepJetCombMVAValidator::endJob() 
{
}
