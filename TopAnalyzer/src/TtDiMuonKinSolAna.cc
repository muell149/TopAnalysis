#include "TF1.h"
#include "TH1F.h"
#include "TMath.h"
#include "TString.h"
#include "TLorentzVector.h"

#include "FWCore/Utilities/interface/EDMException.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"

#include "TopAnalysis/TopAnalyzer/interface/TtDiMuonKinSolAna.h"
#include "AnalysisDataFormats/TopObjects/interface/TtDilepEvtSolution.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"

TtDiMuonKinSolAna::TtDiMuonKinSolAna(const edm::ParameterSet& cfg): 
  solutions_         ( cfg.getParameter<edm::InputTag>( "solutions"         ) ),
  muons_             ( cfg.getParameter<edm::InputTag>( "muons"             ) ),    
  leptonPtCut_       ( cfg.getParameter<double>       ( "leptonPtCut"       ) ),  
  jetPtCut_          ( cfg.getParameter<double>       ( "jetPtCut"          ) ),
  metCut_            ( cfg.getParameter<double>       ( "metCut"            ) ),  
  diMuonMassLowZCut_ ( cfg.getParameter<double>       ( "diMuonMassLowZCut"  ) ),  
  diMuonMassHighZCut_( cfg.getParameter<double>       ( "diMuonMassHighZCut" ) ),
  diMuonMassQCDCut_  ( cfg.getParameter<double>       ( "diMuonMassQCDCut"   ) )  
{
}


TtDiMuonKinSolAna::~TtDiMuonKinSolAna()
{
}

void 
TtDiMuonKinSolAna::book(ofstream& file)
{
  edm::Service<TFileService> fs;

  NameScheme e("kin");
  mass_         = fs->make<TH1F>(e.name( file, "mass"        ), e.name("mass"        ), 51,  99., 301.);
  dimuonmass_   = fs->make<TH1F>(e.name( file, "dimuonmass"  ), e.name("dimuonmass"  ), 50,   0., 250.); 
  weightmax_    = fs->make<TH1F>(e.name( file, "weightmax"   ), e.name("weightmax"   ), 50,   0.,   1.);
  maxweightmax_ = fs->make<TH1F>(e.name( file, "maxweightmax"), e.name("maxweightmax"), 50,   0.,   1.);
  massBbW_      = fs->make<TH1F>(e.name( file, "massBbW"     ), e.name("massBbW"     ), 51,  99., 301.);
  massBbM_      = fs->make<TH1F>(e.name( file, "massBbM"     ), e.name("massBbM"     ), 51,  99., 301.);  
  muPt_         = fs->make<TH1F>(e.name( file, "muPt"        ), e.name("muPt"        ), 60,   0., 300.);  
  jetPt_        = fs->make<TH1F>(e.name( file, "jetPt"       ), e.name("jetPt"       ), 60,   0., 300.);   
  met_          = fs->make<TH1F>(e.name( file, "met"         ), e.name("met"         ), 60,   0., 300.);   
}

int Nsolutions = 0;

void
TtDiMuonKinSolAna::fill(const  edm::Event& evt, 
		       double weight)
{

  // first take a look on the two leading muons and make z-veto
  edm::Handle<std::vector<pat::Muon> > muons; 
  evt.getByLabel(muons_, muons);
   
  int i=0;
  TLorentzVector DiMuonLVector = TLorentzVector(0, 0 , 0, 0);
  TLorentzVector muLVector    = TLorentzVector(0, 0 , 0, 0);
   
  std::vector<pat::Muon>::const_iterator mu = muons->begin();
  for( ;mu!= muons->end(); ++mu) {
    if(i<2){
      muPt_->Fill(mu->pt(), weight);
      muLVector = TLorentzVector(mu->px(), mu->py(), mu->pz(), mu->energy());
      DiMuonLVector += muLVector;
    }
    else break;
  }   
    
  double DiMuonMass = (DiMuonLVector).M();    
  dimuonmass_->Fill( DiMuonMass, weight);
    
  if( (DiMuonMass > diMuonMassLowZCut_ && DiMuonMass < diMuonMassHighZCut_ ) || DiMuonMass < diMuonMassQCDCut_ ) return;
  
  // solutions   
  edm::Handle<TtDilepEvtSolCollection> solutions; 
  evt.getByLabel(solutions_, solutions);
  
  double maxWeight   = 0;
  double bestTopmass = 0;
    
  TtDilepEvtSolCollection::const_iterator sol = solutions->begin();
  for( ;sol!= solutions->end(); ++sol) {
    // check for dummy solution
    if(!sol->getRecTopMass()) continue;

    // Jet Et cut
    pat::Jet BJet = sol->getJetB();
    pat::Jet BbJet= sol->getJetBbar();
    
    jetPt_->Fill(BJet.pt(),  weight);
    jetPt_->Fill(BbJet.pt(), weight);
    
    if(BJet.pt() < jetPtCut_ || BbJet.pt() < jetPtCut_) continue;    
  
    // MET cut
    pat::MET met = sol->getMET();
    
    met_->Fill(met.et(), weight);
    
    if(met.et() < metCut_) continue;

    double topmass = sol->getRecTopMass(); 
    mass_ ->Fill( topmass, weight);
         
    double weightmax = sol->getRecWeightMax();
    weightmax_ ->Fill( weightmax, weight); 
 
    // find best solution using the maximum weight in the event    
    if(weightmax > maxWeight) { 
      maxWeight       = weightmax;
      bestTopmass     = topmass; 
    }     
    // find best solution using MC matching
    if(sol->getBestSol()) {
      massBbM_ ->Fill(topmass, weight);
    }              
  }
  if(maxWeight > 0) {
    maxweightmax_ ->Fill(maxWeight, weight);
    massBbW_      ->Fill(bestTopmass, weight);
  }     
}


void 
TtDiMuonKinSolAna::fithists()
{ 
  this ->fit(mass_   );
  this ->fit(massBbW_);
  this ->fit(massBbM_);
}


double 
breitwigner(double *x, double *par) 
{
  double norm = par[0], mw = par[1], gw = par[2], mw2, gw2, eb2;
  mw2 = mw*mw;
  gw2 = gw*gw;
  eb2 = x[0]*x[0];
  return norm*( gw2*mw2 / ( pow( eb2 - mw2, 2 ) + mw2 * gw2 ) );
}

void
TtDiMuonKinSolAna::fit(TH1F * hist)
{
  TF1 *fitfunc = new TF1("fitfunc", breitwigner, 100, 300, 3);
  double norm  = hist->GetMaximum();
  double max   = 100+(2*hist->GetMaximumBin());  
  double width = hist->GetRMS(); 
  
  cout << endl << "    maximum = " << norm  << endl;
  cout << endl << "maximum bin = " << max   << endl;  
  cout << endl << "      width = " << width << endl;    
   
  fitfunc->SetParameters(norm,max,width);  
  int fitRange = 8;  //in bins around the maximum
  
  int maxBinAll   = hist->GetMaximumBin();  
  int lowLimitAll = 100;
  int uppLimitAll = 300;  
  if(maxBinAll - fitRange > 0) {
    lowLimitAll = 100 + 4*(maxBinAll - fitRange);
  }
  if(maxBinAll + fitRange < 50) {
    uppLimitAll = 100 + 4*(maxBinAll + fitRange);
  }
  
  hist ->Fit("fitfunc","M","E",lowLimitAll, uppLimitAll);
}  



