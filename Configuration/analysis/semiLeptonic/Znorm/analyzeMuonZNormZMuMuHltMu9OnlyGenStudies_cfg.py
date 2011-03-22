## ---
##    this configfile does the same like analyzeMuonZNorm_cfg.py with modifications:
##    + ZMuMu filtering on gen level
##    + HLT Trigger Results Tag
##    + HLT_Mu9 trigger
##    + including genStudies of Z -> mu mu
## ---

## gen level event filter
genEventFilter = 'ZMuMu'

## choose whether studies of Z-> mu mu events should be performed
genStudies = 'only'

## trigger details
triggerResultsTagName = "TriggerResults::HLT"
hltPathsName = ["HLT_Mu9"]


## get the mother file
execfile("analyzeMuonZNorm_cfg.py")

## choose data set
#process.load("TopAnalysis/Configuration/samples/Run2010A_Nov4ReReco_PAT_v4_cff")


## reduce output
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

## change number of processed events
process.maxEvents.input = -1
#process.source.skipEvents = cms.untracked.uint32(0)

## change output name 
process.TFileService.fileName = 'analyzeMuonZNormZMuMuHLT_Mu9.root'
