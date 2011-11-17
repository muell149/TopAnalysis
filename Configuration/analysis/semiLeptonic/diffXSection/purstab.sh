#!/bin/sh

decayChannel=\"muon\" 
inputFolderName=\"TOP2011/110819_AnalysisRun\"

# Array of differential variables:
listVar_=( \"topPt\" \"topY\" \"ttbarPt\" \"ttbarY\" \"ttbarMass\" \"lepPt\" \"lepEta\" )

# Array of relevant chi2 cuts:
listChi2_=( 99999 50 30 15 10 5 3 1 )

    for (( iVar=0; iVar<7; iVar++ ))
      do
      echo
      echo purity and stability for: ${listVar_[$iVar]}
      echo
      for (( iChi2=0; iChi2<8; iChi2++ ))
	do
	echo
	echo "chi2<"${listChi2_[$iChi2]}
	echo
	root -l -q -b './purityStabilityEfficiency.C++('${listVar_[$iVar]}', true, '$decayChannel', '$inputFolderName', true, true, false, '${listChi2_[$iChi2]}')'
	done
    done
      