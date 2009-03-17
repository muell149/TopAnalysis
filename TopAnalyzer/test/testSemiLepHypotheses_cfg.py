import FWCore.ParameterSet.Config as cms

process = cms.Process("TEST")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.categories.append('TtSemiLeptonicEvent')
process.MessageLogger.categories.append('TtSemiLepKinFitter')
process.MessageLogger.categories.append('SemiLepHypothesesAnalyzer')
#process.MessageLogger.categories.append('KinFitter')
process.MessageLogger.cerr.INFO = cms.untracked.PSet(
    default             = cms.untracked.PSet( limit = cms.untracked.int32( 0) ),
    TtSemiLeptonicEvent = cms.untracked.PSet( limit = cms.untracked.int32(-1) ),
    TtSemiLepKinFitter  = cms.untracked.PSet( limit = cms.untracked.int32(-1) ),
    SemiLepHypothesesAnalyzer = cms.untracked.PSet( limit = cms.untracked.int32(-1) )
#    KinFitter           = cms.untracked.PSet( limit = cms.untracked.int32(-1) )
)

#-------------------------------------------------
# process configuration
#-------------------------------------------------

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    ## PAT test sample on AFS
    'file:/afs/cern.ch/cms/PRS/top/cmssw-data/relval200-for-pat-testing/FullSimTTBar-2_1_X_2008-07-08_STARTUP_V4-AODSIM.100.root'
    ## TTBar 2_2_3 RelVal sample at CASTOR (36500 events, 25 files)
    #'/store/relval/CMSSW_2_2_3/RelValTTbar/GEN-SIM-DIGI-RECO/IDEAL_V11_FastSim_v3/0002/1A728879-12CB-DD11-8EFA-001D09F24498.root',
    #'/store/relval/CMSSW_2_2_3/RelValTTbar/GEN-SIM-DIGI-RECO/IDEAL_V11_FastSim_v3/0002/1ED314BA-12CB-DD11-8EBC-000423D60FF6.root',
    #'/store/relval/CMSSW_2_2_3/RelValTTbar/GEN-SIM-DIGI-RECO/IDEAL_V11_FastSim_v3/0002/4271ADD6-18CB-DD11-9549-001617C3B6CC.root',
    #'/store/relval/CMSSW_2_2_3/RelValTTbar/GEN-SIM-DIGI-RECO/IDEAL_V11_FastSim_v3/0002/4EC98C20-18CB-DD11-B178-000423D98BC4.root',
    #'/store/relval/CMSSW_2_2_3/RelValTTbar/GEN-SIM-DIGI-RECO/IDEAL_V11_FastSim_v3/0002/569C1441-17CB-DD11-8800-001617E30F4C.root',
    #'/store/relval/CMSSW_2_2_3/RelValTTbar/GEN-SIM-DIGI-RECO/IDEAL_V11_FastSim_v3/0002/64E94863-1ACB-DD11-BE5C-0019B9F70468.root',
    #'/store/relval/CMSSW_2_2_3/RelValTTbar/GEN-SIM-DIGI-RECO/IDEAL_V11_FastSim_v3/0002/68C67AA7-18CB-DD11-81B4-001617E30E2C.root',
    #'/store/relval/CMSSW_2_2_3/RelValTTbar/GEN-SIM-DIGI-RECO/IDEAL_V11_FastSim_v3/0002/68F07FD8-12CB-DD11-8AC5-001617C3B77C.root',
    #'/store/relval/CMSSW_2_2_3/RelValTTbar/GEN-SIM-DIGI-RECO/IDEAL_V11_FastSim_v3/0002/763BDA8D-18CB-DD11-97FD-001D09F28D54.root',
    #'/store/relval/CMSSW_2_2_3/RelValTTbar/GEN-SIM-DIGI-RECO/IDEAL_V11_FastSim_v3/0002/7EF899CD-12CB-DD11-A35B-000423D98DD4.root',
    #'/store/relval/CMSSW_2_2_3/RelValTTbar/GEN-SIM-DIGI-RECO/IDEAL_V11_FastSim_v3/0002/866E87BC-12CB-DD11-A7C1-001617E30D38.root',
    #'/store/relval/CMSSW_2_2_3/RelValTTbar/GEN-SIM-DIGI-RECO/IDEAL_V11_FastSim_v3/0002/8AF349D5-12CB-DD11-8C14-000423D8F63C.root',
    #'/store/relval/CMSSW_2_2_3/RelValTTbar/GEN-SIM-DIGI-RECO/IDEAL_V11_FastSim_v3/0002/965D66D8-18CB-DD11-8DC5-001617E30F50.root',
    #'/store/relval/CMSSW_2_2_3/RelValTTbar/GEN-SIM-DIGI-RECO/IDEAL_V11_FastSim_v3/0002/9E513379-18CB-DD11-BAAB-000423D991D4.root',
    #'/store/relval/CMSSW_2_2_3/RelValTTbar/GEN-SIM-DIGI-RECO/IDEAL_V11_FastSim_v3/0002/9E75F277-18CB-DD11-ADCE-001617E30E28.root',
    #'/store/relval/CMSSW_2_2_3/RelValTTbar/GEN-SIM-DIGI-RECO/IDEAL_V11_FastSim_v3/0002/B2BFF57A-18CB-DD11-A924-000423D9870C.root',
    #'/store/relval/CMSSW_2_2_3/RelValTTbar/GEN-SIM-DIGI-RECO/IDEAL_V11_FastSim_v3/0002/BC5ABAD9-18CB-DD11-9BCF-001D09F23A02.root',
    #'/store/relval/CMSSW_2_2_3/RelValTTbar/GEN-SIM-DIGI-RECO/IDEAL_V11_FastSim_v3/0002/C2298FC1-18CB-DD11-8BDD-001D09F28D54.root',
    #'/store/relval/CMSSW_2_2_3/RelValTTbar/GEN-SIM-DIGI-RECO/IDEAL_V11_FastSim_v3/0002/C8B18AED-12CB-DD11-A6F3-000423D33970.root',
    #'/store/relval/CMSSW_2_2_3/RelValTTbar/GEN-SIM-DIGI-RECO/IDEAL_V11_FastSim_v3/0002/DE4FF686-18CB-DD11-828A-000423D986C4.root',
    #'/store/relval/CMSSW_2_2_3/RelValTTbar/GEN-SIM-DIGI-RECO/IDEAL_V11_FastSim_v3/0002/F035392E-18CB-DD11-9CAF-001617DBD230.root',
    #'/store/relval/CMSSW_2_2_3/RelValTTbar/GEN-SIM-DIGI-RECO/IDEAL_V11_FastSim_v3/0002/F852D80A-18CB-DD11-84AF-001617C3B6DC.root',
    #'/store/relval/CMSSW_2_2_3/RelValTTbar/GEN-SIM-DIGI-RECO/IDEAL_V11_FastSim_v3/0002/FAAE58A3-14CB-DD11-A372-000423D99BF2.root',
    #'/store/relval/CMSSW_2_2_3/RelValTTbar/GEN-SIM-DIGI-RECO/IDEAL_V11_FastSim_v3/0002/FCF0C3B9-12CB-DD11-B0B9-000423D9517C.root',
    #'/store/relval/CMSSW_2_2_3/RelValTTbar/GEN-SIM-DIGI-RECO/IDEAL_V11_FastSim_v3/0003/ECA1CE88-74CB-DD11-8AAE-000423D99E46.root'
    ),
    #skipEvents = cms.untracked.uint32(400)
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
process.GlobalTag.globaltag = cms.string('STARTUP_V7::All')

## Magnetic field now needs to be in the high-level py
process.load("Configuration.StandardSequences.MagneticField_cff")

#-------------------------------------------------
# tqaf configuration
#-------------------------------------------------

## std sequence for tqaf layer1
process.load("TopQuarkAnalysis.TopObjectProducers.tqafLayer1_cff")
process.p0 = cms.Path(process.tqafLayer1)

## necessary fixes to run 2.2.X on 2.1.X data
## comment this when running on samples produced
## with 22X
from PhysicsTools.PatAlgos.tools.cmsswVersionTools import run22XonSummer08AODSIM
run22XonSummer08AODSIM(process)

## std sequence to produce the ttGenEvt
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")

## configure ttGenEventFilters
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEventFilters_cff")
process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.electron = False
process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.muon     = True
process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.tau      = False

## std sequence to produce the ttSemiLepEvent
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttSemiLepEvtBuilder_cff")
process.ttSemiLepEvent.verbosity = 1
## change maximum number of jets taken into account per event (default: 4)
process.ttSemiLepEvent.maxNJets = 5
## change maximum number of jet combinations taken into account per event (default: 1)
#process.findTtSemiLepJetCombMVA       .maxNComb = -1
#process.kinFitTtSemiLepEventHypothesis.maxNComb = -1

#-------------------------------------------------
# tqaf configuration
#-------------------------------------------------

## add event weight information
from TopAnalysis.TopUtils.EventWeightPlain_cfi import *
process.eventWeight = eventWeight

## analyze hypotheses
process.load("TopAnalysis.TopAnalyzer.SemiLepHypothesesAnalyzer_cff")

#-------------------------------------------------
# file service for output
#-------------------------------------------------

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeSemiLepHypotheses.root')
)

#-------------------------------------------------
# paths
#-------------------------------------------------

process.p2 = cms.Path(process.makeGenEvt *
                      process.ttSemiLeptonicFilter *
                      process.makeTtSemiLepEvent *
                      process.eventWeight *
                      process.analyzeAllSemiLepHypotheses
                      )
