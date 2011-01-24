#----------------------------------------------------------------------------
# cfg file for patTuple production
#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# special MC matching: only muons from specific decays (W, Z, ttbar) are matched
#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#----------------------------------------------------------------------------
import FWCore.ParameterSet.Config as cms
process = cms.Process("PAT")

#----------------------------------------------------------------------------
# process configuration
#----------------------------------------------------------------------------

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 100

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
	'/store/mc/Fall10/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0006/0496C14C-9BE4-DF11-8C37-0030485A3C51.root'
    )
)

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

## configure geometry & conditions
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('START38_V14::All')

#----------------------------------------------------------------------------
# pat configuration
#----------------------------------------------------------------------------

## std sequence for pat
process.load("PhysicsTools.PatAlgos.patSequences_cff")

## use the correct jet energy corrections
process.patJetCorrFactors.corrSample = "Spring10"

## calculate d0 wrt the beam spot
process.patMuons.usePV = False

## Add PfMET and TcMET to the event content
from PhysicsTools.PatAlgos.tools.metTools import *
addPfMET(process,'PF')
	
## add ak5JPTJets
from PhysicsTools.PatAlgos.tools.jetTools import *
	 
## Add particle flow jets
addJetCollection(process,cms.InputTag('ak5PFJets'),'AK5','PF',
                 doJTA        = True,
                 doBTagging   = True,
                 jetCorrLabel = ('AK5', 'PF'),
                 doType1MET   = False,
                 doL1Cleaning = False,
                 doL1Counters = False,
                 genJetCollection=cms.InputTag('ak5GenJets'),
                 doJetID      = True,
                )

## MC Matching and Embedding ------------------
## select only muons from desired decay from genParticles (comment out other processes!!!)
from TopAnalysis.TopUtils.GenCandSelector_cfi import isolatedGenMuons
process.genMuonsFromSpecificDecay = isolatedGenMuons.clone(
    # Z-DECAY
    target = cms.PSet( pdgId = cms.vstring("13", "-13"), status = cms.int32(3) ), #daughter: mu
    ancestor = cms.PSet( pdgId = cms.vstring("23") )      # mother: Z boson
    ## W-DECAY
    #target = cms.PSet( pdgId = cms.vstring("13", "-13"), status = cms.int32(3) ), #daughter: mu
    #ancestor = cms.PSet( pdgId = cms.vstring("24", "-24") )      # mother: W boson
    ## TTbar-DECAY
    #target = cms.PSet( pdgId = cms.vstring("13", "-13"), status = cms.int32(3) ), #daughter: mu
    #ancestor = cms.PSet( pdgId = cms.vstring("6:24", "-6:-24") )      # mother: W boson from t decay
)
process.newMuonMatch = process.muonMatch.clone(
     #src = 'muons',
     matched = 'genMuonsFromSpecificDecay',
     mcStatus = [3]
)
process.patDefaultSequence.replace(process.muonMatch, process.newMuonMatch)
process.patMuons.genParticleMatch = cms.VInputTag(
    cms.InputTag("newMuonMatch")
)

## embedding of jet constituents into the jets
process.patJets.embedCaloTowers       = False
process.patJetsAK5PF.embedPFCandidates= False 

## remove TagInfos from jets
process.patJets.addTagInfos       = False
process.patJetsAK5PF.addTagInfos  = False

## embed IsoDeposits
process.patMuons.isoDeposits = cms.PSet(
     tracker = cms.InputTag("muIsoDepositTk"),
     ecal    = cms.InputTag("muIsoDepositCalByAssociatorTowers","ecal"),
     hcal    = cms.InputTag("muIsoDepositCalByAssociatorTowers","hcal"),
     user    = cms.VInputTag(cms.InputTag("muIsoDepositCalByAssociatorTowers","ho"),
                             cms.InputTag("muIsoDepositJets")
                            ),
    )
    
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

## adding electron identification
#process.load("ElectroWeakAnalysis.WENu.simpleEleIdSequence_cff")

#process.patElectrons.addElectronID     = cms.bool( True )
#process.patElectrons.electronIDSources = cms.PSet( simpleEleId95relIso = cms.InputTag("simpleEleId95relIso"),
#                                                   simpleEleId90relIso = cms.InputTag("simpleEleId90relIso"),
#                                                   simpleEleId85relIso = cms.InputTag("simpleEleId85relIso"),
#                                                   simpleEleId80relIso = cms.InputTag("simpleEleId80relIso"),
#                                                   simpleEleId70relIso = cms.InputTag("simpleEleId70relIso"),
#                                                   simpleEleId60relIso = cms.InputTag("simpleEleId60relIso"),
#                                                   simpleEleId95cIso   = cms.InputTag("simpleEleId95cIso"),
#                                                   simpleEleId90cIso   = cms.InputTag("simpleEleId90cIso"),
#                                                   simpleEleId85cIso   = cms.InputTag("simpleEleId85cIso"),
#                                                   simpleEleId80cIso   = cms.InputTag("simpleEleId80cIso"),
#                                                   simpleEleId70cIso   = cms.InputTag("simpleEleId70cIso"),
#                                                   simpleEleId60cIso   = cms.InputTag("simpleEleId60cIso")
#                                                   )

#process.patElectronIDs = cms.Sequence( process.simpleEleIdSequence )

#process.makePatElectrons = cms.Sequence(process.patElectronIDs       *
#                                        process.patElectronIsolation *
#                                        process.electronMatch        *
#                                        process.patElectrons
#                                       )

process.p = cms.Path(process.genMuonsFromSpecificDecay  *
                     process.patDefaultSequence)

## configure output module
process.out = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring('drop *'),
    dropMetaDataForDroppedData = cms.untracked.bool(True),                                     
    fileName = cms.untracked.string('PATtuple.root')
)

## save pat output
from PhysicsTools.PatAlgos.patEventContent_cff import *
process.out.outputCommands += patExtraAodEventContent
process.out.outputCommands += patEventContentNoCleaning
process.out.outputCommands+= ['keep *_TriggerResults_*_*',
	          'keep *_hltTriggerSummaryAOD_*_*',
	          'keep L1GlobalTriggerReadoutRecord_gtDigis_*_*',
	          'keep *_ak5JetID_*_*'			      		      			      			      
	         ]

process.outpath = cms.EndPath(process.out)


