#include "TopAnalysis/TopAnalyzer/interface/BTags.h"

/// default constructor for generator level analysis in fw lite
BTags::BTags()
{
}

/// default constructor for full fw
BTags::BTags(const edm::ParameterSet& cfg)
{
}

/// histogramm booking for fwlite 
void BTags::book()
{
  /** 
      B Tags for B-Jets
  **/

  hists_["b_combinedSecondaryVertexBJetTags"   ] = new TH1F( "b_combinedSecondaryVertexBJetTags"    , "b_combinedSecondaryVertexBJetTags"    ,   40, -2 , 2 );
  hists_["b_combinedSecondaryVertexMVABJetTags"] = new TH1F( "b_combinedSecondaryVertexMVABJetTags" , "b_combinedSecondaryVertexMVABJetTags" ,   40, -2 , 2 );
  hists_["b_jetBProbabilityBJetTags"           ] = new TH1F( "b_jetBProbabilityBJetTags"            , "b_jetBProbabilityBJetTags"            ,  110,  0 , 11);
  hists_["b_jetProbabilityBJetTags"            ] = new TH1F( "b_jetProbabilityBJetTags"             , "b_jetProbabilityBJetTags"             ,   40,  0 , 4 );
  hists_["b_simpleSecondaryVertexBJetTags"     ] = new TH1F( "b_simpleSecondaryVertexBJetTags"      , "b_simpleSecondaryVertexBJetTags"      ,   80, -2 , 6 );
  hists_["b_softElectronByPtBJetTags"          ] = new TH1F( "b_softElectronByPtBJetTags"           , "b_softElectronByPtBJetTags"           ,  200,  0 , 20);
  hists_["b_softElectronByIP3dBJetTags"        ] = new TH1F( "b_softElectronByIP3dBJetTags"         , "b_softElectronByIP3dBJetTags"         , 1500, -40, 110);
  hists_["b_softMuonBJetTags"                  ] = new TH1F( "b_softMuonBJetTags"                   , "b_softMuonBJetTags"                   ,   10,  0 , 1 );
  hists_["b_softMuonByPtBJetTags"              ] = new TH1F( "b_softMuonByPtBJetTags"               , "b_softMuonByPtBJetTags"               ,  200,  0 , 20);
  hists_["b_softMuonByIP3dBJetTags"            ] = new TH1F( "b_softMuonByIP3dBJetTags"             , "b_softMuonByIP3dBJetTags"             , 2000, -100, 100);
  hists_["b_trackCountingHighEffBJetTags"      ] = new TH1F( "b_trackCountingHighEffBJetTags"       , "b_trackCountingHighEffBJetTags"       ,  400, -20, 20);
  hists_["b_trackCountingHighPurBJetTags"      ] = new TH1F( "b_trackCountingHighPurBJetTags"       , "b_trackCountingHighPurBJetTags"       ,  400, -20, 20);

  /** 
      B Tags for lightQ-Jets
  **/

  hists_["q_combinedSecondaryVertexBJetTags"   ] = new TH1F( "q_combinedSecondaryVertexBJetTags"    , "q_combinedSecondaryVertexBJetTags"    ,   40, -2 , 2 );
  hists_["q_combinedSecondaryVertexMVABJetTags"] = new TH1F( "q_combinedSecondaryVertexMVABJetTags" , "q_combinedSecondaryVertexMVABJetTags" ,   40, -2 , 2 );
  hists_["q_jetBProbabilityBJetTags"           ] = new TH1F( "q_jetBProbabilityBJetTags"            , "q_jetBProbabilityBJetTags"            ,  110,  0 , 11);
  hists_["q_jetProbabilityBJetTags"            ] = new TH1F( "q_jetProbabilityBJetTags"             , "q_jetProbabilityBJetTags"             ,   40, 0 ,  4 );
  hists_["q_simpleSecondaryVertexBJetTags"     ] = new TH1F( "q_simpleSecondaryVertexBJetTags"      , "q_simpleSecondaryVertexBJetTags"      ,   80, -2 , 6 );
  hists_["q_softElectronByPtBJetTags"          ] = new TH1F( "q_softElectronByPtBJetTags"           , "q_softElectronByPtBJetTags"           ,  200,  0 , 20);
  hists_["q_softElectronByIP3dBJetTags"        ] = new TH1F( "q_softElectronByIP3dBJetTags"         , "q_softElectronByIP3dBJetTags"         , 1500, -40, 110);
  hists_["q_softMuonBJetTags"                  ] = new TH1F( "q_softMuonBJetTags"                   , "q_softMuonBJetTags"                   ,   10,  0 , 1 );
  hists_["q_softMuonByPtBJetTags"              ] = new TH1F( "q_softMuonByPtBJetTags"               , "q_softMuonByPtBJetTags"               ,  200,  0 , 20);
  hists_["q_softMuonByIP3dBJetTags"            ] = new TH1F( "q_softMuonByIP3dBJetTags"             , "q_softMuonByIP3dBJetTags"             , 2000, -100, 100);
  hists_["q_trackCountingHighEffBJetTags"      ] = new TH1F( "q_trackCountingHighEffBJetTags"       , "q_trackCountingHighEffBJetTags"       ,  400, -20, 20);
  hists_["q_trackCountingHighPurBJetTags"      ] = new TH1F( "q_trackCountingHighPurBJetTags"       , "q_trackCountingHighPurBJetTags"       ,  400, -20, 20);

  /** 
      B Tags for gluon-Jets
  **/

  hists_["g_combinedSecondaryVertexBJetTags"   ] = new TH1F( "g_combinedSecondaryVertexBJetTags"    , "g_combinedSecondaryVertexBJetTags"    ,   40, -2 , 2 );
  hists_["g_combinedSecondaryVertexMVABJetTags"] = new TH1F( "g_combinedSecondaryVertexMVABJetTags" , "g_combinedSecondaryVertexMVABJetTags" ,   40, -2 , 2 );
  hists_["g_jetBProbabilityBJetTags"           ] = new TH1F( "g_jetBProbabilityBJetTags"            , "g_jetBProbabilityBJetTags"            ,  110,  0 , 11);
  hists_["g_jetProbabilityBJetTags"            ] = new TH1F( "g_jetProbabilityBJetTags"             , "g_jetProbabilityBJetTags"             ,   40,  0 , 4 );
  hists_["g_simpleSecondaryVertexBJetTags"     ] = new TH1F( "g_simpleSecondaryVertexBJetTags"      , "g_simpleSecondaryVertexBJetTags"      ,   80, -2 , 6 );
  hists_["g_softElectronByPtBJetTags"          ] = new TH1F( "g_softElectronByPtBJetTags"           , "g_softElectronByPtBJetTags"           ,  200,  0 , 20);
  hists_["g_softElectronByIP3dBJetTags"        ] = new TH1F( "g_softElectronByIP3dBJetTags"         , "g_softElectronByIP3dBJetTags"         , 1500, -40, 110);
  hists_["g_softMuonBJetTags"                  ] = new TH1F( "g_softMuonBJetTags"                   , "g_softMuonBJetTags"                   ,   10,  0 , 1 );
  hists_["g_softMuonByPtBJetTags"              ] = new TH1F( "g_softMuonByPtBJetTags"               , "g_softMuonByPtBJetTags"               ,  200,  0 , 20);
  hists_["g_softMuonByIP3dBJetTags"            ] = new TH1F( "g_softMuonByIP3dBJetTags"             , "g_softMuonByIP3dBJetTags"             , 2000, -100, 100);
  hists_["g_trackCountingHighEffBJetTags"      ] = new TH1F( "g_trackCountingHighEffBJetTags"       , "g_trackCountingHighEffBJetTags"       ,  400, -20, 20);
  hists_["g_trackCountingHighPurBJetTags"      ] = new TH1F( "g_trackCountingHighPurBJetTags"       , "g_trackCountingHighPurBJetTags"       ,  400, -20, 20);
}

/// histogramm booking for fw
void BTags::book(edm::Service<TFileService>& fs)
{
  /** 
      B Tags for B-Jets
  **/

  hists_["b_combinedSecondaryVertexBJetTags"   ] = fs->make<TH1F>( "b_combinedSecondaryVertexBJetTags"    , "b_combinedSecondaryVertexBJetTags"    ,   40, -2 , 2 );
  hists_["b_combinedSecondaryVertexMVABJetTags"] = fs->make<TH1F>( "b_combinedSecondaryVertexMVABJetTags" , "b_combinedSecondaryVertexMVABJetTags" ,   40, -2 , 2 );
  hists_["b_jetBProbabilityBJetTags"           ] = fs->make<TH1F>( "b_jetBProbabilityBJetTags"            , "b_jetBProbabilityBJetTags"            ,  110,  0 , 11);
  hists_["b_jetProbabilityBJetTags"            ] = fs->make<TH1F>( "b_jetProbabilityBJetTags"             , "b_jetProbabilityBJetTags"             ,   40,  0 , 4 );
  hists_["b_simpleSecondaryVertexBJetTags"     ] = fs->make<TH1F>( "b_simpleSecondaryVertexBJetTags"      , "b_simpleSecondaryVertexBJetTags"      ,   80, -2 , 6 );
  hists_["b_softElectronByPtBJetTags"          ] = fs->make<TH1F>( "b_softElectronByPtBJetTags"           , "b_softElectronByPtBJetTags"           ,  200,  0 , 20);
  hists_["b_softElectronByIP3dBJetTags"        ] = fs->make<TH1F>( "b_softElectronByIP3dBJetTags"         , "b_softElectronByIP3dBJetTags"         , 1500, -40, 110);
  hists_["b_softMuonBJetTags"                  ] = fs->make<TH1F>( "b_softMuonBJetTags"                   , "b_softMuonBJetTags"                   ,   10,  0 , 1 );
  hists_["b_softMuonByPtBJetTags"              ] = fs->make<TH1F>( "b_softMuonByPtBJetTags"               , "b_softMuonByPtBJetTags"               ,  200,  0 , 20);
  hists_["b_softMuonByIP3dBJetTags"            ] = fs->make<TH1F>( "b_softMuonByIP3dBJetTags"             , "b_softMuonByIP3dBJetTags"             , 2000, -100, 100);
  hists_["b_trackCountingHighEffBJetTags"      ] = fs->make<TH1F>( "b_trackCountingHighEffBJetTags"       , "b_trackCountingHighEffBJetTags"       ,  400, -20, 20);
  hists_["b_trackCountingHighPurBJetTags"      ] = fs->make<TH1F>( "b_trackCountingHighPurBJetTags"       , "b_trackCountingHighPurBJetTags"       ,  400, -20, 20);

  /** 
      B Tags for lightQ-Jets
  **/

  hists_["q_combinedSecondaryVertexBJetTags"   ] = fs->make<TH1F>( "q_combinedSecondaryVertexBJetTags"    , "q_combinedSecondaryVertexBJetTags"    ,   40, -2 , 2 );
  hists_["q_combinedSecondaryVertexMVABJetTags"] = fs->make<TH1F>( "q_combinedSecondaryVertexMVABJetTags" , "q_combinedSecondaryVertexMVABJetTags" ,   40, -2 , 2 );
  hists_["q_jetBProbabilityBJetTags"           ] = fs->make<TH1F>( "q_jetBProbabilityBJetTags"            , "q_jetBProbabilityBJetTags"            ,  110,  0 , 11);
  hists_["q_jetProbabilityBJetTags"            ] = fs->make<TH1F>( "q_jetProbabilityBJetTags"             , "q_jetProbabilityBJetTags"             ,   40, 0 ,  4 );
  hists_["q_simpleSecondaryVertexBJetTags"     ] = fs->make<TH1F>( "q_simpleSecondaryVertexBJetTags"      , "q_simpleSecondaryVertexBJetTags"      ,   80, -2 , 6 );
  hists_["q_softElectronByPtBJetTags"          ] = fs->make<TH1F>( "q_softElectronByPtBJetTags"           , "q_softElectronByPtBJetTags"           ,  200,  0 , 20);
  hists_["q_softElectronByIP3dBJetTags"        ] = fs->make<TH1F>( "q_softElectronByIP3dBJetTags"         , "q_softElectronByIP3dBJetTags"         , 1500, -40, 110);
  hists_["q_softMuonBJetTags"                  ] = fs->make<TH1F>( "q_softMuonBJetTags"                   , "q_softMuonBJetTags"                   ,   10,  0 , 1 );
  hists_["q_softMuonByPtBJetTags"              ] = fs->make<TH1F>( "q_softMuonByPtBJetTags"               , "q_softMuonByPtBJetTags"               ,  200,  0 , 20);
  hists_["q_softMuonByIP3dBJetTags"            ] = fs->make<TH1F>( "q_softMuonByIP3dBJetTags"             , "q_softMuonByIP3dBJetTags"             , 2000, -100, 100);
  hists_["q_trackCountingHighEffBJetTags"      ] = fs->make<TH1F>( "q_trackCountingHighEffBJetTags"       , "q_trackCountingHighEffBJetTags"       ,  400, -20, 20);
  hists_["q_trackCountingHighPurBJetTags"      ] = fs->make<TH1F>( "q_trackCountingHighPurBJetTags"       , "q_trackCountingHighPurBJetTags"       ,  400, -20, 20);

  /** 
      B Tags for gluon-Jets
  **/

  hists_["g_combinedSecondaryVertexBJetTags"   ] = fs->make<TH1F>( "g_combinedSecondaryVertexBJetTags"    , "g_combinedSecondaryVertexBJetTags"    ,   40, -2 , 2 );
  hists_["g_combinedSecondaryVertexMVABJetTags"] = fs->make<TH1F>( "g_combinedSecondaryVertexMVABJetTags" , "g_combinedSecondaryVertexMVABJetTags" ,   40, -2 , 2 );
  hists_["g_jetBProbabilityBJetTags"           ] = fs->make<TH1F>( "g_jetBProbabilityBJetTags"            , "g_jetBProbabilityBJetTags"            ,  110,  0 , 11);
  hists_["g_jetProbabilityBJetTags"            ] = fs->make<TH1F>( "g_jetProbabilityBJetTags"             , "g_jetProbabilityBJetTags"             ,   40,  0 , 4 );
  hists_["g_simpleSecondaryVertexBJetTags"     ] = fs->make<TH1F>( "g_simpleSecondaryVertexBJetTags"      , "g_simpleSecondaryVertexBJetTags"      ,   80, -2 , 6 );
  hists_["g_softElectronByPtBJetTags"          ] = fs->make<TH1F>( "g_softElectronByPtBJetTags"           , "g_softElectronByPtBJetTags"           ,  200,  0 , 20);
  hists_["g_softElectronByIP3dBJetTags"        ] = fs->make<TH1F>( "g_softElectronByIP3dBJetTags"         , "g_softElectronByIP3dBJetTags"         , 1500, -40, 110);
  hists_["g_softMuonBJetTags"                  ] = fs->make<TH1F>( "g_softMuonBJetTags"                   , "g_softMuonBJetTags"                   ,   10,  0 , 1 );
  hists_["g_softMuonByPtBJetTags"              ] = fs->make<TH1F>( "g_softMuonByPtBJetTags"               , "g_softMuonByPtBJetTags"               ,  200,  0 , 20);
  hists_["g_softMuonByIP3dBJetTags"            ] = fs->make<TH1F>( "g_softMuonByIP3dBJetTags"             , "g_softMuonByIP3dBJetTags"             , 2000, -100, 100);
  hists_["g_trackCountingHighEffBJetTags"      ] = fs->make<TH1F>( "g_trackCountingHighEffBJetTags"       , "g_trackCountingHighEffBJetTags"       ,  400, -20, 20);
  hists_["g_trackCountingHighPurBJetTags"      ] = fs->make<TH1F>( "g_trackCountingHighPurBJetTags"       , "g_trackCountingHighPurBJetTags"       ,  400, -20, 20);
}


/// histogram filling interface for reconstruction level for access with fwlite or full framework
void
BTags::fill(const edm::View<pat::Jet>& jets, const double& weight)
{

  /** 
      B Tags
  **/

  for(edm::View<pat::Jet>::const_iterator jet=jets.begin(); jet!=jets.end(); ++jet){

    // for b quarks
    if(jet->genParticle() == 0) continue;
    if(jet->genParticle()->pdgId() == 0) continue;
    if(jet->genParticle()->pdgId() == 5 || jet->genParticle()->pdgId() == -5) {

    hists_.find("b_combinedSecondaryVertexBJetTags"   )->second->Fill(jet->bDiscriminator("combinedSecondaryVertexBJetTags"   ), weight);
    hists_.find("b_combinedSecondaryVertexMVABJetTags")->second->Fill(jet->bDiscriminator("combinedSecondaryVertexMVABJetTags"), weight);
    hists_.find("b_jetBProbabilityBJetTags"           )->second->Fill(jet->bDiscriminator("jetBProbabilityBJetTags"           ), weight);
    hists_.find("b_jetProbabilityBJetTags"            )->second->Fill(jet->bDiscriminator("jetProbabilityBJetTags"            ), weight);
    hists_.find("b_simpleSecondaryVertexBJetTags"     )->second->Fill(jet->bDiscriminator("simpleSecondaryVertexBJetTags"     ), weight);
    hists_.find("b_softElectronByPtBJetTags"          )->second->Fill(jet->bDiscriminator("softElectronByPtBJetTags"          ), weight);
    hists_.find("b_softElectronByIP3dBJetTags"        )->second->Fill(jet->bDiscriminator("softElectronByIP3dBJetTags"        ), weight);
    hists_.find("b_softMuonBJetTags"                  )->second->Fill(jet->bDiscriminator("softMuonBJetTags"                  ), weight);
    hists_.find("b_softMuonByPtBJetTags"              )->second->Fill(jet->bDiscriminator("softMuonByPtBJetTags"              ), weight);
    hists_.find("b_softMuonByIP3dBJetTags"            )->second->Fill(jet->bDiscriminator("softMuonByIP3dBJetTags"            ), weight);
    hists_.find("b_trackCountingHighEffBJetTags"      )->second->Fill(jet->bDiscriminator("trackCountingHighEffBJetTags"      ), weight);
    hists_.find("b_trackCountingHighPurBJetTags"      )->second->Fill(jet->bDiscriminator("trackCountingHighPurBJetTags"      ), weight);
    }

    // for light quarks
    if(jet->genParticle()->pdgId() < 5 && jet->genParticle()->pdgId() > -5) {

    hists_.find("q_combinedSecondaryVertexBJetTags"   )->second->Fill(jet->bDiscriminator("combinedSecondaryVertexBJetTags"   ), weight);
    hists_.find("q_combinedSecondaryVertexMVABJetTags")->second->Fill(jet->bDiscriminator("combinedSecondaryVertexMVABJetTags"), weight);
    hists_.find("q_jetBProbabilityBJetTags"           )->second->Fill(jet->bDiscriminator("jetBProbabilityBJetTags"           ), weight);
    hists_.find("q_jetProbabilityBJetTags"            )->second->Fill(jet->bDiscriminator("jetProbabilityBJetTags"            ), weight);
    hists_.find("q_simpleSecondaryVertexBJetTags"     )->second->Fill(jet->bDiscriminator("simpleSecondaryVertexBJetTags"     ), weight);
    hists_.find("q_softElectronByPtBJetTags"          )->second->Fill(jet->bDiscriminator("softElectronByPtBJetTags"          ), weight);
    hists_.find("q_softElectronByIP3dBJetTags"        )->second->Fill(jet->bDiscriminator("softElectronByIP3dBJetTags"        ), weight);
    hists_.find("q_softMuonBJetTags"                  )->second->Fill(jet->bDiscriminator("softMuonBJetTags"                  ), weight);
    hists_.find("q_softMuonByPtBJetTags"              )->second->Fill(jet->bDiscriminator("softMuonByPtBJetTags"              ), weight);
    hists_.find("q_softMuonByIP3dBJetTags"            )->second->Fill(jet->bDiscriminator("softMuonByIP3dBJetTags"            ), weight);
    hists_.find("q_trackCountingHighEffBJetTags"      )->second->Fill(jet->bDiscriminator("trackCountingHighEffBJetTags"      ), weight);
    hists_.find("q_trackCountingHighPurBJetTags"      )->second->Fill(jet->bDiscriminator("trackCountingHighPurBJetTags"      ), weight);
    }

    // for gluons
    if(jet->genParticle()->pdgId() ==  21 || jet->genParticle()->pdgId() ==  9 ||
       jet->genParticle()->pdgId() == -21 || jet->genParticle()->pdgId() == -9) {

    hists_.find("g_combinedSecondaryVertexBJetTags"   )->second->Fill(jet->bDiscriminator("combinedSecondaryVertexBJetTags"   ), weight);
    hists_.find("g_combinedSecondaryVertexMVABJetTags")->second->Fill(jet->bDiscriminator("combinedSecondaryVertexMVABJetTags"), weight);
    hists_.find("g_jetBProbabilityBJetTags"           )->second->Fill(jet->bDiscriminator("jetBProbabilityBJetTags"           ), weight);
    hists_.find("g_jetProbabilityBJetTags"            )->second->Fill(jet->bDiscriminator("jetProbabilityBJetTags"            ), weight);
    hists_.find("g_simpleSecondaryVertexBJetTags"     )->second->Fill(jet->bDiscriminator("simpleSecondaryVertexBJetTags"     ), weight);
    hists_.find("g_softElectronByPtBJetTags"          )->second->Fill(jet->bDiscriminator("softElectronByPtBJetTags"          ), weight);
    hists_.find("g_softElectronByIP3dBJetTags"        )->second->Fill(jet->bDiscriminator("softElectronByIP3dBJetTags"        ), weight);
    hists_.find("g_softMuonBJetTags"                  )->second->Fill(jet->bDiscriminator("softMuonBJetTags"                  ), weight);
    hists_.find("g_softMuonByPtBJetTags"              )->second->Fill(jet->bDiscriminator("softMuonByPtBJetTags"              ), weight);
    hists_.find("g_softMuonByIP3dBJetTags"            )->second->Fill(jet->bDiscriminator("softMuonByIP3dBJetTags"            ), weight);
    hists_.find("g_trackCountingHighEffBJetTags"      )->second->Fill(jet->bDiscriminator("trackCountingHighEffBJetTags"      ), weight);
    hists_.find("g_trackCountingHighPurBJetTags"      )->second->Fill(jet->bDiscriminator("trackCountingHighPurBJetTags"      ), weight);
    }
  }
}
