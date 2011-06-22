## ---
##    this configfile does the same like analyzeMuonDiffXSec_cfg.py
##    but JER are scaled up by 00% (JER variation down)
## ---

## get the mother file
execfile("analyzeMuonDiffXSecCorrected_cfg.py")

# JER -> +00% (default: +10%)
process.scaledJetEnergy.resolutionFactor = 1.00
if(applyKinFit==True):
    process.kinFitTtSemiLepEventHypothesis.jetEnergyResolutionSmearFactor = 1.0
    
## change output name 
process.TFileService.fileName = 'analyzeDiffXSecJERdown_testSig.root'
