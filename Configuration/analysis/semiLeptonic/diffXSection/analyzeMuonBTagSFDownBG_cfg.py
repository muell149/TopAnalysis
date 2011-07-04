## ---
##    this configfile does the same like analyzeMuonDiffXSecBG_cfg.py
##    but b tag SF is varied down
## ---

## get the mother file
execfile("analyzeMuonDiffXSecBG_cfg.py")

process.bTagSFEventWeight.sysVar   = "bTagSFDown"

## change output name 
process.TFileService.fileName = 'analyzeDiffXSecBTagSFDown_testBkg.root'
