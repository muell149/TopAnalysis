## ---
##    this configfile does the same like analyzeMuonDiffXSec_cfg.py
##    but is done withot filtering on gen level
## ---

## get the mother file
execfile("analyzeMuonDiffXSec_cfg.py")

## remove gen level event filter
process.filterSequence  = cms.Sequence(process.hltFilter)
process.filterSequenceb = cms.Sequence(process.hltFilter)
process.filterSequenceABCD = cms.Sequence(process.hltFilter)
process.p4.remove(process.genFilterSequence)
print "all gen level filters using ttbar decay subset are removed" 
print "selection for gen plots only via TopAnalysis.TopFilter.sequences.genSelection_cff"

## reduce output (needed when running over QCD samples)
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

## change output name 
process.TFileService.fileName = 'analyzeDiffXSec_testAll.root'
