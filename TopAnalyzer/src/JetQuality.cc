#include "TopAnalysis/TopAnalyzer/interface/JetQuality.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "DataFormats/Math/interface/deltaR.h"

/// default constructor for fw lite
JetQuality::JetQuality(const int index, std::string flavor) : index_(index), flavor_(flavor)
{ 
}

/// constructor for full FW analyzer
JetQuality::JetQuality(const edm::ParameterSet& cfg) :
  useTree_ ( cfg.getParameter<bool>( "useTree" ) ),
  index_ ( cfg.getParameter<int>( "index" ) ),
  flavor_( cfg.getParameter<std::string>( "flavor" ) )
{
}

/// histogramm booking for fwlite 
void 
JetQuality::book()
{
  /** 
      Calo and PF JetID Variables
  **/
  // number of jet constituents
  hists_["n_"] = new TH1F( "n_" , "n_"  , 50, 0., 50. );

  /** 
      Other Calo and PF Jet Variables
  **/
  // number of jet constituents carrying 90% of the jet energy
  hists_["n90_"] = new TH1F( "n90_" , "n90_" , 50, 0., 50. );
  // number of jet constituents carrying 60% of the jet energy
  hists_["n60_"] = new TH1F( "n60_" , "n60_" , 50, 0., 50. );
  // charge of the jet
  hists_["charge"] = new TH1F( "charge" , "charge" , 220, -1.1, 1.1 );
  // eta-eta moment of the jet
  hists_["etaeta"] = new TH1F( "etaeta" , "etaeta" , 120, 0., 0.12 );
  // eta-phi moment of the jet
  hists_["etaphi"] = new TH1F( "etaphi" , "etaphi" , 100, -0.05, 0.05 );
  // phi-phi moment of the jet
  hists_["phiphi"] = new TH1F( "phiphi" , "phiphi" , 120, 0., 0.12 );

  /** 
      Calo JetID Variables
  **/
  // electromagnetic fraction of jet energy
  hists_["emf"     ] = new TH1F( "emf"      , "emf"      ,  44, 0.,   1.1 );
  // number of rec hits carrying 90% of the jet energy
  hists_["n90Hits_"] = new TH1F( "n90Hits_" , "n90Hits_" , 100, 0., 100.  );
  // fraction of jet energy comming from the leading hybrid photo diode within the jet
  hists_["fHPD_"   ] = new TH1F( "fHPD_"    , "fHPD_"    ,  50, 0.,   1.  );

  /** 
      PF JetID Variables
  **/
  // fraction of energy carried by neutral hadrons
  hists_["nhf"] = new TH1F( "nhf" , "nhf" , 40, 0.,  1. );
  // fraction of energy carried by neutral em (photons)
  hists_["nef"] = new TH1F( "nef" , "nef" , 40, 0.,  1. );
  // fraction of energy carried by charged hadrons
  hists_["chf"] = new TH1F( "chf" , "chf" , 40, 0.,  1. );
  // fraction of energy carried by charged em (electrons)
  hists_["cef"] = new TH1F( "cef" , "cef" , 40, 0.,  1. );
  // multiplicity of charged hadrons
  hists_["nch"] = new TH1F( "nch" , "nch" , 50, 0., 50. );
  // multiplicity of charged particles
  hists_["ncp"] = new TH1F( "ncp" , "ncp" , 50, 0., 50. );

  /** 
      B Tags for Jets
  **/
  // btag track counting high purity
  hists_["btagTrkCntHighPurity"    ] = new TH1F( "btagTrkCntHighPurity"     ,  "btagTrkCntHighPurity"     ,   80,     0.,   20. );
  // btag track counting high efficiency
  hists_["btagTrkCntHighEff_"      ] = new TH1F( "btagTrkCntHighEff_"       ,  "btagTrkCntHighEff_"       ,   80,     0.,   20. ); 
  // btag simple secondary vertex high efficiency
  hists_["btagSimpleSecVtxHighEff_"] = new TH1F( "btagSimpleSecVtxHighEff_" ,  "btagSimpleSecVtxHighEff_" ,   80,    -5.,   15. ); 
  // btag simple secondary vertex high purity
  hists_["btagSimpleSecVtxHighPur_"] = new TH1F( "btagSimpleSecVtxHighPur_" ,  "btagSimpleSecVtxHighPur_" ,   80,    -5.,   15. ); 
  // btag simple secondary vertex (neg bjet tags)
  hists_["btagSimpleSecVtxNeg_"    ] = new TH1F( "btagSimpleSecVtxNeg_"     ,  "btagSimpleSecVtxNeg_"     ,   80, -1005., -985. ); 
  // btag combined secondary vertex
  hists_["btagCombSecVtx_"         ] = new TH1F( "btagCombSecVtx_"          , "btagCombSecVtx_"           ,   80,    -2.,    2. );
  // btag combined secondary vertex using MVA
  hists_["btagCombSecVtxMVA_"      ] = new TH1F( "btagCombSecVtxMVA_"       , "btagCombSecVtxMVA_"        ,   80,    -2.,    2. );
  // btag b jet b probability (newer algo than the following)
  hists_["btagJetBProbability_"    ] = new TH1F( "btagJetBProbability_"     , "btagJetBProbability_"      ,   80,     0.,   11. );
  // btag b jet probability
  hists_["btagJetProbability_"     ] = new TH1F( "btagJetProbability_"      , "btagJetProbability_"       ,   80,     0.,    4. );
  // btag soft electron taggers (not implemented for PFJets)
  hists_["btagSoftElecByPt_"       ] = new TH1F( "btagSoftElecByPt_"        , "btagSoftElecByPt_"         ,   80,     0.,   20. );
  hists_["btagSoftElecByIP3d_"     ] = new TH1F( "btagSoftElecByIP3d_"      , "btagSoftElecByIP3d_"       ,   80,   -40.,  110. );
  // btag soft muon taggers
  hists_["btagSoftMuon_"           ] = new TH1F( "btagSoftMuon_"            , "btagSoftMuon_"             ,   50,     0.,    1. );
  hists_["btagSoftMuonByPt_"       ] = new TH1F( "btagSoftMuonByPt_"        , "btagSoftMuonByPt_"         ,  100,     0.,   10. );
  hists_["btagSoftMuonByIP3d_"     ] = new TH1F( "btagSoftMuonByIP3d_"      , "btagSoftMuonByIP3d_"       ,  160,  -100.,  100. );

  /**
     E-Flow in Jets
  **/
  // jets energy flow in R
  hists_["eFlowR_"  ] = new TH2F( "eFlowR_"  , "eFlowR_"  ,  30 , -0.6 , 0.6 , 150, 0., 300. );
  // jets energy flow in eta
  hists_["eFlowEta_"] = new TH2F( "eFlowEta_", "eFlowEta_",  30 , -0.6 , 0.6 , 150, 0., 300. );
  // jets energy flow in phi
  hists_["eFlowPhi_"] = new TH2F( "eFlowPhi_", "eFlowPhi_",  30 , -0.6 , 0.6 , 150, 0., 300. );

  /** 
      JEC Monitoring Variables
  **/
  // jet pt raw
  hists_["ptL0_"  ] = new TH2F( "ptL0_"  , "ptL0_"  ,  30 ,     0. ,   150. , 150, 0., 3. );
  // jet pt L2Relative
  hists_["ptL2_"  ] = new TH2F( "ptL2_"  , "ptL2_"  ,  30 ,     0. ,   150. , 150, 0., 3. );
  // jet pt L3Absolute
  hists_["ptL3_"  ] = new TH2F( "ptL3_"  , "ptL3_"  ,  30 ,     0. ,   150. , 150, 0., 3. );
  // jet pt L2L3Residual
  hists_["ptL2L3_"] = new TH2F( "ptL2L3_", "ptL2L3_",  30 ,     0. ,   150. , 150, 0., 3. );
  // jet pt L5Hadron
  hists_["ptL5_"  ] = new TH2F( "ptL5_"  , "ptL5_"  ,  30 ,     0. ,   150. , 150, 0., 3. );
  // jet pt L7Parton
  hists_["ptL7_"  ] = new TH2F( "ptL7_"  , "ptL7_"  ,  30 ,     0. ,   150. , 150, 0., 3. );

  // jet eta raw
  hists_["etaL0_"  ] = new TH2F( "etaL0_"  , "etaL0_"  ,  70 ,   -3.5 ,    3.5 , 150, 0., 3. );
  // jet eta L2Relative
  hists_["etaL2_"  ] = new TH2F( "etaL2_"  , "etaL2_"  ,  70 ,   -3.5 ,    3.5 , 150, 0., 3. );
  // jet eta L3Absolute
  hists_["etaL3_"  ] = new TH2F( "etaL3_"  , "etaL3_"  ,  70 ,   -3.5 ,    3.5 , 150, 0., 3. );
  // jet eta L2L3Residual
  hists_["etaL2L3_"] = new TH2F( "etaL2L3_", "etaL2L3_",  70 ,   -3.5 ,    3.5 , 150, 0., 3. );
  // jet eta L5Hadron
  hists_["etaL5_"  ] = new TH2F( "etaL5_"  , "etaL5_"  ,  70 ,   -3.5 ,    3.5 , 150, 0., 3. );
  // jet eta L7Parton
  hists_["etaL7_"  ] = new TH2F( "etaL7_"  , "etaL7_"  ,  70 ,   -3.5 ,    3.5 , 150, 0., 3. );
}

/// histogramm booking for full fw
void 
JetQuality::book(edm::Service<TFileService>& fs)
{
  /** 
      Calo and PF JetID Variables
  **/
  // number of jet constituents
  bookVariable( fs, "n_"  , 50, 0., 50. , false );

  /** 
      Other Calo and PF Jet Variables
  **/
  // number of jet constituents carrying 90% of the jet energy
  bookVariable( fs, "n90_" , 50, 0., 50. , false );
  // number of jet constituents carrying 60% of the jet energy
  bookVariable( fs, "n60_" , 50, 0., 50. , false );
  // charge of the jet
  bookVariable( fs, "charge" , 220, -1.1, 1.1 , false );
  // eta-eta moment of the jet
  bookVariable( fs, "etaeta" , 120, 0., 0.12 , false );
  // eta-phi moment of the jet
  bookVariable( fs, "etaphi" , 100, -0.05, 0.05 , false );
  // phi-phi moment of the jet
  bookVariable( fs, "phiphi" , 120, 0., 0.12 , false );

  /** 
      Calo JetID Variables
  **/
  // electromagnetic fraction of jet energy
  bookVariable( fs, "emf"      ,  44, 0.,   1.1 , false );
  // number of rec hits carrying 90% of the jet energy
  bookVariable( fs, "n90Hits_" , 100, 0., 100.  , false );
  // fraction of jet energy comming from the leading hybrid photo diode within the jet
  bookVariable( fs, "fHPD_"    ,  50, 0.,   1.  , false );

  /** 
      PF JetID Variables
  **/
  // fraction of energy carried by neutral hadrons
  bookVariable( fs, "nhf" , 40, 0.,  1. , false );
  // fraction of energy carried by neutral em (photons)
  bookVariable( fs, "nef" , 40, 0.,  1. , false );
  // fraction of energy carried by charged hadrons
  bookVariable( fs, "chf" , 40, 0.,  1. , false );
  // fraction of energy carried by charged em (electrons)
  bookVariable( fs, "cef" , 40, 0.,  1. , false );
  // multiplicity of charged hadrons
  bookVariable( fs, "nch" , 50, 0., 50. , false );
  // multiplicity of charged particles
  bookVariable( fs, "ncp" , 50, 0., 50. , false );

  /** 
      B Tags for Jets
  **/
  // btag track counting high purity
  bookVariable( fs, "btagTrkCntHighPurity"     ,   80,     0.,   20. , false );
  // btag track counting high efficiency
  bookVariable( fs, "btagTrkCntHighEff_"       ,   80,     0.,   20. , false ); 
  // btag simple secondary vertex high efficiency
  bookVariable( fs, "btagSimpleSecVtxHighEff_" ,   80,    -5.,   15. , false ); 
  // btag simple secondary vertex high purity
  bookVariable( fs, "btagSimpleSecVtxHighPur_" ,   80,    -5.,   15. , false ); 
  // btag simple secondary vertex (neg bjet tags)
  bookVariable( fs, "btagSimpleSecVtxNeg_"     ,   80, -1005., -985. , false ); 
  // btag combined secondary vertex
  bookVariable( fs, "btagCombSecVtx_"          ,   88,    -1.1,   1.1 , false );
  // btag combined secondary vertex using MVA
  bookVariable( fs, "btagCombSecVtxMVA_"       ,   88,    -1.1,   1.1 , false );
  // btag b jet b probability (newer algo than the following)
  bookVariable( fs, "btagJetBProbability_"     ,   80,     0.,   11. , false );
  // btag b jet probability
  bookVariable( fs, "btagJetProbability_"      ,   80,     0.,    4. , false );
  // btag soft electron taggers (not implemented for PFJets)
  bookVariable( fs, "btagSoftElecByPt_"        ,   80,     0.,   20. , false );
  bookVariable( fs, "btagSoftElecByIP3d_"      ,   80,   -40.,  110. , false );
  // btag soft muon taggers
  bookVariable( fs, "btagSoftMuon_"            ,   50,     0.,    1. , false );
  bookVariable( fs, "btagSoftMuonByPt_"        ,  100,     0.,   10. , false );
  bookVariable( fs, "btagSoftMuonByIP3d_"      ,  160,  -100.,  100. , false );

  /**
     E-Flow in Jets
  **/

  // jets energy flow in R
  bookVariable( fs, "eFlowR_"   ,  30 ,  0.  , 0.6 , 100, 0., 1000. );
  // jets energy flow in eta
  bookVariable( fs, "eFlowEta_" ,  30 , -0.6 , 0.6 , 100, 0., 1000. );
  // jets energy flow in phi
  bookVariable( fs, "eFlowPhi_" ,  30 , -0.6 , 0.6 , 100, 0., 1000. );

  /** 
      JEC Monitoring Variables
  **/
  // jet pt raw
  bookVariable( fs, "ptL0_"  ,  30 ,     0. ,   150. , 150, 0., 3. );
  // jet pt L2Relative
  bookVariable( fs, "ptL2_"  ,  30 ,     0. ,   150. , 150, 0., 3. );
  // jet pt L3Absolute
  bookVariable( fs, "ptL3_"  ,  30 ,     0. ,   150. , 150, 0., 3. );
  // jet pt L5Hadron
  bookVariable( fs, "ptL5_"  ,  30 ,     0. ,   150. , 150, 0., 3. );
  // jet pt L7Parton
  bookVariable( fs, "ptL7_"  ,  30 ,     0. ,   150. , 150, 0., 3. );

  // jet eta raw
  bookVariable( fs, "etaL0_" ,  70 ,   -3.5 ,    3.5 , 150, 0., 3. );
  // jet eta L2Relative
  bookVariable( fs, "etaL2_" ,  70 ,   -3.5 ,    3.5 , 150, 0., 3. );
  // jet eta L3Absolute
  bookVariable( fs, "etaL3_" ,  70 ,   -3.5 ,    3.5 , 150, 0., 3. );
  // jet eta L5Hadron
  bookVariable( fs, "etaL5_" ,  70 ,   -3.5 ,    3.5 , 150, 0., 3. );
  // jet eta L7Parton
  bookVariable( fs, "etaL7_" ,  70 ,   -3.5 ,    3.5 , 150, 0., 3. );
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
	  Fill Calo and PF JetID Variables
      **/

      // number of jet constituents
      unsigned int n100 = 0;
      if     ( jet->isCaloJet() ) n100 = jet->getCaloConstituents().size();
      else if( jet->isPFJet()   ) n100 = jet->chargedMultiplicity()+jet->neutralMultiplicity();
      fillValue( "n_"   , n100 , weight );

      /** 
	  Fill Other Calo and PF Jet Variables
      **/

      // charge of the jet
      fillValue( "charge" , jet->jetCharge()    , weight );
      if(jet->nConstituents() > 0){
      	//if( jet->daughterPtr(0).productGetter()->getIt(jet->daughterPtr(0).id()) != 0 ){
	  // number of jet constituents carrying 90% of the jet energy
	  fillValue( "n90_" , jet->n90() , weight );
	  // number of jet constituents carrying 60% of the jet energy
	  fillValue( "n60_" , jet->n60() , weight );
      
	  // eta-eta moment of the jet
      	  fillValue( "etaeta" , jet->etaetaMoment() , weight );
      	  // eta-phi moment of the jet
      	  fillValue( "etaphi" , jet->etaphiMoment() , weight );
      	  // phi-phi moment of the jet
      	  fillValue( "phiphi" , jet->phiphiMoment() , weight );
	  //}
      }
      
      /** 
	  Fill Calo JetID Variables
      **/
      if( jet->isCaloJet() ){
	// electromagnetic fraction of jet energy
	fillValue( "emf"      , jet->emEnergyFraction() , weight );
	// number of rec hits carrying 90% of the jet energy
	fillValue( "n90Hits_" , jet->jetID().n90Hits    , weight );
	// fraction of jet energy comming from the leading hybrid photo diode within the jet
	fillValue( "fHPD_"    , jet->jetID().fHPD       , weight );
      }
      
      /** 
	  PF JetID Variables
      **/
      if( jet->isPFJet() ){
	// fraction of energy carried by neutral hadrons
	fillValue( "nhf" , jet->neutralHadronEnergyFraction()           , weight );
	// fraction of energy carried by neutral em (photons)
	fillValue( "nef" , jet->neutralEmEnergyFraction()               , weight );
	// fraction of energy carried by charged hadrons
	fillValue( "chf" , jet->chargedHadronEnergyFraction()           , weight );
	// fraction of energy carried by charged em (electrons)
	fillValue( "cef" , jet->chargedEmEnergyFraction()               , weight );
	// multiplicity of charged hadrons
	fillValue( "nch" , jet->pfSpecific().mChargedHadronMultiplicity , weight );
	// multiplicity of charged particles
	fillValue( "ncp" , jet->chargedMultiplicity()                   , weight );
      }

      /** 
	  Fill B Tags for Jets
      **/
      // btag track counting high purity
      fillValue( "btagTrkCntHighPurity"     , jet->bDiscriminator("trackCountingHighPurBJetTags")         , weight );
      // btag track counting high efficiency
      fillValue( "btagTrkCntHighEff_"       , jet->bDiscriminator("trackCountingHighEffBJetTags")         , weight );
      // btag simple secondary vertex high efficiency
      fillValue( "btagSimpleSecVtxHighEff_" , jet->bDiscriminator("simpleSecondaryVertexHighEffBJetTags") , weight );
      // btag simple secondary vertex high purity
      fillValue( "btagSimpleSecVtxHighPur_" , jet->bDiscriminator("simpleSecondaryVertexHighPurBJetTags") , weight );
      // btag simple secondary vertex (neg bjet tags) makes no sense yet, value is -1000 for every jet regardless of the btagging
      fillValue( "btagSimpleSecVtxNeg_"     , jet->bDiscriminator("simpleSecondaryVertexNegativeBJetTags") , weight );
      // btag combined secondary vertex
      fillValue( "btagCombSecVtx_"          , jet->bDiscriminator("combinedSecondaryVertexBJetTags")       , weight );
      // btag combined secondary vertex using MVA
      fillValue( "btagCombSecVtxMVA_"       , jet->bDiscriminator("combinedSecondaryVertexMVABJetTags")    , weight );
      // btag b jet b probability (newer algo than the following)
      fillValue( "btagJetBProbability_"     , jet->bDiscriminator("jetBProbabilityBJetTags")               , weight );
      // btag b jet probability
      fillValue( "btagJetProbability_"      , jet->bDiscriminator("jetProbabilityBJetTags")                , weight );
      // btag soft electron taggers (not implemented for PFJets)
      fillValue( "btagSoftElecByPt_"        , jet->bDiscriminator("softElectronByPtBJetTags")              , weight );
      fillValue( "btagSoftElecByIP3d_"      , jet->bDiscriminator("softElectronByIP3dBJetTags")            , weight );
      // btag soft muon taggers
      fillValue( "btagSoftMuon_"            , jet->bDiscriminator("softMuonBJetTags")                      , weight );
      fillValue( "btagSoftMuonByPt_"        , jet->bDiscriminator("softMuonByPtBJetTags")                  , weight );
      fillValue( "btagSoftMuonByIP3d_"      , jet->bDiscriminator("softMuonByIP3dBJetTags")                , weight );

      /**
	 E-Flow in Jets
      **/

//       std::vector<const reco::Candidate*> constituents = jet->getJetConstituentsQuick();
//       for(std::vector<const reco::Candidate*>::const_iterator con = constituents.begin(); con != constituents.end(); ++con){
// 	// jets energy flow in R
// 	fillValue("eFlowR_"  , deltaR((*con)->eta(), (*con)->phi(), jet->eta(), jet->phi()) , jet->pt() , (*con)->energy()/jet->correctedJet("Uncorrected").energy() );
// 	// jets energy flow in eta
// 	fillValue("eFlowEta_", (*con)->eta() - jet->eta()                                   , jet->pt() , (*con)->energy()/jet->correctedJet("Uncorrected").energy() );
// 	// jets energy flow in phi
// 	fillValue("eFlowPhi_", deltaPhi((*con)->phi(), jet->phi())                          , jet->pt() , (*con)->energy()/jet->correctedJet("Uncorrected").energy() );
//       }

      /** 
	  Fill JEC Monitoring Variables
      **/

      if( jet->genJet() ){

	std::vector< std::string > jecs = jet->availableJECLevels();

	for(std::vector< std::string >::const_iterator jec = jecs.begin(); jec != jecs.end(); ++jec){
	  if(*jec == "Uncorrected"){
	    // jet pt raw
	    fillValue( "ptL0_"  , jet->genJet()->pt(),  jet->correctedJet("Uncorrected").pt()/jet->genJet()->pt() , weight );
	    // jet eta raw
	    fillValue( "etaL0_" , jet->genJet()->eta(), jet->correctedJet("Uncorrected").pt()/jet->genJet()->pt() , weight );
	  }
	  if(*jec == "L2Relative"){
	    // jet pt L2Relative
	    fillValue( "ptL2_"  , jet->genJet()->pt(),  jet->correctedJet("L2Relative").pt()/jet->genJet()->pt() , weight );
	    // jet eta L2Relative
	    fillValue( "etaL2_" , jet->genJet()->eta(), jet->correctedJet("L2Relative").pt()/jet->genJet()->pt() , weight );
	  }
	  if(*jec == "L3Absolute"){
	    // jet pt L3Absolute
	    fillValue( "ptL3_"  , jet->genJet()->pt(),  jet->correctedJet("L3Absolute").pt()/jet->genJet()->pt() , weight );
	    // jet eta L3Absolute
	    fillValue( "etaL3_" , jet->genJet()->eta(), jet->correctedJet("L3Absolute").pt()/jet->genJet()->pt() , weight );
	  }
	  if(*jec == "L2L3Residual"){
	    // jet pt L3Absolute
	    fillValue( "ptL2L3_"  , jet->genJet()->pt(),  jet->correctedJet("L2L3Residual").pt()/jet->genJet()->pt() , weight );
	    // jet eta L3Absolute
	    fillValue( "etaL2L3_" , jet->genJet()->eta(), jet->correctedJet("L2L3Residual").pt()/jet->genJet()->pt() , weight );
	  }
	  if(*jec == "L5Flavor"){
	    // jet pt L5Hadron
	    fillValue( "ptL5_"  , jet->genJet()->pt(),  jet->correctedJet("L5Flavor", flavor_).pt()/jet->genJet()->pt() , weight );
	    // jet eta L5Hadron
	    fillValue( "etaL5_" , jet->genJet()->eta(), jet->correctedJet("L5Flavor", flavor_).pt()/jet->genJet()->pt() , weight );
	  }
	  if(*jec == "L7Parton"){
	    // jet pt L7Parton
	    fillValue( "ptL7_"  , jet->genJet()->pt(),  jet->correctedJet("L7Parton", flavor_).pt()/jet->genJet()->pt() , weight );
	    // jet eta L7Parton
	    fillValue( "etaL7_" , jet->genJet()->eta(), jet->correctedJet("L7Parton", flavor_).pt()/jet->genJet()->pt() , weight );
	  }
	}
      }
    }
  }

  // fill the tree, if any variable should be put in
  if(treeVars_.size()) tree->Fill();

}
