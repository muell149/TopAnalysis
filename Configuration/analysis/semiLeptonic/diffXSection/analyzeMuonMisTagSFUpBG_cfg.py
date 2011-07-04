## ---
##    this configfile does the same like analyzeMuonDiffXSecBG_cfg.py
##    but mistag SF is varied up
## ---

## get the mother file
execfile("analyzeMuonDiffXSecBG_cfg.py")

process.bTagSFEventWeight.sysVar   = "misTagSFUp"

## change output name 
process.TFileService.fileName = 'analyzeDiffXSecMisTagSFUp_testBkg.root'
