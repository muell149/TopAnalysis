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
  /// Ht, sum of Et of all jets
  hists_["ht"      ] = new TH1F( "ht"       , "ht"       ,  1000 ,  0. ,  5000. );
  /// real B-Quarks, -1 fake, 1 real
  hists_["realB"   ] = new TH1F( "realB"    , "realB"    ,     2 , -1. ,     1. );
  /// real B-Quarks, -1 fake, 1 real
  hists_["realBCSV"] = new TH1F( "realBCSV" , "realBCSV" ,     2 , -1. ,     1. );
  /// real B-Quarks, -1 fake, 1 real
  hists_["realBSM" ] = new TH1F( "realBSM"  , "realBSM"  ,     2 , -1. ,     1. );
  /// di-jet mass
  hists_["mjj"     ] = new TH1F( "mjj"      , "mjj"      ,  1000 ,  0. ,  5000. );
  /// tri-jet mass
  hists_["mjjj"    ] = new TH1F( "mjjj"     , "mjjj"     ,  1000 ,  0. ,  5000. );
  /// uncorrected jet pt
  hists_["jetPtUn" ] = new TH1F( "jetPtUn"  , "jetPtUn"  ,    50 ,  0. ,   500. );
  /// passing HLT_QuadJet30
  hists_["hltQuadPass"] = new TH1F( "hltQuadPass" , "hltQuadPass" , 2 , -1. , 1.);
  /// pt of b1 vs. pt of b2
  hists2D_["ptb1ptb2" ] = new TH2F( "ptb1ptb2" , "ptb1ptb2" ,   130 , 20. ,   150. , 130 , 20. , 150. );
  /// pt of 1 vs. pt of 2
  hists2D_["pt1pt2"   ] = new TH2F( "pt1pt2"   , "pt1pt2"   ,   130 , 20. ,   150. , 130 , 20. , 150. );
  /// pt of 1 vs. pt of 3
  hists2D_["pt1pt3"   ] = new TH2F( "pt1pt3"   , "pt1pt3"   ,   130 , 20. ,   150. , 130 , 20. , 150. );
  /// pt of 1 vs. pt of 4
  hists2D_["pt1pt4"   ] = new TH2F( "pt1pt4"   , "pt1pt4"   ,   130 , 20. ,   150. , 130 , 20. , 150. );
  /// pt of 1 vs. pt of 5
  hists2D_["pt1pt5"   ] = new TH2F( "pt1pt5"   , "pt1pt5"   ,   130 , 20. ,   150. , 130 , 20. , 150. );
  /// pt of 1 vs. pt of 6
  hists2D_["pt1pt6"   ] = new TH2F( "pt1pt6"   , "pt1pt6"   ,   130 , 20. ,   150. , 130 , 20. , 150. );
  /// pt of 2 vs. pt of 3
  hists2D_["pt2pt3"   ] = new TH2F( "pt2pt3"   , "pt2pt3"   ,   130 , 20. ,   150. , 130 , 20. , 150. );
  /// pt of 2 vs. pt of 4
  hists2D_["pt2pt4"   ] = new TH2F( "pt2pt4"   , "pt2pt4"   ,   130 , 20. ,   150. , 130 , 20. , 150. );
  /// pt of 2 vs. pt of 5
  hists2D_["pt2pt5"   ] = new TH2F( "pt2pt5"   , "pt2pt5"   ,   130 , 20. ,   150. , 130 , 20. , 150. );
  /// pt of 2 vs. pt of 6
  hists2D_["pt2pt6"   ] = new TH2F( "pt2pt6"   , "pt2pt6"   ,   130 , 20. ,   150. , 130 , 20. , 150. );
  /// pt of 3 vs. pt of 4
  hists2D_["pt3pt4"   ] = new TH2F( "pt3pt4"   , "pt3pt4"   ,   130 , 20. ,   150. , 130 , 20. , 150. );
  /// pt of 3 vs. pt of 5
  hists2D_["pt3pt5"   ] = new TH2F( "pt3pt5"   , "pt3pt5"   ,   130 , 20. ,   150. , 130 , 20. , 150. );
  /// pt of 3 vs. pt of 6
  hists2D_["pt3pt6"   ] = new TH2F( "pt3pt6"   , "pt3pt6"   ,   130 , 20. ,   150. , 130 , 20. , 150. );
  /// pt of 4 vs. pt of 5
  hists2D_["pt4pt5"   ] = new TH2F( "pt4pt5"   , "pt4pt5"   ,   130 , 20. ,   150. , 130 , 20. , 150. );
  /// pt of 4 vs. pt of 6
  hists2D_["pt4pt6"   ] = new TH2F( "pt4pt6"   , "pt4pt6"   ,   130 , 20. ,   150. , 130 , 20. , 150. );
  /// pt of 5 vs. pt of 6
  hists2D_["pt5pt6"   ] = new TH2F( "pt5pt6"   , "pt5pt6"   ,   130 , 20. ,   150. , 130 , 20. , 150. );
  /// thrust
  //hists_["thrust"  ] = new TH1F( "thrust"   , "thrust"   ,   100 ,  0. ,     1. );
  /// (thrust - real) vs Ht
  //hists_["thrustHt"] = new TH1F( "thrustHt" , "thrustHt" ,   100 ,  0. ,     1. );
  /// eta-eta-moment
  //hists_["etaeta"  ] = new TH1F( "etaeta"   , "etaeta"   ,   100 ,  0. ,     1. );
  /// eta-phi-moment
  //hists_["etaphi"  ] = new TH1F( "etaphi"   , "etaphi"   ,   100 ,  0. ,     1. );
  /// phi-phi-moment
  //hists_["phiphi"  ] = new TH1F( "phiphi"   , "phiphi"   ,   100 ,  0. ,     1. );
}

/// histogramm booking for full fw
void
FullHadSpecial::book(edm::Service<TFileService>& fs)
{
  /// Ht, sum of Et of all jets
  hists_["ht"      ] = fs->make<TH1F>( "ht"       , "ht"       ,  1000 ,  0. ,  5000. );
  /// real B-Quarks, -1 fake, 1 real
  hists_["realB"   ] = fs->make<TH1F>( "realB"    , "realB"    ,     2 , -1. ,     1. );
  /// real B-Quarks, -1 fake, 1 real
  hists_["realBCSV"] = fs->make<TH1F>( "realBCSV" , "realBCSV" ,     2 , -1. ,     1. );
  /// real B-Quarks, -1 fake, 1 real
  hists_["realBSM" ] = fs->make<TH1F>( "realBSM"  , "realBSM"  ,     2 , -1. ,     1. );
  /// di-jet mass
  hists_["mjj"     ] = fs->make<TH1F>( "mjj"      , "mjj"      ,  1000 ,  0. ,  5000. );
  /// tri-jet mass
  hists_["mjjj"    ] = fs->make<TH1F>( "mjjj"     , "mjjj"     ,  1000 ,  0. ,  5000. );
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
  /// thrust
  //hists_["thrust"  ] = fs->make<TH1F>( "thrust"   , "thrust"   ,   100 ,  0. ,     1. );
  /// (thrust - real) vs Ht
  //hists_["thrustHt"] = fs->make<TH1F>( "thrustHt" , "thrustHt" ,   100 ,  0. ,     1. );
  /// eta-eta-moment
  //hists_["etaeta"  ] = fs->make<TH1F>( "etaeta"   , "etaeta"   ,   100 ,  0. ,     1. );
  /// eta-phi-moment
  //hists_["etaphi"  ] = fs->make<TH1F>( "etaphi"   , "etaphi"   ,   100 ,  0. ,     1. );
  /// phi-phi-moment
  //hists_["phiphi"  ] = fs->make<TH1F>( "phiphi"   , "phiphi"   ,   100 ,  0. ,     1. );
}

/// histogram filling for fwlite and for full fw
void
FullHadSpecial::fill(const edm::View<pat::Jet>& jets, const double& weight)
{
/**
   Calculate variables and fill histograms
**/

  double ht_ = 0;
  int hltQuadJetCounter = 0;
  int bJetCounter = 0;
  pat::Jet bJet1;
  pat::Jet Jet1;
  pat::Jet Jet2;
  pat::Jet Jet3;
  pat::Jet Jet4;
  pat::Jet Jet5;
  pat::Jet Jet6;
  std::string corL_ = "abs";
  std::string corB_ = "abs";

  for(unsigned int idx=0; idx<jets.size(); ++idx){

    ht_ += jets[idx].et();

    hists_.find("jetPtUn")->second->Fill( jets[idx].correctedJet("raw").pt() , weight );

    if(jets[idx].correctedJet("abs").pt() > 30 && hltQuadJetCounter < 4){

      ++hltQuadJetCounter;
      
      if(hltQuadJetCounter == 4){
	hists_.find("hltQuadPass")->second->Fill(  0.5 , weight );
      }
      if(hltQuadJetCounter < 4 && idx == jets.size()-1){
	hists_.find("hltQuadPass")->second->Fill( -0.5 , weight );
      }
    }

    if(idx == 0) Jet1 = jets[idx];
    if(idx == 1){
      Jet2 = jets[idx];
      hists2D_.find("pt1pt2")->second->Fill( Jet1.correctedJet(corL_).pt(), Jet2.correctedJet(corL_).pt(), weight );
    }
    if(idx == 2){
      Jet3 = jets[idx];
      hists2D_.find("pt1pt3")->second->Fill( Jet1.correctedJet(corL_).pt(), Jet3.correctedJet(corL_).pt(), weight );
      hists2D_.find("pt2pt3")->second->Fill( Jet2.correctedJet(corL_).pt(), Jet3.correctedJet(corL_).pt(), weight );
    }
    if(idx == 3){
      Jet4 = jets[idx];
      hists2D_.find("pt1pt4")->second->Fill( Jet1.correctedJet(corL_).pt(), Jet4.correctedJet(corL_).pt(), weight );
      hists2D_.find("pt2pt4")->second->Fill( Jet2.correctedJet(corL_).pt(), Jet4.correctedJet(corL_).pt(), weight );
      hists2D_.find("pt3pt4")->second->Fill( Jet3.correctedJet(corL_).pt(), Jet4.correctedJet(corL_).pt(), weight );
    }
    if(idx == 4){
      Jet5 = jets[idx];
      hists2D_.find("pt1pt5")->second->Fill( Jet1.correctedJet(corL_).pt(), Jet5.correctedJet(corL_).pt(), weight );
      hists2D_.find("pt2pt5")->second->Fill( Jet2.correctedJet(corL_).pt(), Jet5.correctedJet(corL_).pt(), weight );
      hists2D_.find("pt3pt5")->second->Fill( Jet3.correctedJet(corL_).pt(), Jet5.correctedJet(corL_).pt(), weight );
      hists2D_.find("pt4pt5")->second->Fill( Jet4.correctedJet(corL_).pt(), Jet5.correctedJet(corL_).pt(), weight );
    }
    if(idx == 5){
      Jet6 = jets[idx];
      hists2D_.find("pt1pt6")->second->Fill( Jet1.correctedJet(corL_).pt(), Jet6.correctedJet(corL_).pt(), weight );
      hists2D_.find("pt2pt6")->second->Fill( Jet2.correctedJet(corL_).pt(), Jet6.correctedJet(corL_).pt(), weight );
      hists2D_.find("pt3pt6")->second->Fill( Jet3.correctedJet(corL_).pt(), Jet6.correctedJet(corL_).pt(), weight );
      hists2D_.find("pt4pt6")->second->Fill( Jet4.correctedJet(corL_).pt(), Jet6.correctedJet(corL_).pt(), weight );
      hists2D_.find("pt5pt6")->second->Fill( Jet5.correctedJet(corL_).pt(), Jet6.correctedJet(corL_).pt(), weight );
    }

/*
    hists_.find("etaeta")->second->Fill( jets[idx].etaetaMoment() , weight );
    hists_.find("etaphi")->second->Fill( jets[idx].etaphiMoment() , weight );
    hists_.find("phiphi")->second->Fill( jets[idx].phiphiMoment() , weight );
*/
    if(jets[idx].bDiscriminator("trackCountingHighPurBJetTags") > 3.){
      if(jets[idx].genParticle() != 0) {
	++bJetCounter;
	if(bJetCounter == 1) bJet1 = jets[idx];
	if(bJetCounter == 2) hists2D_.find("ptb1ptb2")->second->Fill( bJet1.correctedJet(corB_).pt(), jets[idx].correctedJet(corB_).pt(), weight );
	//std::cout << "PDG-ID of b-jet (HighPur): " << jets[idx].genParticle()->pdgId() << std::endl;
	if(jets[idx].genParticle()->pdgId() == 5 || jets[idx].genParticle()->pdgId() == -5){
	  hists_.find("realB")->second->Fill(  0.5 , weight );
	}
	else{
	  hists_.find("realB")->second->Fill( -0.5 , weight );	
	}
      }
    }

    if(jets[idx].bDiscriminator("combinedSecondaryVertexBJetTags") > 0.9){
      if(jets[idx].genParticle() != 0) {
	//std::cout << "PDG-ID of b-jet (SecVert): " << jets[idx].genParticle()->pdgId() << std::endl;
	if(jets[idx].genParticle()->pdgId() == 5 || jets[idx].genParticle()->pdgId() == -5){
	  hists_.find("realBCSV")->second->Fill(  0.5 , weight );
	}
	else{
	  hists_.find("realBCSV")->second->Fill( -0.5 , weight );	
	}
      }
    }

    if(jets[idx].bDiscriminator("softMuonBJetTags") > 0.3){
      if(jets[idx].genParticle() != 0) {
	//std::cout << "PDG-ID of b-jet (SoftMu ): " << jets[idx].genParticle()->pdgId() << std::endl;
	if(jets[idx].genParticle()->pdgId() == 5 || jets[idx].genParticle()->pdgId() == -5){
	  hists_.find("realBSM")->second->Fill(  0.5 , weight );
	}
	else{
	  hists_.find("realBSM")->second->Fill( -0.5 , weight );	
	}
      }
    }
  }

  hists_.find("ht")->second->Fill( ht_ , weight );

/**
   calculate di-jet and tri-jet masses
**/

  if(jets.size()>1){
    for(unsigned int idx=0; idx<jets.size()-1; ++idx) {
      for(unsigned int jdx=idx+1; jdx<jets.size(); ++jdx) {
	
	hists_.find("mjj")->second->Fill( (jets[idx].p4() + jets[jdx].p4()).mass(), weight );
	
	if(jets.size()>2 && (jets.size() - jdx)>1 ){
	  for(unsigned int kdx=jdx+1; kdx<jets.size(); ++kdx) {
	    
	    hists_.find("mjjj")->second->Fill( (jets[idx].p4() + jets[jdx].p4() + jets[kdx].p4()).mass(), weight );
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

// /// histogram filling for fwlite and for full fw
// void
// FullHadSpecial::fill(const edm::View<reco::Candidate>& jets, const double& weight)
// {
// }
