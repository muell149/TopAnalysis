## ---
##    this configfile does the same like analyzeMuonDiffXSecAll_cfg.py
##    but JER are scaled up by 05% (JER variation down)
## ---

## get the mother file
execfile("analyzeMuonDiffXSecAll_cfg.py")

# JER -> +05%
process.scaledJetEnergy.resolutionFactor = 1.05

## change output name 
process.TFileService.fileName = 'analyzeDiffXSecJER05_testAll.root'
