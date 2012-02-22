jetType="PF"
dataSelector = 1
leptonTypeId = 11
triggerPathSelector1 = "HLT_Ele27_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_v*"
## NOTE the name change between V1ReReco and V4PromptReco!!!
triggerPathSelector2 = "HLT_Ele25_CaloIdVT_TrkIdT_CentralTriJet30_v*"
cutflowSelector = "effOnly"
runOnAOD = True

jetMinNumber = 3

#execfile("TopAnalysis/Configuration/analysis/fullLeptonic/analyzeZMuMuTagAndProbe_cfg.py")
execfile("analyzeCrossTriggerRatios_cfg.py")

#process.load("TopAnalysis.Configuration.samples.Run2011A_SingleMu_May10ReRecoV1_AOD_cff")
process.load("TopAnalysis.Configuration.wlnujets_MadgraphZ2_Summer11_AOD_cff")

process.TFileService.fileName = 'analyzeCrossTriggerRatiosMCSummer11WJets_IsoEle27_Ele25TriJet_TreeV2.root'
process.maxEvents.input = 1000
process.MessageLogger.cerr.FwkReport.reportEvery = 10000
