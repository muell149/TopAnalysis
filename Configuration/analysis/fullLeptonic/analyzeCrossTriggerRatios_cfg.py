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
## switch between efficiency and cutflow studies (for purity)
if(not globals().has_key("cutflowSelector")):
	cutflowSelector = "effOnly" # cutflowOnly, effAndCutflow
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

## Global tags
## needed for L1 lookup tables
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
print "dataSelector = ", dataSelector
if(dataSelector == 14):
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
# ----- Efficiency Studies  ----- #
#-----------------------------------------------------------------------------

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

## lepton analyzers after trigger 1 and trigger 2
process.load("TopAnalysis.TopAnalyzer.MuonKinematics_cfi")
process.analyzeMuonKinematicsTrig1 = process.analyzeMuonKinematics.clone(src="tightMuons");
process.analyzeMuonKinematicsTrig2 = process.analyzeMuonKinematics.clone(src="tightMuons");
process.load("TopAnalysis.TopAnalyzer.MuonQuality_cfi")
process.analyzeMuonQualityTrig1 = process.analyzeMuonQuality.clone(src="tightMuons");
process.analyzeMuonQualityTrig2 = process.analyzeMuonQuality.clone(src="tightMuons");
process.load("TopAnalysis.TopAnalyzer.ElectronKinematics_cfi")
process.analyzeElectronKinematicsTrig1 = process.analyzeElectronKinematics.clone(src="tightElectronsEJ");
process.analyzeElectronKinematicsTrig2 = process.analyzeElectronKinematics.clone(src="tightElectronsEJ");
process.load("TopAnalysis.TopAnalyzer.ElectronQuality_cfi")
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
elif (leptonTypeId == 11):
    process.leptonSelection          = cms.Sequence( process.tightElectronSelection *
                                           process.muonVeto               *
                                           process.secondElectronVeto     *
                                           process.convElecHitRejection   *
                                           process.convElecTrkRejection 
                                         )

## ---
##    Set up selection steps for different jet multiplicities
## ---
## new pt cuts on jet 1 and 2
process.tightLeadingPFJetsMinPt1 = process.tightLeadingPFJets.clone( cut = 'pt >'+ jetMinPt1 )
process.tightLeadingPFJetsMinPt2 = process.tightLeadingPFJets.clone( cut = 'pt >'+ jetMinPt2 )
process.leadingJetSelectionNjets1Pt1 = process.leadingJetSelection.clone (src = 'tightLeadingPFJetsMinPt1', minNumber = 1)
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
       ## HLT trigger filter: lepton + 1jet
       process.hltTriggerFilter1                     *
       ## introduce some collections
       process.semiLeptonicSelection                 *
       ## lepton selection
       process.leptonSelection                       *
       ## jet kinematics analyzer for events fired by trigger 1 before the jet cut
       process.analyzeJet0Trig1BeforeCut             *
       process.analyzeJet1Trig1BeforeCut             *
       process.analyzeJet2Trig1BeforeCut             *
       process.analyzeJet3Trig1BeforeCut             *
       process.analyzeJetAllTrig1BeforeCut           *
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
    
if(jetMinNumber < 4):
    process.p1.remove(process.leadingJetSelectionNjets4MaxNum)
if(jetMinNumber < 3):
    process.p1.remove(process.leadingJetSelectionNjets3MaxNum)
if(jetMinNumber == 0):
    process.p1.remove(leadingJetSelectionNjets2Pt2, leadingJetSelectionNjets1Pt1)

##-------------------------------------------------------------------------------------
## Cutflow path for purity studies
if(cutflowSelector == "cutflowOnly" or cutflowSelector == "effAndCutflow"):
    process.p2 = cms.Path(
       ## apply primary vertex selection
       process.PVSelection                           *
       ## HLT trigger filter
       process.hltTriggerFilter2                     *
       ## introduce some collections
       process.semiLeptonicSelection                 *
       ## muon selection
       process.leptonSelection                       *
       ## jet selections
       process.jetCuts                               *
       process.bottomJetSelection                    *
       process.bottomJetSelection2BTags
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
    
    allpaths  = process.paths_().keys()
    for path in allpaths:
        # replace jet lepton veto
        getattr(process,path).replace(process.noOverlapJetsPF, process.noOverlapJetsPFelec)