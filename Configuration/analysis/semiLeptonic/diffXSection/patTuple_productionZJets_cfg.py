## produces patTuple from MC data
## special: embeds genParticles muons which are only from Z decay

from PhysicsTools.PatAlgos.patTemplate_cfg import *

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

## PAT Standard Sequence
process.load("PhysicsTools.PatAlgos.patSequences_cff")

#from PhysicsTools.PatAlgos.tools.coreTools import *
## Remove Photons and Taus from the Event
#removeSpecificPATObjects(process, ['Photons','Taus'])

from PhysicsTools.PatAlgos.tools.metTools import *
## Add PfMET to the event content
addPfMET(process, 'PF')

from PhysicsTools.PatAlgos.tools.cmsswVersionTools import run36xOn35xInput
run36xOn35xInput(process)

## Needed for redoing the ak5GenJets
process.load("TopAnalysis.TopUtils.GenJetParticles_cff")
process.load("RecoJets.Configuration.RecoGenJets_cff")

## Add particle flow jets
from PhysicsTools.PatAlgos.tools.cmsswVersionTools import *
addJetCollection35X(process,cms.InputTag('ak5PFJets'),'AK5','PF',
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
## select only muons from Z decay from genParticles (genZMuons)
from TopAnalysis.TopUtils.GenCandSelector_cfi import isolatedGenMuons
process.genZMuons = isolatedGenMuons.clone(
    target = cms.PSet( pdgId = cms.vstring("13", "-13"), status = cms.int32(3) ), #daughter: mu
    ancestor = cms.PSet( pdgId = cms.vstring("23") )      # mother: Z boson
)
process.muonMatchZ = process.muonMatch.clone(
     #src = 'muons',
     matched = 'genZMuons',
     mcStatus = [3]
)
process.patDefaultSequence.replace(process.muonMatch, process.muonMatchZ)
process.patMuons.genParticleMatch = cms.VInputTag(
    cms.InputTag("muonMatchZ")
)

# use BeamSpot (not PrimaryVertex) for IP calculation
process.patMuons.usePV = False

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

## embedding of resolutions into the patObjects  COMMENTED AS NOT NEEDED BY ME
#process.load("TopQuarkAnalysis.TopObjectResolutions.stringResolutions_etEtaPhi_cff")
#process.patJets.addResolutions = True
#process.patJets.resolutions = cms.PSet(
    #default = cms.string("udscResolution"),
    #bjets = cms.string("bjetResolution"),
    #)
#process.patJetsAK5PF.addResolutions = True
#process.patJetsAK5PF.resolutions = cms.PSet(
    #default = cms.string("udscResolutionPF"),
    #bjets = cms.string("bjetResolutionPF"),
    #)
#process.patElectrons.addResolutions = True
#process.patElectrons.resolutions = cms.PSet( default = cms.string("elecResolution") )
#process.patMuons.addResolutions = True
#process.patMuons.resolutions = cms.PSet( default = cms.string("muonResolution") )
#process.patMETs.addResolutions = True
#process.patMETs.resolutions = cms.PSet( default = cms.string("metResolution") )
#process.patMETsPF.addResolutions = True
#process.patMETsPF.resolutions = cms.PSet( default = cms.string("metResolutionPF") )

## Check the Event Content
process.content = cms.EDAnalyzer("EventContentAnalyzer")

process.p = cms.Path(process.genJetParticles *
                     process.ak5GenJets *
                     process.genZMuons  *
                     process.patDefaultSequence
                     # + process.content
)

## jet corrections
process.load('JetMETCorrections.Configuration.DefaultJEC_cff')
## sample type used for flavour dependend jet corrections
process.patJetCorrFactors.sampleType = 'ttbar'
process.patJetCorrFactorsAK5PF.sampleType = 'ttbar'

## Define Event Contet
from PhysicsTools.PatAlgos.patEventContent_cff import *
process.out.fileName = cms.untracked.string('PATtuple.root')
process.out.outputCommands = patExtraAodEventContent
process.out.outputCommands+= patEventContentNoCleaning
process.out.outputCommands+= ['drop *_towerMaker_*_*', 'keep *_ak5GenJets_*_*']


## Maximal Number of Events
process.maxEvents.input    = 1000

## Input Files for Testing
process.source.fileNames   = ['/store/mc/Spring10/TTbarJets-madgraph/AODSIM/START3X_V26_S09-v1/0016/2CB76F28-9D47-DF11-959F-003048C693E4.root']
process.source.skipEvents = cms.untracked.uint32(0)

## Options and Output Report
process.options.wantSummary = False
