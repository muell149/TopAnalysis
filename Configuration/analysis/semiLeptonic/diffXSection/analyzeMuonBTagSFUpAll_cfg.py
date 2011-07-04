## ---
##    this configfile does the same like analyzeMuonDiffXSecAll_cfg.py
##    but b tag SF is varied up
## ---

## get the mother file
execfile("analyzeMuonDiffXSecAll_cfg.py")

process.bTagSFEventWeight.sysVar   = "bTagSFUp"

## change output name 
process.TFileService.fileName = 'analyzeDiffXSecBTagSFUp_testAll.root'
