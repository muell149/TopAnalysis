## ---
##    this configfile does the same like analyzeMuonDiffXSec_cfg.py
##    but is done withot filtering on gen level
## ---

## get the mother file
execfile("/afs/naf.desy.de/user/g/goerner/semileptonic361/analyzeMuonDiffXSec_cfg.py")

## remove gen level event filter
process.filterSequence  = cms.Sequence(process.hltMu9)
process.filterSequenceb = cms.Sequence(process.hltMu9b)
process.filterSequenceABCD = cms.Sequence(process.hltMu9ABCD)
process.p4.remove(process.genFilterSequence)
print "all gen level filters using ttbar decay subset are removed" 
print "selection for gen plots only via TopAnalysis.TopFilter.sequences.genSelection_cff"

## reduce output (needed when running over QCD samples)
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

## change output name 
process.TFileService.fileName = 'analyzeDiffXSec_testAll.root'
