import FWCore.ParameterSet.Config as cms

#
# simple study on different event hypotheses
#

from TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff        import *
from TopQuarkAnalysis.TopEventProducers.sequences.ttGenEventFilters_cff import *
from TopQuarkAnalysis.TopTools.TtSemiLepJetPartonMatch_cfi              import ttSemiLepJetPartonMatch
## clone module for the analyses of the different event hypotheses
totalMinDist     = ttSemiLepJetPartonMatch.clone()
minSumDist       = ttSemiLepJetPartonMatch.clone()
ptOrderedMinDist = ttSemiLepJetPartonMatch.clone()
unambiguousOnly  = ttSemiLepJetPartonMatch.clone()  

## replacements
# totalMinDist, minSumDist, ptOrderedMinDist, unambiguousOnly
totalMinDist.algorithm     = "totalMinDist"
minSumDist.algorithm       = "minSumDist"
ptOrderedMinDist.algorithm = "ptOrderedMinDist"
unambiguousOnly.algorithm  = "unambiguousOnly"

from TopAnalysis.TopAnalyzer.PartonMatchAnalyzer_cfi import *

## reconfigure
analyzePartonMatch.matches  = ['totalMinDist', 'minSumDist', 'ptOrderedMinDist', 'unambiguousOnly']
analyzePartonMatch.sumDR    = 'totalMinDist:SumDR'
analyzePartonMatch.sumDPt   = 'totalMinDist:SumPt' 
analyzePartonMatch.quarks   = []
analyzePartonMatch.jets     = []
analyzePartonMatch.ref      = 0

## define sequence
makePartonMatches = cms.Sequence(makeGenEvt           *
                                 ttSemiLeptonicFilter +
                                 totalMinDist         +
                                 minSumDist           +
                                 ptOrderedMinDist     +
                                 unambiguousOnly
                                 )

makePartonMatchAnalysis = cms.Sequence(makePartonMatches *
                                       analyzePartonMatch
                                       )


 
