jetType="PF"
dataSelector = 1
leptonTypeId = 11
triggerPathSelector = "HLT_Ele27_WP80_v*"
#filterPathSelector = "hltSingleMu15L3Filtered15"
#triggerPathSelector2 = "HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralJet30_v*"
runOnAOD = True

#jetMinNumber2 = 3

execfile("analyzeZMuMuTagAndProbe_cfg.py")

process.load("TopAnalysis.Configuration.Summer12.DYJetsToLL_M_50_TuneZ2Star_8TeV_madgraph_tarball_Summer12_DR53X_PU_S10_START53_V7A_v1_cff")

process.TFileService.fileName = 'analyzeZEleEleTagAndProbeMCSummer12_HLT_Ele27WP80.root'
process.maxEvents.input = 10000
process.MessageLogger.cerr.FwkReport.reportEvery = 10000