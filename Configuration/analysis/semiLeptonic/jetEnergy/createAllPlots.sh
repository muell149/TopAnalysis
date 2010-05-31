#!/bin/sh

codeDir=TopAnalysis/Configuration/analysis/semiLeptonic/jetEnergy
targetDir=~/latex/notes/JECTopValidation

compare=$codeDir/compareSamples
anaRes=$codeDir/analyzeResolutionBias
anaCor=$codeDir/analyzeCorrections

##################################################
## JER bias plots
##################################################

echo -n "Produce JER bias plots? [y/n] "
read answer
if [[ $answer == "y" ]]
    then

    cd $codeDir
    make resolution
    cd -

    $anaRes "analyzeJetEnergyResolutionBias.root" "analyzeJetEnergyResolutionBias_mcatnlo.root"

    echo -n "Copy results to $targetDir ? [y/n] "
    read answer
    if [[ $answer == "y" ]]
	then

	cp -r analyzeJetEnergyResolutionBias $targetDir

    fi

fi

##################################################
## sample comparison plots
##################################################

echo -n "Produce sample comparison plots? [y/n] "
read answer
if [[ $answer == "y" ]]
    then

    cd $codeDir
    make comparison
    cd -

    $compare "analyzeJetEnergyCorrections_ak5.root" "analyzeJetEnergyCorrections_ak5_mcatnlo.root"

    echo -n "Copy results to $targetDir ? [y/n] "
    read answer
    if [[ $answer == "y" ]]
	then

	cp -r compareJetEnergyCorrectionSamples $targetDir

    fi

fi

##################################################
## JEC validation plots
##################################################

echo -n "Produce JEC validation plots? [y/n] "
read answer
if [[ $answer == "y" ]]
    then

    cd $codeDir
    make corrections
    cd -

    $anaCor "analyzeJetEnergyCorrections_ak5.root"         "GenMatch"
    $anaCor "analyzeJetEnergyCorrections_ak5_mcatnlo.root" "GenMatch"
    $anaCor "analyzeJetEnergyCorrections_ic5.root"         "GenMatch"
    $anaCor "analyzeJetEnergyCorrections_kt4.root"         "GenMatch"

    echo -n "Copy results to $targetDir ? [y/n] "
    read answer
    if [[ $answer == "y" ]]
	then

	cp -r analyzeJetEnergyCorrections_ak5/         $targetDir
	cp -r analyzeJetEnergyCorrections_ak5_mcatnlo/ $targetDir
	cp -r analyzeJetEnergyCorrections_ic5/         $targetDir
	cp -r analyzeJetEnergyCorrections_kt4/         $targetDir

    fi

fi

