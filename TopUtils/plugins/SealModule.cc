#include "FWCore/Framework/interface/MakerMacros.h"

#include "TopAnalysis/TopUtils/plugins/EventWeight.h"
DEFINE_FWK_MODULE( EventWeight );

#include "TopAnalysis/TopUtils/plugins/EventWeightPlain.h"
DEFINE_FWK_MODULE( EventWeightPlain );

#include "TopAnalysis/TopUtils/plugins/JetEnergyScale.h"
DEFINE_FWK_MODULE( JetEnergyScale );

#include "TopAnalysis/TopUtils/plugins/TtSemiLepSignalSelectorMVATrainer.h"
DEFINE_FWK_MODULE( TtSemiLepSignalSelectorMVATrainer );

#include "TopAnalysis/TopUtils/plugins/TtSemiLepSignalSelectorMVAComputer.h"
DEFINE_FWK_MODULE( TtSemiLepSignalSelectorMVAComputer );


