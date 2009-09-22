import FWCore.ParameterSet.Config as cms

## ---
##    here we need a general description of what the config id good for and the
##    switches mean. This should be in analogy of the Doxygen commentsin the
##    modules...
## --- 
useAntikt5   = False # True
eventFilter  = True  # False
signalInvert = False # True


# analyse jet quantities
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

if(eventFilter):
    ## sequence with filter
    process.filterSequence = cms.Sequence(process.makeGenEvt *
                                          process.ttSemiLeptonicFilter
                                          )
    ## adapt output filename
    if(not signalInvert):
        process.TFileService.fileName = 'analyzeJets_sig.root'
    else:
        process.TFileService.fileName = 'analyzeJets_bkg.root'        
else:
    ## sequence without filter
    process.filterSequence = cms.Sequence(process.makeGenEvt)

## ---
##    configure the cutflow scenario
## ---

## jet quality analyzer
process.load("TopAnalysis.TopAnalyzer.JetQuality_cfi")
## jet kinematics analyzer
process.load("TopAnalysis.TopAnalyzer.JetKinematics_cfi")
## pre-defined jet selection
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

## collect kinematics analyzers
process.goodJetKinematics     = process.analyzeJetKinematics.clone(src = 'goodJets'     )
process.centralJetKinematics  = process.analyzeJetKinematics.clone(src = 'centralJets'  )
process.reliableJetKinematics = process.analyzeJetKinematics.clone(src = 'reliableJets' )
process.goodJet_0_Kinematics  = process.analyzeJetKinematics.clone(src = 'goodJets', analyze = abs0  )
process.goodJet_1_Kinematics  = process.analyzeJetKinematics.clone(src = 'goodJets', analyze = abs1  )
process.goodJet_2_Kinematics  = process.analyzeJetKinematics.clone(src = 'goodJets', analyze = abs2  )
process.goodJet_3_Kinematics  = process.analyzeJetKinematics.clone(src = 'goodJets', analyze = abs3  )

## to be called with jet quality monitoring
process.monitorJetKinematics  = cms.Sequence(process.goodJetKinematics     +
                                             process.centralJetKinematics  +
                                             process.reliableJetKinematics +
                                             process.goodJet_0_Kinematics  +
                                             process.goodJet_1_Kinematics  +
                                             process.goodJet_2_Kinematics  +
                                             process.goodJet_3_Kinematics
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
                      process.filterSequence       *
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
