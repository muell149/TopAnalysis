execfile("TopAnalysis/Configuration/analysis/semiLeptonic/jetEnergy/analyzeJetEnergyCorrections_aod_ak5_ttbarOther_cfg.py")

process.p1.remove(process.makeGenEvt)
process.p1.remove(process.ttSemiLeptonicFilter)

process.TFileService.fileName = 'analyzeJetEnergyCorrections_ak5_anyBkg.root'
