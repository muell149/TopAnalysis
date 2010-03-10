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

useAntikt5   = True # False
writeOutput  = False # True

# analyse muon quantities
process = cms.Process("Selection")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 100

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(    

## add your favourite file here
      '/store/user/rwolf/ttbar09/patTuple_sig_0_ttbarx09.root'
    # '/store/user/henderle/OctEx/InclusiveMu15/PATtuple_1.root'
    # '/store/user/henderle/OctEx/Wmunu/PATtuple_1.root'
    # '/store/user/henderle/OctEx/Zmumu/PATtuple_1.root'
    # '/store/user/rwolf/ttbar09/patTuple_all_0_ttbar09.root''
    #  '/store/user/snaumann/firstCollisions/muTuple_Run123596.root'
    )
 )

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10000)
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

## including some muon and jet collections
from TopAnalysis.TopFilter.sequences.semiLeptonicSelection_cff import combinedMuons
process.combinedMuons = combinedMuons
#from TopAnalysis.TopFilter.sequences.semiLeptonicSelection_cff import isoMuons
#process.isoMuons = isoMuons
from TopAnalysis.TopFilter.sequences.jetSelection_cff import reliableJets
process.reliableJets = reliableJets
from TopAnalysis.TopFilter.sequences.jetSelection_cff import centralJets
process.centralJets = centralJets

## define ordered jets
uds0    = cms.PSet(index = cms.int32(0), correctionLevel = cms.string('abs'    ) )
uds1    = cms.PSet(index = cms.int32(1), correctionLevel = cms.string('abs'    ) )
uds2    = cms.PSet(index = cms.int32(2), correctionLevel = cms.string('abs'    ) )
uds3    = cms.PSet(index = cms.int32(3), correctionLevel = cms.string('abs'    ) )
bottom0 = cms.PSet(index = cms.int32(0), correctionLevel = cms.string('had:b'  ) )
bottom1 = cms.PSet(index = cms.int32(1), correctionLevel = cms.string('had:b'  ) )
uds0L5  = cms.PSet(index = cms.int32(0), correctionLevel = cms.string('had:uds') )   

## replace sisCone5 by antikt5
if( useAntikt5 ):
    process.goodJets.src = 'selectedPatJetsAK5'
    
## collect kinematics analyzers
  ## a) Muon Collection Kinematics
process.unselectedMuonKinematics  = process.analyzeMuonKinematics.clone(src = 'selectedPatMuons'              )
process.combinedMuonKinematics    = process.analyzeMuonKinematics.clone(src = 'combinedMuons'                    )
process.triggerMuonKinematics     = process.analyzeMuonKinematics.clone(src = 'triggerMuons'                     )
#process.isoMuonKinematics         = process.analyzeMuonKinematics.clone(src = 'isoMuons'                         )
process.trackMuonKinematics       = process.analyzeMuonKinematics.clone(src = 'trackMuons'                       )
process.goodMuonKinematics        = process.analyzeMuonKinematics.clone(src = 'goodMuons'                        )
process.goldenMuonKinematics      = process.analyzeMuonKinematics.clone(src = 'goldenMuons'                      )
process.tightMuonKinematics       = process.analyzeMuonKinematics.clone(src = 'tightMuons'                       )

  ## b) Veto Collection Kinematics
process.looseVetoMuonKinematics       = process.analyzeMuonKinematics.clone(src = 'looseMuons',
                                                                            analyze = cms.PSet(index = cms.int32(-1)))
process.unselectedVetoMuonKinematics  = process.analyzeMuonKinematics.clone(src = 'selectedPatMuons',
                                                                            analyze = cms.PSet(index = cms.int32(-1)))
process.looseVetoElectronKinematics      = process.analyzeElectronKinematics.clone(src = 'looseElectrons',
                                                                            analyze = cms.PSet(index = cms.int32(0)))
process.unselectedVetoElectronKinematics = process.analyzeElectronKinematics.clone(src = 'selectedPatElectrons',
                                                                            analyze = cms.PSet(index = cms.int32(0)))

  ## c) Jet Collection Kinematics before jet cuts

process.unselectedLeadingJetKinematicsBefore = process.analyzeJetKinematics.clone (src = 'selectedPatJets'                 )
process.unselectedLead_0_JetKinematicsBefore = process.analyzeJetKinematics.clone (src = 'selectedPatJets', analyze = uds0 )
process.unselectedLead_1_JetKinematicsBefore = process.analyzeJetKinematics.clone (src = 'selectedPatJets', analyze = uds1 )
process.unselectedLead_2_JetKinematicsBefore = process.analyzeJetKinematics.clone (src = 'selectedPatJets', analyze = uds2 )
process.unselectedLead_3_JetKinematicsBefore = process.analyzeJetKinematics.clone (src = 'selectedPatJets', analyze = uds3 )
process.centralLeadingJetKinematicsBefore    = process.analyzeJetKinematics.clone (src = 'centralJets'                        )
process.reliableLeadingJetKinematicsBefore   = process.analyzeJetKinematics.clone (src = 'reliableJets'                       )

process.tightLeadingJetKinematicsBefore = process.analyzeJetKinematics.clone (src = 'tightLeadingJets'                 )
process.tightLead_0_JetKinematicsBefore = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds0 )
process.tightLead_1_JetKinematicsBefore = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds1 )
process.tightLead_2_JetKinematicsBefore = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds2 )
process.tightLead_3_JetKinematicsBefore = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds3 )

process.tightBottomJetKinematicsBefore  = process.analyzeJetKinematics.clone (src = 'tightBottomJets'                  )
process.tightBJet_0_JetKinematicsBefore = process.analyzeJetKinematics.clone (src = 'tightBottomJets' , analyze = uds0 )
process.tightBJet_1_JetKinematicsBefore = process.analyzeJetKinematics.clone (src = 'tightBottomJets' , analyze = uds1 )

  ## d) Jet Collection Kinematics after jet cuts

process.unselectedLeadingJetKinematics = process.analyzeJetKinematics.clone (src = 'selectedPatJets'          )
process.unselectedLead_0_JetKinematics = process.analyzeJetKinematics.clone (src = 'selectedPatJets', analyze = uds0 )
process.unselectedLead_1_JetKinematics = process.analyzeJetKinematics.clone (src = 'selectedPatJets', analyze = uds1 )
process.unselectedLead_2_JetKinematics = process.analyzeJetKinematics.clone (src = 'selectedPatJets', analyze = uds2 )
process.unselectedLead_3_JetKinematics = process.analyzeJetKinematics.clone (src = 'selectedPatJets', analyze = uds3 )
process.centralLeadingJetKinematics    = process.analyzeJetKinematics.clone (src = 'centralJets'                 )
process.reliableLeadingJetKinematics   = process.analyzeJetKinematics.clone (src = 'reliableJets'                )

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
#process.isoMuonKinematicsAfter         = process.analyzeMuonKinematics.clone(src = 'isoMuons'                         )

process.tightLeadingJetKinematicsAfter = process.analyzeJetKinematics.clone (src = 'tightLeadingJets'                 )
process.tightLead_0_JetKinematicsAfter = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds0 )
process.tightLead_1_JetKinematicsAfter = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds1 )
process.tightLead_2_JetKinematicsAfter = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds2 )
process.tightLead_3_JetKinematicsAfter = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds3 )

process.tightBottomJetKinematicsAfter  = process.analyzeJetKinematics.clone (src = 'tightBottomJets'                  )
process.tightBJet_0_JetKinematicsAfter = process.analyzeJetKinematics.clone (src = 'tightBottomJets' , analyze = uds0 )
process.tightBJet_1_JetKinematicsAfter = process.analyzeJetKinematics.clone (src = 'tightBottomJets' , analyze = uds1 )

## choosing the Kinematic-monitoring you want to use
## to be called with semiLeptonicSelection
process.monitorMuonKinematics = cms.Sequence(process.unselectedMuonKinematics +
                                             process.combinedMuonKinematics   +
                                             process.triggerMuonKinematics    +                         
                                             process.trackMuonKinematics      +
                                             #process.isoMuonKinematics        +
                                             process.goodMuonKinematics       +
                                             process.goldenMuonKinematics     +
                                             process.tightMuonKinematics      
                                             )

process.monitorJetsKinematics = cms.Sequence(process.tightBottomJetKinematics       +
                                             process.tightLeadingJetKinematics      +
                                             process.unselectedLeadingJetKinematics +
                                             process.reliableLeadingJetKinematics   +
                                             process.centralLeadingJetKinematics    +
                                             
                                             process.tightBJet_0_JetKinematics      +
                                             process.tightBJet_1_JetKinematics      +

                                             process.tightLead_0_JetKinematics      +
                                             process.tightLead_1_JetKinematics      +
                                             process.tightLead_2_JetKinematics      +
                                             process.tightLead_3_JetKinematics      +

                                             process.unselectedLead_0_JetKinematics +
                                             process.unselectedLead_1_JetKinematics +
                                             process.unselectedLead_2_JetKinematics +
                                             process.unselectedLead_3_JetKinematics 
                                             )

process.monitorJetsKinematicsBefore = cms.Sequence(process.tightBottomJetKinematicsBefore       +
                                                   process.tightLeadingJetKinematicsBefore      +
                                                   process.unselectedLeadingJetKinematicsBefore +
                                                   process.reliableLeadingJetKinematicsBefore   +
                                                   process.centralLeadingJetKinematicsBefore    +
                                             
                                                   process.tightBJet_0_JetKinematicsBefore      +
                                                   process.tightBJet_1_JetKinematicsBefore      +
                                                   
                                                   process.tightLead_0_JetKinematicsBefore      +
                                                   process.tightLead_1_JetKinematicsBefore      +
                                                   process.tightLead_2_JetKinematicsBefore      +
                                                   process.tightLead_3_JetKinematicsBefore      +
                                                   
                                                   process.unselectedLead_0_JetKinematicsBefore +
                                                   process.unselectedLead_1_JetKinematicsBefore +
                                                   process.unselectedLead_2_JetKinematicsBefore +
                                                   process.unselectedLead_3_JetKinematicsBefore 
                                                   )

## collect quality analyzers for Muons and Jets

  ## a) Muon Collection Qualities performed before cuts
process.unselectedMuonQuality  = process.analyzeMuonQuality.clone(src = 'selectedPatMuons'              )
process.combinedMuonQuality    = process.analyzeMuonQuality.clone(src = 'combinedMuons'                    )
process.triggerMuonQuality     = process.analyzeMuonQuality.clone(src = 'triggerMuons'                     )
#process.isoMuonQuality         = process.analyzeMuonQuality.clone(src = 'isoMuons'                         )
process.trackMuonQuality       = process.analyzeMuonQuality.clone(src = 'trackMuons'                       )
process.goodMuonQuality        = process.analyzeMuonQuality.clone(src = 'goodMuons'                        )
process.goldenMuonQuality      = process.analyzeMuonQuality.clone(src = 'goldenMuons'                      )
process.tightMuonQuality       = process.analyzeMuonQuality.clone(src = 'tightMuons'                       )

  ## b) Veto Collection Qualities
process.looseVetoMuonQuality          = process.analyzeMuonQuality.clone     (src = 'looseMuons',
                                                                              analyze =cms.PSet(index = cms.int32(-1))  )
process.unselectedVetoMuonQuality     = process.analyzeMuonQuality.clone     (src = 'selectedPatMuons',
                                                                              analyze =cms.PSet(index = cms.int32(-1))  )
process.looseVetoElectronQuality      = process.analyzeElectronQuality.clone (src = 'looseElectrons',
                                                                              analyze =cms.PSet(index = cms.int32(0))  )
process.unselectedVetoElectronQuality = process.analyzeElectronQuality.clone (src = 'selectedPatElectrons',
                                                                              analyze =cms.PSet(index = cms.int32(0))  )
  ## c) Jet Collection Qualities
process.tightBottomJetQuality        = process.analyzeJetQuality.clone (src = 'tightBottomJets'                  )
process.tightLeadingJetQuality       = process.analyzeJetQuality.clone (src = 'tightLeadingJets'                 )
process.reliableLeadingJetQuality    = process.analyzeJetQuality.clone (src = 'reliableJets'                     )
process.tightMatchedBJetQuality      = process.analyzeJetQuality.clone (src = 'tightMatchedBottomJets'           )
process.tightMatchedLightQJetQuality = process.analyzeJetQuality.clone (src = 'tightMatchedLightQJets'           )

  ## d) Muon Collection Qualities performed after cuts
#process.isoMuonQualityAfter               = process.analyzeMuonQuality.clone(src = 'isoMuons'                         )
process.tightMuonQualityAfter             = process.analyzeMuonQuality.clone(src = 'tightMuons'                       )
process.tightLeadingJetQualityAfter       = process.analyzeJetQuality.clone (src = 'tightLeadingJets'                 )
process.tightBottomJetQualityAfter        = process.analyzeJetQuality.clone (src = 'tightBottomJets'                  )
process.tightLeadingJetQualityAfter       = process.analyzeJetQuality.clone (src = 'tightLeadingJets'                 )
process.tightMatchedBJetQualityAfter      = process.analyzeJetQuality.clone (src = 'tightMatchedBottomJets'           )
process.tightMatchedLightQJetQualityAfter = process.analyzeJetQuality.clone (src = 'tightMatchedLightQJets'           )

## choosing the quality-monitoring you want to use
## to be called with the *selectGoldenMuons* sequence
process.monitorMuonQuality = cms.Sequence(process.unselectedMuonQuality +
                                          process.combinedMuonQuality   +
                                          process.triggerMuonQuality    +
                                          process.trackMuonQuality      +
                                          process.goodMuonQuality       +
                                          #process.isoMuonQuality        +
                                          process.goldenMuonQuality     +
                                          process.tightMuonQuality
                                          )

process.monitorJetsQuality = cms.Sequence(process.tightBottomJetQuality        +
                                          process.reliableLeadingJetQuality    +
                                          process.tightLeadingJetQuality       +
                                          process.tightMatchedBJetQuality      +
                                          process.tightMatchedLightQJetQuality
                                          )

process.monitorVetoCollections = cms.Sequence(process.unselectedVetoMuonQuality        +
                                              process.looseVetoMuonQuality             +
                                              process.unselectedVetoMuonKinematics     +
                                              process.looseVetoMuonKinematics          +
                                              process.unselectedVetoElectronQuality    +                                              
                                              process.looseVetoElectronQuality         +
                                              process.unselectedVetoElectronKinematics +
                                              process.looseVetoElectronKinematics      
                                              )
    
## collect muon-jet analyzer

#process.unselectedMuonUnselectedJetKinematics   = process.analyzeMuonJetKinematics.clone(srcA = 'selectedPatMuons',
#                                                                                         srcB = 'selectedPatJets'  )
#process.unselectedMuonGoodJetKinematics         = process.analyzeMuonJetKinematics.clone(srcA = 'selectedPatMuons',
#                                                                                         srcB = 'goodJets'            )
process.tightMuonGoodJetKinematics              = process.analyzeMuonJetKinematics.clone(srcA = 'tightMuons',
                                                                                         srcB = 'goodJets'            )
#process.tightMuonUnselectedJetKinematics        = process.analyzeMuonJetKinematics.clone(srcA = 'goodMuons',
#                                                                                         srcB = 'selectedPatJets'  )
process.tightMuonGoodJetKinematicsAfter         = process.analyzeMuonJetKinematics.clone(srcA = 'tightMuons',
                                                                                         srcB = 'goodJets'            )

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
                                                        process.tightMatchedBJetQualityAfter           +
                                                        process.tightMatchedLightQJetQualityAfter      +
                                                        process.tightMuonGoodJetKinematicsAfter        
                                                        )

## ---
##    run the final sequence
## ---
process.p1 = cms.Path(## do the gen event selection (decay channel) and the trigger selection (hltMu9)
                      process.filterSequence                      *
                      ## introduce some collecions
                      process.semiLeptonicSelection               *
                      reliableJets                                *
                      centralJets                                 *
                      combinedMuons                               *
                      ## do the matching
                      process.matchJetsToPartons                  *
                      ## do monitoring before cuts
                      process.monitorMuonQuality                  *
                      process.monitorJetsQuality                  *
                      process.monitorJetsKinematics               *
                      process.monitorMuonKinematics               *
                      process.monitorMuonJetKinematics            *
                      ## do the complete event selection
#                      process.semiLeptonicEvents                  *  
                      ## do the event selection for muon
                      process.muonSelection                       *
                      ## monitoring for veto cut selections
                      process.monitorVetoCollections              *
                      ## do event selection veto cuts
                      process.secondMuonVeto                      *
                      process.electronVeto                        *
                      ## do the monitoring for jet quantities
                      process.monitorJetsKinematicsBefore         *
                      ## do event selection jets
                      process.leadingJetSelection                 *
                      ## do monitoring after full cuts (no btag)
                      process.monitorQualitiesAfterSelection      *
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
