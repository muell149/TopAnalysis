## ---
##    this configfile does the same like analyzeMuonDiffXSecBG_cfg.py
##    but b tag SF is varied up
## ---

## get the mother file
execfile("analyzeMuonDiffXSecBG_cfg.py")

process.bTagSFEventWeight.sysVar   = "bTagSFUp"

## change output name 
process.TFileService.fileName = 'analyzeDiffXSecBTagSFUp_testBkg.root'
