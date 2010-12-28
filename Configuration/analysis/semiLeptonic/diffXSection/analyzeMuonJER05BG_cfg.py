## ---
##    this configfile does the same like analyzeMuonDiffXSecBG_cfg.py
##    but JER are scaled up by 00% (JER variation down)
## ---

## get the mother file
execfile("analyzeMuonDiffXSecBG_cfg.py")

# JER -> +00% (default: +10%)
process.scaledJetEnergy.resolutionFactor = 1.00

## change output name 
process.TFileService.fileName = 'analyzeDiffXSecJERdown_testBkg.root'
