import FWCore.ParameterSet.Config as cms

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

## define tight cuts for jet kinematics
tightJetCut  = 'abs(eta) < 2.4 & pt > 30.'
bottomJetCut = 'abs(eta) < 2.4 & pt > 50.'

## define tight JetIDs
tightCaloJetID  = '& (((jecFactor("Uncorrected") * pt) > 25. & jetID.fHPD < 0.95) | (jecFactor("Uncorrected") * pt) <= 25.) & '
tightCaloJetID += '((abs(eta) > 1.0 & (jecFactor("Uncorrected") * pt) > 55. & emEnergyFraction < 1.0) | abs(eta) <= 1.0 | (jecFactor("Uncorrected") * pt) <= 55.)'
tightPFJetID    = '& neutralHadronEnergyFraction < 0.9 & '
tightPFJetID   += 'neutralEmEnergyFraction < 0.9'

## setup the jet selection collection
tightLeadingJets = selectedPatJets.clone(src = 'goodJets',
                                         cut = tightJetCut + tightCaloJetID
                                         )
tightBottomJets  = selectedPatJets.clone(src = 'trackCountingHighPurBJets',
                                         cut = bottomJetCut + tightCaloJetID
                                         )

## setting up the collections for the fully-hadronic
## event selection; on these collection monitoring
## can still be performed
fullHadronicSelection = cms.Sequence(goodJets *
                                     trackCountingHighPurBJets *
                                     tightLeadingJets *
                                     tightBottomJets
                                     )

## ---
##    configure the cutflow scenario
## ---

## jet quality analyzer
from TopAnalysis.TopAnalyzer.JetQuality_cfi import *
## muon quality analyzer
#from TopAnalysis.TopAnalyzer.MuonQuality_cfi import *
## jet kinematics analyzer
from TopAnalysis.TopAnalyzer.JetKinematics_cfi import *
## MET kinematics analyzer
from TopAnalysis.TopAnalyzer.METKinematics_cfi import *
## muon kinematics analyzer
#from TopAnalysis.TopAnalyzer.MuonKinematics_cfi import *
## event shape analyzer
from TopAnalysis.TopAnalyzer.EventShapes_cfi import *
## genParticle analyzer
from TopAnalysis.TopAnalyzer.GenParticle_cfi import *
## ptHat analyzer
from TopAnalysis.TopAnalyzer.PtHat_cfi import *
## analyzer for special variables in fully hadronic channel
from TopAnalysis.TopAnalyzer.FullHadSpecial_cfi import *
## kinfit analyzer
from TopAnalysis.TopAnalyzer.KinFitQuality_cfi import *
from TopAnalysis.TopAnalyzer.KinFitImprover_cfi import *
from TopAnalysis.TopAnalyzer.METKinFitAnalyzer_cfi import *
## analyzer for fully hadronic event reco
from TopAnalysis.TopAnalyzer.FullHadTopReco_cfi import *
## high level trigger filter
from TopAnalysis.TopFilter.sequences.triggerFilter_cff import *
from TopAnalysis.TopFilter.filters.NewTriggerTestFilter_cfi import *
## generator matching
from TopAnalysis.TopFilter.sequences.generatorMatching_cff import *
## kinFit producer
from TopQuarkAnalysis.TopEventProducers.sequences.ttFullHadEvtBuilder_cff import *
from TopAnalysis.TopAnalyzer.FullHadHypothesisAnalyzer_cff import *
## PDF uncertainties
from TopAnalysis.TopAnalyzer.PDFUncertainty_cfi import *

## ---
##    TRIGGER DEFINITION
## ---

### create trigger selection for MC
#trigger = hltQuadJet30.clone( HLTPaths = ["HLT_QuadJet15U"],
#                              TriggerResultsTag = cms.InputTag("TriggerResults","","REDIGI") )
#
### create personal QuadJet40 trigger
#
## get trigger module to be added to the path
from TopAnalysis.TopUtils.patTriggerEvent_cff import *
#
### the QuadJet40 trigger itself
#hltQJ40 = filterTrigger.clone()
#
#trigger = cms.Sequence(patTriggerDefaultSequence *
#                       hltQJ40
#                       )
#
## create personal QuadJet25U trigger

## the QuadJet25U trigger itself
hltQJ25U = filterTrigger.clone( whichTrigger="QuadJet25U" )

trigger = cms.Sequence(patTriggerDefaultSequence *
                       hltQJ25U
                       )

### high level trigger filter
#from HLTrigger.HLTfilters.hltHighLevel_cfi import *
#trigger = hltHighLevel.clone(HLTPaths = ["HLT_QuadJet25U", "HLT_QuadJet25U_v2", "HLT_QuadJet25U_v3"],
#                             throw = False)

## ---
##    FILTER STEP 0
## ---

## vertex filter
vertex = cms.EDFilter("VertexSelector",
                      src = cms.InputTag("offlinePrimaryVertices"),
                      cut = cms.string("!isFake && ndof > 4 && abs(z) < 24 && position.Rho < 2"),
                      filter = cms.bool(True),
                      )

## scraping filter
noscraping = cms.EDFilter("FilterOutScraping",
                          applyfilter = cms.untracked.bool(True),
                          debugOn = cms.untracked.bool(False),
                          numtrack = cms.untracked.uint32(10),
                          thresh = cms.untracked.double(0.25)
                          )

## setup good jet selection collection
goodJetSelection = countPatJets.clone(src = 'goodJets',
                                      minNumber = 6
                                      )

filterStep0 = cms.Sequence(vertex *
                           noscraping *
                           goodJetSelection
                           )

## to switch verbosity modes of the kinFit
#ttFullHadEvent.verbosity = 3

## configuration of kinematic fit
kinFitTtFullHadEventHypothesis.maxNComb = -1

kinFitTtFullHadEventHypothesis.bTags = 2
kinFitTtFullHadEventHypothesis.bTagAlgo = 'trackCountingHighPurBJetTags'
kinFitTtFullHadEventHypothesis.minBTagValueBJet    = 1.93
kinFitTtFullHadEventHypothesis.maxBTagValueNonBJet = 3.41

#setForAllTtFullHadHypotheses(process, 'maxNJets', -1)
kinFitTtFullHadEventHypothesis.maxNJets = -1
ttFullHadJetPartonMatch.maxNJets        = -1

#setForAllTtFullHadHypotheses(process, 'jetCorrectionLevel', 'had')
kinFitTtFullHadEventHypothesis.jetCorrectionLevel = 'L5Flavor'
ttFullHadHypGenMatch.jetCorrectionLevel           = 'L5Flavor'

#setForAllTtFullHadHypotheses(process, 'jets', 'tightLeadingJets')
kinFitTtFullHadEventHypothesis.jets = 'tightLeadingJets'
ttFullHadJetPartonMatch.jets        = 'tightLeadingJets'
ttFullHadHypGenMatch.jets           = 'tightLeadingJets'
ttFullHadHypKinFit.jets             = 'tightLeadingJets'

## define ordered jets
udsall =cms.PSet(index=cms.int32(-1), correctionLevel=cms.string('L3Absolute'), flavor=cms.string("uds")   , useTree=cms.bool(False))
uds0   =cms.PSet(index=cms.int32(0) , correctionLevel=cms.string('L3Absolute'), flavor=cms.string("uds")   , useTree=cms.bool(False))
uds1   =cms.PSet(index=cms.int32(1) , correctionLevel=cms.string('L3Absolute'), flavor=cms.string("uds")   , useTree=cms.bool(False))
uds2   =cms.PSet(index=cms.int32(2) , correctionLevel=cms.string('L3Absolute'), flavor=cms.string("uds")   , useTree=cms.bool(False))
uds3   =cms.PSet(index=cms.int32(3) , correctionLevel=cms.string('L3Absolute'), flavor=cms.string("uds")   , useTree=cms.bool(False))
uds4   =cms.PSet(index=cms.int32(4) , correctionLevel=cms.string('L3Absolute'), flavor=cms.string("uds")   , useTree=cms.bool(False))
uds5   =cms.PSet(index=cms.int32(5) , correctionLevel=cms.string('L3Absolute'), flavor=cms.string("uds")   , useTree=cms.bool(False))
ball   =cms.PSet(index=cms.int32(-1), correctionLevel=cms.string('L3Absolute'), flavor=cms.string("bottom"), useTree=cms.bool(False))
bottom0=cms.PSet(index=cms.int32(0) , correctionLevel=cms.string('L3Absolute'), flavor=cms.string("bottom"), useTree=cms.bool(False))
bottom1=cms.PSet(index=cms.int32(1) , correctionLevel=cms.string('L3Absolute'), flavor=cms.string("bottom"), useTree=cms.bool(False))

## ---
##    MONITOR STEP 0
## ---

## PDF WEIGHTS for PDF uncertainties

PDFUncertainty_0 = analyzePDFUncertainty.clone()

## JET KINEMATICS

## kinematics analyzers
tightBottomJetKinematics_0  = analyzeJetKinematics.clone (src = 'trackCountingHighPurBJets', analyze = ball)
tightLeadingJetKinematics_0 = analyzeJetKinematics.clone (src = 'goodJets', analyze = udsall)
tightLead_0_JetKinematics_0 = analyzeJetKinematics.clone (src = 'goodJets', analyze = uds0  )
tightLead_1_JetKinematics_0 = analyzeJetKinematics.clone (src = 'goodJets', analyze = uds1  )
tightLead_2_JetKinematics_0 = analyzeJetKinematics.clone (src = 'goodJets', analyze = uds2  )
tightLead_3_JetKinematics_0 = analyzeJetKinematics.clone (src = 'goodJets', analyze = uds3  )
tightLead_4_JetKinematics_0 = analyzeJetKinematics.clone (src = 'goodJets', analyze = uds4  )
tightLead_5_JetKinematics_0 = analyzeJetKinematics.clone (src = 'goodJets', analyze = uds5  )
tightBJet_0_JetKinematics_0 = analyzeJetKinematics.clone (src = 'trackCountingHighPurBJets' , analyze = bottom0)
tightBJet_1_JetKinematics_0 = analyzeJetKinematics.clone (src = 'trackCountingHighPurBJets' , analyze = bottom1)
METKinematics_0 = analyzeMETKinematics.clone()

## collect kinematics analyzers
monitorKinematics_0 = cms.Sequence(tightBottomJetKinematics_0  *
                                   tightBJet_0_JetKinematics_0 *
                                   tightBJet_1_JetKinematics_0 *
                                   tightLeadingJetKinematics_0 *
                                   tightLead_0_JetKinematics_0 *
                                   tightLead_1_JetKinematics_0 *
                                   tightLead_2_JetKinematics_0 *
                                   tightLead_3_JetKinematics_0 *
                                   tightLead_4_JetKinematics_0 *
                                   tightLead_5_JetKinematics_0 *
                                   METKinematics_0
                                   )

## JET QUALITY

## quality analyzers
tightBottomJetQuality_0  = analyzeJetQuality.clone (src = 'trackCountingHighPurBJets', analyze = ball)
tightLeadingJetQuality_0 = analyzeJetQuality.clone (src = 'goodJets', analyze = udsall)
tightLead_0_JetQuality_0 = analyzeJetQuality.clone (src = 'goodJets', analyze = uds0  )
tightLead_1_JetQuality_0 = analyzeJetQuality.clone (src = 'goodJets', analyze = uds1  )
tightLead_2_JetQuality_0 = analyzeJetQuality.clone (src = 'goodJets', analyze = uds2  )
tightLead_3_JetQuality_0 = analyzeJetQuality.clone (src = 'goodJets', analyze = uds3  )
tightLead_4_JetQuality_0 = analyzeJetQuality.clone (src = 'goodJets', analyze = uds4  )
tightLead_5_JetQuality_0 = analyzeJetQuality.clone (src = 'goodJets', analyze = uds5  )
tightBJet_0_JetQuality_0 = analyzeJetQuality.clone (src = 'trackCountingHighPurBJets' , analyze = bottom0)
tightBJet_1_JetQuality_0 = analyzeJetQuality.clone (src = 'trackCountingHighPurBJets' , analyze = bottom1)

## collect quality analyzers
monitorJetsQuality_0 = cms.Sequence(tightBottomJetQuality_0  *
                                    tightBJet_0_JetQuality_0 *
                                    tightBJet_1_JetQuality_0 *
                                    tightLeadingJetQuality_0 *
                                    tightLead_0_JetQuality_0 *
                                    tightLead_1_JetQuality_0 *
                                    tightLead_2_JetQuality_0 *
                                    tightLead_3_JetQuality_0 *
                                    tightLead_4_JetQuality_0 *
                                    tightLead_5_JetQuality_0  
                                    )

## EVENT SHAPES

## collect event shape analyzers
eventShapes_0 = analyzeEventShapes.clone( src = 'goodJets' )

## monitor sequence for event shape analyzers
monitorEventShapes_0 = cms.Sequence( eventShapes_0 )

## FULL HAD SPECIAL

## collect analyzers specially for full hadronic analysis
fullHadSpecial_0 = analyzeFullHadSpecials.clone( src = 'goodJets' )

## monitor sequence for specially for full hadronic analyzers
monitorFullHadSpecials_0 = cms.Sequence( fullHadSpecial_0 )

## GENERATOR INFORMATION

## collect analyzers for genParticles
genParticles_0 = analyzeGenParticles.clone()

## collect analyzers for ptHat
ptHat_0 = analyzePtHat.clone()

## monitor sequence for generator
monitorGenerator_0 = cms.Sequence( genParticles_0 *
                                   ptHat_0
                                  )

## ---
##    FILTER STEP 1
## ---

## select all events with at least 6 jets
leadingJetSelection = countPatJets.clone( src = 'tightLeadingJets',
                                          minNumber = 6
                                         )

## ---
##    MONITOR STEP 1
## ---

## JET KINEMATICS

monitoredTightBottomJets  = selectedPatJets.clone(src = 'trackCountingHighPurBJets',
                                                  cut = tightJetCut + tightCaloJetID
                                                  )

## kinematics analyzers
tightBottomJetKinematics_1  = analyzeJetKinematics.clone (src = 'tightBottomJets' , analyze = ball   )
tightLeadingJetKinematics_1 = analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = udsall )
tightLead_0_JetKinematics_1 = analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds0   )
tightLead_1_JetKinematics_1 = analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds1   )
tightLead_2_JetKinematics_1 = analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds2   )
tightLead_3_JetKinematics_1 = analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds3   )
tightLead_4_JetKinematics_1 = analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds4   )
tightLead_5_JetKinematics_1 = analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds5   )
tightBJet_0_JetKinematics_1 = analyzeJetKinematics.clone (src = 'tightBottomJets' , analyze = bottom0)
tightBJet_1_JetKinematics_1 = analyzeJetKinematics.clone (src = 'tightBottomJets' , analyze = bottom1)
METKinematics_1 = analyzeMETKinematics.clone()

monitoredTightBottomJetKinematics_1  = analyzeJetKinematics.clone (src = 'monitoredTightBottomJets' , analyze = ball   )
monitoredTightBJet_0_JetKinematics_1 = analyzeJetKinematics.clone (src = 'monitoredTightBottomJets' , analyze = bottom0)
monitoredTightBJet_1_JetKinematics_1 = analyzeJetKinematics.clone (src = 'monitoredTightBottomJets' , analyze = bottom1)

## collect kinematics analyzers
monitorKinematics_1 = cms.Sequence(tightBottomJetKinematics_1  *
                                   tightBJet_0_JetKinematics_1 *
                                   tightBJet_1_JetKinematics_1 *
                                   tightLeadingJetKinematics_1 *
                                   tightLead_0_JetKinematics_1 *
                                   tightLead_1_JetKinematics_1 *
                                   tightLead_2_JetKinematics_1 *
                                   tightLead_3_JetKinematics_1 *
                                   tightLead_4_JetKinematics_1 *
                                   tightLead_5_JetKinematics_1 *
                                   METKinematics_1             *
                                   monitoredTightBottomJets    *
                                   monitoredTightBottomJetKinematics_1  *
                                   monitoredTightBJet_0_JetKinematics_1 *
                                   monitoredTightBJet_1_JetKinematics_1 
                                   )

## JET QUALITY

## quality analyzers
tightBottomJetQuality_1  = analyzeJetQuality.clone (src = 'tightBottomJets' , analyze = ball   )
tightLeadingJetQuality_1 = analyzeJetQuality.clone (src = 'tightLeadingJets', analyze = udsall )
tightLead_0_JetQuality_1 = analyzeJetQuality.clone (src = 'tightLeadingJets', analyze = uds0   )
tightLead_1_JetQuality_1 = analyzeJetQuality.clone (src = 'tightLeadingJets', analyze = uds1   )
tightLead_2_JetQuality_1 = analyzeJetQuality.clone (src = 'tightLeadingJets', analyze = uds2   )
tightLead_3_JetQuality_1 = analyzeJetQuality.clone (src = 'tightLeadingJets', analyze = uds3   )
tightLead_4_JetQuality_1 = analyzeJetQuality.clone (src = 'tightLeadingJets', analyze = uds4   )
tightLead_5_JetQuality_1 = analyzeJetQuality.clone (src = 'tightLeadingJets', analyze = uds5   )
tightBJet_0_JetQuality_1 = analyzeJetQuality.clone (src = 'tightBottomJets' , analyze = bottom0)
tightBJet_1_JetQuality_1 = analyzeJetQuality.clone (src = 'tightBottomJets' , analyze = bottom1)

## collect quality analyzers
monitorJetsQuality_1 = cms.Sequence(tightBottomJetQuality_1  *
                                    tightBJet_0_JetQuality_1 *
                                    tightBJet_1_JetQuality_1 *
                                    tightLeadingJetQuality_1 *
                                    tightLead_0_JetQuality_1 *
                                    tightLead_1_JetQuality_1 *
                                    tightLead_2_JetQuality_1 *
                                    tightLead_3_JetQuality_1 *
                                    tightLead_4_JetQuality_1 *
                                    tightLead_5_JetQuality_1  
                                    )

## EVENT SHAPES

## collect event shape analyzers
eventShapes_1 = analyzeEventShapes.clone( src = 'tightLeadingJets' )

## monitor sequence for event shape analyzers
monitorEventShapes_1 = cms.Sequence( eventShapes_1 )

## FULL HAD SPECIAL

## collect analyzers specially for full hadronic analysis
fullHadSpecial_1 = analyzeFullHadSpecials.clone( src = 'tightLeadingJets' )

## monitor sequence for specially for full hadronic analyzers
monitorFullHadSpecials_1 = cms.Sequence( fullHadSpecial_1 )

## GENERATOR INFORMATION

## collect analyzers for genParticles
genParticles_1 = analyzeGenParticles.clone()

## collect analyzers for ptHat
ptHat_1 = analyzePtHat.clone()

## monitor sequence for generator
monitorGenerator_1 = cms.Sequence( genParticles_1 *
                                   ptHat_1
                                  )

## ---
##    FILTER STEP 2
## ---

## select events with at least 1 b jets
tightBottomJetSelection_v1   = countPatJets.clone( src = 'tightBottomJets',
                                                   minNumber = 1
                                                 )

tightBottomJetKinematics_2_v1  = analyzeJetKinematics.clone (src = 'tightBottomJets' )
tightLeadingJetKinematics_2_v1 = analyzeJetKinematics.clone (src = 'tightLeadingJets')

## select events with at least 2 b jets
tightBottomJetSelection_v2   = countPatJets.clone( src = 'tightBottomJets',
                                                   minNumber = 2
                                                 )

bottomJetSelection = cms.Sequence(tightBottomJetSelection_v1     *
                                  tightBottomJetKinematics_2_v1  *
                                  tightLeadingJetKinematics_2_v1 *
                                  tightBottomJetSelection_v2
                                  )

## ---
##    MONITOR STEP 2
## ---

## JET KINEMATICS

## collect kinematics analyzers
tightBottomJetKinematics_2  = analyzeJetKinematics.clone (src = 'tightBottomJets' , analyze = ball   )
tightLeadingJetKinematics_2 = analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = udsall )
tightLead_0_JetKinematics_2 = analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds0   )
tightLead_1_JetKinematics_2 = analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds1   )
tightLead_2_JetKinematics_2 = analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds2   )
tightLead_3_JetKinematics_2 = analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds3   )
tightLead_4_JetKinematics_2 = analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds4   )
tightLead_5_JetKinematics_2 = analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds5   )
tightBJet_0_JetKinematics_2 = analyzeJetKinematics.clone (src = 'tightBottomJets' , analyze = bottom0)
tightBJet_1_JetKinematics_2 = analyzeJetKinematics.clone (src = 'tightBottomJets' , analyze = bottom1)
METKinematics_2 = analyzeMETKinematics.clone()

## to be called with fullHadronicSelection
monitorKinematics_2 = cms.Sequence(tightBottomJetKinematics_2  *
                                   tightBJet_0_JetKinematics_2 *
                                   tightBJet_1_JetKinematics_2 *
                                   tightLeadingJetKinematics_2 *
                                   tightLead_0_JetKinematics_2 *
                                   tightLead_1_JetKinematics_2 *
                                   tightLead_2_JetKinematics_2 *
                                   tightLead_3_JetKinematics_2 *
                                   tightLead_4_JetKinematics_2 *
                                   tightLead_5_JetKinematics_2 *
                                   METKinematics_2
                                   )

## JET QUALITY

## quality analyzers
tightBottomJetQuality_2  = analyzeJetQuality.clone (src = 'tightBottomJets' , analyze = ball   )
tightLeadingJetQuality_2 = analyzeJetQuality.clone (src = 'tightLeadingJets', analyze = udsall )
tightLead_0_JetQuality_2 = analyzeJetQuality.clone (src = 'tightLeadingJets', analyze = uds0   )
tightLead_1_JetQuality_2 = analyzeJetQuality.clone (src = 'tightLeadingJets', analyze = uds1   )
tightLead_2_JetQuality_2 = analyzeJetQuality.clone (src = 'tightLeadingJets', analyze = uds2   )
tightLead_3_JetQuality_2 = analyzeJetQuality.clone (src = 'tightLeadingJets', analyze = uds3   )
tightLead_4_JetQuality_2 = analyzeJetQuality.clone (src = 'tightLeadingJets', analyze = uds4   )
tightLead_5_JetQuality_2 = analyzeJetQuality.clone (src = 'tightLeadingJets', analyze = uds5   )
tightBJet_0_JetQuality_2 = analyzeJetQuality.clone (src = 'tightBottomJets' , analyze = bottom0)
tightBJet_1_JetQuality_2 = analyzeJetQuality.clone (src = 'tightBottomJets' , analyze = bottom1)

## collect quality analyzers
monitorJetsQuality_2 = cms.Sequence(tightBottomJetQuality_2  *
                                    tightBJet_0_JetQuality_2 *
                                    tightBJet_1_JetQuality_2 *
                                    tightLeadingJetQuality_2 *
                                    tightLead_0_JetQuality_2 *
                                    tightLead_1_JetQuality_2 *
                                    tightLead_2_JetQuality_2 *
                                    tightLead_3_JetQuality_2 *
                                    tightLead_4_JetQuality_2 *
                                    tightLead_5_JetQuality_2  
                                    )

## EVENT SHAPES

## collect event shape analyzers
eventShapes_2 = analyzeEventShapes.clone( src = 'tightLeadingJets' )

## monitor sequence for event shape analyzers
monitorEventShapes_2 = cms.Sequence( eventShapes_2 )

## KINFIT QUALITY AND FULL HAD TOP RECO

## kinfit quality analyzer
## collect kinfit quality analyzers
kinFitQuality_2  = analyzeKinFitQuality.clone  ( srcB = 'tightLeadingJets' )
kinFitImprover0_2 = analyzeKinFitImprover.clone( srcB = 'tightLeadingJets' , analyze = cms.PSet( comboType = cms.uint32(0) ) )
kinFitImprover1_2 = analyzeKinFitImprover.clone( srcB = 'tightLeadingJets' , analyze = cms.PSet( comboType = cms.uint32(1) ) )
kinFitImprover2_2 = analyzeKinFitImprover.clone( srcB = 'tightLeadingJets' , analyze = cms.PSet( comboType = cms.uint32(2) ) )
kinFitImprover3_2 = analyzeKinFitImprover.clone( srcB = 'tightLeadingJets' , analyze = cms.PSet( comboType = cms.uint32(3) ) )
kinFitImprover4_2 = analyzeKinFitImprover.clone( srcB = 'tightLeadingJets' , analyze = cms.PSet( comboType = cms.uint32(4) ) )

## collect fully hadronic top reco analyzers
fullHadTopReco_2 = analyzeFullHadTopReco.clone( srcB = 'tightLeadingJets' )
fullHadTopReco_2.analyze.bTagAlgo = 'trackCountingHighPurBJetTags' 
METKinFit_2 = analyzeMETKinFit.clone( JetSrc = 'tightLeadingJets' )

## monitor sequence for kinfit quality analyzers
monitorKinFit_2 = cms.Sequence( kinFitQuality_2   *
                                kinFitImprover0_2 *
                                kinFitImprover1_2 *
                                kinFitImprover2_2 *
                                kinFitImprover3_2 *
                                kinFitImprover4_2 *
                                METKinFit_2       *
                                fullHadTopReco_2
                               )

## FULL HAD SPECIAL

## collect analyzers specially for full hadronic analysis
fullHadSpecial_2 = analyzeFullHadSpecials.clone( src = 'tightLeadingJets' )

## monitor sequence for specially for full hadronic analyzers
monitorFullHadSpecials_2 = cms.Sequence( fullHadSpecial_2 )

## GENERATOR INFORMATION

## collect analyzers for genParticles
genParticles_2 = analyzeGenParticles.clone()

## collect analyzers for ptHat
ptHat_2 = analyzePtHat.clone()

## monitor sequence for generator
monitorGenerator_2 = cms.Sequence( genParticles_2 *
                                   ptHat_2
                                  )

## ---
##    FILTER STEP 3
## ---

## kinfit quality filter
#### for back-ward compatibility with releases before CMSSW_3_8_X
##from TopAnalysis.TopFilter.filters.KinFitQualityFilter_cfi import *
##filterKinFitQuality = filterKinFitQuality.clone( srcB = 'tightLeadingJets', minProb = 0.01 )
from TopQuarkAnalysis.TopEventProducers.producers.TtFullHadEvtFilter_cfi import *
filterKinFitQuality = ttFullHadEventFilter.clone( cut = cms.string("isHypoValid('kKinFit') & fitProb > 0.01") )

## ---
##    MONITOR STEP 3
## ---

## JET KINEMATICS

## collect kinematics analyzers
tightBottomJetKinematics_3  = analyzeJetKinematics.clone (src = 'tightBottomJets' , analyze = ball   )
tightLeadingJetKinematics_3 = analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = udsall )
tightLead_0_JetKinematics_3 = analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds0   )
tightLead_1_JetKinematics_3 = analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds1   )
tightLead_2_JetKinematics_3 = analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds2   )
tightLead_3_JetKinematics_3 = analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds3   )
tightLead_4_JetKinematics_3 = analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds4   )
tightLead_5_JetKinematics_3 = analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds5   )
tightBJet_0_JetKinematics_3 = analyzeJetKinematics.clone (src = 'tightBottomJets' , analyze = bottom0)
tightBJet_1_JetKinematics_3 = analyzeJetKinematics.clone (src = 'tightBottomJets' , analyze = bottom1)
METKinematics_3 = analyzeMETKinematics.clone()

## to be called with fullHadronicSelection
monitorKinematics_3 = cms.Sequence(tightBottomJetKinematics_3  *
                                   tightBJet_0_JetKinematics_3 *
                                   tightBJet_1_JetKinematics_3 *
                                   tightLeadingJetKinematics_3 *
                                   tightLead_0_JetKinematics_3 *
                                   tightLead_1_JetKinematics_3 *
                                   tightLead_2_JetKinematics_3 *
                                   tightLead_3_JetKinematics_3 *
                                   tightLead_4_JetKinematics_3 *
                                   tightLead_5_JetKinematics_3 *
                                   METKinematics_3
                                   )

## JET QUALITY

## quality analyzers
tightBottomJetQuality_3  = analyzeJetQuality.clone (src = 'tightBottomJets' , analyze = ball   )
tightLeadingJetQuality_3 = analyzeJetQuality.clone (src = 'tightLeadingJets', analyze = udsall )
tightLead_0_JetQuality_3 = analyzeJetQuality.clone (src = 'tightLeadingJets', analyze = uds0   )
tightLead_1_JetQuality_3 = analyzeJetQuality.clone (src = 'tightLeadingJets', analyze = uds1   )
tightLead_2_JetQuality_3 = analyzeJetQuality.clone (src = 'tightLeadingJets', analyze = uds2   )
tightLead_3_JetQuality_3 = analyzeJetQuality.clone (src = 'tightLeadingJets', analyze = uds3   )
tightLead_4_JetQuality_3 = analyzeJetQuality.clone (src = 'tightLeadingJets', analyze = uds4   )
tightLead_5_JetQuality_3 = analyzeJetQuality.clone (src = 'tightLeadingJets', analyze = uds5   )
tightBJet_0_JetQuality_3 = analyzeJetQuality.clone (src = 'tightBottomJets' , analyze = bottom0)
tightBJet_1_JetQuality_3 = analyzeJetQuality.clone (src = 'tightBottomJets' , analyze = bottom1)

## collect quality analyzers
monitorJetsQuality_3 = cms.Sequence(tightBottomJetQuality_3  *
                                    tightBJet_0_JetQuality_3 *
                                    tightBJet_1_JetQuality_3 *
                                    tightLeadingJetQuality_3 *
                                    tightLead_0_JetQuality_3 *
                                    tightLead_1_JetQuality_3 *
                                    tightLead_2_JetQuality_3 *
                                    tightLead_3_JetQuality_3 *
                                    tightLead_4_JetQuality_3 *
                                    tightLead_5_JetQuality_3  
                                    )

## EVENT SHAPES

## collect event shape analyzers
eventShapes_3 = analyzeEventShapes.clone( src = 'tightLeadingJets' )

## monitor sequence for event shape analyzers
monitorEventShapes_3 = cms.Sequence( eventShapes_3 )

## KINFIT QUALITY AND FULL HAD TOP RECO

## kinfit quality analyzer
## collect kinfit quality analyzers
kinFitQuality_3  = analyzeKinFitQuality.clone  ( srcB = 'tightLeadingJets' )
kinFitImprover0_3 = analyzeKinFitImprover.clone( srcB = 'tightLeadingJets' , analyze = cms.PSet( comboType = cms.uint32(0) ) )
kinFitImprover1_3 = analyzeKinFitImprover.clone( srcB = 'tightLeadingJets' , analyze = cms.PSet( comboType = cms.uint32(1) ) )
kinFitImprover2_3 = analyzeKinFitImprover.clone( srcB = 'tightLeadingJets' , analyze = cms.PSet( comboType = cms.uint32(2) ) )
kinFitImprover3_3 = analyzeKinFitImprover.clone( srcB = 'tightLeadingJets' , analyze = cms.PSet( comboType = cms.uint32(3) ) )
kinFitImprover4_3 = analyzeKinFitImprover.clone( srcB = 'tightLeadingJets' , analyze = cms.PSet( comboType = cms.uint32(4) ) )

## collect fully hadronic top reco analyzers
fullHadTopReco_3 = analyzeFullHadTopReco.clone( srcB = 'tightLeadingJets' )
fullHadTopReco_3.analyze.bTagAlgo = 'trackCountingHighPurBJetTags' 
METKinFit_3 = analyzeMETKinFit.clone( JetSrc = 'tightLeadingJets' )

## monitor sequence for kinfit quality analyzers
monitorKinFit_3 = cms.Sequence( kinFitQuality_3  *
                                kinFitImprover0_3 *
                                kinFitImprover1_3 *
                                kinFitImprover2_3 *
                                kinFitImprover3_3 *
                                kinFitImprover4_3 *
                                METKinFit_3       *
                                fullHadTopReco_3
                               )

## FULL HAD SPECIAL

## collect analyzers specially for full hadronic analysis
fullHadSpecial_3 = analyzeFullHadSpecials.clone( src = 'tightLeadingJets' )

## monitor sequence for specially for full hadronic analyzers
monitorFullHadSpecials_3 = cms.Sequence( fullHadSpecial_3 )

## GENERATOR INFORMATION

## collect analyzers for genParticles
genParticles_3 = analyzeGenParticles.clone()

## collect analyzers for ptHat
ptHat_3 = analyzePtHat.clone()

## monitor sequence for generator
monitorGenerator_3 = cms.Sequence( genParticles_3 *
                                   ptHat_3
                                  )

## ---
##    FILTER STEP 4 (not used)
## ---

## event shape filter
from TopAnalysis.TopFilter.filters.EventShapeFilter_cfi import *
filterEventShapes = filterEventShape.clone( minC = 0.75 )

## ---
##    MONITOR STEP 4
## ---

## To be added in time



## PDF WEIGHTS for PDF uncertainties

PDFUncertainty_3 = analyzePDFUncertainty.clone()

## ---
##    run the final sequence
## ---
analyseFullHadronicSelection = cms.Sequence(PDFUncertainty_0      *
                                            ## do the hlt triggering
                                            trigger               *
                                            ## do the selections
                                            fullHadronicSelection *
                                            ## do the matching
                                            matchJetsToPartons    *
                                            filterStep0           *
                                            ## do the monitoring
                                            monitorKinematics_0      *
                                            monitorJetsQuality_0     *
                                            monitorEventShapes_0     *
                                            monitorFullHadSpecials_0 *
                                            monitorGenerator_0       *
                                            ## do the 1. event selection
                                            leadingJetSelection      *
                                            monitorKinematics_1      *
                                            monitorJetsQuality_1     *
                                            monitorEventShapes_1     *
                                            monitorFullHadSpecials_1 *
                                            monitorGenerator_1       *
                                            ## do the 2. event selection
                                            bottomJetSelection       *
                                            makeTtFullHadEvent       *
                                            monitorKinFit_2          *
                                            monitorKinematics_2      *
                                            monitorJetsQuality_2     *
                                            monitorEventShapes_2     *
                                            monitorFullHadSpecials_2 *
                                            monitorGenerator_2       *
                                            ## do the 3. event selection
                                            filterKinFitQuality      *
                                            monitorKinFit_3          *
                                            monitorKinematics_3      *
                                            monitorJetsQuality_3     *
                                            monitorEventShapes_3     *
                                            monitorFullHadSpecials_3 *
                                            monitorGenerator_3       *
                                            PDFUncertainty_3
                                            )


## ---
##    provide a function to use trees if available instead of histograms
## ---
def useTreesAsOutput(process):
    from PhysicsTools.PatAlgos.tools.helpers import listModules
    for mod in listModules(process.analyseFullHadronicSelection):
        if(hasattr(mod, 'analyze')):
            if(hasattr(mod.analyze, 'useTree')):
                mod.analyze.useTree = True
            if(hasattr(mod, 'useTree')):
                mod.useTree = True

## ---
##    provide a function to disable parts of the selection
## ---
def disableCountFilter(whichCountFilter):
    whichCountFilter.minNumber = 0
    whichCountFilter.maxNumber = 999999

## ---
##    run on real data
## ---
def runOnRealData(process):
    print '++++++++++++++++++++++++++++++++++++++++++++'
    print 'removing all elements from the sequence '
    print '*analyseFullHadronicSelection* that rely '
    print 'on generator information to run properly '
    print '++++++++++++++++++++++++++++++++++++++++++++'
    ## removal of generator based information
    process.analyseFullHadronicSelection.remove(process.matchJetsToPartons)
    process.analyseFullHadronicSelection.remove(process.monitorGenerator_0)
    process.analyseFullHadronicSelection.remove(process.monitorGenerator_1)
    process.analyseFullHadronicSelection.remove(process.monitorGenerator_2)
    process.analyseFullHadronicSelection.remove(process.monitorGenerator_3)

    ## switch to residual jet energy correction for data
    if(hasattr(process, 'goodJetsPF')):
        process.kinFitTtFullHadEventHypothesis.jetCorrectionLevel = 'L2L3Residual'
        process.ttFullHadHypGenMatch.jetCorrectionLevel           = 'L2L3Residual'

    udsall.correctionLevel  = 'L2L3Residual'
    uds0.correctionLevel    = 'L2L3Residual'
    uds1.correctionLevel    = 'L2L3Residual'
    uds2.correctionLevel    = 'L2L3Residual'
    uds3.correctionLevel    = 'L2L3Residual'
    uds4.correctionLevel    = 'L2L3Residual'
    uds5.correctionLevel    = 'L2L3Residual'
    ball.correctionLevel    = 'L2L3Residual'
    bottom0.correctionLevel = 'L2L3Residual'
    bottom1.correctionLevel = 'L2L3Residual'

    ## changes needed for analysis
    #trigger.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
    #process.patTrigger.processName = 'HLT'
    #vertex.cut = cms.string("!isFake && ndof > 4 && abs(z) < 24 && position.Rho < 2")

    ## different detector response for jets than in simulation
    #if(hasattr(process, 'goodJets') & hasattr(process, 'residualCorrectedJets')):
    #    process.goodJets.src   = 'residualCorrectedJets'
    #if(hasattr(process, 'goodJetsPF') & hasattr(process, 'residualCorrectedJets')):
    #    process.goodJetsPF.src = 'residualCorrectedJets'

    ## changes due to different reconstruction releases
    #from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
    #massSearchReplaceAnyInputTag(process.analyseFullHadronicSelection, 'simpleSecondaryVertexBJetTags', 'simpleSecondaryVertexHighEffBJetTags')

    ## to switch verbosity modes of the kinFit
    #process.ttFullHadEvent.verbosity = 3


## ---
##    remove modules that produce monitoring plots during the cutflow
## ---
def removeMonitoringOfCutflow(process):
    print '++++++++++++++++++++++++++++++++++++++++++++'
    print 'removing all monitoring elements from the '
    print 'sequence *analyseFullHadronicSelection* so'
    print 'only a pure selection of events is done '
    print '++++++++++++++++++++++++++++++++++++++++++++'
    process.analyseFullHadronicSelection.remove(process.monitorKinematics_0)
    process.analyseFullHadronicSelection.remove(process.monitorKinematics_1)
    process.analyseFullHadronicSelection.remove(process.monitorKinematics_2)
    process.analyseFullHadronicSelection.remove(process.monitorKinematics_3)
    process.analyseFullHadronicSelection.remove(process.monitorJetsQuality_0)
    process.analyseFullHadronicSelection.remove(process.monitorJetsQuality_1)
    process.analyseFullHadronicSelection.remove(process.monitorJetsQuality_2)
    process.analyseFullHadronicSelection.remove(process.monitorJetsQuality_3)
    process.analyseFullHadronicSelection.remove(process.monitorEventShapes_0)
    process.analyseFullHadronicSelection.remove(process.monitorEventShapes_1)
    process.analyseFullHadronicSelection.remove(process.monitorEventShapes_2)
    process.analyseFullHadronicSelection.remove(process.monitorEventShapes_3)
    process.analyseFullHadronicSelection.remove(process.monitorFullHadSpecials_0)
    process.analyseFullHadronicSelection.remove(process.monitorFullHadSpecials_1)
    process.analyseFullHadronicSelection.remove(process.monitorFullHadSpecials_2)
    process.analyseFullHadronicSelection.remove(process.monitorFullHadSpecials_3)
    process.analyseFullHadronicSelection.remove(process.monitorGenerator_0)
    process.analyseFullHadronicSelection.remove(process.monitorGenerator_1)
    process.analyseFullHadronicSelection.remove(process.monitorGenerator_2)
    process.analyseFullHadronicSelection.remove(process.monitorGenerator_3)
    process.analyseFullHadronicSelection.remove(process.monitorKinFit_2)
    process.analyseFullHadronicSelection.remove(process.monitorKinFit_3)
    process.analyseFullHadronicSelection.remove(tightBottomJetKinematics_2_v1)
    process.analyseFullHadronicSelection.remove(tightLeadingJetKinematics_2_v1)

## ---
##    remove default trigger
## ---
def removeDefaultTrigger(process):
    print '++++++++++++++++++++++++++++++++++++++++++++'
    print 'removing the default trigger from '
    print 'standard fully hadronic event selection '
    print '++++++++++++++++++++++++++++++++++++++++++++'
    process.analyseFullHadronicSelection.remove(process.trigger)
    
## ---
##    switch all necessary filters to run this sequence for background estimation
## ---
def runAsBackgroundEstimation(process):
    print '++++++++++++++++++++++++++++++++++++++++++++'
    print 'switching *analyseFullHadronicSelection* to'
    print 'background estimation'
    print '++++++++++++++++++++++++++++++++++++++++++++'
    process.tightBottomJetSelection_v1.minNumber = 0
    process.tightBottomJetSelection_v1.maxNumber = 0
    process.tightBottomJetSelection_v2.minNumber = 0
    process.tightBottomJetSelection_v2.maxNumber = 0
    process.kinFitTtFullHadEventHypothesis.bTags = 0

## ---
##    run analysis on PFJets instead of caloJets
## ---
def runOnPF(process):
    print '++++++++++++++++++++++++++++++++++++++++++++'
    print 'switching all inputs in to run on PFlow'
    print 'goodJets -> goodJetsPF'
    print 'patMETs  -> patMETsPF'
    print '++++++++++++++++++++++++++++++++++++++++++++'
    process.analyseFullHadronicSelection.replace(process.goodJets, process.goodJetsPF)

    ## exchange JetID cuts to PFJetID
    process.tightLeadingJets.cut = tightJetCut + tightPFJetID
    process.tightBottomJets.cut  = tightJetCut + tightPFJetID
    process.monitoredTightBottomJets.cut = tightJetCut + tightPFJetID

    ## exchange resolutions for PFJets
    process.load("TopQuarkAnalysis.TopObjectResolutions.stringResolutions_etEtaPhi_cff")
    process.kinFitTtFullHadEventHypothesis.udscResolutions = process.udscResolutionPF.functions
    process.kinFitTtFullHadEventHypothesis.bResolutions    = process.bjetResolutionPF.functions

    process.kinFitQuality_2.analyze.udscResolutions        = process.udscResolutionPF.functions
    process.kinFitQuality_2.analyze.bResolutions           = process.bjetResolutionPF.functions
    process.kinFitQuality_3.analyze.udscResolutions        = process.udscResolutionPF.functions
    process.kinFitQuality_3.analyze.bResolutions           = process.bjetResolutionPF.functions

    ## run kinematic fit for PFJets with L2L3 correted jets, as no further corrections are available
    process.kinFitTtFullHadEventHypothesis.jetCorrectionLevel = 'L3Absolute'
    process.ttFullHadHypGenMatch.jetCorrectionLevel           = 'L3Absolute'

    ## replace jets and met with PFJets and PFMET
    from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
    massSearchReplaceAnyInputTag(process.analyseFullHadronicSelection, 'goodJets', 'goodJetsPF')
    massSearchReplaceAnyInputTag(process.analyseFullHadronicSelection, 'patMETs' , 'patMETsPF')

    ## in case of real data, do residual JEC for PFJets
    #if(hasattr(process, 'residualCorrectedJets')):
    #    process.residualCorrectedJets.jets        = 'selectedPatJetsAK5PF'
    #    process.residualCorrectedJets.corrections = 'Spring10DataV2_L2L3Residual_AK5PF.txt'

    # in case of mc, smear the energy resolution additionally
    if(hasattr(process, 'scaledJetEnergy')):
        process.scaledJetEnergy.inputJets = "selectedPatJetsAK5PF"
        process.scaledJetEnergy.inputMETs = "patMETsPF"
        process.scaledJetEnergy.payload   = "AK5PF"

## ---
##    switch to trackCountingHighEfficiency bTagger
## ---
def switchToTCHE(process):
    process.analyseFullHadronicSelection.replace(process.trackCountingHighPurBJets, process.trackCountingHighEffBJets)
    process.kinFitTtFullHadEventHypothesis.bTagAlgo = 'trackCountingHighEffBJetTags'
    process.fullHadTopReco_2.analyze.bTagAlgo       = 'trackCountingHighEffBJetTags' 
    process.fullHadTopReco_3.analyze.bTagAlgo       = 'trackCountingHighEffBJetTags' 
    process.kinFitTtFullHadEventHypothesis.minBTagValueBJet    = 3.3
    process.kinFitTtFullHadEventHypothesis.maxBTagValueNonBJet = 10.2
    from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
    massSearchReplaceAnyInputTag(process.analyseFullHadronicSelection, 'trackCountingHighPurBJets', 'trackCountingHighEffBJets')

## ---
##    switch to trackCountingHighEfficiency bTagger
## ---
def switchToTCHPTight(process):
    #process.analyseFullHadronicSelection.replace(process.trackCountingHighPurBJets, process.trackCountingHighEffBJets)
    process.trackCountingHighPurBJets.cut = 'bDiscriminator(\"trackCountingHighPurBJetTags\") > 3.41'

    process.kinFitTtFullHadEventHypothesis.bTagAlgo = 'trackCountingHighPurBJetTags'
    process.fullHadTopReco_2.analyze.bTagAlgo       = 'trackCountingHighPurBJetTags' 
    process.fullHadTopReco_3.analyze.bTagAlgo       = 'trackCountingHighPurBJetTags' 
    process.kinFitTtFullHadEventHypothesis.minBTagValueBJet    = 3.41
    process.kinFitTtFullHadEventHypothesis.maxBTagValueNonBJet = 3.41
    #from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
    #massSearchReplaceAnyInputTag(process.analyseFullHadronicSelection, 'trackCountingHighPurBJets', 'trackCountingHighEffBJets')

## ---
##    switch to simpleSecondaryVertex bTagger
## ---
def switchToSSV(process):
    process.analyseFullHadronicSelection.replace(process.trackCountingHighPurBJets, process.simpleSecondaryVertexBJets)
    process.kinFitTtFullHadEventHypothesis.bTagAlgo = 'simpleSecondaryVertexBJetTags'
    process.fullHadTopReco_2.analyze.bTagAlgo       = 'simpleSecondaryVertexBJetTags' 
    process.fullHadTopReco_3.analyze.bTagAlgo       = 'simpleSecondaryVertexBJetTags' 
    process.kinFitTtFullHadEventHypothesis.minBTagValueBJet    = 1.74
    process.kinFitTtFullHadEventHypothesis.maxBTagValueNonBJet = 3.05
    from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
    massSearchReplaceAnyInputTag(process.analyseFullHadronicSelection, 'trackCountingHighPurBJets', 'simpleSecondaryVertexBJets')

## ---
##    switch to combinedSecondaryVertex bTagger
## ---
def switchToCSV(process):
    process.analyseFullHadronicSelection.replace(process.trackCountingHighPurBJets, process.combinedSecondaryVertexBJets)
    process.kinFitTtFullHadEventHypothesis.bTagAlgo = 'combinedSecondaryVertexBJetTags'
    process.fullHadTopReco_2.analyze.bTagAlgo       = 'combinedSecondaryVertexBJetTags' 
    process.fullHadTopReco_3.analyze.bTagAlgo       = 'combinedSecondaryVertexBJetTags' 
    process.kinFitTtFullHadEventHypothesis.minBTagValueBJet    = 0.750
    process.kinFitTtFullHadEventHypothesis.maxBTagValueNonBJet = 0.921
    from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
    massSearchReplaceAnyInputTag(process.analyseFullHadronicSelection, 'trackCountingHighPurBJets', 'combinedSecondaryVertexBJets')

## ---
##    switch to combinedSecondaryVertexMVA bTagger
## ---
def switchToCSVMVA(process):
    process.analyseFullHadronicSelection.replace(process.trackCountingHighPurBJets, process.combinedSecondaryVertexMVABJets)
    process.kinFitTtFullHadEventHypothesis.bTagAlgo = 'combinedSecondaryVertexMVABJetTags'
    process.fullHadTopReco_2.analyze.bTagAlgo       = 'combinedSecondaryVertexMVABJetTags' 
    process.fullHadTopReco_3.analyze.bTagAlgo       = 'combinedSecondaryVertexMVABJetTags' 
    process.kinFitTtFullHadEventHypothesis.minBTagValueBJet    = 0.4 #self-derived
    process.kinFitTtFullHadEventHypothesis.maxBTagValueNonBJet = 0.8 #self-derived
    from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
    massSearchReplaceAnyInputTag(process.analyseFullHadronicSelection, 'trackCountingHighPurBJets', 'combinedSecondaryVertexMVABJets')

## ---
##    increase resolutions of kinematic fit
## ---
def increaseKinFitResolution(process, factor):
    process.kinFitTtFullHadEventHypothesis.energyResolutionSmearFactor = factor

## ---
##    remove PDF uncertainty histograms / trees
## ---
def removePDFUncertainties(process):
    process.analyseFullHadronicSelection.remove(process.PDFUncertainty_0)
    process.analyseFullHadronicSelection.remove(process.PDFUncertainty_3)

