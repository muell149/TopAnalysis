from PhysicsTools.PatAlgos.patTemplate_cfg import *

## PAT Standard Sequence
process.load("PhysicsTools.PatAlgos.patSequences_cff")

from PhysicsTools.PatAlgos.tools.coreTools import *
## Remove Photons and Taus from the Event
removeSpecificPATObjects(process, ['Photons','Taus'])

from PhysicsTools.PatAlgos.tools.metTools import *
## Add PfMET to the event content
addPfMET(process, 'PF')

from PhysicsTools.PatAlgos.tools.cmsswVersionTools import run33xOnReRecoMC
run33xOnReRecoMC(process)

## Add particle flow jets
from PhysicsTools.PatAlgos.tools.jetTools import *
#addJetID(process, "antikt5PFJets", "pf")
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

## Check the Event Content
process.content = cms.EDAnalyzer("EventContentAnalyzer")

process.p = cms.Path(
    process.patDefaultSequence # + process.content
)

## Special Replacements

process.patJetCorrFactors.corrSample = 'Summer09_7TeV_ReReco332'
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

## Options and Output Report
process.options.wantSummary = False
