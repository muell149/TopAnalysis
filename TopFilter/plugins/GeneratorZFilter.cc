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
       
      edm::InputTag src_;      
      const std::vector<int>    zDecayModes_;      
      const std::vector<double> diLepMassIntervals_;
};


GeneratorZFilter::GeneratorZFilter(const edm::ParameterSet& cfg):
  src_               (cfg.getParameter<edm::InputTag>       ("src"                  )),
  zDecayModes_       (cfg.getParameter<std::vector<int> >   ("zDecayModes"          )),
  diLepMassIntervals_(cfg.getParameter<std::vector<double> >("diLeptonMassIntervals"))
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


bool
GeneratorZFilter::filter(edm::Event& evt, const edm::EventSetup& es)
{
  edm::Handle<reco::GenParticleCollection> genParticles;
  evt.getByLabel(src_, genParticles);
  
  // Take care: when analysing events with more than one Z, not all have to be Z->xx with specified x
  bool decayModeFilter(false);    
  bool diLeptonMassFilter(false);
  
  for(reco::GenParticleCollection::const_iterator iGenPart = genParticles->begin(); iGenPart != genParticles->end(); ++iGenPart){
    bool isRightDecay(false);
    reco::Candidate::LorentzVector lorVecMinus, lorVecPlus;
    if(iGenPart->pdgId()!=23 || iGenPart->status()!=3) continue;
       
    for(size_t iDaughter = 0; iDaughter < iGenPart->numberOfDaughters(); ++iDaughter){
      const reco::GenParticle* daughter(dynamic_cast<const reco::GenParticle*>(iGenPart->daughter(iDaughter)));
      // select l-
      for(std::vector<int>::const_iterator i_zDecayMode = zDecayModes_.begin();i_zDecayMode != zDecayModes_.end(); ++i_zDecayMode){
        if(daughter->pdgId() == (*i_zDecayMode)){
          lorVecMinus = daughter->p4();
          isRightDecay = true;
        }
        // select l+
        else if(daughter->pdgId() == -(*i_zDecayMode)){
          lorVecPlus = daughter->p4();
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
  if(!diLeptonMassFilter)return false;
  
  // All filters fulfilled...
  return true;
}


void 
GeneratorZFilter::beginJob()
{
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
