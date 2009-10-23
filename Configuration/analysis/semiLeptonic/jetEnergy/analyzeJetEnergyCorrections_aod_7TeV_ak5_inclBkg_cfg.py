execfile("TopAnalysis/Configuration/analysis/semiLeptonic/jetEnergy/analyzeJetEnergyCorrections_aod_ak5_inclBkg_cfg.py")

execfile("TopAnalysis/Configuration/analysis/semiLeptonic/jetEnergy/Source_7TeV_cff.py")

#process.source.fileNames = [
#    '/store/mc/Summer09/QCDEnriched_Pt15to20/AODSIM/MC_31X_V3_7TeV_AODSIM-v1/0009/48664307-07A2-DE11-9D4E-00221987EBAF.root'
#    ]

process.jetCorrFactors.corrSample = 'Summer09_7TeV'

process.TFileService.fileName = 'analyzeJetEnergyCorrections_7TeV_ak5_inclBkg.root'
