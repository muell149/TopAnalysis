import FWCore.ParameterSet.Config as cms

## ---
##    here we need a general description of what the config id good for and the
##    switches mean. This should be in analogy of the Doxygen commentsin the
##    modules...
## --- 
eventFilter  = False # False
signalInvert = False # True

# analyse top quark quantities
process = cms.Process("TopQuark")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
#process.MessageLogger.cerr.FwkReport.reportEvery = 100

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(    
    ## add your favourite file here
    'file:/afs/naf.desy.de/user/r/rwolf/data/samples/ttbar09/patTuple_selected_sig_0_ttbarx09.root'
    ## "file:patTuple.root"
    )
)

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(False)
)

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeTopQuarks.root')
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
        process.TFileService.fileName = 'analyzeTopQuarks_sig.root'
    else:
        process.TFileService.fileName = 'analyzeTopQuarks_bkg.root'        
else:
    ## sequence without filter
    process.filterSequence = cms.Sequence(process.makeGenEvt)

## ---
##    configure the eventHypotheses this part should be stored centrally soon
## ---

## produce top reconstructed event
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttSemiLepEvtBuilder_cff")
## process.ttSemiLepJetPartonMatch.verbosity = 1
process.kinFitTtSemiLepEventHypothesis.leps = "tightMuons"
process.kinFitTtSemiLepEventHypothesis.jets = "tightLeadingJets"
process.kinFitTtSemiLepEventHypothesis.maxNJets = 5
process.kinFitTtSemiLepEventHypothesis.maxNComb = 3
process.kinFitTtSemiLepEventHypothesis.constraints = [1, 2, 3, 4]

## ---
##    configure the analyzer
## ---

## define PSets
matchedGenMatch = cms.PSet(hypoKey=cms.string('kGenMatch'), matchForStabilityAndPurity=cms.bool(True ) )
matchedKinFit   = cms.PSet(hypoKey=cms.string('kKinFit'  ), matchForStabilityAndPurity=cms.bool(True ) )
recoGenMatch    = cms.PSet(hypoKey=cms.string('kGenMatch'), matchForStabilityAndPurity=cms.bool(False) )
recoKinFit      = cms.PSet(hypoKey=cms.string('kKinFit'  ), matchForStabilityAndPurity=cms.bool(False) )

## analyze top quarks on generator level
process.load("TopAnalysis.TopAnalyzer.TopKinematics_gen_cfi")
process.load("TopAnalysis.TopAnalyzer.TopKinematics_rec_cfi")
process.analyzeTopRecoKinematicsKinFit      = process.analyzeTopRecKinematics.clone(analyze=recoKinFit      )
process.analyzeTopRecoKinematicsGenMatch    = process.analyzeTopRecKinematics.clone(analyze=recoGenMatch    )
process.analyzeTopMatchedKinematicsKinFit   = process.analyzeTopRecKinematics.clone(analyze=matchedKinFit   )
process.analyzeTopMatchedKinematicsGenMatch = process.analyzeTopRecKinematics.clone(analyze=matchedGenMatch )

## ---
##    run the final sequence
## ---
process.p1 = cms.Path(## do the gen evetn selection
                      process.filterSequence              *
                      ## make the semi-leptonic event hyotheses
                      process.makeTtSemiLepEvent          *
                       ## analyze the output
                      process.analyzeTopGenKinematics     +
                      process.analyzeTopRecoKinematicsKinFit     +
                      process.analyzeTopRecoKinematicsGenMatch   +
                      process.analyzeTopMatchedKinematicsKinFit  +
                      process.analyzeTopMatchedKinematicsGenMatch
                      )
