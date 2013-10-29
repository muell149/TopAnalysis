import FWCore.ParameterSet.Config as cms
from TopAnalysis.TopUtils.GenHFHadronMatcher_cfi import *

matchGenHFHadronJets = matchGenHFHadron.clone()
matchGenHFHadronJets.genJets = cms.InputTag('ak5GenJetsPlusHadron','','')

