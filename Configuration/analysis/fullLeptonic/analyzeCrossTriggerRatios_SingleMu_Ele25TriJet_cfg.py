jetType="PF"
dataSelector = 14
leptonTypeId = 11
triggerPathSelector1 = "*"
triggerPathSelector2 = "HLT_Ele25_CaloIdVT_TrkIdT_CentralTriJet30_v*"
cutflowSelector = "effOnly"

#execfile("TopAnalysis/Configuration/analysis/fullLeptonic/analyzeZMuMuTagAndProbe_cfg.py")
execfile("analyzeCrossTriggerRatios_cfg.py")

process.load("TopAnalysis.Configuration.samples.Run2011A_SingleMuPromptRecoV1andV2_JsonMay13_newJEC_cff")
process.TFileService.fileName = 'analyzeCrossTriggerRatios_SingleMu_Ele25TriJet.root'
process.maxEvents.input = 10000
process.MessageLogger.cerr.FwkReport.reportEvery = 100
