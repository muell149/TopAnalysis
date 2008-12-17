#include "TH1F.h"
#include "TMath.h"
#include "TString.h"

#include "FWCore/Utilities/interface/EDMException.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"

#include "TopAnalysis/TopUtils/interface/NameScheme.h"
#include "TopAnalysis/TopAnalyzer/interface/TtDiMuonTopObjAna.h"

TtDiMuonTopObjAna::TtDiMuonTopObjAna(const edm::ParameterSet& cfg):
  leptonPtCut_     ( cfg.getParameter<double>       ( "leptonPtCut"      ) ),  
  jetPtCut_        ( cfg.getParameter<double>       ( "jetPtCut"         ) ),
  metCut_          ( cfg.getParameter<double>       ( "metCut"           ) ),  
  muons_           ( cfg.getParameter<edm::InputTag>( "muons"            ) ),
  jets_            ( cfg.getParameter<edm::InputTag>( "jets"             ) ),
  mets_            ( cfg.getParameter<edm::InputTag>( "met"              ) )
{
}

TtDiMuonTopObjAna::~TtDiMuonTopObjAna()
{
}

void
TtDiMuonTopObjAna::book(ofstream& file)
{
  edm::Service<TFileService> fs;

  NameScheme e("obj_mu");
  muPt_     = fs->make<TH1F>(e.name( file, "pt"  ), e.name("pt"  ), 50,   0., 250.);
  muP_      = fs->make<TH1F>(e.name( file, "mom" ), e.name("mom" ), 60,   0., 300.);  
  muEta_    = fs->make<TH1F>(e.name( file, "eta" ), e.name("eta" ), 60,  -3.,   3 );  
  muPhi_    = fs->make<TH1F>(e.name( file, "phi" ), e.name("phi" ), 72,-180., 180.); 
  muN_      = fs->make<TH1F>(e.name( file, "N"   ), e.name("N"   ),  5, 1.5 , 6.5 );  
  
  NameScheme f("obj_jet");
  jetPt_ = fs->make<TH1F>(f.name( file, "pt"  ), f.name("pt"  ), 60,   0., 300.);   
  jetEt_ = fs->make<TH1F>(f.name( file, "et"  ), f.name("et"  ), 60,   0., 300.); 
  jetE_  = fs->make<TH1F>(f.name( file, "e"   ), f.name("e"   ), 60,   0., 300.);   
  jetEta_= fs->make<TH1F>(f.name( file, "eta" ), f.name("eta" ), 60,  -3.,   3.);   
  jetPhi_= fs->make<TH1F>(f.name( file, "phi" ), f.name("phi" ), 72,-180., 180.);
  jetN_  = fs->make<TH1F>(f.name( file, "N"   ), f.name("N"   ),  5, 1.5 , 6.5 ); 
      
  NameScheme g("obj_met");  
  met_      = fs->make<TH1F>(g.name( file, "et"   ), g.name("et" ), 50, 0.  , 250.); 
  metPhi_   = fs->make<TH1F>(g.name( file, "phi"  ), g.name("phi"), 72,-180., 180.);    
}

void
TtDiMuonTopObjAna::fill(const  edm::Event& evt, double weight)
{
  edm::Handle<PatMuonCollection> muons; 
  evt.getByLabel(muons_, muons);  
  PatMuonCollection::const_iterator muon = muons->begin();
  
  int i=0;  
  for( ; muon!=muons->end();++muon) {
    if(i>1) break;
    muPt_ ->Fill(muon->pt()                 , weight); 
    if(muon->pt()<leptonPtCut_) break;      
    muP_  ->Fill(muon->p()                  , weight);     
    muEta_->Fill(muon->eta()                , weight);     
    muPhi_->Fill(muon->phi()*180/TMath::Pi(), weight);  
    muN_  ->Fill(muons->size()              , weight);
    ++i;   
  }
    
  edm::Handle<PatJetCollection> jets; 
  evt.getByLabel(jets_, jets);  
  PatJetCollection::const_iterator jet = jets->begin();  

  i=0;  
  for( ; jet!=jets->end();++jet) {
    if(i>2) break;
    jetEt_ ->Fill(jet->pt()                 , weight);
    if(jet->pt()<jetPtCut_) break;    
    jetEt_ ->Fill(jet->et()                 , weight);
    jetE_  ->Fill(jet->energy()             , weight);    
    jetEta_->Fill(jet->eta()                , weight);    
    jetPhi_->Fill(jet->phi()*180/TMath::Pi(), weight);
    jetN_  ->Fill(jets->size()              , weight);
    ++i;         
  } 
          
  edm::Handle<PatMETCollection> mets; 
  evt.getByLabel(mets_, mets);    
  PatMETCollection::const_iterator met = mets->begin();   
 
  for( ; met!=mets->end();++met) { 
    met_   ->Fill(met->et()                 , weight);
    if(met->et()<metCut_) break;      
    metPhi_->Fill(met->phi()*180/TMath::Pi(), weight);    
  }                  
}

