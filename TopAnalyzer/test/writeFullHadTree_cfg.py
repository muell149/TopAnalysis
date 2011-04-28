import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing
import sys

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
#options.register('backgroundEstimation', 0 , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "do a background estimation")
## do PATification on the fly, not depending on pre-made PAT tuples anymore
#options.register('patify', 0 , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "run PAT on the fly")
## include b-tag efficiency and mis-tag rate in FullHadTreeWriter's TTree
options.register('bTagPara', 1 , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "include bTagEff and mis-tag rate")
## change b-tagging discriminator for b-tagging uncertainty measurement
options.register('bTag', 0 , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "bTag uncertainty")

# get and parse the command line arguments
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
#print "backgroundEstimation:", options.backgroundEstimation
#print "patify  . . . . . . :", options.patify
print "bTagParametersOn  . :", options.bTagPara
print "bTag  . . . . . . . :", options.bTag

## use the FullHadTreeWriter to produce a TTree with the desired information
processName = "FullHadTreeWriter"
process = cms.Process(processName)

## configure message logger
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

# use only when PATTrigger is needed on data to suppress useless error messages
process.MessageLogger.cerr.default.limit = 0

## define input
process.source = cms.Source("PoolSource",
    ## add your favourite file here
    fileNames = cms.untracked.vstring(
    #'file:/tmp/eschliec/tmp.root',
    #'/store/user/eschliec/MultiJet/PAT_6Jets/00b550d1515f7d6868b450d1e5dca901/patTuple_6jets_16_1_oqr.root',
    #'/store/user/eschliec/MultiJet/PAT_6Jets/00b550d1515f7d6868b450d1e5dca901/patTuple_6jets_19_1_CQa.root',
    '/store/user/henderle/TTJets_TuneD6T_7TeV-madgraph-tauola/PAT_FALL10HH/6c1c00d4602477b58cef63f182ce0614/fall10MC_14_3_M5Q.root',
    #'/store/user/henderle/TTJets_TuneD6T_7TeV-madgraph-tauola/PAT_FALL10HH/6c1c00d4602477b58cef63f182ce0614/fall10MC_15_1_5ob.root',
    #'/store/user/henderle/TTJets_TuneD6T_7TeV-madgraph-tauola/PAT_FALL10HH/6c1c00d4602477b58cef63f182ce0614/fall10MC_12_1_Bay.root',
    #'/store/user/henderle/TTJets_TuneD6T_7TeV-madgraph-tauola/PAT_FALL10HH/6c1c00d4602477b58cef63f182ce0614/fall10MC_18_1_WVA.root',
    #'/store/user/henderle/TTJets_TuneD6T_7TeV-madgraph-tauola/PAT_FALL10HH/6c1c00d4602477b58cef63f182ce0614/fall10MC_11_1_yZl.root',
    #'/store/user/henderle/TTJets_TuneD6T_7TeV-madgraph-tauola/PAT_FALL10HH/6c1c00d4602477b58cef63f182ce0614/fall10MC_17_1_dZv.root',
    #'/store/user/henderle/TTJets_TuneD6T_7TeV-madgraph-tauola/PAT_FALL10HH/6c1c00d4602477b58cef63f182ce0614/fall10MC_10_1_6nQ.root',
    #'/store/user/henderle/TTJets_TuneD6T_7TeV-madgraph-tauola/PAT_FALL10HH/6c1c00d4602477b58cef63f182ce0614/fall10MC_13_1_Csv.root',
    #'/store/user/henderle/TTJets_TuneD6T_7TeV-madgraph-tauola/PAT_FALL10HH/6c1c00d4602477b58cef63f182ce0614/fall10MC_16_1_IWI.root',
    #'/store/user/henderle/TTJets_TuneD6T_7TeV-madgraph-tauola/PAT_FALL10HH/6c1c00d4602477b58cef63f182ce0614/fall10MC_4_1_KIn.root',
    #'/store/user/henderle/TTJets_TuneD6T_7TeV-madgraph-tauola/PAT_FALL10HH/6c1c00d4602477b58cef63f182ce0614/fall10MC_8_1_qD9.root',
    #'/store/user/henderle/TTJets_TuneD6T_7TeV-madgraph-tauola/PAT_FALL10HH/6c1c00d4602477b58cef63f182ce0614/fall10MC_6_1_Kur.root',
    #'/store/user/henderle/TTJets_TuneD6T_7TeV-madgraph-tauola/PAT_FALL10HH/6c1c00d4602477b58cef63f182ce0614/fall10MC_3_1_4da.root',
    #'/store/user/henderle/TTJets_TuneD6T_7TeV-madgraph-tauola/PAT_FALL10HH/6c1c00d4602477b58cef63f182ce0614/fall10MC_9_1_WVh.root',
    #'/store/user/henderle/TTJets_TuneD6T_7TeV-madgraph-tauola/PAT_FALL10HH/6c1c00d4602477b58cef63f182ce0614/fall10MC_2_1_I75.root',
    #'/store/user/henderle/TTJets_TuneD6T_7TeV-madgraph-tauola/PAT_FALL10HH/6c1c00d4602477b58cef63f182ce0614/fall10MC_7_1_UxQ.root',
    #'/store/user/henderle/TTJets_TuneD6T_7TeV-madgraph-tauola/PAT_FALL10HH/6c1c00d4602477b58cef63f182ce0614/fall10MC_1_1_qGb.root',
    #'/store/user/henderle/TTJets_TuneD6T_7TeV-madgraph-tauola/PAT_FALL10HH/6c1c00d4602477b58cef63f182ce0614/fall10MC_5_1_wzx.root',
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
            fileName = cms.string('writeFullHadTree_test.root')
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
process.scaledJetEnergy = process.scaledJetEnergy.clone( inputJets            = cms.InputTag("selectedPatJets"),
                                                         inputMETs            = cms.InputTag("patMETs"),
                                                         payload              = cms.string("AK5Calo"),
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
    raise NameError, "'"+options.eventFilter+"' is not a prober eventFilter name choose: 'data', 'sig', 'bkg', 'qcd', 'privA', 'privB' or 'all'"

## fully hadronic selection
process.load("TopAnalysis.TopFilter.sequences.fullHadronicSelection_cff")
from TopAnalysis.TopFilter.sequences.fullHadronicSelection_cff import *

## do kinematic fit needed for fully hadronic selection
from TopQuarkAnalysis.TopEventProducers.sequences.ttFullHadEvtBuilder_cff import *

addTtFullHadHypotheses(process,
                       ["kKinFit"]
                       )

if( (not options.eventFilter=='sig') and (not options.eventFilter=='sigPU') ):
    removeTtFullHadHypGenMatch(process)

## changing bTagger, possible are: TCHE, TCHPTight, SSV, CSV, CSVMVA
## only TCHE, TCHPTight, SSV and CSV have a officialy blessed WP like the default (TCHP)
switchToTCHE(process)
#switchToCSV(process)
#switchToTCHPTight(process)

## modify b-tagging discriminator to estimate b-tagging efficiency and mis-tag uncertainty
if(not options.eventFilter=='data'):
    if(options.bTag < 0):
        modifyBTagDiscs(process, 'trackCountingHighEff', 2.17,  9.73)
    elif(options.bTag > 0):
        modifyBTagDiscs(process, 'trackCountingHighEff', 4.71, 12.46)

## selection should be run on PFJets instead of caloJets
if(not options.usePF==0): 
    runOnPF(process)

## if running on real data, do everything needed for this
if(options.eventFilter=='data'):
    runOnRealData(process)
    ## needed because the patTriggerEvent is to chatty to be used and
    ## data is already skimmed with trigger requirement
    #removeDefaultTrigger(process)

## increase the resolution of the kinematic fit
increaseKinFitResolution(process, options.fitResol)

## remove cutflow monitoring
removeMonitoringOfCutflow(process)

## THE treeWriter itself
process.load("TopAnalysis.TopAnalyzer.FullHadTreeWriter_cfi")

## switch tree writer to appropriate jet source
process.FullHadTreeWriter = process.writeFullHadTree.clone(JetSrc = "tightLeadingJets")

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
                      process.analyseFullHadronicSelection *
                      ## write the tree
                      process.FullHadTreeWriter
                      )

process.p1.remove(process.tightBottomJetSelection_v1)
process.p1.remove(process.tightBottomJetSelection_v2)
process.p1.remove(process.filterKinFitQuality)

if( options.pdfUn==2 and (options.eventFilter=='sig' or options.eventFilter=='bkg') ):
    print "Writing TTree for all", options.eventFilter, "events, no further selection done!"
    process.p1.remove(process.analyseFullHadronicSelection)

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

