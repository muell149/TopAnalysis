#include "FWCore/Framework/interface/MakerMacros.h"

#include "TopAnalysis/TopFilter/plugins/DiMuonMassFilter.h"
DEFINE_FWK_MODULE(DiMuonMassFilter);

#include "TopAnalysis/TopFilter/plugins/MuonJetOverlapSelector.h"
DEFINE_FWK_MODULE(MuonJetOverlapSelector);

#include "TopAnalysis/TopFilter/plugins/SemiLeptonicTopJetSelector.h"
DEFINE_FWK_MODULE(SemiLeptonicTopJetSelector);

#include "TopAnalysis/TopFilter/plugins/SemiLeptonicTopMuonSelector.h"
DEFINE_FWK_MODULE(SemiLeptonicTopMuonSelector);
