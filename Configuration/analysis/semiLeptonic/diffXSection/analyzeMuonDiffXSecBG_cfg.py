## ---
##    this configfile does the same like analyzeMuonDiffXSecCorrected_cfg.py
##    but for ttbar BG
## ---

## change gen level event filter to ttbarBG
eventFilter='background only'
print "ttbar decay subset filter is inverted semileptonic muon decay"

## get the mother file
execfile("analyzeMuonDiffXSecCorrected_cfg.py")

## change output name 
process.TFileService.fileName = 'analyzeDiffXSecCorr_testBkg.root'
