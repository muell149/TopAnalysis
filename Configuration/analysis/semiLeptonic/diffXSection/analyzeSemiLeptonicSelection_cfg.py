import FWCore.ParameterSet.Config as cms

## ---
##    here we need a general description of what the config id good for and the
##    switches mean. This should be in analogy of the Doxygen commentsin the
##    modules...
## --- 
signalInvert  = True
writeOutput   = False

# analyse muon quantities
process = cms.Process("Selection")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1

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
    fileName = cms.string('analyzeSemiLeptonicSelection_all.root')
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
process.load("TopAnalysis.TopAnalyzer.JetQuality_cfi")
## muon quality analyzer
process.load("TopAnalysis.TopAnalyzer.MuonQuality_cfi")
## muon kinematics analyzer
process.load("TopAnalysis.TopAnalyzer.JetKinematics_cfi")
## muon kinematics analyzer
process.load("TopAnalysis.TopAnalyzer.MuonKinematics_cfi")
## high level trigger filter
process.load("TopAnalysis.TopFilter.sequences.triggerFilter_cff")
## semileptonic selection
process.load("TopAnalysis.TopFilter.sequences.semiLeptonicSelection_cff")


## collect kinematics analyzers
process.goodMuonKinematics        = process.analyzeMuonKinematics.clone(src = 'goodMuons'       )
process.trackMuonKinematics       = process.analyzeMuonKinematics.clone(src = 'trackMuons'      )
process.looseMuonKinematics       = process.analyzeMuonKinematics.clone(src = 'trackMuons'      )
process.tightMuonKinematics       = process.analyzeMuonKinematics.clone(src = 'tightMuons'      )
process.goldenMuonKinematics      = process.analyzeMuonKinematics.clone(src = 'goldenMuons'     )
process.tightBottomJetKinematics  = process.analyzeJetKinematics.clone (src = 'tightBottomJets' )
process.tightLeadingJetKinematics = process.analyzeJetKinematics.clone (src = 'tightLeadingJets')

## to be called with semiLeptonicSelection
process.monitorMuonKinematics = cms.Sequence(process.goodMuonKinematics   +
                                             process.trackMuonKinematics  +
                                             process.tightMuonKinematics  +
                                             process.looseMuonKinematics  +
                                             process.goldenMuonKinematics     
                                             ) 
process.monitorJetsKinematics = cms.Sequence(process.tightBottomJetKinematics +
                                             process.tightLeadingJetKinematics
                                             )

## collect quality analyzers for goldenMuon
process.goodMuonQuality        = process.analyzeMuonQuality.clone(src = 'goodMuons'       )
process.trackMuonQuality       = process.analyzeMuonQuality.clone(src = 'trackMuons'      )
process.looseMuonQuality       = process.analyzeMuonQuality.clone(src = 'looseMuons'      )
process.tightMuonQuality       = process.analyzeMuonQuality.clone(src = 'tightMuons'      )
process.goldenMuonQuality      = process.analyzeMuonQuality.clone(src = 'goldenMuons'     )
process.tightBottomJetQuality  = process.analyzeJetQuality.clone (src = 'tightBottomJets' )
process.tightLeadingJetQuality = process.analyzeJetQuality.clone (src = 'tightLeadingJets')

## to be called with the *selectGoldenMuons* sequence
process.monitorMuonQuality = cms.Sequence(process.goodMuonQuality   +
                                          process.trackMuonQuality  +
                                          process.tightMuonQuality  +
                                          process.looseMuonQuality  +
                                          process.goldenMuonQuality     
                                          ) 
process.monitorJetsQuality = cms.Sequence(process.tightBottomJetQuality +
                                          process.tightLeadingJetQuality
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
                      process.semiLeptonicSelection *
                      ## do the monitoring
                      process.monitorMuonQuality    *
                      process.monitorJetsQuality    *
                      process.monitorMuonKinematics *
                      process.monitorJetsKinematics *
                      ## do the event selection
                      process.semiLeptonicEvents
                      )

## Output Module Configuration
if(writeOutput):
    process.out = cms.OutputModule("PoolOutputModule",
                                   fileName = cms.untracked.string('patTuple_selected.root'),
                                   # save only events passing the full path
                                   SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p1') ),
                                   # save output (comment to keep everything...)
                                   #outputCommands = cms.untracked.vstring('drop *',) 
                                   )
    process.outpath = cms.EndPath(process.out)
