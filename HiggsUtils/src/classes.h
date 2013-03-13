#include "TopAnalysis/HiggsUtils/interface/HiggsGenEvent.h"
#include "TopAnalysis/HiggsUtils/interface/JetProperties.h"

#include "DataFormats/Common/interface/Wrapper.h"




namespace {
  struct dictionary {
    HiggsGenEvent higgsGenEvent;
    edm::Wrapper<HiggsGenEvent> w_higgsGenEvent;
    edm::RefProd<HiggsGenEvent> rp_higgsGenEvent;
    
    JetProperties jetProperties;
    std::vector<JetProperties> v_jetProperties;
    edm::Wrapper<JetProperties> w_jetProperties;
    edm::RefProd<JetProperties> rp_jetProperties;
    edm::Wrapper<std::vector<JetProperties> > w_v_jetProperties;
    
  };
}




