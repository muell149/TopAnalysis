jetType="PF"
dataSelector = 2

#execfile("TopAnalysis/Configuration/analysis/fullLeptonic/analyzeZMuMuTagAndProbe_cfg.py")
execfile("analyzeZMuMuTagAndProbe_cfg.py")

process.load("TopAnalysis.Configuration.samples.DYJetsToLL_M50_D6T_madgraph_F10_cff")
process.TFileService.fileName = 'analyzeZMuMuTagAndProbeMCFall10PF.root'
process.maxEvents.input = -1
#process.MessageLogger.cerr.FwkReport.reportEvery = 1