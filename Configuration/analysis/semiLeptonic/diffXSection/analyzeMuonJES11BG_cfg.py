## ---
##    this configfile does the same like analyzeMuonDiffXSec_cfg.py
##    but shifting JES up and for ttbar BG (filtered on gen level)
## ---

## get the mother file
execfile("analyzeMuonDiffXSecBG_cfg.py")

## change input collections to JES-shifted collections
from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
if(jetType=="particleFlow"):
    massSearchReplaceAnyInputTag(process.p1, 'selectedPatJetsAK5PF', 'scaledJetEnergy:selectedPatJetsAK5PF') 
    massSearchReplaceAnyInputTag(process.p2, 'selectedPatJetsAK5PF', 'scaledJetEnergy:selectedPatJetsAK5PF')
    massSearchReplaceAnyInputTag(process.p3, 'selectedPatJetsAK5PF', 'scaledJetEnergy:selectedPatJetsAK5PF')
    massSearchReplaceAnyInputTag(process.p1, 'patMETsPF'           , 'scaledJetEnergy:patMETsPF') 
    massSearchReplaceAnyInputTag(process.p2, 'patMETsPF'           , 'scaledJetEnergy:patMETsPF')
    massSearchReplaceAnyInputTag(process.p3, 'patMETsPF'           , 'scaledJetEnergy:patMETsPF')
elif(jetType=="Calo"):
    massSearchReplaceAnyInputTag(process.p1, 'selectedPatJets', 'scaledJetEnergy:selectedPatJets') 
    massSearchReplaceAnyInputTag(process.p2, 'selectedPatJets', 'scaledJetEnergy:selectedPatJets')
    massSearchReplaceAnyInputTag(process.p3, 'selectedPatJets', 'scaledJetEnergy:selectedPatJets')
    massSearchReplaceAnyInputTag(process.p1, 'patMETs'        , 'scaledJetEnergy:patMETs') 
    massSearchReplaceAnyInputTag(process.p2, 'patMETs'        , 'scaledJetEnergy:patMETs')
    massSearchReplaceAnyInputTag(process.p3, 'patMETs'        , 'scaledJetEnergy:patMETs')
else:
    print "unknown jetType"

## get JES-shifting module
process.load("TopAnalysis.TopUtils.JetEnergyScale_cfi")
# set input collection- needed while running on pat tuples
if(jetType=="particleFlow"):
    process.scaledJetEnergy.inputJets = "selectedPatJetsAK5PF"
    process.scaledJetEnergy.inputMETs = "patMETsPF"
elif(jetType=="Calo"):
    process.scaledJetEnergy.inputJets = "selectedPatJets"
    process.scaledJetEnergy.inputMETs = "patMETs"
else:
    print "unknown jetType"

# JES +5%
process.scaledJetEnergy.scaleFactor = 1.05

## include module to create JES-shifted collection
process.p1.replace(process.semiLeptonicSelection,
                   process.scaledJetEnergy * process.semiLeptonicSelection)
process.p2.replace(process.semiLeptonicSelection,
                   process.scaledJetEnergy * process.semiLeptonicSelection)
process.p3.replace(process.semiLeptonicSelection,
                   process.scaledJetEnergy * process.semiLeptonicSelection)

## change monitoring to shifted collection
process.monitorJetCutflow+= process.shiftedJets

## change output name 
process.TFileService.fileName = 'analyzeDiffXSecJES11_testBkg.root'
