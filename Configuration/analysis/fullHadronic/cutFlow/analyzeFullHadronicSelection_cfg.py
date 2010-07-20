import FWCore.ParameterSet.Config as cms

## ---
##    here we need a general description of what the config id good for and the
##    switches mean. This should be in analogy of the Doxygen commentsin the
##    modules...
## ---

## ---
##    decide whether to run on:  * all *, * signal only *, * background only *
## ---
eventFilter  = 'data'

## NOT YET REIMPLEMENTED
usePF       = True # False
writeOutput = False # True

# analyse muon quantities
process = cms.Process("Selection")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(    
    ## add your favourite file here
    '/store/user/eschliec/Run2010A/patTuple_6jets.root',
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_1_1.root',
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_2_1.root',
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_3_1.root',
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_4_1.root',
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_5_1.root',
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_6_1.root',
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_7_1.root',
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_8_1.root',
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_9_1.root',
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_10_1.root',
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_11_1.root',
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_12_1.root',
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_13_1.root',
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_14_1.root',
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_15_1.root',
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_16_1.root',
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_17_1.root',
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_18_1.root',
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_19_1.root',
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_20_1.root'
    ),
    ## just a code example how to skip lumi blocks or whole runs
    #lumisToSkip = cms.untracked.VLuminosityBlockRange('135445:0-135445:max',
    #                                                  '140126:0-140126:max'),
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
            fileName = cms.string('analyzeFullHadronicSelection.root')
)

## ---
##    decide whether to run on:  * all *, * signal only *, * background only * or * data *
## ---

## std sequence to produce the ttGenEvt
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")

## filter for full-hadronic 
process.load("TopQuarkAnalysis.TopEventProducers.producers.TtDecaySelection_cfi")
process.ttFullHadronicFilter = process.ttDecaySelection.clone()

## ptHat filter
process.load("TopAnalysis.TopFilter.filters.PtHatFilter_cfi")
process.filterPtHat = process.filterPtHat.clone()

## residual jet corrector for data
process.load("TopAnalysis.TopUtils.ResidualJetCorrector_cfi")
process.residualCorrectedJets = process.residualCorrectedJets.clone()

if(eventFilter=='data'):
    ## adapt output filename
    process.TFileService.fileName = 'analyzeFullHadronicSelection_data.root'
    ## sequence with jet energy corrections specially suited for data
    process.filterSequence = cms.Sequence(#process.patDefaultSequence *
                                          process.residualCorrectedJets
                                          )
    
elif(eventFilter=='signal only'):
    ## adapt output filename
    process.TFileService.fileName = 'analyzeFullHadronicSelection_sig.root'
    ## sequence with fullHad ttbar filter
    process.filterSequence = cms.Sequence(#process.patDefaultSequence *
                                          process.makeGenEvt *
                                          process.ttFullHadronicFilter
                                          )

elif(eventFilter=='background only'):
    ## invert fullHad filter
    process.ttFullHadronicFilter.invert = True
    ## adapt output filename
    process.TFileService.fileName = 'analyzeFullHadronicSelection_bkg.root'
    ## sequence with non-fullHad ttbar filter
    process.filterSequence = cms.Sequence(#process.patDefaultSequence *
                                          process.makeGenEvt *
                                          process.ttFullHadronicFilter
                                          )

elif(eventFilter=='all'):
    ## adapt output filename
    process.TFileService.fileName = 'analyzeFullHadronicSelection_all.root'
    ## sequence with ptHat filter
    process.filterSequence = cms.Sequence(#process.patDefaultSequence *
                                          process.filterPtHat)
else:
    raise NameError, "'"+eventFilter+"' is not a prober eventFilter name choose: 'all', 'signal only', 'background only' or 'data'"
    
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

## changing bTagger, possible are: SSV, CSV, CSVMVA
## only SSV has a officialy blessed WP like the default
#switchToSSV(process)

## selection should be run on PFJets instead of caloJets
if(usePF):
    runOnPF(process)

## if running on real data, do everything needed for this
if(eventFilter=='data'):
    runOnRealData(process)

## ---
##    run the final sequence
## ---
process.p1 = cms.Path(## do the genEvent selection
                      process.filterSequence *
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
