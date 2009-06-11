import FWCore.ParameterSet.Config as cms

from TopAnalysis.TopAnalyzer.SemiLepHypothesesAnalyzerBSM_cfi import analyzeSemiLepHypothesesBSM
## clone module
analyzeGeom          = analyzeSemiLepHypothesesBSM.clone()
analyzeWMassMaxSumPt = analyzeSemiLepHypothesesBSM.clone()
analyzeMaxSumPtWMass = analyzeSemiLepHypothesesBSM.clone()
analyzeKinFit        = analyzeSemiLepHypothesesBSM.clone()
analyzeGenMatch      = analyzeSemiLepHypothesesBSM.clone()
analyzeMVADisc       = analyzeSemiLepHypothesesBSM.clone()

## do replacements
analyzeGeom.hypoClassKey          = 'ttSemiLepHypGeom:Key'
analyzeWMassMaxSumPt.hypoClassKey = 'ttSemiLepHypWMassMaxSumPt:Key'
analyzeMaxSumPtWMass.hypoClassKey = 'ttSemiLepHypMaxSumPtWMass:Key'
analyzeKinFit.hypoClassKey        = 'ttSemiLepHypKinFit:Key'
analyzeGenMatch.hypoClassKey      = 'ttSemiLepHypGenMatch:Key'
analyzeMVADisc.hypoClassKey       = 'ttSemiLepHypMVADisc:Key'

analyzeAllSemiLepHypothesesBSM = cms.Sequence(analyzeGeom          +
                                              analyzeWMassMaxSumPt +
                                              analyzeMaxSumPtWMass +
                                              analyzeKinFit        +
                                              ##analyzeGenMatch      +
                                              analyzeMVADisc
                                              )



