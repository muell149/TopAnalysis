#!/bin/sh

TopAnalysis/Configuration/analysis/semiLeptonic/jetEnergy/analyzeCorrections "analyzeJetEnergyCorrections_ak5.root" "GenMatch"
TopAnalysis/Configuration/analysis/semiLeptonic/jetEnergy/analyzeCorrections "analyzeJetEnergyCorrections_ic5.root" "GenMatch"
TopAnalysis/Configuration/analysis/semiLeptonic/jetEnergy/analyzeCorrections "analyzeJetEnergyCorrections_kt4.root" "GenMatch"
TopAnalysis/Configuration/analysis/semiLeptonic/jetEnergy/analyzeCorrections "analyzeJetEnergyCorrections_sc5.root" "GenMatch"

cp -r analyzeJetEnergyCorrections_ak5/ ~/latex/notes/JECTopValidation
cp -r analyzeJetEnergyCorrections_ic5/ ~/latex/notes/JECTopValidation
cp -r analyzeJetEnergyCorrections_kt4/ ~/latex/notes/JECTopValidation
cp -r analyzeJetEnergyCorrections_sc5/ ~/latex/notes/JECTopValidation
