execfile("TopAnalysis/Configuration/analysis/semiLeptonic/jetEnergy/analyzeJetEnergyCorrections_aod_ak5_cfg.py")

process.load("TopAnalysis.TopUtils.JetEnergyScale_cff")
from TopAnalysis.TopUtils.JetEnergyScale_cff import *
scaleAllLayer1JetsEnergy(process, 1.05)

process.TFileService.fileName = 'analyzeJetEnergyCorrections_ak5_JESp5.root'
