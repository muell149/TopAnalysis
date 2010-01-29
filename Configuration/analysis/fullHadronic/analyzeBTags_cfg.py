import FWCore.ParameterSet.Config as cms

## ---
##    here we need a general description of what the config id good for and the
##    switches mean. This should be in analogy of the Doxygen commentsin the
##    modules...
## ---

## ---
##    decide whether to run on:  * all *, * signal only *, * background only *
## ---
eventFilter  = 'signal only' # 'signal only' # 'background only' # 'all'

## NOT YET REIMPLEMENTED
useAntikt5   = True # False
writeOutput  = False # True

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
    '/store/user/rwolf/ttbar09/patTuple_all_0_ttbar09.root',
    '/store/user/rwolf/ttbar09/patTuple_all_10_ttbar09.root',
    '/store/user/rwolf/ttbar09/patTuple_all_11_ttbar09.root',
    '/store/user/rwolf/ttbar09/patTuple_all_12_ttbar09.root',
    '/store/user/rwolf/ttbar09/patTuple_all_13_ttbar09.root',
    '/store/user/rwolf/ttbar09/patTuple_all_14_ttbar09.root',
    '/store/user/rwolf/ttbar09/patTuple_all_15_ttbar09.root',
    '/store/user/rwolf/ttbar09/patTuple_all_16_ttbar09.root',
    '/store/user/rwolf/ttbar09/patTuple_all_17_ttbar09.root',
    '/store/user/rwolf/ttbar09/patTuple_all_18_ttbar09.root'
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

## configure geometry & conditions
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('MC_31X_V9::All')

## std sequence for pat
process.load("PhysicsTools.PatAlgos.patSequences_cff")

## register TFileService
process.TFileService = cms.Service("TFileService",  
            fileName = cms.string('analyzeBTags_all.root')
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

## filter event shape
process.filterPtHat = process.filterPtHat.clone()


if(not eventFilter=='all'):
    ## adapt output filename
    if(eventFilter=='signal only'):
        process.TFileService.fileName = 'analyzeBTags_sig.root'
    elif(eventFilter=='background only'):
        process.ttFullHadronicFilter.invert = True
        process.TFileService.fileName = 'analyzeBTags_bkg.root'
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

## ---
##    configure bTag Analysis
## ---

## generator matching
process.load("TopAnalysis.TopFilter.sequences.generatorMatching_cff")
## generator matching
process.load("TopAnalysis.TopAnalyzer.BTags_cfi")
## fullhadronic selection (for jet collections)
process.load("TopAnalysis.TopFilter.sequences.fullHadronicSelection_cff")

## replace sisCone5 by antikt5
if( useAntikt5 ):
    process.goodJets.src = 'selectedLayer1JetsAK5'

## bTag analyzers
process.analyzeBTags = process.analyzeBTags.clone( src = 'tightLeadingJets' )

## ---
##    run the final sequence
## ---
process.p1 = cms.Path(## do the gen evetn selection
                      process.filterSequence        *
                      ## create jet collections
                      process.fullHadronicSelection *
                      ## do the matching
                      process.matchJetsToPartons    *
                      ## do bTag analysis
                      process.analyzeBTags                      
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
