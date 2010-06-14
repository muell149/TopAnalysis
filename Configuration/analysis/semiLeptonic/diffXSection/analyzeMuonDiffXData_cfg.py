## ---
##    this configfile does the same like analyzeMuonDiffXSec_cfg.py
##    but for data - therefore all gen-plots are thrown out 
## ---

## switch to reco plots only
## -----------------------------
## note: it is important to have
## this definition before the
## execution of the mother file
runningOnData = "data"

## get the mother file
execfile("/afs/naf.desy.de/user/g/goerner/semileptonic361/analyzeMuonDiffXSec_cfg.py")

## reduce output
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

## change number of processed events
process.maxEvents.input = -1

## change source -> data file
process.source.fileNames = ['/store/data/Commissioning10/MinimumBias/RECO/v9/000/135/445/E87253DD-B55F-DF11-AEF2-0030487CD184.root']
#/store/data/Run2010A/JetMETTau/RECO/v2/000/ -> remove run36xOn35xInput(process)

## remove gen particle collections
process.p1.remove(process.isolatedGenMuons)
process.p1.remove(process.semiLeptGenCollections)
process.p2.remove(process.isolatedGenMuons)
process.p2.remove(process.semiLeptGenCollections)

## remove some cut monitoring plots to speed up running
process.p1.remove(process.monitorNMinusOneMuonCuts)
process.p1.remove(process.monitorMuonCutflow)
process.p1.remove(process.monitorVetoCuts)
process.p1.remove(process.monitorNMinusOneJetCuts)
process.p1.remove(process.monitorJetCutflow)
process.p1.remove(process.monitorBtagCuts)

## add configure geometry & conditions
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('GR_R_36X_V10::All')

## add pat default sequence
process.load("PhysicsTools.PatAlgos.patSequences_cff")

## remove MC matching, photons, taus and cleaning from PAT default sequence
from PhysicsTools.PatAlgos.tools.coreTools import *
removeMCMatching(process, ['All'])

removeSpecificPATObjects(process,
                         ['Photons','Taus'],
                         outputInProcess=False)
removeCleaning(process,
               outputInProcess=False)

process.patMuons.usePV = False

from PhysicsTools.PatAlgos.tools.cmsswVersionTools import run36xOn35xInput
run36xOn35xInput(process)

## use the correct jet energy corrections
process.patJetCorrFactors.corrSample = "Spring10"
process.patJetCorrFactors.sampleType = "ttbar"

## remove gen level event filter
process.filterSequence  = cms.Sequence(process.hltMu9 * process.patDefaultSequence)
process.filterSequenceb = cms.Sequence(process.hltMu9 * process.patDefaultSequence)
print "all gen level filters using ttbar decay subset are removed"
print "added pat default sequence"

## change output name 
process.TFileService.fileName = 'analyzeDiffXData_test.root'
