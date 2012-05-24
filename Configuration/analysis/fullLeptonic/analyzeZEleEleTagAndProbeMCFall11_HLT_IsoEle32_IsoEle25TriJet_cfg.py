jetType="PF"
dataSelector = 1
leptonTypeId = 11
triggerPathSelector = "HLT_Ele32_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_v*"
#filterPathSelector = "hltSingleMu15L3Filtered15"
triggerPathSelector2 = "HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralJet30_v*"
runOnAOD = True

jetMinNumber2 = 3

#execfile("TopAnalysis/Configuration/analysis/fullLeptonic/analyzeZMuMuTagAndProbe_cfg.py")
#############################
## ATTENTION!!!!!!!!!!!  Preliminary
##############################
#execfile("analyzeZMuMuTagAndProbe_cfg.py")
execfile("analyzeZMuMuTagAndProbeNEW_cfg.py")

process.load("TopAnalysis.Configuration.Fall11.dylljetsM50_MadgraphZ2_Fall11_AOD_cff")

process.TFileService.fileName = 'analyzeZEleEleTagAndProbeMCFall11_HLT_IsoEle32_IsoEle25TriJet.root'
process.maxEvents.input = 10000
process.MessageLogger.cerr.FwkReport.reportEvery = 10000