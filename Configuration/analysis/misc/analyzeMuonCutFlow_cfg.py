import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# cfg file for the analysis of selected muon
# quantities
#-------------------------------------------------
process = cms.Process("MuonCutFlow")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 100

#-------------------------------------------------
# process configuration
#-------------------------------------------------

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(    
    ## add your favourite file here
    '/store/user/snaumann/ttbar/patTuple_1.root',
    '/store/user/snaumann/ttbar/patTuple_2.root',
    '/store/user/snaumann/ttbar/patTuple_3.root',
    '/store/user/snaumann/ttbar/patTuple_4.root',
    '/store/user/snaumann/ttbar/patTuple_5.root',
    '/store/user/snaumann/ttbar/patTuple_6.root',
    '/store/user/snaumann/ttbar/patTuple_7.root',
    '/store/user/snaumann/ttbar/patTuple_8.root',
    '/store/user/snaumann/ttbar/patTuple_9.root',
    '/store/user/snaumann/ttbar/patTuple_10.root',
    '/store/user/snaumann/ttbar/patTuple_11.root',
    '/store/user/snaumann/ttbar/patTuple_12.root',
    '/store/user/snaumann/ttbar/patTuple_13.root',
    '/store/user/snaumann/ttbar/patTuple_14.root',
    '/store/user/snaumann/ttbar/patTuple_15.root',
    '/store/user/snaumann/ttbar/patTuple_16.root',
    '/store/user/snaumann/ttbar/patTuple_17.root',
    '/store/user/snaumann/ttbar/patTuple_18.root',
    '/store/user/snaumann/ttbar/patTuple_19.root',
    '/store/user/snaumann/ttbar/patTuple_20.root',
    '/store/user/snaumann/ttbar/patTuple_21.root',
    '/store/user/snaumann/ttbar/patTuple_22.root',
    '/store/user/snaumann/ttbar/patTuple_23.root',
    '/store/user/snaumann/ttbar/patTuple_24.root',
    '/store/user/snaumann/ttbar/patTuple_25.root',
    '/store/user/snaumann/ttbar/patTuple_26.root',
    '/store/user/snaumann/ttbar/patTuple_27.root',
    '/store/user/snaumann/ttbar/patTuple_28.root',
    '/store/user/snaumann/ttbar/patTuple_29.root',
    '/store/user/snaumann/ttbar/patTuple_30.root',
    '/store/user/snaumann/ttbar/patTuple_31.root',
    '/store/user/snaumann/ttbar/patTuple_32.root',
    '/store/user/snaumann/ttbar/patTuple_33.root',
    '/store/user/snaumann/ttbar/patTuple_34.root',
    '/store/user/snaumann/ttbar/patTuple_35.root',
    '/store/user/snaumann/ttbar/patTuple_36.root',
    '/store/user/snaumann/ttbar/patTuple_37.root',
    '/store/user/snaumann/ttbar/patTuple_38.root',
    '/store/user/snaumann/ttbar/patTuple_39.root',
    '/store/user/snaumann/ttbar/patTuple_40.root',
    '/store/user/snaumann/ttbar/patTuple_41.root',
    '/store/user/snaumann/ttbar/patTuple_42.root',
    '/store/user/snaumann/ttbar/patTuple_43.root',
    '/store/user/snaumann/ttbar/patTuple_44.root',
    '/store/user/snaumann/ttbar/patTuple_45.root',
    '/store/user/snaumann/ttbar/patTuple_46.root',
    '/store/user/snaumann/ttbar/patTuple_47.root',
    '/store/user/snaumann/ttbar/patTuple_48.root',
    '/store/user/snaumann/ttbar/patTuple_49.root',
    '/store/user/snaumann/ttbar/patTuple_50.root',
    '/store/user/snaumann/ttbar/patTuple_51.root',
    '/store/user/snaumann/ttbar/patTuple_52.root',
    '/store/user/snaumann/ttbar/patTuple_53.root',
    '/store/user/snaumann/ttbar/patTuple_54.root',
    '/store/user/snaumann/ttbar/patTuple_55.root',
    '/store/user/snaumann/ttbar/patTuple_56.root',
    '/store/user/snaumann/ttbar/patTuple_57.root',
    '/store/user/snaumann/ttbar/patTuple_58.root'
    )
)

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(False)
)

## std sequence to produce the ttGenEvt
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")

## semi-leptonic decay filter
process.load("TopQuarkAnalysis.TopEventProducers.producers.TtDecaySelection_cfi")
process.ttSemiLeptonicFilter = process.ttDecaySelection.clone()
process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.muon     = True
process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchB.muon     = False
#process.ttSemiLeptonicFilter.invert = True

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeMuonCutFlow_sig.root') # ('analyzeMuonCutFlow_bkg.root')
)

process.load("TopAnalysis.TopFilter.sequences.MuonCutFlow_cff")

process.p1 = cms.Path(process.makeGenEvt *
                      process.ttSemiLeptonicFilter *
                      process.cutFlowSequence)
