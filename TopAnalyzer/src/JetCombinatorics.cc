#include "TopAnalysis/TopAnalyzer/interface/JetCombinatorics.h"

#include "AnalysisDataFormats/TopObjects/interface/TtSemiLepEvtPartons.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include <iostream>
#include <iomanip>

/// default constructor
JetCombinatorics::JetCombinatorics(const edm::ParameterSet& cfg) :
  hypoKey_( cfg.getParameter<std::string>("hypoKey") )
{

  nEventsStudy_ = 0;
 
  for(unsigned i=0; i<6; i++)
    nEventsGood_.push_back(0);

}

/// histogramm booking
void JetCombinatorics::book(edm::Service<TFileService>& fs)
{
  hists_["numbEvents"] = fs->make<TH1F>( "numbEvents", "number of events", 6, 0., 6.);
}

/// histogram filling
void
JetCombinatorics::fill(const TtSemiLeptonicEvent& semiLepEvt, const double& weight)
{

  if( !semiLepEvt.isHypoValid(hypoKey_) ||
      !semiLepEvt.isHypoValid("kGenMatch") ) return;

  bool good[6];
  // good0: LepB correct
  // good1: HadB correct
  // good2: HadW correct
  // good3: HadT correct
  // good4: good1 && good2
  // good5: good0 && good4

  nEventsStudy_++;
  
  good[0] = (semiLepEvt.jetLeptonCombination(hypoKey_)   [TtSemiLepEvtPartons::LepB] ==
	     semiLepEvt.jetLeptonCombination("kGenMatch")[TtSemiLepEvtPartons::LepB]);
    
  good[1] = (semiLepEvt.jetLeptonCombination(hypoKey_)   [TtSemiLepEvtPartons::HadB] ==
	     semiLepEvt.jetLeptonCombination("kGenMatch")[TtSemiLepEvtPartons::HadB]);
    
  std::vector<int> HadWJets;
  HadWJets.push_back( TtSemiLepEvtPartons::LightQ    );
  HadWJets.push_back( TtSemiLepEvtPartons::LightQBar );
    
  std::vector<int> HadTJets;
  HadTJets.push_back( TtSemiLepEvtPartons::LightQ    );
  HadTJets.push_back( TtSemiLepEvtPartons::LightQBar );
  HadTJets.push_back( TtSemiLepEvtPartons::HadB      );
    
  good[2] = sameJets( semiLepEvt, hypoKey_, "kGenMatch", HadWJets);
  
  good[3] = sameJets( semiLepEvt, hypoKey_, "kGenMatch", HadTJets);
    
  good[4] = (good[1] && good[2]);
  good[5] = (good[0] && good[4]);

  for(unsigned i=0; i<6; i++)
    if(good[i]) nEventsGood_.at(i)++;

}

bool
JetCombinatorics::sameJets(const TtSemiLeptonicEvent& semiLepEvt,
			   const std::string& hyp1,
			   const std::string& hyp2,
			   const std::vector<int>& jetsToCompare)
{

  std::vector<int> jetIndicesHyp1;
  std::vector<int> jetIndicesHyp2;

  for(unsigned i = 0; i < jetsToCompare.size(); i++) {
    jetIndicesHyp1.push_back( (semiLepEvt.jetLeptonCombination(hyp1))[ jetsToCompare[i] ] );
    jetIndicesHyp2.push_back( (semiLepEvt.jetLeptonCombination(hyp2))[ jetsToCompare[i] ] );
  }

  std::sort( jetIndicesHyp1.begin(), jetIndicesHyp1.end() );
  std::sort( jetIndicesHyp2.begin(), jetIndicesHyp2.end() );

  return (jetIndicesHyp1==jetIndicesHyp2);
  
}

void
JetCombinatorics::process()
{

  hists_.find("numbEvents")->second->SetBinContent(1, nEventsStudy_);


  for(unsigned i=0; i<6; i++) {
    hists_.find("numbEvents")->second->SetBinContent(2+i, nEventsGood_.at(i));
  }

  edm::LogInfo summary("JetCombinatoricsAnalyzer");

  summary << "HypoKey: " << hypoKey_ << "\n";

  for(unsigned i=0; i<6; i++)
    summary << "Number, fraction of events (good" << i+1 << "): "
	    << std::setw(6) << nEventsGood_.at(i) << ", "
	    << std::setw(6) << std::fixed << std::setprecision(3) << (double)nEventsGood_.at(i)/nEventsStudy_ << "\n";

}
