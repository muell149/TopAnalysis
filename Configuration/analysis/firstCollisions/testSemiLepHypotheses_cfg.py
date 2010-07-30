import FWCore.ParameterSet.Config as cms

process = cms.Process("TEST")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = cms.untracked.string('INFO')
process.MessageLogger.categories.append('TtSemiLeptonicEvent')
process.MessageLogger.categories.append('TtSemiLepKinFitter')
process.MessageLogger.categories.append('KinFitter')
process.MessageLogger.cerr.TtSemiLeptonicEvent = cms.untracked.PSet(
    limit = cms.untracked.int32(-1)
)
process.MessageLogger.cerr.KinFitter = cms.untracked.PSet(
    limit = cms.untracked.int32(-1)
)

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    #####################
    ## mu+jets candidates
    #####################
    ## Run 138746, Event 54892889, LumiSection 99 (only 3 jets)
    ## Run 138750, Event 38790862, LumiSection 204 (only 3 jets)
    #'file:PR.root'
    ## Run 139971, Event 166160760, LumiSection 229 (only 3 jets)
    ## Run 140158, Event 112262487, LumiSection 130
    ## Run 140158, Event 260945301, LumiSection 297
    #'file:PD.root'
    ####################
    ## e+jets candidates
    ####################
    ## Run 140059, Event 200726415, LumiSection 230 (only 3 jets when removing electron)
    #'file:PickedEventsTagged_1_1_phF.root',
    ## Run 140331, Event 440601613, LumiSection 524
    #'file:PickedEventsTagged_1_1_AGK.root'
    ## Run 140385, Event 90009543, LumiSection 101
    'file:PickedEventsTagged_2_1_JNK.root'
     ),
     skipEvents = cms.untracked.uint32(0)
)

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(False)
)

## configure geometry & conditions
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('START36_V4::All')

## std sequence for pat
process.load("PhysicsTools.PatAlgos.patSequences_cff")

from PhysicsTools.PatAlgos.tools.coreTools import *
removeMCMatching(process, ['All'])

process.patJetCorrFactors.corrSample = "Spring10"
process.patJetCorrFactors.sampleType = "ttbar"

process.selectedPatJets.cut = ('pt > 30. &'
                               'abs(eta) < 2.4 &'
                               'emEnergyFraction > 0.01 &'
                               'jetID.n90Hits > 1 &'
                               'jetID.fHPD < 0.98 '
                               )

process.cleanPatMuons.preselection = ('isGlobalMuon & isTrackerMuon &'
                                      'pt > 20. &'
                                      'abs(eta) < 2.1 &'
                                      '(trackIso+caloIso)/pt < 0.1 &'
                                      'innerTrack.numberOfValidHits > 10 &'
                                      'globalTrack.normalizedChi2 < 10.0 &'
                                      'globalTrack.hitPattern.numberOfValidMuonHits > 0 &'
                                      'abs(dB) < 0.02'
                                      )
process.cleanPatMuons.checkOverlaps = cms.PSet(
    jets = cms.PSet(src       = cms.InputTag("selectedPatJets"),
                    algorithm = cms.string("byDeltaR"),
                    preselection        = cms.string(""),
                    deltaR              = cms.double(0.3),
                    checkRecoComponents = cms.bool(False),
                    pairCut             = cms.string(""),
                    requireNoOverlaps   = cms.bool(True),
                    )
)

process.cleanPatJets.checkOverlaps.tkIsoElectrons.requireNoOverlaps = True

## dummy analyzers
process.load("TopQuarkAnalysis.Examples.TopJetAnalyzer_cfi")
process.load("TopQuarkAnalysis.Examples.TopMuonAnalyzer_cfi")
process.load("TopQuarkAnalysis.Examples.TopElecAnalyzer_cfi")
process.analyzeJet .input     = "cleanPatJets"
process.analyzeMuon.inputMuon = "cleanPatMuons"
process.analyzeElec.input     = "cleanPatElectrons"

## sequence for the TtSemiLeptonicEvent
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttSemiLepEvtBuilder_cff")

## enable per-event printout from the TtSemiLeptonicEvent
## available verbosity levels: 0, 1, 2, 3, 11, 12, 13
process.ttSemiLepEvent.verbosity = 12

## choose which hypotheses to produce
from TopQuarkAnalysis.TopEventProducers.sequences.ttSemiLepEvtBuilder_cff import *
addTtSemiLepHypotheses(process,
                       ["kMaxSumPtWMass", "kWMassMaxSumPt", "kGeom", "kKinFit"]
                       )
removeTtSemiLepHypGenMatch(process)

## use electrons instead of muons for the hypotheses
useElectronsForAllTtSemiLepHypotheses(process)

## more configurations for hypotheses
setForAllTtSemiLepHypotheses(process, "jets", "cleanPatJets")
#setForAllTtSemiLepHypotheses(process, "leps", "cleanPatMuons")
setForAllTtSemiLepHypotheses(process, "leps", "cleanPatElectrons")
#setForAllTtSemiLepHypotheses(process, "jetCorrectionLevel", "had")
setForAllTtSemiLepHypotheses(process, "maxNJets", -1)
setForAllTtSemiLepHypotheses(process, "maxNComb", -1)
setForAllTtSemiLepHypotheses(process, "useBTagging", True)
setForAllTtSemiLepHypotheses(process, "bTagAlgorithm", "trackCountingHighEffBJetTags")
setForAllTtSemiLepHypotheses(process, "minBDiscBJets", -99999)
setForAllTtSemiLepHypotheses(process, "maxBDiscLightJets", 3.99)

## set KinFit constraints
## 1: Whad-mass, 2: Wlep-mass, 3: thad-mass,
## 4: tlep-mass, 5: nu-mass, 6: equal t-masses
process.kinFitTtSemiLepEventHypothesis.constraints = ([1,2,6])

# register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('testSemiLepHypotheses.root')
)

## end path   
process.path = cms.Path(process.patDefaultSequence *
                        process.analyzeJet *
                        process.analyzeMuon *
                        process.analyzeElec *
                        process.makeTtSemiLepEvent)
