#include "TopAnalysis/TopAnalyzer/plugins/FullLepGenAnalyzer.h"
#include "TopAnalysis/TopUtils/interface/NameScheme.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "CommonTools/CandUtils/interface/AddFourMomenta.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "TopAnalysis/TopAnalyzer/interface/DileptonEventWeight.h"
#include "AnalysisDataFormats/TopObjects/interface/TtGenEvent.h"
#include "TopQuarkAnalysis/TopSkimming/interface/TtDecayChannelSelector.h"

FullLepGenAnalyzer::FullLepGenAnalyzer(const edm::ParameterSet& cfg):
  src_        (cfg.getParameter<edm::InputTag>("src"       )),
  puWeight_   (cfg.getParameter<edm::InputTag>( "weightPU"   )),
  lepSfWeight_(cfg.getParameter<edm::InputTag>( "weightLepSF"))
{
}



FullLepGenAnalyzer::~FullLepGenAnalyzer()
{
}



void FullLepGenAnalyzer::beginJob()
{
  edm::Service<TFileService> fs;
  if( !fs ) throw edm::Exception( edm::errors::Configuration, "TFile Service is not registered in cfg file" );
  bookGenHistos(fs);
}



void FullLepGenAnalyzer::analyze(const edm::Event& evt, const edm::EventSetup& es) {

  double weight = getDileptonEventWeight(evt, puWeight_, lepSfWeight_);
  
  edm::Handle<TtGenEvent> genEvt;
  evt.getByLabel(src_, genEvt );
  const std::vector<reco::GenParticle> *genParticles = &(genEvt->particles()); 

  const reco::Candidate* genTop = 0;
  const reco::Candidate* genTopBar = 0;
  const reco::Candidate* genB = 0;
  const reco::Candidate* genBBar = 0;
  const reco::Candidate* genWplus = 0;
  const reco::Candidate* genWminus = 0;
  const reco::Candidate* genLep = 0;
  const reco::Candidate* genLepBar = 0;
  const reco::Candidate* genNu = 0;
  const reco::Candidate* genNuBar = 0;

  // reconstruct ttbar decay chain
  for(reco::GenParticleCollection::const_iterator cand = genParticles->begin(); cand!=genParticles->end(); ++cand) {
    if(abs(cand->pdgId())!=6)         continue;
    if(genTop!=0 && genTopBar!=0) break; //stop loop if ttbar pair already found

    if(cand->pdgId()==6){
      genTop = &(*cand);
      for(size_t i=0; i<genTop->numberOfDaughters(); ++i){
        if(genTop->daughter(i)->pdgId()==5){
	  genB = genTop->daughter(i);
        }
        else if(genTop->daughter(i)->pdgId()==24){
	  genWplus = genTop->daughter(i);
        }
      }
    }
    if(genWplus!=0){
      for(size_t i=0; i<genWplus->numberOfDaughters(); ++i){     
        if(genWplus->daughter(i)->pdgId()==-11 || genWplus->daughter(i)->pdgId()==-13){
	  genLepBar = genWplus->daughter(i);
	}
        else if(genWplus->daughter(i)->pdgId()==-15){
          genLepBar = getTauDaughter(genWplus->daughter(i));
	}
        else if(genWplus->daughter(i)->pdgId()==12 || genWplus->daughter(i)->pdgId()==14 || genWplus->daughter(i)->pdgId()==16){
	  genNu = genWplus->daughter(i);
	}
      }      
    }      
    if(cand->pdgId()==-6){
      genTopBar = &(*cand);
      for(size_t i=0; i<genTopBar->numberOfDaughters(); ++i){
        if(genTopBar->daughter(i)->pdgId()==-5){
	  genBBar = genTopBar->daughter(i);
        }
        else if(genTopBar->daughter(i)->pdgId()==-24){
	  genWminus = genTopBar->daughter(i);
        }
      }
    }
    if(genWminus!=0){
      for(size_t i=0; i<genWminus->numberOfDaughters(); ++i){        
        if(genWminus->daughter(i)->pdgId()==11 || genWminus->daughter(i)->pdgId()==13){
	  genLep = genWminus->daughter(i);
	}
        else if(genWminus->daughter(i)->pdgId()==15){
          genLep = getTauDaughter(genWminus->daughter(i));
	}
        else if(genWminus->daughter(i)->pdgId()==-12 || genWminus->daughter(i)->pdgId()==-14 || genWminus->daughter(i)->pdgId()==-16){
	  genNuBar = genWminus->daughter(i);
	}	
      }      
    }         
  }
  
  // test for dileptons
  if(genB==0){
    std::cout << "bQuark not found" << std::endl;
    return;
  }
  if(genBBar==0){
    std::cout << "bBarQuark not found" << std::endl;
    return;
  }
  if(genLep==0){
    std::cout << "lepton not found" << std::endl;
    return;
  }
  if(genLepBar==0){
    std::cout << "leptonBar not found" << std::endl;
    return;
  }
  if(genNu==0){
    std::cout << "nu not found" << std::endl;
    return;
  }
  if(genNuBar==0){
    std::cout << "nuBar not found" << std::endl;
    return;
  }

  AddFourMomenta addFourMomenta;

  // combined top pair object
  reco::CompositeCandidate* genTtBar = new reco::CompositeCandidate();
  genTtBar->addDaughter(*genTop);
  genTtBar->addDaughter(*genTopBar);
  addFourMomenta.set(*genTtBar);

  // combined lepton pair object
  reco::CompositeCandidate* genLepPair = new reco::CompositeCandidate();
  genLepPair->addDaughter(*genLep);
  genLepPair->addDaughter(*genLepBar);
  addFourMomenta.set(*genLepPair);

  // combined lepton pair object
  reco::CompositeCandidate* genJetPair = new reco::CompositeCandidate();
  genJetPair->addDaughter(*genB);
  genJetPair->addDaughter(*genBBar);
  addFourMomenta.set(*genJetPair);

  // gen particle distributions
  fillGenHistos(TopGen_,    *genTop,     weight);
  fillGenHistos(WplusGen_,  *genWplus,   weight);
  fillGenHistos(BGen_,      *genB,       weight);
  fillGenHistos(LepBarGen_, *genLepBar,  weight);
  fillGenHistos(NuGen_,     *genNu,      weight);

  fillGenHistos(TopBarGen_, *genTopBar,  weight);
  fillGenHistos(WminusGen_, *genWminus,  weight);
  fillGenHistos(BBarGen_,   *genBBar,    weight);
  fillGenHistos(LepGen_,    *genLep,     weight);
  fillGenHistos(NuBarGen_,  *genNuBar,   weight);

  fillGenHistos(TtBarGen_,  *genTtBar,   weight);
  fillGenHistos(LepPairGen_,*genLepPair, weight);
  fillGenHistos(JetPairGen_,*genJetPair, weight);

  delete genTtBar;
  delete genLepPair;
  delete genJetPair;
}



void FullLepGenAnalyzer::endJob()
{
}



/// book histograms for generated particles properties: Pt, E, Eta, Phi, m
void
FullLepGenAnalyzer::bookGenHistos(edm::Service<TFileService>& fs)
{

  NameScheme ns("gen");

  TopGen_.push_back( fs->make<TH1D>(ns.name("TopPt"	 ), "p_{t} (t) [GeV]",100,  0. , 500. ) );
  TopGen_.push_back( fs->make<TH1D>(ns.name("TopEta"	 ), "#eta (t)"       ,100, -5.0,   5.0) );
  TopGen_.push_back( fs->make<TH1D>(ns.name("TopRapidity"), "rapidity (t)"   ,100, -5.0,   5.0) );
  TopGen_.push_back( fs->make<TH1D>(ns.name("TopPhi"	 ), "#phi (t)"       , 62, -3.1,   3.1) );
  TopGen_.push_back( fs->make<TH1D>(ns.name("TopMass"	 ), "M (top) [GeV]"  ,100,  0. , 500. ) );

  WplusGen_.push_back( fs->make<TH1D>(ns.name("WPlusPt"      ), "p_{t} (W^{+}) [GeV]",100,  0. , 500. ) );
  WplusGen_.push_back( fs->make<TH1D>(ns.name("WPlusEta"     ), "#eta (W^{+})"       ,100, -5.0,   5.0) );
  WplusGen_.push_back( fs->make<TH1D>(ns.name("WPlusRapidity"), "rapidity (W^{+})"   ,100, -5.0,   5.0) );
  WplusGen_.push_back( fs->make<TH1D>(ns.name("WPlusPhi"     ), "#phi (W^{+})"       , 62, -3.1,   3.1) );
  WplusGen_.push_back( fs->make<TH1D>(ns.name("WPlusMass"    ), "M (W^{+}) [GeV]"    ,100,  0. , 500. ) );

  BGen_.push_back( fs->make<TH1D>(ns.name("BPt"      ), "p_{t} (b) [GeV]",100,  0. , 500. ) );
  BGen_.push_back( fs->make<TH1D>(ns.name("BEta"     ), "#eta (b)"	 ,100, -5.0,   5.0) );
  BGen_.push_back( fs->make<TH1D>(ns.name("BRapidity"), "rapidity (b)"   ,100, -5.0,   5.0) );
  BGen_.push_back( fs->make<TH1D>(ns.name("BPhi"     ), "#phi (b)"	 , 62, -3.1,   3.1) );
  BGen_.push_back( fs->make<TH1D>(ns.name("BMass"    ), "M (b) [GeV]"	 ,100,  0. , 500. ) );

  LepBarGen_.push_back( fs->make<TH1D>(ns.name("LepBarPt"      ), "p_{t} (l^{+}) [GeV]",100,  0. , 500. ) );
  LepBarGen_.push_back( fs->make<TH1D>(ns.name("LepBarEta"     ), "#eta (l^{+})"       ,100, -5.0,   5.0) );
  LepBarGen_.push_back( fs->make<TH1D>(ns.name("LepBarRapidity"), "rapidity (l^{+})"   ,100, -5.0,   5.0) );
  LepBarGen_.push_back( fs->make<TH1D>(ns.name("LepBarPhi"     ), "#phi (l^{+})"       , 62, -3.1,   3.1) );
  LepBarGen_.push_back( fs->make<TH1D>(ns.name("LepBarMass"    ), "M (l^{+}) [GeV]"    ,100,  0. , 500. ) );

  NuGen_.push_back( fs->make<TH1D>(ns.name("NuPt"      ), "p_{t} (#nu^{-}) [GeV]",100,  0. , 500. ) );
  NuGen_.push_back( fs->make<TH1D>(ns.name("NuEta"     ), "#eta (#nu^{-})"	 ,100, -5.0,   5.0) );
  NuGen_.push_back( fs->make<TH1D>(ns.name("NuRapidity"), "rapidity (#nu^{-})"   ,100, -5.0,   5.0) );
  NuGen_.push_back( fs->make<TH1D>(ns.name("NuPhi"     ), "#phi (#nu^{-})"	 , 62, -3.1,   3.1) );
  NuGen_.push_back( fs->make<TH1D>(ns.name("NuMass"    ), "M (#nu^{-}) [GeV]"	 ,100,  0. , 500. ) );

  TopBarGen_.push_back( fs->make<TH1D>(ns.name("TopBarPt"      ), "p_{t} (#bar{t}) [GeV]",100,  0. , 500. ) );
  TopBarGen_.push_back( fs->make<TH1D>(ns.name("TopBarEta"     ), "#eta (#bar{t})"	 ,100, -5.0,   5.0) );
  TopBarGen_.push_back( fs->make<TH1D>(ns.name("TopBarRapidity"), "rapidity (#bar{t})"   ,100, -5.0,   5.0) );
  TopBarGen_.push_back( fs->make<TH1D>(ns.name("TopBarPhi"     ), "#phi (#bar{t})"	 , 62, -3.1,   3.1) );
  TopBarGen_.push_back( fs->make<TH1D>(ns.name("TopBarMass"    ), "M (#bar{t}) [GeV]"	 ,100,  0. , 500. ) );

  WminusGen_.push_back( fs->make<TH1D>(ns.name("WMinusPt"      ), "p_{t} (W^{-}) [GeV]",100,  0. , 500. ) );
  WminusGen_.push_back( fs->make<TH1D>(ns.name("WMinusEta"     ), "#eta (W^{-})"       ,100, -5.0,   5.0) );
  WminusGen_.push_back( fs->make<TH1D>(ns.name("WMinusRapidity"), "rapidity (W^{-})"   ,100, -5.0,   5.0) );
  WminusGen_.push_back( fs->make<TH1D>(ns.name("WMinusPhi"     ), "#phi (W^{-})"       , 62, -3.1,   3.1) );
  WminusGen_.push_back( fs->make<TH1D>(ns.name("WMinusMass"    ), "M (W^{-}) [GeV]"    ,100,  0. , 500. ) );

  BBarGen_.push_back( fs->make<TH1D>(ns.name("BBarPt"	   ), "p_{t} (#bar{b}) [GeV]",100,  0. , 500. ) );
  BBarGen_.push_back( fs->make<TH1D>(ns.name("BBarEta"     ), "#eta (#bar{b})"       ,100, -5.0,   5.0) );
  BBarGen_.push_back( fs->make<TH1D>(ns.name("BBarRapidity"), "rapidity (#bar{b})"   ,100, -5.0,   5.0) );
  BBarGen_.push_back( fs->make<TH1D>(ns.name("BBarPhi"     ), "#phi (#bar{b})"       , 62, -3.1,   3.1) );
  BBarGen_.push_back( fs->make<TH1D>(ns.name("BBarMass"    ), "M (#bar{b}) [GeV]"    ,100,  0. , 500. ) );

  LepGen_.push_back( fs->make<TH1D>(ns.name("LepPt"	 ), "p_{t} (l^{-}) [GeV]",100,  0. , 500. ) );
  LepGen_.push_back( fs->make<TH1D>(ns.name("LepEta"	 ), "#eta (l^{-})"	 ,100, -5.0,   5.0) );
  LepGen_.push_back( fs->make<TH1D>(ns.name("LepRapidity"), "rapidity (l^{-})"   ,100, -5.0,   5.0) );
  LepGen_.push_back( fs->make<TH1D>(ns.name("LepPhi"	 ), "#phi (l^{-})"	 , 62, -3.1,   3.1) );
  LepGen_.push_back( fs->make<TH1D>(ns.name("LepMass"	 ), "M (l^{-}) [GeV]"	 ,100,  0. , 500. ) );

  NuBarGen_.push_back( fs->make<TH1D>(ns.name("NuBarPt"      ), "p_{t} (#bar{#nu}^{-}) [GeV]",100,  0. , 500. ) );
  NuBarGen_.push_back( fs->make<TH1D>(ns.name("NuBarEta"     ), "#eta (#bar{#nu}^{-})"       ,100, -5.0,   5.0) );
  NuBarGen_.push_back( fs->make<TH1D>(ns.name("NuBarRapidity"), "rapidity (#bar{#nu}^{-})"   ,100, -5.0,   5.0) );
  NuBarGen_.push_back( fs->make<TH1D>(ns.name("NuBarPhi"     ), "#phi (#bar{#nu}^{-})"       , 62, -3.1,   3.1) );
  NuBarGen_.push_back( fs->make<TH1D>(ns.name("NuBarMass"    ), "M (#bar{#nu}^{-}) [GeV]"    ,100,  0. , 500. ) );

  TtBarGen_.push_back( fs->make<TH1D>(ns.name("TtBarPt"      ), "p_{t} (t#bar{t}) [GeV]",100,  0. , 500. ) );
  TtBarGen_.push_back( fs->make<TH1D>(ns.name("TtBarEta"     ), "#eta (t#bar{t})"       , 62, -3.1,   3.1) );
  TtBarGen_.push_back( fs->make<TH1D>(ns.name("TtBarRapidity"), "rapidity (t#bar{t})"   ,100, -5.0,   5.0) );
  TtBarGen_.push_back( fs->make<TH1D>(ns.name("TtBarPhi"     ), "#phi (t#bar{t})"       , 62, -3.1,   3.1) );
  TtBarGen_.push_back( fs->make<TH1D>(ns.name("TtBarMass"    ), "M (t#bar{t}) [GeV]"    ,400,  0. ,2000. ) );

  LepPairGen_.push_back( fs->make<TH1D>(ns.name("LepPairPt"	 ), "p_{t} (l^{+}l^{-}) [GeV]",100,  0. , 500. ) );
  LepPairGen_.push_back( fs->make<TH1D>(ns.name("LepPairEta"	 ), "#eta (l^{+}l^{-})"       ,100, -5.0,   5.0) );
  LepPairGen_.push_back( fs->make<TH1D>(ns.name("LepPairRapidity"), "rapidity (l^{+}l^{-})"   ,100, -5.0,   5.0) );
  LepPairGen_.push_back( fs->make<TH1D>(ns.name("LepPairPhi"	 ), "#phi (l^{+}l^{-})"       , 62, -3.1,   3.1) );
  LepPairGen_.push_back( fs->make<TH1D>(ns.name("LepPairMass"	 ), "M (l^{+}l^{-}) [GeV]"    ,200,  0. , 400. ) );

  JetPairGen_.push_back( fs->make<TH1D>(ns.name("JetPairPt"	 ), "p_{t} (jj) [GeV]",100,  0. , 500. ) );
  JetPairGen_.push_back( fs->make<TH1D>(ns.name("JetPairEta"	 ), "#eta (jj)"       ,100, -5.0,   5.0) );
  JetPairGen_.push_back( fs->make<TH1D>(ns.name("JetPairRapidity"), "rapidity (jj)"   ,100, -5.0,   5.0) );
  JetPairGen_.push_back( fs->make<TH1D>(ns.name("JetPairPhi"	 ), "#phi (jj)"       , 62, -3.1,   3.1) );
  JetPairGen_.push_back( fs->make<TH1D>(ns.name("JetPairMass"	 ), "M (jj) [GeV]"    ,100,  0. , 500. ) );
}



/// fill histograms
void
FullLepGenAnalyzer::fillGenHistos(std::vector<TH1D*>& histos, const reco::Candidate& candidate, double weight)
{
  histos[0]->Fill( candidate.pt(), weight      );
  histos[1]->Fill( candidate.eta(), weight     );
  histos[2]->Fill( candidate.rapidity(), weight);
  histos[3]->Fill( candidate.phi(), weight     );
  histos[4]->Fill( candidate.mass(), weight    );
}



const reco::Candidate* 
FullLepGenAnalyzer::getTauDaughter(const reco::Candidate* tau)
{
  for(size_t i=0; i<tau->numberOfDaughters(); ++i){
    if(fabs(tau->daughter(i)->pdgId())==11 || fabs(tau->daughter(i)->pdgId())==13) return tau->daughter(i);
    else if(fabs(tau->daughter(i)->pdgId())==15) return getTauDaughter(tau->daughter(i));
  }
  //return orgiginal tau if nothing found
  edm::LogWarning ( "No Tau Daughter" ) << "neither electron nor muon daughter found.";
  return tau;
} 


#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(FullLepGenAnalyzer);
