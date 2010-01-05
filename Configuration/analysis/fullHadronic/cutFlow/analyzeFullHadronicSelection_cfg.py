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
##process.MessageLogger.categories.append('TtFullHadronicEvent')
##process.MessageLogger.categories.append('TtFullHadKinFitter')
##process.MessageLogger.categories.append('KinFitter')
##process.MessageLogger.cerr.TtFullHadronicEvent = cms.untracked.PSet(
##    limit = cms.untracked.int32(-1)
##)
##process.MessageLogger.cerr.TtFullHadKinFitter = cms.untracked.PSet(
##    limit = cms.untracked.int32(-1)
##)
##process.MessageLogger.cerr.KinFitter = cms.untracked.PSet(
##    limit = cms.untracked.int32(-1)
##)

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

## filter event shape
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

## ---
##    configure the cutflow scenario
## ---

## jet quality analyzer
process.load("TopAnalysis.TopAnalyzer.JetQuality_cfi")
## muon quality analyzer
process.load("TopAnalysis.TopAnalyzer.MuonQuality_cfi")
## jet kinematics analyzer
process.load("TopAnalysis.TopAnalyzer.JetKinematics_cfi")
## muon kinematics analyzer
process.load("TopAnalysis.TopAnalyzer.MuonKinematics_cfi")
## event shape analyzer
process.load("TopAnalysis.TopAnalyzer.EventShapes_cfi")
## analyzer for special variables in full hadronic channel
process.load("TopAnalysis.TopAnalyzer.FullHadSpecial_cfi")
## analyzer for fully hadronic event reco
process.load("TopAnalysis.TopAnalyzer.FullHadTopReco_cfi")
## high level trigger filter
process.load("TopAnalysis.TopFilter.sequences.triggerFilter_cff")
## semileptonic selection
process.load("TopAnalysis.TopFilter.sequences.fullHadronicSelection_cff")
## generator matching
process.load("TopAnalysis.TopFilter.sequences.generatorMatching_cff")

## kinfit
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttFullHadEvtBuilder_cff")
process.load("TopAnalysis.TopAnalyzer.KinFitQuality_cfi")

from TopQuarkAnalysis.TopEventProducers.sequences.ttFullHadEvtBuilder_cff import addTtFullHadHypotheses
addTtFullHadHypotheses(process,
                       ["kKinFit"]
                       )

process.kinFitTtFullHadEventHypothesis.jets = 'tightLeadingJets'
process.kinFitTtFullHadEventHypothesis.maxNComb = -1

from TopQuarkAnalysis.TopEventProducers.sequences.ttFullHadEvtBuilder_cff import removeTtFullHadHypGenMatch
removeTtFullHadHypGenMatch(process)

process.load("TopAnalysis.TopAnalyzer.FullHadHypothesisAnalyzer_cff")


## define ordered jets
uds0    = cms.PSet(index = cms.int32(0), correctionLevel = cms.string('abs')   )
uds1    = cms.PSet(index = cms.int32(1), correctionLevel = cms.string('abs')   )
uds2    = cms.PSet(index = cms.int32(2), correctionLevel = cms.string('abs')   )
uds3    = cms.PSet(index = cms.int32(3), correctionLevel = cms.string('abs')   )
uds4    = cms.PSet(index = cms.int32(4), correctionLevel = cms.string('abs')   )
uds5    = cms.PSet(index = cms.int32(5), correctionLevel = cms.string('abs')   )
bottom0 = cms.PSet(index = cms.int32(0), correctionLevel = cms.string('had:b') )
bottom1 = cms.PSet(index = cms.int32(1), correctionLevel = cms.string('had:b') )

## replace sisCone5 by antikt5
if( useAntikt5 ):
    process.goodJets.src = 'selectedLayer1Jets'
    
## MONITOR STEP 0

## JET KINEMATICS

## collect kinematics analyzers
process.tightBottomJetKinematics_0  = process.analyzeJetKinematics.clone (src = 'tightBottomJets' )
process.tightLeadingJetKinematics_0 = process.analyzeJetKinematics.clone (src = 'tightLeadingJets')
process.tightLead_0_JetKinematics_0 = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds0 )
process.tightLead_1_JetKinematics_0 = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds1 )
process.tightLead_2_JetKinematics_0 = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds2 )
process.tightLead_3_JetKinematics_0 = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds3 )
process.tightLead_4_JetKinematics_0 = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds4 )
process.tightLead_5_JetKinematics_0 = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds5 )
process.tightBJet_0_JetKinematics_0 = process.analyzeJetKinematics.clone (src = 'tightBottomJets' , analyze = bottom0)
process.tightBJet_1_JetKinematics_0 = process.analyzeJetKinematics.clone (src = 'tightBottomJets' , analyze = bottom1)

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

## EVENT SHAPES

## collect event shape analyzers
process.eventShapes_0 = process.analyzeEventShapes.clone( src = 'tightLeadingJets' )

## monitor sequence for event shape analyzers
process.monitorEventShapes_0 = cms.Sequence(process.eventShapes_0
                                            )

## FULL HAD SPECIAL

## collect analyzers specially for full hadronic analysis
process.fullHadSpecial_0 = process.analyzeFullHadSpecials.clone( src = 'tightLeadingJets' )

## monitor sequence for specially for full hadronic analyzers
process.monitorFullHadSpecials_0 = cms.Sequence(process.fullHadSpecial_0
                                                )



## FILTER STEP 1 (To be found in process.load("TopAnalysis.TopFilter.sequences.fullHadronicSelection_cff") as  process.fullHadronicEvents)

## MONITOR STEP 1

## JET KINEMATICS

## collect kinematics analyzers
process.tightBottomJetKinematics_1  = process.analyzeJetKinematics.clone (src = 'tightBottomJets' )
process.tightLeadingJetKinematics_1 = process.analyzeJetKinematics.clone (src = 'tightLeadingJets')
process.tightLead_0_JetKinematics_1 = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds0 )
process.tightLead_1_JetKinematics_1 = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds1 )
process.tightLead_2_JetKinematics_1 = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds2 )
process.tightLead_3_JetKinematics_1 = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds3 )
process.tightLead_4_JetKinematics_1 = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds4 )
process.tightLead_5_JetKinematics_1 = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds5 )
process.tightBJet_0_JetKinematics_1 = process.analyzeJetKinematics.clone (src = 'tightBottomJets' , analyze = bottom0)
process.tightBJet_1_JetKinematics_1 = process.analyzeJetKinematics.clone (src = 'tightBottomJets' , analyze = bottom1)

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

## EVENT SHAPES

## collect event shape analyzers
process.eventShapes_1 = process.analyzeEventShapes.clone( src = 'tightLeadingJets' )

## monitor sequence for event shape analyzers
process.monitorEventShapes_1 = cms.Sequence(process.eventShapes_1
                                            )

## FULL HAD SPECIAL

## collect analyzers specially for full hadronic analysis
process.fullHadSpecial_1 = process.analyzeFullHadSpecials.clone( src = 'tightLeadingJets' )

## monitor sequence for specially for full hadronic analyzers
process.monitorFullHadSpecials_1 = cms.Sequence(process.fullHadSpecial_1
                                                )

## KINFIT QUALITY

## kinfit quality analyzer
## collect kinfit quality analyzers
process.kinFitQuality_1 = process.analyzeKinFitQuality.clone( srcB = 'tightLeadingJets' )

## monitor sequence for kinfit quality analyzers
process.monitorKinFitQuality_1 = cms.Sequence(process.kinFitQuality_1
                                              )

## FULL HAD TOP RECO

## collect fully hadronic top reco analyzers
process.fullHadTopReco_1 = process.analyzeFullHadTopReco.clone( srcB = 'tightLeadingJets' )

## monitor sequence for fully hadronice top reco analyzers
process.monitorfullHadTopReco_1 = cms.Sequence(process.fullHadTopReco_1
                                               )

## FILTER STEP 2

## kinfit quality filter
process.load("TopAnalysis.TopFilter.filters.KinFitQualityFilter_cfi")

## filter kinfit quality
process.filterKinFitQuality = process.filterKinFitQuality.clone( minProb = 0.15 )

## MONITOR STEP 2

## JET KINEMATICS

## collect kinematics analyzers
process.tightBottomJetKinematics_2  = process.analyzeJetKinematics.clone (src = 'tightBottomJets' )
process.tightLeadingJetKinematics_2 = process.analyzeJetKinematics.clone (src = 'tightLeadingJets')
process.tightLead_0_JetKinematics_2 = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds0 )
process.tightLead_1_JetKinematics_2 = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds1 )
process.tightLead_2_JetKinematics_2 = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds2 )
process.tightLead_3_JetKinematics_2 = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds3 )
process.tightLead_4_JetKinematics_2 = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds4 )
process.tightLead_5_JetKinematics_2 = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds5 )
process.tightBJet_0_JetKinematics_2 = process.analyzeJetKinematics.clone (src = 'tightBottomJets' , analyze = bottom0)
process.tightBJet_1_JetKinematics_2 = process.analyzeJetKinematics.clone (src = 'tightBottomJets' , analyze = bottom1)

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

## EVENT SHAPES

## collect event shape analyzers
process.eventShapes_2 = process.analyzeEventShapes.clone( src = 'tightLeadingJets' )

## monitor sequence for event shape analyzers
process.monitorEventShapes_2 = cms.Sequence(process.eventShapes_2
                                            )

## KINFIT QUALITY

## kinfit quality analyzer
## collect kinfit quality analyzers
process.kinFitQuality_2 = process.analyzeKinFitQuality.clone( srcB = 'tightLeadingJets' )

## monitor sequence for kinfit quality analyzers
process.monitorKinFitQuality_2 = cms.Sequence(process.kinFitQuality_2
                                              )

## FULL HAD TOP RECO

## collect fully hadronic top reco analyzers
process.fullHadTopReco_2 = process.analyzeFullHadTopReco.clone( srcB = 'tightLeadingJets' )

## monitor sequence for fully hadronice top reco analyzers
process.monitorfullHadTopReco_2 = cms.Sequence(process.fullHadTopReco_2
                                               )

## FULL HAD SPECIAL

## collect analyzers specially for full hadronic analysis
process.fullHadSpecial_2 = process.analyzeFullHadSpecials.clone( src = 'tightLeadingJets' )

## monitor sequence for specially for full hadronic analyzers
process.monitorFullHadSpecials_2 = cms.Sequence(process.fullHadSpecial_2
                                                )

## FILTER STEP 3

## event shape filter
process.load("TopAnalysis.TopFilter.filters.EventShapeFilter_cfi")

## filter event shape
process.filterEventShapes = process.filterEventShape.clone (minC = 0.75)

## MONITOR STEP 3

## To be added in time


## ---
##    run the final sequence
## ---
process.p1 = cms.Path(## do the gen evetn selection
                      process.filterSequence        *
                      ## do the selections
                      process.fullHadronicSelection *
                      ## do the matching
                      process.matchJetsToPartons    *
                      ## do the monitoring
                      #process.monitorJetsQuality      *
                      process.monitorJetsKinematics_0 *
                      process.monitorEventShapes_0    *
                      process.monitorFullHadSpecials_0*
                      ## do the 1. event selection
                      process.fullHadronicEvents      *
                      process.monitorJetsKinematics_1 *
                      process.monitorEventShapes_1    *
                      process.makeTtFullHadEvent      *
                      process.monitorKinFitQuality_1  *
                      process.monitorFullHadSpecials_1*
                      process.monitorfullHadTopReco_1 *
                      ## do the 2. event selection
                      process.filterKinFitQuality     *
                      process.monitorJetsKinematics_2 *
                      process.monitorEventShapes_2    *
                      process.monitorKinFitQuality_2  *
                      process.monitorFullHadSpecials_2*
                      process.monitorfullHadTopReco_2 
                      #process.filterEventShapes
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
