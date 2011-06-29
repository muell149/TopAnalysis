#include "DataFormats/PatCandidates/interface/Jet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "AnalysisDataFormats/TopObjects/interface/TtFullHadEvtPartons.h"

#include "TopAnalysis/TopAnalyzer/interface/FullHadQCDEstimation.h"
#include "TopAnalysis/TopAnalyzer/interface/FullHadTopReco.h"

/// default constructor
FullHadQCDEstimation::FullHadQCDEstimation(const edm::ParameterSet& cfg) :
  JetSrc_            (cfg.getParameter<edm::InputTag>("JetSrc")),
  MultiJetMVADiscSrc_(cfg.getParameter<edm::InputTag>("MultiJetMVADiscSrc")),
  useTree_           ( cfg.getParameter<bool>( "useTree" ) ),
  bTagAlgoWP_        ( cfg.getParameter<std::string>( "bTagAlgoWP" ) )
{
  
  if(cfg.exists("udscResolutions") && cfg.exists("bResolutions")){
    udscResolutions_ = cfg.getParameter <std::vector<edm::ParameterSet> >("udscResolutions");
    bResolutions_    = cfg.getParameter <std::vector<edm::ParameterSet> >("bResolutions");
  }
  else if(cfg.exists("udscResolutions") || cfg.exists("bResolutions")){
    if(cfg.exists("udscResolutions")) throw cms::Exception("WrongConfig") << "Parameter 'bResolutions' is needed if parameter 'udscResolutions' is defined!\n";
    else                              throw cms::Exception("WrongConfig") << "Parameter 'udscResolutions' is needed if parameter 'bResolutions' is defined!\n";
  }

  // define kinematic fit interface
  unsigned constr[] = {1,2,5};
  std::vector<unsigned> constraints_(constr, constr + sizeof(constr) / sizeof(unsigned));
  std::string jecLevel = "L2L3Residual";
  if(bTagAlgoWP_ == "TCHEM40MC") jecLevel = "L3Absolute";
  // define kinematic fit interface
  //TtFullHadKinFitter::KinFit(bool useBTagging, unsigned int bTags, std::string bTagAlgo, double minBTagValueBJet, double maxBTagValueNonBJet,
  //			       std::vector<edm::ParameterSet> udscResolutions, std::vector<edm::ParameterSet> bResolutions, double resolutionSmearFactor,
  //			       std::string jetCorrectionLevel, int maxNJets, int maxNComb,
  //			       unsigned int maxNrIter, double maxDeltaS, double maxF, unsigned int jetParam, std::vector<unsigned> constraints, double mW, double mTop)
  kinFitter = new TtFullHadKinFitter::KinFit(true, 2, "myPseudoBTags", 0.5, 0.5,
					     udscResolutions_, bResolutions_, 1.1,
					     jecLevel, -1, -1,
					     500, 5e-5, 0.0001, 1, constraints_, 80.4, 173.);
  
  tree = 0;
}

/// histogramm booking
void
FullHadQCDEstimation::beginJob()
{
  // define TFileService which takes care of writing contents to root file
  edm::Service<TFileService> fs;
  if( !fs ) throw edm::Exception( edm::errors::Configuration, "TFile Service is not registered in cfg file" );

  /** 
      Kinematic Variables
  **/

  // jet pt and eta for later parametrization
  bookVariable( fs, "jet1_pt"  );
  bookVariable( fs, "jet2_pt"  );
  bookVariable( fs, "jet1_eta" );
  bookVariable( fs, "jet2_eta" );
  
  // properties of kinematic fit for the tree
  bookVariable( fs, "topMass" );
  bookVariable( fs, "prob" );
  bookVariable( fs, "chi2" );
  bookVariable( fs, "ttbarPt" );
  bookVariable( fs, "ttbarMass" );
  bookVariable( fs, "bAngle" );
  bookVariable( fs, "multiJetMVADisc" );

  // top mass of kinematic fit  using pt parametrisation
  //bookVariable( fs, "topQuarkMassHypo" );
  bookVariable( fs, "topQuarkMassHypo_pt"    , 1000,  0. , 1000. , useTree_ );
  bookVariable( fs, "topQuarkMassHypoAll_pt" , 1000,  0. , 1000. , useTree_ );

  // top mass of kinematic fit using eta parametrisation
  bookVariable( fs, "topQuarkMassHypo_eta"    , 1000,  0. , 1000. , useTree_ );
  bookVariable( fs, "topQuarkMassHypoAll_eta" , 1000,  0. , 1000. , useTree_ );

  // top mass of kinematic fit using no parametrisation
  bookVariable( fs, "topQuarkMassHypo_no"    , 1000,  0. , 1000. , useTree_ );
  bookVariable( fs, "topQuarkMassHypoAll_no" , 1000,  0. , 1000. , useTree_ );

  // invariant ttbar mass
  //bookVariable( fs, "ttbarInvMassHypo" );
  bookVariable( fs, "ttbarInvMassHypo_pt"  , 750,  0. , 1500. , useTree_ );
  bookVariable( fs, "ttbarInvMassHypo_eta" , 750,  0. , 1500. , useTree_ );
  bookVariable( fs, "ttbarInvMassHypo_no"  , 750,  0. , 1500. , useTree_ );

  // pt of ttbar system of hypothesis
  //bookVariable( fs, "ttbarPtHypo" );
  bookVariable( fs, "ttbarPtHypo_pt"  , 750, 0. , 1500. , useTree_ );
  bookVariable( fs, "ttbarPtHypo_eta" , 750, 0. , 1500. , useTree_ );
  bookVariable( fs, "ttbarPtHypo_no"  , 750, 0. , 1500. , useTree_ );

  // theta* of W bosons of hypothesis
  bookVariable( fs, "thetaStarHypo_pt"  , 320,  0. , M_PI , false );
  bookVariable( fs, "thetaStarHypo_eta" , 320,  0. , M_PI , false );
  bookVariable( fs, "thetaStarHypo_no"  , 320,  0. , M_PI , false );
  // cos(theta*) of W bosons of hypothesis
  bookVariable( fs, "cosThetaStarHypo_pt"  , 200, -1. ,  1.  , false );
  bookVariable( fs, "cosThetaStarHypo_eta" , 200, -1. ,  1.  , false );
  bookVariable( fs, "cosThetaStarHypo_no"  , 200, -1. ,  1.  , false );

  // angle between top quark and W boson from hypothesis
  bookVariable( fs, "topWAngleHypo_pt"  , 315, 0. , M_PI , false );
  bookVariable( fs, "topWAngleHypo_eta" , 315, 0. , M_PI , false );
  bookVariable( fs, "topWAngleHypo_no"  , 315, 0. , M_PI , false );

  // angle between b-quark candidates from hypothesis
  bookVariable( fs, "bAngleHypo_pt"  , 315, 0. , M_PI , useTree_ );
  bookVariable( fs, "bAngleHypo_eta" , 315, 0. , M_PI , useTree_ );
  bookVariable( fs, "bAngleHypo_no"  , 315, 0. , M_PI , useTree_ );

  // angle between b-quark candidates from hypothesis
  bookVariable( fs, "cosBAngleHypo_pt"  , 400, -1. , 1. , useTree_ );
  bookVariable( fs, "cosBAngleHypo_eta" , 400, -1. , 1. , useTree_ );
  bookVariable( fs, "cosBAngleHypo_no"  , 400, -1. , 1. , useTree_ );

  // probability of kinematic fit using pt parametrisation
  bookVariable( fs, "prob_pt"     , 1000,     0. , 1. , useTree_ );
  bookVariable( fs, "prob_log_pt" , 1000,  -100. , 0. , useTree_ );

  // probability of kinematic fit using eta parametrisation
  bookVariable( fs, "prob_eta"     , 1000,     0. , 1. , useTree_ );
  bookVariable( fs, "prob_log_eta" , 1000,  -100. , 0. , useTree_ );

  // probability of kinematic fit using no parametrisation
  bookVariable( fs, "prob_no"     , 1000,     0. , 1. , useTree_ );
  bookVariable( fs, "prob_log_no" , 1000,  -100. , 0. , useTree_ );

  // fit exit code
  bookVariable( fs, "fitExitCode" , 2, -1.5 , 0.5 , useTree_ );

  /*

  // pt / eta / phi / n of pseudo b-jet, const prob
  bookVariable( fs, "pt_1_const"  , 120,  0. , 600. , useTree_ );
  bookVariable( fs, "eta_1_const" ,  70, -3.5,   3.5, useTree_ );
  bookVariable( fs, "phi_1_const" ,  70, -M_PI, M_PI, useTree_ );
  bookVariable( fs, "n_1_const"   ,  20,  0. ,  20. , useTree_ );

  // pt / eta / phi / n of pseudo b-jet, pt-dependend prob
  bookVariable( fs, "pt_1_pt"  , 120,  0. , 600. , useTree_ );
  bookVariable( fs, "eta_1_pt" ,  70, -3.5,   3.5, useTree_ );
  bookVariable( fs, "phi_1_pt" ,  70, -M_PI, M_PI, useTree_ );
  bookVariable( fs, "n_1_pt"   ,  20,  0. ,  20. , useTree_ );

  // pt / eta / phi / n of pseudo b-jet, pt-eta-dependend prob
  bookVariable( fs, "pt_1_pteta"  , 120,  0. , 600. , useTree_ );
  bookVariable( fs, "eta_1_pteta" ,  70, -3.5,   3.5, useTree_ );
  bookVariable( fs, "phi_1_pteta" ,  70, -M_PI, M_PI, useTree_ );
  bookVariable( fs, "n_1_pteta"   ,  20,  0. ,  20. , useTree_ );

   // pt / eta / phi / n of pseudo b-jet, const prob 2 tags
  bookVariable( fs, "pt_2_const"  , 120,  0. , 600. , useTree_ );
  bookVariable( fs, "eta_2_const" ,  70, -3.5,   3.5, useTree_ );
  bookVariable( fs, "phi_2_const" ,  70, -M_PI, M_PI, useTree_ );
  bookVariable( fs, "n_2_const"   ,  20,  0. ,  20. , useTree_ );

  // pt / eta / phi / n of pseudo b-jet, pt-dependend prob 2 tags
  bookVariable( fs, "pt_2_pt"  , 120,  0. , 600. , useTree_ );
  bookVariable( fs, "eta_2_pt" ,  70, -3.5,   3.5, useTree_ );
  bookVariable( fs, "phi_2_pt" ,  70, -M_PI, M_PI, useTree_ );
  bookVariable( fs, "n_2_pt"   ,  20,  0. ,  20. , useTree_ );

  // pt / eta / phi / n of pseudo b-jet, pt-eta-dependend prob 2 tags
  bookVariable( fs, "pt_2_pteta"  , 120,  0. , 600. , useTree_ );
  bookVariable( fs, "eta_2_pteta" ,  70, -3.5,   3.5, useTree_ );
  bookVariable( fs, "phi_2_pteta" ,  70, -M_PI, M_PI, useTree_ );
  bookVariable( fs, "n_2_pteta"   ,  20,  0. ,  20. , useTree_ );

  */

  for(std::map<std::string, TH1*>::const_iterator hist = hists_.begin(); hist != hists_.end(); ++hist){
    hist->second->Sumw2();
  }
}

double
bTagWeight(double bQuark_pt, double bQuark_eta, TString algoWP, bool useEta = false)
{
  // btag / non-b-tag
  //if     (algoWP == "TCHEM40" && !useEta) return (1.73252e-2*log(bQuark_pt-32.9969));
  //else if(algoWP == "TCHEM40" &&  useEta) return (1.73252e-2*log(bQuark_pt-32.9969))*(TMath::Landau(std::abs(bQuark_eta),6.94571e-1,6.10280e-1));
  // btag / all
  if     (algoWP == "TCHEM40" && !useEta) return (1.61306e-2*log(bQuark_pt-32.0962));
  else if(algoWP == "TCHEM40" &&  useEta) return (1.61306e-2*log(bQuark_pt-32.0962))*(TMath::Landau(std::abs(bQuark_eta),7.03245e-1,6.32767e-1));
  // btag / all derived from QCD-MC
  else if(algoWP == "TCHEM40MC" && !useEta) return (1.32326e-2*log(bQuark_pt-33.6152));
  else if(algoWP == "TCHEM40MC" &&  useEta) return (1.32326e-2*log(bQuark_pt-33.6152))*(TMath::Landau(std::abs(bQuark_eta),6.66054e-1,7.37057e-1));
  // btag / all ; pt > 30
  else if(algoWP == "TCHEM30" && !useEta) return (1.48751e-2*log(bQuark_pt-26.655));
  else if(algoWP == "TCHEM30" &&  useEta) return (1.48751e-2*log(bQuark_pt-26.655))*(TMath::Landau(std::abs(bQuark_eta),6.81149e-1,6.46069e-1));
  // btag / all ; pt > 30 ; top cleaned
  else if(algoWP == "TCHEM30clean" && !useEta) return (1.4522e-2*log(bQuark_pt-26.3997));
  else if(algoWP == "TCHEM30clean" &&  useEta) return (1.4522e-2*log(bQuark_pt-26.3997))*(TMath::Landau(std::abs(bQuark_eta),7.03177e-1,6.61813e-1));
  // btag / non-b-tag
  //else if(algoWP == "TCHPT40" && !useEta) return (7.11165e-3*log(bQuark_pt-31.1394));
  //else if(algoWP == "TCHPT40" &&  useEta) return (7.11165e-3*log(bQuark_pt-31.1394))*(TMath::Landau(std::abs(bQuark_eta),5.64953e-1,4.59277e-1));
  // btag / all
  else if(algoWP == "TCHPT40" && !useEta) return (6.82971e-3*log(bQuark_pt-30.9789));
  else if(algoWP == "TCHPT40" &&  useEta) return (6.82971e-3*log(bQuark_pt-30.9789))*(TMath::Landau(std::abs(bQuark_eta),5.68316e-1,4.66944e-1));
  return 0;
}

double
bTagWeight(pat::Jet& bQuark, TString algoWP, bool useEta = false)
{
  return (bTagWeight(bQuark.pt(), bQuark.eta(), algoWP, useEta));
}

double
bTagWeight(pat::Jet& bQuark, pat::Jet& bBarQuark, TString algoWP, bool useEta = false)
{
  return (bTagWeight(bQuark, algoWP, useEta) * bTagWeight(bBarQuark, algoWP, useEta));
}

double
bTagWeight(std::vector<pat::Jet>::const_iterator& bQuark, TString algoWP, bool useEta = false)
{
  return (bTagWeight(bQuark->pt(), bQuark->eta(), algoWP, useEta));
}

double
bTagWeight(std::vector<pat::Jet>::const_iterator& bQuark, std::vector<pat::Jet>::const_iterator& bBarQuark, TString algoWP, bool useEta = false)
{
  return (bTagWeight(bQuark, algoWP, useEta) * bTagWeight(bBarQuark, algoWP, useEta));
}

/// histogram filling for fwlite and for full fw
void
FullHadQCDEstimation::analyze(const edm::Event& event, const edm::EventSetup& iSetup)
{
  
  edm::Handle<edm::View< pat::Jet > > jets_h;
  event.getByLabel(JetSrc_, jets_h);

  edm::Handle<double> multiJetMVADisc_h;
  event.getByLabel(MultiJetMVADiscSrc_, multiJetMVADisc_h);
  
  edm::View<pat::Jet> jets = *jets_h;

  /** 
      Fill Kinematic Variables
  **/
  
  double weight = 1.;

  if(jets.size() < 6) return;

  std::vector<pat::Jet> theJets;
  for(edm::View<pat::Jet>::const_iterator jet = jets.begin(); jet != jets.end(); ++jet){
    theJets.push_back(*jet);
  }
    
  for(std::vector<pat::Jet>::const_iterator jet1 = theJets.begin(); jet1 != theJets.end()-1; ++jet1){
    std::vector<pat::Jet>::const_iterator firstDiscJet = jet1;
    for(std::vector<pat::Jet>::const_iterator jet2 = jet1+1; jet2 != theJets.end(); ++jet2){
      std::vector<pat::Jet>::const_iterator secondDiscJet = jet2;
      std::vector<pat::Jet> myJets;
      for(std::vector<pat::Jet>::iterator newJet = theJets.begin(); newJet != theJets.end(); ++newJet){
	if     (newJet == firstDiscJet ) newJet->addBDiscriminatorPair(std::make_pair("myPseudoBTags", 1.));
	else if(newJet == secondDiscJet) newJet->addBDiscriminatorPair(std::make_pair("myPseudoBTags", 2.));
	else                             newJet->addBDiscriminatorPair(std::make_pair("myPseudoBTags", 0.));
	myJets.push_back(*newJet);
      }
      std::list<TtFullHadKinFitter::KinFitResult> result = kinFitter->fit(myJets);
      if(result.size() == 0) continue;

      for(std::list<TtFullHadKinFitter::KinFitResult>::const_iterator res = result.begin(); res != result.end(); ++res){
	fillValue( "fitExitCode" , (double)res->Status , 1. );
	if(res->Status != 0) continue;
	double b_Tag_Weight = bTagWeight(jet1, jet2, bTagAlgoWP_);
	double b_Tag_Weight_eta = bTagWeight(jet1, jet2, bTagAlgoWP_, true);
	//std::cout << jet1->pt() << ", " << jet2->pt() << " -> " << b_Tag_Weight << std::endl;
	//std::cout << "Fit successful! Tagged Jets: " << jet1-theJets.begin()+1 << ", " << jet2-theJets.begin()+1 << std::endl;
	  
	// kinfitted mass of top quark
	double topMass = (res->B.p4()+res->LightQ.p4()+res->LightQBar.p4()).mass();
	fillValue( "topQuarkMassHypoAll_eta" , topMass , b_Tag_Weight_eta * weight );
	fillValue( "topQuarkMassHypoAll_pt"  , topMass , b_Tag_Weight     * weight );
	fillValue( "topQuarkMassHypoAll_no"  , topMass ,                    weight );
	  
	// probability of kinematic fit
	double prob = res->Prob;
	fillValue( "prob_eta" , prob , b_Tag_Weight_eta * weight );
	fillValue( "prob_pt"  , prob , b_Tag_Weight     * weight );
	fillValue( "prob_no"  , prob ,                    weight );
	if(res->Prob > 0) {
	  double prob_log = log10(prob);
	  fillValue( "prob_log_eta" , prob_log , b_Tag_Weight_eta * weight );
	  fillValue( "prob_log_pt"  , prob_log , b_Tag_Weight     * weight );
	  fillValue( "prob_log_no"  , prob_log ,                    weight );
	}

	// save jet pt and eta for possible later parametrization
	fillValue( "jet1_pt"  , jet1->pt()  );
	fillValue( "jet2_pt"  , jet2->pt()  );
	fillValue( "jet1_eta" , jet1->eta() );
	fillValue( "jet2_eta" , jet2->eta() );

	// multiJet MVA discriminator
	double multiJetMVADisc = multiJetMVADisc_h.isValid() ? *multiJetMVADisc_h : -10.;
	// invariant mass of ttbar system
	double invTTBarMass = (res->B.p4()+res->LightQ.p4()+res->LightQBar.p4()+res->BBar.p4()+res->LightP.p4()+res->LightPBar.p4()).mass();
	// pt of ttbar system
	double ttbarPt      = (res->B.p4()+res->LightQ.p4()+res->LightQBar.p4()+res->BBar.p4()+res->LightP.p4()+res->LightPBar.p4()).pt();
	// angle between b-quark candidates from hypothesis
	TLorentzVector bCandidate    = TLorentzVector( res->B   .px(), res->B   .py(), res->B   .pz(), res->B   .energy() );
	TLorentzVector bBarCandidate = TLorentzVector( res->BBar.px(), res->BBar.py(), res->BBar.pz(), res->BBar.energy() );
	double bAngle = bCandidate.Angle( bBarCandidate.Vect() );
	// properties of kinematic fit for the tree
	fillValue( "topMass"        , topMass      );
	fillValue( "prob"           , prob         );
	fillValue( "chi2"           , res->Chi2    );
	fillValue( "ttbarPt"        , ttbarPt      );
	fillValue( "ttbarMass"      , invTTBarMass );
	fillValue( "bAngle"         , bAngle       );
	fillValue( "multiJetMVADisc", multiJetMVADisc );
	  
	if(res->Prob > 0.01) {
	  // kinfitted mass of top quark
	  fillValue( "topQuarkMassHypo_eta" , topMass , b_Tag_Weight_eta * weight );
	  fillValue( "topQuarkMassHypo_pt"  , topMass , b_Tag_Weight     * weight );
	  fillValue( "topQuarkMassHypo_no"  , topMass ,                    weight );
	  // after other two histograms as its weight needs to be filled last (will be done automatically)

	  // invariant mass of ttbar system
	  fillValue( "ttbarInvMassHypo_eta" , invTTBarMass , b_Tag_Weight_eta * weight );
	  fillValue( "ttbarInvMassHypo_pt"  , invTTBarMass , b_Tag_Weight     * weight );
	  fillValue( "ttbarInvMassHypo_no"  , invTTBarMass ,                    weight );
	    
	  // pt of ttbar system
	  fillValue( "ttbarPtHypo_eta" , ttbarPt , b_Tag_Weight_eta * weight );
	  fillValue( "ttbarPtHypo_pt"  , ttbarPt , b_Tag_Weight     * weight );
	  fillValue( "ttbarPtHypo_no"  , ttbarPt ,                    weight );
	    
	  fillValue("bAngleHypo_eta", bAngle, b_Tag_Weight_eta * weight);
	  fillValue("bAngleHypo_pt" , bAngle, b_Tag_Weight     * weight);
	  fillValue("bAngleHypo_no" , bAngle,                    weight);

	  fillValue("cosBAngleHypo_eta", cos(bAngle), b_Tag_Weight_eta * weight);
	  fillValue("cosBAngleHypo_pt" , cos(bAngle), b_Tag_Weight     * weight);
	  fillValue("cosBAngleHypo_no" , cos(bAngle),                    weight);
	    
	  //// theta* of W boson of hypothesis
	  double thetaStarPlus  = FullHadTopReco::thetaStar( res->LightQ.p4() + res->LightQBar.p4(), res->LightQ.p4(), res->LightQBar.p4() );
	  double thetaStarMinus = FullHadTopReco::thetaStar( res->LightP.p4() + res->LightPBar.p4(), res->LightP.p4(), res->LightPBar.p4() );
	  fillValue("thetaStarHypo_eta", thetaStarPlus , b_Tag_Weight_eta * weight);
	  fillValue("thetaStarHypo_eta", thetaStarMinus, b_Tag_Weight_eta * weight);
	  fillValue("thetaStarHypo_pt" , thetaStarPlus , b_Tag_Weight     * weight);
	  fillValue("thetaStarHypo_pt" , thetaStarMinus, b_Tag_Weight     * weight);
	  fillValue("thetaStarHypo_no" , thetaStarPlus ,                    weight);
	  fillValue("thetaStarHypo_no" , thetaStarMinus,                    weight);
	    
	  // cos(theta*) of W boson of hypothesis
	  fillValue("cosThetaStarHypo_eta", cos(thetaStarPlus) , b_Tag_Weight_eta * weight);
	  fillValue("cosThetaStarHypo_eta", cos(thetaStarMinus), b_Tag_Weight_eta * weight);
	  fillValue("cosThetaStarHypo_pt" , cos(thetaStarPlus) , b_Tag_Weight     * weight);
	  fillValue("cosThetaStarHypo_pt" , cos(thetaStarMinus), b_Tag_Weight     * weight);
	  fillValue("cosThetaStarHypo_no" , cos(thetaStarPlus) ,                    weight);
	  fillValue("cosThetaStarHypo_no" , cos(thetaStarMinus),                    weight);
   		
	  // angle between W boson in top cms and top direction of flight
	  double topWAngle    = FullHadTopReco::topWAngle(res->LightQ.p4()+res->LightQBar.p4()+res->B   .p4(), res->LightQ.p4()+res->LightQBar.p4());
	  double topBarWAngle = FullHadTopReco::topWAngle(res->LightP.p4()+res->LightPBar.p4()+res->BBar.p4(), res->LightP.p4()+res->LightPBar.p4());
	  fillValue("topWAngleHypo_eta", topWAngle   , b_Tag_Weight_eta * weight);
	  fillValue("topWAngleHypo_eta", topBarWAngle, b_Tag_Weight_eta * weight);
	  fillValue("topWAngleHypo_pt" , topWAngle   , b_Tag_Weight     * weight);
	  fillValue("topWAngleHypo_pt" , topBarWAngle, b_Tag_Weight     * weight);
	  fillValue("topWAngleHypo_no" , topWAngle   ,                    weight);
	  fillValue("topWAngleHypo_no" , topBarWAngle,                    weight);
	}
	// fill the tree, if any variable should be put in
	if(treeVars_.size()) tree->Fill();
	  
	break;
      }
      /*
	for(std::vector<pat::Jet>::const_iterator jet = myJets.begin(); jet != myJets.end(); ++jet){
	if(jet->bDiscriminator("myPseudoBTags") > 0.5)
	// const probability
	fillValue( "pt_2_const" , jet->pt() , 0.0249184 * 0.0249184 * weight );
	fillValue( "eta_2_const", jet->eta(), 0.0249184 * 0.0249184 * weight );
	fillValue( "phi_2_const", jet->phi(), 0.0249184 * 0.0249184 * weight );
	fillValue( "n_2_const"  ,        2. , 0.0249184 * 0.0249184 * weight );

	//pt-dependend probability
	double b_Tag_Weight = bTagWeight(jet1, jet2, bTagAlgoWP_);
	fillValue( "pt_2_pt" , jet->pt() , b_Tag_Weight * weight );
	fillValue( "eta_2_pt", jet->eta(), b_Tag_Weight * weight );
	fillValue( "phi_2_pt", jet->phi(), b_Tag_Weight * weight );
	fillValue( "n_2_pt"  ,        2. , b_Tag_Weight * weight );

	//pt-eta-dependend probability
	b_Tag_Weight = bTagWeight(jet1, jet2, bTagAlgoWP_, true);
	fillValue( "pt_2_pteta" , jet->pt() , b_Tag_Weight * weight );
	fillValue( "eta_2_pteta", jet->eta(), b_Tag_Weight * weight );
	fillValue( "phi_2_pteta", jet->phi(), b_Tag_Weight * weight );
	fillValue( "n_2_pteta"  ,        2. , b_Tag_Weight * weight );
	}
      */
      myJets.clear();
    }
  }
  /*
    for(std::vector<pat::Jet>::const_iterator jet = theJets.begin(); jet != theJets.end(); ++jet){
    // const probability
    fillValue( "pt_1_const" , jet->pt() , 0.0249184 * weight );
    fillValue( "eta_1_const", jet->eta(), 0.0249184 * weight );
    fillValue( "phi_1_const", jet->phi(), 0.0249184 * weight );
    fillValue( "n_1_const"  ,        1. , 0.0249184 * weight );
      
    //pt-dependend probability
    double b_Tag_Weight = bTagWeight(jet, bTagAlgoWP_);
    fillValue( "pt_1_pt" , jet->pt() , b_Tag_Weight * weight );
    fillValue( "eta_1_pt", jet->eta(), b_Tag_Weight * weight );
    fillValue( "phi_1_pt", jet->phi(), b_Tag_Weight * weight );
    fillValue( "n_1_pt"  ,        1. , b_Tag_Weight * weight );
      
    //pt-eta-dependend probability
    b_Tag_Weight = bTagWeight(jet, bTagAlgoWP_, true);
    fillValue( "pt_1_pteta" , jet->pt() , b_Tag_Weight * weight );
    fillValue( "eta_1_pteta", jet->eta(), b_Tag_Weight * weight );
    fillValue( "phi_1_pteta", jet->phi(), b_Tag_Weight * weight );
    fillValue( "n_1_pteta"  ,        1. , b_Tag_Weight * weight );
    }
  */
}

void
FullHadQCDEstimation::endJob()
{
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( FullHadQCDEstimation );

