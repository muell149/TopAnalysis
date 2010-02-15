#include "TopAnalysis/TopAnalyzer/interface/FullHadSpecial.h"

/// default constructor for fw lite
FullHadSpecial::FullHadSpecial(const std::string& correctionLevel) : correctionLevel_(correctionLevel)
{
}

/// default constructor for fwfull
FullHadSpecial::FullHadSpecial(const edm::ParameterSet& cfg) :
  correctionLevel_( cfg.getParameter<std::string>( "correctionLevel" ) )
{
}

/// histogramm booking for fwlite 
void
FullHadSpecial::book()
{
  /**
     add histogramms from full fw booking here if fw lite needed
  **/

}

/// histogramm booking for full fw
void
FullHadSpecial::book(edm::Service<TFileService>& fs)
{
  /// Ht, sum of Et of all jets
  hists_["ht"      ] = fs->make<TH1F>( "ht"       , "ht"       ,   500 ,  0. ,  2500. );
  /// real B-Quarks, -1 fake, 1 real
  hists_["realB"   ] = fs->make<TH1F>( "realB"    , "realB"    ,     2 , -1. ,     1. );
  /// real B-Quarks, -1 fake, 1 real
  hists_["realBCSV"] = fs->make<TH1F>( "realBCSV" , "realBCSV" ,     2 , -1. ,     1. );
  /// real B-Quarks, -1 fake, 1 real
  hists_["realBSM" ] = fs->make<TH1F>( "realBSM"  , "realBSM"  ,     2 , -1. ,     1. );
  /// di-jet mass
  hists_["mjj"     ] = fs->make<TH1F>( "mjj"      , "mjj"      ,   400 ,  0. ,  2000. );
  /// tri-jet mass
  hists_["mjjj"    ] = fs->make<TH1F>( "mjjj"     , "mjjj"     ,   400 ,  0. ,  2000. );
  /// uncorrected jet pt
  hists_["jetPtUn" ] = fs->make<TH1F>( "jetPtUn"  , "jetPtUn"  ,    50 ,  0. ,   500. );
  /// passing HLT_QuadJet30
  hists_["hltQuadPass"] = fs->make<TH1F>( "hltQuadPass" , "hltQuadPass" , 2 , -1. , 1.);
  /// pt of b1 vs. pt of b2
  hists2D_["ptb1ptb2" ] = fs->make<TH2F>( "ptb1ptb2" , "ptb1ptb2" ,   130 , 20. ,   150. , 130 , 20. , 150. );
  /// pt of 1 vs. pt of 2
  hists2D_["pt1pt2"   ] = fs->make<TH2F>( "pt1pt2"   , "pt1pt2"   ,   130 , 20. ,   150. , 130 , 20. , 150. );
  /// pt of 1 vs. pt of 3
  hists2D_["pt1pt3"   ] = fs->make<TH2F>( "pt1pt3"   , "pt1pt3"   ,   130 , 20. ,   150. , 130 , 20. , 150. );
  /// pt of 1 vs. pt of 4
  hists2D_["pt1pt4"   ] = fs->make<TH2F>( "pt1pt4"   , "pt1pt4"   ,   130 , 20. ,   150. , 130 , 20. , 150. );
  /// pt of 1 vs. pt of 5
  hists2D_["pt1pt5"   ] = fs->make<TH2F>( "pt1pt5"   , "pt1pt5"   ,   130 , 20. ,   150. , 130 , 20. , 150. );
  /// pt of 1 vs. pt of 6
  hists2D_["pt1pt6"   ] = fs->make<TH2F>( "pt1pt6"   , "pt1pt6"   ,   130 , 20. ,   150. , 130 , 20. , 150. );
  /// pt of 2 vs. pt of 3
  hists2D_["pt2pt3"   ] = fs->make<TH2F>( "pt2pt3"   , "pt2pt3"   ,   130 , 20. ,   150. , 130 , 20. , 150. );
  /// pt of 2 vs. pt of 4
  hists2D_["pt2pt4"   ] = fs->make<TH2F>( "pt2pt4"   , "pt2pt4"   ,   130 , 20. ,   150. , 130 , 20. , 150. );
  /// pt of 2 vs. pt of 5
  hists2D_["pt2pt5"   ] = fs->make<TH2F>( "pt2pt5"   , "pt2pt5"   ,   130 , 20. ,   150. , 130 , 20. , 150. );
  /// pt of 2 vs. pt of 6
  hists2D_["pt2pt6"   ] = fs->make<TH2F>( "pt2pt6"   , "pt2pt6"   ,   130 , 20. ,   150. , 130 , 20. , 150. );
  /// pt of 3 vs. pt of 4
  hists2D_["pt3pt4"   ] = fs->make<TH2F>( "pt3pt4"   , "pt3pt4"   ,   130 , 20. ,   150. , 130 , 20. , 150. );
  /// pt of 3 vs. pt of 5
  hists2D_["pt3pt5"   ] = fs->make<TH2F>( "pt3pt5"   , "pt3pt5"   ,   130 , 20. ,   150. , 130 , 20. , 150. );
  /// pt of 3 vs. pt of 6
  hists2D_["pt3pt6"   ] = fs->make<TH2F>( "pt3pt6"   , "pt3pt6"   ,   130 , 20. ,   150. , 130 , 20. , 150. );
  /// pt of 4 vs. pt of 5
  hists2D_["pt4pt5"   ] = fs->make<TH2F>( "pt4pt5"   , "pt4pt5"   ,   130 , 20. ,   150. , 130 , 20. , 150. );
  /// pt of 4 vs. pt of 6
  hists2D_["pt4pt6"   ] = fs->make<TH2F>( "pt4pt6"   , "pt4pt6"   ,   130 , 20. ,   150. , 130 , 20. , 150. );
  /// pt of 5 vs. pt of 6
  hists2D_["pt5pt6"   ] = fs->make<TH2F>( "pt5pt6"   , "pt5pt6"   ,   130 , 20. ,   150. , 130 , 20. , 150. );
  /// pt of b1 - pt of b2
  hists_["ptb1-ptb2" ] = fs->make<TH1F>( "ptb1-ptb2" , "ptb1-ptb2" , 200 , 0. , 200. );
  /// pt of 1 - pt of 2
  hists_["pt1-pt2" ] = fs->make<TH1F>( "pt1-pt2" , "pt1-pt2" , 200 , 0. , 200. );
  /// pt of 1 - pt of 3
  hists_["pt1-pt3" ] = fs->make<TH1F>( "pt1-pt3" , "pt1-pt3" , 200 , 0. , 200. );
  /// pt of 1 - pt of 4
  hists_["pt1-pt4" ] = fs->make<TH1F>( "pt1-pt4" , "pt1-pt4" , 200 , 0. , 200. );
  /// pt of 1 - pt of 5
  hists_["pt1-pt5" ] = fs->make<TH1F>( "pt1-pt5" , "pt1-pt5" , 200 , 0. , 200. );
  /// pt of 1 - pt of 6
  hists_["pt1-pt6" ] = fs->make<TH1F>( "pt1-pt6" , "pt1-pt6" , 200 , 0. , 200. );
  /// pt of 2 - pt of 3
  hists_["pt2-pt3" ] = fs->make<TH1F>( "pt2-pt3" , "pt2-pt3" , 200 , 0. , 200. );
  /// pt of 2 - pt of 4
  hists_["pt2-pt4" ] = fs->make<TH1F>( "pt2-pt4" , "pt2-pt4" , 200 , 0. , 200. );
  /// pt of 2 - pt of 5
  hists_["pt2-pt5" ] = fs->make<TH1F>( "pt2-pt5" , "pt2-pt5" , 200 , 0. , 200. );
  /// pt of 2 - pt of 6
  hists_["pt2-pt6" ] = fs->make<TH1F>( "pt2-pt6" , "pt2-pt6" , 200 , 0. , 200. );
  /// pt of 3 - pt of 4
  hists_["pt3-pt4" ] = fs->make<TH1F>( "pt3-pt4" , "pt3-pt4" , 200 , 0. , 200. );
  /// pt of 3 - pt of 5
  hists_["pt3-pt5" ] = fs->make<TH1F>( "pt3-pt5" , "pt3-pt5" , 200 , 0. , 200. );
  /// pt of 3 - pt of 6
  hists_["pt3-pt6" ] = fs->make<TH1F>( "pt3-pt6" , "pt3-pt6" , 200 , 0. , 200. );
  /// pt of 4 - pt of 5
  hists_["pt4-pt5" ] = fs->make<TH1F>( "pt4-pt5" , "pt4-pt5" , 200 , 0. , 200. );
  /// pt of 4 - pt of 6
  hists_["pt4-pt6" ] = fs->make<TH1F>( "pt4-pt6" , "pt4-pt6" , 200 , 0. , 200. );
  /// pt of 5 - pt of 6
  hists_["pt5-pt6" ] = fs->make<TH1F>( "pt5-pt6" , "pt5-pt6" , 200 , 0. , 200. );
  /// pt of b1 - pt of b2 norm
  hists_["ptb1-ptb2_norm" ] = fs->make<TH1F>( "ptb1-ptb2_norm" , "ptb1-ptb2_norm" , 100 , 0. , 1. );
  /// pt of 1 - pt of 2 norm
  hists_["pt1-pt2_norm" ] = fs->make<TH1F>( "pt1-pt2_norm" , "pt1-pt2_norm" , 100 , 0. , 1. );
  /// pt of 1 - pt of 3 norm
  hists_["pt1-pt3_norm" ] = fs->make<TH1F>( "pt1-pt3_norm" , "pt1-pt3_norm" , 100 , 0. , 1. );
  /// pt of 1 - pt of 4 norm
  hists_["pt1-pt4_norm" ] = fs->make<TH1F>( "pt1-pt4_norm" , "pt1-pt4_norm" , 100 , 0. , 1. );
  /// pt of 1 - pt of 5 norm
  hists_["pt1-pt5_norm" ] = fs->make<TH1F>( "pt1-pt5_norm" , "pt1-pt5_norm" , 100 , 0. , 1. );
  /// pt of 1 - pt of 6 norm
  hists_["pt1-pt6_norm" ] = fs->make<TH1F>( "pt1-pt6_norm" , "pt1-pt6_norm" , 100 , 0. , 1. );
  /// pt of 2 - pt of 3 norm
  hists_["pt2-pt3_norm" ] = fs->make<TH1F>( "pt2-pt3_norm" , "pt2-pt3_norm" , 100 , 0. , 1. );
  /// pt of 2 - pt of 4 norm
  hists_["pt2-pt4_norm" ] = fs->make<TH1F>( "pt2-pt4_norm" , "pt2-pt4_norm" , 100 , 0. , 1. );
  /// pt of 2 - pt of 5 norm
  hists_["pt2-pt5_norm" ] = fs->make<TH1F>( "pt2-pt5_norm" , "pt2-pt5_norm" , 100 , 0. , 1. );
  /// pt of 2 - pt of 6 norm
  hists_["pt2-pt6_norm" ] = fs->make<TH1F>( "pt2-pt6_norm" , "pt2-pt6_norm" , 100 , 0. , 1. );
  /// pt of 3 - pt of 4 norm
  hists_["pt3-pt4_norm" ] = fs->make<TH1F>( "pt3-pt4_norm" , "pt3-pt4_norm" , 100 , 0. , 1. );
  /// pt of 3 - pt of 5 norm
  hists_["pt3-pt5_norm" ] = fs->make<TH1F>( "pt3-pt5_norm" , "pt3-pt5_norm" , 100 , 0. , 1. );
  /// pt of 3 - pt of 6 norm
  hists_["pt3-pt6_norm" ] = fs->make<TH1F>( "pt3-pt6_norm" , "pt3-pt6_norm" , 100 , 0. , 1. );
  /// pt of 4 - pt of 5 norm
  hists_["pt4-pt5_norm" ] = fs->make<TH1F>( "pt4-pt5_norm" , "pt4-pt5_norm" , 100 , 0. , 1. );
  /// pt of 4 - pt of 6 norm
  hists_["pt4-pt6_norm" ] = fs->make<TH1F>( "pt4-pt6_norm" , "pt4-pt6_norm" , 100 , 0. , 1. );
  /// pt of 5 - pt of 6 norm
  hists_["pt5-pt6_norm" ] = fs->make<TH1F>( "pt5-pt6_norm" , "pt5-pt6_norm" , 100 , 0. , 1. );
  /// thrust
  //hists_["thrust"  ] = fs->make<TH1F>( "thrust"   , "thrust"   ,   100 ,  0. ,     1. );
  /// (thrust - real) vs Ht
  //hists_["thrustHt"] = fs->make<TH1F>( "thrustHt" , "thrustHt" ,   100 ,  0. ,     1. );
  /// eta-eta-moment
  hists_["etaeta"  ] = fs->make<TH1F>( "etaeta" , "etaeta" , 120 , 0. , 0.12 );
  /// eta-phi-moment
  hists_["etaphi"  ] = fs->make<TH1F>( "etaphi" , "etaphi" , 100 , -0.05 , 0.05 );
  /// phi-phi-moment
  hists_["phiphi"  ] = fs->make<TH1F>( "phiphi" , "phiphi" , 120 , 0. , 0.12 );
  /// eta-eta-moment vs. phi-phi-moment
  hists2D_["etaetaphiphi"] = fs->make<TH2F>( "etaetaphiphi" , "etaetaphiphi" , 120 , 0. , 0.12 , 120 , 0. , 0.12 );
  /// eta-eta-moment vs. eta-phi-moment
  hists2D_["etaetaetaphi"] = fs->make<TH2F>( "etaetaetaphi" , "etaetaetaphi" , 120 , 0. , 0.12 , 100 , -0.05 , 0.05 );
  /// eta-phi-moment vs. phi-phi-moment
  hists2D_["etaphiphiphi"] = fs->make<TH2F>( "etaphiphiphi" , "etaphiphiphi" , 100 , -0.05 , 0.05 , 120 , 0. , 0.12 );
  /// eta-eta-moment for b jets
  hists_["etaeta_b"  ] = fs->make<TH1F>( "etaeta_b" , "etaeta_b" , 110 , 0. , 0.12 );
  /// eta-phi-moment for b jets
  hists_["etaphi_b"  ] = fs->make<TH1F>( "etaphi_b" , "etaphi_b" , 100 , -0.05 , 0.05 );
  /// phi-phi-moment for b jets
  hists_["phiphi_b"  ] = fs->make<TH1F>( "phiphi_b" , "phiphi_b" , 120 , 0. , 0.12 );
  /// eta-eta-moment vs. phi-phi-moment for b jets
  hists2D_["etaetaphiphi_b"] = fs->make<TH2F>( "etaetaphiphi_b" , "etaetaphiphi_b" , 120 , 0. , 0.12 , 120 , 0. , 0.12 );
  /// eta-eta-moment vs. eta-phi-moment for b jets
  hists2D_["etaetaetaphi_b"] = fs->make<TH2F>( "etaetaetaphi_b" , "etaetaetaphi_b" , 120 , 0. , 0.12 , 100 , -0.05 , 0.05 );
  /// eta-phi-moment vs. phi-phi-moment for b jets
  hists2D_["etaphiphiphi_b"] = fs->make<TH2F>( "etaphiphiphi_b" , "etaphiphiphi_b" , 100 , -0.05 , 0.05 , 120 , 0. , 0.12 );
  /// eta-eta-moment for q jets
  hists_["etaeta_q"  ] = fs->make<TH1F>( "etaeta_q" , "etaeta_q" , 120 , 0. , 0.12 );
  /// eta-phi-moment for q jets
  hists_["etaphi_q"  ] = fs->make<TH1F>( "etaphi_q" , "etaphi_q" , 100 , -0.05 , 0.05 );
  /// phi-phi-moment for q jets
  hists_["phiphi_q"  ] = fs->make<TH1F>( "phiphi_q" , "phiphi_q" , 120 , 0. , 0.12 );
  /// eta-eta-moment vs. phi-phi-moment for q jets
  hists2D_["etaetaphiphi_q"] = fs->make<TH2F>( "etaetaphiphi_q" , "etaetaphiphi_q" , 120 , 0. , 0.12 , 120 , 0. , 0.12 );
  /// eta-eta-moment vs. eta-phi-moment for q jets
  hists2D_["etaetaetaphi_q"] = fs->make<TH2F>( "etaetaetaphi_q" , "etaetaetaphi_q" , 120 , 0. , 0.12 , 100 , -0.05 , 0.05 );
  /// eta-phi-moment vs. phi-phi-moment for q jets
  hists2D_["etaphiphiphi_q"] = fs->make<TH2F>( "etaphiphiphi_q" , "etaphiphiphi_q" , 100 , -0.05 , 0.05 , 120 , 0. , 0.12 );
  /// eta-eta-moment for g jets
  hists_["etaeta_g"  ] = fs->make<TH1F>( "etaeta_g" , "etaeta_g" , 120 , 0. , 0.12 );
  /// eta-phi-moment for g jets
  hists_["etaphi_g"  ] = fs->make<TH1F>( "etaphi_g" , "etaphi_g" , 100 , -0.05 , 0.05 );
  /// phi-phi-moment for g jets
  hists_["phiphi_g"  ] = fs->make<TH1F>( "phiphi_g" , "phiphi_g" , 120 , 0. , 0.12 );
  /// eta-eta-moment vs. phi-phi-moment for g jets
  hists2D_["etaetaphiphi_g"] = fs->make<TH2F>( "etaetaphiphi_g" , "etaetaphiphi_g" , 120 , 0. , 0.12 , 120 , 0. , 0.12 );
  /// eta-eta-moment vs. eta-phi-moment for g jets
  hists2D_["etaetaetaphi_g"] = fs->make<TH2F>( "etaetaetaphi_g" , "etaetaetaphi_g" , 120 , 0. , 0.12 , 100 , -0.05 , 0.05 );
  /// eta-phi-moment vs. phi-phi-moment for g jets
  hists2D_["etaphiphiphi_g"] = fs->make<TH2F>( "etaphiphiphi_g" , "etaphiphiphi_g" , 100 , -0.05 , 0.05 , 120 , 0. , 0.12 );
  /// sqrt s
  hists_["sqrt_s"] = fs->make<TH1F>( "sqrt_s" , "sqrt_s" ,  500 , 0. , 2500. );
  /// Ht3j, sum of Et of all jets starting from 3. jet
  hists_["ht3jet"] = fs->make<TH1F>( "ht3jet" , "ht3jet" ,  200 , 0. , 1000. );
  /// Et56, geometric mean of Et of 5. and 6. jet
  hists_["et56"  ] = fs->make<TH1F>( "et56"   , "et56"   ,   50 , 0. ,  150. );
  /// Centrality (HT/H)
  hists_["centrality"] = fs->make<TH1F>( "centrality" , "centrality" ,  110 , 0. ,  1.1 );
}

/// histogram filling for fwlite and for full fw
void
FullHadSpecial::fill(const edm::View<pat::Jet>& jets, const double& weight)
{
/**
   Calculate variables and fill histograms
**/

  double ht_ = 0;
  double h_  = 0;
  double ht3jet_ = 0;
  int hltQuadJetCounter = 0;
  int bJetCounter = 0;
  edm::View<pat::Jet>::const_iterator bJet1;
  edm::View<pat::Jet>::const_iterator Jet1;
  edm::View<pat::Jet>::const_iterator Jet2;
  edm::View<pat::Jet>::const_iterator Jet3;
  edm::View<pat::Jet>::const_iterator Jet4;
  edm::View<pat::Jet>::const_iterator Jet5;
  edm::View<pat::Jet>::const_iterator Jet6;
  std::string corL_ = "abs";
  std::string corB_ = "abs";

  unsigned int idx = 0;

  for(edm::View<pat::Jet>::const_iterator jet = jets.begin(); jet != jets.end(); ++jet, ++idx){

    ht_ += jet->et();
    h_  += jet->energy();
    ht3jet_ += jet->et();

    hists_.find("jetPtUn")->second->Fill( jet->correctedJet("raw").pt() , weight );

    if(jet->correctedJet("abs").pt() > 30 && hltQuadJetCounter < 4){

      ++hltQuadJetCounter;
      
      if(hltQuadJetCounter == 4){
	hists_.find("hltQuadPass")->second->Fill(  0.5 , weight );
      }
      if(hltQuadJetCounter < 4 && jet == jets.end()){
	hists_.find("hltQuadPass")->second->Fill( -0.5 , weight );
      }
    }

    if(idx == 0){
      Jet1 = jet;
      ht3jet_ -= jet->et();
    }
    if(idx == 1){
      Jet2 = jet;
      hists2D_.find("pt1pt2")->second->Fill( Jet1->correctedJet(corL_).pt(), Jet2->correctedJet(corL_).pt(), weight );
      hists_.find("pt1-pt2")->second->Fill( Jet1->correctedJet(corL_).pt() - Jet2->correctedJet(corL_).pt() );
      hists_.find("pt1-pt2_norm")->second->Fill( (Jet1->correctedJet(corL_).pt() - Jet2->correctedJet(corL_).pt()) /
						 (Jet1->correctedJet(corL_).pt() + Jet2->correctedJet(corL_).pt()) );
      ht3jet_ -= jet->et();
    }
    if(idx == 2){
      Jet3 = jet;
      hists2D_.find("pt1pt3")->second->Fill( Jet1->correctedJet(corL_).pt(), Jet3->correctedJet(corL_).pt(), weight );
      hists2D_.find("pt2pt3")->second->Fill( Jet2->correctedJet(corL_).pt(), Jet3->correctedJet(corL_).pt(), weight );
      hists_.find("pt1-pt3")->second->Fill( Jet1->correctedJet(corL_).pt() - Jet3->correctedJet(corL_).pt() );
      hists_.find("pt2-pt3")->second->Fill( Jet2->correctedJet(corL_).pt() - Jet3->correctedJet(corL_).pt() );
      hists_.find("pt1-pt3_norm")->second->Fill( (Jet1->correctedJet(corL_).pt() - Jet3->correctedJet(corL_).pt()) /
						 (Jet1->correctedJet(corL_).pt() + Jet3->correctedJet(corL_).pt()) );
      hists_.find("pt2-pt3_norm")->second->Fill( (Jet2->correctedJet(corL_).pt() - Jet3->correctedJet(corL_).pt()) /
						 (Jet2->correctedJet(corL_).pt() + Jet3->correctedJet(corL_).pt()) );
    }
    if(idx == 3){
      Jet4 = jet;
      hists2D_.find("pt1pt4")->second->Fill( Jet1->correctedJet(corL_).pt(), Jet4->correctedJet(corL_).pt(), weight );
      hists2D_.find("pt2pt4")->second->Fill( Jet2->correctedJet(corL_).pt(), Jet4->correctedJet(corL_).pt(), weight );
      hists2D_.find("pt3pt4")->second->Fill( Jet3->correctedJet(corL_).pt(), Jet4->correctedJet(corL_).pt(), weight );
      hists_.find("pt1-pt4")->second->Fill( Jet1->correctedJet(corL_).pt() - Jet4->correctedJet(corL_).pt() );
      hists_.find("pt2-pt4")->second->Fill( Jet2->correctedJet(corL_).pt() - Jet4->correctedJet(corL_).pt() );
      hists_.find("pt3-pt4")->second->Fill( Jet3->correctedJet(corL_).pt() - Jet4->correctedJet(corL_).pt() );
      hists_.find("pt1-pt4_norm")->second->Fill( (Jet1->correctedJet(corL_).pt() - Jet4->correctedJet(corL_).pt()) /
						 (Jet1->correctedJet(corL_).pt() + Jet4->correctedJet(corL_).pt()) );
      hists_.find("pt2-pt4_norm")->second->Fill( (Jet2->correctedJet(corL_).pt() - Jet4->correctedJet(corL_).pt()) /
						 (Jet2->correctedJet(corL_).pt() + Jet4->correctedJet(corL_).pt()) );
      hists_.find("pt3-pt4_norm")->second->Fill( (Jet3->correctedJet(corL_).pt() - Jet4->correctedJet(corL_).pt()) /
						 (Jet3->correctedJet(corL_).pt() + Jet4->correctedJet(corL_).pt()) );
    }
    if(idx == 4){
      Jet5 = jet;
      hists2D_.find("pt1pt5")->second->Fill( Jet1->correctedJet(corL_).pt(), Jet5->correctedJet(corL_).pt(), weight );
      hists2D_.find("pt2pt5")->second->Fill( Jet2->correctedJet(corL_).pt(), Jet5->correctedJet(corL_).pt(), weight );
      hists2D_.find("pt3pt5")->second->Fill( Jet3->correctedJet(corL_).pt(), Jet5->correctedJet(corL_).pt(), weight );
      hists2D_.find("pt4pt5")->second->Fill( Jet4->correctedJet(corL_).pt(), Jet5->correctedJet(corL_).pt(), weight );
      hists_.find("pt1-pt5")->second->Fill( Jet1->correctedJet(corL_).pt() - Jet5->correctedJet(corL_).pt() );
      hists_.find("pt2-pt5")->second->Fill( Jet2->correctedJet(corL_).pt() - Jet5->correctedJet(corL_).pt() );
      hists_.find("pt3-pt5")->second->Fill( Jet3->correctedJet(corL_).pt() - Jet5->correctedJet(corL_).pt() );
      hists_.find("pt4-pt5")->second->Fill( Jet4->correctedJet(corL_).pt() - Jet5->correctedJet(corL_).pt() );
      hists_.find("pt1-pt5_norm")->second->Fill( (Jet1->correctedJet(corL_).pt() - Jet5->correctedJet(corL_).pt()) /
						 (Jet1->correctedJet(corL_).pt() + Jet5->correctedJet(corL_).pt()) );
      hists_.find("pt2-pt5_norm")->second->Fill( (Jet2->correctedJet(corL_).pt() - Jet5->correctedJet(corL_).pt()) /
						 (Jet2->correctedJet(corL_).pt() + Jet5->correctedJet(corL_).pt()) );
      hists_.find("pt3-pt5_norm")->second->Fill( (Jet3->correctedJet(corL_).pt() - Jet5->correctedJet(corL_).pt()) /
						 (Jet3->correctedJet(corL_).pt() + Jet5->correctedJet(corL_).pt()) );
      hists_.find("pt4-pt5_norm")->second->Fill( (Jet4->correctedJet(corL_).pt() - Jet5->correctedJet(corL_).pt()) /
						 (Jet4->correctedJet(corL_).pt() + Jet5->correctedJet(corL_).pt()) );
    }
    if(idx == 5){
      Jet6 = jet;
      hists2D_.find("pt1pt6")->second->Fill( Jet1->correctedJet(corL_).pt(), Jet6->correctedJet(corL_).pt(), weight );
      hists2D_.find("pt2pt6")->second->Fill( Jet2->correctedJet(corL_).pt(), Jet6->correctedJet(corL_).pt(), weight );
      hists2D_.find("pt3pt6")->second->Fill( Jet3->correctedJet(corL_).pt(), Jet6->correctedJet(corL_).pt(), weight );
      hists2D_.find("pt4pt6")->second->Fill( Jet4->correctedJet(corL_).pt(), Jet6->correctedJet(corL_).pt(), weight );
      hists2D_.find("pt5pt6")->second->Fill( Jet5->correctedJet(corL_).pt(), Jet6->correctedJet(corL_).pt(), weight );
      hists_.find("pt1-pt6")->second->Fill( Jet1->correctedJet(corL_).pt() - Jet6->correctedJet(corL_).pt() );
      hists_.find("pt2-pt6")->second->Fill( Jet2->correctedJet(corL_).pt() - Jet6->correctedJet(corL_).pt() );
      hists_.find("pt3-pt6")->second->Fill( Jet3->correctedJet(corL_).pt() - Jet6->correctedJet(corL_).pt() );
      hists_.find("pt4-pt6")->second->Fill( Jet4->correctedJet(corL_).pt() - Jet6->correctedJet(corL_).pt() );
      hists_.find("pt5-pt6")->second->Fill( Jet5->correctedJet(corL_).pt() - Jet6->correctedJet(corL_).pt() );
      hists_.find("pt1-pt6_norm")->second->Fill( (Jet1->correctedJet(corL_).pt() - Jet6->correctedJet(corL_).pt()) / 
						 (Jet1->correctedJet(corL_).pt() + Jet6->correctedJet(corL_).pt()) );
      hists_.find("pt2-pt6_norm")->second->Fill( (Jet2->correctedJet(corL_).pt() - Jet6->correctedJet(corL_).pt()) / 
						 (Jet2->correctedJet(corL_).pt() + Jet6->correctedJet(corL_).pt()) );
      hists_.find("pt3-pt6_norm")->second->Fill( (Jet3->correctedJet(corL_).pt() - Jet6->correctedJet(corL_).pt()) / 
						 (Jet3->correctedJet(corL_).pt() + Jet6->correctedJet(corL_).pt()) );
      hists_.find("pt4-pt6_norm")->second->Fill( (Jet4->correctedJet(corL_).pt() - Jet6->correctedJet(corL_).pt()) /
						 (Jet4->correctedJet(corL_).pt() + Jet6->correctedJet(corL_).pt()) );
      hists_.find("pt5-pt6_norm")->second->Fill( (Jet5->correctedJet(corL_).pt() - Jet6->correctedJet(corL_).pt()) /
						 (Jet5->correctedJet(corL_).pt() + Jet6->correctedJet(corL_).pt()) );
      hists_.find("sqrt_s")->second->Fill( (Jet1->p4()+Jet2->p4()+Jet3->p4()+Jet4->p4()+Jet5->p4()+Jet6->p4()).mass() );
      hists_.find("et56")->second->Fill( sqrt(Jet5->et()*Jet6->et()) );
    }


    hists_.find("etaeta")->second->Fill( jet->etaetaMoment() , weight );
    hists_.find("etaphi")->second->Fill( jet->etaphiMoment() , weight );
    hists_.find("phiphi")->second->Fill( jet->phiphiMoment() , weight );

    hists2D_.find("etaetaphiphi")->second->Fill( jet->etaetaMoment() , jet->phiphiMoment() , weight );
    hists2D_.find("etaetaetaphi")->second->Fill( jet->etaetaMoment() , jet->etaphiMoment() , weight );
    hists2D_.find("etaphiphiphi")->second->Fill( jet->etaphiMoment() , jet->phiphiMoment() , weight );

    if(jet->genParticle() != 0) {
      if(jet->genParticle()->pdgId() == 5 || jet->genParticle()->pdgId() == -5){
	hists_.find("etaeta_b")->second->Fill( jet->etaetaMoment() , weight );
	hists_.find("etaphi_b")->second->Fill( jet->etaphiMoment() , weight );
	hists_.find("phiphi_b")->second->Fill( jet->phiphiMoment() , weight );
	
	hists2D_.find("etaetaphiphi_b")->second->Fill( jet->etaetaMoment() , jet->phiphiMoment() , weight );
	hists2D_.find("etaetaetaphi_b")->second->Fill( jet->etaetaMoment() , jet->etaphiMoment() , weight );
	hists2D_.find("etaphiphiphi_b")->second->Fill( jet->etaphiMoment() , jet->phiphiMoment() , weight );
      }
      if(jet->genParticle()->pdgId() < 5 || jet->genParticle()->pdgId() > -5){
	hists_.find("etaeta_q")->second->Fill( jet->etaetaMoment() , weight );
	hists_.find("etaphi_q")->second->Fill( jet->etaphiMoment() , weight );
	hists_.find("phiphi_q")->second->Fill( jet->phiphiMoment() , weight );
	
	hists2D_.find("etaetaphiphi_q")->second->Fill( jet->etaetaMoment() , jet->phiphiMoment() , weight );
	hists2D_.find("etaetaetaphi_q")->second->Fill( jet->etaetaMoment() , jet->etaphiMoment() , weight );
	hists2D_.find("etaphiphiphi_q")->second->Fill( jet->etaphiMoment() , jet->phiphiMoment() , weight );
      }
      if(jet->genParticle()->pdgId() == 9  || jet->genParticle()->pdgId() == -9 ||
	 jet->genParticle()->pdgId() == 21 || jet->genParticle()->pdgId() == -21){
	hists_.find("etaeta_g")->second->Fill( jet->etaetaMoment() , weight );
	hists_.find("etaphi_g")->second->Fill( jet->etaphiMoment() , weight );
	hists_.find("phiphi_g")->second->Fill( jet->phiphiMoment() , weight );
	
	hists2D_.find("etaetaphiphi_g")->second->Fill( jet->etaetaMoment() , jet->phiphiMoment() , weight );
	hists2D_.find("etaetaetaphi_g")->second->Fill( jet->etaetaMoment() , jet->etaphiMoment() , weight );
	hists2D_.find("etaphiphiphi_g")->second->Fill( jet->etaphiMoment() , jet->phiphiMoment() , weight );
      }
    }

    if(jet->bDiscriminator("trackCountingHighPurBJetTags") > 3.){
      if(jet->genParticle() != 0) {
	++bJetCounter;
	if(bJetCounter == 1) bJet1 = jet;
	if(bJetCounter == 2) {
	  hists2D_.find("ptb1ptb2")->second->Fill( bJet1->correctedJet(corB_).pt(), jet->correctedJet(corB_).pt(), weight );
	  hists_.find("ptb1-ptb2")->second->Fill( bJet1->correctedJet(corB_).pt() - jet->correctedJet(corB_).pt() );
	  hists_.find("ptb1-ptb2_norm")->second->Fill( (bJet1->correctedJet(corB_).pt() - jet->correctedJet(corB_).pt()) /
						       (bJet1->correctedJet(corB_).pt() + jet->correctedJet(corB_).pt()) );
	}
	if(jet->genParticle()->pdgId() == 5 || jet->genParticle()->pdgId() == -5){
	  hists_.find("realB")->second->Fill(  0.5 , weight );
	}
	else{
	  hists_.find("realB")->second->Fill( -0.5 , weight );	
	}
      }
    }

    if(jet->bDiscriminator("combinedSecondaryVertexBJetTags") > 0.9){
      if(jet->genParticle() != 0) {
	if(jet->genParticle()->pdgId() == 5 || jet->genParticle()->pdgId() == -5){
	  hists_.find("realBCSV")->second->Fill(  0.5 , weight );
	}
	else{
	  hists_.find("realBCSV")->second->Fill( -0.5 , weight );	
	}
      }
    }

    if(jet->bDiscriminator("softMuonBJetTags") > 0.3){
      if(jet->genParticle() != 0) {
	if(jet->genParticle()->pdgId() == 5 || jet->genParticle()->pdgId() == -5){
	  hists_.find("realBSM")->second->Fill(  0.5 , weight );
	}
	else{
	  hists_.find("realBSM")->second->Fill( -0.5 , weight );	
	}
      }
    }
  }

  hists_.find("ht")->second->Fill( ht_ , weight );
  hists_.find("ht3jet")->second->Fill( ht3jet_ , weight );
  hists_.find("centrality")->second->Fill( ht_/h_ , weight );

/**
   calculate di-jet and tri-jet masses
**/

  if(jets.size()>1){
    for(edm::View<pat::Jet>::const_iterator jet1 = jets.begin(); jet1 != --jets.end(); ++jet1) {
      edm::View<pat::Jet>::const_iterator jet1_value = jet1;
      for(edm::View<pat::Jet>::const_iterator jet2 = ++jet1_value; jet2 != jets.end(); ++jet2) {
	edm::View<pat::Jet>::const_iterator jet2_value = jet2;
	hists_.find("mjj")->second->Fill( (jet1->p4() + jet2->p4()).mass(), weight );
	
	if(jets.size()>2 && !(jet2_value == jets.end())){
	  for(edm::View<pat::Jet>::const_iterator jet3 = ++jet2_value; jet3 != jets.end(); ++jet3) {
	    
	    hists_.find("mjjj")->second->Fill( (jet1->p4() + jet2->p4() + jet3->p4()).mass(), weight );
	  }
	}
      }
    }
  }
}

/// return the desired correction step from the configuration string, which is expected to be of type 'step' or 'step:flavor'
const std::string FullHadSpecial::correctionStep() const
{
  std::string step;
  if(correctionLevel_.find(":")!=std::string::npos){
    step=correctionLevel_.substr(0,correctionLevel_.find(":"));
  }
  else{
    step=correctionLevel_;
  }
  return step;
}

/// return the desired correction flavor from the configuration string, which is expected to be of type 'step' or 'step:flavor'
const std::string FullHadSpecial::correctionFlavor() const
{
  std::string flavor;
  if(correctionLevel_.find(":")!=std::string::npos){
    flavor=correctionLevel_.substr(1+correctionLevel_.find(":"));
  }
  return flavor;
}
