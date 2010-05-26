## ---
##    this configfile does the same like analyzeMuonDiffXSec_cfg.py
##    but for data - therefore all gen-plots are thrown out 
## ---

## switch to reco plots only
## -----------------------------
## note: it is important to have
## this definition before the
## execution of the mother file
runningOnData = "data"

## get the mother file
execfile("/afs/naf.desy.de/user/g/goerner/semileptonic356/analyzeMuonDiffXSecAll_cfg.py")

## change output name 
process.TFileService.fileName = 'analyzeDiffXData_test.root'
