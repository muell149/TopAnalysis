import FWCore.ParameterSet.Config as cms
from TopAnalysis.TopAnalyzer.GenLevelBJetAnalyzer_cfi import *

analyzeGenLevelBJetPlusHadron = analyzeGenLevelBJets.clone()
analyzeGenLevelBJetPlusHadron.genJets = cms.InputTag('ak5GenJetsPlusHadron','','')

