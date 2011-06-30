jetType="PF"
dataSelector = 14
triggerPathSelector = "HLT_IsoMu17_v*"
#filterPathSelector = "hltSingleMu15L3Filtered15"
#triggerPathSelector2 = "HLT_Mu17_TriCentralJet30_v*"
cutflowSelector = "effAndCutflow"

#execfile("TopAnalysis/Configuration/analysis/fullLeptonic/analyzeZMuMuTagAndProbe_cfg.py")
execfile("analyzeZMuMuTagAndProbe_cfg.py")

process.load("TopAnalysis.Configuration.samples.Run2011A_SingleMuPromptRecoV1andV2_JsonMay13_newJEC_cff")
process.TFileService.fileName = 'analyzeZMuMuTagAndProbeRun2011AV1andV2_HLT_IsoMu17.root'
process.maxEvents.input = -1
process.MessageLogger.cerr.FwkReport.reportEvery = 1000