## ---
##    this configfile does the same like analyzeMuonDiffXSecAll_cfg.py
##    but mistag SF is varied down
## ---

## get the mother file
execfile("analyzeMuonDiffXSecAll_cfg.py")

process.bTagSFEventWeight.sysVar   = "misTagSFDown"

## change output name 
process.TFileService.fileName = 'analyzeDiffXSecMisTagSFDown_testAll.root'
