

import FWCore.ParameterSet.Config as cms

## ---
##   use this file to study different distributions for measurement of differential Cross Section
##   does also a monitoring of the cuts before they are applied
## ---

## ---
##    eventfilter is to get a special ttbar decay channel from ttbarSample by genmatching
##    decide whether to run on:
# 'background only' # 'all' # 'signal only' # 'semileptonic electron only' # 'dileptonic electron only' # 'dileptonic muon only' # 'fullhadronic' # 'dileptonic muon + electron only' # 'via single tau only' # 'dileptonic via tau only'
##    careful: genmatched selection- might cause problems for specific BG samples like qcd or data - use 'all' for them
##    signal is semileptonic with mu
##    background is ttbar other channels
##    'all' does no selection
## ---

jetType =  'particleFlow' # 'Calo' 

eventFilter  = 'signal only' #'all'
## choose between # 'background only' # 'all' # 'signal only' # 'semileptonic electron only' # 'dileptonic electron only' # 'dileptonic muon only' # 'fullhadronic' # 'dileptonic muon + electron only' # 'via single tau only' # 'dileptonic via tau only'
if(not globals().has_key('writeOutput')): 
    writeOutput  = False # True

# analyse muon quantities
process = cms.Process("Selection")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

## define input
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(    
    ## add your favourite file here
    #'/store/user/mgoerner/WJetsToLNu_TuneD6T_7TeV-madgraph-tauola/PAT_FALL10HH/148435cd71339b79cc0025730c13472a/fall10MC_100_1_iJg.root'
    #'/store/user/henderle/TTJets_TuneD6T_7TeV-madgraph-tauola/PAT_FALL10HH/6c1c00d4602477b58cef63f182ce0614/fall10MC_10_1_6nQ.root'
    #'/store/user/mgoerner/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/PAT_FALL10HH2/148435cd71339b79cc0025730c13472a/fall10MC_9_1_mFa.root'
    )
)

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeDiffXSec_test.root')
)

# switch to run on data and remove all gen plots (type 'MC' or 'data')
if(not globals().has_key('runningOnData')): 
    runningOnData = "MC"

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('START38_V14::All')

## Needed for redoing the ak5GenJets
process.load("TopAnalysis.TopUtils.GenJetParticles_cff")
process.load("RecoJets.Configuration.RecoGenJets_cff")

if(runningOnData=="MC"):
    process.p0 = cms.Path(## redo genjets without mu/nu from tau
                          process.genJetParticles *
                          process.ak5GenJets
                          )
    
## ---
##    configure the cutflow scenario
## ---
## std sequence to produce the ttGenEvt
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")
## high level trigger filter
#(use "TriggerResults::REDIGI38X" for fall10 QCD, WW, ZZ and WZ and "TriggerResults::HLT" for the other ones)
from HLTrigger.HLTfilters.hltHighLevel_cfi import *
#process.hltFilter = hltHighLevel.clone(TriggerResultsTag = "TriggerResults::REDIGI38X", HLTPaths = ["HLT_Mu9"])
process.hltFilter = hltHighLevel.clone(TriggerResultsTag = "TriggerResults::HLT", HLTPaths = ["HLT_Mu9"])

## semileptonic selection
process.load("TopAnalysis.TopFilter.sequences.semiLeptonicSelection_cff")
## generator matching
process.load("TopAnalysis.TopFilter.sequences.generatorMatching_cff")
## muon selection
process.load("TopAnalysis.TopFilter.sequences.muonSelection_cff")
## jet selection
process.load("TopAnalysis.TopFilter.sequences.jetSelection_cff")
## tool to select muons from gen Particles and save them as new collection
process.load("TopAnalysis.TopUtils.GenCandSelector_cfi")
## generator level based collections and semileptonic selection (muon and jets)
process.load("TopAnalysis.TopFilter.sequences.genSelection_cff")

## ---
## including analysis tools
## ---
## cross section module
process.load("TopAnalysis.TopAnalyzer.MuonCrossSection_cfi")
## jet kinematics analyzer
process.load("TopAnalysis.TopAnalyzer.JetKinematics_cfi")
## muon kinematics analyzer
process.load("TopAnalysis.TopAnalyzer.MuonKinematics_cfi")
## jet quality analyzer
process.load("TopAnalysis.TopAnalyzer.JetQuality_cfi")
## muon quality analyzer
process.load("TopAnalysis.TopAnalyzer.MuonQuality_cfi")
## electron quality analyzer
process.load("TopAnalysis.TopAnalyzer.ElectronQuality_cfi")
## MET analyzer
process.load("TopAnalysis.TopAnalyzer.METKinematics_cfi")
## electron kinematics analyzer
process.load("TopAnalysis.TopAnalyzer.ElectronKinematics_cfi")
## muon jet kinematics analyzer
process.load("TopAnalysis.TopAnalyzer.MuonJetKinematics_cfi")
## muon vertex analyzer
process.load("TopAnalysis.TopAnalyzer.MuonVertexKinematics_cfi")

## ---
##    set up vertex filter
## ---
process.PVSelection = cms.EDFilter("PrimaryVertexFilter",
                                   pvSrc   = cms.InputTag('offlinePrimaryVertices'),
                                   minNdof = cms.double(4.0),
                                   maxZ    = cms.double(24.0),
                                   maxRho  = cms.double(2.0)
                                   )

## ---
##    set up filter for different ttbar decay channels
## ---
process.load("TopQuarkAnalysis.TopEventProducers.producers.TtDecaySelection_cfi")
process.ttSemiLeptonicFilter = process.ttDecaySelection.clone()
process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.muon = True
if(not eventFilter=='all'):
    ## adapt output filename
    if(eventFilter=='signal only'):
        process.TFileService.fileName = 'analyzeDiffXSec_testSig.root'
    elif(eventFilter=='background only'):
        process.ttSemiLeptonicFilter.invert = True
    elif(eventFilter=='semileptonic electron only'):
        process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.muon     = False
        process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.electron = True
    elif(eventFilter=='dileptonic electron only'):
        process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.muon     = False
        process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.electron = True
        process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchB.electron = True
    elif(eventFilter=='dileptonic muon only'):
        process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.muon     = True
        process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchB.muon     = True
    elif(eventFilter=='fullhadronic'):
        process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.muon     = False
    elif(eventFilter=='dileptonic muon + electron only'):
        process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.muon     = True
        process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchB.electron = True
    elif(eventFilter=='dileptonic via tau only'):
        process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.muon     = False
        process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.tau      = True
        process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchB.electron = True
        process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchB.muon     = True
        process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchB.tau      = True
    elif(eventFilter=='via single tau only'):
        process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.muon     = False
        process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.tau      = True
    else:
        raise NameError, "'"+eventFilter+"' is not a prober eventFilter name choose: 'all', 'signal only', 'background only', 'semileptonic electron only', 'dileptonic electron only', 'dileptonic muon only', 'fullhadronic', 'via single tau only', 'dileptonic via tau only' or 'dileptonic muon + electron only'"
    
    ## sequence with filter for decay channel and trigger selection hltFilter
    process.filterSequence = cms.Sequence(process.makeGenEvt *
                                          process.ttSemiLeptonicFilter *
                                          process.hltFilter
                                          )
else:
    ## sequence without filter (only trigger selection hltFilter) - done when 'all' is chosen
    process.filterSequence = cms.Sequence(process.hltFilter)
    
## ---
##    set up genFilter for semileptonic muons and taus, where taus are decaying into leptons
## ---
process.ttSemiLeptonicFilterSemiTauMuon= process.ttDecaySelection.clone()
process.ttSemiLeptonicFilterSemiTauMuon.allowedTopDecays.decayBranchA.tau = True
process.ttSemiLeptonicFilterSemiTauMuon.allowedTopDecays.decayBranchA.muon= True
process.ttSemiLeptonicFilterSemiTauMuon.restrictTauDecays = cms.PSet(
    leptonic   = cms.bool(True),
    oneProng   = cms.bool(False),
    threeProng = cms.bool(False)
    )
process.genFilterSequence = cms.Sequence(process.makeGenEvt                      *
                                         process.ttSemiLeptonicFilterSemiTauMuon *
                                         process.ttSemiLeptonicFilter             )

## define ordered jets
uds0    = cms.PSet(index = cms.int32(0), correctionLevel = cms.string('L3Absolute'), useTree = cms.bool(False) )
uds1    = cms.PSet(index = cms.int32(1), correctionLevel = cms.string('L3Absolute'), useTree = cms.bool(False) )
uds2    = cms.PSet(index = cms.int32(2), correctionLevel = cms.string('L3Absolute'), useTree = cms.bool(False) )
uds3    = cms.PSet(index = cms.int32(3), correctionLevel = cms.string('L3Absolute'), useTree = cms.bool(False) )

## jet Kinematics to monitor JES shift
if(jetType=="particleFlow"):
    process.patLead_0_JetKinematics = process.analyzeJetKinematics.clone (src = 'selectedPatJetsAK5PF', analyze = uds0 )
    process.patLead_1_JetKinematics = process.analyzeJetKinematics.clone (src = 'selectedPatJetsAK5PF', analyze = uds1 )
    process.patLead_2_JetKinematics = process.analyzeJetKinematics.clone (src = 'selectedPatJetsAK5PF', analyze = uds2 )
    process.patLead_3_JetKinematics = process.analyzeJetKinematics.clone (src = 'selectedPatJetsAK5PF', analyze = uds3 )
    process.shiftedLead_0_JetKinematics = process.analyzeJetKinematics.clone (src = 'scaledJetEnergy:selectedPatJetsAK5PF', analyze = uds0 )
    process.shiftedLead_1_JetKinematics = process.analyzeJetKinematics.clone (src = 'scaledJetEnergy:selectedPatJetsAK5PF', analyze = uds1 )
    process.shiftedLead_2_JetKinematics = process.analyzeJetKinematics.clone (src = 'scaledJetEnergy:selectedPatJetsAK5PF', analyze = uds2 )
    process.shiftedLead_3_JetKinematics = process.analyzeJetKinematics.clone (src = 'scaledJetEnergy:selectedPatJetsAK5PF', analyze = uds3 )
elif(jetType=="Calo"):
    process.patLead_0_JetKinematics = process.analyzeJetKinematics.clone (src = 'selectedPatJets', analyze = uds0 )
    process.patLead_1_JetKinematics = process.analyzeJetKinematics.clone (src = 'selectedPatJets', analyze = uds1 )
    process.patLead_2_JetKinematics = process.analyzeJetKinematics.clone (src = 'selectedPatJets', analyze = uds2 )
    process.patLead_3_JetKinematics = process.analyzeJetKinematics.clone (src = 'selectedPatJets', analyze = uds3 )
    process.shiftedLead_0_JetKinematics = process.analyzeJetKinematics.clone (src = 'scaledJetEnergy:selectedPatJets', analyze = uds0 )
    process.shiftedLead_1_JetKinematics = process.analyzeJetKinematics.clone (src = 'scaledJetEnergy:selectedPatJets', analyze = uds1 )
    process.shiftedLead_2_JetKinematics = process.analyzeJetKinematics.clone (src = 'scaledJetEnergy:selectedPatJets', analyze = uds2 )
    process.shiftedLead_3_JetKinematics = process.analyzeJetKinematics.clone (src = 'scaledJetEnergy:selectedPatJets', analyze = uds3 )
else:
    print "unknown jetType"

    
process.unshiftedJets = cms.Sequence(process.patLead_0_JetKinematics+
                                     process.patLead_1_JetKinematics+
                                     process.patLead_2_JetKinematics+
                                     process.patLead_3_JetKinematics
                                     )

process.shiftedJets = cms.Sequence(process.shiftedLead_0_JetKinematics+
                                   process.shiftedLead_1_JetKinematics+
                                   process.shiftedLead_2_JetKinematics+
                                   process.shiftedLead_3_JetKinematics
                                   )

## ---                                   
##    set up distribution for cross section measurement
## ---

## a) on reconstruction Niveau (with correlation plots for Migration effects if runningOnData=="MC")

if(runningOnData=="MC"):
    process.analyzeTightMuonCrossSectionRecNjets1 = process.analyzeCrossSectionMuonCorrelations.clone(srcA = 'tightMuons',
                                                                                                      srcB = 'selectedGenMuonCollection')
    process.analyzeTightMuonCrossSectionRecNjets2 = process.analyzeCrossSectionMuonCorrelations.clone(srcA = 'tightMuons',
                                                                                                      srcB = 'selectedGenMuonCollection')
    process.analyzeTightMuonCrossSectionRecNjets3 = process.analyzeCrossSectionMuonCorrelations.clone(srcA = 'tightMuons',
                                                                                                      srcB = 'selectedGenMuonCollection')
    process.analyzeTightMuonCrossSectionRecNjets4 = process.analyzeCrossSectionMuonCorrelations.clone(srcA = 'tightMuons',
                                                                                                      srcB = 'selectedGenMuonCollection')
    process.analyzeTightMuonCrossSectionRecNjets4Btag = process.analyzeCrossSectionMuonCorrelations.clone(srcA = 'tightMuons',
                                                                                                          srcB = 'selectedGenMuonCollection')
    process.analyzeTightMuonCrossSectionRecNjets3Btag = process.analyzeCrossSectionMuonCorrelations.clone(srcA = 'tightMuons',
                                                                                                          srcB = 'selectedGenMuonCollection')

else:
    process.analyzeTightMuonCrossSectionRecNjets1     = process.analyzeCrossSectionRecMuon.clone(srcA = 'tightMuons')
    process.analyzeTightMuonCrossSectionRecNjets2     = process.analyzeCrossSectionRecMuon.clone(srcA = 'tightMuons')
    process.analyzeTightMuonCrossSectionRecNjets3     = process.analyzeCrossSectionRecMuon.clone(srcA = 'tightMuons')
    process.analyzeTightMuonCrossSectionRecNjets4     = process.analyzeCrossSectionRecMuon.clone(srcA = 'tightMuons')
    process.analyzeTightMuonCrossSectionRecNjets4Btag = process.analyzeCrossSectionRecMuon.clone(srcA = 'tightMuons')
    process.analyzeTightMuonCrossSectionRecNjets3Btag = process.analyzeCrossSectionRecMuon.clone(srcA = 'tightMuons')   

## b) on generator Niveau
process.analyzeTightMuonCrossSectionGenNjets1 = process.analyzeCrossSectionGenMuon.clone(srcA = 'selectedGenMuonCollection')
process.analyzeTightMuonCrossSectionGenNjets2 = process.analyzeCrossSectionGenMuon.clone(srcA = 'selectedGenMuonCollection')
process.analyzeTightMuonCrossSectionGenNjets3 = process.analyzeCrossSectionGenMuon.clone(srcA = 'selectedGenMuonCollection')
process.analyzeTightMuonCrossSectionGenNjets4 = process.analyzeCrossSectionGenMuon.clone(srcA = 'selectedGenMuonCollection')

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

## ---
##    Set up selection steps for different jet multiplicities
## ---
process.leadingJetSelectionNjets1 = process.leadingJetSelection.clone (src = 'tightLeadingJets', minNumber = 1)
process.leadingJetSelectionNjets2 = process.leadingJetSelection.clone (src = 'tightLeadingJets', minNumber = 2)
process.leadingJetSelectionNjets3 = process.leadingJetSelection.clone (src = 'tightLeadingJets', minNumber = 3)
process.leadingJetSelectionNjets4 = process.leadingJetSelection.clone (src = 'tightLeadingJets', minNumber = 4)

## ---
##    collect selections for path 2 (jetmultiplicity 3 && btag) and the output modules with different names
## ---
process.ttSemiLeptonicFilterb = process.ttSemiLeptonicFilter.clone()
process.filterSequenceb = cms.Sequence(process.makeGenEvt *
                                       process.ttSemiLeptonicFilterb *
                                       process.hltFilter
                                       )
process.bottomJetSelectionb        = process.bottomJetSelection.clone()
process.leadingJetSelectionNjets3b = process.leadingJetSelectionNjets3.clone()
process.muonSelectionb  = process.muonSelection.clone()
process.secondMuonVetob = process.secondMuonVeto.clone()
process.electronVetob   = process.electronVeto.clone()
process.PVSelectionb    = process.PVSelection.clone()
process.leadingJetSelectionNjets1Pat = process.leadingJetSelectionNjets1.clone()
process.leadingJetSelectionNjets2Pat = process.leadingJetSelectionNjets2.clone()
process.leadingJetSelectionNjets3Pat = process.leadingJetSelectionNjets3.clone()

## ---
##    Set up selection steps for different (gen)-jet multiplicities
## ---
process.leadingGenJetSelectionNjets1 = process.leadingGenJetSelection.clone (src = 'selectedGenJetCollection', minNumber = 1)
process.leadingGenJetSelectionNjets2 = process.leadingGenJetSelection.clone (src = 'selectedGenJetCollection', minNumber = 2)
process.leadingGenJetSelectionNjets3 = process.leadingGenJetSelection.clone (src = 'selectedGenJetCollection', minNumber = 3)
process.leadingGenJetSelectionNjets4 = process.leadingGenJetSelection.clone (src = 'selectedGenJetCollection', minNumber = 4)

## ---
##    configure MET analyzer
## ---

process.analyzePfMET  = process.analyzeMETCorrelations.clone(srcA = 'patMETsPF', srcB='tightMuons')
process.analyzePatMET = process.analyzeMETCorrelations.clone(srcA = 'patMETs'  , srcB='tightMuons')
                                    
process.analyzePfMETNjets1    = process.analyzeMETCorrelations.clone(srcA = 'patMETsPF', srcB='tightMuons')
process.analyzePfMETNjets2    = process.analyzeMETCorrelations.clone(srcA = 'patMETsPF', srcB='tightMuons')
process.analyzePfMETNjets3    = process.analyzeMETCorrelations.clone(srcA = 'patMETsPF', srcB='tightMuons')
process.analyzePfMETNjets3Btag= process.analyzeMETCorrelations.clone(srcA = 'patMETsPF', srcB='tightMuons')
process.analyzePfMETNjets4    = process.analyzeMETCorrelations.clone(srcA = 'patMETsPF', srcB='tightMuons')
process.analyzePfMETNjets4Btag= process.analyzeMETCorrelations.clone(srcA = 'patMETsPF', srcB='tightMuons')

process.analyzePatMETNjets1    = process.analyzeMETCorrelations.clone(srcA = 'patMETs', srcB='tightMuons')
process.analyzePatMETNjets2    = process.analyzeMETCorrelations.clone(srcA = 'patMETs', srcB='tightMuons')
process.analyzePatMETNjets3    = process.analyzeMETCorrelations.clone(srcA = 'patMETs', srcB='tightMuons')
process.analyzePatMETNjets3Btag= process.analyzeMETCorrelations.clone(srcA = 'patMETs', srcB='tightMuons')
process.analyzePatMETNjets4    = process.analyzeMETCorrelations.clone(srcA = 'patMETs', srcB='tightMuons')
process.analyzePatMETNjets4Btag= process.analyzeMETCorrelations.clone(srcA = 'patMETs', srcB='tightMuons')

## collect cut monitoring
## N-1 muon collections
process.noDbMuonQuality           = process.analyzeMuonQuality.clone   (src = 'noDbMuons'      )
process.noChi2MuonQuality         = process.analyzeMuonQuality.clone   (src = 'noChi2Muons'    )
process.noTrkHitsMuonQuality      = process.analyzeMuonQuality.clone   (src = 'noTrkHitsMuons' )
process.noIsoMuonQuality          = process.analyzeMuonQuality.clone   (src = 'noIsoMuons'     )
process.noEtaMuonKinematics       = process.analyzeMuonKinematics.clone(src = 'noEtaMuons'     )
process.noPtMuonKinematics        = process.analyzeMuonKinematics.clone(src = 'noPtMuons'      )
process.noDRMuonVetoJetsKinematics = process.analyzeMuonJetKinematics.clone(srcA = 'noDRMuons',
                                                                            srcB = 'goodJets'  )
## N-1 jet collections
process.noEtaJetKinematics  = process.analyzeJetKinematics.clone(src = 'noEtaJets' )
process.noPtJetKinematics   = process.analyzeJetKinematics.clone(src = 'noPtJets'  )
if(jetType!="particleFlow"):
    process.noEmJetQuality      = process.analyzeJetQuality.clone(src = 'noEmJets'     )
    process.noN90HitsJetQuality = process.analyzeJetQuality.clone(src = 'noN90HitsJets')
    process.nofHPDJetQuality    = process.analyzeJetQuality.clone(src = 'nofHPDJets'   )
process.noPtLead_0_JetKinematics = process.analyzeJetKinematics.clone (src = 'noPtJets', analyze = uds0 )
process.noPtLead_1_JetKinematics = process.analyzeJetKinematics.clone (src = 'noPtJets', analyze = uds1 )
process.noPtLead_2_JetKinematics = process.analyzeJetKinematics.clone (src = 'noPtJets', analyze = uds2 )
process.noPtLead_3_JetKinematics = process.analyzeJetKinematics.clone (src = 'noPtJets', analyze = uds3 )
## veto collections
process.looseVetoMuonKinematics     = process.analyzeMuonKinematics.clone(src = 'looseMuons', analyze = cms.PSet(index = cms.int32(-1)))
process.looseVetoElectronKinematics = process.analyzeElectronKinematics.clone(src = 'looseElectrons',
                                                                              analyze = cms.PSet(index = cms.int32(-1)) )
process.patVetoElectronKinematics = process.analyzeElectronKinematics.clone(src = 'selectedPatElectrons',
                                                                            analyze = cms.PSet(index = cms.int32(-1)) )
process.patVetoElectronQuality = process.analyzeElectronQuality.clone(src = 'selectedPatElectrons',
                                                                      analyze = cms.PSet(index = cms.int32(-1)) )

## muon cutflow
process.combinedMuonKinematics = process.analyzeMuonKinematics.clone(src = 'combinedMuons')
process.highPtMuonKinematics   = process.analyzeMuonKinematics.clone(src = 'highPtMuons')
process.kinematicMuonQuality   = process.analyzeMuonQuality.clone   (src = 'kinematicMuons')
process.kinematicMuonVertexKinematics  = process.analyzeMuonVertex.clone(srcA = 'kinematicMuons',
                                                                         srcB = 'offlinePrimaryVertices',
                                                                         analyze = cms.PSet(index = cms.int32(0)) )
process.trackMuonVetoJetsKinematics = process.analyzeMuonJetKinematics.clone(srcA = 'trackMuons',
                                                                             srcB = 'goodJets'  )
process.goldenMuonQuality      = process.analyzeMuonQuality.clone   (src = 'goldenMuons'  )
process.tightMuonKinematics    = process.analyzeMuonKinematics.clone(src = 'tightMuons'   )
process.tightMuonQuality       = process.analyzeMuonQuality.clone   (src = 'tightMuons'   )

## jet cutflow
if(jetType=="particleFlow"):
    process.patJetKinematics = process.analyzeJetKinematics.clone(src = 'selectedPatJetsAK5PF')
elif(jetType=="Calo"):
    process.patJetKinematics = process.analyzeJetKinematics.clone(src = 'selectedPatJets')
else:
    print "unknown jetType"
process.centralLead_0_JetKinematics = process.analyzeJetKinematics.clone (src = 'centralJets', analyze = uds0 )
process.centralLead_1_JetKinematics = process.analyzeJetKinematics.clone (src = 'centralJets', analyze = uds1 )
process.centralLead_2_JetKinematics = process.analyzeJetKinematics.clone (src = 'centralJets', analyze = uds2 )
process.centralLead_3_JetKinematics = process.analyzeJetKinematics.clone (src = 'centralJets', analyze = uds3 )
process.centralJetKinematics = process.analyzeJetKinematics.clone(src = 'centralJets'    )
process.reliableJetQuality   = process.analyzeJetQuality.clone   (src = 'reliableJets'   )
process.tightJetKinematics  = process.analyzeJetKinematics.clone(src = 'tightLeadingJets')
## btag selection cuts
process.tightJetQuality     = process.analyzeJetQuality.clone   (src = 'tightLeadingJets')
process.bottomJetKinematics = process.analyzeJetKinematics.clone(src = 'tightBottomJets' )
process.bottomJetKinematicsNjets1=process.bottomJetKinematics.clone()
process.bottomJetKinematicsNjets2=process.bottomJetKinematics.clone()
process.bottomJetKinematicsNjets3=process.bottomJetKinematics.clone()
process.bottomJetKinematicsNjets4=process.bottomJetKinematics.clone()
## btag monitoring before jetcuts
process.tightJetQualityBeforeJetCuts     = process.analyzeJetQuality.clone   (src = 'tightLeadingJets')
process.bottomJetKinematicsBeforeJetCuts = process.analyzeJetKinematics.clone(src = 'tightBottomJets' )

process.monitorNMinusOneMuonCuts = cms.Sequence(process.noDbMuonQuality            +
                                                process.noChi2MuonQuality          +
                                                process.noTrkHitsMuonQuality       +
                                                process.noIsoMuonQuality           +
                                                process.noEtaMuonKinematics        +
                                                process.noPtMuonKinematics         +
                                                process.noDRMuonVetoJetsKinematics
                                                )
process.monitorMuonCutflow = cms.Sequence(process.combinedMuonKinematics        +
                                          process.highPtMuonKinematics          +
                                          process.kinematicMuonQuality          +
                                          process.kinematicMuonVertexKinematics +
                                          process.trackMuonVetoJetsKinematics   +
                                          process.goldenMuonQuality             +
                                          process.tightMuonKinematics           +
                                          process.tightMuonQuality              +
                                          process.analyzePatMET                 +
                                          process.analyzePfMET
                                          )
if(jetType=="Calo"):
    process.monitorNMinusOneJetCuts = cms.Sequence(process.noPtLead_0_JetKinematics  +
                                                   process.noPtLead_1_JetKinematics  +
                                                   process.noPtLead_2_JetKinematics  +
                                                   process.noPtLead_3_JetKinematics  +
                                                   process.noEtaJetKinematics        +
                                                   process.noPtJetKinematics         +
                                                   process.noEmJetQuality            +
                                                   process.noN90HitsJetQuality       +
                                                   process.nofHPDJetQuality       
                                                   )
elif(jetType=="particleFlow"):
    process.monitorNMinusOneJetCuts = cms.Sequence(process.noPtLead_0_JetKinematics  +
                                                   process.noPtLead_1_JetKinematics  +
                                                   process.noPtLead_2_JetKinematics  +
                                                   process.noPtLead_3_JetKinematics  +
                                                   process.noEtaJetKinematics        +
                                                   process.noPtJetKinematics
                                                   )
else:
    print "unknown jetType"
process.monitorJetCutflow = cms.Sequence(process.patJetKinematics            +
                                         process.centralLead_0_JetKinematics +
                                         process.centralLead_1_JetKinematics +
                                         process.centralLead_2_JetKinematics +
                                         process.centralLead_3_JetKinematics +
                                         process.centralJetKinematics        +
                                         process.reliableJetQuality          +
                                         process.tightJetKinematics
                                         )
process.monitorVetoCuts = cms.Sequence(process.looseVetoMuonKinematics     +
                                       process.patVetoElectronKinematics   +
                                       process.patVetoElectronQuality      +
                                       process.looseVetoElectronKinematics
                                       )
process.monitorBtagCuts = cms.Sequence(process.tightJetQuality     +
                                       process.bottomJetKinematics 
                                       )

## ---
##     collect analyzers for different jet multiplicities
##    ( Selection - CrossSectionMeasurement - CorrelationPlots - JetKinematics - METKinematics)
## ---
process.jetMultiplicity1 = cms.Sequence(process.leadingJetSelectionNjets1             +
                                        process.analyzeTightMuonCrossSectionRecNjets1 +
                                        process.analyzePfMETNjets1                    +
                                        process.analyzePatMETNjets1                   +
                                        process.bottomJetKinematicsNjets1             )
process.jetMultiplicity2 = cms.Sequence(process.leadingJetSelectionNjets2             +
                                        process.analyzeTightMuonCrossSectionRecNjets2 +
                                        process.analyzePfMETNjets2                    +
                                        process.analyzePatMETNjets2                   +
                                        process.bottomJetKinematicsNjets2             )
process.jetMultiplicity3 = cms.Sequence(process.leadingJetSelectionNjets3             +
                                        process.analyzeTightMuonCrossSectionRecNjets3 +
                                        process.analyzePfMETNjets3                    +
                                        process.analyzePatMETNjets3                   +
                                        process.bottomJetKinematicsNjets3             )
process.jetMultiplicity4 = cms.Sequence(process.leadingJetSelectionNjets4             +
                                        process.analyzeTightMuonCrossSectionRecNjets4 +
                                        process.analyzePfMETNjets4                    +
                                        process.analyzePatMETNjets4                   +
                                        process.bottomJetKinematicsNjets4             )
process.jetMultiplicity3Btag = cms.Sequence(process.leadingJetSelectionNjets3b                 +
                                            process.bottomJetSelectionb                        +
                                            process.analyzeTightMuonCrossSectionRecNjets3Btag  +
                                            process.analyzePfMETNjets3Btag                     +
                                            process.analyzePatMETNjets3Btag                    )
process.jetMultiplicity4Btag = cms.Sequence(process.bottomJetSelection                         +
                                            process.analyzeTightMuonCrossSectionRecNjets4Btag  +
                                            process.analyzePfMETNjets4Btag                     +
                                            process.analyzePatMETNjets4Btag                    )

## ---
##    configure ABCD method for QCD estimation
## ---

## a) the muon collection for monitoring relIso vs dB
## muon selector
from PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi import *
process.estimationMuons = selectedPatMuons.clone(src = 'vertexSelectedMuons',
                                                 cut = 'pt > 20. & abs(eta) < 2.1 &'
                                                 'isGlobalMuon &'
                                                 'isTrackerMuon() =1 &'                                            
                                                 'innerTrack.numberOfValidHits >= 11 &'
                                                 'globalTrack.normalizedChi2 < 10.0 &'
                                                 'globalTrack.hitPattern.numberOfValidMuonHits>0 &'
                                                 'innerTrack.hitPattern.pixelLayersWithMeasurement>=1 &'
                                                 'numberOfMatches>1'
                                                 )
## b) the different selection steps
process.ttSemiLeptonicFilterABCD = process.ttSemiLeptonicFilter.clone()
process.filterSequenceABCD = cms.Sequence(process.makeGenEvt *
                                          process.ttSemiLeptonicFilterABCD *
                                          process.hltFilter
                                          )
process.PVSelectionABCD = process.PVSelection.clone()
process.leadingJetSelectionNjets1ABCD = process.leadingJetSelectionNjets1.clone()
process.leadingJetSelectionNjets2ABCD = process.leadingJetSelectionNjets2.clone()         
process.leadingJetSelectionNjets3ABCD = process.leadingJetSelectionNjets3.clone()         
process.leadingJetSelectionNjets4ABCD = process.leadingJetSelectionNjets4.clone()         
process.muonSelectionABCD  = process.muonSelection.clone()                    
process.secondMuonVetoABCD = process.secondMuonVeto.clone()                   
process.electronVetoABCD   = process.electronVeto.clone()
process.estimationMuonsSelection = process.muonSelection.clone (src = 'estimationMuons', minNumber = 1, maxNumber = 1)

## c) the relIso vs dB monitoring plots
process.estimationMuonsQualityNjets1 = process.analyzeMuonQuality.clone(src = 'estimationMuons',
                                                                        analyze = cms.PSet(index = cms.int32(0)) )
process.estimationMuonsQualityNjets2 = process.estimationMuonsQualityNjets1.clone()
process.estimationMuonsQualityNjets3 = process.estimationMuonsQualityNjets1.clone()
process.estimationMuonsQualityNjets4 = process.estimationMuonsQualityNjets1.clone()

## ---
##    run the final sequences
## ---

process.p1 = cms.Path(
                      ## gen event selection (decay channel) and the trigger selection (hltFilter)
                      process.filterSequence                        *
                      ## PV event selection
                      process.PVSelection                           *
                      ## introduce some collections
                      process.semiLeptonicSelection                 *
                      process.selectNMinusOneJets                   *
                      process.selectNMinusOneMuons                  *
                      process.isolatedGenMuons                      *
                      process.semiLeptGenCollections                *
                      ## monitor all muon cut quantities
                      process.monitorNMinusOneMuonCuts              *
                      process.monitorMuonCutflow                    *
                      ## do the event selection for muon
                      process.muonCuts                              *
                      ## monitor veto collection
                      process.monitorVetoCuts                       *
                      ## do event selection veto cuts
                      process.secondMuonVeto                        *
                      process.electronVeto                          *
                      ## b-tag quantities before jetcut
                      process.tightJetQualityBeforeJetCuts          *
                      process.bottomJetKinematicsBeforeJetCuts      *
                      ## monitor all jet cut quantities
                      process.monitorNMinusOneJetCuts               *
                      process.monitorJetCutflow                     *
                      ## analysis for different jet multiplicities
                      ## N_jets >= 1                    
                      process.jetMultiplicity1                      *
                      ## N_jets >= 2
                      process.jetMultiplicity2                      *
                      ## N_jets >= 3
                      process.jetMultiplicity3                      *
                      ## N_jets >= 4
                      process.jetMultiplicity4                      *
                      ## monitor btag cut quantities
                      process.monitorBtagCuts                       *
                      ## N_jets >= 4 + btag >=1                      
                      process.jetMultiplicity4Btag
                      )
## Njets>=3 & btag
process.p2 = cms.Path(
                      ## gen event selection (decay channel) and the trigger selection (hltFilter)
                      process.filterSequenceb                       *
                      ## PV event selection
                      process.PVSelectionb                          *
                      ## introduce some collections
                      process.semiLeptonicSelection                 *
                      process.isolatedGenMuons                      *
                      process.semiLeptGenCollections                *
                      ## do the event selection for muon
                      process.muonSelectionb                        *
                      ## do event selection veto cuts
                      process.secondMuonVetob                       *
                      process.electronVetob                         *
                      ## N_jets >= 3 + btag >=1
                      process.jetMultiplicity3Btag
                      )

## QCD estimation via ABCD
process.p3 = cms.Path(
                      ## gen event selection (decay channel) and trigger selection (hltFilter)
                      process.filterSequenceABCD                    *        
                      ## introduce collections
                      process.semiLeptonicSelection                 *
                      process.estimationMuons                       *
                      ## PV event selection
                      process.PVSelectionABCD                       *
                      ## lepton veto event selection cut
                      process.secondMuonVetoABCD                    *
                      process.electronVetoABCD                      *
                      ## do the event selection for ==1 muon (without dB, relIso and dR cut)
                      process.estimationMuonsSelection              *
                      ## jetcut event selection + monitoring of dB and relIso variable
                      ## a) 1 jet
                      process.leadingJetSelectionNjets1ABCD         *
                      process.estimationMuonsQualityNjets1          *
                      ## a) 2 jet
                      process.leadingJetSelectionNjets2ABCD         *
                      process.estimationMuonsQualityNjets2          *
                      ## a) 3 jet
                      process.leadingJetSelectionNjets3ABCD         *
                      process.estimationMuonsQualityNjets3          *
                      ## a) 4 jet
                      process.leadingJetSelectionNjets4ABCD         *
                      process.estimationMuonsQualityNjets4          *
                      ## do the standard muon selection
                      process.muonSelectionABCD                     
                      )

## on generator niveau
if(runningOnData=="MC"):
    print "running on Monte Carlo, gen-plots produced"
    process.p4 = cms.Path(
                          ## gen event selection: semileptonic (muon & tau->lepton)
                          process.genFilterSequence                     *
                          ## introduce some collections
                          process.isolatedGenMuons                      *
                          process.semiLeptGenCollections                *
                          ## do the event selection for muon
                          process.genMuonSelection                      *
                          ## for N_jets = 1+
                          process.leadingGenJetSelectionNjets1          *
                          process.analyzeTightMuonCrossSectionGenNjets1 *
                          ## for N_jets = 2+
                          process.leadingGenJetSelectionNjets2          *
                          process.analyzeTightMuonCrossSectionGenNjets2 *
                          ## for N_jets = 3+
                          process.leadingGenJetSelectionNjets3          *
                          process.analyzeTightMuonCrossSectionGenNjets3 *
                          ##  for N_jets = 4+
                          process.leadingGenJetSelectionNjets4          *
                          process.analyzeTightMuonCrossSectionGenNjets4 
                          )
elif(runningOnData=="data"):
    print "running on data, no gen-plots"
else:
    print "choose runningOnData= data or MC, creating no gen-plots"

## Output Module Configuration
if(writeOutput):
    from PhysicsTools.PatAlgos.patEventContent_cff import *
    process.out = cms.OutputModule("PoolOutputModule",
                                   fileName = cms.untracked.string('patTuple_selectedNjets4.root'),
                                   # save only events passing the full path
                                   SelectEvents = cms.untracked.PSet( SelectEvents = cms.vstring('p1') ),
                                   #save output (comment to keep everything...)
                                   outputCommands = cms.untracked.vstring('drop *') 
                                   )
    process.out.outputCommands += patEventContentNoCleaning
    process.out.outputCommands += patExtraAodEventContent
    process.outpath = cms.EndPath(process.out)
    
if(jetType=="particleFlow"):
    from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
    massSearchReplaceAnyInputTag(process.p1, 'tightLeadingJets', 'tightLeadingPFJets')
    massSearchReplaceAnyInputTag(process.p2, 'tightLeadingJets', 'tightLeadingPFJets')
    massSearchReplaceAnyInputTag(process.p3, 'tightLeadingJets', 'tightLeadingPFJets')

    massSearchReplaceAnyInputTag(process.p1, 'tightBottomJets', 'tightBottomPFJets')
    massSearchReplaceAnyInputTag(process.p2, 'tightBottomJets', 'tightBottomPFJets')
    massSearchReplaceAnyInputTag(process.p3, 'tightBottomJets', 'tightBottomPFJets')

    massSearchReplaceAnyInputTag(process.p1, 'goodJets', 'goodJetsPF30')
    massSearchReplaceAnyInputTag(process.p2, 'goodJets', 'goodJetsPF30')
    massSearchReplaceAnyInputTag(process.p3, 'goodJets', 'goodJetsPF30')

    massSearchReplaceAnyInputTag(process.p1, 'centralJets', 'centralJetsPF30')
    massSearchReplaceAnyInputTag(process.p2, 'centralJets', 'centralJetsPF30')
    massSearchReplaceAnyInputTag(process.p3, 'centralJets', 'centralJetsPF30')

    massSearchReplaceAnyInputTag(process.p1, 'reliableJets', 'reliableJetsPF30')
    massSearchReplaceAnyInputTag(process.p2, 'reliableJets', 'reliableJetsPF30')
    massSearchReplaceAnyInputTag(process.p3, 'reliableJets', 'reliableJetsPF30')

    massSearchReplaceAnyInputTag(process.p1, 'noEtaJets', 'noEtaJetsPF30')
    massSearchReplaceAnyInputTag(process.p2, 'noEtaJets', 'noEtaJetsPF30')
    massSearchReplaceAnyInputTag(process.p3, 'noEtaJets', 'noEtaJetsPF30')

    massSearchReplaceAnyInputTag(process.p1, 'noPtJets', 'noPtJetsPF')
    massSearchReplaceAnyInputTag(process.p2, 'noPtJets', 'noPtJetsPF')
    massSearchReplaceAnyInputTag(process.p3, 'noPtJets', 'noPtJetsPF')

    massSearchReplaceAnyInputTag(process.p1, 'patMETs', 'patMETsPF')
    massSearchReplaceAnyInputTag(process.p2, 'patMETs', 'patMETsPF')
    massSearchReplaceAnyInputTag(process.p3, 'patMETs', 'patMETsPF')
