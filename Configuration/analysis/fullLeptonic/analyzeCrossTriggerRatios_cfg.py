import FWCore.ParameterSet.Config as cms
from PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi import *

process = cms.Process("CrossTriggerRatios")
## lepton Id for efficiency studies: 11 for electron, 13 for muon
if(not globals().has_key("leptonTypeId")):
	leptonTypeId = 13
## switch dataSelector to 1 for MC Spring2010, 2 for Fall10 MC, 3 for Spring11, to 11 for Run2010 data (GR_R_38X_V13), to 12 for Run2010 (old RECO, GR_R_36X_V12), to 13 for Run2011A
if(not globals().has_key("dataSelector")):
	dataSelector = 1
## select triggerPath of single muon trigger (HLT_Mu9, HLT_Mu15_v1, ...)
if(not globals().has_key("triggerPathSelector1")):
	triggerPathSelector1 = "HLT_Ele25_CaloIdVT_TrkIdT_CentralJet30_v*"
##
if(not globals().has_key("triggerPathSelector2")):
	triggerPathSelector2 = "HLT_Ele25_CaloIdVT_TrkIdT_CentralTriJet30_v*"
## optionally filter on l3 filter of HLT path
if(not globals().has_key("l3FilterSelector")):
	l3FilterSelector = ""
## switch between efficiency and cutflow studies (for purity)
if(not globals().has_key("cutflowSelector")):
	cutflowSelector = "effOnly" # cutflowOnly, effAndCutflow, analyzeAfterCut
## select processName of trigger, e.g. "HLT" for data, "REDIGIXXX" for some MC
if(not globals().has_key("triggerProcessName")):
	triggerProcessName = "HLT"
## option to cut L3 trigger object on a new (higher) pTthreshold (default: -1, i.e. switched off)
if(not globals().has_key("triggerPtThresholdNew")):
	triggerPtThresholdNew = -1
## select cut on jet multiplicity
if(not globals().has_key("jetMinNumber")):
	jetMinNumber = 4
## select cut on jet multiplicity
if(not globals().has_key("jetMaxNumber")):
	jetMaxNumber = 999999
## select jet type (any for calo, "PF" for particle flow
if(not globals().has_key("jetType")):
	jetType = "PF"
## minimum jet pt of first jet
if(not globals().has_key("jetMinPt1")):
	jetMinPt1 = '30'
## minimum jet pt of 2nd jet
if(not globals().has_key("jetMinPt2")):
	jetMinPt2 = '30'
## run PF2PAT?
## only possible for special pat tuples!!!
if(not globals().has_key('pfToPAT')):
    pfToPAT = True #False
print "run PF2PAT?: ",pfToPAT," won't work if the file does not contain the necessary information!"
## select whether to run directly on AOD
if(not globals().has_key("runOnAOD")):
	runOnAOD = True
if(not globals().has_key("PF2PATwithoutLeptonIsoCut")):
	PF2PATwithoutLeptonIsoCut = False
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

## choose JSON file for data
if(not globals().has_key('noLeptonVetoes')):
    noLeptonVetoes =  'False'

print "----------------------------------------------"
print "Efficiency Studies for Lepton ID (11 electron, 13 muon): ", leptonTypeId
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
    fileName = cms.string('analyzeTriggerRatio.root')
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
				   
#----------------------------------------------------------------------------
#    Trigger configuration
#----------------------------------------------------------------------------
## trigger sequences
process.load( "PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cff" )
				
process.patTriggerSequenceUser = cms.Sequence(
      process.patTrigger *
      process.patTriggerEvent
    )
    
    
#-----------------------------------------------------------------------------
# ----- MC PU reweighting                                         ----- #
#-----------------------------------------------------------------------------

process.load("TopAnalysis.TopUtils.EventWeightPU_cfi")

## Apply common setting before module is cloned for systematic studies

process.eventWeightPU.MCSampleTag = "Fall11"

process.eventWeightPU.MCSampleHistoName        = "histo_Fall11_true"
process.eventWeightPU.DataHistoName            = "histoData_true"

process.eventWeightPU        = process.eventWeightPU.clone()
process.eventWeightPUsysUp   = process.eventWeightPU.clone()
process.eventWeightPUsysDown = process.eventWeightPU.clone()
process.eventWeightPUEPS     = process.eventWeightPU.clone()

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

process.makeEventWeightsPU = cms.Sequence(process.eventWeightPU        *
                                          process.eventWeightPUsysUp   *
                                          process.eventWeightPUsysDown *
                                          process.eventWeightPUEPS  )

# relevant PU event weights (potentially merged with shape distortion weights)
PUweightraw     = cms.InputTag("eventWeightPU",       "eventWeightPU")
PUweightrawUp   = cms.InputTag("eventWeightPUsysUp",  "eventWeightPUUp")
PUweightrawDown = cms.InputTag("eventWeightPUsysDown","eventWeightPUDown")
PUweightrawEPS  = cms.InputTag("eventWeightPUEPS",    "eventWeightPUEPS")

## create vector of input tags
PUweights = cms.VInputTag(PUweightraw, PUweightrawUp, PUweightrawDown, PUweightrawEPS)
## standard weight as normal input tag
PUweight = PUweightraw


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
process.hltTriggerFilter1 = hltHighLevel.clone(TriggerResultsTag = triggerResultsTagString, HLTPaths = [triggerPathSelector1], throw=False)
process.hltTriggerFilter2 = hltHighLevel.clone(TriggerResultsTag = triggerResultsTagString, HLTPaths = [triggerPathSelector2], throw=False)

## optionally filter on L3 filter of HLTPath
from TopAnalysis.TopFilter.filters.TriggerFilterFilter_cfi import filterTriggerFilters
process.hltL3Filter = filterTriggerFilters.clone()
process.hltL3Filter.hltFilter= l3FilterSelector

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
# ----- C o n f i g u r e   P A T   T r i g g e r  M a t c h i n g (optional)----- #
#-----------------------------------------------------------------------------
#######################################
## so far only used for test purposes!!!!!!!! switch only to True if you know what you do!!
#######################################
useTriggerMatching = False

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
if(l3FilterSelector == ""):
    ## in path (after triggerPathSelector): first number stands for lastFilterAccepted, the second
    ## number for L3FilterAccepted
    #matchedCutsString=' path( "'+triggerPathSelector+'",1,0 )'
    matchedCutsString=''
else:
    #matchedCutsString=' path( "'+triggerPathSelector+'" ,0) && filter( "'+l3FilterSelector+'" )'
    matchedCutsString=' filter( "'+l3FilterSelector+'" )'
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
    
if(useTriggerMatching):
    ## configure patTrigger & patTriggerEvent
    process.patTriggerEvent.patTriggerMatches = [ "muonTriggerMatchHLTMuons" ]
    process.patTriggerSequenceUser = cms.Sequence(
	  process.patTrigger *
	  process.muonTriggerMatchHLTMuons *
	  process.patTriggerEvent *
	  process.selectedPatMuonsTriggerMatch
	  #process.analyzePostTriggerLeadPatMuons
	)
    ## use this filter to study trigger efficiency with the help of trigger matching
    #process.goodElectronsEJTriggerMatch  = process.selectedPatElectrons.clone(src = "selectedPatMuonsTriggerMatch", cut = 'triggerObjectMatches.size > 0')
    process.onlyTriggerMatchedLeptons    = process.selectedPatElectrons.clone(src = "selectedPatMuonsTriggerMatch", cut = 'triggerObjectMatches.size > 0')
    process.hltL3FilterByTriggerMatching = process.countPatElectrons.clone   ( src = 'onlyTriggerMatchedLeptons'     , minNumber = 1, maxNumber = 1 )


#-----------------------------------------------------------------------------
# ----- Efficiency Studies  ----- #
#-----------------------------------------------------------------------------

## jet kinematics analyzer
process.load("TopAnalysis.TopAnalyzer.JetKinematicsVertex_cfi")
#process.load("TopAnalysis.TopAnalyzer.JetKinematicsDifferentMultiplicities_cfi")

if(PUreweighting):
        process.analyzeJetKinematicsVertex.weight = PUweight
	process.analyzeJetKinematicsVertex.weights = PUweights
	#process.analyzeJetKinematicsDifferentMultiplicities.weight = PUweight
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
#process.analyzeJetDiffMultTrig1BeforeCut  = process.analyzeJetKinematicsDifferentMultiplicities.clone (src = 'tightLeadingPFJets')
##  Jet Kinematics Analyzer for the first 4 and all jets, for events fired by trigger 1 after the jet cut 
process.analyzeJet0Trig1AfterCut  = process.analyzeJet0Trig1BeforeCut.clone() 
process.analyzeJet1Trig1AfterCut  = process.analyzeJet1Trig1BeforeCut.clone()
process.analyzeJet2Trig1AfterCut  = process.analyzeJet2Trig1BeforeCut.clone()
process.analyzeJet3Trig1AfterCut  = process.analyzeJet3Trig1BeforeCut.clone()
process.analyzeJetAllTrig1AfterCut= process.analyzeJetAllTrig1BeforeCut.clone()
#process.analyzeJetDiffMultTrig1AfterCut  = process.analyzeJetKinematicsDifferentMultiplicities.clone (src = 'tightLeadingPFJets')
##  Jet Kinematics Analyzer for the first 4 and all jets, for events fired by trigger 2 after the jet cut
process.analyzeJet0Trig2AfterCut  = process.analyzeJet0Trig1BeforeCut.clone()
process.analyzeJet1Trig2AfterCut  = process.analyzeJet1Trig1BeforeCut.clone()
process.analyzeJet2Trig2AfterCut  = process.analyzeJet2Trig1BeforeCut.clone()
process.analyzeJet3Trig2AfterCut  = process.analyzeJet3Trig1BeforeCut.clone()
process.analyzeJetAllTrig2AfterCut= process.analyzeJetAllTrig1BeforeCut.clone()
#process.analyzeJetDiffMultTrig2AfterCut  = process.analyzeJetKinematicsDifferentMultiplicities.clone (src = 'tightLeadingPFJets')

## lepton analyzers after trigger 1 and trigger 2
process.load("TopAnalysis.TopAnalyzer.MuonKinematics_cfi")
if(PUreweighting):
        process.analyzeMuonKinematics.weight  = PUweight
	process.analyzeMuonKinematics.weights = PUweights
process.analyzeMuonKinematicsTrig1 = process.analyzeMuonKinematics.clone(src="tightMuons");
process.analyzeMuonKinematicsTrig1.analyze=cms.PSet(index = cms.int32(0), useTree = cms.bool(True) )
process.analyzeMuonKinematicsTrig2 = process.analyzeMuonKinematics.clone(src="tightMuons");
process.analyzeMuonKinematicsTrig2.analyze=cms.PSet(index = cms.int32(0), useTree = cms.bool(True) )
process.load("TopAnalysis.TopAnalyzer.MuonQuality_cfi")
if(PUreweighting):
        process.analyzeMuonQuality.weight = PUweight
	process.analyzeMuonQuality.weights = PUweights
process.analyzeMuonQualityTrig1 = process.analyzeMuonQuality.clone(src="tightMuons");
process.analyzeMuonQualityTrig2 = process.analyzeMuonQuality.clone(src="tightMuons");
process.load("TopAnalysis.TopAnalyzer.ElectronKinematics_cfi")
if(PUreweighting):
        process.analyzeElectronKinematics.weight = PUweight
	process.analyzeElectronKinematics.weights = PUweights
process.analyzeElectronKinematicsTrig1 = process.analyzeElectronKinematics.clone(src="tightElectronsEJ")
process.analyzeElectronKinematicsTrig1.analyze=cms.PSet(index = cms.int32(0), useTree = cms.bool(True) )
process.analyzeElectronKinematicsTrig2 = process.analyzeElectronKinematics.clone(src="tightElectronsEJ")
process.analyzeElectronKinematicsTrig2.analyze=cms.PSet(index = cms.int32(0), useTree = cms.bool(True) )
process.load("TopAnalysis.TopAnalyzer.ElectronQuality_cfi")
if(PUreweighting):
        process.analyzeElectronQuality.weight = PUweight
        process.analyzeElectronQuality.weights = PUweights
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

## ---
##    Set up selection steps for different jet multiplicities
## ---
## new pt cuts on jet 1 and 2
process.tightLeadingPFJetsMinPt1 = process.tightLeadingPFJets.clone( cut = 'pt >'+ jetMinPt1 )
process.tightLeadingPFJetsMinPt2 = process.tightLeadingPFJets.clone( cut = 'pt >'+ jetMinPt2 )
process.leadingJetSelectionNjets1Pt1 = process.leadingJetSelection.clone (src = 'tightLeadingPFJetsMinPt1', minNumber = 1, maxNumber = jetMaxNumber)
process.leadingJetSelectionNjets2Pt2 = process.leadingJetSelection.clone (src = 'tightLeadingPFJetsMinPt2', minNumber = 2, maxNumber = jetMaxNumber)
process.leadingJetSelectionNjets3MaxNum = process.leadingJetSelection.clone (src = 'tightLeadingPFJets', minNumber = 3, maxNumber = jetMaxNumber)
process.leadingJetSelectionNjets4MaxNum = process.leadingJetSelection.clone (src = 'tightLeadingPFJets', minNumber = 4, maxNumber = jetMaxNumber)
## normal inclusive jet selection
process.leadingJetSelectionNjets1 = process.leadingJetSelection.clone (src = 'tightLeadingPFJets', minNumber = 1)
process.leadingJetSelectionNjets2 = process.leadingJetSelection.clone (src = 'tightLeadingPFJets', minNumber = 2)
process.leadingJetSelectionNjets3 = process.leadingJetSelection.clone (src = 'tightLeadingPFJets', minNumber = 3)
process.leadingJetSelectionNjets4 = process.leadingJetSelection.clone (src = 'tightLeadingPFJets', minNumber = 4)
process.jetCuts = cms.Sequence(process.leadingJetSelectionNjets1 +
                               process.leadingJetSelectionNjets2 +
                               process.leadingJetSelectionNjets3 +
                               process.leadingJetSelectionNjets4 
                               )

process.bottomJetSelection2BTags  = process.bottomJetSelection.clone( minNumber = 2 )


## ----------------------------------------------------------------------------
##    run the final sequence
##-----------------------------------------------------------------------------

if(cutflowSelector == "effOnly" or cutflowSelector == "effAndCutflow"):
    process.p1 = cms.Path(
       ## apply primary vertex selection
       process.PVSelection                           *
       ## calculate PU weights
       process.makeEventWeightsPU                    *
       ## HLT trigger filter: lepton + 1jet
       process.hltTriggerFilter1                     *
       ## trigger event
       process.patTriggerSequenceUser                *
       ## introduce some collections
       process.semiLeptonicSelection                 *
       ## lepton selection
       process.leptonSelection                       *
       ## jet kinematics analyzer for events fired by trigger 1 before the jet cut
       #process.analyzeJet0Trig1BeforeCut             *
       #process.analyzeJet1Trig1BeforeCut             *
       #process.analyzeJet2Trig1BeforeCut             *
       #process.analyzeJet3Trig1BeforeCut             *
       #process.analyzeJetAllTrig1BeforeCut           *
       #process.analyzeJetDiffMultTrig1BeforeCut      *
       ## jet selection
       process.tightLeadingPFJetsMinPt1              *
       process.tightLeadingPFJetsMinPt2              *
       process.leadingJetSelectionNjets1Pt1          *
       process.leadingJetSelectionNjets2Pt2          *
       process.leadingJetSelectionNjets3MaxNum       *
       process.leadingJetSelectionNjets4MaxNum       *
       ## jet kinematics analyzer for events fired by trigger 1 after the jet cut
       process.analyzeJet0Trig1AfterCut              *
       process.analyzeJet1Trig1AfterCut              *
       process.analyzeJet2Trig1AfterCut              *
       process.analyzeJet3Trig1AfterCut              *
       process.analyzeJetAllTrig1AfterCut            *
       #process.analyzeJetDiffMultTrig1AfterCut       *
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
       #process.analyzeJetDiffMultTrig2AfterCut       *
       ## lepton analyzers
       process.leptonAnalyzersTrig2                  
    )
    
if(jetMinNumber < 4):
    process.p1.remove(process.leadingJetSelectionNjets4MaxNum)
if(jetMinNumber < 3):
    process.p1.remove(process.leadingJetSelectionNjets3MaxNum)
if(jetMinNumber < 2):
    process.p1.remove(process.leadingJetSelectionNjets2Pt2)
if(jetMinNumber == 0):
    process.p1.remove(process.leadingJetSelectionNjets1Pt1)
    
if(l3FilterSelector!=""):
    if(not useTriggerMatching):
        process.p1.replace(process.hltTriggerFilter2, process.hltL3Filter)
    else:
        process.p1.replace(process.hltTriggerFilter2, process.onlyTriggerMatchedLeptons*process.hltL3FilterByTriggerMatching)
if(not PUreweighting):
    process.p1.remove(process.makeEventWeightsPU)

##-------------------------------------------------------------------------------------
## Cutflow path for purity studies
if(cutflowSelector == "cutflowOnly" or cutflowSelector == "effAndCutflow" or cutflowSelector=="analyzeAfterCut"):
    process.p2 = cms.Path(
       ## apply primary vertex selection
       process.PVSelection                           *
       ## calculate PU weights
       process.eventWeightPU                         *
       ## HLT trigger filter
       process.hltTriggerFilter2                     *
       ## introduce some collections
       process.semiLeptonicSelection                 *
       ## muon selection
       process.leptonSelection                       *
       ## jet selections
       process.jetCuts                               *
       #process.bottomJetSelection                    *
       #process.bottomJetSelection2BTags              *
       ## analyzers after cuts
       process.analyzeJet0Trig2AfterCut              *
       process.analyzeJet1Trig2AfterCut              *
       process.analyzeJet2Trig2AfterCut              *
       process.analyzeJet3Trig2AfterCut              *
       process.analyzeJetAllTrig2AfterCut            *
       #process.analyzeJetDiffMultTrig2AfterCut       *
       ## lepton analyzers
       process.leptonAnalyzersTrig2
    )
    if(cutflowSelector == "cutflowOnly"):
	process.p2.remove(process.analyzeJet0Trig2AfterCut)
	process.p2.remove(process.analyzeJet1Trig2AfterCut)
	process.p2.remove(process.analyzeJet2Trig2AfterCut)
	process.p2.remove(process.analyzeJet3Trig2AfterCut)
	process.p2.remove(process.analyzeJetAllTrig2AfterCut)
	process.p2.remove(process.analyzeJetDiffMultTrig2AfterCut)
	process.p2.remove(process.leptonAnalyzersTrig2)
    if(not PUreweighting):
	process.p2.remove(process.eventWeightPU)
    
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
	
## switch from muon to electron collections
if(leptonTypeId==11):
    ## lepton-jet veto
    from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import *
    from PhysicsTools.PatAlgos.cleaningLayer1.jetCleaner_cfi import *
    process.noOverlapJetsPFelec = cleanPatJets.clone(
        src = cms.InputTag("selectedPatJetsAK5PF"),
        preselection = cms.string(''),
        checkOverlaps = cms.PSet(
          electrons = cms.PSet(
            src       = cms.InputTag("tightElectronsEJ"),
            algorithm = cms.string("byDeltaR"),
            preselection        = cms.string(''),
            deltaR              = cms.double(0.3),
            checkRecoComponents = cms.bool(False), # don't check if they share some AOD object ref
            pairCut             = cms.string(""),
            requireNoOverlaps   = cms.bool(True), # overlaps don't cause the jet to be discared
            )
          ),
        finalCut = cms.string(''),
        )
    process.goodJetsPF20.src  ='noOverlapJetsPFelec'
    process.centralJetsPF.src ='noOverlapJetsPFelec'
    process.reliableJetsPF.src='noOverlapJetsPFelec'
    process.noEtaJetsPF.src   ='noOverlapJetsPFelec'
    process.noPtJetsPF.src    ='noOverlapJetsPFelec'
    process.noConstJetsPF.src ='noOverlapJetsPFelec'
    process.noCEFJetsPF.src   ='noOverlapJetsPFelec'
    process.noNHFJetsPF.src   ='noOverlapJetsPFelec'
    process.noNEFJetsPF .src  ='noOverlapJetsPFelec'
    process.noCHFJetsPF.src   ='noOverlapJetsPFelec'
    process.noNCHJetsPF.src   ='noOverlapJetsPFelec'
    process.noKinJetsPF.src   ='noOverlapJetsPFelec'
    
    allpaths  = process.paths_().keys()
    for path in allpaths:
        # replace jet lepton veto
        getattr(process,path).replace(process.noOverlapJetsPF, process.noOverlapJetsPFelec)
	
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
        'analyzersBeforeElecIso':cms.Sequence(),
        'excludeElectronsFromWsFromGenJets': True,
        'METCorrectionLevel': 0
        }

    # adaptions when running on data
    if(dataSelector == 11):
        options['runOnMC']=False
    options['runOnAOD']=runOnAOD
    if(leptonTypeId==11):
    # take into account different electron vetos in mu and e channel
        options['cutsElec'    ] = 'et > 20. & abs(eta) < 2.5'
	if(PF2PATwithoutLeptonIsoCut):
	    ## change the source of the PAT leptons to nonIso leptons to be able to do isolation studies
	    process.load("PhysicsTools.PatAlgos.producersLayer1.electronProducer_cfi")
            process.patElectrons.pfElectronSource = cms.InputTag("pfSelectedElectrons")
	else:
	    options['skipIfNoPFElec']=True
    elif(leptonTypeId==13):
	if(PF2PATwithoutLeptonIsoCut):
	    ## change the source of the PAT leptons to nonIso leptons to be able to do isolation studies
	    process.load("PhysicsTools.PatAlgos.producersLayer1.muonProducer_cfi")
            process.patMuons.pfMuonSource = cms.InputTag("pfSelectedMuons")
	else:
	    options['skipIfNoPFMuon']=True 
    prependPF2PATSequence(process, allpaths, options)
    ## change the source of the PAT leptons to nonIso leptons to be able to do isolation studies
    if(PF2PATwithoutLeptonIsoCut):
        for path in allpaths:
	    if(leptonTypeId==11):
		getattr(process,path).remove(process.electronMatch)
		getattr(process,path).remove(process.patElectrons)
		if(dataSelector == 1):
		    getattr(process,path).replace(process.pfIsolatedElectrons, process.electronMatch*process.patElectrons*process.pfIsolatedElectrons)
		else:
		    getattr(process,path).replace(process.pfIsolatedElectrons, process.patElectrons*process.pfIsolatedElectrons)
		      
	    elif(leptonTypeId==13):
		getattr(process,path).remove(process.muonMatch)
		getattr(process,path).remove(process.patMuons)
		if(dataSelector == 1):
		    getattr(process,path).replace(process.pfIsolatedMuons, process.muonMatch*process.patMuons*process.pfIsolatedMuons)
		else:
		    getattr(process,path).replace(process.pfIsolatedMuons, process.patMuons*process.pfIsolatedMuons)
    
    # remove electron collections as long as id does not exist in the tuples
    #for path in allpaths:
        #getattr(process,path).remove( process.looseElectronsEJ )
        #getattr(process,path).remove( process.tightElectronsEJ )
        #getattr(process,path).remove( process.unconvTightElectronsEJ )
        #getattr(process,path).remove( process.goodElectronsEJ )
        # replace object consistently with names from PF2PAT
        #massSearchReplaceAnyInputTag(getattr(process,path), 'patMETsPF', 'patMETs')
        #massSearchReplaceAnyInputTag(getattr(process,path), 'selectedPatJetsAK5PF', 'selectedPatJets')
            
    # run trigger at the beginning to save a lot of time
    if(cutflowSelector == "effOnly" or cutflowSelector == "effAndCutflow"):
        process.p1.insert(0,process.hltTriggerFilter1)
	print "hltTriggerFilter1 moved to the beginning of p1"
    if(cutflowSelector == "cutflowOnly" or cutflowSelector == "effAndCutflow"):
        process.p2.insert(0,process.hltTriggerFilter2)
	print "hltTriggerFilter2 moved to the beginning of p2"