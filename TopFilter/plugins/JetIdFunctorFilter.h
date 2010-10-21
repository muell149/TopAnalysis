#ifndef JetIdFunctorFilter_h
#define JetIdFunctorFilter_h

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "PhysicsTools/SelectorUtils/interface/JetIDSelectionFunctor.h"
#include "PhysicsTools/SelectorUtils/interface/PFJetIDSelectionFunctor.h"

/**
   \class   JetIdFunctorFilter JetIdFunctorFilter.h "TopAnalysis/TopFilter/plugins/JetIdFunctorFilter.h"

   \brief   EDProducer for Calo, JPT or PF jets fulfilling predefined quality cuts 

   This producer creates a new collection of Calo, JPT or PF jets which fulfill predefined quality cuts.
   It uses the JetIdSelectionFunctor resp. PFJetIdSelectionFunctor. See also:
   https://twiki.cern.ch/twiki/bin/view/CMS/SWGuidePATSelectors
*/

class JetIdFunctorFilter : public edm::EDProducer {

 public:
  explicit JetIdFunctorFilter(const edm::ParameterSet&);
  ~JetIdFunctorFilter(){
  };
  
 private:
  virtual void beginJob();
  virtual void produce(edm::Event&, const edm::EventSetup&);

  /// input jet collection
  edm::InputTag jets_;
  /// given jet type: CALO, JPT or PF
  std::string type_;
  /// version of the selection criteria to be used
  std::string version_;
  /// selection quality to be used
  std::string quality_;
    
  JetIDSelectionFunctor::Version_t version;
  JetIDSelectionFunctor::Quality_t quality;
  
  PFJetIDSelectionFunctor::Version_t versionPF;
  PFJetIDSelectionFunctor::Quality_t qualityPF;  
   
};

#endif
