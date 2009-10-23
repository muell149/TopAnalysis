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
## produce geom hypothesis for different jet energy correction levels
##########################################################################################

ttSemiLepHypGeomRaw  = ttSemiLepHypGeom.clone(useBTagging = True, jetCorrectionLevel = "raw" )
ttSemiLepHypGeomOff  = ttSemiLepHypGeom.clone(useBTagging = True, jetCorrectionLevel = "off" ) ## L1
ttSemiLepHypGeomRel  = ttSemiLepHypGeom.clone(useBTagging = True, jetCorrectionLevel = "rel" ) ## L2
ttSemiLepHypGeomAbs  = ttSemiLepHypGeom.clone(useBTagging = True, jetCorrectionLevel = "abs" ) ## L3
ttSemiLepHypGeomEmf  = ttSemiLepHypGeom.clone(useBTagging = True, jetCorrectionLevel = "emf" ) ## L4
ttSemiLepHypGeomHad  = ttSemiLepHypGeom.clone(useBTagging = True, jetCorrectionLevel = "had" ) ## L5
ttSemiLepHypGeomUe   = ttSemiLepHypGeom.clone(useBTagging = True, jetCorrectionLevel = "ue"  ) ## L6
ttSemiLepHypGeomPart = ttSemiLepHypGeom.clone(useBTagging = True, jetCorrectionLevel = "part") ## L7

ttSemiLepHypGeomRaw .minBDiscBJets = 1.90
ttSemiLepHypGeomOff .minBDiscBJets = 1.90
ttSemiLepHypGeomRel .minBDiscBJets = 1.90
ttSemiLepHypGeomAbs .minBDiscBJets = 1.90
ttSemiLepHypGeomEmf .minBDiscBJets = 1.90
ttSemiLepHypGeomHad .minBDiscBJets = 1.90
ttSemiLepHypGeomUe  .minBDiscBJets = 1.90
ttSemiLepHypGeomPart.minBDiscBJets = 1.90

ttSemiLepHypGeomRaw .maxBDiscLightJets = 3.99
ttSemiLepHypGeomOff .maxBDiscLightJets = 3.99
ttSemiLepHypGeomRel .maxBDiscLightJets = 3.99
ttSemiLepHypGeomAbs .maxBDiscLightJets = 3.99
ttSemiLepHypGeomEmf .maxBDiscLightJets = 3.99
ttSemiLepHypGeomHad .maxBDiscLightJets = 3.99
ttSemiLepHypGeomUe  .maxBDiscLightJets = 3.99
ttSemiLepHypGeomPart.maxBDiscLightJets = 3.99

ttSemiLepHypGeom_multilevel = cms.Sequence(ttSemiLepHypGeomRaw  *
                                           ttSemiLepHypGeomOff  *
                                           ttSemiLepHypGeomRel  *
                                           ttSemiLepHypGeomAbs  *
                                           ttSemiLepHypGeomEmf  *
                                           ttSemiLepHypGeomHad  *
                                           ttSemiLepHypGeomUe   *
                                           ttSemiLepHypGeomPart
                                           )

##########################################################################################
## produce ttSemiLeptonicEvent for different jet energy correction levels
##########################################################################################

ttSemiLepEventRaw  = ttSemiLepEvent.clone(hypotheses = ["ttSemiLepHypGenMatchRaw" , "ttSemiLepHypGeomRaw" ])
ttSemiLepEventOff  = ttSemiLepEvent.clone(hypotheses = ["ttSemiLepHypGenMatchOff" , "ttSemiLepHypGeomOff" ]) ## L1
ttSemiLepEventRel  = ttSemiLepEvent.clone(hypotheses = ["ttSemiLepHypGenMatchRel" , "ttSemiLepHypGeomRel" ]) ## L2
ttSemiLepEventAbs  = ttSemiLepEvent.clone(hypotheses = ["ttSemiLepHypGenMatchAbs" , "ttSemiLepHypGeomAbs" ]) ## L3
ttSemiLepEventEmf  = ttSemiLepEvent.clone(hypotheses = ["ttSemiLepHypGenMatchEmf" , "ttSemiLepHypGeomEmf" ]) ## L4
ttSemiLepEventHad  = ttSemiLepEvent.clone(hypotheses = ["ttSemiLepHypGenMatchHad" , "ttSemiLepHypGeomHad" ]) ## L5
ttSemiLepEventUe   = ttSemiLepEvent.clone(hypotheses = ["ttSemiLepHypGenMatchUe"  , "ttSemiLepHypGeomUe"  ]) ## L6
ttSemiLepEventPart = ttSemiLepEvent.clone(hypotheses = ["ttSemiLepHypGenMatchPart", "ttSemiLepHypGeomPart"]) ## L7

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
## analyze genMatch hypothesis for different jet energy correction levels
##########################################################################################

analyzeJetEnergyGenMatch_raw  = analyzeJetEnergyCorrections.clone(semiLepEvt = "ttSemiLepEventRaw" , hypoKey = "kGenMatch")
analyzeJetEnergyGenMatch_off  = analyzeJetEnergyCorrections.clone(semiLepEvt = "ttSemiLepEventOff" , hypoKey = "kGenMatch") ## L1
analyzeJetEnergyGenMatch_rel  = analyzeJetEnergyCorrections.clone(semiLepEvt = "ttSemiLepEventRel" , hypoKey = "kGenMatch") ## L2
analyzeJetEnergyGenMatch_abs  = analyzeJetEnergyCorrections.clone(semiLepEvt = "ttSemiLepEventAbs" , hypoKey = "kGenMatch") ## L3
analyzeJetEnergyGenMatch_emf  = analyzeJetEnergyCorrections.clone(semiLepEvt = "ttSemiLepEventEmf" , hypoKey = "kGenMatch") ## L4
analyzeJetEnergyGenMatch_had  = analyzeJetEnergyCorrections.clone(semiLepEvt = "ttSemiLepEventHad" , hypoKey = "kGenMatch") ## L5
analyzeJetEnergyGenMatch_ue   = analyzeJetEnergyCorrections.clone(semiLepEvt = "ttSemiLepEventUe"  , hypoKey = "kGenMatch") ## L6
analyzeJetEnergyGenMatch_part = analyzeJetEnergyCorrections.clone(semiLepEvt = "ttSemiLepEventPart", hypoKey = "kGenMatch") ## L7

analyzeJetEnergyGenMatch_multilevel = cms.Sequence(analyzeJetEnergyGenMatch_raw  *
                                                   analyzeJetEnergyGenMatch_off  *
                                                   analyzeJetEnergyGenMatch_rel  *
                                                   analyzeJetEnergyGenMatch_abs  *
                                                   analyzeJetEnergyGenMatch_emf  *
                                                   analyzeJetEnergyGenMatch_had  *
                                                   analyzeJetEnergyGenMatch_ue   *
                                                   analyzeJetEnergyGenMatch_part
                                                   )

##########################################################################################
## analyze geom hypothesis for different jet energy correction levels
##########################################################################################

analyzeJetEnergyGeom_raw  = analyzeJetEnergyCorrections.clone(semiLepEvt = "ttSemiLepEventRaw" , hypoKey = "kGeom")
analyzeJetEnergyGeom_off  = analyzeJetEnergyCorrections.clone(semiLepEvt = "ttSemiLepEventOff" , hypoKey = "kGeom") ## L1
analyzeJetEnergyGeom_rel  = analyzeJetEnergyCorrections.clone(semiLepEvt = "ttSemiLepEventRel" , hypoKey = "kGeom") ## L2
analyzeJetEnergyGeom_abs  = analyzeJetEnergyCorrections.clone(semiLepEvt = "ttSemiLepEventAbs" , hypoKey = "kGeom") ## L3
analyzeJetEnergyGeom_emf  = analyzeJetEnergyCorrections.clone(semiLepEvt = "ttSemiLepEventEmf" , hypoKey = "kGeom") ## L4
analyzeJetEnergyGeom_had  = analyzeJetEnergyCorrections.clone(semiLepEvt = "ttSemiLepEventHad" , hypoKey = "kGeom") ## L5
analyzeJetEnergyGeom_ue   = analyzeJetEnergyCorrections.clone(semiLepEvt = "ttSemiLepEventUe"  , hypoKey = "kGeom") ## L6
analyzeJetEnergyGeom_part = analyzeJetEnergyCorrections.clone(semiLepEvt = "ttSemiLepEventPart", hypoKey = "kGeom") ## L7

analyzeJetEnergyGeom_multilevel = cms.Sequence(analyzeJetEnergyGeom_raw  *
                                               analyzeJetEnergyGeom_off  *
                                               analyzeJetEnergyGeom_rel  *
                                               analyzeJetEnergyGeom_abs  *
                                               analyzeJetEnergyGeom_emf  *
                                               analyzeJetEnergyGeom_had  *
                                               analyzeJetEnergyGeom_ue   *
                                               analyzeJetEnergyGeom_part
                                               )

##########################################################################################
## bundle everything into one sequence
##########################################################################################

makeHypGenMatch = cms.Sequence(ttSemiLepJetPartonMatch *
                               ttSemiLepGenJetPartonMatch *
                               ttSemiLepHypGenMatch_multilevel)

makeJetEnergyCorrectionsAnalysis = cms.Sequence(makeHypGenMatch *
                                                ttSemiLepHypGeom_multilevel *
                                                ttSemiLepEvent_multilevel *
                                                analyzeJetEnergyGenMatch_multilevel *
                                                analyzeJetEnergyGeom_multilevel
                                                )
                                                
