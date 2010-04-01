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

## Add particle flow jets
from PhysicsTools.PatAlgos.tools.jetTools import *
#addJetID(process, "antikt5PFJets", "pf")
addJetCollection(process,cms.InputTag('antikt5PFJets'),'PF',
              doJTA        = True,
              doBTagging   = True,
              jetCorrLabel = ('AK5', 'PF'),
              doType1MET   = False,
              doL1Cleaning = False,
              doL1Counters = False,
              genJetCollection=cms.InputTag("antikt5GenJets"),
              doJetID      = False,
              ) 

## Check the Event Content
process.content = cms.EDAnalyzer("EventContentAnalyzer")

process.p = cms.Path(
    process.patDefaultSequence # + process.content
)

## Special Replacements

## sample type used for flavour dependend jet corrections
process.patJetCorrFactors.sampleType = 'ttbar'
process.patJetCorrFactorsPF.sampleType = 'ttbar'

## Define Event Contet
from PhysicsTools.PatAlgos.patEventContent_cff import *
process.out.fileName = cms.untracked.string('PATtuple.root')
process.out.outputCommands = patExtraAodEventContent
process.out.outputCommands+= patEventContentNoCleaning
process.out.outputCommands+= ['keep *_selectedPatJets*_*_*', 'keep *_patMETs*_*_*']


## Maximal Number of Events
process.maxEvents.input    = 100

## Input Files for Testing
process.source.fileNames   = ['/store/mc/Summer09/ZmumuJet_Pt50to80/GEN-SIM-RECO/MC_31X_V3-v1/0034/A02B9E45-F18D-DE11-ADC7-00E0812DB027.root']

## Options and Output Report
process.options.wantSummary = False
