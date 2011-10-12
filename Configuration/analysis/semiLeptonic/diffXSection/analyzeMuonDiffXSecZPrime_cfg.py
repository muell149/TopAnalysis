## ---
##    this configfile does the same like analyzeMuonDiffXSecCorrected_cfg.py
##    but for Z'--> ttbar
## ---

## change gen level event filter to ttbarBG
eventFilter='signal only'

## get the mother file
execfile("analyzeMuonDiffXSecCorrected_cfg.py")

## reduce output
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

## change number of processed events
process.maxEvents.input = -1

## change output name 
process.TFileService.fileName = 'analyzeMuonDiffXSecCorr_ZPrime.root'
