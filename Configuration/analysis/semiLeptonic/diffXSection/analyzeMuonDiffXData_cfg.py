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
writeOutput = True

## get the mother file
execfile("/afs/naf.desy.de/user/g/goerner/semileptonic361/analyzeMuonDiffXSec_cfg.py")

## reduce output
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

## change number of processed events
process.maxEvents.input = 100

## change source -> data file
dataFiles = cms.untracked.vstring()
dataFiles.extend([
'/store/data/Run2010A/JetMETTau/RECO/v2/000/136/088/50E30071-6C67-DF11-8831-000423D98930.root'
])

process.source.fileNames = dataFiles

## remove gen particle collections
process.p1.remove(process.isolatedGenMuons)
process.p1.remove(process.semiLeptGenCollections)
process.p2.remove(process.isolatedGenMuons)
process.p2.remove(process.semiLeptGenCollections)

## add configure geometry & conditions
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('GR_R_36X_V12::All')

## create tuples with events surviving the cuts
## a) Njets>=1
## process.pat1 = cms.Path(
##                       ## do the trigger selection (hltMu9)
##                       process.hltMu9b                               *
##                       ## do the PV event selection
##                       process.PVSelectionb                          *
##                       ## introduce collections
##                       process.semiLeptonicSelection                 *
##                       ## do the event selection for muon
##                       process.muonSelectionb                        *
##                       ## do event selection veto cuts
##                       process.secondMuonVetob                       *
##                       process.electronVetob                         *
##                       ## N_jets >= 1
##                       process.leadingJetSelectionNjets1
##                       )
## ## b) Njets>=2
## process.pat2 = cms.Path(
##                       ## do the trigger selection (hltMu9)
##                       process.hltMu9b                               *
##                       ## do the PV event selection
##                       process.PVSelectionb                          *
##                       ## introduce collections
##                       process.semiLeptonicSelection                 *
##                       ## do the event selection for muon
##                       process.muonSelectionb                        *
##                       ## do event selection veto cuts
##                       process.secondMuonVetob                       *
##                       process.electronVetob                         *
##                       ## N_jets >= 2
##                       process.leadingJetSelectionNjets2
##                       )
## b) Njets>=3
process.pat3 = cms.Path(
                      ## do the trigger selection (hltMu9)
                      process.hltMu9b                               *
                      ## do the PV event selection
                      process.PVSelectionb                          *
                      ## introduce collections
                      process.semiLeptonicSelection                 *
                      ## do the event selection for muon
                      process.muonSelectionb                        *
                      ## do event selection veto cuts
                      process.secondMuonVetob                       *
                      process.electronVetob                         *
                      ## N_jets >= 3
                      process.leadingJetSelectionNjets3
                      )

process.out.SelectEvents = cms.untracked.PSet( SelectEvents = cms.vstring('pat3') )
process.out.fileName = cms.untracked.string('patTuple_selectedNjets3.root')

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
from PhysicsTools.PatAlgos.tools.metTools import *
addPfMET(process, 'PF')

## use the correct jet energy corrections
process.patJetCorrFactors.corrSample = "Spring10"
process.patJetCorrFactors.sampleType = "ttbar"

## remove gen level event filter
process.filterSequence  = cms.Sequence(process.hltMu9 * process.patDefaultSequence)
process.filterSequenceb = cms.Sequence(process.hltMu9 * process.patDefaultSequence)
print "all gen level filters using ttbar decay subset are removed"
print "added pat default sequence"

## change output name 
process.TFileService.fileName = 'analyzeDiffXData.root'
