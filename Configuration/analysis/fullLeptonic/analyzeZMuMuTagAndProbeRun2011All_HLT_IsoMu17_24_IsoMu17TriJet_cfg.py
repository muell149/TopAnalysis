jetType="PF"
dataSelector = 11
leptonTypeId = 13
triggerPathSelector = "HLT_IsoMu24_eta2p1_v*"
#filterPathSelector = "hltSingleMu15L3Filtered15"
triggerPathSelector2 = "HLT_IsoMu17_eta2p1_TriCentralPFJet30_v*"
#triggerPathSelector2 = "HLT_Mu_24_v*"
jetMinNumber2 = 3

jsonFile = "../semiLeptonic/diffXSection/Cert_160404-180252_7TeV_PromptReco_ReReco_Combined_Collisions11_JSON_modified.txt"
#jsonFile = "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions11/7TeV/Reprocessing/Cert_160404-163869_7TeV_May10ReReco_Collisions11_JSON.txt"


#execfile("TopAnalysis/Configuration/analysis/fullLeptonic/analyzeZMuMuTagAndProbe_cfg.py")
execfile("analyzeZMuMuTagAndProbe_cfg.py")

## connection of more than one path name: all IsoMu paths used in 2011
process.muonTriggerMatchHLTMuons.matchedCuts = cms.string( 'path( "HLT_IsoMu17_v5" ,1,0) || path( "HLT_IsoMu17_v6" ,1,0) || path( "HLT_IsoMu17_v8" ,1,0) || path( "HLT_IsoMu17_v9" ,1,0) || path( "HLT_IsoMu17_v10" ,1,0) || path( "HLT_IsoMu17_v11" ,1,0) || path( "HLT_IsoMu24_v8" ,1,0) || path( "HLT_IsoMu24_eta2p1_v*" ,1,0)' )
process.hltTriggerFilter.HLTPaths = ["HLT_IsoMu17_v5", "HLT_IsoMu17_v6", "HLT_IsoMu17_v8", "HLT_IsoMu17_v9", "HLT_IsoMu17_v10", "HLT_IsoMu17_v11", "HLT_IsoMu24_v8", "HLT_IsoMu24_eta2p1_v*"]
process.hltTriggerFilter2.HLTPaths = ["HLT_Mu17_TriCentralJet30_v*", "HLT_IsoMu17_TriCentralJet30_v*", "HLT_IsoMu17_eta2p1_TriCentralJet30_v*", "HLT_IsoMu17_eta2p1_TriCentralPFJet30_v*"]



#process.load("TopAnalysis.Configuration.samples.Run2011A_SingleMu_PromptRecoV4_AOD_cff")
process.load("TopAnalysis/Configuration/samples/Run2011All_SingleMu_160404_180252_AOD_cff")

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
process.TFileService.fileName = 'analyzeZMuMuTagAndProbeRun2011All_HLT_IsoMu17_24_IsoMu17TriJet.root'
process.maxEvents.input = 10000
process.MessageLogger.cerr.FwkReport.reportEvery = 10000