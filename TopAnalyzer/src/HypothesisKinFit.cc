#include "TopAnalysis/TopAnalyzer/interface/HypothesisKinFit.h"
#include "AnalysisDataFormats/TopObjects/interface/TtSemiLepEvtPartons.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "TopQuarkAnalysis/TopObjectResolutions/interface/MET.h"
#include "TopQuarkAnalysis/TopObjectResolutions/interface/Jet.h"
#include "TopQuarkAnalysis/TopObjectResolutions/interface/Muon.h"
#include "TopQuarkAnalysis/TopObjectResolutions/interface/Electron.h"
/// default constructor for fw lite
HypothesisKinFit::HypothesisKinFit()
{
}

/// default constructor for full fw
HypothesisKinFit::HypothesisKinFit(const edm::ParameterSet& cfg) :
  hypoKey_( cfg.getParameter<std::string>("hypoKey") ),
  wantTree( cfg.getParameter<bool>("wantTree") )
{
}

/// histogramm booking for fwlite
void HypothesisKinFit::book()
{
  /**
     Monitoring Variables
   **/
  // fit probability of the best fit hypothesis
  hists_["prob"       ] = new TH1F( "prob"       , "prob"       ,   100,    0.,    1. );
  // chi2 of the best fit hypothesis
  hists_["chi2"       ] = new TH1F( "chi2"       , "chi2"       ,   100,    0.,   10. );
  // delta chi2 between best and second best fit hyothesis
  hists_["delChi2"    ] = new TH1F( "delChi2"    , "delChi2"    ,   100,    0.,   10. );
  // index n: (n+1)th leading jet 
  // difference of hadBQuark index between genMatch and kinFit
  hists_["hadBQuark"  ] = new TH1F( "hadBQuark"  , "hadBQuark"  ,     9,  -4.5,   4.5 );
  // difference of lepBQuark index between genMatch and kinFit
  hists_["lepBQuark"  ] = new TH1F( "lepBQuark"  , "lepBQuark"  ,     9,  -4.5,   4.5 );
  // smallest difference of the two lightQuark indices between genMatch and kinFit
  // (taking into accont that the two indices can be switched)
  hists_["lightQuark" ] = new TH1F( "lightQuark" , "lightQuark" ,     9,  -4.5,   4.5 );
  // number of quarks differing in the index between genMatch and the other hypothesis
  hists_["wrongAssign"] = new TH1F( "wrongAssign", "wrongAssign",     5,  -0.5,   4.5 );

  /**
     Pull Distributions muon, neutrino, jets (relative to the MC Truth)
  **/
  // hadronic top b pt
  hists_["hadBQuarkPt"  ] = new TH1F( "hadBQuarkPt"   , "hadBQuarkPt"    ,  100,  -5.,   5. );
  // hadronic top b eta
  hists_["hadBQuarkEta" ] = new TH1F( "hadBQuarkEta"  , "hadBQuarkEta"   ,  100,  -5.,   5. );
  // hadronic top b phi
  hists_["hadBQuarkPhi" ] = new TH1F( "hadBQuarkPhi"  , "hadBQuarkPhi"   ,  100,  -5.,   5. );
  // leptonic top b pt
  hists_["lepBQuarkPt"  ] = new TH1F( "lepBQuarkPt"   , "lepBQuarkPt"    ,  100,  -5.,   5. );
  // leptonic top b eta
  hists_["lepBQuarkEta" ] = new TH1F( "lepBQuarkEta"  , "lepBQuarkEta"   ,  100,  -5.,   5. );
  // leptonic top b phi
  hists_["lepBQuarkPhi" ] = new TH1F( "lepBQuarkPhi"  , "lepBQuarkPhi"   ,  100,  -5.,   5. );
  // lightQuark pt
  hists_["lightQuarkPt" ] = new TH1F( "lightQuarkPt"  , "lightQuarkPt"   ,  100,  -5.,   5. );
  // lightQuark b eta
  hists_["lightQuarkEta"] = new TH1F( "lightQuarkEta" , "lightQuarkEta"  ,  100,  -5.,   5. );
  // lightQuark b phi
  hists_["lightQuarkPhi"] = new TH1F( "lightQuarkPhi" , "lightQuarkPhi"  ,  100,  -5.,   5. );
  // lepton pt
  hists_["leptonPt"     ] = new TH1F( "leptonPt"      , "leptonPt"       ,  100,  -5.,   5. );
  // lepton eta
  hists_["leptonEta"    ] = new TH1F( "leptonEta"     , "leptonEta"      ,  100,  -5.,   5. );
  // lepton phi
  hists_["leptonPhi"    ] = new TH1F( "leptonPhi"     , "leptonPhi"      ,  100,  -5.,   5. );
  // neutrino pt
  hists_["neutrinoPt"   ] = new TH1F( "neutrinoPt"    , "neutrinoPt"     ,  100,  -5.,   5. );
  // neutrino eta
  hists_["neutrinoEta"  ] = new TH1F( "neutrinoEta"   , "neutrinoEta"    ,  100,  -5.,   5. );
  // neutrino phi
  hists_["neutrinoPhi"  ] = new TH1F( "neutrinoPhi"   , "neutrinoPhi"    ,  100,  -5.,   5. );
  // leptonic W pt
  hists_["lepWPt"       ] = new TH1F( "lepWPt"        , "lepWPt"         ,  100,  -5.,   5. );
  // leptonic W eta
  hists_["lepWEta"      ] = new TH1F( "lepWEta"       , "lepWEta"        ,  100,  -5.,   5. );
  // leptonic W phi
  hists_["lepWPhi"      ] = new TH1F( "lepWPhi"       , "lepWPhi"        ,  100,  -4.,   4. );
  // leptonic W mass
  hists_["lepWMass"     ] = new TH1F( "lepWMass"      , "lepWMass"       ,  400,  60.,   100. );
  // hadronic W pt
  hists_["hadWPt"       ] = new TH1F( "hadWPt"        , "hadWPt"         ,  100,  -5.,   5. );
  // hadronic W eta
  hists_["hadWEta"      ] = new TH1F( "hadWEta"       , "hadWEta"        ,  100,  -5.,   5. );
  // hadronic W phi
  hists_["hadWPhi"      ] = new TH1F( "hadWPhi"       , "hadWPhi"        ,  100,  -4.,   4. );
  // hadronic W mass
  hists_["hadWMass"     ] = new TH1F( "hadWMass"      , "hadWMass"       ,  400,  60.,   100. );
  // leptonic Top pt
  hists_["lepTopPt"     ] = new TH1F( "lepTopPt"      , "lepTopPt"       ,  100,  -5.,   5. );
  // leptonic Top eta
  hists_["lepTopEta"    ] = new TH1F( "lepTopEta"     , "lepTopEta"      ,  100,  -5.,   5. );
  // leptonic Top phi
  hists_["lepTopPhi"    ] = new TH1F( "lepTopPhi"     , "lepTopPhi"      ,  100,  -5.,   5. );
  // leptonic Top mass
  hists_["lepTopMass"   ] = new TH1F( "lepTopMass"    , "lepTopMass"     ,  400,  100.,  300. );
  // hadronic Top pt
  hists_["hadTopPt"     ] = new TH1F( "hadTopPt"      , "hadTopPt"       ,  100,  -5.,   5. );
  // hadronic Top eta
  hists_["hadTopEta"    ] = new TH1F( "hadTopEta"     , "hadTopEta"      ,  100,  -5.,   5. );
  // hadronic Top phi
  hists_["hadTopPhi"    ] = new TH1F( "hadTopPhi"     , "hadTopPhi"      ,  100,  -4.,   4. );
  /**
     Reconstructed Top Quantities
  **/
  // hadronic Top mass
  hists_["hadTopMass"   ] = new TH1F( "hadTopMass"    , "hadTopMass"     ,  400,  100.,  300. );
  // Top mass 2nd chi2
  hists_["TopMass2ndchi2"] = new TH1F( "TopMass2ndchi2", "TopMass2ndchi2",  500,   0., 500. );
  // Top mass 3rd chi2
  hists_["TopMass3rdchi2"] = new TH1F( "TopMass3rdchi2", "TopMass3rdchi2",  500,   0., 500. );
  // Top mass 4th chi2
  hists_["TopMass4thchi2"] = new TH1F( "TopMass4thchi2", "TopMass4thchi2",  500,   0., 500. );
  // Top mass 5th chi2
  hists_["TopMass5thchi2"] = new TH1F( "TopMass5thchi2", "TopMass5thchi2",  500,   0., 500. );
  // Top mass 6th chi2
  hists_["TopMass6thchi2"] = new TH1F( "TopMass6thchi2", "TopMass6thchi2",  500,   0., 500. );
  // Top mass 7th chi2
  hists_["TopMass7thchi2"] = new TH1F( "TopMass7thchi2", "TopMass7thchi2",  500,   0., 500. );
  // Top mass 8th chi2
  hists_["TopMass8thchi2"] = new TH1F( "TopMass8thchi2", "TopMass8thchi2",  500,   0., 500. );
  // Top mass 9th chi2
  hists_["TopMass9thchi2"] = new TH1F( "TopMass9thchi2", "TopMass9thchi2",  500,   0., 500. );
  // Top mass 10th chi2
  hists_["TopMass10thchi2"] = new TH1F( "TopMass10thchi2", "TopMass10thchi2",  500,   0., 500. );

  /**
     Correlation Plots
  **/
  // correlation between jet hypothesis and jet index
  corrs_["mapGenMatch_"    ] = new TH2F( "mapGenMatch_",  "mapGenMatch_",   4,  0.,  4.,  4,  0.,  4.);
  // correlation between jet hypothesis and jet index
  corrs_["mapKinFit_"      ] = new TH2F( "mapKinFit_"  ,  "mapKinFit_"  ,   4,  0.,  4.,  4,  0.,  4.);
}

/// histogramm booking for fw
void HypothesisKinFit::book(edm::Service<TFileService>& fs)
{
  /**
     Monitoring Variables
  **/
  // fit probability of the best fit hypothesis
  hists_["prob"       ] = fs->make<TH1F>( "prob"       , "prob"       ,   100,    0.,    1. );
  // chi2 of the best fit hypothesis
  hists_["chi2"       ] = fs->make<TH1F>( "chi2"       , "chi2"       ,   100,    0.,   10. );
  // delta chi2 between best and second best fit hyothesis
  hists_["delChi2"    ] = fs->make<TH1F>( "delChi2"    , "delChi2"    ,   100,    0.,   10. );
  // difference of hadBQuark index between genMatch and kinFit
  hists_["hadBQuark"  ] = fs->make<TH1F>( "hadBQuark"  , "hadBQuark"  ,     9,  -4.5,   4.5 );
  // difference of lepBQuark index between genMatch and kinFit
  hists_["lepBQuark"  ] = fs->make<TH1F>( "lepBQuark"  , "lepBQuark"  ,     9,  -4.5,   4.5 );
  // smallest difference of the two lightQuark indices between genMatch and kinFit
  // (taking into accont that the two indices can be switched)
  hists_["lightQuark" ] = fs->make<TH1F>( "lightQuark" , "lightQuark" ,     9,  -4.5,   4.5 );
  // number of quarks differing in the index between genMatch and the other hypothesis
  hists_["wrongAssign"] = fs->make<TH1F>( "wrongAssign", "wrongAssign",     5,  -0.5,   4.5 );

  /**
     Pull Distributions (Relative to the MC Truth)
  **/
  // hadronic top b pt
  hists_["hadBQuarkPt"   ] = fs->make<TH1F>( "hadBQuarkPt"    , "hadBQuarkPt"     ,  100,  -5.,   5. );
  // hadronic top b eta
  hists_["hadBQuarkEta"  ] = fs->make<TH1F>( "hadBQuarkEta"   , "hadBQuarkEta"    ,  100,  -5.,   5. );
  // hadronic top b phi
  hists_["hadBQuarkPhi"  ] = fs->make<TH1F>( "hadBQuarkPhi"   , "hadBQuarkPhi"    ,  100,  -5.,   5. );
  // leptonic top b pt
  hists_["lepBQuarkPt"   ] = fs->make<TH1F>( "lepBQuarkPt"    , "lepBQuarkPt"     ,  100,  -5.,   5. );
  // leptonic top b eta
  hists_["lepBQuarkEta"  ] = fs->make<TH1F>( "lepBQuarkEta"   , "lepBQuarkEta"    ,  100,  -5.,   5. );
  // leptonic top b phi
  hists_["lepBQuarkPhi"  ] = fs->make<TH1F>( "lepBQuarkPhi"   , "lepBQuarkPhi"    ,  100,  -5.,   5. );
  // lightQuark pt
  hists_["lightQuarkPt"  ] = fs->make<TH1F>( "lightQuarkPt"   , "lightQuarkPt"    ,  100,  -5.,   5. );
  // lightQuark b eta
  hists_["lightQuarkEta" ] = fs->make<TH1F>( "lightQuarkEta"  , "lightQuarkEta"   ,  100,  -5.,   5. );
  // lightQuark b phi
  hists_["lightQuarkPhi" ] = fs->make<TH1F>( "lightQuarkPhi"  , "lightQuarkPhi"   ,  100,  -5.,   5. );
  // lepton pt
  hists_["leptonPt"      ] = fs->make<TH1F>( "leptonPt"       , "leptonPt"        ,  100,  -5.,   5. );
  // lepton eta
  hists_["leptonEta"     ] = fs->make<TH1F>( "leptonEta"      , "leptonEta"       ,  100,  -5.,   5. );
  // lepton phi
  hists_["leptonPhi"     ] = fs->make<TH1F>( "leptonPhi"      , "leptonPhi"       ,  100,  -5.,   5. );
  // neutrino pt
  hists_["neutrinoPt"    ] = fs->make<TH1F>( "neutrinoPt"     , "neutrinoPt"      ,  100,  -5.,   5. );
  // neutrino eta
  hists_["neutrinoEta"   ] = fs->make<TH1F>( "neutrinoEta"    , "neutrinoEta"     ,  100,  -5.,   5. );
  // neutrino phi
  hists_["neutrinoPhi"   ] = fs->make<TH1F>( "neutrinoPhi"    , "neutrinoPhi"     ,  100,  -5.,   5. );
  // leptonic W pt
  hists_["lepWPt"        ] = fs->make<TH1F>( "lepWPt"         , "lepWPt"          ,  100,  -5.,   5. );
  // leptonic W eta
  hists_["lepWEta"       ] = fs->make<TH1F>( "lepWEta"        , "lepWEta"         ,  100,  -5.,   5. );
  // leptonic W phi
  hists_["lepWPhi"       ] = fs->make<TH1F>( "lepWPhi"        , "lepWPhi"         ,  100,  -4.,   4. );
  // leptonic W mass
  hists_["lepWMass"      ] = fs->make<TH1F>( "lepWMass"       , "lepWMass"        ,  400,  60., 100. );
  // hadronic W pt
  hists_["hadWPt"        ] = fs->make<TH1F>( "hadWPt"         , "hadWPt"          ,  100,  -5.,   5. );
  // hadronic W eta
  hists_["hadWEta"       ] = fs->make<TH1F>( "hadWEta"        , "hadWEta"         ,  100,  -5.,   5. );
  // hadronic W phi
  hists_["hadWPhi"       ] = fs->make<TH1F>( "hadWPhi"        , "hadWPhi"         ,  100,  -4.,   4. );
  // hadronic W mass
  hists_["hadWMass"      ] = fs->make<TH1F>( "hadWMass"       , "hadWMass"        ,  400,  60., 100. );
  // leptonic Top pt
  hists_["lepTopPt"      ] = fs->make<TH1F>( "lepTopPt"       , "lepTopPt"        ,  100,  -5.,   5. );
  // leptonic Top eta
  hists_["lepTopEta"     ] = fs->make<TH1F>( "lepTopEta"      , "lepTopEta"       ,  100,  -5.,   5. );
  // leptonic Top phi
  hists_["lepTopPhi"     ] = fs->make<TH1F>( "lepTopPhi"      , "lepTopPhi"       ,  100,  -4.,   4. );
  // leptonic Top mass
  hists_["lepTopMass"    ] = fs->make<TH1F>( "lepTopMass"     , "lepTopMass"      ,  500,   0., 500. );
  // hadronic Top pt
  hists_["hadTopPt"      ] = fs->make<TH1F>( "hadTopPt"       , "hadTopPt"        ,  100,  -5.,   5. );
  // hadronic Top eta
  hists_["hadTopEta"     ] = fs->make<TH1F>( "hadTopEta"      , "hadTopEta"       ,  100,  -5.,   5. );
  // hadronic Top phi
  hists_["hadTopPhi"     ] = fs->make<TH1F>( "hadTopPhi"      , "hadTopPhi"       ,  100,  -4.,   4. );
  // hadronic Top mass
  hists_["hadTopMass"    ] = fs->make<TH1F>( "hadTopMass"     , "hadTopMass"      ,  500,   0., 500. );
  // Top mass 2nd chi2
  hists_["TopMass2ndchi2"] = fs->make<TH1F>( "TopMass2ndchi2" , "TopMass2ndchi2"  ,  500,   0., 500. );
  // Top mass 3rd chi2
  hists_["TopMass3rdchi2"] = fs->make<TH1F>( "TopMass3rdchi2" , "TopMass3rdchi2"  ,  500,   0., 500. );
  // Top mass 4th chi2
  hists_["TopMass4thchi2"] = fs->make<TH1F>( "TopMass4thchi2" , "TopMass4thchi2"  ,  500,   0., 500. );
  // Top mass 5th chi2
  hists_["TopMass5thchi2"] = fs->make<TH1F>( "TopMass5thchi2" , "TopMass5thchi2"  ,  500,   0., 500. );
  // Top mass 6th chi2
  hists_["TopMass6thchi2"] = fs->make<TH1F>( "TopMass6thchi2" , "TopMass6thchi2"  ,  500,   0., 500. );
  // Top mass 7th chi2
  hists_["TopMass7thchi2"] = fs->make<TH1F>( "TopMass7thchi2" , "TopMass7thchi2"  ,  500,   0., 500. );
  // Top mass 8th chi2
  hists_["TopMass8thchi2"] = fs->make<TH1F>( "TopMass8thchi2" , "TopMass8thchi2"  ,  500,   0., 500. );
  // Top mass 9th chi2
  hists_["TopMass9thchi2"] = fs->make<TH1F>( "TopMass9thchi2" , "TopMass9thchi2"  ,  500,   0., 500. );
  // Top mass 10th chi2
  hists_["TopMass10thchi2"]= fs->make<TH1F>( "TopMass10thchi2", "TopMass10thchi2" ,  500,   0., 500. );
  /**
     Correlation Plots
  **/
  // correlation between jet hypothesis (genmatched objects) and jet index MC truth
  corrs_["mapGenMatch_"    ] = fs->make<TH2F>( "mapGenMatch_",  "mapGenMatch_",   4,  0.,  4.,  4,  0.,  4.);
  // correlation between jet hypothesis (reconstructed objects) and jet index MC truth
  corrs_["mapKinFit_"      ] = fs->make<TH2F>( "mapKinFit_"  ,  "mapKinFit_"  ,   4,  0.,  4.,  4,  0.,  4.);

  if(wantTree){
    /**
       make Tree with all variables
    **/
    tree = fs->make<TTree>("Hypothesistree","Hypothesistree",0);
    tree->Branch("numberOfDifferingIndices", &numberOfDifferingIndices, "numberOfDifferingIndices/I");
    tree->Branch("hadBIndexDiff", &hadBIndexDiff, "hadBIndexDiff/I");
    tree->Branch("lepBIndexDiff", &lepBIndexDiff, "lepBIndexDiff/I");
    tree->Branch("lepBIndex", &lepBIndex, "lepBIndex/I");
    tree->Branch("hadBIndex", &hadBIndex, "hadBIndex/I");
    tree->Branch("lightQIndex", &lightQIndex, "lightQIndex/I");
    tree->Branch("lightQBarIndex", &lightQBarIndex, "lightQBarIndex/I");
    tree->Branch("lepBIndexGen", &lepBIndexGen, "lepBIndexGen/I");
    tree->Branch("hadBIndexGen", &hadBIndexGen, "hadBIndexGen/I");
    tree->Branch("lightQIndexGen", &lightQIndexGen, "lightQIndexGen/I");
    tree->Branch("lightQBarIndexGen", &lightQBarIndexGen, "lightQBarIndexGen/I");
    tree->Branch("lightQIndexDiff", &lightQIndexDiff, "lightQIndexDiff/I");
    tree->Branch("lightQBarIndexDiff", &lightQBarIndexDiff, "lightQBarIndexDiff/I");
    tree->Branch("hadTopMass", &hadTopMass, "hadTopMass/F");
    tree->Branch("lepTopMass", &lepTopMass, "lepTopMass/F");
    tree->Branch("TopMass2ndchi2", &TopMass2ndchi2, "TopMass2ndchi2/F");
    tree->Branch("TopMass3rdchi2", &TopMass3rdchi2, "TopMass3rdchi2/F");
    tree->Branch("TopMass4thchi2", &TopMass4thchi2, "TopMass4thchi2/F");
    tree->Branch("TopMass5thchi2", &TopMass5thchi2, "TopMass5thchi2/F");
    tree->Branch("TopMass6thchi2", &TopMass6thchi2, "TopMass6thchi2/F");
    tree->Branch("TopMass7thchi2", &TopMass7thchi2, "TopMass7thchi2/F");
    tree->Branch("TopMass8thchi2", &TopMass8thchi2, "TopMass8thchi2/F");
    tree->Branch("TopMass9thchi2", &TopMass9thchi2, "TopMass9thchi2/F");
    tree->Branch("TopMass10thchi2", &TopMass10thchi2, "TopMass10thchi2/F");
    tree->Branch("hadWMass", &hadWMass, "hadWMass/F");
    tree->Branch("lepWMass", &lepWMass, "lepWMass/F");
    if(hypoKey_ == "kKinFit" ){
      tree->Branch("prob", &prob, "prob/F");
      tree->Branch("chi2", &chi2, "chi2/F");
      tree->Branch("delChi2", &delChi2, "delChi2/F");
    }
    tree->Branch("numberOfDifferingIndicesKinFit", &numberOfDifferingIndicesKinFit, "numberOfDifferingIndicesKinFit/I");
    tree->Branch("hadBIndexDiffKinFit", &hadBIndexDiffKinFit, "hadBIndexDiffKinFit/I");
    tree->Branch("lepBIndexDiffKinFit", &lepBIndexDiffKinFit, "lepBIndexDiffKinFit/I");
    tree->Branch("lightQIndexDiffKinFit", &lightQIndexDiffKinFit, "lightQIndexDiffKinFit/I");
    tree->Branch("lightQBarIndexDiffKinFit", &lightQBarIndexDiffKinFit, "lightQBarIndexDiffKinFit/I");
    tree->Branch("hadTopMassKinFit", &hadTopMassKinFit, "hadTopMassKinFit/F");
    tree->Branch("lepTopMassKinFit", &lepTopMassKinFit, "lepTopMassKinFit/F");
    tree->Branch("hadWMassKinFit",   &hadWMassKinFit,   "hadWMassKinFit/F");
    tree->Branch("lepWMassKinFit",   &lepWMassKinFit,   "lepWMassKinFit/F");
    tree->Branch("lepBpt_gen",       &lepBpt_gen,       "lepBpt_gen/F");
    tree->Branch("lepBphi_gen",      &lepBphi_gen,      "lepBphi_gen");          
    tree->Branch("lepBeta_gen",      &lepBeta_gen,      "lepBeta_gen");          
    tree->Branch("hadBpt_gen",       &hadBpt_gen,       "hadBpt_gen");          
    tree->Branch("hadBphi_gen",      &hadBphi_gen,      "hadBphi_gen");          
    tree->Branch("hadBeta_gen",      &hadBeta_gen,      "hadBeta_gen");          
    tree->Branch("lightQpt_gen",     &lightQpt_gen,     "lightQpt_gen");          
    tree->Branch("lightQphi_gen",    &lightQphi_gen,    "lightQphi_gen");           
    tree->Branch("lightQeta_gen",    &lightQeta_gen,    "lightQeta_gen");           
    tree->Branch("lightQBarpt_gen",  &lightQBarpt_gen,  "lightQBarpt_gen");      
    tree->Branch("lightQBarphi_gen", &lightQBarphi_gen, "lightQBarphi_gen");      
    tree->Branch("lightQBareta_gen", &lightQBareta_gen, "lightQBareta_gen");      
    tree->Branch("leptonpt_gen",     &leptonpt_gen,     "leptonpt_gen");          
    tree->Branch("leptonphi_gen",    &leptonphi_gen,    "leptonphi_gen");           
    tree->Branch("leptoneta_gen",    &leptoneta_gen,    "leptoneta_gen");           
    tree->Branch("neutrinopt_gen",   &neutrinopt_gen,   "neutrinopt_gen");
    tree->Branch("neutrinophi_gen",  &neutrinophi_gen,  "neutrinophi_gen");       
    tree->Branch("neutrinoeta_gen",  &neutrinoeta_gen,  "neutrinoeta_gen");       
    tree->Branch("lepWpt_gen",       &lepWpt_gen,       "lepWpt_gen");          
    tree->Branch("lepWphi_gen",      &lepWphi_gen,      "lepWphi_gen");          
    tree->Branch("lepWeta_gen",      &lepWeta_gen,      "lepWeta_gen");          
    tree->Branch("hadWpt_gen",       &hadWpt_gen,       "hadWpt_gen");          
    tree->Branch("hadWphi_gen",      &hadWphi_gen,      "hadWphi_gen");          
    tree->Branch("hadWeta_gen",      &hadWeta_gen,      "hadWeta_gen");          
    tree->Branch("lepToppt_gen",     &lepToppt_gen,     "lepToppt_gen");           
    tree->Branch("lepTopphi_gen",    &lepTopphi_gen,    "lepTopphi_gen");           
    tree->Branch("lepTopeta_gen",    &lepTopeta_gen,    "lepTopeta_gen");
    tree->Branch("lepTopY_gen",      &lepTopY_gen,      "lepTopY_gen");
    tree->Branch("hadToppt_gen",     &hadToppt_gen,     "hadToppt_gen");           
    tree->Branch("hadTopphi_gen",    &hadTopphi_gen,    "hadTopphi_gen");           
    tree->Branch("hadTopeta_gen",    &hadTopeta_gen,    "hadTopeta_gen");
    tree->Branch("hadTopY_gen",      &hadTopY_gen,      "hadTopY_gen");
    tree->Branch("ttBarpt_gen",      &ttBarpt_gen,      "ttBarpt_gen");           
    tree->Branch("ttBarphi_gen",     &ttBarphi_gen,     "ttBarphi_gen");          
    tree->Branch("ttBareta_gen",     &ttBareta_gen,     "ttBareta_gen");
    tree->Branch("ttBarY_gen",       &ttBarY_gen,       "ttBarY_gen");
    tree->Branch("ttBarMass_gen",    &ttBarMass_gen,    "ttBarMass_gen");
    tree->Branch("ttBarDelPhi_gen",  &ttBarDelPhi_gen,  "ttBarDelPhi_gen");
    tree->Branch("ttBarDelY_gen",    &ttBarDelY_gen,    "ttBarDelY_gen");
    tree->Branch("ttBarSumY_gen",    &ttBarSumY_gen,    "ttBarSumY_gen");
    tree->Branch("lepBpt_fit",       &lepBpt_fit,       "lepBpt_fit");         
    tree->Branch("lepBphi_fit",      &lepBphi_fit,      "lepBphi_fit");          
    tree->Branch("lepBeta_fit",      &lepBeta_fit,      "lepBeta_fit");          
    tree->Branch("hadBpt_fit",       &hadBpt_fit,       "hadBpt_fit");          
    tree->Branch("hadBphi_fit",      &hadBphi_fit,      "hadBphi_fit");          
    tree->Branch("hadBeta_fit",      &hadBeta_fit,      "hadBeta_fit");          
    tree->Branch("lightQpt_fit",     &lightQpt_fit,     "lightQpt_fit");          
    tree->Branch("lightQphi_fit",    &lightQphi_fit,    "lightQphi_fit");           
    tree->Branch("lightQeta_fit",    &lightQeta_fit,    "lightQeta_fit");           
    tree->Branch("lightQBarpt_fit",  &lightQBarpt_fit,  "lightQBarpt_fit");       
    tree->Branch("lightQBarphi_fit", &lightQBarphi_fit, "lightQBarphi_fit");      
    tree->Branch("lightQBareta_fit", &lightQBareta_fit, "lightQBareta_fit");      
    tree->Branch("leptonpt_fit",     &leptonpt_fit,     "leptonpt_fit");          
    tree->Branch("leptonphi_fit",    &leptonphi_fit,    "leptonphi_fit");           
    tree->Branch("leptoneta_fit",    &leptoneta_fit,    "leptoneta_fit");           
    tree->Branch("neutrinopt_fit",   &neutrinopt_fit,   "neutrinopt_fit");
    tree->Branch("neutrinophi_fit",  &neutrinophi_fit,  "neutrinophi_fit");       
    tree->Branch("neutrinoeta_fit",  &neutrinoeta_fit,  "neutrinoeta_fit");       
    tree->Branch("lepWpt_fit",       &lepWpt_fit,       "lepWpt_fit");          
    tree->Branch("lepWphi_fit",      &lepWphi_fit,      "lepWphi_fit");          
    tree->Branch("lepWeta_fit",      &lepWeta_fit,      "lepWeta_fit");          
    tree->Branch("hadWpt_fit",       &hadWpt_fit,       "hadWpt_fit");          
    tree->Branch("hadWphi_fit",      &hadWphi_fit,      "hadWphi_fit");          
    tree->Branch("hadWeta_fit",      &hadWeta_fit,      "hadWeta_fit");          
    tree->Branch("lepToppt_fit",     &lepToppt_fit,     "lepToppt_fit");           
    tree->Branch("lepTopphi_fit",    &lepTopphi_fit,    "lepTopphi_fit");           
    tree->Branch("lepTopeta_fit",    &lepTopeta_fit,    "lepTopeta_fit");
    tree->Branch("lepTopY_fit",      &lepTopY_fit,      "lepTopY_fit");
    tree->Branch("hadToppt_fit",     &hadToppt_fit,     "hadToppt_fit");           
    tree->Branch("hadTopphi_fit",    &hadTopphi_fit,    "hadTopphi_fit");           
    tree->Branch("hadTopeta_fit",    &hadTopeta_fit,    "hadTopeta_fit");
    tree->Branch("hadTopY_fit",      &hadTopY_fit,      "hadTopY_fit");
    tree->Branch("ttBarpt_fit",      &ttBarpt_fit,      "ttBarpt_fit");           
    tree->Branch("ttBarphi_fit",     &ttBarphi_fit,     "ttBarphi_fit");          
    tree->Branch("ttBareta_fit",     &ttBareta_fit,     "ttBareta_fit");
    tree->Branch("ttBarY_fit",       &ttBarY_fit,       "ttBarY_fit");
    tree->Branch("ttBarMass_fit",    &ttBarMass_fit,    "ttBarMass_fit");
    tree->Branch("ttBarDelPhi_fit",  &ttBarDelPhi_fit,  "ttBarDelPhi_fit");
    tree->Branch("ttBarDelY_fit",    &ttBarDelY_fit,    "ttBarDelY_fit");
    tree->Branch("ttBarSumY_fit",    &ttBarSumY_fit,    "ttBarSumY_fit");
  }
}

/// calculating difference of object indices in the reco collections between the genMatch and kinFit hypotheses
int
HypothesisKinFit::delObjectIndex(const TtSemiLeptonicEvent& tops, const int& index, const std::string& myHypoKey)
{
  // a) calculate differences for indeces of reconstructed and genmatched quarks light quarks
  // name convention: "del"+genmatchQuark+recoQuark
  int delLightQQ       = objectIndex(tops, "kGenMatch", TtSemiLepEvtPartons::LightQ   )-objectIndex(tops, myHypoKey, TtSemiLepEvtPartons::LightQ   );
  int delLightQBarQBar = objectIndex(tops, "kGenMatch", TtSemiLepEvtPartons::LightQBar)-objectIndex(tops, myHypoKey, TtSemiLepEvtPartons::LightQBar);
  int delLightQQBar    = objectIndex(tops, "kGenMatch", TtSemiLepEvtPartons::LightQ   )-objectIndex(tops, myHypoKey, TtSemiLepEvtPartons::LightQBar);
  int delLightQBarQ    = objectIndex(tops, "kGenMatch", TtSemiLepEvtPartons::LightQBar)-objectIndex(tops, myHypoKey, TtSemiLepEvtPartons::LightQ   );
  // b) test if q and qbar are swopped in Hypothesis	    
  // because kinfit can not destinguish between them
  // implementation: ask if index for q or qbar is closer to q gen truth 
  bool switchRecoQQBar=true;
  if(std::min(abs(delLightQQ), abs(delLightQBarQBar)) < std::min(abs(delLightQQBar), abs(delLightQBarQ))) switchRecoQQBar=false;
  // c) return index difference
  // light q
  if     (index==TtSemiLepEvtPartons::LightQ   ) return switchRecoQQBar ? delLightQQBar : delLightQQ;
  // light qbar
  else if(index==TtSemiLepEvtPartons::LightQBar) return switchRecoQQBar ? delLightQBarQ : delLightQBarQBar;
  // other
  else return objectIndex(tops, "kGenMatch", index)-objectIndex(tops, myHypoKey, index);
}

/// histogram filling interface for reconstruction level for access with fwlite or full framework
void
HypothesisKinFit::fill(const TtSemiLeptonicEvent& tops, const double& weight)
{  
  //std::cout << "is default (" << hypoKey_ << ") hypo valid? " << tops.isHypoValid(hypoKey_) << std::endl;
  //std::cout << "genmatch hypo valid? " << tops.isHypoValid("kGenMatch") << std::endl;
  //std::cout << "KinFit hypo valid? " << tops.isHypoValid("kKinFit") << std::endl;

  /**
     Fill the Monitoring Variables
  **/
  // make sure to have a valid hypothesis on reconstruction level
  // and an existing genmatch
  if( tops.isHypoValid(hypoKey_)&& tops.isHypoValid("kGenMatch")){
    // if kinFit is the hypothesis, fill KinFit quantities 
    if(hypoKey_ == "kKinFit" ){
      // fit probability of the best fit hypothesis
      hists_.find("prob")->second->Fill( tops.fitProb(), weight );
      prob=tops.fitProb();
      // chi2 of the best fit hypothesis
      hists_.find("chi2")->second->Fill( tops.fitChi2(), weight );      
      chi2=tops.fitChi2();
      // make sure that a second best fit hypothesis exists to be able to fill these plots
      delChi2=100;
      if( tops.fitChi2(1) >= 0 ){
	// delta chi2 between best and second best fit hyothesis
	hists_.find("delChi2")->second->Fill( tops.fitChi2(1)-tops.fitChi2(0), weight);
	delChi2=tops.fitChi2(1)-tops.fitChi2(0);
      }
    }
    // indices for all quarks from Kinfit Hypothesis and genmatch
    lepBIndex         = tops.jetLeptonCombination(hypoKey_   )[TtSemiLepEvtPartons::LepB     ];
    hadBIndex         = tops.jetLeptonCombination(hypoKey_   )[TtSemiLepEvtPartons::HadB     ];
    lightQIndex       = tops.jetLeptonCombination(hypoKey_   )[TtSemiLepEvtPartons::LightQ   ];
    lightQBarIndex    = tops.jetLeptonCombination(hypoKey_   )[TtSemiLepEvtPartons::LightQBar];
    lepBIndexGen      = tops.jetLeptonCombination("kGenMatch")[TtSemiLepEvtPartons::LepB     ];
    hadBIndexGen      = tops.jetLeptonCombination("kGenMatch")[TtSemiLepEvtPartons::HadB     ];
    lightQIndexGen    = tops.jetLeptonCombination("kGenMatch")[TtSemiLepEvtPartons::LightQ   ];
    lightQBarIndexGen = tops.jetLeptonCombination("kGenMatch")[TtSemiLepEvtPartons::LightQBar];
    // difference of hadBQuark index between genMatch and kinFit
    hadBIndexDiff = delObjectIndex(tops, TtSemiLepEvtPartons::HadB, hypoKey_);
    if(tops.isHypoValid("kKinFit"))hadBIndexDiffKinFit = delObjectIndex(tops, TtSemiLepEvtPartons::HadB, "kKinFit");
    else hadBIndexDiffKinFit = -10;
    hists_.find("hadBQuark" )->second->Fill( hadBIndexDiff, weight);
    // difference of lepBQuark index between genMatch and kinFit
    lepBIndexDiff = delObjectIndex(tops, TtSemiLepEvtPartons::LepB, hypoKey_);
    if(tops.isHypoValid("kKinFit"))lepBIndexDiffKinFit = delObjectIndex(tops, TtSemiLepEvtPartons::LepB, "kKinFit");
    else lepBIndexDiffKinFit = -10;
    hists_.find("lepBQuark" )->second->Fill( lepBIndexDiff, weight);
    // smallest difference of the two lightQuark indices between genMatch and kinFit
    // (taking into account that the two indices can be switched)
    lightQIndexDiff    = delObjectIndex(tops, TtSemiLepEvtPartons::LightQ   , hypoKey_);
    lightQBarIndexDiff = delObjectIndex(tops, TtSemiLepEvtPartons::LightQBar, hypoKey_);
    if(tops.isHypoValid("kKinFit"))lightQIndexDiffKinFit    = delObjectIndex(tops, TtSemiLepEvtPartons::LightQ   , "kKinFit");
    else lightQIndexDiffKinFit = -10;
    if(tops.isHypoValid("kKinFit"))lightQBarIndexDiffKinFit = delObjectIndex(tops, TtSemiLepEvtPartons::LightQBar, "kKinFit");
    else lightQBarIndexDiffKinFit = -10;
    hists_.find("lightQuark")->second->Fill( lightQIndexDiff,    weight);
    hists_.find("lightQuark")->second->Fill( lightQBarIndexDiff, weight);
    // number of quarks differing in the index between genMatch and the other hypothesis
    // a) for choosen Hypothesis hypoKey_
    numberOfDifferingIndices = 0;
    if(delObjectIndex(tops, TtSemiLepEvtPartons::HadB     , hypoKey_))numberOfDifferingIndices++;
    if(delObjectIndex(tops, TtSemiLepEvtPartons::LepB     , hypoKey_))numberOfDifferingIndices++;
    if(delObjectIndex(tops, TtSemiLepEvtPartons::LightQ   , hypoKey_))numberOfDifferingIndices++;
    if(delObjectIndex(tops, TtSemiLepEvtPartons::LightQBar, hypoKey_))numberOfDifferingIndices++;
    hists_.find("wrongAssign")->second->Fill( numberOfDifferingIndices, weight);
    // b) for KinFit result
    numberOfDifferingIndicesKinFit = -1;
    if(tops.isHypoValid("kKinFit")){
      numberOfDifferingIndicesKinFit = 0;
      if(delObjectIndex(tops, TtSemiLepEvtPartons::HadB     , "kKinFit"))numberOfDifferingIndicesKinFit++;
      if(delObjectIndex(tops, TtSemiLepEvtPartons::LepB     , "kKinFit"))numberOfDifferingIndicesKinFit++;
      if(delObjectIndex(tops, TtSemiLepEvtPartons::LightQ   , "kKinFit"))numberOfDifferingIndicesKinFit++;
      if(delObjectIndex(tops, TtSemiLepEvtPartons::LightQBar, "kKinFit"))numberOfDifferingIndicesKinFit++;
      if( tops.leptonicDecayTop("kKinFit",1) )TopMass2ndchi2 =tops.leptonicDecayTop("kKinFit",1)->mass();
      if( tops.leptonicDecayTop("kKinFit",2) )TopMass3rdchi2 =tops.leptonicDecayTop("kKinFit",2)->mass();
      if( tops.leptonicDecayTop("kKinFit",3) )TopMass4thchi2 =tops.leptonicDecayTop("kKinFit",3)->mass();
      if( tops.leptonicDecayTop("kKinFit",4) )TopMass5thchi2 =tops.leptonicDecayTop("kKinFit",4)->mass();
      if( tops.leptonicDecayTop("kKinFit",5) )TopMass6thchi2 =tops.leptonicDecayTop("kKinFit",5)->mass();
      if( tops.leptonicDecayTop("kKinFit",6) )TopMass7thchi2 =tops.leptonicDecayTop("kKinFit",6)->mass();
      if( tops.leptonicDecayTop("kKinFit",7) )TopMass8thchi2 =tops.leptonicDecayTop("kKinFit",7)->mass();
      if( tops.leptonicDecayTop("kKinFit",8) )TopMass9thchi2 =tops.leptonicDecayTop("kKinFit",8)->mass();
      if( tops.leptonicDecayTop("kKinFit",9) )TopMass10thchi2=tops.leptonicDecayTop("kKinFit",9)->mass();
      hists_.find("TopMass2ndchi2")->second->Fill( TopMass2ndchi2 );
      hists_.find("TopMass3rdchi2")->second->Fill( TopMass3rdchi2 );
      hists_.find("TopMass4thchi2")->second->Fill( TopMass4thchi2 );
      hists_.find("TopMass5thchi2")->second->Fill( TopMass5thchi2 );
      hists_.find("TopMass6thchi2")->second->Fill( TopMass6thchi2 );
      hists_.find("TopMass7thchi2")->second->Fill( TopMass7thchi2 );
      hists_.find("TopMass8thchi2")->second->Fill( TopMass8thchi2 );
      hists_.find("TopMass9thchi2")->second->Fill( TopMass9thchi2 );
      hists_.find("TopMass10thchi2")->second->Fill( TopMass10thchi2 );
    }
    // object kinematics 
    // a) for gen objects
    lepBpt_gen =       tops.leptonicDecayB()->pt();
    lepBphi_gen =      tops.leptonicDecayB()->phi();
    lepBeta_gen =      tops.leptonicDecayB()->eta();
    hadBpt_gen =       tops.hadronicDecayB()->pt();
    hadBphi_gen =      tops.hadronicDecayB()->phi();
    hadBeta_gen =      tops.hadronicDecayB()->eta();
    lightQpt_gen =     tops.hadronicDecayQuark()->pt();
    lightQphi_gen =    tops.hadronicDecayQuark()->phi();
    lightQeta_gen =    tops.hadronicDecayQuark()->eta();
    lightQBarpt_gen =  tops.hadronicDecayQuarkBar()->pt();
    lightQBarphi_gen = tops.hadronicDecayQuarkBar()->phi();
    lightQBareta_gen = tops.hadronicDecayQuarkBar()->eta();
    leptonpt_gen =     tops.singleLepton()->pt();
    leptonphi_gen =    tops.singleLepton()->phi();
    leptoneta_gen =    tops.singleLepton()->eta();
    neutrinopt_gen =   tops.singleNeutrino()->pt();
    neutrinophi_gen =  tops.singleNeutrino()->phi();
    neutrinoeta_gen =  tops.singleNeutrino()->eta();
    lepWpt_gen =       tops.leptonicDecayW()->pt();
    lepWphi_gen =      tops.leptonicDecayW()->phi();
    lepWeta_gen =      tops.leptonicDecayW()->eta();
    hadWpt_gen =       tops.hadronicDecayW()->pt();
    hadWphi_gen =      tops.hadronicDecayW()->phi();
    hadWeta_gen =      tops.hadronicDecayW()->eta();
    lepToppt_gen  =    tops.leptonicDecayTop()->pt();
    lepTopphi_gen =    tops.leptonicDecayTop()->phi();
    lepTopeta_gen =    tops.leptonicDecayTop()->eta();
    lepTopY_gen =      tops.leptonicDecayTop()->rapidity();
    hadToppt_gen =     tops.hadronicDecayTop()->pt();
    hadTopphi_gen =    tops.hadronicDecayTop()->phi();
    hadTopeta_gen =    tops.hadronicDecayTop()->eta();
    hadTopY_gen =      tops.hadronicDecayTop()->rapidity();
    ttBarpt_gen =      (tops.leptonicDecayTop()->p4()+tops.hadronicDecayTop()->p4()).pt();
    ttBarphi_gen =     (tops.leptonicDecayTop()->p4()+tops.hadronicDecayTop()->p4()).phi();
    ttBareta_gen =     (tops.leptonicDecayTop()->p4()+tops.hadronicDecayTop()->p4()).eta();
    ttBarY_gen =       (tops.leptonicDecayTop()->p4()+tops.hadronicDecayTop()->p4()).Rapidity();
    ttBarMass_gen =    (tops.leptonicDecayTop()->p4()+tops.hadronicDecayTop()->p4()).mass();
    ttBarDelPhi_gen =  deltaPhi(tops.leptonicDecayTop()->phi(), tops.hadronicDecayTop()->phi());
    ttBarDelY_gen =    tops.leptonicDecayTop()->rapidity()-tops.hadronicDecayTop()->rapidity();
    ttBarSumY_gen =    tops.leptonicDecayTop()->rapidity()+tops.hadronicDecayTop()->rapidity();
    // b) for Reconstruction Hypothesis
    lepBpt_fit =       tops.leptonicDecayB       (hypoKey_)->pt();
    lepBphi_fit =      tops.leptonicDecayB       (hypoKey_)->phi();
    lepBeta_fit =      tops.leptonicDecayB       (hypoKey_)->eta();
    hadBpt_fit =       tops.hadronicDecayB       (hypoKey_)->pt();
    hadBphi_fit =      tops.hadronicDecayB       (hypoKey_)->phi();
    hadBeta_fit =      tops.hadronicDecayB       (hypoKey_)->eta();
    lightQpt_fit =     tops.hadronicDecayQuark   (hypoKey_)->pt();
    lightQphi_fit =    tops.hadronicDecayQuark   (hypoKey_)->phi();
    lightQeta_fit =    tops.hadronicDecayQuark   (hypoKey_)->eta();
    lightQBarpt_fit =  tops.hadronicDecayQuarkBar(hypoKey_)->pt();
    lightQBarphi_fit = tops.hadronicDecayQuarkBar(hypoKey_)->phi();
    lightQBareta_fit = tops.hadronicDecayQuarkBar(hypoKey_)->eta();
    leptonpt_fit =     tops.singleLepton         (hypoKey_)->pt();
    leptonphi_fit =    tops.singleLepton         (hypoKey_)->phi();
    leptoneta_fit =    tops.singleLepton         (hypoKey_)->eta();
    neutrinopt_fit =   tops.singleNeutrino       (hypoKey_)->pt();
    neutrinophi_fit =  tops.singleNeutrino       (hypoKey_)->phi();
    neutrinoeta_fit =  tops.singleNeutrino       (hypoKey_)->eta();
    lepWpt_fit =       tops.leptonicDecayW       (hypoKey_)->pt();
    lepWphi_fit =      tops.leptonicDecayW       (hypoKey_)->phi();
    lepWeta_fit =      tops.leptonicDecayW       (hypoKey_)->eta();
    hadWpt_fit =       tops.hadronicDecayW       (hypoKey_)->pt();
    hadWphi_fit =      tops.hadronicDecayW       (hypoKey_)->phi();
    hadWeta_fit =      tops.hadronicDecayW       (hypoKey_)->eta();
    lepToppt_fit =     tops.leptonicDecayTop     (hypoKey_)->pt();
    lepTopphi_fit =    tops.leptonicDecayTop     (hypoKey_)->phi();
    lepTopeta_fit =    tops.leptonicDecayTop     (hypoKey_)->eta();
    lepTopY_fit =      tops.leptonicDecayTop     (hypoKey_)->rapidity();
    hadToppt_fit =     tops.hadronicDecayTop     (hypoKey_)->pt();       
    hadTopphi_fit =    tops.hadronicDecayTop     (hypoKey_)->phi();
    hadTopeta_fit =    tops.hadronicDecayTop     (hypoKey_)->eta();
    hadTopY_fit =      tops.hadronicDecayTop     (hypoKey_)->rapidity();
    ttBarpt_fit =      (tops.leptonicDecayTop(hypoKey_)->p4()+tops.hadronicDecayTop(hypoKey_)->p4()).pt();
    ttBarphi_fit =     (tops.leptonicDecayTop(hypoKey_)->p4()+tops.hadronicDecayTop(hypoKey_)->p4()).phi();
    ttBareta_fit =     (tops.leptonicDecayTop(hypoKey_)->p4()+tops.hadronicDecayTop(hypoKey_)->p4()).eta();
    ttBarY_fit =       (tops.leptonicDecayTop(hypoKey_)->p4()+tops.hadronicDecayTop(hypoKey_)->p4()).Rapidity();
    ttBarMass_fit =    (tops.leptonicDecayTop(hypoKey_)->p4()+tops.hadronicDecayTop(hypoKey_)->p4()).mass();
    ttBarDelPhi_fit =  deltaPhi(tops.leptonicDecayTop(hypoKey_)->phi(), tops.hadronicDecayTop(hypoKey_)->phi());
    ttBarDelY_fit =    tops.leptonicDecayTop(hypoKey_)->rapidity()-tops.hadronicDecayTop(hypoKey_)->rapidity();
    ttBarSumY_fit =    tops.leptonicDecayTop(hypoKey_)->rapidity()+tops.hadronicDecayTop(hypoKey_)->rapidity();

    /**
       Fill the Mass Distributions
    **/
    // leptonic W mass
    if( tops.leptonicDecayW(hypoKey_) ){
      lepWMass = tops.leptonicDecayW(hypoKey_)->mass();
      hists_.find("lepWMass"   )->second->Fill( lepWMass );
    }
    else lepWMass=0;
    // hadronic W mass
    if( tops.hadronicDecayW(hypoKey_) ){
      hadWMass = tops.hadronicDecayW(hypoKey_)->mass();
      hists_.find("hadWMass"   )->second->Fill( hadWMass );
    }
    else hadWMass=0;
    // leptonic Top mass
    if( tops.leptonicDecayTop(hypoKey_) ){
      lepTopMass = tops.leptonicDecayTop(hypoKey_)->mass();
      hists_.find("lepTopMass"   )->second->Fill( lepTopMass );
    }
    else lepTopMass=0;
    // hadronic Top mass
    if( tops.hadronicDecayTop(hypoKey_) ){
      hadTopMass = tops.hadronicDecayTop(hypoKey_)->mass();
      hists_.find("hadTopMass"   )->second->Fill( hadTopMass );
    }
    else hadTopMass=0;

    /**
       Fill the Pull Distributions for the reconstructed object(mu/nu/jets) kinematics (Relative to the MC Truth)
    **/
    // check existence and ttbar decay mode
    if( tops.genEvent().isAvailable() && tops.genEvent()->isSemiLeptonic(WDecay::kMuon) ){
      res::HelperJet  jetRes;
      res::HelperMuon muonRes;
      res::HelperMET  metRes;
      // hadronic b-quark from top 
      if( tops.hadronicDecayB() && tops.hadronicDecayB(hypoKey_) ){
	double hadBPt  = tops.hadronicDecayB()->pt();
	double hadBEta = tops.hadronicDecayB()->eta();
	// hadronic top b pt
	hists_.find("hadBQuarkPt"   )->second->Fill( (hadBPt -tops.hadronicDecayB(hypoKey_)->pt()) /jetRes.et (hadBPt, hadBEta, res::HelperJet::kB) );
	// hadronic top b eta
	hists_.find("hadBQuarkEta"  )->second->Fill( (hadBEta-tops.hadronicDecayB(hypoKey_)->eta())/jetRes.eta(hadBPt, hadBEta, res::HelperJet::kB) );
	// hadronic top b phi
	hists_.find("hadBQuarkPhi"  )->second->Fill( deltaPhi(tops.hadronicDecayB()->phi(), tops.hadronicDecayB(hypoKey_)->phi())/jetRes.phi(hadBPt, hadBEta, res::HelperJet::kB) );
      }
      // leptonic b-quark from top
      if( tops.leptonicDecayB() && tops.leptonicDecayB(hypoKey_) ){
	double lepBPt  = tops.leptonicDecayB()->pt();
	double lepBEta = tops.leptonicDecayB()->eta();
	// leptonic top b pt
	hists_.find("lepBQuarkPt"   )->second->Fill( (lepBPt -tops.leptonicDecayB(hypoKey_)->pt()) /jetRes.et (lepBPt, lepBEta, res::HelperJet::kB) );
	// leptonic top b eta
	hists_.find("lepBQuarkEta"  )->second->Fill( (lepBEta-tops.leptonicDecayB(hypoKey_)->eta())/jetRes.eta(lepBPt, lepBEta, res::HelperJet::kB) );
	// leptonic top b phi
	hists_.find("lepBQuarkPhi"  )->second->Fill( deltaPhi(tops.leptonicDecayB()->phi(), tops.leptonicDecayB(hypoKey_)->phi())/jetRes.phi(lepBPt, lepBEta, res::HelperJet::kB) );
      }
      // light quark from W
      if( tops.hadronicDecayQuark() && tops.hadronicDecayQuark(hypoKey_) ){
	double lightQPt  = tops.hadronicDecayQuark()->pt();
	double lightQEta = tops.hadronicDecayQuark()->eta();
	// lightQuark pt
	hists_.find("lightQuarkPt"  )->second->Fill( (lightQPt -tops.hadronicDecayQuark(hypoKey_)->pt()) /jetRes.et (lightQPt, lightQEta, res::HelperJet::kUds) );
	// lightQuark b eta
	hists_.find("lightQuarkEta" )->second->Fill( (lightQEta-tops.hadronicDecayQuark(hypoKey_)->eta())/jetRes.eta(lightQPt, lightQEta, res::HelperJet::kUds) );
	// lightQuark b phi
	hists_.find("lightQuarkPhi" )->second->Fill( deltaPhi(tops.hadronicDecayQuark()->phi(), tops.hadronicDecayQuark(hypoKey_)->phi())/jetRes.phi(lightQPt, lightQEta, res::HelperJet::kUds) );
      }
      // light anti-quark from W
      if( tops.hadronicDecayQuarkBar() && tops.hadronicDecayQuarkBar(hypoKey_) ){
	double lightQBarPt  = tops.hadronicDecayQuarkBar()->pt();
	double lightQBarEta = tops.hadronicDecayQuarkBar()->eta();
	// lightQuark pt
	hists_.find("lightQuarkPt"  )->second->Fill( (lightQBarPt -tops.hadronicDecayQuarkBar(hypoKey_)->pt()) /jetRes.et (lightQBarPt, lightQBarEta, res::HelperJet::kUds) );
	// lightQuark b eta
	hists_.find("lightQuarkEta" )->second->Fill( (lightQBarEta-tops.hadronicDecayQuarkBar(hypoKey_)->eta())/jetRes.eta(lightQBarPt, lightQBarEta, res::HelperJet::kUds) );
	// lightQuark b phi
	hists_.find("lightQuarkPhi" )->second->Fill( deltaPhi(tops.hadronicDecayQuarkBar()->phi(), tops.hadronicDecayQuarkBar(hypoKey_)->phi())/jetRes.phi(lightQBarPt, lightQBarEta, res::HelperJet::kUds) );
      }
      // muon
      if( tops.singleLepton() && tops.singleLepton(hypoKey_) ){
	double muPt  = tops.singleLepton()->pt();
	double muEta = tops.singleLepton()->eta();
	// lepton pt
	hists_.find("leptonPt"      )->second->Fill( (muPt -tops.singleLepton(hypoKey_)->pt()) /muonRes.et (muPt, muEta) );
	// lepton eta
	hists_.find("leptonEta"     )->second->Fill( (muEta-tops.singleLepton(hypoKey_)->eta())/muonRes.eta(muPt, muEta) );
	// lepton phi
	hists_.find("leptonPhi"     )->second->Fill( deltaPhi(tops.singleLepton()->phi(), tops.singleLepton(hypoKey_)->phi())/muonRes.phi(muPt, muEta) );
      }
      // neurino
      if( tops.singleNeutrino() && tops.singleNeutrino(hypoKey_) ){
	double nuPt  = tops.singleNeutrino()->pt();
	double nuEta = tops.singleNeutrino()->eta();
	// neutrino pt
	hists_.find("neutrinoPt"    )->second->Fill( (nuPt -tops.singleNeutrino(hypoKey_)->pt()) /metRes.et(nuPt) );
	// neutrino eta
	hists_.find("neutrinoEta"   )->second->Fill( (nuEta-tops.singleNeutrino(hypoKey_)->eta())/9999. );
	// neutrino phi
	hists_.find("neutrinoPhi"   )->second->Fill( deltaPhi(tops.singleNeutrino()->phi(), tops.singleNeutrino(hypoKey_)->phi())/metRes.phi(nuPt) );
      }
    /**
       Fill differences of reconstructed W/Top Kinematics (Relative to the MC Truth)
    **/
      // leptonic W
      if( tops.leptonicDecayW() && tops.leptonicDecayW(hypoKey_) ){
	// leptonic W pt
	hists_.find("lepWPt"    )->second->Fill( (tops.leptonicDecayW()->pt()-tops.leptonicDecayW(hypoKey_)->pt())/tops.leptonicDecayW()->pt() );
	// leptonic W eta
	hists_.find("lepWEta"   )->second->Fill( tops.leptonicDecayW()->eta()-tops.leptonicDecayW(hypoKey_)->eta() );
	// leptonic W phi
	hists_.find("lepWPhi"   )->second->Fill( deltaPhi(tops.leptonicDecayW()->phi(), tops.leptonicDecayW(hypoKey_)->phi()) );
      }
      // hadronic W
      if( tops.hadronicDecayW() && tops.hadronicDecayW(hypoKey_) ){
	// hadronic W pt
	hists_.find("hadWPt"    )->second->Fill( (tops.hadronicDecayW()->pt()-tops.hadronicDecayW(hypoKey_)->pt())/tops.hadronicDecayW()->pt() );
	// hadronic W eta
	hists_.find("hadWEta"   )->second->Fill( tops.hadronicDecayW()->eta()-tops.hadronicDecayW(hypoKey_)->eta() );
	// hadronic W phi
	hists_.find("hadWPhi"   )->second->Fill( deltaPhi(tops.hadronicDecayW()->phi(), tops.hadronicDecayW(hypoKey_)->phi()) );
      }
      // leptonic Top
      if( tops.leptonicDecayTop() && tops.leptonicDecayTop(hypoKey_) ){
      // leptonic Top pt
	hists_.find("lepTopPt"    )->second->Fill( (tops.leptonicDecayTop()->pt()-tops.leptonicDecayTop(hypoKey_)->pt())/tops.leptonicDecayTop()->pt() );
	// leptonic Top eta
	hists_.find("lepTopEta"   )->second->Fill( tops.leptonicDecayTop()->eta()-tops.leptonicDecayTop(hypoKey_)->eta() );
	// leptonic Top phi
	hists_.find("lepTopPhi"   )->second->Fill( deltaPhi(tops.leptonicDecayTop()->phi(), tops.leptonicDecayTop(hypoKey_)->phi()) );
      }
      // hadronic Top
      if( tops.hadronicDecayTop() && tops.hadronicDecayTop(hypoKey_) ){
	// hadronic Top pt
	hists_.find("hadTopPt"    )->second->Fill( (tops.hadronicDecayTop()->pt()-tops.hadronicDecayTop(hypoKey_)->pt())/tops.hadronicDecayTop()->pt() );
	// hadronic Top eta
	hists_.find("hadTopEta"   )->second->Fill( tops.hadronicDecayTop()->eta()-tops.hadronicDecayTop(hypoKey_)->eta() );
	// hadronic Top phi
	hists_.find("hadTopPhi"   )->second->Fill( deltaPhi(tops.hadronicDecayTop()->phi(), tops.hadronicDecayTop(hypoKey_)->phi()) );
      }
    }

    /**
       Correlation Plots
    **/
    // correlation between jet hypothesis (genmatched objects) and jet index MC truth
    if( tops.isHypoValid("kGenMatch") ){
      corrs_.find("mapGenMatch_" )->second->Fill(TtSemiLepEvtPartons::LightQ   , objectIndex(tops, "kGenMatch", TtSemiLepEvtPartons::LightQ   ) );
      corrs_.find("mapGenMatch_" )->second->Fill(TtSemiLepEvtPartons::LightQBar, objectIndex(tops, "kGenMatch", TtSemiLepEvtPartons::LightQBar) );
      corrs_.find("mapGenMatch_" )->second->Fill(TtSemiLepEvtPartons::HadB     , objectIndex(tops, "kGenMatch", TtSemiLepEvtPartons::HadB     ) );
      corrs_.find("mapGenMatch_" )->second->Fill(TtSemiLepEvtPartons::LepB     , objectIndex(tops, "kGenMatch", TtSemiLepEvtPartons::LepB     ) );
    }
    // correlation between jet hypothesis (reconstructed objects) and jet index MC truth
    if( tops.isHypoValid(hypoKey_) ){
      corrs_.find("mapKinFit_"   )->second->Fill(TtSemiLepEvtPartons::LightQ   , objectIndex(tops, hypoKey_  , TtSemiLepEvtPartons::LightQ   ) );
      corrs_.find("mapKinFit_"   )->second->Fill(TtSemiLepEvtPartons::LightQBar, objectIndex(tops, hypoKey_  , TtSemiLepEvtPartons::LightQBar) );
      corrs_.find("mapKinFit_"   )->second->Fill(TtSemiLepEvtPartons::HadB     , objectIndex(tops, hypoKey_  , TtSemiLepEvtPartons::HadB     ) );
      corrs_.find("mapKinFit_"   )->second->Fill(TtSemiLepEvtPartons::LepB     , objectIndex(tops, hypoKey_  , TtSemiLepEvtPartons::LepB     ) );
    }
    if(wantTree) tree->Fill();
  }
}

