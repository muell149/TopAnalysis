#include <TMath.h>
#include "DataFormats/Math/interface/deltaR.h"
#include "TopAnalysis/TopAnalyzer/interface/KinFitImprover.h"
#include "AnalysisDataFormats/TopObjects/interface/TtFullHadEvtPartons.h"

/// default constructor for fw lite
KinFitImprover::KinFitImprover()
{
}

/// default constructor for full fw
KinFitImprover::KinFitImprover(const edm::ParameterSet& cfg)
{
  comboType_= cfg.getParameter<unsigned int>("comboType");
}

/// histogramm booking for fwlite 
void KinFitImprover::book()
{
  /** 
      Add needed histogramms from full fw list of histogramms
  **/
}

/// histogramm booking for fw
void KinFitImprover::book(edm::Service<TFileService>& fs)
{
  /** 
      book histogramms to analyze the quality of the fit
  **/

  // show comboTypes of fits
  hists_["fitQuality"] = fs->make<TH1F>( "fitQuality" , "fitQuality" , 4 , 1. , 5. );
  // top mass of fit
  hists_["topMass"  ] = fs->make<TH1F>( "topMass"   , "topMass"   ,  100 , 0. , 1000. );
  // min deltaR between b quark and corresponding light quarks (fit)
  hists_["minDRFit" ] = fs->make<TH1F>( "minDRFit"  , "minDRFit"  ,  100 , 0. ,   10. );
  // min deltaR between b quark and corresponding light quarks (reco)
  hists_["minDRRec" ] = fs->make<TH1F>( "minDRRec"  , "minDRRec"  ,  100 , 0. ,   10. );
  // min deltaR between b quark and corresponding light quarks (fit)
  hists2D_["minDRFitRec"] = fs->make<TH2F>( "minDRFitRec" , "minDRFitRec" , 100 , 0. , 10. , 100 , 0. , 10. );
  // max deltaR between b quark and corresponding light quarks (fit)
  hists_["maxDRFit" ] = fs->make<TH1F>( "maxDRFit"  , "maxDRFit"  ,  100 , 0. ,   10. );
  // max deltaR between b quark and corresponding light quarks (reco)
  hists_["maxDRRec" ] = fs->make<TH1F>( "maxDRRec"  , "maxDRRec"  ,  100 , 0. ,   10. );
  // max deltaR between b quark and corresponding light quarks (fit)
  hists2D_["maxDRFitRec"] = fs->make<TH2F>( "maxDRFitRec" , "maxDRFitRec" , 100 , 0. , 10. , 100 , 0. , 10. );
  // min vs. max deltaR between b quark and corresponding light quarks (fit)
  hists2D_["minMaxDRFit"] = fs->make<TH2F>( "minMaxDRFit" , "minMaxDRFit" , 100 , 0. , 10. , 100 , 0. , 10. );
  // min vs. max deltaR between b quark and corresponding light quarks (reco)
  hists2D_["minMaxDRRec"] = fs->make<TH2F>( "minMaxDRRec" , "minMaxDRRec" , 100 , 0. , 10. , 100 , 0. , 10. );
  // all deltaR between b quark and corresponding light quarks (fit)
  hists_["allDRFit" ] = fs->make<TH1F>( "allDRFit"  , "allDRFit"  ,  100 , 0. ,   10. );
  // all deltaR between b quark and corresponding light quarks (reco)
  hists_["allDRRec" ] = fs->make<TH1F>( "allDRRec"  , "allDRRec"  ,  100 , 0. ,   10. );
  // all deltaR between b quark and corresponding light quarks (fit)
  hists2D_["allDRFitRec"] = fs->make<TH2F>( "allDRFitRec" , "allDRFitRec" , 100 , 0. , 10. , 100 , 0. , 10. );
  // energy of process
  hists_["sqrt_s_fit"  ] = fs->make<TH1F>( "sqrt_s_fit"   , "sqrt_s_fit"   ,  500 , 0. ,   5000. );
  // pt of final system
  hists_["pt_final_fit"] = fs->make<TH1F>( "pt_final_fit" , "pt_final_fit" ,  100 , 0. ,   1000. );
  // energy of process
  hists_["sqrt_s_rec"  ] = fs->make<TH1F>( "sqrt_s_rec"   , "sqrt_s_rec"   ,  500 , 0. ,   5000. );
  // pt of final system
  hists_["pt_final_rec"] = fs->make<TH1F>( "pt_final_rec" , "pt_final_rec" ,  100 , 0. ,   1000. );
  // pt rec vs. fit of final system
  hists2D_["pt_final"] = fs->make<TH2F>( "pt_final" , "pt_final" , 100 , 0. , 1000. , 100 , 0. , 1000. );
  // Probability of fit
  hists_["prob"] = fs->make<TH1F>( "prob" , "prob" , 100 , 0. , 1. );
  // Chi2 of fit
  hists_["chi2"] = fs->make<TH1F>( "chi2" , "chi2" , 100 , 0. , 100. );
  // pt vs. top mass fit of final system
  hists2D_["pt_mass_fit"] = fs->make<TH2F>( "pt_mass_fit" , "pt_mass_fit" , 100 , 0. , 1000. , 100 , 0. , 1000. );
  // pt vs. top mass rec of final system
  hists2D_["pt_mass_rec"] = fs->make<TH2F>( "pt_mass_rec" , "pt_mass_rec" , 100 , 0. , 1000. , 100 , 0. , 1000. );
  // top mass fit vs. rec of final system
  hists2D_["mass_fit_rec"] = fs->make<TH2F>( "mass_fit_rec" , "mass_fit_rec" , 100 , 0. , 1000. , 100 , 0. , 1000. );

}

/// function to find types of jet-combinations in KinFits (1 right, 2 branches right, but inner-branche particles mixup, 3 inter-branch mixup, 4 missing jet)
int
KinFitImprover::comboType()
{
  int lightQFit    = jetIndex[LQ];
  int lightQBarFit = jetIndex[LQBar];
  int bFit         = jetIndex[B];
  int bBarFit      = jetIndex[BBar];
  int lightPFit    = jetIndex[LP];
  int lightPBarFit = jetIndex[LPBar];

  int lightQGen    = jetIndex[LQ_Gen];
  int lightQBarGen = jetIndex[LQBar_Gen];
  int bGen         = jetIndex[B_Gen];
  int bBarGen      = jetIndex[BBar_Gen];
  int lightPGen    = jetIndex[LP_Gen];
  int lightPBarGen = jetIndex[LPBar_Gen];

  std::list<int> fit;
  std::list<int> fitBar;
  std::list<int> gen;
  std::list<int> genBar;

  fit.push_back(jetIndex[LQ]);
  fit.push_back(jetIndex[LQBar]);
  fit.push_back(jetIndex[B]);

  fitBar.push_back(jetIndex[LP]);
  fitBar.push_back(jetIndex[LPBar]);
  fitBar.push_back(jetIndex[BBar]);

  gen.push_back(jetIndex[LQ_Gen]);
  gen.push_back(jetIndex[LQBar_Gen]);
  gen.push_back(jetIndex[B_Gen]);

  genBar.push_back(jetIndex[LP_Gen]);
  genBar.push_back(jetIndex[LPBar_Gen]);
  genBar.push_back(jetIndex[BBar_Gen]);

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

/// histogram filling interface for reconstruction level for access with fwlite or full framework
void
KinFitImprover::fill(const TtFullHadronicEvent& tops, const edm::View<pat::Jet>& jets, const double& weight)
{
  // make sure to have a valid hypothesis on reconstruction level
  if( tops.isHypoValid("kKinFit") ){

    // define indices in pat::Jet collection
    jetIndex.clear();
    jetIndex.resize(6);

    /// keep vector jetIndex and enum whichParticle (filled in interface/KinFitImprover.h) synced !!!

    jetIndex[0]  = tops.jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::LightQ   ];
    jetIndex[1]  = tops.jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::LightQBar];
    jetIndex[2]  = tops.jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::B        ];
    jetIndex[3]  = tops.jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::BBar     ];
    jetIndex[4]  = tops.jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::LightP   ];
    jetIndex[5]  = tops.jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::LightPBar];

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


      if(tops.numberOfAvailableHypos("kKinFit")>1){
      }
    */

    float dR1 = deltaR(tops.b("kKinFit")->phi(), tops.b("kKinFit")->eta(), tops.lightQ("kKinFit")->phi(), tops.lightQ("kKinFit")->eta());
    float dR2 = deltaR(tops.b("kKinFit")->phi(), tops.b("kKinFit")->eta(), tops.lightQBar("kKinFit")->phi(), tops.lightQBar("kKinFit")->eta());
    float dR3 = deltaR(tops.bBar("kKinFit")->phi(), tops.bBar("kKinFit")->eta(), tops.lightP("kKinFit")->phi(), tops.lightP("kKinFit")->eta());
    float dR4 = deltaR(tops.bBar("kKinFit")->phi(), tops.bBar("kKinFit")->eta(), tops.lightPBar("kKinFit")->phi(), tops.lightPBar("kKinFit")->eta());

    float dR1Rec;
    float dR2Rec;
    float dR3Rec;
    float dR4Rec;
    dR1Rec = deltaR(jets[jetIndex[B   ]].phi(), jets[jetIndex[B   ]].eta(), jets[jetIndex[LQ   ]].phi(), jets[jetIndex[LQ   ]].eta());
    dR2Rec = deltaR(jets[jetIndex[B   ]].phi(), jets[jetIndex[B   ]].eta(), jets[jetIndex[LQBar]].phi(), jets[jetIndex[LQBar]].eta());
    dR3Rec = deltaR(jets[jetIndex[BBar]].phi(), jets[jetIndex[BBar]].eta(), jets[jetIndex[LP   ]].phi(), jets[jetIndex[LP   ]].eta());
    dR4Rec = deltaR(jets[jetIndex[BBar]].phi(), jets[jetIndex[BBar]].eta(), jets[jetIndex[LPBar]].phi(), jets[jetIndex[LPBar]].eta());

    std::vector<float> dRs;
    dRs.clear();
      
    dRs.push_back(dR1);
      
    if(dR2 < dR1) dRs.insert(dRs.begin(), dR2);
    else dRs.push_back(dR2);
      
    if(dR3 < dR1) dRs.insert(dRs.begin(), dR3);
    else if(dR3 < dR2) dRs.insert(++dRs.begin(), dR3);
    else dRs.push_back(dR3);
      
    if(dR4 < dR1) dRs.insert(dRs.begin(), dR4);
    else if(dR4 < dR2) dRs.insert(++dRs.begin(), dR4);
    else if(dR4 < dR3) dRs.insert(++(++dRs.begin()), dR4);
    else dRs.push_back(dR4);

    std::vector<float> dRecs;
    dRecs.clear();
      
    dRecs.push_back(dR1Rec);
      
    if(dR2Rec < dR1Rec) dRecs.insert(dRecs.begin(), dR2Rec);
    else dRecs.push_back(dR2Rec);
      
    if(dR3Rec < dR1Rec) dRecs.insert(dRecs.begin(), dR3Rec);
    else if(dR3Rec < dR2Rec) dRecs.insert(++dRecs.begin(), dR3Rec);
    else dRecs.push_back(dR3Rec);
      
    if(dR4Rec < dR1Rec) dRecs.insert(dRecs.begin(), dR4Rec);
    else if(dR4Rec < dR2Rec) dRecs.insert(++dRecs.begin(), dR4Rec);
    else if(dR4Rec < dR3Rec) dRecs.insert(++(++dRecs.begin()), dR4Rec);
    else dRecs.push_back(dR4Rec);
      
    reco::Candidate::LorentzVector top_p4    = jets[jetIndex[LQ]].p4() + jets[jetIndex[LQBar]].p4() + jets[jetIndex[B   ]].p4();
    reco::Candidate::LorentzVector topBar_p4 = jets[jetIndex[LP]].p4() + jets[jetIndex[LPBar]].p4() + jets[jetIndex[BBar]].p4();

    double sqrt_s_fit = ( tops.top("kKinFit")->p4() + tops.topBar("kKinFit")->p4() ).mass();
    double sqrt_s_rec = ( top_p4 + topBar_p4 ).mass();
 
    double pt_final_fit = ( tops.top("kKinFit")->p4() + tops.topBar("kKinFit")->p4() ).pt();
    double pt_final_rec = ( top_p4 + topBar_p4 ).pt();

    double top_mass_fit    = tops.top("kKinFit")->mass();
    double topBar_mass_fit = tops.topBar("kKinFit")->mass();

    double top_pt_fit      = tops.top("kKinFit")->pt();
    double topBar_pt_fit   = tops.topBar("kKinFit")->pt();

    double top_mass_rec    = ( top_p4 ).mass();
    double topBar_mass_rec = ( topBar_p4 ).mass();

    double top_pt_rec    = ( top_p4 ).pt();
    double topBar_pt_rec = ( topBar_p4 ).pt();

    int comboTypeValue = 0;

    if( tops.isHypoValid("kGenMatch") ){

      jetIndex.resize(12);

      jetIndex[6]  = tops.jetLeptonCombination("kGenMatch")[TtFullHadEvtPartons::LightQ   ];
      jetIndex[7]  = tops.jetLeptonCombination("kGenMatch")[TtFullHadEvtPartons::LightQBar];
      jetIndex[8]  = tops.jetLeptonCombination("kGenMatch")[TtFullHadEvtPartons::B        ];
      jetIndex[9]  = tops.jetLeptonCombination("kGenMatch")[TtFullHadEvtPartons::BBar     ];
      jetIndex[10] = tops.jetLeptonCombination("kGenMatch")[TtFullHadEvtPartons::LightP   ];
      jetIndex[11] = tops.jetLeptonCombination("kGenMatch")[TtFullHadEvtPartons::LightPBar];

      comboTypeValue = comboType();
    }

    hists_.find("fitQuality")->second->Fill( comboTypeValue + 0.5 );

    if( comboType_ == comboTypeValue ){
      hists_.find("topMass"  )->second->Fill( top_mass_fit );
      hists_.find("allDRFit" )->second->Fill( dR1 );
      hists_.find("allDRFit" )->second->Fill( dR2 );
      hists_.find("allDRFit" )->second->Fill( dR3 );
      hists_.find("allDRFit" )->second->Fill( dR4 );
      hists_.find("minDRFit" )->second->Fill( dRs.front() );
      hists_.find("maxDRFit" )->second->Fill( dRs.back() );
      hists2D_.find("minMaxDRFit")->second->Fill( dRs.back() , dRs.front() );
	
      hists_.find("allDRRec" )->second->Fill( dR1Rec );
      hists_.find("allDRRec" )->second->Fill( dR2Rec );
      hists_.find("allDRRec" )->second->Fill( dR3Rec );
      hists_.find("allDRRec" )->second->Fill( dR4Rec );
      hists_.find("minDRRec" )->second->Fill( dRecs.front() );
      hists_.find("maxDRRec" )->second->Fill( dRecs.back() );
      hists2D_.find("minMaxDRRec")->second->Fill( dRecs.back() , dRecs.front() );
      hists2D_.find("minDRFitRec")->second->Fill( dRecs.front() , dRs.front() );
      hists2D_.find("maxDRFitRec")->second->Fill( dRecs.back() , dRs.back() );
      hists2D_.find("allDRFitRec")->second->Fill( dR1Rec , dR1 );
      hists2D_.find("allDRFitRec")->second->Fill( dR2Rec , dR2 );
      hists2D_.find("allDRFitRec")->second->Fill( dR3Rec , dR3 );
      hists2D_.find("allDRFitRec")->second->Fill( dR4Rec , dR4 );

      hists_.find("sqrt_s_fit"  )->second->Fill( sqrt_s_fit );
      hists_.find("sqrt_s_rec"  )->second->Fill( sqrt_s_rec );
      hists_.find("pt_final_fit")->second->Fill( pt_final_fit );
      hists_.find("pt_final_rec")->second->Fill( pt_final_rec );
      hists2D_.find("pt_final")->second->Fill( pt_final_fit, pt_final_rec );
      hists2D_.find("pt_mass_fit")->second->Fill( top_pt_fit, top_mass_fit );
      hists2D_.find("pt_mass_fit")->second->Fill( topBar_pt_fit, topBar_mass_fit );
      hists2D_.find("pt_mass_rec")->second->Fill( top_pt_rec, top_mass_rec );
      hists2D_.find("pt_mass_rec")->second->Fill( topBar_pt_rec, topBar_mass_rec );
      hists2D_.find("mass_fit_rec")->second->Fill( top_mass_fit, top_mass_rec );
      hists2D_.find("mass_fit_rec")->second->Fill( topBar_mass_fit, topBar_mass_rec );

      hists_.find("prob")->second->Fill( tops.fitProb() );
      hists_.find("chi2")->second->Fill( tops.fitChi2() );
    }
    dRs.clear();
    dRecs.clear();
  }
  jetIndex.clear();
}
