## ---
##    this configfile does the same like analyzeMuonDiffXSecCorrected_cfg.py
##    but is done without filtering on gen level
## ---

## remove ttbar gen level event filter
removeGenTtbar = True
eventFilter='all'

## get the mother file
execfile("analyzeMuonDiffXSecCorrected_cfg.py")

## reduce output (needed when running over QCD samples)
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

## change output name 
process.TFileService.fileName = 'analyzeDiffXSecCorr_testAll.root'
