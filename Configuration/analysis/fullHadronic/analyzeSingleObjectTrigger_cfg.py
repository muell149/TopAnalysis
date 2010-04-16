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
    process.patDefaultSequence = cms.Sequence(#process.patDefaultSequence *
                                              process.makeGenEvt *
                                              process.ttFullHadronicFilter
                                              )
else:
    ## sequence without filter
    process.patDefaultSequence = cms.Sequence(#process.patDefaultSequence *
                                              process.filterPtHat
                                              )

## jet selection for analysis
from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import *
process.goodJets = selectedPatJets.clone(src = 'selectedLayer1Jets',
                                         cut = 'abs(eta) < 3.0 & pt > 20. &'
                                               '0.05 < emEnergyFraction   & '
                                               '0.95 > emEnergyFraction'
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
                                               resolveByMatchQuality = cms.bool( False )
                                               )

#process.jetTriggerMatchL1Jets = cms.EDFilter( "PATTriggerMatcherDRLessByPt",
#                                              #src     = cms.InputTag( "selectedLayer1Jets" ),
#                                              src     = cms.InputTag( "goodJets" ),
#                                              matched = cms.InputTag( "patTrigger" ),
#                                              andOr          = cms.bool( False ),
#                                              filterIdsEnum  = cms.vstring( 'TriggerL1CenJet','TriggerL1ForJet','TriggerL1JetCounts' ),
#                                              filterIds      = cms.vint32( 0 ),
#                                              filterLabels   = cms.vstring( '*' ),
#                                              pathNames      = cms.vstring( '*' ),
#                                              collectionTags = cms.vstring( '*' ),
#                                              maxDPtRel = cms.double( 0.5 ),
#                                              maxDeltaR = cms.double( 0.5 ),
#                                              resolveAmbiguities    = cms.bool( True ),
#                                              resolveByMatchQuality = cms.bool( False )
#                                              )

#""" Enables trigger information in PAT  """
## add trigger modules to path
process.load("PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cff")
process.patDefaultSequence += process.patTriggerSequence

## configure pat trigger
process.patTrigger.onlyStandAlone = False

process.patTriggerEvent.patTriggerMatches = ['jetTriggerMatchHLTJets']#,'jetTriggerMatchL1Jets']

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
#process.load("TopAnalysis.TopAnalyzer.JetKinematics_cfi")
## high level trigger filter
process.load("TopAnalysis.TopFilter.sequences.triggerFilter_cff")
## high level jet trigger analyzer
process.load("TopAnalysis.TopAnalyzer.SingleObjectJetTrigger_cfi")
## for the jet collections which should be used
#process.load("TopAnalysis.TopFilter.sequences.jetSelection_cff")
## generator matching
#process.load("TopAnalysis.TopFilter.sequences.generatorMatching_cff")

process.analyzeSingleObjectJetTrigger.jets = 'goodJets'

## ---
##    run the final sequence
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

