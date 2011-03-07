import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# dump event content to output
#-------------------------------------------------
process = cms.Process("dumpEventContent")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1

#-------------------------------------------------
# process configuration
#-------------------------------------------------

## define input
process.source = cms.Source("PoolSource",
     fileNames = cms.untracked.vstring(#'/store/data/Run2010B/Jet/RECO/PromptReco-v2/000/146/436/0263EEFC-DEC6-DF11-8CB1-003048F118C6.root'
    #'/store/data/Run2010B/MultiJet/AOD/PromptReco-v2/000/148/058/207C5CA4-82DB-DF11-8A85-0030487CD716.root'
    #'/store/data/Run2010B/MultiJet/AOD/Nov4ReReco_v1/0111/0CE1C38F-C7ED-DF11-9A52-003048679076.root'
    #'/store/mc/Fall10/QCD_TuneD6T_HT-500To1000_7TeV-madgraph/AODSIM/START38_V12-v1/0017/4A5B3187-DFDB-DF11-9F3E-00238BBD7590.root'
    #'/store/mc/Fall10/QCD2Jets_Pt-120to280_TuneZ2_7TeV-alpgen/AODSIM/START38_V12-v1/0007/E48CD66B-15DD-DF11-BA58-00163E090301.root'
    #'/store/mc/Fall10/QCD_Pt_800to1000_TuneZ2_7TeV_pythia6/GEN-SIM-RECO/START38_V12-v1/0002/F8455FD4-63D0-DF11-A481-00A0D1EE8E00.root'
    )
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

process.dump = cms.EDAnalyzer('EventContentAnalyzer')

process.p = cms.Path(process.dump)
