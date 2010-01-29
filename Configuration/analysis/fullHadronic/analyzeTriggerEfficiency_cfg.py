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

useAntikt5   = True # False
writeOutput  = False # True

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
    '/store/user/rwolf/ttbar09/patTuple_all_0_ttbar09.root',
    '/store/user/rwolf/ttbar09/patTuple_all_1_ttbar09.root',
    '/store/user/rwolf/ttbar09/patTuple_all_2_ttbar09.root',
    '/store/user/rwolf/ttbar09/patTuple_all_3_ttbar09.root',
    '/store/user/rwolf/ttbar09/patTuple_all_4_ttbar09.root',
    '/store/user/rwolf/ttbar09/patTuple_all_5_ttbar09.root',
    '/store/user/rwolf/ttbar09/patTuple_all_6_ttbar09.root',
    '/store/user/rwolf/ttbar09/patTuple_all_7_ttbar09.root',
    '/store/user/rwolf/ttbar09/patTuple_all_8_ttbar09.root',
    '/store/user/rwolf/ttbar09/patTuple_all_9_ttbar09.root',
    '/store/user/rwolf/ttbar09/patTuple_all_10_ttbar09.root',
    '/store/user/rwolf/ttbar09/patTuple_all_11_ttbar09.root',
    '/store/user/rwolf/ttbar09/patTuple_all_12_ttbar09.root',
    '/store/user/rwolf/ttbar09/patTuple_all_13_ttbar09.root',
    '/store/user/rwolf/ttbar09/patTuple_all_14_ttbar09.root',
    '/store/user/rwolf/ttbar09/patTuple_all_15_ttbar09.root',
    '/store/user/rwolf/ttbar09/patTuple_all_16_ttbar09.root',
    '/store/user/rwolf/ttbar09/patTuple_all_17_ttbar09.root',
    '/store/user/rwolf/ttbar09/patTuple_all_18_ttbar09.root',
    '/store/user/rwolf/ttbar09/patTuple_all_19_ttbar09.root'
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
            fileName = cms.string('analyzeTriggerEfficiency_all.root')
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
        process.TFileService.fileName = 'analyzeTriggerEfficiency_sig.root'
    elif(eventFilter=='background only'):
        process.ttFullHadronicFilter.invert = True
        process.TFileService.fileName = 'analyzeTriggerEfficiency_bkg.root'
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

## jet kinematics analyzer
process.load("TopAnalysis.TopAnalyzer.JetKinematics_cfi")
## high level trigger filter
process.load("TopAnalysis.TopFilter.sequences.triggerFilter_cff")
## for the jet collections which should be used
process.load("TopAnalysis.TopFilter.sequences.jetSelection_cff")
## generator matching
process.load("TopAnalysis.TopFilter.sequences.generatorMatching_cff")

## replace sisCone5 by antikt5
if( useAntikt5 ):
    process.goodJets.src = 'selectedLayer1JetsAK5'

## define ordered jets
uds0    = cms.PSet(index = cms.int32(0), correctionLevel = cms.string('abs') )
uds1    = cms.PSet(index = cms.int32(1), correctionLevel = cms.string('abs') )
uds2    = cms.PSet(index = cms.int32(2), correctionLevel = cms.string('abs') )
uds3    = cms.PSet(index = cms.int32(3), correctionLevel = cms.string('abs') )
uds4    = cms.PSet(index = cms.int32(4), correctionLevel = cms.string('abs') )
uds5    = cms.PSet(index = cms.int32(5), correctionLevel = cms.string('abs') )
bottom0 = cms.PSet(index = cms.int32(0), correctionLevel = cms.string('abs') )
bottom1 = cms.PSet(index = cms.int32(1), correctionLevel = cms.string('abs') )

## Pre Trigger

## collect kinematics analyzers
process.tightBottomJetKinematics_0  = process.analyzeJetKinematics.clone (src = 'trackCountingHighPurBJets' )
process.tightLeadingJetKinematics_0 = process.analyzeJetKinematics.clone (src = 'goodJets')
process.tightLead_0_JetKinematics_0 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds0 )
process.tightLead_1_JetKinematics_0 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds1 )
process.tightLead_2_JetKinematics_0 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds2 )
process.tightLead_3_JetKinematics_0 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds3 )
process.tightLead_4_JetKinematics_0 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds4 )
process.tightLead_5_JetKinematics_0 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds5 )
process.tightBJet_0_JetKinematics_0 = process.analyzeJetKinematics.clone (src = 'trackCountingHighPurBJets' , analyze = bottom0)
process.tightBJet_1_JetKinematics_0 = process.analyzeJetKinematics.clone (src = 'trackCountingHighPurBJets' , analyze = bottom1)

## to be called with fullHadronicSelection
process.monitorJetsKinematics_0 = cms.Sequence(process.tightBottomJetKinematics_0  +
                                               process.tightBJet_0_JetKinematics_0 +
                                               process.tightBJet_1_JetKinematics_0 +
                                               process.tightLeadingJetKinematics_0 +
                                               process.tightLead_0_JetKinematics_0 +
                                               process.tightLead_1_JetKinematics_0 +
                                               process.tightLead_2_JetKinematics_0 +
                                               process.tightLead_3_JetKinematics_0 +
                                               process.tightLead_4_JetKinematics_0 +
                                               process.tightLead_5_JetKinematics_0  
                                               )

## After Monitor Trigger

## collect kinematics analyzers
process.tightBottomJetKinematics_1  = process.analyzeJetKinematics.clone (src = 'trackCountingHighPurBJets' )
process.tightLeadingJetKinematics_1 = process.analyzeJetKinematics.clone (src = 'goodJets')
process.tightLead_0_JetKinematics_1 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds0 )
process.tightLead_1_JetKinematics_1 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds1 )
process.tightLead_2_JetKinematics_1 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds2 )
process.tightLead_3_JetKinematics_1 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds3 )
process.tightLead_4_JetKinematics_1 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds4 )
process.tightLead_5_JetKinematics_1 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds5 )
process.tightBJet_0_JetKinematics_1 = process.analyzeJetKinematics.clone (src = 'trackCountingHighPurBJets' , analyze = bottom0)
process.tightBJet_1_JetKinematics_1 = process.analyzeJetKinematics.clone (src = 'trackCountingHighPurBJets' , analyze = bottom1)

## to be called with fullHadronicSelection
process.monitorJetsKinematics_1 = cms.Sequence(process.tightBottomJetKinematics_1  +
                                               process.tightBJet_0_JetKinematics_1 +
                                               process.tightBJet_1_JetKinematics_1 +
                                               process.tightLeadingJetKinematics_1 +
                                               process.tightLead_0_JetKinematics_1 +
                                               process.tightLead_1_JetKinematics_1 +
                                               process.tightLead_2_JetKinematics_1 +
                                               process.tightLead_3_JetKinematics_1 +
                                               process.tightLead_4_JetKinematics_1 +
                                               process.tightLead_5_JetKinematics_1  
                                               )

## After Trigger to test

## collect kinematics analyzers
process.tightBottomJetKinematics_2  = process.analyzeJetKinematics.clone (src = 'trackCountingHighPurBJets' )
process.tightLeadingJetKinematics_2 = process.analyzeJetKinematics.clone (src = 'goodJets')
process.tightLead_0_JetKinematics_2 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds0 )
process.tightLead_1_JetKinematics_2 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds1 )
process.tightLead_2_JetKinematics_2 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds2 )
process.tightLead_3_JetKinematics_2 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds3 )
process.tightLead_4_JetKinematics_2 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds4 )
process.tightLead_5_JetKinematics_2 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds5 )
process.tightBJet_0_JetKinematics_2 = process.analyzeJetKinematics.clone (src = 'trackCountingHighPurBJets' , analyze = bottom0)
process.tightBJet_1_JetKinematics_2 = process.analyzeJetKinematics.clone (src = 'trackCountingHighPurBJets' , analyze = bottom1)

## to be called with fullHadronicSelection
process.monitorJetsKinematics_2 = cms.Sequence(process.tightBottomJetKinematics_2  +
                                               process.tightBJet_0_JetKinematics_2 +
                                               process.tightBJet_1_JetKinematics_2 +
                                               process.tightLeadingJetKinematics_2 +
                                               process.tightLead_0_JetKinematics_2 +
                                               process.tightLead_1_JetKinematics_2 +
                                               process.tightLead_2_JetKinematics_2 +
                                               process.tightLead_3_JetKinematics_2 +
                                               process.tightLead_4_JetKinematics_2 +
                                               process.tightLead_5_JetKinematics_2  
                                               )



## ---
##    run the final sequence
## ---
process.p1 = cms.Path(## do the genEvent selection
                      process.filterSequence  *
                      ## create jet collections
                      process.goodJets *
                      process.trackCountingHighPurBJets *
                      ## do the monitoring (pre-trigger)
                      process.monitorJetsKinematics_0 *
                      ## do the hlt triggering (monitor)
                      process.hltHt200                *
                      ## do the monitoring (monitor-trigger)
                      process.monitorJetsKinematics_1 *
                      ## do the hlt triggering
                      process.hltQuadJet30            *
                      ## do the monitoring (post-trigger)
                      process.monitorJetsKinematics_2
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
