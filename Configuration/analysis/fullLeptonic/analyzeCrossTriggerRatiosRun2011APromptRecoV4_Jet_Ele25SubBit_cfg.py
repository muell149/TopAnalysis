jetType="PF"
dataSelector = 11
leptonTypeId = 11
triggerPathSelector1 = "*"
triggerPathSelector2 = "*"
cutflowSelector = "effOnly"

jetMinNumber = 0

l3FilterSelector = "hltEle25CaloIdVTTrkIdTDphiFilter"

jsonFile = "../semiLeptonic/diffXSection/Cert_160404-180252_7TeV_PromptReco_ReReco_Combined_Collisions11_JSON_modified.txt"

#execfile("TopAnalysis/Configuration/analysis/fullLeptonic/analyzeZMuMuTagAndProbe_cfg.py")
execfile("analyzeCrossTriggerRatios_cfg.py")

process.load("TopAnalysis.Configuration.samples.Run2011A_Jet_PromptRecoV4_165088_165633_Trig1_AOD_cff")
#process.load("TopAnalysis.Configuration.samples.Run2011A_ElectronHad_PromptRecoV4_165970_latest_Trig2_AOD_cff")
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

#from HLTrigger.HLTfilters.hltSummaryFilter_cfi import *
#process.hltL3Filter = hltSummaryFilter.clone(member = "hltEle25CaloIdVTTrkIdTCaloIsoTTrkIsoTTrackIsolFilter", cut="")

#from TopAnalysis.TopFilter.filters.TriggerFilterFilter_cfi import filterTriggerFilters
#process.hltL3Filter = filterTriggerFilters.clone()
#process.p1.insert(0,process.patTriggerSequenceUser*process.hltL3Filter *process.hltTriggerFilter1)

process.TFileService.fileName = 'analyzeCrossTriggerRatiosRun2011APromptRecoV4_165088_165633_Trig1_Jet_Ele25TriJet.root'
process.maxEvents.input = 10000
process.MessageLogger.cerr.FwkReport.reportEvery = 10000
