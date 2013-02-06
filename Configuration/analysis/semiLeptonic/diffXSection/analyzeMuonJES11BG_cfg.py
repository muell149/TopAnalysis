## ---
##    this configfile does the same like analyzeMuonDiffXSec_cfg.py
##    but shifting JES up and for ttbar BG (filtered on gen level)
## ---

additionalEventWeights  = False
## get the mother file
execfile("analyzeMuonDiffXSecBG_cfg.py")

# JES up
process.scaledJetEnergy.scaleType   = "jes:up"
#process.scaledJetEnergy.scaleFactor = 1.015
if(jetType=="particleFlow"):
    process.scaledJetEnergy.payload = "AK5PF"
elif(jetType=="Calo"):
    process.scaledJetEnergy.payload = "AK5Calo"
else:
    print "unknown jetType"
process.scaledJetEnergy.JECUncSrcFile = "TopAnalysis/TopUtils/data/Fall12_V7_DATA_UncertaintySources_AK5PFchs.txt"

## change output name 
#process.TFileService.fileName = 'analyzeDiffXSecJESUp_testBkg.root'
process.TFileService.fileName = outputFileNamePart+"JESUp"+options.mctag+"PF.root"
print "output file name = ", process.TFileService.fileName
