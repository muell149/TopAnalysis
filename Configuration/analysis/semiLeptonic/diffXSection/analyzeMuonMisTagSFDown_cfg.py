## ---
##    this configfile does the same like analyzeMuonDiffXSec_cfg.py
##    but mistag SF is varied down
## ---

## get the mother file
execfile("analyzeMuonDiffXSecCorrected_cfg.py")

process.bTagSFEventWeight.sysVar   = "misTagSFDown"

## change output name 
process.TFileService.fileName = 'analyzeDiffXSecMisTagSFDown_testSig.root'
