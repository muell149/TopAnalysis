#!/bin/sh

#LIST="default
#      tauola
#      looseSelection
#      tightSelection
#      4jets
#      6jets
#      minSumDist
#      minSumDist_rejectOutliers
#      totalMinDist
#      totalMinDist_rejectOutliers
#      ptOrderedMinDist
#      ptOrderedMinDist_rejectOutliers
#      electrons"

LIST="default
      electrons"

for NAME in $LIST
  do
  crab -create -cfg TopAnalysis/Configuration/analysis/semiLeptonic/jetCombMVA/trainTreeSaver_$NAME.cfg -submit 1-40
done
