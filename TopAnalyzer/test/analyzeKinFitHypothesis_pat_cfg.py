import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# cfg file for the analysis of selected muon
# quantities
#-------------------------------------------------
process = cms.Process("TopQuark")

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
    ## add your favourite file here
    'file:/afs/naf.desy.de/user/r/rwolf/data/samples/ttbar09/patTuple_sig_0_ttbarx09.root'
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

#-------------------------------------------------
# top analysis
#-------------------------------------------------

## produce top generated event
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEventFilters_cff")
process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.electron = False
process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.muon     = True

## produce top reconstructed event
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttSemiLepEvtBuilder_cff")
## process.ttSemiLepJetPartonMatch.verbosity = 1

## configure fit hypothesis
process.ttSemiLepHypKinFit.leps = "tightMuons"
process.ttSemiLepHypKinFit.jets = "tightLeadingJets"


## apply realistic event selection
process.load("TopAnalysis.TopFilter.sequences.semiLeptonicSelection_cff")
#from TopAnalysis.TopFilter.sequences.semiLeptonicSelection_cff import disableCountFilter
#disableCountFilter(process.bottomJetSelection)

## analyze top quarks on generator level
process.load("TopAnalysis.TopAnalyzer.HypothesisKinFit_cfi")
process.load("TopAnalysis.TopAnalyzer.HypothesisKinFitMET_cfi" )
process.load("TopAnalysis.TopAnalyzer.HypothesisKinFitJets_cfi" )
process.load("TopAnalysis.TopAnalyzer.HypothesisKinFitMuon_cfi")

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeHypothesisKinFit.root')
)

process.p1 = cms.Path(process.makeGenEvt *
                      process.ttSemiLeptonicFilter *
                      process.makeTtSemiLepEvent *
                      process.semiLeptonicSelection *           ## comment this line to run w/o selection
                      process.analyzeHypothesisKinFit +
                      process.analyzeHypothesisKinFitMET *
                      process.analyzeHypothesisKinFitJets +
                      process.analyzeHypothesisKinFitMuon
                      )
