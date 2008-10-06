import FWCore.ParameterSet.Config as cms

#
# simple study on different event hypotheses
#

from TopAnalysis.TopAnalyzer.SemiLepHypothesesAnalyzer_cfi import analyzeSemiLepHypotheses

## clone module for the analyses of the different event hypotheses
analyzeGeom                  = analyzeSemiLepHypotheses.clone()
analyzeWMassMaxSumPt         = analyzeSemiLepHypotheses.clone()
analyzeMaxSumPtWMass         = analyzeSemiLepHypotheses.clone()
analyzeKinFit                = analyzeSemiLepHypotheses.clone()
analyzeGenMatch              = analyzeSemiLepHypotheses.clone()
analyzeMVADisc               = analyzeSemiLepHypotheses.clone()

## reconfigure
analyzeGeom.hypoKey          = 'ttSemiLepHypGeom:Key'
analyzeWMassMaxSumPt.hypoKey = 'ttSemiLepHypWMassMaxSumPt:Key'
analyzeMaxSumPtWMass.hypoKey = 'ttSemiLepHypMaxSumPtWMass:Key'
analyzeKinFit.hypoKey        = 'ttSemiLepHypKinFit:Key'
analyzeGenMatch.hypoKey      = 'ttSemiLepHypGenMatch:Key'
analyzeMVADisc.hypoKey       = 'ttSemiLepHypMVADisc:Key'

## define sequence
makeAllSemiLepHypothesesAnalysis = cms.Sequence(analyzeGeom          *
                                                analyzeWMassMaxSumPt *
                                                analyzeMaxSumPtWMass *
                                                analyzeKinFit        *
                                                analyzeGenMatch      *
                                                analyzeMVADisc
                                                )
