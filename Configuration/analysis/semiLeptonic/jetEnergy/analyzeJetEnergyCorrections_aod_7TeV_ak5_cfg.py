execfile("TopAnalysis/Configuration/analysis/semiLeptonic/jetEnergy/analyzeJetEnergyCorrections_aod_ak5_cfg.py")

execfile("TopAnalysis/Configuration/analysis/semiLeptonic/jetEnergy/Source_7TeV_cff.py")

process.maxEvents.input = 100

process.jetCorrFactors.corrSample = 'Summer09_7TeV'

process.TFileService.fileName = 'analyzeJetEnergyCorrections_7TeV_ak5.root'
