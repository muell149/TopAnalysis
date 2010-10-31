from PhysicsTools.PatAlgos.patTemplate_cfg import *

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

## PAT Standard Sequence
process.load("PhysicsTools.PatAlgos.patSequences_cff")

from PhysicsTools.PatAlgos.tools.coreTools import *
## Remove Photons and Taus from the Event
#removeSpecificPATObjects(process, ['Photons','Taus'])
## Remove cleaning of collections
removeCleaning(process)

from PhysicsTools.PatAlgos.tools.metTools import *
## Add PfMET to the event content
addPfMET(process, 'PF')

#from PhysicsTools.PatAlgos.tools.cmsswVersionTools import run36xOn35xInput
#run36xOn35xInput(process)

## Needed for redoing the ak5GenJets
#process.load("RecoJets.Configuration.GenJetParticles_cff")
#process.load("RecoJets.Configuration.RecoGenJets_cff")

## Add particle flow jets
from PhysicsTools.PatAlgos.tools.jetTools import *
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

## Check the Event Content
process.content = cms.EDAnalyzer("EventContentAnalyzer")

process.p = cms.Path(#process.genJetParticles *
                     #process.ak5GenJets *
                     process.patDefaultSequence
                     # + process.content
)

## jet corrections
process.load('JetMETCorrections.Configuration.DefaultJEC_cff')
## sample type used for flavour dependend jet corrections
process.patJetCorrFactors.sampleType = 'ttbar'
process.patJetCorrFactorsAK5PF.sampleType = 'ttbar'

#-------------------------------------------------
# preselection paths (involved jet collections
# need to be known first)
#-------------------------------------------------

## preselection for ak5 jets 
process.selectedPatJets.cut = 'abs(eta) < 3.0 & pt > 30'
process.countPatJetsAK5 = process.countPatJets.clone(src = 'selectedPatJets' , minNumber = 6)
process.ak5Selection = cms.Path(process.countPatJetsAK5)

## preselection for ak5 pf jets 
process.selectedPatJetsAK5PF.cut = 'abs(eta) < 3.0 & pt > 30'
process.countPatJetsAK5PF = process.countPatJets.clone(src = 'selectedPatJetsAK5PF' , minNumber = 6)
process.ak5PfSelection = cms.Path(process.countPatJetsAK5PF)

#-------------------------------------------------
# process output; first the event selection is
# defined: only those events that have passed the
# full production path are selected and written
# to file; the event content has been defined
# above
#-------------------------------------------------

## define event selection
process.EventSelection = cms.PSet(
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('ak5PfSelection', 'ak5Selection')
    )
)

## Define Event Contet
from PhysicsTools.PatAlgos.patEventContent_cff import *
## configure output module
process.out = cms.OutputModule("PoolOutputModule",
    process.EventSelection,
    outputCommands = cms.untracked.vstring('drop *'),
    dropMetaData = cms.untracked.string('DROPPED'),
    fileName = cms.untracked.string('patTuple_6jets.root')
)

process.out.outputCommands = patExtraAodEventContent
process.out.outputCommands+= patEventContentNoCleaning
process.out.outputCommands+= ['drop *_towerMaker_*_*']


## Maximal Number of Events
process.maxEvents.input    = 1000

## Input Files for Testing
#process.source.fileNames   = ['/store/mc/Fall10/QCD_Pt_15to30_TuneZ2_7TeV_pythia6/GEN-SIM-RECO/START38_V12-v1/0000/0031AA8D-65C8-DF11-8FC9-00261894386C.root']
#process.source.fileNames   = ['/store/mc/Fall10/QCD_Pt_30to50_TuneZ2_7TeV_pythia6/GEN-SIM-RECO/START38_V12-v1/0000/003B1242-5DC8-DF11-9D80-003048678F8C.root']
#process.source.fileNames   = ['/store/mc/Fall10/QCD_Pt_50to80_TuneZ2_7TeV_pythia6/GEN-SIM-RECO/START38_V12-v1/0029/00F3A898-B1C9-DF11-A22E-00261894382D.root']
#process.source.fileNames   = ['/store/mc/Fall10/QCD_Pt_80to120_TuneZ2_7TeV_pythia6/GEN-SIM-RECO/START38_V12-v1/0000/0025204E-42CB-DF11-AE6A-00E08178C0C7.root']
#process.source.fileNames   = ['/store/mc/Fall10/QCD_Pt_120to170_TuneZ2_7TeV_pythia6/GEN-SIM-RECO/START38_V12-v1/0000/0051917E-22C8-DF11-9A95-0025B3E066F0.root']
#process.source.fileNames   = ['/store/mc/Fall10/QCD_Pt_170to300_TuneZ2_7TeV_pythia6/GEN-SIM-RECO/START38_V12-v1/0000/001208AF-28C8-DF11-BA0E-0025B3E0653E.root']
#process.source.fileNames   = ['/store/mc/Fall10/QCD_Pt_300to470_TuneZ2_7TeV_pythia6/GEN-SIM-RECO/START38_V12-v1/0000/0880AC1E-78CB-DF11-93D3-00151796C0DC.root']
#process.source.fileNames   = ['/store/mc/Fall10/QCD_Pt_470to600_TuneZ2_7TeV_pythia6/GEN-SIM-RECO/START38_V12-v1/0000/001A0257-1DD9-DF11-9835-00151796D938.root']
#process.source.fileNames   = ['/store/mc/Fall10/QCD_Pt_600to800_TuneZ2_7TeV_pythia6/GEN-SIM-RECO/START38_V12-v2/0000/001E0679-80CE-DF11-9416-00151796D4B0.root']
#process.source.fileNames   = ['/store/mc/Fall10/QCD_Pt_800to1000_TuneZ2_7TeV_pythia6/GEN-SIM-RECO/START38_V12-v1/0000/002FBC64-DBCF-DF11-AC3B-001D0967DA6C.root']
#process.source.fileNames   = ['/store/mc/Fall10/QCD_Pt_1000to1400_TuneZ2_7TeV_pythia6/GEN-SIM-RECO/START38_V12-v1/0000/020F115E-78CB-DF11-818C-00151796D938.root']
#process.source.fileNames   = ['/store/mc/Fall10/QCD_Pt_1400to1800_TuneZ2_7TeV_pythia6/GEN-SIM-RECO/START38_V12-v1/0000/006719C2-D9CF-DF11-8FFB-0024E87699A6.root']
#process.source.fileNames   = ['/store/mc/Fall10/QCD_Pt_1800_TuneZ2_7TeV_pythia6/GEN-SIM-RECO/START38_V12-v1/0000/00701F95-DECF-DF11-9C95-001D0967D689.root']
process.source.fileNames   = ['']
process.source.skipEvents = cms.untracked.uint32(0)

## Options and Output Report
process.options.wantSummary = True

