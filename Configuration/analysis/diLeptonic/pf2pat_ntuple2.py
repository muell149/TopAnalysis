import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing
import sys
import os


####################################################################
# global job options

MAXEVENTS = -1
REPORTEVERY = 10000
WANTSUMMARY = True

####################################################################

process = cms.Process("pf2patDilepton")
#SimpleMemoryCheck = cms.Service("SimpleMemoryCheck",ignoreTotal = cms.untracked.int32(1) )

####################################################################
# setup command line options
options = VarParsing.VarParsing ('standard')
options.register('runOnMC', True, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.bool, "decide to run on MC or data")
options.register('runOnAOD', False, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.bool, "run on AOD")
options.register('globalTag', '', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "which globalTag should be used")
options.register('mode', '', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "which type of analysis to run")
options.register('samplename', 'standard', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "which sample to run over")
options.register('inputScript', '', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "python file with input source")
options.register('outputFile', '', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "root output file")
options.register('rereco', False, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.bool, "is rereco")
options.register('prompt', False, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.bool, "is prompt")
options.register('syncExcercise', False, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.bool, "do sync excercise, i.e. print all event numbers")
options.register('json', '', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "limit to certain lumis")
options.register('skipEvents', 0, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "skip N events")
options.register('pu', '', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "Pileup distribution input file")

# get and parse the command line arguments
if( hasattr(sys, "argv") ):
    for args in sys.argv :
        arg = args.split(',')
        for val in arg:
            val = val.split('=')
            if(len(val)==2):
                setattr(options,val[0], val[1])

print options.mode
if options.mode == '':
    print 'cannot run without specifying a mode'
    exit(8888)

if options.samplename == 'realdata':
    options.runOnMC = False

####################################################################
# define input

if options.inputScript != '':
    process.load(options.inputScript)
else:
    print 'need an input script'
    exit(8889)

####################################################################
# limit to json file (if passed as parameter)

if options.json != '':
    import PhysicsTools.PythonAnalysis.LumiList as LumiList
    import FWCore.ParameterSet.Types as CfgTypes
    myLumis = LumiList.LumiList(filename = options.json).getCMSSWString().split(',')
    process.source.lumisToProcess = CfgTypes.untracked(CfgTypes.VLuminosityBlockRange())
    process.source.lumisToProcess.extend(myLumis)

if options.skipEvents > 0:
    process.source.skipEvents = cms.untracked.uint32(options.skipEvents)

####################################################################

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = REPORTEVERY

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(WANTSUMMARY)
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(MAXEVENTS)
)

####################################################################
# Geometry and Detector Conditions

process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")

if options.globalTag != '':
    process.GlobalTag.globaltag = cms.string( options.globalTag )
else:
    from Configuration.PyReleaseValidation.autoCond import autoCond
    if options.runOnMC:
        #process.GlobalTag.globaltag = cms.string( autoCond[ 'startup' ] )
        #process.GlobalTag.globaltag = cms.string("START42_V13::All")
        process.GlobalTag.globaltag = cms.string("START42_V17::All")
    else:
        #process.GlobalTag.globaltag = cms.string( autoCond[ 'com10' ] )
        #process.GlobalTag.globaltag = cms.string( 'GR_R_42_V19::All' )
        process.GlobalTag.globaltag = cms.string( 'GR_R_42_V23::All' )

process.load("Configuration.StandardSequences.MagneticField_cff")

####################################################################

# Pythia rejection
process.load("GeneratorInterface.GenFilters.TotalKinematicsFilter_cfi")
process.totalKinematicsFilter.tolerance = 5
# set default cut to 5 GeV istead of 0.5 GeV https://indico.cern.ch/conferenceDisplay.py?confId=153867
# adds process.totalKinematicsFilter

# trigger filtering

process.load("TopAnalysis.TopFilter.filters.TriggerFilter_cfi")
process.filterTrigger.TriggerResults = cms.InputTag('TriggerResults','','HLT')
process.filterTrigger.printTriggers = False
if options.mode == 'mumu':
    ttFilterChannelName = 'MuonMuon'
    process.filterTrigger.hltPaths  = cms.vstring(
        'HLT_Mu10_Ele10_CaloIdL_*',
        'HLT_DoubleMu6_v*',
        'HLT_DoubleMu7_v*',
        'HLT_Mu13_Mu8_v*',
        'HLT_Mu17_Mu8_v*',
        'HLT_DoubleMu45_v*'
    )

elif options.mode == 'emu':
    ttFilterChannelName = 'ElectronMuon'
    process.filterTrigger.hltPaths  = cms.vstring(
        'HLT_Mu10_Ele10_CaloIdL_*',
        'HLT_Mu8_Ele17_CaloIdL_*',
        'HLT_Mu17_Ele8_CaloIdL_*',
        'HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_v*',
        'HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_v*',
        'HLT_Mu10_Ele10_CaloIdL_v*'
    )
elif options.mode == 'ee':
    ttFilterChannelName = 'ElectronElectron'
    process.filterTrigger.hltPaths  = cms.vstring(
        'HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v*',
        'HLT_Ele17_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_v*',
        'HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v*',
        'HLT_DoubleEle45_CaloIdL_v*',
    )
else:
    print 'ERROR: unrecognised mode ' + options.mode +'\nuse ee, emu, or mumu'
    exit(8888)


####################################################################
# add output


process.EventSelection = cms.PSet(
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring( 'p' )
    )
)

process.outPF = cms.OutputModule("PoolOutputModule",
    process.EventSelection,
    outputCommands = cms.untracked.vstring('drop *'),
    dropMetaData = cms.untracked.string("DROPPED"),
    fileName = cms.untracked.string(os.getenv('TMPDIR', '.') + '/datapat.root')
)

from PhysicsTools.PatAlgos.patEventContent_cff import *
process.outPF.outputCommands += patExtraAodEventContent
process.outPF.outputCommands += patEventContentNoCleaning
process.outPF.outputCommands += ['drop *_towerMaker_*_*',
                                 'keep *_TriggerResults_*_*',
                                 'keep *_hltTriggerSummaryAOD_*_*',
                                 'keep L1GlobalTriggerReadoutRecord_gtDigis_*_*',
                                 'keep *_ak5JetID_*_*',
                                 'keep *_gsf*_*_*',
                                 'keep *DcsStatus*_*_*_*',
                                 ]

#process.outpath = cms.EndPath(process.outPF)


####################################################################
# setup selections for PF2PAT & PAT objects

# selection values
electronSelectionPF = cms.string('    gsfTrackRef.isNonnull '
#                                 ' && conversionRef.isNonnull' not available
#                                 ' && gsfElectronRef.isNonnull' not available
                               #  ' && et > 20 '
                                 ' && pt > 20 '
                                 ' && abs(eta) < 2.4'
                                 ' && gsfTrackRef.trackerExpectedHitsInner.numberOfLostHits < 2' # conversion rejection 1/3
                                 )

electronSelectionPAT = cms.string('  abs(dB) < 0.04'             # not available in PF
                                  #' && isGsfCtfScPixChargeConsistent()'
#                                  ' && (abs(convDcot) > 0.02'  # not available in PF # conversion rejection 2/3
#                                  '     || abs(convDist) > 0.02)'  # not available in PF # conversion rejection 3/3
                                 )

electronSelectionCiC = cms.string(eval(electronSelectionPAT.pythonValue())+
                                  ' && test_bit( electronID("eidTightMC"), 0)'
                                  )

electronSelectionOldID = cms.string(eval(electronSelectionPAT.pythonValue())+
                                    ' && test_bit( electronID(\"simpleEleId90cIso\") , 0 )'
                                    )


electronIsolation = 0.17
electronIsolationCone = 0.3

muonSelectionPF = cms.string(' pt > 20 '
                            #' et > 20 '
                             ' && abs(eta) < 2.4'
                             ' && muonRef.isNonnull '                                           # can be void!
                             ' && muonRef.innerTrack.isNonnull'                                 # can be void!
                             ' && muonRef.globalTrack.isNonnull'                                # can be void!
                             ' && muonRef.innerTrack.numberOfValidHits > 10'
                             ' && muonRef.globalTrack.hitPattern.numberOfValidMuonHits > 0'
                             ' && muonRef.globalTrack.normalizedChi2 < 10.0'
                             )

muonSelectionPAT = cms.string('    isGlobalMuon'   # not available in PF
                              ' && isTrackerMuon ' # not available in PF
                              ' && abs(dB) < 0.02'      # not available in PF
                              )

muonIsolation = 0.2
muonIsolationCone = 0.3

# setup part running PAT objects

from PhysicsTools.PatAlgos.selectionLayer1.electronSelector_cfi import *
from PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi import *

process.fullySelectedPatElectronsCiC = selectedPatElectrons.clone(
    src = 'selectedPatElectrons',
    cut = electronSelectionCiC)

process.fullySelectedPatElectronsOldID = selectedPatElectrons.clone(
    src = 'selectedPatElectrons',
    cut = electronSelectionOldID)

process.fullySelectedPatMuons = selectedPatMuons.clone(
    src = 'selectedPatMuons',
    cut = muonSelectionPAT)

process.additionalPatSelection = cms.Sequence( process.fullySelectedPatElectronsCiC *
                                               process.fullySelectedPatElectronsOldID *
                                               process.fullySelectedPatMuons )

process.unisolatedMuons = selectedPatMuons.clone(
    src = 'noCutPatMuons',
    cut = ' pt > 20 '
            ' && abs(eta) < 2.4'
            ' && innerTrack.isNonnull'
            ' && globalTrack.isNonnull'
            ' && innerTrack.numberOfValidHits > 10'
            ' && globalTrack.hitPattern.numberOfValidMuonHits > 0'
            ' && globalTrack.normalizedChi2 < 10.0'
            ' && ' + eval(muonSelectionPAT.pythonValue()))

process.unisolatedElectrons = selectedPatElectrons.clone(
    src = 'noCutPatElectrons',
    cut =  ' pt > 20 '
            ' && abs(eta) < 2.4'
            ' && gsfTrack.trackerExpectedHitsInner.numberOfLostHits < 2'
            #' && isGsfCtfScPixChargeConsistent'
            ' && ' + eval(electronSelectionCiC.pythonValue()))

print 'additional selection on top of PF selection (not used in top projection):'
print '  electrons CiC: ', electronSelectionCiC
print '  electrons OldID: ', electronSelectionOldID
print '  muons: ', muonSelectionPAT


# skip events (and jet calculation) if event is empty
skipIfNoElectrons = False
skipIfNoMuons     = False
if options.mode == 'mumu':
    skipIfNoMuons = True
elif options.mode == 'emu':
    skipIfNoElectrons = True
    skipIfNoMuons     = True
elif options.mode == 'ee':
    skipIfNoElectrons = True
else:
    print 'ERROR: unrecognised mode ' + options.mode +'\nuse ee, emu, or mumu'
    exit(8888)

####################################################################
# basic debugging analyzer

# process.load("TopAnalysis.TopAnalyzer.CheckDiLeptonAnalyzer_cfi")
# process.analyzeDiLepton.electrons = 'fullySelectedPatElectronsCiC'
# process.analyzeDiLepton.muons = 'fullySelectedPatMuons'

####################################################################
# create path

if options.outputFile == '':
    fn = options.mode + '_test.root'
else:
    fn = options.outputFile
print 'Using output file ' + fn

process.TFileService = cms.Service("TFileService",
    fileName = cms.string(fn)
)

### OLD ANALYSIS STARTS HERE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

mcname = 'standard'

if options.samplename != '':
    mcname = options.samplename

zfilter = False
topfilter = False
signal = False
isdata = False
alsoViaTau = False
useGenCutsInTopSignal = True
filterMadgraphPythiaBug = False
mcpufile = "TopAnalysis/TopUtils/data/MC_PUDist_Summer11_TTJets_TuneZ2_7TeV_madgraph_tauola.root"

if mcname == 'realdata':
    isdata = True

if mcname == 'ttbarsignal':
    topfilter = True
    signal = True
    viaTau = False
    filterMadgraphPythiaBug = True

if mcname == 'ttbarsignalviatau':
    topfilter = True
    signal = True
    viaTau = True
    filterMadgraphPythiaBug = True

if mcname == 'ttbarsignalplustau':
    topfilter = True
    signal = True
    viaTau = False
    alsoViaTau = True
    filterMadgraphPythiaBug = True

if mcname == 'ttbarbg':
    topfilter = True
    filterMadgraphPythiaBug = True

if mcname == 'dyee1050':
    zfilter = True
    zfilterValue = 11
    zrange = (10,50)
    filterMadgraphPythiaBug = True

if mcname == 'dymumu1050':
    zfilter = True
    zfilterValue = 13
    zrange = (10,50)
    filterMadgraphPythiaBug = True

if mcname == 'dytautau1050':
    zfilter = True
    zfilterValue = 15
    zrange = (10,50)
    filterMadgraphPythiaBug = True

if mcname == 'dyee50inf':
    zfilter = True
    zfilterValue = 11
    zrange = (50,1e9)
    filterMadgraphPythiaBug = True

if mcname == 'dymumu50inf':
    zfilter = True
    zfilterValue = 13
    zrange = (50,1e9)
    filterMadgraphPythiaBug = True

if mcname == 'dytautau50inf':
    zfilter = True
    zfilterValue = 15
    zrange = (50,1e9)
    filterMadgraphPythiaBug = True

if mcname == 'wjets':
    filterMadgraphPythiaBug = True

if options.pu != '':
    print "Using user-definded PU file", options.pu
    mcpufile = options.pu

filterMadgraphPythiaBug = filterMadgraphPythiaBug and options.runOnAOD
print "Madgraph/Pythia energy/momentum conservation filter: ", filterMadgraphPythiaBug

if signal:
    print "Not skipping if no leptons -- need true level info\n"
    skipIfNoElectrons = False
    skipIfNoMuons = False

#-------------------------------------------------
# process configuration
#-------------------------------------------------

# Pileup Reweighting
eventWeightPuTag = cms.InputTag('eventWeightPU', 'eventWeightPU')
eventWeightPuTag_Up = cms.InputTag('eventWeightPUsysUp', 'eventWeightPUUp')
eventWeightPuTag_Down = cms.InputTag('eventWeightPUsysDown', 'eventWeightPUDown')
# lepton SF
eventWeightDileptonSfTag = cms.InputTag('eventWeightDileptonSF', 'eventWeightDileptonSF')


if options.runOnMC:
    process.load("TopAnalysis.TopUtils.EventWeightPU_cfi")
    process.eventWeightPU        = process.eventWeightPU.clone()
    process.eventWeightPUsysUp   = process.eventWeightPU.clone()
    process.eventWeightPUsysDown = process.eventWeightPU.clone()

    process.eventWeightPU.WeightName          = "eventWeightPU"
    process.eventWeightPU.Weight3DName        = "eventWeightPU3D"
    process.eventWeightPU.MCSampleFile        = cms.FileInPath("TopAnalysis/TopUtils/data/MC_PUDist_Default2011.root")
    process.eventWeightPU.MCSample3DFile      = cms.FileInPath("TopAnalysis/TopUtils/data/MC_PUDist_Default2011.root")
    process.eventWeightPU.DataFile            = cms.FileInPath("TopAnalysis/TopUtils/data/Data_PUDist_2011Full.root")
    process.eventWeightPU.Data3DFile          = cms.FileInPath("TopAnalysis/TopUtils/data/Data_PUDist_2011Full.root")
    process.eventWeightPU.Weight3DHistoFile   = cms.FileInPath("TopAnalysis/TopUtils/data/DefaultWeight3D.root")

    #Systematics: PU Up/Down
    process.eventWeightPUsysUp.WeightName         = "eventWeightPUUp"
    process.eventWeightPUsysUp.Weight3DName       = "eventWeightPU3DUp"
    process.eventWeightPUsysUp.MCSampleFile        = cms.FileInPath("TopAnalysis/TopUtils/data/MC_PUDist_Default2011.root")
    process.eventWeightPUsysUp.MCSample3DFile      = cms.FileInPath("TopAnalysis/TopUtils/data/MC_PUDist_Default2011.root")
    process.eventWeightPUsysUp.DataFile            = cms.FileInPath("TopAnalysis/TopUtils/data/Data_PUDist_sysUp_2011Full.root")
    process.eventWeightPUsysUp.Data3DFile          = cms.FileInPath("TopAnalysis/TopUtils/data/Data_PUDist_sysUp_2011Full.root")
    process.eventWeightPUsysUp.Weight3DHistoFile   = cms.FileInPath("TopAnalysis/TopUtils/data/DefaultWeight3DUp.root")

    process.eventWeightPUsysDown.WeightName         = "eventWeightPUDown"
    process.eventWeightPUsysDown.Weight3DName       = "eventWeightPU3DDown"
    process.eventWeightPUsysDown.MCSampleFile        = cms.FileInPath("TopAnalysis/TopUtils/data/MC_PUDist_Default2011.root")
    process.eventWeightPUsysDown.MCSample3DFile      = cms.FileInPath("TopAnalysis/TopUtils/data/MC_PUDist_Default2011.root")
    process.eventWeightPUsysDown.DataFile            = cms.FileInPath("TopAnalysis/TopUtils/data/Data_PUDist_sysDown_2011Full.root")
    process.eventWeightPUsysDown.Data3DFile          = cms.FileInPath("TopAnalysis/TopUtils/data/Data_PUDist_sysDown_2011Full.root")
    process.eventWeightPUsysDown.Weight3DHistoFile   = cms.FileInPath("TopAnalysis/TopUtils/data/DefaultWeight3DDown.root")

else:
    process.eventWeightPU = cms.Sequence()

## define which collections and correction you want to be used
isolatedMuonCollection = "fullySelectedPatMuons"
isolatedElecCollection = "fullySelectedPatElectronsCiC"
#isolatedElecCollection = "fullySelectedPatElectronsOldID"
jetCollection = "hardJets"
if options.runOnMC and not options.syncExcercise:
    metCollection = "scaledJetEnergy:patMETs"
else:
    metCollection = "patMETs"

#-------------------------------------------------
# modules
#-------------------------------------------------

## detector conditions and magnetic field

## select DY mass window and decay channel (**MC only**)
if zfilter:
        process.load("TopAnalysis.TopFilter.filters.GeneratorZFilter_cfi")
        process.generatorZFilter.zDecayModes = [zfilterValue]
        process.generatorZFilter.diLeptonMassIntervals = zrange

if topfilter:
        process.load("TopAnalysis.TopFilter.filters.GeneratorTopFilter_cfi")
        if signal:
                process.generatorTopFilter.invert_selection = False
                if viaTau:
                        process.generatorTopFilter.channels = [ttFilterChannelName + 'ViaTau']
                elif alsoViaTau:
                        process.generatorTopFilter.channels = [ttFilterChannelName, ttFilterChannelName + 'ViaTau']
                else:
                        process.generatorTopFilter.channels = [ttFilterChannelName]
        else:
                process.generatorTopFilter.channels = [ttFilterChannelName, ttFilterChannelName + 'ViaTau']
                process.generatorTopFilter.invert_selection = True


## produce pat trigger content
process.load("PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cff")
process.patTriggerEvent.patTriggerMatches = []

## analyze and filter trigger
process.load("TopAnalysis.TopAnalyzer.TriggerAnalyzer_cfi")
process.analyzeTrigger.weightPU = eventWeightPuTag
process.analyzeTrigger.weightLepSF = ""
#process.analyzeTrigger.TriggerResults = cms.InputTag('TriggerResults',         '','REDIGI38X')
#process.analyzeTrigger.TriggerEvent   = cms.InputTag('hltTriggerSummaryAOD',   '','REDIGI38X')
#process.analyzeTrigger.TriggerFilter  = cms.InputTag('hltSingleMu9L3Filtered9','','REDIGI38X')


## Build Jet Collections
process.load("TopAnalysis.TopFilter.sequences.fullLeptonicSelection_cff")

## Lepton-Vertex matching
process.load("TopAnalysis.TopFilter.filters.LeptonVertexFilter_cfi")
process.filterLeptonVertexDistance.muons = isolatedMuonCollection
process.filterLeptonVertexDistance.elecs = isolatedElecCollection


#process.dileptons = cms.EDProducer("CandViewShallowCloneCombiner",
    #checkCharge = cms.bool(True),
    #cut = cms.string('mass > 12'),
    #decay = cms.string(isolatedElecCollection + '@+ ' + isolatedElecCollection + '@- ' +
                       #isolatedMuonCollection + '@+ ' + isolatedElecCollection + '@- ' +
                       #isolatedMuonCollection + '@+ ' + isolatedMuonCollection + '@-'),
#)

#process.dileptonCountFilter = cms.EDFilter("CandViewCountFilter",
    #src = cms.InputTag("dileptons"),
    #minNumber = cms.uint32(1)
#)

from TopAnalysis.TopFilter.filters.DiLeptonFilter_cfi import *
process.filterOppositeCharge = filterLeptonPair.clone(
    electrons    = isolatedElecCollection,
    muons        = isolatedMuonCollection,
    Cut          = (0.,0.),
    filterCharge = -1,
)

process.filterSameCharge = filterLeptonPair.clone(
    electrons    = isolatedElecCollection,
    muons        = isolatedMuonCollection,
    Cut          = (0.,0.),
    filterCharge = 1,
)

from PhysicsTools.PatAlgos.selectionLayer1.leptonCountFilter_cfi import *
process.filterChannel =  countPatLeptons.clone()
process.filterChannel.electronSource    = 'filterOppositeCharge'
process.filterChannel.muonSource        = 'filterOppositeCharge'
process.filterChannel.minNumber         = 2
process.filterChannel.countTaus         = False

leptons3 = 'filterDiLeptonMassQCDveto'
finalLeptons = 'filterDiLeptonMassQCDveto'
if options.mode == 'ee':
    process.filterChannel.countElectrons    = True
    process.filterChannel.countMuons        = False
elif options.mode == 'mumu':
    process.filterChannel.countElectrons    = False
    process.filterChannel.countMuons        = True
else:
    process.filterChannel.minNumber         = 1
    process.filterChannel1 = process.filterChannel.clone()
    process.filterChannel2 = process.filterChannel1.clone()
    process.filterChannel1.countElectrons    = True
    process.filterChannel1.countMuons        = False
    process.filterChannel2.countElectrons    = False
    process.filterChannel2.countMuons        = True
    process.filterChannel = cms.Sequence(process.filterChannel1 * process.filterChannel2)

process.filterDiLeptonMassQCDveto           = filterLeptonPair.clone()
process.filterDiLeptonMassQCDveto.muons     = 'filterOppositeCharge'
process.filterDiLeptonMassQCDveto.electrons = 'filterOppositeCharge'
process.filterDiLeptonMassQCDveto.Cut       = (0.,12.)

## produces weight from lepton SF 
process.load("TopAnalysis.TopUtils.EventWeightDileptonSF_cfi")
process.eventWeightDileptonSF.electrons = cms.InputTag('filterDiLeptonMassQCDveto')
process.eventWeightDileptonSF.muons = cms.InputTag('filterDiLeptonMassQCDveto')

## produces weight for kin reconstruction efficiency SF
process.load("TopAnalysis.TopUtils.EventWeightDileptonKinEffSF_cfi")
process.eventWeightDileptonKinEffSF.electrons = cms.InputTag('filterDiLeptonMassQCDveto')
process.eventWeightDileptonKinEffSF.muons = cms.InputTag('filterDiLeptonMassQCDveto')
process.eventWeightKinEffForNtuple = process.eventWeightDileptonKinEffSF.clone()

## Zveto
process.filterDiLeptonMassZveto = filterLeptonPair.clone(
    electrons = "filterDiLeptonMassQCDveto",
    muons = "filterDiLeptonMassQCDveto",
    Cut   = (76.,106.)
)

process.filterDiLeptonMassZselection = process.filterDiLeptonMassZveto.clone(isVeto = False)
process.ZWindowSelection = cms.Sequence(process.filterDiLeptonMassZselection)

## vertex analyzer
from TopAnalysis.TopAnalyzer.VertexAnalyzer_cfi import analyzePrimaryVertex
analyzePrimaryVertex.weightPU    = eventWeightPuTag
analyzePrimaryVertex.weightLepSF = eventWeightDileptonSfTag
process.analyzeUnscaledVertex = analyzePrimaryVertex.clone(weightPU = "", weightLepSF = "")
process.analyzeVertex2 = analyzePrimaryVertex.clone(weightLepSF = "")
process.analyzeVertex3 = analyzePrimaryVertex.clone()
process.analyzeVertex4 = analyzePrimaryVertex.clone()
process.analyzeVertex5 = analyzePrimaryVertex.clone()
process.analyzeVertex6 = analyzePrimaryVertex.clone()
process.analyzeVertex7 = analyzePrimaryVertex.clone()
process.analyzeVertex8 = analyzePrimaryVertex.clone()
process.analyzeVertex9 = analyzePrimaryVertex.clone()

## jet analyzer
from TopAnalysis.TopAnalyzer.JetAnalyzer_cfi import analyzeJets
analyzeJets.jets = jetCollection
analyzeJets.weightPU    = eventWeightPuTag
analyzeJets.weightLepSF = eventWeightDileptonSfTag

process.analyzeJets3 = analyzeJets.clone()
process.analyzeJets4 = process.analyzeJets3.clone()
process.analyzeJets5 = process.analyzeJets4.clone()
process.analyzeJets6 = process.analyzeJets5.clone()
process.analyzeJets7 = process.analyzeJets6.clone()
process.analyzeJets8 = process.analyzeJets7.clone()
process.analyzeJets9 = process.analyzeJets7.clone()

## met analyzer
from TopAnalysis.TopAnalyzer.METAnalyzer_cfi import analyzeMET
analyzeMET.METs = metCollection
analyzeMET.weightPU    = eventWeightPuTag
analyzeMET.weightLepSF = eventWeightDileptonSfTag
process.analyzeMet3 = analyzeMET.clone()
process.analyzeMet4 = analyzeMET.clone()
process.analyzeMet5 = analyzeMET.clone()
process.analyzeMet6 = analyzeMET.clone()
process.analyzeMet7 = analyzeMET.clone()
process.analyzeMet8 = analyzeMET.clone()
process.analyzeMet9 = analyzeMET.clone()


## muon analyzer

from TopAnalysis.TopAnalyzer.MuonAnalyzer_cfi import analyzeMuons
analyzeMuons.jets        = jetCollection
analyzeMuons.weightPU    = eventWeightPuTag
analyzeMuons.weightLepSF = eventWeightDileptonSfTag

process.analyzeMuons1 = analyzeMuons.clone(muons = "unisolatedMuons", weightLepSF = "")
process.analyzeMuons2 = process.analyzeMuons1.clone()

process.analyzeMuons3 = analyzeMuons.clone(muons = leptons3)
process.analyzeMuons4 = process.analyzeMuons3.clone(muons = finalLeptons)
process.analyzeMuons5 = process.analyzeMuons4.clone()
process.analyzeMuons6 = process.analyzeMuons5.clone()
process.analyzeMuons7 = process.analyzeMuons6.clone()
process.analyzeMuons8 = process.analyzeMuons7.clone()
process.analyzeMuons9 = process.analyzeMuons8.clone()


## electron analyzer
from TopAnalysis.TopAnalyzer.ElectronAnalyzer_cfi import analyzeElectrons
analyzeElectrons.jets = jetCollection
analyzeElectrons.weightPU    = eventWeightPuTag
analyzeElectrons.weightLepSF = eventWeightDileptonSfTag

process.analyzeElecs2 = analyzeElectrons.clone(electrons = "unisolatedElectrons")
process.analyzeElecs2.weightLepSF = ""

process.analyzeElecs3 = analyzeElectrons.clone(electrons = leptons3)
process.analyzeElecs4 = process.analyzeElecs3.clone(electrons = finalLeptons)
process.analyzeElecs5 = process.analyzeElecs4.clone()
process.analyzeElecs6 = process.analyzeElecs5.clone()
process.analyzeElecs7 = process.analyzeElecs6.clone()
process.analyzeElecs8 = process.analyzeElecs7.clone()
process.analyzeElecs9 = process.analyzeElecs8.clone()

##Write Ntuple
from TopAnalysis.TopAnalyzer.ntuplewriter_cfi import writeNTuple
writeNTuple.weightPU    = eventWeightPuTag
writeNTuple.weightPU_Up    = eventWeightPuTag_Up
writeNTuple.weightPU_Down    = eventWeightPuTag_Down
writeNTuple.weightLepSF = eventWeightDileptonSfTag

process.writeNTuple = writeNTuple.clone(
    muons=isolatedMuonCollection, 
    elecs=isolatedElecCollection, 
    jets=jetCollection, 
    met=metCollection,
    weightKinFit = cms.InputTag("eventWeightDileptonKinEffSF", "eventWeightDileptonKinEffSF"),
)

## dilepton analyzer
from TopAnalysis.TopAnalyzer.DiLeptonAnalyzer_cfi import analyzeLeptonPair
analyzeLeptonPair.fileOutput = False
analyzeLeptonPair.jets = jetCollection
analyzeLeptonPair.weightPU    = eventWeightPuTag
analyzeLeptonPair.weightLepSF = eventWeightDileptonSfTag

process.analyzeLeptonPair3 = analyzeLeptonPair.clone(muons = leptons3, elecs = leptons3)
process.analyzeLeptonPair4 = process.analyzeLeptonPair3.clone(muons = finalLeptons, elecs = finalLeptons)
process.analyzeLeptonPair5 = process.analyzeLeptonPair4.clone()
process.analyzeLeptonPair6 = process.analyzeLeptonPair5.clone()
process.analyzeLeptonPair7 = process.analyzeLeptonPair6.clone()
process.analyzeLeptonPair8 = process.analyzeLeptonPair7.clone()
process.analyzeLeptonPair9 = process.analyzeLeptonPair8.clone()

process.analyzeLeptonPairZvetoRegion4 = analyzeLeptonPair.clone(muons = finalLeptons, elecs = finalLeptons)
process.analyzeLeptonPairZvetoRegion5 = process.analyzeLeptonPairZvetoRegion4.clone()
process.analyzeLeptonPairZvetoRegion6 = process.analyzeLeptonPairZvetoRegion5.clone()
process.analyzeLeptonPairZvetoRegion7 = process.analyzeLeptonPairZvetoRegion6.clone()
process.analyzeLeptonPairZvetoRegion8 = process.analyzeLeptonPairZvetoRegion7.clone()
process.analyzeLeptonPairZvetoRegion9 = process.analyzeLeptonPairZvetoRegion8.clone()
process.analyzeMetZvetoRegion6 = analyzeMET.clone()


## std sequence to produce the ttFullLepEvent
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttFullLepEvtBuilder_cff")
from TopQuarkAnalysis.TopEventProducers.sequences.ttFullLepEvtBuilder_cff import *
if not signal:
    removeTtFullLepHypGenMatch(process)

setForAllTtFullLepHypotheses(process,"muons"    ,finalLeptons)
setForAllTtFullLepHypotheses(process,"electrons",finalLeptons)
setForAllTtFullLepHypotheses(process,"jets"     ,jetCollection         )
setForAllTtFullLepHypotheses(process,"mets"     ,metCollection        )
setForAllTtFullLepHypotheses(process,"jetCorrectionLevel","L3Absolute")
setForAllTtFullLepHypotheses(process,"maxNJets",-1)

#use this?
#process.ttFullLepJetPartonMatch.jets = hardJets

process.kinSolutionTtFullLepEventHypothesis.maxNComb = -1
process.kinSolutionTtFullLepEventHypothesis.searchWrongCharge = True
process.kinSolutionTtFullLepEventHypothesis.tmassbegin = 100.0
process.kinSolutionTtFullLepEventHypothesis.tmassend   = 300.0
process.kinSolutionTtFullLepEventHypothesis.neutrino_parameters = (30.641, 57.941, 22.344, 57.533, 22.232)

process.kinSolutionTtFullLepEventHypothesis.mumuChannel = False
process.kinSolutionTtFullLepEventHypothesis.emuChannel  = False
process.kinSolutionTtFullLepEventHypothesis.eeChannel = False
if options.mode == 'mumu':
    process.kinSolutionTtFullLepEventHypothesis.mumuChannel = True
    process.ttFullLepEvent.decayChannel1 = cms.int32(2)
    process.ttFullLepEvent.decayChannel2 = cms.int32(2)
elif options.mode == 'emu':
    process.kinSolutionTtFullLepEventHypothesis.emuChannel = True
    process.ttFullLepEvent.decayChannel1 = cms.int32(1)
    process.ttFullLepEvent.decayChannel2 = cms.int32(2)
elif options.mode == 'ee':
    process.kinSolutionTtFullLepEventHypothesis.eeChannel = True
    process.ttFullLepEvent.decayChannel1 = cms.int32(1)
    process.ttFullLepEvent.decayChannel2 = cms.int32(1)


## analyze hypotheses
process.load("TopAnalysis.TopAnalyzer.FullLepKinAnalyzer_cfi")
from TopAnalysis.TopAnalyzer.FullLepKinAnalyzer_cfi import analyzeFullLepKinematics
analyzeFullLepKinematics.weightPU    = eventWeightPuTag
analyzeFullLepKinematics.weightLepSF = eventWeightDileptonSfTag

if signal:
        analyzeFullLepKinematics.isSignalMC = True
process.analyzeKinSolution6 = analyzeFullLepKinematics.clone()

process.analyzeKinSolutionNoBtagging7 = process.analyzeKinSolution6.clone() # used for measurement of b-tagging efficiency
process.analyzeKinSolutionNoBtagging7.useBtagging = False
process.analyzeKinSolutionNoBtagging7.useLeadingJets = True

process.analyzeKinSolution7 = process.analyzeKinSolution6.clone()
process.analyzeKinSolution8 = process.analyzeKinSolution7.clone()
process.analyzeKinSolution9 = process.analyzeKinSolution8.clone()

## filter hypotheses
process.load("TopAnalysis.TopFilter.filters.FullLepHypothesesFilter_cfi")
process.filterFullLepHypothesis.useLeadingJets = False
process.filterFullLepHypothesis.weightCut = 0
process.filterFullLepHypothesis.jets = "hardJets"
process.filterFullLepHypothesis.bAlgorithm = 'trackCountingHighEffBJetTags'
process.filterFullLepHypothesis.bDiscriminator = cms.vdouble()
    
#-------------------------------------------------
# analysis path
#-------------------------------------------------

if zfilter:
        process.zsequence = cms.Sequence(process.generatorZFilter)
else:
        process.zsequence = cms.Sequence()

if signal and useGenCutsInTopSignal:
    from TopAnalysis.TopFilter.filters.GeneratorTtDileptonFilter_cfi import generatorTtDileptonFilter
    process.generatorTtCutsLeptons = generatorTtDileptonFilter.clone(
        leptonPt            = 20.,
        leptonEta           = 2.4,
    )
    process.generatorTtCutsBJets = generatorTtDileptonFilter.clone(
        #bPt                 = 30.,
        #bEta                = 2.4,
        bHadronPt = 30,
        bHadronEta = 2.4,
    )
else:
    process.generatorTtCutsLeptons = cms.Sequence()
    process.generatorTtCutsBJets = cms.Sequence()

process.analyzeGenEvent7 = cms.Sequence()
process.analyzeGenEvent8 = cms.Sequence()
process.analyzeGenEvent9 = cms.Sequence()

if topfilter:
	process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")
	process.load("TopAnalysis.TopUtils.HadronLevelBJetProducer_cfi")

        process.load("SimGeneral.HepPDTESSource.pdt_cfi")#necessary for GOOD running of bHadronGenerator
	process.load("TopAnalysis.TopUtils.GenLevelBJetProducer_cfi")
        process.produceGenLevelBJets.deltaR = 5.0
        process.produceGenLevelBJets.noBBbarResonances = True
        
	process.decaySubset.fillMode = "kME" # Status3, use kStable for Status2     
        process.topsequence = cms.Sequence( 
	        process.makeGenEvt *
	        process.produceHadronLevelBJets *
                process.produceGenLevelBJets*
		process.generatorTopFilter 
	)

        #PLACE_MODEL_VARIATION_HERE
        #leave line above with PLACE_MODEL_VARIATION_HERE in place, it is replaced by makeModel.pl

        if signal:
                from TopAnalysis.TopAnalyzer.FullLepGenAnalyzer_cfi import analyzeFullLepGenEvent
                analyzeFullLepGenEvent.weightPU = eventWeightPuTag
		analyzeFullLepGenEvent.weightLepSF = ""
                process.analyzeGenTopEvent = analyzeFullLepGenEvent.clone()
                process.analyzeVisibleGenTopEvent = analyzeFullLepGenEvent.clone()
                process.analyzeGenTopEvent7 = analyzeFullLepGenEvent.clone()
		process.analyzeGenEvent7 = cms.Sequence(process.analyzeGenTopEvent7)
		process.analyzeGenTopEvent8 = analyzeFullLepGenEvent.clone()
                process.analyzeGenEvent8 = cms.Sequence(process.analyzeGenTopEvent8)
		process.analyzeGenTopEvent9 = analyzeFullLepGenEvent.clone()
                process.analyzeGenEvent9 = cms.Sequence(process.analyzeGenTopEvent9) 
else:
        process.topsequence = cms.Sequence()

if options.mode == 'emu':
    process.Step4Cut = cms.Sequence()
    #process.Step7Cut = cms.Sequence(process.pfMETSelectionEMu)
    process.Step7Cut = cms.Sequence()
else:
    # we need to implement cuts on the Z window and on MET
    process.Step4Cut = cms.Sequence(process.filterDiLeptonMassZveto)
    process.Step7Cut = cms.Sequence(process.pfMETSelection)


from TopAnalysis.TopAnalyzer.EventIDPrinter_cfi import eventIDPrinter
eventIDPrinter.mets = metCollection
eventIDPrinter.elecs = isolatedElecCollection
eventIDPrinter.muons = isolatedMuonCollection
eventIDPrinter.jets = jetCollection
if options.syncExcercise:
    #skipIfNoElectrons=False
    #skipIfNoMuons=False
    process.eventIDPrinter2 = eventIDPrinter.clone(
        runOnMC = True,
        outputString = 'Step2: ',
        showDetails = True,
        #jets = "goodIdJets",
        #jecLevel = "L1FastJet",
        #jecLevel = "L3Absolute",
    )

    process.eventIDPrinter3 = eventIDPrinter.clone(runOnMC = True, outputString = 'Step3: ')
    process.eventIDPrinter4 = eventIDPrinter.clone(runOnMC = True, outputString = 'Step4: ')
    process.eventIDPrinter6 = eventIDPrinter.clone(runOnMC = True, outputString = 'Step6: ')
    process.eventIDPrinter7 = eventIDPrinter.clone(runOnMC = True, outputString = 'Step7: ')
    process.eventIDPrinter8 = eventIDPrinter.clone(runOnMC = True, outputString = 'Step8: ')
    process.eventIDPrinter9 = eventIDPrinter.clone(runOnMC = True, outputString = 'Step9: ')
else:
    process.eventIDPrinter2 = cms.Sequence()
    process.eventIDPrinter3 = cms.Sequence()
    process.eventIDPrinter4 = cms.Sequence()
    process.eventIDPrinter6 = cms.Sequence()
    process.eventIDPrinter7 = eventIDPrinter.clone(runOnMC = False, outputString = 'Step7: ', showDetails = True)
    process.eventIDPrinter8 = eventIDPrinter.clone(runOnMC = False, outputString = 'Step8: ')
    process.eventIDPrinter9 = eventIDPrinter.clone(runOnMC = False, outputString = 'Step9: ')

### OLD ANALYSIS ENDS HERE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#process.source.skipEvents = cms.untracked.uint32(40000)

process.load("TopAnalysis.TopUtils.JetEnergyScale_cfi")
from PhysicsTools.PatAlgos.tools.helpers import cloneProcessingSnippet, massSearchReplaceAnyInputTag

#process.SimpleMemoryCheck = cms.Service("SimpleMemoryCheck", ignoreTotal = cms.untracked.int32(1))

if signal:
    process.ntupleInRecoSeq = cms.Sequence()
else:
    process.writeNTuple.isTtBarSample = False
    process.ntupleInRecoSeq = cms.Sequence(process.writeNTuple)

process.afterLeptonChargeSelection = cms.Sequence(
    process.filterChannel            *
    process.filterDiLeptonMassQCDveto*
    process.makeTtFullLepEvent       *
    process.eventWeightDileptonSF    *
    process.ntupleInRecoSeq *

    process.analyzeLeptonPair3       *
    process.analyzeJets3             *
    process.analyzeMet3              *
    process.analyzeMuons3            *
    process.analyzeElecs3            *
    process.analyzeVertex3           *
    process.eventIDPrinter3          *

    #Step 4 = Z veto
    process.Step4Cut                 *
    process.analyzeJets4             *
    process.analyzeMet4              *
    process.analyzeMuons4            *
    process.analyzeElecs4            *
    process.analyzeLeptonPair4       *
    process.analyzeVertex4           *
    process.eventIDPrinter4          *

    process.onePFJetSelection        *
    process.analyzeJets5             *
    process.analyzeMet5              *
    process.analyzeMuons5            *
    process.analyzeElecs5            *
    process.analyzeVertex5           *
    process.analyzeLeptonPair5       *

    process.twoPFJetSelection        *

    process.analyzeJets6             *
    process.analyzeMet6              *
    process.analyzeMuons6            *
    process.analyzeElecs6            *
    process.analyzeLeptonPair6       *
    process.analyzeKinSolution6      *
    process.analyzeVertex6           *
    process.eventIDPrinter6          *

    #Step7 = MET cut
    process.Step7Cut *
    process.analyzeJets7             *
    process.analyzeMet7              *
    process.analyzeMuons7            *
    process.analyzeElecs7            *
    process.analyzeLeptonPair7       *
    process.analyzeKinSolution7      *
    process.analyzeKinSolutionNoBtagging7 *     
    process.analyzeVertex7           *
    process.analyzeGenEvent7         *
    process.eventIDPrinter7          *

    process.bTagSelectionTCHEL       *
    process.analyzeKinSolution8      *
    process.analyzeJets8             *
    process.analyzeMet8              *
    process.analyzeMuons8            *
    process.analyzeElecs8            *
    process.analyzeLeptonPair8       *
    process.analyzeVertex8           *
    process.analyzeGenEvent8         *
    process.eventIDPrinter8          *
    
    process.filterFullLepHypothesis  *
    process.eventWeightDileptonKinEffSF*     
    process.analyzeKinSolution9      *
    process.analyzeJets9             *
    process.analyzeMet9              *
    process.analyzeMuons9            *
    process.analyzeElecs9            *
    process.analyzeLeptonPair9       *
    process.analyzeVertex9           *
    process.analyzeGenEvent9         *
    process.eventIDPrinter9
).expandAndClone()

process.p = cms.Path(
    process.additionalPatSelection   *
    process.analyzeUnscaledVertex    *
    process.analyzeVertex2           *
    process.buildJets                *
    process.eventIDPrinter2          *
    process.filterOppositeCharge     *
    process.afterLeptonChargeSelection
)

#process.afterLeptonChargeSelectionSS = cloneProcessingSnippet(process, process.afterLeptonChargeSelection, "SS")
#massSearchReplaceAnyInputTag(process.afterLeptonChargeSelectionSS, "filterOppositeCharge", "filterSameCharge")
#massSearchReplaceAnyInputTag(process.afterLeptonChargeSelectionSS, "ttFullLepHypKinSolution", "ttFullLepHypKinSolutionSS")
#process.ttFullLepEventSS.hypotheses = cms.vstring('ttFullLepHypKinSolutionSS')


#process.pSS = cms.Path(
#   process.additionalPatSelection *
   #process.unscaledVertex        *
   #process.analyzeVertex2        *
#   process.buildJets              *
   #process.eventIDPrinter2       *
#   process.filterSameCharge       *
#   process.afterLeptonChargeSelectionSS
#)

process.pZWindow = cms.Path(
    process.eventWeightPU                 *
    process.eventWeightPUsysUp            *
    process.eventWeightPUsysDown          *
    process.filterTrigger                 *
    process.buildJets                     *
    process.filterOppositeCharge          *
    process.filterChannel                 *
    process.filterDiLeptonMassQCDveto     *
    process.eventWeightDileptonSF         *    
    process.ZWindowSelection              *
    process.analyzeLeptonPairZvetoRegion4 *
    process.onePFJetSelection             *
    process.analyzeLeptonPairZvetoRegion5 *
    process.twoPFJetSelection             *
    process.analyzeLeptonPairZvetoRegion6 *
    process.analyzeMetZvetoRegion6        *
    process.Step7Cut                      *
    process.analyzeLeptonPairZvetoRegion7 *
    process.bTagSelectionTCHEL            *
    process.analyzeLeptonPairZvetoRegion8 *
    process.makeTtFullLepEvent            *
    process.filterFullLepHypothesis       *
    process.eventWeightDileptonKinEffSF   *     
    process.analyzeLeptonPairZvetoRegion9
)

if signal:
    process.pNtuple = cms.Path(
        process.additionalPatSelection *
        process.buildJets *
        process.writeNTuple
    )


####################################################################
# prepend PF2PAT

from TopAnalysis.TopUtils.usePatTupleWithParticleFlow_cff import prependPF2PATSequence
prependPF2PATSequence(process, options = { 'switchOffEmbedding': False,
                                           'runOnMC': options.runOnMC,
                                           'runOnAOD': options.runOnAOD,
                                           'electronIDs': ['CiC','classical'],
                                           'cutsMuon':     muonSelectionPF,
                                           'pfIsoValMuon': muonIsolation,
                                           'pfIsoConeMuon': muonIsolationCone,
                                           'cutsElec':     electronSelectionPF,
                                           'pfIsoValElec': electronIsolation,
                                           'pfIsoConeElec': electronIsolationCone,
                                           'skipIfNoPFMuon': skipIfNoMuons,
                                           'skipIfNoPFElec': skipIfNoElectrons,
                                           #'addNoCutPFMuon': False,
                                           #'addNoCutPFElec': False,
                                           #'skipIfNoPFMuon': False,
                                           #'skipIfNoPFElec': False,
                                           'addNoCutPFMuon': True,
                                           'addNoCutPFElec': True,
                                           'analyzersBeforeMuonIso': cms.Sequence(
                                                process.unisolatedMuons *
                                                process.analyzeMuons1),
                                           'analyzersBeforeElecIso': cms.Sequence(
                                                process.unisolatedElectrons *
                                                process.analyzeMuons2*
                                                process.analyzeElecs2
                                                ),
                                           'METCorrectionLevel': 1,
                                           }
                      )

pathnames = process.paths_().keys()
print 'prepending trigger sequence to paths:', pathnames
for pathname in pathnames:
    getattr(process, pathname).insert(0, cms.Sequence(
        process.topsequence *
        process.zsequence *
        process.eventWeightPU *
        process.eventWeightPUsysUp *
        process.eventWeightPUsysDown *
        process.analyzeTrigger *
        process.filterTrigger
        ))
if signal:
    process.pNtuple.remove(process.analyzeTrigger)
    process.pNtuple.remove(process.filterTrigger)

#PATH on genparticles only, no pf2pat
if signal:
    process.genPath = cms.Path(
        process.topsequence *
        process.eventWeightPU *
        process.eventWeightPUsysUp *
        process.eventWeightPUsysDown *
        process.analyzeGenTopEvent *
        process.generatorTtCutsLeptons    *
        process.generatorTtCutsBJets *
        process.analyzeVisibleGenTopEvent)


if options.runOnMC and not options.syncExcercise:
    for pathname in pathnames:
        getattr(process, pathname).replace(process.selectedPatJets,
                                        process.scaledJetEnergy * process.selectedPatJets)

    process.selectedPatJets.src = cms.InputTag("scaledJetEnergy", "patJets")
    process.highMETs.src = cms.InputTag("scaledJetEnergy", "patMETs")
    process.scaledJetEnergy.scaleType = "abs" #abs = 1, jes:up, jes:down
    #process.scaledJetEnergy.scaleType = "jes:up" #abs = 1, jes:up, jes:down
    #process.scaledJetEnergy.scaleType = "jes:down" #abs = 1, jes:up, jes:down

    process.scaledJetEnergy.resolutionEtaRanges  = cms.vdouble(0, 1.5, 1.5, 2.0, 2.0, -1)

    #process.scaledJetEnergy.resolutionFactors    = cms.vdouble(1.0, 0.95, 0.9) # JER down
    process.scaledJetEnergy.resolutionFactors    = cms.vdouble(1.1, 1.1, 1.1) # JER standard
    #process.scaledJetEnergy.resolutionFactors    = cms.vdouble(1.2, 1.25, 1.3) # JER up


if options.runOnMC and not options.syncExcercise and filterMadgraphPythiaBug:
    for pathname in process.paths_().keys():
        getattr(process, pathname).insert(0, process.totalKinematicsFilter)


process.load("TopAnalysis.TopUtils.SignalCatcher_cfi")
