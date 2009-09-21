from PhysicsTools.PatAlgos.patTemplate_cfg import *

## PAT Standard Sequence
process.load("PhysicsTools.PatAlgos.patSequences_cff")

from PhysicsTools.PatAlgos.tools.coreTools import *
## Restrict Output to AOD (no JetID)
restrictInputToAOD(process, ['All',])
## Remove Photons and Taus from the Event
removeSpecificPATObjects(process, ['Photons','Taus'])

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

## Hadron Level Corrections for sisCone5
process.jetCorrFactors.sampleType = 'ttbar'
process.jetCorrFactors.L5Flavor = 'L5Flavor_IC5'
process.jetCorrFactors.L7Parton = 'L7Parton_SC5'
## Parton Level Corrections for antikt5
process.jetCorrFactorsAK5.sampleType = 'ttbar'
process.jetCorrFactorsAK5.L5Flavor = 'L5Flavor_IC5'
process.jetCorrFactorsAK5.L7Parton = 'L7Parton_SC5'

## Define Event Contet
from PhysicsTools.PatAlgos.patEventContent_cff import *
process.out.outputCommands = patExtraAodEventContent
process.out.outputCommands+= patEventContentNoLayer1Cleaning
process.out.outputCommands+= ['keep *_selectedLayer1Jets*_*_*', 'keep *_layer1METs*_*_*']


## Maximal Number of Events
process.maxEvents.input    = 100

## Input Files for Testing
process.source.fileNames   = ['/store/mc/Summer09/TTbar/AODSIM/MC_31X_V3_AODSIM-v1/0024/068F7867-2C88-DE11-B3C2-001F29C9A5AE.root']   

## Options and Output Report
process.options.wantSummary = False
