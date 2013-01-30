## ---
##    this configfile does the same like analyzeMuonDiffXSec_cfg.py
##    but JER are scaled up by the recommended 10% 
## ---

## get the mother file
#execfile("analyzeMuonDiffXSec_cfg.py")
execfile("analyzeTopDiffXSec_cfg.py")

## change input collections to JER-shifted collections (for reco paths only)
#from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
pathlist = [process.p1, process.p2]#, process.p5]
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
#process.load("TopAnalysis.TopUtils.JetEnergyScale_cfi")
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

# eta-dependent smearing of the jet energy
process.scaledJetEnergy.resolutionFactors   = cms.vdouble( 1.052 , 1.057 , 1.096 , 1.134 , 1.288 )
process.scaledJetEnergy.resolutionEtaRanges = cms.vdouble(0.0,0.5,0.5,1.1,1.1,1.7,1.7,2.3,2.3,-1.)

if(applyKinFit==True):
# use status 3 particles (!)
    process.decaySubset.fillMode = cms.string("kME")

## include module to create JES-shifted collection
for path in pathlist:
    path.replace(process.selectedPatJets,
                 process.selectedPatJets * process.scaledJetEnergy)

## change output name 
#process.TFileService.fileName = 'analyzeDiffXSecCorr_testSig.root'
