import FWCore.ParameterSet.Config as cms

## ---
##    here we need a general description of what the config id good for and the
##    switches mean. This should be in analogy of the Doxygen commentsin the
##    modules...
## --- 
signalInvert  = True


# analyse muon quantities
process = cms.Process("Muons")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 100

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(    
    ## add your favourite file here
    'file:/afs/naf.desy.de/user/r/rwolf/data/samples/ttbar09/patTuple_all_0_ttbar09.root'
    )
)

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeMuons_all.root')
)

## ---
##    decide whether to run on:  * all *, * signal only *, * background only *
## ---

## std sequence to produce the ttGenEvt
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")

## filter for semi-leptonic 
process.load("TopQuarkAnalysis.TopEventProducers.producers.TtDecaySelection_cfi")
process.ttSemiLeptonicFilter = process.ttDecaySelection.clone()
process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.muon = True
process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchB.muon = False
process.ttSemiLeptonicFilter.invert = signalInvert

## ---
##    configure the cutflow scenario
## ---
    
## muon quality analyzer
process.load("TopAnalysis.TopAnalyzer.MuonQuality_cfi")
## muon kinematics analyzer
process.load("TopAnalysis.TopAnalyzer.MuonKinematics_cfi")
## pre-defined muon selection
process.load("TopAnalysis.TopFilter.sequences.muonSelection_cff")
## high level trigger filter
process.load("TopAnalysis.TopFilter.sequences.triggerFilter_cff")


## collect kinematics analyzers
process.goodMuonKinematics     = process.analyzeMuonKinematics.clone(src = 'goodMuons'    )
process.trackMuonKinematics    = process.analyzeMuonKinematics.clone(src = 'trackMuons'   )
process.goldenMuonKinematics   = process.analyzeMuonKinematics.clone(src = 'goldenMuons'  )
process.relIsoMuonKinematics   = process.analyzeMuonKinematics.clone(src = 'relIsoMuons'  )
process.combinedMuonKinematics = process.analyzeMuonKinematics.clone(src = 'combinedMuons')

## to be called with muon quality monitoring
process.monitorMuonKinematics  = cms.Sequence(process.goodMuonKinematics   +
                                              process.trackMuonKinematics  +
                                              process.goldenMuonKinematics +     
                                              process.relIsoMuonKinematics +
                                              process.combinedMuonKinematics
                                              ) 

## collect quality analyzers for trackMuon
process.chi2FitQuality   = process.analyzeMuonQuality.clone(src = 'chi2Fit')
process.trackSigQuality  = process.analyzeMuonQuality.clone(src = 'trackSig')
process.goodMuonQuality  = process.analyzeMuonQuality.clone(src = 'goodMuons')
process.validHitsQuality = process.analyzeMuonQuality.clone(src = 'validHits')
process.trackMuonQuality = process.analyzeMuonQuality.clone(src = 'trackMuons')

## to be called with the *selectTrackMuons* sequence
process.monitorTrackMuons = cms.Sequence(process.chi2FitQuality   +
                                         process.trackSigQuality  +
                                         process.goodMuonQuality  +
                                         process.validHitsQuality +
                                         process.trackMuonQuality
                                         )

## collect quality analyzers for goldenMuon
process.ecalDepQuality    = process.analyzeMuonQuality.clone(src = 'ecalDep')
process.hcalDepQuality    = process.analyzeMuonQuality.clone(src = 'hcalDep')
process.goldenMuonQuality = process.analyzeMuonQuality.clone(src = 'goldenMuons')

## to be called with the *selectGoldenMuons* sequence
process.monitorGoldenMuons = cms.Sequence(process.ecalDepQuality  +
                                          process.hcalDepQuality  +
                                          process.goldenMuonQuality
                                          )

## collect quality analyzers for goldenMuon
process.relIsoMuonQuality   = process.analyzeMuonQuality.clone(src = 'relIsoMuons')
process.caloIsoMuonQuality  = process.analyzeMuonQuality.clone(src = 'caloIsoMuons')
process.trackIsoMuonQuality = process.analyzeMuonQuality.clone(src = 'trackIsoMuons')

## to be called with the *selectIsolatedMuons* sequence
process.monitorIsolatedMuons = cms.Sequence(process.relIsoMuonQuality  +
                                            process.caloIsoMuonQuality +
                                            process.trackIsoMuonQuality
                                            )

## ---
##    run the final sequence
## ---
process.p1 = cms.Path(## do the gen evetn selection
                      process.makeGenEvt            *
                      process.ttSemiLeptonicFilter  *
                      ## do the trigger selection
                      process.hltMu9                * 
                      ## do the selections
                      process.selectGoodMuons       +
                      process.selectTrackMuons      +
                      process.selectGoldenMuons     +
                      process.selectIsolatedMuons   +
                      ## do the monitoring
                      process.monitorTrackMuons     +
                      process.monitorGoldenMuons    +
                      process.monitorIsolatedMuons  +
                      process.monitorMuonKinematics
                      )
