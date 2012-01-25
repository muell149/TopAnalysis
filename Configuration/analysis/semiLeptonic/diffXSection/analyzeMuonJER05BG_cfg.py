## ---
##    this configfile does the same like analyzeMuonDiffXSecBG_cfg.py
##    but JER are scaled up by 00% (JER variation down)
## ---

additionalEventWeights  = False
## get the mother file
execfile("analyzeMuonDiffXSecBG_cfg.py")

# JER -> +00% (default: +10%)
# JER -> +00% (default: +10%)
process.scaledJetEnergy.resolutionFactors   = cms.vdouble(1.0,   0.95,   0.9   )
process.scaledJetEnergy.resolutionEtaRanges = cms.vdouble(0.,1.5,1.5,2.0,2.0,-1)
if(applyKinFit==True):
    process.kinFitTtSemiLepEventHypothesis.jetEnergyResolutionSmearFactor = 1.0

## change output name 
#process.TFileService.fileName = 'analyzeDiffXSecJERdown_testBkg.root'
process.TFileService.fileName = outputFileName+"JERdownPF.root"
print "output file name = ", process.TFileService.fileName