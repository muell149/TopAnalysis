jetType="PF"
dataSelector = 11
leptonTypeId = 11
triggerPathSelector1 = "HLT_Ele27_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_v*"
triggerPathSelector2 = "HLT_Ele25_CaloIdVT_TrkIdT_CentralTriJet30_v*"
cutflowSelector = "effOnly"
#jsonFile = "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions11/7TeV/Prompt/Cert_160404-167151_7TeV_PromptReco_Collisions11_JSON.txt"
jsonFile = "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions11/7TeV/Reprocessing/Cert_160404-163869_7TeV_May10ReReco_Collisions11_JSON_v3.txt"

#execfile("TopAnalysis/Configuration/analysis/fullLeptonic/analyzeZMuMuTagAndProbe_cfg.py")
execfile("analyzeCrossTriggerRatios_cfg.py")

process.load("TopAnalysis.Configuration.samples.Run2011A_SingleEle_May10ReRecoV1_AOD_cff")
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
    #process.source.lumisToSkip = cms.untracked.VLuminosityBlockRange('167151:3-999999:1')
    #print "lumisToProcess = ", process.source.lumisToProcess

process.TFileService.fileName = 'analyzeCrossTriggerRatiosRun2011AV1ReReco_IsoEle27_Ele25TriJet.root'
process.maxEvents.input = 1000
process.MessageLogger.cerr.FwkReport.reportEvery = 10000
