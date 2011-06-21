## ---
##    this configfile does the same like analyzeMuonDiffXSec_cfg.py
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
## use L2L3Residual correction in analyzers
corrLevel="L2L3Residual"

## get the mother file
execfile("analyzeTopDiffXSec_cfg.py")

## choose data set
process.load("TopAnalysis/Configuration/samples/Run2011A_ElectronHadPromptRecoV1and2combined_JsonMay13_newJEC_cff")

##TopAnalysis/Configuration/samples/Run2011A_MuHadPromptReco_160404_to_163369_v2_cff"
## high level trigger filter: hltMu15 (HLT_Mu9 prescaled
process.hltFilter.TriggerResultsTag = "TriggerResults::HLT"
process.hltFilter.HLTPaths = ["HLT_Ele25_CaloIdVT_TrkIdT_CentralTriJet30_v*"]
# Lumi range (exclude range of unprescaled HLT_Mu9)
#process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange('147120:1-999999:1')

## reduce output
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

## change number of processed events
process.maxEvents.input = -1
process.source.skipEvents = cms.untracked.uint32(0)

## create tuples with events surviving the cuts
## for Njets>=4
if(writeOutput):
    process.out.SelectEvents = cms.untracked.PSet( SelectEvents = cms.vstring('p1') )
    process.out.fileName = cms.untracked.string('patTuple_selectedNjets4Btag2_Run2011.root')

## change output name 
process.TFileService.fileName = 'analyzeDiffXData2011_ElectronHad_160404-161312.root'
