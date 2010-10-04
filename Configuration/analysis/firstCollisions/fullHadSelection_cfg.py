import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing

# setup 'standard' options
options = VarParsing.VarParsing ('standard')
## decide whether to run on:  * ReRecoA *, * ReRecoB *, * Prompt *, * Sep17 *, * PromptV9 *
options.register('globalTag', 'PromptV9', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "kind of data to be processed")

# get and parse the command line arguments
options.parseArguments()

#-------------------------------------------------
# test cfg file for the selection of
# fully hadronic ttbar events 
#-------------------------------------------------
process = cms.Process("PreSelection")

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
    '/store/data/Run2010B/Jet/RECO/PromptReco-v2/000/146/436/0263EEFC-DEC6-DF11-8CB1-003048F118C6.root'
    )
)

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

print "Set to run with GlobalTag:",
if(options.globalTag=='Prompt'):
    process.GlobalTag.globaltag = cms.string('GR10_P_V7::All')
elif(options.globalTag=='PromptV9'):
    process.GlobalTag.globaltag = cms.string('GR10_P_V9::All')
elif(options.globalTag=='ReRecoA'):
    process.GlobalTag.globaltag = cms.string('GR_R_36X_V12A::All')
elif(options.globalTag=='ReRecoB'):
    process.GlobalTag.globaltag = cms.string('GR_R_36X_V12B::All')
elif(options.globalTag=='Sep17'):
    process.GlobalTag.globaltag = cms.string('GR_R_38X_V13A::All')
else:
    print "Error occured, GlobalTag not definded properly, stopping program execution"
    sys.exit(0)
print process.GlobalTag.globaltag

#-------------------------------------------------
# vertex filter
#-------------------------------------------------

# vertex filter
process.vertex = cms.EDFilter("VertexSelector",
                              src = cms.InputTag("offlinePrimaryVertices"),
                              cut = cms.string("!isFake && ndof > 4 && abs(z) < 24 && position.Rho < 2"),
                              filter = cms.bool(True),
                              )

#-------------------------------------------------
# scraping filter
#-------------------------------------------------

# scraping filter
process.noscraping = cms.EDFilter("FilterOutScraping",
                                  applyfilter = cms.untracked.bool(True),
                                  debugOn = cms.untracked.bool(False),
                                  numtrack = cms.untracked.uint32(10),
                                  thresh = cms.untracked.double(0.25)
                                  )

#-------------------------------------------------
# trigger
#-------------------------------------------------

## high level trigger filter
from HLTrigger.HLTfilters.hltHighLevel_cfi import *
if(options.globalTag=='PromptV9'):
    process.trigger = hltHighLevel.clone(HLTPaths = ["HLT_QuadJet15U","HLT_QuadJet20U"])
else:
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

#-------------------------------------------------
# event selection
#-------------------------------------------------

## create jet collections need for the preselection
process.goodJets = process.selectedPatJets.clone(src = 'selectedPatJets',
                                                 cut = 'pt > 30. & abs(eta) < 2.4 &'
                                                       'emEnergyFraction > 0.01   &'
                                                       'jetID.fHPD < 0.98         &'
                                                       'jetID.n90Hits > 1'
                                                 )

process.goodJetsAK5PF = process.selectedPatJets.clone(src = 'selectedPatJetsAK5PF',
                                                      cut = 'pt > 30. & abs(eta) < 2.4          &'
                                                            'chargedHadronEnergyFraction > 0.0  &'
                                                            'neutralHadronEnergyFraction < 0.99 &'
                                                            'chargedEmEnergyFraction < 0.99     &'
                                                            'neutralEmEnergyFraction < 0.99     &'
                                                            'chargedMultiplicity > 0            &'
                                                            'nConstituents > 0'
                                                      )

## setup good jet selection collection
process.goodJetSelection = process.countPatJets.clone(src = 'goodJets',
                                                      minNumber = 6
                                                      )

## setup good jet selection collection
process.goodJetSelectionAK5PF = process.countPatJets.clone(src = 'goodJetsAK5PF',
                                                           minNumber = 6
                                                           )

## the parts of the process needed for all pathes
process.prerequists = cms.Sequence(process.trigger         *
                                   process.vertex          *
                                   process.noscraping      *
                                   process.patDefaultSequence
                                   )

## pathes to be run for every event
process.caloLoose = cms.Path(process.prerequists        *
                             process.goodJets           *
                             process.goodJetSelection   
                             )

process.pfLoose = cms.Path(process.prerequists           *
                           process.goodJetsAK5PF         *
                           process.goodJetSelectionAK5PF 
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
    fileName = cms.untracked.string('patTuple_fullHad_6jets_Selection.root')
)

## save pat output
from PhysicsTools.PatAlgos.patEventContent_cff import *
process.out.outputCommands += patTriggerEventContent
process.out.outputCommands += patExtraAodEventContent
process.out.outputCommands += patEventContentNoCleaning

process.outpath = cms.EndPath(process.out)
