import FWCore.ParameterSet.Config as cms

process = cms.Process("ZMuMuTagAndProbe")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'WARNING'
process.MessageLogger.cerr.FwkReport.reportEvery = 10000
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool( True )
)

## define input
process.source = cms.Source( "PoolSource",
    fileNames = cms.untracked.vstring(
        '/store/user/henderle/Spring10/WJets_MAD/PATtuple_8_1.root'
    )
)
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32( 1000 )
)

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeZMuMuTagAndProbe.root')
)


# ----- C o n f i g u r e   P A T   T r i g g e r ----- #


## needed for L1 lookup tables
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('START36_V4::All')

## trigger sequences
process.load( "PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cff" )

## define HLT_Mu9 matches
process.muonTriggerMatchHLTMuons = cms.EDFilter( "PATTriggerMatcherDRLessByR",
    src     = cms.InputTag( "selectedPatMuons" ),
    matched = cms.InputTag( "patTrigger" ),
    andOr          = cms.bool( False ),
    filterIdsEnum  = cms.vstring( 'TriggerMuon' ),
    filterIds      = cms.vint32 ( 0 ),
    filterLabels   = cms.vstring( '*' ),
    pathNames      = cms.vstring( 'HLT_Mu9' ),
    collectionTags = cms.vstring( '*' ),
    maxDPtRel = cms.double( 0.5 ),
    maxDeltaR = cms.double( 0.5 ),
    resolveAmbiguities    = cms.bool( True ),
    resolveByMatchQuality = cms.bool( True )
)

## take obsolete matches out of the patTriggerMatcher sequence
## and add the match that is relevant for this analysis
process.patTriggerMatcher += process.muonTriggerMatchHLTMuons
process.patTriggerMatcher.remove( process.patTriggerMatcherElectron )
process.patTriggerMatcher.remove( process.patTriggerMatcherMuon )
process.patTriggerMatcher.remove( process.patTriggerMatcherTau )

## configure patTrigger & patTriggerEvent
process.patTrigger.onlyStandAlone = False
process.patTriggerEvent.patTriggerMatches = [ "muonTriggerMatchHLTMuons" ]

## high level trigger filter
process.load("TopAnalysis.TopFilter.sequences.triggerFilter_cff")


# ----- P r e p a r e   M u o n   C o l l e c t i o n s ----- #


## create triggerMatchedMuons
process.load( "TopAnalysis.TopUtils.triggerMatchedMuons_cfi" )

from PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi import *

from TopAnalysis.TopUtils.taggedProbeMuons_cfi import taggedProbeMuons
taggedProbeMuons.tags   = "selectedPatMuons"
taggedProbeMuons.mass   =  90
taggedProbeMuons.deltaM =   5

## start collection
process.combPT = selectedPatMuons.clone(src = 'selectedPatMuons', 
                                        cut = 'combinedMuon.isNull = 0 &'
                                              '(trackIso+caloIso)/pt < 0.05'
                                        )
process.comb = taggedProbeMuons.clone(probes = 'combPT')

## validHits
process.combValhitPT = selectedPatMuons.clone(src = 'combPT', 
                                              cut = 'track.numberOfValidHits >= 11'
                                              )
process.combValhit = taggedProbeMuons.clone(probes = 'combValhitPT')

## chi2
process.combChi2PT = selectedPatMuons.clone(src = 'combPT', 
                                            cut = 'combinedMuon.normalizedChi2 < 10.0'
                                            )
process.combChi2 = taggedProbeMuons.clone(probes = 'combChi2PT')

## dB
process.combTrksigPT = selectedPatMuons.clone(src = 'combPT', 
                                              cut = 'abs(dB) < 0.02'
                                              )
process.combTrksig = taggedProbeMuons.clone(probes = 'combTrksigPT')

## ecal
process.combEcalPT = selectedPatMuons.clone(src = 'combPT', 
                                            cut = 'ecalIsoDeposit.candEnergy < 4'           
                                            )
process.combEcal = taggedProbeMuons.clone(probes = 'combEcalPT')

## hcal
process.combHcalPT = selectedPatMuons.clone(src = 'combPT', 
                                            cut = 'hcalIsoDeposit.candEnergy < 6'           
                                            )
process.combHcal = taggedProbeMuons.clone(probes = 'combHcalPT')

## trigger muons
process.combTrigPT = selectedPatMuons.clone(src = 'triggerMatchedMuons', 
                                          cut = 'combinedMuon.isNull = 0 &'
                                                '(trackIso+caloIso)/pt < 0.05'
                                          )
process.combTrig = taggedProbeMuons.clone(probes = 'combTrigPT')

## tag muons
process.tagMuons = selectedPatMuons.clone(src = 'combTrigPT', 
                                          cut = 'track.numberOfValidHits >= 11 &'
                                                'combinedMuon.normalizedChi2 < 10.0  &'
                                                'abs(dB) < 0.02 &'
                                                'ecalIsoDeposit.candEnergy < 4 &'
                                                'hcalIsoDeposit.candEnergy < 6'
                                          )

process.muonCollections = cms.Sequence(
    ## produce pre tag collections
    process.combPT          +
    process.combValhitPT    +
    process.combChi2PT      +
    process.combTrksigPT    +
    process.combEcalPT      +
    process.combHcalPT      +
    process.combTrigPT      +
    process.tagMuons        +
    ## produce tagged probe collections
    process.comb            +
    process.combValhit      +
    process.combChi2        +
    process.combTrksig      +
    process.combEcal        +
    process.combHcal        +
    process.combTrig
)            


# ----- P r e p a r e   J e t   C o l l e c t i o n ----- #


from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import *

process.jetsCF2 = selectedPatJets.clone(src = 'selectedPatJets', 
                                        cut = 'abs(eta)<3  &  pt>20 &'
                                              '0.05 < emEnergyFraction  &'
                                              '0.95 > emEnergyFraction'
                                        )


# ----- D o   T a g   A n d   P r o b e   A n a l y s i s ----- #

process.load("TopAnalysis.TopAnalyzer.TagAndProbeAnalyzer_cfi")

process.comb_combValhit   = process.tagAndProbeAnalyzer.clone(probes = "comb", tests = "combValhit" ,   jets = "jetsCF2")
process.comb_combChi2     = process.tagAndProbeAnalyzer.clone(probes = "comb", tests = "combChi2"   ,   jets = "jetsCF2")
process.comb_combTrksig   = process.tagAndProbeAnalyzer.clone(probes = "comb", tests = "combTrksig" ,   jets = "jetsCF2")
process.comb_combEcal     = process.tagAndProbeAnalyzer.clone(probes = "comb", tests = "combEcal"   ,   jets = "jetsCF2")
process.comb_combHcal     = process.tagAndProbeAnalyzer.clone(probes = "comb", tests = "combHcal"   ,   jets = "jetsCF2")
process.comb_combValhit_3 = process.tagAndProbeAnalyzer.clone(probes = "comb", tests = "combTrig"   ,   jets = "jetsCF2")

process.tagAndProbeAnalysis = cms.Sequence(
    process.comb_combValhit  +
    process.comb_combChi2    +
    process.comb_combTrksig  +
    process.comb_combEcal    +
    process.comb_combHcal    +
    process.comb_combValhit_3                
 )


## ---
##    run the final sequence
## ---
process.p1 = cms.Path(
    ## apply trigger selection and matching
    process.hltMu9              *
    process.patTriggerSequence  *
    process.triggerMatchedMuons *
    ## prepare muon input collections
    process.muonCollections     *
    ## prepare jet collection
    process.jetsCF2             *
    ## do tag and probe analysis
    process.tagAndProbeAnalysis
)
