import FWCore.ParameterSet.Config as cms

from TopAnalysis.TopAnalyzer.FullLepHypothesesAnalyzerBSM_cfi import analyzeFullLepHypothesesBSM
## clone module
analyzeKinSolution = analyzeFullLepHypothesesBSM.clone()
analyzeGenMatch    = analyzeFullLepHypothesesBSM.clone()

## do replacements
analyzeKinSolution.hypoKey = 'ttFullLepHypKinSolution:Key'
analyzeGenMatch.hypoKey    = 'ttFullLepHypGenMatch:Key'

analyzeAllFullLepHypothesesBSM = cms.Sequence(analyzeGenMatch +
                                           analyzeKinSolution     
                                          )



