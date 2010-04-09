execfile("TopAnalysis/Configuration/analysis/firstCollisions/runMultijetAnalysis_cfg.py")

execfile("TopAnalysis/Configuration/analysis/firstCollisions/Source_QCD30_cff.py")

process.maxEvents.input = 10000

process.TFileService.fileName = 'analyzeMultijet_MC_new.root'
