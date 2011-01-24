jetType="PF"
dataSelector = 11
triggerPathSelector = "HLT_Mu15_v1"

#execfile("TopAnalysis/Configuration/analysis/fullLeptonic/analyzeZMuMuTagAndProbe_cfg.py")
execfile("analyzeZMuMuTagAndProbe_cfg.py")

process.load("TopAnalysis.Configuration.samples.Run2010B2_Nov04ReReco_cff")
process.TFileService.fileName = 'analyzeZMuMuTagAndProbeRun2010B2_Nov4ReRecoPF.root'
process.maxEvents.input = -1