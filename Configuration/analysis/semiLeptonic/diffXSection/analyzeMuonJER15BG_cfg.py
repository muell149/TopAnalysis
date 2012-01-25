## ---
##    this configfile does the same like analyzeMuonDiffXSecBG_cfg.py
##    but JER are scaled up by 20% (JER variation up)
## ---

additionalEventWeights  = False
## get the mother file
execfile("analyzeMuonDiffXSecBG_cfg.py")

# JER +20%
process.scaledJetEnergy.resolutionFactors   = cms.vdouble(1.2,   1.25,   1.30  )
process.scaledJetEnergy.resolutionEtaRanges = cms.vdouble(0.,1.5,1.5,2.0,2.0,-1)
if(applyKinFit==True):
    process.kinFitTtSemiLepEventHypothesis.jetEnergyResolutionSmearFactor = 1.20

## change output name 
#process.TFileService.fileName = 'analyzeDiffXSecJERup_testBkg.root'
process.TFileService.fileName = outputFileName+"JERupPF.root"
print "output file name = ", process.TFileService.fileName