/* \class TtbarChannelSelector
 *
 * \author Dirk Dammann
 *
 * \decription: decay channels are coded by numbers.
 *              signal dimuon channel is 33
 *              with tau going to mu also: 66, 36, 63
 */
#include <memory>  
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "FWCore/Framework/interface/MakerMacros.h"

using namespace std;

class TtbarChannelSelector : public edm::EDFilter {
 public:
  explicit TtbarChannelSelector(const edm::ParameterSet&);
  ~TtbarChannelSelector();
  
 private:  
  virtual void beginJob(const edm::EventSetup&);
  virtual bool filter(edm::Event&, const edm::EventSetup&);
  virtual void endJob(); 

  bool check(edm::Event&, const edm::EventSetup&);  
  int wDecay(); 
  int tauDecay();
  
  edm::InputTag src_;
  int nEvents_;
  int nEvts, nHits;

  bool SingleTopHadronic_;
  bool SingleTopElectron_;
  bool SingleTopMuon_; 
  bool SingleTopTau_;
  bool TtbarHadronic_;
  bool TtbarSemiElec_;
  bool TtbarSemiMuon_; 
  bool TtbarSemiTau_;
  bool TtbarElecElec_;
  bool TtbarMuonMuon_;
  bool TtbarTauTau_;
  bool TtbarElecMuon_;
  bool TtbarElecTau_;    
  bool TtbarMuonTau_; 
  bool TauHadronic_;
  bool TauElec_; 
  bool TauMuon_;
  bool invert_;   
    
  vector<int> selectedChannels; 
  unsigned int selChSize; 
  
  const reco::Candidate* bquark;
  const reco::Candidate* wbos;
  const reco::Candidate* tau;
  const reco::Candidate* wdaugh1;
  const reco::Candidate* wdaugh2;     
};


TtbarChannelSelector::TtbarChannelSelector(const edm::ParameterSet& cfg) :
  src_              (cfg.getParameter<edm::InputTag>("src"      )),
  nEvents_          (cfg.getParameter<int> ("n_events"          )),  
  SingleTopHadronic_(cfg.getParameter<bool>("SingleTop_Hadronic")),  
  SingleTopElectron_(cfg.getParameter<bool>("SingleTop_Electron")),  
  SingleTopMuon_    (cfg.getParameter<bool>("SingleTop_Muon"    )),  
  SingleTopTau_     (cfg.getParameter<bool>("SingleTop_Tau"     )),  
  TtbarHadronic_    (cfg.getParameter<bool>("Ttbar_Hadronic"    )), 
  TtbarSemiElec_    (cfg.getParameter<bool>("Ttbar_SemiElec"    )),   
  TtbarSemiMuon_    (cfg.getParameter<bool>("Ttbar_SemiMuon"    )),   
  TtbarSemiTau_     (cfg.getParameter<bool>("Ttbar_SemiTau"     )),   
  TtbarElecElec_    (cfg.getParameter<bool>("Ttbar_ElecElec"    )),   
  TtbarMuonMuon_    (cfg.getParameter<bool>("Ttbar_MuonMuon"    )),   
  TtbarTauTau_      (cfg.getParameter<bool>("Ttbar_TauTau"      )), 
  TtbarElecMuon_    (cfg.getParameter<bool>("Ttbar_ElecMuon"    )),   
  TtbarElecTau_     (cfg.getParameter<bool>("Ttbar_ElecTau"     )),   
  TtbarMuonTau_     (cfg.getParameter<bool>("Ttbar_MuonTau"     )),
  TauHadronic_      (cfg.getParameter<bool>("Tau_Hadronic"      )),   
  TauElec_          (cfg.getParameter<bool>("Tau_Elec"          )),
  TauMuon_          (cfg.getParameter<bool>("Tau_Muon"          )),
  invert_           (cfg.getParameter<bool>("invert_selection"  ))              
{
  nEvts = 0;
  nHits = 0;     
}


TtbarChannelSelector::~TtbarChannelSelector() { 
}


bool TtbarChannelSelector::filter(edm::Event& evt, const edm::EventSetup& es) {
    nEvts++;
    bool result = check( evt, es);
    if(result) nHits++;
    return result;
}

bool TtbarChannelSelector::check(edm::Event& evt, const edm::EventSetup& es) {  
  if(nEvents_!=-1){
    if(nHits >= nEvents_){
      return false;      
    }
  }
  
  bool Pass;
  bool Block;
  
  if (invert_==false){
    Block = false;
    Pass  = true;
  }
  else{
    Block = true;
    Pass  = false;    
  }
        
  int decayVl = 0;
  
  bquark = 0;
  wbos = 0;
  tau = 0;
  wdaugh1 = 0;
  wdaugh2 = 0;
  
  edm::Handle<reco::GenParticleCollection> genParticles;
  evt.getByLabel(src_, genParticles);
  
  for(reco::GenParticleCollection::const_iterator cand = genParticles->begin(); cand!=genParticles->end(); ++cand) {
    if(abs(cand->pdgId())!=6) continue; 
    
    for(size_t i=0; i<cand->numberOfDaughters(); ++i){        
      if(abs(cand->daughter(i)->pdgId())==5){
	bquark = cand->daughter(i);
      }
      if(abs(cand->daughter(i)->pdgId())==24){
	wbos = cand->daughter(i);	  	  
      }	
    }
    // in few event the top decays to s or d
    if(bquark==0){ 
      cout << "MESSAGE: top does not decay to b." << endl;
      return Block;
    }
    // in some MC the w is not in the decay chain but directly its decay products
    if(wbos==0){
      // search for top daughters which are neither the b nor a radiated gluon
      for(size_t i=0; i<cand->numberOfDaughters(); ++i){        
        if(abs(cand->daughter(i)->pdgId())!=5 && cand->daughter(i)->pdgId()!=21){
	  wdaugh1 = cand->daughter(i);
	  break;
	}
      }
      for(size_t i=0; i<cand->numberOfDaughters(); ++i){   	  
        if(abs(cand->daughter(i)->pdgId())!=5 && cand->daughter(i)->pdgId()!=21 && 
	 cand->daughter(i)!=wdaugh1){	     
	   wdaugh2 = cand->daughter(i);	  	  
	}	  	
      }			        
    }
    else{
      // if w is in decay chain search for its daughters
      if(wbos->numberOfDaughters()>=2){
        wdaugh1 = wbos->daughter(0);
	wdaugh2 = wbos->daughter(1);
      }   	      
    }
    if(wdaugh1==0 || wdaugh2==0){
      cout << "MESSAGE: top has no good daughters" << endl;
      return Block;	
    }
    // calculate the decay value from the w decays
    int wNumber = wDecay();
    
    if(wNumber<0) return Block;
    
    if(cand->pdgId()==6){ 
      decayVl = decayVl + 10*wNumber;
    }
    else{
      decayVl = decayVl + wNumber;	  
    }           
  }

  for(unsigned int i=0; i<selChSize; i++){
    if(decayVl==selectedChannels.at(i)){ 
      int selectedTauChannel = selectedChannels[i];     
      if(selectedTauChannel/10 > 3 || selectedTauChannel%10 > 3){ //that means if a tau channel is selected
        if(!TauHadronic_ && (decayVl/10==4 || decayVl%10==4)) return Block;
        if(!TauElec_     && (decayVl/10==5 || decayVl%10==5)) return Block;
        if(!TauMuon_     && (decayVl/10==6 || decayVl%10==6)) return Block;	  	    	
      }           
      return Pass;
    }
  }      
  return Block;
}   

int TtbarChannelSelector::wDecay(){
  if((abs(wdaugh1->pdgId())<6)||(abs(wdaugh2->pdgId())<6)){	  
    return 1; 
  }
  if((abs(wdaugh1->pdgId())==11)||(abs(wdaugh2->pdgId())==11)){	  
    return 2;	    
  }
  if((abs(wdaugh1->pdgId())==13)||(abs(wdaugh2->pdgId())==13)){	  
    return 3;
  }
  if((abs(wdaugh1->pdgId())==15)||(abs(wdaugh2->pdgId())==15)){
    tau = wdaugh2;
    if(abs(wdaugh1->pdgId())==15){    	  
      tau = wdaugh1;
    }
    return tauDecay();          
  }
  return -1;     
}

int TtbarChannelSelector::tauDecay(){  
  for(unsigned int i=0; i<tau->numberOfDaughters();++i){
    if(abs(tau->daughter(i)->pdgId())>99 || abs(tau->daughter(i)->pdgId())<10){ 
      return 4;
    }
    if(abs(tau->daughter(i)->pdgId())==11){ 
      return 5;
    }
    if(abs(tau->daughter(i)->pdgId())==13){ 
      return 6;
    }
    if(abs(tau->daughter(i)->pdgId())==15) {
      tau = tau->daughter(i);
      return tauDecay();
    }  
  }
  cout << "MESSAGE: TtbarChannelSelector::tauDecay returns -1 since tau has no daughters." << endl;

  return -1;   
}

void TtbarChannelSelector::beginJob(const edm::EventSetup&) {

  if(SingleTopHadronic_){
    selectedChannels.push_back(1);  
    selectedChannels.push_back(10);
  }
  if(SingleTopElectron_){
    selectedChannels.push_back(2);  
    selectedChannels.push_back(20);
  }
  if(SingleTopMuon_){
    selectedChannels.push_back(3);  
    selectedChannels.push_back(30);
  } 
  if(SingleTopTau_){
    selectedChannels.push_back(4);  
    selectedChannels.push_back(40);
    selectedChannels.push_back(5);  
    selectedChannels.push_back(50);    
    selectedChannels.push_back(6);  
    selectedChannels.push_back(60);    
  }
  if(TtbarHadronic_){
    selectedChannels.push_back(11);
  }
  if(TtbarSemiElec_){
    selectedChannels.push_back(12); 
    selectedChannels.push_back(21);
  }
  if(TtbarSemiMuon_){
    selectedChannels.push_back(13); 
    selectedChannels.push_back(31);
  } 
  if(TtbarSemiTau_){
    selectedChannels.push_back(14); 
    selectedChannels.push_back(41);
    selectedChannels.push_back(15); 
    selectedChannels.push_back(51);    
    selectedChannels.push_back(16); 
    selectedChannels.push_back(61);    
  }
  if(TtbarElecElec_){
    selectedChannels.push_back(22);
  }
  if(TtbarMuonMuon_){
    selectedChannels.push_back(33);
  }
  if(TtbarTauTau_){
    selectedChannels.push_back(44);
    selectedChannels.push_back(55);    
    selectedChannels.push_back(66);
    selectedChannels.push_back(45);
    selectedChannels.push_back(54);    
    selectedChannels.push_back(46);    
    selectedChannels.push_back(64);
    selectedChannels.push_back(56);    
    selectedChannels.push_back(65);        
  }
  if(TtbarElecMuon_){
    selectedChannels.push_back(23); 
    selectedChannels.push_back(32);
  }
  if(TtbarElecTau_){
    selectedChannels.push_back(24); 
    selectedChannels.push_back(42);
    selectedChannels.push_back(25); 
    selectedChannels.push_back(52);    
    selectedChannels.push_back(26); 
    selectedChannels.push_back(62);    
  }   
  if(TtbarMuonTau_){
    selectedChannels.push_back(34); 
    selectedChannels.push_back(43);
    selectedChannels.push_back(35); 
    selectedChannels.push_back(53);    
    selectedChannels.push_back(36); 
    selectedChannels.push_back(63);    
  } 
  
  selChSize = selectedChannels.size();
  
  cout << "==============================================================" << endl;
  if(invert_==false) cout << "List of selected decay channels:"            << endl;
  else cout << "All Channel selected, except of: "                         << endl;
  for(unsigned int i=0; i<selChSize; i++){
   cout << selectedChannels[i]                                             << endl;
  } 
  cout << "==============================================================" << endl;    
}

void TtbarChannelSelector::endJob() {  
  cout << "==============================================================" << endl;
  cout << "       Selected: " << nHits  << " of " << nEvts                 << endl;
  cout << "==============================================================" << endl;     
}

DEFINE_FWK_MODULE(TtbarChannelSelector);

