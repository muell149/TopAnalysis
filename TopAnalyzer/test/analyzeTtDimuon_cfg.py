import FWCore.ParameterSet.Config as cms

process = cms.Process("TestAnalysis")
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.categories.append('topFilter')
process.MessageLogger.categories.append('TopChannelSelector')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)
#
#  Source
#
import FWCore.ParameterSet.Config as cms
#
# Source
#
process.load("TopAnalysis.Configuration.samples.ttbar_pat_cff")
#process.load("TopAnalysis.Configuration.samples.qcd_pat_cff")
#
# Output file
#
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('test.root')
)
#
# Event Selector for certain Ttbar decay channels on generator level
#
<<<<<<< analyzeTtDimuon_cfg.py
process.load("TopAnalysis.TopFilter.filters.TopChannelSelector_cfi")
=======
process.load("TopAnalysis.TopFilter.filters.TtbarChannelSelector_cfi")
>>>>>>> 1.2
process.selectChannel.Ttbar_MuonMuon = cms.bool(True)
#
# filter for kinematics, muon iso and quality
#
process.load("TopAnalysis.TopFilter.sequences.fullLepMuonSelection_step1_cff")
#
# analyze invariant mass of muon pair
#
process.load("TopAnalysis.TopAnalyzer.DimuonAnalyzer_cfi")
#
# procuce gen event
#
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")
#
# find event solutions
#
process.load("TopQuarkAnalysis.TopEventProducers.producers.TtDilepEvtSolProducer_cfi")
process.solutions.jetCorrectionScheme = 0
process.solutions.nrCombJets = 3
process.solutions.matchToGenEvt = True
process.solutions.bestSolFromMC = False
process.solutions.tmassbegin = 100.0
process.solutions.tmassend = 300.0
process.solutions.tmassstep = 1.0
#
# analyze event solutions
#
process.load("TopAnalysis.TopAnalyzer.TtDimuonAnalyzer_cfi")
process.analyzeTtDimuon.show_Gen_Event = False

process.p1 = cms.Path(process.selectChannel*
		      process.selectFullMuonMuonKinematics*
                      process.selectFullMuonJetsKinematics*                      
		      process.analyzeMuonPair*
		      process.selectFullMuonMuonIsolation*
		      process.makeGenEvt*
		      process.solutions*
		      process.analyzeTtDimuon
		     )
