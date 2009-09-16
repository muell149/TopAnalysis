#include "FWCore/Framework/interface/MakerMacros.h"
#include "TopAnalysis/TopAnalyzer/plugins/SingleObjectAnalyzer.h"
#include "TopAnalysis/TopAnalyzer/plugins/DoubleObjectAnalyzer.h"

/**
    Define modules needed for the analysis of the muon
**/

#include "TopAnalysis/TopAnalyzer/interface/MuonQuality.h"
typedef SingleObjectAnalyzer<std::vector<pat::Muon>, MuonQuality> MuonQualityAnalyzer;
DEFINE_FWK_MODULE(MuonQualityAnalyzer);

#include "TopAnalysis/TopAnalyzer/interface/MuonKinematics.h"
typedef SingleObjectAnalyzer<std::vector<pat::Muon>, MuonKinematics> MuonKinematicsAnalyzer;
DEFINE_FWK_MODULE(MuonKinematicsAnalyzer);

#include "TopAnalysis/TopAnalyzer/interface/MuonResolution.h"
typedef SingleObjectAnalyzer<std::vector<pat::Muon>, MuonResolution> MuonResolutionAnalyzer;
DEFINE_FWK_MODULE(MuonResolutionAnalyzer);


/**
    Define modules needed for the analysis of the jets
**/

#include "TopAnalysis/TopAnalyzer/interface/JetQuality.h"
typedef SingleObjectAnalyzer<std::vector<pat::Jet>, JetQuality> JetQualityAnalyzer;
DEFINE_FWK_MODULE(JetQualityAnalyzer);

#include "TopAnalysis/TopAnalyzer/interface/JetKinematics.h"
typedef SingleObjectAnalyzer<std::vector<pat::Jet>, JetKinematics> JetKinematicsAnalyzer;
DEFINE_FWK_MODULE(JetKinematicsAnalyzer);

#include "TopAnalysis/TopAnalyzer/interface/JetResolution.h"
typedef SingleObjectAnalyzer<std::vector<pat::Jet>, JetResolution> JetResolutionAnalyzer;
DEFINE_FWK_MODULE(JetResolutionAnalyzer);


/**
    Define modules needed for the analysis of muon jet relations
**/

#include "TopAnalysis/TopAnalyzer/interface/MuonJetKinematics.h"
typedef DoubleObjectAnalyzer<std::vector<pat::Muon>, std::vector<pat::Jet>, MuonJetKinematics> MuonJetKinematicsAnalyzer;
DEFINE_FWK_MODULE(MuonJetKinematicsAnalyzer);


/**
    Define modules needed for the analysis of the top quarks
**/

#include "TopAnalysis/TopAnalyzer/interface/TopKinematics.h"
typedef SingleObjectAnalyzer<TtGenEvent, TopKinematics> TopKinematicsGenAnalyzer;
DEFINE_FWK_MODULE(TopKinematicsGenAnalyzer);

typedef SingleObjectAnalyzer<TtSemiLeptonicEvent, TopKinematics> TopKinematicsRecAnalyzer;
DEFINE_FWK_MODULE(TopKinematicsRecAnalyzer);



#include "TopAnalysis/TopAnalyzer/interface/JetCombinatorics.h"
typedef SingleObjectAnalyzer<TtSemiLeptonicEvent, JetCombinatorics> JetCombinatoricsAnalyzer;
DEFINE_FWK_MODULE(JetCombinatoricsAnalyzer);
