/* \class TopChannelSelector
 *
 * \author Dirk Dammann
 *
 * \decription: filter for single top or ttbar decay channels
 *              on generator level.
 *              decay channels are internaly coded by numbers:
 *              1 stands for a hadronically decaying top
 *              2 is top to electron
 *              3 muon
 *              4 tau further decaying to hadrons
 *              5 tau to electron
 *              6 tau to muon.
 *              in two digit numbers the first digit is the top
 *              and the second the antitop.
 *              so e.g. dimuon channel is 33 or single electron is 21 and 12             
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

class TopChannelSelector : public edm::EDFilter {
 public:
  explicit TopChannelSelector(const edm::ParameterSet&);
  ~TopChannelSelector();
  
 private:  
  virtual void beginJob(const edm::EventSetup&);
  virtual bool filter(edm::Event&, const edm::EventSetup&);
  virtual void endJob(); 

  bool analyze(edm::Event&, const edm::EventSetup&);  
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
  bool Tau2Had_;
  bool Tau2Elec_; 
  bool Tau2Muon_;
  bool invert_;   
    
  vector<int> selectedChannels; 
  unsigned int selChSize; 
  
  const reco::Candidate* bquark;
  const reco::Candidate* wbos;
  const reco::Candidate* tau;
  const reco::Candidate* wdaugh1;
  const reco::Candidate* wdaugh2;     
};


TopChannelSelector::TopChannelSelector(const edm::ParameterSet& cfg) :
  src_              (cfg.getParameter<edm::InputTag>("src"       )),
  nEvents_          (cfg.getParameter<int> ("n_events"           )),  
  SingleTopHadronic_(cfg.getParameter<bool>("SingleTop_Hadronic" )),  
  SingleTopElectron_(cfg.getParameter<bool>("SingleTop_Electron" )),  
  SingleTopMuon_    (cfg.getParameter<bool>("SingleTop_Muon"     )),  
  SingleTopTau_     (cfg.getParameter<bool>("SingleTop_Tau"      )),  
  TtbarHadronic_    (cfg.getParameter<bool>("Ttbar_Hadronic"     )), 
  TtbarSemiElec_    (cfg.getParameter<bool>("Ttbar_SemiElec"     )),   
  TtbarSemiMuon_    (cfg.getParameter<bool>("Ttbar_SemiMuon"     )),   
  TtbarSemiTau_     (cfg.getParameter<bool>("Ttbar_SemiTau"      )),   
  TtbarElecElec_    (cfg.getParameter<bool>("Ttbar_ElecElec"     )),   
  TtbarMuonMuon_    (cfg.getParameter<bool>("Ttbar_MuonMuon"     )),   
  TtbarTauTau_      (cfg.getParameter<bool>("Ttbar_TauTau"       )), 
  TtbarElecMuon_    (cfg.getParameter<bool>("Ttbar_ElecMuon"     )),   
  TtbarElecTau_     (cfg.getParameter<bool>("Ttbar_ElecTau"      )),   
  TtbarMuonTau_     (cfg.getParameter<bool>("Ttbar_MuonTau"      )),
  Tau2Had_          (cfg.getParameter<bool>("Tau_To_Hadron"      )),   
  Tau2Elec_         (cfg.getParameter<bool>("Tau_To_Electron"    )),
  Tau2Muon_         (cfg.getParameter<bool>("Tau_To_Muon"        )), 
  invert_           (cfg.getParameter<bool>("invert_selection"   ))              
{
  nEvts = 0;
  nHits = 0;     
}


TopChannelSelector::~TopChannelSelector() { 
}

bool TopChannelSelector::filter(edm::Event& evt, const edm::EventSetup& es) {
    nEvts++;
    bool result = analyze( evt, es);
    if(result) nHits++;
    return result;
}

bool TopChannelSelector::analyze(edm::Event& evt, const edm::EventSetup& es) {  
  if(nEvents_!=-1){
    if(nHits >= nEvents_){
      return false;      
    }
  }
  
  bool passed;
  bool blocked;
  
  if (invert_==false){
    blocked = false;
    passed  = true;
  }
  else{
    blocked = true;
    passed  = false;    
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
      edm::LogPrint("TopDecaySelector") << "Top does not decay to b.";
      return blocked;
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
      edm::LogPrint("TopDecaySelector") << "Top has no W daughter.";
      return blocked;	
    }
    // calculate the decay value from the w decays
    int wNumber = wDecay();
    
    if(wNumber<0){ 
      edm::LogPrint("TopDecaySelector") << "Could not identify W-decay.";
      return blocked;
    }
    
    if(wNumber==7){
      // if it happens that the wNumber is 7 that means that no tau daughter
      // is in the genParticle collection. This then is an error of the MC.
      // If at least one tau decay mode is blocked it is assumed that only
      // special tau decays shoul be selected. So in this case "stable taus"
      // are blocked.
      edm::LogPrint("TopDecaySelector") << "Tau from top decay does not decay.";
      if(!Tau2Had_ || !Tau2Elec_ || ! Tau2Muon_) return blocked;
    }
    
    if(cand->pdgId()==6){ 
      decayVl = decayVl + 10*wNumber;
    }
    else{
      decayVl = decayVl + wNumber;	  
    }           
  }

  for(unsigned int i=0; i<selChSize; i++){
    if(decayVl==selectedChannels.at(i)) return passed;
  }      
  return blocked;
}   

int TopChannelSelector::wDecay(){
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
  // if w does not decay into quarks or leptons
  return -1;     
}

int TopChannelSelector::tauDecay(){  
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
  // if tau is stable
  return 7;   
}

void TopChannelSelector::beginJob(const edm::EventSetup&) {
  // build vector of selected decay channel numbers
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
    if(Tau2Had_){
      selectedChannels.push_back( 4);  
      selectedChannels.push_back(40);
    }
    if(Tau2Elec_){      
      selectedChannels.push_back( 5);  
      selectedChannels.push_back(50); 
    }
    if(Tau2Muon_){                 
      selectedChannels.push_back( 6);  
      selectedChannels.push_back(60);
    }       
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
    if(Tau2Had_){  
      selectedChannels.push_back(14); 
      selectedChannels.push_back(41);
    }
    if(Tau2Elec_){     
      selectedChannels.push_back(15); 
      selectedChannels.push_back(51);  
    }
    if(Tau2Muon_){        
      selectedChannels.push_back(16); 
      selectedChannels.push_back(61); 
    }     
  }
  
  if(TtbarElecElec_){
    selectedChannels.push_back(22);
  }
  
  if(TtbarMuonMuon_){
    selectedChannels.push_back(33);
  }
  
  if(TtbarTauTau_){
    if(Tau2Had_){   
      selectedChannels.push_back(44);
    }
    if(Tau2Elec_){     
      selectedChannels.push_back(55); 
    }
    if(Tau2Muon_){         
      selectedChannels.push_back(66);
    }
    if(Tau2Had_ && Tau2Elec_){           
      selectedChannels.push_back(45);
      selectedChannels.push_back(54);
    } 
    if(Tau2Had_ && Tau2Muon_){   
      selectedChannels.push_back(46);    
      selectedChannels.push_back(64);
    } 
    if(Tau2Elec_ && Tau2Muon_){          
      selectedChannels.push_back(56);    
      selectedChannels.push_back(65);
    }          
  }
  
  if(TtbarElecMuon_){
    selectedChannels.push_back(23); 
    selectedChannels.push_back(32);
  }
  
  if(TtbarElecTau_){
    if(Tau2Had_){  
      selectedChannels.push_back(24); 
      selectedChannels.push_back(42);
    }
    if(Tau2Elec_){     
      selectedChannels.push_back(25); 
      selectedChannels.push_back(52);  
    }
    if(Tau2Muon_){        
      selectedChannels.push_back(26); 
      selectedChannels.push_back(62); 
    }    
  }  
  
  if(TtbarMuonTau_){
    if(Tau2Had_){  
      selectedChannels.push_back(34); 
      selectedChannels.push_back(43);
    }
    if(Tau2Elec_){     
      selectedChannels.push_back(35); 
      selectedChannels.push_back(53);  
    }
    if(Tau2Muon_){        
      selectedChannels.push_back(36); 
      selectedChannels.push_back(63); 
    }     
  } 
  
  selChSize = selectedChannels.size();
  
  edm::LogInfo log("TopChannelSelector");
  
  log << "==============================================================\n";
  if(invert_==false) log << "List of selected decay channels:\n";
  else log << "All decay channels selected except of:\n";
  for(unsigned int i=0; i<selChSize; i++){
    int channel = selectedChannels[i];
    int first = channel/10;
    int second = channel%10;
  
    if(first == 0 || second==0){
      if(first==1) log << "single top to hadrons\n";
      else if(first==2) log << "single top to electron\n";
      else if(first==3) log << "single top to muon\n";
      else if(first>3) log << "single top to tau\n";
    }
  
    else if(channel==11) log << "fullhadronic\n";
  
    else if(first == second){
      log << "dileptonic ";
      if(channel==22) log << "e e\n";
      else if(channel==33) log << "mu mu\n";
      else log << "tau tau\n";
    }
    
    else if(first > second){
      if(second>1){
        log << "dilepton ";
	if(first==3) log << "mu e\n";
	else if(first>=4 && second==3) log << "tau mu\n";
	else log << "tau e\n";
      }
      else{
        log << "semileptonic with ";
	if(first==2) log << "electron\n";
	else if(first==3) log << "muon\n";
	else log << "tau\n";
      }
    }      
  } 
  if(!Tau2Had_ || !Tau2Elec_ || !Tau2Muon_){
    log << "\nTaus decaying to ";
    if(!Tau2Had_) log << "hadrons ";
    if(!Tau2Elec_) log << "electrons ";
    if(!Tau2Muon_)  log << "muons ";
    log << "are excluded form selection.\n";
  }     
  log << "==============================================================\n";   
}

void TopChannelSelector::endJob() {  
  edm::LogInfo log("TopChannelSelector");

  log << "==============================================================\n";
  log << "       Selected: " << nHits  << " of " << nEvts << "\n";
  log << "==============================================================\n";   
}

DEFINE_FWK_MODULE(TopChannelSelector);

