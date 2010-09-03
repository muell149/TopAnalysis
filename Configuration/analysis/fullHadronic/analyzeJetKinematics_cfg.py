import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing

# setup 'standard' options
options = VarParsing.VarParsing ('standard')
## decide whether to run on:  * dat12 *, * dat3 *, * dat4 *, * MC *, * pthat *
options.register('eventFilter', 'pthat', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "kind of data to be processed")
# setup any defaults you want
options.register('maxPtHat', 999999., VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.float, "maxPtHat to be processed")
options.register('minPtHat', 0.     , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.float, "minPtHat to be processed")

# get and parse the command line arguments
options.parseArguments()

# analyse jet quantities
process = cms.Process("test")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    ## add your favourite file here
    #'/store/mc/Spring10/QCD_Pt800/AODSIM/START3X_V26_S09-v1/0004/005B769C-4C46-DF11-A353-0030487F164D.root'
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
            fileName = cms.string('analyzeJetKinematics_test.root')
)

## configure geometry & conditions
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")

if(options.eventFilter=='MC' or options.eventFilter=='pthat'):
    process.GlobalTag.globaltag = cms.string('START3X_V26::All')
    print "Set to run on MC with",
elif(options.eventFilter=='dat12'):
    process.GlobalTag.globaltag = cms.string('GR_R_36X_V12A::All')
    print "Set to run on data with",
elif(options.eventFilter=='dat4'):
    process.GlobalTag.globaltag = cms.string('GR_R_36X_V12B::All')
    print "Set to run on data with",
elif(options.eventFilter=='dat3'):
    process.GlobalTag.globaltag = cms.string('GR10_P_V7::All')
    print "Set to run on data with",
print process.GlobalTag.globaltag

## std sequence for pat
process.load("PhysicsTools.PatAlgos.patSequences_cff")

## configure output module
process.out = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring('drop *'),
    dropMetaDataForDroppedData = cms.untracked.bool(True),                                     
    fileName = cms.untracked.string('patTuple_jetKinematics.root')
)


if(options.eventFilter=='MC' or options.eventFilter=='pthat'):
    ## run CMSSW 36X on 35X MC
    from PhysicsTools.PatAlgos.tools.cmsswVersionTools import *
    run36xOn35xInput(process)

## remove MC matching, photons, taus and cleaning from PAT default sequence
from PhysicsTools.PatAlgos.tools.coreTools import *
restrictInputToAOD(process)
removeMCMatching(process, ['All'])
removeCleaning(process)
removeAllPATObjectsBut(process, ['Jets'])

## Add particle flow jets
if(options.eventFilter=='MC' or options.eventFilter=='pthat'):
    addJetCollection35X(process,cms.InputTag('ak5PFJets'),'AK5','PF',
                        doJTA        = True,
                        doBTagging   = False,
                        jetCorrLabel = ('AK5', 'PF'),
                        doType1MET   = False,
                        doL1Cleaning = False,
                        doL1Counters = False,
                        genJetCollection=None,
                        doJetID      = True,
                        )
else:
    from PhysicsTools.PatAlgos.tools.jetTools import *
    addJetCollection(process,cms.InputTag('ak5PFJets'),'AK5','PF',
                     doJTA        = True,
                     doBTagging   = False,
                     jetCorrLabel = ('AK5', 'PF'),
                     doType1MET   = False,
                     doL1Cleaning = False,
                     doL1Counters = False,
                     genJetCollection=None,
                     doJetID      = True,
                     )

## embedding of jet constituents into the jets
process.patJets.embedCaloTowers = False
process.patJetsAK5PF.embedPFCandidates = True

## remove TagInfos from jets
process.patJets.addTagInfos = False
process.patJetsAK5PF.addTagInfos = False

## use the correct jet energy corrections
process.patJetCorrFactors.corrSample = "Spring10"
process.patJetCorrFactors.sampleType = "ttbar"
process.patJetCorrFactorsAK5PF.corrSample = "Spring10"
process.patJetCorrFactorsAK5PF.sampleType = "ttbar"

## setup the jet selection collection
process.load("PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi")

## create jet collections need for the preselection
process.looseJets20   = process.selectedPatJets.clone(src = 'selectedPatJets',
                                                      cut = 'pt > 20. & abs(eta) < 2.4 & '
                                                            'emEnergyFraction > 0.01   & '
                                                            'jetID.fHPD < 0.98         & '
                                                            'jetID.n90Hits > 1'
                                                      )

process.tightJets20   = process.selectedPatJets.clone(src = 'looseJets20',
                                                      cut = '(((corrFactor("raw") * pt) > 25. & jetID.fHPD < 0.95) | (corrFactor("raw") * pt) <= 25.) & '
                                                            '((abs(eta) > 1.0 & (corrFactor("raw") * pt) > 55. & emEnergyFraction < 1.0) | abs(eta) <= 1.0 | (corrFactor("raw") * pt) <= 55.)'
                                                      )

process.loosePFJets20 = process.selectedPatJets.clone(src = 'selectedPatJetsAK5PF',
                                                      cut = 'pt > 20. & abs(eta) < 2.4 & '
                                                            'chargedHadronEnergyFraction > 0.0  & '
                                                            'neutralHadronEnergyFraction < 0.99 & '
                                                            'chargedEmEnergyFraction < 0.99 & '
                                                            'neutralEmEnergyFraction < 0.99 & '
                                                            'chargedMultiplicity > 0 & '
                                                            'nConstituents > 0'
                                                      )
process.tightPFJets20 = process.selectedPatJets.clone(src = 'loosePFJets20',
                                                      cut = 'neutralHadronEnergyFraction < 0.9 & '
                                                            'neutralEmEnergyFraction < 0.9'
                                                      )

process.looseJets30   = process.selectedPatJets.clone(src = 'looseJets20',   cut = 'pt > 30.')
process.tightJets30   = process.selectedPatJets.clone(src = 'tightJets20',   cut = 'pt > 30.')
process.loosePFJets30 = process.selectedPatJets.clone(src = 'loosePFJets20', cut = 'pt > 30.')
process.tightPFJets30 = process.selectedPatJets.clone(src = 'tightPFJets20', cut = 'pt > 30.')

process.looseJets40   = process.selectedPatJets.clone(src = 'looseJets30',   cut = 'pt > 40.')
process.tightJets40   = process.selectedPatJets.clone(src = 'tightJets30',   cut = 'pt > 40.')
process.loosePFJets40 = process.selectedPatJets.clone(src = 'loosePFJets30', cut = 'pt > 40.')
process.tightPFJets40 = process.selectedPatJets.clone(src = 'tightPFJets30', cut = 'pt > 40.')

process.looseJets50   = process.selectedPatJets.clone(src = 'looseJets40',   cut = 'pt > 50.')
process.tightJets50   = process.selectedPatJets.clone(src = 'tightJets40',   cut = 'pt > 50.')
process.loosePFJets50 = process.selectedPatJets.clone(src = 'loosePFJets40', cut = 'pt > 50.')
process.tightPFJets50 = process.selectedPatJets.clone(src = 'tightPFJets40', cut = 'pt > 50.')

#-------------------------------------------------
# vertex filter
#-------------------------------------------------

# vertex filter
process.vertex = cms.EDFilter("VertexSelector",
                              src = cms.InputTag("offlinePrimaryVertices"),
                              cut = cms.string("!isFake && ndof > 4 && abs(z) < 15 && position.Rho < 2"),
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

#-------------------------------------------------
# trigger HLT_QuadJet15U | HLT_Jet50U
#-------------------------------------------------

## high level trigger filter
from HLTrigger.HLTfilters.hltHighLevel_cfi import *
## MC
if(options.eventFilter=='MC' or options.eventFilter=='pthat'):
    #process.trigger = hltHighLevel.clone(HLTPaths = ["HLT_QuadJet15U"],
    process.trigger = hltHighLevel.clone(HLTPaths = ["HLT_Jet50U"],
                                         TriggerResultsTag = cms.InputTag("TriggerResults","","REDIGI"))
## data
else:
    #process.trigger = hltHighLevel.clone(HLTPaths = ["HLT_QuadJet15U"])
    process.trigger = hltHighLevel.clone(HLTPaths = ["HLT_Jet50U"])

process.preFilterSequence = cms.Sequence(process.vertex *
                                         process.noscraping *
                                         process.trigger
                                         )

#-------------------------------------------------
# pt-hat filter for samples where needed
#-------------------------------------------------

if(options.eventFilter=='pthat'):
    if(options.maxPtHat<999999.):
        ## ptHat filter
        process.load("TopAnalysis.TopFilter.filters.PtHatFilter_cfi")
        process.filterPtHat = process.filterPtHat.clone(maxPtHat = options.maxPtHat)
        process.preFilterSequence *= process.filterPtHat
        print "included ptHatFilter with 'maxPtHat' =",
        print process.filterPtHat.maxPtHat

    if(options.minPtHat>0.):
        if(hasattr(process,'filterPtHat')):
            process.filterPtHat.minPtHat = options.minPtHat
        else:
            ## ptHat filter
            process.load("TopAnalysis.TopFilter.filters.PtHatFilter_cfi")
            process.filterPtHat = process.filterPtHat.clone(minPtHat = options.minPtHat)
            process.preFilterSequence *= process.filterPtHat
            print "included ptHatFilter with 'minPtHat' =",
            print process.filterPtHat.minPtHat

#-------------------------------------------------
# min. 4 jets filters
#-------------------------------------------------

## jet selector
from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import *
## select all events with at least 4 jets
process.looseJet20Selection = process.countPatJets.clone( src = 'looseJets20', minNumber = 6 )
process.looseJet30Selection = process.countPatJets.clone( src = 'looseJets30', minNumber = 6 )
process.looseJet40Selection = process.countPatJets.clone( src = 'looseJets40', minNumber = 6 )
process.looseJet50Selection = process.countPatJets.clone( src = 'looseJets50', minNumber = 6 )

process.tightJet20Selection = process.countPatJets.clone( src = 'tightJets20', minNumber = 6 )
process.tightJet30Selection = process.countPatJets.clone( src = 'tightJets30', minNumber = 6 )
process.tightJet40Selection = process.countPatJets.clone( src = 'tightJets40', minNumber = 6 )
process.tightJet50Selection = process.countPatJets.clone( src = 'tightJets50', minNumber = 6 )

process.loosePFJet20Selection = process.countPatJets.clone( src = 'loosePFJets20', minNumber = 6 )
process.loosePFJet30Selection = process.countPatJets.clone( src = 'loosePFJets30', minNumber = 6 )
process.loosePFJet40Selection = process.countPatJets.clone( src = 'loosePFJets40', minNumber = 6 )
process.loosePFJet50Selection = process.countPatJets.clone( src = 'loosePFJets50', minNumber = 6 )

process.tightPFJet20Selection = process.countPatJets.clone( src = 'tightPFJets20', minNumber = 6 )
process.tightPFJet30Selection = process.countPatJets.clone( src = 'tightPFJets30', minNumber = 6 )
process.tightPFJet40Selection = process.countPatJets.clone( src = 'tightPFJets40', minNumber = 6 )
process.tightPFJet50Selection = process.countPatJets.clone( src = 'tightPFJets50', minNumber = 6 )

## ---
##    MONITOR JET MULTIPLICITIES
## ---

## jet kinematics analyzer
process.load("TopAnalysis.TopAnalyzer.JetKinematics_cfi")

## collect kinematics analyzers
process.looseCaloJetMultiplicities20 = process.analyzeJetKinematics.clone (src = 'looseJets20')
process.tightCaloJetMultiplicities20 = process.analyzeJetKinematics.clone (src = 'tightJets20')
process.loosePFJetMultiplicities20   = process.analyzeJetKinematics.clone (src = 'loosePFJets20')
process.tightPFJetMultiplicities20   = process.analyzeJetKinematics.clone (src = 'tightPFJets20')

process.looseCaloJetMultiplicities30 = process.analyzeJetKinematics.clone (src = 'looseJets30')
process.tightCaloJetMultiplicities30 = process.analyzeJetKinematics.clone (src = 'tightJets30')
process.loosePFJetMultiplicities30   = process.analyzeJetKinematics.clone (src = 'loosePFJets30')
process.tightPFJetMultiplicities30   = process.analyzeJetKinematics.clone (src = 'tightPFJets30')

process.looseCaloJetMultiplicities40 = process.analyzeJetKinematics.clone (src = 'looseJets40')
process.tightCaloJetMultiplicities40 = process.analyzeJetKinematics.clone (src = 'tightJets40')
process.loosePFJetMultiplicities40   = process.analyzeJetKinematics.clone (src = 'loosePFJets40')
process.tightPFJetMultiplicities40   = process.analyzeJetKinematics.clone (src = 'tightPFJets40')

process.looseCaloJetMultiplicities50 = process.analyzeJetKinematics.clone (src = 'looseJets50')
process.tightCaloJetMultiplicities50 = process.analyzeJetKinematics.clone (src = 'tightJets50')
process.loosePFJetMultiplicities50   = process.analyzeJetKinematics.clone (src = 'loosePFJets50')
process.tightPFJetMultiplicities50   = process.analyzeJetKinematics.clone (src = 'tightPFJets50')

## ---
##    MONITOR JET KINEMATICS
## ---

## collect kinematics analyzers
process.looseCaloJetKinematics20 = process.analyzeJetKinematics.clone (src = 'looseJets20')
process.tightCaloJetKinematics20 = process.analyzeJetKinematics.clone (src = 'tightJets20')
process.loosePFJetKinematics20   = process.analyzeJetKinematics.clone (src = 'loosePFJets20')
process.tightPFJetKinematics20   = process.analyzeJetKinematics.clone (src = 'tightPFJets20')

process.looseCaloJetKinematics30 = process.analyzeJetKinematics.clone (src = 'looseJets30')
process.tightCaloJetKinematics30 = process.analyzeJetKinematics.clone (src = 'tightJets30')
process.loosePFJetKinematics30   = process.analyzeJetKinematics.clone (src = 'loosePFJets30')
process.tightPFJetKinematics30   = process.analyzeJetKinematics.clone (src = 'tightPFJets30')

process.looseCaloJetKinematics40 = process.analyzeJetKinematics.clone (src = 'looseJets40')
process.tightCaloJetKinematics40 = process.analyzeJetKinematics.clone (src = 'tightJets40')
process.loosePFJetKinematics40   = process.analyzeJetKinematics.clone (src = 'loosePFJets40')
process.tightPFJetKinematics40   = process.analyzeJetKinematics.clone (src = 'tightPFJets40')

process.looseCaloJetKinematics50 = process.analyzeJetKinematics.clone (src = 'looseJets50')
process.tightCaloJetKinematics50 = process.analyzeJetKinematics.clone (src = 'tightJets50')
process.loosePFJetKinematics50   = process.analyzeJetKinematics.clone (src = 'loosePFJets50')
process.tightPFJetKinematics50   = process.analyzeJetKinematics.clone (src = 'tightPFJets50')

## analyze the kinematics of the jets in the event
process.p1 = cms.Path(process.preFilterSequence            *
                      process.patDefaultSequence           *
                      process.looseJets20                  *
                      process.looseJets30                  *
                      process.looseJets40                  *
                      process.looseJets50                  *
                      process.looseCaloJetMultiplicities20 *
                      process.looseCaloJetMultiplicities30 *
                      process.looseCaloJetMultiplicities40 *
                      process.looseCaloJetMultiplicities50 *
                      process.looseJet20Selection          *
                      process.looseCaloJetKinematics20     *
                      process.looseJet30Selection          *
                      process.looseCaloJetKinematics30     *
                      process.looseJet40Selection          *
                      process.looseCaloJetKinematics40     *
                      process.looseJet50Selection          *
                      process.looseCaloJetKinematics50
                      )

process.p2 = cms.Path(process.preFilterSequence            *
                      process.patDefaultSequence           *
                      process.tightJets20                  *
                      process.tightJets30                  *
                      process.tightJets40                  *
                      process.tightJets50                  *
                      process.tightCaloJetMultiplicities20 *
                      process.tightCaloJetMultiplicities30 *
                      process.tightCaloJetMultiplicities40 *
                      process.tightCaloJetMultiplicities50 *
                      process.tightJet20Selection          *
                      process.tightCaloJetKinematics20     *
                      process.tightJet30Selection          *
                      process.tightCaloJetKinematics30     *
                      process.tightJet40Selection          *
                      process.tightCaloJetKinematics40     *
                      process.tightJet50Selection          *
                      process.tightCaloJetKinematics50
                      )

process.p3 = cms.Path(process.preFilterSequence          *
                      process.patDefaultSequence         *
                      process.loosePFJets20              *
                      process.loosePFJets30              *
                      process.loosePFJets40              *
                      process.loosePFJets50              *
                      process.loosePFJetMultiplicities20 *
                      process.loosePFJetMultiplicities30 *
                      process.loosePFJetMultiplicities40 *
                      process.loosePFJetMultiplicities50 *
                      process.loosePFJet20Selection      *
                      process.loosePFJetKinematics20     *
                      process.loosePFJet30Selection      *
                      process.loosePFJetKinematics30     *
                      process.loosePFJet40Selection      *
                      process.loosePFJetKinematics40     *
                      process.loosePFJet50Selection      *
                      process.loosePFJetKinematics50
                      )

process.p4 = cms.Path(process.preFilterSequence          *
                      process.patDefaultSequence         *
                      process.tightPFJets20              *
                      process.tightPFJets30              *
                      process.tightPFJets40              *
                      process.tightPFJets50              *
                      process.tightPFJetMultiplicities20 *
                      process.tightPFJetMultiplicities30 *
                      process.tightPFJetMultiplicities40 *
                      process.tightPFJetMultiplicities50 *
                      process.tightPFJet20Selection      *
                      process.tightPFJetKinematics20     *
                      process.tightPFJet30Selection      *
                      process.tightPFJetKinematics30     *
                      process.tightPFJet40Selection      *
                      process.tightPFJetKinematics40     *
                      process.tightPFJet50Selection      *
                      process.tightPFJetKinematics50
                      )

