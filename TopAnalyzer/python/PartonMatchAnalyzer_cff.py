import FWCore.ParameterSet.Config as cms

#
# simple study on different jet parton match algorithms
#

from TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff        import *
from TopQuarkAnalysis.TopEventProducers.sequences.ttGenEventFilters_cff import *

from TopAnalysis.TopAnalyzer.PartonMatchAnalyzer_cfi                    import analyzePartonMatch
from TopQuarkAnalysis.TopTools.TtSemiLepJetPartonMatch_cfi              import ttSemiLepJetPartonMatch


## clone module for jet parton matching

totalMinDist     = ttSemiLepJetPartonMatch.clone()
minSumDist       = ttSemiLepJetPartonMatch.clone()
ptOrderedMinDist = ttSemiLepJetPartonMatch.clone()
unambiguousOnly  = ttSemiLepJetPartonMatch.clone()

## reconfigure
totalMinDist.algorithm      = 0
minSumDist.algorithm        = 1
ptOrderedMinDist.algorithm  = 2
unambiguousOnly.algorithm   = 3

## analyze different jat parton match configurations

analyzePartonMatch.matches  = [totalMinDist, minSumDist, ptOrderedMinDist, unambiguousOnly]
analyzePartonMatch.sumDR    = 'totalMinDist:SumDR'
analyzePartonMatch.sumDPt   = 'totalMinDist:SumPt'
analyzePartonMatch.quarks   = []
analyzePartonMatch.jets     = []
analyzePartonMatch.ref      = 0

## define sequences
makePartonMatches = cms.Sequence(makeGenEvt           *
                                 ttSemiLeptonicFilter *
                                 totalMinDist         *
                                 minSumDist           *
                                 ptOrderedMinDist     *
                                 unambiguousOnly
                                 )

makePartonMatchAnalysis = cms.Sequence(makePartonMatches *
                                       analyzePartonMatch
                                       )
