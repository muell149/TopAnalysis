import FWCore.ParameterSet.Config as cms

#
# make simple analysis plots for a comparison
# between a simple algorithmic and a gen match
# based event hypothesis
#

# initialize analyzers
from TopAnalysis.TopAnalyzer.FullHadHypothesisAnalyzer_cfi import *
analyzeGenMatch      = analyzeHypothesis.clone()
analyzeKinFit        = analyzeHypothesis.clone()

# configure analyzers
analyzeGenMatch.hypoClassKey      = "ttFullHadHypGenMatch:Key"
analyzeKinFit.hypoClassKey        = "ttFullHadHypKinFit:Key"

# define sequence
analyzeHypotheses = cms.Sequence(analyzeGenMatch *
                                 analyzeKinFit)

