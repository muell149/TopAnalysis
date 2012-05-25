##
## This is the generic T&P config file (both for Z->mumu and Z->ele ele despite the name)
##


import FWCore.ParameterSet.Config as cms
from PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi import *
from PhysicsTools.PatAlgos.selectionLayer1.electronSelector_cfi import *

process = cms.Process("ZMuMuTagAndProbe")
## lepton Id for T&P: 11 for electron, 13 for muon
if(not globals().has_key("leptonTypeId")):
	leptonTypeId = 13
## switch modeSelector to 1 for TagAndProbe, to 2 for generator efficiency
if(not globals().has_key("modeSelector")):
	modeSelector = 1
## switch dataSelector to 1 for MC Summer11, to 11 for Run2011 data (GR_R_38X_V13)
if(not globals().has_key("dataSelector")):
	dataSelector = 1
## select triggerPath of single muon trigger (HLT_Mu9, HLT_Mu15_v1, ...)
if(not globals().has_key("triggerPathSelector")):
	triggerPathSelector = "HLT_Mu9"
## select triggerPath of second trigger under test (e.g. cross triggers)
## if empty ("") only T&P for first triggerPath is done
if(not globals().has_key("triggerPathSelector2")):
	triggerPathSelector2 = ""
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
	jetMinNumber2 = 0
## select jet type (any for calo, "PF" for particle flow
if(not globals().has_key("jetType")):
	jetType = "PF"
## change muonPtCut from default if >0
if(not globals().has_key("muonPtCut")):
	muonPtCut = 30.
## run PF2PAT?
## only possible for special pat tuples!!!
if(not globals().has_key('pfToPAT')):
    pfToPAT = True #False
print "run PF2PAT?: ",pfToPAT," won't work if the file does not contain the necessary information!"
## select whether to run directly on AOD
if(not globals().has_key("runOnAOD")):
	runOnAOD = True
if(not globals().has_key("PF2PATwithoutLeptonIsoCut")):
	PF2PATwithoutLeptonIsoCut = True
## choose JSON file for data
if(not globals().has_key('jsonFile')):
    jsonFile =  ''
## enable/ disable PU event reweighting
if(not globals().has_key('PUreweighting')):
    PUreweighting = True
## switch PU reweighting off for data
if(dataSelector>10):
    PUreweighting = False
print "apply PU reweighting?: ",PUreweighting
## change relIso value for top projection; default = 0.2 is enabled if relIsoTopProj = -1
if(not globals().has_key('relIsoTopProj')):
    relIsoTopProj = -1
## change mass window deltaM
if(not globals().has_key("deltaM")):
	deltaM = 15

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
## inpu tag for selectedPatMuons/Electrons
if(leptonTypeId == 11):
    selectedPatLeptons = "selectedPatElectrons"
elif(leptonTypeId == 13):
    selectedPatLeptons = "selectedPatMuons"

## the following format for matchedCuts is needed for 3_11_X and higher, e.g.
## matchedCuts = cms.string( 'type( "TriggerMuon" ) && ( path( "HLT_Mu15_v*" ) || path( "HLT_Mu15" ) )' )
if(filterPathSelector == ""):
    ## in path (after triggerPathSelector): first number stands for lastFilterAccepted, the second
    ## number for L3FilterAccepted
    matchedCutsString=' path( "'+triggerPathSelector+'",1,0 )'
elif(triggerPathSelector == "*"):
    matchedCutsString='filter( "'+filterPathSelector+'" )'
else:
    matchedCutsString=' path( "'+triggerPathSelector+'" ,0) && filter( "'+filterPathSelector+'" )'
print "matchedCutsString = ", matchedCutsString
## define HLT_Mu9 (or other trigger path) matches
process.muonTriggerMatchHLTMuons = cms.EDProducer( "PATTriggerMatcherDRLessByR",
    src     = cms.InputTag( selectedPatLeptons ),
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
if(leptonTypeId == 11):
    process.selectedPatMuonsTriggerMatch = cms.EDProducer( "PATTriggerMatchElectronEmbedder",
      src     = cms.InputTag( "selectedPatElectrons" ),
      matches = cms.VInputTag( "muonTriggerMatchHLTMuons" )
    )
elif(leptonTypeId == 13):
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
  analyze = cms.PSet(useTree  = cms.bool(False), index = cms.int32(0))
)
## look at kinematics of leading reconstructed muons after emulation of new trigger
process.analyzePostTriggerEmuLeadPatMuons=analyzeMuonKinematics.clone(
  src = "selectedPatMuons",
  analyze = cms.PSet(useTree  = cms.bool(False), index = cms.int32(0))
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
      #process.analyzePostTriggerLeadPatMuons*
      process.hltMu17FilterEmulation
      #process.analyzePostTriggerEmuLeadPatMuons
    )

else:
    print "no new triggerPtThresholdNew set"
    process.patTriggerSequenceUser = cms.Sequence(
      process.patTrigger *
      process.muonTriggerMatchHLTMuons *
      process.patTriggerEvent *
      process.selectedPatMuonsTriggerMatch
      #process.analyzePostTriggerLeadPatMuons
    )


#-----------------------------------------------------------------------------
# ----- R U N   D E T A I L S                       ----- #
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
     process.GlobalTag.globaltag = cms.string('START42_V17::All')
     jsonFile = ""
     print "dataSelector = 1, global tag: ", process.GlobalTag.globaltag
elif(dataSelector == 11):
     process.GlobalTag.globaltag = cms.string('GR_R_42_V23::All')
     ##-------------------- Import the JEC services -----------------------
     #process.load('JetMETCorrections.Configuration.DefaultJEC_cff')
     ##-------------------- Import the Jet RECO modules -----------------------
     #process.load('RecoJets.Configuration.RecoPFJets_cff')
     
     ## load JSON file for data
     if(jsonFile!=""):
	  import PhysicsTools.PythonAnalysis.LumiList as LumiList
	  import FWCore.ParameterSet.Types as CfgTypes
	  print "The following JSON file is used in the cfg file: ", jsonFile
	  myLumis = LumiList.LumiList(filename = jsonFile).getCMSSWString().split(',')
	  process.source.lumisToProcess = CfgTypes.untracked(CfgTypes.VLuminosityBlockRange())
	  process.source.lumisToProcess.extend(myLumis)
	  ## ATTENTION!!! At the moment myLumis are filled in the separate data_cfg files again
	  ## as otherwise overwritten by load("data_cff")
     else:
	  print "No JSON file specified in cfg file (but possibly via CRAB)."


     print "dataSelector = 11, global tag: ", process.GlobalTag.globaltag
else:
     print "ERROR! DataSelector not defined. No global tag can be chosen."
     
#-----------------------------------------------------------------------------
# ----- MC PU reweighting                                         ----- #
#-----------------------------------------------------------------------------

process.load("TopAnalysis.TopUtils.EventWeightPU_cfi")

## Apply common setting before module is cloned for systematic studies

process.eventWeightPU.MCSampleTag = "Fall11"

process.eventWeightPU.MCSampleHistoName        = "histo_Fall11_true"
process.eventWeightPU.DataHistoName            = "histoData_true"

process.eventWeightPU           = process.eventWeightPU.clone()
process.eventWeightPUsysUp      = process.eventWeightPU.clone()
process.eventWeightPUsysDown    = process.eventWeightPU.clone()
process.eventWeightPUEPS        = process.eventWeightPU.clone()
process.eventWeightPU2011B      = process.eventWeightPU.clone()
process.eventWeightPUEle32      = process.eventWeightPU.clone()
process.eventWeightPUEle32WP70 = process.eventWeightPU.clone()

#### Configuration for Nominal PU Weights

process.eventWeightPU.WeightName          = "eventWeightPU"
process.eventWeightPU.DataFile            = "TopAnalysis/TopUtils/data/Data_PUDist_2011Full.root"
process.eventWeightPU.CreateWeight3DHisto = False
process.eventWeightPU.Weight3DHistoFile   = "TopAnalysis/TopUtils/data/DefaultWeight3D.root"

#### Configuration for PU Up Variations

process.eventWeightPUsysUp.WeightName          = "eventWeightPUUp"
process.eventWeightPUsysUp.DataFile            = "TopAnalysis/TopUtils/data/Data_PUDist_sysUp_2011Full.root"
process.eventWeightPUsysUp.CreateWeight3DHisto = False
process.eventWeightPUsysUp.Weight3DHistoFile   = "TopAnalysis/TopUtils/data/DefaultWeight3DUp.root"

#### Configuration for PU Down Variations

process.eventWeightPUsysDown.WeightName          = "eventWeightPUDown"
process.eventWeightPUsysDown.DataFile            = "TopAnalysis/TopUtils/data/Data_PUDist_sysDown_2011Full.root"
process.eventWeightPUsysDown.CreateWeight3DHisto = False
process.eventWeightPUsysDown.Weight3DHistoFile   = "TopAnalysis/TopUtils/data/DefaultWeight3DDown.root"

#### Configuration for Nominal PU Weights EPS

process.eventWeightPUEPS.WeightName          = "eventWeightPUEPS"
process.eventWeightPUEPS.DataFile            = "TopAnalysis/TopUtils/data/Data_PUDist_EPS.root"
process.eventWeightPUEPS.CreateWeight3DHisto = False
process.eventWeightPUEPS.Weight3DHistoFile   = "TopAnalysis/TopUtils/data/DefaultWeight3DEPS.root"

### Configuration for Nominal PU Weights B

process.eventWeightPU2011B.WeightName          = "eventWeightPU2011B"
process.eventWeightPU2011B.DataFile            = "TopAnalysis/TopUtils/data/Data_PUDist_2011B.root"
process.eventWeightPU2011B.CreateWeight3DHisto = False
#process.eventWeightPU2011B.Weight3DHistoFile   = "TopAnalysis/TopUtils/data/DefaultWeight3D2011B.root"

### Configuration for Ele32 (effective taking pre scale into account)

process.eventWeightPUEle32.WeightName          = "eventWeightPUEle32"
process.eventWeightPUEle32.DataFile            = "TopAnalysis/TopUtils/data/DataPileupHistogram_Ele32_v1to7.root"
process.eventWeightPUEle32.DataHistoName       = "pileup"
process.eventWeightPUEle32.CreateWeight3DHisto = False
#process.eventWeightPUEle32.Weight3DHistoFile   = "TopAnalysis/TopUtils/data/DefaultWeight3DEle32.root"

### Configuration for Ele32 including Ele32WP70 (effective taking pre scale into account)

process.eventWeightPUEle32WP70.WeightName          = "eventWeightPUEle32WP70"
process.eventWeightPUEle32WP70.DataFile            = "TopAnalysis/TopUtils/data/DataPileupHistogram_Ele32_v1to7_Ele32_WP70_v2to3.root"
process.eventWeightPUEle32WP70.DataHistoName       = "pileup"
process.eventWeightPUEle32WP70.CreateWeight3DHisto = False
#process.eventWeightPUEle32WP70.Weight3DHistoFile   = "TopAnalysis/TopUtils/data/DefaultWeight3DEle32WP70.root"

process.makeEventWeightsPU = cms.Sequence(process.eventWeightPU        *
                                          process.eventWeightPUsysUp   *
                                          process.eventWeightPUsysDown *
                                          process.eventWeightPUEPS     *
                                          process.eventWeightPU2011B   *
                                          process.eventWeightPUEle32   *
                                          process.eventWeightPUEle32WP70)

# relevant PU event weights (potentially merged with shape distortion weights)
PUweightraw     = cms.InputTag("eventWeightPU",       "eventWeightPU")
PUweightrawUp   = cms.InputTag("eventWeightPUsysUp",  "eventWeightPUUp")
PUweightrawDown = cms.InputTag("eventWeightPUsysDown","eventWeightPUDown")
PUweightrawEPS  = cms.InputTag("eventWeightPUEPS",    "eventWeightPUEPS")
PUweightraw2011B= cms.InputTag("eventWeightPU2011B",  "eventWeightPU2011B")
PUweightrawEle32= cms.InputTag("eventWeightPUEle32",  "eventWeightPUEle32")
PUweightrawEle32WP70= cms.InputTag("eventWeightPUEle32WP70",  "eventWeightPUEle32WP70")

## create vector of input tags
PUweights = cms.VInputTag(PUweightraw, PUweightrawUp, PUweightrawDown, PUweightrawEPS, PUweightraw2011B, PUweightrawEle32, PUweightrawEle32WP70)
## standard weight as normal input tag
PUweight = PUweightraw

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

## if desired change mu pt cut
if(muonPtCut>0):
    process.highPtMuons.cut = cms.string('pt > ' + str(muonPtCut))
    process.trackMuons.cut = cms.string('isGlobalMuon & isTrackerMuon &abs(eta) < 2.1 &innerTrack.numberOfValidHits >= 11 &globalTrack.normalizedChi2 < 10.0  &globalTrack.hitPattern.numberOfValidMuonHits>0 &abs(dB)<0.02 &innerTrack.hitPattern.pixelLayersWithMeasurement>=1 &numberOfMatches>1 &pt >' + str(muonPtCut))
print "trackMuonsCut = ", process.trackMuons.cut

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


#########################################################################################

################    M U O N S

#########################################################################################

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
       #process.tagMuonsNoDR = ....
       process.tagMuons = selectedPatMuons.clone(
            src = 'selectedPatMuonsTriggerMatch', 
            cut = 'triggerObjectMatches.size > 0 &'
                  'isGlobalMuon & isTrackerMuon &'
                  'abs(eta) < 2.1 &'
                  'innerTrack.numberOfValidHits >= 11 &'
                  'globalTrack.normalizedChi2 < 10.0  &'
                  'globalTrack.hitPattern.numberOfValidMuonHits>0 &'
                  'abs(dB)<0.02 &'
                  'innerTrack.hitPattern.pixelLayersWithMeasurement>=1 &'
                  'numberOfMatches>1 &'
		  '(chargedHadronIso+neutralHadronIso+photonIso)/pt < 0.125 &'
		  'pt >' + str(muonPtCut)
                  #'(trackIso+caloIso)/pt < 0.05'
       )
       ## jet-muon-distance filter
       #process.tagMuons = cms.EDProducer("MuonJetOverlapSelector",
            ### input muon collection
            #muons = cms.InputTag("tagMuonsNoDR"),
            ### jet collection to check overlap
            #jets = cms.InputTag("selectedJets"),
            ### define overlap region (<deltaR)
            #deltaR = cms.double(0.3),
            ### choose whether you want to
            ### include/exclude overlapping
            ### muons in the created collection
            ### include: overlap = true,
            ### exclude: overlap = false
            #overlap = cms.bool(False)
       #)


       ## do tagging with help of Z resonance
       from TopAnalysis.TopUtils.taggedProbeMuons_cfi import taggedProbeMuons
       process.probeMuons = taggedProbeMuons.clone(
        tags   = "tagMuons",
        probes = "globalMuons",
        mass   =  91,
        deltaM =  deltaM,
	leptonId = leptonTypeId
       )
       #process.produceProbeMuons = cms.Sequence(process.tagMuonsNoDR *process.tagMuons * process.probeMuons)
       process.produceProbeMuons = cms.Sequence(process.tagMuons * process.probeMuons)
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

## probe muons with deltaZ(muonVertex, PV) < 0.5
process.probeMuonsDZ = cms.EDProducer("MuonVertexDistanceSelector",
  src           = cms.InputTag("probeMuons"),
  primaryVertex = cms.InputTag("offlinePrimaryVertices"),
  cutValue      = cms.double(0.5)
)

## probe muons to test track quality on: triggered muons
process.probeMuonsTrkQ = selectedPatMuons.clone(
   src = 'probeMuons',
   cut = ''
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
	 '(chargedHadronIso+neutralHadronIso+photonIso)/pt < 0.125'
         #'(trackIso+caloIso)/pt < 0.05'
)

## probe muons to test total selection: only global & tracker 
process.probeMuonsTotalSelection = selectedPatMuons.clone(
   src = 'probeMuons',
   cut = ''
)

## probe muons to test trigger on: muons passing track quality and isolation selection
# process.probeMuonsTriggerNoDR = ....
process.probeMuonsTrigger = selectedPatMuons.clone(
   src = 'probeMuonsDZ',
   cut = 'innerTrack.numberOfValidHits >= 11 &'
         'globalTrack.normalizedChi2 < 10.0  &'
         'globalTrack.hitPattern.numberOfValidMuonHits>0 &'
         'abs(dB)<0.02 &'
         'innerTrack.hitPattern.pixelLayersWithMeasurement>=1 &'
         'numberOfMatches>1 &'
	 '(chargedHadronIso+neutralHadronIso+photonIso)/pt < 0.125'
         #'(trackIso+caloIso)/pt < 0.05'
)
#process.probeMuonsTrigger = cms.EDProducer("MuonJetOverlapSelector",
  #muons = cms.InputTag("probeMuonsTriggerNoDR"),
  #jets = cms.InputTag("selectedJets"),
  #deltaR = cms.double(0.3),
  #overlap = cms.bool(False)
#)


#-----------------------------------------------------------------------------
# -----Probe Muon -Jet Cleaning (only for ID/Iso T&P)                  ----- #
#-----------------------------------------------------------------------------

## reintroduce jet-muon cleaning between jets and probe muons
process.noOverlapJetsProbeMuons = cleanPatJets.clone( 	 
	  src = cms.InputTag("selectedPatJetsAK5PF"), 	 
	    
	  ## preselection (any string-based cut on pat::Jet) 	 
	  preselection = cms.string(''), 	 
	    
	  ## overlap checking configurables 	 
	  checkOverlaps = cms.PSet( 	 
	      muons = cms.PSet( 	 
		  src       = cms.InputTag("probeMuonsDZ"), 	 
		  algorithm = cms.string("byDeltaR"), 	 
		  preselection        = cms.string('abs(eta) < 2.1 & pt >' + str(muonPtCut)), 	 
		  deltaR              = cms.double(0.1), 	 
		  checkRecoComponents = cms.bool(False), # don't check if they share some AOD object ref 	 
		  pairCut             = cms.string(""), 	 
		  requireNoOverlaps   = cms.bool(True), # overlaps don't cause the jet to be discared 	 
	      ) 	 
	  ), 	 
	  ## finalCut (any string-based cut on pat::Jet) 	 
	  finalCut = cms.string(''), 	 
	)
process.goodJetsPF30NoOverlapJetsProbeMuons     = selectedPatJets.clone(src = 'noOverlapJetsProbeMuons',
					    cut = 'abs(eta) < 2.4 & pt > 30.          &'
						  'chargedHadronEnergyFraction > 0.0  &'
						  'neutralHadronEnergyFraction < 0.99 &'
						  'chargedEmEnergyFraction     < 0.99 &'
						  'neutralEmEnergyFraction     < 0.99 &'
						  'chargedMultiplicity > 0            &'
						  'nConstituents > 1'
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
## deltaZ(muonVertex, PV) < 0.5
process.testMuonsTrkQ = cms.EDProducer("MuonVertexDistanceSelector",
  src           = cms.InputTag("testMuonsTrkQNoDZ"),
  primaryVertex = cms.InputTag("offlinePrimaryVertices"),
  cutValue      = cms.double(0.5)
)

## cut on muon isolation
process.testMuonsIso = selectedPatMuons.clone(
  src = 'probeMuonsIso',
  cut = '(chargedHadronIso+neutralHadronIso+photonIso)/pt < 0.125' 
        #'(trackIso+caloIso)/pt < 0.05'	
)

## cut on jet-muon-distance
process.testMuonsMinDR = cms.EDProducer("MuonJetOverlapSelector",
  muons = cms.InputTag("probeMuonsMinDR"),
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
	'(chargedHadronIso+neutralHadronIso+photonIso)/pt < 0.125'
        #'(trackIso+caloIso)/pt < 0.05'
)
## deltaZ(muonVertex, PV) < 0.5
#process.testMuonsTotalSelectionNoDR = ...
process.testMuonsTotalSelection = cms.EDProducer("MuonVertexDistanceSelector",
  src           = cms.InputTag("testMuonsTotalSelectionNoDZNoDR"),
  primaryVertex = cms.InputTag("offlinePrimaryVertices"),
  cutValue      = cms.double(0.5)
)
#process.testMuonsTotalSelection = cms.EDProducer("MuonJetOverlapSelector",
  #muons = cms.InputTag("testMuonsTotalSelectionNoDR"),
  #jets = cms.InputTag("selectedJets"),
  #deltaR = cms.double(0.3),
  #overlap = cms.bool(False)
#)

## check if probe muons (without further selection) fired trigger
process.testMuonsTrigger = selectedPatMuons.clone(
  src = 'probeMuonsTrigger',
  cut = "triggerObjectMatches.size > 0"
)


#-----------------------------------------------------------------------------
# ----- D o   T a g   A n d   P r o b e   A n a l y s i s ( M U O N S ) ----- #
#-----------------------------------------------------------------------------

from TopAnalysis.TopAnalyzer.TagAndProbeAnalyzer_cfi import tagAndProbeAnalyzer
tagAndProbeAnalyzer.ptCut = muonPtCut
tagAndProbeAnalyzer.deltaM = deltaM

print "muonPtCut in TaP analyzer: ", tagAndProbeAnalyzer.ptCut
print "mass window in TaP analyzer: ", tagAndProbeAnalyzer.deltaM

#process.tapTrkQ = tagAndProbeAnalyzer.clone(
  #probes = "probeMuonsTrkQ", 
  #tests  = "testMuonsTrkQ",
  #jets   = "selectedJets"
#)

#process.tapIso = tagAndProbeAnalyzer.clone(
  #probes = "probeMuonsIso", 
  #tests  = "testMuonsIso",
  #jets   = "selectedJets"
#)

#process.tapMinDR = tagAndProbeAnalyzer.clone(
  #probes = "probeMuonsMinDR", 
  #tests  = "testMuonsMinDR",
  #jets   = "selectedJets"
#)

## take jets which are cleaned from probe muons
process.tapTrkQ = tagAndProbeAnalyzer.clone(
  tags   = "tagMuons",
  probes = "probeMuonsTrkQ", 
  tests  = "testMuonsTrkQ",
  #jets   = "goodJetsPF30NoOverlapJetsProbeMuons"
  jets   = "selectedJets"
  
)

process.tapIso = tagAndProbeAnalyzer.clone(
  tags   = "tagMuons",
  probes = "probeMuonsIso", 
  tests  = "testMuonsIso",
  #jets   = "goodJetsPF30NoOverlapJetsProbeMuons"
  jets   = "selectedJets"
)

process.tapMinDR = tagAndProbeAnalyzer.clone(
  tags   = "tagMuons",
  probes = "probeMuonsMinDR", 
  tests  = "testMuonsMinDR",
  #jets   = "goodJetsPF30NoOverlapJetsProbeMuons"
  jets   = "selectedJets"
)

process.tapTotalSelection = tagAndProbeAnalyzer.clone(
  tags   = "tagMuons",
  probes = "probeMuonsTotalSelection", 
  tests  = "testMuonsTotalSelection",
  #jets   = "goodJetsPF30NoOverlapJetsProbeMuons"
  jets   = "selectedJets"
)

process.tapTrigger = tagAndProbeAnalyzer.clone(
  tags   = "tagMuons",
  probes = "probeMuonsTrigger", 
  tests  = "testMuonsTrigger",
  #jets   = "goodJetsPF30NoOverlapJetsProbeMuons"
  jets   = "selectedJets"
)

## add PU reweighting
if(PUreweighting):
    process.tapTrkQ.weightTags = PUweights
    process.tapIso.weightTags = PUweights
    process.tapMinDR.weightTags = PUweights
    process.tapTotalSelection.weightTags = PUweights
    process.tapTrigger.weightTags = PUweights
    
#-----------------------------------------------------------------------------
# ----- M U O N   S E Q U E N C E----- #
#-----------------------------------------------------------------------------
    
if(leptonTypeId==13):
    process.TaPSequence = cms.Sequence(
	## prepare probe muons
	process.globalMuons        *
	process.produceProbeMuons  *
	process.probeMuonsDZ       *
	process.probeMuonsTrkQ     *
	process.probeMuonsIso      *
	process.probeMuonsMinDR      *
	process.probeMuonsTotalSelection *
	#process.probeMuonsTriggerNoDR  *
	process.probeMuonsTrigger  *
	## do jet-probe muon cleaning
	#process.noOverlapJetsProbeMuons *
	#process.goodJetsPF30NoOverlapJetsProbeMuons *
	## prepare test muons
	process.testMuonsTrkQNoDZ  *
	process.testMuonsTrkQ      *
	process.testMuonsIso       *
	process.testMuonsMinDR     *
	process.testMuonsTotalSelectionNoDZNoDR *
	#process.testMuonsTotalSelectionNoDR *
	process.testMuonsTotalSelection *
	process.testMuonsTrigger   *
	#process.analyzeTestMuonsTrigger *
	## do tag and probe analysis
	process.tapTrkQ            *
	process.tapIso             *
	process.tapMinDR           *
	process.tapTotalSelection  *
	process.tapTrigger
	)

#########################################################################################

################    E L E C T R O N S

#########################################################################################

#-----------------------------------------------------------------------------
# -----   P r o d u c e  P r o b e  E L E C T R O N S ----- #
#-----------------------------------------------------------------------------

## pre-selection on probe electrons (eta cuts)
process.probeElectronsBasis = selectedPatElectrons.clone(src = 'selectedPatMuonsTriggerMatch', 
                                                         cut = 'abs(eta) <  2.1  &'
                                                               '( abs(superCluster.eta) < 1.4442   |'
                                                               '  abs(superCluster.eta) > 1.5660 )  '
                                                         )

## take fully selected electrons as tag electrons
from TopAnalysis.TopFilter.sequences.ElectronVertexDistanceSelector_cfi import *
process.vertexSelectedElectronsTaP = vertexSelectedElectrons.clone(src='selectedPatMuonsTriggerMatch')
process.tightElectronsEJTaP        = process.tightElectronsEJ.clone(src='vertexSelectedElectronsTaP')
process.unconvTightElectronsEJTaP  = process.unconvTightElectronsEJ.clone(src='tightElectronsEJTaP')
process.goodElectronsEJTaP         = process.goodElectronsEJ.clone(src='unconvTightElectronsEJTaP')

## in case of tagAndProbe:
if(modeSelector == 1):
       ## tag electrons (tight selection) according to V4
       process.tagElectrons = selectedPatElectrons.clone(
            src = 'goodElectronsEJTaP', 
	    ## both following options work, check if consistent
            cut = 'triggerObjectMatches.size > 0'
	    #cut = "!triggerObjectMatchesByPath('HLT_Ele27_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_v*', 1, 0).empty()"
	    
       )


       ## do tagging with help of Z resonance
       from TopAnalysis.TopUtils.taggedProbeMuons_cfi import taggedProbeMuons
       process.probeElectrons = taggedProbeMuons.clone(
        tags   = "tagElectrons",
        probes = "probeElectronsBasis",
        mass   =  91,
        deltaM =  deltaM,
	leptonId = leptonTypeId
       )
       process.produceProbeElectrons = cms.Sequence(process.probeElectronsBasis * process.vertexSelectedElectronsTaP * process.tightElectronsEJTaP * process.unconvTightElectronsEJTaP * process.goodElectronsEJTaP *process.tagElectrons * process.probeElectrons)
       print "modeSelector =1"
	
#-----------------------------------------------------------------------------
# ----- Further Selection on  P r o b e  E L E C T R O N S ----- #
#-----------------------------------------------------------------------------

## probe electrons to test track quality on
process.probeElectronsTrkQ = selectedPatElectrons.clone(
   src = 'probeElectrons',
   cut = ''
)

## deltaZ(muonVertex, PV) < 0.5
process.probeElectronsDZ = cms.EDProducer("ElectronVertexDistanceSelector",
  src           = cms.InputTag("probeElectrons"),
  primaryVertex = cms.InputTag("offlinePrimaryVertices"),
  cutValue      = cms.double(0.5)
)

## probe electrons to test eID on: electrons passing track quality
process.probeElectronsID = selectedPatElectrons.clone(
   src = 'probeElectronsDZ',
   cut = 'abs(dB)  <  0.02'
)
## probe electrons to test isolation on: electrons passing track quality & ID
process.probeElectronsIso = selectedPatElectrons.clone(
   src = 'probeElectronsDZ',
   cut = 'abs(dB)  <  0.02 & test_bit( electronID("eidHyperTight1MC"), 0 )'
)
## probe electrons to test conversion rejection on: electrons passing track quality & ID &ISo
process.probeElectronsConvRej = selectedPatElectrons.clone(
   src = 'probeElectronsDZ',
   cut = 'abs(dB)  <  0.02 & test_bit( electronID("eidHyperTight1MC"), 0 ) &'
         '(chargedHadronIso+neutralHadronIso+photonIso)/et < 0.125'
)

## probe electrons to test trigger on: electrons passing track quality, ID, Iso and conv. rej.
process.probeElectronsTrigger = selectedPatElectrons.clone(
   src = 'probeElectrons',
   cut = 'abs(dB)  <  0.02 & test_bit( electronID("eidHyperTight1MC"), 0 ) &'
         '(chargedHadronIso+neutralHadronIso+photonIso)/et < 0.125 &'
	 'gsfTrack.trackerExpectedHitsInner.numberOfHits = 0 &'
         'abs(convDcot) > 0.02 &'
	 'abs(convDist) > 0.02'
)

#-----------------------------------------------------------------------------
# -----Probe Electron -Jet Cleaning (only for ID/Iso T&P)                  ----- #
#-----------------------------------------------------------------------------

## reintroduce jet-electron cleaning between jets and probe electrons
process.noOverlapJetsProbeElectrons = cleanPatJets.clone( 	 
	  src = cms.InputTag("selectedPatJetsAK5PF"), 	 
	    
	  ## preselection (any string-based cut on pat::Jet) 	 
	  preselection = cms.string(''), 	 
	    
	  ## overlap checking configurables 	 
	  checkOverlaps = cms.PSet( 	 
	      muons = cms.PSet( 	 
		  src       = cms.InputTag("probeElectronsDZ"), 	 
		  algorithm = cms.string("byDeltaR"), 	 
		  preselection        = cms.string('abs(eta) < 2.1 & pt >' + str(muonPtCut)), 	 
		  deltaR              = cms.double(0.1), 	 
		  checkRecoComponents = cms.bool(False), # don't check if they share some AOD object ref 	 
		  pairCut             = cms.string(""), 	 
		  requireNoOverlaps   = cms.bool(True), # overlaps don't cause the jet to be discared 	 
	      ) 	 
	  ), 	 
	  ## finalCut (any string-based cut on pat::Jet) 	 
	  finalCut = cms.string(''), 	 
	)
process.goodJetsPF30NoOverlapJetsProbeElectrons     = selectedPatJets.clone(src = 'noOverlapJetsProbeElectrons',
						cut = 'abs(eta) < 2.4 & pt > 30.          &'
						      'chargedHadronEnergyFraction > 0.0  &'
						      'neutralHadronEnergyFraction < 0.99 &'
						      'chargedEmEnergyFraction     < 0.99 &'
						      'neutralEmEnergyFraction     < 0.99 &'
						      'chargedMultiplicity > 0            &'
						      'nConstituents > 1'
						)

#-----------------------------------------------------------------------------
# ----- P r e p a r e   T e s t   C o l l e c t i o n  ( C u t s ) ----- #
#-----------------------------------------------------------------------------

## cut on track quality
## deltaZ(muonVertex, PV) < 0.5
process.testElectronsDZ = cms.EDProducer("ElectronVertexDistanceSelector",
  src           = cms.InputTag("probeElectrons"),
  primaryVertex = cms.InputTag("offlinePrimaryVertices"),
  cutValue      = cms.double(0.5)
)
process.testElectronsTrkQ = selectedPatElectrons.clone(
   src = 'testElectronsDZ',
   cut = 'abs(dB)  <  0.02'
)

## cut on eID
process.testElectronsID = selectedPatElectrons.clone(
   src = 'probeElectronsID',
   cut = 'test_bit( electronID("eidHyperTight1MC"), 0 )'
)

## cut on isolation
process.testElectronsIso = selectedPatElectrons.clone(
   src = 'probeElectronsIso',
   cut = '(chargedHadronIso+neutralHadronIso+photonIso)/et < 0.125'
)

## conversion rejection
process.testElectronsConvRej = selectedPatElectrons.clone(
   src = 'probeElectronsConvRej',
   cut = 'gsfTrack.trackerExpectedHitsInner.numberOfHits = 0 &'
         'abs(convDcot) > 0.02 &'
	 'abs(convDist) > 0.02'
)

## total selection: same as ConvRej

## check if probe electrons (without further selection) fired trigger
process.testElectronsTrigger = selectedPatElectrons.clone(
  src = 'probeElectronsTrigger',
  cut = "triggerObjectMatches.size > 0"
)


#-----------------------------------------------------------------------------
# ----- D o   T a g   A n d   P r o b e   A n a l y s i s ----- #
#-----------------------------------------------------------------------------

from TopAnalysis.TopAnalyzer.TagAndProbeAnalyzer_cfi import tagAndProbeAnalyzer
tagAndProbeAnalyzer.deltaM = deltaM

print "muonPtCut in TaP analyzer: ", tagAndProbeAnalyzer.ptCut
print "mass window in TaP analyzer: ", tagAndProbeAnalyzer.deltaM

process.tapTrkQEle = tagAndProbeAnalyzer.clone(
  tags   = "tagElectrons",
  probes = "probeElectronsTrkQ", 
  tests  = "testElectronsTrkQ",
  #jets   = "goodJetsPF30NoOverlapJetsProbeElectrons"
  jets   = "selectedJets"
  
  )
  
process.tapIDEle = tagAndProbeAnalyzer.clone(
  tags   = "tagElectrons",
  probes = "probeElectronsID", 
  tests  = "testElectronsID",
  #jets   = "goodJetsPF30NoOverlapJetsProbeElectrons"
  jets   = "selectedJets"
  )
  
process.tapIsoEle = tagAndProbeAnalyzer.clone(
  tags   = "tagElectrons",
  probes = "probeElectronsIso", 
  tests  = "testElectronsIso",
  #jets   = "goodJetsPF30NoOverlapJetsProbeElectrons"
  jets   = "selectedJets"
  )

process.tapConvRejEle = tagAndProbeAnalyzer.clone(
  tags   = "tagElectrons",
  probes = "probeElectronsConvRej", 
  tests  = "testElectronsConvRej",
  #jets   = "goodJetsPF30NoOverlapJetsProbeElectrons"
  jets   = "selectedJets"
  )
  
process.tapTotalSelectionEle = tagAndProbeAnalyzer.clone(
  tags   = "tagElectrons",
  probes = "probeElectronsTrkQ", 
  tests  = "testElectronsConvRej",
  #jets   = "goodJetsPF30NoOverlapJetsProbeElectrons"
  jets   = "selectedJets"
  )

process.tapTriggerEle = tagAndProbeAnalyzer.clone(
  tags   = "tagElectrons",
  probes = "probeElectronsTrigger", 
  tests  = "testElectronsTrigger",
  jets   = "selectedJets"
  )
  
## add PU reweighting
if(PUreweighting):
    process.tapTrkQEle.weightTags           = PUweights
    process.tapIDEle.weightTags             = PUweights
    process.tapIsoEle.weightTags            = PUweights
    process.tapConvRejEle.weightTags        = PUweights
    process.tapTotalSelectionEle.weightTags = PUweights
    process.tapTriggerEle.weightTags        = PUweights
  
  
#-----------------------------------------------------------------------------
# ----- E L E C T R O N   S E Q U E N C E----- #
#-----------------------------------------------------------------------------
    
if(leptonTypeId==11):
    process.TaPSequence = cms.Sequence(
	## prepare probe electrons
	process.produceProbeElectrons  *
	process.probeElectronsTrkQ *
	process.probeElectronsDZ *
	process.probeElectronsID *
	process.probeElectronsIso *
	process.probeElectronsConvRej *
	process.probeElectronsTrigger *
	## jet cleaning
	#process.noOverlapJetsProbeElectrons *
        #process.goodJetsPF30NoOverlapJetsProbeElectrons *
	## prepare test electrons
	process.testElectronsDZ *
	process.testElectronsTrkQ *
	process.testElectronsID *
	process.testElectronsIso *
	process.testElectronsConvRej *
	process.testElectronsTrigger   *
	#process.analyzeTestElectronsTrigger *
	## do tag and probe analysis
	process.tapTrkQEle *
	process.tapIDEle *
	process.tapIsoEle *
	process.tapConvRejEle *
	process.tapTotalSelectionEle *
	process.tapTriggerEle
    )


#########################################################################################

################    Efficiency Studies using Single Muon Trigger as Control Trigger

#########################################################################################


if(triggerPathSelector2 == ""):
    print "Only T&P for ", triggerPathSelector, ", no efficiency studies for a second trigger done."
    ## dummy process - ignore!!!
    process.effStudies2 = cms.Sequence(process.hltTriggerFilter)
else:
    print "Additional efficiency studies for", triggerPathSelector2, "; ", triggerPathSelector, "as control trigger."
    process.leadingJetSelectionNjets = process.leadingJetSelection.clone (src = 'tightLeadingPFJets', minNumber = jetMinNumber2)
    #leptonTypeId = 13
    noLeptonVetoes = False
    
    ## second HLT trigger filter
    process.hltTriggerFilter2 = hltHighLevel.clone(HLTPaths = [triggerPathSelector2], throw=False)
    
    ## jet kinematics analyzer
    process.load("TopAnalysis.TopAnalyzer.JetKinematicsVertex_cfi")
    ## add PU reweighting
    if(PUreweighting):
        process.analyzeJetKinematicsVertex.weight = PUweight
    ## define ordered jets
    ## ATTENTION!!! For MC it should be 'L3Absolute' !!!!
    corrLevel=''
    if(dataSelector == 1):
	corrLevel='L3Absolute'
    elif(dataSelector == 11):
	corrLevel='L2L3Residual'
    #corrLevel='L2L3Residual'
    uds0    = cms.PSet(index = cms.int32(0),  correctionLevel = cms.string(corrLevel), useTree = cms.bool(False) )
    uds1    = cms.PSet(index = cms.int32(1),  correctionLevel = cms.string(corrLevel), useTree = cms.bool(False) )
    uds2    = cms.PSet(index = cms.int32(2),  correctionLevel = cms.string(corrLevel), useTree = cms.bool(False) )
    uds3    = cms.PSet(index = cms.int32(3),  correctionLevel = cms.string(corrLevel), useTree = cms.bool(False) )
    udsAll  = cms.PSet(index = cms.int32(-1), correctionLevel = cms.string(corrLevel), useTree = cms.bool(True) )
    #uds0    = cms.PSet(index = cms.int32(0),  correctionLevel = cms.string(corrLevel), useTree = cms.bool(False) )
    #uds1    = cms.PSet(index = cms.int32(1),  correctionLevel = cms.string(corrLevel), useTree = cms.bool(False) )
    #uds2    = cms.PSet(index = cms.int32(2),  correctionLevel = cms.string(corrLevel), useTree = cms.bool(False) )
    #uds3    = cms.PSet(index = cms.int32(3),  correctionLevel = cms.string(corrLevel), useTree = cms.bool(False) )
    #udsAll  = cms.PSet(index = cms.int32(-1), correctionLevel = cms.string(corrLevel), useTree = cms.bool(False) )
    ##  Jet Kinematics Analyzer for the first 4 and all jets, for events fired by trigger 1 before the jet cut
    process.analyzeJet0Trig1BeforeCut  = process.analyzeJetKinematicsVertex.clone (srcA = 'tightLeadingPFJets', analyze = uds0 )
    process.analyzeJet1Trig1BeforeCut  = process.analyzeJetKinematicsVertex.clone (srcA = 'tightLeadingPFJets', analyze = uds1 )
    process.analyzeJet2Trig1BeforeCut  = process.analyzeJetKinematicsVertex.clone (srcA = 'tightLeadingPFJets', analyze = uds2 )
    process.analyzeJet3Trig1BeforeCut  = process.analyzeJetKinematicsVertex.clone (srcA = 'tightLeadingPFJets', analyze = uds3 )
    process.analyzeJetAllTrig1BeforeCut= process.analyzeJetKinematicsVertex.clone (srcA = 'tightLeadingPFJets', analyze = udsAll)
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
    
    ## lepton analyzers after trigger 1 and trigger 2
    process.load("TopAnalysis.TopAnalyzer.MuonKinematics_cfi")
    if(PUreweighting):
        process.analyzeMuonKinematics.weight = PUweight
    process.analyzeMuonKinematicsTrig1 = process.analyzeMuonKinematics.clone(src="tightMuons");
    process.analyzeMuonKinematicsTrig2 = process.analyzeMuonKinematics.clone(src="tightMuons");
    process.load("TopAnalysis.TopAnalyzer.MuonQuality_cfi")
    if(PUreweighting):
        process.analyzeMuonQuality.weight = PUweight
    process.analyzeMuonQualityTrig1 = process.analyzeMuonQuality.clone(src="tightMuons");
    process.analyzeMuonQualityTrig2 = process.analyzeMuonQuality.clone(src="tightMuons");
    process.load("TopAnalysis.TopAnalyzer.ElectronKinematics_cfi")
    if(PUreweighting):
        process.analyzeElectronKinematics.weight = PUweight
    process.analyzeElectronKinematicsTrig1 = process.analyzeElectronKinematics.clone(src="tightElectronsEJ");
    process.analyzeElectronKinematicsTrig2 = process.analyzeElectronKinematics.clone(src="tightElectronsEJ");
    process.load("TopAnalysis.TopAnalyzer.ElectronQuality_cfi")
    if(PUreweighting):
        process.analyzeElectronQuality.weight = PUweight
    process.analyzeElectronQualityTrig1 = process.analyzeElectronQuality.clone(src="tightElectronsEJ");
    process.analyzeElectronQualityTrig2 = process.analyzeElectronQuality.clone(src="tightElectronsEJ");
    
    if(leptonTypeId==13):
	process.leptonAnalyzersTrig1 = cms.Sequence(process.analyzeMuonKinematicsTrig1
						    * process.analyzeMuonQualityTrig1)
	process.leptonAnalyzersTrig2 = cms.Sequence(process.analyzeMuonKinematicsTrig2
						    * process.analyzeMuonQualityTrig2)
    elif(leptonTypeId==11):
	process.leptonAnalyzersTrig1 = cms.Sequence(process.analyzeElectronKinematicsTrig1
						    * process.analyzeElectronQualityTrig1)
	process.leptonAnalyzersTrig2 = cms.Sequence(process.analyzeElectronKinematicsTrig2
						    * process.analyzeElectronQualityTrig2)
    ## ---
    ##    Set up selection steps for muon selection
    ## ---
    process.combinedMuonsSelection        = process.muonSelection.clone (src = 'combinedMuons'       , minNumber = 1, maxNumber = 99999999)
    process.kinematicMuonsSelection       = process.muonSelection.clone (src = 'kinematicMuons'      , minNumber = 1, maxNumber = 99999999)
    process.trackMuonsSelection           = process.muonSelection.clone (src = 'trackMuons'          , minNumber = 1, maxNumber = 99999999)
    process.highPtMuonsSelection          = process.muonSelection.clone (src = 'highPtMuons'         , minNumber = 1, maxNumber = 99999999)
    process.goldenMuonsSelection          = process.muonSelection.clone (src = 'goldenMuons'         , minNumber = 1, maxNumber = 99999999)
    process.tightMuonsSelection           = process.muonSelection.clone (src = 'tightMuons'          , minNumber = 1, maxNumber = 99999999)
    
    process.muonCuts = cms.Sequence(process.combinedMuonsSelection        +
				    process.highPtMuonsSelection          +
				    process.kinematicMuonsSelection       +
				    process.trackMuonsSelection           +
				    process.goldenMuonsSelection          +
				    process.tightMuonsSelection           +
				    process.muonSelection
				    )
    
    if (leptonTypeId == 13):
	process.leptonSelection          = cms.Sequence( process.muonCuts     *
					      process.electronVeto           *
					      process.secondMuonVeto
					    )
	if(noLeptonVetoes):
	    process.leptonSelection.remove(process.electronVeto)
	    process.leptonSelection.remove(process.secondMuonVeto)
    elif (leptonTypeId == 11):
	process.leptonSelection          = cms.Sequence( process.tightElectronSelection *
					      process.muonVeto               *
					      process.secondElectronVeto     *
					      process.convElecHitRejection   *
					      process.convElecTrkRejection 
					    )
	if(noLeptonVetoes):
	    process.leptonSelection.remove(process.secondElectronVeto)
	    process.leptonSelection.remove(process.muonVeto)
    
    process.effStudies2 = cms.Sequence(
    
       ## lepton selection
       process.leptonSelection                       *
       ## jet kinematics analyzer for events fired by trigger 1 before the jet cut
       process.analyzeJet0Trig1BeforeCut             *
       process.analyzeJet1Trig1BeforeCut             *
       process.analyzeJet2Trig1BeforeCut             *
       process.analyzeJet3Trig1BeforeCut             *
       #process.analyzeJetAllTrig1BeforeCut           *
       ## jet selection
       process.leadingJetSelectionNjets              *
       ## jet kinematics analyzer for events fired by trigger 1 after the jet cut
       process.analyzeJet0Trig1AfterCut              *
       process.analyzeJet1Trig1AfterCut              *
       process.analyzeJet2Trig1AfterCut              *
       process.analyzeJet3Trig1AfterCut              *
       process.analyzeJetAllTrig1AfterCut            *
       ## lepton analyzers
       process.leptonAnalyzersTrig1                  *
       ## HLT trigger filter: 2nd trigger
       process.hltTriggerFilter2                     *
       ## jet kinematics analyzer for events fired by trigger 1 after the jet cut
       process.analyzeJet0Trig2AfterCut              *
       process.analyzeJet1Trig2AfterCut              *
       process.analyzeJet2Trig2AfterCut              *
       process.analyzeJet3Trig2AfterCut              *
       process.analyzeJetAllTrig2AfterCut            *
       ## lepton analyzers
       process.leptonAnalyzersTrig2                 
    )


#-----------------------------------------------------------------------------
# ----- H e l p e r   A n a l y z e r s ----- #
#-----------------------------------------------------------------------------

## create triggerMatchedMuons
process.triggerMatchedPatLeptons = selectedPatMuons.clone(
  src = "selectedPatMuonsTriggerMatch",
  cut = "triggerObjectMatches.size > 0"
)

## look at kinematics of all reconstructed muons (i.e. use it before trigger is applied)
process.analyzeAllPatMuons=analyzeMuonKinematics.clone(
  src = "selectedPatMuons",
  analyze = cms.PSet(useTree  = cms.bool(False), index = cms.int32(-1))
)

## analyze dimuon mass
process.analyzeAllPatMuonsMass = analyzeMuonPair.clone(
   muons = "selectedPatMuons"
)

## look at kinematics of reconstructed muons after HLT_mu9 trigger (i.e. use it after trigger is applied)
process.analyzePostTriggerPatMuons=analyzeMuonKinematics.clone(
  src = "selectedPatMuons",
  analyze = cms.PSet(useTree  = cms.bool(False), index = cms.int32(-1))
)

## look at quality of reconstructed muons after HLT_mu9 trigger (i.e. use it after trigger is applied)
process.analyzePostTriggerPatMuonsQuality=analyzeMuonQuality.clone(
  src = "selectedPatMuons",
  analyze = cms.PSet(useTree  = cms.bool(False), index = cms.int32(-1))
)

## look at kinematics of muons which fired HLT_Mu9 (i.e. trigger matched muons)
process.analyzetriggerMatchedPatLeptons=analyzeMuonKinematics.clone(
  src = "triggerMatchedPatLeptons",
  analyze = cms.PSet(useTree  = cms.bool(False), index = cms.int32(-1))
)

## look at kinematics of test muons which fired HLT_Mu9
process.analyzeTestMuonsTrigger=analyzeMuonKinematics.clone(
  src = "testMuonsTrigger",
  analyze = cms.PSet(useTree  = cms.bool(False), index = cms.int32(-1))
)

## ----------------------------------------------------------------------------
##    run the final sequence
##-----------------------------------------------------------------------------

process.p1 = cms.Path(
    #process.analyzeAllPatMuons     *
    #process.analyzeAllPatMuonsMass *
    ## apply primary vertex selection
    process.PVSelection                *
    ## calculate PU weights
    process.makeEventWeightsPU         *
    ## apply trigger selection
    process.hltTriggerFilter           *
    #process.analyzePostTriggerPatMuons *
    #process.analyzePostTriggerPatMuonsQuality *
    ## prepare trigger matching
    process.patTriggerSequenceUser     *
    #process.triggerMatchedPatLeptons *
    #process.analyzetriggerMatchedPatLeptons*
    ## introduce some collections
    process.semiLeptonicSelection        *
    ## prepare jet collection
    process.selectedJetsSequence *
    process.jetMultCut         *
    ## TaP sequence
    process.TaPSequence        *
    ## efficiency studies using Single Muon Trigger as Control Trigger
    process.effStudies2
)

if(not PUreweighting):
    process.p1.remove(process.makeEventWeightsPU)

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

# switch to PF2PAT
if(pfToPAT):
    #from PhysicsTools.PatAlgos.producersLayer1.muonProducer_cfi import *
    #patMuons.pfMuonSource = cms.InputTag("pfAllMuons") # ODER cms.InputTag("pfMuonsFromVertex")
    from TopAnalysis.TopUtils.usePatTupleWithParticleFlow_cff import prependPF2PATSequence
    allpaths  = process.paths_().keys()
    recoPaths=['p1']
    # define general options
    options = {
        'runOnMC': True,
        'runOnAOD': True,
        'switchOffEmbedding': False,
        'addResolutions': True,
	'resolutionsVersion': 'summer11',
        'runOnOLDcfg': True,
        'cutsMuon': 'pt > 10. & abs(eta) < 2.5',
        'cutsElec': 'et > 15. & abs(eta) < 2.5',
        'cutsJets': 'pt > 10 & abs(eta) < 5.0', 
        'electronIDs': ['CiC','classical'],
        'pfIsoConeMuon': 0.4,
        'pfIsoConeElec': 0.4,
        'pfIsoValMuon': 0.2,
        'pfIsoValElec': 0.2,
        'skipIfNoPFMuon': False,
        'skipIfNoPFElec': False,
        'addNoCutPFMuon': False,
        'addNoCutPFElec': False,
        'noMuonTopProjection': False,
        'noElecTopProjection': False,
        'analyzersBeforeMuonIso':cms.Sequence(),
        'excludeElectronsFromWsFromGenJets': True
        }
    # adaptions when running on data
    if(dataSelector == 11):
        options['runOnMC']=False
    options['runOnAOD']=runOnAOD
    ## introduce possibility to change relIso threshold for top projection
    if(relIsoTopProj > 0):
	options['pfIsoValMuon'  ] = relIsoTopProj
	options['pfIsoValElec'  ] = relIsoTopProj
    if(leptonTypeId==11):
    # take into account different electron vetos in mu and e channel
        options['cutsElec'    ] = 'et > 20. & abs(eta) < 2.5'
	if(PF2PATwithoutLeptonIsoCut):
	    ## change the source of the PAT leptons to nonIso leptons to be able to do isolation studies
	    #process.load("PhysicsTools.PatAlgos.producersLayer1.electronProducer_cfi")
            #process.patElectrons.pfElectronSource = cms.InputTag("pfSelectedElectrons")
	    options['addNoCutPFElec']=True
	else:
	    options['skipIfNoPFElec']=True
    elif(leptonTypeId==13):
	if(PF2PATwithoutLeptonIsoCut):
	    ## change the source of the PAT leptons to nonIso leptons to be able to do isolation studies
	    #process.load("PhysicsTools.PatAlgos.producersLayer1.muonProducer_cfi")
            #process.patMuons.pfMuonSource = cms.InputTag("pfSelectedMuons")
	    options['addNoCutPFMuon']=True 
	else:
	    options['skipIfNoPFMuon']=True 
    prependPF2PATSequence(process, recoPaths, options)
    ## change the source of the PAT leptons to nonIso leptons to be able to do isolation studies
    if(PF2PATwithoutLeptonIsoCut):
        if(leptonTypeId==11):
	    process.selectedPatElectrons.src="noCutPatElectrons"
	    #process.p1.remove(process.electronMatch)
	    #process.p1.remove(process.patElectrons)
	    #if(dataSelector == 1):
            #    process.p1.replace(process.pfIsolatedElectrons, process.electronMatch*process.patElectrons*process.pfIsolatedElectrons)
	    #else:
	    #    process.p1.replace(process.pfIsolatedElectrons, process.patElectrons*process.pfIsolatedElectrons)
		  
        elif(leptonTypeId==13):
	    process.selectedPatMuons.src="noCutPatMuons"
	    #process.p1.remove(process.muonMatch)
            #process.p1.remove(process.patMuons)
	    #if(dataSelector == 1):
            #    process.p1.replace(process.pfIsolatedMuons, process.muonMatch*process.patMuons*process.pfIsolatedMuons)
	    #else:
	    #    process.p1.replace(process.pfIsolatedMuons, process.patMuons*process.pfIsolatedMuons)
    
    # remove electron collections as long as id does not exist in the tuples
    for path in recoPaths:
        #getattr(process,path).remove( process.looseElectronsEJ )
        #getattr(process,path).remove( process.tightElectronsEJ )
        #getattr(process,path).remove( process.unconvTightElectronsEJ )
        #getattr(process,path).remove( process.goodElectronsEJ )
        # replace object consistently with names from PF2PAT
        #massSearchReplaceAnyInputTag(getattr(process,path), 'patMETsPF', 'patMETs')
        #massSearchReplaceAnyInputTag(getattr(process,path), 'selectedPatJetsAK5PF', 'selectedPatJets')        
        # run trigger at the beginning to save a lot of time
        getattr(process,path).insert(0,process.hltTriggerFilter)
    