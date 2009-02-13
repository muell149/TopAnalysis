import FWCore.ParameterSet.Config as cms

from TopAnalysis.TopAnalyzer.FullLepHypothesesAnalyzer_cfi import analyzeFullLepHypotheses
## clone module
analyzeKinFit   = analyzeFullLepHypotheses.clone()
analyzeGenMatch = analyzeFullLepHypotheses.clone()

## do replacements
analyzeKinFit.hypoKey    = 'ttFullLepHypKinFit:Key'
analyzeGenMatch.hypoKey  = 'ttFullLepHypGenMatch:Key'

analyzeAllFullLepHypotheses = cms.Sequence(#analyzeKinFit   +
                                           analyzeGenMatch     
                                          )



