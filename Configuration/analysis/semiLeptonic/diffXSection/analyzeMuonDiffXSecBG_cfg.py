## ---
##    this configfile does the same like analyzeMuonDiffXSecCorrected_cfg.py
##    but for ttbar BG
## ---

## get the mother file
execfile("analyzeMuonDiffXSecCorrected_cfg.py")

## change gen level event filter to ttbarBG
process.ttSemiLeptonicFilter.invert = True
process.ttSemiLeptonicFilterb.invert = True

print "ttbar decay subset filter is inverted semileptonic muon decay" 

## change output name 
process.TFileService.fileName = 'analyzeDiffXSecCorr_testBkg.root'
