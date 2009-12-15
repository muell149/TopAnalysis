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
    input = cms.untracked.int32(100)
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

## including some muon and jet collections
from TopAnalysis.TopFilter.sequences.semiLeptonicSelection_cff import combinedMuons
process.combinedMuons = combinedMuons
from TopAnalysis.TopFilter.sequences.semiLeptonicSelection_cff import isoMuons
process.isoMuons = isoMuons
from TopAnalysis.TopFilter.sequences.semiLeptonicSelection_cff import mipTightMuons
process.mipTightMuons = mipTightMuons
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
    process.goodJets.src = 'selectedLayer1JetsAK5'
    
## collect kinematics analyzers
process.trackMuonKinematics       = process.analyzeMuonKinematics.clone(src = 'trackMuons'                       )
process.looseMuonKinematics       = process.analyzeMuonKinematics.clone(src = 'looseMuons'                       )
process.isoMuonKinematics         = process.analyzeMuonKinematics.clone(src = 'isoMuons'                         )
process.tightMuonKinematics       = process.analyzeMuonKinematics.clone(src = 'tightMuons'                       )
process.goldenMuonKinematics      = process.analyzeMuonKinematics.clone(src = 'goldenMuons'                      )
process.goodMuonKinematics        = process.analyzeMuonKinematics.clone(src = 'goodMuons'                        )
process.combinedMuonKinematics    = process.analyzeMuonKinematics.clone(src = 'combinedMuons'                    )
process.unselectedMuonKinematics  = process.analyzeMuonKinematics.clone(src = 'selectedLayer1Muons'              )
process.triggerMuonKinematics     = process.analyzeMuonKinematics.clone(src = 'triggerMuons'                     )
process.tightBottomJetKinematics  = process.analyzeJetKinematics.clone (src = 'tightBottomJets'                  )
process.tightLeadingJetKinematics = process.analyzeJetKinematics.clone (src = 'tightLeadingJets'                 )
process.tightLead_0_JetKinematics = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds0 )
process.tightLead_1_JetKinematics = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds1 )
process.tightLead_2_JetKinematics = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds2 )
process.tightLead_3_JetKinematics = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds3 )
process.tightBJet_0_JetKinematics = process.analyzeJetKinematics.clone (src = 'tightBottomJets' , analyze = uds0 )
process.tightBJet_1_JetKinematics = process.analyzeJetKinematics.clone (src = 'tightBottomJets' , analyze = uds1 )
process.unselectedLeadingJetKinematics = process.analyzeJetKinematics.clone (src = 'selectedLayer1Jets'          )
process.centralLeadingJetKinematics    = process.analyzeJetKinematics.clone (src = 'centralJets'                 )
process.reliableLeadingJetKinematics   = process.analyzeJetKinematics.clone (src = 'reliableJets'                )
process.unselectedLead_0_JetKinematics = process.analyzeJetKinematics.clone (src = 'selectedLayer1Jets', analyze = uds0 )
process.unselectedLead_1_JetKinematics = process.analyzeJetKinematics.clone (src = 'selectedLayer1Jets', analyze = uds1 )
process.unselectedLead_2_JetKinematics = process.analyzeJetKinematics.clone (src = 'selectedLayer1Jets', analyze = uds2 )
process.unselectedLead_3_JetKinematics = process.analyzeJetKinematics.clone (src = 'selectedLayer1Jets', analyze = uds3 )

process.tightMuonKinematicsAfter       = process.analyzeMuonKinematics.clone(src = 'tightMuons'                       )
process.isoMuonKinematicsAfter         = process.analyzeMuonKinematics.clone(src = 'isoMuons'                         )
process.tightBottomJetKinematicsAfter  = process.analyzeJetKinematics.clone (src = 'tightBottomJets'                  )
process.tightLeadingJetKinematicsAfter = process.analyzeJetKinematics.clone (src = 'tightLeadingJets'                 )
process.tightLead_0_JetKinematicsAfter = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds0 )
process.tightLead_1_JetKinematicsAfter = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds1 )
process.tightLead_2_JetKinematicsAfter = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds2 )
process.tightLead_3_JetKinematicsAfter = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds3 )
process.tightBJet_0_JetKinematicsAfter = process.analyzeJetKinematics.clone (src = 'tightBottomJets' , analyze = uds0 )
process.tightBJet_1_JetKinematicsAfter = process.analyzeJetKinematics.clone (src = 'tightBottomJets' , analyze = uds1 )
process.tightBJet_0_JetKinematicsAfter = process.analyzeJetKinematics.clone (src = 'tightBottomJets' , analyze = uds0 )
process.tightBJet_1_JetKinematicsAfter = process.analyzeJetKinematics.clone (src = 'tightBottomJets' , analyze = uds1 )

## to be called with semiLeptonicSelection
process.monitorMuonKinematics = cms.Sequence(process.unselectedMuonKinematics +
                                             process.combinedMuonKinematics   +
                                             process.triggerMuonKinematics    +
                                             process.trackMuonKinematics      +
                                             process.looseMuonKinematics      +
                                             process.isoMuonKinematics        +
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

## collect quality analyzers for Muons and Jets
process.goodMuonQuality              = process.analyzeMuonQuality.clone(src = 'goodMuons'                        )
process.trackMuonQuality             = process.analyzeMuonQuality.clone(src = 'trackMuons'                       )
#process.looseMuonQuality             = process.analyzeMuonQuality.clone(src = 'looseMuons'                       )
process.isoMuonQuality               = process.analyzeMuonQuality.clone(src = 'isoMuons'                         )
process.unselectedMuonQuality        = process.analyzeMuonQuality.clone(src = 'selectedLayer1Muons'              )
process.combinedMuonQuality          = process.analyzeMuonQuality.clone(src = 'combinedMuons'                    )
process.triggerMuonQuality           = process.analyzeMuonQuality.clone(src = 'triggerMuons'                     )
process.tightMuonQuality             = process.analyzeMuonQuality.clone(src = 'tightMuons'                       )
process.goldenMuonQuality            = process.analyzeMuonQuality.clone(src = 'goldenMuons'                      )

process.tightBottomJetQuality        = process.analyzeJetQuality.clone (src = 'tightBottomJets'                  )
process.tightLeadingJetQuality       = process.analyzeJetQuality.clone (src = 'tightLeadingJets'                 )
process.reliableLeadingJetQuality    = process.analyzeJetQuality.clone (src = 'reliableJets'                     )
process.tightMatchedBJetQuality      = process.analyzeJetQuality.clone (src = 'tightMatchedBottomJets'           )
process.tightMatchedLightQJetQuality = process.analyzeJetQuality.clone (src = 'tightMatchedLightQJets'           )

process.isoMuonQualityAfter               = process.analyzeMuonQuality.clone(src = 'isoMuons'                         )
process.tightMuonQualityAfter             = process.analyzeMuonQuality.clone(src = 'tightMuons'                       )
process.tightLeadingJetQualityAfter       = process.analyzeJetQuality.clone (src = 'tightLeadingJets'                 )
process.tightBottomJetQualityAfter        = process.analyzeJetQuality.clone (src = 'tightBottomJets'                  )
process.tightLeadingJetQualityAfter       = process.analyzeJetQuality.clone (src = 'tightLeadingJets'                 )
process.tightMatchedBJetQualityAfter      = process.analyzeJetQuality.clone (src = 'tightMatchedBottomJets'           )
process.tightMatchedLightQJetQualityAfter = process.analyzeJetQuality.clone (src = 'tightMatchedLightQJets'           )



## to be called with the *selectGoldenMuons* sequence
process.monitorMuonQuality = cms.Sequence(process.unselectedMuonQuality +
                                          process.combinedMuonQuality   +
                                          process.triggerMuonQuality    +
                                          process.trackMuonQuality      +
                                          process.goodMuonQuality       +
#                                          process.looseMuonQuality      +
                                          process.isoMuonQuality        +
                                          process.goldenMuonQuality     +
                                          process.tightMuonQuality
                                          ) 
process.monitorJetsQuality = cms.Sequence(process.tightBottomJetQuality        +
                                          process.reliableLeadingJetQuality    +
                                          process.tightLeadingJetQuality       +
                                          process.tightMatchedBJetQuality      +
                                          process.tightMatchedLightQJetQuality
                                          )
## collect muon-jet analyzer
#process.unselectedMuonUnselectedJetKinematics   = process.analyzeMuonJetKinematics.clone(srcA = 'selectedLayer1Muons',
#                                                                                         srcB = 'selectedLayer1Jets'  )
#process.goodMuonUnselectedJetKinematics         = process.analyzeMuonJetKinematics.clone(srcA = 'goodMuons',
#                                                                                         srcB = 'selectedLayer1Jets'  )
#process.unselectedMuonGoodJetKinematics         = process.analyzeMuonJetKinematics.clone(srcA = 'selectedLayer1Muons',
#                                                                                         srcB = 'goodJets'            )
#process.goodMuonGoodJetKinematics               = process.analyzeMuonJetKinematics.clone(srcA = 'goodMuons',
#                                                                                         srcB = 'goodJets'            )
#process.trackMuonGoodJetKinematics             = process.analyzeMuonJetKinematics.clone(srcA = 'trackMuons',
#                                                                                        srcB = 'goodJets'            )
#process.looseMuonGoodJetKinematics             = process.analyzeMuonJetKinematics.clone(srcA = 'looseMuons',
#                                                                                        srcB = 'goodJets'
process.tightMuonGoodJetKinematics              = process.analyzeMuonJetKinematics.clone(srcA = 'tightMuons',
                                                                                         srcB = 'goodJets'            )
#process.tightMuonUnselectedJetKinematics        = process.analyzeMuonJetKinematics.clone(srcA = 'goodMuons',
#                                                                                         srcB = 'selectedLayer1Jets'  )
#process.goodMuonCentralJetKinematics           = process.analyzeMuonJetKinematics.clone(srcA = 'goodMuons',
#                                                                                        srcB = 'centralJets'         )
#process.tightMuonReliableJetKinematics          = process.analyzeMuonJetKinematics.clone(srcA = 'tightMuons',
#                                                                                         srcB = 'reliableJets'        )
#process.secLeadTightMuonGoodJetKinematics       = process.analyzeMuonJetKinematics.clone(srcA = 'tightMuons',
#                                                                                         analyze = cms.PSet(index = cms.int32(1)),
#                                                                                         srcB = 'goodJets'            )
#process.tightMuonSecLeadGoodJetKinematics       = process.analyzeMuonJetKinematics.clone(srcA = 'tightMuons',
#                                                                                         srcB = 'goodJets',
#                                                                                         analyze = uds1               )
process.mipTightMuonGoodJetKinematics           = process.analyzeMuonJetKinematics.clone(srcA = 'mipTightMuons',
                                                                                         srcB = 'goodJets'            )
#process.tightMuonL5GoodJetKinematics            = process.analyzeMuonJetKinematics.clone(srcA = 'tightMuons',
#                                                                                         srcB = 'goodJets',
#                                                                                         analyze = uds0L5             )

process.tightMuonGoodJetKinematicsAfter         = process.analyzeMuonJetKinematics.clone(srcA = 'tightMuons',
                                                                                         srcB = 'goodJets'            )
process.mipTightMuonGoodJetKinematicsAfter      = process.analyzeMuonJetKinematics.clone(srcA = 'mipTightMuons',
                                                                                         srcB = 'goodJets'            )
#process.tightMuonL5GoodJetKinematicsAfter       = process.analyzeMuonJetKinematics.clone(srcA = 'tightMuons',
#                                                                                         srcB = 'goodJets',
#                                                                                         analyze = uds0L5             )
#process.tightMuonSecLeadGoodJetKinematicsAfter  = process.analyzeMuonJetKinematics.clone(srcA = 'tightMuons',
#                                                                                         srcB = 'goodJets',
#                                                                                         analyze = uds1               )

## choosing the muon-jet analyzer you want to use 

process.monitorMuonJetKinematics= cms.Sequence(
                                               process.tightMuonGoodJetKinematics            +
                                               process.mipTightMuonGoodJetKinematics         
                                               )
                               
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
                                                        process.tightMuonGoodJetKinematicsAfter        +
                                                        process.mipTightMuonGoodJetKinematicsAfter     +
                                                        process.isoMuonQualityAfter                    +
                                                        process.isoMuonKinematicsAfter
                                                        )

## ---
##    run the final sequence
## ---
process.p1 = cms.Path(## do the gen event selection and the trigger selection
                      process.filterSequence           *
                      ## do the selections
                      combinedMuons                    *
                      process.semiLeptonicSelection    *
                      reliableJets                     *
                      centralJets                      *
                      ## do the matching
                      process.matchJetsToPartons       *
                      ## do the monitoring
                      process.monitorMuonQuality       *
                      process.monitorJetsQuality       *
                      process.monitorJetsKinematics    *
                      process.monitorMuonKinematics    *
                      process.monitorMuonJetKinematics *
                      ## do the event selection
                      process.semiLeptonicEvents       *
                      ## do monitoring after full cuts (no btag)
                      process.monitorQualitiesAfterSelection *
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
