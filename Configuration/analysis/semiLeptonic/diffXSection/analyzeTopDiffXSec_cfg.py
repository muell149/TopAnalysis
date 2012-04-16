import FWCore.ParameterSet.Config as cms

## ---
##   use this file to study different distributions for measurement of differential Cross Section
##   does also a monitoring of the cuts before they are applied
## ---

## ---
##    example to run this cfg file
## ---
## cmsRun analyzeTopDiffXSec_cfg.py triggerTag=HLT,sample=ttbar,lepton=muon,mctag=Fall11,eventsToProcess=5000

## ---
##    options
## ---

## introduce interface with crab file
## allows to choose registered parameter for every job individually
import FWCore.ParameterSet.VarParsing as VarParsing
import sys
import os
options = VarParsing.VarParsing ('standard')

# create object triggerTag with default value HLT of type singleton and string
options.register('triggerTag', 'HLT',VarParsing.VarParsing.multiplicity.singleton,VarParsing.VarParsing.varType.string, "chosen trigger tag")
# create sample label with default value data
# for Summer11/Fall11 MC one can choose: ttbar, wjets, zjets, singleAntiTopS, singleTopT, singleAntiTopT, singleTopTw, singleAntiTopTw, singleTopS WW, WZ, ZZ, qcd (for muon channel); qcdEM1, qcdEM2, qcdEM3, qcdBCE1, qcdBCE2, qcdBCE3 (for electron channel), zprime_m500gev_w5000mev, zprime_m750gev_w7500mev
# for systematic samples see list for each MC sample
options.register('sample', 'none',VarParsing.VarParsing.multiplicity.singleton,VarParsing.VarParsing.varType.string, "chosen sample")
# create lepton channel label 
options.register('lepton', 'unset',VarParsing.VarParsing.multiplicity.singleton,VarParsing.VarParsing.varType.string, "chosen decay channel")
# create label to select version of MC samples (Summer11, Fall11)
# a) important for trigger
# b) also used to automatically select the mode for PU event reweighting
options.register('mctag', 'Fall11',VarParsing.VarParsing.multiplicity.singleton,VarParsing.VarParsing.varType.string, "label for version of MC samples (Fall11, Summer11")
# create variable to indicate number of processed events
# -42 means nothing is changed wrt number typed below
options.register('eventsToProcess', -42,VarParsing.VarParsing.multiplicity.singleton,VarParsing.VarParsing.varType.int, "events to process")

# define the syntax for parsing
# you need to enter in the cfg file:
# search for arguments entered after cmsRun
if( hasattr(sys, "argv") ):
    # split arguments by comma - seperating different variables
    for args in sys.argv :
        arg = args.split(',')
        # split further by = to separate variable name and value
        for val in arg:
            val = val.split('=')
            # set variable var to value val (expected crab syntax: var=val)
            if(len(val)==2):
                setattr(options,val[0], val[1])

## choose jet collection and corresponding MET
if(not globals().has_key('jetType')):
    jetType =  'particleFlow' # 'Calo'

## run PF2PAT?
## only possible for special pat tuples!!!
if(not globals().has_key('pfToPAT')):
    pfToPAT = True #False

## choose the semileptonic decay channel (electron or muon)
#decayChannel=options.lepton
if(options.lepton=='unset'): 
    if(not globals().has_key('decayChannel')):
        decayChannel = 'muon' # 'electron'
else:
    decayChannel=options.lepton

# switch to run on data and remove all gen plots (type 'MC' or 'data')
if(not globals().has_key('runningOnData')): 
    runningOnData = "MC"
    
# print chosen sample (e.g. ttbar)
# value is known from external parsing
# if set, switches runOnAOD in PF2PAT to true
#print "Chosen sample to run over: ", options.sample

## choose JSON file for data
if(not globals().has_key('jsonFile')):
    jsonFile =  ''

## enable/ disable PU event reweighting
if(not globals().has_key('PUreweigthing')):
    PUreweigthing = True # False
    # take care of data
    if (not runningOnData == "MC"):
        PUreweigthing = False

## enable/ disable btag SF event reweighting
if(not globals().has_key('BtagReweigthing')):
    BtagReweigthing = True # False
    # take care of data
    if (not runningOnData == "MC"):
        BtagReweigthing = False

## choose b tag algo
if(not globals().has_key('bTagAlgo')):
    bTagAlgo =  'combinedSecondaryVertexBJet' # 'simpleSecondaryVertexHighEffBJet'

## choose b tag working point (discriminator cut value)
if(not globals().has_key('bTagDiscrCut')):
    bTagDiscrCut =  0.679  # 1.74 for SSVHEM

## enable/ disable efficiency SF event reweighting
if(not globals().has_key('effSFReweigthing')):
    effSFReweigthing = True # False
    # take care of data
    if (not runningOnData == "MC"):
        effSFReweigthing = False

# choose jet correction level shown in plots
# L3Absolute for MC, L2L3Residual for data
if(not globals().has_key('corrLevel')):
    corrLevel='L3Absolute'

## run kinematic fit?
## ATTENTION: until the new parameter jetResolutionSmearFactor
## is implemented in a higher version of the TKinFitter package you
## need to check out the head:
## cvs co TopQuarkAnalysis/TopKinFitter

if(not globals().has_key('applyKinFit')):
   applyKinFit = True#  False
    
## choose whether you want a pat tuple as output
if(not globals().has_key('writeOutput')): 
    writeOutput  = False # True
    
## remove all ttbar specific gen level filter - used by other _cfg based on this file
if(not globals().has_key('removeGenTtbar')):
    removeGenTtbar = False 

## implement anti b-tagging path
if(not globals().has_key('implement0TagPath')):
    implement0TagPath = False
#if(implement0TagPath==True):
#    print "path with ==0 btagged jets included" 
#if(implement0TagPath==False):
#    print "path with ==0 btagged jets excluded"
    
## eventfilter is to select a special ttbar decay channel from ttbarSample by genmatching (ttbar MC only, other MC: choose 'all')
if(not globals().has_key('eventFilter')):
    eventFilter  = 'signal only' # 'background only' # 'all' # 'signal only' # 'semileptonic electron only' # 'dileptonic electron only' # 'dileptonic muon only' # 'fullhadronic' # 'dileptonic muon + electron only' # 'via single tau only' # 'dileptonic via tau only'

## choose if you want to include tau (->e/mu) events
if(not globals().has_key('tau')):
    tau = False # True
# use these tau events only in SG/SB configuration not for single decay modes or all
if(not eventFilter=='signal only' and not eventFilter=='background only'):
    tau= False

## choose whether synchronisation exercise should be done
if(not globals().has_key('cutflowSynch')): 
    cutflowSynch  = False # True
    
## choose whether additional event weights should be applied
if(not globals().has_key('additionalEventWeights')): 
    additionalEventWeights  = True

## enable/ disable systematic shape distortion event reweighting
if(not globals().has_key('sysDistort')):
    sysDistort =  ''
    #sysDistort =  'up'
    #sysDistort =  'down'
# only done for ttbar
if(not options.sample=="ttbar"):
    sysDistort=''
# coupled to PU weight, therefore not applicable without
if(not PUreweigthing):
    sysDistort=''

# differetial xSec Analysis
process = cms.Process("topDifferentialXSec")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 10000
process.MessageLogger.categories.append('TtSemiLepKinFitter')
process.MessageLogger.categories.append('KinFitter')
process.MessageLogger.cerr.TtSemiLepKinFitter = cms.untracked.PSet(
    limit = cms.untracked.int32(0)
)
process.MessageLogger.cerr.KinFitter = cms.untracked.PSet(
    limit = cms.untracked.int32(0)
)

## print memory infos to check for modules with memory leaks
#process.SimpleMemoryCheck = cms.Service("SimpleMemoryCheck", ignoreTotal = cms.untracked.int32(0)) 

## define input
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(    
    ## add your favourite file here
    #'/store/data/Run2011A/ElectronHad/AOD/PromptReco-v4/000/165/093/2C186C6C-C27F-E011-A1C7-001617E30F58.root'
    #'/store/data/Run2011A/MuHad/AOD/PromptReco-v4/000/165/205/0C569F2A-D382-E011-B122-00304879FBB2.root' 
    #'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FEEE3638-F297-E011-AAF8-00304867BEC0.root'
    #'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1204EE92-F397-E011-99E8-003048679012.root' 
    )
)

## create output file name
outputFileName = ""
if(decayChannel=="muon"):
    outputFileName = "muon"
elif(decayChannel=="electron"):
    outputFileName = "elec"
## will be continued later

## Flag required to compensate bug in energy-momentum conservation for non Pythia samples
## Modified in the following depending on the input sample, but only for the Pythia samples!
## Default value: False

PythiaSample="False"
usedSample="none"

## automatically load the correct (AOD) .root file list for each MC sample
if(not options.sample=="none"):
    outputFileName+="DiffXSec"    
    if(options.sample=="ttbar"):
        # usedSample="TopAnalysis/Configuration/ttjets_MadgraphZ2_Summer11_AOD_cff"
        usedSample="TopAnalysis/Configuration/Fall11/ttjets_MadgraphZ2_Fall11_v1_AOD_cff"
	if(eventFilter=='signal only'):
	    outputFileName+="Sig"
	elif(eventFilter=='background only'):
	    outputFileName+="Bkg"
    elif(options.sample=="ttbarMatchingDown"):        
        usedSample="TopAnalysis/Configuration/ttjets_matching_down_MadgraphZ2_Summer11_AOD_cff"
	additionalEventWeights=False
	if(eventFilter=='signal only'):
	    outputFileName+="SigMatchDown"
	elif(eventFilter=='background only'):
	    outputFileName+="BkgMatchDown"
    elif(options.sample=="ttbarMatchingUp"):        
        usedSample="TopAnalysis/Configuration/ttjets_matching_up_MadgraphZ2_Summer11_AOD_cff"
	additionalEventWeights=False
	if(eventFilter=='signal only'):
	    outputFileName+="SigMatchUp"
	elif(eventFilter=='background only'):
	    outputFileName+="BkgMatchUp"
    elif(options.sample=="ttbarScaleDown"):        
        usedSample="TopAnalysis/Configuration/ttjets_scale_down_MadgraphZ2_Summer11_AOD_cff"
	additionalEventWeights=False
	if(eventFilter=='signal only'):
	    outputFileName+="SigScaleDown"
	elif(eventFilter=='background only'):
	    outputFileName+="BkgScaleDown"
    elif(options.sample=="ttbarScaleUp"):        
        usedSample="TopAnalysis/Configuration/ttjets_scale_up_MadgraphZ2_Summer11_AOD_cff"
	additionalEventWeights=False
	if(eventFilter=='signal only'):
	    outputFileName+="SigScaleUp"
	elif(eventFilter=='background only'):
	    outputFileName+="BkgScaleUp"
    elif(options.sample=="ttbarMassDown"):        
        usedSample="TopAnalysis/Configuration/ttjets_mass169_5_MadgraphZ2_Summer11_AOD_cff"
	additionalEventWeights=False
	if(eventFilter=='signal only'):
	    outputFileName+="SigTopMassDown"
	elif(eventFilter=='background only'):
	    outputFileName+="BkgTopMassDown"
    elif(options.sample=="ttbarMassUp"):        
        usedSample="TopAnalysis/Configuration/ttjets_mass175_5_MadgraphZ2_Summer11_AOD_cff"
	additionalEventWeights=False
	if(eventFilter=='signal only'):
	    outputFileName+="SigTopMassUp"
	elif(eventFilter=='background only'):
	    outputFileName+="BkgTopMassUp"
    elif(options.sample=="wjets"):        
        usedSample="TopAnalysis/Configuration/Fall11/wlnujets_MadgraphZ2_Fall11_AOD_cff"
	outputFileName+="Wjets"
    elif(options.sample=="wjetsMatchingUp"):        
        usedSample="TopAnalysis/Configuration/wlnujets_matching_up_MadgraphZ2_Summer11_AOD_cff"
	additionalEventWeights=False
	outputFileName+="WjetsMatchUp"
    elif(options.sample=="wjetsMatchingDown"):        
        usedSample="TopAnalysis/Configuration/wlnujets_matching_down_MadgraphZ2_Summer11_AOD_cff"
	additionalEventWeights=False
	outputFileName+="WjetsMatchDown"
    elif(options.sample=="wjetsScaleUp"):        
        usedSample="TopAnalysis/Configuration/wlnujets_scale_up_MadgraphZ2_Summer11_AOD_cff"
	additionalEventWeights=False
	outputFileName+="WjetsScaleUp"
    elif(options.sample=="wjetsScaleDown"):
        usedSample="TopAnalysis/Configuration/wlnujets_scale_down_MadgraphZ2_Summer11_AOD_cff"
	additionalEventWeights=False        
	outputFileName+="WjetsScaleDown"
    elif(options.sample=="zjets"):        
        usedSample="TopAnalysis/Configuration/Fall11/dylljetsM50_MadgraphZ2_Fall11_AOD_cff"
	outputFileName+="Zjets"
    elif(options.sample=="zjetsMatchingUp"):        
        usedSample="TopAnalysis/Configuration/zlljets_matching_up_MadgraphZ2_Summer11_AOD_cff"
	additionalEventWeights=False
	outputFileName+="ZjetsMatchUp"
    elif(options.sample=="zjetsMatchingDown"):        
        usedSample="TopAnalysis/Configuration/zlljets_matching_down_MadgraphZ2_Summer11_AOD_cff"
	additionalEventWeights=False
	outputFileName+="ZjetsMatchDown"
    elif(options.sample=="zjetsScaleUp"):        
        usedSample="TopAnalysis/Configuration/zlljets_scale_up_MadgraphZ2_Summer11_AOD_cff"
	additionalEventWeights=False
	outputFileName+="ZjetsScaleUp"
    elif(options.sample=="zjetsScaleDown"):        
        usedSample="TopAnalysis/Configuration/zlljets_scale_down_MadgraphZ2_Summer11_AOD_cff"
	additionalEventWeights=False      
	outputFileName+="ZjetsScaleDown"
    elif(options.sample=="singleTopS"):        
        usedSample="TopAnalysis/Configuration/Fall11/singleTop_schannel_PythiaPowhegZ2_Fall11_AOD_cff"
	outputFileName+="SingleTopS"
    elif(options.sample=="singleTopSScaleDown"):        
        usedSample="TopAnalysis/Configuration/singleTop_schannel_scale_down_PythiaPowhegZ2_Summer11_AOD_cff"
	additionalEventWeights=False   
	outputFileName+="SingleTopSScaleDown"
    elif(options.sample=="singleTopSScaleUp"):        
        usedSample="TopAnalysis/Configuration/singleTop_schannel_scale_up_PythiaPowhegZ2_Summer11_AOD_cff"
	additionalEventWeights=False
	outputFileName+="SingleTopSScaleUp"
    elif(options.sample=="singleAntiTopS"):        
        usedSample="TopAnalysis/Configuration/Fall11/singleAntiTop_schannel_PythiaPowhegZ2_Fall11_AOD_cff"
	outputFileName+="SingleAntiTopS"
    elif(options.sample=="singleAntiTopSScaleDown"):        
        usedSample="TopAnalysis/Configuration/singleAntiTop_schannel_scale_down_PythiaPowhegZ2_Summer11_AOD_cff"
	additionalEventWeights=False
	outputFileName+="SingleAntiTopSScaleDown"
    elif(options.sample=="singleAntiTopSScaleUp"):        
        usedSample="TopAnalysis/Configuration/singleAntiTop_schannel_scale_up_PythiaPowhegZ2_Summer11_AOD_cff"
	additionalEventWeights=False
	outputFileName+="SingleAntiTopSScaleUp"
    elif(options.sample=="singleTopT"):        
        usedSample="TopAnalysis/Configuration/Fall11/singleTop_tchannel_PythiaPowhegZ2_Fall11_AOD_cff"
	outputFileName+="SingleTopT"
    elif(options.sample=="singleTopTScaleDown"):        
        usedSample="TopAnalysis/Configuration/singleTop_tchannel_scale_down_PythiaPowhegZ2_Summer11_AOD_cff"
	additionalEventWeights=False
	outputFileName+="SingleTopTScaleDown"
    elif(options.sample=="singleTopTScaleUp"):        
        usedSample="TopAnalysis/Configuration/singleTop_tchannel_scale_up_PythiaPowhegZ2_Summer11_AOD_cff"
	additionalEventWeights=False
	outputFileName+="SingleTopTScaleUp"
    elif(options.sample=="singleAntiTopT"):        
        usedSample="TopAnalysis/Configuration/Fall11/singleAntiTop_tchannel_PythiaPowhegZ2_Fall11_AOD_cff"
	outputFileName+="SingleAntiTopT"
    elif(options.sample=="singleAntiTopTScaleDown"):        
        usedSample="TopAnalysis/Configuration/singleAntiTop_tchannel_scale_down_PythiaPowhegZ2_Summer11_AOD_cff"
	additionalEventWeights=False
	outputFileName+="SingleAntiTopTScaleDown"
    elif(options.sample=="singleAntiTopTScaleUp"):        
        usedSample="TopAnalysis/Configuration/singleAntiTop_tchannel_scale_up_PythiaPowhegZ2_Summer11_AOD_cff"
	additionalEventWeights=False
	outputFileName+="SingleAntiTopTScaleUp"
    elif(options.sample=="singleTopTw"):        
        usedSample="TopAnalysis/Configuration/Fall11/singleTop_twchannelDR_PythiaPowhegZ2_Fall11_AOD_cff"
	outputFileName+="SingleTopTW"
    elif(options.sample=="singleTopTwScaleDown"):        
        usedSample="TopAnalysis/Configuration/singleTop_twchannelDR_scale_down_PythiaPowhegZ2_Summer11_AOD_cff"
	additionalEventWeights=False
	outputFileName+="SingleTopTWScaleDown"
    elif(options.sample=="singleTopTwScaleUp"):        
        usedSample="TopAnalysis/Configuration/singleTop_twchannelDR_scale_up_PythiaPowhegZ2_Summer11_AOD_cff"
	additionalEventWeights=False
	outputFileName+="SingleTopTWScaleUp"
    elif(options.sample=="singleAntiTopTw"):        
        usedSample="TopAnalysis/Configuration/Fall11/singleAntiTop_twchannelDR_PythiaPowhegZ2_Fall11_AOD_cff"
	outputFileName+="SingleAntiTopTW"
    elif(options.sample=="singleAntiTopTwScaleDown"):        
        usedSample="TopAnalysis/Configuration/singleAntiTop_twchannelDR_scale_down_PythiaPowhegZ2_Summer11_AOD_cff"
	additionalEventWeights=False
	outputFileName+="SingleAntiTopTWScaleDown"
    elif(options.sample=="singleAntiTopTwScaleUp"):        
        usedSample="TopAnalysis/Configuration/singleAntiTop_twchannelDR_scale_up_PythiaPowhegZ2_Summer11_AOD_cff"
	additionalEventWeights=False
	outputFileName+="SingleAntiTopTWScaleUp"
    elif(options.sample=="zprime_m500gev_w5000mev"):        
        usedSample="TopAnalysis/Configuration/zprime_M500GeV_W5000MeV_Madgraph_Summer11_AOD_cff"
    elif(options.sample=="zprime_m750gev_w7500mev"):        
        usedSample="TopAnalysis/Configuration/zprime_M750GeV_W7500MeV_Madgraph_Summer11_AOD_cff"
	additionalEventWeights=False
    elif(options.sample=="qcd" and decayChannel=='muon'):
        usedSample="TopAnalysis/Configuration/Fall11/qcdmu15enriched_Pythia6_Fall11_AOD_cff"
        PythiaSample="True"
        outputFileName+="QCD"
    elif(options.sample=="qcdEM1" and decayChannel=='electron'):
        usedSample="TopAnalysis/Configuration/Fall11/qcdEMenrichedPt20to30_Pythia6_Fall11_AOD_cff"
        PythiaSample="True"
        outputFileName+="QCDEM1"
    elif(options.sample=="qcdEM2" and decayChannel=='electron'):
        usedSample="TopAnalysis/Configuration/Fall11/qcdEMenrichedPt30to80_Pythia6_Fall11_AOD_cff"
        PythiaSample="True"
        outputFileName+="QCDEM2"
    elif(options.sample=="qcdEM3" and decayChannel=='electron'):
        usedSample="TopAnalysis/Configuration/Fall11/qcdEMenrichedPt80to170_Pythia6_Fall11_AOD_cff"
        PythiaSample="True"
        outputFileName+="QCDEM3"
    elif(options.sample=="qcdBCE1" and decayChannel=='electron'):
        usedSample="TopAnalysis/Configuration/Fall11/qcdBCtoEPt20to30_Pythia6_Fall11_AOD_cff"
        PythiaSample="True"
        outputFileName+="QCDBCE1"
    elif(options.sample=="qcdBCE2" and decayChannel=='electron'):
        usedSample="TopAnalysis/Configuration/Fall11/qcdBCtoEPt30to80_Pythia6_Fall11_AOD_cff"
        PythiaSample="True"
        outputFileName+="QCDBCE2"
    elif(options.sample=="qcdBCE3" and decayChannel=='electron'):
        usedSample="TopAnalysis/Configuration/Fall11/qcdBCtoEPt80to170_Pythia6_Fall11_AOD_cff"
        PythiaSample="True"
        outputFileName+="QCDBCE3"
    elif(options.sample=="WW"):        
        usedSample="TopAnalysis/Configuration/Fall11/wwtoall_Pythia6Z2_Fall11_AOD_cff"
        PythiaSample="True"
	outputFileName+="WW"
    elif(options.sample=="WZ"):        
        usedSample="TopAnalysis/Configuration/Fall11/wztoall_Pythia6Z2_Fall11_AOD_cff"
        PythiaSample="True"
	outputFileName+="WZ"
    elif(options.sample=="ZZ"):        
        usedSample="TopAnalysis/Configuration/Fall11/zztoall_Pythia6Z2_Fall11_AOD_cff"
        PythiaSample="True"
	outputFileName+="ZZ"
    else:
         usedSample="none"
        
    if(not usedSample=='none'):
        process.load(usedSample)
    else:
        print "\n ERROR ---- Poolsource file does not exist.\n"
        os._exit(0)

outputFileName+=options.mctag+"PF.root"

#### =================================================
####  Print out summary of configuration parameters
#### =================================================

print "                                     "
print " =================================== "
print "   Basic Configuration Parameters    "
print " =================================== "
print "                                     "
print " Trigger path:                       ","TriggerResults::"+options.triggerTag
print " Jet Type:                           ",jetType 
print " Run PF2PAT:                         ",pfToPAT," ---- Not working if the file does not contain the necessary information"
print " RunningOnData:                      ",runningOnData
print " JsonFile:                           ",jsonFile
print " Label for MC samples:               ",options.mctag
print " Chosen sample                       ",options.sample
print " Lepton decay channel:               ",decayChannel
print " ttbar filter:                       ",eventFilter," ---- Obsolete if RunningOnData != 'MC' "
print " Include tau->l events               ",tau
print " B-tag algo:                         ",bTagAlgo
print " B-tag discriminator cut value:      ",bTagDiscrCut
print " Include 0 b-ttaged jets:            ",implement0TagPath
print " Apply PU reweighting:               ",PUreweigthing
print " Apply Btag reweighting:             ",BtagReweigthing
print " Apply effSF reweighting:            ",effSFReweigthing
print " JEC level in jetKinematics:         ",corrLevel
print " Apply kinematic Fit:                ",applyKinFit," ---- Programme execution slowed down if 'True'"
print " Write PAT tuples:                   ",writeOutput
print " Analyzed sample:                    ",usedSample+".py"
print " Output file name:                   ",outputFileName
print " Synchronization exercise:           ",cutflowSynch
print " Additional event weights:           ",additionalEventWeights," ---- If 'True' weights are applied to the KinFit analyzers for monitoring, PU, b-tag and lepton eff. variations"
print " Apply shape reweighting, variation: ",sysDistort
print " "
if(removeGenTtbar==True):
    print " All gen level filters using ttbar decay subset are removed" 
    if(runningOnData=="MC"):
        print " Selection for gen plots only via TopAnalysis.TopFilter.sequences.genSelection_cff"
print " "

#### =================================================

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string(outputFileName))

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)
process.source.skipEvents = cms.untracked.uint32(0)
if(not options.eventsToProcess==-42):
    process.maxEvents.input=options.eventsToProcess

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
#global tag:
# a) 4_1:
#process.GlobalTag.globaltag = cms.string('START38_V14::All')
# b) 4_2:
from Configuration.PyReleaseValidation.autoCond import autoCond
if(runningOnData=="MC"):
    process.GlobalTag.globaltag = cms.string('START42_V17::All')
    #process.GlobalTag.globaltag = cms.string( autoCond[ 'startup' ] )
else:
    process.GlobalTag.globaltag = cms.string('GR_R_42_V23::All')

## Needed for redoing the ak5GenJets
#if(runningOnData=="MC" and pfToPAT==False):
#    process.load("TopAnalysis.TopUtils.GenJetParticles_cff")
#    process.load("RecoJets.Configuration.RecoGenJets_cff")  
#    process.p0 = cms.Path(## redo genjets without mu/nu from tau
#                          process.genJetParticles *
#                          process.ak5GenJets
#                          )

## load JSON file for data
if(runningOnData=="data"):
    if(jsonFile!=""):
        import PhysicsTools.PythonAnalysis.LumiList as LumiList
        import FWCore.ParameterSet.Types as CfgTypes
	print "The following JSON file is used in the cfg file: ", jsonFile
	myLumis = LumiList.LumiList(filename = jsonFile).getCMSSWString().split(',')
	process.source.lumisToProcess = CfgTypes.untracked(CfgTypes.VLuminosityBlockRange())
	process.source.lumisToProcess.extend(myLumis)
	## ATTENTION!!! At the moment myLumis are filled in the separate data_cfg files again
	## as otherwise overwritten by load("data_cff")
    else:
        print "No JSON file specified in cfg file (but possibly via CRAB)."
    
    
## ---
##    configure the cutflow scenario
## ---
## std sequence to produce the ttGenEvt
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")

## high level trigger filter
from HLTrigger.HLTfilters.hltHighLevel_cfi import *
process.hltFilter = hltHighLevel.clone(TriggerResultsTag = "TriggerResults::"+options.triggerTag, HLTPaths = ["HLT_IsoMu24_eta2p1_v*"], throw=False)
if(options.mctag=="Summer11"):
      process.hltFilter.HLTPaths=["HLT_IsoMu24_v*"]
#process.hltFilter = hltHighLevel.clone(TriggerResultsTag = "TriggerResults::HLT", HLTPaths = ["HLT_Mu15_v*"], throw=False)
#process.hltFilter.HLTPaths = ["HLT_Mu17_TriCentralJet30_v*"]

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
## generator filter based on direct cuts on lepton and parton pt and eta
## at ttGenEventLevel
from TopAnalysis.TopFilter.filters.SemiLeptonicGenPhaseSpaceFilter_cfi import filterSemiLeptonicGenPhaseSpace
process.filterGenPhaseSpace = filterSemiLeptonicGenPhaseSpace.clone(src = "genEvt")

## Generator kinematics selection (https://hypernews.cern.ch/HyperNews/CMS/get/physics-validation/1489.html)
## Currently set to 5.0 to prevent bias in throwing out heavy flavours, see:
## https://hypernews.cern.ch/HyperNews/CMS/get/physics-validation/1489/4/1/1/1/1/1.html
process.load("GeneratorInterface.GenFilters.TotalKinematicsFilter_cfi")
#process.totalKinematicsFilterDefault = process.totalKinematicsFilter.clone(tolerance = 0.5)
process.totalKinematicsFilterDefault = process.totalKinematicsFilter.clone(tolerance = 5.0)

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
if(tau==True):
    process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.tau  = True
    process.ttSemiLeptonicFilter.restrictTauDecays = cms.PSet(
        leptonic   = cms.bool(True ),
        oneProng   = cms.bool(False),
        threeProng = cms.bool(False)
        )
# take care of electron channel
if(decayChannel=='electron'):
    process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.muon     = False
    process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.electron = True
if(not eventFilter=='all'):
    ## adapt output filename
    if(eventFilter=='signal only'):
        print " " # Dummy output to avoid programme crash
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
        raise NameError, "'"+eventFilter+"' is not a proper eventFilter name choose: 'all', 'signal only', 'background only', 'semileptonic electron only', 'dileptonic electron only', 'dileptonic muon only', 'fullhadronic', 'via single tau only', 'dileptonic via tau only' or 'dileptonic muon + electron only'"
    ## sequence with filter for decay channel and trigger selection hltFilter
    process.filterSequence = cms.Sequence(process.makeGenEvt *
                                          process.ttSemiLeptonicFilter *
                                          process.hltFilter
                                          )
## sequence without filter (only trigger selection hltFilter) - done when 'all' is chosen, removeGenTtbar=True or runningOnData = "data"
if(eventFilter=='all') or (removeGenTtbar==True) or (runningOnData=="data"):
    process.filterSequence = cms.Sequence(process.hltFilter)
     
process.genFilterSequence = cms.Sequence(process.makeGenEvt                      *
                                         process.ttSemiLeptonicFilter             )

## define ordered jets
uds0    = cms.PSet(index = cms.int32(0), correctionLevel = cms.string(corrLevel), useTree = cms.bool(False) )
uds1    = cms.PSet(index = cms.int32(1), correctionLevel = cms.string(corrLevel), useTree = cms.bool(False) )
uds2    = cms.PSet(index = cms.int32(2), correctionLevel = cms.string(corrLevel), useTree = cms.bool(False) )
uds3    = cms.PSet(index = cms.int32(3), correctionLevel = cms.string(corrLevel), useTree = cms.bool(False) )
udsAll  = cms.PSet(index = cms.int32(-1), correctionLevel = cms.string(corrLevel), useTree = cms.bool(False) )

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
process.leadingJetSelectionNjets1 = process.leadingJetSelection.clone (src = 'tightLeadingPFJets', minNumber = 1)
process.leadingJetSelectionNjets2 = process.leadingJetSelection.clone (src = 'tightLeadingPFJets', minNumber = 2)
process.leadingJetSelectionNjets3 = process.leadingJetSelection.clone (src = 'tightLeadingPFJets', minNumber = 3)
process.leadingJetSelectionNjets4 = process.leadingJetSelection.clone (src = 'tightLeadingPFJets', minNumber = 4)

## ---
##    Set up low level selection steps (sligthly above trigger) for monitoring
## ---
from TopAnalysis.TopFilter.sequences.jetSelection_cff import selectedPatJets
process.looseCentralJets = selectedPatJets.clone(src = 'selectedPatJetsAK5PF', cut = 'abs(eta) < 2.5 & pt > 30.')
process.looseJetSelectionNjets3 = process.leadingJetSelection.clone (src = 'looseCentralJets', minNumber = 3)
process.looseCuts = cms.Sequence(process.looseCentralJets*process.kinematicMuonsSelection+process.looseJetSelectionNjets3)
                               
## ---
##    Set up selection steps for different (gen)-jet multiplicities
## ---
process.leadingGenJetSelectionNjets1 = process.leadingGenJetSelection.clone (src = 'selectedGenJetCollection', minNumber = 1)
process.leadingGenJetSelectionNjets2 = process.leadingGenJetSelection.clone (src = 'selectedGenJetCollection', minNumber = 2)
process.leadingGenJetSelectionNjets3 = process.leadingGenJetSelection.clone (src = 'selectedGenJetCollection', minNumber = 3)
process.leadingGenJetSelectionNjets4 = process.leadingGenJetSelection.clone (src = 'selectedGenJetCollection', minNumber = 4)

process.genJetCuts = cms.Sequence(process.leadingGenJetSelectionNjets1 +
                                  process.leadingGenJetSelectionNjets2 +
                                  process.leadingGenJetSelectionNjets3 +
                                  process.leadingGenJetSelectionNjets4 
                                  )
process.selectedGenMuonCollection.cut=cms.string('abs(eta) < 2.1 & pt > 30.')
process.selectedGenElectronCollection.cut=cms.string('abs(eta) < 2.1 & pt > 30.')
process.genAllMuonKinematics = process.analyzeMuonKinematics.clone    (src = 'isolatedGenMuons')
process.genAllElectronKinematics = process.analyzeElectronKinematics.clone(src = 'isolatedGenElectrons')
process.genAllJetKinematics  = process.analyzeJetKinematics.clone(src = 'ak5GenJets', analyze = udsAll)
process.genSelJetKinematics  = process.analyzeJetKinematics.clone(src = 'selectedGenJetCollection', analyze = udsAll)
process.hadLvObjectMonitoring = cms.Sequence(process.genAllElectronKinematics *
                                             process.genAllMuonKinematics     *
                                             process.genAllJetKinematics      *
                                             process.genSelJetKinematics      
                                             )
## ---
##    Set up selection for b-jet multiplicity
## ---

## switch to desired btagging algo
process.tightBottomPFJets.src = bTagAlgo+"s"
## select number of b tags
process.btagSelection = process.bottomJetSelection.clone(src = 'tightBottomPFJets', minNumber = 2, maxNumber = 99999)
process.btagSelectionSSV=process.btagSelection.clone(src = 'simpleSecondaryVertexHighEffBJets')

## kinematic contributions
## muon
process.tightMuonKinematics        = process.analyzeMuonKinematics.clone (src = 'tightMuons')
process.tightMuonQuality           = process.analyzeMuonQuality.clone    (src = 'tightMuons')
process.tightMuonKinematicsTagged  = process.tightMuonKinematics.clone();
process.tightMuonQualityTagged     = process.tightMuonQuality.clone();
process.tightMuonKinematicsSSV  = process.analyzeMuonKinematics.clone (src = 'tightMuons'    )
process.tightMuonQualitySSV     = process.analyzeMuonQuality.clone    (src = 'tightMuons'    )

process.tightMuonKinematicsNjets1 = process.tightMuonKinematics.clone() 
process.tightMuonQualityNjets1    = process.tightMuonQuality.clone   ()    
process.tightMuonKinematicsNjets2 = process.tightMuonKinematics.clone() 
process.tightMuonQualityNjets2    = process.tightMuonQuality.clone   ()
process.tightMuonKinematicsNjets3 = process.tightMuonKinematics.clone() 
process.tightMuonQualityNjets3    = process.tightMuonQuality.clone   ()

## jets
process.tightLead_0_JetKinematics = process.analyzeJetKinematics.clone(src = 'tightLeadingPFJets', analyze = uds0 )
process.tightLead_1_JetKinematics = process.analyzeJetKinematics.clone(src = 'tightLeadingPFJets', analyze = uds1 )
process.tightLead_2_JetKinematics = process.analyzeJetKinematics.clone(src = 'tightLeadingPFJets', analyze = uds2 )
process.tightLead_3_JetKinematics = process.analyzeJetKinematics.clone(src = 'tightLeadingPFJets', analyze = uds3 )
process.tightJetKinematics        = process.analyzeJetKinematics.clone(src = 'tightLeadingPFJets', analyze = udsAll)
process.tightJetQuality           = process.analyzeJetQuality.clone   (src = 'tightLeadingPFJets')
process.bottomJetKinematics       = process.analyzeJetKinematics.clone(src = 'tightBottomPFJets', analyze = udsAll)
process.bottomJetQuality          = process.analyzeJetQuality.clone(src = 'tightBottomPFJets')
process.tightJetKinematicsSSV  = process.analyzeJetKinematics.clone(src = 'tightLeadingPFJets', analyze = udsAll)
process.tightJetQualitySSV     = process.analyzeJetQuality.clone   (src = 'tightLeadingPFJets')

process.tightJetKinematicsNjets1=process.tightJetKinematics.clone()
process.tightJetQualityNjets1   =process.tightJetQuality   .clone()
process.tightJetKinematicsNjets2=process.tightJetKinematics.clone()
process.tightJetQualityNjets2   =process.tightJetQuality   .clone()
process.tightJetKinematicsNjets3=process.tightJetKinematics.clone()
process.tightJetQualityNjets3   =process.tightJetQuality   .clone()

process.tightLead_0_JetKinematicsTagged  = process.tightLead_0_JetKinematics.clone()
process.tightLead_1_JetKinematicsTagged  = process.tightLead_1_JetKinematics.clone()
process.tightLead_2_JetKinematicsTagged  = process.tightLead_2_JetKinematics.clone()
process.tightLead_3_JetKinematicsTagged  = process.tightLead_3_JetKinematics.clone()
process.tightJetKinematicsTagged         = process.tightJetKinematics.clone()
process.tightJetQualityTagged            = process.tightJetQuality.clone()
process.bottomJetKinematicsTagged        = process.bottomJetKinematics.clone()
process.bottomJetQualityTagged           = process.bottomJetQuality.clone()
process.bottomLead_0_JetKinematicsTagged = process.analyzeJetKinematics.clone (src = 'tightBottomPFJets', analyze = uds0 )
process.bottomLead_1_JetKinematicsTagged = process.analyzeJetKinematics.clone (src = 'tightBottomPFJets', analyze = uds1 )

## muon&jets
process.tightMuontightJetsKinematics       = process.analyzeMuonJetKinematics.clone(srcA = 'tightMuons', srcB = 'tightLeadingPFJets')
process.tightMuontightJetsKinematicsTagged = process.tightMuontightJetsKinematics.clone()
process.tightMuontightJetsKinematicsSSV = process.analyzeMuonJetKinematics.clone(srcA = 'tightMuons', srcB = 'vetoJets')

## electrons
process.tightElectronKinematics        = process.analyzeElectronKinematics.clone( src = 'goodElectronsEJ'  )
process.tightElectronQuality           = process.analyzeElectronQuality.clone   ( src = 'goodElectronsEJ'  )
process.tightElectronKinematicsTagged  = process.analyzeElectronKinematics.clone( src = 'goodElectronsEJ'  )
process.tightElectronQualityTagged     = process.analyzeElectronQuality.clone   ( src = 'goodElectronsEJ'  )
process.tightElectronKinematicsSSV     = process.analyzeElectronKinematics.clone( src = 'goodElectronsEJ'  )
process.tightElectronQualitySSV        = process.analyzeElectronQuality.clone   ( src = 'goodElectronsEJ'  )

process.tightElectronKinematicsNjets1  = process.tightElectronKinematics.clone()
process.tightElectronQualityNjets1     = process.tightElectronQuality   .clone()
process.tightElectronKinematicsNjets2  = process.tightElectronKinematics.clone()
process.tightElectronQualityNjets2     = process.tightElectronQuality   .clone()
process.tightElectronKinematicsNjets3  = process.tightElectronKinematics.clone()
process.tightElectronQualityNjets3     = process.tightElectronQuality   .clone()

## MET
process.analyzeMETMuon       = process.analyzeMETCorrelations.clone(srcA = 'patMETs', srcB='tightMuons')
process.analyzeMETMuonTagged = process.analyzeMETMuon.clone()

## ---
##    PU reweighting monitoring
## ---
process.load("TopAnalysis.TopAnalyzer.PUControlDistributions_cfi")
process.PUControlDistributions.PUSource                   = cms.InputTag("addPileupInfo"                       )
process.PUControlDistributions.PVertexSource              = cms.InputTag("goodOfflinePrimaryVertices"          )
process.PUControlDistributions.PUEventWeightSource        = cms.InputTag("eventWeightPUsysNo",  "eventWeightPU"       )
process.PUControlDistributions.PUEventWeightUpSource      = cms.InputTag("eventWeightPUsysUp",  "eventWeightPUUp"     )
process.PUControlDistributions.PUEventWeightDownSource    = cms.InputTag("eventWeightPUsysDown","eventWeightPUDown"   )
process.PUControlDistributions.MCSampleTag                = options.mctag

process.PUControlDistributionsDefault        = process.PUControlDistributions.clone()
process.PUControlDistributionsBeforeBtagging = process.PUControlDistributions.clone()
process.PUControlDistributionsAfterBtagging  = process.PUControlDistributions.clone()

## collect kinematics
process.monitorKinematicsNjets1 = cms.Sequence(process.tightJetKinematicsNjets1  +
                                               process.tightJetQualityNjets1
                                               )

process.monitorKinematicsNjets2 = cms.Sequence(process.tightJetKinematicsNjets2  +
                                               process.tightJetQualityNjets2
                                               )

process.monitorKinematicsNjets3 = cms.Sequence(process.tightJetKinematicsNjets3  +
                                               process.tightJetQualityNjets3
                                               )


if(decayChannel =='muon'):
    process.monitorKinematicsNjets1 += cms.Sequence(process.tightMuonKinematicsNjets1 +
                                                    process.tightMuonQualityNjets1    
                                                    )
    process.monitorKinematicsNjets2 += cms.Sequence(process.tightMuonKinematicsNjets2 +
                                                    process.tightMuonQualityNjets2    
                                                    )
    process.monitorKinematicsNjets3 += cms.Sequence(process.tightMuonKinematicsNjets3 +
                                                    process.tightMuonQualityNjets3    
                                                    )
elif(decayChannel =='electron'):
    process.monitorKinematicsNjets1 += cms.Sequence(process.tightElectronKinematicsNjets1 +
                                                    process.tightElectronQualityNjets1    
                                                    )
    process.monitorKinematicsNjets2 += cms.Sequence(process.tightElectronKinematicsNjets2 +
                                                    process.tightElectronQualityNjets2    
                                                    )
    process.monitorKinematicsNjets3 += cms.Sequence(process.tightElectronKinematicsNjets3 +
                                                    process.tightElectronQualityNjets3    
                                                    )
     
    
process.monitorKinematicsBeforeBtagging = cms.Sequence(process.tightMuonKinematics          +
                                                       process.tightMuonQuality             +
                                                       process.tightLead_0_JetKinematics    +
                                                       process.tightLead_1_JetKinematics    +
                                                       process.tightLead_2_JetKinematics    +
                                                       process.tightLead_3_JetKinematics    +
                                                       process.tightJetKinematics           +
                                                       process.tightJetQuality              +
                                                       process.bottomJetKinematics          +
						       process.bottomJetQuality             +
                                                       process.analyzeMETMuon               +
                                                       process.tightMuontightJetsKinematics
                                                       )


process.monitorKinematicsAfterBtagging = cms.Sequence(process.tightMuonKinematicsTagged          +
                                                      process.tightMuonQualityTagged             +
                                                      process.tightLead_0_JetKinematicsTagged    +
                                                      process.tightLead_1_JetKinematicsTagged    +
                                                      process.tightLead_2_JetKinematicsTagged    +
                                                      process.tightLead_3_JetKinematicsTagged    +
                                                      process.tightJetKinematicsTagged           +
                                                      process.tightJetQualityTagged              +
                                                      process.bottomJetKinematicsTagged          +
                                                      process.bottomJetQualityTagged             +
                                                      process.analyzeMETMuonTagged               +
                                                      process.tightMuontightJetsKinematicsTagged +
                                                      process.bottomLead_0_JetKinematicsTagged   +
                                                      process.bottomLead_1_JetKinematicsTagged
                                                      )
    
process.SSVMonitoring = cms.Sequence(process.tightMuontightJetsKinematicsSSV +
                                     process.tightMuonKinematicsSSV          +
                                     process.tightMuonQualitySSV             +
                                     process.tightJetKinematicsSSV           +
                                     process.tightJetQualitySSV              
                                     )

process.monitorElectronKinematicsBeforeBtagging = cms.Sequence(process.tightElectronKinematics+
                                                               process.tightElectronQuality   )
process.monitorElectronKinematicsAfterBtagging  = cms.Sequence(process.tightElectronKinematicsTagged+
                                                               process.tightElectronQualityTagged   )

# combined jet selection+monitoring
process.jetSelection = cms.Sequence(process.leadingJetSelectionNjets1 +
                                    process.monitorKinematicsNjets1   +
                                    process.leadingJetSelectionNjets2 +
                                    process.monitorKinematicsNjets2   +
                                    process.leadingJetSelectionNjets3 +
                                    process.monitorKinematicsNjets3   +
                                    process.leadingJetSelectionNjets4 
                                    )

## ---
##    configure Kinematic fit
## ---

## produce top reconstructed event
process.load('TopQuarkAnalysis.TopEventProducers.sequences.ttSemiLepEvtBuilder_cff')
## process.ttSemiLepJetPartonMatch.verbosity = 1

# add hypothesis
from TopQuarkAnalysis.TopEventProducers.sequences.ttSemiLepEvtBuilder_cff import *
addTtSemiLepHypotheses(process,['kKinFit'])
if(decayChannel=='electron'):
    useElectronsForAllTtSemiLepHypotheses(process,'goodElectronsEJ')
if(eventFilter=='signal only') and (runningOnData=="MC"):
    if(applyKinFit==True):
        print ' kinFit: processing ttbar SG MC - build genmatch'
else:
    removeTtSemiLepHypGenMatch(process)
    if(applyKinFit==True):
        print ' kinFit: processing bkg or data - genmatch removed'

## choose collections
## in fitting procedure
process.kinFitTtSemiLepEventHypothesis.leps = 'tightMuons'
process.kinFitTtSemiLepEventHypothesis.jets = 'tightLeadingPFJets'
process.kinFitTtSemiLepEventHypothesis.mets = 'patMETsPF'
## in genmatch
process.ttSemiLepHypGenMatch.jets = 'tightLeadingPFJets'
process.ttSemiLepHypGenMatch.leps = 'tightMuons'
process.ttSemiLepHypGenMatch.mets = 'patMETsPF'
process.ttSemiLepHypGenMatch.jetCorrectionLevel=corrLevel
## in event hypothesis used for 
process.ttSemiLepHypKinFit.jets = 'tightLeadingPFJets'
process.ttSemiLepHypKinFit.leps = 'tightMuons'
process.ttSemiLepHypKinFit.mets = 'patMETsPF'
process.ttSemiLepEvent.verbosity=0

# maximum number of jets to be considered in the jet combinatorics
# (has to be >= 4, can be set to -1 if you want to take all)
process.kinFitTtSemiLepEventHypothesis.maxNJets = 5

# maximum number of jet combinations finally written into the event, starting from the "best"
# (has to be >= 1, can be set to -1 if you want to take all)
process.kinFitTtSemiLepEventHypothesis.maxNComb = 3

# set constraints:: 1: Whad-mass, 2: Wlep-mass, 3: thad-mass, 4: tlep-mass, 5: nu-mass, 6: equal t-masses, 7: Pt balance
process.kinFitTtSemiLepEventHypothesis.constraints = [1, 2, 6]
#process.kinFitTtSemiLepEventHypothesis.constraints = [1, 2, 3, 4]
process.kinFitTtSemiLepEventHypothesis.mTop = 172.5

# consider b-tagging in event reconstruction
process.kinFitTtSemiLepEventHypothesis.bTagAlgo = bTagAlgo+"Tags" # "simpleSecondaryVertexHighEffBJetTags"

# TCHE  discr.values 7TeV: 1.70,  3.30  , 10.20
# SSVHE discr.values 7TeV: x.xx,  1.74  ,  x.xx
# CSV   discr.values 7TeV: 0.244, 0.679 , 0.898
process.kinFitTtSemiLepEventHypothesis.minBDiscBJets     = bTagDiscrCut
process.kinFitTtSemiLepEventHypothesis.maxBDiscLightJets = bTagDiscrCut
process.kinFitTtSemiLepEventHypothesis.useBTagging       = True

# eta-dependent scaling of JER (input to kinFit)
if(applyKinFit==True):
    process.kinFitTtSemiLepEventHypothesis.jetEnergyResolutionScaleFactors = cms.vdouble( 1.052 , 1.057 , 1.096 , 1.134 , 1.288   )
    process.kinFitTtSemiLepEventHypothesis.jetEnergyResolutionEtaBinning = cms.vdouble(0.0  ,  0.5  ,  1.1  ,  1.7  ,  2.3  ,  -1.)
    
## keep only events with unambigues parton matches
## (no other partons exist in dR=0.3 cone) 
## attention: improves purity but reduces efficiency
if(eventFilter=='signal only') and (runningOnData=="MC"):
    process.ttSemiLepJetPartonMatch.algorithm = "unambiguousOnly"
    #process.ttSemiLepJetPartonMatch.algorithm = "totalMinDist"
    process.ttSemiLepJetPartonMatch.useMaxDist = True
    ## set number of jets considered in jet-parton matching
    process.ttSemiLepJetPartonMatch.maxNJets=-1
    ## choose jet collection considered in jet-parton matching
    process.ttSemiLepJetPartonMatch.jets='tightLeadingPFJets'
    
## ---
##    configure KinFit Analyzers
## ---

## kinfit succeeded?
process.load("TopQuarkAnalysis.TopEventProducers.producers.TtSemiLepEvtFilter_cfi")
process.filterRecoKinFit  = process.ttSemiLepEventFilter.clone( cut = cms.string("isHypoValid('kKinFit')"  ) )
process.filterProbKinFit  = process.ttSemiLepEventFilter.clone( cut = cms.string("isHypoValid('kKinFit') && fitProb>0.05"  ) )
process.filterMatchKinFit = process.ttSemiLepEventFilter.clone( cut = cms.string("isHypoValid('kGenMatch')") )

## configure top reconstruction analyzers & define PSets
## A) for top reconstruction analyzer
process.load("TopAnalysis.TopAnalyzer.TopKinematics_cfi")
## 1)  plots built from event hypothesis kinFit after reco selection
recoKinFit        = cms.PSet(hypoKey=cms.string('kKinFit'  ), lepton=cms.string(decayChannel), useTree=cms.bool(True),
                             matchForStabilityAndPurity=cms.bool(False), ttbarInsteadOfLepHadTop = cms.bool(False),
                             maxNJets = process.kinFitTtSemiLepEventHypothesis.maxNJets)
process.analyzeTopRecoKinematicsKinFit = process.analyzeTopRecKinematics.clone(analyze=recoKinFit)
## 2)  same as 1) but for top/antitop instead of leptonic/hadronic top
recoKinFitTopAntitop = cms.PSet(hypoKey=cms.string('kKinFit'  ), lepton=cms.string(decayChannel), useTree=cms.bool(True),
                                matchForStabilityAndPurity=cms.bool(False), ttbarInsteadOfLepHadTop = cms.bool(True),
                                maxNJets = process.kinFitTtSemiLepEventHypothesis.maxNJets)
process.analyzeTopRecoKinematicsKinFitTopAntitop = process.analyzeTopRecKinematics.clone(analyze=recoKinFitTopAntitop)
## 3)  plots built from event hypothesis of objects from genmatch to partons (ttSemiLepJetPartonMatch) after reco selection
recoGenMatch      = cms.PSet(hypoKey=cms.string('kGenMatch'), lepton=cms.string(decayChannel), useTree=cms.bool(True),
                             matchForStabilityAndPurity=cms.bool(False), ttbarInsteadOfLepHadTop = cms.bool(False),
                             maxNJets = process.kinFitTtSemiLepEventHypothesis.maxNJets)
process.analyzeTopRecoKinematicsGenMatch      = process.analyzeTopRecKinematics.clone(analyze=recoGenMatch)
## 4) plots built from parton level objects
## a) after parton level phase space selection
genTtbarSemiMu    = cms.PSet(hypoKey=cms.string("None"     ), lepton=cms.string(decayChannel), useTree=cms.bool(True),
                             matchForStabilityAndPurity=cms.bool(False), ttbarInsteadOfLepHadTop = cms.bool(False),
                             maxNJets = process.kinFitTtSemiLepEventHypothesis.maxNJets)
process.analyzeTopPartonLevelKinematics = process.analyzeTopGenKinematics.clone(analyze=genTtbarSemiMu)
## b) without phase space selection
process.analyzeTopPartonLevelKinematicsPhaseSpace = process.analyzeTopGenKinematics.clone(analyze=genTtbarSemiMu)
## c) after hadron level phase space selection
process.analyzeTopHadronLevelKinematicsPhaseSpace = process.analyzeTopGenKinematics.clone(analyze=genTtbarSemiMu)
## 5) same as 1) for monitoring before probability selection
process.analyzeTopRecoKinematicsKinFitBeforeProbSel = process.analyzeTopRecoKinematicsKinFit.clone()

## configure Kin Fit performance analyzers
process.load("TopAnalysis.TopAnalyzer.HypothesisKinFit_cfi"    )
hypoKinFit = cms.PSet(hypoKey = cms.string("kKinFit"),
                      lepton  = cms.string(decayChannel),
                      wantTree = cms.bool(True),
                      maxNJets = process.kinFitTtSemiLepEventHypothesis.maxNJets)
process.analyzeHypoKinFit = process.analyzeHypothesisKinFit.clone(analyze=hypoKinFit)


## B object reconstruction quality
# 1) Psets:
# a) all
analyzeAll = cms.PSet( corrPerm=cms.bool(False), maxChi2=cms.double(10000) )
# b) correct permutation
analyzeCorrect = cms.PSet( corrPerm=cms.bool(True), maxChi2=cms.double(10000) )
# 2) lepton
process.load("TopAnalysis.TopAnalyzer.HypothesisKinFitLepton_cfi")
process.analyzeHypoKinFitLepton      = process.analyzeHypothesisKinFitLepton.clone(srcA = "ttSemiLepEvent", srcB = "tightMuons", analyze=analyzeAll    )
process.analyzeHypoKinFitLeptonCorr  = process.analyzeHypothesisKinFitLepton.clone(srcA = "ttSemiLepEvent", srcB = "tightMuons", analyze=analyzeCorrect)
# 3) jets
process.load("TopAnalysis.TopAnalyzer.HypothesisKinFitJets_cfi")
process.analyzeHypoKinFitJets      = process.analyzeHypothesisKinFitJets.clone(srcA = "ttSemiLepEvent", srcB = "tightLeadingPFJets", analyze=analyzeAll    )
process.analyzeHypoKinFitJetsCorr  = process.analyzeHypothesisKinFitJets.clone(srcA = "ttSemiLepEvent", srcB = "tightLeadingPFJets", analyze=analyzeCorrect)
# 4) neutrino/MET
process.load("TopAnalysis.TopAnalyzer.HypothesisKinFitMET_cfi" )
process.analyzeHypoKinFitMET      = process.analyzeHypothesisKinFitMET.clone(srcA = "ttSemiLepEvent", srcB = "patMETs", analyze=analyzeAll    )
process.analyzeHypoKinFitMETCorr  = process.analyzeHypothesisKinFitMET.clone(srcA = "ttSemiLepEvent", srcB = "patMETs", analyze=analyzeCorrect)

## ---
##    b hadron level distributions
## ---
## tool to identify b-jets from genjet collection
process.load("TopAnalysis.TopUtils.GenLevelBJetProducer_cfi")
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi") # supplies PDG ID to real name resolution of MC particles, necessary for GenLevelBJetProducer
process.makeGenLevelBJets=process.produceGenLevelBJets.clone(
    ttGenEvent = cms.InputTag('genEvt'),
    genJets = cms.InputTag('ak5GenJets','','HLT'),
    deltaR = cms.double(5.0),
    resolveParticleName = cms.bool(False),
    requireTopBquark = cms.bool(False),
    noBBbarResonances = cms.bool(True)
)
# make b jet gen and rec plots using the identification from above
process.load("TopAnalysis.TopAnalyzer.SemiLepBjetAnalyzer_cfi")
process.analyzeTopRecoKinematicsBjets=process.analyzeSemiLepBJets.clone(
    semiLepEvent = cms.InputTag("ttSemiLepEvent"),
    hypoKey = cms.string("kKinFit"),
    genJets = cms.InputTag('ak5GenJets','','HLT'),
    output = cms.int32(0),
    weight = cms.InputTag(""),
    genPlots = cms.bool(True),
    recPlots = cms.bool(True),
    BHadJetIndex     = cms.InputTag("makeGenLevelBJets", "BHadJetIndex"    ),
    AntiBHadJetIndex = cms.InputTag("makeGenLevelBJets", "AntiBHadJetIndex"),
    useTree = cms.bool(True)
    )

process.analyzeTopPartonLevelKinematicsBjets=process.analyzeTopRecoKinematicsBjets.clone(recPlots = cms.bool(False))
process.analyzeTopPartonLevelKinematicsBjetsPhaseSpace=process.analyzeTopRecoKinematicsBjets.clone(recPlots = cms.bool(False))
process.analyzeTopHadronLevelKinematicsBjetsPhaseSpace=process.analyzeTopRecoKinematicsBjets.clone(recPlots = cms.bool(False))

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
            process.kinFit    = cms.Sequence(process.makeTtSemiLepEvent                      +
                                             process.filterRecoKinFit                        +
                                             process.analyzeTopRecoKinematicsKinFitBeforeProbSel+
                                             #process.filterProbKinFit                        +
                                             process.analyzeTopRecoKinematicsKinFit          +
                                             process.analyzeTopRecoKinematicsKinFitTopAntitop+
                                             process.analyzeTopRecoKinematicsGenMatch        +
                                             process.analyzeHypoKinFit                       +
                                             process.analyzeHypoKinFitLepton                 +
                                             process.analyzeHypoKinFitLeptonCorr             +
                                             process.analyzeHypoKinFitMET                    +
                                             process.analyzeHypoKinFitMETCorr                +
                                             process.analyzeHypoKinFitJets                   +
                                             process.analyzeHypoKinFitJetsCorr               +
                                             # add bjet indices
                                             process.makeGenLevelBJets                       +
                                             process.analyzeTopRecoKinematicsBjets           +
                                             process.filterMatchKinFit
                                             )
            process.kinFitGen           = cms.Sequence(process.analyzeTopPartonLevelKinematics     +
                                                       # add bjet indices
                                                       process.makeGenLevelBJets                   +
                                                       # add bjet analyzer
                                                       process.analyzeTopPartonLevelKinematicsBjets
                                                       )
            process.kinFitGenPhaseSpace = cms.Sequence(process.analyzeTopPartonLevelKinematicsPhaseSpace+
                                                       # add bjet indices
                                                       process.makeGenLevelBJets                        +
                                                       # add bjet analyzer
                                                       process.analyzeTopPartonLevelKinematicsBjetsPhaseSpace
                                                       )
            process.kinFitGenPhaseSpaceHad = cms.Sequence(process.analyzeTopHadronLevelKinematicsPhaseSpace +
                                                          # add bjet indices
                                                          process.makeGenLevelBJets                         +
                                                          # add bjet analyzer
                                                          process.analyzeTopHadronLevelKinematicsBjetsPhaseSpace
                                                          )

        ## case 1b): other MC
        else:
            process.kinFit    = cms.Sequence(process.makeTtSemiLepEvent                      +
                                             process.filterRecoKinFit                        +
                                             process.analyzeTopRecoKinematicsKinFitBeforeProbSel+
                                             #process.filterProbKinFit                        +
                                             process.analyzeTopRecoKinematicsKinFitTopAntitop+
                                             process.analyzeTopRecoKinematicsKinFit          
                                             )
            process.kinFitGen           = cms.Sequence(process.dummy)
            process.kinFitGenPhaseSpace = cms.Sequence(process.dummy)
            process.kinFitGenPhaseSpaceHad = cms.Sequence(process.dummy)
    ## case 2: data sample
    elif(runningOnData=="data"):
        process.kinFit    = cms.Sequence(process.makeTtSemiLepEvent                      +
                                         process.filterRecoKinFit                        +
                                         process.analyzeTopRecoKinematicsKinFitBeforeProbSel+
                                         #process.filterProbKinFit                        +
                                         process.analyzeTopRecoKinematicsKinFit          +
                                         process.analyzeTopRecoKinematicsKinFitTopAntitop
                                         )
        process.kinFitGen           = cms.Sequence(process.dummy)
        process.kinFitGenPhaseSpace = cms.Sequence(process.dummy)
        process.kinFitGenPhaseSpaceHad = cms.Sequence(process.dummy)
    else:
         print "choose runningOnData= data or MC"
else:
    process.kinFit              = cms.Sequence(process.dummy)
    process.kinFitGen           = cms.Sequence(process.dummy)
    process.kinFitGenPhaseSpace = cms.Sequence(process.dummy)
    process.kinFitGenPhaseSpaceHad = cms.Sequence(process.dummy)

## ============================
##  MC PU reweighting
## ============================

process.load("TopAnalysis.TopUtils.EventWeightPU_cfi")

## Apply common setting before module is cloned for systematic studies

process.eventWeightPU.MCSampleTag = options.mctag

if (options.mctag == "Fall11"):
    process.eventWeightPU.MCSampleHistoName        = "histo_Fall11_true"
    process.eventWeightPU.DataHistoName            = "histoData_true"
elif (options.mctag == "Summer11"):    
    process.eventWeightPU.MCSampleHistoName        = "histoSummer11_flat_true"
    process.eventWeightPU.DataHistoName            = "histoData_true_fineBinning"

process.eventWeightPUsysNo   = process.eventWeightPU.clone()
process.eventWeightPUsysUp   = process.eventWeightPU.clone()
process.eventWeightPUsysDown = process.eventWeightPU.clone()

#### Parameters 'CreateWeight3DHisto' and 'Weight3DHistoFile' required for cff-file, but actually not used for Fall11 samples
    
#### Configuration for Nominal PU Weights

process.eventWeightPUsysNo.WeightName          = "eventWeightPU"
process.eventWeightPUsysNo.DataFile            = "TopAnalysis/TopUtils/data/Data_PUDist_2011Full.root"
process.eventWeightPUsysNo.CreateWeight3DHisto = False 
process.eventWeightPUsysNo.Weight3DHistoFile   = "TopAnalysis/TopUtils/data/DefaultWeight3D.root"

#### Configuration for PU Up Variations

process.eventWeightPUsysUp.WeightName          = "eventWeightPUUp"
process.eventWeightPUsysUp.DataFile            = "TopAnalysis/TopUtils/data/Data_PUDist_sysUp_2011Full.root"
process.eventWeightPUsysUp.CreateWeight3DHisto = False
process.eventWeightPUsysUp.Weight3DHistoFile   = "TopAnalysis/TopUtils/data/DefaultWeight3DUp.root"

#### Configuration for PU Down Variations

process.eventWeightPUsysDown.WeightName          = "eventWeightPUDown"
process.eventWeightPUsysDown.DataFile            = "TopAnalysis/TopUtils/data/Data_PUDist_sysDown_2011Full.root"
process.eventWeightPUsysDown.CreateWeight3DHisto = False
process.eventWeightPUsysDown.Weight3DHistoFile   = "TopAnalysis/TopUtils/data/DefaultWeight3DDown.root"

#### event weight sequence

process.makeEventWeightsPU = cms.Sequence(process.eventWeightPUsysNo   *
                                          process.eventWeightPUsysUp   *
                                          process.eventWeightPUsysDown  )

#### relevant PU event weights (potentially merged with shape distortion weights)

PUweightraw     = cms.InputTag("eventWeightPUsysNo",  "eventWeightPU")
PUweightrawUp   = cms.InputTag("eventWeightPUsysUp",  "eventWeightPUUp")
PUweightrawDown = cms.InputTag("eventWeightPUsysDown","eventWeightPUDown")

## =================================================
##    MC ttbar systematic variation reweighting
## =================================================

## tool to multiply event weights
process.load("TopAnalysis.TopUtils.EventWeightMultiplier_cfi")
## load weight producer
process.load("TopAnalysis.TopUtils.EventWeightDileptonModelVariation_cfi")
# specify parameters
#process.eventWeightDileptonModelVariation.variation=cms.string(sysDistort)
#process.eventWeightDileptonModelVariation.ttGenEvent=cms.InputTag('genEvt')
process.eventWeightDileptonModelVariation.ttGenEvent = cms.InputTag('genEvt')
process.eventWeightDileptonModelVariation.weightVariable = cms.string('ttbarmass') #valid values: toppt, topeta, ttbarmass
process.eventWeightDileptonModelVariation.slope = cms.double(0.03)
process.eventWeightDileptonModelVariation.weight1x = cms.double(350)  #position where weight is 1
process.eventWeightDileptonModelVariation.minWeight = cms.double(0.1) #low cut-off, at least 0.1 event weight
process.eventWeightDileptonModelVariation.maxWeight = cms.double(100)  #high cut-off, at most 2 event weight
process.eventWeightDileptonModelVariation.landauMPV = cms.double(420)
process.eventWeightDileptonModelVariation.landauSigma = cms.double(34)
if(sysDistort=='up'):
    process.eventWeightDileptonModelVariation.landauMoveX = cms.double(100)
if(sysDistort=='down'):
    process.eventWeightDileptonModelVariation.landauMoveX = cms.double(-100)
# multiply with PU weight
eventWeightDileptonModelVariation=cms.InputTag("eventWeightDileptonModelVariation")
weightlistDistortPU=cms.VInputTag()
weightlistDistortPU.append(PUweightraw)
weightlistDistortPU.append(eventWeightDileptonModelVariation)
weightlistDistortPUup=cms.VInputTag()
weightlistDistortPUup.append(PUweightrawUp)
weightlistDistortPUup.append(eventWeightDileptonModelVariation)
weightlistDistortPUdown=cms.VInputTag()
weightlistDistortPUdown.append(PUweightrawDown)
weightlistDistortPUdown.append(eventWeightDileptonModelVariation)
process.eventWeightPUDistort     = process.eventWeightMultiplier.clone(eventWeightTags = weightlistDistortPU)
process.eventWeightPUupDistort   = process.eventWeightMultiplier.clone(eventWeightTags = weightlistDistortPUup)
process.eventWeightPUdownDistort = process.eventWeightMultiplier.clone(eventWeightTags = weightlistDistortPUdown)
if(sysDistort==''):
    # final PU weights without shape distortion weights
    PUweight    =cms.InputTag("eventWeightPUsysNo",  "eventWeightPU")
    PUweightUp  =cms.InputTag("eventWeightPUsysUp",  "eventWeightPUUp")
    PUweightDown=cms.InputTag("eventWeightPUsysDown","eventWeightPUDown")
else:
    # final PU x shape distortion weights
    PUweight    =cms.InputTag("eventWeightPUDistort")
    PUweightUp  =cms.InputTag("eventWeightPUupDistort")
    PUweightDown=cms.InputTag("eventWeightPUdownDistort")

## ---
##    MC B-tag reweighting
## ---
## load BTV database
process.load ("RecoBTag.PerformanceDB.PoolBTagPerformanceDB1107")
process.load ("RecoBTag.PerformanceDB.BTagPerformanceDB1107")

process.load("TopAnalysis.TopUtils.BTagSFEventWeight_cfi")
## DB only accepts short tagger algo names
bTagAlgoShort = "CSVM"
if(bTagAlgo =='simpleSecondaryVertexHighEffBJet'):
    bTagAlgoShort = "SSVHEM"
process.bTagSFEventWeight.jets=cms.InputTag("tightLeadingPFJets")
process.bTagSFEventWeight.bTagAlgo=bTagAlgoShort
process.bTagSFEventWeight.version="11-004"
process.bTagSFEventWeight.sysVar   = cms.string("") # bTagSFUp, bTagSFDown, misTagSFUp, misTagSFDown, 
                                                    # bTagSFShapeUpPt, bTagSFShapeDownPt, bTagSFShapeUpEta, bTagSFShapeDownEta possible;
process.bTagSFEventWeight.filename= "TopAnalysis/Configuration/data/analyzeBTagEfficiency"+bTagAlgoShort+".root"
process.bTagSFEventWeight.verbose=cms.int32(0)

## for SSV:
process.bTagSFEventWeightSSV                      =  process.bTagSFEventWeight.clone(bTagAlgo = "SSVHEM", 
                                                                       filename = "TopAnalysis/Configuration/data/analyzeBTagEfficiencySSVHEM.root")

process.bTagSFEventWeightBTagSFUp                  = process.bTagSFEventWeight.clone(sysVar = "bTagSFUp")
process.bTagSFEventWeightBTagSFDown                = process.bTagSFEventWeight.clone(sysVar = "bTagSFDown")
process.bTagSFEventWeightMisTagSFUp                = process.bTagSFEventWeight.clone(sysVar = "misTagSFUp")
process.bTagSFEventWeightMisTagSFDown              = process.bTagSFEventWeight.clone(sysVar = "misTagSFDown")
## per default SF is only varied by half of the BTV uncertainty for shape variations in BTagSFEventWeight_cfi 
## -> "HalfShape" not needed anymore (commented out later on)
process.bTagSFEventWeightBTagSFShapeUpPt65         = process.bTagSFEventWeight.clone(sysVar = "bTagSFShapeUpPt")
process.bTagSFEventWeightBTagSFShapeDownPt65       = process.bTagSFEventWeight.clone(sysVar = "bTagSFShapeDownPt")
process.bTagSFEventWeightBTagSFShapeUpEta0p7       = process.bTagSFEventWeight.clone(sysVar = "bTagSFShapeUpEta")
process.bTagSFEventWeightBTagSFShapeDownEta0p7     = process.bTagSFEventWeight.clone(sysVar = "bTagSFShapeDownEta")
process.bTagSFEventWeightBTagSFShapeUpPt100        = process.bTagSFEventWeight.clone(sysVar = "bTagSFShapeUpPt",    shapeVarPtThreshold   = 100.0)
process.bTagSFEventWeightBTagSFShapeDownPt100      = process.bTagSFEventWeight.clone(sysVar = "bTagSFShapeDownPt",  shapeVarPtThreshold   = 100.0)
process.bTagSFEventWeightBTagSFShapeUpEta1p2       = process.bTagSFEventWeight.clone(sysVar = "bTagSFShapeUpEta",   shapeVarEtaThreshold  =   1.2)
process.bTagSFEventWeightBTagSFShapeDownEta1p2     = process.bTagSFEventWeight.clone(sysVar = "bTagSFShapeDownEta", shapeVarEtaThreshold  =   1.2)
process.bTagSFEventWeightBTagSFHalfShapeUpPt65     = process.bTagSFEventWeight.clone(sysVar = "bTagSFShapeUpPt",    shapeDistortionFactor =   0.5)
process.bTagSFEventWeightBTagSFHalfShapeDownPt65   = process.bTagSFEventWeight.clone(sysVar = "bTagSFShapeDownPt",  shapeDistortionFactor =   0.5)
process.bTagSFEventWeightBTagSFHalfShapeUpEta0p7   = process.bTagSFEventWeight.clone(sysVar = "bTagSFShapeUpEta",   shapeDistortionFactor =   0.5)
process.bTagSFEventWeightBTagSFHalfShapeDownEta0p7 = process.bTagSFEventWeight.clone(sysVar = "bTagSFShapeDownEta", shapeDistortionFactor =   0.5)

## ---
##    MC eff SF reweighting
## ---
## scale factor for trigger and lepton selection efficiency
process.load("TopAnalysis.TopUtils.EffSFMuonEventWeight_cfi")
process.effSFMuonEventWeight.particles=cms.InputTag("tightMuons")
process.effSFMuonEventWeight.sysVar   = cms.string("")
process.effSFMuonEventWeight.filename= "TopAnalysis/Configuration/data/MuonEffSF2011.root"
process.effSFMuonEventWeight.verbose=cms.int32(0)
process.effSFMuonEventWeight.additionalFactor=1. ## lepton selection and trigger eff. SF both included in loaded histo
process.effSFMuonEventWeight.additionalFactorErr=0.01 ## 1% sys error to account for non-flatness
process.effSFMuonEventWeight.meanTriggerEffSF=0.9824
process.effSFMuonEventWeight.shapeDistortionFactor=-1

process.effSFMuonEventWeightPUup              = process.effSFMuonEventWeight.clone(sysVar = "PUup")
process.effSFMuonEventWeightPUdown            = process.effSFMuonEventWeight.clone(sysVar = "PUdown")
process.effSFMuonEventWeightFlatTriggerSF     = process.effSFMuonEventWeight.clone(sysVar = "flatTriggerSF")
process.effSFMuonEventWeightEffSFNormUpStat   = process.effSFMuonEventWeight.clone(sysVar = "combinedEffSFNormUpStat")
process.effSFMuonEventWeightEffSFNormDownStat = process.effSFMuonEventWeight.clone(sysVar = "combinedEffSFNormDownStat")
process.effSFMuonEventWeightEffSFShapeUpEta   = process.effSFMuonEventWeight.clone(sysVar = "combinedEffSFShapeUpEta")
process.effSFMuonEventWeightEffSFShapeDownEta = process.effSFMuonEventWeight.clone(sysVar = "combinedEffSFShapeDownEta")
process.effSFMuonEventWeightEffSFShapeUpPt    = process.effSFMuonEventWeight.clone(sysVar = "combinedEffSFShapeUpPt")
process.effSFMuonEventWeightEffSFShapeDownPt  = process.effSFMuonEventWeight.clone(sysVar = "combinedEffSFShapeDownPt")
process.effSFMuonEventWeightEffSFShapeUpPt40  = process.effSFMuonEventWeight.clone(sysVar = "combinedEffSFShapeUpPt",   shapeVarPtThreshold=40.0)
process.effSFMuonEventWeightEffSFShapeDownPt40= process.effSFMuonEventWeight.clone(sysVar = "combinedEffSFShapeDownPt", shapeVarPtThreshold=40.0)
process.effSFMuonEventWeighEffSFNormUpSys     = process.effSFMuonEventWeight.clone(sysVar = "combinedEffSFNormUpSys")
process.effSFMuonEventWeightEffSFNormDownSys  = process.effSFMuonEventWeight.clone(sysVar = "combinedEffSFNormDownSys")

process.load("TopAnalysis.TopUtils.EffSFElectronEventWeight_cfi")
process.effSFElectronEventWeight.particles=cms.InputTag("goodElectronsEJ")
process.effSFElectronEventWeight.sysVar   = cms.string("")
process.effSFElectronEventWeight.verbose=cms.int32(0)
process.effSFElectronEventWeight.additionalFactor=1. ## lepton selection eff. SF
process.effSFElectronEventWeight.additionalFactorErr=0.02 ## 2% sys error to account for selection difference Z - ttbar
process.effSFElectronEventWeight.meanTriggerEffSF=0.968
process.effSFElectronEventWeight.meanTriggerEffSFErr=0.004
process.effSFElectronEventWeight.shapeDistortionErr=0.02

process.effSFElectronEventWeightPUup              = process.effSFElectronEventWeight.clone(meanTriggerEffSF=0.991)
process.effSFElectronEventWeightPUdown            = process.effSFElectronEventWeight.clone(meanTriggerEffSF=0.946)
process.effSFElectronEventWeightFlatTriggerSF     = process.effSFElectronEventWeight.clone(sysVar = "flatTriggerSF")
process.effSFElectronEventWeightEffSFNormUpStat   = process.effSFElectronEventWeight.clone(sysVar = "combinedEffSFNormUpStat")
process.effSFElectronEventWeightEffSFNormDownStat = process.effSFElectronEventWeight.clone(sysVar = "combinedEffSFNormDownStat")
process.effSFElectronEventWeightEffSFShapeUpEta   = process.effSFElectronEventWeight.clone(sysVar = "combinedEffSFShapeUpEta")
process.effSFElectronEventWeightEffSFShapeDownEta = process.effSFElectronEventWeight.clone(sysVar = "combinedEffSFShapeDownEta")
process.effSFElectronEventWeightEffSFShapeUpPt    = process.effSFElectronEventWeight.clone(sysVar = "combinedEffSFShapeUpPt")
process.effSFElectronEventWeightEffSFShapeDownPt  = process.effSFElectronEventWeight.clone(sysVar = "combinedEffSFShapeDownPt")
process.effSFElectronEventWeightEffSFShapeUpPt40  = process.effSFElectronEventWeight.clone(sysVar = "combinedEffSFShapeUpPt", shapeVarPtThreshold=40.)
process.effSFElectronEventWeightEffSFShapeDownPt40= process.effSFElectronEventWeight.clone(sysVar = "combinedEffSFShapeDownPt", shapeVarPtThreshold=40.)
process.effSFElectronEventWeightEffSFNormUpSys    = process.effSFElectronEventWeight.clone(sysVar = "combinedEffSFNormUpSys")
process.effSFElectronEventWeightEffSFNormDownSys  = process.effSFElectronEventWeight.clone(sysVar = "combinedEffSFNormDownSys")

## ---
##    collect all eventweights
## ---

## create weightlists
weightlistFinal                    =cms.VInputTag()
weightlistNoEffSFWeight            =cms.VInputTag()
weightlistNoBtagSFWeight           =cms.VInputTag()
weightlistNoPUWeight               =cms.VInputTag()
weightlistPUup                     =cms.VInputTag()
weightlistPUdown                   =cms.VInputTag()
weightlistFlatTriggerSF            =cms.VInputTag()
weightlistTriggerEffSFNormUp       =cms.VInputTag()
weightlistTriggerEffSFNormDown     =cms.VInputTag()
weightlistTriggerEffSFShapeUpEta   =cms.VInputTag()
weightlistTriggerEffSFShapeDownEta =cms.VInputTag()
weightlistTriggerEffSFShapeUpPt    =cms.VInputTag()
weightlistTriggerEffSFShapeDownPt  =cms.VInputTag()
weightlistTriggerEffSFShapeUpPt40  =cms.VInputTag()
weightlistTriggerEffSFShapeDownPt40=cms.VInputTag()
weightlistSelectionEffSFNormUp     =cms.VInputTag()
weightlistSelectionEffSFNormDown   =cms.VInputTag()
weightlistFinalSSV                 =cms.VInputTag()
weightlistBtagSFup                 =cms.VInputTag()
weightlistBtagSFdown               =cms.VInputTag()
weightlistMisTagSFup               =cms.VInputTag()
weightlistMisTagSFdown             =cms.VInputTag()
weightlistBTagSFShapeUpPt65        =cms.VInputTag()
weightlistBTagSFShapeDownPt65      =cms.VInputTag()
weightlistBTagSFShapeUpEta1p2      =cms.VInputTag()
weightlistBTagSFShapeDownEta1p2    =cms.VInputTag()
weightlistBTagSFHalfShapeUpPt65    =cms.VInputTag()
weightlistBTagSFHalfShapeDownPt65  =cms.VInputTag()
weightlistBTagSFHalfShapeUpEta0p7  =cms.VInputTag()
weightlistBTagSFHalfShapeDownEta0p7=cms.VInputTag()
weightlistBTagSFShapeUpPt100       =cms.VInputTag()
weightlistBTagSFShapeDownPt100     =cms.VInputTag()
weightlistBTagSFShapeUpEta0p7      =cms.VInputTag()
weightlistBTagSFShapeDownEta0p7    =cms.VInputTag()

if(PUreweigthing):
    weightlistFinal                    .append(PUweight)
    weightlistNoBtagSFWeight           .append(PUweight)
    weightlistPUup                     .append(PUweightUp)
    weightlistPUdown                   .append(PUweightDown)
    weightlistFlatTriggerSF            .append(PUweight)
    weightlistTriggerEffSFNormUp       .append(PUweight)
    weightlistTriggerEffSFNormDown     .append(PUweight)
    weightlistTriggerEffSFShapeUpEta   .append(PUweight)
    weightlistTriggerEffSFShapeDownEta .append(PUweight)
    weightlistTriggerEffSFShapeUpPt    .append(PUweight)
    weightlistTriggerEffSFShapeDownPt  .append(PUweight)
    weightlistTriggerEffSFShapeUpPt40  .append(PUweight)
    weightlistTriggerEffSFShapeDownPt40.append(PUweight)
    weightlistSelectionEffSFNormUp     .append(PUweight)
    weightlistSelectionEffSFNormDown   .append(PUweight)
    weightlistFinalSSV                 .append(PUweight)
    weightlistBtagSFup                 .append(PUweight)
    weightlistBtagSFdown               .append(PUweight)
    weightlistMisTagSFup               .append(PUweight)
    weightlistMisTagSFdown             .append(PUweight)
    weightlistBTagSFShapeUpPt65        .append(PUweight) 
    weightlistBTagSFShapeDownPt65      .append(PUweight) 
    weightlistBTagSFShapeUpEta1p2      .append(PUweight) 
    weightlistBTagSFShapeDownEta1p2    .append(PUweight) 
    weightlistBTagSFHalfShapeUpPt65    .append(PUweight) 
    weightlistBTagSFHalfShapeDownPt65  .append(PUweight) 
    weightlistBTagSFHalfShapeUpEta0p7  .append(PUweight) 
    weightlistBTagSFHalfShapeDownEta0p7.append(PUweight) 
    weightlistBTagSFShapeUpPt100       .append(PUweight) 
    weightlistBTagSFShapeDownPt100     .append(PUweight) 
    weightlistBTagSFShapeUpEta0p7      .append(PUweight) 
    weightlistBTagSFShapeDownEta0p7    .append(PUweight) 

if(effSFReweigthing and decayChannel=="muon"):
    weightlistFinal                    .append("effSFMuonEventWeight")
    weightlistNoBtagSFWeight           .append("effSFMuonEventWeight")
    weightlistNoPUWeight               .append("effSFMuonEventWeight")
    weightlistPUup                     .append("effSFMuonEventWeightPUup")
    weightlistPUdown                   .append("effSFMuonEventWeightPUdown")
    weightlistFlatTriggerSF            .append("effSFMuonEventWeightFlatTriggerSF")
    weightlistTriggerEffSFNormUp       .append("effSFMuonEventWeightEffSFNormUpStat")
    weightlistTriggerEffSFNormDown     .append("effSFMuonEventWeightEffSFNormDownStat")
    weightlistTriggerEffSFShapeUpEta   .append("effSFMuonEventWeightEffSFShapeUpEta")
    weightlistTriggerEffSFShapeDownEta .append("effSFMuonEventWeightEffSFShapeDownEta")
    weightlistTriggerEffSFShapeUpPt    .append("effSFMuonEventWeightEffSFShapeUpPt")
    weightlistTriggerEffSFShapeDownPt  .append("effSFMuonEventWeightEffSFShapeDownPt")
    weightlistTriggerEffSFShapeUpPt40  .append("effSFMuonEventWeightEffSFShapeUpPt40")
    weightlistTriggerEffSFShapeDownPt40.append("effSFMuonEventWeightEffSFShapeDownPt40")
    weightlistSelectionEffSFNormUp     .append("effSFMuonEventWeighEffSFNormUpSys")
    weightlistSelectionEffSFNormDown   .append("effSFMuonEventWeightEffSFNormDownSys")
    weightlistFinalSSV                 .append("effSFMuonEventWeight")
    weightlistBtagSFup                 .append("effSFMuonEventWeight")
    weightlistBtagSFdown               .append("effSFMuonEventWeight")
    weightlistMisTagSFup               .append("effSFMuonEventWeight")
    weightlistMisTagSFdown             .append("effSFMuonEventWeight")
    weightlistBTagSFShapeUpPt65        .append("effSFMuonEventWeight")
    weightlistBTagSFShapeDownPt65      .append("effSFMuonEventWeight")
    weightlistBTagSFShapeUpEta1p2      .append("effSFMuonEventWeight")
    weightlistBTagSFShapeDownEta1p2    .append("effSFMuonEventWeight")
    weightlistBTagSFHalfShapeUpPt65    .append("effSFMuonEventWeight")
    weightlistBTagSFHalfShapeDownPt65  .append("effSFMuonEventWeight")
    weightlistBTagSFHalfShapeUpEta0p7  .append("effSFMuonEventWeight")
    weightlistBTagSFHalfShapeDownEta0p7.append("effSFMuonEventWeight")
    weightlistBTagSFShapeUpPt100       .append("effSFMuonEventWeight")
    weightlistBTagSFShapeDownPt100     .append("effSFMuonEventWeight")
    weightlistBTagSFShapeUpEta0p7      .append("effSFMuonEventWeight")
    weightlistBTagSFShapeDownEta0p7    .append("effSFMuonEventWeight")
if(effSFReweigthing and decayChannel=="electron"):
    weightlistFinal                    .append("effSFElectronEventWeight")
    weightlistNoBtagSFWeight           .append("effSFElectronEventWeight")
    weightlistNoPUWeight               .append("effSFElectronEventWeight")
    weightlistPUup                     .append("effSFElectronEventWeightPUup")
    weightlistPUdown                   .append("effSFElectronEventWeightPUdown")
    weightlistFlatTriggerSF            .append("effSFElectronEventWeightFlatTriggerSF")
    weightlistTriggerEffSFNormUp       .append("effSFElectronEventWeightEffSFNormUpStat")
    weightlistTriggerEffSFNormDown     .append("effSFElectronEventWeightEffSFNormDownStat")
    weightlistTriggerEffSFShapeUpEta   .append("effSFElectronEventWeightEffSFShapeUpEta")
    weightlistTriggerEffSFShapeDownEta .append("effSFElectronEventWeightEffSFShapeDownEta")
    weightlistTriggerEffSFShapeUpPt    .append("effSFElectronEventWeightEffSFShapeUpPt")
    weightlistTriggerEffSFShapeDownPt  .append("effSFElectronEventWeightEffSFShapeDownPt")
    weightlistTriggerEffSFShapeUpPt40  .append("effSFElectronEventWeightEffSFShapeUpPt40")
    weightlistTriggerEffSFShapeDownPt40.append("effSFElectronEventWeightEffSFShapeDownPt40")
    weightlistSelectionEffSFNormUp     .append("effSFElectronEventWeightEffSFNormUpSys")
    weightlistSelectionEffSFNormDown   .append("effSFElectronEventWeightEffSFNormDownSys")
    weightlistFinalSSV                 .append("effSFElectronEventWeight")
    weightlistBtagSFup                 .append("effSFElectronEventWeight")
    weightlistBtagSFdown               .append("effSFElectronEventWeight")
    weightlistMisTagSFup               .append("effSFElectronEventWeight")
    weightlistMisTagSFdown             .append("effSFElectronEventWeight")
    weightlistBTagSFShapeUpPt65        .append("effSFElectronEventWeight")
    weightlistBTagSFShapeDownPt65      .append("effSFElectronEventWeight")
    weightlistBTagSFShapeUpEta1p2      .append("effSFElectronEventWeight")
    weightlistBTagSFShapeDownEta1p2    .append("effSFElectronEventWeight")
    weightlistBTagSFHalfShapeUpPt65    .append("effSFElectronEventWeight")
    weightlistBTagSFHalfShapeDownPt65  .append("effSFElectronEventWeight")
    weightlistBTagSFHalfShapeUpEta0p7  .append("effSFElectronEventWeight")
    weightlistBTagSFHalfShapeDownEta0p7.append("effSFElectronEventWeight")
    weightlistBTagSFShapeUpPt100       .append("effSFElectronEventWeight")
    weightlistBTagSFShapeDownPt100     .append("effSFElectronEventWeight")
    weightlistBTagSFShapeUpEta0p7      .append("effSFElectronEventWeight")
    weightlistBTagSFShapeDownEta0p7    .append("effSFElectronEventWeight")
if(BtagReweigthing):
    weightlistFinal                    .append("bTagSFEventWeight")
    weightlistNoPUWeight               .append("bTagSFEventWeight")
    weightlistPUup                     .append("bTagSFEventWeight")
    weightlistPUdown                   .append("bTagSFEventWeight")
    weightlistFlatTriggerSF            .append("bTagSFEventWeight")
    weightlistTriggerEffSFNormUp       .append("bTagSFEventWeight")
    weightlistTriggerEffSFNormDown     .append("bTagSFEventWeight")
    weightlistTriggerEffSFShapeUpEta   .append("bTagSFEventWeight")
    weightlistTriggerEffSFShapeDownEta .append("bTagSFEventWeight")
    weightlistTriggerEffSFShapeUpPt    .append("bTagSFEventWeight")
    weightlistTriggerEffSFShapeDownPt  .append("bTagSFEventWeight")
    weightlistTriggerEffSFShapeUpPt40  .append("bTagSFEventWeight")
    weightlistTriggerEffSFShapeDownPt40.append("bTagSFEventWeight")
    weightlistSelectionEffSFNormUp     .append("bTagSFEventWeight")
    weightlistSelectionEffSFNormDown   .append("bTagSFEventWeight")
    weightlistFinalSSV                 .append("bTagSFEventWeightSSV")
    weightlistBtagSFup                 .append("bTagSFEventWeightBTagSFUp")
    weightlistBtagSFdown               .append("bTagSFEventWeightBTagSFDown")
    weightlistMisTagSFup               .append("bTagSFEventWeightMisTagSFUp")
    weightlistMisTagSFdown             .append("bTagSFEventWeightMisTagSFDown")
    weightlistBTagSFShapeUpPt65        .append("bTagSFEventWeightBTagSFShapeUpPt65")
    weightlistBTagSFShapeDownPt65      .append("bTagSFEventWeightBTagSFShapeDownPt65")
    weightlistBTagSFShapeUpEta1p2      .append("bTagSFEventWeightBTagSFShapeUpEta1p2")
    weightlistBTagSFShapeDownEta1p2    .append("bTagSFEventWeightBTagSFShapeDownEta1p2")
    weightlistBTagSFHalfShapeUpPt65    .append("bTagSFEventWeightBTagSFHalfShapeUpPt65")
    weightlistBTagSFHalfShapeDownPt65  .append("bTagSFEventWeightBTagSFHalfShapeDownPt65")
    weightlistBTagSFHalfShapeUpEta0p7  .append("bTagSFEventWeightBTagSFHalfShapeUpEta0p7")
    weightlistBTagSFHalfShapeDownEta0p7.append("bTagSFEventWeightBTagSFHalfShapeDownEta0p7")
    weightlistBTagSFShapeUpPt100       .append("bTagSFEventWeightBTagSFShapeUpPt100")
    weightlistBTagSFShapeDownPt100     .append("bTagSFEventWeightBTagSFShapeDownPt100")
    weightlistBTagSFShapeUpEta0p7      .append("bTagSFEventWeightBTagSFShapeUpEta0p7")
    weightlistBTagSFShapeDownEta0p7    .append("bTagSFEventWeightBTagSFShapeDownEta0p7")

## multiply all event weights
## a) default
process.eventWeightNoBtagSFWeight           = process.eventWeightMultiplier.clone(eventWeightTags = weightlistNoBtagSFWeight)
process.eventWeightNoPUWeight               = process.eventWeightMultiplier.clone(eventWeightTags = weightlistNoPUWeight)
process.eventWeightFinal                    = process.eventWeightMultiplier.clone(eventWeightTags = weightlistFinal)

process.eventWeightFinalSSV                 = process.eventWeightMultiplier.clone(eventWeightTags = weightlistFinalSSV)

## b) for systematics
process.eventWeightPUup                     = process.eventWeightMultiplier.clone(eventWeightTags = weightlistPUup)
process.eventWeightPUdown                   = process.eventWeightMultiplier.clone(eventWeightTags = weightlistPUdown)
process.eventWeightFlatTriggerSF            = process.eventWeightMultiplier.clone(eventWeightTags = weightlistFlatTriggerSF)
process.eventWeightTriggerEffSFNormUp       = process.eventWeightMultiplier.clone(eventWeightTags = weightlistTriggerEffSFNormUp)
process.eventWeightTriggerEffSFNormDown     = process.eventWeightMultiplier.clone(eventWeightTags = weightlistTriggerEffSFNormDown)
process.eventWeightTriggerEffSFShapeUpEta   = process.eventWeightMultiplier.clone(eventWeightTags = weightlistTriggerEffSFShapeUpEta)
process.eventWeightTriggerEffSFShapeDownEta = process.eventWeightMultiplier.clone(eventWeightTags = weightlistTriggerEffSFShapeDownEta)
process.eventWeightTriggerEffSFShapeUpPt    = process.eventWeightMultiplier.clone(eventWeightTags = weightlistTriggerEffSFShapeUpPt)
process.eventWeightTriggerEffSFShapeDownPt  = process.eventWeightMultiplier.clone(eventWeightTags = weightlistTriggerEffSFShapeDownPt)
process.eventWeightTriggerEffSFShapeUpPt40  = process.eventWeightMultiplier.clone(eventWeightTags = weightlistTriggerEffSFShapeUpPt40)
process.eventWeightTriggerEffSFShapeDownPt40= process.eventWeightMultiplier.clone(eventWeightTags = weightlistTriggerEffSFShapeDownPt40)
process.eventWeightSelectionEffSFNormUp     = process.eventWeightMultiplier.clone(eventWeightTags = weightlistSelectionEffSFNormUp)
process.eventWeightSelectionEffSFNormDown   = process.eventWeightMultiplier.clone(eventWeightTags = weightlistSelectionEffSFNormDown)
process.eventWeightBtagSFup                 = process.eventWeightMultiplier.clone(eventWeightTags = weightlistBtagSFup)
process.eventWeightBtagSFdown               = process.eventWeightMultiplier.clone(eventWeightTags = weightlistBtagSFdown)
process.eventWeightMisTagSFup               = process.eventWeightMultiplier.clone(eventWeightTags = weightlistMisTagSFup)
process.eventWeightMisTagSFdown             = process.eventWeightMultiplier.clone(eventWeightTags = weightlistMisTagSFdown)
process.eventWeightBTagSFShapeUpPt65        = process.eventWeightMultiplier.clone(eventWeightTags = weightlistBTagSFShapeUpPt65)
process.eventWeightBTagSFShapeDownPt65      = process.eventWeightMultiplier.clone(eventWeightTags = weightlistBTagSFShapeDownPt65)
process.eventWeightBTagSFShapeUpEta1p2      = process.eventWeightMultiplier.clone(eventWeightTags = weightlistBTagSFShapeUpEta1p2)
process.eventWeightBTagSFShapeDownEta1p2    = process.eventWeightMultiplier.clone(eventWeightTags = weightlistBTagSFShapeDownEta1p2)
process.eventWeightBTagSFHalfShapeUpPt65    = process.eventWeightMultiplier.clone(eventWeightTags = weightlistBTagSFHalfShapeUpPt65)
process.eventWeightBTagSFHalfShapeDownPt65  = process.eventWeightMultiplier.clone(eventWeightTags = weightlistBTagSFHalfShapeDownPt65)
process.eventWeightBTagSFHalfShapeUpEta0p7  = process.eventWeightMultiplier.clone(eventWeightTags = weightlistBTagSFHalfShapeUpEta0p7)
process.eventWeightBTagSFHalfShapeDownEta0p7= process.eventWeightMultiplier.clone(eventWeightTags = weightlistBTagSFHalfShapeDownEta0p7)
process.eventWeightBTagSFShapeUpPt100       = process.eventWeightMultiplier.clone(eventWeightTags = weightlistBTagSFShapeUpPt100)
process.eventWeightBTagSFShapeDownPt100     = process.eventWeightMultiplier.clone(eventWeightTags = weightlistBTagSFShapeDownPt100)
process.eventWeightBTagSFShapeUpEta0p7      = process.eventWeightMultiplier.clone(eventWeightTags = weightlistBTagSFShapeUpEta0p7)
process.eventWeightBTagSFShapeDownEta0p7    = process.eventWeightMultiplier.clone(eventWeightTags = weightlistBTagSFShapeDownEta0p7)
    
# use weight in single and double object analyzer modules for central values
modulelist   = process.analyzers_().keys()
genModules1  = process.kinFitGen.moduleNames()
genModules2  = process.kinFitGenPhaseSpace.moduleNames()
PUModuleList = set(['PUControlDistributionsDefault','PUControlDistributionsBeforeBtagging','PUControlDistributionsAfterBtagging'])

# a) Default configuration for event weights for all modules (gen + reco)
#    No re-weighting at all is to be applied
if(runningOnData=="MC" and not PUreweigthing and not effSFReweigthing and not BtagReweigthing):
    for module in modulelist:
        if module not in PUModuleList:
            getattr(process,module).weight=cms.InputTag("")     
# b) Re-weighting (PU and/or effSF) for reco-modules
if(runningOnData=="MC" and (PUreweigthing or effSFReweigthing)):
    if(PUreweigthing):
        print " All reco-modules will use PU event weights"
    if(effSFReweigthing):
        print " All reco-modules will use eff SF event weights"
    for module in modulelist:
        # exclude PU control modules and gen-modules
        if(module not in PUModuleList and module not in genModules1 and module not in genModules2):
            # 'eventWeightNoBtagSFWeight' treats the correct combination of 'PUreweigthing' and 'effSFReweigthing'
            getattr(process,module).weight=cms.InputTag("eventWeightNoBtagSFWeight")
        
# c) Re-weighting (b-tag SF) only for reco-modules after btagging
if(runningOnData=="MC" and BtagReweigthing):
    btagModules1 = process.monitorKinematicsAfterBtagging.moduleNames()
    btagModules2 = process.kinFit.moduleNames()
    btagModules3 = process.monitorElectronKinematicsAfterBtagging.moduleNames()
    print
    print " The following reco-modules will use additionally the b-tag event weights:"
    print btagModules1
    print btagModules2
    print btagModules3
    # 'eventWeightFinal' combines the correct combination of 'PUreweigthing' and 'effSFReweigthing' with the b-tag SF
    for module1 in btagModules1:
        getattr(process,module1).weight=cms.InputTag("eventWeightFinal")
    for module2 in btagModules2:
        if(not module2=='makeGenLevelBJets'):
            getattr(process,module2).weight=cms.InputTag("eventWeightFinal")
    for module3 in btagModules3:
        getattr(process,module3).weight=cms.InputTag("eventWeightFinal")
    print
        
# d) Re-weighting of gen-modules - PU reweighting only
if(runningOnData=="MC" and PUreweigthing):
    print
    print " The following gen-modules will only use the PU reweighting:"
    #print genModules1
    #print genModules2
    for module1 in genModules1:
        if(not module1=='makeGenLevelBJets'):
            print module1
            getattr(process,module1).weight=PUweight
    for module2 in genModules2:
        if(not module2=='makeGenLevelBJets'):
            print module2
            getattr(process,module2).weight=PUweight
    genModules3 = process.kinFitGenPhaseSpaceHad.moduleNames()
    #print genModules3
    for module3 in genModules3:
        if(not module3=='makeGenLevelBJets'):
            print module3
            getattr(process,module3).weight=PUweight
    genModules4 = process.hadLvObjectMonitoring.moduleNames()
    #print genModules4
    for module4 in genModules4:
        if(not module4=='makeGenLevelBJets'):
            print module4
            getattr(process,module4).weight=PUweight
    if(additionalEventWeights and eventFilter=='signal only'):
        print "those gen modules are also cloned in order to also use NoPU, PUup and PUdown event weights "

        GENFULLanalyzers     =cms.Sequence(process.dummy)
        GENpartonPSanalyzers =cms.Sequence(process.dummy)
        GENhadronPSanalyzers =cms.Sequence(process.dummy)
        GENFULLbanalyzers    =cms.Sequence(process.dummy)
        GENpartonPSbanalyzers=cms.Sequence(process.dummy)
        GENhadronPSbanalyzers=cms.Sequence(process.dummy)
        genSystExt=["NoPUWeight", "PUup", "PUdown"]
        for sys in genSystExt:
            # get correct weight
            weightTagName=cms.InputTag("")
            if(not sys.find("PUup") == -1):
                weightTagName=PUweightUp
            elif(not sys.find("PUdown") == -1):
                weightTagName=PUweightDown
            # create plots for full PS
            setattr(process,"analyzeTopPartonLevelKinematics"+sys, process.analyzeTopPartonLevelKinematics.clone(weight=weightTagName))
            getattr(process,"analyzeTopPartonLevelKinematics"+sys).analyze.useTree = False
            setattr(process,"analyzeTopPartonLevelKinematicsBjets"+sys, process.analyzeTopPartonLevelKinematicsBjets.clone(weight=weightTagName))
            getattr(process,"analyzeTopPartonLevelKinematicsBjets"+sys).useTree = False
            # create plots for parton level PS
            setattr(process,"analyzeTopPartonLevelKinematicsPhaseSpace"+sys, process.analyzeTopPartonLevelKinematicsPhaseSpace.clone(weight=weightTagName))
            getattr(process,"analyzeTopPartonLevelKinematicsPhaseSpace"+sys).analyze.useTree = False
            setattr(process,"analyzeTopPartonLevelKinematicsBjetsPhaseSpace"+sys, process.analyzeTopPartonLevelKinematicsBjetsPhaseSpace.clone(weight=weightTagName))
            getattr(process,"analyzeTopPartonLevelKinematicsBjetsPhaseSpace"+sys).useTree = False
            # create plots for hadron level PS
            setattr(process,"analyzeTopHadronLevelKinematicsPhaseSpace"+sys, process.analyzeTopHadronLevelKinematicsPhaseSpace.clone(weight=weightTagName))
            getattr(process,"analyzeTopHadronLevelKinematicsPhaseSpace"+sys).analyze.useTree = False
            setattr(process,"analyzeTopHadronLevelKinematicsBjetsPhaseSpace"+sys, process.analyzeTopHadronLevelKinematicsBjetsPhaseSpace.clone(weight=weightTagName))
            getattr(process,"analyzeTopHadronLevelKinematicsBjetsPhaseSpace"+sys).useTree = False
            # analyzer to be added to sequence
            GENFULLanalyzers    *=getattr(process,"analyzeTopPartonLevelKinematics"+sys)
            GENpartonPSanalyzers*=getattr(process,"analyzeTopPartonLevelKinematicsPhaseSpace"+sys)
            GENhadronPSanalyzers*=getattr(process,"analyzeTopHadronLevelKinematicsPhaseSpace"+sys)
            GENFULLbanalyzers    *=getattr(process,"analyzeTopPartonLevelKinematicsBjets"+sys)
            GENpartonPSbanalyzers*=getattr(process,"analyzeTopPartonLevelKinematicsBjetsPhaseSpace"+sys)
            GENhadronPSbanalyzers*=getattr(process,"analyzeTopHadronLevelKinematicsBjetsPhaseSpace"+sys)

        GENFULLanalyzers.remove(process.dummy)
        GENpartonPSanalyzers.remove(process.dummy)
        GENhadronPSanalyzers.remove(process.dummy)
        GENFULLbanalyzers.remove(process.dummy)
        GENpartonPSbanalyzers.remove(process.dummy)
        GENhadronPSbanalyzers.remove(process.dummy)
        
        # add them to sequence
        process.kinFitGen              *= (GENFULLanalyzers *
                                           GENFULLbanalyzers)
        
        process.kinFitGenPhaseSpace    *= (GENpartonPSanalyzers *
                                           GENpartonPSbanalyzers)
        
        process.kinFitGenPhaseSpaceHad *= (GENhadronPSanalyzers *
                                           GENhadronPSbanalyzers)
        
elif(runningOnData=="MC" and not PUreweigthing):
    for module1 in genModules1:
        if(not module1=='makeGenLevelBJets'):
            getattr(process,module1).weight=cms.InputTag("")
    for module2 in genModules2:
        if(not module2=='makeGenLevelBJets'):
            getattr(process,module2).weight=cms.InputTag("")
    for module3 in genModules3:
        if(not module3=='makeGenLevelBJets'):
            getattr(process,module3).weight=cms.InputTag("")
    for module4 in genModules4:
        if(not module4=='makeGenLevelBJets'):
            getattr(process,module4).weight=cms.InputTag("")

# e) PU Modules - special configuration because of different possible PU weights that are handled in the modules themselves
if(runningOnData=="MC"):
    if(effSFReweigthing and decayChannel=="muon"):
        process.PUControlDistributionsDefault.DefEventWeight        = cms.InputTag("effSFMuonEventWeight")
        process.PUControlDistributionsBeforeBtagging.DefEventWeight = cms.InputTag("effSFMuonEventWeight")
    elif(effSFReweigthing and decayChannel=="electron"):     
        process.PUControlDistributionsDefault.DefEventWeight        = cms.InputTag("effSFElectronEventWeight")
        process.PUControlDistributionsBeforeBtagging.DefEventWeight = cms.InputTag("effSFElectronEventWeight")
    else:
        process.PUControlDistributionsDefault.DefEventWeight        = cms.InputTag("")
        process.PUControlDistributionsBeforeBtagging.DefEventWeight = cms.InputTag("")
    # 'eventWeightNoPUWeight' combines the correct combination of 'effSFReweigthing' and 'BtagReweigthing'
    process.PUControlDistributionsAfterBtagging.DefEventWeight  = cms.InputTag("eventWeightNoPUWeight")    
    ## copies of TopRecoKinematicsKinFit analyzers with varied weights for monitoring and systematic unc.
if(runningOnData=="MC" and applyKinFit==True and additionalEventWeights):

    ## list of systematic variations via event weights
    weights=cms.Sequence(process.dummy)
    analyzers=cms.Sequence(process.dummy)
    banalyzers=cms.Sequence(process.dummy)
    systExt=["NoWeight", "OnlyPUWeight", "NoBtagSFWeight",
             "PUup", "PUdown",
             "FlatTriggerSF", "TriggerEffSFNormUp", "TriggerEffSFNormDown", "TriggerEffSFShapeUpEta", "TriggerEffSFShapeDownEta",
             "TriggerEffSFShapeUpPt", "TriggerEffSFShapeDownPt", "TriggerEffSFShapeUpPt40", "TriggerEffSFShapeDownPt40",
             "SelectionEffSFNormUp", "SelectionEffSFNormDown",
             "BtagSFup", "BtagSFdown", "MisTagSFup", "MisTagSFdown", "BTagSFShapeUpPt65", "BTagSFShapeDownPt65", "BTagSFShapeUpEta1p2", "BTagSFShapeDownEta1p2",
             #"BTagSFHalfShapeUpPt65", "BTagSFHalfShapeDownPt65", "BTagSFHalfShapeUpEta0p7", "BTagSFHalfShapeDownEta0p7",
             "BTagSFShapeUpPt100", "BTagSFShapeDownPt100", "BTagSFShapeUpEta0p7", "BTagSFShapeDownEta0p7"]
    # loop them
    for sys in systExt:
        # take care of correct name and non existing weights
        weightTagName=cms.InputTag("eventWeight"+sys)
        if(not sys.find("OnlyPUWeight") == -1):
            weightTagName=PUweight
        noweight=False
        if(not PUreweigthing and not sys.find("PU") == -1):
            noweight=True
        if(not PUreweigthing and not effSFReweigthing and not sys.find("NoBtagSFWeight") == -1):
            noweight=True
        if(not sys.find("NoWeight") == -1):
            noweight=True
        if(noweight):
            weightTagName=cms.InputTag("")
        # create plots for standard analyzer
        setattr(process,"analyzeTopRecoKinematicsKinFit"+sys, process.analyzeTopRecoKinematicsKinFit.clone(weight=weightTagName))
        getattr(process,"analyzeTopRecoKinematicsKinFit"+sys).analyze.useTree = False
        # create plots for top/antitop analyzer
        setattr(process,"analyzeTopRecoKinematicsKinFitTopAntitop"+sys, process.analyzeTopRecoKinematicsKinFitTopAntitop.clone(weight=weightTagName))
        getattr(process,"analyzeTopRecoKinematicsKinFitTopAntitop"+sys).analyze.useTree = False
        # create plots for standard analyzer
        setattr(process,"analyzeTopRecoKinematicsBjets"+sys, process.analyzeTopRecoKinematicsBjets.clone(weight=weightTagName, useTree = False))
        # weights to be added to sequence
        if(sys.find("NoWeight") == -1 and sys.find("OnlyPUWeight") == -1 and sys.find("NoBtagSFWeight") == -1):                  
            weights*=getattr(process,"eventWeight"+sys)
        # analyzer to be added to sequence
        analyzers*=getattr(process,"analyzeTopRecoKinematicsKinFit"+sys)
        #analyzer*=getattr(process,"analyzeTopRecoKinematicsKinFitTopAntitop"+sys)
        if(sys.find("NoWeight") == -1 and sys.find("OnlyPUWeight") == -1 and sys.find("NoBtagSFWeight") == -1):
            banalyzers*=getattr(process,"analyzeTopRecoKinematicsBjets"+sys)
    weights   .remove(process.dummy)
    analyzers .remove(process.dummy)
    banalyzers.remove(process.dummy)
        
    ## add to Sequence
    # a) event weights 
    process.kinFit.replace(process.analyzeTopRecoKinematicsKinFit, 
                           process.analyzeTopRecoKinematicsKinFit*                            
                           process.bTagSFEventWeightBTagSFUp    *
                           process.bTagSFEventWeightBTagSFDown  *
                           process.bTagSFEventWeightMisTagSFUp  *
                           process.bTagSFEventWeightMisTagSFDown*
                           process.bTagSFEventWeightBTagSFShapeUpPt65    *
                           process.bTagSFEventWeightBTagSFShapeDownPt65  *
                           process.bTagSFEventWeightBTagSFShapeUpEta1p2    *
                           process.bTagSFEventWeightBTagSFShapeDownEta1p2  *
                           #process.bTagSFEventWeightBTagSFHalfShapeUpPt65    *
                           #process.bTagSFEventWeightBTagSFHalfShapeDownPt65  *
                           #process.bTagSFEventWeightBTagSFHalfShapeUpEta0p7    *
                           #process.bTagSFEventWeightBTagSFHalfShapeDownEta0p7  *
                           process.bTagSFEventWeightBTagSFShapeUpPt100    *
                           process.bTagSFEventWeightBTagSFShapeDownPt100  *
                           process.bTagSFEventWeightBTagSFShapeUpEta0p7    *
                           process.bTagSFEventWeightBTagSFShapeDownEta0p7
                           )
    if(decayChannel=="muon"):
	process.kinFit.replace(process.analyzeTopRecoKinematicsKinFit, 
                               process.analyzeTopRecoKinematicsKinFit*
			       process.effSFMuonEventWeightPUup*
			       process.effSFMuonEventWeightPUdown*
                               process.effSFMuonEventWeightFlatTriggerSF*           
                               process.effSFMuonEventWeightEffSFNormUpStat*      
                               process.effSFMuonEventWeightEffSFNormDownStat*    
                               process.effSFMuonEventWeightEffSFShapeUpEta*  
                               process.effSFMuonEventWeightEffSFShapeDownEta*
                               process.effSFMuonEventWeightEffSFShapeUpPt*  
                               process.effSFMuonEventWeightEffSFShapeDownPt*
			       process.effSFMuonEventWeightEffSFShapeUpPt40*  
                               process.effSFMuonEventWeightEffSFShapeDownPt40*
                               process.effSFMuonEventWeighEffSFNormUpSys    *
                               process.effSFMuonEventWeightEffSFNormDownSys
                               )
    elif(decayChannel=="electron"):
        process.kinFit.replace(process.analyzeTopRecoKinematicsKinFit, 
                               process.analyzeTopRecoKinematicsKinFit*
                               process.effSFElectronEventWeightFlatTriggerSF*           
                               process.effSFElectronEventWeightEffSFNormUpStat*      
                               process.effSFElectronEventWeightEffSFNormDownStat*    
                               process.effSFElectronEventWeightEffSFShapeUpEta*  
                               process.effSFElectronEventWeightEffSFShapeDownEta*
                               process.effSFElectronEventWeightEffSFShapeUpPt*  
                               process.effSFElectronEventWeightEffSFShapeDownPt*
			       process.effSFElectronEventWeightEffSFShapeUpPt40*  
                               process.effSFElectronEventWeightEffSFShapeDownPt40*
                               process.effSFElectronEventWeightEffSFNormUpSys    *
                               process.effSFElectronEventWeightEffSFNormDownSys
                               )
    process.kinFit.replace(process.bTagSFEventWeightBTagSFShapeDownEta0p7,
                           process.bTagSFEventWeightBTagSFShapeDownEta0p7      *
                           ## additional weights
                           weights *
                           ## additional std top analyzers
                           analyzers                         
                           )
    process.kinFit.replace(process.analyzeTopRecoKinematicsBjets,
                           process.analyzeTopRecoKinematicsBjets *
                           ## additional b-hadron jet analyzers
                           banalyzers                     
                           )
    
## SSV event weights
if(runningOnData=="MC" and BtagReweigthing):
    SSVModules = process.SSVMonitoring.moduleNames()
    print
    print " The following reco-modules will use the SSV b-tag event weights:"
    print SSVModules
    # 'eventWeightFinal' combines the correct combination of 'PUreweigthing' and 'effSFReweigthing' with the SSV b-tag SF
    for module in SSVModules:
        getattr(process,module).weight=cms.InputTag("eventWeightFinalSSV")
        
## ---
##    run the final sequences
## ---
## standard sequence for cross section analyis and detailed cut monitoring
process.p1 = cms.Path(## gen event selection (decay channel) and the trigger selection (hltFilter)
                      process.filterSequence                        *
                      ## PV event selection
                      process.PVSelection                           *
                      ## introduce some collections
                      process.semiLeptonicSelection                 *
                      ## create PU event weights
                      process.makeEventWeightsPU                    *
                      ## create shape distortion event weights
                      process.eventWeightDileptonModelVariation     *
                      process.eventWeightPUDistort                  *
                      process.eventWeightPUupDistort                *
                      process.eventWeightPUdownDistort              *
		      ## create effSF eventWeight
		      process.effSFMuonEventWeight                  *
		      ## multiply event weights
		      process.eventWeightNoBtagSFWeight             *
                      ## muon selection
                      process.muonCuts                              *
                      ## veto on additional leptons
                      process.secondMuonVeto                        *
                      process.electronVeto                          *
                      ## jet selection and monitoring
                      process.jetSelection                          *
                      ## monitoring before b-tagging
                      process.monitorKinematicsBeforeBtagging       *
                      process.PUControlDistributionsBeforeBtagging  *                      
                      ## b-tagging
                      process.btagSelection                         *
                      ## create PU event weights
                      process.bTagSFEventWeight                     *
                      ## create combined weights
                      process.eventWeightNoPUWeight                 *
                      ## create combined weight
                      process.eventWeightFinal                      *
                      ## monitor after b-tagging
                      process.monitorKinematicsAfterBtagging        *
                      process.PUControlDistributionsAfterBtagging   *
                      ## apply kinematic fit
                      process.kinFit
                      )
if(applyKinFit==False or eventFilter!="signal only"):
    process.p1.remove(process.dummy)
if(runningOnData=="data"):
    process.p1.remove(process.isolatedGenMuons)
    process.p1.remove(process.semiLeptGenCollections)

## analysis with SSV btagger
process.p2 = cms.Path(## gen event selection (decay channel) and the trigger selection (hltFilter)
                      process.filterSequence                        *
                      ## PV event selection
                      process.PVSelection                           *
                      ## introduce some collections
                      process.semiLeptonicSelection                 *
                      ## create PU event weights
                      process.makeEventWeightsPU                    *
                      ## create shape distortion event weights
                      process.eventWeightDileptonModelVariation     *
                      process.eventWeightPUDistort                  *
                      process.eventWeightPUupDistort                *
                      process.eventWeightPUdownDistort              *
		      ## create effSF eventWeight
		      process.effSFMuonEventWeight                  *
		      ## multiply event weights
		      process.eventWeightNoBtagSFWeight             *
                      ## monitoring of PU reweighting and PV
                      process.PUControlDistributionsDefault         *
                      ## std sel wo b-tagging
                      process.muonCuts                              *
                      process.secondMuonVeto                        *
                      process.electronVeto                          *
                      process.leadingJetSelectionNjets4             *
                      ## SSV btag-selection
                      process.btagSelectionSSV                      *
                      ## create PU event weights
                      process.bTagSFEventWeightSSV                  *
                      ## create combined weight
                      process.eventWeightFinalSSV                   *
                      ## monitoring after SSV
                      process.SSVMonitoring                         
                      )

## std analysis with generator objects as input for efficiency determination
## no phase space cuts and phase space cuts for hadron level
if(runningOnData=="MC"):
    print "running on Monte Carlo, gen-plots produced"
    process.p3 = cms.Path(## gen event selection: semileptonic (lepton &
                          ## tau->lepton if tau==True), lepton=muon/electron
                          process.genFilterSequence                     *
                          ## introduce some collections
                          process.isolatedGenLeptons                    *
                          process.semiLeptGenCollections                *
                          ## create PU event weights
                          process.makeEventWeightsPU                    *
                          ## create shape distortion event weights
                          process.eventWeightDileptonModelVariation     *
                          process.eventWeightPUDistort                  *
                          process.eventWeightPUupDistort                *
                          process.eventWeightPUdownDistort              *
                          ## investigate top reconstruction full PS
                          process.kinFitGen                             *
                          ## monitoring of hadron level kinematics
                          process.hadLvObjectMonitoring                 *
                          ## hadron level muon selection
                          process.genMuonSelection                      *
                          ## hadron level gen jet selection
                          process.genJetCuts                            *
                          ## investigate top reconstruction hadron level PS
                          process.kinFitGenPhaseSpaceHad                *
                          ## new phase space cuts on the basis of genTtbarEvent
                          process.filterGenPhaseSpace   
                          )
    ## delete gen filter
    if(removeGenTtbar==True):    
        process.p3.remove(process.genFilterSequence)        
        process.p3.remove(process.filterGenPhaseSpace)
    if(eventFilter=='background only'):
        process.p3.remove(process.filterGenPhaseSpace)
    ## delete dummy sequence
    if(applyKinFit==False or eventFilter!="signal only"):
        process.p3.remove(process.dummy)
else:
    process.p3 = cms.Path(process.dummy)
    
## std analysis with generator objects as input for efficiency determination
## phase space cuts for parton level
if(runningOnData=="MC"):
    process.s4 = cms.Sequence(## introduce some collections
                              process.isolatedGenLeptons                    *
                              process.semiLeptGenCollections                *
                              ## create PU event weights
                              process.makeEventWeightsPU                    *
                              ## create shape distortion event weights
                              process.eventWeightDileptonModelVariation     *
                              process.eventWeightPUDistort                  *
                              process.eventWeightPUupDistort                *
                              process.eventWeightPUdownDistort              *
			      ## new phase space cuts on the basis of genTtbarEvent
			      process.filterGenPhaseSpace                   *
                              ## investigate top reconstruction parton level PS
                              process.kinFitGenPhaseSpace                   *
                              ## hadron level muon selection
                              process.genMuonSelection                      *
                              ## hadron level gen jet selection
                              process.genJetCuts                            
                              )
    process.p4 = cms.Path(## gen event selection: semileptonic (muon & tau->lepton)
                          ## tau->Mu if eventFilter=='background only' and
                          ## process.ttSemiLeptonicFilter.invert = True
                          process.genFilterSequence                      *
                          ## sequence with gen selection and histograms
                          process.s4
                          )
    ## delete gen filter
    if(removeGenTtbar==True):    
        process.p4.remove(process.genFilterSequence)
	process.p4.remove(process.filterGenPhaseSpace)
    if(eventFilter=='background only'):
        process.p4.remove(process.filterGenPhaseSpace)
    ## delete dummy sequence
    if(applyKinFit==False or eventFilter!="signal only"):
        process.p4.remove(process.dummy)
elif(runningOnData=="data"):
    process.p4 = cms.Path(process.dummy)
    print "running on data, no gen-plots"
else:
    print "choose runningOnData= data or MC, creating no gen-plots"

from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag

## switch to PF objects
if(jetType=="particleFlow"):
    pathlist = [process.p1, process.p2, process.p3, process.p4]
    for path in pathlist:  
        massSearchReplaceAnyInputTag(path, 'tightLeadingJets', 'tightLeadingPFJets')
        massSearchReplaceAnyInputTag(path, 'tightBottomJets' , 'tightBottomPFJets' )
        massSearchReplaceAnyInputTag(path, 'goodJets'        , 'goodJetsPF30'      )
        massSearchReplaceAnyInputTag(path, 'centralJets'     , 'centralJetsPF30'   )
        massSearchReplaceAnyInputTag(path, 'reliableJets'    , 'reliableJetsPF30'  )
        massSearchReplaceAnyInputTag(path, 'noEtaJets'       , 'noEtaJetsPF30'     )
        massSearchReplaceAnyInputTag(path, 'noPtJets'        , 'noPtJetsPF'        )
        massSearchReplaceAnyInputTag(path, 'patMETs'         , 'patMETsPF'         )
        path.remove(process.centralJets)
        path.remove(process.reliableJets)
        path.remove(process.goodJets)
        path.remove(process.tightLeadingJets)
        path.remove(process.tightBottomJets)

## switch to from muon to electron collections
if(decayChannel=="electron"):
    # adpat trigger
    if(options.mctag=="Summer11"):
      process.hltFilter.HLTPaths=["HLT_Ele25_CaloIdVT_TrkIdT_CentralTriJet30_v*"]
      process.dummy.HLTPaths=["HLT_Ele25_CaloIdVT_TrkIdT_CentralTriJet30_v*"]
    elif(options.mctag=="Fall11"):
      process.hltFilter.HLTPaths=["HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralJet30_v*"]
      process.dummy.HLTPaths=["HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralJet30_v*"]
    # adapt gen filter
    process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.electron = True
    process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.muon= False
    ## lepton-jet veto
    from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import *
    from PhysicsTools.PatAlgos.cleaningLayer1.jetCleaner_cfi import *
    process.noOverlapJetsPFelec = cleanPatJets.clone(
        src = cms.InputTag("selectedPatJetsAK5PF"),
        preselection = cms.string(''),
        checkOverlaps = cms.PSet(
          electrons = cms.PSet(
            src       = cms.InputTag("tightElectronsEJ"),
            algorithm = cms.string("byDeltaR"),
            preselection        = cms.string(''),
            deltaR              = cms.double(0.3),
            checkRecoComponents = cms.bool(False), # don't check if they share some AOD object ref
            pairCut             = cms.string(""),
            requireNoOverlaps   = cms.bool(True), # overlaps don't cause the jet to be discared
            )
          ),
        finalCut = cms.string(''),
        )
    process.goodJetsPF20.src  ='noOverlapJetsPFelec'
    process.centralJetsPF.src ='noOverlapJetsPFelec'
    process.reliableJetsPF.src='noOverlapJetsPFelec'
    process.noEtaJetsPF.src   ='noOverlapJetsPFelec'
    process.noPtJetsPF.src    ='noOverlapJetsPFelec'
    process.noConstJetsPF.src ='noOverlapJetsPFelec'
    process.noCEFJetsPF.src   ='noOverlapJetsPFelec'
    process.noNHFJetsPF.src   ='noOverlapJetsPFelec'
    process.noNEFJetsPF .src  ='noOverlapJetsPFelec'
    process.noCHFJetsPF.src   ='noOverlapJetsPFelec'
    process.noNCHJetsPF.src   ='noOverlapJetsPFelec'
    process.noKinJetsPF.src   ='noOverlapJetsPFelec' 
    # gen selection
    process.p3.replace(process.genMuonSelection, process.genElectronSelection)
    process.p4.replace(process.genMuonSelection, process.genElectronSelection)
    pathlist = [process.p1, process.p2, process.p3, process.p4]
    for path in pathlist:
        # replace jet lepton veto
        path.replace(process.noOverlapJetsPF, process.noOverlapJetsPFelec)
        # replace muon selection
        path.remove(process.muonCuts)
        path.remove(process.secondMuonVeto)
        path.replace( process.electronVeto, process.electronSelection)
	## replace effSF
        path.replace(process.effSFMuonEventWeight, process.effSFElectronEventWeight)
        ## replace gen object kinematics
        if(runningOnData=="MC"):
            process.genAllElectronKinematics.weight=cms.InputTag("")
        # remove muon monitoring
        path.remove(process.tightMuontightJetsKinematics)
        path.remove(process.tightMuonKinematics)
        path.remove(process.tightMuonQuality)
        path.remove(process.tightMuontightJetsKinematicsTagged)
        path.remove(process.tightMuonKinematicsTagged         )
        path.remove(process.tightMuonQualityTagged            )
        path.remove(process.tightMuontightJetsKinematicsSSV)
        # add electron monitoring
        path.replace(process.tightLead_0_JetKinematics      , process.tightElectronKinematics * process.tightElectronQuality * process.tightLead_0_JetKinematics)
        path.replace(process.tightLead_0_JetKinematicsTagged, process.tightElectronKinematicsTagged * process.tightElectronQualityTagged  * process.tightLead_0_JetKinematicsTagged)
        path.replace(process.tightMuonKinematicsSSV, process.tightElectronKinematicsSSV)
        path.replace(process.tightMuonQualitySSV   , process.tightElectronQualitySSV   )
        # replace muon by electron in (remaining) kinfit analyzers
        massSearchReplaceAnyInputTag(path, 'tightMuons', 'goodElectronsEJ')


allpaths  = process.paths_().keys()

# switch to PF2PAT
if(pfToPAT):
    from TopAnalysis.TopUtils.usePatTupleWithParticleFlow_cff import prependPF2PATSequence
    recoPaths=['p1','p2']
    # define general options
    PFoptions = {
        'runOnMC': True,
        'runOnAOD': True,
        'switchOffEmbedding': False,
        'addResolutions': True,
        'resolutionsVersion': 'fall11',
        'runOnOLDcfg': True,
        'cutsMuon': 'pt > 10. & abs(eta) < 2.5',
        'cutsElec': 'et > 15. & abs(eta) < 2.5',
        'cutsJets': 'pt > 10 & abs(eta) < 5.0', 
        'electronIDs': ['CiC','classical'],
        'pfIsoConeMuon': 0.4,
        'pfIsoConeElec': 0.4,
        'pfIsoValMuon': 0.2,
        'pfIsoValElec': 0.2,
        'skipIfNoPFMuon': False,
        'skipIfNoPFElec': False,
        'addNoCutPFMuon': False,
        'addNoCutPFElec': False,
        'noMuonTopProjection': False,
        'noElecTopProjection': False,
        'analyzersBeforeMuonIso':cms.Sequence(),
        'analyzersBeforeElecIso':cms.Sequence(),
        'excludeElectronsFromWsFromGenJets': True,
        'METCorrectionLevel': 1
        }
    # adaptions when running on data
    if(runningOnData=="data"):
        PFoptions['runOnMC']=False
    if(decayChannel=="electron"):
    # take into account different electron vetos in mu and e channel
        PFoptions['cutsElec'    ] = 'et > 20. & abs(eta) < 2.5'
    # skip events (and jet calculation) if no lepton is found
    # only done in data, as in MC you need the events for parton truth plots
        PFoptions['skipIfNoPFElec']=True
    # collection without cuts is added
        PFoptions['addNoCutPFElec']=True
    # project no other leptons than the selected ones
        #PFoptions['noMuonTopProjection']=True
    elif(decayChannel=="muon"):
        PFoptions['skipIfNoPFMuon']=True
        PFoptions['addNoCutPFMuon']=True
        #PFoptions['noElecTopProjection']=True
	## option to change PF2PAT settings for cutflow excercise:
	if(cutflowSynch):
	    PFoptions['pfIsoValMuon'] = 0.2
	    #PFoptions['cutsElec'] = 'pt>5 && gsfTrackRef.isNonnull && gsfTrackRef.trackerExpectedHitsInner.numberOfLostHits<2'
    prependPF2PATSequence(process, recoPaths, PFoptions)
    # remove electron collections as long as id does not exist in the tuples
    for path in recoPaths:
        #getattr(process,path).remove( process.looseElectronsEJ )
        #getattr(process,path).remove( process.tightElectronsEJ )
        #getattr(process,path).remove( process.unconvTightElectronsEJ )
        #getattr(process,path).remove( process.goodElectronsEJ )
        # replace object consistently with names from PF2PAT
        #massSearchReplaceAnyInputTag(getattr(process,path), 'patMETsPF', 'patMETs')
        #massSearchReplaceAnyInputTag(getattr(process,path), 'selectedPatJetsAK5PF', 'selectedPatJets')        
        # run trigger at the beginning to save a lot of time
        getattr(process,path).insert(0,process.hltFilter)
  
## change decay subset to parton level (ME)
#process.decaySubset.fillMode = cms.string("kME")

## generator kinematics (check E-p conservation on gen level)
if (PythiaSample=="False" and runningOnData=="MC"):
    print
    print "Applying MC Kinematics Filter"
    for path in allpaths:
        getattr(process,path).insert(0,process.totalKinematicsFilterDefault)

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

## possibly remove event reweighting

# define allpaths if not done yet
if(not pfToPAT):
    allpaths  = process.paths_().keys()
    
# Pile up
if(not PUreweigthing or runningOnData=="data"):
    for path in allpaths:
        getattr(process,path).remove( process.makeEventWeightsPU )

# Eff SF
if(not effSFReweigthing or runningOnData=="data"):
    for path in allpaths:
        if(decayChannel=="muon"):
            getattr(process,path).remove( process.effSFMuonEventWeight )
	elif(decayChannel=="electron"):
            getattr(process,path).remove( process.effSFElectronEventWeight )

# Btag scale factor
if(not BtagReweigthing or runningOnData=="data"):
    for path in allpaths:
        getattr(process,path).remove( process.bTagSFEventWeight )

# combined scale factor
if(runningOnData=="data" or (not PUreweigthing and not effSFReweigthing) ):
    for path in allpaths:
        getattr(process,path).remove( process.eventWeightNoBtagSFWeight )

# combined scale factor   
if(runningOnData=="data" or (not BtagReweigthing and not effSFReweigthing) ):
    for path in allpaths:
        getattr(process,path).remove( process.eventWeightNoPUWeight )

# combined scale factor
if(runningOnData=="data" or (not PUreweigthing and not BtagReweigthing and not effSFReweigthing) ):
    for path in allpaths:
        getattr(process,path).remove( process.eventWeightFinal )

# shape distortion scale factor
if(sysDistort==''):
    for path in allpaths:
        getattr(process,path).remove( process.eventWeightDileptonModelVariation )
        getattr(process,path).remove( process.eventWeightPUDistort              )
        getattr(process,path).remove( process.eventWeightPUupDistort            )
        getattr(process,path).remove( process.eventWeightPUdownDistort          )
