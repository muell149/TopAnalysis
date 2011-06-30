## ---
##    this configfile does the same like analyzeMuonDiffXSecAll_cfg.py
##    but JER are scald up by 20% (JER variation up)
## ---

## get the mother file
execfile("analyzeMuonDiffXSecAll_cfg.py")

# JER +20%
process.scaledJetEnergy.resolutionFactors   = cms.vdouble(1.2,   1.25,   1.30  )
process.scaledJetEnergy.resolutionEtaRanges = cms.vdouble(0.,1.5,1.5,2.0,2.0,-1)
if(applyKinFit==True):
    process.kinFitTtSemiLepEventHypothesis.jetEnergyResolutionSmearFactor = 1.20

## change output name 
process.TFileService.fileName = 'analyzeDiffXSecJERup_testAll.root'
