import FWCore.ParameterSet.Config as cms

# analyse jet quantities
process = cms.Process("test")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    ## add your favourite file here
   )
)

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

## register TFileService
process.TFileService = cms.Service("TFileService",  
            fileName = cms.string('analyzeJetKinematics_test.root')
)

## setup the jet selection collection
process.load("PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi")

process.goodJets = process.selectedPatJets.clone(src = 'selectedPatJets',
                                                 cut = 'abs(eta) < 2.4 & pt > 30. &'
                                                       'emEnergyFraction > 0.01   &'
                                                       'jetID.fHPD < 0.98         &'
                                                       'jetID.n90Hits > 1'
                                                 )

process.trackCountingHighEffBJets  = process.selectedPatJets.clone(src = 'goodJets',
                                                                   cut = 'bDiscriminator(\"trackCountingHighEffBJetTags\") > 1.9'
                                                                   )

process.simpleSecondaryVertexBJets = process.selectedPatJets.clone(src = 'goodJets',
                                                                   cut = 'bDiscriminator(\"simpleSecondaryVertexBJetTags\") > 2.02'
                                                                   )

## define ordered jets
uds0    = cms.PSet(index = cms.int32(0), correctionLevel = cms.string('L3Absolute'), useTree = cms.bool(False))
uds1    = cms.PSet(index = cms.int32(1), correctionLevel = cms.string('L3Absolute'), useTree = cms.bool(False))
uds2    = cms.PSet(index = cms.int32(2), correctionLevel = cms.string('L3Absolute'), useTree = cms.bool(False))
uds3    = cms.PSet(index = cms.int32(3), correctionLevel = cms.string('L3Absolute'), useTree = cms.bool(False))
uds4    = cms.PSet(index = cms.int32(4), correctionLevel = cms.string('L3Absolute'), useTree = cms.bool(False))
uds5    = cms.PSet(index = cms.int32(5), correctionLevel = cms.string('L3Absolute'), useTree = cms.bool(False))
bottom0 = cms.PSet(index = cms.int32(0), correctionLevel = cms.string('L3Absolute'), useTree = cms.bool(False))
bottom1 = cms.PSet(index = cms.int32(1), correctionLevel = cms.string('L3Absolute'), useTree = cms.bool(False))

## ---
##    MONITOR JET KINEMATICS
## ---

## jet kinematics analyzer
process.load("TopAnalysis.TopAnalyzer.JetKinematics_cfi")

## collect kinematics analyzers
process.leadingJetKinematics = process.analyzeJetKinematics.clone (src = 'goodJets')
process.lead_0_JetKinematics = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds0 )
process.lead_1_JetKinematics = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds1 )
process.lead_2_JetKinematics = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds2 )
process.lead_3_JetKinematics = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds3 )
process.lead_4_JetKinematics = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds4 )
process.lead_5_JetKinematics = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds5 )

process.bTCHEJetKinematics    = process.analyzeJetKinematics.clone (src = 'trackCountingHighEffBJets' )
process.bTCHE_0_JetKinematics = process.analyzeJetKinematics.clone (src = 'trackCountingHighEffBJets' , analyze = bottom0)
process.bTCHE_1_JetKinematics = process.analyzeJetKinematics.clone (src = 'trackCountingHighEffBJets' , analyze = bottom1)

process.bSSVJetKinematics    = process.analyzeJetKinematics.clone (src = 'simpleSecondaryVertexBJets' )
process.bSSV_0_JetKinematics = process.analyzeJetKinematics.clone (src = 'simpleSecondaryVertexBJets' , analyze = bottom0)
process.bSSV_1_JetKinematics = process.analyzeJetKinematics.clone (src = 'simpleSecondaryVertexBJets' , analyze = bottom1)
## analyze the kinematics of the jets in the event
process.p1 = cms.Path(process.goodJets                   *
                      process.trackCountingHighEffBJets  *
                      process.simpleSecondaryVertexBJets *
                      process.bTCHEJetKinematics         +
                      process.bTCHE_0_JetKinematics      +
                      process.bTCHE_1_JetKinematics      +
                      process.bSSVJetKinematics          +
                      process.bSSV_0_JetKinematics       +
                      process.bSSV_1_JetKinematics       +
                      process.leadingJetKinematics       +
                      process.lead_0_JetKinematics       +
                      process.lead_1_JetKinematics       +
                      process.lead_2_JetKinematics       +
                      process.lead_3_JetKinematics       +
                      process.lead_4_JetKinematics       +
                      process.lead_5_JetKinematics  
                      )
