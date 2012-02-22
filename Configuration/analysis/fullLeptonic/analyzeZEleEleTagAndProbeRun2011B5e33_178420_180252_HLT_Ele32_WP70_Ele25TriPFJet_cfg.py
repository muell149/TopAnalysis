jetType="PF"
dataSelector = 11
leptonTypeId = 11
triggerPathSelector = "HLT_Ele32_WP70_v*"
#filterPathSelector = "hltSingleMu15L3Filtered15"
triggerPathSelector2 = "HLT_IsoMu17_TriCentralJet30_v*"
#triggerPathSelector2 = "HLT_Mu_24_v*"
muonPtCut = 30.
jetMinNumber2 = 3

jsonFile = "../semiLeptonic/diffXSection/Cert_160404-180252_7TeV_PromptReco_ReReco_Combined_Collisions11_JSON_modified.txt"
#jsonFile = "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions11/7TeV/Reprocessing/Cert_160404-163869_7TeV_May10ReReco_Collisions11_JSON.txt"


#execfile("TopAnalysis/Configuration/analysis/fullLeptonic/analyzeZMuMuTagAndProbe_cfg.py")
execfile("analyzeZMuMuTagAndProbe_cfg.py")

#process.load("TopAnlaysis.Configuration.samples.Run2011A_SingleMu_PromptRecoV4_AOD_cff")
##~1550 files
process.load("TopAnalysis/Configuration/samples/Run2011B_SingleEle_PromptRecoV1_5e33_AOD_cff")

# change second triggers!!!!
process.hltTriggerFilter2.HLTPaths = ["HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralPFJet30_v*"]

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
process.TFileService.fileName = 'analyzeZEleEleTagAndProbeRun2011AB_178420_180252_HLT_Ele32_WP70_IsoEle25TriJet.root'
process.maxEvents.input = 10000
process.MessageLogger.cerr.FwkReport.reportEvery = 10000