import FWCore.ParameterSet.Config as cms

## ---
##    here we need a general description of what the config id good for and the
##    switches mean. This should be in analogy of the Doxygen commentsin the
##    modules...
## --- 
useAntikt5    = False
signalInvert  = True


# analyse muon quantities
process = cms.Process("analyzeJets")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 100

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(    
    ## add your favourite file here
    'file:/afs/naf.desy.de/user/r/rwolf/data/samples/ttbar09/patTuple_all_0_ttbar09.root'
    )
)

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeJets_all.root')
)

## ---
##    decide whether to run on:  * all *, * signal only *, * background only *
## ---

## std sequence to produce the ttGenEvt
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")

## filter for semi-leptonic 
process.load("TopQuarkAnalysis.TopEventProducers.producers.TtDecaySelection_cfi")
process.ttSemiLeptonicFilter = process.ttDecaySelection.clone()
process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.muon = True
process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchB.muon = False
process.ttSemiLeptonicFilter.invert = signalInvert

## ---
##    configure the cutflow scenario
## ---

## muon quality analyzer
process.load("TopAnalysis.TopAnalyzer.JetQuality_cfi")
## muon kinematics analyzer
process.load("TopAnalysis.TopAnalyzer.JetKinematics_cfi")
## pre-defined muon selection
process.load("TopAnalysis.TopFilter.sequences.jetSelection_cff")
## high level trigger filter
process.load("TopAnalysis.TopFilter.sequences.triggerFilter_cff")

## replace sisCone5 by antikt5
if( useAntikt5 ):
    process.goodJets.src = 'selectedLayer1JetsAK5'

## define ordered jets
abs0  = cms.PSet(index = cms.int32( 0), correctionLevel = cms.string('abs')   )
abs1  = cms.PSet(index = cms.int32( 1), correctionLevel = cms.string('abs')   )
abs2  = cms.PSet(index = cms.int32( 2), correctionLevel = cms.string('abs')   )
abs3  = cms.PSet(index = cms.int32( 3), correctionLevel = cms.string('abs')   )

## define jet correction levels
L0Raw = cms.PSet(index = cms.int32(-1), correctionLevel = cms.string('raw')   )
L2Rel = cms.PSet(index = cms.int32(-1), correctionLevel = cms.string('rel')   )
L3Abs = cms.PSet(index = cms.int32(-1), correctionLevel = cms.string('abs')   )
L5Had = cms.PSet(index = cms.int32(-1), correctionLevel = cms.string('had:b') )
L7Part= cms.PSet(index = cms.int32(-1), correctionLevel = cms.string('part:b'))

## collect kinematics analyzers
process.goodJetKinematics     = process.analyzeJetKinematics.clone(src = 'goodJets'     )
process.centralJetKinematics  = process.analyzeJetKinematics.clone(src = 'centralJets'  )
process.reliableJetKinematics = process.analyzeJetKinematics.clone(src = 'reliableJets' )
process.goodJet_0_Kinematics  = process.analyzeJetKinematics.clone(src = 'goodJets', analyze = abs0  )
process.goodJet_1_Kinematics  = process.analyzeJetKinematics.clone(src = 'goodJets', analyze = abs1  )
process.goodJet_2_Kinematics  = process.analyzeJetKinematics.clone(src = 'goodJets', analyze = abs2  )
process.goodJet_3_Kinematics  = process.analyzeJetKinematics.clone(src = 'goodJets', analyze = abs3  )
process.goodJet_L0_Kinematics = process.analyzeJetKinematics.clone(src = 'goodJets', analyze = L0Raw )
process.goodJet_L1_Kinematics = process.analyzeJetKinematics.clone(src = 'goodJets', analyze = L2Rel )
process.goodJet_L2_Kinematics = process.analyzeJetKinematics.clone(src = 'goodJets', analyze = L3Abs )


## to be called with jet quality monitoring
process.monitorJetKinematics  = cms.Sequence(process.goodJetKinematics     +
                                             process.centralJetKinematics  +
                                             process.reliableJetKinematics +
                                             process.goodJet_0_Kinematics  +
                                             process.goodJet_1_Kinematics  +
                                             process.goodJet_2_Kinematics  +
                                             process.goodJet_3_Kinematics  +
                                             process.goodJet_L0_Kinematics +
                                             process.goodJet_L1_Kinematics +
                                             process.goodJet_L2_Kinematics
                                             ) 

## collect quality analyzers for goodJets
process.goodJetQuality     = process.analyzeJetQuality.clone(src = 'goodJets')
process.centralJetQuality  = process.analyzeJetQuality.clone(src = 'centralJets')
process.reliableJetQuality = process.analyzeJetQuality.clone(src = 'reliableJets')

## to be called with the *selectGoodJets + goodJets* sequence
process.monitorGoodJets = cms.Sequence(process.goodJetQuality    +
                                       process.centralJetQuality +
                                       process.reliableJetQuality
                                       )

## collect quality analyzers for bTaggedJets
process.trackCountingHighPurBJetQuality     = process.analyzeJetQuality.clone(src = 'trackCountingHighPurBJets')
process.trackCountingHighEffBJetQuality     = process.analyzeJetQuality.clone(src = 'trackCountingHighEffBJets')
process.simpleSecondaryVertexBJetQuality    = process.analyzeJetQuality.clone(src = 'simpleSecondaryVertexBJets')
process.simpleSecondaryVertexNegBJetQuality = process.analyzeJetQuality.clone(src = 'simpleSecondaryVertexNegBJets')

## to be called with the *selectBTaggedJets* sequence
process.monitorBTaggedJets = cms.Sequence(process.trackCountingHighPurBJetQuality  +
                                          process.trackCountingHighEffBJetQuality  +
                                          process.simpleSecondaryVertexBJetQuality +
                                          process.simpleSecondaryVertexNegBJetQuality
                                          )

## ---
##    run the final sequence
## ---
process.p1 = cms.Path(## do the gen evetn selection
                      process.makeGenEvt           *
                      process.ttSemiLeptonicFilter *
                      ## do the trigger selection
                      process.hltMu9               * 
                      ## do the selections
                      process.selectGoodJets       +
                      process.selectBTaggedJets    +
                      ## do the monitoring
                      process.monitorGoodJets      +
                      process.monitorBTaggedJets   +
                      process.monitorJetKinematics
                      )
