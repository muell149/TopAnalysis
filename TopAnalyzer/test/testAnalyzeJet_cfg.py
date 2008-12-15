import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# test cfg file for tqaflayer1 & 2 production from
# fullsim for semi-leptonic ttbar events 
#-------------------------------------------------
process = cms.Process("TEST")

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
    ## PAT test sample
    #'file:/afs/cern.ch/cms/PRS/top/cmssw-data/relval200-for-pat-testing/FullSimTTBar-2_1_X_2008-07-08_STARTUP_V4-AODSIM.100.root'
    ## RelVal sample
    '/store/relval/CMSSW_2_1_4/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V6_v1/0004/02EC71C1-7E6C-DD11-9822-000423D944DC.root',
    '/store/relval/CMSSW_2_1_4/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V6_v1/0004/145944C5-7E6C-DD11-AC78-001617C3B79A.root',
    '/store/relval/CMSSW_2_1_4/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V6_v1/0004/2E1AB0F6-7E6C-DD11-9CBB-0019DB29C614.root',
    '/store/relval/CMSSW_2_1_4/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V6_v1/0004/3E0BD034-7F6C-DD11-9882-000423D9A212.root',
    '/store/relval/CMSSW_2_1_4/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V6_v1/0004/3E6FD0C6-7E6C-DD11-8258-001617C3B706.root',
    '/store/relval/CMSSW_2_1_4/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V6_v1/0004/40A974C8-7E6C-DD11-A9A0-001617E30CE8.root',
    '/store/relval/CMSSW_2_1_4/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V6_v1/0004/50F05233-7F6C-DD11-A908-000423D99EEE.root'
    ## madgraph pre-production test sample
    #'/store/mc/Fall08/TTJets-madgraph/GEN-SIM-RECO/IDEAL_V9_v1_pre-production/0000/249ACBCC-37BF-DD11-A191-00144F2031D4.root',
    #'/store/mc/Fall08/TTJets-madgraph/GEN-SIM-RECO/IDEAL_V9_v1_pre-production/0000/2CF2748D-6BBC-DD11-815C-001EC9DB3AD3.root',
    #'/store/mc/Fall08/TTJets-madgraph/GEN-SIM-RECO/IDEAL_V9_v1_pre-production/0000/30E599BC-66BC-DD11-B985-001E4F3DC624.root',
    #'/store/mc/Fall08/TTJets-madgraph/GEN-SIM-RECO/IDEAL_V9_v1_pre-production/0000/40313322-27BF-DD11-9773-0015C5E9C030.root',
    #'/store/mc/Fall08/TTJets-madgraph/GEN-SIM-RECO/IDEAL_V9_v1_pre-production/0000/B4AE994C-72BF-DD11-9909-001EC9DAED82.root',
    #'/store/mc/Fall08/TTJets-madgraph/GEN-SIM-RECO/IDEAL_V9_v1_pre-production/0000/EAC1080E-65BC-DD11-B8B8-001EC9DB1EF1.root',
    #'/store/mc/Fall08/TTJets-madgraph/GEN-SIM-RECO/IDEAL_V9_v1_pre-production/0000/F25A6622-27BF-DD11-AEA0-0015C5E9C186.root'
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
process.load("TopQuarkAnalysis.TopObjectProducers.tqafLayer1_cff")

## necessary fixes to run 2.2.X on 2.1.X data
## comment this when running on samples produced
## with 22X
from PhysicsTools.PatAlgos.tools.cmsswVersionTools import run22XonSummer08AODSIM
run22XonSummer08AODSIM(process)

process.p0 = cms.Path(process.tqafLayer1)

#-------------------------------------------------
# private uni Hamburg analysis code
#-------------------------------------------------

## add event weight information
from TopAnalysis.TopUtils.EventWeightPlain_cfi import *
process.eventWeight = eventWeight

# analyze jets
from TopAnalysis.TopAnalyzer.JetAnalyzer_cfi import analyzeJets
process.analyzeJets = analyzeJets

process.analyzeAllJets = process.analyzeJets.clone()
process.analyzeSelJets = process.analyzeJets.clone()

## reconfigure
process.analyzeAllJets.input = 'allLayer1Jets'
process.analyzeSelJets.input = 'selectedLayer1Jets'

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeJets.root')
)

process.p1 = cms.Path(process.eventWeight    *
                      process.analyzeAllJets +
                      process.analyzeSelJets
                      )
