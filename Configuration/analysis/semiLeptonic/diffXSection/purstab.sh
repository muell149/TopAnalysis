#!/bin/sh

 decayChannel=\"muon\"
#decayChannel=\"electron\"  
inputFolderName=\"RecentAnalysisRun\"

# Array of differential variables:
# number of variables:
num=1
#   listVar_=( \"topPt\" \"topY\" \"ttbarPt\" \"ttbarY\" \"ttbarMass\" \"lepPt\" \"lepEta\" \"bqPt\" \"bqEta\")
# listVar_=( \"topPt\" )
listVar_=( \"bqPt\" )

# listVar_=( \"lepPt\" \"lepEta\" \"bqPt\" \"bqEta\")

# Array of relevant chi2 cuts:
listChi2_=( 99999 50 30 15 10 5 3 1 )

    for (( iVar=0; iVar<$num; iVar++ ))
      do
      echo
      echo purity and stability for: ${listVar_[$iVar]}
      echo
#      for (( iChi2=0; iChi2<8; iChi2++ ))
#	do
# 	echo
# 	echo "chi2<"${listChi2_[$iChi2]}
# 	echo
# 	root -l -q -b './purityStabilityEfficiency.C++('${listVar_[$iVar]}', true, '$decayChannel', '$inputFolderName', true, true, false, '${listChi2_[$iChi2]}')'
## For parton level:
# root -l -q -b './purityStabilityEfficiency.C++('${listVar_[$iVar]}', true, '$decayChannel', '$inputFolderName', true, true, false)'
## For hadron level:
          root -l -q -b './purityStabilityEfficiency.C++('${listVar_[$iVar]}', true, '$decayChannel', '$inputFolderName', true, true, false, 99999, 0, true)'
#	done
    done
      