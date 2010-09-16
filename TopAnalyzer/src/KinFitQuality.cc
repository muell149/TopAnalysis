#include <TMath.h>
#include "DataFormats/Math/interface/deltaPhi.h"
#include "TopAnalysis/TopAnalyzer/interface/KinFitQuality.h"
#include "AnalysisDataFormats/TopObjects/interface/TtFullHadEvtPartons.h"

/// default constructor for fw lite
KinFitQuality::KinFitQuality()
{
  covM=0;
}

/// default constructor for full fw
KinFitQuality::KinFitQuality(const edm::ParameterSet& cfg) :
  numberOfHypos_   ( cfg.getParameter<unsigned int>                   ( "numberOfHypos"   ) ),
  udscResolutions_ ( cfg.getParameter<std::vector<edm::ParameterSet> >( "udscResolutions" ) ),
  bResolutions_    ( cfg.getParameter<std::vector<edm::ParameterSet> >( "bResolutions"    ) )
{
  covM=0;
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

  double pi = TMath::Pi();

  // b pt
  hists_["bQuarkPt"     ] = fs->make<TH1F>( "bQuarkPt"      , "bQuarkPt"      ,   60, -2. , 1. );
  // b eta
  hists_["bQuarkEta"    ] = fs->make<TH1F>( "bQuarkEta"     , "bQuarkEta"     ,   60, -3. , 3. );
  // b phi
  hists_["bQuarkPhi"    ] = fs->make<TH1F>( "bQuarkPhi"     , "bQuarkPhi"     ,   60, -pi , pi );
  // lightQuark pt
  hists_["lightQuarkPt" ] = fs->make<TH1F>( "lightQuarkPt"  , "lightQuarkPt"  ,   60, -2. , 1. );
  // lightQuark b eta
  hists_["lightQuarkEta"] = fs->make<TH1F>( "lightQuarkEta" , "lightQuarkEta" ,   60, -3. , 3. );
  // lightQuark b phi
  hists_["lightQuarkPhi"] = fs->make<TH1F>( "lightQuarkPhi" , "lightQuarkPhi" ,   60, -pi , pi );
  // w pt
  hists_["wPt"          ] = fs->make<TH1F>( "wPt"           , "wPt"           ,   60, -2. , 1. );
  // w eta
  hists_["wEta"         ] = fs->make<TH1F>( "wEta"          , "wEta"          ,   60, -3. , 3. );
  // w phi
  hists_["wPhi"         ] = fs->make<TH1F>( "wPhi"          , "wPhi"          ,   60, -pi , pi );
  // topQuark pt
  hists_["topQuarkPt"   ] = fs->make<TH1F>( "topQuarkPt"    , "topQuarkPt"    ,   60, -2. , 1. );
  // topQuark eta
  hists_["topQuarkEta"  ] = fs->make<TH1F>( "topQuarkEta"   , "topQuarkEta"   ,   60, -3. , 3. );
  // topQuark phi
  hists_["topQuarkPhi"  ] = fs->make<TH1F>( "topQuarkPhi"   , "topQuarkPhi"   ,   60, -pi , pi );

  // b pt pull
  hists_["bPullEt"     ] = fs->make<TH1F>( "bPullEt"      , "bPullEt"      ,  400, -10. , 10. );
  // b eta pull
  hists_["bPullEta"    ] = fs->make<TH1F>( "bPullEta"     , "bPullEta"     ,  200,  -5. ,  5. );
  // b phi pull
  hists_["bPullPhi"    ] = fs->make<TH1F>( "bPullPhi"     , "bPullPhi"     ,  200,  -5. ,  5. );
  // lightQuark pt pull
  hists_["lightPullEt" ] = fs->make<TH1F>( "lightPullEt"  , "lightPullEt"  ,  200,  -5. ,  5. );
  // lightQuark eta pull
  hists_["lightPullEta"] = fs->make<TH1F>( "lightPullEta" , "lightPullEta" ,  200,  -5. ,  5. );
  // lightQuark phi pull
  hists_["lightPullPhi"] = fs->make<TH1F>( "lightPullPhi" , "lightPullPhi" ,  200,  -5. ,  5. );

  /**
     KinFit Properties
  **/

  // chi2prob of kinfit log plot
  hists_["prob_log"] = fs->make<TH1F>( "prob_log" , "prob_log" ,  100, -100., 0. );
  // chi2 of kinfit
  hists_["chi2"] = fs->make<TH1F>( "chi2" , "chi2" ,  100, 0., 1000. );
  // chi2prob of kinfit
  hists_["prob"] = fs->make<TH1F>( "prob" , "prob" ,  100, 0.,    1. );

  for(unsigned int i = 1; i < numberOfHypos_; ++i){

    TString tName = "chi2_"; tName += i+1;
    std::string name = tName.Data();
    // chi2 of kinfit
    hists_[name] = fs->make<TH1F>( tName.Data() , tName.Data() ,  100, 0., 1000. );

    tName = "prob_"; tName += i+1;
    name = tName.Data();
    // chi2prob of kinfit
    hists_[name] = fs->make<TH1F>( tName.Data() , tName.Data() ,  100, 0.,    1. );
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
      hists_.find("bQuarkPt" )->second->Fill( (jets[b].pt() -tops.b("kKinFit")->pt())/jets[b].pt()  );
      // b eta
      hists_.find("bQuarkEta")->second->Fill( (jets[b].eta()-tops.b("kKinFit")->eta()) );
      // b phi
      hists_.find("bQuarkPhi")->second->Fill( deltaPhi(jets[b].phi(),tops.b("kKinFit")->phi()) );

      // b pt pull
      hists_.find("bPullEt" )->second->Fill( (jets[b].et() -tops.b("kKinFit")->et())/covM->getResolution(jets[b], "et" , true) );
      // b eta pull
      hists_.find("bPullEta")->second->Fill( (jets[b].eta()-tops.b("kKinFit")->eta())/covM->getResolution(jets[b], "eta" , true) );
      // b phi pull
      hists_.find("bPullPhi")->second->Fill( deltaPhi(jets[b].phi(),tops.b("kKinFit")->phi())/covM->getResolution(jets[b], "phi" , true) );
    }
   // make sure the bBar-jet index is in the range of the jet collection
    if( bBar >= 0 && bBar< (int)jets.size() ){
      // bBar pt
      hists_.find("bQuarkPt" )->second->Fill( (jets[bBar].pt() -tops.bBar("kKinFit")->pt())/jets[bBar].pt()  );
      // bBar eta
      hists_.find("bQuarkEta")->second->Fill( (jets[bBar].eta()-tops.bBar("kKinFit")->eta()) );
      // bBar phi
      hists_.find("bQuarkPhi")->second->Fill( deltaPhi(jets[bBar].phi(),tops.bBar("kKinFit")->phi()) );

      // bBar pt pull
      hists_.find("bPullEt" )->second->Fill( (jets[bBar].pt() -tops.bBar("kKinFit")->pt())/covM->getResolution(jets[bBar], "et" , true) );
      // bBar eta pull
      hists_.find("bPullEta")->second->Fill( (jets[bBar].eta()-tops.bBar("kKinFit")->eta())/covM->getResolution(jets[bBar], "eta" , true) );
      // bBar phi pull
      hists_.find("bPullPhi")->second->Fill( deltaPhi(jets[bBar].phi(),tops.bBar("kKinFit")->phi())/covM->getResolution(jets[bBar], "phi" , true) );
    }
   // make sure the light quark index is in the range of the jet collection
    if( lightQ >= 0 && lightQ < (int)jets.size() ){
      // lightQuark pt
      hists_.find("lightQuarkPt" )->second->Fill( (jets[lightQ].pt() -tops.lightQ("kKinFit")->pt())/jets[lightQ].pt()  );
      // lightQuark eta
      hists_.find("lightQuarkEta")->second->Fill( (jets[lightQ].eta()-tops.lightQ("kKinFit")->eta()) );
      // lightQuark phi
      hists_.find("lightQuarkPhi")->second->Fill( deltaPhi(jets[lightQ].phi(),tops.lightQ("kKinFit")->phi()) );

      // lightQuark pt pull
      hists_.find("lightPullEt" )->second->Fill((jets[lightQ].pt() -tops.lightQ("kKinFit")->pt())/covM->getResolution(jets[lightQ], "et") );
      // lightQuark eta pull
      hists_.find("lightPullEta")->second->Fill((jets[lightQ].eta()-tops.lightQ("kKinFit")->eta())/covM->getResolution(jets[lightQ], "eta") );
      // lightQuark phi pull
      hists_.find("lightPullPhi")->second->Fill(deltaPhi(jets[lightQ].phi(),tops.lightQ("kKinFit")->phi())/covM->getResolution(jets[lightQ], "phi") );
    }
    // make sure the light quark bar index is in the range of the jet collection
    if( lightQBar >= 0 && lightQBar< (int)jets.size() ){
      // lightQuark pt
      hists_.find("lightQuarkPt" )->second->Fill( (jets[lightQBar].pt() -tops.lightQBar("kKinFit")->pt())/jets[lightQBar].pt()  );
      // lightQuark eta
      hists_.find("lightQuarkEta")->second->Fill( (jets[lightQBar].eta()-tops.lightQBar("kKinFit")->eta()) );
      // lightQuark phi
      hists_.find("lightQuarkPhi")->second->Fill( deltaPhi(jets[lightQBar].phi(),tops.lightQBar("kKinFit")->phi()) );

      // lightQuark pt pull
      hists_.find("lightPullEt" )->second->Fill( (jets[lightQBar].pt() -tops.lightQBar("kKinFit")->pt())/covM->getResolution(jets[lightQBar], "et") );
      // lightQuark eta pull
      hists_.find("lightPullEta")->second->Fill( (jets[lightQBar].eta()-tops.lightQBar("kKinFit")->eta())/covM->getResolution(jets[lightQBar], "eta") );
      // lightQuark phi pull
      hists_.find("lightPullPhi")->second->Fill( deltaPhi(jets[lightQBar].phi(),tops.lightQBar("kKinFit")->phi())/covM->getResolution(jets[lightQBar], "phi") );
    }
    // make sure the light quark index is in the range of the jet collection
    if( lightP >= 0 && lightP < (int)jets.size() ){
      // lightQuark pt
      hists_.find("lightQuarkPt" )->second->Fill( (jets[lightP].pt() -tops.lightP("kKinFit")->pt())/jets[lightP].pt()  );
      // lightQuark eta
      hists_.find("lightQuarkEta")->second->Fill( (jets[lightP].eta()-tops.lightP("kKinFit")->eta()) );
      // lightQuark phi
      hists_.find("lightQuarkPhi")->second->Fill( deltaPhi(jets[lightP].phi(),tops.lightP("kKinFit")->phi()) );

      // lightQuark pt pull
      hists_.find("lightPullEt" )->second->Fill((jets[lightP].pt() -tops.lightP("kKinFit")->pt())/covM->getResolution(jets[lightP], "et") );
      // lightQuark eta pull
      hists_.find("lightPullEta")->second->Fill((jets[lightP].eta()-tops.lightP("kKinFit")->eta())/covM->getResolution(jets[lightP], "eta") );
      // lightQuark phi pull
      hists_.find("lightPullPhi")->second->Fill(deltaPhi(jets[lightP].phi(),tops.lightP("kKinFit")->phi())/covM->getResolution(jets[lightP], "phi") );
    }
    // make sure the light quark bar index is in the range of the jet collection
    if( lightPBar >= 0 && lightPBar < (int)jets.size() ){
      // lightQuark pt
      hists_.find("lightQuarkPt"  )->second->Fill( (jets[lightPBar].pt() -tops.lightPBar("kKinFit")->pt())/jets[lightPBar].pt()  );
      // lightQuark eta
      hists_.find("lightQuarkEta" )->second->Fill( (jets[lightPBar].eta()-tops.lightPBar("kKinFit")->eta()) );
      // lightQuark phi
      hists_.find("lightQuarkPhi" )->second->Fill( deltaPhi(jets[lightPBar].phi(),tops.lightPBar("kKinFit")->phi()) );

      // lightQuark pt
      hists_.find("lightPullEt" )->second->Fill( (jets[lightPBar].pt() -tops.lightPBar("kKinFit")->pt())/covM->getResolution(jets[lightPBar], "et") );
      // lightQuark eta
      hists_.find("lightPullEta")->second->Fill( (jets[lightPBar].eta()-tops.lightPBar("kKinFit")->eta())/covM->getResolution(jets[lightPBar], "eta") );
      // lightQuark phi
      hists_.find("lightPullPhi")->second->Fill( deltaPhi(jets[lightPBar].phi(),tops.lightPBar("kKinFit")->phi())/covM->getResolution(jets[lightPBar], "phi") );
    }
    // make sure the light quarks of w+ indices are in the range of the jet collection
    if( lightQ >= 0 && lightQ < (int)jets.size() && lightQBar >= 0 && lightQBar < (int)jets.size() ){
      // w+ pt
      hists_.find("wPt"  )->second->Fill( ((jets[lightQ].p4()+jets[lightQBar].p4()).pt() - (tops.lightQ("kKinFit")->p4()+tops.lightQBar("kKinFit")->p4()).pt()) /
					   (jets[lightQ].p4()+jets[lightQBar].p4()).pt() );
      // w+ eta
      hists_.find("wEta" )->second->Fill( (jets[lightQ].p4()+jets[lightQBar].p4()).eta() - (tops.lightQ("kKinFit")->p4()+tops.lightQBar("kKinFit")->p4()).eta() );
      // w+ phi
      hists_.find("wPhi" )->second->Fill( deltaPhi((jets[lightQ].p4()+jets[lightQBar].p4()).phi(), (tops.lightQ("kKinFit")->p4()+tops.lightQBar("kKinFit")->p4()).phi()) );
    }
    // make sure the light quarks of w- indices are in the range of the jet collection
    if( lightP >= 0 && lightP < (int)jets.size() && lightPBar >= 0 && lightPBar < (int)jets.size() ){
      // w+ pt
      hists_.find("wPt" )->second->Fill( ((jets[lightP].p4()+jets[lightPBar].p4()).pt() - (tops.lightP("kKinFit")->p4()+tops.lightPBar("kKinFit")->p4()).pt()) /
					 (jets[lightP].p4()+jets[lightPBar].p4()).pt());
      // w+ eta
      hists_.find("wEta")->second->Fill( (jets[lightP].p4()+jets[lightPBar].p4()).eta() - (tops.lightP("kKinFit")->p4()+tops.lightPBar("kKinFit")->p4()).eta() );
      // w+ phi
      hists_.find("wPhi" )->second->Fill( deltaPhi((jets[lightP].p4()+jets[lightPBar].p4()).phi(), (tops.lightP("kKinFit")->p4()+tops.lightPBar("kKinFit")->p4()).phi()) );
    }
    // make sure the quarks of top quark indices are in the range of the jet collection
    if( lightQ >= 0 && lightQ < (int)jets.size() && lightQBar >= 0 && lightQBar < (int)jets.size() && b >=0 && b < (int)jets.size()  ){
      // top pt
      hists_.find("topQuarkPt" )->second->Fill( ((jets[lightQ].p4()+jets[lightQBar].p4()+jets[b].p4()).pt() - 
						 (tops.lightQ("kKinFit")->p4() + tops.lightQBar("kKinFit")->p4() + tops.b("kKinFit")->p4()).pt()) /
						(jets[lightQ].p4()+jets[lightQBar].p4()+jets[b].p4()).pt());
      // top eta
      hists_.find("topQuarkEta")->second->Fill( (jets[lightQ].p4()+jets[lightQBar].p4()+jets[b].p4()).eta() - 
						(tops.lightQ("kKinFit")->p4() + tops.lightQBar("kKinFit")->p4() + tops.b("kKinFit")->p4()).eta() );
      // top phi
      hists_.find("topQuarkPhi")->second->Fill( deltaPhi((jets[lightQ].p4()+jets[lightQBar].p4()+jets[b].p4()).phi(), 
							 (tops.lightQ("kKinFit")->p4() + tops.lightQBar("kKinFit")->p4() + tops.b("kKinFit")->p4()).phi()) );
    }
    // make sure the quarks of topBar quark indices are in the range of the jet collection
    if( lightP >= 0 && lightP < (int)jets.size() && lightPBar >= 0 && lightPBar < (int)jets.size() && bBar >=0 && bBar < (int)jets.size()  ){
      // top pt
      hists_.find("topQuarkPt" )->second->Fill( ((jets[lightP].p4() + jets[lightPBar].p4() + jets[bBar].p4()).pt() - 
						 (tops.lightP("kKinFit")->p4() + tops.lightPBar("kKinFit")->p4() + tops.bBar("kKinFit")->p4()).pt()) /
						(jets[lightP].p4()+jets[lightPBar].p4()+jets[bBar].p4()).pt() );
      // top eta
      hists_.find("topQuarkEta")->second->Fill( (jets[lightP].p4() + jets[lightPBar].p4() + jets[bBar].p4()).eta() - 
						(tops.lightP("kKinFit")->p4() + tops.lightPBar("kKinFit")->p4() + tops.bBar("kKinFit")->p4()).eta() );
      // top phi
      hists_.find("topQuarkPhi")->second->Fill( deltaPhi((jets[lightP].p4() + jets[lightPBar].p4() + jets[bBar].p4()).phi(),
							 (tops.lightP("kKinFit")->p4() + tops.lightPBar("kKinFit")->p4() + tops.bBar("kKinFit")->p4()).phi()) );
    }


    // chi2 of kinfit
    hists_.find("chi2")->second->Fill( tops.fitChi2() );
    // chi2prob of kinfit
    hists_.find("prob")->second->Fill( tops.fitProb() );
    // chi2prob of kinfit log plot
    if(tops.fitProb() > 0) hists_.find("prob_log")->second->Fill( log10(tops.fitProb()) );

    if(tops.numberOfAvailableHypos("kKinFit")>1){

      for(unsigned int i = 1; i < numberOfHypos_; ++i){

	if(tops.numberOfAvailableHypos("kKinFit") > i){
	  TString tName = "chi2_"; tName += i+1;
	  std::string name = tName.Data();
	  // chi2 of kinfit
	  hists_.find(name)->second->Fill( tops.fitChi2(i) );
  
	  tName = "prob_"; tName += i+1;
	  name = tName.Data();
	  // chi2prob of kinfit
	  hists_.find(name)->second->Fill( tops.fitProb(i) );
	}
      }
    }
  }
}

