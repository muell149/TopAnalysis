import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing
import sys

## ---
##   use this file to test the FullHadQCDEstimation.cc module
## ---

# setup 'standard' options
options = VarParsing.VarParsing ('standard')
## decide whether to run on:  * data *, * mc * , * mcRedigi * , * mcPtHat * or * mcRedigiPU *
options.register('eventFilter', 'data', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "kind of data to be processed")
## setup the ptHatFilter in case 'eventFilter' is chosen to be qcd
options.register('maxPtHat', 999999., VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.float, "maxPtHat to be processed")
options.register('minPtHat', 0.     , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.float, "minPtHat to be processed")

# get and parse the command line arguments

for args in sys.argv :
    arg = args.split(',')
    for val in arg:
        val = val.split('=')
        if(len(val)==2):
            setattr(options,val[0], val[1])

print "eventFilter: ", options.eventFilter

# set sequence shortcut
process = cms.Process("Analysis")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

# use only when PATTrigger is needed on data to suppress useless error messages
process.MessageLogger.cerr.default.limit = 0

## define input
process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring(    
    ## add your favourite file here
    #'/store/user/eschliec/QCD_Pt_1400to1800_TuneZ2_7TeV_pythia6/PAT_6Jets/149c912aa5a5b907805fbf3f0797a95b/patTuple_6jets_10_4_rID.root',
    #'/store/mc/Fall10/TT_7TeV-mcatnlo/AODSIM/START38_V12-v1/0000/68A868AD-F7EB-DF11-AD08-00221982AF2D.root'
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
if(options.eventFilter=='data'):
    process.GlobalTag.globaltag = cms.string('GR_R_38X_V15::All')
else:
    process.GlobalTag.globaltag = cms.string('START38_V14::All')

## std sequence for pat
process.load("PhysicsTools.PatAlgos.patSequences_cff")

from PhysicsTools.PatAlgos.tools.jetTools import *
addJetCollection(process,cms.InputTag('ak5PFJets'),'AK5','PF',
                 doJTA        = True,
                 doBTagging   = True,
                 jetCorrLabel = ('AK5PF', ['L2Relative', 'L3Absolute', 'L2L3Residual']),
                 doType1MET   = False,
                 doL1Cleaning = False,
                 doL1Counters = False,
                 genJetCollection=cms.InputTag('ak5GenJets'),
                 doJetID      = True,
                 )

if(not options.eventFilter=='data'):
        process.patJetCorrFactors.levels.remove('L2L3Residual')

process.patJets.addTagInfos = False
process.patJetsAK5PF.addTagInfos = False

## get trigger module to be added to the path
process.load('TopAnalysis.TopUtils.patTriggerEvent_cff')
from TopAnalysis.TopFilter.filters.NewTriggerTestFilter_cfi import *

## the QuadJet25U trigger itself
process.hltQJ25U = filterTrigger.clone( whichTrigger="QuadJet25U" )

if(options.eventFilter=='mcRedigi'):
    process.patTrigger.processName      = 'REDIGI38X'
    process.patTriggerEvent.processName = 'REDIGI38X'
elif(options.eventFilter=='mcRedigiPU'):
    process.patTrigger.processName      = 'REDIGI38XPU'
    process.patTriggerEvent.processName = 'REDIGI38XPU'


process.trigger = cms.Sequence(process.patTriggerDefaultSequence *
                               process.hltQJ25U
                               )

if(options.eventFilter=='mcPtHat'):
    ## ptHat filter
    print "maxPtHat   : ", options.maxPtHat
    print "minPtHat   : ", options.minPtHat
    process.load("TopAnalysis.TopFilter.filters.PtHatFilter_cfi")
    process.filterPtHat = process.filterPtHat.clone( maxPtHat = options.maxPtHat,
                                                     minPtHat = options.minPtHat )

    process.trigger = cms.Sequence(process.filterPtHat *
                                   process.trigger
                                   )

## additional jet energy smearing for MC
if(options.eventFilter=='data'):
    resFactor = 1.0
else:
    resFactor = 1.1

process.load("TopAnalysis.TopUtils.JetEnergyScale_cfi")
process.scaledJetEnergy = process.scaledJetEnergy.clone( inputJets            = cms.InputTag("selectedPatJetsAK5PF"),
                                                         inputMETs            = cms.InputTag("patMETsPF"),
                                                         payload              = cms.string("AK5PF"),
                                                         scaleFactor          = cms.double(1.0),
                                                         scaleType            = cms.string("abs"), #abs or rel
                                                         jetPTThresholdForMET = cms.double(20.),
                                                         jetEMLimitForMET     = cms.double(0.9),
                                                         resolutionFactor     = cms.double(resFactor)
                                                       )

print "resFactor : ", process.scaledJetEnergy.resolutionFactor

## select events with at least 6 jets
process.load("PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi")
process.tightLeadingJets = process.selectedPatJets.clone(src = 'selectedPatJetsAK5PF',
                                                         cut = 'abs(eta) < 2.4 & pt > 30. &'
                                                               'chargedHadronEnergyFraction > 0.0  &'
                                                               'neutralHadronEnergyFraction < 0.9  &'
                                                               'chargedEmEnergyFraction     < 0.99 &'
                                                               'neutralEmEnergyFraction     < 0.9  &'
                                                               'chargedMultiplicity > 0            &'
                                                               'nConstituents > 1'
                                                         )

#process.tightBottomJets = process.selectedPatJets.clone(src = 'tightLeadingJets',
#                                                        cut = 'bDiscriminator(\"trackCountingHighPurBJetTags\") > 3.41'
#                                                        )
process.tightBottomJets = process.selectedPatJets.clone(src = 'tightLeadingJets',
                                                        cut = 'bDiscriminator(\"trackCountingHighEffBJetTags\") > 3.3'
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
#process.analyzeFullHadQCDEstimation.analyze.bTagAlgoWP = "TCHPT40"
#process.analyzeFullHadQCDEstimation.analyze.bTagAlgoWP = "TCHEM40"
#process.analyzeFullHadQCDEstimation.analyze.bTagAlgoWP = "TCHEM40MC"
process.analyzeFullHadQCDEstimation.analyze.bTagAlgoWP = "TCHEM30"
#process.analyzeFullHadQCDEstimation.analyze.bTagAlgoWP = "TCHEM30clean"

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
    #process.patDefaultSequence   *
    process.trigger              *
    process.tightLeadingJets     *
    process.leadingJetSelection  *
    process.tightBottomJets      *
    process.bottomJetSelection   *
    ## apply the analyzer
    process.analyzeFullHadQCDEstimation
    )

if(not options.eventFilter=='data'):
    process.tightLeadingJets.src = cms.InputTag('scaledJetEnergy', 'selectedPatJetsAK5PF', 'Analysis')
    process.p1.replace(process.tightLeadingJets, process.scaledJetEnergy*process.tightLeadingJets)
