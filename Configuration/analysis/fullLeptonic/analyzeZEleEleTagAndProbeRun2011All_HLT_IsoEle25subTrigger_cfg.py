## This config performs T&P on the electron subtrigger leg of EleHadron cross triggers!!!

jetType="PF"
dataSelector = 11
leptonTypeId = 11
## This is overwritten later!!!!
triggerPathSelector = "*"
## l3 subtrigger filter which is used for T&P
filterPathSelector  = "hltEle25CaloIdVTTrkIdTCaloIsoTTrkIsoTTrackIsolFilter"


jsonFile = "../semiLeptonic/diffXSection/Cert_160404-180252_7TeV_PromptReco_ReReco_Combined_Collisions11_JSON_modified.txt"
#jsonFile = "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions11/7TeV/Reprocessing/Cert_160404-163869_7TeV_May10ReReco_Collisions11_JSON.txt"


#execfile("TopAnalysis/Configuration/analysis/fullLeptonic/analyzeZMuMuTagAndProbe_cfg.py")
execfile("analyzeZMuMuTagAndProbe_cfg.py")

## 1119
#process.load("TopAnalysis/Configuration/samples/Run2011A_ElectronHad_PromptRecoV4_165970_latest_Trig2_AOD_cff")
##
process.load("Run2011PostEPS_ElectronHad_Aug05ReRecoV1_AV6_BV1_170053_180252_AOD_cff.py")

# change triggers!!!!
## connection of more than one path name: all HLT_Ele paths used in 2011
#process.muonTriggerMatchHLTMuons.matchedCuts = cms.string( 'path( "HLT_Ele27_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_v1" ,1,0) || path( "HLT_Ele32_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_v*" ,1,0) || path( "HLT_Ele32_WP70_v*" ,1,0)' )

## All Ele25_MultiJet triggers
#process.hltTriggerFilter.HLTPaths = ["HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralJet30_v*", "HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_DiCentralJet30_v*", "HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralJet30_v*", "HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_QuadCentralJet30_v*", "HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralJet30_BTagIP_v*"]
process.hltTriggerFilter.HLTPaths = ["HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralJet30_v*"]
    
#process.hltTriggerFilter.HLTPaths = ["HLT_Ele25_CaloIdVT_TrkIdT_CentralTriJet30_v*",
    #"HLT_Ele25_CaloIdVT_TrkIdT_TriCentralJet30_v3", "HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralJet30_v*", "HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralPFJet30_v*"]

# Lumi range
## ATTENTION!!! At the moment myLumis are filled in this data_cfg files again
## as otherwise overwritten by load("data_cff")
if(jsonFile==''):
    print "No JSON file used"
    #process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange('160404:1-999999:1')
    #print "lumisToProcess = ", process.source.lumisToProcess
else:
    process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange()
    process.source.lumisToProcess.extend(myLumis)
    ## Use lumisToSkip if JSON file shall be constrained additionally to a certain run range
    #process.source.lumisToSkip = cms.untracked.VLuminosityBlockRange('165634:1-999999:1')
    #print "lumisToProcess = ", process.source.lumisToProcess
process.TFileService.fileName = 'analyzeZEleEleTagAndProbeRun2011AEPS_IsoEle25subTrigger.root'
process.maxEvents.input = 10000
process.MessageLogger.cerr.FwkReport.reportEvery = 10000