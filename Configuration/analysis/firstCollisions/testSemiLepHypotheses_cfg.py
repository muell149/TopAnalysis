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
    'file://ExpressPhysics_Run2010A-Express-v2_FEVT_136100_922_273730582.root'
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

## use jets and MET from particle flow (True or False)
usePFlow = True

## std sequence for pat
process.load("PhysicsTools.PatAlgos.patSequences_cff")

process.patJetCorrFactors.corrSample = "Spring10"
process.patJetCorrFactors.sampleType = "ttbar"

if(usePFlow):
    from PhysicsTools.PatAlgos.tools.jetTools import *
    switchJetCollection(process,cms.InputTag('ak5PFJets'),
                        doJTA        = True,
                        doBTagging   = True,
                        jetCorrLabel = ('AK5', 'PF'),
                        doType1MET   = True,
                        genJetCollection=cms.InputTag("ak5GenJets"),
                        doJetID      = True
                        )
    ## setting the pt cut to 31 GeV was only a dirty workaround for this first e+jets event
    process.selectedPatJets.cut = ('pt > 31. &'
                                   'abs(eta) < 2.4 &'
                                   'chargedHadronEnergyFraction > 0.0 &'
                                   'neutralHadronEnergyFraction < 1.0 &'
                                   'chargedEmEnergyFraction     < 1.0 &'
                                   'neutralEmEnergyFraction     < 1.0 &'
                                   'pfSpecific.mChargedHadronMultiplicity > 0 &'
                                   'nConstituents > 0')
    process.patMETs.metSource = "pfMet"
    process.patMETs.addMuonCorrections = False
else:
    process.selectedPatJets.cut = ('pt > 30. &'
                                   'abs(eta) < 2.4 &'
                                   'emEnergyFraction > 0.01 &'
                                   'jetID.n90Hits > 1 &'
                                   'jetID.fHPD < 0.98 '
                                   )

from PhysicsTools.PatAlgos.tools.coreTools import *
removeMCMatching(process, ['All'])

process.cleanPatJets.checkOverlaps.tkIsoElectrons.requireNoOverlaps = True

process.load("TopAnalysis.TopAnalyzer.JetKinematics_cfi")
process.analyzeJetKinematics.src = "cleanPatJets"

## sequence for the TtSemiLeptonicEvent
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttSemiLepEvtBuilder_cff")

## enable per-event printout from the TtSemiLeptonicEvent
## available verbosity levels: 0, 1, 2, 3, 11, 12, 13
process.ttSemiLepEvent.verbosity = 13

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
#setForAllTtSemiLepHypotheses(process, "jetCorrectionLevel", "had")
setForAllTtSemiLepHypotheses(process, "maxNJets", -1)
setForAllTtSemiLepHypotheses(process, "maxNComb", -1)
setForAllTtSemiLepHypotheses(process, "useBTagging", True)
setForAllTtSemiLepHypotheses(process, "minBDiscBJets", 1.90)
setForAllTtSemiLepHypotheses(process, "maxBDiscLightJets", 3.99)

## set KinFit constraints
## 1: Whad-mass, 2: Wlep-mass, 3: thad-mass,
## 4: tlep-mass, 5: nu-mass, 6: equal t-masses
process.kinFitTtSemiLepEventHypothesis.constraints = ([2,6])

# register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('testSemiLepHypotheses.root')
)

## end path   
process.path = cms.Path(process.patDefaultSequence *
                        process.analyzeJetKinematics *
                        process.makeTtSemiLepEvent)
