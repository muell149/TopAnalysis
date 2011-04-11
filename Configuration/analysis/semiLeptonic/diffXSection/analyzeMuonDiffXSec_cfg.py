import FWCore.ParameterSet.Config as cms

## ---
##   use this file to study different distributions for measurement of differential Cross Section
##   does also a monitoring of the cuts before they are applied
## ---

## ---
##    options
## ---

## choose jet collection and corresponding MET
if(not globals().has_key('jetType')):
    jetType =  'particleFlow' # 'Calo'

# switch to run on data and remove all gen plots (type 'MC' or 'data')
if(not globals().has_key('runningOnData')): 
    runningOnData = "MC"

# choose jet correction level shown in plots
# L3Absolute for MC, L2L3Residual for data
if(not globals().has_key('corrLevel')):
    corrLevel='L3Absolute'
print "used corr.Level in jetKinematics: "+corrLevel

## run kinematic fit?
if(not globals().has_key('applyKinFit')):
   applyKinFit = True # False
if(applyKinFit==True):
    print "kinFit and top reconstruction is applied - attention: slows down!!!"
if(applyKinFit==False):
    print "kinFit and top reconstruction not applied"
    
## choose whether you want a pat tuple as output
if(not globals().has_key('writeOutput')): 
    writeOutput  = False # True
    
## remove all ttbar specific gen level filter - used by other _cfg based on this file
if(not globals().has_key('removeGenTtbar')):
    removeGenTtbar = False 
if(removeGenTtbar==True):
    print "all gen level filters using ttbar decay subset are removed" 
    if(runningOnData=="MC"):
        print "selection for gen plots only via TopAnalysis.TopFilter.sequences.genSelection_cff"

## implement anti b-tagging path
if(not globals().has_key('implement0TagPath')):
    implement0TagPath = False
if(implement0TagPath==True):
    print "path with ==0 btagged jets included" 
if(implement0TagPath==False):
    print "path with ==0 btagged jets excluded"
    
## eventfilter is to select a special ttbar decay channel from ttbarSample by genmatching (ttbar MC only, other MC: choose 'all')
if(not globals().has_key('eventFilter')):
    eventFilter  = 'signal only' # 'background only' # 'all' # 'signal only' # 'semileptonic electron only' # 'dileptonic electron only' # 'dileptonic muon only' # 'fullhadronic' # 'dileptonic muon + electron only' # 'via single tau only' # 'dileptonic via tau only'
if(runningOnData=="MC"):
    print 'chosen ttbar filter:' , eventFilter

# analyze muon quantities
process = cms.Process("Selection")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

## define input
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(    
    ## add your favourite file here
    #'/store/user/mgoerner/WJetsToLNu_TuneD6T_7TeV-madgraph-tauola/PAT_FALL10HH/148435cd71339b79cc0025730c13472a/fall10MC_100_1_iJg.root'
    #'/store/user/henderle/TTJets_TuneD6T_7TeV-madgraph-tauola/PAT_FALL10HH/6c1c00d4602477b58cef63f182ce0614/fall10MC_10_1_6nQ.root'
    #'/store/user/mgoerner/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/PAT_FALL10HH2/148435cd71339b79cc0025730c13472a/fall10MC_9_1_mFa.root'
    #'/store/user/mgoerner/Mu/PAT_Nov4RerecoL1IncludedUHH/e37a6f43ad6b01bd8486b714dc367330/DataNov4RerecoL1included_196_1_jzY.root'
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
# for all PileUp sample use "TriggerResults::REDIGI38XPU"
from HLTrigger.HLTfilters.hltHighLevel_cfi import *
process.hltFilter = hltHighLevel.clone(TriggerResultsTag = "TriggerResults::HLT", HLTPaths = ["HLT_Mu9"])
#process.hltFilter = hltHighLevel.clone(TriggerResultsTag = "TriggerResults::REDIGI38X", HLTPaths = ["HLT_Mu9"])
#process.hltFilter = hltHighLevel.clone(TriggerResultsTag = "TriggerResults::REDIGI38XPU", HLTPaths = ["HLT_Mu9"])


## semileptonic selection
process.load("TopAnalysis.TopFilter.sequences.semiLeptonicSelection_cff")
## generator matching
process.load("TopAnalysis.TopFilter.sequences.generatorMatching_cff")
## muon selection
process.load("TopAnalysis.TopFilter.sequences.muonSelection_cff")
## jet selection
process.load("TopAnalysis.TopFilter.sequences.jetSelection_cff")
## redefine veto jets to be sure it is also replaced when running on PF
from TopAnalysis.TopFilter.sequences.jetSelection_cff import goodJets
process.vetoJets.src="goodJets"
process.vetoJets.cut=''

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
## sequence without filter (only trigger selection hltFilter) - done when 'all' is chosen, removeGenTtbar=True or runningOnData = "data"
if(eventFilter=='all') or (removeGenTtbar==True) or (runningOnData=="data"):
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
uds0    = cms.PSet(index = cms.int32(0), correctionLevel = cms.string(corrLevel), useTree = cms.bool(False) )
uds1    = cms.PSet(index = cms.int32(1), correctionLevel = cms.string(corrLevel), useTree = cms.bool(False) )
uds2    = cms.PSet(index = cms.int32(2), correctionLevel = cms.string(corrLevel), useTree = cms.bool(False) )
uds3    = cms.PSet(index = cms.int32(3), correctionLevel = cms.string(corrLevel), useTree = cms.bool(False) )
udsAll  = cms.PSet(index = cms.int32(-1), correctionLevel = cms.string(corrLevel), useTree = cms.bool(False) )

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
##    Set up selection steps for different (gen)-jet multiplicities
## ---
process.leadingGenJetSelectionNjets1 = process.leadingGenJetSelection.clone (src = 'selectedGenJetCollection', minNumber = 1)
process.leadingGenJetSelectionNjets2 = process.leadingGenJetSelection.clone (src = 'selectedGenJetCollection', minNumber = 2)
process.leadingGenJetSelectionNjets3 = process.leadingGenJetSelection.clone (src = 'selectedGenJetCollection', minNumber = 3)
process.leadingGenJetSelectionNjets4 = process.leadingGenJetSelection.clone (src = 'selectedGenJetCollection', minNumber = 4)

## ---
##    configure MET analyzer
## ---
process.analyzePatMET          = process.analyzeMETCorrelations.clone(srcA = 'patMETs', srcB='tightMuons')
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
process.noEtaJetKinematics  = process.analyzeJetKinematics.clone(src = 'noEtaJets', analyze = udsAll )
process.noPtJetKinematics   = process.analyzeJetKinematics.clone(src = 'noPtJets' , analyze = udsAll )
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
    process.patJetKinematics = process.analyzeJetKinematics.clone(src = 'selectedPatJetsAK5PF', analyze = udsAll)
elif(jetType=="Calo"):
    process.patJetKinematics = process.analyzeJetKinematics.clone(src = 'selectedPatJets', analyze = udsAll)
else:
    print "unknown jetType"
process.centralLead_0_JetKinematics = process.analyzeJetKinematics.clone (src = 'centralJets', analyze = uds0 )
process.centralLead_1_JetKinematics = process.analyzeJetKinematics.clone (src = 'centralJets', analyze = uds1 )
process.centralLead_2_JetKinematics = process.analyzeJetKinematics.clone (src = 'centralJets', analyze = uds2 )
process.centralLead_3_JetKinematics = process.analyzeJetKinematics.clone (src = 'centralJets', analyze = uds3 )
process.centralJetKinematics = process.analyzeJetKinematics.clone(src = 'centralJets', analyze = udsAll)
process.reliableJetQuality   = process.analyzeJetQuality.clone   (src = 'reliableJets'   )
process.tightJetKinematics  = process.analyzeJetKinematics.clone(src = 'tightLeadingJets', analyze = udsAll)
## btag selection cuts
process.tightJetQuality     = process.analyzeJetQuality.clone   (src = 'tightLeadingJets')
process.bottomJetKinematics = process.analyzeJetKinematics.clone(src = 'tightBottomJets', analyze = udsAll)
process.bottomJetKinematicsNjets1=process.bottomJetKinematics.clone()
process.bottomJetKinematicsNjets2=process.bottomJetKinematics.clone()
process.bottomJetKinematicsNjets3=process.bottomJetKinematics.clone()
process.bottomJetKinematicsNjets4=process.bottomJetKinematics.clone()
## btag monitoring before jetcuts
process.tightJetQualityBeforeJetCuts     = process.analyzeJetQuality.clone   (src = 'tightLeadingJets')
process.bottomJetKinematicsBeforeJetCuts = process.analyzeJetKinematics.clone(src = 'tightBottomJets', analyze = udsAll)

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
                                          process.analyzePatMET
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
                                        process.analyzePatMETNjets1                   +
                                        process.bottomJetKinematicsNjets1             )
process.jetMultiplicity2 = cms.Sequence(process.leadingJetSelectionNjets2             +
                                        process.analyzeTightMuonCrossSectionRecNjets2 +
                                        process.analyzePatMETNjets2                   +
                                        process.bottomJetKinematicsNjets2             )
process.jetMultiplicity3 = cms.Sequence(process.leadingJetSelectionNjets3             +
                                        process.analyzeTightMuonCrossSectionRecNjets3 +
                                        process.analyzePatMETNjets3                   +
                                        process.bottomJetKinematicsNjets3             )
process.jetMultiplicity4 = cms.Sequence(process.leadingJetSelectionNjets4             +
                                        process.analyzeTightMuonCrossSectionRecNjets4 +
                                        process.analyzePatMETNjets4                   +
                                        process.bottomJetKinematicsNjets4             )
process.jetMultiplicity3Btag = cms.Sequence(process.leadingJetSelectionNjets3                  +
                                            process.bottomJetSelection                         +
                                            process.analyzeTightMuonCrossSectionRecNjets3Btag  +
                                            process.analyzePatMETNjets3Btag                    )
process.jetMultiplicity4Btag = cms.Sequence(process.bottomJetSelection                         +
                                            process.analyzeTightMuonCrossSectionRecNjets4Btag  +
                                            process.analyzePatMETNjets4Btag                    )

## ---
##    anti b-tag analysis
## ---
## descriminator monitoring
process.tightJetQualityBeforeAnyCuts = process.analyzeJetQuality.clone   (src = 'tightLeadingJets')
## monitoring jet kinematics
process.noPtLead_0_JetKinematicsNoBtagNjets0 = process.analyzeJetKinematics.clone (src = 'noPtJets', analyze = uds0 )
process.noPtLead_1_JetKinematicsNoBtagNjets0 = process.analyzeJetKinematics.clone (src = 'noPtJets', analyze = uds1 )
process.noPtLead_2_JetKinematicsNoBtagNjets0 = process.analyzeJetKinematics.clone (src = 'noPtJets', analyze = uds2 )
process.noPtLead_3_JetKinematicsNoBtagNjets0 = process.analyzeJetKinematics.clone (src = 'noPtJets', analyze = uds3 )
process.noPtLead_0_JetKinematicsNoBtagNjets4 = process.analyzeJetKinematics.clone (src = 'noPtJets', analyze = uds0 )
process.noPtLead_1_JetKinematicsNoBtagNjets4 = process.analyzeJetKinematics.clone (src = 'noPtJets', analyze = uds1 )
process.noPtLead_2_JetKinematicsNoBtagNjets4 = process.analyzeJetKinematics.clone (src = 'noPtJets', analyze = uds2 )
process.noPtLead_3_JetKinematicsNoBtagNjets4 = process.analyzeJetKinematics.clone (src = 'noPtJets', analyze = uds3 )
## 0 b-jets selection
process.antiBottomJetSelection = process.bottomJetSelection.clone(src = 'tightBottomJets', minNumber = 0, maxNumber = 0)
## analysis for each jet multiplicity
process.noBjetNjets1 = process.analyzeTightMuonCrossSectionRecNjets1.clone()
process.noBjetNjets2 = process.analyzeTightMuonCrossSectionRecNjets2.clone()
process.noBjetNjets3 = process.analyzeTightMuonCrossSectionRecNjets3.clone()
process.noBjetNjets4 = process.analyzeTightMuonCrossSectionRecNjets4.clone()


## collect sequences
process.antiBjetSelection = cms.Sequence(process.tightJetQualityBeforeAnyCuts +
                                         process.antiBottomJetSelection
                                         )
process.jetKinematicsAntiBNjets0 = cms.Sequence(process.noPtLead_0_JetKinematicsNoBtagNjets0 +
                                                process.noPtLead_1_JetKinematicsNoBtagNjets0 +
                                                process.noPtLead_2_JetKinematicsNoBtagNjets0 +
                                                process.noPtLead_3_JetKinematicsNoBtagNjets0 
                                                )
process.jetKinematicsAntiBNjets4 = cms.Sequence(process.noPtLead_0_JetKinematicsNoBtagNjets4 +
                                                process.noPtLead_1_JetKinematicsNoBtagNjets4 +
                                                process.noPtLead_2_JetKinematicsNoBtagNjets4 +
                                                process.noPtLead_3_JetKinematicsNoBtagNjets4    
                                                )
process.jetMultiplicity1AntiB = cms.Sequence(process.leadingJetSelectionNjets1 +                                
                                             process.noBjetNjets1
                                             )
process.jetMultiplicity2AntiB = cms.Sequence(process.leadingJetSelectionNjets2 +                                
                                             process.noBjetNjets2
                                             )
process.jetMultiplicity3AntiB = cms.Sequence(process.leadingJetSelectionNjets3 +                                
                                             process.noBjetNjets3
                                             )
process.jetMultiplicity4AntiB = cms.Sequence(process.leadingJetSelectionNjets4 +                                
                                             process.noBjetNjets4
                                             )

## ---
##    configure Kinematic fit
## ---

## produce top reconstructed event
process.load('TopQuarkAnalysis.TopEventProducers.sequences.ttSemiLepEvtBuilder_cff')
## process.ttSemiLepJetPartonMatch.verbosity = 1
process.kinFitTtSemiLepEventHypothesis.leps = 'tightMuons'
process.kinFitTtSemiLepEventHypothesis.jets = 'tightLeadingJets'
process.kinFitTtSemiLepEventHypothesis.mets = 'patMETs'

# maximum number of jets to be considered in the jet combinatorics
# (has to be >= 4, can be set to -1 if you want to take all)
process.kinFitTtSemiLepEventHypothesis.maxNJets = 5

# maximum number of jet combinations finally written into the event, starting from the "best"
# (has to be >= 1, can be set to -1 if you want to take all)
process.kinFitTtSemiLepEventHypothesis.maxNComb = 3

# set constraints:: 1: Whad-mass, 2: Wlep-mass, 3: thad-mass, 4: tlep-mass, 5: nu-mass, 6: equal t-masses
process.kinFitTtSemiLepEventHypothesis.constraints = [1, 2, 6]

# consider b-tagging in event reconstruction
process.kinFitTtSemiLepEventHypothesis.bTagAlgo = "trackCountingHighEffBJetTags"

# TCHE discr.values 7TeV: 1.7, 3.3, 10.2
process.kinFitTtSemiLepEventHypothesis.minBDiscBJets     = 1.7
process.kinFitTtSemiLepEventHypothesis.maxBDiscLightJets = 3.3
process.kinFitTtSemiLepEventHypothesis.useBTagging       = True

# add hypothesis
from TopQuarkAnalysis.TopEventProducers.sequences.ttSemiLepEvtBuilder_cff import *
addTtSemiLepHypotheses(process,['kKinFit'])
if(eventFilter=='signal only') and (runningOnData=="MC"):
    if(applyKinFit==True):
        print 'kinfit: processing ttbar SG MC - build genmatch'
else:
    removeTtSemiLepHypGenMatch(process)
    if(applyKinFit==True):
        print 'kinfit: processing bkg or data - genmatch removed'

# keep only events with unambigues parton matches
# (no other partons exist in dR=0.3 cone) 
# attention: improves purity but reduces efficiency
if(eventFilter=='signal only') and (runningOnData=="MC"):
    #process.ttSemiLepJetPartonMatch.algorithm = "unambiguousOnly"
    process.ttSemiLepJetPartonMatch.algorithm = "totalMinDist"
    process.ttSemiLepJetPartonMatch.useMaxDist = True
    # set number of jets considered in jet-parton matching
    process.ttSemiLepJetPartonMatch.maxNJets=-1
    # choose jet collection considered in jet-parton matching
    process.ttSemiLepJetPartonMatch.jets='tightLeadingJets'
    
## ---
##    configure KinFit Analyzers
## ---

## ## configure top reconstruction analyzers & define PSets
## a) for top reconstruction analyzer
process.load("TopAnalysis.TopAnalyzer.TopKinematics_cfi")
## 1) event hypothesis kinFit after reco selection
recoKinFit        = cms.PSet(hypoKey=cms.string('kKinFit'  ), useTree=cms.bool(True), matchForStabilityAndPurity=cms.bool(False), ttbarInsteadOfLepHadTop = cms.bool(False) )
process.analyzeTopRecoKinematicsKinFit = process.analyzeTopRecKinematics.clone(analyze=recoKinFit  )
## 2) event hypothesis with top quantities filled for top/antitop instead of leptonic/hadronic top
recoKinFitTopAntitop = cms.PSet(hypoKey=cms.string('kKinFit'  ), useTree=cms.bool(True), matchForStabilityAndPurity=cms.bool(False), ttbarInsteadOfLepHadTop = cms.bool(True) )
process.analyzeTopRecoKinematicsKinFitTopAntitop = process.analyzeTopRecKinematics.clone(analyze=recoKinFitTopAntitop)
## 3) event hypothesis kinFit after reco selection including match to gen objects
## 1D histograms include only events where the reconstructed and matched object are within the same bin
recoKinFitMatched = cms.PSet(hypoKey=cms.string('kKinFit'  ), useTree=cms.bool(True), matchForStabilityAndPurity=cms.bool(True ), ttbarInsteadOfLepHadTop = cms.bool(False) )
process.analyzeTopRecoKinematicsKinFitMatched = process.analyzeTopRecKinematics.clone(analyze=recoKinFitMatched )
## 4) event hypothesis built of objects from genmatch to partons (ttSemiLepJetPartonMatch) after reco selection
recoGenMatch      = cms.PSet(hypoKey=cms.string('kGenMatch'), useTree=cms.bool(True), matchForStabilityAndPurity=cms.bool(False), ttbarInsteadOfLepHadTop = cms.bool(False) )
process.analyzeTopRecoKinematicsGenMatch      = process.analyzeTopRecKinematics.clone(analyze=recoGenMatch)
## 5) event hypothesis built with generator truth informations
## as reconstructed from generator objects after gen selection
genTtbarSemiMu    = cms.PSet(hypoKey=cms.string("None"     ), useTree=cms.bool(True), matchForStabilityAndPurity=cms.bool(False), ttbarInsteadOfLepHadTop = cms.bool(False) )
process.analyzeTopGenLevelKinematics = process.analyzeTopGenKinematics.clone(analyze=genTtbarSemiMu)

## configure Kin Fit performance analyzers
process.load("TopAnalysis.TopAnalyzer.HypothesisKinFit_cfi"    )
hypoKinFit = cms.PSet(hypoKey = cms.string("kKinFit"),
                      wantTree = cms.bool(True),
                      maxNJets = process.kinFitTtSemiLepEventHypothesis.maxNJets)
process.analyzeHypoKinFit = process.analyzeHypothesisKinFit.clone(analyze=hypoKinFit)
#process.load("TopAnalysis.TopAnalyzer.HypothesisKinFitMET_cfi" )
#process.analyzeHypoKinFitMET  = process.analyzeHypothesisKinFitMET.clone (srcA = "ttSemiLepEvent", srcB = "patMETs"         )
#process.load("TopAnalysis.TopAnalyzer.HypothesisKinFitJets_cfi")
#process.analyzeHypoKinFitJets = process.analyzeHypothesisKinFitJets.clone(srcA = "ttSemiLepEvent", srcB = "tightLeadingJets")
#process.load("TopAnalysis.TopAnalyzer.HypothesisKinFitMuon_cfi")
#process.analyzeHypoKinFitMuon = process.analyzeHypothesisKinFitMuon.clone(srcA = "ttSemiLepEvent", srcB = "tightMuons"      )

## ---
##    collect KinFit Analyzers depending on sample processed
## ---
## dummy to avoid empty sequences
process.dummy = process.hltFilter.clone()
## check if kinFit should be included in main path
if(applyKinFit==True):
    ## case 1: MC sample
    if(runningOnData=="MC"):
        ## case 1a): ttbar semileptonic mu-signal
        if(eventFilter=='signal only'):
            process.kinFit    = cms.Sequence(process.makeTtSemiLepEvent                    +
                                             process.analyzeTopRecoKinematicsKinFit        +
                                             process.analyzeTopRecoKinematicsKinFitTopAntitop+
                                             process.analyzeTopRecoKinematicsKinFitMatched +
                                             process.analyzeTopRecoKinematicsGenMatch      +
                                             process.analyzeHypoKinFit                      
                                             )
            process.kinFitGen = cms.Sequence(process.analyzeTopGenLevelKinematics)
        ## case 1b): other MC
        else:
            process.kinFit    = cms.Sequence(process.makeTtSemiLepEvent                      +
                                             process.analyzeTopRecoKinematicsKinFitTopAntitop+
                                             process.analyzeTopRecoKinematicsKinFit
                                             )
            process.kinFitGen = cms.Sequence(process.dummy)
    ## case 2: data sample
    elif(runningOnData=="data"):
        process.kinFit    = cms.Sequence(process.makeTtSemiLepEvent                    +
                                         process.analyzeTopRecoKinematicsKinFit        +
                                         process.analyzeTopRecoKinematicsKinFitTopAntitop)
        process.kinFitGen = cms.Sequence(process.dummy)
    else:
         print "choose runningOnData= data or MC"
else:
    process.kinFit    = cms.Sequence(process.dummy)
    process.kinFitGen = cms.Sequence(process.dummy)

## ---
##    run the final sequences
## ---
## standard sequence for cross section analyis and detailed cut monitoring
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
                      ## veto on additional leptons
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
                      process.jetMultiplicity4Btag                  *
                      ## apply kinematic fit
                      process.kinFit
                      )
if(applyKinFit==False or eventFilter!="signal only"):
    process.p1.remove(process.dummy)
if(runningOnData=="data"):
    process.p1.remove(process.isolatedGenMuons)
    process.p1.remove(process.semiLeptGenCollections)
    
## Njets>=3 & btag
process.p2 = cms.Path(
                      ## gen event selection (decay channel) and the trigger selection (hltFilter)
                      process.filterSequence                        *
                      ## PV event selection
                      process.PVSelection                           *
                      ## introduce some collections
                      process.semiLeptonicSelection                 *
                      process.isolatedGenMuons                      *
                      process.semiLeptGenCollections                *
                      ## do the event selection for muon
                      process.muonSelection                         *
                      ## do event selection veto cuts
                      process.secondMuonVeto                        *
                      process.electronVeto                          *
                      ## N_jets >= 3 + btag >=1
                      process.jetMultiplicity3Btag
                      )
if(runningOnData=="data"):
    process.p2.remove(process.isolatedGenMuons)
    process.p2.remove(process.semiLeptGenCollections)
## anti-btag-selection to get W+jets estimation
if(implement0TagPath==True):
    process.p3 = cms.Path(
                          ## gen event selection (decay channel) and the trigger selection (hltFilter)
                          process.filterSequence                        *
                          ## PV event selection
                          process.PVSelection                           *
                          ## introduce some collections
                          process.semiLeptonicSelection                 *
                          process.semiLeptGenCollections                *
                          ## anti b-jet selection
                          process.antiBjetSelection                     *
                          ## do the event selection for muon
                          process.muonSelection                         *
                          ## veto on additional leptons
                          process.secondMuonVeto                        *
                          process.electronVeto                          *
                          ## monitor jet kinematics before jet cuts
                          process.jetKinematicsAntiBNjets0              *
                          ## do std analyis for each jet multiplicity
                          process.jetMultiplicity1AntiB                 *
                          process.jetMultiplicity2AntiB                 *
                          process.jetMultiplicity3AntiB                 *
                          process.jetMultiplicity4AntiB                 *
                          ## monitor jet kinematics after jet cuts
                          process.jetKinematicsAntiBNjets4              
                          )
if(runningOnData=="data"):
    process.p3.remove(process.semiLeptGenCollections)
## std analysis with generator objects as input for efficiency determination
if(runningOnData=="MC"):
    print "running on Monte Carlo, gen-plots produced"
    process.s4 = cms.Sequence(
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
                              process.analyzeTightMuonCrossSectionGenNjets4 *
                              ## investigate top reconstruction
                              process.kinFitGen
                              )
    process.p4 = cms.Path(
                          ## gen event selection: semileptonic (muon & tau->lepton)
                          process.genFilterSequence *
                          ## sequence with gen selection and histograms
                          process.s4
                          )
    ## delete gen filter
    if(removeGenTtbar==True):    
        process.p4.remove(process.genFilterSequence)
    ## delete dummy sequence
    if(applyKinFit==False or eventFilter!="signal only"):        
        process.p4.remove(process.dummy)
    
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
    if(implement0TagPath==True):
        pathlist = [process.p1, process.p2, process.p3]
    else:
        pathlist = [process.p1, process.p2]
    for path in pathlist:  
        massSearchReplaceAnyInputTag(path, 'tightLeadingJets', 'tightLeadingPFJets')
        massSearchReplaceAnyInputTag(path, 'tightBottomJets' , 'tightBottomPFJets')
        massSearchReplaceAnyInputTag(path, 'goodJets'        , 'goodJetsPF30')
        massSearchReplaceAnyInputTag(path, 'centralJets'     , 'centralJetsPF30')
        massSearchReplaceAnyInputTag(path, 'reliableJets'    , 'reliableJetsPF30')
        massSearchReplaceAnyInputTag(path, 'noEtaJets'       , 'noEtaJetsPF30')
        massSearchReplaceAnyInputTag(path, 'noPtJets'        , 'noPtJetsPF')
        massSearchReplaceAnyInputTag(path, 'patMETs'         , 'patMETsPF')
