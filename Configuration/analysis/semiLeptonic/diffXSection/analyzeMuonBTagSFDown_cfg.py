## ---
##    this configfile does the same like analyzeMuonDiffXSecCorrected_cfg.py
##    but b tag SF is varied down
## ---

## get the mother file
execfile("analyzeMuonDiffXSecCorrected_cfg.py")

process.bTagSFEventWeight.sysVar   = "bTagSFDown"

## change output name 
process.TFileService.fileName = 'analyzeDiffXSecBTagSFDown_testSig.root'
