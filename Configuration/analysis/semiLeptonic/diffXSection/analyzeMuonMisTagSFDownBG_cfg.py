## ---
##    this configfile does the same like analyzeMuonDiffXSecBG_cfg.py
##    but mistag SF is varied down
## ---

## get the mother file
execfile("analyzeMuonDiffXSecBG_cfg.py")

process.bTagSFEventWeight.sysVar   = "misTagSFDown"

## change output name 
process.TFileService.fileName = 'analyzeDiffXSecMisTagSFDown_testBkg.root'
