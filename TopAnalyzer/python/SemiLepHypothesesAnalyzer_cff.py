import FWCore.ParameterSet.Config as cms

from TopAnalysis.TopAnalyzer.SemiLepHypothesesAnalyzer_cfi import analyzeSemiLepHypotheses
## clone module
analyzeGeom          = analyzeSemiLepHypotheses.clone()
analyzeWMassMaxSumPt = analyzeSemiLepHypotheses.clone()
analyzeMaxSumPtWMass = analyzeSemiLepHypotheses.clone()
analyzeKinFit        = analyzeSemiLepHypotheses.clone()
analyzeGenMatch      = analyzeSemiLepHypotheses.clone()
analyzeMVADisc       = analyzeSemiLepHypotheses.clone()

## do replacements
analyzeGeom.hypoClassKey          = 'ttSemiLepHypGeom:Key'
analyzeWMassMaxSumPt.hypoClassKey = 'ttSemiLepHypWMassMaxSumPt:Key'
analyzeMaxSumPtWMass.hypoClassKey = 'ttSemiLepHypMaxSumPtWMass:Key'
analyzeKinFit.hypoClassKey        = 'ttSemiLepHypKinFit:Key'
analyzeGenMatch.hypoClassKey      = 'ttSemiLepHypGenMatch:Key'
analyzeMVADisc.hypoClassKey       = 'ttSemiLepHypMVADisc:Key'

analyzeAllSemiLepHypotheses = cms.Sequence(analyzeGeom          +
                                           analyzeWMassMaxSumPt +
                                           analyzeMaxSumPtWMass +
                                           analyzeKinFit        +
                                           analyzeGenMatch      +
                                           analyzeMVADisc
                                           )



