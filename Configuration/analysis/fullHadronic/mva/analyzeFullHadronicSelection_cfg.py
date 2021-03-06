import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing
import sys

## ---
##    here we need a general description of what the config id good for and the
##    switches mean. This should be in analogy of the Doxygen comments in the
##    modules...
## ---

# setup 'standard' options
options = VarParsing.VarParsing ('standard')
## decide whether to run on:  * data *, * sig *, * sigPU *, * bkg *, * bkgPU *, * qcd *, * allRedigi *, * allRedigiPU * or * all *
options.register('eventFilter', 'data', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "kind of data to be processed")
## choose whether to use PF or not
options.register('usePF'      ,  1   , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int  , "use PF for processing")
## set the jet energy scale factor for MC
options.register('jesFactor'  ,  1.0 , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.float, "jet energy scale factor for MC")
## set the jet energy resolution smear factor for MC
options.register('jetEResol'  ,  1.1 , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.float, "jet energy resol factor for MC")
## set the resolution fractor for the kinematic fit
options.register('fitResol'   ,  1.1 , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.float, "kinFit resolution factor")
## choose whether to write output to disk or not
options.register('writeOutput',    0 , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int  , "write events surviving all cuts to disk")
## setup the ptHatFilter in case 'eventFilter' is chosen to be qcd
options.register('maxPtHat', 999999., VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.float, "maxPtHat to be processed")
options.register('minPtHat', 0.     , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.float, "minPtHat to be processed")
## include PDF uncertainty histograms / tree
options.register('pdfUn'   , 0 , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "include hists/tree for pdf uncertainty")
## choose whether to do a background estimation or a normal selection
options.register('backgroundEstimation', 0 , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "do a background estimation")
## do PATification on the fly, not depending on pre-made PAT tuples anymore
options.register('patify', 0 , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "run PAT on the fly")
## change b-tagging discriminator for b-tagging uncertainty measurement
options.register('bTag', 0 , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "bTag uncertainty")

# get and parse the command line arguments
#options.parseArguments()

if( hasattr(sys, "argv") ):
    for args in sys.argv :
        arg = args.split(',')
        for val in arg:
            val = val.split('=')
            if(len(val)==2):
                setattr(options,val[0], val[1])

print "eventFilter . . . . :", options.eventFilter
print "usePF . . . . . . . :", options.usePF
print "jesFactor . . . . . :", options.jesFactor
print "jetEResol . . . . . :", options.jetEResol
print "fitResol  . . . . . :", options.fitResol
print "writeOutput . . . . :", options.writeOutput
print "maxPtHat  . . . . . :", options.maxPtHat
print "minPtHat  . . . . . :", options.minPtHat
print "pdfUncertainty  . . :", options.pdfUn
print "backgroundEstimation:", options.backgroundEstimation
print "patify  . . . . . . :", options.patify
print "bTag  . . . . . . . :", options.bTag

# analyze fully hadronic selection
processName = "Selection"
process = cms.Process(processName)

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 10000
process.MessageLogger.categories.append('TtFullHadronicEvent')

# use only when PATTrigger is needed on data to suppress useless error messages
process.MessageLogger.cerr.default.limit = 0

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(    
    ## add your favourite file here
    #'/store/user/eschliec/MultiJet/PAT_6Jets/00b550d1515f7d6868b450d1e5dca901/patTuple_6jets_10_1_WVq.root',
    #'/store/user/eschliec/MultiJet/PAT_6Jets/00b550d1515f7d6868b450d1e5dca901/patTuple_6jets_11_1_KHs.root',
    #'/store/user/eschliec/MultiJet/PAT_6Jets/00b550d1515f7d6868b450d1e5dca901/patTuple_6jets_12_1_3wB.root',
    #'/store/user/eschliec/MultiJet/PAT_6Jets/00b550d1515f7d6868b450d1e5dca901/patTuple_6jets_13_1_uUW.root', 
    #'/store/user/eschliec/MultiJet/PAT_6Jets/00b550d1515f7d6868b450d1e5dca901/patTuple_6jets_14_1_M3c.root', 
    #'/store/user/eschliec/MultiJet/PAT_6Jets/00b550d1515f7d6868b450d1e5dca901/patTuple_6jets_14_2_SgJ.root', 
    #'/store/user/eschliec/MultiJet/PAT_6Jets/00b550d1515f7d6868b450d1e5dca901/patTuple_6jets_15_1_96C.root', 
    #'/store/user/eschliec/MultiJet/PAT_6Jets/00b550d1515f7d6868b450d1e5dca901/patTuple_6jets_16_1_oqr.root', 
    #'/store/user/eschliec/MultiJet/PAT_6Jets/00b550d1515f7d6868b450d1e5dca901/patTuple_6jets_17_1_ubf.root', 
    #'/store/user/eschliec/MultiJet/PAT_6Jets/00b550d1515f7d6868b450d1e5dca901/patTuple_6jets_18_1_HdM.root', 
    #'/store/user/eschliec/MultiJet/PAT_6Jets/00b550d1515f7d6868b450d1e5dca901/patTuple_6jets_19_1_CQa.root',
    #'/store/user/eschliec/MultiJet/PAT_6Jets/00b550d1515f7d6868b450d1e5dca901/patTuple_6jets_1_1_IBt.root', 
    #'/store/user/eschliec/MultiJet/PAT_6Jets/00b550d1515f7d6868b450d1e5dca901/patTuple_6jets_20_1_hTV.root', 
    #'/store/user/eschliec/MultiJet/PAT_6Jets/00b550d1515f7d6868b450d1e5dca901/patTuple_6jets_21_1_eDR.root', 
    #'/store/user/eschliec/MultiJet/PAT_6Jets/00b550d1515f7d6868b450d1e5dca901/patTuple_6jets_22_1_30C.root', 
    #'/store/user/eschliec/MultiJet/PAT_6Jets/00b550d1515f7d6868b450d1e5dca901/patTuple_6jets_23_1_53b.root', 
    #'/store/user/eschliec/MultiJet/PAT_6Jets/00b550d1515f7d6868b450d1e5dca901/patTuple_6jets_24_1_L28.root', 
    #'/store/user/eschliec/MultiJet/PAT_6Jets/00b550d1515f7d6868b450d1e5dca901/patTuple_6jets_25_1_c9c.root', 
    #'/store/user/eschliec/MultiJet/PAT_6Jets/00b550d1515f7d6868b450d1e5dca901/patTuple_6jets_26_1_VWf.root', 
    #'/store/user/eschliec/MultiJet/PAT_6Jets/00b550d1515f7d6868b450d1e5dca901/patTuple_6jets_2_1_arG.root', 
    #'/store/user/eschliec/MultiJet/PAT_6Jets/00b550d1515f7d6868b450d1e5dca901/patTuple_6jets_3_1_xQc.root', 
    #'/store/user/eschliec/MultiJet/PAT_6Jets/00b550d1515f7d6868b450d1e5dca901/patTuple_6jets_4_1_tCL.root',
    #'/store/user/eschliec/MultiJet/PAT_6Jets/00b550d1515f7d6868b450d1e5dca901/patTuple_6jets_5_1_Qtp.root', 
    #'/store/user/eschliec/MultiJet/PAT_6Jets/00b550d1515f7d6868b450d1e5dca901/patTuple_6jets_6_1_6Aa.root', 
    #'/store/user/eschliec/MultiJet/PAT_6Jets/00b550d1515f7d6868b450d1e5dca901/patTuple_6jets_7_1_hCe.root', 
    #'/store/user/eschliec/MultiJet/PAT_6Jets/00b550d1515f7d6868b450d1e5dca901/patTuple_6jets_8_1_o49.root', 
    #'/store/user/eschliec/MultiJet/PAT_6Jets/00b550d1515f7d6868b450d1e5dca901/patTuple_6jets_9_1_TIv.root', 
    #'/store/user/henderle/TTJets_TuneZ2_7TeV-madgraph-tauola/PAT_FALL10HH/d11bd92e226f3f64b5cff39b069a59bb/fall10MC_2_1_Jua.root',
    #'/store/user/eschliec/MultiJet/PAT_6Jets/00b550d1515f7d6868b450d1e5dca901/patTuple_6jets_16_1_oqr.root',
    ),
    ## just a code example how to skip lumi blocks or whole runs
    #lumisToSkip = cms.untracked.VLuminosityBlockRange('135445:0-135445:max',
    #                                                  '140126:0-140126:max'),
    ## just a code example how to process specific events
    #eventsToProcess = cms.untracked.VEventRange('147757:196025134',
    #                                            '147757:197303976',
    #                                            '147757:198417181',
    #                                            '147757:200167888'),
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
            fileName = cms.string('analyzeFullHadronicSelection.root')
)

## configure geometry & conditions
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")

if(options.eventFilter=='data'):
    process.GlobalTag.globaltag = cms.string('GR_R_38X_V15::All')
else:
    process.GlobalTag.globaltag = cms.string('START38_V14::All')

## std sequence to produce the ttGenEvt
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")

## filter for full-hadronic 
process.load("TopQuarkAnalysis.TopEventProducers.producers.TtDecaySelection_cfi")
process.ttFullHadronicFilter = process.ttDecaySelection.clone()

## ptHat filter
process.load("TopAnalysis.TopFilter.filters.PtHatFilter_cfi")
process.filterPtHat = process.filterPtHat.clone()

## additional jet energy smearing for MC
process.load("TopAnalysis.TopUtils.JetEnergyScale_cfi")
process.scaledJetEnergy = process.scaledJetEnergy.clone( inputJets            = cms.InputTag("selectedPatJetsAK5PF"),
                                                         inputMETs            = cms.InputTag("patMETsPF"),
                                                         payload              = cms.string("AK5PF"),
                                                         scaleFactor          = cms.double(options.jesFactor),
                                                         scaleType            = cms.string("abs"), #abs or rel
                                                         jetPTThresholdForMET = cms.double(20.),
                                                         jetEMLimitForMET     = cms.double(0.9),
                                                         resolutionFactor     = cms.double(options.jetEResol)
                                                       )
## set set energy scaling factors
if(options.jesFactor > 1.0):
    process.scaledJetEnergy.scaleType = "top:up"

if(options.jesFactor < 1.0):
    process.scaledJetEnergy.scaleType = "top:down"

## residual jet corrector for data
process.load("TopAnalysis.TopUtils.ResidualJetCorrector_cfi")
process.residualCorrectedJets = process.residualCorrectedJets.clone()

if(options.eventFilter=='data'):
    ## sequence with jet energy corrections specially suited for data
    process.filterSequence = cms.Sequence(process.residualCorrectedJets
                                          )
    
elif(options.eventFilter=='sig' or options.eventFilter=='sigPU'):
    ## sequence with fullHad ttbar filter
    process.filterSequence = cms.Sequence(process.makeGenEvt *
                                          process.ttFullHadronicFilter *
                                          process.scaledJetEnergy
                                          )

elif(options.eventFilter=='bkg' or options.eventFilter=='bkgPU'):
    ## invert fullHad filter
    process.ttFullHadronicFilter.invert = True
    ## sequence with non-fullHad ttbar filter
    process.filterSequence = cms.Sequence(process.makeGenEvt *
                                          process.ttFullHadronicFilter *
                                          process.scaledJetEnergy
                                          )

elif(options.eventFilter=='qcd'):
    if(options.maxPtHat<999999.):
        ## ptHat filter
        process.filterPtHat.maxPtHat = options.maxPtHat
        print "included ptHatFilter with 'maxPtHat' =",
        print process.filterPtHat.maxPtHat

    if(options.minPtHat>0.):
        process.filterPtHat.minPtHat = options.minPtHat
        print "included ptHatFilter with 'minPtHat' =",
        print process.filterPtHat.minPtHat

    ## sequence with ptHat filter
    process.filterSequence = cms.Sequence(process.filterPtHat *
                                          process.scaledJetEnergy)

elif(options.eventFilter=='all' or options.eventFilter=='allRedigi' or options.eventFilter=='allRedigiPU'):
    process.filterSequence = cms.Sequence(process.scaledJetEnergy)
    
else:
    raise NameError, "'"+options.eventFilter+"' is not a proper eventFilter name choose: 'data', 'sig(PU)', 'bkg(PU)', 'qcd' or 'all(Redigi(PU))'"

## adapt output filename
process.TFileService.fileName = 'analyzeFullHadronicSelection_'+options.eventFilter+'.root'

## fully hadronic selection
process.load("TopAnalysis.TopFilter.sequences.fullHadronicSelectionMVA_cff")
from TopAnalysis.TopFilter.sequences.fullHadronicSelectionMVA_cff import *

## do kinematic fit needed for fully hadronic selection
from TopQuarkAnalysis.TopEventProducers.sequences.ttFullHadEvtBuilder_cff import *

addTtFullHadHypotheses(process,
                       ["kKinFit"]
                       )

if( (not options.eventFilter=='sig') and (not options.eventFilter=='sigPU') ):
    removeTtFullHadHypGenMatch(process)

if( options.pdfUn==0 ):
    removePDFUncertainties(process)

## changing bTagger, possible are: TCHELoose, TCHP, SSV, CSV, CSVMVA
## only TCHELoose, TCHE, TCHP, TCHPTight, SSVHE, SSVHPTight and CSV have a officialy blessed WP
#switchToTCHELoose(process)
#switchToCSV(process)
#switchToTCHP(process)
#switchToTCHPTight(process)
#switchToSSVHE(process)
#switchToSSVHPTight(process)

## modify b-tagging discriminator to estimate b-tagging efficiency and mis-tag uncertainty
if(not options.eventFilter=='data'):
    if(options.bTag < 0):
        modifyBTagDiscs(process, 'trackCountingHighEff', 2.84,  9.28)
    elif(options.bTag > 0):
        modifyBTagDiscs(process, 'trackCountingHighEff', 3.90, 11.36)

## selection should be run on PFJets instead of caloJets
if(options.usePF==0): 
    runOnCalo(process)

## if running on real data, do everything needed for this
if(options.eventFilter=='data'):
    runOnData(process)
    ## needed because the patTriggerEvent is to chatty to be used and
    ## data is already skimmed with trigger requirement
    removeTrigger(process)

## do a background estimantion for QCD events
if(not options.backgroundEstimation==0):
    runAsBackgroundEstimation(process)

## increase the resolution of the kinematic fit
increaseKinFitResolution(process, options.fitResol)

## ---
##    run the final sequence
## ---
process.p1 = cms.Path(## do the genEvent selection
                      process.filterSequence *
                      ## do the filtering
                      process.analyseFullHadronicSelection
                      )

## ---
##    pat configuration
## ---
    
if(not options.patify==0):

    ## std sequence for pat
    process.load("PhysicsTools.PatAlgos.patSequences_cff")
    
    ## configure output module
    process.out = cms.OutputModule("PoolOutputModule",
        outputCommands = cms.untracked.vstring('drop *'),
        dropMetaData = cms.untracked.string('DROPPED'),
        fileName = cms.untracked.string('patTuple_6jets.root')
    )
    
    ## remove MC matching, photons, taus and cleaning from PAT default sequence
    from PhysicsTools.PatAlgos.tools.coreTools import *
    removeCleaning(process)
    if(options.eventFilter=='data'):
        removeMCMatching(process, ['All'])
    
    ## restrict needed input to AOD event content
    restrictInputToAOD(process)
    
    ## Add particle flow jets
    from PhysicsTools.PatAlgos.tools.jetTools import *
    
    if(options.eventFilter=='data'):
        addJetCollection(process,cms.InputTag('ak5PFJets'),'AK5','PF',
                         doJTA        = True,
                         doBTagging   = True,
                         jetCorrLabel = ('AK5PF', ['L2Relative', 'L3Absolute', 'L2L3Residual']),
                         doType1MET   = False,
                         doL1Cleaning = False,
                         doL1Counters = False,
                         genJetCollection=None,
                         doJetID      = True,
                         )
    
    else:
        addJetCollection(process,cms.InputTag('ak5PFJets'),'AK5','PF',
                         doJTA        = True,
                         doBTagging   = True,
                         jetCorrLabel = ('AK5PF', ['L2Relative', 'L3Absolute']),
                         doType1MET   = False,
                         doL1Cleaning = False,
                         doL1Counters = False,
                         genJetCollection=cms.InputTag('ak5GenJets'),
                         doJetID      = True,
                         )
        process.patJetCorrFactors.levels.remove('L2L3Residual')
    
    
    from PhysicsTools.PatAlgos.tools.metTools import *
    ## Add PfMET to the event content
    addPfMET(process, 'PF')
    
    ## embedding of jet constituents into the jets
    process.patJets.embedCaloTowers = True
    process.patJetsAK5PF.embedPFCandidates = True
    
    ## remove TagInfos from jets
    process.patJets.addTagInfos = False
    process.patJetsAK5PF.addTagInfos = False
    
    ## embedding of resolutions into the patObjects
    process.load("TopQuarkAnalysis.TopObjectResolutions.stringResolutions_etEtaPhi_cff")
    process.patJets.addResolutions = True
    process.patJets.resolutions = cms.PSet(
        default = cms.string("udscResolution"),
        bjets = cms.string("bjetResolution"),
        )
    process.patJetsAK5PF.addResolutions = True
    process.patJetsAK5PF.resolutions = cms.PSet(
        default = cms.string("udscResolutionPF"),
        bjets = cms.string("bjetResolutionPF"),
        )
    process.patElectrons.addResolutions = True
    process.patElectrons.resolutions = cms.PSet( default = cms.string("elecResolution") )
    process.patMuons.addResolutions = True
    process.patMuons.resolutions = cms.PSet( default = cms.string("muonResolution") )
    process.patMETs.addResolutions = True
    process.patMETs.resolutions = cms.PSet( default = cms.string("metResolution") )
    process.patMETsPF.addResolutions = True
    process.patMETsPF.resolutions = cms.PSet( default = cms.string("metResolutionPF") )
    
    ## use the correct jet energy corrections
    process.patJetCorrFactors.flavorType = "T"
    process.patJetCorrFactorsAK5PF.flavorType = "T"
    
    # embed IsoDeposits
    process.patMuons.isoDeposits = cms.PSet(
        tracker = cms.InputTag("muIsoDepositTk"),
        ecal    = cms.InputTag("muIsoDepositCalByAssociatorTowers","ecal"),
        hcal    = cms.InputTag("muIsoDepositCalByAssociatorTowers","hcal"),
        user    = cms.VInputTag(
                                cms.InputTag("muIsoDepositCalByAssociatorTowers","ho"),
                                cms.InputTag("muIsoDepositJets")
                                ),
        )
    
    process.dump = cms.EDAnalyzer('EventContentAnalyzer')
    
    process.p1 = cms.Path(## do the triggering
                          process.trigger *
                          ## do the PATification of the event content
                          process.patDefaultSequence *
                          ## do the event selection
                          process.filterSequence *
                          #process.dump *
                          ## do the filtering
                          process.analyseFullHadronicSelection)

#useTreesAsOutput(process)

## search for b' -> Zb instead of top quark pairs
#bPrimeSearchMode(process)

if(options.eventFilter=='data'):
    process.p1.remove(process.filterSequence)

if(not options.eventFilter=='data'):
    # different energy resolution of jets in simulation
    if(hasattr(process, 'goodJets') & hasattr(process, 'scaledJetEnergy')):
        process.goodJets.src   = cms.InputTag('scaledJetEnergy', 'selectedPatJets', processName)
    if(hasattr(process, 'goodJetsPF') & hasattr(process, 'scaledJetEnergy')):
        process.goodJetsPF.src = cms.InputTag('scaledJetEnergy', 'selectedPatJetsAK5PF', processName)


## ATTENTION: some Fall10 samples are REDIGI and some are NOT
if(options.eventFilter=='allRedigi'):
    from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
    massSearchReplaceAnyInputTag(process.analyseFullHadronicSelection, cms.InputTag("TriggerResults","","HLT"), cms.InputTag("TriggerResults","","REDIGI38X"))
    #process.trigger.TriggerResultsTag   = cms.InputTag("TriggerResults","","REDIGI38X")
    process.patTrigger.processName      = 'REDIGI38X'
    process.patTriggerEvent.processName = 'REDIGI38X'

elif(options.eventFilter=='allRedigiPU' or options.eventFilter=='sigPU' or options.eventFilter=='bkgPU'):
    from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
    massSearchReplaceAnyInputTag(process.analyseFullHadronicSelection, cms.InputTag("TriggerResults","","HLT"), cms.InputTag("TriggerResults","","REDIGI38XPU"))
    #process.trigger.TriggerResultsTag   = cms.InputTag("TriggerResults","","REDIGI38XPU")
    process.patTrigger.processName      = 'REDIGI38XPU'
    process.patTriggerEvent.processName = 'REDIGI38XPU'

## Output Module Configuration
if(options.writeOutput):
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
