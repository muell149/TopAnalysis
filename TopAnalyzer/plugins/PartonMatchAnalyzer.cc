#include "TopAnalysis/TopAnalyzer/plugins/PartonMatchAnalyzer.h"
#include "TopQuarkAnalysis/TopTools/interface/JetPartonMatching.h"

PartonMatchAnalyzer::PartonMatchAnalyzer(const edm::ParameterSet& cfg):
  jets_ (cfg.getParameter<edm::InputTag>("jets")),
  hist_ (cfg.getParameter<std::string>("file")),
  nJets_(cfg.getParameter<int>("nJets")),
  useDeltaR_(cfg.getParameter<bool>("useDeltaR")),
  useMaxDist_(cfg.getParameter<bool>("useMaxDist")),
  maxDist_(cfg.getParameter<double>("maxDist"))
{
  cutmon.name("JetPartonMatchAnalyzer");
  cutmon.add("sample",                      Cut::Boolean, true);
  cutmon.add("outlier in totalMinDist",     Cut::Boolean, true);
  cutmon.add("outlier in minSumDist",       Cut::Boolean, true);
  cutmon.add("outlier in ptOrderedMinDist", Cut::Boolean, true);
  cutmon.add("outlier in unambiguousOnly",  Cut::Boolean, true);
  cutmon.add("allConsistent",               Cut::Boolean, true);
  cutmon.add("inconsistencies (w/o outl.)", Cut::Boolean, true);
}

void
PartonMatchAnalyzer::analyze(const edm::Event& evt, const edm::EventSetup& setup)
{
  cutmon.select("sample", true);

  edm::Handle<TtGenEvent> genEvt;
  evt.getByLabel("genEvt", genEvt);

  edm::Handle<std::vector<pat::Jet> > topJets;
  evt.getByLabel(jets_, topJets);

  // prepare vector of partons
  std::vector<const reco::Candidate*> partons;
  partons.push_back( genEvt->hadronicDecayQuark() );
  partons.push_back( genEvt->hadronicDecayQuarkBar() );
  partons.push_back( genEvt->hadronicDecayB() );
  partons.push_back( genEvt->leptonicDecayB() );

  // prepare vector of jets
  std::vector<pat::JetType> jets;
  for(unsigned int idx=0; idx<topJets->size(); ++idx){
    if(nJets_>=partons.size() && idx == nJets_) break;
    jets.push_back( (*topJets)[idx].recJet() );
  }

  // do the matching
  std::vector<JetPartonMatching> jetPartonMatch;

  // fill vector of algorithms; number 
  // of available algorithms is 4, idx 
  // is the number od the algorithm
  unsigned int nAlgos = 4;
  for(unsigned int idx=0; idx<nAlgos; ++idx){
    jetPartonMatch.push_back( JetPartonMatching(partons, jets, idx, useMaxDist_, useDeltaR_, maxDist_) );
  }

  // check if different algorithms give 
  // the same matching
  bool consistent=true;
  bool outlierRejected=false;
  for(unsigned int idx=0; idx<nAlgos; idx++) {
    if(jetPartonMatch[idx].getNumberOfUnmatchedPartons()>0) {
      outlierRejected=true;
      switch(idx) {
      case JetPartonMatching::totalMinDist:
	cutmon.select("outlier in totalMinDist", true);
	break;
      case JetPartonMatching::minSumDist:
	cutmon.select("outlier in minSumDist", true);
	break;
      case JetPartonMatching::ptOrderedMinDist:
	cutmon.select("outlier in ptOrderedMinDist", true);
	break;
      case JetPartonMatching::unambiguousOnly:
	cutmon.select("outlier in unambiguousOnly", true);
      }
    }
  }

  if(!outlierRejected){
    for(unsigned int idx=0; idx<partons.size(); ++idx){
      // loop over the four partons
      for(unsigned int jdx=1; jdx<nAlgos; ++jdx){
	// loop over algorithms
	if(jetPartonMatch[0].getMatchForParton(idx)!=jetPartonMatch[jdx].getMatchForParton(idx)){
	  consistent = false;
	  break;
	}
      }
      if(!consistent) break;
    }
    if(consistent)
      cutmon.select("allConsistent", true);
    else{
      cutmon.select("inconsistencies", true);
      std::cout << "Inconsistency between different jet-parton matching algorithms!" << std::endl;
      for(unsigned int idx=0; idx<partons.size(); ++idx){
	for(unsigned int jdx=0; jdx<nAlgos; ++jdx)
	  std::cout << jetPartonMatch[jdx].getMatchForParton(idx) << " ";
	std::cout << std::endl;
      }
      for(unsigned int idx=0; idx<nAlgos; ++idx){
	// loop over algorithms
	std::cout << "Algorithm " << idx << " : "
		  << "SumDeltaR / SumDeltaE / SumDeltaPt = ";
	std::cout << jetPartonMatch[idx].getSumDeltaR() << " / "
		  << jetPartonMatch[idx].getSumDeltaE() << " / "
		  << jetPartonMatch[idx].getSumDeltaPt() << std::endl;
      }
    }
  }
}

void 
PartonMatchAnalyzer::beginJob(const edm::EventSetup&)
{
}

void 
PartonMatchAnalyzer::endJob() 
{
  if(hist_.empty())
    cutmon.print();
  else{
    ofstream hist(hist_.c_str(), std::ios::out);
    cutmon.print( hist );
  }
}
