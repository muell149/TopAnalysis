## ---
##    this configfile does the same like analyzeMuonDiffXSec_cfg.py
##    but mistag SF is varied up
## ---

## get the mother file
execfile("analyzeMuonDiffXSecCorrected_cfg.py")

process.bTagSFEventWeight.sysVar   = "misTagSFUp"

## change output name 
process.TFileService.fileName = 'analyzeDiffXSecMisTagSFUp_testSig.root'
