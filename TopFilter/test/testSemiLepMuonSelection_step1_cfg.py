import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# test cfg file for tqaflayer1 & 2 production from
# fullsim for semi-leptonic ttbar events 
#-------------------------------------------------
process = cms.Process("HH")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
#process.MessageLogger.cerr.FwkReport.reportEvery = 100

#-------------------------------------------------
# process configuration
#-------------------------------------------------

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    #PAT test sample
    #'file:/afs/cern.ch/cms/PRS/top/cmssw-data/relval200-for-pat-testing/FullSimTTBar-2_1_X_2008-07-08_STARTUP_V4-AODSIM.100.root'
    #PAT-tuple at DESY
    '/store/mc/Summer08/TauolaTTbar/USER/IDEAL_V9_PAT_v2/0000/12B02891-66CF-DD11-9F1C-00E08178C11F.root',
    '/store/mc/Summer08/TauolaTTbar/USER/IDEAL_V9_PAT_v2/0000/48B6CB13-E9CC-DD11-8FC0-00E08179183F.root',
    '/store/mc/Summer08/TauolaTTbar/USER/IDEAL_V9_PAT_v2/0000/6289DFE2-EBCC-DD11-A923-00E0817918BB.root',
    '/store/mc/Summer08/TauolaTTbar/USER/IDEAL_V9_PAT_v2/0000/689A17B1-ECCC-DD11-8E7D-00E08179186B.root',
    '/store/mc/Summer08/TauolaTTbar/USER/IDEAL_V9_PAT_v2/0000/828ECBD8-3ACC-DD11-A0C3-001A6478A7C4.root',
    '/store/mc/Summer08/TauolaTTbar/USER/IDEAL_V9_PAT_v2/0000/AA8BFCA6-31CF-DD11-A7F4-00E08178C18F.root',
    '/store/mc/Summer08/TauolaTTbar/USER/IDEAL_V9_PAT_v2/0000/C68584CC-C6CB-DD11-9714-0013D3D85A8B.root',
    '/store/mc/Summer08/TauolaTTbar/USER/IDEAL_V9_PAT_v2/0000/D03CE81C-8BDD-DD11-82BE-00E081791767.root',
    '/store/mc/Summer08/TauolaTTbar/USER/IDEAL_V9_PAT_v2/0000/DAF9D007-42CD-DD11-A455-00E081B08BC9.root',
    '/store/mc/Summer08/TauolaTTbar/USER/IDEAL_V9_PAT_v2/0000/F4E0BF7B-42CD-DD11-94BB-00E08178C0F3.root'
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

## configure geometry
process.load("Configuration.StandardSequences.Geometry_cff")

## configure conditions
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('STARTUP_V4::All')

## Magnetic field now needs to be in the high-level py
process.load("Configuration.StandardSequences.MagneticField_cff")

#-------------------------------------------------
# tqaf configuration; if you want just to produce 
# tqafLayer2 on top of an already existing
# tqafLayer1 just comment the standard tqafLayer1
# production sequence
#-------------------------------------------------

## std sequence for tqaf layer1
#process.load("TopQuarkAnalysis.TopObjectProducers.tqafLayer1_cff")
#process.p0 = cms.Path(process.tqafLayer1)

## necessary fixes to run 2.2.X on 2.1.X data
## comment this when running on samples produced
## with 22X
#from PhysicsTools.PatAlgos.tools.cmsswVersionTools import run22XonSummer08AODSIM
#run22XonSummer08AODSIM(process)

#-------------------------------------------------
# private uni Hamburg analysis code
#-------------------------------------------------

## add event weight information
process.load("TopAnalysis.TopUtils.EventWeightPlain_cfi")

## test basic event selection
process.load("TopAnalysis.TopFilter.sequences.semiLepMuonSelection_step1_cff")

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('testSemiLepMuonSelection_step1.root')
)

process.p1 = cms.Path(process.eventWeight   *
                      process.selectSemiLepMuon
                      )
