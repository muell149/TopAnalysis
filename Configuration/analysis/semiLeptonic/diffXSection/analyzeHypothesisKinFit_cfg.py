import FWCore.ParameterSet.Config as cms

## ---
##    here we need a general description of what the config id good for and the
##    switches mean. This should be in analogy of the Doxygen commentsin the
##    modules...
## --- 
eventFilter  = True  # False
signalInvert = False # True


# analyse the kinFit hypothesis
process = cms.Process("KinFit")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
#process.MessageLogger.cerr.FwkReport.reportEvery = 100

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(    
    ## add your favourite file here
    'file:/afs/naf.desy.de/user/r/rwolf/data/samples/ttbar09/patTuple_sig_0_ttbarx09.root'
    ## "file:patTuple.root"
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

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeHypothesisKinFit.root')
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
        process.TFileService.fileName = 'analyzeSemiLeptonicSelection_sig.root'
    else:
        process.TFileService.fileName = 'analyzeSemiLeptonicSelection_bkg.root'        
else:
    ## sequence without filter
    process.filterSequence = cms.Sequence(process.makeGenEvt)

## ---
##    configure the KinFit hypothesis
## ---

## produce top reconstructed event
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttSemiLepEvtBuilder_cff")
## process.ttSemiLepJetPartonMatch.verbosity = 1
process.ttSemiLepHypKinFit.leps = "tightMuons"
process.ttSemiLepHypKinFit.jets = "tightLeadingJets"

## ---
##    configure the analyzer
## ---

## analyze top quarks on generator level
process.load("TopAnalysis.TopAnalyzer.HypothesisKinFit_cfi")
process.load("TopAnalysis.TopAnalyzer.HypothesisKinFitMET_cfi" )
process.load("TopAnalysis.TopAnalyzer.HypothesisKinFitJets_cfi" )
process.load("TopAnalysis.TopAnalyzer.HypothesisKinFitMuon_cfi")

## ---
##    run the final sequence
## ---
process.p1 = cms.Path(## do the gen evetn selection
                      process.filterSequence              *
                      ## make the semi-leptonic event hyotheses
                      process.makeTtSemiLepEvent          *
                      ## analyze the output
                      process.analyzeHypothesisKinFit     +
                      process.analyzeHypothesisKinFitMET  +
                      process.analyzeHypothesisKinFitJets +
                      process.analyzeHypothesisKinFitMuon
                      )
