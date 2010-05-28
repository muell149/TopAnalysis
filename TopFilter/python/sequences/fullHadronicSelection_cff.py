import FWCore.ParameterSet.Config as cms

## configure geometry & conditions
#from Configuration.StandardSequences.Geometry_cff import *
#from Configuration.StandardSequences.MagneticField_cff import *
#from Configuration.StandardSequences.FrontierConditions_GlobalTag_cff import *
#GlobalTag.globaltag = cms.string('MC_31X_V9::All')

## std sequence for pat
#from PhysicsTools.PatAlgos.patSequences_cff import *

## all leptons kept for possible rejection of events later on (not yet implemented)

## jet selector
from TopAnalysis.TopFilter.sequences.jetSelection_cff import *
## muon selector
#from TopAnalysis.TopFilter.sequences.muonSelection_cff import *

## jet selector
from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import *
## muon selector
#from PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi import *
## electron selector
#from PhysicsTools.PatAlgos.selectionLayer1.electronSelector_cfi import *

## jet count filter
from PhysicsTools.PatAlgos.selectionLayer1.jetCountFilter_cfi import *
## muon count filter
#from PhysicsTools.PatAlgos.selectionLayer1.muonCountFilter_cfi import *
## electron count filter
#from PhysicsTools.PatAlgos.selectionLayer1.electronCountFilter_cfi import *


## ---
##    setup the collections for the fully-hadronic event selection
## ---

## setup the jet selection collection
tightLeadingJets = selectedPatJets.clone(src = 'goodJets',
                                         cut = 'abs(eta) < 2.4 & pt > 40'
                                         )
tightBottomJets  = selectedPatJets.clone(src = 'simpleSecondaryVertexBJets',
                                         cut = 'abs(eta) < 2.4 & pt > 50'
                                         )

## setting up the collections for the fully-hadronic
## event selection; on these collection monitoring
## can still be performed
fullHadronicSelection = cms.Sequence(goodJets *
                                     simpleSecondaryVertexBJets *
                                     tightLeadingJets *
                                     tightBottomJets
                                     )

## ---
##    setup the fully-hadronic event selection
## ---

## setup jet selection collection
leadingJetSelection = countPatJets.clone(src = 'tightLeadingJets',
                                         minNumber = 6
                                         )
bottomJetSelection  = countPatJets.clone(src = 'tightBottomJets',
                                         minNumber = 2
                                         )

## setting up the fully-hadronic event selection;
## on these collection monitoring can still be
## performed
fullHadronicEvents = cms.Sequence(leadingJetSelection *
                                  bottomJetSelection
                                  )

## ---
##    provide a function to disable parts of the selection
## ---
def disableCountFilter(whichCountFilter):
    whichCountFilter.minNumber = 0
    whichCountFilter.maxNumber = 999999

## ---
##    configure the cutflow scenario
## ---

## jet quality analyzer
from TopAnalysis.TopAnalyzer.JetQuality_cfi import *
## muon quality analyzer
from TopAnalysis.TopAnalyzer.MuonQuality_cfi import *
## jet kinematics analyzer
from TopAnalysis.TopAnalyzer.JetKinematics_cfi import *
## muon kinematics analyzer
from TopAnalysis.TopAnalyzer.MuonKinematics_cfi import *
## event shape analyzer
from TopAnalysis.TopAnalyzer.EventShapes_cfi import *
## genParticle analyzer
from TopAnalysis.TopAnalyzer.GenParticle_cfi import *
## analyzer for special variables in full hadronic channel
from TopAnalysis.TopAnalyzer.FullHadSpecial_cfi import *
## analyzer for fully hadronic event reco
from TopAnalysis.TopAnalyzer.FullHadTopReco_cfi import *
## high level trigger filter
from TopAnalysis.TopFilter.sequences.triggerFilter_cff import *
## semileptonic selection
from TopAnalysis.TopFilter.sequences.fullHadronicSelection_cff import *
## generator matching
from TopAnalysis.TopFilter.sequences.generatorMatching_cff import *
## kinFit producer
from TopQuarkAnalysis.TopEventProducers.sequences.ttFullHadEvtBuilder_cff import *

#ttFullHadEvent.verbosity = 1

## configuration of kinematic fit
kinFitTtFullHadEventHypothesis.jets = 'tightLeadingJets'
kinFitTtFullHadEventHypothesis.maxNComb = -1
kinFitTtFullHadEventHypothesis.bTags = 2
kinFitTtFullHadEventHypothesis.bTagAlgo = 'simpleSecondaryVertexBJetTags'
kinFitTtFullHadEventHypothesis.minBTagValueBJet = 2.02
kinFitTtFullHadEventHypothesis.maxBTagValueNonBJet = 3.4
kinFitTtFullHadEventHypothesis.jetCorrectionLevel = 'had'

## kinfit analyzer
from TopAnalysis.TopAnalyzer.KinFitQuality_cfi import *

#bottomJetSelection.minNumber = 1

from TopAnalysis.TopAnalyzer.FullHadHypothesisAnalyzer_cff import *


## define ordered jets
uds0    = cms.PSet(index = cms.int32(0), correctionLevel = cms.string('abs') )
uds1    = cms.PSet(index = cms.int32(1), correctionLevel = cms.string('abs') )
uds2    = cms.PSet(index = cms.int32(2), correctionLevel = cms.string('abs') )
uds3    = cms.PSet(index = cms.int32(3), correctionLevel = cms.string('abs') )
uds4    = cms.PSet(index = cms.int32(4), correctionLevel = cms.string('abs') )
uds5    = cms.PSet(index = cms.int32(5), correctionLevel = cms.string('abs') )
bottom0 = cms.PSet(index = cms.int32(0), correctionLevel = cms.string('abs') )
bottom1 = cms.PSet(index = cms.int32(1), correctionLevel = cms.string('abs') )

## MONITOR STEP 0

## JET KINEMATICS

## collect kinematics analyzers
tightBottomJetKinematics_0  = analyzeJetKinematics.clone (src = 'simpleSecondaryVertexBJets' )
tightLeadingJetKinematics_0 = analyzeJetKinematics.clone (src = 'goodJets')
tightLead_0_JetKinematics_0 = analyzeJetKinematics.clone (src = 'goodJets', analyze = uds0 )
tightLead_1_JetKinematics_0 = analyzeJetKinematics.clone (src = 'goodJets', analyze = uds1 )
tightLead_2_JetKinematics_0 = analyzeJetKinematics.clone (src = 'goodJets', analyze = uds2 )
tightLead_3_JetKinematics_0 = analyzeJetKinematics.clone (src = 'goodJets', analyze = uds3 )
tightLead_4_JetKinematics_0 = analyzeJetKinematics.clone (src = 'goodJets', analyze = uds4 )
tightLead_5_JetKinematics_0 = analyzeJetKinematics.clone (src = 'goodJets', analyze = uds5 )
tightBJet_0_JetKinematics_0 = analyzeJetKinematics.clone (src = 'simpleSecondaryVertexBJets' , analyze = bottom0)
tightBJet_1_JetKinematics_0 = analyzeJetKinematics.clone (src = 'simpleSecondaryVertexBJets' , analyze = bottom1)

## to be called with fullHadronicSelection
monitorJetsKinematics_0 = cms.Sequence(tightBottomJetKinematics_0  +
                                       tightBJet_0_JetKinematics_0 +
                                       tightBJet_1_JetKinematics_0 +
                                       tightLeadingJetKinematics_0 +
                                       tightLead_0_JetKinematics_0 +
                                       tightLead_1_JetKinematics_0 +
                                       tightLead_2_JetKinematics_0 +
                                       tightLead_3_JetKinematics_0 +
                                       tightLead_4_JetKinematics_0 +
                                       tightLead_5_JetKinematics_0  
                                       )

## EVENT SHAPES

## collect event shape analyzers
eventShapes_0 = analyzeEventShapes.clone( src = 'goodJets' )

## monitor sequence for event shape analyzers
monitorEventShapes_0 = cms.Sequence(eventShapes_0
                                    )

## FULL HAD SPECIAL

## collect analyzers specially for full hadronic analysis
fullHadSpecial_0 = analyzeFullHadSpecials.clone( src = 'goodJets' )

## monitor sequence for specially for full hadronic analyzers
monitorFullHadSpecials_0 = cms.Sequence(fullHadSpecial_0
                                        )

## GEN PARTICLE

## collect analyzers for genParticles
genParticles_0 = analyzeGenParticles.clone()

## monitor sequence for genParticles
monitorGenParticles_0 = cms.Sequence(genParticles_0
                                     )

## FILTER STEP 1 (To be found in from TopAnalysis.TopFilter.sequences.fullHadronicSelection_cff as  fullHadronicEvents)

## MONITOR STEP 1

## JET KINEMATICS

## collect kinematics analyzers
tightBottomJetKinematics_1  = analyzeJetKinematics.clone (src = 'tightBottomJets' )
tightLeadingJetKinematics_1 = analyzeJetKinematics.clone (src = 'tightLeadingJets')
tightLead_0_JetKinematics_1 = analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds0 )
tightLead_1_JetKinematics_1 = analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds1 )
tightLead_2_JetKinematics_1 = analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds2 )
tightLead_3_JetKinematics_1 = analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds3 )
tightLead_4_JetKinematics_1 = analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds4 )
tightLead_5_JetKinematics_1 = analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds5 )
tightBJet_0_JetKinematics_1 = analyzeJetKinematics.clone (src = 'tightBottomJets' , analyze = bottom0)
tightBJet_1_JetKinematics_1 = analyzeJetKinematics.clone (src = 'tightBottomJets' , analyze = bottom1)

## to be called with fullHadronicSelection
monitorJetsKinematics_1 = cms.Sequence(tightBottomJetKinematics_1  +
                                       tightBJet_0_JetKinematics_1 +
                                       tightBJet_1_JetKinematics_1 +
                                       tightLeadingJetKinematics_1 +
                                       tightLead_0_JetKinematics_1 +
                                       tightLead_1_JetKinematics_1 +
                                       tightLead_2_JetKinematics_1 +
                                       tightLead_3_JetKinematics_1 +
                                       tightLead_4_JetKinematics_1 +
                                       tightLead_5_JetKinematics_1  
                                       )

## EVENT SHAPES

## collect event shape analyzers
eventShapes_1 = analyzeEventShapes.clone( src = 'tightLeadingJets' )

## monitor sequence for event shape analyzers
monitorEventShapes_1 = cms.Sequence(eventShapes_1
                                    )

## FULL HAD SPECIAL

## collect analyzers specially for full hadronic analysis
fullHadSpecial_1 = analyzeFullHadSpecials.clone( src = 'tightLeadingJets' )

## monitor sequence for specially for full hadronic analyzers
monitorFullHadSpecials_1 = cms.Sequence(fullHadSpecial_1
                                        )

## KINFIT QUALITY

## kinfit quality analyzer
## collect kinfit quality analyzers
kinFitQuality_1 = analyzeKinFitQuality.clone( srcB = 'tightLeadingJets' )

## monitor sequence for kinfit quality analyzers
monitorKinFitQuality_1 = cms.Sequence(kinFitQuality_1
                                      )

## FULL HAD TOP RECO

## collect fully hadronic top reco analyzers
fullHadTopReco_1 = analyzeFullHadTopReco.clone( srcB = 'tightLeadingJets' )

## monitor sequence for fully hadronice top reco analyzers
monitorFullHadTopReco_1 = cms.Sequence(fullHadTopReco_1
                                       )

## GEN PARTICLE

## collect analyzers for genParticles
genParticles_1 = analyzeGenParticles.clone()

## monitor sequence for genParticles
monitorGenParticles_1 = cms.Sequence(genParticles_1
                                     )

## FILTER STEP 2

## kinfit quality filter
from TopAnalysis.TopFilter.filters.KinFitQualityFilter_cfi import *

## filter kinfit quality
filterKinFitQuality = filterKinFitQuality.clone( minProb = 0.01 )

## MONITOR STEP 2

## JET KINEMATICS

## collect kinematics analyzers
tightBottomJetKinematics_2  = analyzeJetKinematics.clone (src = 'tightBottomJets' )
tightLeadingJetKinematics_2 = analyzeJetKinematics.clone (src = 'tightLeadingJets')
tightLead_0_JetKinematics_2 = analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds0 )
tightLead_1_JetKinematics_2 = analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds1 )
tightLead_2_JetKinematics_2 = analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds2 )
tightLead_3_JetKinematics_2 = analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds3 )
tightLead_4_JetKinematics_2 = analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds4 )
tightLead_5_JetKinematics_2 = analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds5 )
tightBJet_0_JetKinematics_2 = analyzeJetKinematics.clone (src = 'tightBottomJets' , analyze = bottom0)
tightBJet_1_JetKinematics_2 = analyzeJetKinematics.clone (src = 'tightBottomJets' , analyze = bottom1)

## to be called with fullHadronicSelection
monitorJetsKinematics_2 = cms.Sequence(tightBottomJetKinematics_2  +
                                       tightBJet_0_JetKinematics_2 +
                                       tightBJet_1_JetKinematics_2 +
                                       tightLeadingJetKinematics_2 +
                                       tightLead_0_JetKinematics_2 +
                                       tightLead_1_JetKinematics_2 +
                                       tightLead_2_JetKinematics_2 +
                                       tightLead_3_JetKinematics_2 +
                                       tightLead_4_JetKinematics_2 +
                                       tightLead_5_JetKinematics_2  
                                       )

## EVENT SHAPES

## collect event shape analyzers
eventShapes_2 = analyzeEventShapes.clone( src = 'tightLeadingJets' )

## monitor sequence for event shape analyzers
monitorEventShapes_2 = cms.Sequence(eventShapes_2
                                    )

## KINFIT QUALITY

## kinfit quality analyzer
## collect kinfit quality analyzers
kinFitQuality_2 = analyzeKinFitQuality.clone( srcB = 'tightLeadingJets' )

## monitor sequence for kinfit quality analyzers
monitorKinFitQuality_2 = cms.Sequence(kinFitQuality_2
                                      )

## FULL HAD TOP RECO

## collect fully hadronic top reco analyzers
fullHadTopReco_2 = analyzeFullHadTopReco.clone( srcB = 'tightLeadingJets' )

## monitor sequence for fully hadronice top reco analyzers
monitorFullHadTopReco_2 = cms.Sequence(fullHadTopReco_2
                                       )

## FULL HAD SPECIAL

## collect analyzers specially for full hadronic analysis
fullHadSpecial_2 = analyzeFullHadSpecials.clone( src = 'tightLeadingJets' )

## monitor sequence for specially for full hadronic analyzers
monitorFullHadSpecials_2 = cms.Sequence(fullHadSpecial_2
                                        )

## GEN PARTICLE

## collect analyzers for genParticles
genParticles_2 = analyzeGenParticles.clone()

## monitor sequence for genParticles
monitorGenParticles_2 = cms.Sequence(genParticles_2
                                     )

## FILTER STEP 3

## event shape filter
from TopAnalysis.TopFilter.filters.EventShapeFilter_cfi import *

## filter event shape
filterEventShapes = filterEventShape.clone (minC = 0.75)

## MONITOR STEP 3

## To be added in time


## ---
##    run the final sequence
## ---
analyseFullHadronicSelection = cms.Sequence(## do the hlt triggering
                                            #hltQuadJet30          *
                                            hltHt200              *
                                            ## do the selections
                                            fullHadronicSelection *
                                            ## do the matching
                                            matchJetsToPartons    *
                                            ## do the monitoring
                                            #monitorJetsQuality      *
                                            monitorJetsKinematics_0 *
                                            monitorEventShapes_0    *
                                            monitorFullHadSpecials_0*
                                            monitorGenParticles_0   *
                                            ## do the 1. event selection
                                            fullHadronicEvents      *
                                            monitorJetsKinematics_1 *
                                            monitorEventShapes_1    *
                                            makeTtFullHadEvent      *
                                            monitorKinFitQuality_1  *
                                            monitorFullHadSpecials_1*
                                            monitorFullHadTopReco_1 *
                                            monitorGenParticles_1   *
                                            ## do the 2. event selection
                                            filterKinFitQuality     *
                                            monitorJetsKinematics_2 *
                                            monitorEventShapes_2    *
                                            monitorKinFitQuality_2  *
                                            monitorFullHadSpecials_2*
                                            monitorFullHadTopReco_2 *
                                            monitorGenParticles_2
                                            )

## run on real data
def runOnRealData(process):
    print '++++++++++++++++++++++++++++++++++++++++++++'
    print 'removing all elements from the sequence '
    print '*analyseFullHadronicSelection* that rely '
    print 'on generator information to run properly '
    print '++++++++++++++++++++++++++++++++++++++++++++'
    process.analyseFullHadronicSelection.remove(process.matchJetsToPartons)
    process.analyseFullHadronicSelection.remove(process.monitorGenParticles_0)
    process.analyseFullHadronicSelection.remove(process.monitorGenParticles_1)
    process.analyseFullHadronicSelection.remove(process.monitorGenParticles_2)

## run on real data
def removeMonitoringOfCutflow(process):
    print '++++++++++++++++++++++++++++++++++++++++++++'
    print 'removing all monitoring elements from the '
    print 'sequence *analyseFullHadronicSelection* so'
    print 'only a pure selection of events is done '
    print '++++++++++++++++++++++++++++++++++++++++++++'
    process.analyseFullHadronicSelection.remove(process.monitorJetsKinematics_0)
    process.analyseFullHadronicSelection.remove(process.monitorJetsKinematics_1)
    process.analyseFullHadronicSelection.remove(process.monitorJetsKinematics_2)
    process.analyseFullHadronicSelection.remove(process.monitorEventShapes_0)
    process.analyseFullHadronicSelection.remove(process.monitorEventShapes_1)
    process.analyseFullHadronicSelection.remove(process.monitorEventShapes_2)
    process.analyseFullHadronicSelection.remove(process.monitorFullHadSpecials_0)
    process.analyseFullHadronicSelection.remove(process.monitorFullHadSpecials_1)
    process.analyseFullHadronicSelection.remove(process.monitorFullHadSpecials_2)
    process.analyseFullHadronicSelection.remove(process.monitorGenParticles_0)
    process.analyseFullHadronicSelection.remove(process.monitorGenParticles_1)
    process.analyseFullHadronicSelection.remove(process.monitorGenParticles_2)
    process.analyseFullHadronicSelection.remove(process.monitorKinFitQuality_1)
    process.analyseFullHadronicSelection.remove(process.monitorKinFitQuality_2)
    process.analyseFullHadronicSelection.remove(process.monitorFullHadTopReco_1)
    process.analyseFullHadronicSelection.remove(process.monitorFullHadTopReco_2)

## remove default trigger
def removeDefaultTrigger(process):
    print '++++++++++++++++++++++++++++++++++++++++++++'
    print 'removing the default HLT_Ht200 trigger from '
    print 'standard fully hadronic event selection '
    print '++++++++++++++++++++++++++++++++++++++++++++'
    process.analyseFullHadronicSelection.remove(process.matchJetsToPartons)

