#include <TMath.h>
#include "DataFormats/Math/interface/deltaPhi.h"
#include "TopAnalysis/TopAnalyzer/interface/KinFitQuality.h"
#include "AnalysisDataFormats/TopObjects/interface/TtFullHadEvtPartons.h"

/// default constructor for fw lite
KinFitQuality::KinFitQuality()
{
  covM = 0;
  tree = 0;
}

/// default constructor for full fw
KinFitQuality::KinFitQuality(const edm::ParameterSet& cfg) :
  useTree_         ( cfg.getParameter<bool>                           ( "useTree"         ) ),
  numberOfHypos_   ( cfg.getParameter<unsigned int>                   ( "numberOfHypos"   ) ),
  udscResolutions_ ( cfg.getParameter<std::vector<edm::ParameterSet> >( "udscResolutions" ) ),
  bResolutions_    ( cfg.getParameter<std::vector<edm::ParameterSet> >( "bResolutions"    ) )
{
  covM = 0;
  tree = 0;
}

/// default destructor
KinFitQuality::~KinFitQuality()
{
  delete covM;
}

/// histogramm booking for fwlite 
void KinFitQuality::book()
{
  /** 
      Add needed histogramms from full fw list of histogramms
  **/
}

/// histogramm booking for fw
void KinFitQuality::book(edm::Service<TFileService>& fs)
{
  /** 
      Pull Distributions (Relative to the Reco Input)
  **/

  // b pt
  bookVariable( fs, "bQuarkPt"      ,   60, -2. , 1. , false );
  // b eta
  bookVariable( fs, "bQuarkEta"     ,   60, -3. , 3. , false );
  // b phi
  bookVariable( fs, "bQuarkPhi"     ,   60, -M_PI , M_PI , false );
  // lightQuark pt
  bookVariable( fs, "lightQuarkPt"  ,   60, -2. , 1. , false );
  // lightQuark b eta
  bookVariable( fs, "lightQuarkEta" ,   60, -3. , 3. , false );
  // lightQuark b phi
  bookVariable( fs, "lightQuarkPhi" ,   60, -M_PI , M_PI , false );
  // w pt
  bookVariable( fs, "wPt"           ,   60, -2. , 1. , false );
  // w eta
  bookVariable( fs, "wEta"          ,   60, -3. , 3. , false );
  // w phi
  bookVariable( fs, "wPhi"          ,   60, -M_PI , M_PI , false );
  // topQuark pt
  bookVariable( fs, "topQuarkPt"    ,   60, -2. , 1. , false );
  // topQuark eta
  bookVariable( fs, "topQuarkEta"   ,   60, -3. , 3. , false );
  // topQuark phi
  bookVariable( fs, "topQuarkPhi"   ,   60, -M_PI , M_PI , false );

  // b pt pull
  bookVariable( fs, "bPullEt"      ,  400, -10. , 10. , false );
  // b eta pull
  bookVariable( fs, "bPullEta"     ,  200,  -5. ,  5. , false );
  // b phi pull
  bookVariable( fs, "bPullPhi"     ,  200,  -5. ,  5. , false );
  // lightQuark pt pull
  bookVariable( fs, "lightPullEt"  ,  200,  -5. ,  5. , false );
  // lightQuark eta pull
  bookVariable( fs, "lightPullEta" ,  200,  -5. ,  5. , false );
  // lightQuark phi pull
  bookVariable( fs, "lightPullPhi" ,  200,  -5. ,  5. , false );

  /**
     KinFit Properties
  **/

  // chi2prob of kinfit log plot
  bookVariable( fs, "prob_log" ,  100, -100., 0. , useTree_ );
  // chi2 of kinfit
  bookVariable( fs, "chi2"     ,  100, 0., 1000. , useTree_ );
  // chi2prob of kinfit
  bookVariable( fs, "prob"     ,  100, 0.,    1. , useTree_ );

  for(unsigned int i = 1; i < numberOfHypos_; ++i){

    TString tName = "chi2_"; tName += i+1;
    std::string name = tName.Data();
    // chi2 of kinfit
    bookVariable( fs, name.c_str() ,  100, 0., 1000. , useTree_ );

    tName = "prob_"; tName += i+1;
    name = tName.Data();
    // chi2prob of kinfit
    bookVariable( fs, name.c_str() ,  100, 0.,    1. , useTree_ );
  }
}

/// histogram filling interface for reconstruction level for access with fwlite or full framework
void
KinFitQuality::fill(const TtFullHadronicEvent& tops, const edm::View<pat::Jet>& jets, const double& weight)
{
  // make sure to have a valid hypothesis on reconstruction level
  if( tops.isHypoValid("kKinFit") ){
    /** 
	Fill the Pull Distributions (Relative to the Reco Input)
    **/
    // define indices in pat::Jet collection

    int lightQ    = tops.jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::LightQ   ];
    int lightQBar = tops.jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::LightQBar];
    int b         = tops.jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::B        ];
    int bBar      = tops.jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::BBar     ];
    int lightP    = tops.jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::LightP   ];
    int lightPBar = tops.jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::LightPBar];

/*
    std::cout << "-------- New Event --------" << std::endl;
    std::cout << "LightQ-mass   : " << tops.lightQ("kKinFit")->mass()    << std::endl;
    std::cout << "LightQBar-mass: " << tops.lightQBar("kKinFit")->mass() << std::endl;
    std::cout << "LightP-mass   : " << tops.lightP("kKinFit")->mass()    << std::endl;
    std::cout << "LightPBar-mass: " << tops.lightPBar("kKinFit")->mass() << std::endl;
    std::cout << "B-mass        : " << tops.b("kKinFit")->mass()         << std::endl;
    std::cout << "BBar-mass     : " << tops.bBar("kKinFit")->mass()      << std::endl;
    std::cout << "WPlus-mass    : " << tops.wPlus("kKinFit")->mass()     << std::endl;
    std::cout << "WMinus-mass   : " << tops.wMinus("kKinFit")->mass()    << std::endl;
    std::cout << "Top-mass      : " << tops.top("kKinFit")->mass()       << std::endl;
    std::cout << "TopBar-mass   : " << tops.topBar("kKinFit")->mass()    << std::endl;
*/

    // helper to get the resolutions for the jets
    if(!covM) covM = new CovarianceMatrix(udscResolutions_, bResolutions_);

    // make sure the b-jet index is in the range of the jet collection
    if( b >=0 && b < (int)jets.size() ){
      // b pt
      fillValue("bQuarkPt"  , (jets[b].pt() -tops.b("kKinFit")->pt())/jets[b].pt()  , weight);
      // b eta
      fillValue("bQuarkEta" , (jets[b].eta()-tops.b("kKinFit")->eta()) , weight);
      // b phi
      fillValue("bQuarkPhi" , deltaPhi(jets[b].phi(),tops.b("kKinFit")->phi()) , weight);

      // b pt pull
      fillValue("bPullEt"  , (jets[b].et() -tops.b("kKinFit")->et())/covM->getResolution(jets[b], "et" , true) , weight);
      // b eta pull
      fillValue("bPullEta" , (jets[b].eta()-tops.b("kKinFit")->eta())/covM->getResolution(jets[b], "eta" , true) , weight);
      // b phi pull
      fillValue("bPullPhi" , deltaPhi(jets[b].phi(),tops.b("kKinFit")->phi())/covM->getResolution(jets[b], "phi" , true) , weight);
    }
   // make sure the bBar-jet index is in the range of the jet collection
    if( bBar >= 0 && bBar< (int)jets.size() ){
      // bBar pt
      fillValue("bQuarkPt"  , (jets[bBar].pt() -tops.bBar("kKinFit")->pt())/jets[bBar].pt()  , weight);
      // bBar eta
      fillValue("bQuarkEta" , (jets[bBar].eta()-tops.bBar("kKinFit")->eta()) , weight);
      // bBar phi
      fillValue("bQuarkPhi" , deltaPhi(jets[bBar].phi(),tops.bBar("kKinFit")->phi()) , weight);

      // bBar pt pull
      fillValue("bPullEt"  , (jets[bBar].pt() -tops.bBar("kKinFit")->pt())/covM->getResolution(jets[bBar], "et" , true) , weight);
      // bBar eta pull
      fillValue("bPullEta" , (jets[bBar].eta()-tops.bBar("kKinFit")->eta())/covM->getResolution(jets[bBar], "eta" , true) , weight);
      // bBar phi pull
      fillValue("bPullPhi" , deltaPhi(jets[bBar].phi(),tops.bBar("kKinFit")->phi())/covM->getResolution(jets[bBar], "phi" , true) , weight);
    }
   // make sure the light quark index is in the range of the jet collection
    if( lightQ >= 0 && lightQ < (int)jets.size() ){
      // lightQuark pt
      fillValue("lightQuarkPt"  , (jets[lightQ].pt() -tops.lightQ("kKinFit")->pt())/jets[lightQ].pt()  , weight);
      // lightQuark eta
      fillValue("lightQuarkEta" , (jets[lightQ].eta()-tops.lightQ("kKinFit")->eta()) , weight);
      // lightQuark phi
      fillValue("lightQuarkPhi" , deltaPhi(jets[lightQ].phi(),tops.lightQ("kKinFit")->phi()) , weight);

      // lightQuark pt pull
      fillValue("lightPullEt"  ,(jets[lightQ].pt() -tops.lightQ("kKinFit")->pt())/covM->getResolution(jets[lightQ], "et") , weight);
      // lightQuark eta pull
      fillValue("lightPullEta" ,(jets[lightQ].eta()-tops.lightQ("kKinFit")->eta())/covM->getResolution(jets[lightQ], "eta") , weight);
      // lightQuark phi pull
      fillValue("lightPullPhi" ,deltaPhi(jets[lightQ].phi(),tops.lightQ("kKinFit")->phi())/covM->getResolution(jets[lightQ], "phi") , weight);
    }
    // make sure the light quark bar index is in the range of the jet collection
    if( lightQBar >= 0 && lightQBar< (int)jets.size() ){
      // lightQuark pt
      fillValue("lightQuarkPt"  , (jets[lightQBar].pt() -tops.lightQBar("kKinFit")->pt())/jets[lightQBar].pt()  , weight);
      // lightQuark eta
      fillValue("lightQuarkEta" , (jets[lightQBar].eta()-tops.lightQBar("kKinFit")->eta()) , weight);
      // lightQuark phi
      fillValue("lightQuarkPhi" , deltaPhi(jets[lightQBar].phi(),tops.lightQBar("kKinFit")->phi()) , weight);

      // lightQuark pt pull
      fillValue("lightPullEt"  , (jets[lightQBar].pt() -tops.lightQBar("kKinFit")->pt())/covM->getResolution(jets[lightQBar], "et") , weight);
      // lightQuark eta pull
      fillValue("lightPullEta" , (jets[lightQBar].eta()-tops.lightQBar("kKinFit")->eta())/covM->getResolution(jets[lightQBar], "eta") , weight);
      // lightQuark phi pull
      fillValue("lightPullPhi" , deltaPhi(jets[lightQBar].phi(),tops.lightQBar("kKinFit")->phi())/covM->getResolution(jets[lightQBar], "phi") , weight);
    }
    // make sure the light quark index is in the range of the jet collection
    if( lightP >= 0 && lightP < (int)jets.size() ){
      // lightQuark pt
      fillValue("lightQuarkPt"  , (jets[lightP].pt() -tops.lightP("kKinFit")->pt())/jets[lightP].pt()  , weight);
      // lightQuark eta
      fillValue("lightQuarkEta" , (jets[lightP].eta()-tops.lightP("kKinFit")->eta()) , weight);
      // lightQuark phi
      fillValue("lightQuarkPhi" , deltaPhi(jets[lightP].phi(),tops.lightP("kKinFit")->phi()) , weight);

      // lightQuark pt pull
      fillValue("lightPullEt"  ,(jets[lightP].pt() -tops.lightP("kKinFit")->pt())/covM->getResolution(jets[lightP], "et") , weight);
      // lightQuark eta pull
      fillValue("lightPullEta" ,(jets[lightP].eta()-tops.lightP("kKinFit")->eta())/covM->getResolution(jets[lightP], "eta") , weight);
      // lightQuark phi pull
      fillValue("lightPullPhi" ,deltaPhi(jets[lightP].phi(),tops.lightP("kKinFit")->phi())/covM->getResolution(jets[lightP], "phi") , weight);
    }
    // make sure the light quark bar index is in the range of the jet collection
    if( lightPBar >= 0 && lightPBar < (int)jets.size() ){
      // lightQuark pt
      fillValue("lightQuarkPt"   , (jets[lightPBar].pt() -tops.lightPBar("kKinFit")->pt())/jets[lightPBar].pt()  , weight);
      // lightQuark eta
      fillValue("lightQuarkEta"  , (jets[lightPBar].eta()-tops.lightPBar("kKinFit")->eta()) , weight);
      // lightQuark phi
      fillValue("lightQuarkPhi"  , deltaPhi(jets[lightPBar].phi(),tops.lightPBar("kKinFit")->phi()) , weight);

      // lightQuark pt
      fillValue("lightPullEt"  , (jets[lightPBar].pt() -tops.lightPBar("kKinFit")->pt())/covM->getResolution(jets[lightPBar], "et") , weight);
      // lightQuark eta
      fillValue("lightPullEta" , (jets[lightPBar].eta()-tops.lightPBar("kKinFit")->eta())/covM->getResolution(jets[lightPBar], "eta") , weight);
      // lightQuark phi
      fillValue("lightPullPhi" , deltaPhi(jets[lightPBar].phi(),tops.lightPBar("kKinFit")->phi())/covM->getResolution(jets[lightPBar], "phi") , weight);
    }
    // make sure the light quarks of w+ indices are in the range of the jet collection
    if( lightQ >= 0 && lightQ < (int)jets.size() && lightQBar >= 0 && lightQBar < (int)jets.size() ){
      // w+ pt
      fillValue("wPt"   , ((jets[lightQ].p4()+jets[lightQBar].p4()).pt() - (tops.lightQ("kKinFit")->p4()+tops.lightQBar("kKinFit")->p4()).pt()) /
					   (jets[lightQ].p4()+jets[lightQBar].p4()).pt() , weight);
      // w+ eta
      fillValue("wEta"  , (jets[lightQ].p4()+jets[lightQBar].p4()).eta() - (tops.lightQ("kKinFit")->p4()+tops.lightQBar("kKinFit")->p4()).eta() , weight);
      // w+ phi
      fillValue("wPhi"  , deltaPhi((jets[lightQ].p4()+jets[lightQBar].p4()).phi(), (tops.lightQ("kKinFit")->p4()+tops.lightQBar("kKinFit")->p4()).phi()) , weight);
    }
    // make sure the light quarks of w- indices are in the range of the jet collection
    if( lightP >= 0 && lightP < (int)jets.size() && lightPBar >= 0 && lightPBar < (int)jets.size() ){
      // w+ pt
      fillValue("wPt"  , ((jets[lightP].p4()+jets[lightPBar].p4()).pt() - (tops.lightP("kKinFit")->p4()+tops.lightPBar("kKinFit")->p4()).pt()) /
					 (jets[lightP].p4()+jets[lightPBar].p4()).pt(), weight);
      // w+ eta
      fillValue("wEta" , (jets[lightP].p4()+jets[lightPBar].p4()).eta() - (tops.lightP("kKinFit")->p4()+tops.lightPBar("kKinFit")->p4()).eta() , weight);
      // w+ phi
      fillValue("wPhi"  , deltaPhi((jets[lightP].p4()+jets[lightPBar].p4()).phi(), (tops.lightP("kKinFit")->p4()+tops.lightPBar("kKinFit")->p4()).phi()) , weight);
    }
    // make sure the quarks of top quark indices are in the range of the jet collection
    if( lightQ >= 0 && lightQ < (int)jets.size() && lightQBar >= 0 && lightQBar < (int)jets.size() && b >=0 && b < (int)jets.size()  ){
      // top pt
      fillValue("topQuarkPt"  , ((jets[lightQ].p4()+jets[lightQBar].p4()+jets[b].p4()).pt() - 
						 (tops.lightQ("kKinFit")->p4() + tops.lightQBar("kKinFit")->p4() + tops.b("kKinFit")->p4()).pt()) /
						(jets[lightQ].p4()+jets[lightQBar].p4()+jets[b].p4()).pt(), weight);
      // top eta
      fillValue("topQuarkEta" , (jets[lightQ].p4()+jets[lightQBar].p4()+jets[b].p4()).eta() - 
						(tops.lightQ("kKinFit")->p4() + tops.lightQBar("kKinFit")->p4() + tops.b("kKinFit")->p4()).eta() , weight);
      // top phi
      fillValue("topQuarkPhi" , deltaPhi((jets[lightQ].p4()+jets[lightQBar].p4()+jets[b].p4()).phi(), 
							 (tops.lightQ("kKinFit")->p4() + tops.lightQBar("kKinFit")->p4() + tops.b("kKinFit")->p4()).phi()) , weight);
    }
    // make sure the quarks of topBar quark indices are in the range of the jet collection
    if( lightP >= 0 && lightP < (int)jets.size() && lightPBar >= 0 && lightPBar < (int)jets.size() && bBar >=0 && bBar < (int)jets.size()  ){
      // top pt
      fillValue("topQuarkPt"  , ((jets[lightP].p4() + jets[lightPBar].p4() + jets[bBar].p4()).pt() - 
						 (tops.lightP("kKinFit")->p4() + tops.lightPBar("kKinFit")->p4() + tops.bBar("kKinFit")->p4()).pt()) /
						(jets[lightP].p4()+jets[lightPBar].p4()+jets[bBar].p4()).pt() , weight);
      // top eta
      fillValue("topQuarkEta" , (jets[lightP].p4() + jets[lightPBar].p4() + jets[bBar].p4()).eta() - 
						(tops.lightP("kKinFit")->p4() + tops.lightPBar("kKinFit")->p4() + tops.bBar("kKinFit")->p4()).eta() , weight);
      // top phi
      fillValue("topQuarkPhi" , deltaPhi((jets[lightP].p4() + jets[lightPBar].p4() + jets[bBar].p4()).phi(),
							 (tops.lightP("kKinFit")->p4() + tops.lightPBar("kKinFit")->p4() + tops.bBar("kKinFit")->p4()).phi()) , weight);
    }


    // chi2 of kinfit
    fillValue("chi2" , tops.fitChi2() , weight);
    // chi2prob of kinfit
    fillValue("prob" , tops.fitProb() , weight);
    // chi2prob of kinfit log plot
    if(tops.fitProb() > 0) fillValue("prob_log" , log10(tops.fitProb()) , weight);

    if(tops.numberOfAvailableHypos("kKinFit")>1){

      for(unsigned int i = 1; i < numberOfHypos_; ++i){

	if(tops.numberOfAvailableHypos("kKinFit") > i){
	  TString tName = "chi2_"; tName += i+1;
	  std::string name = tName.Data();
	  // chi2 of kinfit
	  fillValue(name , tops.fitChi2(i) , weight);
  
	  tName = "prob_"; tName += i+1;
	  name = tName.Data();
	  // chi2prob of kinfit
	  fillValue(name , tops.fitProb(i) , weight);
	}
      }
    }
    // fill the tree, if any variable should be put in
    if(treeVars_.size()) tree->Fill();
  }
}

