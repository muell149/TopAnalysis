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
## this should be executable with both leptons
## use PF2PAT
pfToPAT = True
## no event reweighting for data!
BtagReweigthing = False
PUreweigthing = False
effSFReweigthing = False
## use L2L3Residual correction in analyzers
corrLevel="L2L3Residual"
## JSON file
jsonFile = 'Cert_194270-196531_8TeV_13Jul2012ReReco_Collisions12_JSON_v2_3885pbRunBonly.txt'

## get the mother file
execfile("analyzeTopDiffXSec_cfg.py")

## choose data set
if(decayChannel == 'muon'):
    process.load("TopAnalysis/Configuration/samples/SingleMu_Run2012B_13Jul2012_v1_cff")
elif(decayChannel == 'electron'):
    process.load("TopAnalysis/Configuration/samples/SingleElectron_Run2012B_13Jul2012_v1_cff")
else:
    print "ERROR: chosen decay channel is not valid"
    
## choose unprescaled trigger
process.hltFilter.TriggerResultsTag = "TriggerResults::HLT"
if(decayChannel == 'muon'):
    process.hltFilter.HLTPaths = ["HLT_IsoMu24_eta2p1_v*"]
elif(decayChannel == 'electron'):
     process.hltFilter.HLTPaths = ["HLT_Ele27_WP80_v*"]

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

## global tag: set in main cfg

## reduce output
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

## change number of processed events: process them all
#process.maxEvents.input = -1 #FIXME: for testing
process.source.skipEvents = cms.untracked.uint32(0)

## create tuples with events surviving the cuts
## for Njets>=4
if(writeOutput):
    process.out.SelectEvents = cms.untracked.PSet( SelectEvents = cms.vstring('p1') )
    process.out.fileName = cms.untracked.string('patTuple_selectedNjets4Btag1_Run2012B.root')

## change output name
if(decayChannel == 'muon'):
    process.TFileService.fileName = 'analyzeDiffXData2012BMuon.root'
elif(decayChannel == 'electron'):
    process.TFileService.fileName = 'analyzeDiffXData2012BElec.root'
