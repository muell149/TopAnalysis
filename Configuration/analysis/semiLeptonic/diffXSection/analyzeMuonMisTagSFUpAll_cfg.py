## ---
##    this configfile does the same like analyzeMuonDiffXSecAll_cfg.py
##    but mistag SF is varied up
## ---

## get the mother file
execfile("analyzeMuonDiffXSecAll_cfg.py")

process.bTagSFEventWeight.sysVar   = "misTagSFUp"

## change output name 
process.TFileService.fileName = 'analyzeDiffXSecMisTagSFUp_testAll.root'
