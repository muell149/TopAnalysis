import FWCore.ParameterSet.Config as cms
from PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi import *

process = cms.Process("ZMuMuTagAndProbe")
## lepton Id for T&P: 11 for electron, 13 for muon
if(not globals().has_key("leptonTypeId")):
	leptonTypeId = 13
## switch modeSelector to 1 for TagAndProbe, to 2 for generator efficiency
if(not globals().has_key("modeSelector")):
	modeSelector = 1
## switch dataSelector to 1 for MC Spring2010, 2 for Fall10 MC, 3 for Spring11, to 11 for Run2010 data (GR_R_38X_V13), to 12 for Run2010 (old RECO, GR_R_36X_V12), to 13 for Run2011A
if(not globals().has_key("dataSelector")):
	dataSelector = 1
## select triggerPath of single muon trigger (HLT_Mu9, HLT_Mu15_v1, ...)
if(not globals().has_key("triggerPathSelector")):
	triggerPathSelector = "HLT_Mu9"
## select triggerPath of second trigger under test (e.g. cross triggers)
## if empty ("") only T&P for first triggerPath is done
if(not globals().has_key("triggerPathSelector2")):
	triggerPathSelector2 = ""
## switch between efficiency and cutflow studies (for purity)
if(not globals().has_key("cutflowSelector")):
	cutflowSelector = "effOnly" # cutflowOnly, effAndCutflow
## select filterPath of cross trigger, which includes the firing muon
if(not globals().has_key("filterPathSelector")):
	filterPathSelector = ""
## select processName of trigger, e.g. "HLT" for data, "REDIGIXXX" for some MC
if(not globals().has_key("triggerProcessName")):
	triggerProcessName = "HLT"
## option to cut L3 trigger object on a new (higher) pTthreshold (default: -1, i.e. switched off)
if(not globals().has_key("triggerPtThresholdNew")):
	triggerPtThresholdNew = -1
## select cut on jet multiplicity for first trigger studies (T&P)
if(not globals().has_key("jetMinNumber")):
	jetMinNumber = 0
## select cut on jet multiplicity for second trigger studies
if(not globals().has_key("jetMinNumber2")):
	jetMinNumber2 = 4
## select jet type (any for calo, "PF" for particle flow
if(not globals().has_key("jetType")):
	jetType = "PF"
	
print "----------------------------------------------"
print "Tag and Probe for Lepton ID (11 electron, 13 muon): ", leptonTypeId
print "----------------------------------------------"

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool( True )
)
process.MessageLogger.cerr.threshold='INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

## define input (uncomment desired data selection)
## MC:
process.load("TopAnalysis.Configuration.samples.DYJetsToLL_M50_D6T_madgraph_F10_cff")
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
## change triggerProcessName, e.g. to HLT or REDIGIXXXX
process.patTrigger.processName      = triggerProcessName
process.patTriggerEvent.processName = triggerProcessName
## the following format for matchedCuts is needed for 3_11_X and higher, e.g.
## matchedCuts = cms.string( 'type( "TriggerMuon" ) && ( path( "HLT_Mu15_v*" ) || path( "HLT_Mu15" ) )' )
if(filterPathSelector == ""):
    matchedCutsString=' type( "TriggerMuon" ) && path( "'+triggerPathSelector+'" )'
else:
    matchedCutsString=' type( "TriggerMuon" ) && path( "'+triggerPathSelector+'" ,0) && filter( "'+filterPathSelector+'" )'
print "matchedCutsString = ", matchedCutsString
## define HLT_Mu9 (or other trigger path) matches
process.muonTriggerMatchHLTMuons = cms.EDProducer( "PATTriggerMatcherDRLessByR",
    src     = cms.InputTag( "selectedPatMuons" ),
    matched = cms.InputTag( "patTrigger" ),
    matchedCuts = cms.string( matchedCutsString ), # adapted to 3_11_X and higher
    #matchedCuts = cms.string( ' type( "TriggerMuon" ) && path( "HLT_Mu15_v*" ,0) && filter("hltSingleMu15L3Filtered15" )'),
    #matchedCuts = cms.string( ' type( "TriggerMuon" ) && path( "HLT_Mu15_v*")'),
    maxDPtRel = cms.double( 0.2 ),  #originally: 0.5
    maxDeltaR = cms.double( 0.2 ),  #originally: 0.5
    resolveAmbiguities    = cms.bool( True ),
    resolveByMatchQuality = cms.bool( True )
)

## configure patTrigger & patTriggerEvent
process.patTriggerEvent.patTriggerMatches = [ "muonTriggerMatchHLTMuons" ]

## Trigger match embedding in selectedPatMuons. In the following selectedPatMuonsTriggerMatch
## must be used to make use of the embedded match
process.selectedPatMuonsTriggerMatch = cms.EDProducer( "PATTriggerMatchMuonEmbedder",
   src     = cms.InputTag( "selectedPatMuons" ),
   matches = cms.VInputTag( "muonTriggerMatchHLTMuons" )
)

## HELPER ANALYZERS:
## load kinematics analyzer
from TopAnalysis.TopAnalyzer.MuonKinematics_cfi import analyzeMuonKinematics
## load quality analyzer
from TopAnalysis.TopAnalyzer.MuonQuality_cfi import analyzeMuonQuality
## load dimuons mass analyzer
from TopAnalysis.TopAnalyzer.DimuonAnalyzer_cfi import analyzeMuonPair



## look at kinematics of leading reconstructed muons after trigger
process.analyzePostTriggerLeadPatMuons=analyzeMuonKinematics.clone(
  src = "selectedPatMuons",
  analyze = cms.PSet(index = cms.int32(0))
)
## look at kinematics of leading reconstructed muons after emulation of new trigger
process.analyzePostTriggerEmuLeadPatMuons=analyzeMuonKinematics.clone(
  src = "selectedPatMuons",
  analyze = cms.PSet(index = cms.int32(0))
)

if(triggerPtThresholdNew>0):
    print "triggerPtThresholdNew = ", triggerPtThresholdNew
    ## emulation of a new trigger using a higher pt threshold of the trigger objects
    from TopAnalysis.TopFilter.filters.TriggerObjectFilter_cfi import filterTriggerObject
    process.hltMu17FilterEmulation = filterTriggerObject.clone( hltPaths = ["HLT_Mu15", "HLT_Mu15_v1", "HLT_Mu15_v2", "HLT_Mu15_v3", "HLT_Mu15_v4", "HLT_Mu15_v5", "HLT_Mu15_v6", "HLT_Mu15_v7", "HLT_Mu15_v8", "HLT_Mu15_v9"], ptMin=triggerPtThresholdNew )

    process.patTriggerSequenceUser = cms.Sequence(
      process.patTrigger *
      process.muonTriggerMatchHLTMuons *
      process.patTriggerEvent *
      process.selectedPatMuonsTriggerMatch *
      process.analyzePostTriggerLeadPatMuons*
      process.hltMu17FilterEmulation        *
      process.analyzePostTriggerEmuLeadPatMuons
    )

else:
    print "no new triggerPtThresholdNew set"
    process.patTriggerSequenceUser = cms.Sequence(
      process.patTrigger *
      process.muonTriggerMatchHLTMuons *
      process.patTriggerEvent *
      process.selectedPatMuonsTriggerMatch *
      process.analyzePostTriggerLeadPatMuons
    )


#-----------------------------------------------------------------------------
# ----- P r e p a r e   M u o n   C o l l e c t i o n s ----- #
#-----------------------------------------------------------------------------

## high level trigger filter (to apply trigger on MC events), here: hltMu9 or other single-mu trigger
#process.load("TopAnalysis.TopFilter.sequences.triggerFilter_cff")
from HLTrigger.HLTfilters.hltHighLevel_cfi import *
#process.hltTriggerFilter = hltHighLevel.clone(HLTPaths = [triggerPathSelector])
triggerResultsTagString = "TriggerResults::"+triggerProcessName
print "triggerResultsTagString = ", triggerResultsTagString
#process.hltTriggerFilter = hltHighLevel.clone(TriggerResultsTag = "TriggerResults::REDIGI311X", HLTPaths = ["HLT_Mu9"], throw=False)
process.hltTriggerFilter = hltHighLevel.clone(TriggerResultsTag = triggerResultsTagString, HLTPaths = [triggerPathSelector], throw=False)

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
elif(dataSelector == 3):
     process.GlobalTag.globaltag = cms.string('START311_V2::All')
     print "dataSelector = 3"
elif(dataSelector == 11):
     process.GlobalTag.globaltag = cms.string('GR_R_38X_V15::All')
     print "dataSelector = 11"
elif(dataSelector == 12):
     process.GlobalTag.globaltag = cms.string('GR_R_36X_V12::All')
     print "dataSelector = 12"
elif(dataSelector == 13):
     process.GlobalTag.globaltag = cms.string('GR_R_311_V3::All')
     print "dataSelector = 13"
elif(dataSelector == 14):
     process.GlobalTag.globaltag = cms.string('GR_R_41_V0::All')
     ##-------------------- Import the JEC services -----------------------
     process.load('JetMETCorrections.Configuration.DefaultJEC_cff')
     ##-------------------- Import the Jet RECO modules -----------------------
     process.load('RecoJets.Configuration.RecoPFJets_cff')

     print "dataSelector = 14"
else:
     print "ERROR! DataSelector not defined. No global tag can be chosen."

#-----------------------------------------------------------------------------
# ----- P r e p a r e   S t a n d a r d   C o l l e c t i o n s ----- #
#-----------------------------------------------------------------------------

## apply event selection
## semileptonic selection
process.load("TopAnalysis.TopFilter.sequences.semiLeptonicSelection_cff")
### redefine veto jets to be sure it is also replaced when running on PF
from TopAnalysis.TopFilter.sequences.jetSelection_cff import goodJets
process.vetoJets.src="goodJets"
process.vetoJets.cut=''    

#-----------------------------------------------------------------------------
# ----- P r e p a r e   J e t   C o l l e c t i o n ----- #
#-----------------------------------------------------------------------------

from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import selectedPatJets
from PhysicsTools.PatAlgos.cleaningLayer1.jetCleaner_cfi import *

## according to official selection (from TopAnalysis/TopFilter/python/sequences/jetSelection_cff)
if(jetType == "PF") :
     process.selectedJets = process.goodJetsPF30.clone()
     process.selectedJetsSequence = cms.Sequence(process.selectedJets)
     print "jetType=", jetType
else:
     process.selectedJets = process.goodJets.clone()
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
        deltaM =  15,
	leptonId = leptonTypeId
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
# ----- Efficiency Studies using Single Muon Trigger as Control Trigger ----- #
#-----------------------------------------------------------------------------
if(triggerPathSelector2 == ""):
    print "Only T&P for ", triggerPathSelector, ", no efficiency studies for a second trigger done."
    ## dummy process - ignore!!!
    process.effStudies2 = cms.Sequence(process.hltTriggerFilter)
else:
    print "Additional efficiency studies for", triggerPathSelector2, "; ", triggerPathSelector, "as control trigger."
    process.leadingJetSelectionNjets = process.leadingJetSelection.clone (src = 'tightLeadingPFJets', minNumber = jetMinNumber2)
    
    ## second HLT trigger filter
    process.hltTriggerFilter2 = hltHighLevel.clone(HLTPaths = [triggerPathSelector2])
    
    ## jet kinematics analyzer
    process.load("TopAnalysis.TopAnalyzer.JetKinematics_cfi")
    ## define ordered jets
    ## ATTENTION!!! For MC it should be 'L3Absolute' !!!!
    corrLevel='L2L3Residual'
    uds0    = cms.PSet(index = cms.int32(0),  correctionLevel = cms.string(corrLevel), useTree = cms.bool(False) )
    uds1    = cms.PSet(index = cms.int32(1),  correctionLevel = cms.string(corrLevel), useTree = cms.bool(False) )
    uds2    = cms.PSet(index = cms.int32(2),  correctionLevel = cms.string(corrLevel), useTree = cms.bool(False) )
    uds3    = cms.PSet(index = cms.int32(3),  correctionLevel = cms.string(corrLevel), useTree = cms.bool(False) )
    udsAll  = cms.PSet(index = cms.int32(-1), correctionLevel = cms.string(corrLevel), useTree = cms.bool(False) )
    ##  Jet Kinematics Analyzer for the first 4 and all jets, for events fired by trigger 1 before the jet cut
    process.analyzeJet0Trig1BeforeCut  = process.analyzeJetKinematics.clone (src = 'tightLeadingPFJets', analyze = uds0 )
    process.analyzeJet1Trig1BeforeCut  = process.analyzeJetKinematics.clone (src = 'tightLeadingPFJets', analyze = uds1 )
    process.analyzeJet2Trig1BeforeCut  = process.analyzeJetKinematics.clone (src = 'tightLeadingPFJets', analyze = uds2 )
    process.analyzeJet3Trig1BeforeCut  = process.analyzeJetKinematics.clone (src = 'tightLeadingPFJets', analyze = uds3 )
    process.analyzeJetAllTrig1BeforeCut= process.analyzeJetKinematics.clone (src = 'tightLeadingPFJets', analyze = udsAll)
    ##  Jet Kinematics Analyzer for the first 4 and all jets, for events fired by trigger 1 after the jet cut 
    process.analyzeJet0Trig1AfterCut  = process.analyzeJet0Trig1BeforeCut.clone() 
    process.analyzeJet1Trig1AfterCut  = process.analyzeJet1Trig1BeforeCut.clone()
    process.analyzeJet2Trig1AfterCut  = process.analyzeJet2Trig1BeforeCut.clone()
    process.analyzeJet3Trig1AfterCut  = process.analyzeJet3Trig1BeforeCut.clone()
    process.analyzeJetAllTrig1AfterCut= process.analyzeJetAllTrig1BeforeCut.clone()
    ##  Jet Kinematics Analyzer for the first 4 and all jets, for events fired by trigger 2 after the jet cut
    process.analyzeJet0Trig2AfterCut  = process.analyzeJet0Trig1BeforeCut.clone()
    process.analyzeJet1Trig2AfterCut  = process.analyzeJet1Trig1BeforeCut.clone()
    process.analyzeJet2Trig2AfterCut  = process.analyzeJet2Trig1BeforeCut.clone()
    process.analyzeJet3Trig2AfterCut  = process.analyzeJet3Trig1BeforeCut.clone()
    process.analyzeJetAllTrig2AfterCut= process.analyzeJetAllTrig1BeforeCut.clone()
    
    ## muon kinematics and quality analyzer
    ## look at kinematics of muons after the first trigger
    process.analyzeMuonKinematicsTrig1=analyzeMuonKinematics.clone(
      src = "tightMuons",
      analyze = cms.PSet(index = cms.int32(-1))
    )
    ## muon kinematics and quality analyzer
    ## look at kinematics of muons after the first trigger
    process.analyzeSelectedPatMuon0KinematicsTrig1=analyzeMuonKinematics.clone(
      src = "selectedPatMuons",
      analyze = cms.PSet(index = cms.int32(0))
    )
    ## look at kinematics of muons after the second trigger
    process.analyzeMuonKinematicsTrig2=analyzeMuonKinematics.clone(
      src = "tightMuons",
      analyze = cms.PSet(index = cms.int32(-1))
    )
    ## look at quality of muons after the first trigger
    process.analyzeMuonQualityTrig1=analyzeMuonQuality.clone(
      src = "tightMuons",
      analyze = cms.PSet(index = cms.int32(-1))
    )
    ## look at quality of muons after the second trigger
    process.analyzeMuonQualityTrig2=analyzeMuonQuality.clone(
      src = "tightMuons",
      analyze = cms.PSet(index = cms.int32(-1))
    )
    
    process.effStudies2 = cms.Sequence(
       ## introduce some collections
       #process.semiLeptonicSelection                 *
       ## muon selection
       process.muonSelection                         *
       ## veto on additional leptons
       process.secondMuonVeto                        *
       process.electronVeto                          *
       ## jet kinematics analyzer for events fired by trigger 1 before the jet cut
       process.analyzeJet0Trig1BeforeCut             *
       process.analyzeJet1Trig1BeforeCut             *
       process.analyzeJet2Trig1BeforeCut             *
       process.analyzeJet3Trig1BeforeCut             *
       process.analyzeJetAllTrig1BeforeCut           *
       ## jet selection
       process.leadingJetSelectionNjets              *
       ## jet kinematics analyzer for events fired by trigger 1 after the jet cut
       process.analyzeJet0Trig1AfterCut              *
       process.analyzeJet1Trig1AfterCut              *
       process.analyzeJet2Trig1AfterCut              *
       process.analyzeJet3Trig1AfterCut              *
       process.analyzeJetAllTrig1AfterCut            *
       ## muon analyzer  for events fired by trigger 1 after the cuts
       process.analyzeSelectedPatMuon0KinematicsTrig1*
       process.analyzeMuonKinematicsTrig1            *
       process.analyzeMuonQualityTrig1               * 
       ## second HLT trigger filter
       process.hltTriggerFilter2                     *
       ## jet kinematics analyzer for events fired by trigger 2 after the jet cut
       process.analyzeJet0Trig2AfterCut              *
       process.analyzeJet1Trig2AfterCut              *
       process.analyzeJet2Trig2AfterCut              *
       process.analyzeJet3Trig2AfterCut              *
       process.analyzeJetAllTrig2AfterCut            *
       ## muon analyzer  for events fired by trigger 1 after the cuts
       process.analyzeMuonKinematicsTrig2            *
       process.analyzeMuonQualityTrig2
    )


#-----------------------------------------------------------------------------
# ----- H e l p e r   A n a l y z e r s ----- #
#-----------------------------------------------------------------------------

## create triggerMatchedMuons
process.triggerMatchedPatMuons = selectedPatMuons.clone(
  src = "selectedPatMuonsTriggerMatch",
  cut = "triggerObjectMatches.size > 0"
)

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
    process.patTriggerSequenceUser     *
    process.triggerMatchedPatMuons *
    process.analyzeTriggerMatchedPatMuons*
    ## introduce some collections
    process.semiLeptonicSelection        *
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
    process.tapTrigger         *
    ## efficiency studies using Single Muon Trigger as Control Trigger
    process.effStudies2
)

    ## switch to PF objects
if(jetType=="PF"):
    from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
    #pathlist = [process.p1, process.p2]
    allpaths  = process.paths_().keys()
    for path in allpaths: #pathlist:  
        massSearchReplaceAnyInputTag(getattr(process,path), 'tightLeadingJets', 'tightLeadingPFJets')
        massSearchReplaceAnyInputTag(getattr(process,path), 'tightBottomJets' , 'tightBottomPFJets' )
        massSearchReplaceAnyInputTag(getattr(process,path), 'goodJets'        , 'goodJetsPF30'      )
        massSearchReplaceAnyInputTag(getattr(process,path), 'centralJets'     , 'centralJetsPF30'   )
        massSearchReplaceAnyInputTag(getattr(process,path), 'reliableJets'    , 'reliableJetsPF30'  )
        massSearchReplaceAnyInputTag(getattr(process,path), 'noEtaJets'       , 'noEtaJetsPF30'     )
        massSearchReplaceAnyInputTag(getattr(process,path), 'noPtJets'        , 'noPtJetsPF'        )
        massSearchReplaceAnyInputTag(getattr(process,path), 'patMETs'         , 'patMETsPF'         )
        getattr(process,path).remove(process.centralJets)
        getattr(process,path).remove(process.reliableJets)
        getattr(process,path).remove(process.goodJets)
        getattr(process,path).remove(process.tightLeadingJets)
        getattr(process,path).remove(process.tightBottomJets)
