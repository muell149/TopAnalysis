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
process.MessageLogger.cerr.FwkReport.reportEvery = 1

## change number of processed events
process.maxEvents.input = -1
process.source.skipEvents = cms.untracked.uint32(3779)
## change source -> data file
dataFiles = cms.untracked.vstring()
dataFiles.extend([
    '/store/data/Run2010A/Mu/RECO/v4/000/138/457/BC48D2D6-9B7F-DF11-8851-003048F024E0.root',
    '/store/data/Run2010A/Mu/RECO/v4/000/139/407/0AA0D8C2-7888-DF11-9EDB-0019B9F581C9.root',
    '/store/data/Run2010A/Mu/RECO/v4/000/139/407/0AA0D8C2-7888-DF11-9EDB-0019B9F581C9.root',
    '/store/data/Run2010A/Mu/RECO/v4/000/139/407/EEEEE7C8-7B88-DF11-9FFE-003048F024DC.root',
    '/store/data/Run2010A/Mu/RECO/v4/000/139/407/9443ED2B-7888-DF11-A556-000423D94908.root',
    '/store/data/Run2010A/Mu/RECO/v4/000/139/458/1055D2F6-CB88-DF11-923E-001D09F29169.root'
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

## use BeamSpot (not PrimaryVertex) for IP calculation
process.patMuons.usePV = False

## include particle flow MET
from PhysicsTools.PatAlgos.tools.metTools import *
addPfMET(process, 'PF')

# embed IsoDeposits
process.patMuons.isoDeposits = cms.PSet(
    tracker = cms.InputTag("muIsoDepositTk"),
    ecal    = cms.InputTag("muIsoDepositCalByAssociatorTowers","ecal"),
    hcal    = cms.InputTag("muIsoDepositCalByAssociatorTowers","hcal"),
    user    = cms.VInputTag(
                            cms.InputTag("muIsoDepositCalByAssociatorTowers","ho"),
                            cms.InputTag("muIsoDepositJets")
                            ),
    )

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
