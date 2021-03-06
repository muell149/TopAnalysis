jetType="PF"
dataSelector = 1
leptonTypeId = 11
triggerPathSelector1 = "HLT_Ele32_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_v*"
## NOTE the name change between V1ReReco and V4PromptReco!!!
triggerPathSelector2 = "HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralJet30_v*"
cutflowSelector = "effOnly"
runOnAOD = True

jetMinNumber = 3

#execfile("TopAnalysis/Configuration/analysis/fullLeptonic/analyzeZMuMuTagAndProbe_cfg.py")
execfile("analyzeCrossTriggerRatios_cfg.py")

## 4540 files
process.load("TopAnalysis/Configuration/Fall11/wlnujets_MadgraphZ2_Fall11_AOD_cff")

process.TFileService.fileName = 'analyzeCrossTriggerRatiosMCFall11WJets_IsoEle32_IsoEle25TriJet.root'
process.maxEvents.input = 1000
process.MessageLogger.cerr.FwkReport.reportEvery = 10000
