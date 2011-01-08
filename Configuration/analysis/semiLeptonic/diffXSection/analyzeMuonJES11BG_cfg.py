## ---
##    this configfile does the same like analyzeMuonDiffXSec_cfg.py
##    but shifting JES up and for ttbar BG (filtered on gen level)
## ---

## get the mother file
execfile("analyzeMuonDiffXSecBG_cfg.py")

# JES up
process.scaledJetEnergy.scaleType   = "top:up"
process.scaledJetEnergy.scaleFactor = 1.053
if(jetType=="particleFlow"):
    process.scaledJetEnergy.payload = "AK5PF"
elif(jetType=="Calo"):
    process.scaledJetEnergy.payload = "AK5Calo"
else:
    print "unknown jetType"

## change output name 
process.TFileService.fileName = 'analyzeDiffXSecJESUp_testBkg.root'
