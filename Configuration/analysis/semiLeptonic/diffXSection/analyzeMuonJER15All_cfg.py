## ---
##    this configfile does the same like analyzeMuonDiffXSecAll_cfg.py
##    but JER are scald up by 15% (JER variation down)
## ---

## get the mother file
execfile("analyzeMuonDiffXSecAll_cfg.py")

# JER +15%
process.scaledJetEnergy.resolutionFactor = 1.15

## change output name 
process.TFileService.fileName = 'analyzeDiffXSecJER15_testAll.root'
