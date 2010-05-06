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

usePF       = False # False
writeOutput = False # True

# analyse muon quantities
process = cms.Process("SingleObjectTrigger")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('MC_3XY_V20::All')

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(    
    ## add your favourite file here
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_1.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_2.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_3.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_4.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_5.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_6.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_7.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_8.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_9.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_10.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_11.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_12.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_13.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_14.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_15.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_16.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_17.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_18.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_19.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_20.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_21.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_22.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_23.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_24.root'
    ),
    skipEvents = cms.untracked.uint32(9160)
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
            fileName = cms.string('analyzeSingleObjectTrigger_all.root')
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
        process.TFileService.fileName = 'analyzeSingleObjectTrigger_sig.root'
    elif(eventFilter=='background only'):
        process.ttFullHadronicFilter.invert = True
        process.TFileService.fileName = 'analyzeSingleObjectTrigger_bkg.root'
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
                                          process.filterPtHat
                                          )

## sequence with filter
process.patDefaultSequence = cms.Sequence(process.filterSequence
                                          )

## jet selection for analysis
from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import *
process.goodJets = selectedPatJets.clone(src = 'selectedLayer1Jets',
                                         cut = 'abs(eta) < 3.0 & pt > 20. &'
                                               '0.01 < emEnergyFraction   &'
                                               #'0.05 < emEnergyFraction   &'
                                               #'0.95 > emEnergyFraction   &'
                                               'jetID.n90Hits > 1 &'
                                               'jetID.fHPD < 0.98'
                                         )

process.simpleSecondaryVertexBJets = selectedPatJets.clone(src = 'goodJets',
                                                           cut = 'bDiscriminator(\"simpleSecondaryVertexBJetTags\") > 2.02'
                                                           )

## Output Module Configuration
if(writeOutput):
    process.out = cms.OutputModule("PoolOutputModule",
                                   fileName = cms.untracked.string('patTuple_trigger.root'),
                                   # save only events passing the full path
                                   SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p1') ),
                                   # save output (comment to keep everything...)
                                   outputCommands = cms.untracked.vstring('drop *',) 
                                   )
    process.outpath = cms.EndPath(process.out)

process.jetTriggerMatchHLTJets = cms.EDFilter( "PATTriggerMatcherDRLessByPt",
                                               #src     = cms.InputTag( "selectedLayer1Jets" ),
                                               src     = cms.InputTag( "goodJets" ),
                                               matched = cms.InputTag( "patTrigger" ),
                                               andOr          = cms.bool( False ),
                                               filterIdsEnum  = cms.vstring( 'TriggerJet' ),
                                               filterIds      = cms.vint32( 0 ),
                                               filterLabels   = cms.vstring( '*' ),
                                               pathNames      = cms.vstring( '*' ),
                                               #collectionTags = cms.vstring( '*' ),
                                               collectionTags = cms.vstring( 'hltMCJetCorJetIcone5::HLT' ),
                                               maxDPtRel = cms.double( 0.5 ),
                                               maxDeltaR = cms.double( 0.5 ),
                                               resolveAmbiguities    = cms.bool( True ),
                                               resolveByMatchQuality = cms.bool( True )
                                               #resolveByMatchQuality = cms.bool( False )
                                               )

#""" Enables trigger information in PAT  """
## add trigger modules to path
process.load("PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cff")
process.patDefaultSequence += process.patTriggerSequence

## configure pat trigger
process.patTrigger.onlyStandAlone = False

process.patTriggerEvent.patTriggerMatches = ['jetTriggerMatchHLTJets']

process.patTriggerMatcher += process.jetTriggerMatchHLTJets
#process.patTriggerMatcher += process.jetTriggerMatchL1Jets

process.patTriggerMatcher.remove( process.electronTriggerMatchHLTEle15LWL1R)
process.patTriggerMatcher.remove( process.electronTriggerMatchHLTDoubleEle5SWL1R)
process.patTriggerMatcher.remove( process.muonTriggerMatchL1Muon)
process.patTriggerMatcher.remove( process.muonTriggerMatchHLTIsoMu3)
process.patTriggerMatcher.remove( process.muonTriggerMatchHLTMu3)
process.patTriggerMatcher.remove( process.muonTriggerMatchHLTDoubleMu3)
process.patTriggerMatcher.remove( process.tauTriggerMatchHLTDoubleLooseIsoTau15)

## one might want to run the trigger not on clean, but on selected PAT objects
inputs = ['Electrons','Jets','Taus','Muons','Photons']
from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
for input in inputs:
    massSearchReplaceAnyInputTag(process.patTriggerSequence, 'cleanPat'+input, 'selectedLayer1'+input)
        
## jet kinematics analyzer
process.load("TopAnalysis.TopAnalyzer.JetKinematics_cfi")
## high level trigger filter
process.load("TopAnalysis.TopFilter.sequences.triggerFilter_cff")
process.load("TopAnalysis.TopFilter.filters.NewTriggerTestFilter_cfi")
## high level jet trigger analyzer
process.load("TopAnalysis.TopAnalyzer.SingleObjectJetTrigger_cfi")
## for the jet collections which should be used
#process.load("TopAnalysis.TopFilter.sequences.jetSelection_cff")
## generator matching
#process.load("TopAnalysis.TopFilter.sequences.generatorMatching_cff")

process.analyzeSingleObjectJetTrigger.jets = 'goodJets'
process.analyzeSingleObjectJetTrigger.width = 10.

## filter for full-hadronic 
process.load("TopQuarkAnalysis.TopEventProducers.producers.TtDecaySelection_cfi")
process.ttFullHadronicFilter = process.ttDecaySelection.clone()

## define new trigger to be used
process.hltQuadJet40 = process.filterTrigger.clone( whichTrigger = "QuadJet40" )

## define new trigger to be used
process.hltDiJet40 = process.filterTrigger.clone( whichTrigger = "DiJet40" )

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
process.tightBottomJetKinematics_0  = process.analyzeJetKinematics.clone (src = 'simpleSecondaryVertexBJets' )
process.tightLeadingJetKinematics_0 = process.analyzeJetKinematics.clone (src = 'goodJets')
process.tightLead_0_JetKinematics_0 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds0 )
process.tightLead_1_JetKinematics_0 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds1 )
process.tightLead_2_JetKinematics_0 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds2 )
process.tightLead_3_JetKinematics_0 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds3 )
process.tightLead_4_JetKinematics_0 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds4 )
process.tightLead_5_JetKinematics_0 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds5 )
process.tightBJet_0_JetKinematics_0 = process.analyzeJetKinematics.clone (src = 'simpleSecondaryVertexBJets' , analyze = bottom0)
process.tightBJet_1_JetKinematics_0 = process.analyzeJetKinematics.clone (src = 'simpleSecondaryVertexBJets' , analyze = bottom1)

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
process.tightBottomJetKinematics_1  = process.analyzeJetKinematics.clone (src = 'simpleSecondaryVertexBJets' )
process.tightLeadingJetKinematics_1 = process.analyzeJetKinematics.clone (src = 'goodJets')
process.tightLead_0_JetKinematics_1 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds0 )
process.tightLead_1_JetKinematics_1 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds1 )
process.tightLead_2_JetKinematics_1 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds2 )
process.tightLead_3_JetKinematics_1 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds3 )
process.tightLead_4_JetKinematics_1 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds4 )
process.tightLead_5_JetKinematics_1 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds5 )
process.tightBJet_0_JetKinematics_1 = process.analyzeJetKinematics.clone (src = 'simpleSecondaryVertexBJets' , analyze = bottom0)
process.tightBJet_1_JetKinematics_1 = process.analyzeJetKinematics.clone (src = 'simpleSecondaryVertexBJets' , analyze = bottom1)

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
process.tightBottomJetKinematics_2  = process.analyzeJetKinematics.clone (src = 'simpleSecondaryVertexBJets' )
process.tightLeadingJetKinematics_2 = process.analyzeJetKinematics.clone (src = 'goodJets')
process.tightLead_0_JetKinematics_2 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds0 )
process.tightLead_1_JetKinematics_2 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds1 )
process.tightLead_2_JetKinematics_2 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds2 )
process.tightLead_3_JetKinematics_2 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds3 )
process.tightLead_4_JetKinematics_2 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds4 )
process.tightLead_5_JetKinematics_2 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds5 )
process.tightBJet_0_JetKinematics_2 = process.analyzeJetKinematics.clone (src = 'simpleSecondaryVertexBJets' , analyze = bottom0)
process.tightBJet_1_JetKinematics_2 = process.analyzeJetKinematics.clone (src = 'simpleSecondaryVertexBJets' , analyze = bottom1)

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

## After Trigger to test

## collect kinematics analyzers
process.tightBottomJetKinematics_3  = process.analyzeJetKinematics.clone (src = 'simpleSecondaryVertexBJets' )
process.tightLeadingJetKinematics_3 = process.analyzeJetKinematics.clone (src = 'goodJets')
process.tightLead_0_JetKinematics_3 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds0 )
process.tightLead_1_JetKinematics_3 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds1 )
process.tightLead_2_JetKinematics_3 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds2 )
process.tightLead_3_JetKinematics_3 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds3 )
process.tightLead_4_JetKinematics_3 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds4 )
process.tightLead_5_JetKinematics_3 = process.analyzeJetKinematics.clone (src = 'goodJets', analyze = uds5 )
process.tightBJet_0_JetKinematics_3 = process.analyzeJetKinematics.clone (src = 'simpleSecondaryVertexBJets' , analyze = bottom0)
process.tightBJet_1_JetKinematics_3 = process.analyzeJetKinematics.clone (src = 'simpleSecondaryVertexBJets' , analyze = bottom1)

## to be called with fullHadronicSelection
process.monitorJetsKinematics_3 = cms.Sequence(process.tightBottomJetKinematics_3  +
                                               process.tightBJet_0_JetKinematics_3 +
                                               process.tightBJet_1_JetKinematics_3 +
                                               process.tightLeadingJetKinematics_3 +
                                               process.tightLead_0_JetKinematics_3 +
                                               process.tightLead_1_JetKinematics_3 +
                                               process.tightLead_2_JetKinematics_3 +
                                               process.tightLead_3_JetKinematics_3 +
                                               process.tightLead_4_JetKinematics_3 +
                                               process.tightLead_5_JetKinematics_3  
                                               )

## ---
##    run the final sequence: single object trigger monitoring
## ---
process.p1 = cms.Path(## do triggering
                      #process.hltMu9 *
                      #process.hltHt200 *
                      #process.hltQuadJet30 *
                      ## create jet collection for further investigation
                      process.goodJets *
                      ## do the genEvent filtering and trigger matching
                      process.patDefaultSequence *
                      ## analyze jet trigger
                      process.analyzeSingleObjectJetTrigger
                      )

## ---
##    run the final sequence: generator based trigger monitoring
## ---
process.p2 = cms.Path(## do the genEvent selection
                      process.filterSequence            *
                      ## create jet collections
                      process.goodJets                  *
                      process.simpleSecondaryVertexBJets*
                      ## do the monitoring (pre-trigger)
                      process.monitorJetsKinematics_0   *
                      ## do the hlt triggering (monitor)
                      process.hltQuadJet30              *
                      ## do the monitoring (monitor-trigger)
                      process.monitorJetsKinematics_1   *
                      ## do the hlt triggering
                      process.hltQuadJet40              *
                      ## do the monitoring (post-trigger)
                      process.monitorJetsKinematics_2
                      )

## ---
##    run the final sequence: generator based trigger monitoring
## ---
process.p3 = cms.Path(## do the genEvent selection
                      process.filterSequence            *
                      ## create jet collections
                      process.goodJets                  *
                      process.simpleSecondaryVertexBJets*
                      ## do the monitoring (pre-trigger)
                      process.monitorJetsKinematics_0   *
                      ## do the hlt triggering (monitor)
                      process.hltDiJet40                *
                      ## do the monitoring (monitor-trigger)
                      process.monitorJetsKinematics_3
                      )



## replace antikt5 calojets bei antikt5 particleflow jets
## not jet working because goodJets still have to be calo jets
if( usePF ):
    print "######################################"
    print "## Using PFJets instead of CaloJets ##"
    print "######################################"
    print "##   Switching to an appropriate    ##"
    print "##  jet collection for PF as input  ##"
    print "######################################"
    from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
    massSearchReplaceAnyInputTag(process.p1, 'selectedLayer1Jets', 'selectedLayer1JetsPF')

    #process.reliableJets.src = 'selectedLayer1JetsPF'

