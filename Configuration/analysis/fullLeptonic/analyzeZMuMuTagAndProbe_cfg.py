import FWCore.ParameterSet.Config as cms
from PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi import *

process = cms.Process("ZMuMuTagAndProbe")

## switch modeSelector to 1 for TagAndProbe, to 2 for generator efficiency
modeSelector = 1

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool( True )
)
process.MessageLogger.cerr.threshold='INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

## define input (uncomment desired data selection)
## MC:
process.load("TopAnalysis.Configuration.samples.Spring10_ZJets_PATtuple_cff")
#process.source = cms.Source( "PoolSource",
#    fileNames = cms.untracked.vstring(
#        '/store/user/henderle/Spring10/ZJets_MAD/PATtuple_1_1.root'
#    )
#)
## other file name:
#process.source.fileNames = ['/store/user/jlange/samples/Spring10/ZJets-madgraph/PATtuple_1_1_epo.root']
## data: load PAT MuonPreselection
#process.load("TopAnalysis.Configuration.samples.Run2010A_Sep17ReReco_v2_Oct22_cff")
#process.load("TopAnalysis.Configuration.samples.Run2010B_PromptReco_v2_Oct29_145000_147120_cff") ## before hltMu9 prescale
#process.load("TopAnalysis.Configuration.samples.Run2010B_PromptReco_v2_Oct29_147120_148864_cff") ## after hltMu9 prescale

## register TFileService => define output file
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeZMuMuTagAndProbeMC10000test.root')
)
# in case of data: other name
#process.TFileService.fileName = 'analyzeZMuMuTagAndProbeData.root'
#process.TFileService.fileName = 'analyzeZMuMuGenEff10000.root'

## number of events
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32( 10000 )
)


#-----------------------------------------------------------------------------
# ----- C o n f i g u r e   P A T   T r i g g e r ----- #
#-----------------------------------------------------------------------------

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

## Trigger match embedding in selectedPatMuons. In the following selectedPatMuonsTriggerMatch
## must be used to make use of the embedded match
process.selectedPatMuonsTriggerMatch = cms.EDProducer( "PATTriggerMatchMuonEmbedder",
   src     = cms.InputTag( "selectedPatMuons" ),
   matches = cms.VInputTag( "muonTriggerMatchHLTMuons" )
)
process.patTriggerSequence *= process.selectedPatMuonsTriggerMatch


#-----------------------------------------------------------------------------
# ----- P r e p a r e   M u o n   C o l l e c t i o n s ----- #
#-----------------------------------------------------------------------------

## high level trigger filter (to apply trigger on MC events), here: hltMu9
process.load("TopAnalysis.TopFilter.sequences.triggerFilter_cff")

## needed for L1 lookup tables
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('START36_V4::All')


#-----------------------------------------------------------------------------
# -----   P r o d u c e  P r o b e  M u o n s ----- #
#-----------------------------------------------------------------------------

## global muons as candidate for probe muons (loose selection)
process.globalMuons = selectedPatMuons.clone(
  src = 'selectedPatMuonsTriggerMatch',
  cut = 'isGlobalMuon & isTrackerMuon'	
)

## in case of tagAndProbe:
if(modeSelector == 1):
       ## tag muons (tight selection)
       process.tagMuons = selectedPatMuons.clone(
            src = 'selectedPatMuonsTriggerMatch', 
            cut = 'triggerObjectMatches.size > 0 &'
                  'isGlobalMuon & isTrackerMuon &'
                  'track.numberOfValidHits >= 11 &'
                  'combinedMuon.normalizedChi2 < 10.0 &'
                  'abs(dB) < 0.02 &'
                  'ecalIsoDeposit.candEnergy < 4 &'
                  'hcalIsoDeposit.candEnergy < 6 &'
                  '(trackIso+caloIso)/pt < 0.05'
       )
       ## do tagging with help of Z resonance
       from TopAnalysis.TopUtils.taggedProbeMuons_cfi import taggedProbeMuons
       process.probeMuons = taggedProbeMuons.clone(
        tags   = "tagMuons",
        probes = "globalMuons",
        mass   =  91,
        deltaM =  10
       )
       process.produceProbeMuons = cms.Sequence(process.tagMuons * process.probeMuons)
       print "modeSelector =1"

## in case of generator efficiency: 
if(modeSelector == 2):
       ## accept as probe muon if it has a matched genMuon from W or Z (depending on input file)
       process.probeMuons = selectedPatMuons.clone(
         src = 'globalMuons',
         cut = 'genParticlesSize > 0'	
       )
       process.produceProbeMuons = cms.Sequence(process.probeMuons)
       print "modeSelector =2"
	
#-----------------------------------------------------------------------------
# ----- Further Selection on  P r o b e  M u o n s ----- #
#-----------------------------------------------------------------------------

## probe muons to test track quality on: triggered muons
process.probeMuonsTrkQ = selectedPatMuons.clone(
   src = 'probeMuons',
   cut = 'triggerObjectMatches.size > 0'
)

## probe muons to test isolation on: triggered muons passing track quality selection
process.probeMuonsIso = selectedPatMuons.clone(
   src = 'probeMuons',
   cut = 'triggerObjectMatches.size > 0 &'
         'innerTrack.numberOfValidHits >= 11 &'
         'globalTrack.normalizedChi2 < 10.0  &'
         'globalTrack.hitPattern.numberOfValidMuonHits>0 &'
         'abs(dB)<0.02 &'
         'innerTrack.hitPattern.pixelLayersWithMeasurement>=1 &'
         'numberOfMatches>1'
)

## probe muons to test trigger on: muons passing track quality and isolation selection
process.probeMuonsTrigger = selectedPatMuons.clone(
   src = 'probeMuons',
   cut = 'innerTrack.numberOfValidHits >= 11 &'
         'globalTrack.normalizedChi2 < 10.0  &'
         'globalTrack.hitPattern.numberOfValidMuonHits>0 &'
         'abs(dB)<0.02 &'
         'innerTrack.hitPattern.pixelLayersWithMeasurement>=1 &'
         'numberOfMatches>1 &'
         '(trackIso+caloIso)/pt < 0.05'
)


#-----------------------------------------------------------------------------
# ----- P r e p a r e   T e s t   C o l l e c t i o n  ( C u t s ) ----- #
#-----------------------------------------------------------------------------

# cut on track quality
process.testMuonsTrkQ = selectedPatMuons.clone(
  src = 'probeMuonsTrkQ',
  cut = 'innerTrack.numberOfValidHits >= 11 &'
        'globalTrack.normalizedChi2 < 10.0  &'
        'globalTrack.hitPattern.numberOfValidMuonHits>0 &'
        'abs(dB)<0.02 &'
        'innerTrack.hitPattern.pixelLayersWithMeasurement>=1 &'
        'numberOfMatches>1'	
)

# cut on muon isolation
process.testMuonsIso = selectedPatMuons.clone(
  src = 'probeMuonsIso',
  cut = '(trackIso+caloIso)/pt < 0.05'	
)

# check if probe muons (without further selection) fired trigger
process.testMuonsTrigger = selectedPatMuons.clone(
  src = 'probeMuonsTrigger',
  cut = "triggerObjectMatches.size > 0"
)



#-----------------------------------------------------------------------------
# ----- P r e p a r e   J e t   C o l l e c t i o n ----- #
#-----------------------------------------------------------------------------

from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import selectedPatJets

process.selectedJets = selectedPatJets.clone(
  src = 'selectedPatJets', 
  cut = 'abs(eta)<3 & pt>20 &'
        '0.05<emEnergyFraction &'
        '0.95>emEnergyFraction'
)


#-----------------------------------------------------------------------------
# ----- D o   T a g   A n d   P r o b e   A n a l y s i s ----- #
#-----------------------------------------------------------------------------

from TopAnalysis.TopAnalyzer.TagAndProbeAnalyzer_cfi import tagAndProbeAnalyzer

process.tapTrkQ = tagAndProbeAnalyzer.clone(
  probes = "probeMuonsTrkQ", 
  tests  = "testMuonsTrkQ",
  jets   = "selectedJets"
)

process.tapIso = tagAndProbeAnalyzer.clone(
  probes = "probeMuonsIso", 
  tests  = "testMuonsIso",
  jets   = "selectedJets"
)

process.tapTrigger = tagAndProbeAnalyzer.clone(
  probes = "probeMuonsTrigger", 
  tests  = "testMuonsTrigger",
  jets   = "selectedJets"
)


#-----------------------------------------------------------------------------
## ----- H e l p e r   A n a l y z e r s ----- #
#-----------------------------------------------------------------------------

## create triggerMatchedMuons
process.triggerMatchedPatMuons = selectedPatMuons.clone(
  src = "selectedPatMuonsTriggerMatch",
  cut = "triggerObjectMatches.size > 0"
)

## load kinematics analyzer
from TopAnalysis.TopAnalyzer.MuonKinematics_cfi import analyzeMuonKinematics
## load dimuons mass analyzer
from TopAnalysis.TopAnalyzer.DimuonAnalyzer_cfi import analyzeMuonPair

## look at kinematics of all reconstructed muons (i.e. use it before trigger is applied)
process.analyzeAllPatMuons=analyzeMuonKinematics.clone(
  src = "selectedPatMuons",
  analyze = cms.PSet(index = cms.int32(-1))
)

## analyze dimuon mass
process.analyzeAllPatMuonsMass = analyzeMuonPair.clone(
   muons = "selectedPatMuons"
)
	
## look at kinematics of reconstructed muons after HLT_mu9 trigger (i.e. use it after trigger is applied)
process.analyzePostTriggerPatMuons=analyzeMuonKinematics.clone(
  src = "selectedPatMuons",
  analyze = cms.PSet(index = cms.int32(-1))
)

## look at kinematics of muons which fired HLT_Mu9 (i.e. trigger matched muons)
process.analyzeTriggerMatchedPatMuons=analyzeMuonKinematics.clone(
  src = "triggerMatchedPatMuons",
  analyze = cms.PSet(index = cms.int32(-1))
)

## look at kinematics of test muons which fired HLT_Mu9
process.analyzeTestMuonsTrigger=analyzeMuonKinematics.clone(
  src = "testMuonsTrigger",
  analyze = cms.PSet(index = cms.int32(-1))
)

## ----------------------------------------------------------------------------
##    run the final sequence
##-----------------------------------------------------------------------------

process.p1 = cms.Path(
    process.analyzeAllPatMuons     *
    process.analyzeAllPatMuonsMass *
    ## apply trigger selection
    process.hltMu9                 *
    process.analyzePostTriggerPatMuons *
    ## prepare trigger matching
    process.patTriggerSequence     *
    process.triggerMatchedPatMuons *
    process.analyzeTriggerMatchedPatMuons*
    ## prepare probe muons
    process.globalMuons        *
    process.produceProbeMuons  *
    process.probeMuonsTrkQ     *
    process.probeMuonsIso      *
    process.probeMuonsTrigger  *
    ## prepare test muons
    process.testMuonsTrkQ      *
    process.testMuonsIso       *
    process.testMuonsTrigger   *
    process.analyzeTestMuonsTrigger *
    ## prepare jet collection
    process.selectedJets       *
    ## do tag and probe analysis
    process.tapTrkQ            *
    process.tapIso             *
    process.tapTrigger
)
