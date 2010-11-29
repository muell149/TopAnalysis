import FWCore.ParameterSet.Config as cms

## ---
##   use this file to test the FullHadQCDEstimation.cc module
## ---


# set sequence shortcut
process = cms.Process("Analysis")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1

## define input
process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring(    
    ## add your favourite file here
    '/store/mc/Fall10/TT_7TeV-mcatnlo/AODSIM/START38_V12-v1/0000/68A868AD-F7EB-DF11-AD08-00221982AF2D.root'
    #'/store/user/eschliec/MultiJet/PAT_6Jets/b453efd6b4e702a41534c3116b93394f/patTuple_6jets_29_1_V8G.root',
    #'/store/user/eschliec/MultiJet/PAT_6Jets/b453efd6b4e702a41534c3116b93394f/patTuple_6jets_30_1_Nu3.root',
    #'/store/user/eschliec/MultiJet/PAT_6Jets/b453efd6b4e702a41534c3116b93394f/patTuple_6jets_33_1_028.root',
    #'/store/user/eschliec/MultiJet/PAT_6Jets/b453efd6b4e702a41534c3116b93394f/patTuple_6jets_34_1_ADU.root',
    #'/store/user/eschliec/MultiJet/PAT_6Jets/b453efd6b4e702a41534c3116b93394f/patTuple_6jets_35_1_RgW.root',
    #'/store/user/eschliec/MultiJet/PAT_6Jets/b453efd6b4e702a41534c3116b93394f/patTuple_6jets_38_1_q1a.root',
    #'/store/user/eschliec/MultiJet/PAT_6Jets/b453efd6b4e702a41534c3116b93394f/patTuple_6jets_39_1_9aN.root',
    #'/store/user/eschliec/MultiJet/PAT_6Jets/b453efd6b4e702a41534c3116b93394f/patTuple_6jets_36_1_XTu.root',
    #'/store/user/eschliec/MultiJet/PAT_6Jets/b453efd6b4e702a41534c3116b93394f/patTuple_6jets_37_1_rJ6.root',
    ),
    skipEvents = cms.untracked.uint32(0)
 )

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeFullHadQCDEstimation_test.root')
)

## do event filtering on generator level
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEventFilters_cff")

## configure geometry & conditions
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('START38_V14::All')

## std sequence for pat
process.load("PhysicsTools.PatAlgos.patSequences_cff")

from PhysicsTools.PatAlgos.tools.jetTools import *
addJetCollection(process,cms.InputTag('ak5PFJets'),'AK5','PF',
                 doJTA        = True,
                 doBTagging   = True,
                 jetCorrLabel = ('AK5PF', ['L2Relative', 'L3Absolute']),
                 doType1MET   = False,
                 doL1Cleaning = False,
                 doL1Counters = False,
                 genJetCollection=cms.InputTag('ak5GenJets'),
                 doJetID      = True,
                 )

process.patJets.addTagInfos = False
process.patJetsAK5PF.addTagInfos = False

## select events with at least 6 jets
process.load("PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi")
process.tightLeadingJets = process.selectedPatJets.clone(src = 'selectedPatJetsAK5PF',
                                                         cut = 'abs(eta) < 2.4 & pt > 40. &'
                                                               'chargedHadronEnergyFraction > 0.0  &'
                                                               'neutralHadronEnergyFraction < 0.9  &'
                                                               'chargedEmEnergyFraction     < 0.99 &'
                                                               'neutralEmEnergyFraction     < 0.9  &'
                                                               'chargedMultiplicity > 0            &'
                                                               'nConstituents > 1'
                                                         )

process.tightBottomJets = process.selectedPatJets.clone(src = 'tightLeadingJets',
                                                        cut = 'bDiscriminator(\"trackCountingHighPurBJetTags\") > 3.41'
                                                        )

process.load("PhysicsTools.PatAlgos.selectionLayer1.jetCountFilter_cfi")
process.leadingJetSelection = process.countPatJets.clone( src = 'tightLeadingJets',
                                                          minNumber = 6
                                                          )
process.bottomJetSelection = process.countPatJets.clone( src = 'tightBottomJets',
                                                         minNumber = 0,
                                                         maxNumber = 0
                                                         )

## ---
##    load FullHadQCDEstimation Analyzer
## ---

## analyze the QCD estimation for fully hadronic ttbar events
process.load("TopAnalysis.TopAnalyzer.FullHadQCDEstimation_cfi")
process.analyzeFullHadQCDEstimation = process.analyzeFullHadQCDEstimation.clone(src = "tightLeadingJets")
from TopQuarkAnalysis.TopObjectResolutions.stringResolutions_etEtaPhi_cff import *
process.analyzeFullHadQCDEstimation.analyze.udscResolutions = udscResolutionPF.functions
process.analyzeFullHadQCDEstimation.analyze.bResolutions    = bjetResolutionPF.functions

## ---
##    run the final sequence
## ---

process.p1 = cms.Path(
    ## do the filtering
    #process.makeGenEvt           *
    #process.ttFullHadronicFilter *
    process.patDefaultSequence   *
    process.tightLeadingJets     *
    process.leadingJetSelection  *
    process.tightBottomJets      *
    process.bottomJetSelection   *
    ## apply the analyzer
    process.analyzeFullHadQCDEstimation
    )
