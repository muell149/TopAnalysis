#!/bin/sh

TopAnalysis/Configuration/analysis/semiLeptonic/jetEnergy/analyze "analyzeJetEnergyCorrections_ak5.root"         "GenMatch"
TopAnalysis/Configuration/analysis/semiLeptonic/jetEnergy/analyze "analyzeJetEnergyCorrections_ak5_inclBkg.root" "Geom"
TopAnalysis/Configuration/analysis/semiLeptonic/jetEnergy/analyze "analyzeJetEnergyCorrections_ic5.root"         "GenMatch"
TopAnalysis/Configuration/analysis/semiLeptonic/jetEnergy/analyze "analyzeJetEnergyCorrections_kt4.root"         "GenMatch"
TopAnalysis/Configuration/analysis/semiLeptonic/jetEnergy/analyze "analyzeJetEnergyCorrections_sc5.root"         "GenMatch"

cp -r analyzeJetEnergyCorrections_ak5/         ~/latex/notes/JECTopValidation
cp -r analyzeJetEnergyCorrections_ak5_inclBkg/ ~/latex/notes/JECTopValidation
cp -r analyzeJetEnergyCorrections_ic5/         ~/latex/notes/JECTopValidation
cp -r analyzeJetEnergyCorrections_kt4/         ~/latex/notes/JECTopValidation
cp -r analyzeJetEnergyCorrections_sc5/         ~/latex/notes/JECTopValidation
