execfile("TopAnalysis/Configuration/analysis/semiLeptonic/jetEnergy/analyzeJetEnergyCorrections_aod_ak5_cfg.py")

process.load("TopAnalysis.TopUtils.JetEnergyScale_cff")
from TopAnalysis.TopUtils.JetEnergyScale_cff import *
scaleAllLayer1JetsEnergy(process, 0.95)

process.TFileService.fileName = 'analyzeJetEnergyCorrections_ak5_JESm5.root'
