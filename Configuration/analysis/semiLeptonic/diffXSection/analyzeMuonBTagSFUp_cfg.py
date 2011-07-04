## ---
##    this configfile does the same like analyzeMuonDiffXSec_cfg.py
##    but b tag SF is varied up
## ---

## get the mother file
execfile("analyzeMuonDiffXSecCorrected_cfg.py")

process.bTagSFEventWeight.sysVar   = "bTagSFUp"

## change output name 
process.TFileService.fileName = 'analyzeDiffXSecBTagSFUp_testSig.root'
