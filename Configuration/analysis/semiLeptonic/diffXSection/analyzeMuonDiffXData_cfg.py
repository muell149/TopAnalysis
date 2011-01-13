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
writeOutput = False

## execute mother file
execfile("analyzeMuonDiffXSec_cfg.py")

## choose data set
process.load("TopAnalysis/Configuration/samples/Run2010A_Nov4ReReco_PAT_v3_cff")

## high level trigger filter
process.hltFilter.TriggerResultsTag = "TriggerResults::HLT"

## reduce output
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

## change number of processed events
process.maxEvents.input = -1
process.source.skipEvents = cms.untracked.uint32(0)

## remove gen particle collections
process.p1.remove(process.isolatedGenMuons)
process.p1.remove(process.semiLeptGenCollections)
process.p2.remove(process.isolatedGenMuons)
process.p2.remove(process.semiLeptGenCollections)

## create tuples with events surviving the cuts
## for Njets>=4
if(writeOutput):
    process.out.SelectEvents = cms.untracked.PSet( SelectEvents = cms.vstring('p1') )
    process.out.fileName = cms.untracked.string('patTuple_selectedNjets4.root')

process.filterSequence     = cms.Sequence(process.hltFilter)
process.filterSequenceb    = cms.Sequence(process.hltFilter)
process.filterSequenceABCD = cms.Sequence(process.hltFilter)
print "all gen level filters using ttbar decay subset are removed"

## change output name 
process.TFileService.fileName = 'analyzeDiffXData.root'
