#include "TopAnalysis/TopFilter/plugins/KinFitQualityFilter.h"
#include "AnalysisDataFormats/TopObjects/interface/TtFullHadEvtPartons.h"

#include "FWCore/Framework/interface/Event.h"

KinFitQualityFilter::KinFitQualityFilter(const edm::ParameterSet& cfg):
  srcA_            ( cfg.getParameter<edm::InputTag>("srcA"            ) ),
  srcB_            ( cfg.getParameter<edm::InputTag>("srcB"            ) ),
  whichFit_        ( cfg.getParameter<int>          ("whichFit"        ) ),
  maxChi2_         ( cfg.getParameter<double>       ("maxChi2"         ) ),
  minChi2_         ( cfg.getParameter<double>       ("minChi2"         ) ),
  maxProb_         ( cfg.getParameter<double>       ("maxProb"         ) ),
  minProb_         ( cfg.getParameter<double>       ("minProb"         ) ),
  maxbQuarkPt_     ( cfg.getParameter<double>       ("maxbQuarkPt"     ) ),
  minbQuarkPt_     ( cfg.getParameter<double>       ("minbQuarkPt"     ) ),
  maxbQuarkEta_    ( cfg.getParameter<double>       ("maxbQuarkEta"    ) ),
  minbQuarkEta_    ( cfg.getParameter<double>       ("minbQuarkEta"    ) ),
  maxbQuarkPhi_    ( cfg.getParameter<double>       ("maxQuarkPhi"     ) ),
  minbQuarkPhi_    ( cfg.getParameter<double>       ("minQuarkPhi"     ) ),
  maxlightQuarkPt_ ( cfg.getParameter<double>       ("maxlightQuarkPt" ) ),
  minlightQuarkPt_ ( cfg.getParameter<double>       ("minlightQuarkPt" ) ),
  maxlightQuarkEta_( cfg.getParameter<double>       ("maxlightQuarkEta") ),
  minlightQuarkEta_( cfg.getParameter<double>       ("minlightQuarkEta") ),
  maxlightQuarkPhi_( cfg.getParameter<double>       ("maxlightQuarkPhi") ),
  minlightQuarkPhi_( cfg.getParameter<double>       ("minlightQuarkPhi") ),
  useEventWeight_  ( cfg.getParameter<bool>         ("useEventWeight"  ) ),
  weight_          ( cfg.getParameter<edm::InputTag>("weight"          ) ),
  beforeCut_( 0 ), afterCut_( 0 ), beforeCutWeighted_( 0. ), afterCutWeighted_( 0. )
{
}

bool KinFitQualityFilter::filter(edm::Event& event, const edm::EventSetup& setup)
{

  bool pass = false;
  
  double weight = 1.;
  if(useEventWeight_) { 
    edm::Handle<double> weightHandle;
    event.getByLabel(weight_, weightHandle);
    weight = *weightHandle;
  }
  
  ++beforeCut_;
  beforeCutWeighted_ += weight;

  edm::Handle<TtFullHadronicEvent> tops;
  event.getByLabel(srcA_, tops);
  
  if( tops->isHypoValid("kKinFit") ){

    edm::Handle<std::vector<pat::Jet> > jets;
    event.getByLabel(srcB_, jets);

    int lightQ    = tops->jetLeptonCombination("kKinFit", whichFit_)[TtFullHadEvtPartons::LightQ   ];
    int lightQBar = tops->jetLeptonCombination("kKinFit", whichFit_)[TtFullHadEvtPartons::LightQBar];
    int b         = tops->jetLeptonCombination("kKinFit", whichFit_)[TtFullHadEvtPartons::B        ];
    int bBar      = tops->jetLeptonCombination("kKinFit", whichFit_)[TtFullHadEvtPartons::BBar     ];
    int lightP    = tops->jetLeptonCombination("kKinFit", whichFit_)[TtFullHadEvtPartons::LightP   ];
    int lightPBar = tops->jetLeptonCombination("kKinFit", whichFit_)[TtFullHadEvtPartons::LightPBar];
    
    if( maxChi2_ >= tops->fitChi2(whichFit_) && maxProb_ >= tops->fitProb(whichFit_) &&

	maxbQuarkPt_     >= ((*jets)[b].pt()        -tops->b("kKinFit", whichFit_)        ->pt())/(*jets)[b].pt()         &&
	maxbQuarkPt_     >= ((*jets)[bBar].pt()     -tops->bBar("kKinFit", whichFit_)     ->pt())/(*jets)[bBar].pt()      &&
	maxlightQuarkPt_ >= ((*jets)[lightQ].pt()   -tops->lightQ("kKinFit", whichFit_)   ->pt())/(*jets)[lightQ].pt()    &&
	maxlightQuarkPt_ >= ((*jets)[lightQBar].pt()-tops->lightQBar("kKinFit", whichFit_)->pt())/(*jets)[lightQBar].pt() &&
	maxlightQuarkPt_ >= ((*jets)[lightP].pt()   -tops->lightP("kKinFit", whichFit_)   ->pt())/(*jets)[lightP].pt()    &&
	maxlightQuarkPt_ >= ((*jets)[lightPBar].pt()-tops->lightPBar("kKinFit", whichFit_)->pt())/(*jets)[lightPBar].pt() &&

	maxbQuarkEta_     >= (*jets)[b].eta()        -tops->b("kKinFit", whichFit_)        ->eta() &&
	maxbQuarkEta_     >= (*jets)[bBar].eta()     -tops->bBar("kKinFit", whichFit_)     ->eta() &&
	maxlightQuarkEta_ >= (*jets)[lightQ].eta()   -tops->lightQ("kKinFit", whichFit_)   ->eta() &&
	maxlightQuarkEta_ >= (*jets)[lightQBar].eta()-tops->lightQBar("kKinFit", whichFit_)->eta() &&
	maxlightQuarkEta_ >= (*jets)[lightP].eta()   -tops->lightP("kKinFit", whichFit_)   ->eta() &&
	maxlightQuarkEta_ >= (*jets)[lightPBar].eta()-tops->lightPBar("kKinFit", whichFit_)->eta() &&

	maxbQuarkPhi_     >= (*jets)[b].phi()        -tops->b("kKinFit", whichFit_)        ->phi() &&
	maxbQuarkPhi_     >= (*jets)[bBar].phi()     -tops->bBar("kKinFit", whichFit_)     ->phi() &&
	maxlightQuarkPhi_ >= (*jets)[lightQ].phi()   -tops->lightQ("kKinFit", whichFit_)   ->phi() &&
	maxlightQuarkPhi_ >= (*jets)[lightQBar].phi()-tops->lightQBar("kKinFit", whichFit_)->phi() &&
	maxlightQuarkPhi_ >= (*jets)[lightP].phi()   -tops->lightP("kKinFit", whichFit_)   ->phi() &&
	maxlightQuarkPhi_ >= (*jets)[lightPBar].phi()-tops->lightPBar("kKinFit", whichFit_)->phi() && 

	minChi2_ <= tops->fitChi2(whichFit_) && minProb_ <= tops->fitProb(whichFit_) &&

	minbQuarkPt_     <= ((*jets)[b].pt()        -tops->b("kKinFit", whichFit_)        ->pt())/(*jets)[b].pt()         &&
	minbQuarkPt_     <= ((*jets)[bBar].pt()     -tops->bBar("kKinFit", whichFit_)     ->pt())/(*jets)[bBar].pt()      &&
	minlightQuarkPt_ <= ((*jets)[lightQ].pt()   -tops->lightQ("kKinFit", whichFit_)   ->pt())/(*jets)[lightQ].pt()    &&
	minlightQuarkPt_ <= ((*jets)[lightQBar].pt()-tops->lightQBar("kKinFit", whichFit_)->pt())/(*jets)[lightQBar].pt() &&
	minlightQuarkPt_ <= ((*jets)[lightP].pt()   -tops->lightP("kKinFit", whichFit_)   ->pt())/(*jets)[lightP].pt()    &&
	minlightQuarkPt_ <= ((*jets)[lightPBar].pt()-tops->lightPBar("kKinFit", whichFit_)->pt())/(*jets)[lightPBar].pt() &&

	minbQuarkEta_     <= (*jets)[b].eta()        -tops->b("kKinFit", whichFit_)        ->eta() &&
	minbQuarkEta_     <= (*jets)[bBar].eta()     -tops->bBar("kKinFit", whichFit_)     ->eta() &&
	minlightQuarkEta_ <= (*jets)[lightQ].eta()   -tops->lightQ("kKinFit", whichFit_)   ->eta() &&
	minlightQuarkEta_ <= (*jets)[lightQBar].eta()-tops->lightQBar("kKinFit", whichFit_)->eta() &&
	minlightQuarkEta_ <= (*jets)[lightP].eta()   -tops->lightP("kKinFit", whichFit_)   ->eta() &&
	minlightQuarkEta_ <= (*jets)[lightPBar].eta()-tops->lightPBar("kKinFit", whichFit_)->eta() &&

	minbQuarkPhi_     <= (*jets)[b].phi()        -tops->b("kKinFit", whichFit_)        ->phi() &&
	minbQuarkPhi_     <= (*jets)[bBar].phi()     -tops->bBar("kKinFit", whichFit_)     ->phi() &&
	minlightQuarkPhi_ <= (*jets)[lightQ].phi()   -tops->lightQ("kKinFit", whichFit_)   ->phi() &&
	minlightQuarkPhi_ <= (*jets)[lightQBar].phi()-tops->lightQBar("kKinFit", whichFit_)->phi() &&
	minlightQuarkPhi_ <= (*jets)[lightP].phi()   -tops->lightP("kKinFit", whichFit_)   ->phi() &&
	minlightQuarkPhi_ <= (*jets)[lightPBar].phi()-tops->lightPBar("kKinFit", whichFit_)->phi() ){
      
      pass=true;
      
      ++afterCut_;
      afterCutWeighted_ += weight;
    }
  }
  return pass;
}

void KinFitQualityFilter::beginJob(const edm::EventSetup& setup)
{
}

void KinFitQualityFilter::endJob()
{
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( KinFitQualityFilter );
