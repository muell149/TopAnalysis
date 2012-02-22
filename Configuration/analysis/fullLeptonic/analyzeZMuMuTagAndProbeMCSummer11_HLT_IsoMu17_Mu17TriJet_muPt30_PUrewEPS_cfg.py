jetType="PF"
dataSelector = 1
leptonTypeId = 13
triggerPathSelector = "HLT_IsoMu17_v*"
#filterPathSelector = "hltSingleMu15L3Filtered15"
triggerPathSelector2 = "HLT_Mu17_TriCentralJet30_v*"
runOnAOD = True
muonPtCut = 30.
jetMinNumber2 = 3


#execfile("TopAnalysis/Configuration/analysis/fullLeptonic/analyzeZMuMuTagAndProbe_cfg.py")
execfile("analyzeZMuMuTagAndProbe_cfg.py")

process.load("TopAnalysis.Configuration.dylljetsM50_MadgraphZ2_Summer11_AOD_cff")

process.TFileService.fileName = 'analyzeZMuMuTagAndProbeMCSummer11_HLT_IsoMu17_Mu17TriJet_muPt30_PUrewEPS.root'
process.maxEvents.input = 10000
process.MessageLogger.cerr.FwkReport.reportEvery = 10000