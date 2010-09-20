import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing

## ---
##    here we need a general description of what the config id good for and the
##    switches mean. This should be in analogy of the Doxygen commentsin the
##    modules...
## ---

# setup 'standard' options
options = VarParsing.VarParsing ('standard')
## decide whether to run on:  * data *, * signal only (sig) *, * background only (bkg) *, * qcd * or * all *
options.register('eventFilter', 'data', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "kind of data to be processed")
## choose whether to write output to disk or not
options.register('writeOutput', 0 , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "write events surviving all cuts to disk")
## setup the ptHatFilter in case 'eventFilter' is chosen to be qcd
options.register('maxPtHat', 999999., VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.float, "maxPtHat to be processed")
options.register('minPtHat', 0.     , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.float, "minPtHat to be processed")
## decide whether to run on:  * ReRecoA *, * ReRecoB *, * Prompt *
options.register('globalTag', 'Prompt', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "kind of data to be processed")

# get and parse the command line arguments
options.parseArguments()

# analyse muon quantities
process = cms.Process("TriggerEfficiency")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'ERROR'
#process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(    
    ## add your favourite file here
    #'/store/user/eschliec/Run2010A/patTuple_6jets.root',
    #'/store/user/eschliec/Run2010A/patTuple_6jets_06.root',
    '/store/user/eschliec/Run2010A/patTuple_6jets_07.root',
    '/store/user/eschliec/Run2010A/patTuple_6jets_0809.root',
    #'/store/data/Run2010A/JetMETTau/RECO/v4/000/140/124/02731F1A-728F-DF11-AD45-003048F024E0.root'
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_1_1.root',
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_2_1.root',
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_3_1.root',
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_4_1.root',
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_5_1.root',
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_6_1.root',
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_7_1.root',
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_8_1.root',
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_9_1.root',
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_10_1.root',
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_11_1.root',
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_12_1.root',
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_13_1.root',
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_14_1.root',
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_15_1.root',
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_16_1.root',
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_17_1.root',
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_18_1.root',
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_19_1.root',
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_20_1.root'
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
            fileName = cms.string('analyzeL1QuadJetTriggerThreshold_all.root')
)

## ---
##    decide whether to run on:  * all *, * signal only *, * background only *
## ---

## std sequence to produce the ttGenEvt
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")

## filter for full-hadronic 
process.load("TopQuarkAnalysis.TopEventProducers.producers.TtDecaySelection_cfi")
process.ttFullHadronicFilter = process.ttDecaySelection.clone()

## ptHat filter
process.load("TopAnalysis.TopFilter.filters.PtHatFilter_cfi")
process.filterPtHat = process.filterPtHat.clone()

## residual jet corrector for data
process.load("TopAnalysis.TopUtils.ResidualJetCorrector_cfi")
process.residualCorrectedJets   = process.residualCorrectedJets.clone()
process.residualCorrectedJetsPF = process.residualCorrectedJets.clone(jets = 'selectedPatJetsAK5PF',
                                                                      corrections = 'Spring10DataV2_L2L3Residual_AK5PF.txt')

if(options.eventFilter=='data'):
    
    ## configure geometry & conditions
    process.load("Configuration.StandardSequences.Geometry_cff")
    process.load("Configuration.StandardSequences.MagneticField_cff")
    process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")

    print "Set to run with GlobalTag:",
    if(options.globalTag=='Prompt'):
        process.GlobalTag.globaltag = cms.string('GR10_P_V9::All')
    elif(options.globalTag=='ReRecoA'):
        process.GlobalTag.globaltag = cms.string('GR_R_36X_V12A::All')
    elif(options.globalTag=='ReRecoB'):
        process.GlobalTag.globaltag = cms.string('GR_R_36X_V12B::All')
    else:
        print "Error occured, GlobalTag not definded properly, stopping program execution"
        sys.exit(0)
    print process.GlobalTag.globaltag

    #-------------------------------------------------
    # vertex filter
    #-------------------------------------------------
    
    # vertex filter
    process.vertex = cms.EDFilter("VertexSelector",
                                  src = cms.InputTag("offlinePrimaryVertices"),
                                  cut = cms.string("!isFake && ndof > 4 && abs(z) < 24 && position.Rho < 2"),
                                  filter = cms.bool(True),
                                  )

    #-------------------------------------------------
    # scraping filter
    #-------------------------------------------------

    # scraping filter
    process.noscraping = cms.EDFilter("FilterOutScraping",
                                      applyfilter = cms.untracked.bool(True),
                                      debugOn = cms.untracked.bool(False),
                                      numtrack = cms.untracked.uint32(10),
                                      thresh = cms.untracked.double(0.25)
                                      )

#####    #-------------------------------------------------
#####    # pat configuration
#####    #-------------------------------------------------
#####
#####    ## std sequence for pat
#####    process.load("PhysicsTools.PatAlgos.patSequences_cff")
#####
#####    ## remove MC matching, photons, taus and cleaning from PAT default sequence
#####    from PhysicsTools.PatAlgos.tools.coreTools import *
#####    removeMCMatching(process, ['All'])
#####
#####    ## remove unneeded objects from processing (speed up of whole sequence)
#####    removeAllPATObjectsBut(process,['Jets'],outputInProcess=False)
#####
#####    ## cleaning not neede here
#####    removeCleaning(process,outputInProcess=False)
#####
#####    ## Add particle flow jets
#####    from PhysicsTools.PatAlgos.tools.jetTools import *
#####    addJetCollection(process,cms.InputTag('ak5PFJets'),'AK5','PF',
#####                     doJTA        = True,
#####                     doBTagging   = True,
#####                     jetCorrLabel = ('AK5', 'PF'),
#####                     doType1MET   = False,
#####                     doL1Cleaning = True,
#####                     doL1Counters = False,
#####                     genJetCollection=None,
#####                     doJetID      = True,
#####                     )
#####
#####    ## remove TagInfos from jets
#####    process.patJets.addTagInfos = False
#####    process.patJetsAK5PF.addTagInfos = False
#####    
#####    ## use the correct jet energy corrections
#####    process.patJetCorrFactors.corrSample = "Spring10"
#####    process.patJetCorrFactors.sampleType = "ttbar"
#####    process.patJetCorrFactorsAK5PF.corrSample = "Spring10"
#####    process.patJetCorrFactorsAK5PF.sampleType = "ttbar"
#####

    process.load("TopAnalysis.TopUtils.patTriggerEvent_cff")
    
    ## sequence with jet energy corrections specially suited for data
    process.filterSequence = cms.Sequence(process.patTriggerSequence *
                                          process.residualCorrectedJets *
                                          process.residualCorrectedJetsPF
                                          )
    
elif(options.eventFilter=='sig'):
    ## sequence with fullHad ttbar filter
    process.filterSequence = cms.Sequence(#process.patDefaultSequence *
                                          process.makeGenEvt *
                                          process.ttFullHadronicFilter
                                          )

elif(options.eventFilter=='bkg'):
    ## invert fullHad filter
    process.ttFullHadronicFilter.invert = True
    ## sequence with non-fullHad ttbar filter
    process.filterSequence = cms.Sequence(#process.patDefaultSequence *
                                          process.makeGenEvt *
                                          process.ttFullHadronicFilter
                                          )

elif(options.eventFilter=='all'):
    process.filterSequence = cms.Sequence(#process.patDefaultSequence *
                                          process.filterPtHat)
    
else:
    raise NameError, "'"+options.eventFilter+"' is not a prober eventFilter name choose: 'data', 'sig', 'bkg', 'qcd' or 'all'"

## adapt output filename
process.TFileService.fileName = 'analyzeL1QuadJetTriggerThreshold_'+options.eventFilter+'.root'

## high level trigger filter
process.load("TopAnalysis.TopFilter.sequences.triggerFilter_cff")
process.load("TopAnalysis.TopFilter.filters.NewTriggerTestFilter_cfi")
## for the jet collections which should be used
#process.load("TopAnalysis.TopFilter.sequences.jetSelection_cff")
## generator matching
process.load("TopAnalysis.TopFilter.sequences.generatorMatching_cff")
## load trigger analyzer
process.load("TopAnalysis.TopAnalyzer.TriggerEfficiency_cfi")

process.analyzeTriggerEfficiencyCalo = process.analyzeTriggerEfficiency.clone()
process.analyzeTriggerEfficiencyPF   = process.analyzeTriggerEfficiency.clone()

## jet selector
process.load("PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi")
process.goodJets     = process.selectedPatJets.clone(src = 'selectedPatJets',
                                                     cut = 'abs(eta) < 3.0 & pt > 30. &'
                                                           'emEnergyFraction > 0.01   &'
                                                           'jetID.fHPD < 0.98         &'
                                                           'jetID.n90Hits > 1'
                                                     )
process.goodJetsPF   = process.selectedPatJets.clone(src = 'selectedPatJetsAK5PF',
                                                     cut = 'abs(eta) < 3.0 & pt > 30. &'
                                            '((abs(eta) < 2.4 & chargedHadronEnergyFraction > 0.0)                | abs(eta) >= 2.4) &'
                                            '((abs(eta) < 2.4 & chargedEmEnergyFraction/corrFactor("raw") < 0.99) | abs(eta) >= 2.4) &'
                                                           'neutralHadronEnergyFraction/corrFactor("raw") < 0.99 &'
                                                           'neutralEmEnergyFraction/corrFactor("raw")     < 0.99 &'
                                                           '((abs(eta) < 2.4 & chargedMultiplicity > 0) | abs(eta) >= 2.4) &'
                                                           'nConstituents > 0'
                                                     )

## jet count filter
process.load("PhysicsTools.PatAlgos.selectionLayer1.jetCountFilter_cfi")

process.goodJetSelection   = process.countPatJets.clone(src = 'goodJets'  , minNumber = 6)
process.goodJetSelectionPF = process.countPatJets.clone(src = 'goodJetsPF', minNumber = 6)

## add jet collection to prerequists
process.filterSequenceCalo = cms.Sequence(process.filterSequence *
                                          process.goodJets *
                                          process.goodJetSelection
                                          )
process.filterSequencePF   = cms.Sequence(process.filterSequence *
                                          process.goodJetsPF *
                                          process.goodJetSelectionPF
                                          )

## ---
##    run the final sequence
## ---
process.p_calo = cms.Path(## do the genEvent selection
                          process.filterSequenceCalo *
                          ## do the L1 trigger monitoring
                          process.analyzeTriggerEfficiencyCalo
                          )

process.p_pf   = cms.Path(## do the genEvent selection
                          process.filterSequencePF *
                          ## do the L1 trigger monitoring
                          process.analyzeTriggerEfficiencyPF
                          )

if(options.eventFilter=='data'):
    ## different detector response for jets than in simulation
    if(hasattr(process, 'goodJets') & hasattr(process, 'residualCorrectedJets')):
        process.goodJets.src   = 'residualCorrectedJets'
    if(hasattr(process, 'goodJetsPF') & hasattr(process, 'residualCorrectedJetsPF')):
        process.goodJetsPF.src = 'residualCorrectedJetsPF'
#else:
#    print "hallo"
    
## Output Module Configuration
if(not options.writeOutput==0):
    process.out = cms.OutputModule("PoolOutputModule",
                                   fileName = cms.untracked.string('patTuple_selected.root'),
                                   # save only events passing the full path
                                   SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p1') ),
                                   # drop meta data for dropped events
                                   dropMetaData = cms.untracked.string('DROPPED'),
                                   # save output (comment to keep everything...)
                                   #outputCommands = cms.untracked.vstring('drop *',) 
                                   )
    process.outpath = cms.EndPath(process.out)
