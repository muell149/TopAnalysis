import FWCore.ParameterSet.Config as cms

from TopQuarkAnalysis.TopEventProducers.sequences.ttSemiLepEvtBuilder_cff import *

from TopAnalysis.TopAnalyzer.JetEnergyCorrectionsAnalyzer_cfi import *

##########################################################################################
## configure recJet-parton matching
##########################################################################################

ttSemiLepJetPartonMatch.jets       = 'goodJets'
ttSemiLepJetPartonMatch.algorithm  = 'unambiguousOnly'
ttSemiLepJetPartonMatch.useMaxDist = True
ttSemiLepJetPartonMatch.maxDist    = 0.5
ttSemiLepJetPartonMatch.maxNJets   = -1

##########################################################################################
## configure genJet-parton matching
##########################################################################################

ttSemiLepGenJetPartonMatch            = ttSemiLepJetPartonMatch.clone()
ttSemiLepGenJetPartonMatch.jets       = "antikt5GenJets"
ttSemiLepGenJetPartonMatch.algorithm  = "unambiguousOnly"
ttSemiLepGenJetPartonMatch.useMaxDist = True
ttSemiLepGenJetPartonMatch.maxDist    = 0.5
ttSemiLepGenJetPartonMatch.maxNJets   = -1

##########################################################################################
## produce genMatch hypothesis for different jet energy correction levels
##########################################################################################

ttSemiLepHypGenMatchRaw  = ttSemiLepHypGenMatch.clone(jetCorrectionLevel = "raw" )
ttSemiLepHypGenMatchOff  = ttSemiLepHypGenMatch.clone(jetCorrectionLevel = "off" ) ## L1
ttSemiLepHypGenMatchRel  = ttSemiLepHypGenMatch.clone(jetCorrectionLevel = "rel" ) ## L2
ttSemiLepHypGenMatchAbs  = ttSemiLepHypGenMatch.clone(jetCorrectionLevel = "abs" ) ## L3
ttSemiLepHypGenMatchEmf  = ttSemiLepHypGenMatch.clone(jetCorrectionLevel = "emf" ) ## L4
ttSemiLepHypGenMatchHad  = ttSemiLepHypGenMatch.clone(jetCorrectionLevel = "had" ) ## L5
ttSemiLepHypGenMatchUe   = ttSemiLepHypGenMatch.clone(jetCorrectionLevel = "ue"  ) ## L6
ttSemiLepHypGenMatchPart = ttSemiLepHypGenMatch.clone(jetCorrectionLevel = "part") ## L7

ttSemiLepHypGenMatch_multilevel = cms.Sequence(ttSemiLepHypGenMatchRaw  *
                                               ttSemiLepHypGenMatchOff  *
                                               ttSemiLepHypGenMatchRel  *
                                               ttSemiLepHypGenMatchAbs  *
                                               ttSemiLepHypGenMatchEmf  *
                                               ttSemiLepHypGenMatchHad  *
                                               ttSemiLepHypGenMatchUe   *
                                               ttSemiLepHypGenMatchPart
                                               )

##########################################################################################
## produce ttSemiLeptonicEvent for different jet energy correction levels
##########################################################################################

ttSemiLepEventRaw  = ttSemiLepEvent.clone(hypotheses = ["ttSemiLepHypGenMatchRaw" ])
ttSemiLepEventOff  = ttSemiLepEvent.clone(hypotheses = ["ttSemiLepHypGenMatchOff" ]) ## L1
ttSemiLepEventRel  = ttSemiLepEvent.clone(hypotheses = ["ttSemiLepHypGenMatchRel" ]) ## L2
ttSemiLepEventAbs  = ttSemiLepEvent.clone(hypotheses = ["ttSemiLepHypGenMatchAbs" ]) ## L3
ttSemiLepEventEmf  = ttSemiLepEvent.clone(hypotheses = ["ttSemiLepHypGenMatchEmf" ]) ## L4
ttSemiLepEventHad  = ttSemiLepEvent.clone(hypotheses = ["ttSemiLepHypGenMatchHad" ]) ## L5
ttSemiLepEventUe   = ttSemiLepEvent.clone(hypotheses = ["ttSemiLepHypGenMatchUe"  ]) ## L6
ttSemiLepEventPart = ttSemiLepEvent.clone(hypotheses = ["ttSemiLepHypGenMatchPart"]) ## L7

ttSemiLepEvent_multilevel = cms.Sequence(ttSemiLepEventRaw  *
                                         ttSemiLepEventOff  *
                                         ttSemiLepEventRel  *
                                         ttSemiLepEventAbs  *
                                         ttSemiLepEventEmf  *
                                         ttSemiLepEventHad  *
                                         ttSemiLepEventUe   *
                                         ttSemiLepEventPart
                                         )

##########################################################################################
## analyze ttSemiLeptonicEvent for different jet energy correction levels
##########################################################################################

analyzeJetEnergyCorrections_raw  = analyzeJetEnergyCorrections.clone(semiLepEvt = "ttSemiLepEventRaw" )
analyzeJetEnergyCorrections_off  = analyzeJetEnergyCorrections.clone(semiLepEvt = "ttSemiLepEventOff" ) ## L1
analyzeJetEnergyCorrections_rel  = analyzeJetEnergyCorrections.clone(semiLepEvt = "ttSemiLepEventRel" ) ## L2
analyzeJetEnergyCorrections_abs  = analyzeJetEnergyCorrections.clone(semiLepEvt = "ttSemiLepEventAbs" ) ## L3
analyzeJetEnergyCorrections_emf  = analyzeJetEnergyCorrections.clone(semiLepEvt = "ttSemiLepEventEmf" ) ## L4
analyzeJetEnergyCorrections_had  = analyzeJetEnergyCorrections.clone(semiLepEvt = "ttSemiLepEventHad" ) ## L5
analyzeJetEnergyCorrections_ue   = analyzeJetEnergyCorrections.clone(semiLepEvt = "ttSemiLepEventUe"  ) ## L6
analyzeJetEnergyCorrections_part = analyzeJetEnergyCorrections.clone(semiLepEvt = "ttSemiLepEventPart") ## L7

analyzeJetEnergyCorrections_multilevel = cms.Sequence(analyzeJetEnergyCorrections_raw  *
                                                      analyzeJetEnergyCorrections_off  *
                                                      analyzeJetEnergyCorrections_rel  *
                                                      analyzeJetEnergyCorrections_abs  *
                                                      analyzeJetEnergyCorrections_emf  *
                                                      analyzeJetEnergyCorrections_had  *
                                                      analyzeJetEnergyCorrections_ue   *
                                                      analyzeJetEnergyCorrections_part
                                                      )

##########################################################################################
## bundle everything into one sequence
##########################################################################################

makeJetEnergyCorrectionsAnalysis = cms.Sequence(ttSemiLepJetPartonMatch *
                                                ttSemiLepGenJetPartonMatch *
                                                ttSemiLepHypGenMatch_multilevel *
                                                ttSemiLepEvent_multilevel *
                                                analyzeJetEnergyCorrections_multilevel
                                                )
                                                
