import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing

# setup 'standard' options
options = VarParsing.VarParsing ('standard')
## decide whether to run on:  * GR10_P_V11 *, * GR_R_38X_V13A *, * GR_R_38X_V15 *, * START38_V14 *
options.register('globalTag', 'GR10_P_V11', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "kind of data to be processed")

# get and parse the command line arguments
options.parseArguments()

#-------------------------------------------------
# test cfg file for the selection of
# fully hadronic ttbar events 
#-------------------------------------------------
process = cms.Process("PAT")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

#-------------------------------------------------
# process configuration
#-------------------------------------------------

## define input
process.source = cms.Source("PoolSource",
     fileNames = cms.untracked.vstring(#'/store/data/Run2010B/Jet/RECO/PromptReco-v2/000/146/436/0263EEFC-DEC6-DF11-8CB1-003048F118C6.root'
    #'/store/data/Run2010B/MultiJet/AOD/PromptReco-v2/000/148/058/207C5CA4-82DB-DF11-8A85-0030487CD716.root'
    #'/store/data/Run2010B/MultiJet/AOD/Nov4ReReco_v1/0111/0CE1C38F-C7ED-DF11-9A52-003048679076.root'
    #'/store/mc/Fall10/QCD_TuneD6T_HT-500To1000_7TeV-madgraph/AODSIM/START38_V12-v1/0017/4A5B3187-DFDB-DF11-9F3E-00238BBD7590.root'
    #'/store/mc/Fall10/QCD2Jets_Pt-120to280_TuneZ2_7TeV-alpgen/AODSIM/START38_V12-v1/0007/E48CD66B-15DD-DF11-BA58-00163E090301.root'
    #'/store/mc/Fall10/QCD_Pt_800to1000_TuneZ2_7TeV_pythia6/GEN-SIM-RECO/START38_V12-v1/0002/F8455FD4-63D0-DF11-A481-00A0D1EE8E00.root'
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
if(options.globalTag=='GR10_P_V11'):
    process.GlobalTag.globaltag = cms.string('GR10_P_V11::All')
elif(options.globalTag=='GR_R_38X_V13A'):
    process.GlobalTag.globaltag = cms.string('GR_R_38X_V13A::All')
elif(options.globalTag=='GR_R_38X_V15'):
    process.GlobalTag.globaltag = cms.string('GR_R_38X_V15::All')
elif(options.globalTag=='START38_V14'):
    process.GlobalTag.globaltag = cms.string('START38_V14::All')
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

if(options.globalTag=='START38_V14'):
    process.vertex.cut = cms.string("!isFake && ndof > 4 && abs(z) < 15 && position.Rho < 2")

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
process.trigger = hltHighLevel.clone(HLTPaths = ["HLT_QuadJet15U"   ,"HLT_QuadJet20U"   ,"HLT_QuadJet25U"   ,
                                                 "HLT_QuadJet15U_v2","HLT_QuadJet20U_v2","HLT_QuadJet25U_v2",
                                                 "HLT_QuadJet15U_v3","HLT_QuadJet20U_v3","HLT_QuadJet25U_v3"],
                                     throw = False)

## ATTENTION: some Fall10 samples are REDIGI and some are NOT
if(options.globalTag=='START38_V14'):
    process.trigger.TriggerResultsTag = cms.InputTag("TriggerResults","","REDIGI38X")

#-------------------------------------------------
# pat configuration
#-------------------------------------------------

## std sequence for pat
process.load("PhysicsTools.PatAlgos.patSequences_cff")

## configure output module
process.out = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring('drop *'),
    dropMetaData = cms.untracked.string('DROPPED'),
    fileName = cms.untracked.string('patTuple_6jets.root')
)

## remove MC matching, photons, taus and cleaning from PAT default sequence
from PhysicsTools.PatAlgos.tools.coreTools import *
if(not options.globalTag=='START38_V14'):
    removeMCMatching(process, ['All'])
## restrict needed input to AOD event content
restrictInputToAOD(process)

## Add particle flow jets
from PhysicsTools.PatAlgos.tools.jetTools import *
if(options.globalTag=='START38_V14'):
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
else:
    addJetCollection(process,cms.InputTag('ak5PFJets'),'AK5','PF',
                     doJTA        = True,
                     doBTagging   = True,
                     jetCorrLabel = ('AK5PF', ['L2Relative', 'L3Absolute']),
                     doType1MET   = False,
                     doL1Cleaning = False,
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

## embedding of resolutions into the patObjects
process.load("TopQuarkAnalysis.TopObjectResolutions.stringResolutions_etEtaPhi_cff")
process.patJets.addResolutions = True
process.patJets.resolutions = cms.PSet(
    default = cms.string("udscResolution"),
    bjets = cms.string("bjetResolution"),
    )
process.patJetsAK5PF.addResolutions = True
process.patJetsAK5PF.resolutions = cms.PSet(
    default = cms.string("udscResolutionPF"),
    bjets = cms.string("bjetResolutionPF"),
    )
process.patElectrons.addResolutions = True
process.patElectrons.resolutions = cms.PSet( default = cms.string("elecResolution") )
process.patMuons.addResolutions = True
process.patMuons.resolutions = cms.PSet( default = cms.string("muonResolution") )
process.patMETs.addResolutions = True
process.patMETs.resolutions = cms.PSet( default = cms.string("metResolution") )
process.patMETsPF.addResolutions = True
process.patMETsPF.resolutions = cms.PSet( default = cms.string("metResolutionPF") )

## use the correct jet energy corrections
process.patJetCorrFactors.flavorType = "T"
process.patJetCorrFactorsAK5PF.flavorType = "T"

# embed IsoDeposits
process.patMuons.isoDeposits = cms.PSet(
    tracker = cms.InputTag("muIsoDepositTk"),
    ecal    = cms.InputTag("muIsoDepositCalByAssociatorTowers","ecal"),
    hcal    = cms.InputTag("muIsoDepositCalByAssociatorTowers","hcal"),
    user    = cms.VInputTag(
                            cms.InputTag("muIsoDepositCalByAssociatorTowers","ho"),
                            cms.InputTag("muIsoDepositJets")
                            ),
    )

#-------------------------------------------------
# event selection
#-------------------------------------------------

## create jet collections need for the preselection
process.goodJets = process.selectedPatJets.clone(src = 'selectedPatJets',
                                                 cut = 'pt > 40. & abs(eta) < 2.4'
                                                 )

process.goodJetsAK5PF = process.selectedPatJets.clone(src = 'selectedPatJetsAK5PF',
                                                      cut = 'pt > 40. & abs(eta) < 2.4'
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
    dropMetaData = cms.untracked.string('DROPPED'),
    fileName = cms.untracked.string('patTuple_6jets.root')
)

## remove cleaning of collections
removeCleaning(process)

## save pat output
from PhysicsTools.PatAlgos.patEventContent_cff import *
process.out.outputCommands += patTriggerEventContent
process.out.outputCommands += patExtraAodEventContent
process.out.outputCommands += patEventContentNoCleaning
process.out.outputCommands += cms.untracked.vstring('drop *_towerMaker_*_*')

process.outpath = cms.EndPath(process.out)
