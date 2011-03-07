#include "TopAnalysis/TopAnalyzer/interface/FullHadSpecial.h"
#include "DataFormats/Math/interface/deltaR.h"

/// default constructor for fw lite
FullHadSpecial::FullHadSpecial()
{
  tree = 0;
}

/// default constructor for fwfull
FullHadSpecial::FullHadSpecial(const edm::ParameterSet& cfg) :
  useTree_ ( cfg.getParameter<bool>( "useTree" ) )
{
  tree = 0;
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
  bookVariable( fs , "ht" , 500, 0. , 2500. , useTree_ );
  /// real B-Quarks, -1 fake, 1 real
  //bookVariable( fs , "realB"    ,   2,  -1. ,    1. , useTree_ );
  /// real B-Quarks, -1 fake, 1 real
  //bookVariable( fs , "realBCSV" ,   2,  -1. ,    1. , useTree_ );
  /// real B-Quarks, -1 fake, 1 real
  //bookVariable( fs , "realBSM"  ,   2,  -1. ,    1. , useTree_ );
  /// di-jet mass
  bookVariable( fs, "mjj"     , 200, 0. , 2000. , false );
  /// tri-jet mass
  bookVariable( fs, "mjjj"    , 200, 0. , 2000. , false );
  /// uncorrected jet pt
  bookVariable( fs, "jetPtUn" ,  50, 0. ,  500. , false );

  if(!useTree_){
    /// pt of b1 vs. pt of b2
    bookVariable( fs, "ptb1ptb2" ,  130 , 20. , 150. , 130 , 20. , 150. );
    /// pt of 1 vs. pt of 2
    bookVariable( fs, "pt1pt2"   ,  130 , 20. , 150. , 130 , 20. , 150. );
    /// pt of 1 vs. pt of 3
    bookVariable( fs, "pt1pt3"   ,  130 , 20. , 150. , 130 , 20. , 150. );
    /// pt of 1 vs. pt of 4
    bookVariable( fs, "pt1pt4"   ,  130 , 20. , 150. , 130 , 20. , 150. );
    /// pt of 1 vs. pt of 5
    bookVariable( fs, "pt1pt5"   ,  130 , 20. , 150. , 130 , 20. , 150. );
    /// pt of 1 vs. pt of 6
    bookVariable( fs, "pt1pt6"   ,  130 , 20. , 150. , 130 , 20. , 150. );
    /// pt of 2 vs. pt of 3
    bookVariable( fs, "pt2pt3"   ,  130 , 20. , 150. , 130 , 20. , 150. );
    /// pt of 2 vs. pt of 4
    bookVariable( fs, "pt2pt4"   ,  130 , 20. , 150. , 130 , 20. , 150. );
    /// pt of 2 vs. pt of 5
    bookVariable( fs, "pt2pt5"   ,  130 , 20. , 150. , 130 , 20. , 150. );
    /// pt of 2 vs. pt of 6
    bookVariable( fs, "pt2pt6"   ,  130 , 20. , 150. , 130 , 20. , 150. );
    /// pt of 3 vs. pt of 4
    bookVariable( fs, "pt3pt4"   ,  130 , 20. , 150. , 130 , 20. , 150. );
    /// pt of 3 vs. pt of 5
    bookVariable( fs, "pt3pt5"   ,  130 , 20. , 150. , 130 , 20. , 150. );
    /// pt of 3 vs. pt of 6
    bookVariable( fs, "pt3pt6"   ,  130 , 20. , 150. , 130 , 20. , 150. );
    /// pt of 4 vs. pt of 5
    bookVariable( fs, "pt4pt5"   ,  130 , 20. , 150. , 130 , 20. , 150. );
    /// pt of 4 vs. pt of 6
    bookVariable( fs, "pt4pt6"   ,  130 , 20. , 150. , 130 , 20. , 150. );
    /// pt of 5 vs. pt of 6
    bookVariable( fs, "pt5pt6"   ,  130 , 20. , 150. , 130 , 20. , 150. );
  }

  /// pt of b1 - pt of b2
  bookVariable( fs, "ptb1-ptb2" , 200 , 0. , 200. , useTree_ );
  /// pt of 1 - pt of 2
  bookVariable( fs, "pt1-pt2"   , 200 , 0. , 200. , useTree_ );
  /// pt of 1 - pt of 3
  bookVariable( fs, "pt1-pt3"   , 200 , 0. , 200. , useTree_ );
  /// pt of 1 - pt of 4
  bookVariable( fs, "pt1-pt4"   , 200 , 0. , 200. , useTree_ );
  /// pt of 1 - pt of 5
  bookVariable( fs, "pt1-pt5"   , 200 , 0. , 200. , useTree_ );
  /// pt of 1 - pt of 6
  bookVariable( fs, "pt1-pt6"   , 200 , 0. , 200. , useTree_ );
  /// pt of 2 - pt of 3
  bookVariable( fs, "pt2-pt3"   , 200 , 0. , 200. , useTree_ );
  /// pt of 2 - pt of 4
  bookVariable( fs, "pt2-pt4"   , 200 , 0. , 200. , useTree_ );
  /// pt of 2 - pt of 5
  bookVariable( fs, "pt2-pt5"   , 200 , 0. , 200. , useTree_ );
  /// pt of 2 - pt of 6
  bookVariable( fs, "pt2-pt6"   , 200 , 0. , 200. , useTree_ );
  /// pt of 3 - pt of 4
  bookVariable( fs, "pt3-pt4"   , 200 , 0. , 200. , useTree_ );
  /// pt of 3 - pt of 5
  bookVariable( fs, "pt3-pt5"   , 200 , 0. , 200. , useTree_ );
  /// pt of 3 - pt of 6
  bookVariable( fs, "pt3-pt6"   , 200 , 0. , 200. , useTree_ );
  /// pt of 4 - pt of 5
  bookVariable( fs, "pt4-pt5"   , 200 , 0. , 200. , useTree_ );
  /// pt of 4 - pt of 6
  bookVariable( fs, "pt4-pt6"   , 200 , 0. , 200. , useTree_ );
  /// pt of 5 - pt of 6
  bookVariable( fs, "pt5-pt6"   , 200 , 0. , 200. , useTree_ );

  /// pt of b1 - pt of b2 norm
  bookVariable( fs, "ptb1-ptb2_norm" , 100 , 0. , 1. , useTree_ );
  /// pt of 1 - pt of 2 norm
  bookVariable( fs, "pt1-pt2_norm"   , 100 , 0. , 1. , useTree_ );
  /// pt of 1 - pt of 3 norm
  bookVariable( fs, "pt1-pt3_norm"   , 100 , 0. , 1. , useTree_ );
  /// pt of 1 - pt of 4 norm
  bookVariable( fs, "pt1-pt4_norm"   , 100 , 0. , 1. , useTree_ );
  /// pt of 1 - pt of 5 norm
  bookVariable( fs, "pt1-pt5_norm"   , 100 , 0. , 1. , useTree_ );
  /// pt of 1 - pt of 6 norm
  bookVariable( fs, "pt1-pt6_norm"   , 100 , 0. , 1. , useTree_ );
  /// pt of 2 - pt of 3 norm
  bookVariable( fs, "pt2-pt3_norm"   , 100 , 0. , 1. , useTree_ );
  /// pt of 2 - pt of 4 norm
  bookVariable( fs, "pt2-pt4_norm"   , 100 , 0. , 1. , useTree_ );
  /// pt of 2 - pt of 5 norm
  bookVariable( fs, "pt2-pt5_norm"   , 100 , 0. , 1. , useTree_ );
  /// pt of 2 - pt of 6 norm
  bookVariable( fs, "pt2-pt6_norm"   , 100 , 0. , 1. , useTree_ );
  /// pt of 3 - pt of 4 norm
  bookVariable( fs, "pt3-pt4_norm"   , 100 , 0. , 1. , useTree_ );
  /// pt of 3 - pt of 5 norm
  bookVariable( fs, "pt3-pt5_norm"   , 100 , 0. , 1. , useTree_ );
  /// pt of 3 - pt of 6 norm
  bookVariable( fs, "pt3-pt6_norm"   , 100 , 0. , 1. , useTree_ );
  /// pt of 4 - pt of 5 norm
  bookVariable( fs, "pt4-pt5_norm"   , 100 , 0. , 1. , useTree_ );
  /// pt of 4 - pt of 6 norm
  bookVariable( fs, "pt4-pt6_norm"   , 100 , 0. , 1. , useTree_ );
  /// pt of 5 - pt of 6 norm
  bookVariable( fs, "pt5-pt6_norm"   , 100 , 0. , 1. , useTree_ );
  /// thrust
  //bookVariable( fs, "thrust"   , 100 , 0. , 1. , useTree_ );
  /// (thrust - real) vs Ht
  //bookVariable( fs, "thrustHt" , 100 , 0. , 1. , useTree_ );
  /// eta-eta-moment
  bookVariable( fs, "etaeta" , 120 ,  0.   , 0.12 , false );
  /// eta-phi-moment
  bookVariable( fs, "etaphi" , 100 , -0.05 , 0.05 , false );
  /// phi-phi-moment
  bookVariable( fs, "phiphi" , 120 ,  0.   , 0.12 , false );

  /// sum eta-eta-moments
  bookVariable( fs, "sumEtaEta"    , 250 , 0. , 0.5 , useTree_ );
  /// sum phi-phi-moments
  bookVariable( fs, "sumPhiPhi"    , 250 , 0. , 0.5 , useTree_ );
  /// sum abs(eta-phi-moments)
  bookVariable( fs, "sumAbsEtaPhi" , 250 , 0. , 0.5 , useTree_ );

  /// sum eta-eta-moments + phi-phi-moments
  bookVariable( fs, "sumEtaEtaPhiPhi"       , 500 , 0. , 1.0 , useTree_ );
  /// sum eta-eta-moments + phi-phi-moments + abs(eta-phi-moments)
  bookVariable( fs, "sumEtaEtaEtaPhiPhiPhi" , 750 , 0. , 1.5 , useTree_ );

  /// sum eta-eta-moments normalized to number of jets
  bookVariable( fs, "sumEtaEta_norm"    , 120 , 0. , 0.12 , useTree_ );
  /// sum phi-phi-moments normalized to number of jets
  bookVariable( fs, "sumPhiPhi_norm"    , 120 , 0. , 0.12 , useTree_ );
  /// sum abs(eta-phi-moments) normalized to number of jets
  bookVariable( fs, "sumAbsEtaPhi_norm" , 100 , 0. , 0.05 , useTree_ );

  /// sum eta-eta-moments + phi-phi-moments normalized to number of jets
  bookVariable( fs, "sumEtaEtaPhiPhi_norm"       , 250 , 0. , 0.25 , useTree_ );
  /// sum eta-eta-moments + phi-phi-moments + abs(eta-phi-moments) normalized to number of jets
  bookVariable( fs, "sumEtaEtaEtaPhiPhiPhi_norm" , 300 , 0. , 0.30 , useTree_ );


  if(!useTree_){
    /// eta-eta-moment vs. phi-phi-moment
    bookVariable( fs, "etaetaphiphi" ,  120 ,  0.   , 0.12 , 120 ,  0.   , 0.12 );
    /// eta-eta-moment vs. eta-phi-moment
    bookVariable( fs, "etaetaetaphi" ,  120 ,  0.   , 0.12 , 100 , -0.05 , 0.05 );
    /// eta-phi-moment vs. phi-phi-moment
    bookVariable( fs, "etaphiphiphi" ,  100 , -0.05 , 0.05 , 120 ,  0.   , 0.12 );
  }

  /*
  /// eta-eta-moment for b jets
  bookVariable( fs, "etaeta_b" , 120 ,  0.   , 0.12 , false );
  /// eta-phi-moment for b jets
  bookVariable( fs, "etaphi_b" , 100 , -0.05 , 0.05 , false );
  /// phi-phi-moment for b jets
  bookVariable( fs, "phiphi_b" , 120 ,  0.   , 0.12 , false );

  if(!useTree_){
    /// eta-eta-moment vs. phi-phi-moment for b jets
    bookVariable( fs, "etaetaphiphi_b" ,  120 ,  0.   , 0.12 , 120 ,  0.   , 0.12 );
    /// eta-eta-moment vs. eta-phi-moment for b jets
    bookVariable( fs, "etaetaetaphi_b" ,  120 ,  0.   , 0.12 , 100 , -0.05 , 0.05 );
    /// eta-phi-moment vs. phi-phi-moment for b jets
    bookVariable( fs, "etaphiphiphi_b" ,  100 , -0.05 , 0.05 , 120 ,  0.   , 0.12 );
  }
  
  /// eta-eta-moment for q jets
  bookVariable( fs, "etaeta_q" , 120 ,  0.   , 0.12 , false );
  /// eta-phi-moment for q jets
  bookVariable( fs, "etaphi_q" , 100 , -0.05 , 0.05 , false );
  /// phi-phi-moment for q jets
  bookVariable( fs, "phiphi_q" , 120 ,  0.   , 0.12 , false );

  if(!useTree_){
    /// eta-eta-moment vs. phi-phi-moment for q jets
    bookVariable( fs, "etaetaphiphi_q" ,  120 ,  0.   , 0.12 , 120 ,  0.   , 0.12 );
    /// eta-eta-moment vs. eta-phi-moment for q jets
    bookVariable( fs, "etaetaetaphi_q" ,  120 ,  0.   , 0.12 , 100 , -0.05 , 0.05 );
    /// eta-phi-moment vs. phi-phi-moment for q jets
    bookVariable( fs, "etaphiphiphi_q" ,  100 , -0.05 , 0.05 , 120 ,  0.   , 0.12 );
  }
  
  /// eta-eta-moment for g jets
  bookVariable( fs, "etaeta_g" , 120 ,  0.   , 0.12 , false );
  /// eta-phi-moment for g jets
  bookVariable( fs, "etaphi_g" , 100 , -0.05 , 0.05 , false );
  /// phi-phi-moment for g jets
  bookVariable( fs, "phiphi_g" , 120 ,  0.   , 0.12 , false );

  if(!useTree_){
    /// eta-eta-moment vs. phi-phi-moment for g jets
    bookVariable( fs, "etaetaphiphi_g" ,  120 ,  0.   , 0.12 , 120 ,  0.   , 0.12 );
    /// eta-eta-moment vs. eta-phi-moment for g jets
    bookVariable( fs, "etaetaetaphi_g" ,  120 ,  0.   , 0.12 , 100 , -0.05 , 0.05 );
    /// eta-phi-moment vs. phi-phi-moment for g jets
    bookVariable( fs, "etaphiphiphi_g" ,  100 , -0.05 , 0.05 , 120 ,  0.   , 0.12 );
  }
  */

  /// sqrt s
  bookVariable( fs, "sqrt_s"     , 250 ,  0. , 2500. , useTree_ );
  /// Ht3j, sum of Et of all jets starting from 3. jet
  bookVariable( fs, "ht3jet"     , 200 ,  0. , 1000. , useTree_ );
  /// Et56, geometric mean of Et of 5. and 6. jet
  bookVariable( fs, "et56"       ,  50 ,  0. ,  150. , useTree_ );
  /// Centrality (HT/H)
  bookVariable( fs, "centrality" , 100 ,  0. ,    1. , useTree_ );
  /// M3 mass of first 3 jets in event
  bookVariable( fs, "M3"         , 200 ,  0. , 1000. , useTree_ );

  /// TCHP disci of 1. Jet
  bookVariable( fs, "TCHP_Bjet1" ,  60 , -5. ,   25. , useTree_ );
  /// TCHP disci of 2. Jet
  bookVariable( fs, "TCHP_Bjet2" ,  60 , -5. ,   25. , useTree_ );
  /// TCHP disci of 3. Jet
  bookVariable( fs, "TCHP_Bjet3" ,  60 , -5. ,   25. , useTree_ );
  /// TCHP disci of 4. Jet
  bookVariable( fs, "TCHP_Bjet4" ,  60 , -5. ,   25. , useTree_ );
  /// TCHP disci of 5. Jet
  bookVariable( fs, "TCHP_Bjet5" ,  60 , -5. ,   25. , useTree_ );
  /// TCHP disci of 6. Jet
  bookVariable( fs, "TCHP_Bjet6" ,  60 , -5. ,   25. , useTree_ );
  /// SSV disci of 1. Jet
  bookVariable( fs, "SSV_Bjet1"  ,  60 ,  0. ,    6. , useTree_ );
  /// SSV disci of 2. Jet
  bookVariable( fs, "SSV_Bjet2"  ,  60 ,  0. ,    6. , useTree_ );
  /// SSV disci of 3. Jet
  bookVariable( fs, "SSV_Bjet3"  ,  60 ,  0. ,    6. , useTree_ );
  /// SSV disci of 4. Jet
  bookVariable( fs, "SSV_Bjet4"  ,  60 ,  0. ,    6. , useTree_ );
  /// SSV disci of 5. Jet
  bookVariable( fs, "SSV_Bjet5"  ,  60 ,  0. ,    6. , useTree_ );
  /// SSV disci of 6. Jet
  bookVariable( fs, "SSV_Bjet6"  ,  60 ,  0. ,    6. , useTree_ );
  /// CSV disci of 1. Jet
  bookVariable( fs, "CSV_Bjet1"  ,  50 ,  0. , 1.001 , useTree_ );
  /// CSV disci of 2. Jet
  bookVariable( fs, "CSV_Bjet2"  ,  50 ,  0. , 1.001 , useTree_ );
  /// CSV disci of 3. Jet
  bookVariable( fs, "CSV_Bjet3"  ,  50 ,  0. , 1.001 , useTree_ );
  /// CSV disci of 4. Jet
  bookVariable( fs, "CSV_Bjet4"  ,  50 ,  0. , 1.001 , useTree_ );
  /// CSV disci of 5. Jet
  bookVariable( fs, "CSV_Bjet5"  ,  50 ,  0. , 1.001 , useTree_ );
  /// CSV disci of 6. Jet
  bookVariable( fs, "CSV_Bjet6"  ,  50 ,  0. , 1.001 , useTree_ );

  /*
  /// SM disci of 1. Jet
  bookVariable( fs, "SM_Bjet1"  ,  50 ,  0. , 1.001 , useTree_ );
  /// SM disci of 2. Jet
  bookVariable( fs, "SM_Bjet2"  ,  50 ,  0. , 1.001 , useTree_ );
  /// SM disci of 3. Jet
  bookVariable( fs, "SM_Bjet3"  ,  50 ,  0. , 1.001 , useTree_ );
  /// SM disci of 4. Jet
  bookVariable( fs, "SM_Bjet4"  ,  50 ,  0. , 1.001 , useTree_ );
  /// SM disci of 5. Jet
  bookVariable( fs, "SM_Bjet5"  ,  50 ,  0. , 1.001 , useTree_ );
  /// SM disci of 6. Jet
  bookVariable( fs, "SM_Bjet6"  ,  50 ,  0. , 1.001 , useTree_ );
  */

  /// min. dR of 2 jets in the event
  bookVariable( fs, "dRMin1"            ,  40 ,  0. ,    4. , useTree_ );
  /// 2. min. dR of 2 jets in the event
  bookVariable( fs, "dRMin2"            ,  40 ,  0. ,    4. , useTree_ );
  /// 3. min. dR of 2 jets in the event
  bookVariable( fs, "dRMin3"            ,  40 ,  0. ,    4. , useTree_ );
  /// 4. min. dR of 2 jets in the event
  bookVariable( fs, "dRMin4"            ,  40 ,  0. ,    4. , useTree_ );
  /// 5. min. dR of 2 jets in the event
  bookVariable( fs, "dRMin5"            ,  40 ,  0. ,    4. , useTree_ );
  /// 6. min. dR of 2 jets in the event
  bookVariable( fs, "dRMin6"            ,  40 ,  0. ,    4. , useTree_ );
  /// mass of min. dR of 2 jets in the event
  bookVariable( fs, "dRMin1Mass"        , 200 ,  0. ,  800. , useTree_ );
  /// mass of 2. min. dR of 2 jets in the event
  bookVariable( fs, "dRMin2Mass"        , 200 ,  0. ,  800. , useTree_ );
  /// min. sum dR of 3 jets in the event
  bookVariable( fs, "sumDR3JetMin1"     ,  70 ,  0. ,   14. , useTree_ );
  /// 2. min. sum dR of 3 jets in the event
  bookVariable( fs, "sumDR3JetMin2"     ,  70 ,  0. ,   14. , useTree_ );
  /// mass of min. sum dR of 3 jets in the event
  bookVariable( fs, "sumDR3JetMin1Mass" , 250 ,  0. , 1000. , useTree_ );
  /// mass of 2. min. sum dR of 3 jets in the event
  bookVariable( fs, "sumDR3JetMin2Mass" , 250 ,  0. , 1000. , useTree_ );
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
  double M3_ = -1.;

  double sumEtaEta    = 0.;
  double sumPhiPhi    = 0.;
  double sumAbsEtaPhi = 0.;

  int bJetCounter = 0;
  edm::View<pat::Jet>::const_iterator bJet1;
  edm::View<pat::Jet>::const_iterator Jet1;
  edm::View<pat::Jet>::const_iterator Jet2;
  edm::View<pat::Jet>::const_iterator Jet3;
  edm::View<pat::Jet>::const_iterator Jet4;
  edm::View<pat::Jet>::const_iterator Jet5;
  edm::View<pat::Jet>::const_iterator Jet6;

  unsigned int idx = 0;

  double TCHP_Bjet1_ = -9999.0;
  double TCHP_Bjet2_ = -9999.0;
  double TCHP_Bjet3_ = -9999.0;
  double TCHP_Bjet4_ = -9999.0;
  double TCHP_Bjet5_ = -9999.0;
  double TCHP_Bjet6_ = -9999.0;
  double SSV_Bjet1_  = -9999.0; 
  double SSV_Bjet2_  = -9999.0; 
  double SSV_Bjet3_  = -9999.0; 
  double SSV_Bjet4_  = -9999.0; 
  double SSV_Bjet5_  = -9999.0; 
  double SSV_Bjet6_  = -9999.0; 
  double CSV_Bjet1_  = -9999.0; 
  double CSV_Bjet2_  = -9999.0; 
  double CSV_Bjet3_  = -9999.0; 
  double CSV_Bjet4_  = -9999.0; 
  double CSV_Bjet5_  = -9999.0; 
  double CSV_Bjet6_  = -9999.0; 
  //double SM_Bjet1_   = -9999.0;  
  //double SM_Bjet2_   = -9999.0;  
  //double SM_Bjet3_   = -9999.0;  
  //double SM_Bjet4_   = -9999.0;  
  //double SM_Bjet5_   = -9999.0;  
  //double SM_Bjet6_   = -9999.0;  

  double dRMin1_        = -1;	   
  double dRMin2_        = -1;	   
  double dRMin3_        = -1;	   
  double dRMin4_        = -1;	   
  double dRMin5_        = -1;	   
  double dRMin6_        = -1;	   
  double sumDR3JetMin1_ = -1;	   
  double sumDR3JetMin2_ = -1;	   

  double dRMin1Mass_        = -1;	   
  double dRMin2Mass_        = -1;	   
  double sumDR3JetMin1Mass_ = -1;
  double sumDR3JetMin2Mass_ = -1;

  std::list< double > TCHP_Bjet_Discis;
  std::list< double > SSV_Bjet_Discis;
  std::list< double > CSV_Bjet_Discis;
  std::list< double > SM_Bjet_Discis;

  std::list< std::pair< double, std::pair< unsigned int, unsigned int > > > dRs;
  std::list< std::pair< double, std::pair< std::pair< unsigned int, unsigned int >, unsigned int > > > dRs3Jets;

  unsigned int jetCounter = 1;
  for(edm::View<pat::Jet>::const_iterator jet = jets.begin(); jet != jets.end(); ++jet, ++idx, ++jetCounter){

    ht_ += jet->et();
    h_  += jet->energy();
    ht3jet_ += jet->et();

    TCHP_Bjet_Discis.push_back( jet->bDiscriminator("trackCountingHighPurBJetTags")    );
    SSV_Bjet_Discis.push_back(  jet->bDiscriminator("simpleSecondaryVertexBJetTags")   );
    CSV_Bjet_Discis.push_back(  jet->bDiscriminator("combinedSecondaryVertexBJetTags") );
    //SM_Bjet_Discis.push_back(   jet->bDiscriminator("softMuonBJetTags")                );

    fillValue("jetPtUn" , jet->correctedJet("Uncorrected").pt() , weight );

    if(idx == 0){
      Jet1 = jet;
      ht3jet_ -= jet->et();
    }
    if(idx == 1){
      Jet2 = jet;
      if(!useTree_) fillValue("pt1pt2" , Jet1->pt(), Jet2->pt(), weight );
      fillValue("pt1-pt2" , Jet1->pt() - Jet2->pt(), weight );
      fillValue("pt1-pt2_norm" , (Jet1->pt() - Jet2->pt()) / (Jet1->pt() + Jet2->pt()), weight );
      ht3jet_ -= jet->et();
    }
    if(idx == 2){
      Jet3 = jet;
      if(!useTree_) {
	fillValue("pt1pt3" , Jet1->pt(), Jet3->pt(), weight );
	fillValue("pt2pt3" , Jet2->pt(), Jet3->pt(), weight );
      }
      fillValue("pt1-pt3" , Jet1->pt() - Jet3->pt(), weight );
      fillValue("pt2-pt3" , Jet2->pt() - Jet3->pt(), weight );
      fillValue("pt1-pt3_norm" , (Jet1->pt() - Jet3->pt()) / (Jet1->pt() + Jet3->pt()), weight );
      fillValue("pt2-pt3_norm" , (Jet2->pt() - Jet3->pt()) / (Jet2->pt() + Jet3->pt()), weight );
    }
    if(idx == 3){
      Jet4 = jet;
      if(!useTree_) {
	fillValue("pt1pt4" , Jet1->pt(), Jet4->pt(), weight );
	fillValue("pt2pt4" , Jet2->pt(), Jet4->pt(), weight );
	fillValue("pt3pt4" , Jet3->pt(), Jet4->pt(), weight );
      }
      fillValue("pt1-pt4" , Jet1->pt() - Jet4->pt(), weight );
      fillValue("pt2-pt4" , Jet2->pt() - Jet4->pt(), weight );
      fillValue("pt3-pt4" , Jet3->pt() - Jet4->pt(), weight );
      fillValue("pt1-pt4_norm" , (Jet1->pt() - Jet4->pt()) / (Jet1->pt() + Jet4->pt()), weight );
      fillValue("pt2-pt4_norm" , (Jet2->pt() - Jet4->pt()) / (Jet2->pt() + Jet4->pt()), weight );
      fillValue("pt3-pt4_norm" , (Jet3->pt() - Jet4->pt()) / (Jet3->pt() + Jet4->pt()), weight );
    }
    if(idx == 4){
      Jet5 = jet;
      if(!useTree_) {
	fillValue("pt1pt5" , Jet1->pt(), Jet5->pt(), weight );
	fillValue("pt2pt5" , Jet2->pt(), Jet5->pt(), weight );
	fillValue("pt3pt5" , Jet3->pt(), Jet5->pt(), weight );
	fillValue("pt4pt5" , Jet4->pt(), Jet5->pt(), weight );
      }
      fillValue("pt1-pt5" , Jet1->pt() - Jet5->pt(), weight );
      fillValue("pt2-pt5" , Jet2->pt() - Jet5->pt(), weight );
      fillValue("pt3-pt5" , Jet3->pt() - Jet5->pt(), weight );
      fillValue("pt4-pt5" , Jet4->pt() - Jet5->pt(), weight );
      fillValue("pt1-pt5_norm" , (Jet1->pt() - Jet5->pt()) / (Jet1->pt() + Jet5->pt()), weight );
      fillValue("pt2-pt5_norm" , (Jet2->pt() - Jet5->pt()) / (Jet2->pt() + Jet5->pt()), weight );
      fillValue("pt3-pt5_norm" , (Jet3->pt() - Jet5->pt()) / (Jet3->pt() + Jet5->pt()), weight );
      fillValue("pt4-pt5_norm" , (Jet4->pt() - Jet5->pt()) / (Jet4->pt() + Jet5->pt()), weight );
    }
    if(idx == 5){
      Jet6 = jet;
      if(!useTree_) {
	fillValue("pt1pt6" , Jet1->pt(), Jet6->pt(), weight );
	fillValue("pt2pt6" , Jet2->pt(), Jet6->pt(), weight );
	fillValue("pt3pt6" , Jet3->pt(), Jet6->pt(), weight );
	fillValue("pt4pt6" , Jet4->pt(), Jet6->pt(), weight );
	fillValue("pt5pt6" , Jet5->pt(), Jet6->pt(), weight );
      }
      fillValue("pt1-pt6" , Jet1->pt() - Jet6->pt(), weight );
      fillValue("pt2-pt6" , Jet2->pt() - Jet6->pt(), weight );
      fillValue("pt3-pt6" , Jet3->pt() - Jet6->pt(), weight );
      fillValue("pt4-pt6" , Jet4->pt() - Jet6->pt(), weight );
      fillValue("pt5-pt6" , Jet5->pt() - Jet6->pt(), weight );
      fillValue("pt1-pt6_norm" , (Jet1->pt() - Jet6->pt()) / (Jet1->pt() + Jet6->pt()), weight );
      fillValue("pt2-pt6_norm" , (Jet2->pt() - Jet6->pt()) / (Jet2->pt() + Jet6->pt()), weight );
      fillValue("pt3-pt6_norm" , (Jet3->pt() - Jet6->pt()) / (Jet3->pt() + Jet6->pt()), weight );
      fillValue("pt4-pt6_norm" , (Jet4->pt() - Jet6->pt()) / (Jet4->pt() + Jet6->pt()), weight );
      fillValue("pt5-pt6_norm" , (Jet5->pt() - Jet6->pt()) / (Jet5->pt() + Jet6->pt()), weight );
      fillValue("sqrt_s" , (Jet1->p4()+Jet2->p4()+Jet3->p4()+Jet4->p4()+Jet5->p4()+Jet6->p4()).mass(), weight );
      fillValue("et56" , sqrt(Jet5->et()*Jet6->et()), weight );
    }

    fillValue("etaeta" , jet->etaetaMoment() , weight );
    fillValue("etaphi" , jet->etaphiMoment() , weight );
    fillValue("phiphi" , jet->phiphiMoment() , weight );

    sumEtaEta    += jet->etaetaMoment();
    sumPhiPhi    += jet->phiphiMoment();
    sumAbsEtaPhi += std::abs(jet->etaphiMoment());

    if(!useTree_) {
      fillValue("etaetaphiphi" , jet->etaetaMoment() , jet->phiphiMoment() , weight );
      fillValue("etaetaetaphi" , jet->etaetaMoment() , jet->etaphiMoment() , weight );
      fillValue("etaphiphiphi" , jet->etaphiMoment() , jet->phiphiMoment() , weight );
    }

    /*
    if(jet->genParticle() != 0) {
      if(jet->genParticle()->pdgId() == 5 || jet->genParticle()->pdgId() == -5){
	fillValue("etaeta_b" , jet->etaetaMoment() , weight );
	fillValue("etaphi_b" , jet->etaphiMoment() , weight );
	fillValue("phiphi_b" , jet->phiphiMoment() , weight );
	
	if(!useTree_) {
	  fillValue("etaetaphiphi_b" , jet->etaetaMoment() , jet->phiphiMoment() , weight );
	  fillValue("etaetaetaphi_b" , jet->etaetaMoment() , jet->etaphiMoment() , weight );
	  fillValue("etaphiphiphi_b" , jet->etaphiMoment() , jet->phiphiMoment() , weight );
	  }
      }
      if(jet->genParticle()->pdgId() < 5 || jet->genParticle()->pdgId() > -5){
	fillValue("etaeta_q" , jet->etaetaMoment() , weight );
	fillValue("etaphi_q" , jet->etaphiMoment() , weight );
	fillValue("phiphi_q" , jet->phiphiMoment() , weight );
	
	if(!useTree_) {
	  fillValue("etaetaphiphi_q" , jet->etaetaMoment() , jet->phiphiMoment() , weight );
	  fillValue("etaetaetaphi_q" , jet->etaetaMoment() , jet->etaphiMoment() , weight );
	  fillValue("etaphiphiphi_q" , jet->etaphiMoment() , jet->phiphiMoment() , weight );
	  }
      }
      if(jet->genParticle()->pdgId() == 9  || jet->genParticle()->pdgId() == -9 ||
	 jet->genParticle()->pdgId() == 21 || jet->genParticle()->pdgId() == -21){
	fillValue("etaeta_g" , jet->etaetaMoment() , weight );
	fillValue("etaphi_g" , jet->etaphiMoment() , weight );
	fillValue("phiphi_g" , jet->phiphiMoment() , weight );
	
	if(!useTree_) {
	  fillValue("etaetaphiphi_g" , jet->etaetaMoment() , jet->phiphiMoment() , weight );
	  fillValue("etaetaetaphi_g" , jet->etaetaMoment() , jet->etaphiMoment() , weight );
	  fillValue("etaphiphiphi_g" , jet->etaphiMoment() , jet->phiphiMoment() , weight );
	}
      }
    }
    */

    if(jet->bDiscriminator("trackCountingHighPurBJetTags") > 3.){
      if(jet->genParticle() != 0) {
	++bJetCounter;
	if(bJetCounter == 1) bJet1 = jet;
	if(bJetCounter == 2) {
	  if(!useTree_) fillValue("ptb1ptb2" , bJet1->pt(), jet->pt(), weight );
	  fillValue("ptb1-ptb2" , bJet1->pt() - jet->pt(), weight );
	  fillValue("ptb1-ptb2_norm" , (bJet1->pt() - jet->pt()) / (bJet1->pt() + jet->pt()), weight );
	}
	/*
	if(jet->genParticle()->pdgId() == 5 || jet->genParticle()->pdgId() == -5){
	  fillValue("realB" ,  0.5 , weight );
	}
	else{
	  fillValue("realB" , -0.5 , weight );	
	}
	*/
      }
    }
    /*
    if(jet->bDiscriminator("combinedSecondaryVertexBJetTags") > 0.9){
      if(jet->genParticle() != 0) {
	if(jet->genParticle()->pdgId() == 5 || jet->genParticle()->pdgId() == -5){
	  fillValue("realBCSV" ,  0.5 , weight );
	}
	else{
	  fillValue("realBCSV" , -0.5 , weight );	
	}
      }
    }

    if(jet->bDiscriminator("softMuonBJetTags") > 0.3){
      if(jet->genParticle() != 0) {
	if(jet->genParticle()->pdgId() == 5 || jet->genParticle()->pdgId() == -5){
	  fillValue("realBSM" ,  0.5 , weight );
	}
	else{
	  fillValue("realBSM" , -0.5 , weight );	
	}
      }
    }
    */
    if(jets.size()>5){
      unsigned int jetCounter2 = jetCounter + 1;
      for(edm::View<pat::Jet>::const_iterator jet2 = jet; (jet2 != jets.end() && jet2 != (--jets.end()) && jet2 != (--(--jets.end()))); ++jet2, ++jetCounter2){
	++jet2;
	dRs.push_back( std::make_pair( deltaR( jet->eta(), jet->phi(), jet2->eta(), jet2->phi() ), std::make_pair( jetCounter-1, jetCounter2-1 ) ) );
	
	unsigned int jetCounter3 = jetCounter2 + 1;
	for(edm::View<pat::Jet>::const_iterator jet3 = jet2; (jet3 != jets.end() && jet3 != (--jets.end()) && jet3 != (--(--jets.end())) && jet3 != (--(--(--jets.end())))); ++jet3, ++jetCounter3){
	  ++jet3;
	  double dR1 = deltaR( jet->eta() , jet->phi() , jet2->eta(), jet2->phi() );
	  double dR2 = deltaR( jet->eta() , jet->phi() , jet3->eta(), jet3->phi() );
	  double dR3 = deltaR( jet2->eta(), jet2->phi(), jet3->eta(), jet3->phi() );
	  dRs3Jets.push_back( std::make_pair( dR1+dR2+dR3, std::make_pair( std::make_pair( jetCounter-1, jetCounter2-1 ), jetCounter3-1 ) ) );
	}
      }
    }
  }

  fillValue("ht" , ht_ , weight );
  fillValue("ht3jet" , ht3jet_ , weight );
  fillValue("centrality" , ht_/h_ , weight );

  fillValue("sumEtaEta"    , sumEtaEta    , weight );
  fillValue("sumPhiPhi"    , sumPhiPhi    , weight );
  fillValue("sumAbsEtaPhi" , sumAbsEtaPhi , weight );

  fillValue("sumEtaEtaPhiPhi"      , sumEtaEta                + sumPhiPhi , weight );
  fillValue("sumEtaEtaEtaPhiPhiPhi", sumEtaEta + sumAbsEtaPhi + sumPhiPhi , weight );

  sumEtaEta   /=jets.size();
  sumPhiPhi   /=jets.size();
  sumAbsEtaPhi/=jets.size();

  fillValue("sumEtaEta_norm"    , sumEtaEta    , weight );
  fillValue("sumPhiPhi_norm"    , sumPhiPhi    , weight );
  fillValue("sumAbsEtaPhi_norm" , sumAbsEtaPhi , weight );

  fillValue("sumEtaEtaPhiPhi_norm"      , sumEtaEta                + sumPhiPhi , weight );
  fillValue("sumEtaEtaEtaPhiPhiPhi_norm", sumEtaEta + sumAbsEtaPhi + sumPhiPhi , weight );

  dRs.sort();
  dRs3Jets.sort();
  
  if(jets.size()>5){
    dRMin1_ = dRs.begin()->first;
    dRMin1Mass_ = (jets[dRs.begin()->second.first].p4()+jets[dRs.begin()->second.second].p4()).mass();
    sumDR3JetMin1_ = dRs3Jets.begin()->first;
    sumDR3JetMin1Mass_ = (jets[dRs3Jets.begin()->second.first.first].p4()+jets[dRs3Jets.begin()->second.first.second].p4()+jets[dRs3Jets.begin()->second.second].p4()).mass();

    int dRCounter = 1;
    for(std::list< std::pair< double, std::pair< unsigned int, unsigned int > > >::const_iterator dR = ++dRs.begin(); dR != dRs.end(); ++dR, ++dRCounter){

      if( (dR->second.first  != dRs.begin()->second.first) && (dR->second.first  != dRs.begin()->second.second) &&
	  (dR->second.second != dRs.begin()->second.first) && (dR->second.second != dRs.begin()->second.second) ){
	//dRMin2_ = dR->first;
	dRMin2Mass_ = (jets[dR->second.first].p4()+jets[dR->second.second].p4()).mass();
	//break;
      }

      if     (dRCounter==2) { dRMin2_ = dR->first; continue; }
      else if(dRCounter==3) { dRMin3_ = dR->first; continue; }
      else if(dRCounter==4) { dRMin4_ = dR->first; continue; }
      else if(dRCounter==5) { dRMin5_ = dR->first; continue; }
      else if(dRCounter==6) { dRMin6_ = dR->first; continue; }
    }
    
    for(std::list< std::pair< double, std::pair< std::pair< unsigned int, unsigned int >, unsigned int > > >::const_iterator dR = ++dRs3Jets.begin(); dR != dRs3Jets.end(); ++dR){
      if( (dR->second.first.first  != dRs3Jets.begin()->second.first.first) && (dR->second.first.first  != dRs3Jets.begin()->second.first.second) &&
	  (dR->second.first.second != dRs3Jets.begin()->second.first.first) && (dR->second.first.second != dRs3Jets.begin()->second.first.second) &&
	  (dR->second.first.first  != dRs3Jets.begin()->second.second)      && (dR->second.first.second != dRs3Jets.begin()->second.second)       ){
	sumDR3JetMin2_ = dR->first;
	sumDR3JetMin2Mass_ = (jets[dR->second.first.first].p4()+jets[dR->second.first.second].p4()+jets[dR->second.second].p4()).mass();
	break;
      }
    }
  }

  TCHP_Bjet_Discis.sort();
  SSV_Bjet_Discis.sort();
  CSV_Bjet_Discis.sort();
  //SM_Bjet_Discis.sort();
  
  unsigned int counter = 1;
  for(std::list< double >::const_reverse_iterator jet = TCHP_Bjet_Discis.rbegin(); jet != TCHP_Bjet_Discis.rend(); ++jet, ++counter){
    if     (counter == 1) TCHP_Bjet1_ = *jet;
    else if(counter == 2) TCHP_Bjet2_ = *jet;
    else if(counter == 3) TCHP_Bjet3_ = *jet;
    else if(counter == 4) TCHP_Bjet4_ = *jet;
    else if(counter == 5) TCHP_Bjet5_ = *jet;
    else if(counter == 6) TCHP_Bjet6_ = *jet;
  }

  counter = 1;
  for(std::list< double >::const_reverse_iterator jet = SSV_Bjet_Discis.rbegin(); jet != SSV_Bjet_Discis.rend(); ++jet, ++counter){
    if     (counter == 1) SSV_Bjet1_ = *jet;
    else if(counter == 2) SSV_Bjet2_ = *jet;
    else if(counter == 3) SSV_Bjet3_ = *jet;
    else if(counter == 4) SSV_Bjet4_ = *jet;
    else if(counter == 5) SSV_Bjet5_ = *jet;
    else if(counter == 6) SSV_Bjet6_ = *jet;
  }

  counter = 1;
  for(std::list< double >::const_reverse_iterator jet = CSV_Bjet_Discis.rbegin(); jet != CSV_Bjet_Discis.rend(); ++jet, ++counter){
    if     (counter == 1) CSV_Bjet1_ = *jet;
    else if(counter == 2) CSV_Bjet2_ = *jet;
    else if(counter == 3) CSV_Bjet3_ = *jet;
    else if(counter == 4) CSV_Bjet4_ = *jet;
    else if(counter == 5) CSV_Bjet5_ = *jet;
    else if(counter == 6) CSV_Bjet6_ = *jet;
  }

  //counter = 1;
  //for(std::list< double >::const_reverse_iterator jet = SM_Bjet_Discis.rbegin(); jet != SM_Bjet_Discis.rend(); ++jet, ++counter){
  //  if     (counter == 1) SM_Bjet1_ = *jet;
  //  else if(counter == 2) SM_Bjet2_ = *jet;
  //  else if(counter == 3) SM_Bjet3_ = *jet;
  //  else if(counter == 4) SM_Bjet4_ = *jet;
  //  else if(counter == 5) SM_Bjet5_ = *jet;
  //  else if(counter == 6) SM_Bjet6_ = *jet;
  //}
  
  if(jets.size() > 2){

    M3_ = (jets[0].p4() + jets[1].p4() + jets[2].p4()).mass();
  }

  fillValue("M3", M3_, weight);     
  fillValue("TCHP_Bjet1", TCHP_Bjet1_, weight); 
  fillValue("TCHP_Bjet2", TCHP_Bjet2_, weight); 
  fillValue("TCHP_Bjet3", TCHP_Bjet3_, weight); 
  fillValue("TCHP_Bjet4", TCHP_Bjet4_, weight); 
  fillValue("TCHP_Bjet5", TCHP_Bjet5_, weight); 
  fillValue("TCHP_Bjet6", TCHP_Bjet6_, weight); 
  fillValue("SSV_Bjet1", SSV_Bjet1_, weight);  
  fillValue("SSV_Bjet2", SSV_Bjet2_, weight);  
  fillValue("SSV_Bjet3", SSV_Bjet3_, weight);  
  fillValue("SSV_Bjet4", SSV_Bjet4_, weight);  
  fillValue("SSV_Bjet5", SSV_Bjet5_, weight);  
  fillValue("SSV_Bjet6", SSV_Bjet6_, weight);  
  fillValue("CSV_Bjet1", CSV_Bjet1_, weight);  
  fillValue("CSV_Bjet2", CSV_Bjet2_, weight);  
  fillValue("CSV_Bjet3", CSV_Bjet3_, weight);  
  fillValue("CSV_Bjet4", CSV_Bjet4_, weight);  
  fillValue("CSV_Bjet5", CSV_Bjet5_, weight);  
  fillValue("CSV_Bjet6", CSV_Bjet6_, weight);  
  //fillValue("SM_Bjet1", SM_Bjet1_, weight);   
  //fillValue("SM_Bjet2", SM_Bjet2_, weight);   
  //fillValue("SM_Bjet3", SM_Bjet3_, weight);   
  //fillValue("SM_Bjet4", SM_Bjet4_, weight);   
  //fillValue("SM_Bjet5", SM_Bjet5_, weight);   
  //fillValue("SM_Bjet6", SM_Bjet6_, weight);   
  fillValue("dRMin1", dRMin1_, weight);       
  fillValue("dRMin2", dRMin2_, weight);       
  fillValue("dRMin3", dRMin3_, weight);       
  fillValue("dRMin4", dRMin4_, weight);       
  fillValue("dRMin5", dRMin5_, weight);       
  fillValue("dRMin6", dRMin6_, weight);       
  fillValue("sumDR3JetMin1", sumDR3JetMin1_, weight); 
  fillValue("sumDR3JetMin2", sumDR3JetMin2_, weight); 
  fillValue("dRMin1Mass", dRMin1Mass_, weight);        
  fillValue("dRMin2Mass", dRMin2Mass_, weight);        
  fillValue("sumDR3JetMin1Mass", sumDR3JetMin1Mass_, weight);
  fillValue("sumDR3JetMin2Mass", sumDR3JetMin2Mass_, weight);

/**
   calculate di-jet and tri-jet masses
**/

  if(jets.size()>1){
    for(edm::View<pat::Jet>::const_iterator jet1 = jets.begin(); jet1 != --jets.end(); ++jet1) {
      edm::View<pat::Jet>::const_iterator jet1_value = jet1;
      for(edm::View<pat::Jet>::const_iterator jet2 = ++jet1_value; jet2 != jets.end(); ++jet2) {
	edm::View<pat::Jet>::const_iterator jet2_value = jet2;
	fillValue("mjj" , (jet1->p4() + jet2->p4()).mass(), weight );
	
	if(jets.size()>2 && !(jet2_value == jets.end())){
	  for(edm::View<pat::Jet>::const_iterator jet3 = ++jet2_value; jet3 != jets.end(); ++jet3) {
	    
	    fillValue("mjjj" , (jet1->p4() + jet2->p4() + jet3->p4()).mass(), weight );
	  }
	}
      }
    }
  }

  // fill the tree, if any variable should be put in
  if(treeVars_.size()) tree->Fill();

}
