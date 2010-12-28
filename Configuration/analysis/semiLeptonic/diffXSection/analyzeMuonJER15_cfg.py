## ---
##    this configfile does the same like analyzeMuonDiffXSec_cfg.py
##    but JER are scaled up by 20% (JER variation up)
## ---

## get the mother file
execfile("analyzeMuonDiffXSecCorrected_cfg.py")

# JER +20%
process.scaledJetEnergy.resolutionFactor = 1.20

## change output name 
process.TFileService.fileName = 'analyzeDiffXSecJERup_testSig.root'
