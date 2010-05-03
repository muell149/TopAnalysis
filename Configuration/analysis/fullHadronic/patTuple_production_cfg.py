from PhysicsTools.PatAlgos.patTemplate_cfg import *

## PAT Standard Sequence
process.load("PhysicsTools.PatAlgos.patSequences_cff")

from PhysicsTools.PatAlgos.tools.coreTools import *
## Remove Photons and Taus from the Event
removeSpecificPATObjects(process, ['Photons','Taus'])

from PhysicsTools.PatAlgos.tools.metTools import *
## Add PfMET to the event content
addPfMET(process, 'PF')

from PhysicsTools.PatAlgos.tools.jetTools import *

from PhysicsTools.PatAlgos.tools.cmsswVersionTools import *
run36xOn35xInput(process)

## Add particle flow jets
addJetCollection35X(process,cms.InputTag('ak5PFJets'),'AK5','PF',
                 doJTA        = True,
                 doBTagging   = True,
                 jetCorrLabel = ('AK5', 'PF'),
                 doType1MET   = False,
                 doL1Cleaning = False,                 
                 doL1Counters = False,
                 genJetCollection=cms.InputTag("ak5GenJets"),
                 doJetID      = True
                 )

#addJetCollection(process,cms.InputTag('ak5PFJets'),'AK5','PF',
#                 doJTA        = True,
#                 doBTagging   = True,
#                 jetCorrLabel = ('AK5', 'PF'),
#                 doType1MET   = False,
#                 doL1Cleaning = False,
#                 doL1Counters = False,
#                 genJetCollection=cms.InputTag('ak5GenJets'),
#                 doJetID      = True,
#                 ) 

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

## Check the Event Content
process.content = cms.EDAnalyzer("EventContentAnalyzer")

## Re-Create missing ak5GenJet collection
process.load("RecoJets.Configuration.GenJetParticles_cff")
process.load("RecoJets.Configuration.RecoGenJets_cff")

process.p = cms.Path(
    process.genJetParticles * process.ak5GenJets * process.patDefaultSequence # + process.content
)

## Special Replacements

process.patJetCorrFactors.corrSample = 'Spring10'#'Summer09_7TeV_ReReco332'
## sample type used for flavour dependend jet corrections
process.patJetCorrFactors.sampleType = 'ttbar'
process.patJetCorrFactorsAK5PF.sampleType = 'ttbar'

#-------------------------------------------------
# preselection paths (involved jet collections
# need to be known first)
#-------------------------------------------------

## preselection for ak5 jets 
process.selectedPatJets.cut = 'abs(eta) < 3.0 & pt > 20'
process.countPatJetsAK5 = process.countPatJets.clone(src = 'selectedPatJets' , minNumber = 6)
process.ak5Selection = cms.Path(process.countPatJetsAK5 )   

## preselection for ak5 pf jets 
process.selectedPatJetsAK5PF.cut = 'abs(eta) < 3.0 & pt > 20'
process.countPatJetsAK5PF = process.countPatJets.clone(src = 'selectedPatJetsAK5PF' , minNumber = 6)
process.ak5PfSelection = cms.Path(process.countPatJetsAK5PF )   

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
    dropMetaDataForDroppedData = cms.untracked.bool(True),                                     
    fileName = cms.untracked.string('patTuple.root')
)

process.out.outputCommands = patExtraAodEventContent
process.out.outputCommands+= patEventContentNoCleaning
process.out.outputCommands+= ['drop *_towerMaker_*_*', 'keep *_ak5GenJets_*_*']


## Maximal Number of Events
process.maxEvents.input    = 1000

## Input Files for Testing
process.source.fileNames   = ['/store/mc/Spring10/TTbarJets-madgraph/AODSIM/START3X_V26_S09-v1/0016/2CB76F28-9D47-DF11-959F-003048C693E4.root']

## Options and Output Report
process.options.wantSummary = False
