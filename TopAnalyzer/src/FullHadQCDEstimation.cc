#include "TopAnalysis/TopAnalyzer/interface/FullHadQCDEstimation.h"

/// default constructor for fw lite
FullHadQCDEstimation::FullHadQCDEstimation()
{
  tree = 0;
}

/// default constructor for fwfull
FullHadQCDEstimation::FullHadQCDEstimation(const edm::ParameterSet& cfg) :
  useTree_ ( cfg.getParameter<bool>( "useTree" ) )
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
  // define kinematic fit interface
  kinFitter = new TtFullHadKinFitter::KinFit(true, 2, "myPseudoBTags", 0.5, 0.5,
					     udscResolutions_, bResolutions_,
					     "L3Absolute", -1, -1,
					     500, 5e-5, 0.0001, 1, constraints_, 80.4, 173.);

  tree = 0;
}

/// histogramm booking for fwlite 
void
FullHadQCDEstimation::book()
{
}

/// histogramm booking for full fw
void
FullHadQCDEstimation::book(edm::Service<TFileService>& fs)
{
  /** 
      Kinematic Variables
  **/
  // top mass of kinematic fit
  bookVariable( fs, "topQuarkMassHypo" ,  1000,  0. , 1000. , useTree_ );

  // top mass of kinematic fit
  bookVariable( fs, "topQuarkMassHypoAll" ,  1000,  0. , 1000. , useTree_ );
}

/// histogram filling for fwlite and for full fw
void
FullHadQCDEstimation::fill(const edm::View<pat::Jet>& jets, const double& weight)
{
  /** 
      Fill Kinematic Variables
  **/

  if(jets.size() >= 6){

    std::vector<pat::Jet> theJets;
    for(edm::View<pat::Jet>::const_iterator jet = jets.begin(); jet != jets.end()-1; ++jet){
      theJets.push_back(*jet);
    }
    for(std::vector<pat::Jet>::const_iterator jet1 = theJets.begin(); jet1 != theJets.end()-1; ++jet1){
      std::vector<pat::Jet>::const_iterator firstDiscJet = jet1;
      for(std::vector<pat::Jet>::const_iterator jet2 = jet1+1; jet2 != theJets.end(); ++jet2){
	std::vector<pat::Jet>::const_iterator secondDiscJet = jet2;
	std::vector<pat::Jet> myJets;
	for(std::vector<pat::Jet>::iterator newJet = theJets.begin(); newJet != theJets.end(); ++newJet){
	  if(newJet == firstDiscJet || newJet == secondDiscJet) newJet->addBDiscriminatorPair(std::make_pair("myPseudoBTags", 1.));
	  else newJet->addBDiscriminatorPair(std::make_pair("myPseudoBTags", 0.));
	  myJets.push_back(*newJet);
	}
	std::list<TtFullHadKinFitter::KinFitResult> result = kinFitter->fit(myJets);
	double bTagWeight = 0.233 * 0.233;
	if(result.size() > 0) {
	  //std::cout << result.size() << std::endl;
	  for(std::list<TtFullHadKinFitter::KinFitResult>::const_iterator res = result.begin(); res != result.end(); ++res){
	    if(res->Status == 0 ) {
	      //std::cout << "Fit successful! Tagged Jets: " << jet1-theJets.begin()+1 << ", " << jet2-theJets.begin()+1 << std::endl;
	      fillValue( "topQuarkMassHypoAll" , (res->B.p4()+res->LightQ.p4()+res->LightQBar.p4()).mass() , bTagWeight * weight );
	      if(res->Prob > 0.01) fillValue( "topQuarkMassHypo" , (res->B.p4()+res->LightQ.p4()+res->LightQBar.p4()).mass() , bTagWeight * weight );
	      break;
	    }
	  }
	}
	myJets.clear();
      }
    }
  }

  // fill the tree, if any variable should be put in
  if(treeVars_.size()) tree->Fill();
}
