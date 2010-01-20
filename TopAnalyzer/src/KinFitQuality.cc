#include <TMath.h>
#include "TopAnalysis/TopAnalyzer/interface/KinFitQuality.h"
#include "AnalysisDataFormats/TopObjects/interface/TtFullHadEvtPartons.h"

/// default constructor for fw lite
KinFitQuality::KinFitQuality()
{
}

/// default constructor for full fw
KinFitQuality::KinFitQuality(const edm::ParameterSet& cfg)
{
}

/// histogramm booking for fwlite 
void KinFitQuality::book()
{
  /** 
      Pull Distributions (Relative to the Reco Input)
  **/

  // b pt
  hists_["bQuarkPt"     ] = new TH1F( "bQuarkPt"      , "bQuarkPt"      ,   60, -2. , 1. );
  // b eta
  hists_["bQuarkEta"    ] = new TH1F( "bQuarkEta"     , "bQuarkEta"     ,   40, -1. , 1. );
  // b phi
  hists_["bQuarkPhi"    ] = new TH1F( "bQuarkPhi"     , "bQuarkPhi"     ,   40, -1. , 1. );
  // lightQuark pt
  hists_["lightQuarkPt" ] = new TH1F( "lightQuarkPt"  , "lightQuarkPt"  ,   60, -2. , 1. );
  // lightQuark b eta
  hists_["lightQuarkEta"] = new TH1F( "lightQuarkEta" , "lightQuarkEta" ,   40, -1. , 1. );
  // lightQuark b phi
  hists_["lightQuarkPhi"] = new TH1F( "lightQuarkPhi" , "lightQuarkPhi" ,   40, -1. , 1. );
  // w pt
  hists_["wPt"          ] = new TH1F( "wPt"           , "wPt"           ,   60, -2. , 1. );
  // w eta
  hists_["wEta"         ] = new TH1F( "wEta"          , "wEta"          ,   40, -1. , 1. );
  // w phi
  hists_["wPhi"         ] = new TH1F( "wPhi"          , "wPhi"          ,   40, -1. , 1. );
  // topQuark pt
  hists_["topQuarkPt"   ] = new TH1F( "topQuarkPt"    , "topQuarkPt"    ,   60, -2. , 1. );
  // topQuark b eta
  hists_["topQuarkEta"  ] = new TH1F( "topQuarkEta"   , "topQuarkEta"   ,   40, -1. , 1. );
  // topQuark b phi
  hists_["topQuarkPhi"  ] = new TH1F( "topQuarkPhi"   , "topQuarkPhi"   ,   40, -1. , 1. );

  /**
     KinFit Properties
  **/

  // chi2 of kinfit
  hists_["chi2"] = new TH1F( "chi2" , "chi2" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob"] = new TH1F( "prob" , "prob" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_2"] = new TH1F( "chi2_2" , "chi2_2" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_2"] = new TH1F( "prob_2" , "prob_2" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_3"] = new TH1F( "chi2_3" , "chi2_3" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_3"] = new TH1F( "prob_3" , "prob_3" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_4"] = new TH1F( "chi2_4" , "chi2_4" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_4"] = new TH1F( "prob_4" , "prob_4" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_5"] = new TH1F( "chi2_5" , "chi2_5" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_5"] = new TH1F( "prob_5" , "prob_5" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_6"] = new TH1F( "chi2_6" , "chi2_6" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_6"] = new TH1F( "prob_6" , "prob_6" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_7"] = new TH1F( "chi2_7" , "chi2_7" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_7"] = new TH1F( "prob_7" , "prob_7" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_8"] = new TH1F( "chi2_8" , "chi2_8" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_8"] = new TH1F( "prob_8" , "prob_8" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_9"] = new TH1F( "chi2_9" , "chi2_9" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_9"] = new TH1F( "prob_9" , "prob_9" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_10"] = new TH1F( "chi2_10" , "chi2_10" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_10"] = new TH1F( "prob_10" , "prob_10" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_11"] = new TH1F( "chi2_11" , "chi2_11" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_11"] = new TH1F( "prob_11" , "prob_11" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_12"] = new TH1F( "chi2_12" , "chi2_12" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_12"] = new TH1F( "prob_12" , "prob_12" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_13"] = new TH1F( "chi2_13" , "chi2_13" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_13"] = new TH1F( "prob_13" , "prob_13" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_14"] = new TH1F( "chi2_14" , "chi2_14" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_14"] = new TH1F( "prob_14" , "prob_14" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_15"] = new TH1F( "chi2_15" , "chi2_15" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_15"] = new TH1F( "prob_15" , "prob_15" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_16"] = new TH1F( "chi2_16" , "chi2_16" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_16"] = new TH1F( "prob_16" , "prob_16" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_17"] = new TH1F( "chi2_17" , "chi2_17" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_17"] = new TH1F( "prob_17" , "prob_17" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_18"] = new TH1F( "chi2_18" , "chi2_18" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_18"] = new TH1F( "prob_18" , "prob_18" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_19"] = new TH1F( "chi2_19" , "chi2_19" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_19"] = new TH1F( "prob_19" , "prob_19" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_20"] = new TH1F( "chi2_20" , "chi2_20" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_20"] = new TH1F( "prob_20" , "prob_20" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_21"] = new TH1F( "chi2_21" , "chi2_21" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_21"] = new TH1F( "prob_21" , "prob_21" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_22"] = new TH1F( "chi2_22" , "chi2_22" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_22"] = new TH1F( "prob_22" , "prob_22" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_23"] = new TH1F( "chi2_23" , "chi2_23" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_23"] = new TH1F( "prob_23" , "prob_23" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_24"] = new TH1F( "chi2_24" , "chi2_24" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_24"] = new TH1F( "prob_24" , "prob_24" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_25"] = new TH1F( "chi2_25" , "chi2_25" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_25"] = new TH1F( "prob_25" , "prob_25" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_26"] = new TH1F( "chi2_26" , "chi2_26" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_26"] = new TH1F( "prob_26" , "prob_26" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_27"] = new TH1F( "chi2_27" , "chi2_27" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_27"] = new TH1F( "prob_27" , "prob_27" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_28"] = new TH1F( "chi2_28" , "chi2_28" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_28"] = new TH1F( "prob_28" , "prob_28" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_29"] = new TH1F( "chi2_29" , "chi2_29" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_29"] = new TH1F( "prob_29" , "prob_29" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_30"] = new TH1F( "chi2_30" , "chi2_30" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_30"] = new TH1F( "prob_30" , "prob_30" ,  100, 0. ,    1. );
}

/// histogramm booking for fw
void KinFitQuality::book(edm::Service<TFileService>& fs)
{
  /** 
      Pull Distributions (Relative to the Reco Input)
  **/

  // b pt
  hists_["bQuarkPt"     ] = fs->make<TH1F>( "bQuarkPt"      , "bQuarkPt"      ,   60, -2. , 1. );
  // b eta
  hists_["bQuarkEta"    ] = fs->make<TH1F>( "bQuarkEta"     , "bQuarkEta"     ,   40, -1. , 1. );
  // b phi
  hists_["bQuarkPhi"    ] = fs->make<TH1F>( "bQuarkPhi"     , "bQuarkPhi"     ,   40, -1. , 1. );
  // lightQuark pt
  hists_["lightQuarkPt" ] = fs->make<TH1F>( "lightQuarkPt"  , "lightQuarkPt"  ,   60, -2. , 1. );
  // lightQuark b eta
  hists_["lightQuarkEta"] = fs->make<TH1F>( "lightQuarkEta" , "lightQuarkEta" ,   40, -1. , 1. );
  // lightQuark b phi
  hists_["lightQuarkPhi"] = fs->make<TH1F>( "lightQuarkPhi" , "lightQuarkPhi" ,   40, -1. , 1. );
  // w pt
  hists_["wPt"          ] = fs->make<TH1F>( "wPt"           , "wPt"           ,   60, -2. , 1. );
  // w eta
  hists_["wEta"         ] = fs->make<TH1F>( "wEta"          , "wEta"          ,   40, -1. , 1. );
  // w phi
  hists_["wPhi"         ] = fs->make<TH1F>( "wPhi"          , "wPhi"          ,   40, -1. , 1. );
  // topQuark pt
  hists_["topQuarkPt"   ] = fs->make<TH1F>( "topQuarkPt"    , "topQuarkPt"    ,   60, -2. , 1. );
  // topQuark b eta
  hists_["topQuarkEta"  ] = fs->make<TH1F>( "topQuarkEta"   , "topQuarkEta"   ,   40, -1. , 1. );
  // topQuark b phi
  hists_["topQuarkPhi"  ] = fs->make<TH1F>( "topQuarkPhi"   , "topQuarkPhi"   ,   40, -1. , 1. );

  /**
     KinFit Properties
  **/

  // chi2 of kinfit
  hists_["chi2"] = fs->make<TH1F>( "chi2" , "chi2" ,  100, 0., 1000. );
  // chi2prob of kinfit
  hists_["prob"] = fs->make<TH1F>( "prob" , "prob" ,  100, 0.,    1. );
  // chi2 of kinfit
  hists_["chi2_2"] = fs->make<TH1F>( "chi2_2" , "chi2_2" ,  100, 0., 1000. );
  // chi2prob of kinfit
  hists_["prob_2"] = fs->make<TH1F>( "prob_2" , "prob_2" ,  100, 0.,    1. );
  // chi2 of kinfit
  hists_["chi2_3"] = fs->make<TH1F>( "chi2_3" , "chi2_3" ,  100, 0., 1000. );
  // chi2prob of kinfit
  hists_["prob_3"] = fs->make<TH1F>( "prob_3" , "prob_3" ,  100, 0.,    1. );
  // chi2 of kinfit
  hists_["chi2_4"] = fs->make<TH1F>( "chi2_4" , "chi2_4" ,  100, 0., 1000. );
  // chi2prob of kinfit
  hists_["prob_4"] = fs->make<TH1F>( "prob_4" , "prob_4" ,  100, 0.,    1. );
  // chi2 of kinfit
  hists_["chi2_5"] = fs->make<TH1F>( "chi2_5" , "chi2_5" ,  100, 0., 1000. );
  // chi2prob of kinfit
  hists_["prob_5"] = fs->make<TH1F>( "prob_5" , "prob_5" ,  100, 0.,    1. );
  // chi2 of kinfit
  hists_["chi2_6"] = fs->make<TH1F>( "chi2_6" , "chi2_6" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_6"] = fs->make<TH1F>( "prob_6" , "prob_6" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_7"] = fs->make<TH1F>( "chi2_7" , "chi2_7" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_7"] = fs->make<TH1F>( "prob_7" , "prob_7" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_8"] = fs->make<TH1F>( "chi2_8" , "chi2_8" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_8"] = fs->make<TH1F>( "prob_8" , "prob_8" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_9"] = fs->make<TH1F>( "chi2_9" , "chi2_9" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_9"] = fs->make<TH1F>( "prob_9" , "prob_9" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_10"] = fs->make<TH1F>( "chi2_10" , "chi2_10" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_10"] = fs->make<TH1F>( "prob_10" , "prob_10" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_11"] = fs->make<TH1F>( "chi2_11" , "chi2_11" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_11"] = fs->make<TH1F>( "prob_11" , "prob_11" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_12"] = fs->make<TH1F>( "chi2_12" , "chi2_12" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_12"] = fs->make<TH1F>( "prob_12" , "prob_12" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_13"] = fs->make<TH1F>( "chi2_13" , "chi2_13" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_13"] = fs->make<TH1F>( "prob_13" , "prob_13" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_14"] = fs->make<TH1F>( "chi2_14" , "chi2_14" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_14"] = fs->make<TH1F>( "prob_14" , "prob_14" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_15"] = fs->make<TH1F>( "chi2_15" , "chi2_15" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_15"] = fs->make<TH1F>( "prob_15" , "prob_15" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_16"] = fs->make<TH1F>( "chi2_16" , "chi2_16" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_16"] = fs->make<TH1F>( "prob_16" , "prob_16" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_17"] = fs->make<TH1F>( "chi2_17" , "chi2_17" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_17"] = fs->make<TH1F>( "prob_17" , "prob_17" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_18"] = fs->make<TH1F>( "chi2_18" , "chi2_18" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_18"] = fs->make<TH1F>( "prob_18" , "prob_18" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_19"] = fs->make<TH1F>( "chi2_19" , "chi2_19" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_19"] = fs->make<TH1F>( "prob_19" , "prob_19" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_20"] = fs->make<TH1F>( "chi2_20" , "chi2_20" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_20"] = fs->make<TH1F>( "prob_20" , "prob_20" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_21"] = fs->make<TH1F>( "chi2_21" , "chi2_21" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_21"] = fs->make<TH1F>( "prob_21" , "prob_21" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_22"] = fs->make<TH1F>( "chi2_22" , "chi2_22" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_22"] = fs->make<TH1F>( "prob_22" , "prob_22" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_23"] = fs->make<TH1F>( "chi2_23" , "chi2_23" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_23"] = fs->make<TH1F>( "prob_23" , "prob_23" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_24"] = fs->make<TH1F>( "chi2_24" , "chi2_24" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_24"] = fs->make<TH1F>( "prob_24" , "prob_24" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_25"] = fs->make<TH1F>( "chi2_25" , "chi2_25" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_25"] = fs->make<TH1F>( "prob_25" , "prob_25" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_26"] = fs->make<TH1F>( "chi2_26" , "chi2_26" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_26"] = fs->make<TH1F>( "prob_26" , "prob_26" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_27"] = fs->make<TH1F>( "chi2_27" , "chi2_27" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_27"] = fs->make<TH1F>( "prob_27" , "prob_27" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_28"] = fs->make<TH1F>( "chi2_28" , "chi2_28" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_28"] = fs->make<TH1F>( "prob_28" , "prob_28" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_29"] = fs->make<TH1F>( "chi2_29" , "chi2_29" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_29"] = fs->make<TH1F>( "prob_29" , "prob_29" ,  100, 0. ,    1. );
  // chi2 of kinfit
  hists_["chi2_30"] = fs->make<TH1F>( "chi2_30" , "chi2_30" ,  100, 0. , 1000. );
  // chi2prob of kinfit
  hists_["prob_30"] = fs->make<TH1F>( "prob_30" , "prob_30" ,  100, 0. ,    1. );
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
    // make sure the b-jet index is in the range of the jet collection
    if( b >=0 && b < (int)jets.size() ){
      // b pt
      hists_.find("bQuarkPt" )->second->Fill( (jets[b].pt() -tops.b("kKinFit")->pt()) /jets[b].pt()  );
      // b eta
      hists_.find("bQuarkEta")->second->Fill( (jets[b].eta()-tops.b("kKinFit")->eta())/jets[b].eta() );
      // b phi
      hists_.find("bQuarkPhi")->second->Fill( (jets[b].phi()-tops.b("kKinFit")->phi())/jets[b].phi() );
/*
      if( fabs(jets[b].phi() - tops.b("kKinFit")->phi()) < TMath::Pi() ){
	hists_.find("bQuarkPhi" )->second->Fill( fabs(jets[b].phi() - tops.b("kKinFit")->phi()) );
	}
      else{
	hists_.find("bQuarkPhi" )->second->Fill( fabs(jets[b].phi() - tops.b("kKinFit")->phi()) - TMath::TwoPi() );
      }
*/
    }
   // make sure the bBar-jet index is in the range of the jet collection
    if( bBar >= 0 && bBar< (int)jets.size() ){
      // bBar pt
      hists_.find("bQuarkPt" )->second->Fill( (jets[bBar].pt() -tops.bBar("kKinFit")->pt()) /jets[bBar].pt()  );
      // bBar eta
      hists_.find("bQuarkEta")->second->Fill( (jets[bBar].eta()-tops.bBar("kKinFit")->eta())/jets[bBar].eta() );
      // bBar phi
      hists_.find("bQuarkPhi")->second->Fill( (jets[bBar].phi()-tops.bBar("kKinFit")->phi())/jets[bBar].phi() );
/*
      if( fabs(jets[bBar].phi() - tops.bBar("kKinFit")->phi()) < TMath::Pi() ){
	hists_.find("bQuarkPhi" )->second->Fill( fabs(jets[bBar].phi() - tops.bBar("kKinFit")->phi()) );
	}
      else{
	hists_.find("bQuarkPhi" )->second->Fill( fabs(jets[bBar].phi() - tops.bBar("kKinFit")->phi()) - TMath::TwoPi() );
      }
*/
    }
   // make sure the light quark index is in the range of the jet collection
    if( lightQ >= 0 && lightQ < (int)jets.size() ){
      // lightQuark pt
      hists_.find("lightQuarkPt"  )->second->Fill( (jets[lightQ].pt() -tops.lightQ("kKinFit")->pt()) /jets[lightQ].pt()  );
      // lightQuark eta
      hists_.find("lightQuarkEta" )->second->Fill( (jets[lightQ].eta()-tops.lightQ("kKinFit")->eta())/jets[lightQ].eta() );
      // lightQuark phi
      hists_.find("lightQuarkPhi" )->second->Fill( (jets[lightQ].phi()-tops.lightQ("kKinFit")->phi())/jets[lightQ].phi() );
/*
      if(fabs(jets[lightQ].p4().phi() - tops.lightQ("kKinFit")->phi()) < TMath::Pi() ){
	hists_.find("lightQuarkPhi" )->second->Fill( fabs(jets[lightQ].phi() - tops.lightQ("kKinFit")->phi()) );
	}
      else{
	hists_.find("lightQuarkPhi" )->second->Fill( fabs(jets[lightQ].phi() - tops.lightQ("kKinFit")->phi()) - TMath::TwoPi() );
      }
*/
    }
    // make sure the light quark bar index is in the range of the jet collection
    if( lightQBar >= 0 && lightQBar< (int)jets.size() ){
      // lightQuark pt
      hists_.find("lightQuarkPt"  )->second->Fill( (jets[lightQBar].pt() -tops.lightQBar("kKinFit")->pt()) /jets[lightQBar].pt()  );
      // lightQuark eta
      hists_.find("lightQuarkEta" )->second->Fill( (jets[lightQBar].eta()-tops.lightQBar("kKinFit")->eta())/jets[lightQBar].eta() );
      // lightQuark phi
      hists_.find("lightQuarkPhi" )->second->Fill( (jets[lightQBar].phi()-tops.lightQBar("kKinFit")->phi())/jets[lightQBar].phi() );
/*
      if(fabs(jets[lightQBar].p4().phi() - tops.lightQBar("kKinFit")->phi()) < TMath::Pi() ){
	hists_.find("lightQuarkPhi" )->second->Fill( fabs(jets[lightQBar].phi() - tops.lightQBar("kKinFit")->phi()) );
	}
      else{
	hists_.find("lightQuarkPhi" )->second->Fill( fabs(jets[lightQBar].phi() - tops.lightQBar("kKinFit")->phi()) - TMath::TwoPi() );
      }
*/
    }
    // make sure the light quark index is in the range of the jet collection
    if( lightP >= 0 && lightP < (int)jets.size() ){
      // lightQuark pt
      hists_.find("lightQuarkPt"  )->second->Fill( (jets[lightP].pt() -tops.lightP("kKinFit")->pt()) /jets[lightP].pt()  );
      // lightQuark eta
      hists_.find("lightQuarkEta" )->second->Fill( (jets[lightP].eta()-tops.lightP("kKinFit")->eta())/jets[lightP].eta() );
      // lightQuark phi
      hists_.find("lightQuarkPhi" )->second->Fill( (jets[lightP].phi()-tops.lightP("kKinFit")->phi())/jets[lightP].phi() );
/*
      if(fabs(jets[lightP].p4().phi() - tops.lightP("kKinFit")->phi()) < TMath::Pi() ){
	hists_.find("lightQuarkPhi" )->second->Fill( fabs(jets[lightP].phi() - tops.lightP("kKinFit")->phi()) );
	}
      else{
	hists_.find("lightQuarkPhi" )->second->Fill( fabs(jets[lightP].phi() - tops.lightP("kKinFit")->phi()) - TMath::TwoPi() );
      }
*/
    }
    // make sure the light quark bar index is in the range of the jet collection
    if( lightPBar >= 0 && lightPBar < (int)jets.size() ){
      // lightQuark pt
      hists_.find("lightQuarkPt"  )->second->Fill( (jets[lightPBar].pt() -tops.lightPBar("kKinFit")->pt()) /jets[lightPBar].pt()  );
      // lightQuark eta
      hists_.find("lightQuarkEta" )->second->Fill( (jets[lightPBar].eta()-tops.lightPBar("kKinFit")->eta())/jets[lightPBar].eta() );
      // lightQuark phi
      hists_.find("lightQuarkPhi" )->second->Fill( (jets[lightPBar].phi()-tops.lightPBar("kKinFit")->phi())/jets[lightPBar].phi() );
/*
      if(fabs(jets[lightPBar].p4().phi() - tops.lightPBar("kKinFit")->phi()) < TMath::Pi() ){
	hists_.find("lightQuarkPhi" )->second->Fill( fabs(jets[lightPBar].phi() - tops.lightPBar("kKinFit")->phi()) );
	}
      else{
	hists_.find("lightQuarkPhi" )->second->Fill( fabs(jets[lightPBar].phi() - tops.lightPBar("kKinFit")->phi()) - TMath::TwoPi() );
      }
*/
    }
    // make sure the light quarks of w+ indices are in the range of the jet collection
    if( lightQ >= 0 && lightQ < (int)jets.size() && lightQBar >= 0 && lightQBar < (int)jets.size() ){
      // w+ pt
      hists_.find("wPt"  )->second->Fill( ((jets[lightQ].p4()+jets[lightQBar].p4()).pt() - 
					   (tops.lightQ("kKinFit")->p4()+tops.lightQBar("kKinFit")->p4()).pt()) /
					   (jets[lightQ].p4()+jets[lightQBar].p4()).pt() );
      // w+ eta
      hists_.find("wEta" )->second->Fill( ((jets[lightQ].p4()+jets[lightQBar].p4()).eta() - 
					   (tops.lightQ("kKinFit")->p4()+tops.lightQBar("kKinFit")->p4()).eta())/
					  (jets[lightQ].p4()+jets[lightQBar].p4()).eta() );
      // w+ phi
      hists_.find("wPhi" )->second->Fill( ((jets[lightQ].p4()+jets[lightQBar].p4()).phi() - 
					   (tops.lightQ("kKinFit")->p4()+tops.lightQBar("kKinFit")->p4()).phi())/
					  (jets[lightQ].p4()+jets[lightQBar].p4()).phi() );
/*
      if(fabs((jets[lightQ].p4()+jets[lightQBar].p4()).phi() - (tops.lightQ("kKinFit")->p4()+tops.lightQBar("kKinFit")->p4()).phi())<TMath::Pi())
	{
	  hists_.find("wPhi" )->second->Fill( fabs((jets[lightQ].p4()+jets[lightQBar].p4()).phi() - 
						   (tops.lightQ("kKinFit")->p4()+tops.lightQBar("kKinFit")->p4()).phi()));
	}
      else{
	  hists_.find("wPhi" )->second->Fill( fabs((jets[lightQ].p4()+jets[lightQBar].p4()).phi() - 
						   (tops.lightQ("kKinFit")->p4()+tops.lightQBar("kKinFit")->p4()).phi()) - TMath::TwoPi());
      }
*/
    }
    // make sure the light quarks of w- indices are in the range of the jet collection
    if( lightP >= 0 && lightP < (int)jets.size() && lightPBar >= 0 && lightPBar < (int)jets.size() ){
      // w+ pt
      hists_.find("wPt" )->second->Fill( ((jets[lightP].p4()+jets[lightPBar].p4()).pt() - 
					  (tops.lightP("kKinFit")->p4()+tops.lightPBar("kKinFit")->p4()).pt()) /
					 (jets[lightP].p4()+jets[lightPBar].p4()).pt());
      // w+ eta
      hists_.find("wEta")->second->Fill( ((jets[lightP].p4()+jets[lightPBar].p4()).eta() - 
					  (tops.lightP("kKinFit")->p4()+tops.lightPBar("kKinFit")->p4()).eta())/
					 (jets[lightP].p4()+jets[lightPBar].p4()).eta());
      // w+ phi
      hists_.find("wPhi" )->second->Fill( ((jets[lightP].p4()+jets[lightPBar].p4()).phi() - 
					   (tops.lightP("kKinFit")->p4()+tops.lightPBar("kKinFit")->p4()).phi())/
					  (jets[lightP].p4()+jets[lightPBar].p4()).phi() );
/*
      if(fabs((jets[lightP].p4()+jets[lightPBar].p4()).phi() - (tops.lightP("kKinFit")->p4()+tops.lightPBar("kKinFit")->p4()).phi())<TMath::Pi())
	{
	  hists_.find("wPhi")->second->Fill( fabs((jets[lightP].p4()+jets[lightPBar].p4()).phi() - 
						  (tops.lightP("kKinFit")->p4()+tops.lightPBar("kKinFit")->p4()).phi()));
	}
      else{
	  hists_.find("wPhi")->second->Fill( fabs((jets[lightP].p4()+jets[lightPBar].p4()).phi() - 
						  (tops.lightP("kKinFit")->p4()+tops.lightPBar("kKinFit")->p4()).phi()) - TMath::TwoPi());
      }
*/
    }
    // make sure the quarks of top quark indices are in the range of the jet collection
    if( lightQ >= 0 && lightQ < (int)jets.size() && lightQBar >= 0 && lightQBar < (int)jets.size() && b >=0 && b < (int)jets.size()  ){
      // top pt
      hists_.find("topQuarkPt" )->second->Fill( ((jets[lightQ].p4()+jets[lightQBar].p4()+jets[b].p4()).pt() - 
						 (tops.lightQ("kKinFit")->p4()    +
						  tops.lightQBar("kKinFit")->p4() +
						  tops.b("kKinFit")->p4()).pt())  /
						(jets[lightQ].p4()+jets[lightQBar].p4()+jets[b].p4()).pt());
      // top eta
      hists_.find("topQuarkEta")->second->Fill( ((jets[lightQ].p4()+jets[lightQBar].p4()+jets[b].p4()).eta() - 
						 (tops.lightQ("kKinFit")->p4()    +
						  tops.lightQBar("kKinFit")->p4() +
						  tops.b("kKinFit")->p4()).eta()) /
						(jets[lightQ].p4()+jets[lightQBar].p4()+jets[b].p4()).eta());
      // top phi
      hists_.find("topQuarkPhi")->second->Fill( ((jets[lightQ].p4()+jets[lightQBar].p4()+jets[b].p4()).phi() - 
						 (tops.lightQ("kKinFit")->p4()    +
						  tops.lightQBar("kKinFit")->p4() +
						  tops.b("kKinFit")->p4()).phi()) /
						(jets[lightQ].p4()+jets[lightQBar].p4()+jets[b].p4()).phi());
/*
      if( fabs((jets[lightQ].p4()+jets[lightQBar].p4()+jets[b].p4()).phi() - 
	       (tops.lightQ("kKinFit")->p4()+tops.lightQBar("kKinFit")->p4()+tops.b("kKinFit")->p4()).phi()) < TMath::Pi() ){
	hists_.find("topQuarkPhi")->second->Fill( fabs((jets[lightQ].p4()+jets[lightQBar].p4()+jets[b].p4()).phi() - 
						 (tops.lightQ("kKinFit")->p4() +
						  tops.lightQBar("kKinFit")->p4() +
						  tops.b("kKinFit")->p4()).phi()));
	}
      else{
	hists_.find("topQuarkPhi")->second->Fill( fabs((jets[lightQ].p4()+jets[lightQBar].p4()+jets[b].p4()).phi() - 
						 (tops.lightQ("kKinFit")->p4() +
						  tops.lightQBar("kKinFit")->p4() +
						  tops.b("kKinFit")->p4()).phi()) - TMath::TwoPi());
      }
*/
    }
    // make sure the quarks of topBar quark indices are in the range of the jet collection
    if( lightP >= 0 && lightP < (int)jets.size() && lightPBar >= 0 && lightPBar < (int)jets.size() && bBar >=0 && bBar < (int)jets.size()  ){
      // top pt
      hists_.find("topQuarkPt" )->second->Fill( ((jets[lightP].p4()+jets[lightPBar].p4()+jets[bBar].p4()).pt() - 
						 (tops.lightP("kKinFit")->p4()      +
						  tops.lightPBar("kKinFit")->p4()   +
						  tops.bBar("kKinFit")->p4()).pt()) /
						(jets[lightP].p4()+jets[lightPBar].p4()+jets[bBar].p4()).pt() );
      // top eta
      hists_.find("topQuarkEta")->second->Fill( ((jets[lightP].p4()+jets[lightPBar].p4()+jets[bBar].p4()).eta() - 
						 (tops.lightP("kKinFit")->p4()       +
						  tops.lightPBar("kKinFit")->p4()    +
						  tops.bBar("kKinFit")->p4()).eta()) /
						(jets[lightP].p4()+jets[lightPBar].p4()+jets[bBar].p4()).eta());
      // top phi
      hists_.find("topQuarkPhi")->second->Fill( ((jets[lightP].p4()+jets[lightPBar].p4()+jets[bBar].p4()).phi() - 
						 (tops.lightP("kKinFit")->p4()       +
						  tops.lightPBar("kKinFit")->p4()    +
						  tops.bBar("kKinFit")->p4()).phi()) /
						(jets[lightP].p4()+jets[lightPBar].p4()+jets[bBar].p4()).phi());
/*
      if( fabs((jets[lightP].p4()+jets[lightPBar].p4()+jets[bBar].p4()).phi() - 
	       (tops.lightP("kKinFit")->p4()+tops.lightPBar("kKinFit")->p4()+tops.bBar("kKinFit")->p4()).phi()) < TMath::Pi() ){
	hists_.find("topQuarkPhi")->second->Fill( fabs((jets[lightP].p4()+jets[lightPBar].p4()+jets[bBar].p4()).phi() - 
						       (tops.lightP("kKinFit")->p4() +
							tops.lightPBar("kKinFit")->p4() +
							tops.bBar("kKinFit")->p4()).phi()) );
	}
      else{
	hists_.find("topQuarkPhi")->second->Fill( fabs((jets[lightP].p4()+jets[lightPBar].p4()+jets[bBar].p4()).phi() - 
						       (tops.lightP("kKinFit")->p4() +
							tops.lightPBar("kKinFit")->p4() +
							tops.bBar("kKinFit")->p4()).phi()) - TMath::TwoPi() );
      }
*/
    }


    // chi2 of kinfit
    hists_.find("chi2")->second->Fill( tops.fitChi2() );
    // chi2prob of kinfit
    hists_.find("prob")->second->Fill( tops.fitProb() );

    if(tops.numberOfAvailableHypos("kKinFit")>1){

      // chi2 of kinfit
      hists_.find("chi2_2")->second->Fill( tops.fitChi2(1) );
      // chi2prob of kinfit
      hists_.find("prob_2")->second->Fill( tops.fitProb(1) );
      
      if(tops.numberOfAvailableHypos("kKinFit")>2){

	// chi2 of kinfit
	hists_.find("chi2_3")->second->Fill( tops.fitChi2(2) );
	// chi2prob of kinfit
	hists_.find("prob_3")->second->Fill( tops.fitProb(2) );

	if(tops.numberOfAvailableHypos("kKinFit")>3){

	  // chi2 of kinfit
	  hists_.find("chi2_4")->second->Fill( tops.fitChi2(3) );
	  // chi2prob of kinfit
	  hists_.find("prob_4")->second->Fill( tops.fitProb(3) );

	  if(tops.numberOfAvailableHypos("kKinFit")>4){

	    // chi2 of kinfit
	    hists_.find("chi2_5")->second->Fill( tops.fitChi2(4) );
	    // chi2prob of kinfit
	    hists_.find("prob_5")->second->Fill( tops.fitProb(4) );
	    
	    if(tops.numberOfAvailableHypos("kKinFit")>5){
	      
	      // chi2 of kinfit
	      hists_.find("chi2_6")->second->Fill( tops.fitChi2(5) );
	      // chi2prob of kinfit
	      hists_.find("prob_6")->second->Fill( tops.fitProb(5) );
	      
	      if(tops.numberOfAvailableHypos("kKinFit")>6){
		
		// chi2 of kinfit
		hists_.find("chi2_7")->second->Fill( tops.fitChi2(6) );
		// chi2prob of kinfit
		hists_.find("prob_7")->second->Fill( tops.fitProb(6) );
		
		if(tops.numberOfAvailableHypos("kKinFit")>7){
		  
		  // chi2 of kinfit
		  hists_.find("chi2_8")->second->Fill( tops.fitChi2(7) );
		  // chi2prob of kinfit
		  hists_.find("prob_8")->second->Fill( tops.fitProb(7) );
		  
		  if(tops.numberOfAvailableHypos("kKinFit")>8){
		    
		    // chi2 of kinfit
		    hists_.find("chi2_9")->second->Fill( tops.fitChi2(8) );
		    // chi2prob of kinfit
		    hists_.find("prob_9")->second->Fill( tops.fitProb(8) );
		    
		    if(tops.numberOfAvailableHypos("kKinFit")>9){
		
		      // chi2 of kinfit
		      hists_.find("chi2_10")->second->Fill( tops.fitChi2(9) );
		      // chi2prob of kinfit
		      hists_.find("prob_10")->second->Fill( tops.fitProb(9) );
		      
		      if(tops.numberOfAvailableHypos("kKinFit")>10){
			
			// chi2 of kinfit
			hists_.find("chi2_11")->second->Fill( tops.fitChi2(10) );
			// chi2prob of kinfit
			hists_.find("prob_11")->second->Fill( tops.fitProb(10) );
			
			if(tops.numberOfAvailableHypos("kKinFit")>11){
			  
			  // chi2 of kinfit
			  hists_.find("chi2_12")->second->Fill( tops.fitChi2(11) );
			  // chi2prob of kinfit
			  hists_.find("prob_12")->second->Fill( tops.fitProb(11) );
			  
			  if(tops.numberOfAvailableHypos("kKinFit")>12){
			    
			    // chi2 of kinfit
			    hists_.find("chi2_13")->second->Fill( tops.fitChi2(12) );
			    // chi2prob of kinfit
			    hists_.find("prob_13")->second->Fill( tops.fitProb(12) );
			    
			    if(tops.numberOfAvailableHypos("kKinFit")>13){
			      
			      // chi2 of kinfit
			      hists_.find("chi2_14")->second->Fill( tops.fitChi2(13) );
			      // chi2prob of kinfit
			      hists_.find("prob_14")->second->Fill( tops.fitProb(13) );
			      
			      if(tops.numberOfAvailableHypos("kKinFit")>14){
				
				// chi2 of kinfit
				hists_.find("chi2_15")->second->Fill( tops.fitChi2(14) );
				// chi2prob of kinfit
				hists_.find("prob_15")->second->Fill( tops.fitProb(14) );
				
				if(tops.numberOfAvailableHypos("kKinFit")>15){
				  
				  // chi2 of kinfit
				  hists_.find("chi2_16")->second->Fill( tops.fitChi2(15) );
				  // chi2prob of kinfit
				  hists_.find("prob_16")->second->Fill( tops.fitProb(15) );
				  
				  if(tops.numberOfAvailableHypos("kKinFit")>16){
				    
				    // chi2 of kinfit
				    hists_.find("chi2_17")->second->Fill( tops.fitChi2(16) );
				    // chi2prob of kinfit
				    hists_.find("prob_17")->second->Fill( tops.fitProb(16) );
				    
				    if(tops.numberOfAvailableHypos("kKinFit")>17){
				      
				      // chi2 of kinfit
				      hists_.find("chi2_18")->second->Fill( tops.fitChi2(17) );
				      // chi2prob of kinfit
				      hists_.find("prob_18")->second->Fill( tops.fitProb(17) );
		  
				      if(tops.numberOfAvailableHypos("kKinFit")>18){
					
					// chi2 of kinfit
					hists_.find("chi2_19")->second->Fill( tops.fitChi2(18) );
					// chi2prob of kinfit
					hists_.find("prob_19")->second->Fill( tops.fitProb(18) );
					
					if(tops.numberOfAvailableHypos("kKinFit")>19){
					  
					  // chi2 of kinfit
					  hists_.find("chi2_20")->second->Fill( tops.fitChi2(19) );
					  // chi2prob of kinfit
					  hists_.find("prob_20")->second->Fill( tops.fitProb(19) );
					  
					  if(tops.numberOfAvailableHypos("kKinFit")>20){
					    
					    // chi2 of kinfit
					    hists_.find("chi2_21")->second->Fill( tops.fitChi2(20) );
					    // chi2prob of kinfit
					    hists_.find("prob_21")->second->Fill( tops.fitProb(20) );
					    
					    if(tops.numberOfAvailableHypos("kKinFit")>21){
			  
					      // chi2 of kinfit
					      hists_.find("chi2_22")->second->Fill( tops.fitChi2(21) );
					      // chi2prob of kinfit
					      hists_.find("prob_22")->second->Fill( tops.fitProb(21) );
					      
					      if(tops.numberOfAvailableHypos("kKinFit")>22){
						
						// chi2 of kinfit
						hists_.find("chi2_23")->second->Fill( tops.fitChi2(22) );
						// chi2prob of kinfit
						hists_.find("prob_23")->second->Fill( tops.fitProb(22) );
						
						if(tops.numberOfAvailableHypos("kKinFit")>23){
						  
						  // chi2 of kinfit
						  hists_.find("chi2_24")->second->Fill( tops.fitChi2(23) );
						  // chi2prob of kinfit
						  hists_.find("prob_24")->second->Fill( tops.fitProb(23) );
						  
						  if(tops.numberOfAvailableHypos("kKinFit")>24){
						    
						    // chi2 of kinfit
						    hists_.find("chi2_25")->second->Fill( tops.fitChi2(24) );
						    // chi2prob of kinfit
						    hists_.find("prob_25")->second->Fill( tops.fitProb(24) );
						    
						    if(tops.numberOfAvailableHypos("kKinFit")>25){
						      
						      // chi2 of kinfit
						      hists_.find("chi2_26")->second->Fill( tops.fitChi2(25) );
						      // chi2prob of kinfit
						      hists_.find("prob_26")->second->Fill( tops.fitProb(25) );
						      
						      if(tops.numberOfAvailableHypos("kKinFit")>26){
							
							// chi2 of kinfit
							hists_.find("chi2_27")->second->Fill( tops.fitChi2(26) );
							// chi2prob of kinfit
							hists_.find("prob_27")->second->Fill( tops.fitProb(26) );
							
							if(tops.numberOfAvailableHypos("kKinFit")>27){
							  
							  // chi2 of kinfit
							  hists_.find("chi2_28")->second->Fill( tops.fitChi2(27) );
							  // chi2prob of kinfit
							  hists_.find("prob_28")->second->Fill( tops.fitProb(27) );
							  
							  if(tops.numberOfAvailableHypos("kKinFit")>28){
							    
							    // chi2 of kinfit
							    hists_.find("chi2_29")->second->Fill( tops.fitChi2(28) );
							    // chi2prob of kinfit
							    hists_.find("prob_29")->second->Fill( tops.fitProb(28) );
							    
							    if(tops.numberOfAvailableHypos("kKinFit")>29){
							      
							      // chi2 of kinfit
							      hists_.find("chi2_30")->second->Fill( tops.fitChi2(29) );
							      // chi2prob of kinfit
							      hists_.find("prob_30")->second->Fill( tops.fitProb(29) );
							      
							    }
							  }
							}
						      }
						    }
						  }
						}
					      }
					    }
					  }
					}
				      }
				    }
				  }
				}
			      }
			    }
			  }
			}
		      }
		    }
		  }
		}
	      }
	    }
	  }
	}
      }
    }
  }
}

