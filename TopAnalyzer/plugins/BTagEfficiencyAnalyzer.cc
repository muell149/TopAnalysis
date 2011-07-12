#include "DataFormats/Common/interface/Association.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TopAnalysis/TopAnalyzer/plugins/BTagEfficiencyAnalyzer.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

/// default constructor
BTagEfficiencyAnalyzer::BTagEfficiencyAnalyzer(const edm::ParameterSet& cfg):
  jets_         ( cfg.getParameter<edm::InputTag> ("jets") ),
  bTagAlgo_     ( cfg.getParameter<std::string>   ("bTagAlgo"  ) ),
  bTagDiscrCut_ ( cfg.getParameter<double>        ("bTagDiscrCut") ),
  binsPtB_       (cfg.getParameter<std::vector<double> >("binsPtB")),
  binsEtaB_      (cfg.getParameter<std::vector<double> >("binsEtaB")),
  binsPtL_       (cfg.getParameter<std::vector<double> >("binsPtL")),
  binsEtaL_      (cfg.getParameter<std::vector<double> >("binsEtaL"))
{
}

/// default destructor
BTagEfficiencyAnalyzer::~BTagEfficiencyAnalyzer()
{
}

/// ...
void 
BTagEfficiencyAnalyzer::analyze(const edm::Event& evt, const edm::EventSetup& setup)
{
  // get jet collection
  edm::Handle<edm::View< pat::Jet > > jets;
  evt.getByLabel(jets_, jets);
  
  hists_.find("NumEvents" )->second->Fill( 0.5 );
  
  for(edm::View<pat::Jet>::const_iterator jet = jets->begin();jet != jets->end(); ++jet) {
    
    double bTagDiscr = jet->bDiscriminator( bTagAlgo_ );
    
    if(jet->partonFlavour() == 5 || jet->partonFlavour() == -5){
      hists_.find("NumBJets" )   ->second->Fill( 0.5 );
      hists_.find("NumBJetsPt" ) ->second->Fill( jet->pt() );
      hists_.find("NumBJetsEta" )->second->Fill( std::abs(jet->eta()) );
      hists2D_.find("NumBJetsPtEta" ) ->second->Fill( jet->pt(), std::abs(jet->eta()) );
      if(bTagDiscr > bTagDiscrCut_){
	hists_.find("NumBJetsTagged" )   ->second->Fill( 0.5 );
	hists_.find("NumBJetsTaggedPt" ) ->second->Fill( jet->pt() );
	hists_.find("NumBJetsTaggedEta" )->second->Fill( std::abs(jet->eta()) );
	hists2D_.find("NumBJetsTaggedPtEta" ) ->second->Fill( jet->pt(), std::abs(jet->eta()) );
      }
    }
  
    else if(jet->partonFlavour() == 4 || jet->partonFlavour() == -4){
      hists_.find("NumCJets" )   ->second->Fill( 0.5 );
      hists_.find("NumCJetsPt" ) ->second->Fill( jet->pt() );
      hists_.find("NumCJetsEta" )->second->Fill( std::abs(jet->eta()) );
      hists2D_.find("NumCJetsPtEta" ) ->second->Fill( jet->pt(), std::abs(jet->eta()) );
      if(bTagDiscr > bTagDiscrCut_){
	hists_.find("NumCJetsTagged" )   ->second->Fill( 0.5 );
	hists_.find("NumCJetsTaggedPt" ) ->second->Fill( jet->pt() );
	hists_.find("NumCJetsTaggedEta" )->second->Fill( std::abs(jet->eta()) );
	hists2D_.find("NumCJetsTaggedPtEta" ) ->second->Fill( jet->pt(), std::abs(jet->eta()) );
      }
    }
  
    else{
      hists_.find("NumLJets" )   ->second->Fill( 0.5 );
      hists_.find("NumLJetsPt" ) ->second->Fill( jet->pt() );
      hists_.find("NumLJetsEta" )->second->Fill( std::abs(jet->eta()) );
      hists2D_.find("NumLJetsPtEta" ) ->second->Fill( jet->pt(), std::abs(jet->eta()) );
      if(bTagDiscr > bTagDiscrCut_){
	hists_.find("NumLJetsTagged" )   ->second->Fill( 0.5 );
	hists_.find("NumLJetsTaggedPt" ) ->second->Fill( jet->pt() );
	hists_.find("NumLJetsTaggedEta" )->second->Fill( std::abs(jet->eta()) );
	hists2D_.find("NumLJetsTaggedPtEta" ) ->second->Fill( jet->pt(), std::abs(jet->eta()) );
      }
    }
  }
}

/// ...
void 
BTagEfficiencyAnalyzer::beginJob()
{
  // laod TFile Service
  edm::Service<TFileService> fs;
  if( !fs ){
    throw edm::Exception( edm::errors::Configuration,
                          "TFile Service is not registered in cfg file" );
  }
  
  /// booking of histos for number of events and jets (only one bin) and b tag eff.
  hists_["NumEvents"]      = fs->make<TH1F>( "NumEvents", "NumEvents", 1, 0, 1 );
  hists_["NumBJets" ]      = fs->make<TH1F>( "NumBJets" , "NumBJets" , 1, 0, 1 );
  hists_["NumBJetsTagged"] = fs->make<TH1F>( "NumBJetsTagged"  , "NumBJetsTagged"  , 1, 0, 1 );
  hists_["EffBJetsTagged"] = fs->make<TH1F>( "EffBJetsTagged"  , "EffBJetsTagged"  , 1, 0, 1 );
  hists_["NumBJetsPt"    ] = fs->make<TH1F>( "NumBJetsPt"    , "NumBJetsPt"    ,  binsPtB_.size()-1, &binsPtB_[0] );
  hists_["NumBJetsTaggedPt"] = fs->make<TH1F>( "NumBJetsTaggedPt", "NumBJetsTaggedPt",  binsPtB_.size()-1, &binsPtB_[0] );
  hists_["EffBJetsTaggedPt"] = fs->make<TH1F>( "EffBJetsTaggedPt", "EffBJetsTaggedPt",  binsPtB_.size()-1, &binsPtB_[0] );
  hists_["NumBJetsEta"    ] = fs->make<TH1F>( "NumBJetsEta"    , "NumBJetsEta"    ,  binsEtaB_.size()-1, &binsEtaB_[0] );
  hists_["NumBJetsTaggedEta"] = fs->make<TH1F>( "NumBJetsTaggedEta", "NumBJetsTaggedEta",  binsEtaB_.size()-1, &binsEtaB_[0] );
  hists_["EffBJetsTaggedEta"] = fs->make<TH1F>( "EffBJetsTaggedEta", "EffBJetsTaggedEta",  binsEtaB_.size()-1, &binsEtaB_[0] );
  hists2D_["NumBJetsPtEta"    ]   = fs->make<TH2F>( "NumBJetsPtEta"    , "NumBJetsPtEta"    ,  binsPtB_.size()-1, &binsPtB_[0],  binsEtaB_.size()-1, &binsEtaB_[0] );
  hists2D_["NumBJetsTaggedPtEta"] = fs->make<TH2F>( "NumBJetsTaggedPtEta", "NumBJetsTaggedPtEta",  binsPtB_.size()-1, &binsPtB_[0],  binsEtaB_.size()-1, &binsEtaB_[0] );
  hists2D_["EffBJetsTaggedPtEta"] = fs->make<TH2F>( "EffBJetsTaggedPtEta", "EffBJetsTaggedPtEta",  binsPtB_.size()-1, &binsPtB_[0],  binsEtaB_.size()-1, &binsEtaB_[0] );
  
  hists_["NumCJets" ]      = fs->make<TH1F>( "NumCJets" , "NumCJets" , 1, 0, 1 );
  hists_["NumCJetsTagged"] = fs->make<TH1F>( "NumCJetsTagged"  , "NumCJetsTagged"  , 1, 0, 1 );
  hists_["EffCJetsTagged"] = fs->make<TH1F>( "EffCJetsTagged"  , "EffCJetsTagged"  , 1, 0, 1 );
  hists_["NumCJetsPt"    ] = fs->make<TH1F>( "NumCJetsPt"    , "NumCJetsPt"    ,  binsPtB_.size()-1, &binsPtB_[0] );
  hists_["NumCJetsTaggedPt"] = fs->make<TH1F>( "NumCJetsTaggedPt", "NumCJetsTaggedPt",  binsPtB_.size()-1, &binsPtB_[0] );
  hists_["EffCJetsTaggedPt"] = fs->make<TH1F>( "EffCJetsTaggedPt", "EffCJetsTaggedPt",  binsPtB_.size()-1, &binsPtB_[0] );
  hists_["NumCJetsEta"    ] = fs->make<TH1F>( "NumCJetsEta"    , "NumCJetsEta"    ,  binsEtaB_.size()-1, &binsEtaB_[0] );
  hists_["NumCJetsTaggedEta"] = fs->make<TH1F>( "NumCJetsTaggedEta", "NumCJetsTaggedEta",  binsEtaB_.size()-1, &binsEtaB_[0] );
  hists_["EffCJetsTaggedEta"] = fs->make<TH1F>( "EffCJetsTaggedEta", "EffCJetsTaggedEta",  binsEtaB_.size()-1, &binsEtaB_[0] );
  hists2D_["NumCJetsPtEta"    ]   = fs->make<TH2F>( "NumCJetsPtEta"    , "NumCJetsPtEta"    ,  binsPtB_.size()-1, &binsPtB_[0],  binsEtaB_.size()-1, &binsEtaB_[0] );
  hists2D_["NumCJetsTaggedPtEta"] = fs->make<TH2F>( "NumCJetsTaggedPtEta", "NumCJetsTaggedPtEta",  binsPtB_.size()-1, &binsPtB_[0],  binsEtaB_.size()-1, &binsEtaB_[0] );
  hists2D_["EffCJetsTaggedPtEta"] = fs->make<TH2F>( "EffCJetsTaggedPtEta", "EffCJetsTaggedPtEta",  binsPtB_.size()-1, &binsPtB_[0],  binsEtaB_.size()-1, &binsEtaB_[0] );
  
  
  hists_["NumLJets" ]      = fs->make<TH1F>( "NumLJets" , "NumLJets" , 1, 0, 1 );
  hists_["NumLJetsTagged"] = fs->make<TH1F>( "NumLJetsTagged"  , "NumLJetsTagged"  , 1, 0, 1 );
  hists_["EffLJetsTagged"] = fs->make<TH1F>( "EffLJetsTagged"  , "EffLJetsTagged"  , 1, 0, 1 );
  hists_["NumLJetsPt"    ] = fs->make<TH1F>( "NumLJetsPt"    , "NumLJetsPt"    ,  binsPtL_.size()-1, &binsPtL_[0] );
  hists_["NumLJetsTaggedPt"] = fs->make<TH1F>( "NumLJetsTaggedPt", "NumLJetsTaggedPt",  binsPtL_.size()-1, &binsPtL_[0] );
  hists_["EffLJetsTaggedPt"] = fs->make<TH1F>( "EffLJetsTaggedPt", "EffLJetsTaggedPt",  binsPtL_.size()-1, &binsPtL_[0] );
  hists_["NumLJetsEta"    ] = fs->make<TH1F>( "NumLJetsEta"    , "NumLJetsEta"    ,  binsEtaL_.size()-1, &binsEtaL_[0] );
  hists_["NumLJetsTaggedEta"] = fs->make<TH1F>( "NumLJetsTaggedEta", "NumLJetsTaggedEta",  binsEtaL_.size()-1, &binsEtaL_[0] );
  hists_["EffLJetsTaggedEta"] = fs->make<TH1F>( "EffLJetsTaggedEta", "EffLJetsTaggedEta",  binsEtaL_.size()-1, &binsEtaL_[0] );
  hists2D_["NumLJetsPtEta"    ]   = fs->make<TH2F>( "NumLJetsPtEta"    , "NumLJetsPtEta"    ,  binsPtL_.size()-1, &binsPtL_[0],  binsEtaL_.size()-1, &binsEtaL_[0] );
  hists2D_["NumLJetsTaggedPtEta"] = fs->make<TH2F>( "NumLJetsTaggedPtEta", "NumLJetsTaggedPtEta",  binsPtL_.size()-1, &binsPtL_[0],  binsEtaL_.size()-1, &binsEtaL_[0] );
  hists2D_["EffLJetsTaggedPtEta"] = fs->make<TH2F>( "EffLJetsTaggedPtEta", "EffLJetsTaggedPtEta",  binsPtL_.size()-1, &binsPtL_[0],  binsEtaL_.size()-1, &binsEtaL_[0] );
 
// set errors
  hists_["NumEvents"]      ->Sumw2();
  hists_["NumBJets" ]      ->Sumw2();
  hists_["NumBJetsTagged"] ->Sumw2();
  hists_["EffBJetsTagged"] ->Sumw2();
  hists_["NumBJetsPt" ]      ->Sumw2();
  hists_["NumBJetsTaggedPt"] ->Sumw2();
  hists_["EffBJetsTaggedPt"] ->Sumw2();
  hists_["NumBJetsEta" ]      ->Sumw2();
  hists_["NumBJetsTaggedEta"] ->Sumw2();
  hists_["EffBJetsTaggedEta"] ->Sumw2();
  hists2D_["NumBJetsPtEta"    ]   ->Sumw2();
  hists2D_["NumBJetsTaggedPtEta"] ->Sumw2();
  hists2D_["EffBJetsTaggedPtEta"] ->Sumw2();
      
  hists_["NumCJets" ]      ->Sumw2();
  hists_["NumCJetsTagged"] ->Sumw2();
  hists_["EffCJetsTagged"] ->Sumw2();
  hists_["NumCJetsPt" ]      ->Sumw2();
  hists_["NumCJetsTaggedPt"] ->Sumw2();
  hists_["EffCJetsTaggedPt"] ->Sumw2();
  hists_["NumCJetsEta" ]      ->Sumw2();
  hists_["NumCJetsTaggedEta"] ->Sumw2();
  hists_["EffCJetsTaggedEta"] ->Sumw2();
  hists2D_["NumCJetsPtEta"    ]   ->Sumw2();
  hists2D_["NumCJetsTaggedPtEta"] ->Sumw2();
  hists2D_["EffCJetsTaggedPtEta"] ->Sumw2();
  
  hists_["NumLJets" ]      ->Sumw2();
  hists_["NumLJetsTagged"] ->Sumw2();
  hists_["EffLJetsTagged"] ->Sumw2();
  hists_["NumLJetsPt" ]      ->Sumw2();
  hists_["NumLJetsTaggedPt"] ->Sumw2();
  hists_["EffLJetsTaggedPt"] ->Sumw2();
  hists_["NumLJetsEta" ]      ->Sumw2();
  hists_["NumLJetsTaggedEta"] ->Sumw2();
  hists_["EffLJetsTaggedEta"] ->Sumw2();
  hists2D_["NumLJetsPtEta"    ]   ->Sumw2();
  hists2D_["NumLJetsTaggedPtEta"] ->Sumw2();
  hists2D_["EffLJetsTaggedPtEta"] ->Sumw2();
}

/// ...
void 
BTagEfficiencyAnalyzer::endJob() 
{
  /// calculation of b tag efficiencies
  hists_.find("EffBJetsTagged")->second->Divide(hists_.find("NumBJetsTagged")->second, 
                 hists_.find("NumBJets")->second,1,1,"B");
  hists_.find("EffBJetsTaggedPt")->second->Divide(hists_.find("NumBJetsTaggedPt")->second, 
                 hists_.find("NumBJetsPt")->second,1,1,"B");
  hists_.find("EffBJetsTaggedEta")->second->Divide(hists_.find("NumBJetsTaggedEta")->second, 
                 hists_.find("NumBJetsEta")->second,1,1,"B");
  hists2D_.find("EffBJetsTaggedPtEta")->second->Divide(hists2D_.find("NumBJetsTaggedPtEta")->second, 
  hists2D_.find("NumBJetsPtEta")->second,1,1,"B");
  
  hists_.find("EffCJetsTagged")->second->Divide(hists_.find("NumCJetsTagged")->second, 
                 hists_.find("NumCJets")->second,1,1,"B");
  hists_.find("EffCJetsTaggedPt")->second->Divide(hists_.find("NumCJetsTaggedPt")->second, 
                 hists_.find("NumCJetsPt")->second,1,1,"B");
  hists_.find("EffCJetsTaggedEta")->second->Divide(hists_.find("NumCJetsTaggedEta")->second, 
                 hists_.find("NumCJetsEta")->second,1,1,"B");
  hists2D_.find("EffCJetsTaggedPtEta")->second->Divide(hists2D_.find("NumCJetsTaggedPtEta")->second, 
  hists2D_.find("NumCJetsPtEta")->second,1,1,"B");
  
  hists_.find("EffLJetsTagged")->second->Divide(hists_.find("NumLJetsTagged")->second, 
                 hists_.find("NumLJets")->second,1,1,"B");
  hists_.find("EffLJetsTaggedPt")->second->Divide(hists_.find("NumLJetsTaggedPt")->second, 
                 hists_.find("NumLJetsPt")->second,1,1,"B");
  hists_.find("EffLJetsTaggedEta")->second->Divide(hists_.find("NumLJetsTaggedEta")->second, 
                 hists_.find("NumLJetsEta")->second,1,1,"B");
  hists2D_.find("EffLJetsTaggedPtEta")->second->Divide(hists2D_.find("NumLJetsTaggedPtEta")->second, 
  hists2D_.find("NumLJetsPtEta")->second,1,1,"B");
}

//define plugin
#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(BTagEfficiencyAnalyzer);
