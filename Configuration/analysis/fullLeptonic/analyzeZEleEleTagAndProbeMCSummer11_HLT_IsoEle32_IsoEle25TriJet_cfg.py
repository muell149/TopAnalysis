jetType="PF"
dataSelector = 1
leptonTypeId = 11
triggerPathSelector = "HLT_Ele32_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_v*"
#filterPathSelector = "hltSingleMu15L3Filtered15"
triggerPathSelector2 = "HLT_Ele25_CaloIdVT_TrkIdT_CentralTriJet30_v*"
runOnAOD = False

muonPtCut = 30.
jetMinNumber2 = 3

#execfile("TopAnalysis/Configuration/analysis/fullLeptonic/analyzeZMuMuTagAndProbe_cfg.py")
execfile("analyzeZMuMuTagAndProbe_cfg.py")

process.load("TopAnalysis.Configuration.samples.DYJetsToLL_M50_madgraph_Summer11_cff")

process.TFileService.fileName = 'analyzeZEleEleTagAndProbeMCSummer11_HLT_IsoEle32_IsoEle25TriJet.root'
process.maxEvents.input = 10000
process.MessageLogger.cerr.FwkReport.reportEvery = 10000