import FWCore.ParameterSet.Config as cms

import TopAnalysis.TopAnalyzer.TopKinematics_rec_cfi
analyzeTopRecKinematicsMatched = TopAnalysis.TopAnalyzer.TopKinematics_rec_cfi.analyzeTopRecKinematics.clone(
    analyze = cms.PSet(hypoKey=cms.string('kGenMatch'), matchForStabilityAndPurity=cms.bool(True)))
