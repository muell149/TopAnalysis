#!/bin/sh

## this shell script runs all macro parts of the 2011 differential cross section analysis 

## HOW TO USE THIS SHELL SCRIPT
## note: has to be called from .../TopAnalysis/Configuration/analysis/semiLeptonic/diffXSection
## a) set up the folder structure:
## mkdir -p diffXSecFromSignal/plots/kinFit/2010/monitoring
## mkdir -p diffXSecFromSignal/plots/kinFit/2010/partonLevel
## mkdir -p diffXSecFromSignal/plots/kinFit/2010/recoYield
## mkdir -p diffXSecFromSignal/plots/kinFit/2010/uncertainties
## mkdir -p diffXSecFromSignal/plots/kinFit/2010/xSec
## mkdir -p diffXSecFromSignal/plots/kinFit/2010/binning
## mkdir -p diffXSecFromSignal/plots/kinFit/2010/effAndAcc
## mkdir -p diffXSecFromSignal/plots/kinFit/2010/genRecoCorrPlots
## mkdir -p diffXSecFromSignal/plots/kinFit/2010/kinFitPerformance
## mkdir -p diffXSecFromSignal/plots/kinFit/2011/monitoring
## mkdir -p diffXSecFromSignal/plots/kinFit/2011/partonLevel
## mkdir -p diffXSecFromSignal/plots/kinFit/2011/recoYield
## mkdir -p diffXSecFromSignal/plots/kinFit/2011/uncertainties
## mkdir -p diffXSecFromSignal/plots/kinFit/2011/xSec
## mkdir -p diffXSecFromSignal/plots/kinFit/2011/binning
## mkdir -p diffXSecFromSignal/plots/kinFit/2011/effAndAcc
## mkdir -p diffXSecFromSignal/plots/kinFit/2011/genRecoCorrPlots
## mkdir -p diffXSecFromSignal/plots/kinFit/2011/kinFitPerformance
## b) copy root files needed for the Analysis
## scp -r username@uhh-cms03.desy.de:/afs/desy.de/user/m/mgoerner/public/analysisRootFilesWithKinFit ./diffXSecFromSignal
## c) when using the shell script for the very first time, do "chmod a+x topDiffXSecAnalysis2011.sh
## find final plots in ./diffXSecFromSignal/plots/ after running the analysis via ./topDiffXSecAnalysis2011.sh

########################
## configure settings ##
########################
# lepton flavour in semi leptonic decay
decayChannel=\"muon\" # or \"electron\"
## lumi [/pb]
## has to fit to current dataset
dataLuminosity=35.9
## dataset: 2010 or 2011
#dataSample=\"diffXSecFromSignal/differentDataSets/analyzeDiffXData2011_Electron204pb.root\"
#dataSample=\"diffXSecFromSignal/differentDataSets/analyzeDiffXData2011_Muon204pb.root\"
#dataSample=\"diffXSecFromSignal/differentDataSets/analyzeDiffXData2011_MuonIso678pb_160404_167151.root\"
dataSample=\"diffXSecFromSignal/analysisRootFilesWithKinFit/muonDiffXSec2010Data36pbNov4ReRecoNov12Json.root\"
#dataSample=\"diffXSecFromSignal/analysisRootFilesWithKinFit/muonDiffXSec2011Data188pPromptReco1305Json.root\"
#dataSample=\"diffXSecFromSignal/analysisRootFilesWithKinFit/analyzeDiffXData2011_ElectronHad_160404-161312.root\"
dataLabel=2011
dataLuminosity2=`echo $dataLuminosity '*100' | bc -l | awk -F '.' '{ print $1; exit; }'`
if [ $dataLuminosity2 -le 3600 ]
then
    dataLabel=2010
fi
## save all plots? (.eps and .root)
save=true
## detail level of output 
## 0: no output, 1: std output 2: output for debugging
verbose=0 
## last systematic to proceed (0: only std analysis without variation)
## has to be consistend with the enumerator "systematicVariation" in "basicFunctions.h"
## maxSys>0 needs a lot of time
#maxSys=0
maxSys=0
## disable waiting time to read output
## fast = true / false
fast=true
## delete all (old) existing .eps and .pdf plots?
## clean = true / false
clean=true
## use errors from 2010 mu+jets analysis
## if error for 2011 analysis is not available
## NOTE: the rootfile ./diffXSecTopSemiMu2010.root
## must be available and contain the uncertainties 
oldErrors=true

#####################
## prepare running ##
#####################
## start the timer to stop the time needed for running the whole analysis
START=$(date +%s)

## print out configuration
clear
echo
echo "doing the full differential top xSec analysis"
echo "used data: $dataSample"
echo "luminosity: $dataLuminosity"
echo "save plots?: $save"
echo
if [ $fast = false ]
    then
    sleep 5
fi

## delete existing root file
Lep="Mu"
if [ $decayChannel = "electron" ]
    then
    Lep="Elec"
fi
echo "part A: delete existing rootfile ./diffXSecTopSemi$Lep$dataLabel.root"
if [ $fast = false ]
    then
    sleep 3
fi
rm ./diffXSecTopSemi$Lep$dataLabel.root

## delete existing plots
if [ $clean = true ]
    then
    rm ./diffXSecFromSignal/plots/kinFit/$dataLabel/*/*.*
    echo "part A2 delete existing plots within diffXSecFromSignal/plots/kinFit/$dataLabel/*/*.*"
    if [ $fast = false ]
	then
	sleep 1
    fi
fi

########################
## run cut monitoring ##
########################
BEFOREB=$(date +%s)
echo
echo "part B: process cut monitoring macro"
if [ $fast = false ]
    then
    sleep 3
fi
root -l -q -b './analyzeTopDiffXSecMonitoring.C+('$dataLuminosity', '$save', '$verbose', '$dataSample', '$decayChannel')'

#####################################
## run migration macro for binning ##
#####################################
BEFOREC=$(date +%s)
echo
echo "part C: process migration macro to validate binning"
if [ $fast = false ]
    then
    sleep 3
fi
#root -l -q -b './findBinning.C+()'

#########################################
## run efficiency& cross section macro ##
#########################################
BEFORED=$(date +%s)
echo
echo "part D: process cross section calculation macro for all systematics"
echo "INFO: missing files must not be problematic"
echo "      either all WZ, WW and ZZ or the combined VV sample are necessary"
echo "      same is true for the single top samples (s, t, tW)"
echo
if [ $fast = false ]
    then
    sleep 5
fi
## print key for systematic variations
## has to be consistend with the enumerator "systematicVariation" in "basicFunctions.h"
echo " 0: sysNo            1: sysLumiUp         2: sysLumiDown         3: sysJESUp     "
echo " 4: sysJESDown       5: sysJERUp          6: sysJERDown          7: sysTopScaleUp"
echo " 8: sysTopScaleDown  9: sysVBosonScaleUp 10: sysVBosonScaleDown 11: sysTopMatchUp"
echo "12: sysTopMatchDown 13: sysVBosonMatchUp 14: sysVBosonMatchDown 15: sysMuEffSFup "
echo "16: sysMuEffSFdown  17: sysISRFSRup      18: sysISRFSRdown      19: sysPileUp    "
echo "20: sysQCDup        21: sysQCDdown       22: sysSTopUp          23: sysSTopDown  "
echo "24: sysBtagUp       25: sysBtagDown      26: sysDiBosUp         27: sysDiBosDown "
if [ $fast = false ]
    then
    sleep 5
fi
## loop all systematic variations
for ((  systematicVariation = 0 ;  systematicVariation <= $maxSys;  systematicVariation++  ))
do 
  echo
  echo "running systematic variation number $systematicVariation"
  if [ $fast = false ]
      then
      sleep 2
  fi
  if [ $systematicVariation = 1 ]
      then
      BEFORESYS=$(date +%s)
  fi
## run macro
  root -l -q -b './analyzeHypothesisKinFit.C+('$dataLuminosity', '$save', '$systematicVariation', '$verbose', '$dataSample', '$decayChannel')'
done
AFTERSYS=$(date +%s)

###########################################
## combine uncertainties for final xSecs ##
###########################################
BEFOREE=$(date +%s)
echo
echo "part E: calculate systematic errors and draw final cross section"
if [ $fast = false ]
    then
    sleep 3
fi
root -l -q -b './combineTopDiffXSecUncertainties.C+('$dataLuminosity', '$save', '$verbose', '$decayChannel', '$oldErrors')'
echo "all analysis steps finished!"


################################
## after running the analysis ##
################################
## stop the timer and echo time
END=$(date +%s)
TIME=$(( $END - $START ))
echo "time needed: $TIME seconds"
if [ $maxSys -ge 1 ]
    then
    SYS=$(( $AFTERSYS - $BEFORESYS ))
    echo "($SYS seconds due to systematic variations)"
fi
echo "part A: $(( $BEFOREB - $START  )) seconds (clean up  )"
echo "part B: $(( $BEFOREC - $BEFOREB)) seconds (monitoring)"
echo "part C: $(( $BEFORED - $BEFOREC)) seconds (migration)"
echo "part D: $(( $BEFOREE - $BEFORED)) seconds (xSec, $maxSys systematic variations considered)"
echo "part E: $(( $END     - $BEFOREE)) seconds (errors and final xSec)"
