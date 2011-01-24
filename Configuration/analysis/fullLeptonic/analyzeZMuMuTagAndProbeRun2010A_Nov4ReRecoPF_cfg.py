jetType="PF"
dataSelector = 11

#execfile("TopAnalysis/Configuration/analysis/fullLeptonic/analyzeZMuMuTagAndProbe_cfg.py")
execfile("analyzeZMuMuTagAndProbe_cfg.py")

process.load("TopAnalysis.Configuration.samples.Run2010A_Nov04ReReco_cff")
process.TFileService.fileName = 'analyzeZMuMuTagAndProbeRun2010A_Nov4ReRecoPF.root'
process.maxEvents.input = -1