#!/bin/sh

anaCor=TopAnalysis/Configuration/analysis/semiLeptonic/jetEnergy/analyzeCorrections
anaRes=TopAnalysis/Configuration/analysis/semiLeptonic/jetEnergy/analyzeResolutionBias

targetDir=~/latex/notes/JECTopValidation

$anaCor "analyzeJetEnergyCorrections_ak5.root"         "GenMatch"
$anaCor "analyzeJetEnergyCorrections_ak5_mcatnlo.root" "GenMatch"
$anaCor "analyzeJetEnergyCorrections_ic5.root"         "GenMatch"
$anaCor "analyzeJetEnergyCorrections_kt4.root"         "GenMatch"
$anaCor "analyzeJetEnergyCorrections_sc5.root"         "GenMatch"

cp -r analyzeJetEnergyCorrections_ak5/         $targetDir
cp -r analyzeJetEnergyCorrections_ak5_mcatnlo/ $targetDir
cp -r analyzeJetEnergyCorrections_ic5/         $targetDir
cp -r analyzeJetEnergyCorrections_kt4/         $targetDir
cp -r analyzeJetEnergyCorrections_sc5/         $targetDir

#$anaRes "analyzeJetEnergyResolutionBias.root" "analyzeJetEnergyResolutionBias_mcatnlo.root"
#
#cp -r analyzeJetEnergyResolutionBias $targetDir
