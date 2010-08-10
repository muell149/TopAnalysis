#include "TopAnalysis/TopAnalyzer/interface/METKinFitAnalyzer.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/LeafCandidate.h"
#include "AnalysisDataFormats/TopObjects/interface/TtFullHadEvtPartons.h"
#include "AnalysisDataFormats/TopObjects/interface/TtFullHadronicEvent.h"

/// default constructor
METKinFitAnalyzer::METKinFitAnalyzer(const edm::ParameterSet& cfg)
{
  METSrc_ = cfg.getParameter<edm::InputTag>("METSrc");
  JetSrc_ = cfg.getParameter<edm::InputTag>("JetSrc");
  FitSrc_ = cfg.getParameter<edm::InputTag>("FitSrc");
}

/// initiate histograms
void
METKinFitAnalyzer::beginJob()
{
  edm::Service<TFileService> fs;
  if( !fs ) throw edm::Exception( edm::errors::Configuration, "TFile Service is not registered in cfg file" );

  // pre-fit MET
  hists_["preFitMET"    ] = fs->make<TH1F>( "preFitMET"     , "preFitMET"     ,  400,  0. , 400. );
  // post-fit MET
  hists_["postFitMET"   ] = fs->make<TH1F>( "postFitMET"    , "postFitMET"    ,  400,  0. , 400. );
 }

/// analyze triggers and fill histograms
void
METKinFitAnalyzer::analyze(const edm::Event& event, const edm::EventSetup&)
{

  edm::Handle<TtFullHadronicEvent> tops;
  event.getByLabel(FitSrc_, tops);

  edm::Handle<edm::View< reco::LeafCandidate > > jets;
  event.getByLabel(JetSrc_, jets);

  edm::Handle<edm::View< reco::LeafCandidate > > MET;
  event.getByLabel(METSrc_, MET);
  
  // make sure to have a valid hypothesis on reconstruction level
  if( tops->isHypoValid("kKinFit") ){
    int lightQ    = tops->jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::LightQ   ];
    int lightQBar = tops->jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::LightQBar];
    int b         = tops->jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::B        ];
    int bBar      = tops->jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::BBar     ];
    int lightP    = tops->jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::LightP   ];
    int lightPBar = tops->jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::LightPBar];
    
    double met = MET->begin()->pt();
    double metFit = (MET->begin()->p4() - 
		     jets->at(lightQ).p4() - jets->at(lightQBar).p4() - jets->at(b).p4() -
		     jets->at(lightP).p4() - jets->at(lightPBar).p4() - jets->at(bBar).p4() +
		     tops->lightQ("kKinFit")->p4() + tops->lightQBar("kKinFit")->p4() + tops->b("kKinFit")->p4() +
		     tops->lightP("kKinFit")->p4() + tops->lightPBar("kKinFit")->p4() + tops->bBar("kKinFit")->p4()).Pt();

    //double test = (jets->at(lightQ).p4() + jets->at(lightQBar).p4() + jets->at(b).p4() + jets->at(lightP).p4() + jets->at(lightPBar).p4() + jets->at(bBar).p4() -
    //		   tops->lightQ("kKinFit")->p4() - tops->lightQBar("kKinFit")->p4() - tops->b("kKinFit")->p4() -
    //		   tops->lightP("kKinFit")->p4() - tops->lightPBar("kKinFit")->p4() - tops->bBar("kKinFit")->p4()).Pt();

    hists_.find("preFitMET" )->second->Fill( met );
    hists_.find("postFitMET")->second->Fill( metFit );

    //std::cout << "Et LQ : " << jets->at(lightQ).pt()    << " -> " << tops->lightQ("kKinFit")->pt()    << std::endl;
    //std::cout << "Et LQB: " << jets->at(lightQBar).pt() << " -> " << tops->lightQBar("kKinFit")->pt() << std::endl;
    //std::cout << "Et LP : " << jets->at(lightP).pt()    << " -> " << tops->lightP("kKinFit")->pt()    << std::endl;
    //std::cout << "Et LPB: " << jets->at(lightPBar).pt() << " -> " << tops->lightPBar("kKinFit")->pt() << std::endl;
    //std::cout << "Et B  : " << jets->at(b).pt()         << " -> " << tops->b("kKinFit")->pt()         << std::endl;
    //std::cout << "Et BB : " << jets->at(bBar).pt()      << " -> " << tops->bBar("kKinFit")->pt()      << std::endl;
    //std::cout << "Met: " << met << " -> " << metFit << "; 0 = " << test << " prob: " << tops->fitProb() << std::endl;

  }
}

void
METKinFitAnalyzer::endJob()
{
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( METKinFitAnalyzer );
