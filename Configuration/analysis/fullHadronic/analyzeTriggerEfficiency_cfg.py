import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing

## ---
##    here we need a general description of what the config id good for and the
##    switches mean. This should be in analogy of the Doxygen commentsin the
##    modules...
## ---

# setup 'standard' options
options = VarParsing.VarParsing ('standard')
## decide whether to run on:  * data *, * signal only (sig) *, * background only (bkg) *, * qcd * or * all *
options.register('eventFilter', 'data', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "kind of data to be processed")
## choose whether to use PF or not
options.register('usePF'      , 1 , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "use PF for processing")
## choose whether to write output to disk or not
options.register('writeOutput', 0 , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "write events surviving all cuts to disk")
## setup the ptHatFilter in case 'eventFilter' is chosen to be qcd
options.register('maxPtHat', 999999., VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.float, "maxPtHat to be processed")
options.register('minPtHat', 0.     , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.float, "minPtHat to be processed")

# get and parse the command line arguments
options.parseArguments()

# analyse muon quantities
process = cms.Process("TriggerEfficiency")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 10000


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

## residual jet corrector for data
process.load("TopAnalysis.TopUtils.ResidualJetCorrector_cfi")
process.residualCorrectedJets = process.residualCorrectedJets.clone()

if(options.eventFilter=='data'):
    ## sequence with jet energy corrections specially suited for data
    process.filterSequence = cms.Sequence(#process.patDefaultSequence *
                                          process.residualCorrectedJets
                                          )
    
elif(options.eventFilter=='sig'):
    ## sequence with fullHad ttbar filter
    process.filterSequence = cms.Sequence(#process.patDefaultSequence *
                                          process.makeGenEvt *
                                          process.ttFullHadronicFilter
                                          )

elif(options.eventFilter=='bkg'):
    ## invert fullHad filter
    process.ttFullHadronicFilter.invert = True
    ## sequence with non-fullHad ttbar filter
    process.filterSequence = cms.Sequence(#process.patDefaultSequence *
                                          process.makeGenEvt *
                                          process.ttFullHadronicFilter
                                          )

elif(options.eventFilter=='qcd' or options.eventFilter=='priv'):
    if(options.maxPtHat<999999.):
        ## ptHat filter
        process.filterPtHat.maxPtHat = options.maxPtHat
        print "included ptHatFilter with 'maxPtHat' =",
        print process.filterPtHat.maxPtHat

    if(options.minPtHat>0.):
        process.filterPtHat.minPtHat = options.minPtHat
        print "included ptHatFilter with 'minPtHat' =",
        print process.filterPtHat.minPtHat

    ## deactivate duplicate check for private samples
    ## as event numbers are used multiple times in there
    if(options.eventFilter=='priv'):
        process.source.duplicateCheckMode = cms.untracked.string("noDuplicateCheck")

    ## sequence with ptHat filter
    process.filterSequence = cms.Sequence(#process.patDefaultSequence *
                                          process.filterPtHat)

elif(options.eventFilter=='all'):
    process.filterSequence = cms.Sequence(#process.patDefaultSequence *
                                          process.filterPtHat)
    
else:
    raise NameError, "'"+options.eventFilter+"' is not a prober eventFilter name choose: 'data', 'sig', 'bkg', 'qcd' or 'all'"

## adapt output filename
process.TFileService.fileName = 'analyzeFullHadronicSelection_'+options.eventFilter+'.root'

## jet kinematics analyzer
process.load("TopAnalysis.TopAnalyzer.JetKinematics_cfi")
## high level trigger filter
process.load("TopAnalysis.TopFilter.sequences.triggerFilter_cff")
## for the jet collections which should be used
process.load("TopAnalysis.TopFilter.sequences.jetSelection_cff")
## generator matching
process.load("TopAnalysis.TopFilter.sequences.generatorMatching_cff")

## add jet collection to prerequists
process.filterSequence *= process.goodJets

## define ordered jets
uds0    = cms.PSet(index = cms.int32(0), correctionLevel = cms.string('abs') )
uds1    = cms.PSet(index = cms.int32(1), correctionLevel = cms.string('abs') )
uds2    = cms.PSet(index = cms.int32(2), correctionLevel = cms.string('abs') )
uds3    = cms.PSet(index = cms.int32(3), correctionLevel = cms.string('abs') )
uds4    = cms.PSet(index = cms.int32(4), correctionLevel = cms.string('abs') )
uds5    = cms.PSet(index = cms.int32(5), correctionLevel = cms.string('abs') )

## pre-triggered

## collect kinematics analyzers
process.tightLeadingJetKinematics_0 = process.analyzeJetKinematics.clone (src = 'goodJets')
process.tightLead_0_JetKinematics_0 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds0 )
process.tightLead_1_JetKinematics_0 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds1 )
process.tightLead_2_JetKinematics_0 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds2 )
process.tightLead_3_JetKinematics_0 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds3 )
process.tightLead_4_JetKinematics_0 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds4 )
process.tightLead_5_JetKinematics_0 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds5 )

## to be called with fullHadronicSelection
process.monitorJetsKinematics_0 = cms.Sequence(process.tightLeadingJetKinematics_0 *
                                               process.tightLead_0_JetKinematics_0 *
                                               process.tightLead_1_JetKinematics_0 *
                                               process.tightLead_2_JetKinematics_0 *
                                               process.tightLead_3_JetKinematics_0 *
                                               process.tightLead_4_JetKinematics_0 *
                                               process.tightLead_5_JetKinematics_0  
                                               )

## QuadJet15U triggered

## collect kinematics analyzers
process.tightLeadingJetKinematics_QJ15U = process.analyzeJetKinematics.clone (src = 'goodJets')
process.tightLead_0_JetKinematics_QJ15U = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds0 )
process.tightLead_1_JetKinematics_QJ15U = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds1 )
process.tightLead_2_JetKinematics_QJ15U = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds2 )
process.tightLead_3_JetKinematics_QJ15U = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds3 )
process.tightLead_4_JetKinematics_QJ15U = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds4 )
process.tightLead_5_JetKinematics_QJ15U = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds5 )

## to be called with fullHadronicSelection
process.monitorJetsKinematics_QJ15U = cms.Sequence(process.tightLeadingJetKinematics_QJ15U *
                                                   process.tightLead_0_JetKinematics_QJ15U *
                                                   process.tightLead_1_JetKinematics_QJ15U *
                                                   process.tightLead_2_JetKinematics_QJ15U *
                                                   process.tightLead_3_JetKinematics_QJ15U *
                                                   process.tightLead_4_JetKinematics_QJ15U *
                                                   process.tightLead_5_JetKinematics_QJ15U  
                                                   )

## Jet50U triggered

## collect kinematics analyzers
process.tightLeadingJetKinematics_J50U = process.analyzeJetKinematics.clone (src = 'goodJets')
process.tightLead_0_JetKinematics_J50U = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds0 )
process.tightLead_1_JetKinematics_J50U = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds1 )
process.tightLead_2_JetKinematics_J50U = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds2 )
process.tightLead_3_JetKinematics_J50U = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds3 )
process.tightLead_4_JetKinematics_J50U = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds4 )
process.tightLead_5_JetKinematics_J50U = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds5 )

## to be called with fullHadronicSelection
process.monitorJetsKinematics_J50U = cms.Sequence(process.tightLeadingJetKinematics_J50U *
                                                  process.tightLead_0_JetKinematics_J50U *
                                                  process.tightLead_1_JetKinematics_J50U *
                                                  process.tightLead_2_JetKinematics_J50U *
                                                  process.tightLead_3_JetKinematics_J50U *
                                                  process.tightLead_4_JetKinematics_J50U *
                                                  process.tightLead_5_JetKinematics_J50U  
                                                  )

## Jet50U -> QuadJet15U triggered

## collect kinematics analyzers
process.tightLeadingJetKinematics_J50U_QJ15U = process.analyzeJetKinematics.clone (src = 'goodJets')
process.tightLead_0_JetKinematics_J50U_QJ15U = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds0 )
process.tightLead_1_JetKinematics_J50U_QJ15U = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds1 )
process.tightLead_2_JetKinematics_J50U_QJ15U = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds2 )
process.tightLead_3_JetKinematics_J50U_QJ15U = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds3 )
process.tightLead_4_JetKinematics_J50U_QJ15U = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds4 )
process.tightLead_5_JetKinematics_J50U_QJ15U = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds5 )

## to be called with fullHadronicSelection
process.monitorJetsKinematics_J50U_QJ15U = cms.Sequence(process.tightLeadingJetKinematics_J50U_QJ15U *
                                                        process.tightLead_0_JetKinematics_J50U_QJ15U *
                                                        process.tightLead_1_JetKinematics_J50U_QJ15U *
                                                        process.tightLead_2_JetKinematics_J50U_QJ15U *
                                                        process.tightLead_3_JetKinematics_J50U_QJ15U *
                                                        process.tightLead_4_JetKinematics_J50U_QJ15U *
                                                        process.tightLead_5_JetKinematics_J50U_QJ15U  
                                                        )

## Mu9 triggered

## collect kinematics analyzers
process.tightLeadingJetKinematics_Mu9 = process.analyzeJetKinematics.clone (src = 'goodJets')
process.tightLead_0_JetKinematics_Mu9 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds0 )
process.tightLead_1_JetKinematics_Mu9 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds1 )
process.tightLead_2_JetKinematics_Mu9 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds2 )
process.tightLead_3_JetKinematics_Mu9 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds3 )
process.tightLead_4_JetKinematics_Mu9 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds4 )
process.tightLead_5_JetKinematics_Mu9 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds5 )

## to be called with fullHadronicSelection
process.monitorJetsKinematics_Mu9 = cms.Sequence(process.tightLeadingJetKinematics_Mu9 *
                                                 process.tightLead_0_JetKinematics_Mu9 *
                                                 process.tightLead_1_JetKinematics_Mu9 *
                                                 process.tightLead_2_JetKinematics_Mu9 *
                                                 process.tightLead_3_JetKinematics_Mu9 *
                                                 process.tightLead_4_JetKinematics_Mu9 *
                                                 process.tightLead_5_JetKinematics_Mu9  
                                                 )

## Mu9 -> QuadJet15U triggered

## collect kinematics analyzers
process.tightLeadingJetKinematics_Mu9_QJ15U = process.analyzeJetKinematics.clone (src = 'goodJets')
process.tightLead_0_JetKinematics_Mu9_QJ15U = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds0 )
process.tightLead_1_JetKinematics_Mu9_QJ15U = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds1 )
process.tightLead_2_JetKinematics_Mu9_QJ15U = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds2 )
process.tightLead_3_JetKinematics_Mu9_QJ15U = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds3 )
process.tightLead_4_JetKinematics_Mu9_QJ15U = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds4 )
process.tightLead_5_JetKinematics_Mu9_QJ15U = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds5 )

## to be called with fullHadronicSelection
process.monitorJetsKinematics_Mu9_QJ15U = cms.Sequence(process.tightLeadingJetKinematics_Mu9_QJ15U *
                                                       process.tightLead_0_JetKinematics_Mu9_QJ15U *
                                                       process.tightLead_1_JetKinematics_Mu9_QJ15U *
                                                       process.tightLead_2_JetKinematics_Mu9_QJ15U *
                                                       process.tightLead_3_JetKinematics_Mu9_QJ15U *
                                                       process.tightLead_4_JetKinematics_Mu9_QJ15U *
                                                       process.tightLead_5_JetKinematics_Mu9_QJ15U  
                                                       )

## create trigger selection for MC
process.hltQuadJet15U = process.hltQuadJet30.clone( HLTPaths = ["HLT_QuadJet15U"], TriggerResultsTag = cms.InputTag("TriggerResults","","REDIGI") )
process.hltJet50U     = process.hltQuadJet30.clone( HLTPaths = ["HLT_Jet50U"],     TriggerResultsTag = cms.InputTag("TriggerResults","","REDIGI") )
process.hltMu9        = process.hltQuadJet30.clone( HLTPaths = ["HLT_Mu9"],        TriggerResultsTag = cms.InputTag("TriggerResults","","REDIGI") )

## ---
##    run the final sequence
## ---
process.QJ15U = cms.Path(## do the genEvent selection
                         process.filterSequence *
                         ## do the pre trigger monitoring
                         process.monitorJetsKinematics_0 *
                         ## do QuadJet15U triggering
                         process.hltQuadJet15U *
                         ## do the monitoring QuadJet15U
                         process.monitorJetsKinematics_QJ15U
                         )

process.J50U_QJ15U = cms.Path(## do the genEvent selection
                              process.filterSequence *
                              ## do Jet50U triggering
                              process.hltJet50U *
                              ## do the monitoring Jet50U
                              process.monitorJetsKinematics_J50U *
                              ## do QuadJet15U triggering
                              process.hltQuadJet15U *
                              ## do the monitoring QuadJet15U
                              process.monitorJetsKinematics_J50U_QJ15U
                              )

process.Mu9_QJ15U = cms.Path(## do the genEvent selection
                             process.filterSequence *
                             ## do Mu9 triggering
                              process.hltMu9 *
                              ## do the monitoring Mu9
                              process.monitorJetsKinematics_Mu9 *
                              ## do QuadJet15U triggering
                              process.hltQuadJet15U *
                              ## do the monitoring QuadJet15U
                              process.monitorJetsKinematics_Mu9_QJ15U
                              )

if(not options.usePF==0):
    process.filterSequence.replace(process.goodJets, process.goodJetsPF)
    from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
    massSearchReplaceAnyInputTag(process.QJ15U     , 'goodJets', 'goodJetsPF')
    massSearchReplaceAnyInputTag(process.J50U_QJ15U, 'goodJets', 'goodJetsPF')
    massSearchReplaceAnyInputTag(process.Mu9_QJ15U , 'goodJets', 'goodJetsPF')
    if(hasattr(process, 'residualCorrectedJets')):
        process.residualCorrectedJets.jets    = 'selectedPatJetsAK5PF'
        process.residualCorrectedJets.jetType = 'PF'

if(options.eventFilter=='data'):
    process.QJ15U.remove(process.monitorJetsKinematics_0)
    from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
    massSearchReplaceAnyInputTag(process.QJ15U     , cms.InputTag("TriggerResults","","REDIGI"), cms.InputTag("TriggerResults","","HLT"))
    massSearchReplaceAnyInputTag(process.J50U_QJ15U, cms.InputTag("TriggerResults","","REDIGI"), cms.InputTag("TriggerResults","","HLT"))
    massSearchReplaceAnyInputTag(process.Mu9_QJ15U , cms.InputTag("TriggerResults","","REDIGI"), cms.InputTag("TriggerResults","","HLT"))


## Output Module Configuration
if(not options.writeOutput==0):
    process.out = cms.OutputModule("PoolOutputModule",
                                   fileName = cms.untracked.string('patTuple_selected.root'),
                                   # save only events passing the full path
                                   SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p1') ),
                                   # drop meta data for dropped events
                                   dropMetaData = cms.untracked.string('DROPPED'),
                                   # save output (comment to keep everything...)
                                   #outputCommands = cms.untracked.vstring('drop *',) 
                                   )
    process.outpath = cms.EndPath(process.out)
