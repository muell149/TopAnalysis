#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "AnalysisDataFormats/TopObjects/interface/TtFullHadronicEvent.h"

#include "TopAnalysis/TopAnalyzer/plugins/FullHadHypothesisAnalyzer.h"

FullHadHypothesisAnalyzer::FullHadHypothesisAnalyzer(const edm::ParameterSet& cfg):
  fullHadEvt_  (cfg.getParameter<edm::InputTag>("fullHadEvent")),
  hypoClassKey_(cfg.getParameter<edm::InputTag>("hypoClassKey"))
{
}

void
FullHadHypothesisAnalyzer::analyze(const edm::Event& event, const edm::EventSetup& setup)
{
  //////////////////////////////////////////////////////////////////////////////////////////////////
  // get a handle for the TtFullHadronicEvent and a key to the hypothesis
  //////////////////////////////////////////////////////////////////////////////////////////////////
  
  edm::Handle<TtFullHadronicEvent> fullHadEvt;
  event.getByLabel(fullHadEvt_, fullHadEvt);

  edm::Handle<int> hypoClassKeyHandle;
  event.getByLabel(hypoClassKey_, hypoClassKeyHandle);
  TtFullHadronicEvent::HypoClassKey& hypoClassKey = (TtFullHadronicEvent::HypoClassKey&) *hypoClassKeyHandle;

  //////////////////////////////////////////////////////////////////////////////////////////////////
  // check if hypothesis is available and valid in this event
  //////////////////////////////////////////////////////////////////////////////////////////////////

  if( !fullHadEvt->isHypoValid(hypoClassKey) ){
    edm::LogInfo("HypothesisAnalyzer") << "Hypothesis not valid for this event";
    return;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////
  // get reconstructed top quarks and W bosons from the hypothesis
  //////////////////////////////////////////////////////////////////////////////////////////////////

  const reco::Candidate* Top    = fullHadEvt->top   (hypoClassKey);
  const reco::Candidate* WPlus  = fullHadEvt->wPlus (hypoClassKey);
  const reco::Candidate* TopBar = fullHadEvt->topBar(hypoClassKey);
  const reco::Candidate* WMinus = fullHadEvt->wMinus(hypoClassKey);

  //////////////////////////////////////////////////////////////////////////////////////////////////
  // fill simple histograms with pt, eta and the masses of the reconstructed particles
  //////////////////////////////////////////////////////////////////////////////////////////////////

  if(WPlus) {
    WPt_  ->Fill( WPlus->pt()   );
    WEta_ ->Fill( WPlus->eta()  );
    WMass_->Fill( WPlus->mass() );
  }

  if(WMinus) {
    WPt_  ->Fill( WMinus->pt()   );
    WEta_ ->Fill( WMinus->eta()  );
    WMass_->Fill( WMinus->mass() );
  }

  if(Top) {
    TopPt_  ->Fill( Top->pt()   );
    TopEta_ ->Fill( Top->eta()  );
    TopMass_->Fill( Top->mass() );
  }

  if(TopBar) {
    TopPt_  ->Fill( TopBar->pt()   );
    TopEta_ ->Fill( TopBar->eta()  );
    TopMass_->Fill( TopBar->mass() );
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////
  // get genParticles
  //////////////////////////////////////////////////////////////////////////////////////////////////

  const reco::Candidate* genTop    = fullHadEvt->top();
  const reco::Candidate* genWPlus  = fullHadEvt->wPlus();
  const reco::Candidate* genTopBar = fullHadEvt->topBar();
  const reco::Candidate* genWMinus = fullHadEvt->wMinus();

  //////////////////////////////////////////////////////////////////////////////////////////////////
  // fill pull histograms for pt, eta and the masses of the reconstructed with respect to the generated particles
  //////////////////////////////////////////////////////////////////////////////////////////////////

  if(WPlus && genWPlus) {
    WPullPt_  ->Fill( (WPlus->pt()   - genWPlus->pt())   / genWPlus->pt()   );
    WPullEta_ ->Fill( (WPlus->eta()  - genWPlus->eta())  / genWPlus->eta()  );
    WPullMass_->Fill( (WPlus->mass() - genWPlus->mass()) / genWPlus->mass() );
  }

  if(WMinus && genWMinus) {
    WPullPt_  ->Fill( (WMinus->pt()   - genWMinus->pt())   / genWMinus->pt()   );
    WPullEta_ ->Fill( (WMinus->eta()  - genWMinus->eta())  / genWMinus->eta()  );
    WPullMass_->Fill( (WMinus->mass() - genWMinus->mass()) / genWMinus->mass() );
  }

  if(Top && genTop) {
    TopPullPt_  ->Fill( (Top->pt() -   genTop->pt())   / genTop->pt()   );
    TopPullEta_ ->Fill( (Top->eta() -  genTop->eta())  / genTop->eta()  );
    TopPullMass_->Fill( (Top->mass() - genTop->mass()) / genTop->mass() );
  }

  if(TopBar && genTopBar) {
    TopPullPt_  ->Fill( (TopBar->pt() -   genTopBar->pt())   / genTopBar->pt()   );
    TopPullEta_ ->Fill( (TopBar->eta() -  genTopBar->eta())  / genTopBar->eta()  );
    TopPullMass_->Fill( (TopBar->mass() - genTopBar->mass()) / genTopBar->mass() );
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////
  // fill histograms with variables describing the quality of the hypotheses
  //////////////////////////////////////////////////////////////////////////////////////////////////

  genMatchDr_->Fill(fullHadEvt->genMatchSumDR());
  mvaDisc_   ->Fill(fullHadEvt->mvaDisc());

  if(Top && genTop) {

    genMatchDrVsTopPullMass_->Fill((Top->mass() - genTop->mass()) / genTop->mass(), fullHadEvt->genMatchSumDR());
    mvaDiscVsTopPullMass_   ->Fill((Top->mass() - genTop->mass()) / genTop->mass(), fullHadEvt->mvaDisc());

  }

  if(TopBar && genTopBar) {

    genMatchDrVsTopPullMass_->Fill((TopBar->mass() - genTopBar->mass()) / genTopBar->mass(), fullHadEvt->genMatchSumDR());
    mvaDiscVsTopPullMass_   ->Fill((TopBar->mass() - genTopBar->mass()) / genTopBar->mass(), fullHadEvt->mvaDisc());

  }
}

void 
FullHadHypothesisAnalyzer::beginJob()
{
  edm::Service<TFileService> fs;
  if( !fs ) throw edm::Exception( edm::errors::Configuration, "TFile Service is not registered in cfg file" );

  //////////////////////////////////////////////////////////////////////////////////////////////////
  // book histograms
  //////////////////////////////////////////////////////////////////////////////////////////////////

  WPt_   = fs->make<TH1F>("WPt"  , "p_{t} (W) [GeV]", 25,  0., 500.);
  WEta_  = fs->make<TH1F>("WEta" , "#eta (W)"       , 20, -4.,   4.);
  WMass_ = fs->make<TH1F>("WMass", "M (W) [GeV]"    , 25,  0., 200.);

  TopPt_   = fs->make<TH1F>("TopPt"  , "p_{t} (t) [GeV]", 25, 0. , 500.);
  TopEta_  = fs->make<TH1F>("TopEta" , "#eta (t)"       , 20, -4.,   4.);
  TopMass_ = fs->make<TH1F>("TopMass", "M (t) [GeV]"    , 40, 0. , 400.);

  WPullPt_   = fs->make<TH1F>("WPullPt"  , "(p_{t,rec}-p_{t,gen})/p_{t,gen} (W)"   , 40, -1., 1.);
  WPullEta_  = fs->make<TH1F>("WPullEta" , "(#eta_{rec}-#eta_{gen})/#eta_{gen} (W)", 40, -1., 1.);
  WPullMass_ = fs->make<TH1F>("WPullMass", "(M_{rec}-M_{gen})/M_{gen} (W)"         , 40, -1., 1.);

  TopPullPt_   = fs->make<TH1F>("TopPullPt"  , "(p_{t,rec}-p_{t,gen})/p_{t,gen} (t)"   , 40, -1., 1.);
  TopPullEta_  = fs->make<TH1F>("TopPullEta" , "(#eta_{rec}-#eta_{gen})/#eta_{gen} (t)", 40, -1., 1.);
  TopPullMass_ = fs->make<TH1F>("TopPullMass", "(M_{rec}-M_{gen})/M_{gen} (t)"         , 40, -1., 1.);

  genMatchDr_ = fs->make<TH1F>("genMatchDr", "GenMatch #Sigma #Delta R", 40, 0., 4.);
  mvaDisc_    = fs->make<TH1F>("mvaDisc"   , "MVA discriminator"       , 20, 0., 1.);

  genMatchDrVsTopPullMass_ = fs->make<TH2F>("genMatchDrVsTopPullMass",
					       "GenMatch #Sigma #Delta R vs. (M_{rec}-M_{gen})/M_{gen} (t_{had}))",
					       40, -1., 1., 40, 0., 4.);
  mvaDiscVsTopPullMass_    = fs->make<TH2F>("mvaDiscVsTopPullMass",
					       "MVA discriminator vs. (M_{rec}-M_{gen})/M_{gen} (t_{had}))",
					       40, -1., 1., 20, 0., 1.);
}

void
FullHadHypothesisAnalyzer::endJob() 
{
}
