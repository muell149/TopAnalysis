## ---
##    this configfile does the same like analyzeTopDiffXSec_cfg.py
##    but for data - therefore all gen-plots are thrown out
## ---

## switch to reco plots only
## -----------------------------
## note: it is important to have
## this definitions before the
## execution of the mother file
runningOnData = "data"
eventFilter='all'
removeGenTtbar=True
## output
writeOutput = False
## extend functionality
applyKinFit = True
implement0TagPath = True
## use correct leptons
decayChannel = 'muon'
## use PF2PAT
pfToPAT = True
## no event reweighting for data!
BtagReweigthing = False
PUreweigthing = False
effSFReweigthing = False
## use L2L3Residual correction in analyzers
corrLevel="L2L3Residual"
## JSON file
jsonFile =  'Cert_160404-180252_7TeV_PromptReco_ReReco_Combined_Collisions11_JSON_modified.txt'

## get the mother file
execfile("analyzeTopDiffXSec_cfg.py")

## choose data set
process.load("TopAnalysis/Configuration/samples/Run2011PostEPS_SingleMu_Aug05ReReco_AV6_BV1_170053_180252_AOD_cff")

## choose unprescaled trigger
process.hltFilter.TriggerResultsTag = "TriggerResults::HLT"
process.hltFilter.HLTPaths = ["HLT_IsoMu24_v8", "HLT_IsoMu24_eta2p1_v*"]

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

# global tag
#process.GlobalTag.globaltag = cms.string( autoCond[ 'com10' ] )
#process.GlobalTag.globaltag = cms.string('GR_R_42_V13::All')

## reduce output
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

## change number of processed events
process.maxEvents.input = options.eventsToProcess
process.source.skipEvents = cms.untracked.uint32(0)

## create tuples with events surviving the cuts
## for Njets>=4
if(writeOutput):
    process.out.SelectEvents = cms.untracked.PSet( SelectEvents = cms.vstring('p1') )
    process.out.fileName = cms.untracked.string('patTuple_selectedNjets4Btag1_Run2011AReReco.root')

## change output name 
process.TFileService.fileName = 'analyzeDiffXData2011PostEPSCombinedMuon.root'