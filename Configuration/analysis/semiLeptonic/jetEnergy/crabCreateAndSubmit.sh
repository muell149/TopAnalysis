#!/bin/sh

list="crabJetEnergyCorrections_aod_ak5 \
      crabJetEnergyCorrections_aod_ic5 \
      crabJetEnergyCorrections_aod_kt4 \
      crabJetEnergyCorrections_aod_sc5 \
      crabJetEnergyResolutionBias      \
      crabJetEnergyResolutionBias_mcatnlo"

for i in $list
  do
  echo "==========================================================================================="
  echo $i
  echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
  crab -cfg TopAnalysis/Configuration/analysis/semiLeptonic/jetEnergy/$i.cfg -create -submit
done