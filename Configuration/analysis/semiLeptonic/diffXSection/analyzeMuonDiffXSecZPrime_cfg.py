## ---
##    this configfile does the same like analyzeMuonDiffXSecCorrected_cfg.py
##    but for Z'--> ttbar
## ---

## change gen level event filter to ttbarBG
eventFilter='signal only'

## get the mother file and adapt required changes
execfile("analyzeMuonDiffXSecCorrected_cfg.py")

pathlist = [process.p1, process.p2]
for path in pathlist:
    path.replace( process.filterSequence, process.makeGenEvt )

## reduce output
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

## change number of processed events
process.maxEvents.input = -1

## change output name 
process.TFileService.fileName = 'analyzeMuonDiffXSecCorr_ZPrime.root'
