#include "TopAnalysis/TopAnalyzer/interface/JetQuality.h"

/// default constructor for fw lite
JetQuality::JetQuality(const int index, std::string flavor) : index_(index), flavor_(flavor)
{ 
}

/// constructor for full FW analyzer
JetQuality::JetQuality(const edm::ParameterSet& cfg) :
  index_ ( cfg.getParameter<int>( "index" ) ),
  flavor_( cfg.getParameter<std::string>( "flavor" ) )
{
}

/// histogramm booking for fwlite 
void 
JetQuality::book()
{
  /** 
      Selection Variables
  **/
  // electromagnetic fraction of jet energy
  hists_["emf"                  ] = new TH1F( "emf"                  ,  "emf"                  ,   40,   0.,    1. );
  // btag track counting high purity
  hists_["btagTrkCntHighPurity" ] = new TH1F( "btagTrkCntHighPurity" ,  "btagTrkCntHighPurity" ,   80,   0.,   20. );

  /** 
      Monitoring Variables
  **/
  // number of jet constituents
  hists_["n_"                   ] = new TH1F( "n_"                     ,  "n_"                   ,   50,   0.,  50. );
  // number of jet constituents carrying 90% of the jet energy
  hists_["n90_"                 ] = new TH1F( "n90_"                   ,  "n90_"                 ,   50,   0.,   1. );
  // number of jet constituents carrying 60% of the jet energy
  hists_["n60_"                 ] = new TH1F( "n60_"                   ,  "n60_"                 ,   50,   0.,   1. );
  // number of rec hits carrying 90% of the jet energy
  hists_["n90Hits_"             ] = new TH1F( "n90Hits_"               ,  "n90Hits_"             ,   50,   0.,  50. );
  // fraction of jet energy comming from the leading hybrid photo diode within the jet
  hists_["fHPD_"                ] = new TH1F( "fHPD_"                  ,  "fHPD_"                ,   50,   0.,   1. );
  // btag track counting high efficiency
  hists_["btagTrkCntHighEff_"   ] = new TH1F( "btagTrkCntHighEff_"     ,  "btagTrkCntHighEff_"   ,   80,   0.,  20. ); 
  // btag simple secondary vertex
  hists_["btagSimpleSecVtx_"    ] = new TH1F( "btagSimpleSecVtx_"      ,  "btagSimpleSecVtx_"    ,   80,  -5.,  15. ); 
  // btag simple secondary vertex (neg bjet tags)
  hists_["btagSimpleSecVtxNeg_" ] = new TH1F( "btagSimpleSecVtxNeg_"   ,  "btagSimpleSecVtxNeg_" ,   80, -20.,   0. ); 

  /** 
      JEC Monitoring Variables
  **/
  // jet pt raw
  hists_["ptL0_" ] = new TH2F( "ptL0_"  , "ptL0_"  ,  30 ,     0. ,   150. , 150, 0., 3. );
  // jet pt L2Relative
  hists_["ptL2_" ] = new TH2F( "ptL2_"  , "ptL2_"  ,  30 ,     0. ,   150. , 150, 0., 3. );
  // jet pt L3Absolute
  hists_["ptL3_" ] = new TH2F( "ptL3_"  , "ptL3_"  ,  30 ,     0. ,   150. , 150, 0., 3. );
  // jet pt L5Hadron
  hists_["ptL5_" ] = new TH2F( "ptL5_"  , "ptL5_"  ,  30 ,     0. ,   150. , 150, 0., 3. );
  // jet pt L7Parton
  hists_["ptL7_" ] = new TH2F( "ptL7_"  , "ptL7_"  ,  30 ,     0. ,   150. , 150, 0., 3. );

  // jet eta raw
  hists_["etaL0_"] = new TH2F( "etaL0_" , "etaL0_" ,  70 ,   -3.5 ,    3.5 , 150, 0., 3. );
  // jet eta L2Relative
  hists_["etaL2_"] = new TH2F( "etaL2_" , "etaL2_" ,  70 ,   -3.5 ,    3.5 , 150, 0., 3. );
  // jet eta L3Absolute
  hists_["etaL3_"] = new TH2F( "etaL3_" , "etaL3_" ,  70 ,   -3.5 ,    3.5 , 150, 0., 3. );
  // jet eta L5Hadron
  hists_["etaL5_"] = new TH2F( "etaL5_" , "etaL5_" ,  70 ,   -3.5 ,    3.5 , 150, 0., 3. );
  // jet eta L7Parton
  hists_["etaL7_"] = new TH2F( "etaL7_" , "etaL7_" ,  70 ,   -3.5 ,    3.5 , 150, 0., 3. );
}

/// histogramm booking for full fw
void 
JetQuality::book(edm::Service<TFileService>& fs)
{
  /** 
      Selection Variables
  **/
  // electromagnetic fraction of jet energy
  hists_["emf"                  ] = fs->make<TH1F>( "emf"                  ,  "emf"                  ,   40,   0.,    1. );
  // btag track counting high purity
  hists_["btagTrkCntHighPurity" ] = fs->make<TH1F>( "btagTrkCntHighPurity" ,  "btagTrkCntHighPurity" ,   80,   0.,   20. );

  /** 
      Monitoring Variables
  **/
  // number of jet constituents
  hists_["n_"                   ] = fs->make<TH1F>( "n_"                     ,  "n_"                   ,   50,   0.,  50. );
  // number of jet constituents carrying 90% of the jet energy
  hists_["n90_"                 ] = fs->make<TH1F>( "n90_"                   ,  "n90_"                 ,   50,   0.,   1. );
  // number of jet constituents carrying 60% of the jet energy
  hists_["n60_"                 ] = fs->make<TH1F>( "n60_"                   ,  "n60_"                 ,   50,   0.,   1. );
  // number of rec hits carrying 90% of the jet energy
  hists_["n90Hits_"             ] = fs->make<TH1F>( "n90Hits_"               ,  "n90Hits_"             ,   50,   0.,  50. );
  // fraction of jet energy comming from the leading hybrid photo diode within the jet
  hists_["fHPD_"                ] = fs->make<TH1F>( "fHPD_"                  ,  "fHPD_"                ,   50,   0.,   1. );
  // btag track counting high efficiency
  hists_["btagTrkCntHighEff_"   ] = fs->make<TH1F>( "btagTrkCntHighEff_"     ,  "btagTrkCntHighEff_"   ,   80,   0.,  20. ); 
  // btag simple secondary vertex
  hists_["btagSimpleSecVtx_"    ] = fs->make<TH1F>( "btagSimpleSecVtx_"      ,  "btagSimpleSecVtx_"    ,   80,  -5.,  15. ); 
  // btag simple secondary vertex (neg bjet tags)
  hists_["btagSimpleSecVtxNeg_" ] = fs->make<TH1F>( "btagSimpleSecVtxNeg_"   ,  "btagSimpleSecVtxNeg_" ,   80,-1005.,-985.); 

  /** 
      JEC Monitoring Variables
  **/
  // jet pt raw
  hists_["ptL0_" ] = fs->make<TH2F>( "ptL0_"  , "ptL0_"  ,  30 ,     0. ,   150. , 150, 0., 3. );
  // jet pt L2Relative
  hists_["ptL2_" ] = fs->make<TH2F>( "ptL2_"  , "ptL2_"  ,  30 ,     0. ,   150. , 150, 0., 3. );
  // jet pt L3Absolute
  hists_["ptL3_" ] = fs->make<TH2F>( "ptL3_"  , "ptL3_"  ,  30 ,     0. ,   150. , 150, 0., 3. );
  // jet pt L5Hadron
  hists_["ptL5_" ] = fs->make<TH2F>( "ptL5_"  , "ptL5_"  ,  30 ,     0. ,   150. , 150, 0., 3. );
  // jet pt L7Parton
  hists_["ptL7_" ] = fs->make<TH2F>( "ptL7_"  , "ptL7_"  ,  30 ,     0. ,   150. , 150, 0., 3. );

  // jet eta raw
  hists_["etaL0_"] = fs->make<TH2F>( "etaL0_" , "etaL0_" ,  70 ,   -3.5 ,    3.5 , 150, 0., 3. );
  // jet eta L2Relative
  hists_["etaL2_"] = fs->make<TH2F>( "etaL2_" , "etaL2_" ,  70 ,   -3.5 ,    3.5 , 150, 0., 3. );
  // jet eta L3Absolute
  hists_["etaL3_"] = fs->make<TH2F>( "etaL3_" , "etaL3_" ,  70 ,   -3.5 ,    3.5 , 150, 0., 3. );
  // jet eta L5Hadron
  hists_["etaL5_"] = fs->make<TH2F>( "etaL5_" , "etaL5_" ,  70 ,   -3.5 ,    3.5 , 150, 0., 3. );
  // jet eta L7Parton
  hists_["etaL7_"] = fs->make<TH2F>( "etaL7_" , "etaL7_" ,  70 ,   -3.5 ,    3.5 , 150, 0., 3. );
}

/// histogram filling for fwlite and for full fw from reco objects
void
JetQuality::fill(const edm::View<pat::Jet>& jets, const double& weight)
{
  int index=0;
  for(edm::View<pat::Jet>::const_iterator jet=jets.begin(); jet!=jets.end(); ++jet, ++index){
    // NOTE: These histograms still need to be filled apropriately
    if( index_<0 || index_==index ){
      /**
	 Fill Selection Variables
      **/
      // electromagnetic fraction of jet energy
      hists_.find( "emf"                 )->second->Fill( jet->emEnergyFraction() , weight );
      // btag track counting high purity
      hists_.find( "btagTrkCntHighPurity")->second->Fill( jet->bDiscriminator("trackCountingHighPurBJetTags") , weight );
      
      /** 
	  Fill Monitoring Variables
      **/
      // number of jet constituents
      unsigned int n100 = 0;
      if( jet->isCaloJet() ) n100 = jet->getCaloConstituents().size();	
      else if( jet->isPFJet() ) n100 = jet->getPFConstituents().size();
      hists_.find( "n_"   )->second->Fill( n100 , weight );
      // number of jet constituents carrying 90% of the jet energy
      hists_.find( "n90_" )->second->Fill( jet->n90()/n100 , weight );
      // number of jet constituents carrying 60% of the jet energy
      hists_.find( "n60_" )->second->Fill( jet->n60()/n100 , weight );
      // number of rec hits carrying 90% of the jet energy
      hists_.find( "n90Hits_" )->second->Fill( jet->jetID().n90Hits , weight );
      // fraction of jet energy comming from the leading hybrid photo diode within the jet
      hists_.find( "fHPD_" )->second->Fill( jet->jetID().fHPD , weight );
      // btag track counting high efficiency
      hists_.find( "btagTrkCntHighEff_"  )->second->Fill( jet->bDiscriminator("trackCountingHighEffBJetTags") , weight );
      // btag simple secondary vertex
      hists_.find( "btagSimpleSecVtx_"   )->second->Fill( jet->bDiscriminator("simpleSecondaryVertexBJetTags") , weight );
      // btag simple secondary vertex (neg bjet tags) makes no sense yet, value is -1000 for every jet regardless of the btagging
      hists_.find( "btagSimpleSecVtxNeg_")->second->Fill( jet->bDiscriminator("simpleSecondaryVertexNegativeBJetTags") , weight );

      /** 
	  Fill JEC Monitoring Variables
      **/
      if( jet->genJet() ){
	// jet pt raw
	hists_.find( "ptL0_"  )->second->Fill( jet->genJet()->pt(),  jet->correctedJet("raw").pt()/jet->genJet()->pt() );
	// jet pt L2Relative
	hists_.find( "ptL2_"  )->second->Fill( jet->genJet()->pt(),  jet->correctedJet("rel").pt()/jet->genJet()->pt() );
	// jet pt L3Absolute
	hists_.find( "ptL3_"  )->second->Fill( jet->genJet()->pt(),  jet->correctedJet("abs").pt()/jet->genJet()->pt() );
	// jet pt L5Hadron
	hists_.find( "ptL5_"  )->second->Fill( jet->genJet()->pt(),  jet->correctedJet("had",  flavor_).pt()/jet->genJet()->pt() );
	// jet pt L7Parton
	hists_.find( "ptL7_"  )->second->Fill( jet->genJet()->pt(),  jet->correctedJet("part", flavor_).pt()/jet->genJet()->pt() );
	
	// jet eta raw
	hists_.find( "etaL0_" )->second->Fill( jet->genJet()->eta(),  jet->correctedJet("raw").pt()/jet->genJet()->pt() );
	// jet eta L2Relative
	hists_.find( "etaL2_" )->second->Fill( jet->genJet()->eta(),  jet->correctedJet("rel").pt()/jet->genJet()->pt() );
	// jet eta L3Absolute
	hists_.find( "etaL3_" )->second->Fill( jet->genJet()->eta(),  jet->correctedJet("abs").pt()/jet->genJet()->pt() );
	// jet eta L5Hadron
	hists_.find( "etaL5_" )->second->Fill( jet->genJet()->eta(),  jet->correctedJet("had",  flavor_).pt()/jet->genJet()->pt() );
	// jet eta L7Parton
	hists_.find( "etaL7_" )->second->Fill( jet->genJet()->eta(),  jet->correctedJet("part", flavor_).pt()/jet->genJet()->pt() );
      }
    }
  }
}
