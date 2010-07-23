import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing

## ---
##    here we need a general description of what the config id good for and the
##    switches mean. This should be in analogy of the Doxygen commentsin the
##    modules...
## ---

# setup 'standard' options
options = VarParsing.VarParsing ('standard')
## decide whether to run on:  * data *, * signal only *, * background only *, * qcd *
options.register('eventFilter', 'data', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "kind of data to be processed")
## choose whether to use PF or not
options.register('usePF'      ,     1 , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int   , "use PF for processing")
##  choose whether to write output to disk or not
options.register('writeOutput',     0 , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int   , "write events surviving all cuts to disk")

# get and parse the command line arguments
options.parseArguments()

# analyze fully hadronic selection
process = cms.Process("Selection")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.MessageLogger.categories.append('TtFullHadronicEvent')

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
##    decide whether to run on:  * data *, * signal only *, * background only * or * qcd *
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

if(options.eventFilter=='data'):
    ## adapt output filename
    process.TFileService.fileName = 'analyzeFullHadronicSelection_data.root'
    ## sequence with jet energy corrections specially suited for data
    process.filterSequence = cms.Sequence(#process.patDefaultSequence *
                                          process.residualCorrectedJets
                                          )
    
elif(options.eventFilter=='signal only'):
    ## adapt output filename
    process.TFileService.fileName = 'analyzeFullHadronicSelection_sig.root'
    ## sequence with fullHad ttbar filter
    process.filterSequence = cms.Sequence(#process.patDefaultSequence *
                                          process.makeGenEvt *
                                          process.ttFullHadronicFilter
                                          )

elif(options.eventFilter=='background only'):
    ## invert fullHad filter
    process.ttFullHadronicFilter.invert = True
    ## adapt output filename
    process.TFileService.fileName = 'analyzeFullHadronicSelection_bkg.root'
    ## sequence with non-fullHad ttbar filter
    process.filterSequence = cms.Sequence(#process.patDefaultSequence *
                                          process.makeGenEvt *
                                          process.ttFullHadronicFilter
                                          )

elif(options.eventFilter=='qcd'):
    ## adapt output filename
    process.TFileService.fileName = 'analyzeFullHadronicSelection_qcd.root'

    # setup any variables and default values for the ptHatFilter
    options.register('maxPtHat', 999999., VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.float, "maxPtHat to be processed")
    options.register('minPtHat', 0.     , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.float, "minPtHat to be processed")

    # get and parse the command line arguments
    options.parseArguments()
    
    if(options.maxPtHat<999999.):
        ## ptHat filter
        process.filterPtHat.minPtHat = options.minPtHat
        print "included ptHatFilter with 'maxPtHat' =",
        print process.filterPtHat.maxPtHat

    if(options.minPtHat>0.):
        process.filterPtHat.minPtHat = options.minPtHat
        print "included ptHatFilter with 'minPtHat' =",
        print process.filterPtHat.minPtHat

    ## sequence with ptHat filter
    process.filterSequence = cms.Sequence(#process.patDefaultSequence *
                                          process.filterPtHat)
else:
    raise NameError, "'"+options.eventFilter+"' is not a prober eventFilter name choose: 'data', 'signal only', 'background only' or 'qcd'"
    
## fully hadronic selection
process.load("TopAnalysis.TopFilter.sequences.fullHadronicSelection_cff")
from TopAnalysis.TopFilter.sequences.fullHadronicSelection_cff import *

## do kinematic fit needed for fully hadronic selection
from TopQuarkAnalysis.TopEventProducers.sequences.ttFullHadEvtBuilder_cff import *

addTtFullHadHypotheses(process,
                       ["kKinFit"]
                       )

if(not options.eventFilter=='signal only'):
    removeTtFullHadHypGenMatch(process)

## changing bTagger, possible are: TCHE, SSV, CSV, CSVMVA
## only TCHE and SSV have a officialy blessed WP like the default (TCHP)
switchToTCHE(process)

## selection should be run on PFJets instead of caloJets
if(not options.usePF==0):
    runOnPF(process)

## if running on real data, do everything needed for this
if(options.eventFilter=='data'):
    runOnRealData(process)
    ## needed as in MC the process label is different -> trigger in data not found
    removeDefaultTrigger(process)

## ---
##    run the final sequence
## ---
process.p1 = cms.Path(## do the genEvent selection
                      process.filterSequence *
                      ## do the filtering
                      process.analyseFullHadronicSelection
                      )

## Output Module Configuration
if(options.writeOutput):
    process.out = cms.OutputModule("PoolOutputModule",
                                   fileName = cms.untracked.string('patTuple_selected.root'),
                                   # save only events passing the full path
                                   SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p1') ),
                                   # save output (comment to keep everything...)
                                   #outputCommands = cms.untracked.vstring('drop *',) 
                                   )
    process.outpath = cms.EndPath(process.out)
