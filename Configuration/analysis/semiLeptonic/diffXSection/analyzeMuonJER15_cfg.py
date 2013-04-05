## ---
##    this configfile does the same like analyzeMuonDiffXSec_cfg.py
##    but JER are scaled up by 20% (JER variation up)
## ---

additionalEventWeights  = False
## get the mother file
execfile("analyzeMuonDiffXSecCorrected_cfg.py")

# eta-dependent smearing of the jet energy
process.scaledJetEnergy.resolutionFactors   = cms.vdouble( 1.115 , 1.114 , 1.161 , 1.228 , 1.488 )
#process.scaledJetEnergy.resolutionEtaRanges = cms.vdouble(0.0,0.5,0.5,1.1,1.1,1.7,1.7,2.3,2.3,-1.)

## change output name 
#process.TFileService.fileName = 'analyzeDiffXSecJERup_testSig.root'
process.TFileService.fileName = outputFileNamePart+"JERUp"+options.mctag+"PF.root"
print "output file name = ", process.TFileService.fileName
