## ---
##    this configfile does the same like analyzeMuonDiffXSec_cfg.py
##    but shifting JES down and for ttbar BG (filtered on gen level)
## ---

## get the mother file
execfile("analyzeMuonDiffXSecBG_cfg.py")

# JES down
process.scaledJetEnergy.scaleType   = "top:down"
process.scaledJetEnergy.scaleFactor = 0.982
if(jetType=="particleFlow"):
    process.scaledJetEnergy.payload = "AK5PF"
elif(jetType=="Calo"):
    process.scaledJetEnergy.payload = "AK5Calo"
else:
    print "unknown jetType"

## change output name 
process.TFileService.fileName = 'analyzeDiffXSecJESDown_testBkg.root'
