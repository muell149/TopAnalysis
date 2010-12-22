## ---
##    this configfile does the same like analyzeMuonDiffXSecCorrected_cfg.py
##    but is done without filtering on gen level
## ---

## get the mother file
execfile("analyzeMuonDiffXSecCorrected_cfg.py")

process.source.fileNames = ['/store/user/mgoerner/WJetsToLNu_TuneD6T_7TeV-madgraph-tauola/PAT_FALL10HH/148435cd71339b79cc0025730c13472a/fall10MC_100_1_iJg.root']

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
process.TFileService.fileName = 'analyzeDiffXSecCorr_testAll.root'
