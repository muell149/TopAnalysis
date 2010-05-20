#include "TopAnalysis/TopAnalyzer/interface/FullHadKinFit.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "PhysicsTools/KinFitter/interface/TFitConstraintM.h"
#include "PhysicsTools/KinFitter/interface/TFitConstraintMGaus.h"
#include "PhysicsTools/KinFitter/interface/TFitParticleEtEtaPhi.h"
#include "PhysicsTools/KinFitter/interface/TKinFitter.h"

/// default constructor
FullHadKinFit::FullHadKinFit(const edm::ParameterSet& cfg) : rnd(0)
{
  src_       = cfg.getParameter<edm::InputTag>("src");
  smearOnly_ = cfg.getParameter<int>("smearOnly");
  smear_     = cfg.getParameter<double>("smear");
  resol_     = cfg.getParameter<double>("resol");
}

/// do generator matching
void
FullHadKinFit::genMatcher(const edm::View<reco::LeafCandidate>& src)
{
  std::vector<const reco::GenParticle*> parts = dynCastVector<reco::GenParticle>( src );
  //std::vector<const reco::GenParticle*> parts(src.size());
  //std::transform(src.begin(),src.end(),parts.begin(),F<reco::GenParticle>());
  //parts.erase(std::remove_if(parts.begin(), parts.end(),std::bind2nd(std::equal_to<const reco::GenParticle*>(), 0)),parts.end());

  if(parts.size()){

    genParticles.resize(6);
    
    for(std::vector<const reco::GenParticle*>::const_iterator obj = parts.begin(); obj != parts.end(); ++obj){
      
      if((*obj)->status() == 3){
	
	if((*obj)->mother()){
	  if((*obj)->mother()->mother()){
	    if((*obj)->pdgId() ==   5 && (*obj)->mother()->mother()->pdgId() ==  6) genParticles[B]    = *obj;
	    if((*obj)->pdgId() ==  -5 && (*obj)->mother()->mother()->pdgId() == -6) genParticles[BBar] = *obj;
	  }
	  if((*obj)->pdgId() < 5 && (*obj)->pdgId() > -5 && (*obj)->pdgId() != 0) {
	    if((*obj)->pdgId() > 0 && (*obj)->mother()->pdgId() ==  24) genParticles[LQ]    = *obj;
	    if((*obj)->pdgId() < 0 && (*obj)->mother()->pdgId() ==  24) genParticles[LQBar] = *obj;
	    if((*obj)->pdgId() > 0 && (*obj)->mother()->pdgId() == -24) genParticles[LP]    = *obj;
	    if((*obj)->pdgId() < 0 && (*obj)->mother()->pdgId() == -24) genParticles[LPBar] = *obj;
	  }
	}
      }
    }
  }
}

/// smear input vectors for kinematic fit
void
FullHadKinFit::smear(std::vector< TLorentzVector >& vecs){
  Double_t phi, pt, eta, e;
  for(std::vector< TLorentzVector >::iterator vec = vecs.begin(); vec != vecs.end(); ++vec){
    if( smearOnly_ == -1 || smearOnly_ == vec - vecs.begin() ){
      pt = -1.0;
      while( pt < 0 ){
	pt = rnd.Gaus( vec->Pt(), smear_ * 0.3 * sqrt( vec->Pt() ) );
      }
      eta = rnd.Gaus( vec->Eta(), smear_ * 0.5 * sqrt( vec->Pt() ) / vec->Pt() );
      phi = rnd.Gaus( vec->Phi(), smear_ * 0.5 * sqrt( vec->Pt() ) / vec->Pt() );
      if( phi >= TMath::Pi() ) phi -= 2* TMath::Pi();
      if( phi < -TMath::Pi() ) phi += 2* TMath::Pi();
      e = vec->E() * ( pt / vec->Pt() );
      //std::cout << "-------------------" << std::endl;
      //std::cout << "pt:  " << vec->Pt()  << " +- " << 0.5 * sqrt( vec->Pt() )                          << " -> " << pt  << std::endl;
      //std::cout << "eta: " << vec->Eta() << " +- " << 0.2 * vec->Eta() * sqrt( vec->Pt() ) / vec->Pt() << " -> " << eta << std::endl;
      //std::cout << "phi: " << vec->Phi() << " +- " << 0.1                                              << " -> " << phi << std::endl;
      //std::cout << "e:   " << vec->E()   << " +- " << 0.5 * sqrt( vec->E() )                           << " -> " << e   << std::endl;
      //if(pt > e) std::cout << "--==!! ERROR !!==--" << std::endl << "pt > e : " << pt << " > " << e << std::endl;
      vec->SetPtEtaPhiE( pt, eta, phi, e );
      //vec->SetPtEtaPhiM( pt, eta, phi, m );
    }
  }
}

/// function to find types of jet-combinations in KinFits (1 right, 2 branches right, but inner-branche particles mixup, 3 inter-branch mixup, 4 missing jet)
int
FullHadKinFit::comboType(std::vector< unsigned int > combi)
{
  int bFit         = combi[B];
  int lightQFit    = combi[LQ];
  int lightQBarFit = combi[LQBar];
  int bBarFit      = combi[BBar];
  int lightPFit    = combi[LP];
  int lightPBarFit = combi[LPBar];

  int bGen         = 0;
  int lightQGen    = 1;
  int lightQBarGen = 2;
  int bBarGen      = 3;
  int lightPGen    = 4;
  int lightPBarGen = 5;

  std::list<int> fit;
  std::list<int> fitBar;
  std::list<int> gen;
  std::list<int> genBar;

  fit.push_back(combi[B]);
  fit.push_back(combi[LQ]);
  fit.push_back(combi[LQBar]);

  fitBar.push_back(combi[BBar]);
  fitBar.push_back(combi[LP]);
  fitBar.push_back(combi[LPBar]);

  gen.push_back(0);
  gen.push_back(1);
  gen.push_back(2);

  genBar.push_back(3);
  genBar.push_back(4);
  genBar.push_back(5);

  if( ( bFit == bGen && bBarFit == bBarGen ) || ( bFit == bBarGen && bBarFit == bGen ) ) {

    if( bFit == bGen &&
	( ( lightQFit == lightQGen    && lightQBarFit == lightQBarGen ) ||
	  ( lightQFit == lightQBarGen && lightQBarFit == lightQGen    ) ) &&
	( ( lightPFit == lightPGen    && lightPBarFit == lightPBarGen ) ||
	  ( lightPFit == lightPBarGen && lightPBarFit == lightPGen    ) ) )
      return 1;
    
    if( bBarFit == bGen &&
	( ( lightPFit == lightQGen    && lightPBarFit == lightQBarGen ) ||
	  ( lightPFit == lightQBarGen && lightPBarFit == lightQGen    ) ) &&
	( ( lightQFit == lightPGen    && lightQBarFit == lightPBarGen ) ||
	  ( lightQFit == lightPBarGen && lightQBarFit == lightPGen    ) ) )
      return 1;
  }

  fit.sort();
  fitBar.sort();
  gen.sort();
  genBar.sort();

  if( ( fit == gen && fitBar == genBar ) || ( fit == genBar && fitBar == gen ) ) return 2;

  fit.splice(fit.end(),fitBar);
  gen.splice(gen.end(),genBar);

  fit.sort();
  fitBar.sort();

  if( fit == gen ) return 3;

  return 4;
}

/// definition of resolutions to be used in kinematic fit
Double_t
FullHadKinFit::ErrEt(Float_t Et, Float_t Eta) {
  /*
  Double_t InvPerr2, a, b, c;
  if(fabs(Eta) < 1.4){
    a = 5.6;
    b = 1.25;
    c = 0.033;
  }
  else{
    a = 4.8;
    b = 0.89;
    c = 0.043;
  }
  InvPerr2 = (a * a) + (b * b) * Et + (c * c) * Et * Et;
  return 0.1 * InvPerr2;
 */ 
  return resol_ * 0.3 * sqrt( Et );
}

Double_t
FullHadKinFit::ErrEta(Float_t Et, Float_t Eta) {
  /*
  Double_t InvPerr2, a, b, c;
  if(fabs(Eta) < 1.4){
    a = 1.215;
    b = 0.037;
    c = 7.941 * 0.0001;
  }
  else{
    a = 1.773;
    b = 0.034;
    c = 3.56 * 0.0001;
  }
  InvPerr2 = a/(Et * Et) + b/Et + c;
  return 0.1 * InvPerr2;
*/
  return resol_ * 0.5 * sqrt( Et ) / Et;
}

Double_t
FullHadKinFit::ErrPhi(Float_t Et, Float_t Eta) {
  /*
  Double_t InvPerr2, a, b, c;
  if(fabs(Eta) < 1.4){
    a = 6.65;
    b = 0.04;
    c = 8.49 * 0.00001;
  }
  else{
    a = 2.908;
    b = 0.021;
    c = 2.59 * 0.0001;
  }
  InvPerr2 = a/(Et * Et) + b/Et + c;
  return 0.1 * InvPerr2;
  */
  return resol_ * 0.5 * sqrt( Et ) / Et;
}

/// initiate histograms
void
FullHadKinFit::beginJob()
{
  edm::Service<TFileService> fs;
  if( !fs ) throw edm::Exception( edm::errors::Configuration, "TFile Service is not registered in cfg file" );

  eventCounter = 0;
  fullHadCounter = 0;
  fitCounter = 0;

  hists_["chi2"    ] = fs->make<TH1F>( "chi2"     , "Chi2;#chi^{2};" , 100 , 0.  , 1.  );
  hists_["prob"    ] = fs->make<TH1F>( "prob"     , "Prob;Prob;"     , 100 , 0.  , 1.  );
  hists_["combo"   ] = fs->make<TH1F>( "combo"    , "Combo;Combo;"   ,   4 , 0.5 , 4.5 );
  hists_["ptGenRec"] = fs->make<TH1F>( "ptGenRec" , "ptGenRec;#frac{pt_{rec}}{pt_{gen}};"   , 500 , 0. , 10. );
  hists_["mTop"    ] = fs->make<TH1F>( "mTop"     , "mTop;m_{top};"   , 500 , 0. , 400. );

}

/// analyze kinFit and fill histograms
void
FullHadKinFit::analyze(const edm::Event& event, const edm::EventSetup&)
{
  ++eventCounter;

  edm::Handle<edm::View< reco::LeafCandidate > > src;
  event.getByLabel(src_, src);

  genMatcher(*src);

  if(genParticles.size()){
    if(genParticles[B] && genParticles[BBar] && genParticles[LQ] && genParticles[LQBar] && genParticles[LP] && genParticles[LPBar]){

      ++fullHadCounter;

      // store results of the kinematic fit
      std::list< KinFitResult > fitResults;

      std::vector< TLorentzVector > vecs;
      vecs.push_back( TLorentzVector( genParticles[B]    ->px(), genParticles[B]    ->py(), genParticles[B]    ->pz(), genParticles[B]    ->energy() ) );
      vecs.push_back( TLorentzVector( genParticles[LQ]   ->px(), genParticles[LQ]   ->py(), genParticles[LQ]   ->pz(), genParticles[LQ]   ->energy() ) );
      vecs.push_back( TLorentzVector( genParticles[LQBar]->px(), genParticles[LQBar]->py(), genParticles[LQBar]->pz(), genParticles[LQBar]->energy() ) );
      vecs.push_back( TLorentzVector( genParticles[BBar] ->px(), genParticles[BBar] ->py(), genParticles[BBar] ->pz(), genParticles[BBar] ->energy() ) );
      vecs.push_back( TLorentzVector( genParticles[LP]   ->px(), genParticles[LP]   ->py(), genParticles[LP]   ->pz(), genParticles[LP]   ->energy() ) );
      vecs.push_back( TLorentzVector( genParticles[LPBar]->px(), genParticles[LPBar]->py(), genParticles[LPBar]->pz(), genParticles[LPBar]->energy() ) );

      std::vector< TLorentzVector > genVecs = vecs;

      if(smear_) smear(vecs);

      std::vector< TLorentzVector > smearVecs = vecs;

      TMatrixD m0(3,3);
      TMatrixD m1(3,3);
      TMatrixD m2(3,3);
      TMatrixD m3(3,3);
      TMatrixD m4(3,3);
      TMatrixD m5(3,3);
      m0.Zero();
      m1.Zero();
      m2.Zero();
      m3.Zero();
      m4.Zero();
      m5.Zero();

      //In this example the covariant matrix depends on the transverse energy and eta of the jets
      m0(0,0) = ErrEt (vecs[0].Et(), vecs[0].Eta()); // et
      m0(1,1) = ErrEta(vecs[0].Et(), vecs[0].Eta()); // eta
      m0(2,2) = ErrPhi(vecs[0].Et(), vecs[0].Eta()); // phi

      m1(0,0) = ErrEt (vecs[1].Et(), vecs[1].Eta()); // et
      m1(1,1) = ErrEta(vecs[1].Et(), vecs[1].Eta()); // eta
      m1(2,2) = ErrPhi(vecs[1].Et(), vecs[1].Eta()); // phi

      m2(0,0) = ErrEt (vecs[2].Et(), vecs[2].Eta()); // et
      m2(1,1) = ErrEta(vecs[2].Et(), vecs[2].Eta()); // eta
      m2(2,2) = ErrPhi(vecs[2].Et(), vecs[2].Eta()); // phi

      m3(0,0) = ErrEt (vecs[3].Et(), vecs[3].Eta()); // et
      m3(1,1) = ErrEta(vecs[3].Et(), vecs[3].Eta()); // eta
      m3(2,2) = ErrPhi(vecs[3].Et(), vecs[3].Eta()); // phi

      m4(0,0) = ErrEt (vecs[4].Et(), vecs[4].Eta()); // et
      m4(1,1) = ErrEta(vecs[4].Et(), vecs[4].Eta()); // eta
      m4(2,2) = ErrPhi(vecs[4].Et(), vecs[4].Eta()); // phi

      m5(0,0) = ErrEt (vecs[5].Et(), vecs[5].Eta()); // et
      m5(1,1) = ErrEta(vecs[5].Et(), vecs[5].Eta()); // eta
      m5(2,2) = ErrPhi(vecs[5].Et(), vecs[5].Eta()); // phi

      std::vector< TMatrixD > mats;
      mats.push_back( m0 );
      mats.push_back( m1 );
      mats.push_back( m2 );
      mats.push_back( m3 );
      mats.push_back( m4 );
      mats.push_back( m5 );

      std::vector< unsigned int > combi(6);
      combi[B]     = 0;
      combi[LQ]    = 1;
      combi[LQBar] = 2;
      combi[BBar]  = 3;
      combi[LP]    = 4;
      combi[LPBar] = 5;

      for(unsigned int cnt=0; cnt<TMath::Factorial(combi.size()); ++cnt){
	if( combi[LQ] < combi[LQBar] ||
	    combi[LP] < combi[LPBar] ||
	    combi[B]  < combi[BBar]  ){

	  TFitParticleEtEtaPhi *cand_b     = new TFitParticleEtEtaPhi( "cand_b"    , "cand_b"    , &vecs[combi[B]]    , &mats[combi[B]]     );
	  TFitParticleEtEtaPhi *cand_bBar  = new TFitParticleEtEtaPhi( "cand_bBar" , "cand_bBar" , &vecs[combi[BBar]] , &mats[combi[BBar]]  );
	  TFitParticleEtEtaPhi *cand_lQ    = new TFitParticleEtEtaPhi( "cand_lQ"   , "cand_lQ"   , &vecs[combi[LQ]]   , &mats[combi[LQ]]    );
	  TFitParticleEtEtaPhi *cand_lQBar = new TFitParticleEtEtaPhi( "cand_lQBar", "cand_lQBar", &vecs[combi[LQBar]], &mats[combi[LQBar]] );
	  TFitParticleEtEtaPhi *cand_lP    = new TFitParticleEtEtaPhi( "cand_lP"   , "cand_lP"   , &vecs[combi[LP]]   , &mats[combi[LP]]    );
	  TFitParticleEtEtaPhi *cand_lPBar = new TFitParticleEtEtaPhi( "cand_lPBar", "cand_lPBar", &vecs[combi[LPBar]], &mats[combi[LPBar]] );

	  //TFitConstraintM *mCons1 = new TFitConstraintM( "WMassConstraint1", "WMass-Constraint1", 0, 0 , 80.4 );
	  TFitConstraintMGaus *mCons1 = new TFitConstraintMGaus( "WMassConstraint1", "WMass-Constraint1", 0, 0 , 80.4 , 2.141 );
	  mCons1->addParticles1( cand_lQ, cand_lQBar );
	  //TFitConstraintM *mCons2 = new TFitConstraintM( "WMassConstraint2", "WMass-Constraint2", 0, 0 , 80.4 );
	  TFitConstraintMGaus *mCons2 = new TFitConstraintMGaus( "WMassConstraint2", "WMass-Constraint2", 0, 0 , 80.4 , 2.141 );
	  mCons2->addParticles1( cand_lP, cand_lPBar );
	  TFitConstraintM *mCons3 = new TFitConstraintM( "EqualTopMasses", "EqualTopMasses" , 0 , 0 , 0 );
	  //TFitConstraintMGaus *mCons3 = new TFitConstraintMGaus( "EqualTopMasses", "EqualTopMasses" , 0 , 0 , 0 , 10. );
	  mCons3->addParticles1( cand_b   , cand_lQ, cand_lQBar );
	  mCons3->addParticles2( cand_bBar, cand_lP, cand_lPBar );

	  //Definition of the fitter
	  TKinFitter* fitter = new TKinFitter("fitter", "fitter");
	  //Add measured particles(jets)
	  fitter->addMeasParticle( cand_b     );
	  fitter->addMeasParticle( cand_bBar  );
	  fitter->addMeasParticle( cand_lQ    );
	  fitter->addMeasParticle( cand_lQBar );
	  fitter->addMeasParticle( cand_lP    );
	  fitter->addMeasParticle( cand_lPBar );
	  //Add constraints
	  fitter->addConstraint( mCons1 );
	  fitter->addConstraint( mCons2 );
	  fitter->addConstraint( mCons3 );

	  //Set convergence criteria
	  fitter->setMaxNbIter( 300 );
	  fitter->setMaxDeltaS( 1e-2 );
	  fitter->setMaxF( 1e-1 );
	  fitter->setVerbosity(1);

	  //Perform the fit
	  fitter->fit();
	  if(fitter->getStatus() == 0){
	    
	    std::vector< TLorentzVector > helperVec;
	    helperVec.push_back(*cand_b    ->getCurr4Vec());
	    helperVec.push_back(*cand_lQ   ->getCurr4Vec());
	    helperVec.push_back(*cand_lQBar->getCurr4Vec());
	    helperVec.push_back(*cand_bBar ->getCurr4Vec());
	    helperVec.push_back(*cand_lP   ->getCurr4Vec());
	    helperVec.push_back(*cand_lPBar->getCurr4Vec());

	    KinFitResult result;
	    result.GenVecs = genVecs;
	    result.IniVecs = smearVecs;
	    result.FitVecs = helperVec;
	    result.Chi2 = fitter->getS();
	    result.NDF = fitter->getNDF();
	    result.Prob = TMath::Prob(result.Chi2, result.NDF);
	    result.JetCombi = combi;
	    fitResults.push_back( result );
	  }

	  delete cand_b;
	  delete cand_bBar;
	  delete cand_lQ;
	  delete cand_lQBar;
	  delete cand_lP;
	  delete cand_lPBar;
	  delete mCons1;
	  delete mCons2;
	  delete mCons3;
	  delete fitter;
	}
	std::next_permutation( combi.begin(), combi.end() );
      }
      fitResults.sort();

      if(fitResults.size()) ++fitCounter;

      hists_.find("chi2" )->second->Fill(fitResults.front().Chi2);
      hists_.find("prob" )->second->Fill(fitResults.front().Prob);
      hists_.find("combo")->second->Fill(comboType(fitResults.front().JetCombi));
      hists_.find("mTop" )->second->Fill( (fitResults.front().FitVecs[B] + fitResults.front().FitVecs[LQ] + fitResults.front().FitVecs[LQBar]).M() );

      std::vector< TLorentzVector >::const_iterator vec_gen = fitResults.front().GenVecs.begin();
      for(std::vector< TLorentzVector >::const_iterator vec = fitResults.front().FitVecs.begin() ; vec != fitResults.front().FitVecs.end() ; ++vec, ++vec_gen){
	if(vec_gen == fitResults.front().GenVecs.end()) break;
	if(smearOnly_ == -1 || smearOnly_ == vec - fitResults.front().FitVecs.begin())	hists_.find("ptGenRec")->second->Fill(vec->Pt()/vec_gen->Pt());
      }

    }
  }
  genParticles.clear();
}

void
FullHadKinFit::endJob()
{
  std::cout << " Total Events   : " << eventCounter   << std::endl;
  std::cout << " Fully hadronic : " << fullHadCounter << std::endl;
  std::cout << " Fitted events  : " << fitCounter     << std::endl;
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( FullHadKinFit );
