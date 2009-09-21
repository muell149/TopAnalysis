from PhysicsTools.PatAlgos.patTemplate_cfg import *

## PAT Standard Sequence
process.load("PhysicsTools.PatAlgos.patSequences_cff")

## Restrict Output to AOD (no ECAL rec hit isolation for electrons or photons, no JetID)
from PhysicsTools.PatAlgos.tools.coreTools import *
restrictInputToAOD(process, ['All',])

## Add antikt and siscone jets
from PhysicsTools.PatAlgos.tools.jetTools import *
addJetCollection(process,cms.InputTag('sisCone5CaloJets'),
                 'SC5',
                 doJTA        = True,
                 doBTagging   = True,
                 jetCorrLabel = ('SC5','Calo'),
                 doType1MET   = True,
                 doL1Cleaning = False,                 
                 doL1Counters = False,
                 genJetCollection=cms.InputTag("sisCone5GenJets")
                 )

addJetCollection(process,cms.InputTag('antikt5CaloJets'),
                 'AK5',
                 doJTA        = True,
                 doBTagging   = True,
                 jetCorrLabel = ('AK5','Calo'),
                 doType1MET   = True,
                 doL1Cleaning = False,                 
                 doL1Counters = False,
                 genJetCollection=cms.InputTag("antikt5GenJets")
                 )

## Check the Event Content
process.content = cms.EDAnalyzer("EventContentAnalyzer")

process.p = cms.Path(
    process.patDefaultSequence # + process.content
)

## Special Replacements
process.jetCorrFactors.sampleType  = 'ttbar'
process.jetCorrFactorsAK5.L7Parton = 'L7Parton_SC5'

## Maximal Number of Events
process.maxEvents.input    = 100

## Input Files for Testing
process.source.fileNames   = ['/store/mc/Summer09/TTbar/AODSIM/MC_31X_V3_AODSIM-v1/0024/068F7867-2C88-DE11-B3C2-001F29C9A5AE.root']   

## Define Event Contet
from PhysicsTools.PatAlgos.patEventContent_cff import *
process.out.outputCommands = patEventContentNoLayer1Cleaning
process.out.outputCommands+= patExtraAodEventContent

## Options and Output Report
process.options.wantSummary = False
