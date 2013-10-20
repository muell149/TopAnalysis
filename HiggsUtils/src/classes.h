#include "TopAnalysis/HiggsUtils/interface/HiggsGenEvent.h"
#include "TopAnalysis/HiggsUtils/interface/JetProperties.h"
#include "TopAnalysis/HiggsUtils/interface/GenZDecayProperties.h"

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
    
    GenZDecayProperties genZDecayProperties;
    std::vector<GenZDecayProperties> v_genZDecayProperties;
    edm::Wrapper<GenZDecayProperties> w_genZDecayProperties;
    edm::RefProd<GenZDecayProperties> rp_genZDecayProperties;
    edm::Wrapper<std::vector<GenZDecayProperties> > w_v_genZDecayProperties;
  };
}




