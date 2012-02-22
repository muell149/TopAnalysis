jetType="PF"
dataSelector = 11
leptonTypeId = 13
triggerPathSelector1 = "HLT_IsoMu24_eta2p1_v*"
triggerPathSelector2 = "HLT_IsoMu17_eta2p1_TriCentralJet30_v*"
cutflowSelector = "effOnly"
jetMinNumber = 3
muonPtCut = '30.'
jsonFile = "../semiLeptonic/diffXSection/Cert_175860-178380_7TeV_PromptReco_Collisions11_JSON_afterEPS_3e33.txt"
#jsonFile = "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions11/7TeV/Reprocessing/Cert_160404-163869_7TeV_May10ReReco_Collisions11_JSON.txt"

#execfile("TopAnalysis/Configuration/analysis/fullLeptonic/analyzeZMuMuTagAndProbe_cfg.py")
execfile("analyzeCrossTriggerRatios_cfg.py")

#process.load("TopAnalysis.Configuration.samples.Run2011A_SingleMu_May10ReRecoV1_AOD_cff")
process.load("TopAnalysis/Configuration/samples/Run2011B_SingleMu_PromptRecoV1_3e33_175832-178380_AOD_cff")
#process.load("TopAnalysis/Configuration/samples/Run2011A_SingleMuPromptRecoV4_AOD_June21_cff")
#process.load("TopAnalysis.Configuration.samples.Run2011A_ElectronHadPromptRecoV4_AOD_June21_cff")
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
    #process.source.lumisToSkip = cms.untracked.VLuminosityBlockRange('100000:1-165634:1')
    #print "lumisToProcess = ", process.source.lumisToProcess

process.TFileService.fileName = 'analyzeCrossTriggerRatiosRun2011BPromptReco5e33_IsoMu24_IsoMu17TriJet_MinJet3.root'
process.maxEvents.input = 1000
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

process.highPtMuons.cut = cms.string('pt > ' + muonPtCut)
process.trackMuons.cut = cms.string('isGlobalMuon & isTrackerMuon &abs(eta) < 2.1 &innerTrack.numberOfValidHits >= 11 &globalTrack.normalizedChi2 < 10.0  &globalTrack.hitPattern.numberOfValidMuonHits>0 &abs(dB)<0.02 &innerTrack.hitPattern.pixelLayersWithMeasurement>=1 &numberOfMatches>1 &pt >' + muonPtCut)
print "trackMuonsCut = ", process.trackMuons.cut

