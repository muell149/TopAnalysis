## ---
##    this configfile does the same like analyzeMuonDiffXSec_cfg.py
##    but with a JES shift of -10%
## ---

## get the mother file
execfile("/afs/naf.desy.de/user/g/goerner/semileptonic356/analyzeMuonDiffXSec_cfg.py")

## get JES-shifting module
process.load("TopAnalysis.TopUtils.JetEnergyScale_cfi")
# set input collection- needed while running on pat tuples
process.scaledJetEnergy.inputJets = "selectedPatJets"
# JES -10%
process.scaledJetEnergy.scaleFactor = 0.9

## include module to create JES-shifted collection
process.p1.replace(process.semiLeptonicSelection,
                   process.scaledJetEnergy * process.semiLeptonicSelection)

## change monitoring to shifted collection
process.monitorCuts+= process.shiftedJets

## change input collection to JES-shifted collection
process.centralJets.src =  'scaledJetEnergy:selectedPatJets'
process.reliableJets.src = 'scaledJetEnergy:selectedPatJets'
process.goodJets.src =     'scaledJetEnergy:selectedPatJets'

## change output name 
process.TFileService.fileName = 'analyzeDiffXSecJES09_testSig.root'

# replace MET label name when running on old (3_4_X) MC samples
inputs = ['Electrons','Jets','Taus','Muons','Photons']
from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
for input in inputs:
    massSearchReplaceAnyInputTag(process.p1, 'patMETs', 'layer1METs')    
    massSearchReplaceAnyInputTag(process.p1, 'selectedPat'+input, 'selectedLayer1'+input)
    massSearchReplaceAnyInputTag(process.p1, 'scaledJetEnergy:selectedPatJets', 'scaledJetEnergy:selectedLayer1Jets')
