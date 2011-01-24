#execfile("TopAnalysis/Configuration/analysis/fullLeptonic/analyzeZMuMuTagAndProbe_cfg.py")
jetType="PF"
modeSelector = 2
execfile("analyzeZMuMuTagAndProbe_cfg.py")

process.load("TopAnalysis.Configuration.samples.Fall10_TTbar_PATtuple_MuMCMatching_cff")
process.TFileService.fileName = 'analyzeZMuMuTagAndProbeGenEffTTbar.root'
process.maxEvents.input = -1
process.p1.remove(process.hltTriggerFilter)
