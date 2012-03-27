## ---
##    this configfile does the same like analyzeMuonDiffXSec_cfg.py
##    but JER are scaled up by 00% (JER variation down)
## ---

additionalEventWeights  = False
## get the mother file
execfile("analyzeMuonDiffXSecCorrected_cfg.py")

# JER -> +00% (default: +10%)
process.scaledJetEnergy.resolutionFactors   = cms.vdouble(0.990, 1.001, 1.032, 1.042, 1.089)
process.scaledJetEnergy.resolutionEtaRanges = cms.vdouble(0.0,0.5,0.5,1.1,1.1,1.7,1.7,2.3,2.3,-1.)
if(applyKinFit==True):
    process.kinFitTtSemiLepEventHypothesis.jetEnergyResolutionSmearFactor = 1.0126
    
## change output name 
#process.TFileService.fileName = 'analyzeDiffXSecJERdown_testSig.root'
process.TFileService.fileName = outputFileName+"JERdownPF.root"
print "output file name = ", process.TFileService.fileName
