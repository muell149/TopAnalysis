import FWCore.ParameterSet.Config as cms

## ---
##    here we need a general description of what the config id good for and the
##    switches mean. This should be in analogy of the Doxygen commentsin the
##    modules...
## ---

## ---
##    decide whether to run on:  * all *, * signal only *, * background only *
## ---
eventFilter  = 'signal only'

## NOT YET REIMPLEMENTED
usePF       = True  # False
writeOutput = False # True

# analyse muon quantities
process = cms.Process("Selection")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 100

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(    
    ## add your favourite file here
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_1_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_2_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_3_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_4_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_5_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_6_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_7_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_8_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_9_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_10_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_11_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_12_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_13_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_14_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_15_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_16_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_17_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_18_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_19_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_20_1.root'
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
            fileName = cms.string('analyzeFullHadronicSelection_all.root')
)

## ---
##    decide whether to run on:  * all *, * signal only *, * background only *
## ---

## std sequence to produce the ttGenEvt
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")

## filter for full-hadronic 
process.load("TopQuarkAnalysis.TopEventProducers.producers.TtDecaySelection_cfi")
process.ttFullHadronicFilter = process.ttDecaySelection.clone()

## ptHat filter
process.load("TopAnalysis.TopFilter.filters.PtHatFilter_cfi")
process.filterPtHat = process.filterPtHat.clone()


if(not eventFilter=='all'):
    ## adapt output filename
    if(eventFilter=='signal only'):
        process.TFileService.fileName = 'analyzeFullHadronicSelection_sig.root'
    elif(eventFilter=='background only'):
        process.ttFullHadronicFilter.invert = True
        process.TFileService.fileName = 'analyzeFullHadronicSelection_bkg.root'
    else:
        raise NameError, "'"+eventFilter+"' is not a prober eventFilter name choose: 'all', 'signal only' or 'background only'"
    
    ## sequence with filter
    process.filterSequence = cms.Sequence(#process.patDefaultSequence *
                                          process.makeGenEvt *
                                          process.ttFullHadronicFilter
                                          )
else:
    ## sequence without filter
    process.filterSequence = cms.Sequence(#process.patDefaultSequence *
                                          process.filterPtHat)

## fully hadronic selection
process.load("TopAnalysis.TopFilter.sequences.fullHadronicSelection_cff")
from TopAnalysis.TopFilter.sequences.fullHadronicSelection_cff import *

## do kinematic fit needed for fully hadronic selection
from TopQuarkAnalysis.TopEventProducers.sequences.ttFullHadEvtBuilder_cff import *

addTtFullHadHypotheses(process,
                       ["kKinFit"]
                       )

if(not eventFilter=='signal only'):
    removeTtFullHadHypGenMatch(process)

## selection should be run on PFJets instead of caloJets
if(usePF):
    runOnPF(process)

## ---
##    run the final sequence
## ---
process.p1 = cms.Path(## do the genEvent selection
                      process.filterSequence        *
                      ## do the filtering
                      process.analyseFullHadronicSelection
                      )

## Output Module Configuration
if(writeOutput):
    process.out = cms.OutputModule("PoolOutputModule",
                                   fileName = cms.untracked.string('patTuple_selected.root'),
                                   # save only events passing the full path
                                   SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p1') ),
                                   # save output (comment to keep everything...)
                                   #outputCommands = cms.untracked.vstring('drop *',) 
                                   )
    process.outpath = cms.EndPath(process.out)
