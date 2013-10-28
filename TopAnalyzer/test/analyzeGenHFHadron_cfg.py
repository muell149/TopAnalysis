import FWCore.ParameterSet.Config as cms

## ---
##   use this file to test the GenHFHadronAnalyzer.cc module
## ---


# set sequence shortcut
process = cms.Process("Analyzer")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 100

## define input
process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring(    
    ## add your favourite file here
    '/store/mc/Summer12_DR53X/TTJets_FullLeptMGDecays_8TeV-madgraph/AODSIM/PU_S10_START53_V7A-v1/00000/FEF43CF5-E60F-E211-9FBB-E0CB4E1A117A.root',
    '/store/mc/Summer12_DR53X/TTJets_FullLeptMGDecays_8TeV-madgraph/AODSIM/PU_S10_START53_V7A-v1/00000/FEB2FB74-2B10-E211-8B1F-00259073E322.root',
    '/store/mc/Summer12_DR53X/TTJets_FullLeptMGDecays_8TeV-madgraph/AODSIM/PU_S10_START53_V7A-v1/00000/FEA9D489-1910-E211-A6E4-00259073E3D6.root',
    '/store/mc/Summer12_DR53X/TTJets_FullLeptMGDecays_8TeV-madgraph/AODSIM/PU_S10_START53_V7A-v1/00000/FE675CF5-0810-E211-A5A3-E0CB4EA0A904.root',
    '/store/mc/Summer12_DR53X/TTJets_FullLeptMGDecays_8TeV-madgraph/AODSIM/PU_S10_START53_V7A-v1/00000/FE64FE2E-DB0F-E211-BF12-90E6BA442F33.root',
    '/store/mc/Summer12_DR53X/TTJets_FullLeptMGDecays_8TeV-madgraph/AODSIM/PU_S10_START53_V7A-v1/00000/FE1EAE1A-4410-E211-BBB4-001EC9D8A8D4.root',
    '/store/mc/Summer12_DR53X/TTJets_FullLeptMGDecays_8TeV-madgraph/AODSIM/PU_S10_START53_V7A-v1/00000/FCE064CB-DB0F-E211-89C3-E0CB4EA0A937.root',
    '/store/mc/Summer12_DR53X/TTJets_FullLeptMGDecays_8TeV-madgraph/AODSIM/PU_S10_START53_V7A-v1/00000/FCA17D81-0510-E211-A333-20CF305616CC.root',
    '/store/mc/Summer12_DR53X/TTJets_FullLeptMGDecays_8TeV-madgraph/AODSIM/PU_S10_START53_V7A-v1/00000/FC8E9086-F10F-E211-9A3F-00259073E3B4.root',
    '/store/mc/Summer12_DR53X/TTJets_FullLeptMGDecays_8TeV-madgraph/AODSIM/PU_S10_START53_V7A-v1/00000/FC742CD1-C00F-E211-8277-20CF305B0572.root',
    '/store/mc/Summer12_DR53X/TTJets_FullLeptMGDecays_8TeV-madgraph/AODSIM/PU_S10_START53_V7A-v1/00000/FC354441-FF0F-E211-A9AC-E0CB4E553641.root',
    '/store/mc/Summer12_DR53X/TTJets_FullLeptMGDecays_8TeV-madgraph/AODSIM/PU_S10_START53_V7A-v1/00000/FC1E7E5A-E60F-E211-9605-485B39800C3B.root',
    '/store/mc/Summer12_DR53X/TTJets_FullLeptMGDecays_8TeV-madgraph/AODSIM/PU_S10_START53_V7A-v1/00000/FAB3BB25-2210-E211-968B-20CF305616E0.root',
    '/store/mc/Summer12_DR53X/TTJets_FullLeptMGDecays_8TeV-madgraph/AODSIM/PU_S10_START53_V7A-v1/00000/F8FDB54E-1110-E211-A162-E0CB4E19F962.root'
    ),
    skipEvents = cms.untracked.uint32(0)
 )

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeGenHFHadronJetsAnalyzer_test.root')
)

## ---
##    load GenParticle
## ---

# get gen ttbar event
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")

# get genJets with hadrons in it
process.load("TopAnalysis.TopUtils.sequences.improvedJetHadronQuarkMatching_cff")

# supply PDG ID to real name resolution of MC particles, necessary for GenHFHadronAnalyzer
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

## get particle content of sample with IDs
process.load("TopAnalysis.TopAnalyzer.GenHFHadronAnalyzer_cff")
process.analyzeGenHFHadronJets = process.analyzeGenHFHadronJets.clone()

process.analyzeGenHFHadronJets.noBBbarResonances = True


## ---
##    run the final sequence
## ---

process.p1 = cms.Path(
    ## apply the analyzer
    process.makeGenEvt *
    process.improvedJetHadronQuarkMatchingSequence *
    process.analyzeGenHFHadronJets
    )
