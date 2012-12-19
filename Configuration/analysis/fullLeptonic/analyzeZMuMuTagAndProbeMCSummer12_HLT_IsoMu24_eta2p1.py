jetType="PF"
dataSelector = 1
leptonTypeId = 13
triggerPathSelector = "HLT_IsoMu24_eta2p1_v*"
#filterPathSelector = "hltSingleMu15L3Filtered15"
#triggerPathSelector2 = "HLT_IsoMu17_eta2p1_TriCentralJet30_v*"
runOnAOD = True
#jetMinNumber2 = 3


#execfile("TopAnalysis/Configuration/analysis/fullLeptonic/analyzeZMuMuTagAndProbe_cfg.py")
execfile("analyzeZMuMuTagAndProbe_cfg.py")

process.load("TopAnalysis.Configuration.Summer12.DYJetsToLL_M_50_TuneZ2Star_8TeV_madgraph_tarball_Summer12_DR53X_PU_S10_START53_V7A_v1_cff")

process.TFileService.fileName = 'analyzeZMuMuTagAndProbeMCSummer12_HLT_IsoMu24_eta2p1.root'
process.maxEvents.input = 10000
process.MessageLogger.cerr.FwkReport.reportEvery = 10000