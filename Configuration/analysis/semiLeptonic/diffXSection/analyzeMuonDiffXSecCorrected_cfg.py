## ---
##    this configfile does the same like analyzeMuonDiffXSec_cfg.py
##    but JER are scaled up by the recommended 10% 
## ---

## get the mother file
#execfile("analyzeMuonDiffXSec_cfg.py")
execfile("analyzeTopDiffXSec_cfg.py")

## change input collections to JER-shifted collections (for reco paths only)
from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
pathlist = [process.p1, process.p2]
for path in pathlist:
    if(jetType=="particleFlow"):
        massSearchReplaceAnyInputTag(path, 'selectedPatJetsAK5PF', 'scaledJetEnergy:selectedPatJetsAK5PF')
        massSearchReplaceAnyInputTag(path, 'patMETsPF'           , 'scaledJetEnergy:patMETsPF'           )
    elif(jetType=="Calo"):
        massSearchReplaceAnyInputTag(path, 'selectedPatJets', 'scaledJetEnergy:selectedPatJets') 
        massSearchReplaceAnyInputTag(path, 'patMETs'        , 'scaledJetEnergy:patMETs'        )
    if(pfToPAT==True):
        massSearchReplaceAnyInputTag(path, 'selectedPatJets', 'scaledJetEnergy:selectedPatJets')
        massSearchReplaceAnyInputTag(path, 'patMETs'        , 'scaledJetEnergy:patMETs'        )
    else:
        print "unknown jetType"

## get JER/JES-shifting module
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
if(pfToPAT==True):
    process.scaledJetEnergy.inputJets = "selectedPatJets"
    process.scaledJetEnergy.inputMETs = "patMETs"

# JER +10%
process.scaledJetEnergy.resolutionFactor = 1.1
if(applyKinFit==True):
    process.kinFitTtSemiLepEventHypothesis.jetEnergyResolutionSmearFactor = 1.1

## include module to create JES-shifted collection
for path in pathlist:
    path.replace(process.PVSelection,
                 process.PVSelection * process.scaledJetEnergy)

## change output name 
process.TFileService.fileName = 'analyzeDiffXSecCorr_testSig.root'
