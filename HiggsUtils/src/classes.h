#include "TopAnalysis/HiggsUtils/interface/HiggsGenEvent.h"

#include "DataFormats/Common/interface/Wrapper.h"




namespace {
  struct dictionary {
    HiggsGenEvent higgsGenEvent;
    
    edm::Wrapper<HiggsGenEvent> w_higgsGenEvent;
    
    edm::RefProd<HiggsGenEvent> rp_higgsGenEvent;
  };
}
