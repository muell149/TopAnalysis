import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# test cfg file for the selection of
# fully hadronic ttbar events 
#-------------------------------------------------
process = cms.Process("Selection")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

#-------------------------------------------------
# process configuration
#-------------------------------------------------

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    #'/store/data/Run2010A/MinimumBias/RECO/v1/000/136/080/BCE37B96-BF66-DF11-891A-0019DB29C614.root'
    #'/store/data/Run2010A/MinimumBias/RECO/v1/000/136/082/0E723EBB-CF66-DF11-B20C-001D09F25438.root'
    '/store/data/Run2010A/JetMETTau/RECO/v2/000/136/088/50E30071-6C67-DF11-8831-000423D98930.root'
    )
)
#execfile("TopAnalysis/Configuration/analysis/firstCollisions/Source_Run132654_cff.py")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

## configure geometry & conditions
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('GR_R_36X_V10::All')

#-------------------------------------------------
# event selection
#-------------------------------------------------

#-------------------------------------------------
# vertex filter
#-------------------------------------------------

# vertex filter
process.vertex = cms.EDFilter("VertexSelector",
                              src = cms.InputTag("offlinePrimaryVertices"),
                              cut = cms.string("!isFake && ndof > 4 && abs(z) < 15 && position.Rho < 2"),
                              filter = cms.bool(True),
                              )

#-------------------------------------------------
# trigger
#-------------------------------------------------

## high level trigger filter
#from TopAnalysis.TopFilter.sequences.triggerFilter_cff import *
from HLTrigger.HLTfilters.hltHighLevel_cfi import *
process.trigger = hltHighLevel.clone(HLTPaths = ["HLT_QuadJet15U"])

#-------------------------------------------------
# pat configuration
#-------------------------------------------------

## std sequence for pat
process.load("PhysicsTools.PatAlgos.patSequences_cff")

## remove MC matching, photons, taus and cleaning from PAT default sequence
from PhysicsTools.PatAlgos.tools.coreTools import *
removeMCMatching(process, ['All'])

## Add particle flow jets
from PhysicsTools.PatAlgos.tools.jetTools import *
addJetCollection(process,cms.InputTag('ak5PFJets'),'AK5','PF',
                 doJTA        = True,
                 doBTagging   = True,
                 jetCorrLabel = ('AK5', 'PF'),
                 doType1MET   = False,
                 doL1Cleaning = True,
                 doL1Counters = False,
                 genJetCollection=None,
                 doJetID      = True,
                 ) 

from PhysicsTools.PatAlgos.tools.metTools import *
## Add PfMET to the event content
addPfMET(process, 'PF')

#from PhysicsTools.PatAlgos.tools.cmsswVersionTools import run36xOn35xInput
#run36xOn35xInput(process)

## embedding of jet constituents into the jets
process.patJets.embedCaloTowers = True
process.patJetsAK5PF.embedPFCandidates = True

## remove TagInfos from jets
process.patJets.addTagInfos = False
process.patJetsAK5PF.addTagInfos = False

## use the correct jet energy corrections
process.patJetCorrFactors.corrSample = "Spring10"
process.patJetCorrFactors.sampleType = "ttbar"
process.patJetCorrFactorsAK5PF.corrSample = "Spring10"
process.patJetCorrFactorsAK5PF.sampleType = "ttbar"

## load modules for fully hadronic analysis
process.load("TopAnalysis.TopFilter.sequences.fullHadronicSelection_cff")

process.goodJets.cut = ('pt > 20. &'
                        '( (abs(eta) < 2.6 & 0.01 < emEnergyFraction) | (abs(eta) >= 2.6 & abs(eta) < 3.0) ) &'
                        'jetID.fHPD < 0.98 &'
                        'jetID.n90Hits > 1')

process.goodJetsAK5PF = process.selectedPatJets.clone(src = 'selectedPatJetsAK5PF',
                                                      cut = 'pt > 20. &'
                                                            '( (abs(eta) >= 2.4 & abs(eta) < 3.0) | (abs(eta) < 2.4 & chargedHadronEnergyFraction > 0.0) ) &'
                                                            'neutralHadronEnergyFraction < 1.0 &'
                                                            'chargedEmEnergyFraction < 1.0 &'
                                                            'neutralEmEnergyFraction < 1.0 &'
                                                            'pfSpecific.mChargedHadronMultiplicity > 0 &'
                                                            'nConstituents > 0')

process.simpleSecondaryVertexBJetsAK5PF = process.selectedPatJets.clone(src = 'goodJetsAK5PF',
                                                                        cut = 'bDiscriminator(\"simpleSecondaryVertexBJetTags\") > 2.02'
                                                                        )

## setup good jet selection collection
process.goodJetSelection = process.countPatJets.clone(src = 'goodJets',
                                                      minNumber = 6
                                                      )

## setup good jet selection collection
process.goodJetSelectionAK5PF = process.countPatJets.clone(src = 'goodJetsAK5PF',
                                                           minNumber = 6
                                                           )

## modify tight jet selection due to change in good jet selection
process.tightLeadingJetsAK5PF = process.selectedPatJets.clone(src = 'goodJetsAK5PF',
                                                              cut = 'abs(eta) < 2.4 & pt > 40'
                                                              )

process.tightBottomJetsAK5PF  = process.selectedPatJets.clone(src = 'simpleSecondaryVertexBJetsAK5PF',
                                                              cut = 'abs(eta) < 2.4 & pt > 50'
                                                              )

process.fullHadronicSelectionAK5PF = cms.Sequence(process.goodJetsAK5PF *
                                                  process.simpleSecondaryVertexBJetsAK5PF *
                                                  process.tightLeadingJetsAK5PF *
                                                  process.tightBottomJetsAK5PF
                                                  )

## setup jet selection collection
process.leadingJetSelectionAK5PF = process.countPatJets.clone(src = 'tightLeadingJetsAK5PF',
                                                              minNumber = 6
                                                              )
process.bottomJetSelectionAK5PF  = process.countPatJets.clone(src = 'tightBottomJetsAK5PF',
                                                              minNumber = 2
                                                              )

## setting up the fully-hadronic event selection;
## on these collection monitoring can still be
## performed
process.fullHadronicEventsAK5PF = cms.Sequence(process.leadingJetSelectionAK5PF *
                                               process.bottomJetSelectionAK5PF
                                               )

## implimentation and configuration of kinematic fit
from TopQuarkAnalysis.TopEventProducers.sequences.ttFullHadEvtBuilder_cff import *

addTtFullHadHypotheses(process,
                       ["kKinFit"]
                       )

removeTtFullHadHypGenMatch(process)

## the parts of the process needed for all pathes
process.prerequists = cms.Sequence(process.trigger *
                                   process.vertex  *
                                   process.patDefaultSequence
                                   )

## configure information specific for this analysis (values edited later on for different pathes are for caloLoose selection)
process.kinFitTtFullHadEventHypothesis.jets = 'goodJets'
process.kinFitTtFullHadEventHypothesis.maxNComb = -1
process.kinFitTtFullHadEventHypothesis.bTags = 2
process.kinFitTtFullHadEventHypothesis.bTagAlgo = 'simpleSecondaryVertexBJetTags'
process.kinFitTtFullHadEventHypothesis.minBTagValueBJet = 2.02
process.kinFitTtFullHadEventHypothesis.maxBTagValueNonBJet = 3.4
process.kinFitTtFullHadEventHypothesis.jetCorrectionLevel = 'had'
process.ttFullHadHypKinFit.jets = 'goodJets'

## modules for tight calojet selection (caloTight)
process.kinFitTtFullHadEventHypothesisTight = process.kinFitTtFullHadEventHypothesis.clone( jets = 'tightLeadingJets' )

process.ttFullHadHypKinFitTight = cms.EDProducer("TtFullHadHypKinFit",
                                                 bBarTag = cms.InputTag("kinFitTtFullHadEventHypothesisTight","PartonsBBar"),
                                                 status = cms.InputTag("kinFitTtFullHadEventHypothesisTight","Status"),
                                                 lightPTag = cms.InputTag("kinFitTtFullHadEventHypothesisTight","PartonsLightP"),
                                                 bTag = cms.InputTag("kinFitTtFullHadEventHypothesisTight","PartonsB"),
                                                 lightPBarTag = cms.InputTag("kinFitTtFullHadEventHypothesisTight","PartonsLightPBar"),
                                                 lightQBarTag = cms.InputTag("kinFitTtFullHadEventHypothesisTight","PartonsLightQBar"),
                                                 lightQTag = cms.InputTag("kinFitTtFullHadEventHypothesisTight","PartonsLightQ"),
                                                 jets = cms.InputTag("tightLeadingJets"),
                                                 match = cms.InputTag("kinFitTtFullHadEventHypothesisTight")
                                                 )

process.ttFullHadEventTight = process.ttFullHadEvent.clone( kinFit = cms.PSet(chi2 = cms.InputTag("kinFitTtFullHadEventHypothesisTight","Chi2"),
                                                                              prob = cms.InputTag("kinFitTtFullHadEventHypothesisTight","Prob")),
                                                            hypotheses = ['ttFullHadHypKinFitTight'] )

process.filterKinFitQualityTight = process.filterKinFitQuality.clone( srcA = 'ttFullHadEventTight' )

process.kinFittingTight = cms.Sequence(process.kinFitTtFullHadEventHypothesisTight*
                                       process.ttFullHadHypKinFitTight *
                                       process.ttFullHadEventTight *
                                       process.filterKinFitQualityTight
                                       )

## modules for tight calojet selection (pfTight)
process.kinFitTtFullHadEventHypothesisAK5PFTight = process.kinFitTtFullHadEventHypothesis.clone( jets = 'tightLeadingJetsAK5PF' )

process.ttFullHadHypKinFitAK5PFTight = cms.EDProducer("TtFullHadHypKinFit",
                                                      bBarTag = cms.InputTag("kinFitTtFullHadEventHypothesisAK5PFTight","PartonsBBar"),
                                                      status = cms.InputTag("kinFitTtFullHadEventHypothesisAK5PFTight","Status"),
                                                      lightPTag = cms.InputTag("kinFitTtFullHadEventHypothesisAK5PFTight","PartonsLightP"),
                                                      bTag = cms.InputTag("kinFitTtFullHadEventHypothesisAK5PFTight","PartonsB"),
                                                      lightPBarTag = cms.InputTag("kinFitTtFullHadEventHypothesisAK5PFTight","PartonsLightPBar"),
                                                      lightQBarTag = cms.InputTag("kinFitTtFullHadEventHypothesisAK5PFTight","PartonsLightQBar"),
                                                      lightQTag = cms.InputTag("kinFitTtFullHadEventHypothesisAK5PFTight","PartonsLightQ"),
                                                      jets = cms.InputTag("tightLeadingJetsAK5PF"),
                                                      match = cms.InputTag("kinFitTtFullHadEventHypothesisAK5PFTight")
                                                      )

process.ttFullHadEventAK5PFTight = process.ttFullHadEvent.clone( kinFit = cms.PSet(chi2 = cms.InputTag("kinFitTtFullHadEventHypothesisAK5PFTight","Chi2"),
                                                                                   prob = cms.InputTag("kinFitTtFullHadEventHypothesisAK5PFTight","Prob")),
                                                                 hypotheses = ['ttFullHadHypKinFitAK5PFTight'] )

process.filterKinFitQualityAK5PFTight = process.filterKinFitQuality.clone( srcA = 'ttFullHadEventAK5PFTight' )

process.kinFittingAK5PFTight = cms.Sequence(process.kinFitTtFullHadEventHypothesisAK5PFTight*
                                       process.ttFullHadHypKinFitAK5PFTight *
                                       process.ttFullHadEventAK5PFTight *
                                       process.filterKinFitQualityAK5PFTight
                                       )

## modules for loose pfjet selection (pfLoose)
process.kinFitTtFullHadEventHypothesisAK5PF = process.kinFitTtFullHadEventHypothesis.clone( jets = 'goodJetsAK5PF' )

process.ttFullHadHypKinFitAK5PF = cms.EDProducer("TtFullHadHypKinFit",
                                                 bBarTag = cms.InputTag("kinFitTtFullHadEventHypothesisAK5PF","PartonsBBar"),
                                                 status = cms.InputTag("kinFitTtFullHadEventHypothesisAK5PF","Status"),
                                                 lightPTag = cms.InputTag("kinFitTtFullHadEventHypothesisAK5PF","PartonsLightP"),
                                                 bTag = cms.InputTag("kinFitTtFullHadEventHypothesisAK5PF","PartonsB"),
                                                 lightPBarTag = cms.InputTag("kinFitTtFullHadEventHypothesisAK5PF","PartonsLightPBar"),
                                                 lightQBarTag = cms.InputTag("kinFitTtFullHadEventHypothesisAK5PF","PartonsLightQBar"),
                                                 lightQTag = cms.InputTag("kinFitTtFullHadEventHypothesisAK5PF","PartonsLightQ"),
                                                 jets = cms.InputTag("goodJetsAK5PF"),
                                                 match = cms.InputTag("kinFitTtFullHadEventHypothesisAK5PF")
                                                 )

process.ttFullHadEventAK5PF = process.ttFullHadEvent.clone( kinFit = cms.PSet(chi2 = cms.InputTag("kinFitTtFullHadEventHypothesisAK5PF","Chi2"),
                                                                              prob = cms.InputTag("kinFitTtFullHadEventHypothesisAK5PF","Prob")),
                                                            hypotheses = ['ttFullHadHypKinFitAK5PF'] )

process.filterKinFitQualityAK5PF = process.filterKinFitQuality.clone( srcA = 'ttFullHadEventAK5PF' )

process.kinFittingAK5PF = cms.Sequence(process.kinFitTtFullHadEventHypothesisAK5PF*
                                       process.ttFullHadHypKinFitAK5PF *
                                       process.ttFullHadEventAK5PF *
                                       process.filterKinFitQualityAK5PF
                                       )

## pathes to be run for every event
process.caloLoose = cms.Path(process.prerequists        *
                             process.goodJets           *
                             process.goodJetSelection   *
                             process.makeTtFullHadEvent *
                             process.filterKinFitQuality
                             )

process.caloTight = cms.Path(process.prerequists           *
                             process.fullHadronicSelection *
                             process.fullHadronicEvents    *
                             process.kinFittingTight
                             )

process.pfLoose = cms.Path(process.prerequists           *
                           process.goodJetsAK5PF         *
                           process.goodJetSelectionAK5PF *
                           process.kinFittingAK5PF
                           )

process.pfTight = cms.Path(process.prerequists                *
                           process.fullHadronicSelectionAK5PF *
                           process.fullHadronicEventsAK5PF    *
                           process.kinFittingAK5PFTight
                           )

## define event selection
process.EventSelection = cms.PSet(
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('caloLoose','pfLoose')
    )
)

## configure output module
process.out = cms.OutputModule("PoolOutputModule",
    process.EventSelection,
    outputCommands = cms.untracked.vstring('drop *'),
    dropMetaDataForDroppedData = cms.untracked.bool(True),                                     
    fileName = cms.untracked.string('patTuple_fullHad_looseSelection.root')
)

## save pat output
from PhysicsTools.PatAlgos.patEventContent_cff import *
process.out.outputCommands += patTriggerEventContent
process.out.outputCommands += patExtraAodEventContent
process.out.outputCommands += patEventContentNoCleaning
process.out.outputCommands += patEventContent

process.outpath = cms.EndPath(process.out)
