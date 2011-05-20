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
process.load("TopAnalysis/Configuration/samples/Run2010B1_Nov4ReReco_PAT_v5_L1Included_cff")
#process.source.fileNames = cms.untracked.vstring('/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct22-PAT/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_33_1_KUU.root')

## Lumi range (unprescaled HLT_Mu9)
process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange('132000:1-147120:1')
## Lumi Sections for synchronisation
#process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange('146644:96-146644:117')

## high level trigger filter: hltMu9
process.hltFilter.TriggerResultsTag = "TriggerResults::HLT"

## reduce output
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

## change number of processed events
process.maxEvents.input = -1
process.source.skipEvents = cms.untracked.uint32(0)

## create tuples with events surviving the cuts
## for Njets>=4
if(writeOutput):
    process.out.SelectEvents = cms.untracked.PSet( SelectEvents = cms.vstring('p1') )
    process.out.fileName = cms.untracked.string('patTuple_selectedNjets4Btag1_RunB1.root')

## change output name 
process.TFileService.fileName = 'analyzeDiffXData_B1.root'
