#include <memory>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "FWCore/Utilities/interface/EDMException.h"

class GeneratorZFilter : public edm::EDFilter {
   public:
      explicit GeneratorZFilter(const edm::ParameterSet&);
      ~GeneratorZFilter();

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      const bool filterInterval(const double, const std::vector<double>&)const;
      const int  tauDecay(const reco::GenParticle*);
       
      edm::InputTag src_;      
      const std::vector<int>         zDecayModes_;   
      const std::vector<std::string> tauDecays_;   
      const std::vector<double>      diLepMassIntervals_;
};


GeneratorZFilter::GeneratorZFilter(const edm::ParameterSet& cfg):
  src_               (cfg.getParameter<edm::InputTag>               ("src"                  )),
  zDecayModes_       (cfg.getParameter<std::vector<int> >           ("zDecayModes"          )),
  tauDecays_         (cfg.getParameter<std::vector<std::string> >   ("tauDecays"            )),  
  diLepMassIntervals_(cfg.getParameter<std::vector<double> >        ("diLeptonMassIntervals"))
{
}


GeneratorZFilter::~GeneratorZFilter()
{
}


const bool
GeneratorZFilter::filterInterval(const double variable, const std::vector<double>& v_interval)const{
  if(v_interval.size()==0)return true;
  int i_entry(1);
  double intervalBegin(999.);
  for(std::vector<double>::const_iterator i_interval = v_interval.begin(); i_interval != v_interval.end(); ++i_interval, ++i_entry){
    if(i_entry%2==1)intervalBegin = *i_interval;
    if(i_entry%2==0 && variable>=intervalBegin && variable<=*i_interval)return true;  // keep also interval borders absolutely symmetric 
  }
  return false;
}


const int
GeneratorZFilter::tauDecay(const reco::GenParticle* part)
{
  int id = -1;
  
  for(unsigned int i=0; i<part->numberOfDaughters();++i){
    if(abs(part->daughter(i)->pdgId())==11)
      return 11;
    if(abs(part->daughter(i)->pdgId())==13)
      return 13;
    // In many cases tau radiates a photon before it decays. So one daughter is again a tau. Use Recursion then.
    if(abs(part->daughter(i)->pdgId())==15)    
      return tauDecay(dynamic_cast<const reco::GenParticle*>(part->daughter(i)));   
  }  
  
  return id;
}


bool
GeneratorZFilter::filter(edm::Event& evt, const edm::EventSetup& es)
{
  edm::Handle<reco::GenParticleCollection> genParticles;
  evt.getByLabel(src_, genParticles);
  
  // Take care: when analysing events with more than one Z, not all have to be Z->xx with specified x
  bool decayModeFilter = false;    
  bool diLeptonMassFilter = false;

  // check if specific tau decays are selected
  bool specificTauDecaysSelected = false;
  if(tauDecays_.size()>0) specificTauDecaysSelected = true;  
  bool isTauTau = false;
  bool isTauSelected = false;
    
  for(reco::GenParticleCollection::const_iterator iGenPart = genParticles->begin(); iGenPart != genParticles->end(); ++iGenPart){
    bool isRightDecay(false);
    reco::Candidate::LorentzVector lorVecMinus, lorVecPlus;
    if(iGenPart->pdgId()!=23 || iGenPart->status()!=3) continue;
    
    // needed if specific tau decays are selected
    int tauMinusDecay = -1;
    int tauPlusDecay  = -1;
       
    for(size_t iDaughter = 0; iDaughter < iGenPart->numberOfDaughters(); ++iDaughter){
      const reco::GenParticle* daughter(dynamic_cast<const reco::GenParticle*>(iGenPart->daughter(iDaughter)));
      // select l-
      for(std::vector<int>::const_iterator i_zDecayMode = zDecayModes_.begin();i_zDecayMode != zDecayModes_.end(); ++i_zDecayMode){
        if(daughter->pdgId() == (*i_zDecayMode)){
          lorVecMinus = daughter->p4();
          isRightDecay = true;
	  if(specificTauDecaysSelected && daughter->pdgId() == 15){
	    isTauTau = true;
	    tauMinusDecay = tauDecay(daughter);
	  }
        }
        // select l+
        else if(daughter->pdgId() == -(*i_zDecayMode)){
          lorVecPlus = daughter->p4();
	  if(specificTauDecaysSelected && daughter->pdgId() == -15){
	    tauPlusDecay = tauDecay(daughter);
	  }	  
        }
      }
    }
    
    // if specific tau decay is selected check result
    if(specificTauDecaysSelected){
      std::string tauDecay;
      if(tauMinusDecay == 11 && tauPlusDecay == 11)
        tauDecay = "ee";
      else if((tauMinusDecay == 11 && tauPlusDecay == 13) || (tauMinusDecay == 13 && tauPlusDecay == 11))	
        tauDecay = "emu";
      else if(tauMinusDecay == 13 && tauPlusDecay == 13)	
        tauDecay = "mumu";	
	
      // return 'false' if tau decays in the event are not in the vector of selected tau decay modes      
      for(std::vector<std::string>::const_iterator td = tauDecays_.begin(); td!=tauDecays_.end(); ++td){	
        if(*td==tauDecay){
	  isTauSelected = true;
	  break;
	}
      }	    
    }
    
    if(!isRightDecay)continue;
    else decayModeFilter = true;        
    
    const reco::Candidate::LorentzVector diLeptonVec = lorVecMinus + lorVecPlus;
    const double diLeptonMass = diLeptonVec.M(); 
    
    if(this->filterInterval(diLeptonMass, diLepMassIntervals_)) diLeptonMassFilter = true; 
  }  
  if(!decayModeFilter)return false;
  if(specificTauDecaysSelected && isTauTau && !isTauSelected) return false;  
  if(!diLeptonMassFilter)return false;
  
  // All filters fulfilled...
  return true;
}


void 
GeneratorZFilter::beginJob()
{
  // check if tauDecays contains elements if tau channel is selected at all
  if(tauDecays_.size()>0){
    bool containsTau = false;
    for(std::vector<int>::const_iterator it = zDecayModes_.begin(); it!=zDecayModes_.end(); ++it){	
      if(abs(*it) == 15) containsTau = true;
    }
    if(!containsTau){
      edm::LogWarning("GeneratorZFilter")<<"tauDecays are specified although no tau decays are selected. Is your configuration correct?";        
    }
  }

  // check if tauDecays contains elements which are not 'ee', 'em', or 'mumu'
  for(size_t i=0;i<tauDecays_.size();++i){
    if(tauDecays_[i]!="ee" && tauDecays_[i]!="emu" && tauDecays_[i]!="mumu"){
      edm::LogError("GeneratorZFilter")<<"tauDecays contains invalid string: " << tauDecays_[i];  
      throw edm::Exception( edm::errors::Configuration,"Incorrect tau channel selection in cfg file!!!\n" );    
    }  
  }

  // check validity of all filter intervals taken from cfg
  if(diLepMassIntervals_.size()==0){
    edm::LogInfo("GeneratorZFilter")<<"No selection for diLeptonMass";
    return;
  }
  
  const std::string message("Incorrect interval definition in cfg file for diLepMassIntervals!!!\n");
  
  // Odd no., of arguments cannot give intervals
  if(diLepMassIntervals_.size()%2==1){
    edm::LogError("Error in cfg file")<<"Odd number of arguments in interval definition of diLeptonMass, throw exception:";
    throw edm::Exception( edm::errors::Configuration,
                          message );
  }
  
  // Every odd entry must be followed by one with bigger (or equal) value to define intervals
  int i_Entry(1);
  double intervalBegin(999.);
  for(std::vector<double>::const_iterator i_interval = diLepMassIntervals_.begin(); i_interval != diLepMassIntervals_.end(); ++i_interval, ++i_Entry){
    if(i_Entry%2==1)intervalBegin = *i_interval;
    if(i_Entry%2==0){
      if(intervalBegin>*i_interval){
        edm::LogError("Error in cfg file")<<"Incorrect interval definition of diLepMassIntervals, entry "<<i_Entry-1<<" is smaller than entry "<<i_Entry<<", throw exception:";
        throw edm::Exception( edm::errors::Configuration,
                              message );
      }
      else{
        edm::LogInfo("GeneratorZFilter")<<"Selected diLepMassIntervals, interval no. "<<i_Entry/2<<": ["<<intervalBegin<<", "<<*i_interval<<"]";
      }
    }
  }
}


void 
GeneratorZFilter::endJob() 
{
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(GeneratorZFilter);
