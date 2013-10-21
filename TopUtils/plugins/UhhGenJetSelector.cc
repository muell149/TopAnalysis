#include "TopAnalysis/TopUtils/plugins/UhhGenJetSelector.h"

UhhGenJetSelector::UhhGenJetSelector(const edm::ParameterSet& cfg):
  genJet_ ( cfg.getParameter<edm::InputTag>("genJet" )),
  bHadJetIdx_    (cfg.getParameter<edm::InputTag> ("BHadJetIndex"    )),
  antibHadJetIdx_(cfg.getParameter<edm::InputTag> ("AntiBHadJetIndex")),
  pt_     ( cfg.getParameter<double       >("pt"     )),
  eta_    ( cfg.getParameter<double       >("eta"    ))
{
  // register output
  produces<std::vector<reco::GenJet> >();
  produces<std::vector<reco::GenJet> >("lightJetsFromTop");
  produces<std::vector<reco::GenJet> >("additionalJets"  );
}

void
UhhGenJetSelector::produce(edm::Event& evt, const edm::EventSetup& setup)
{
  bool debug=false;
  // read collection from file
  edm::Handle<edm::View<reco::GenJet> > genJet; 
  evt.getByLabel(genJet_, genJet);
  
  // prepare output vector
  std::auto_ptr<std::vector<reco::GenJet> > bJetsOut(  new std::vector<reco::GenJet>);
  std::auto_ptr<std::vector<reco::GenJet> > lJetsOut(  new std::vector<reco::GenJet>);
  std::auto_ptr<std::vector<reco::GenJet> > addJetsOut(new std::vector<reco::GenJet>);
  std::auto_ptr<std::vector<reco::GenJet> > dummy     (new std::vector<reco::GenJet>);

  // info output
  if(debug) {
    std::cout << std::endl << "processing UhhGenJetSelector" << std::endl;
    std::cout << "a) input:" << std::endl;
    std::cout << "- jet acceptance:" << std::endl;
    std::cout << "   pT > "  << pt_  << std::endl;
    std::cout << "   eta< "  << eta_ << std::endl;
  }

  // get indices (e.g. produced by TopAnalysis/TopUtils/GenLevelBJetProducer.cc)
  bIX   =-1;
  bbarIX=-1;
  std::vector<int> VBHadJetIdx, VAntiBHadJetIdx;
  edm::Handle<std::vector<int> > BHadJetIndex, AntiBHadJetIndex;
  evt.getByLabel(bHadJetIdx_    , BHadJetIndex    );
  evt.getByLabel(antibHadJetIdx_, AntiBHadJetIndex);
  // collect them in vector
  if(debug) std::cout << "- BHadJetIndices: "  << std::endl;
  for (int i=0; i<(int) BHadJetIndex->size()    ; ++i){
    // avoid double listing of indices
    if(i==0||(BHadJetIndex->at(i-1)!=BHadJetIndex->at(i))){
      VBHadJetIdx    .push_back(    BHadJetIndex->at(i));
      if(debug) std::cout << "   " << BHadJetIndex->at(i)  << std::endl;
    }
  };
  if(debug) std::cout << "- AntiBHadJetIndices: "  << std::endl;
  for (int i=0; i<(int) AntiBHadJetIndex->size(); ++i){
    // avoid double listing of indices within each list
    if(i==0||(AntiBHadJetIndex->at(i-1)!=AntiBHadJetIndex->at(i))){
      VAntiBHadJetIdx.push_back(AntiBHadJetIndex->at(i));
      if(debug) std::cout << "   " << AntiBHadJetIndex->at(i) << std::endl;
    }
  };
//   // deal with more than one bjet index:
//   // avoid using the same jets
//   if(VBHadJetIdx.size()>1&&VAntiBHadJetIdx.size()==1){
//     // scan B-jet for overlapping entries
//     for(int i=0; i<(int) VBHadJetIdx.size(); ++i){
//       if(VBHadJetIdx[i]==VAntiBHadJetIdx[0]){
// 	// rm overlapping entry in collection with more than one entry
// 	VBHadJetIdx.erase(VBHadJetIdx.begin()+i);
//       }
//     }
//   }
//   if(VAntiBHadJetIdx.size()>1&&VBHadJetIdx.size()==1){
//     // scan ANTI-B-jet for overlapping entries
//     for(int i=0; i<(int) VAntiBHadJetIdx.size(); ++i){
//       if(VAntiBHadJetIdx[i]==VBHadJetIdx[0]){
// 	// rm overlapping entry in collection with more than one entry
// 	VAntiBHadJetIdx.erase(VAntiBHadJetIdx.begin()+i);
//       }
//     }
//   }
  // deal with bjet indices appearing in both index lists
  if(VAntiBHadJetIdx.size()>1&&VBHadJetIdx.size()>1){
    for(int i=0; i<(int) VBHadJetIdx.size(); ++i){
      for(int j=0; j<(int) VAntiBHadJetIdx.size(); ++j){
	if(VAntiBHadJetIdx[j]==VBHadJetIdx[i]){
	  // rm overlapping entry in collection with more than one entry
	  if(VBHadJetIdx.size()==1&&VAntiBHadJetIdx.size()>1) VAntiBHadJetIdx.erase(VAntiBHadJetIdx.begin()+j); 
	  else if(VBHadJetIdx.size()>1&&VAntiBHadJetIdx.size()==1) VBHadJetIdx.erase(VBHadJetIdx.begin()+i);
	  else{
	    VAntiBHadJetIdx.erase(VAntiBHadJetIdx.begin()+j);
	  }
	}
      }
    }
  }
  // choose B-jet index from list
  if(VBHadJetIdx.size()>0){
    for(int i=0; i<(int) VBHadJetIdx.size(); ++i){
      // use indices of jets satisfying the PS cuts if possible, loop reverse to prefer high pt jets in PS
      for(edm::View<reco::GenJet>::const_reverse_iterator p=genJet->rbegin(); p!=genJet->rend(); ++p){
	int currentIndex=genJet->size()-(p-genJet->rbegin())-1; // reverse iterator has last element in collection as element #0; -1 because index starts with 0
	// scan for jet index and prefer jets in kinematic range of reco selection
	if(currentIndex==VBHadJetIdx[i]&&std::abs(p->eta())<eta_&&p->pt()>pt_) bIX=VBHadJetIdx[i];    
      }
    }
    // if not: take leading index
    if(bIX==-1)  bIX   =VBHadJetIdx    [0];
  }
  // choose Anti-B-jet index from list
  if(VAntiBHadJetIdx.size()>0){
    for(int i=0; i<(int) VAntiBHadJetIdx.size(); ++i){
      // use indices of jets satisfying the PS cuts if possible, loop reverse to prefer high pt jets in PS
      for(edm::View<reco::GenJet>::const_reverse_iterator p=genJet->rbegin(); p!=genJet->rend(); ++p){
	int currentIndex=genJet->size()-(p-genJet->rbegin())-1; // reverse iterator has last element in collection as element #0; -1 because index starts with 0
	// scan for jet index and prefer jets in kinematic range of reco selection
	if(currentIndex==VAntiBHadJetIdx[i]&&std::abs(p->eta())<eta_&&p->pt()>pt_) bbarIX=VAntiBHadJetIdx[i]; 
      }
    }
    // if not: take leading index
    if(bbarIX==-1)  bbarIX   =VAntiBHadJetIdx    [0];
  }
  
  // debug output
  if(debug){
     std::cout << " -> chosen bjet-index:      " << bIX    << std::endl;
     std::cout << " -> chosen anti-bjet-index: " << bbarIX << std::endl;
  }
  
  // configuration for light jet candidates
  std::map<float, std::pair<int,int> > jjWcand_;
  double mW=80.4;
  double mWMax=105.;
  double mWMin=65. ;

  // loop input genJet collection
  if(debug) std::cout << "b) scan all genJets" << std::endl;
  bool foundB   =false;
  bool foundBbar=false;
  for(edm::View<reco::GenJet>::const_iterator p=genJet->begin(); p!=genJet->end(); ++p){
    int currentIndex=p-genJet->begin();
    if(debug) std::cout << " - checking jet no. " << currentIndex << "/" << genJet->end()-genJet->begin() << std::endl;
    // check acceptance
    if(std::abs(p->eta())<eta_&&p->pt()>pt_){
      // A find b-jet
      if(currentIndex==bIX){
	if(debug) std::cout << "  -> bjet candidate found!" << std::endl;
	if(std::abs(p->eta())<eta_&&p->pt()>pt_){
	  if(debug) std::cout << std::endl << "   -> selected b-jet! index " << currentIndex << ", ";
	  if(debug) std::cout << "pt=" << p->pt() << ", eta=" << p->eta() << std::endl;
	  bJetsOut->push_back(*p);
	  foundB=true;
	}
	else if(debug) std::cout << "   -> outside acceptance" << std::endl;
      }
      // B find bbar-jet
      else if(currentIndex==bbarIX){
	if(debug) std::cout << "  -> anti-bjet candidate found!" << std::endl;
	if(std::abs(p->eta())<eta_&&p->pt()>pt_){
	  if(debug) std::cout << std::endl << "   -> selected anti b-jet! index " << currentIndex << ", ";
	  if(debug) std::cout << "pt=" << p->pt() << ", eta=" << p->eta() << std::endl;
	  bJetsOut->push_back(*p);
	  foundBbar=true;
	}
	else if(debug) std::cout << "   -> outside acceptance" << std::endl;
      }
      // C find candidates for light jets from W decay
      else{
	// 2nd genjet collection loop (loop only remaining gen jets)
	for(edm::View<reco::GenJet>::const_iterator p2=p+1; p2!=genJet->end(); ++p2){
	  int currentIndex2=p2-genJet->begin();
	  // 2nd check acceptance
	  if(std::abs(p2->eta())<eta_&&p2->pt()>pt_){
	    // no b candidate
	    if(currentIndex2!=bIX&&currentIndex2!=bbarIX){
	      // calculate w mass from candidates
	      double mjj=(p->p4()+p2->p4()).mass();
	      double wcand=std::abs(mjj-mW)/mW;
	      if(mjj>=mWMin&&mjj<=mWMax){
		if(debug){
		  std::cout << "  -> W(jj) candidate: mW(" << currentIndex << "," << currentIndex2 << ")=" << mjj << std::endl;
		  std::cout << "  (|m(j1j2)-" << mW << "|/" << mW << "=" << wcand << ")"<< std::endl;
		}
		jjWcand_[wcand]=std::make_pair(currentIndex,currentIndex2);
	      }
	    }
	  }
	}
      }
    }
  }
  
  // choose light jet pair closest to W mass as light jets from hadronic top candidate
  if(debug) std::cout << "c) find (non-b) genJet pair closest to W mass" << std::endl;
  int lJet1Index=-1;
  int lJet2Index=-1;
  if(jjWcand_.size()){
    lJet1Index=((jjWcand_.begin())->second).first;
    lJet2Index=((jjWcand_.begin())->second).second; 
    if(debug){
      double mWCandRel=(jjWcand_.begin())->first;
      double mWCand=(genJet->at(lJet1Index).p4()+genJet->at(lJet2Index).p4()).mass();
      std::cout << "  -> light jets candidates (closest to W mass found):" << std::endl;
      std::cout << "     mW(jj)=" << mWCand << " GeV (=" << mWCandRel *100 << "% wrt. " << mW << ")" << std::endl;
      std::cout << "     jet1: IX " << lJet1Index << "(pt=" << genJet->at(lJet1Index).pt() << "eta=" << genJet->at(lJet1Index).eta() << ")" << std::endl;
      std::cout << "     jet2: IX " << lJet2Index << "(pt=" << genJet->at(lJet2Index).pt() << "eta=" << genJet->at(lJet2Index).eta() << ")" << std::endl;  
    }
  }
  // add light jets to output
  if(lJet1Index!=-1) lJetsOut->push_back(genJet->at(lJet1Index));
  if(lJet2Index!=-1) lJetsOut->push_back(genJet->at(lJet2Index));

  // D sample additionally radiated jets
  // loop input genJet collection
  if(debug){ std::cout << "d) searching for additionally radiated jets:" << std::endl; }
  if(lJet1Index!=-1&&lJet2Index!=-1&&foundBbar&&foundB){
    if(debug){ std::cout << "- search for leading jet (within PS) not associated to ttbar system: " << std::endl; }
    for(edm::View<reco::GenJet>::const_iterator p=genJet->begin(); p!=genJet->end(); ++p){
      int currentIndex=p-genJet->begin();    
      if(debug) std::cout << "  check jet #" << currentIndex << std::endl;
      // check that its no light jet or b/bbar jet
      if(currentIndex!=bIX&&currentIndex!=bbarIX&&currentIndex!=lJet1Index&&currentIndex!=lJet2Index){
	if(debug) std::cout << "  -> additional jet candidate found!" << std::endl;
	// check acceptance
	if(std::abs(p->eta())<eta_&&p->pt()>pt_){
	  addJetsOut->push_back(*p);
	  if(debug){
	    std::cout << std::endl << "   -> selected additional jet: index " << currentIndex << ", ";
	    std::cout << "pt=" << p->pt() << ", eta=" << p->eta() << std::endl;
	  }
	}
	else if(debug) std::cout << "   -> outside acceptance" << std::endl;
      }
    }
  }
  else if(debug){ std::cout << "- WARNING: only done if both b and light jets from tops have been identified" << std::endl; }

  // E write collections into the event 
  if(debug) std::cout << "e) saving output collection in event" << std::endl;
  // sanity check- need two light jets
  if(!(lJet1Index!=-1&&lJet2Index!=-1)) lJetsOut  ->clear();
  
  // push out new gen jet collection vectors into the event
  evt.put(bJetsOut                      );
  evt.put(lJetsOut  , "lightJetsFromTop");
  evt.put(addJetsOut, "additionalJets"  );
}


bool checkKinematicRange(int index, edm::Handle<edm::View<reco::GenJet> > genJet, double etaVal, double ptVal){
  // loop input collection
  for(edm::View<reco::GenJet>::const_iterator p=genJet->begin(); p!=genJet->end(); ++p){
    int currentIndex=p-genJet->begin();
    // scan for jet index
    if(currentIndex==index){
      // check keinematic range
      if(std::abs(p->eta())<etaVal&&p->pt()>ptVal) return true;
      else return false;
    }
  }
  return false;
}



#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(UhhGenJetSelector);
