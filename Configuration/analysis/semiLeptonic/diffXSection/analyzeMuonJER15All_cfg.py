## ---
##    this configfile does the same like analyzeMuonDiffXSecAll_cfg.py
##    but JER are scald up by 20% (JER variation up)
## ---

## get the mother file
execfile("analyzeMuonDiffXSecAll_cfg.py")

# JER +20%
process.scaledJetEnergy.resolutionFactor = 1.20

## change output name 
process.TFileService.fileName = 'analyzeDiffXSecJERup_testAll.root'
