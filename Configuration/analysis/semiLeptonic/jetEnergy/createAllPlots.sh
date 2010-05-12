#!/bin/sh

codeDir=TopAnalysis/Configuration/analysis/semiLeptonic/jetEnergy
targetDir=~/latex/notes/JECTopValidation

anaCor=$codeDir/analyzeCorrections
anaRes=$codeDir/analyzeResolutionBias

if test ! -x $anaCor
    then
    cd $codeDir
    make corrections
    cd -
fi

$anaCor "analyzeJetEnergyCorrections_ak5.root"         "GenMatch"
$anaCor "analyzeJetEnergyCorrections_ak5_mcatnlo.root" "GenMatch"
$anaCor "analyzeJetEnergyCorrections_ic5.root"         "GenMatch"
$anaCor "analyzeJetEnergyCorrections_kt4.root"         "GenMatch"

cp -r analyzeJetEnergyCorrections_ak5/         $targetDir
cp -r analyzeJetEnergyCorrections_ak5_mcatnlo/ $targetDir
cp -r analyzeJetEnergyCorrections_ic5/         $targetDir
cp -r analyzeJetEnergyCorrections_kt4/         $targetDir

if test ! -x $anaRes
    then
    cd $codeDir
    make resolution
    cd -
fi

$anaRes "analyzeJetEnergyResolutionBias.root" "analyzeJetEnergyResolutionBias_mcatnlo.root"

cp -r analyzeJetEnergyResolutionBias $targetDir
