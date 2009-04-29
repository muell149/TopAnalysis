import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# cfg file for the analysis of selected muon
# quantities
#-------------------------------------------------
process = cms.Process("Muon")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
## process.MessageLogger.cerr.FwkReport.reportEvery = 100

#-------------------------------------------------
# process configuration
#-------------------------------------------------

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    ## add your favourite file here
    )
)

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(False)
)

#-------------------------------------------------
# muon analysis
#-------------------------------------------------

## analyze muon isolation
process.load("TopAnalysis.TopAnalyzer.IsolationAnalyzer_cfi")
from TopAnalysis.TopAnalyzer.IsolationAnalyzer_cfi import analyzeisolationMET
before = analyzeisolationMET.clone()
after = analyzeisolationMET.clone()
before.modulename = "findQCDBkgMVA"
after.modulename = "findQCDBkgMVA"
process.load("TopAnalysis.TopUtils.QCDBkgMVAComputer_cff")
## import selection cuts here
from TopAnalysis.TopFilter.selectlions.semiLepMuonSelection_step1_cff import *
from TopAnalysis.TopFilter.filters.SemiLepMuonEventFilter_cfi import filterSemiLepMuonEvent
#process.load("TopAnalysis.TopFilter.sequences.semiLepMuonSelection_step1_cff")
tight = filterSemiLepMuonEvent.clone()
loose = filterSemiLepMuonEvent.clone()
loose.trkIso = False
loose.calIso = False
loose.jetDist = False
semiLepJetsPt.min = 20.0, 20.0, 20.0, 20.0
semiLepMuonPt.min = 20.0,
## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeMuonIso.root')
)

process.p1 = cms.Path(process.findQCDBkgMVA * loose * before * tight * after)
