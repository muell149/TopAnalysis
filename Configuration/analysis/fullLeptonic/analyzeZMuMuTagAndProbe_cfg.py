import FWCore.ParameterSet.Config as cms
from PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi import *

process = cms.Process("ZMuMuTagAndProbe")

## switch modeSelector to 1 for TagAndProbe, to 2 for generator efficiency
if(not globals().has_key("modeSelector")):
	modeSelector = 1
## switch dataSelector to 1 for MC Spring2010, 2 for Fall10 MC, to 11 for Run2010 data (GR_R_38X_V13), to 12 for Run2010 (old RECO, GR_R_36X_V12), to 
if(not globals().has_key("dataSelector")):
	dataSelector = 1
## select triggerPath (HLT_Mu9, HLT_Mu15_v1, ...)
if(not globals().has_key("triggerPathSelector")):
	triggerPathSelector = "HLT_Mu9"
## select cut on jet multiplicity
if(not globals().has_key("jetMinNumber")):
	jetMinNumber = 0
## select jet type (any for calo, "PF" for particle flow
if(not globals().has_key("jetType")):
	jetType = "calo"

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

## register TFileService => define output file
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeZMuMuTagAndProbeMCtest.root')
)

## number of events
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32( 1000 )
)

#----------------------------------------------------------------------------
#    Filter on Primary Vertex
#----------------------------------------------------------------------------
## new DiffXSection version (compatible with SelV4)
process.PVSelection = cms.EDFilter("PrimaryVertexFilter",
                                   pvSrc   = cms.InputTag('offlinePrimaryVertices'),
                                   minNdof = cms.double(4.0),
                                   maxZ    = cms.double(24.0),
                                   maxRho  = cms.double(2.0)
                                   )


#-----------------------------------------------------------------------------
# ----- C o n f i g u r e   P A T   T r i g g e r ----- #
#-----------------------------------------------------------------------------

## trigger sequences
process.load( "PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cff" )
print triggerPathSelector
## define HLT_Mu9 (or other trigger path) matches
process.muonTriggerMatchHLTMuons = cms.EDProducer( "PATTriggerMatcherDRLessByR",
    src     = cms.InputTag( "selectedPatMuons" ),
    matched = cms.InputTag( "patTrigger" ),
    andOr          = cms.bool( False ),
    filterIdsEnum  = cms.vstring( 'TriggerMuon' ),
    filterIds      = cms.vint32 ( 0 ),
    filterLabels   = cms.vstring( '*' ),
    pathNames      = cms.vstring( triggerPathSelector ),
    collectionTags = cms.vstring( '*' ),
    maxDPtRel = cms.double( 0.2 ),  #originally: 0.5
    maxDeltaR = cms.double( 0.2 ),  #originally: 0.5
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
## works with CMSSW_3_8_4, might need change for 3_8_7
process.selectedPatMuonsTriggerMatch = cms.EDProducer( "PATTriggerMatchMuonEmbedder",
   src     = cms.InputTag( "selectedPatMuons" ),
   matches = cms.VInputTag( "muonTriggerMatchHLTMuons" )
)
process.patTriggerSequence *= process.selectedPatMuonsTriggerMatch


#-----------------------------------------------------------------------------
# ----- P r e p a r e   M u o n   C o l l e c t i o n s ----- #
#-----------------------------------------------------------------------------

## high level trigger filter (to apply trigger on MC events), here: hltMu9 or other single-mu trigger
#process.load("TopAnalysis.TopFilter.sequences.triggerFilter_cff")
from HLTrigger.HLTfilters.hltHighLevel_cfi import *
process.hltTriggerFilter = hltHighLevel.clone(HLTPaths = [triggerPathSelector])

## Global tags
## needed for L1 lookup tables
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
print "dataSelector = ", dataSelector
if(dataSelector == 1):
     process.GlobalTag.globaltag = cms.string('START36_V4::All')
     print "dataSelector = 1"
elif(dataSelector == 2):
     process.GlobalTag.globaltag = cms.string('START38_V14::All')
     print "dataSelector = 2"
elif(dataSelector == 11):
     process.GlobalTag.globaltag = cms.string('GR_R_38X_V15::All')
     print "dataSelector = 11"
elif(dataSelector == 12):
     process.GlobalTag.globaltag = cms.string('GR_R_36X_V12::All')
     print "dataSelector = 12"
else:
     print "ERROR! DataSelector not defined. No global tag can be chosen."

#-----------------------------------------------------------------------------
# ----- P r e p a r e   J e t   C o l l e c t i o n ----- #
#-----------------------------------------------------------------------------

from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import selectedPatJets
from PhysicsTools.PatAlgos.cleaningLayer1.jetCleaner_cfi import *

## according to official selection (from TopAnalysis/TopFilter/python/sequences/jetSelection_cff)
if(jetType == "PF") :
     ## PF for CMSSW_3_8_6; for 387 change!!!! (e.g. cancel corrFactor)
     ## patMuons muons with deltaZ(muonVertex, PV) < 1
     process.vertexSelectedMuons = cms.EDProducer("MuonVertexDistanceSelector",
       src           = cms.InputTag("selectedPatMuonsTriggerMatch"),
       primaryVertex = cms.InputTag("offlinePrimaryVertices")
     )
     process.noOverlapJetsPF = cleanPatJets.clone(
       src = cms.InputTag("selectedPatJetsAK5PF"), 

       ## preselection (any string-based cut on pat::Jet)
       preselection = cms.string(''),

       ## overlap checking configurables
       checkOverlaps = cms.PSet(
           muons = cms.PSet(
              src       = cms.InputTag("vertexSelectedMuons"),
              algorithm = cms.string("byDeltaR"),
              preselection        = cms.string('pt > 20. & abs(eta) < 2.1 &'
                                             'combinedMuon.isNull = 0 &'
                                             'isTrackerMuon() =1 &'
                                             '(trackIso+caloIso)/pt < 0.05 &'
                                             'innerTrack.numberOfValidHits >= 11 &'
                                             'globalTrack.normalizedChi2 < 10.0 &'
                                             'globalTrack.hitPattern.numberOfValidMuonHits>0 &'
                                             'abs(dB)<0.02 &'
                                             'innerTrack.hitPattern.pixelLayersWithMeasurement>=1 &'
                                             'numberOfMatches>1'),
              deltaR              = cms.double(0.1),
              checkRecoComponents = cms.bool(False), # don't check if they share some AOD object ref
              pairCut             = cms.string(""),
              requireNoOverlaps   = cms.bool(True), # overlaps don't cause the jet to be discared
           )
      ),
      ## finalCut (any string-based cut on pat::Jet)
      finalCut = cms.string(''),
     )
     
     process.selectedJets = selectedPatJets.clone(
       src = 'noOverlapJetsPF',
       cut = 'abs(eta) < 2.4 & pt > 30. &'
             'chargedHadronEnergyFraction > 0.0  &'
             'neutralHadronEnergyFraction/corrFactor("raw") < 0.99 &'
             'chargedEmEnergyFraction/corrFactor("raw")     < 0.99 &'
             'neutralEmEnergyFraction/corrFactor("raw")     < 0.99 &'
             'chargedMultiplicity > 0            &'
             'nConstituents > 1'
     )
     process.selectedJetsSequence = cms.Sequence(process.vertexSelectedMuons * 
                                         process.noOverlapJetsPF     *
                                         process.selectedJets)
     print "jetType=", jetType
else:
     ## calo jets
     process.selectedJets = selectedPatJets.clone(
       src = 'selectedPatJets',
       cut = 'abs(eta) < 2.4 & pt > 30. &'
             'emEnergyFraction > 0.01   &'
             'jetID.fHPD < 0.98         &'
             'jetID.n90Hits > 1'
     )
     process.selectedJetsSequence = cms.Sequence(process.selectedJets)
     print "jetType=", jetType


## if desired: Jet Count Filter (filters on NJets)
from PhysicsTools.PatAlgos.selectionLayer1.jetCountFilter_cfi import *
process.jetMultCut1 = countPatJets.clone(
  src = 'selectedJets',
  minNumber = jetMinNumber
)
if(jetMinNumber == 0):
     process.jetMultCut = cms.Sequence()
     print "jetMinNumber=0"
else:
     process.jetMultCut = cms.Sequence(process.jetMultCut1)
     print "jetMinNumber=", jetMinNumber



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
       ## tag muons (tight selection) according to V4
       process.tagMuonsNoDR = selectedPatMuons.clone(
            src = 'selectedPatMuonsTriggerMatch', 
            cut = 'triggerObjectMatches.size > 0 &'
                  'isGlobalMuon & isTrackerMuon &'
                  'pt > 20. &'
                  'abs(eta) < 2.1 &'
                  'innerTrack.numberOfValidHits >= 11 &'
                  'globalTrack.normalizedChi2 < 10.0  &'
                  'globalTrack.hitPattern.numberOfValidMuonHits>0 &'
                  'abs(dB)<0.02 &'
                  'innerTrack.hitPattern.pixelLayersWithMeasurement>=1 &'
                  'numberOfMatches>1 &'
                  '(trackIso+caloIso)/pt < 0.05'
       )
       ## jet-muon-distance filter
       process.tagMuons = cms.EDProducer("MuonJetOverlapSelector",
            ## input muon collection
            muons = cms.InputTag("tagMuonsNoDR"),
            ## jet collection to check overlap
            jets = cms.InputTag("selectedJets"),
            ## define overlap region (<deltaR)
            deltaR = cms.double(0.3),
            ## choose whether you want to
            ## include/exclude overlapping
            ## muons in the created collection
            ## include: overlap = true,
            ## exclude: overlap = false
            overlap = cms.bool(False)
       )


       ## do tagging with help of Z resonance
       from TopAnalysis.TopUtils.taggedProbeMuons_cfi import taggedProbeMuons
       process.probeMuons = taggedProbeMuons.clone(
        tags   = "tagMuons",
        probes = "globalMuons",
        mass   =  91,
        deltaM =  15
       )
       process.produceProbeMuons = cms.Sequence(process.tagMuonsNoDR *process.tagMuons * process.probeMuons)
       print "modeSelector =1"

## in case of generator efficiency: 
elif(modeSelector == 2):
       ## accept as probe muon if it has a matched genMuon from W or Z (depending on input file)
       process.probeMuons = selectedPatMuons.clone(
         src = 'globalMuons',
         cut = 'genParticlesSize > 0'	
       )
       process.produceProbeMuons = cms.Sequence(process.probeMuons)
       print "modeSelector =2"

else:
       print "ERROR! ModeSelector not defined. No probeMuons produced."
	
#-----------------------------------------------------------------------------
# ----- Further Selection on  P r o b e  M u o n s ----- #
#-----------------------------------------------------------------------------

## probe muons with deltaZ(muonVertex, PV) < 1
process.probeMuonsDZ = cms.EDProducer("MuonVertexDistanceSelector",
  src           = cms.InputTag("probeMuons"),
  primaryVertex = cms.InputTag("offlinePrimaryVertices")
)

## probe muons to test track quality on: triggered muons
process.probeMuonsTrkQ = selectedPatMuons.clone(
   src = 'probeMuons',
   cut = ''
)

## probe muons to test track significance dB on: muons with other track quality cuts
process.probeMuonsTrkSig = selectedPatMuons.clone(
   src = 'probeMuonsDZ',
   cut = 'innerTrack.numberOfValidHits >= 11 &'
         'globalTrack.normalizedChi2 < 10.0  &'
         'globalTrack.hitPattern.numberOfValidMuonHits>0 &'
         'innerTrack.hitPattern.pixelLayersWithMeasurement>=1 &'
         'numberOfMatches>1'
)

## probe muons to test isolation on: muons passing track quality selection
process.probeMuonsIso = selectedPatMuons.clone(
   src = 'probeMuonsDZ',
   cut = 'innerTrack.numberOfValidHits >= 11 &'
         'globalTrack.normalizedChi2 < 10.0  &'
         'globalTrack.hitPattern.numberOfValidMuonHits>0 &'
         'abs(dB)<0.02 &'
         'innerTrack.hitPattern.pixelLayersWithMeasurement>=1 &'
         'numberOfMatches>1'
)

## probe muons to test cut of minimum distance (mu,jet) on: isolated muons
process.probeMuonsMinDR = selectedPatMuons.clone(
   src = 'probeMuonsDZ',
   cut = 'innerTrack.numberOfValidHits >= 11 &'
         'globalTrack.normalizedChi2 < 10.0  &'
         'globalTrack.hitPattern.numberOfValidMuonHits>0 &'
         'abs(dB)<0.02 &'
         'innerTrack.hitPattern.pixelLayersWithMeasurement>=1 &'
         'numberOfMatches>1 &'
         '(trackIso+caloIso)/pt < 0.05'
)

## probe muons to test cut of minimum distance (mu,jet) on: NON-isolated muons
process.probeMuonsMinDRNoIso = selectedPatMuons.clone(
   src = 'probeMuonsDZ',
   cut = 'innerTrack.numberOfValidHits >= 11 &'
         'globalTrack.normalizedChi2 < 10.0  &'
         'globalTrack.hitPattern.numberOfValidMuonHits>0 &'
         'abs(dB)<0.02 &'
         'innerTrack.hitPattern.pixelLayersWithMeasurement>=1 &'
         'numberOfMatches>1'
)

## probe muons to test total selection: only global & tracker 
process.probeMuonsTotalSelection = selectedPatMuons.clone(
   src = 'probeMuons',
   cut = ''
)

## probe muons to test trigger on: muons passing track quality and isolation selection
process.probeMuonsTriggerNoDR = selectedPatMuons.clone(
   src = 'probeMuonsDZ',
   cut = 'innerTrack.numberOfValidHits >= 11 &'
         'globalTrack.normalizedChi2 < 10.0  &'
         'globalTrack.hitPattern.numberOfValidMuonHits>0 &'
         'abs(dB)<0.02 &'
         'innerTrack.hitPattern.pixelLayersWithMeasurement>=1 &'
         'numberOfMatches>1 &'
         '(trackIso+caloIso)/pt < 0.05'
)
process.probeMuonsTrigger = cms.EDProducer("MuonJetOverlapSelector",
  muons = cms.InputTag("probeMuonsTriggerNoDR"),
  jets = cms.InputTag("selectedJets"),
  deltaR = cms.double(0.3),
  overlap = cms.bool(False)
)


#-----------------------------------------------------------------------------
# ----- P r e p a r e   T e s t   C o l l e c t i o n  ( C u t s ) ----- #
#-----------------------------------------------------------------------------

## cut on track quality
process.testMuonsTrkQNoDZ = selectedPatMuons.clone(
  src = 'probeMuonsTrkQ',
  cut = 'innerTrack.numberOfValidHits >= 11 &'
        'globalTrack.normalizedChi2 < 10.0  &'
        'globalTrack.hitPattern.numberOfValidMuonHits>0 &'
        'abs(dB)<0.02 &'
        'innerTrack.hitPattern.pixelLayersWithMeasurement>=1 &'
        'numberOfMatches>1'	
)
## deltaZ(muonVertex, PV) < 1
process.testMuonsTrkQ = cms.EDProducer("MuonVertexDistanceSelector",
  src           = cms.InputTag("testMuonsTrkQNoDZ"),
  primaryVertex = cms.InputTag("offlinePrimaryVertices")
)


## cut on track significance
process.testMuonsTrkSig = selectedPatMuons.clone(
  src = 'probeMuonsTrkSig',
  cut = 'abs(dB)<0.02'	
)

## cut on muon isolation
process.testMuonsIso = selectedPatMuons.clone(
  src = 'probeMuonsIso',
  cut = '(trackIso+caloIso)/pt < 0.05'	
)

## cut on jet-muon-distance
process.testMuonsMinDR = cms.EDProducer("MuonJetOverlapSelector",
  muons = cms.InputTag("probeMuonsMinDR"),
  jets = cms.InputTag("selectedJets"),
  deltaR = cms.double(0.3),
  overlap = cms.bool(False)
)

## cut on jet-muon-distance before isolation cut
process.testMuonsMinDRNoIso = cms.EDProducer("MuonJetOverlapSelector",
  muons = cms.InputTag("probeMuonsMinDRNoIso"),
  jets = cms.InputTag("selectedJets"),
  deltaR = cms.double(0.3),
  overlap = cms.bool(False)
)

## test the whole muon selection except trigger
process.testMuonsTotalSelectionNoDZNoDR = selectedPatMuons.clone(
  src = 'probeMuonsTotalSelection',
  cut = 'innerTrack.numberOfValidHits >= 11 &'
        'globalTrack.normalizedChi2 < 10.0  &'
        'globalTrack.hitPattern.numberOfValidMuonHits>0 &'
        'abs(dB)<0.02 &'
        'innerTrack.hitPattern.pixelLayersWithMeasurement>=1 &'
        'numberOfMatches>1 &'
        '(trackIso+caloIso)/pt < 0.05'
)
## deltaZ(muonVertex, PV) < 1
process.testMuonsTotalSelectionNoDR = cms.EDProducer("MuonVertexDistanceSelector",
  src           = cms.InputTag("testMuonsTotalSelectionNoDZNoDR"),
  primaryVertex = cms.InputTag("offlinePrimaryVertices")
)
process.testMuonsTotalSelection = cms.EDProducer("MuonJetOverlapSelector",
  muons = cms.InputTag("testMuonsTotalSelectionNoDR"),
  jets = cms.InputTag("selectedJets"),
  deltaR = cms.double(0.3),
  overlap = cms.bool(False)
)

## check if probe muons (without further selection) fired trigger
process.testMuonsTrigger = selectedPatMuons.clone(
  src = 'probeMuonsTrigger',
  cut = "triggerObjectMatches.size > 0"
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

process.tapTrkSig = tagAndProbeAnalyzer.clone(
  probes = "probeMuonsTrkSig", 
  tests  = "testMuonsTrkSig",
  jets   = "selectedJets"
)

process.tapIso = tagAndProbeAnalyzer.clone(
  probes = "probeMuonsIso", 
  tests  = "testMuonsIso",
  jets   = "selectedJets"
)

process.tapMinDR = tagAndProbeAnalyzer.clone(
  probes = "probeMuonsMinDR", 
  tests  = "testMuonsMinDR",
  jets   = "selectedJets"
)

process.tapMinDRNoIso = tagAndProbeAnalyzer.clone(
  probes = "probeMuonsMinDRNoIso", 
  tests  = "testMuonsMinDRNoIso",
  jets   = "selectedJets"
)

process.tapTotalSelection = tagAndProbeAnalyzer.clone(
  probes = "probeMuonsTotalSelection", 
  tests  = "testMuonsTotalSelection",
  jets   = "selectedJets"
)

process.tapTrigger = tagAndProbeAnalyzer.clone(
  probes = "probeMuonsTrigger", 
  tests  = "testMuonsTrigger",
  jets   = "selectedJets"
)


#-----------------------------------------------------------------------------
# ----- H e l p e r   A n a l y z e r s ----- #
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
    ## apply primary vertex selection
    process.PVSelection                *
    ## apply trigger selection
    process.hltTriggerFilter           *
    process.analyzePostTriggerPatMuons *
    ## prepare trigger matching
    process.patTriggerSequence     *
    process.triggerMatchedPatMuons *
    process.analyzeTriggerMatchedPatMuons*
    ## prepare jet collection
    process.selectedJetsSequence *
    process.jetMultCut         *
    ## prepare probe muons
    process.globalMuons        *
    process.produceProbeMuons  *
    process.probeMuonsDZ       *
    process.probeMuonsTrkQ     *
    process.probeMuonsTrkSig   *
    process.probeMuonsIso      *
    process.probeMuonsMinDR      *
    process.probeMuonsMinDRNoIso *
    process.probeMuonsTotalSelection *
    process.probeMuonsTriggerNoDR  *
    process.probeMuonsTrigger  *
    ## prepare test muons
    process.testMuonsTrkQNoDZ  *
    process.testMuonsTrkQ      *
    process.testMuonsTrkSig    *
    process.testMuonsIso       *
    process.testMuonsMinDR     *
    process.testMuonsMinDRNoIso*
    process.testMuonsTotalSelectionNoDZNoDR *
    process.testMuonsTotalSelectionNoDR *
    process.testMuonsTotalSelection *
    process.testMuonsTrigger   *
    process.analyzeTestMuonsTrigger *
    ## do tag and probe analysis
    process.tapTrkQ            *
    process.tapTrkSig          *
    process.tapIso             *
    process.tapMinDR           *
    process.tapMinDRNoIso      *
    process.tapTotalSelection  *
    process.tapTrigger
)
