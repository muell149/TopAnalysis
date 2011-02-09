#include "FWCore/Framework/interface/MakerMacros.h"

#include "TopAnalysis/TopFilter/plugins/DiMuonFilter.h"
DEFINE_FWK_MODULE(DiMuonFilter);

#include "TopAnalysis/TopFilter/plugins/DiElectronFilter.h"
DEFINE_FWK_MODULE(DiElectronFilter);

#include "TopAnalysis/TopFilter/plugins/FullLepHypothesesFilter.h"
DEFINE_FWK_MODULE(FullLepHypothesesFilter);

#include "TopAnalysis/TopFilter/plugins/MuonJetOverlapSelector.h"
DEFINE_FWK_MODULE(MuonJetOverlapSelector);

#include "TopAnalysis/TopFilter/plugins/JetOverlapEventFilter.h"
DEFINE_FWK_MODULE(JetOverlapEventFilter);

#include "TopAnalysis/TopFilter/plugins/SemiLeptonicTopJetSelector.h"
DEFINE_FWK_MODULE(SemiLeptonicTopJetSelector);

#include "TopAnalysis/TopFilter/plugins/SemiLeptonicTopMuonSelector.h"
DEFINE_FWK_MODULE(SemiLeptonicTopMuonSelector);

