jetType="PF"
dataSelector = 1
leptonTypeId = 13
triggerPathSelector = "HLT_IsoMu24_eta2p1_v*"
#filterPathSelector = "hltSingleMu15L3Filtered15"
triggerPathSelector2 = "HLT_IsoMu17_eta2p1_TriCentralJet30_v*"
runOnAOD = True
jetMinNumber2 = 3


#execfile("TopAnalysis/Configuration/analysis/fullLeptonic/analyzeZMuMuTagAndProbe_cfg.py")
execfile("analyzeZMuMuTagAndProbe_cfg.py")

process.load("TopAnalysis.Configuration.Fall11.dylljetsM50_MadgraphZ2_Fall11_AOD_cff")

process.TFileService.fileName = 'analyzeZMuMuTagAndProbeMCFall11_HLT_IsoMu24_eta2p1_IsoMu17eta2p1TriJet.root'
process.maxEvents.input = 10000
process.MessageLogger.cerr.FwkReport.reportEvery = 10000