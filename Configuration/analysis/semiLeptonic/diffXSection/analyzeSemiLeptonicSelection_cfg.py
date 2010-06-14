import FWCore.ParameterSet.Config as cms

## ---
##   use this file to collect different Informations about the Quality, 
##   Kinematics and other properties of the Muon and the jets in ttbar
##   semileptonic decay with Muon (also for some backgroundsamples)
## ---

## ---
##    plots are for leading, 2nd lead, ..., all muons/jets- dependend on the coresponding cfi-file
##    eventfilter is to get a special ttbar decay channel from ttbarSample by genmatching
##    decide whether to run on:
# 'background only' # 'all' # 'signal only' # 'semileptonic electron only' # 'dileptonic electron only' # 'dileptonic muon only' # 'fullhadronic' # 'dileptonic muon + electron only' # 'via single tau only' # 'dileptonic via tau only'
##    careful: genmatched selection- might cause problems for specific BG samples like qcd or data - use 'all' for them
##    signal is semileptonic with mu
##    background is ttbar other channels
##    'all' does no selection

## ---
eventFilter  = 'all'
## choose between # 'background only' # 'all' # 'signal only' # 'semileptonic electron only' # 'dileptonic electron only' # 'dileptonic muon only' # 'fullhadronic' # 'dileptonic muon + electron only' # 'via single tau only' # 'dileptonic via tau only'

writeOutput  = False # True
    
# analyse muon quantities
process = cms.Process("Selection")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(    

## add your favourite file here
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_10_1.root'
    '/store/user/snaumann/sync/patTuple_afterStep2_1_1.root'
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
    fileName = cms.string('analyzeSemiLeptonicSelection_test.root')
)

## std sequence to produce the ttGenEvt
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")
## high level trigger filter
process.load("TopAnalysis.TopFilter.sequences.triggerFilter_cff")
process.hltMu9.TriggerResultsTag = "TriggerResults::REDIGI"

## filter for different ttbar decay channels
process.load("TopQuarkAnalysis.TopEventProducers.producers.TtDecaySelection_cfi")
process.ttSemiLeptonicFilter = process.ttDecaySelection.clone()
process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.muon = True
process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchB.muon = False

if(not eventFilter=='all'):
    ## adapt output filename
    if(eventFilter=='signal only'):
        process.TFileService.fileName = 'analyzeSemiLeptonicSelection_sig.root'
    elif(eventFilter=='background only'):
        process.ttSemiLeptonicFilter.invert = True
        process.TFileService.fileName = 'analyzeSemiLeptonicSelection_bkg.root'
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
    
    ## sequence with filter for decay channel and trigger selection hltMu9

    process.filterSequence = cms.Sequence(process.makeGenEvt *
                                          process.ttSemiLeptonicFilter *
                                          process.hltMu9
                                          )
else:
    ## sequence without filter (only trigger selection hltMu9) - done when 'all' is chosen
    process.filterSequence = cms.Sequence(process.hltMu9)

## ---
##    configure the cutflow scenario
## ---

## jet quality analyzer
process.load("TopAnalysis.TopAnalyzer.JetQuality_cfi")
## muon quality analyzer
process.load("TopAnalysis.TopAnalyzer.MuonQuality_cfi")
## jet kinematics analyzer
process.load("TopAnalysis.TopAnalyzer.JetKinematics_cfi")
## muon kinematics analyzer
process.load("TopAnalysis.TopAnalyzer.MuonKinematics_cfi")
## muon jet kinematics analyzer
process.load("TopAnalysis.TopAnalyzer.MuonJetKinematics_cfi")
## semileptonic selection
process.load("TopAnalysis.TopFilter.sequences.semiLeptonicSelection_cff")
## generator matching
process.load("TopAnalysis.TopFilter.sequences.generatorMatching_cff")
## jet selection
process.load("TopAnalysis.TopFilter.sequences.jetSelection_cff")
## muon selection
process.load("TopAnalysis.TopFilter.sequences.muonSelection_cff")
## electron kinematics analyzer
process.load("TopAnalysis.TopAnalyzer.ElectronKinematics_cfi")
## electron quality analyzer
process.load("TopAnalysis.TopAnalyzer.ElectronQuality_cfi")

## ---
##    set up vertex filter
## ---
process.PVSelection = cms.EDFilter("VertexSelector",
                                   src = cms.InputTag("offlinePrimaryVertices"),
                                   cut = cms.string("!isFake && ndof > 4 && abs(z) < 15 && position.Rho < 2"),
                                   filter = cms.bool(True),
                                   )

## define ordered jets
uds0    = cms.PSet(index = cms.int32(0), correctionLevel = cms.string('abs'    ) )
uds1    = cms.PSet(index = cms.int32(1), correctionLevel = cms.string('abs'    ) )
uds2    = cms.PSet(index = cms.int32(2), correctionLevel = cms.string('abs'    ) )
uds3    = cms.PSet(index = cms.int32(3), correctionLevel = cms.string('abs'    ) )
bottom0 = cms.PSet(index = cms.int32(0), correctionLevel = cms.string('had:b'  ) )
bottom1 = cms.PSet(index = cms.int32(1), correctionLevel = cms.string('had:b'  ) )
uds0L5  = cms.PSet(index = cms.int32(0), correctionLevel = cms.string('had:uds') )   

## collect kinematics analyzers
  ## a) Muon Collection Kinematics
process.patMuonKinematics              = process.analyzeMuonKinematics.clone(src = 'cleanPatMuons'         )
process.standAloneMuonKinematics       = process.analyzeMuonKinematics.clone(src = 'standAloneMuons'       )
process.combinedMuonKinematics         = process.analyzeMuonKinematics.clone(src = 'combinedMuons'         )
process.triggerMuonKinematics          = process.analyzeMuonKinematics.clone(src = 'triggerMuons'          )
process.trackMuonKinematics            = process.analyzeMuonKinematics.clone(src = 'trackMuons'            )
process.goldenMuonsMuonKinematics      = process.analyzeMuonKinematics.clone(src = 'goldenMuons'           )
process.tightMuonKinematics            = process.analyzeMuonKinematics.clone(src = 'tightMuons'            )

  ## b) Veto Collection Kinematics
process.looseVetoMuonKinematics           = process.analyzeMuonKinematics.clone(src = 'looseMuons',
                                                                                analyze = cms.PSet(index = cms.int32(-1)))
process.looseVetoElectronKinematics       = process.analyzeElectronKinematics.clone(src = 'looseElectrons',
                                                                                    analyze = cms.PSet(index = cms.int32(0)))
process.patVetoMuonKinematics     = process.analyzeMuonKinematics.clone    (src = 'cleanPatMuons',
                                                                            analyze = cms.PSet(index = cms.int32(-1)))
process.patVetoElectronKinematics = process.analyzeElectronKinematics.clone(src = 'cleanPatElectrons',
                                                                            analyze = cms.PSet(index = cms.int32(0)))

  ## c) Jet Collection Kinematics before jet cuts

process.patLeadingJetKinematicsBefore = process.analyzeJetKinematics.clone (src = 'cleanPatJets'                 )
process.patLead_0_JetKinematicsBefore = process.analyzeJetKinematics.clone (src = 'cleanPatJets', analyze = uds0 )
process.patLead_1_JetKinematicsBefore = process.analyzeJetKinematics.clone (src = 'cleanPatJets', analyze = uds1 )
process.patLead_2_JetKinematicsBefore = process.analyzeJetKinematics.clone (src = 'cleanPatJets', analyze = uds2 )
process.patLead_3_JetKinematicsBefore = process.analyzeJetKinematics.clone (src = 'cleanPatJets', analyze = uds3 )

process.tightLeadingJetKinematicsBefore = process.analyzeJetKinematics.clone (src = 'tightLeadingJets'                 )
process.tightLead_0_JetKinematicsBefore = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds0 )
process.tightLead_1_JetKinematicsBefore = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds1 )
process.tightLead_2_JetKinematicsBefore = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds2 )
process.tightLead_3_JetKinematicsBefore = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds3 )

process.tightBottomJetKinematicsBefore  = process.analyzeJetKinematics.clone (src = 'tightBottomJets'                  )
process.tightBJet_0_JetKinematicsBefore = process.analyzeJetKinematics.clone (src = 'tightBottomJets' , analyze = uds0 )
process.tightBJet_1_JetKinematicsBefore = process.analyzeJetKinematics.clone (src = 'tightBottomJets' , analyze = uds1 )

  ## d) Jet Collection Kinematics after jet cuts

process.patLeadingJetKinematics = process.analyzeJetKinematics.clone (src = 'cleanPatJets'          )
process.patLead_0_JetKinematics = process.analyzeJetKinematics.clone (src = 'cleanPatJets', analyze = uds0 )
process.patLead_1_JetKinematics = process.analyzeJetKinematics.clone (src = 'cleanPatJets', analyze = uds1 )
process.patLead_2_JetKinematics = process.analyzeJetKinematics.clone (src = 'cleanPatJets', analyze = uds2 )
process.patLead_3_JetKinematics = process.analyzeJetKinematics.clone (src = 'cleanPatJets', analyze = uds3 )

process.tightLeadingJetKinematics = process.analyzeJetKinematics.clone (src = 'tightLeadingJets'                 )
process.tightLead_0_JetKinematics = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds0 )
process.tightLead_1_JetKinematics = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds1 )
process.tightLead_2_JetKinematics = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds2 )
process.tightLead_3_JetKinematics = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds3 )

process.tightBottomJetKinematics  = process.analyzeJetKinematics.clone (src = 'tightBottomJets'                  )
process.tightBJet_0_JetKinematics = process.analyzeJetKinematics.clone (src = 'tightBottomJets' , analyze = uds0 )
process.tightBJet_1_JetKinematics = process.analyzeJetKinematics.clone (src = 'tightBottomJets' , analyze = uds1 )

  ## e) Muon and Jet Collection Kinematics for monitoring after all cuts
process.tightMuonKinematicsAfter       = process.analyzeMuonKinematics.clone(src = 'tightMuons'                       )

process.tightLeadingJetKinematicsAfter = process.analyzeJetKinematics.clone (src = 'tightLeadingJets'                 )
process.tightLead_0_JetKinematicsAfter = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds0 )
process.tightLead_1_JetKinematicsAfter = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds1 )
process.tightLead_2_JetKinematicsAfter = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds2 )
process.tightLead_3_JetKinematicsAfter = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds3 )

process.tightBottomJetKinematicsAfter  = process.analyzeJetKinematics.clone (src = 'tightBottomJets'                  )
process.tightBJet_0_JetKinematicsAfter = process.analyzeJetKinematics.clone (src = 'tightBottomJets' , analyze = uds0 )
process.tightBJet_1_JetKinematicsAfter = process.analyzeJetKinematics.clone (src = 'tightBottomJets' , analyze = uds1 )

## choosing the Kinematic-monitoring you want to use
process.monitorMuonKinematics = cms.Sequence(process.patMuonKinematics +
                                             process.combinedMuonKinematics    +
                                             process.standAloneMuonKinematics  +
                                             process.triggerMuonKinematics     +                         
                                             process.trackMuonKinematics       +
                                             process.goldenMuonsMuonKinematics +
                                             process.tightMuonKinematics      
                                             )

process.monitorJetsKinematics = cms.Sequence(process.tightBottomJetKinematics       +
                                             process.tightLeadingJetKinematics      +
                                             process.patLeadingJetKinematics +
                                                                                         
                                             process.tightBJet_0_JetKinematics      +
                                             process.tightBJet_1_JetKinematics      +

                                             process.tightLead_0_JetKinematics      +
                                             process.tightLead_1_JetKinematics      +
                                             process.tightLead_2_JetKinematics      +
                                             process.tightLead_3_JetKinematics      +

                                             process.patLead_0_JetKinematics +
                                             process.patLead_1_JetKinematics +
                                             process.patLead_2_JetKinematics +
                                             process.patLead_3_JetKinematics 
                                             )

process.monitorJetsKinematicsBefore = cms.Sequence(process.tightBottomJetKinematicsBefore       +
                                                   process.tightLeadingJetKinematicsBefore      +
                                                   process.patLeadingJetKinematicsBefore        +
                                                   
                                                   process.tightBJet_0_JetKinematicsBefore      +
                                                   process.tightBJet_1_JetKinematicsBefore      +
                                                   
                                                   process.tightLead_0_JetKinematicsBefore      +
                                                   process.tightLead_1_JetKinematicsBefore      +
                                                   process.tightLead_2_JetKinematicsBefore      +
                                                   process.tightLead_3_JetKinematicsBefore      +
                                                   
                                                   process.patLead_0_JetKinematicsBefore +
                                                   process.patLead_1_JetKinematicsBefore +
                                                   process.patLead_2_JetKinematicsBefore +
                                                   process.patLead_3_JetKinematicsBefore 
                                                   )

## collect quality analyzers for Muons and Jets

  ## a) Muon Collection Qualities performed before cuts
process.patMuonQuality              = process.analyzeMuonQuality.clone(src = 'cleanPatMuons'         )
process.standAloneMuonQuality       = process.analyzeMuonQuality.clone(src = 'standAloneMuons'       )
process.combinedMuonQuality         = process.analyzeMuonQuality.clone(src = 'combinedMuons'         )
process.triggerMuonQuality          = process.analyzeMuonQuality.clone(src = 'triggerMuons'          )
process.trackMuonQuality            = process.analyzeMuonQuality.clone(src = 'trackMuons'            )
process.goldenMuonsMuonQuality      = process.analyzeMuonQuality.clone(src = 'goldenMuons'           )
process.tightMuonQuality            = process.analyzeMuonQuality.clone(src = 'tightMuons'            )

  ## b) Veto Collection Qualities
process.looseVetoMuonQuality   = process.analyzeMuonQuality.clone(src = 'looseMuons',
                                                                  analyze =cms.PSet(index = cms.int32(-1)) )
process.patVetoMuonQuality     = process.analyzeMuonQuality.clone(src = 'cleanPatMuons',
                                                                  analyze =cms.PSet(index = cms.int32(-1)) )
process.looseVetoElectronQuality = process.analyzeElectronQuality.clone(src = 'looseElectrons',
                                                                        analyze =cms.PSet(index = cms.int32(0))  )
process.patVetoElectronQuality   = process.analyzeElectronQuality.clone(src = 'cleanPatElectrons',
                                                                        analyze =cms.PSet(index = cms.int32(0))  )
  ## c) Jet Collection Qualities
process.tightBottomJetQuality        = process.analyzeJetQuality.clone (src = 'tightBottomJets'  )
process.tightLeadingJetQuality       = process.analyzeJetQuality.clone (src = 'tightLeadingJets' )

  ## d) Muon Collection Qualities performed after cuts
process.tightMuonQualityAfter             = process.analyzeMuonQuality.clone(src = 'tightMuons'       )
process.tightLeadingJetQualityAfter       = process.analyzeJetQuality.clone (src = 'tightLeadingJets' )
process.tightBottomJetQualityAfter        = process.analyzeJetQuality.clone (src = 'tightBottomJets'  )

## choosing the quality-monitoring you want to use
process.monitorMuonQuality = cms.Sequence(process.patMuonQuality         +
                                          process.combinedMuonQuality    +
                                          process.standAloneMuonQuality  +
                                          process.triggerMuonQuality     +                         
                                          process.trackMuonQuality       +
                                          process.goldenMuonsMuonQuality +
                                          process.tightMuonQuality      
                                          )

process.monitorJetsQuality = cms.Sequence(process.tightBottomJetQuality        +
                                          process.tightLeadingJetQuality       
                                          )

process.monitorVetoCollections = cms.Sequence(process.patVetoMuonQuality        +
                                              process.looseVetoMuonQuality      +
                                              process.patVetoMuonKinematics     +
                                              process.looseVetoMuonKinematics   +
                                              process.patVetoElectronQuality    +                                              
                                              process.looseVetoElectronQuality  +
                                              process.patVetoElectronKinematics +
                                              process.looseVetoElectronKinematics      
                                              )

## collect muon-jet analyzer

process.patMuonPatJetKinematics    = process.analyzeMuonJetKinematics.clone(srcA = 'cleanPatMuons',
                                                                            srcB = 'cleanPatJets'   )
process.patMuonGoodJetKinematics   = process.analyzeMuonJetKinematics.clone(srcA = 'cleanPatMuons',
                                                                            srcB = 'goodJets'       )
process.tightMuonGoodJetKinematics = process.analyzeMuonJetKinematics.clone(srcA = 'tightMuons',
                                                                            srcB = 'goodJets'       )
process.tightMuonPatJetKinematics  = process.analyzeMuonJetKinematics.clone(srcA = 'goodMuons',
                                                                            srcB = 'cleanPatJets'   )
process.tightMuonGoodJetKinematicsAfter = process.analyzeMuonJetKinematics.clone(srcA = 'tightMuons',
                                                                                 srcB = 'goodJets'  )

## choosing the muon-jet analyzer you want to use 

process.monitorMuonJetKinematics= cms.Sequence(process.tightMuonGoodJetKinematics)
                               
## collect analyzers to investigate properties after event selection

process.monitorQualitiesAfterSelection = cms.Sequence(  process.tightMuonKinematicsAfter               +
                                                        process.tightMuonQualityAfter                  +
                                                        process.tightLeadingJetQualityAfter            +
                                                        process.tightLeadingJetKinematicsAfter         +
                                                        process.tightBottomJetKinematicsAfter          +
                                                        process.tightBottomJetQualityAfter             +
                                                        process.tightLead_0_JetKinematicsAfter         +
                                                        process.tightLead_1_JetKinematicsAfter         +
                                                        process.tightLead_2_JetKinematicsAfter         +
                                                        process.tightLead_3_JetKinematicsAfter         +
                                                        process.tightBJet_0_JetKinematicsAfter         +
                                                        process.tightBJet_1_JetKinematicsAfter         +                     
                                                        process.tightMuonGoodJetKinematicsAfter        
                                                        )

## collect Muon N-1 Collection plots
process.noDbMuonsQuality          = process.analyzeMuonQuality.clone   (src = 'noDbMuons'        )
process.noChi2MuonQuality         = process.analyzeMuonQuality.clone   (src = 'noChi2Muons'      )
process.noTrkHitsMuonQuality      = process.analyzeMuonQuality.clone   (src = 'noTrkHitsMuons'   )
process.noIsoMuonQuality          = process.analyzeMuonQuality.clone   (src = 'noIsoMuons'       )
process.noEtaMuonKinematics       = process.analyzeMuonKinematics.clone(src = 'noEtaMuons'       )
process.noPtMuonKinematics        = process.analyzeMuonKinematics.clone(src = 'noPtMuons'        )
process.noDRMuonVetoJetsKinematics = process.analyzeMuonJetKinematics.clone(srcA = 'noDRMuons',
                                                                            srcB = 'vetoJets'    )
process.noEtaJetsKinematics     = process.analyzeJetKinematics.clone(src = 'noEtaJets'    )
process.noPtJetsKinematics      = process.analyzeJetKinematics.clone(src = 'noPtJets'     )
process.noEmJetsQuality         = process.analyzeJetQuality.clone   (src = 'noEmJets'     )
process.noN90HitsJetsKinematics = process.analyzeJetKinematics.clone(src = 'noN90HitsJets')
process.nofHPDJetsKinematics    = process.analyzeJetKinematics.clone(src = 'nofHPDJets'   )

process.monitorNMinusOne = cms.Sequence(process.noDbMuonsQuality           +
                                        process.noChi2MuonQuality          +
                                        process.noTrkHitsMuonQuality       +
                                        process.noIsoMuonQuality           +
                                        process.noEtaMuonKinematics        +
                                        process.noPtMuonKinematics         +
                                        process.noDRMuonVetoJetsKinematics +
                                        process.noEtaJetsKinematics        +
                                        process.noPtJetsKinematics         +
                                        process.noEmJetsQuality            +
                                        process.noN90HitsJetsKinematics    +
                                        process.nofHPDJetsKinematics
                                        )

## ---
##    Set up selection steps for muon selection
## ---
process.combinedMuonsSelection        = process.muonSelection.clone (src = 'combinedMuons'       , minNumber = 1, maxNumber = 999999)
process.triggerMuonsSelection         = process.muonSelection.clone (src = 'triggerMuons'        , minNumber = 1, maxNumber = 999999)
process.trackMuonsSelection           = process.muonSelection.clone (src = 'trackMuons'          , minNumber = 1, maxNumber = 999999)
process.goodMuonsSelection            = process.muonSelection.clone (src = 'goodMuons'           , minNumber = 1, maxNumber = 999999)
process.goldenMuonsSelection          = process.muonSelection.clone (src = 'goldenMuons'         , minNumber = 1, maxNumber = 999999)
process.tightMuonsSelection           = process.muonSelection.clone (src = 'tightMuons'          , minNumber = 1, maxNumber = 999999)

process.muonCuts = cms.Sequence(process.combinedMuonsSelection        +
                                process.triggerMuonsSelection         +
                                process.trackMuonsSelection           +
                                process.goodMuonsSelection            +
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

process.jetCuts = cms.Sequence(process.leadingJetSelectionNjets1 +
                               process.leadingJetSelectionNjets2 +
                               process.leadingJetSelectionNjets3 +
                               process.leadingJetSelectionNjets4 
                               )
## ---
##    run the final sequence
## ---
process.p1 = cms.Path(## do the gen event selection (decay channel) and the trigger selection (hltMu9)
                      process.filterSequence                      *
                      ## do the PV event selection
                      process.PVSelection                         *
                      ## introduce collecions   
                      process.semiLeptonicSelection               *                   
                      process.selectNMinusOneJets                 *
                      process.selectNMinusOneMuons                *
                      ## do monitoring before cuts
#                      process.monitorMuonQuality                  *
#                      process.monitorJetsQuality                  *
#                      process.monitorJetsKinematics               *
#                      process.monitorMuonKinematics               *
#                      process.monitorMuonJetKinematics            *
#                      process.monitorNMinusOne                    *
                      ## do the complete event selection
#                      process.semiLeptonicEvents                  *  
                      ## do the event selection for muon step by step
                      process.muonCuts                            *
                      ## monitoring for veto cut selections
#                      process.monitorVetoCollections              *
                      ## do event selection veto cuts
                      process.secondMuonVeto                      *
                      process.electronVeto                        *
                      ## do the monitoring for jet quantities
#                      process.monitorJetsKinematicsBefore         *
                      ## do the event selection for jets step by step
                      process.jetCuts                             *
                      ## do monitoring after full cuts (no btag)
#                      process.monitorQualitiesAfterSelection      *
                      ## btag
                      process.bottomJetSelection
                      )

## Output Module Configuration
if(writeOutput):
    process.out = cms.OutputModule("PoolOutputModule",
                                   fileName = cms.untracked.string('patTuple_selected.root'),
                                   # save only events passing the full path
                                   SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p1') ),
                                   #save output (comment to keep everything...)
                                   #outputCommands = cms.untracked.vstring('drop *',) 
                                   )
    process.outpath = cms.EndPath(process.out)
