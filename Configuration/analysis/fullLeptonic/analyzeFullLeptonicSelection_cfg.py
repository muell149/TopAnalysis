import FWCore.ParameterSet.Config as cms

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
    '/store/user/rwolf/ttbar09/patTuple_all_0_ttbar09.root'
    )
)

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10000)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeFullLeptonicSelection.root')
)

## std sequence to produce the ttGenEvt
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")

## filter for different ttbar decay channels
process.load("TopQuarkAnalysis.TopEventProducers.producers.TtDecaySelection_cfi")
process.ttDecaySelection.allowedTopDecays.decayBranchA.muon     = True
process.ttDecaySelection.allowedTopDecays.decayBranchB.electron = True

## high level trigger filter
process.load("TopAnalysis.TopFilter.sequences.triggerFilter_cff")


## sequence with filter for decay channel
process.genFilterSequence = cms.Sequence(process.makeGenEvt *
                                         process.ttDecaySelection
                                         )
## sequence with filter for trigger selection
process.recFilterSequence = cms.Sequence(process.hltEle15
                                         )
## ---
##    define selection
## ---

## jet selection
process.load("TopAnalysis.TopFilter.sequences.jetSelection_cff")

from TopAnalysis.TopFilter.sequences.jetSelection_cff import reliableJets
process.reliableJets = reliableJets

from TopAnalysis.TopFilter.sequences.jetSelection_cff import centralJets
process.centralJets = centralJets

from TopAnalysis.TopFilter.sequences.jetSelection_cff import goodJets
process.goodJets = goodJets

## muon selection
process.load("TopAnalysis.TopFilter.sequences.muonSelection_cff")

from TopAnalysis.TopFilter.sequences.muonSelection_cff import standAloneMuons
process.standAloneMuons = standAloneMuons

## electron selection
process.load("TopAnalysis.TopFilter.sequences.electronSelection_cff")

from TopAnalysis.TopFilter.sequences.electronSelection_cff import centralElectrons
process.centralElectrons = centralElectrons

from TopAnalysis.TopFilter.sequences.electronSelection_cff import highPtElectrons
process.highPtElectrons = highPtElectrons

from TopAnalysis.TopFilter.sequences.electronSelection_cff import tightElectrons
process.tightElectrons = tightElectrons


## ---
##    define monitoring
## ---

## ---
## jet kinematics analyzer
## ---
process.load("TopAnalysis.TopAnalyzer.JetKinematics_cfi")

## 1. leading jet before any cut
process.jetKin_1st_selected = process.analyzeJetKinematics.clone (src = 'selectedLayer1Jets',
                                                                  analyze = cms.PSet(index = cms.int32(0), correctionLevel = cms.string('abs'  ) )
                                                                  )
## 2. leading jet before any cut
process.jetKin_2nd_selected = process.jetKin_1st_selected.clone  (analyze = cms.PSet(index = cms.int32(1), correctionLevel = cms.string('abs'  ) )
                                                                  )
## 1. leading jet after restriction in eta
process.jetKin_1st_central  = process.analyzeJetKinematics.clone (src = 'centralJets',
                                                                  analyze = cms.PSet(index = cms.int32(0), correctionLevel = cms.string('abs'  ) )
                                                                  )
## 2. leading jet after restriction in eta
process.jetKin_2nd_central  = process.jetKin_1st_central.clone   (analyze = cms.PSet(index = cms.int32(1), correctionLevel = cms.string('abs'  ) )
                                                                  )
## define sequence
process.monitorJetKinematics = cms.Sequence(process.jetKin_1st_selected +
                                            process.jetKin_2nd_selected +
                                            process.jetKin_1st_central  +
                                            process.jetKin_2nd_central
                                            )

## ---
## jet quality analyzer
## ---
process.load("TopAnalysis.TopAnalyzer.JetQuality_cfi")

## 1. leading jet after restriction in eta and pt (for emf)
process.jetID_1st_reliable  = process.analyzeJetQuality.clone  (src = 'reliableJets',
                                                                analyze = cms.PSet(index = cms.int32(0), flavor = cms.string('uds' ) )
                                                                )
## 2. leading jet after restriction in eta and pt (for emf)
process.jetID_2nd_reliable  = process.jetID_1st_reliable.clone (analyze = cms.PSet(index = cms.int32(1), flavor = cms.string('uds' ) )
                                                               )
## 1. leading jet after restriction in eta, pt and emf (for btag)
process.jetID_1st_good      = process.analyzeJetQuality.clone  (src = 'goodJets',
                                                                analyze = cms.PSet(index = cms.int32(0), flavor = cms.string('uds' ) )
                                                                )
## 2. leading jet after restriction in eta, pt and emf (for btag)
process.jetID_2nd_good      = process.jetID_1st_good.clone     (analyze = cms.PSet(index = cms.int32(1), flavor = cms.string('uds' ) )
                                                                )
## define sequence
process.monitorJetQuality = cms.Sequence(process.jetID_1st_reliable +
                                         process.jetID_2nd_reliable +
                                         process.jetID_1st_good     +
                                         process.jetID_2nd_good
                                         )
## ---
## electron kinematics analyzer
## ---
process.load("TopAnalysis.TopAnalyzer.ElectronKinematics_cfi")

## 1. leading electron before any cut
process.eleKin_1st_selected = process.analyzeElectronKinematics.clone(src = 'selectedLayer1Electrons',
                                                                      analyze = cms.PSet(index = cms.int32(0))
                                                                      )
## 1. leading electron after restriction in eta
process.eleKin_1st_central  = process.analyzeElectronKinematics.clone(src = 'centralElectrons',
                                                                      analyze = cms.PSet(index = cms.int32(0))
                                                                      )
## define sequence
process.monitorElectronKinematics = cms.Sequence(process.eleKin_1st_selected +
                                                 process.eleKin_1st_central
                                                 )
    
## ---
## electron quality analyzer
## ---
process.load("TopAnalysis.TopAnalyzer.ElectronQuality_cfi")

## 1. leading electron after restriction in eta and pt (electronID)
process.elecID_1st_highPt   = process.analyzeElectronQuality.clone (src = 'highPtElectrons',
                                                                    analyze = cms.PSet(index = cms.int32(0))
                                                                    )
## 1. leading electron after restriction in eta, pt and electronID (for isolation)
process.elecID_1st_tight    = process.analyzeElectronQuality.clone (src = 'tightElectrons',
                                                                    analyze = cms.PSet(index = cms.int32(0))
                                                                    )
## define sequence
process.monitorElectronQuality = cms.Sequence(process.elecID_1st_highPt +
                                              process.elecID_1st_tight
                                              )
    
## ---
## muon kinematics analyzer
## ---
process.load("TopAnalysis.TopAnalyzer.MuonKinematics_cfi")

## 1. leading muon with standAlone restriction
process.muonKin_1st_standAlone = process.analyzeMuonKinematics.clone(src='standAloneMuons')

## ---
## muon quality analyzer
## ---
process.load("TopAnalysis.TopAnalyzer.MuonQuality_cfi")

## 1. leading muon with standAlone restriction
process.muonID_1st_standAlone = process.analyzeMuonQuality.clone(src='standAloneMuons')


## ---
##    run the final sequence
## ---
process.p1 = cms.Path(## do the gen event selection (decay channel)
                      process.genFilterSequence  *
                      ## the trigger selection (hltEle15)
                      process.recFilterSequence  *
                      ## get corresponding jet collections
                      process.reliableJets       *
                      process.centralJets        *
                      process.goodJets           *
                      ## get corresponding electron collection
                      process.centralElectrons   *
                      process.highPtElectrons    *
                      process.tightElectrons     *
                      ## get corresponding muon collection
                      process.standAloneMuons    *
                      ## do the monitoring
                      process.monitorJetKinematics      *
                      process.monitorJetQuality         *
                      process.monitorElectronKinematics *
                      process.monitorElectronQuality    *
                      process.muonKin_1st_standAlone    *
                      process.muonID_1st_standAlone
                      )
