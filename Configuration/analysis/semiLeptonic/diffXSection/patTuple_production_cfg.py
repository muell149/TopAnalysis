from PhysicsTools.PatAlgos.patTemplate_cfg import *

## PAT Standard Sequence
process.load("PhysicsTools.PatAlgos.patSequences_cff")

from PhysicsTools.PatAlgos.tools.coreTools import *
## Remove Photons and Taus from the Event
removeSpecificPATObjects(process, ['Photons','Taus'])

from PhysicsTools.PatAlgos.tools.cmsswVersionTools import *
## Run 3_3_x version on 3_1_x-samples
run33xOn31xMC(process,
               jetSrc = cms.InputTag("antikt5CaloJets"),
               jetIdTag = "antikt5"
              )

## Add antikt and siscone jets
from PhysicsTools.PatAlgos.tools.jetTools import *
addJetID(process, "sisCone5CaloJets", "sc5")
addJetCollection(process,cms.InputTag('sisCone5CaloJets'),
                 'SC5',
                 doJTA        = True,
                 doBTagging   = True,
                 jetCorrLabel = ('SC5','Calo'),
                 doType1MET   = True,
                 doL1Cleaning = False,                 
                 doL1Counters = False,
                 genJetCollection=cms.InputTag("sisCone5GenJets"),
                 doJetID      = True,
                 jetIdLabel   = "sc5"                 
                 )

addJetID(process, "iterativeCone5CaloJets", "ic5")
addJetCollection(process,cms.InputTag('iterativeCone5CaloJets'),
                 'IC5',
                 doJTA        = True,
                 doBTagging   = True,
                 jetCorrLabel = ('IC5', 'Calo'),
                 doType1MET   = True,
                 doL1Cleaning = False,                 
                 doL1Counters = False,
                 genJetCollection=cms.InputTag("iterativeCone5GenJets"),
                 doJetID      = True,
                 jetIdLabel   = "ic5"
                 )

## Check the Event Content
process.content = cms.EDAnalyzer("EventContentAnalyzer")

process.p = cms.Path(
    process.patDefaultSequence # + process.content
)

## Special Replacements

## sample type used for flavour dependend jet corrections
process.jetCorrFactors.sampleType = 'ttbar'
process.jetCorrFactorsIC5.sampleType = 'ttbar'
process.jetCorrFactorsSC5.sampleType = 'ttbar'

## Define Event Contet
from PhysicsTools.PatAlgos.patEventContent_cff import *
process.out.fileName = cms.untracked.string('PATtuple.root')
process.out.outputCommands = patExtraAodEventContent
process.out.outputCommands+= patEventContentNoLayer1Cleaning
process.out.outputCommands+= ['keep *_selectedLayer1Jets*_*_*', 'keep *_layer1METs*_*_*']


## Maximal Number of Events
process.maxEvents.input    = 100

## Input Files for Testing
process.source.fileNames   = ['/store/mc/Summer09/ZmumuJet_Pt50to80/GEN-SIM-RECO/MC_31X_V3-v1/0034/A02B9E45-F18D-DE11-ADC7-00E0812DB027.root']

## Options and Output Report
process.options.wantSummary = False
