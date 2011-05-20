
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
    
## execute mother file
execfile("analyzeTopDiffXSec_cfg.py")

## choose data set
process.load("TopAnalysis/Configuration/samples/Run2010A_Nov4ReReco_PAT_v5_L1Included_cff")

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
    process.out.fileName = cms.untracked.string('patTuple_selectedNjets4Btag1_RunA.root')

## change output name 
process.TFileService.fileName = 'analyzeDiffXData_A.root'
