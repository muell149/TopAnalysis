#!/bin/sh

## this shell script runs all macro parts of the 2011 differential cross section analysis 

## HOW TO USE THIS SHELL SCRIPT
## note: has to be called from .../TopAnalysis/Configuration/analysis/semiLeptonic/diffXSection
## a) set up the folder structure:
## mkdir -p diffXSecFromSignal/plots/muon/2010/monitoring
## mkdir -p diffXSecFromSignal/plots/muon/2010/partonLevel
## mkdir -p diffXSecFromSignal/plots/muon/2010/recoYield
## mkdir -p diffXSecFromSignal/plots/muon/2010/uncertainties
## mkdir -p diffXSecFromSignal/plots/muon/2010/xSec
## mkdir -p diffXSecFromSignal/plots/muon/2010/binning
## mkdir -p diffXSecFromSignal/plots/muon/2010/effAndAcc
## mkdir -p diffXSecFromSignal/plots/muon/2010/genRecoCorrPlots
## mkdir -p diffXSecFromSignal/plots/muon/2010/kinFitPerformance
## mkdir -p diffXSecFromSignal/plots/muon/2011/monitoring
## mkdir -p diffXSecFromSignal/plots/muon/2011/monitoring/withoutRatioPlots
## mkdir -p diffXSecFromSignal/plots/muon/2011/partonLevel
## mkdir -p diffXSecFromSignal/plots/muon/2011/recoYield
## mkdir -p diffXSecFromSignal/plots/muon/2011/uncertainties
## mkdir -p diffXSecFromSignal/plots/muon/2011/xSec
## mkdir -p diffXSecFromSignal/plots/muon/2011/binning
## mkdir -p diffXSecFromSignal/plots/muon/2011/effAndAcc
## mkdir -p diffXSecFromSignal/plots/muon/2011/genRecoCorrPlots
## mkdir -p diffXSecFromSignal/plots/muon/2011/kinFitPerformance
## mkdir -p diffXSecFromSignal/plots/muon/2011/shapeReweighting
## mkdir -p diffXSecFromSignal/plots/electron/2011/monitoring
## mkdir -p diffXSecFromSignal/plots/electron/2011/monitoring/withoutRatioPlots
## mkdir -p diffXSecFromSignal/plots/electron/2011/partonLevel
## mkdir -p diffXSecFromSignal/plots/electron/2011/recoYield
## mkdir -p diffXSecFromSignal/plots/electron/2011/uncertainties
## mkdir -p diffXSecFromSignal/plots/electron/2011/xSec
## mkdir -p diffXSecFromSignal/plots/electron/2011/binning
## mkdir -p diffXSecFromSignal/plots/electron/2011/effAndAcc
## mkdir -p diffXSecFromSignal/plots/electron/2011/genRecoCorrPlots
## mkdir -p diffXSecFromSignal/plots/electron/2011/kinFitPerformance
## mkdir -p diffXSecFromSignal/plots/electron/2011/shapeReweighting
## mkdir -p diffXSecFromSignal/plots/combined/2011/xSec
## mkdir -p diffXSecFromSignal/plots/combined/2011/uncertainties

## b) you don't need to copy root files needed for the Analysis 
##    the are loaded automatically from /afs/naf.desy.de/group/cms/scratch/tophh/TOP2011/
## c) when using the shell script for the very first time, do "chmod a+x topDiffXSecAnalysis2011.sh
## find final plots in ./diffXSecFromSignal/plots/ after running the analysis via ./topDiffXSecAnalysis2011.sh

########################
## configure settings ##
########################
# lepton flavour in semi leptonic decay
# choose \"muon\" or \"electron\" or \"combined\"
decayChannel=\"electron\" 
## lumi [/pb]
## has to fit to current dataset
dataLuminosity=1143.22
## dataset: 2010 or 2011
#dataSample=\"/afs/naf.desy.de/group/cms/scratch/tophh/TOP2011/110819_AnalysisRun/muonPseudoData1143pb7TeV.root\"
#dataSample=\"/afs/naf.desy.de/group/cms/scratch/tophh/TOP2011/110819_AnalysisRun/electronPseudoData1143pb7TeV.root\"
#dataSample=\"/afs/naf.desy.de/group/cms/scratch/tophh/TOP2011/110819_AnalysisRun/muonPseudoData1143pband500GeVZprime7TeV.root\"
#dataSample=\"/afs/naf.desy.de/group/cms/scratch/tophh/TOP2011/110819_AnalysisRun/electronPseudoData1143pband500GeVZprime7TeV.root\"
#dataSample=\"/afs/naf.desy.de/group/cms/scratch/tophh/TOP2011/110819_AnalysisRun/muonPseudoData1143pband750GeVZprime7TeV.root\"
#dataSample=\"/afs/naf.desy.de/group/cms/scratch/tophh/TOP2011/110819_AnalysisRun/electronPseudoData1143pband750GeVZprime7TeV.root\"
#dataSample=\"/afs/naf.desy.de/group/cms/scratch/tophh/TOP2011/110819_AnalysisRun/analyzeDiffXData2011A_Muon_160404_167913_1fb.root\"
#dataSample=\"/afs/naf.desy.de/group/cms/scratch/tophh/TOP2011/110819_AnalysisRun/analyzeDiffXData2011A_Elec_160404_167913_1fb.root\"
#dataSample=\"/afs/naf.desy.de/group/cms/scratch/tophh/TOP2011/110819_AnalysisRun/analyzeDiffXData2011A_Muon_160404_167913_1fb_withVTXDistributions.root\"
dataSample=\"/afs/naf.desy.de/group/cms/scratch/tophh/TOP2011/110819_AnalysisRun/analyzeDiffXData2011A_Elec_160404_167913_1fb_withVTXDistributions.root\"
#dataSample=\"diffXSecFromSignal/differentDataSets/analyzeDiffXData2011_Electron204pb.root\"
#dataSample=\"diffXSecFromSignal/differentDataSets/analyzeDiffXData2011_Muon204pb.root\"
#dataSample=\"diffXSecFromSignal/differentDataSets/analyzeDiffXData2011_MuonIso678pb_160404_167151.root\"
#dataSample=\"diffXSecFromSignal/analysisRootFilesWithKinFit/muonDiffXSec2010Data36pbNov4ReRecoNov12Json.root\"
#dataSample=\"diffXSecFromSignal/analysisRootFilesWithKinFit/muonDiffXSec2011Data188pPromptReco1305Json.root\"
#dataSample=\"diffXSecFromSignal/analysisRootFilesWithKinFit/elecDiffXSec2011Data191pPromptReco1305Json.root\"
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
## folder on /afs/naf.desy.de/group/cms/scratch/tophh where MC and data files are stored
inputFolderName=\"TOP2011/110819_AnalysisRun\"
## last systematic to proceed (0: only std analysis without variation)
## has to be consistend with the enumerator "systematicVariation" in "basicFunctions.h"
## maxSys>0 needs a lot of time (must be<=42, see list of systematics below)
maxSys=44
## shape variations?
shapeVar=true
## disable waiting time to read output
## fast = true / false
fast=true
## delete all (old) existing .eps and .pdf plots?
## clean = true / false
clean=true
### automatic definition of used MC sets
### 2010: fall10 MC
#if [ $dataLuminosity2 -le 3600 ]
#    then
#    sed -i s/newSpring11MC=true/newSpring11MC=false/g ./basicFunctions.h
#    sed -i s/newSummer11MC=true/newSummer11MC=false/g ./basicFunctions.h
#fi
### 2011: summer11MC
#if [ $dataLuminosity2 -ge 3601 ]
#    then
#    sed -i s/newSpring11MC=false/newSpring11MC=true/g ./basicFunctions.h
#    sed -i s/newSummer11MC=true/newSummer11MC=true/g ./basicFunctions.h
#fi

#####################
## prepare running ##
#####################
## start the timer to stop the time needed for running the whole analysis
START=$(date +%s)

## print out configuration
clear
if [ $decayChannel == \"combined\" ]
    then
    echo
    echo "combining the electron and muon channel"
    echo "NOTE: requires the files"
    echo "diffXSecTopSemiMu2011.root and diffXSecTopSemiElec2011.root"
    echo "get them by running the e/mu channel first"
    echo
else
    echo
    echo "doing the full differential top xSec analysis"
    echo "used data:                $dataSample"
    echo "decay channel:            $decayChannel"
    echo "luminosity:               $dataLuminosity"
    echo "considered systematics:   $maxSys"
    echo "consider shape variation: $shapeVar"
    echo "save plots:               $save"
    grep newSpring11MC= ./basicFunctions.h
    grep newSummer11MC= ./basicFunctions.h
    echo
fi
if [ $fast = false ]
    then
    sleep 5
fi

## delete existing root file
echo "part A: delete existing rootfile"
if [ $fast = false ]
    then
    sleep 3
fi
if [ $clean = true ]
    then
    echo "will be done for: "
    if [ $decayChannel == \"electron\" ]
	then
	echo "./diffXSecTopSemiElec$dataLabel.root"
	rm ./diffXSecTopSemiElec$dataLabel.root
    else
	if [ $decayChannel == \"muon\" ]
	    then
	    echo "./diffXSecTopSemiMu$dataLabel.root"
	    rm ./diffXSecTopSemiMu$dataLabel.root
	else
	    if [ $decayChannel == \"combination\" ]
		then
		echo "./diffXSecTopSemiLep.root"
		rm ./diffXSecTopSemiLep.root
		echo "none" 
	    fi
	fi
    fi 
fi

## delete existing plots
if [ $clean = true ]
    then
    echo "part A2 delete existing plots within diffXSecFromSignal/plots/$decayChannel/$dataLabel/*/*.*"
    if [ $decayChannel == \"muon\" ]
	then
	rm ./diffXSecFromSignal/plots/muon/$dataLabel/*/*.*
    fi
    if [ $decayChannel == \"electron\" ]
	then
	rm ./diffXSecFromSignal/plots/electron/$dataLabel/*/*.*
    fi
    if [ $decayChannel == \"combined\" ]
	then
	rm ./diffXSecFromSignal/plots/combined/$dataLabel/*/*.*
    fi
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
if [ $decayChannel != \"combined\" ]
    then  
    echo
    root -l -q -b './analyzeTopDiffXSecMonitoring.C++('$dataLuminosity', '$save', '$verbose', '$inputFolderName', '$dataSample', '$decayChannel', 'true')'   # with ratio plots
    root -l -q -b './analyzeTopDiffXSecMonitoring.C++('$dataLuminosity', '$save', '$verbose', '$inputFolderName', '$dataSample', '$decayChannel', 'false')'  # without ratio plots
fi

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
# Array of differential variables:
listVar_=( \"topPt\" \"topY\" \"ttbarPt\" \"ttbarY\" \"ttbarMass\" \"lepPt\" \"lepEta\")
if [ $decayChannel != \"combined\" ]
    then
    echo "purity and stability will be calculated for the following variables:"
    # loop over all systematic variations
    for (( iVar=0; iVar<7; iVar++ ))
    do
    echo
    echo purity and stability for: ${listVar_[$iVar]}
    echo
    root -l -q -b './purityStabilityEfficiency.C++('${listVar_[$iVar]}','$save', '$decayChannel', '$inputFolderName')'
    done
    echo
    echo "purity and stability done"
else
    echo "will be ignored, only done for decayChannel=muon/electron"
fi

#############################
# prepare PDF uncertainties #
#############################
BEFOREPDF=$(date +%s)
echo
echo "part PDF: Prepare files for pdf uncertainties"
echo

if [ $decayChannel != \"combined\" ]
    then
    echo
    root -l -q -b './analyzeTopDiffXSecMCdependency.C++('$dataLuminosity','$decayChannel', '$save', '$verbose', '$inputFolderName', '$dataSample', 'true')' 
else
    echo "Done for 2011 analysis in e/mu channel separate."
fi

##################################################################
# run shape distortion macro to get root files for MC dependency #
##################################################################
BEFORED=$(date +%s)
echo
echo "part D: create rootfiles with shape variations"
echo

if [ $shapeVar = true ]
    then
    if [ $decayChannel != \"combined\" ]
	then    
	if [ $dataLuminosity2 -ge 3601 ]
	    then
	    echo "will be done"
	    root -l -q -b './analyzeTopDiffXSecMCdependency.C++('$dataLuminosity','$decayChannel', '$save', '$verbose', '$inputFolderName', '$dataSample', 'false')'
	else
	    echo "only done for 2011 analysis in e/mu channel separate"
	fi
    else
	echo "only done for 2011 analysis in e/mu channel separate"
    fi
else
    echo "choose shapeVar = true!"
fi

#########################################
## run efficiency& cross section macro ##
#########################################
BEFOREE=$(date +%s)
echo
echo "part E1: process cross section calculation macro for all systematics"
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
echo
echo "  0: noSys                                                     "
echo "  1: sysLumiUp                  2: sysLumiDown                 "              
echo "  3: sysPUUp                    4: sysPUDown                   "
echo "  5: sysJESUp                   6: sysJESDown                  "
echo "  7: sysJERUp                   8: sysJERDown                  "
echo "  9: sysTrigEffSFNormUp        10: sysTrigEffSFNormDown        " 
echo " 11: sysTriggerEffSFShapeUpEta 12: sysTriggerEffSFShapeDownEta "
echo " 13: sysTriggerEffSFShapeUpPt  14: sysTriggerEffSFShapeDownPt  "
echo " 15: sysMuEffSFUp              16: sysMuEffSFDown              " 
echo " 17: sysBtagSFUp               18: sysBtagSFDown               "
echo " 19: sysMisTagSFUp             20: sysMisTagSFDown             "
echo " 21: sysTopScaleUp             22: sysTopScaleDown             "
echo " 23: sysVBosonScaleUp          24: sysVBosonScaleDown          "
echo " 25: sysSingleTopScaleUp       26: sysSingleTopScaleDown       "
echo " 27: sysTopMatchUp             28: sysTopMatchDown             " 
echo " 29: sysVBosonMatchUp          30: sysVBosonMatchDown          "
echo " 31: sysTopMassUp              32: sysTopMassDown              "
echo " 33: sysQCDUp                  34: sysQCDown                   " 
echo " 35: sysSTopUp                 36: sysSTopDown                 "
echo " 37: sysDiBosUp                38: sysDiBosDown                "
echo " 39: sysShapeUp                40: sysShapeDown                " 
echo " 41: sysPDFUp                  42: sysPDFDown                  " 
echo " 43: sysHadUp                  44: sysHadDown                  "    
echo " 45: ENDOFSYSENUM                                              "
echo
if [ $fast = false ]
    then
    sleep 5
fi
# get start time
BEFORESYS=$(date +%s)

if [ $decayChannel != \"combined\" ]
    then
    root -l -q -b './analyzeHypothesisKinFit.C++('$dataLuminosity', '$save', 0, '$verbose', '$inputFolderName', '$dataSample', '$decayChannel')'
fi

## loop all systematic variations
for (( systematicVariation = 1;  systematicVariation <= $maxSys;  systematicVariation++ ))
  do 
  echo
  echo " Running systematic variation: $systematicVariation"
  if [ $fast = false ]
      then
      sleep 2
  fi
  if [ $decayChannel != \"combined\" ]
      then
      ## exclude shape variation
      if [ $systematicVariation == 39 -o $systematicVariation == 40 ]
	  then
	  echo " Shape variations are executed separately."
      else
	  ## run macro for 2011 analysis
	  root -l -q -b './analyzeHypothesisKinFit.C++('$dataLuminosity', '$save', '$systematicVariation', '$verbose', '$inputFolderName', '$dataSample', '$decayChannel')'
      fi  
  else
      echo "will be ignored, only done for decayChannel=muon/electron"
  fi
done

## shape and PDF variations
if [ $shapeVar = true ]
    then
    if [ $decayChannel != \"combined\" ]
	then
	echo ""
	echo " All regular systematic uncertainties processed .... Now running shape variations."
	echo ""
	root -l -q -b './analyzeHypothesisKinFit.C++('$dataLuminosity', '$save', 39, '$verbose', '$inputFolderName', '$dataSample', '$decayChannel')'
	root -l -q -b './analyzeHypothesisKinFit.C++('$dataLuminosity', '$save', 40, '$verbose', '$inputFolderName', '$dataSample', '$decayChannel')'
    fi
fi

#######################################
## combine electron and muon channel ##
#######################################
echo
echo "part E2: combine electron and muon channel"
if [ $fast = false ]
    then
    sleep 2
fi
if [ $decayChannel == \"combined\" ]
    then
    echo "cross sections for all systematic variations"
    echo "and all decay channels"
    echo
    root -l -q -b './bothDecayChannelsCombination.C++('$dataLuminosity', '$save', '$verbose', '$inputFolderName')'
else
    echo "will be ignored, only done for decayChannel=combined"
fi
echo
AFTERSYS=$(date +%s)

###########################################
## combine uncertainties for final xSecs ##
###########################################
BEFOREF=$(date +%s)
echo
echo "part F: calculate systematic errors and draw final cross section"
if [ $fast = false ]
    then
    sleep 3
fi
if [ -f commands.cint ]; then    
  
    rm commands.cint
    rm combineTopDiffXSecUncertainties_C.so
    rm combineTopDiffXSecUncertainties_C.d

fi

cat >> commands.cint << EOF
.L BCC.C++
.L BCC_C.so
.L combineTopDiffXSecUncertainties.C++g
.L combineTopDiffXSecUncertainties_C.so
combineTopDiffXSecUncertainties($dataLuminosity, $save, $verbose, $inputFolderName, $decayChannel)
EOF

root -l -b < commands.cint

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
echo "part A: $(( $BEFOREB   - $START    )) seconds (clean up  )"
echo "part B: $(( $BEFOREC   - $BEFOREB  )) seconds (monitoring)"
echo "part C: $(( $BEFOREPDF - $BEFOREC  )) seconds (migration)"
echo "part D: $(( $BEFORED   - $BEFOREPDF)) seconds (prepare PDF uncertainty run)"
echo "part E: $(( $BEFOREE   - $BEFORED  )) seconds (shape variations)"
echo "part F: $(( $BEFOREF   - $BEFOREE  )) seconds (xSec, $maxSys systematic variations considered)"
echo "part G: $(( $END       - $BEFOREF  )) seconds (errors and final xSec)"
