## ---
##    this configfile does the same like analyzeMuonZNorm_cfg.py with modifications:
##    + without filtering on gen level
##    + REDIGI38XPU Trigger Results Tag
##    + REDIGI38XPU_Mu9 trigger
## ---

## gen level event filter
genEventFilter = 'all'

## choose whether studies of Z-> mu mu events should be performed
genStudies = 'no'

## trigger details
triggerResultsTagName = "TriggerResults::REDIGI38XPU"
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
process.TFileService.fileName = 'analyzeMuonZNormAllRedigi38XPu_Mu9.root'
