## ---
##    this configfile does the same like analyzeMuonDiffXSec_cfg.py
##    but is done withot filtering on gen level
## ---

## get the mother file
execfile("/afs/naf.desy.de/user/g/goerner/semileptonic356/analyzeMuonDiffXSec_cfg.py")

## kick out gen level event filter
process.filterSequence = cms.Sequence(process.hltMu9)

## reduce output (needed when running over QCD samples)
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

## change output name 
process.TFileService.fileName = 'analyzeDiffXSec_testAll.root'
