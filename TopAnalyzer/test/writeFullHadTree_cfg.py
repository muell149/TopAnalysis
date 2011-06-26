import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing
import sys

# setup 'standard' options
options = VarParsing.VarParsing ('standard')
## decide whether to run on:  * data *, * sig *, * sigPU *, * bkg *, * bkgPU *, * qcd *, * allRedigi *, * allRedigiPU * or * all *
options.register('eventFilter', 'data', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "kind of data to be processed")
## choose whether to use PF or not
options.register('usePF'      , True , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.bool , "use PF for processing")
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
options.register('backgroundEstimation', False , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.bool, "do a background estimation")
## run directly on AOD, do everything on the fly
options.register('runOnAOD', False , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.bool, "run on AOD, do everything on the fly")
## include b-tag efficiency and mis-tag rate in FullHadTreeWriter's TTree
options.register('bTagPara', 1 , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "include bTagEff and mis-tag rate")
## change b-tagging discriminator for b-tagging uncertainty measurement
options.register('bTag', 0 , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "bTag uncertainty")
## which b-tag algo and WP should be used
options.register('bTagAlgoWP', 'SSVHEM', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "which b-tag algo and WP should be used")
## do mva selection instead of old style selection
options.register('mvaSelection', True , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.bool, "mva selection")
## weight of events (should be used only for MC samples)
options.register('mcWeight', 1.0 , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.float, "MC sample event weight")
## which PU scenario for PU reweighting
options.register('PUscenario', '11_165542', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "PU distribution used for MC PUweight calculation")

# get and parse the command line arguments
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
print "runOnAOD  . . . . . :", options.runOnAOD
print "bTagParametersOn  . :", options.bTagPara
print "bTag  . . . . . . . :", options.bTag
print "bTagAlgoWP  . . . . :", options.bTagAlgoWP
print "mvaSelection  . . . :", options.mvaSelection
print "mcWeight  . . . . . :", options.mcWeight
print "PUscenario  . . . . :", options.PUscenario

## use the FullHadTreeWriter to produce a TTree with the desired information
process = cms.Process("FullHadTreeWriter")

## configure message logger
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

# use only when PATTrigger is needed on data to suppress useless error messages
#process.MessageLogger.cerr.default.limit = 0

## define input
process.source = cms.Source("PoolSource",
    ## add your favourite file here
    fileNames = cms.untracked.vstring(
    #'file:patTuple.root',
    #'file:/tmp/eschliec/tmp.root',
    '/store/user/eschliec/TTJets_TuneZ2_7TeV-madgraph-tauola/PATWithPF_v4/247cdaa1cf6bc716522e6e8a50301fbd/patTuple_131_1_MfV.root',
    '/store/user/eschliec/TTJets_TuneZ2_7TeV-madgraph-tauola/PATWithPF_v4/247cdaa1cf6bc716522e6e8a50301fbd/patTuple_182_1_CNE.root',
    #'/store/user/eschliec/MultiJet/Run2011A_v42_PATWithPF_v4/9610e89f650df43cf8a89da2e1021a9c/patTuple_9_1_LMr.root',
    #'/store/user/eschliec/MultiJet/Run2011A_v42_PATWithPF_v4/9610e89f650df43cf8a89da2e1021a9c/patTuple_8_1_OjE.root',
    ),
                            skipEvents = cms.untracked.uint32(0)
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
            fileName = cms.string('writeFullHadTree_test.root')
)

## configure geometry & conditions
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")

if(options.eventFilter=='data'):
    #process.GlobalTag.globaltag = cms.string('GR_R_38X_V15::All')
    process.GlobalTag.globaltag = cms.string('GR_R_42_V14::All')
else:
    #process.GlobalTag.globaltag = cms.string('START38_V14::All')
    #process.GlobalTag.globaltag = cms.string('START41_V0::All')
    process.GlobalTag.globaltag = cms.string('START42_V12::All')

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
                                                         payload              = cms.string("AK5PFchs"),
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
    raise NameError, "'"+options.eventFilter+"' is not a proper eventFilter!"

# adapt output filename
process.TFileService.fileName = 'writeFullHadTree_test_'+options.eventFilter+'.root'

## fully hadronic selection
if options.mvaSelection:
    process.load("TopAnalysis.TopFilter.sequences.fullHadronicSelectionMVA_cff")
    from TopAnalysis.TopFilter.sequences.fullHadronicSelectionMVA_cff import *
else:
    process.load("TopAnalysis.TopFilter.sequences.fullHadronicSelection_cff")
    from TopAnalysis.TopFilter.sequences.fullHadronicSelection_cff import *

## do kinematic fit needed for fully hadronic selection
from TopQuarkAnalysis.TopEventProducers.sequences.ttFullHadEvtBuilder_cff import *

addTtFullHadHypotheses(process,
                       ["kKinFit"]
                       )

if( (not options.eventFilter=='sig') and (not options.eventFilter=='sigPU') ):
    removeTtFullHadHypGenMatch(process)

## changing bTagger, possible are: TCHEL, TCHEM, TCHPM, TCHPT, SSVHEM, SSVHPT, CSV, CSVMVA
## only TCHEL, TCHEM, TCHPM, TCHPT, SSVHEM, SSVHPT and CSV have a officialy blessed WP
if options.bTagAlgoWP == "TCHEM" :
    switchToTCHEM(process)
elif options.bTagAlgoWP == "TCHEL" :
    switchToTCHEL(process)
elif options.bTagAlgoWP == "TCHPM" :
    switchToTCHPM(process)
elif options.bTagAlgoWP == "TCHPT" :
    switchToTCHPT(process)
elif options.bTagAlgoWP == "SSVHEM" :
    switchToSSVHEM(process)
elif options.bTagAlgoWP == "SSVHPT" :
    switchToSSVHPT(process)
elif options.bTagAlgoWP == "CSV" :
    switchToCSV(process)
elif options.bTagAlgoWP == "CSVMVA" :
    switchToCSVMVA(process)
else :
    exit('bTagAlgoWP * ' + options.bTagAlgoWP + " * NOT SUPPORTED, STOP PROCESSING")
    

## modify b-tagging discriminator to estimate b-tagging efficiency and mis-tag uncertainty
if(not options.eventFilter=='data'):
    if(options.bTag < 0):
        modifyBTagDiscs(process, 'trackCountingHighEff', 2.84,  9.28)
    elif(options.bTag > 0):
        modifyBTagDiscs(process, 'trackCountingHighEff', 3.90, 11.36)

## selection should be run on PFJets instead of caloJets
if not options.usePF: 
    runOnCalo(process)

## if running on real data, do everything needed for this
if(options.eventFilter=='data'):
    runOnData(process)
    ## needed because the patTriggerEvent is to chatty to be used and
    ## data is already skimmed with trigger requirement
    #removeTrigger(process)

## increase the resolution of the kinematic fit
increaseKinFitResolution(process, options.fitResol)

## remove cutflow monitoring
removeMonitoringOfCutflow(process)

## THE treeWriter itself
process.load("TopAnalysis.TopAnalyzer.FullHadTreeWriter_cfi")

## switch tree writer to appropriate jet source
process.FullHadTreeWriter = process.writeFullHadTree.clone(JetSrc = "tightLeadingJets")

## set correct MC weight
process.FullHadTreeWriter.MCweight = options.mcWeight

process.load("TopAnalysis.TopUtils.EventWeightPU_cfi")
process.eventWeightPU = process.eventWeightPU.clone()
if options.PUscenario == '11_165542':
    process.eventWeightPU.DataFile = "TopAnalysis/TopUtils/data/Data_PUDist_110527.root"
elif options.PUscenario == '11_166502':
    process.eventWeightPU.DataFile = "TopAnalysis/TopUtils/data/Data_PUDist_160404-166502_7TeV_PromptReco_Collisions11.root"
elif options.PUscenario == '11_May10':
    process.eventWeightPU.DataFile = "TopAnalysis/TopUtils/data/Data_PUDist_160404-163869_7TeV_May10ReReco_Collisions11.root"
elif options.PUscenario == '10_Apr21':
    process.eventWeightPU.DataFile = "TopAnalysis/TopUtils/data/Data_PUDist_136033-149442_7TeV_Apr21ReReco_Collisions10.root"
elif not options.eventFilter == 'data':
    exit('PU SCENARIO * ' + options.PUscenario + " * NOT SUPPORTED, STOP PROCESSING")

## switch bTagEff and mis-tag rate for FullHadTreeWriter
if( options.bTagPara==0 ):
    process.FullHadTreeWriter.bTagParams = 0

## remove PDF uncertainties
removePDFUncertainties(process)
if( options.pdfUn==0 ):
    process.FullHadTreeWriter.GenSrc = ""

## get b-tag efficiency infos
process.load ("RecoBTag.PerformanceDB.PoolBTagPerformanceDBMC36X")
process.load ("RecoBTag.PerformanceDB.BTagPerformanceDBMC36X")

process.load ("RecoBTag.PerformanceDB.PoolBTagPerformanceDB1101")
process.load ("RecoBTag.PerformanceDB.BTagPerformanceDB1101")

## ---
##    run the final sequence
## ---
process.p1 = cms.Path(## do the genEvent selection
                      process.filterSequence *
                      ## do the filtering
                      process.createJetCollections *
                      process.leadingJetSelection  *
                      process.eventWeightPU        *
                      process.makeTtFullHadEvent   *
                      ## write the tree
                      process.FullHadTreeWriter
                      )

if options.mvaSelection:
    process.p1.replace(process.leadingJetSelection,process.leadingJetSelection*process.mvaDisc)
    process.p1.remove(process.trackCountingHighEffBJets)
    process.p1.remove(process.tightBottomJets)

if options.backgroundEstimation:
    runAsBackgroundEstimation(process)
    process.p1.remove(process.makeTtFullHadEvent)
    process.p1.remove(process.FullHadTreeWriter)
    #if(not options.eventFilter=='data'):
    process.analyzeFullHadQCDEstimation.bTagAlgoWP = "TCHEM40MC"
    print "#################################################"
    print "#################################################"
    print "## QCDEstimation DONE WITHOUT L2L3Residual JEC ##"
    print "## QCDEstimation DONE WITHOUT L2L3Residual JEC ##"
    print "## QCDEstimation DONE WITHOUT L2L3Residual JEC ##"
    print "## QCDEstimation DONE WITHOUT L2L3Residual JEC ##"
    print "#################################################"
    print "#################################################"

    if options.usePF:
        getattr(process, process.tightBottomJets.src.getModuleLabel()).src = cms.InputTag("goodJetsPF")
                 
    process.p1 += cms.Sequence(getattr(process, process.tightBottomJets.src.getModuleLabel()) *
                               process.tightBottomJets                                        *
                               process.tightBottomJetSelection                                *
                               process.analyzeFullHadQCDEstimation
                               )

    process.TFileService.fileName = 'QCDEstimation_'+options.eventFilter+'.root'

if(options.pdfUn==2 and (options.eventFilter=='sig' or options.eventFilter=='bkg')):
    print "Writing TTree for all", options.eventFilter, "events, no further selection done!"
    process.p1.remove(process.analyseFullHadronicSelection)

if options.eventFilter=='data':
    process.p1.remove(process.filterSequence)
    process.p1.remove(process.eventWeightPU)
else:
    # different energy resolution of jets in simulation
    if(hasattr(process, 'goodJets') & hasattr(process, 'scaledJetEnergy')):
        process.goodJets.src   = cms.InputTag('scaledJetEnergy', 'selectedPatJets', process.name_())
    if(hasattr(process, 'goodJetsPF') & hasattr(process, 'scaledJetEnergy')):
        process.goodJetsPF.src = cms.InputTag('scaledJetEnergy', 'selectedPatJetsAK5PF', process.name_())


## prepend the sequence needed to run on the NEW PAT tuples
from TopAnalysis.TopUtils.usePatTupleWithParticleFlow_cff import prependPF2PATSequence
pf2patOptions = {'runOnOLDcfg': True}
pf2patOptions['electronIDs'] = ''
if options.eventFilter=='data':
    pf2patOptions['runOnMC'] = False
if options.runOnAOD:
    pf2patOptions['runOnAOD'] = True
prependPF2PATSequence(process, options = pf2patOptions)

## adaptions (re-aranging of modules) to speed up processing
pathnames = process.paths_().keys()
for pathname in pathnames:
    ## move the ttGenEvent filter to the beginning of the sequence
    if options.eventFilter=='sig' or options.eventFilter=='bkg' or options.eventFilter=='sigPU' or options.eventFilter=='bkgPU':
        getattr(process, pathname).remove(process.ttFullHadronicFilter)
        getattr(process, pathname).insert(0,process.ttFullHadronicFilter)
        getattr(process, pathname).remove(process.genEvt)
        getattr(process, pathname).insert(0,process.genEvt)
        getattr(process, pathname).remove(process.decaySubset)
        getattr(process, pathname).insert(0,process.decaySubset)
        getattr(process, pathname).remove(process.initSubset)
        getattr(process, pathname).insert(0,process.initSubset)
    ## move the trigger to the beginning of the sequence
    getattr(process, pathname).remove(process.trigger)
    getattr(process, pathname).insert(0,process.trigger)


## ATTENTION: some Fall10 samples are REDIGI and some are NOT
if options.eventFilter=='allRedigi':
    from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
    massSearchReplaceAnyInputTag(process.analyseFullHadronicSelection, cms.InputTag("TriggerResults","","HLT"), cms.InputTag("TriggerResults","","REDIGI38X"))
    #process.trigger.TriggerResultsTag   = cms.InputTag("TriggerResults","","REDIGI38X")
    process.patTrigger.processName      = 'REDIGI38X'
    process.patTriggerEvent.processName = 'REDIGI38X'

elif options.eventFilter=='allRedigiPU' or options.eventFilter=='sigPU' or options.eventFilter=='bkgPU':
    from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
    massSearchReplaceAnyInputTag(process.analyseFullHadronicSelection, cms.InputTag("TriggerResults","","HLT"), cms.InputTag("TriggerResults","","REDIGI38XPU"))
    #process.trigger.TriggerResultsTag   = cms.InputTag("TriggerResults","","REDIGI38XPU")
    process.patTrigger.processName      = 'REDIGI38XPU'
    process.patTriggerEvent.processName = 'REDIGI38XPU'

