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
process.maxEvents.input = 200
process.source.skipEvents = cms.untracked.uint32(0)
## change source -> data file
dataFiles = cms.untracked.vstring()
dataFiles.extend([
    ##'/store/data/Run2010A/Mu/RECO/v4/000/138/457/BC48D2D6-9B7F-DF11-8851-003048F024E0.root'
    '/store/data/Run2010A/Mu/RECO/v4/000/140/124/84F485E8-668F-DF11-9F8E-003048F11114.root'
    ])

process.source.fileNames = dataFiles

## remove gen particle collections
process.p1.remove(process.isolatedGenMuons)
process.p1.remove(process.semiLeptGenCollections)
process.p2.remove(process.isolatedGenMuons)
process.p2.remove(process.semiLeptGenCollections)

## add configure geometry & conditions
process.load("Configuration.StandardSequences.Geometry_cff")
#process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('GR_R_36X_V12::All')
#process.GlobalTag.globaltag = cms.string('GR_R_36X_V11A::All')

## create tuples with events surviving the cuts
## for Njets>=4
process.out.SelectEvents = cms.untracked.PSet( SelectEvents = cms.vstring('p1') )
process.out.fileName = cms.untracked.string('patTuple_selectedNjets4.root')

## do cleaning steps
## a) beam scrap filter
#process.beamScrapFilter = cms.EDFilter("FilterOutScraping",
#                                       applyfilter = cms.untracked.bool(True),
#                                       debugOn     = cms.untracked.bool(False),
#                                       numtrack    = cms.untracked.uint32(10),
#                                       thresh      = cms.untracked.double(0.25)
#                                       )
# b) HBHE noise filter
#process.load('CommonTools.RecoAlgos.HBHENoiseFilter_cfi')
# c) spike cleaning
#process.load('EGamma.EGammaSkims.cleanReRecoSequence_cff')				      
# d) get electrons corrected for EE misalignment
#from RecoEgamma.EgammaTools.correctedElectronsProducer_cfi import *
#process.load('RecoEgamma.ElectronIdentification.electronIdSequence_cff')

#process.cleaningSteps = cms.Sequence(process.beamScrapFilter        *  
#                                     process.HBHENoiseFilter        *
#                                     process.cleanedEgammaSkimReco  *
#                                     process.eIdSequence    
#                                     )

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

## d) apply EE misalignment cleaning to electrons
#process.load('RecoEgamma.ElectronIdentification.electronIdSequence_cff')
#process.patElectrons.electronSource = "gsfElectrons::PAT"

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

## use residual jet corrections for data
process.load("TopAnalysis.TopUtils.ResidualJetCorrector_cfi")
process.residualCorrectedJets = process.residualCorrectedJets.clone()
#process.residualCorrectedJets.jets = 'selectedPatJets '
#process.residualCorrectedJets.jetType = 'PF'
from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
massSearchReplaceAnyInputTag(process.p1, 'selectedPatJets', 'residualCorrectedJets')
massSearchReplaceAnyInputTag(process.p2, 'selectedPatJets', 'residualCorrectedJets')
massSearchReplaceAnyInputTag(process.p3, 'selectedPatJets', 'residualCorrectedJets')
print "residual jet corrections used!"

## remove gen level event filter + add residual jet correction sequence
process.filterSequence     = cms.Sequence(process.hltMu9     * process.patDefaultSequence * process.residualCorrectedJets)
process.filterSequenceb    = cms.Sequence(process.hltMu9b    * process.patDefaultSequence * process.residualCorrectedJets)
process.filterSequenceABCD = cms.Sequence(process.hltMu9ABCD * process.patDefaultSequence * process.residualCorrectedJets)
print "all gen level filters using ttbar decay subset are removed"
print "added pat default sequence"

## change output name 
process.TFileService.fileName = 'analyzeDiffXData.root'
