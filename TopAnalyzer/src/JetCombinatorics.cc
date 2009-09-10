#include "TopAnalysis/TopAnalyzer/interface/JetCombinatorics.h"

#include "AnalysisDataFormats/TopObjects/interface/TtSemiLepEvtPartons.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include <Math/VectorUtil.h>

#include <iostream>
#include <iomanip>

/// default constructor
JetCombinatorics::JetCombinatorics(const edm::ParameterSet& cfg) :
  hypoKey_( cfg.getParameter<std::string>("hypoKey") )
{

  nEventsTotal_ = 0;
  nEventsStudy_ = 0;
 
  for(unsigned i=0; i<6; i++)
    nEventsGood_.push_back(0);

}

/// histogramm booking
void JetCombinatorics::book(edm::Service<TFileService>& fs)
{

  hists_["numbEvents"] = fs->make<TH1F>( "numbEvents", "number of events", 6, 0., 6.);

  // parton Pt
  hists_["partonPtLepB"] = fs->make<TH1F>( "partonPtLepB", "partonPtLepB", 40, 0., 200.);
  hists_["partonPtHadB"] = fs->make<TH1F>( "partonPtHadB", "partonPtHadB", 40, 0., 200.);
  hists_["partonPtHadQ"] = fs->make<TH1F>( "partonPtHadQ", "partonPtHadQ", 40, 0., 200.);

  // parton Eta
  hists_["partonEtaLepB"] = fs->make<TH1F>( "partonEtaLepB", "partonEtaLepB", 40, 0., 4.);
  hists_["partonEtaHadB"] = fs->make<TH1F>( "partonEtaHadB", "partonEtaHadB", 40, 0., 4.);
  hists_["partonEtaHadQ"] = fs->make<TH1F>( "partonEtaHadQ", "partonEtaHadQ", 40, 0., 4.);

  hists_["partonDeltaRHadQ"] = fs->make<TH1F>( "partonDeltaRHadQ", "partonDeltaRHadQ", 40, 0., 4.);

}

/// histogram filling
void
JetCombinatorics::fill(const TtSemiLeptonicEvent& semiLepEvt, const double& weight)
{

  nEventsTotal_++;

  hists_.find("partonPtLepB")->second->Fill( semiLepEvt.leptonicDecayB()       ->pt() , weight );
  hists_.find("partonPtHadB")->second->Fill( semiLepEvt.hadronicDecayB()       ->pt() , weight );
  hists_.find("partonPtHadQ")->second->Fill( semiLepEvt.hadronicDecayQuark()   ->pt() , weight );
  hists_.find("partonPtHadQ")->second->Fill( semiLepEvt.hadronicDecayQuarkBar()->pt() , weight );

  hists_.find("partonEtaLepB")->second->Fill( semiLepEvt.leptonicDecayB()       ->eta() , weight );
  hists_.find("partonEtaHadB")->second->Fill( semiLepEvt.hadronicDecayB()       ->eta() , weight );
  hists_.find("partonEtaHadQ")->second->Fill( semiLepEvt.hadronicDecayQuark()   ->eta() , weight );
  hists_.find("partonEtaHadQ")->second->Fill( semiLepEvt.hadronicDecayQuarkBar()->eta() , weight );

  hists_.find("partonDeltaRHadQ")->second->Fill( ROOT::Math::VectorUtil::DeltaR(semiLepEvt.hadronicDecayQuark   ()->p4(),
										semiLepEvt.hadronicDecayQuarkBar()->p4()) ,
						 weight );

  if( (!semiLepEvt.isHypoValid(hypoKey_) && hypoKey_!="kGenMatch") 
      || (hypoKey_=="kKinFit" && semiLepEvt.fitProb()<0.01)) return;

  nEventsStudy_++;

  bool valid[6];
  bool good [6];
  // 0: LepB correct
  // 1: HadB correct
  // 2: HadW correct
  // 3: HadT correct
  // 4: good1 && good2
  // 5: good0 && good4
  
  valid[0] = (semiLepEvt.jetLeptonCombination("kGenMatch")[TtSemiLepEvtPartons::LepB] >= 0 );

  good[0] = (valid[0] && semiLepEvt.jetLeptonCombination(hypoKey_)   [TtSemiLepEvtPartons::LepB] ==
	                 semiLepEvt.jetLeptonCombination("kGenMatch")[TtSemiLepEvtPartons::LepB]);

  valid[1] = (semiLepEvt.jetLeptonCombination("kGenMatch")[TtSemiLepEvtPartons::HadB] >= 0 );    

  good[1] = (valid[1] && semiLepEvt.jetLeptonCombination(hypoKey_)   [TtSemiLepEvtPartons::HadB] ==
	                 semiLepEvt.jetLeptonCombination("kGenMatch")[TtSemiLepEvtPartons::HadB]);
    
  std::vector<int> HadWJets;
  HadWJets.push_back( TtSemiLepEvtPartons::LightQ    );
  HadWJets.push_back( TtSemiLepEvtPartons::LightQBar );

  valid[2] = (semiLepEvt.jetLeptonCombination("kGenMatch")[TtSemiLepEvtPartons::LightQ   ] >= 0 &&
	      semiLepEvt.jetLeptonCombination("kGenMatch")[TtSemiLepEvtPartons::LightQBar] >= 0);
    
  good[2] = (valid[2] && sameJets( semiLepEvt, hypoKey_, "kGenMatch", HadWJets));

  std::vector<int> HadTJets;
  HadTJets.push_back( TtSemiLepEvtPartons::LightQ    );
  HadTJets.push_back( TtSemiLepEvtPartons::LightQBar );
  HadTJets.push_back( TtSemiLepEvtPartons::HadB      );

  valid[3] = (valid[1] && valid[2]);
  
  good[3] = (valid[3] && sameJets( semiLepEvt, hypoKey_, "kGenMatch", HadTJets));

  valid[4] = valid[3];

  good[4] = (valid[4] && good[1] && good[2]);

  valid[5] = (valid[0] && valid[3]);

  good[5] = (valid[5] && good[0] && good[4]);

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

double efficiencyError(const int eventsAfter, const int eventsBefore)
{
  double eff = (double)eventsAfter/eventsBefore;
  return sqrt(eff*(1-eff)/eventsBefore);
}

void
JetCombinatorics::process()
{

  //  hists_.find("numbEvents")->second->SetBinContent(1, nEventsStudy_);
  //
  //  for(unsigned i=0; i<6; i++) {
  //    hists_.find("numbEvents")->second->SetBinContent(2+i, nEventsGood_.at(i));
  //  }

  edm::LogInfo summary("JetCombinatoricsAnalyzer");

  summary << "HypoKey: " << hypoKey_ << "\n";

  summary << "Number, fraction of events (total): "
	  << std::setw(6) << nEventsTotal_ <<  " / " << nEventsTotal_ << " , "
	  << std::setw(6) << std::fixed << std::setprecision(4) << (double)nEventsTotal_/nEventsTotal_ << "\n";

  summary << "Number, fraction of events (study): "
	  << std::setw(6) << nEventsStudy_ <<  " / " << nEventsTotal_ << " , "
	  << std::setw(6) << std::fixed << std::setprecision(4) << (double)nEventsStudy_/nEventsTotal_
	  << " +/- "
	  << std::setw(6) << std::fixed << std::setprecision(4) << efficiencyError(nEventsStudy_,
										   nEventsTotal_)
	  << "\n";
  

  for(unsigned i=0; i<6; i++)
    summary << "Number, fraction of events (good" << i << "): "
	    << std::setw(6) << nEventsGood_.at(i) << " / " << nEventsStudy_ << " , "
	    << std::setw(6) << std::fixed << std::setprecision(4) << (double)nEventsGood_.at(i)/nEventsStudy_
	    << " +/- "
	    << std::setw(6) << std::fixed << std::setprecision(4) << efficiencyError(nEventsGood_.at(i),
										     nEventsStudy_)
	    << "\n";

}
