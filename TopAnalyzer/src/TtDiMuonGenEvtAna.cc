#include "TH1F.h"
#include "TH2F.h"
#include "TString.h"

#include "FWCore/Utilities/interface/EDMException.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"

#include "TopAnalysis/TopUtils/interface/NameScheme.h"
#include "TopAnalysis/TopAnalyzer/interface/TtDiMuonGenEvtAna.h"
#include "AnalysisDataFormats/TopObjects/interface/TtGenEvent.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

TtDiMuonGenEvtAna::TtDiMuonGenEvtAna(const edm::ParameterSet& cfg):
  genEvt_(cfg.getParameter<edm::InputTag>("genEvt"))
{
}

TtDiMuonGenEvtAna::~TtDiMuonGenEvtAna()
{
}

void
TtDiMuonGenEvtAna::book(ofstream& file)
{
  edm::Service<TFileService> fs;

  NameScheme e("gen");
  genMass_       = fs->make<TH1F>(e.name( file, "genMass")      , e.name("genMass")      , 50, 100., 300.);
  genNuSpectrum_ = fs->make<TH2F>(e.name( file, "genNuSpectrum"), e.name("genNuSpectrum"), 25,   0., 500., 25,   0., 500.);
}

void
TtDiMuonGenEvtAna::fill(const  edm::Event& evt,  
		       double weight)
{
  edm::Handle<TtGenEvent> genEvt; 
  evt.getByLabel(genEvt_, genEvt);
             
  const reco::GenParticle * top  = genEvt->top();   
  const reco::GenParticle * topB = genEvt->topBar();  
  
  genMass_ ->Fill(top ->mass(), weight);    
  genMass_ ->Fill(topB->mass(), weight);
  
  // fill neutrino spectrum only for gen dimuon decay  
  if(genEvt->numberOfLeptons()!=2) return; 
       
  const reco::GenParticle * lepP = genEvt->lepton();   
  const reco::GenParticle * lepM = genEvt->leptonBar();
  
  if(!lepP || !lepM) return;
  if(lepP->pdgId()!=-13 || lepM->pdgId()!=13) return;
   
  const reco::GenParticle * nu   = genEvt->neutrino();   
  const reco::GenParticle * nuB  = genEvt->neutrinoBar();  
    
  genNuSpectrum_->Fill(nu->energy(), nuB->energy());                           
}


void
TtDiMuonGenEvtAna::normSpectrum()
{
  double max = genNuSpectrum_->GetMaximum();
  for(int i=1; i<26; i++) {
    for(int k=1; k<26; k++) {
      double temp = genNuSpectrum_->GetBinContent(i,k);
      temp = temp/max;
      genNuSpectrum_->SetBinContent(i,k,temp);
    }
  }
  return;
}
