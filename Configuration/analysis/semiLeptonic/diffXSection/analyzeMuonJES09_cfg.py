## ---
##    this configfile does the same like analyzeMuonDiffXSec_cfg.py
##    but shifting JES down
## ---

## get the mother file
execfile("analyzeMuonDiffXSecCorrected_cfg.py")

# JES down
process.scaledJetEnergy.scaleType   = "top:down"
process.scaledJetEnergy.scaleFactor = 0.975
if(jetType=="particleFlow"):
    process.scaledJetEnergy.payload = "AK5PF"
elif(jetType=="Calo"):
    process.scaledJetEnergy.payload = "AK5Calo"
else:
    print "unknown jetType"

## change output name 
process.TFileService.fileName = 'analyzeDiffXSecJESDown_testSig.root'
