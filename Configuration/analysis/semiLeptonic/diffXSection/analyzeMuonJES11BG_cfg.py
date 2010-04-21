## ---
##    this configfile does the same like analyzeMuonDiffXSec_cfg.py
##    but with a JES shift of +10% and for ttbar BG (filtered on gen level)
## ---

## get the mother file
execfile("/afs/naf.desy.de/user/g/goerner/semileptonic356/analyzeMuonDiffXSecBG_cfg.py")

## get JES-shifting module
process.load("TopAnalysis.TopUtils.JetEnergyScale_cfi")
# set input collection- needed while running on pat tuples
process.scaledJetEnergy.inputJets = "selectedPatJets"
# JES +10%
process.scaledJetEnergy.scaleFactor = 1.1

## include module to create JES-shifted collection
process.p1.replace(process.semiLeptonicSelection,
                   process.scaledJetEnergy * process.semiLeptonicSelection)

## change monitoring to shifted collection
process.p1.replace(process.unshiftedJets,
                   process.shiftedJets)

## change input collection to JES-shifted collection 
## ATTENTION: this needs to be adapted when running on 3_5_X MC samples
process.centralJets.src = "scaledJetEnergy:selectedLayer1Jets"
process.reliableJets.src = "scaledJetEnergy:selectedLayer1Jets"
process.goodJets.src = "scaledJetEnergy:selectedLayer1Jets"

## change output name 
process.TFileService.fileName = 'analyzeDiffXSecJES11_testBkg.root'

# replace label names when running on old (3_4_X) MC samples
inputs = ['Electrons','Jets','Taus','Muons','Photons']
from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
for input in inputs:
    massSearchReplaceAnyInputTag(process.p1, 'patMETs', 'layer1METs')    
    massSearchReplaceAnyInputTag(process.p1, 'selectedPat'+input, 'selectedLayer1'+input)
