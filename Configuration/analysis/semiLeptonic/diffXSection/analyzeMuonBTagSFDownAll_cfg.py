## ---
##    this configfile does the same like analyzeMuonDiffXSecAll_cfg.py
##    but b tag SF is varied down
## ---

## get the mother file
execfile("analyzeMuonDiffXSecAll_cfg.py")

process.bTagSFEventWeight.sysVar   = "bTagSFDown"

## change output name 
process.TFileService.fileName = 'analyzeDiffXSecBTagSFDown_testAll.root'
