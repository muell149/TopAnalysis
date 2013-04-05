## ---
##    this configfile does the same like analyzeMuonDiffXSecAll_cfg.py
##    but JER are scaled up by 00% (JER variation down)
## ---

additionalEventWeights  = False
## get the mother file
execfile("analyzeMuonDiffXSecAll_cfg.py")

# eta-dependent smearing of the jet energy
process.scaledJetEnergy.resolutionFactors   = cms.vdouble( 0.990 , 1.001 , 1.032 , 1.042 , 1.089 )
#process.scaledJetEnergy.resolutionEtaRanges = cms.vdouble(0.0,0.5,0.5,1.1,1.1,1.7,1.7,2.3,2.3,-1.)

## change output name 
#process.TFileService.fileName = 'analyzeDiffXSecJERdown_testAll.root'
process.TFileService.fileName = outputFileNamePart+"JERDown"+options.mctag+"PF.root"
print "output file name = ", process.TFileService.fileName
