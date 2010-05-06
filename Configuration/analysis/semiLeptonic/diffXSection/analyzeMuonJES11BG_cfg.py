## ---
##    this configfile does the same like analyzeMuonDiffXSec_cfg.py
##    but with a JES shift of +10% and for ttbar BG (filtered on gen level)
## ---

## get the mother file
execfile("/afs/naf.desy.de/user/g/goerner/semileptonic356/analyzeMuonDiffXSecBG_cfg.py")

## change input collections to JES-shifted collections
from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
massSearchReplaceAnyInputTag(process.p1, 'selectedPatJets', 'scaledJetEnergy:selectedPatJets') 
massSearchReplaceAnyInputTag(process.p2, 'selectedPatJets', 'scaledJetEnergy:selectedPatJets')
massSearchReplaceAnyInputTag(process.p1, 'patMETs'        , 'scaledJetEnergy:patMETs') 
massSearchReplaceAnyInputTag(process.p2, 'patMETs'        , 'scaledJetEnergy:patMETs')

## get JES-shifting module
process.load("TopAnalysis.TopUtils.JetEnergyScale_cfi")
# set input collection- needed while running on pat tuples
process.scaledJetEnergy.inputJets = "selectedPatJets"
process.scaledJetEnergy.inputMETs = "patMETs"

# JES +10%
process.scaledJetEnergy.scaleFactor = 1.1

## include module to create JES-shifted collection
process.p1.replace(process.semiLeptonicSelection,
                   process.scaledJetEnergy * process.semiLeptonicSelection)

## change monitoring to shifted collection
process.monitorCuts+= process.shiftedJets

## change output name 
process.TFileService.fileName = 'analyzeDiffXSecJES11_testBkg.root'
