## This config performs T&P on the electron subtrigger leg of EleHadron cross triggers!!!

jetType="PF"
dataSelector = 1
leptonTypeId = 11
## CHANGE MASS WINDOW:
deltaM = 50
## This is overwritten later!!!!
triggerPathSelector = "*"
## l3 subtrigger filter which is used for T&P
filterPathSelector  = "hltEle25CaloIdVTTrkIdTCaloIsoTTrkIsoTTrackIsolFilter"

#execfile("TopAnalysis/Configuration/analysis/fullLeptonic/analyzeZMuMuTagAndProbe_cfg.py")
execfile("analyzeZMuMuTagAndProbe_cfg.py")

## ~2770 files
process.load("TopAnalysis.Configuration.Fall11.dylljetsM50_MadgraphZ2_Fall11_AOD_cff")

# change triggers!!!!
## connection of more than one path name: all HLT_Ele paths used in 2011
#process.muonTriggerMatchHLTMuons.matchedCuts = cms.string( 'path( "HLT_Ele27_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_v1" ,1,0) || path( "HLT_Ele32_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_v*" ,1,0) || path( "HLT_Ele32_WP70_v*" ,1,0)' )

## All Ele25_MultiJet triggers
#process.hltTriggerFilter.HLTPaths = ["HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralJet30_v*", "HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_DiCentralJet30_v*", "HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralJet30_v*", "HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_QuadCentralJet30_v*", "HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralJet30_BTagIP_v*"]
process.hltTriggerFilter.HLTPaths = ["HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralJet30_v*"]
    
#process.hltTriggerFilter.HLTPaths = ["HLT_Ele25_CaloIdVT_TrkIdT_CentralTriJet30_v*",
    #"HLT_Ele25_CaloIdVT_TrkIdT_TriCentralJet30_v3", "HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralJet30_v*", "HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralPFJet30_v*"]

process.TFileService.fileName = 'analyzeZEleEleTagAndProbeMCFall11_IsoEle25subTrigger.root'
process.maxEvents.input = 10000
process.MessageLogger.cerr.FwkReport.reportEvery = 10000