#include "TopAnalysis/TopAnalyzer/interface/JetQuality.h"

/// default constructor for fw lite
JetQuality::JetQuality(const int index) : index_(index)
{ 
}

/// constructor for full FW analyzer
JetQuality::JetQuality(const edm::ParameterSet& cfg) :
  index_( cfg.getParameter<int>( "index" ) )
{
}

/// histogramm booking for fwlite 
void 
JetQuality::book()
{
  /** 
      Selection Variables
  **/
  // electromagnetic fraction of jet
  hists_["emf"                  ] = new TH1F( "emf"                  ,  "emf"                  ,   40,   0.,    1. );
  // btag track counting high purity
  hists_["btagTrkCntHighPurity" ] = new TH1F( "btagTrkCntHighPurity" ,  "btagTrkCntHighPurity" ,   80,   0.,   20. );

  /** 
      Monitoring Variables
  **/
  // number of jet constituents
  hists_["nConst_"            ] = new TH1F( "nConst_"                ,  "nConst_"              ,   50,   0.,  50. );
  // ntag track counting high efficiency
  hists_["btagTrkCntHighEff_" ] = new TH1F( "btagTrkCntHighEff_"     ,  "btagTrkCntHighEff_"   ,   80,   0.,  20. ); 
  // ntag track counting high efficiency
  hists_["btagSimpleSecVtx_"  ] = new TH1F( "btagSimpleSecVtx_"      ,  "btagSimpleSecVtx_"    ,   80,   0.,  20. ); 
}

/// histogramm booking for full fw
void 
JetQuality::book(edm::Service<TFileService>& fs)
{
  /** 
      Selection Variables
  **/
  // electromagnetic fraction of jet
  hists_["emf"                  ] = fs->make<TH1F>( "emf"                  ,  "emf"                  ,   40,   0.,    1. );
  // btag track counting high purity
  hists_["btagTrkCntHighPurity" ] = fs->make<TH1F>( "btagTrkCntHighPurity" ,  "btagTrkCntHighPurity" ,   80,   0.,   20. );

  /** 
      Monitoring Variables
  **/
  // number of jet constituents
  hists_["nConst_"            ] = fs->make<TH1F>( "nConst_"                ,  "nConst_"              ,   50,   0.,  50. );
  // ntag track counting high efficiency
  hists_["btagTrkCntHighEff_" ] = fs->make<TH1F>( "btagTrkCntHighEff_"     ,  "btagTrkCntHighEff_"   ,   80,   0.,  20. ); 
  // ntag track counting high efficiency
  hists_["btagSimpleSecVtx_"  ] = fs->make<TH1F>( "btagSimpleSecVtx_"      ,  "btagSimpleSecVtx_"    ,   80,   0.,  20. ); 
}

/// histogram filling for fwlite and for full fw from reco objects
void
JetQuality::fill(const std::vector<pat::Jet>& jets, const double& weight)
{
  int index=0;
  for(std::vector<pat::Jet>::const_iterator jet=jets.begin(); jet!=jets.end(); ++jet, ++index){
    // NOTE: These histograms still need to be filled apropriately
    if( index_<0 || index_==index ){
      /**
	 Fill Selection Variables
      **/

      
      /** 
	  Fill Monitoring Variables
      **/
    }
  }
}
