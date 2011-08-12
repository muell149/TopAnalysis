## ---
##    this configfile does the same like analyzeMuonDiffXSec_cfg.py
##    but shifting JES down
## ---

additionalEventWeights  = False
## get the mother file
execfile("analyzeMuonDiffXSecCorrected_cfg.py")

# JES down
process.scaledJetEnergy.scaleType   = "jes:down"
#process.scaledJetEnergy.scaleFactor = 0.985
if(jetType=="particleFlow"):
    process.scaledJetEnergy.payload = "AK5PF"
elif(jetType=="Calo"):
    process.scaledJetEnergy.payload = "AK5Calo"
else:
    print "unknown jetType"

## change output name 
process.TFileService.fileName = 'analyzeDiffXSecJESDown_testSig.root'
