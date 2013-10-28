import FWCore.ParameterSet.Config as cms
from TopAnalysis.TopAnalyzer.GenHFHadronAnalyzer_cfi import *

analyzeGenHFHadronJets = analyzeGenHFHadron.clone()
analyzeGenHFHadronJets.genJets = cms.InputTag('ak5GenJetsPlusHadron','','')

