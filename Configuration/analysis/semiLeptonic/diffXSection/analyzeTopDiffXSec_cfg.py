import FWCore.ParameterSet.Config as cms

## ---
##   use this file to study different distributions for measurement of differential Cross Section
##   does also a monitoring of the cuts before they are applied
## ---

## ---
##    example to run this cfg file
## ---
## cmsRun analyzeTopDiffXSec_cfg.py triggerTag=HLT,sample=ttbar,lepton=muon,eventsToProcess=5000

## ---
##    options
## ---

## introduce interface with crab file
## allows to choose registered parameter for every job individually
import FWCore.ParameterSet.VarParsing as VarParsing
import sys
options = VarParsing.VarParsing ('standard')

# create object triggerTag with default value HLT of type singleton and string
options.register('triggerTag', 'HLT',VarParsing.VarParsing.multiplicity.singleton,VarParsing.VarParsing.varType.string, "chosen trigger tag")
# create sample label with default value data
# for summer11 MC one can choose: ttbar, wjets, zjets, singleAntiTopS, singleTopT, singleAntiTopT, singleTopTw, singleAntiTopTw, singleTopS WW, WZ, ZZ, qcd (for muon channel); qcdEM1, qcdEM2, qcdEM3, qcdBCE1, qcdBCE2, qcdBCE3 (for electron channel), zprime_m500gev_w5000mev, zprime_m750gev_w7500mev
# for systematic samples see list for each MC sample
options.register('sample', 'none',VarParsing.VarParsing.multiplicity.singleton,VarParsing.VarParsing.varType.string, "chosen sample")
# create lepton channel label 
options.register('lepton', 'unset',VarParsing.VarParsing.multiplicity.singleton,VarParsing.VarParsing.varType.string, "chosen decay channel")
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

print "used trigger path: TriggerResults::"+options.triggerTag

## choose jet collection and corresponding MET
if(not globals().has_key('jetType')):
    jetType =  'particleFlow' # 'Calo'

## run PF2PAT?
## only possible for special pat tuples!!!
if(not globals().has_key('pfToPAT')):
    pfToPAT = True #False
print "run PF2PAT?: ",pfToPAT,"(won't work if the file does not contain the necessary information!)"

## choose the semileptonic decay channel (electron or muon)
#decayChannel=options.lepton
if(options.lepton=='unset'): 
    if(not globals().has_key('decayChannel')):
        decayChannel = 'muon' # 'electron'
else:
    decayChannel=options.lepton
print "used lepton decay channel: "+decayChannel

# switch to run on data and remove all gen plots (type 'MC' or 'data')
if(not globals().has_key('runningOnData')): 
    runningOnData = "MC"
    
# print chosen sample (e.g. ttbar)
# value is known from external parsing
# if set, switches runOnAOD in PF2PAT to true
print "Chosen sample to run over: ", options.sample

## choose JSON file for data
if(not globals().has_key('jsonFile')):
    jsonFile =  ''

## enable/ disable PU event reweighting
if(not globals().has_key('PUreweigthing')):
    PUreweigthing = True # False
    # take care of data
    if (not runningOnData == "MC"):
        PUreweigthing = False
print "apply PU reweighting?: ",PUreweigthing

## version of the MC (important for trigger)
if(not globals().has_key('MCversion')):
    MCversion = "Fall11"

## enable/ disable btag SF event reweighting
if(not globals().has_key('BtagReweigthing')):
    BtagReweigthing = True # False
    # take care of data
    if (not runningOnData == "MC"):
        BtagReweigthing = False
print "apply Btag reweighting?: ",BtagReweigthing

## enable/ disable efficiency SF event reweighting
if(not globals().has_key('effSFReweigthing')):
    effSFReweigthing = True # False
    # take care of data
    if (not runningOnData == "MC"):
        effSFReweigthing = False
print "apply effSF reweighting?: ",effSFReweigthing

# choose jet correction level shown in plots
# L3Absolute for MC, L2L3Residual for data
if(not globals().has_key('corrLevel')):
    corrLevel='L3Absolute'
## define input
print "used JEC level in jetKinematics: "+corrLevel

## run kinematic fit?
## ATTENTION: until the new parameter jetResolutionSmearFactor
## is implemented in a higher version of the TKinFitter package you
## need to check out the head:
## cvs co TopQuarkAnalysis/TopKinFitter

if(not globals().has_key('applyKinFit')):
   applyKinFit = True#  False
if(applyKinFit==True):
    print "kinFit and top reconstruction is applied - attention: slows down!!!"
if(applyKinFit==False):
    print "kinFit and top reconstruction not applied"
    
## choose whether you want a pat tuple as output
if(not globals().has_key('writeOutput')): 
    writeOutput  = False # True
    
## remove all ttbar specific gen level filter - used by other _cfg based on this file
if(not globals().has_key('removeGenTtbar')):
    removeGenTtbar = False 
if(removeGenTtbar==True):
    print "all gen level filters using ttbar decay subset are removed" 
    if(runningOnData=="MC"):
        print "selection for gen plots only via TopAnalysis.TopFilter.sequences.genSelection_cff"

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
if(runningOnData=="MC"):
    print 'chosen ttbar filter:' , eventFilter

## choose if you want to include tau (->e/mu) events
if(not globals().has_key('tau')):
    tau = False # True
# use these tau events only in SG/SB configuration not for single decay modes or all
if(not eventFilter=='signal only' and not eventFilter=='background only'):
    tau= False
print "include tau->l events? ",tau

## choose whether synchronisation exercise should be done
if(not globals().has_key('cutflowSynch')): 
    cutflowSynch  = False # True
if(cutflowSynch):
    print "!!!! CUTFLOW SYNCHRONISATION EXERCISE !!!!"
    
## choose whether additional event weights should be applied
if(not globals().has_key('additionalEventWeights')): 
    additionalEventWeights  = True
if(additionalEventWeights):
    print "Additional event weights are applied to the KinFit analyzers for monitoring, PU, b-tag and lepton eff. variations!"

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
if(not sysDistort==''):
    print "ATTENTION!!! apply shape reweighting, variation", sysDistort

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
    #'/store/data/Run2011A/MuHad/AOD/May10ReReco-v1/0005/FC809CA7-0C7D-E011-AE04-003048678B1C.root' 

    #'/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_9_1_HFr.root'
    #'/store/user/mgoerner/WJetsToLNu_TuneD6T_7TeV-madgraph-tauola/PAT_FALL10HH/148435cd71339b79cc0025730c13472a/fall10MC_36_1_085.root'
    #'/store/user/mgoerner/WJetsToLNu_TuneD6T_7TeV-madgraph-tauola/PAT_FALL10HH/148435cd71339b79cc0025730c13472a/fall10MC_100_1_iJg.root'
    #'/store/user/wbehrenh/WJetsToLNu_TuneD6T_7TeV-madgraph-tauola/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_9_2_k5G.root'
    #'/store/user/henderle/TTJets_TuneD6T_7TeV-madgraph-tauola/PAT_FALL10HH/6c1c00d4602477b58cef63f182ce0614/fall10MC_14_3_M5Q.root'
    #'/store/user/dammann/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_21_1_JdU.root'
    #'/store/user/mgoerner/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/PAT_FALL10HH2/148435cd71339b79cc0025730c13472a/fall10MC_9_1_mFa.root'
    #'/store/user/mgoerner/Mu/PAT_Nov4RerecoL1IncludedUHH/e37a6f43ad6b01bd8486b714dc367330/DataNov4RerecoL1included_196_1_jzY.root'
    #'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FEEE3638-F297-E011-AAF8-00304867BEC0.root'
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

## automatically load the correct (AOD) .root file list for each MC sample
if(not options.sample=="none"):
    if(options.sample=="ttbar"):
       # process.load("TopAnalysis/Configuration/ttjets_MadgraphZ2_Summer11_AOD_cff")
        process.load("TopAnalysis/Configuration/samples/Fall11_TTJets_TuneZ2_7TeV_madgraph_tauola_cff")
        print "analyzed sample: TopAnalysis/Configuration/python/ttjets_MadgraphZ2_Summer11_AOD_cff.py"
	if(eventFilter=='signal only'):
	    outputFileName+="DiffXSecSigMadD6TSummer11"
	elif(eventFilter=='background only'):
	    outputFileName+="DiffXSecBkgMadD6TSummer11"
    if(options.sample=="ttbarMatchingDown"):        
        process.load("TopAnalysis/Configuration/ttjets_matching_down_MadgraphZ2_Summer11_AOD_cff")
        print "analyzed sample: TopAnalysis/Configuration/python/ttjets_matching_down_MadgraphZ2_Summer11_AOD_cff.py"
	additionalEventWeights=False
	if(eventFilter=='signal only'):
	    outputFileName+="DiffXSecSigMadD6TSummer11MatchDown"
	elif(eventFilter=='background only'):
	    outputFileName+="DiffXSecBkgMadD6TSummer11MatchDown"
    if(options.sample=="ttbarMatchingUp"):        
        process.load("TopAnalysis/Configuration/ttjets_matching_up_MadgraphZ2_Summer11_AOD_cff")
        print "analyzed sample: TopAnalysis/Configuration/python/ttjets_matching_up_MadgraphZ2_Summer11_AOD_cff.py"
	additionalEventWeights=False
	if(eventFilter=='signal only'):
	    outputFileName+="DiffXSecSigMadD6TSummer11MatchUp"
	elif(eventFilter=='background only'):
	    outputFileName+="DiffXSecBkgMadD6TSummer11MatchUp"
    if(options.sample=="ttbarScaleDown"):        
        process.load("TopAnalysis/Configuration/ttjets_scale_down_MadgraphZ2_Summer11_AOD_cff")
        print "analyzed sample: TopAnalysis/Configuration/python/ttjets_scale_down_MadgraphZ2_Summer11_AOD_cff.py"
	additionalEventWeights=False
	if(eventFilter=='signal only'):
	    outputFileName+="DiffXSecSigMadD6TSummer11ScaleDown"
	elif(eventFilter=='background only'):
	    outputFileName+="DiffXSecBkgMadD6TSummer11ScaleDown"
    if(options.sample=="ttbarScaleUp"):        
        process.load("TopAnalysis/Configuration/ttjets_scale_up_MadgraphZ2_Summer11_AOD_cff")
        print "analyzed sample: TopAnalysis/Configuration/python/ttjets_scale_up_MadgraphZ2_Summer11_AOD_cff.py"
	additionalEventWeights=False
	if(eventFilter=='signal only'):
	    outputFileName+="DiffXSecSigMadD6TSummer11ScaleUp"
	elif(eventFilter=='background only'):
	    outputFileName+="DiffXSecBkgMadD6TSummer11ScaleUp"
    if(options.sample=="ttbarMassDown"):        
        process.load("TopAnalysis/Configuration/ttjets_mass169_5_MadgraphZ2_Summer11_AOD_cff")
        print "analyzed sample: TopAnalysis/Configuration/python/ttjets_mass169_5_MadgraphZ2_Summer11_AOD_cff.py"
	additionalEventWeights=False
	if(eventFilter=='signal only'):
	    outputFileName+="DiffXSecSigMadD6TSummer11TopMassDown"
	elif(eventFilter=='background only'):
	    outputFileName+="DiffXSecBkgMadD6TSummer11TopMassDown"
    if(options.sample=="ttbarMassUp"):        
        process.load("TopAnalysis/Configuration/ttjets_mass175_5_MadgraphZ2_Summer11_AOD_cff")
        print "analyzed sample: TopAnalysis/Configuration/python/ttjets_mass175_5__MadgraphZ2_Summer11_AOD_cff.py"
	additionalEventWeights=False
	if(eventFilter=='signal only'):
	    outputFileName+="DiffXSecSigMadD6TSummer11TopMassUp"
	elif(eventFilter=='background only'):
	    outputFileName+="DiffXSecBkgMadD6TSummer11TopMassUp"
    if(options.sample=="wjets"):        
        process.load("TopAnalysis/Configuration/wlnujets_MadgraphZ2_Summer11_AOD_cff")
        print "analyzed sample: TopAnalysis/Configuration/python/wlnujets_MadgraphZ2_Summer11_AOD_cff.py"
	outputFileName+="DiffXSecWjetsMadD6TSummer11"
    if(options.sample=="wjetsMatchingUp"):        
        process.load("TopAnalysis/Configuration/wlnujets_matching_up_MadgraphZ2_Summer11_AOD_cff")
        print "analyzed sample: TopAnalysis/Configuration/python/wlnujets_matching_up_MadgraphZ2_Summer11_AOD_cff.py"
	additionalEventWeights=False
	outputFileName+="DiffXSecWjetsMadD6TSummer11MatchUp"
    if(options.sample=="wjetsMatchingDown"):        
        process.load("TopAnalysis/Configuration/wlnujets_matching_down_MadgraphZ2_Summer11_AOD_cff")
        print "analyzed sample: TopAnalysis/Configuration/python/wlnujets_matching_down_MadgraphZ2_Summer11_AOD_cff.py"
	additionalEventWeights=False
	outputFileName+="DiffXSecWjetsMadD6TSummer11MatchDown"
    if(options.sample=="wjetsScaleUp"):        
        process.load("TopAnalysis/Configuration/wlnujets_scale_up_MadgraphZ2_Summer11_AOD_cff")
        print "analyzed sample: TopAnalysis/Configuration/python/wlnujets_scale_up_MadgraphZ2_Summer11_AOD_cff.py"
	additionalEventWeights=False
	outputFileName+="DiffXSecWjetsMadD6TSummer11ScaleUp"
    if(options.sample=="wjetsScaleDown"):
        process.load("TopAnalysis/Configuration/wlnujets_scale_down_MadgraphZ2_Summer11_AOD_cff")
        print "analyzed sample: TopAnalysis/Configuration/python/wlnujets_scale_down_MadgraphZ2_Summer11_AOD_cff.py"
	additionalEventWeights=False        
	outputFileName+="DiffXSecWjetsMadD6TSummer11ScaleDown"
    if(options.sample=="zjets"):        
        process.load("TopAnalysis/Configuration/dylljetsM50_MadgraphZ2_Summer11_AOD_cff")
        print "analyzed sample: TopAnalysis/Configuration/python/dylljetsM50_MadgraphZ2_Summer11_AOD_cff.py"
	outputFileName+="DiffXSecZjetsMadD6TSummer11"
    if(options.sample=="zjetsMatchingUp"):        
        process.load("TopAnalysis/Configuration/zlljets_matching_up_MadgraphZ2_Summer11_AOD_cff")
        print "analyzed sample: TopAnalysis/Configuration/python/zlljets_matching_up_MadgraphZ2_Summer11_AOD_cff.py"
	additionalEventWeights=False
	outputFileName+="DiffXSecZjetsMadD6TSummer11MatchUp"
    if(options.sample=="zjetsMatchingDown"):        
        process.load("TopAnalysis/Configuration/zlljets_matching_down_MadgraphZ2_Summer11_AOD_cff")
        print "analyzed sample: TopAnalysis/Configuration/python/zlljets_matching_down_MadgraphZ2_Summer11_AOD_cff.py"
	additionalEventWeights=False
	outputFileName+="DiffXSecZjetsMadD6TSummer11MatchDown"
    if(options.sample=="zjetsScaleUp"):        
        process.load("TopAnalysis/Configuration/zlljets_scale_up_MadgraphZ2_Summer11_AOD_cff")
        print "analyzed sample: TopAnalysis/Configuration/python/zlljets_scale_up_MadgraphZ2_Summer11_AOD_cff.py"
	additionalEventWeights=False
	outputFileName+="DiffXSecZjetsMadD6TSummer11ScaleUp"
    if(options.sample=="zjetsScaleDown"):        
        process.load("TopAnalysis/Configuration/zlljets_scale_down_MadgraphZ2_Summer11_AOD_cff")
        print "analyzed sample: TopAnalysis/Configuration/python/zlljets_scale_down_MadgraphZ2_Summer11_AOD_cff.py"
	additionalEventWeights=False      
	outputFileName+="DiffXSecZjetsMadD6TSummer11ScaleDown"
    if(options.sample=="singleTopS"):        
        process.load("TopAnalysis/Configuration/singleTop_schannel_PythiaPowhegZ2_Summer11_AOD_cff")
        print "analyzed sample: singleTop_schannel_PythiaPowhegZ2_Summer11_AOD_cff.py"
	outputFileName+="DiffXSecSingleTopSchannelMadZ2Summer11"
    if(options.sample=="singleTopSScaleDown"):        
        process.load("TopAnalysis/Configuration/singleTop_schannel_scale_down_PythiaPowhegZ2_Summer11_AOD_cff")
        print "analyzed sample: singleTop_schannel_scale_down_PythiaPowhegZ2_Summer11_AOD_cff.py"
	additionalEventWeights=False   
	outputFileName+="DiffXSecSingleTopSchannelMadZ2Summer11ScaleDown"
    if(options.sample=="singleTopSScaleUp"):        
        process.load("TopAnalysis/Configuration/singleTop_schannel_scale_up_PythiaPowhegZ2_Summer11_AOD_cff")
        print "analyzed sample: singleTop_schannel_scale_up_PythiaPowhegZ2_Summer11_AOD_cff.py"
	additionalEventWeights=False
	outputFileName+="DiffXSecSingleTopSchannelMadZ2Summer11ScaleUp"
    if(options.sample=="singleAntiTopS"):        
        process.load("TopAnalysis/Configuration/singleAntiTop_schannel_PythiaPowhegZ2_Summer11_AOD_cff")
        print "analyzed sample: singleAntiTop_schannel_PythiaPowhegZ2_Summer11_AOD_cff.py"
	outputFileName+="DiffXSecSingleAntiTopSchannelMadZ2Summer11"
    if(options.sample=="singleAntiTopSScaleDown"):        
        process.load("TopAnalysis/Configuration/singleAntiTop_schannel_scale_down_PythiaPowhegZ2_Summer11_AOD_cff")
        print "analyzed sample: singleAntiTop_schannel_scale_down_PythiaPowhegZ2_Summer11_AOD_cff.py"
	additionalEventWeights=False
	outputFileName+="DiffXSecSingleAntiTopSchannelMadZ2Summer11ScaleDown"
    if(options.sample=="singleAntiTopSScaleUp"):        
        process.load("TopAnalysis/Configuration/singleAntiTop_schannel_scale_up_PythiaPowhegZ2_Summer11_AOD_cff")
        print "analyzed sample: singleAntiTop_schannel_scale_up_PythiaPowhegZ2_Summer11_AOD_cff.py"
	additionalEventWeights=False
	outputFileName+="DiffXSecSingleAntiTopSchannelMadZ2Summer11ScaleUp"
    if(options.sample=="singleTopT"):        
        process.load("TopAnalysis/Configuration/singleTop_tchannel_PythiaPowhegZ2_Summer11_AOD_cff")
        print "analyzed sample: singleTop_tchannel_PythiaPowhegZ2_Summer11_AOD_cff.py"
	outputFileName+="DiffXSecSingleTopTchannelMadZ2Summer11"
    if(options.sample=="singleTopTScaleDown"):        
        process.load("TopAnalysis/Configuration/singleTop_tchannel_scale_down_PythiaPowhegZ2_Summer11_AOD_cff")
        print "analyzed sample: singleTop_tchannel_scale_down_PythiaPowhegZ2_Summer11_AOD_cff.py"
	additionalEventWeights=False
	outputFileName+="DiffXSecSingleTopTchannelMadZ2Summer11ScaleDown"
    if(options.sample=="singleTopTScaleUp"):        
        process.load("TopAnalysis/Configuration/singleTop_tchannel_scale_up_PythiaPowhegZ2_Summer11_AOD_cff")
        print "analyzed sample: singleTop_tchannel_scale_up_PythiaPowhegZ2_Summer11_AOD_cff.py"
	additionalEventWeights=False
	outputFileName+="DiffXSecSingleTopTchannelMadZ2Summer11ScaleUp"
    if(options.sample=="singleAntiTopT"):        
        process.load("TopAnalysis/Configuration/singleAntiTop_tchannel_PythiaPowhegZ2_Summer11_AOD_cff")
        print "analyzed sample: singleAntiTop_tchannel_PythiaPowhegZ2_Summer11_AOD_cff.py"
	outputFileName+="DiffXSecSingleAntiTopTchannelMadZ2Summer11"
    if(options.sample=="singleAntiTopTScaleDown"):        
        process.load("TopAnalysis/Configuration/singleAntiTop_tchannel_scale_down_PythiaPowhegZ2_Summer11_AOD_cff")
        print "analyzed sample: singleAntiTop_tchannel_scale_down_PythiaPowhegZ2_Summer11_AOD_cff.py"
	additionalEventWeights=False
	outputFileName+="DiffXSecSingleAntiTopTchannelMadZ2Summer11ScaleDown"
    if(options.sample=="singleAntiTopTScaleUp"):        
        process.load("TopAnalysis/Configuration/singleAntiTop_tchannel_scale_up_PythiaPowhegZ2_Summer11_AOD_cff")
        print "analyzed sample: singleAntiTop_tchannel_scale_up_PythiaPowhegZ2_Summer11_AOD_cff.py"
	additionalEventWeights=False
	outputFileName+="DiffXSecSingleAntiTopTchannelMadZ2Summer11ScaleUp"
    if(options.sample=="singleTopTw"):        
        process.load("TopAnalysis/Configuration/singleTop_twchannelDR_PythiaPowhegZ2_Summer11_AOD_cff")
        print "analyzed sample: singleTop_twchannelDR_PythiaPowhegZ2_Summer11_AOD_cff.py"
	outputFileName+="DiffXSecSingleTopTWchannelMadZ2Summer11"
    if(options.sample=="singleTopTwScaleDown"):        
        process.load("TopAnalysis/Configuration/singleTop_twchannelDR_scale_down_PythiaPowhegZ2_Summer11_AOD_cff")
        print "analyzed sample: singleTop_twchannelDR_scale_down_PythiaPowhegZ2_Summer11_AOD_cff.py"
	additionalEventWeights=False
	outputFileName+="DiffXSecSingleTopTWchannelMadZ2Summer11ScaleDown"
    if(options.sample=="singleTopTwScaleUp"):        
        process.load("TopAnalysis/Configuration/singleTop_twchannelDR_scale_up_PythiaPowhegZ2_Summer11_AOD_cff")
        print "analyzed sample: singleTop_twchannelDR_PythiaPowhegZ2_scale_up_Summer11_AOD_cff.py"
	additionalEventWeights=False
	outputFileName+="DiffXSecSingleTopTWchannelMadZ2Summer11ScaleUp"
    if(options.sample=="singleAntiTopTw"):        
        process.load("TopAnalysis/Configuration/singleAntiTop_twchannelDR_PythiaPowhegZ2_Summer11_AOD_cff")
        print "analyzed sample: singleAntiTop_twchannelDR_PythiaPowhegZ2_Summer11_AOD_cff.py"
	outputFileName+="DiffXSecSingleAntiTopTWchannelMadZ2Summer11"
    if(options.sample=="singleAntiTopTwScaleDown"):        
        process.load("TopAnalysis/Configuration/singleAntiTop_twchannelDR_scale_down_PythiaPowhegZ2_Summer11_AOD_cff")
        print "analyzed sample: singleAntiTop_twchannelDR_scale_down_PythiaPowhegZ2_Summer11_AOD_cff.py"
	additionalEventWeights=False
	outputFileName+="DiffXSecSingleAntiTopTWchannelMadZ2Summer11ScaleDown"
    if(options.sample=="singleAntiTopTwScaleUp"):        
        process.load("TopAnalysis/Configuration/singleAntiTop_twchannelDR_scale_up_PythiaPowhegZ2_Summer11_AOD_cff")
        print "analyzed sample: singleAntiTop_twchannelDR_scale_up_PythiaPowhegZ2_Summer11_AOD_cff.py"
	additionalEventWeights=False
	outputFileName+="DiffXSecSingleAntiTopTWchannelMadZ2Summer11ScaleUp"
    if(options.sample=="zprime_m500gev_w5000mev"):        
        process.load("TopAnalysis/Configuration/zprime_M500GeV_W5000MeV_Madgraph_Summer11_AOD_cff")
        print "analyzed sample: zprime_M500GeV_W5000MeV_Madgraph_Summer11_AOD_cff.py"
    if(options.sample=="zprime_m750gev_w7500mev"):        
        process.load("TopAnalysis/Configuration/zprime_M750GeV_W7500MeV_Madgraph_Summer11_AOD_cff")
        print "analyzed sample: zprime_M750GeV_W7500MeV_Madgraph_Summer11_AOD_cff.py"
	additionalEventWeights=False
    if(decayChannel=='muon'):
        if(options.sample=="qcd"):
            process.load("TopAnalysis/Configuration/qcdmu15enriched_Pythia6_Summer11_AOD_cff")
            print "analyzed sample: TopAnalysis/Configuration/python/qcdmu15enriched_Pythia6_Summer11_AOD_cff.py"
            PythiaSample="True"
	    outputFileName+="DiffXSecQCDPythiaZ2Summer11"
    if(decayChannel=='electron'):
        if(options.sample=="qcdEM1"):
            process.load("TopAnalysis/Configuration/qcdEMenrichedPt20to30_Pythia6_Summer11_AOD_cff")
            print "analyzed sample: TopAnalysis/Configuration/python/qcdEMenrichedPt20to30_Pythia6_Summer11_AOD_cff.py"
            PythiaSample="True"
	    outputFileName+="DiffXSecQCDPythiaEM1Z2Summer11"
        if(options.sample=="qcdEM2"):
            process.load("TopAnalysis/Configuration/qcdEMenrichedPt30to80_Pythia6_Summer11_AOD_cff")
            print "analyzed sample: TopAnalysis/Configuration/python/qcdEMenrichedPt30to80_Pythia6_Summer11_AOD_cff.py"
            PythiaSample="True"
	    outputFileName+="DiffXSecQCDPythiaEM2Z2Summer11"
        if(options.sample=="qcdEM3"):
            process.load("TopAnalysis/Configuration/qcdEMenrichedPt80to170_Pythia6_Summer11_AOD_cff")
            print "analyzed sample: TopAnalysis/Configuration/python/qcdEMenrichedPt80to170_Pythia6_Summer11_AOD_cff.py"
            PythiaSample="True"
	    outputFileName+="DiffXSecQCDPythiaEM3Z2Summer11"
        if(options.sample=="qcdBCE1"):
            process.load("TopAnalysis/Configuration/qcdBCtoEPt20to30_Pythia6_Summer11_AOD_cff")
            print "analyzed sample: TopAnalysis/Configuration/python/qcdBCtoEPt20to30_Pythia6_Summer11_AOD_cff.py"
            PythiaSample="True"
	    outputFileName+="DiffXSecQCDPythiaBCE1Z2Summer11"
        if(options.sample=="qcdBCE2"):
            process.load("TopAnalysis/Configuration/qcdBCtoEPt30to80_Pythia6_Summer11_AOD_cff")
            print "analyzed sample: TopAnalysis/Configuration/python/qcdBCtoEPt30to80_Pythia6_Summer11_AOD_cff.py"
            PythiaSample="True"
	    outputFileName+="DiffXSecQCDPythiaBCE2Z2Summer11"
        if(options.sample=="qcdBCE3"):
            process.load("TopAnalysis/Configuration/qcdBCtoEPt80to170_Pythia6_Summer11_AOD_cff")
            print "analyzed sample: TopAnalysis/Configuration/python/qcdBCtoEPt80to170_Pythia6_Summer11_AOD_cff.py"
            PythiaSample="True"
	    outputFileName+="DiffXSecQCDPythiaBCE3Z2Summer11"
    if(options.sample=="WW"):        
        process.load("TopAnalysis/Configuration/wwtoall_Pythia6Z2_Summer11_AOD_cff")
        print "analyzed sample: TopAnalysis/Configuration/wwtoall_Pythia6Z2_Summer11_AOD_cff.py"
        PythiaSample="True"
	outputFileName+="DiffXSecWWPytia6Z2Summer11"
    if(options.sample=="WZ"):        
        process.load("TopAnalysis/Configuration/wztoall_Pythia6Z2_Summer11_AOD_cff")
        print "analyzed sample: TopAnalysis/Configuration/wztoall_Pythia6Z2_Summer11_AOD_cff.py"
        PythiaSample="True"
	outputFileName+="DiffXSecWZPytia6Z2Summer11"
    if(options.sample=="ZZ"):        
        process.load("TopAnalysis/Configuration/zztoall_Pythia6Z2_Summer11_AOD_cff")
        print "analyzed sample: TopAnalysis/Configuration/zztoall_Pythia6Z2_Summer11_AOD_cff.py"
        PythiaSample="True"
	outputFileName+="DiffXSecZZPytia6Z2Summer11"
        	
## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string(outputFileName+"PF.root")
)
print "output file name = ", process.TFileService.fileName

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
#(use "TriggerResults::REDIGI38X" for fall10 QCD, WW, ZZ and WZ and "TriggerResults::HLT" for the other ones)
# for all PileUp sample use "TriggerResults::REDIGI38XPU"
# for all spring11 MC use REDIGI311X
from HLTrigger.HLTfilters.hltHighLevel_cfi import *
process.hltFilter = hltHighLevel.clone(TriggerResultsTag = "TriggerResults::"+options.triggerTag, HLTPaths = ["HLT_IsoMu24_eta2p1_v*"], throw=False)
if(MCversion=="Summer11"):
      process.hltFilter.HLTPaths=["HLT_IsoMu24_v*"]
#process.hltFilter = hltHighLevel.clone(TriggerResultsTag = "TriggerResults::HLT", HLTPaths = ["HLT_Mu15_v*"], throw=False)
#process.hltFilter = hltHighLevel.clone(TriggerResultsTag = "TriggerResults::REDIGI38X", HLTPaths = [""], throw=False)
#process.hltFilter = hltHighLevel.clone(TriggerResultsTag = "TriggerResults::REDIGI38XPU", HLTPaths = ["HLT_Mu9"], throw=False)
#process.hltFilter = hltHighLevel.clone(TriggerResultsTag = "TriggerResults::REDIGI311X", HLTPaths = ["HLT_Mu9"], throw=False)
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
        print "Dummy output to avoid programme crash --> to be revised !!!!"
        #process.TFileService.fileName = 'analyzeDiffXSec_testSig.root'
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
process.btagSelection = process.bottomJetSelection.clone(src = 'tightBottomPFJets', minNumber = 2, maxNumber = 99999)

## kinematic contributions
## muon
process.tightMuonKinematics        = process.analyzeMuonKinematics.clone (src = 'tightMuons')
process.tightMuonQuality           = process.analyzeMuonQuality.clone    (src = 'tightMuons')
process.tightMuonKinematicsTagged  = process.tightMuonKinematics.clone();
process.tightMuonQualityTagged     = process.tightMuonQuality.clone();
process.kinematicMuonQualityPreSel = process.analyzeMuonQuality.clone    (src = 'kinematicMuons')
process.goldenMuonQualityPreSel    = process.analyzeMuonQuality.clone    (src = 'goldenMuons'   )
process.tightMuonKinematicsPreSel  = process.analyzeMuonKinematics.clone (src = 'tightMuons'    )
process.tightMuonQualityPreSel     = process.analyzeMuonQuality.clone    (src = 'tightMuons'    )

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
process.tightJetKinematicsPreSel  = process.analyzeJetKinematics.clone(src = 'tightLeadingPFJets', analyze = udsAll)
process.tightJetQualityPreSel     = process.analyzeJetQuality.clone   (src = 'tightLeadingPFJets')

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
process.bottomLead_0_JetKinematicsTagged = process.analyzeJetKinematics.clone (src = 'tightBottomPFJets', analyze = uds0 )
process.bottomLead_1_JetKinematicsTagged = process.analyzeJetKinematics.clone (src = 'tightBottomPFJets', analyze = uds1 )

## muon&jets
process.tightMuontightJetsKinematics       = process.analyzeMuonJetKinematics.clone(srcA = 'tightMuons', srcB = 'tightLeadingPFJets')
process.tightMuontightJetsKinematicsTagged = process.tightMuontightJetsKinematics.clone()
process.trackMuontightJetsKinematicsPreSel = process.analyzeMuonJetKinematics.clone(srcA = 'trackMuons', srcB = 'vetoJets')

## electrons
process.tightElectronKinematics        = process.analyzeElectronKinematics.clone( src = 'goodElectronsEJ'  )
process.tightElectronQuality           = process.analyzeElectronQuality.clone   ( src = 'goodElectronsEJ'  )
process.tightElectronKinematicsTagged  = process.analyzeElectronKinematics.clone( src = 'goodElectronsEJ'  )
process.tightElectronQualityTagged     = process.analyzeElectronQuality.clone   ( src = 'goodElectronsEJ'  )

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
process.PUControlDistributions.PUEventWeightSource        = cms.InputTag("eventWeightPU",       "eventWeightPU"       )
process.PUControlDistributions.PUEventWeightUpSource      = cms.InputTag("eventWeightPUsysUp",  "eventWeightPUUp"     )
process.PUControlDistributions.PUEventWeightDownSource    = cms.InputTag("eventWeightPUsysDown","eventWeightPUDown"   )
process.PUControlDistributions.PUEventWeight3DSource      = cms.InputTag("eventWeightPU",       "eventWeightPU3D"     )
process.PUControlDistributions.PUEventWeight3DUpSource    = cms.InputTag("eventWeightPUsysUp",  "eventWeightPU3DUp"   )
process.PUControlDistributions.PUEventWeight3DDownSource  = cms.InputTag("eventWeightPUsysDown","eventWeightPU3DDown" )

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
                                                      process.analyzeMETMuonTagged               +
                                                      process.tightMuontightJetsKinematicsTagged +
                                                      process.bottomLead_0_JetKinematicsTagged   +
                                                      process.bottomLead_1_JetKinematicsTagged
                                                      )
    
process.basicMonitoring = cms.Sequence(process.trackMuontightJetsKinematicsPreSel +
                                       process.kinematicMuonQualityPreSel         +
                                       process.goldenMuonQualityPreSel            +
                                       process.tightMuonKinematicsPreSel          +
                                       process.tightMuonQualityPreSel             +
                                       process.tightJetKinematicsPreSel           +
                                       process.tightJetQualityPreSel              
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
        print 'kinfit: processing ttbar SG MC - build genmatch'
else:
    removeTtSemiLepHypGenMatch(process)
    if(applyKinFit==True):
        print 'kinfit: processing bkg or data - genmatch removed'

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
#process.kinFitTtSemiLepEventHypothesis.constraints = [1, 2, 6]
process.kinFitTtSemiLepEventHypothesis.constraints = [1, 2, 3, 4]
process.kinFitTtSemiLepEventHypothesis.mTop = 172.5

# consider b-tagging in event reconstruction
#process.kinFitTtSemiLepEventHypothesis.bTagAlgo = "trackCountingHighEffBJetTags"
process.kinFitTtSemiLepEventHypothesis.bTagAlgo = "simpleSecondaryVertexHighEffBJetTags"

# TCHE  discr.values 7TeV: 1.70, 3.30, 10.20
# SSVHE discr.values 7TeV: x.xx, 1.74,  x.xx
process.kinFitTtSemiLepEventHypothesis.minBDiscBJets     = 1.74
process.kinFitTtSemiLepEventHypothesis.maxBDiscLightJets = 1.74
process.kinFitTtSemiLepEventHypothesis.useBTagging       = True

# use larger JER in KinFit as it is obtained from data
if(runningOnData=="data") and (applyKinFit==True):
    process.kinFitTtSemiLepEventHypothesis.jetEnergyResolutionSmearFactor = 1.1

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
# c) chi2<5
analyzeChi5  = cms.PSet( corrPerm=cms.bool(False), maxChi2=cms.double(5)  )
# d) chi2<10
analyzeChi10 = cms.PSet( corrPerm=cms.bool(False), maxChi2=cms.double(10) )
# e) chi2<15
analyzeChi15 = cms.PSet( corrPerm=cms.bool(False), maxChi2=cms.double(15) )
# f) chi2<30
analyzeChi30 = cms.PSet( corrPerm=cms.bool(False), maxChi2=cms.double(30) )
# g) chi2<50
analyzeChi50 = cms.PSet( corrPerm=cms.bool(False), maxChi2=cms.double(50) )
# 2) lepton
process.load("TopAnalysis.TopAnalyzer.HypothesisKinFitLepton_cfi")
process.analyzeHypoKinFitLepton      = process.analyzeHypothesisKinFitLepton.clone(srcA = "ttSemiLepEvent", srcB = "tightMuons", analyze=analyzeAll    )
process.analyzeHypoKinFitLeptonCorr  = process.analyzeHypothesisKinFitLepton.clone(srcA = "ttSemiLepEvent", srcB = "tightMuons", analyze=analyzeCorrect)
process.analyzeHypoKinFitLeptonChi5  = process.analyzeHypothesisKinFitLepton.clone(srcA = "ttSemiLepEvent", srcB = "tightMuons", analyze=analyzeChi5   )
process.analyzeHypoKinFitLeptonChi10 = process.analyzeHypothesisKinFitLepton.clone(srcA = "ttSemiLepEvent", srcB = "tightMuons", analyze=analyzeChi10  )
process.analyzeHypoKinFitLeptonChi15 = process.analyzeHypothesisKinFitLepton.clone(srcA = "ttSemiLepEvent", srcB = "tightMuons", analyze=analyzeChi15   )
process.analyzeHypoKinFitLeptonChi30 = process.analyzeHypothesisKinFitLepton.clone(srcA = "ttSemiLepEvent", srcB = "tightMuons", analyze=analyzeChi30  )
process.analyzeHypoKinFitLeptonChi50 = process.analyzeHypothesisKinFitLepton.clone(srcA = "ttSemiLepEvent", srcB = "tightMuons", analyze=analyzeChi50  )
# 3) jets
process.load("TopAnalysis.TopAnalyzer.HypothesisKinFitJets_cfi")
process.analyzeHypoKinFitJets      = process.analyzeHypothesisKinFitJets.clone(srcA = "ttSemiLepEvent", srcB = "tightLeadingPFJets", analyze=analyzeAll    )
process.analyzeHypoKinFitJetsCorr  = process.analyzeHypothesisKinFitJets.clone(srcA = "ttSemiLepEvent", srcB = "tightLeadingPFJets", analyze=analyzeCorrect)
process.analyzeHypoKinFitJetsChi5  = process.analyzeHypothesisKinFitJets.clone(srcA = "ttSemiLepEvent", srcB = "tightLeadingPFJets", analyze=analyzeChi5   )
process.analyzeHypoKinFitJetsChi10 = process.analyzeHypothesisKinFitJets.clone(srcA = "ttSemiLepEvent", srcB = "tightLeadingPFJets", analyze=analyzeChi10  )
process.analyzeHypoKinFitJetsChi15 = process.analyzeHypothesisKinFitJets.clone(srcA = "ttSemiLepEvent", srcB = "tightLeadingPFJets", analyze=analyzeChi15  )
process.analyzeHypoKinFitJetsChi30 = process.analyzeHypothesisKinFitJets.clone(srcA = "ttSemiLepEvent", srcB = "tightLeadingPFJets", analyze=analyzeChi30  )
process.analyzeHypoKinFitJetsChi50 = process.analyzeHypothesisKinFitJets.clone(srcA = "ttSemiLepEvent", srcB = "tightLeadingPFJets", analyze=analyzeChi50  )
# 4) neutrino/MET
process.load("TopAnalysis.TopAnalyzer.HypothesisKinFitMET_cfi" )
process.analyzeHypoKinFitMET      = process.analyzeHypothesisKinFitMET.clone(srcA = "ttSemiLepEvent", srcB = "patMETs", analyze=analyzeAll    )
process.analyzeHypoKinFitMETCorr  = process.analyzeHypothesisKinFitMET.clone(srcA = "ttSemiLepEvent", srcB = "patMETs", analyze=analyzeCorrect)
process.analyzeHypoKinFitMETChi5  = process.analyzeHypothesisKinFitMET.clone(srcA = "ttSemiLepEvent", srcB = "patMETs", analyze=analyzeChi5   )
process.analyzeHypoKinFitMETChi10 = process.analyzeHypothesisKinFitMET.clone(srcA = "ttSemiLepEvent", srcB = "patMETs", analyze=analyzeChi10  )
process.analyzeHypoKinFitMETChi15 = process.analyzeHypothesisKinFitMET.clone(srcA = "ttSemiLepEvent", srcB = "patMETs", analyze=analyzeChi15  )
process.analyzeHypoKinFitMETChi30 = process.analyzeHypothesisKinFitMET.clone(srcA = "ttSemiLepEvent", srcB = "patMETs", analyze=analyzeChi30  )
process.analyzeHypoKinFitMETChi50 = process.analyzeHypothesisKinFitMET.clone(srcA = "ttSemiLepEvent", srcB = "patMETs", analyze=analyzeChi50  )

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
                                             process.filterProbKinFit                        +
                                             process.analyzeTopRecoKinematicsKinFit          +
                                             process.analyzeTopRecoKinematicsKinFitTopAntitop+
                                             process.analyzeTopRecoKinematicsGenMatch        +
                                             process.analyzeHypoKinFit                       +
                                             process.analyzeHypoKinFitLepton                 +
                                             process.analyzeHypoKinFitLeptonCorr             +
                                             process.analyzeHypoKinFitLeptonChi5             +
                                             process.analyzeHypoKinFitLeptonChi10            +
                                             process.analyzeHypoKinFitLeptonChi15            +
                                             process.analyzeHypoKinFitLeptonChi30            +
                                             process.analyzeHypoKinFitLeptonChi50            +
                                             process.analyzeHypoKinFitMET                    +
                                             process.analyzeHypoKinFitMETCorr                +
                                             process.analyzeHypoKinFitMETChi5                +
                                             process.analyzeHypoKinFitMETChi10               +
                                             process.analyzeHypoKinFitMETChi15               +
                                             process.analyzeHypoKinFitMETChi30               +
                                             process.analyzeHypoKinFitMETChi50               +
                                             process.analyzeHypoKinFitJets                   +
                                             process.analyzeHypoKinFitJetsCorr               +
                                             process.analyzeHypoKinFitJetsChi5               +
                                             process.analyzeHypoKinFitJetsChi10              +
                                             process.analyzeHypoKinFitJetsChi15              +
                                             process.analyzeHypoKinFitJetsChi30              +
                                             process.analyzeHypoKinFitJetsChi50              +
                                             process.filterMatchKinFit
                                             )
            process.kinFitGen           = cms.Sequence(process.analyzeTopPartonLevelKinematics          )
            process.kinFitGenPhaseSpace = cms.Sequence(process.analyzeTopPartonLevelKinematicsPhaseSpace)
            process.kinFitGenPhaseSpaceHad = cms.Sequence(process.analyzeTopHadronLevelKinematicsPhaseSpace)
        ## case 1b): other MC
        else:
            process.kinFit    = cms.Sequence(process.makeTtSemiLepEvent                      +
                                             process.filterRecoKinFit                        +
                                             process.analyzeTopRecoKinematicsKinFitBeforeProbSel+
                                             process.filterProbKinFit                        +
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
                                         process.filterProbKinFit                        +
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

process.eventWeightPU        = process.eventWeightPU.clone()
process.eventWeightPUsysUp   = process.eventWeightPU.clone()
process.eventWeightPUsysDown = process.eventWeightPU.clone()

#### Configuration for Nominal PU Weights

process.eventWeightPU.WeightName          = "eventWeightPU"
process.eventWeightPU.Weight3DName        = "eventWeightPU3D"
process.eventWeightPU.DataFile            = "TopAnalysis/TopUtils/data/Data_PUDist_2011Full.root"
process.eventWeightPU.Data3DFile          = "TopAnalysis/TopUtils/data/Data_PUDist_2011Full.root"

process.eventWeightPU.CreateWeight3DHisto = False
process.eventWeightPU.Weight3DHistoFile   = "TopAnalysis/TopUtils/data/DefaultWeight3D.root"

#### Configuration for PU Up Variations

process.eventWeightPUsysUp.WeightName          = "eventWeightPUUp"
process.eventWeightPUsysUp.Weight3DName        = "eventWeightPU3DUp"
process.eventWeightPUsysUp.DataFile            = "TopAnalysis/TopUtils/data/Data_PUDist_sysUp_2011Full.root"
process.eventWeightPUsysUp.Data3DFile          = "TopAnalysis/TopUtils/data/Data_PUDist_sysUp_2011Full.root"

process.eventWeightPUsysUp.CreateWeight3DHisto = False
process.eventWeightPUsysUp.Weight3DHistoFile   = "TopAnalysis/TopUtils/data/DefaultWeight3DUp.root"

#### Configuration for PU Down Variations

process.eventWeightPUsysDown.WeightName          = "eventWeightPUDown"
process.eventWeightPUsysDown.Weight3DName        = "eventWeightPU3DDown"
process.eventWeightPUsysDown.DataFile            = "TopAnalysis/TopUtils/data/Data_PUDist_sysDown_2011Full.root"
process.eventWeightPUsysDown.Data3DFile          = "TopAnalysis/TopUtils/data/Data_PUDist_sysDown_2011Full.root"

process.eventWeightPUsysDown.CreateWeight3DHisto = False
process.eventWeightPUsysDown.Weight3DHistoFile   = "TopAnalysis/TopUtils/data/DefaultWeight3DDown.root"

process.makeEventWeightsPU = cms.Sequence(process.eventWeightPU        *
                                          process.eventWeightPUsysUp   *
                                          process.eventWeightPUsysDown  )

# relevant PU event weights (potentially merged with shape distortion weights)
PUweightraw     = cms.InputTag("eventWeightPU",       "eventWeightPU")
PUweightrawUp   = cms.InputTag("eventWeightPUsysUp",  "eventWeightPUUp")
PUweightrawDown = cms.InputTag("eventWeightPUsysDown","eventWeightPUDown")

## ---
##    MC ttbar systematic variation reweighting
## ---
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
    PUweight    =cms.InputTag("eventWeightPU",       "eventWeightPU")
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
process.bTagSFEventWeight.jets=cms.InputTag("tightLeadingPFJets")
process.bTagSFEventWeight.bTagAlgo=cms.string("SSVHEM")
process.bTagSFEventWeight.sysVar   = cms.string("") # bTagSFUp, bTagSFDown, misTagSFUp, misTagSFDown, 
                                                    # bTagSFShapeUpPt, bTagSFShapeDownPt, bTagSFShapeUpEta, bTagSFShapeDownEta possible;
process.bTagSFEventWeight.filename= cms.string("../../../../Configuration/data/analyzeBTagEfficiency.root")
process.bTagSFEventWeight.verbose=cms.int32(0)

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
process.effSFMuonEventWeight.filename= cms.string("../../../../Configuration/data/efficiencyIsoMu17Combined_tapTrigger_SF_Eta.root")
process.effSFMuonEventWeight.verbose=cms.int32(0)
process.effSFMuonEventWeight.additionalFactor=0.9990 ## lepton selection eff. SF
process.effSFMuonEventWeight.additionalFactorErr=0.03 ## 3% sys error to account for selection difference Z - ttbar
process.effSFMuonEventWeight.meanTriggerEffSF=0.9905
process.effSFMuonEventWeight.shapeDistortionFactor=0.5

process.effSFMuonEventWeightFlatTriggerSF            = process.effSFMuonEventWeight.clone(sysVar = "flatTriggerSF")
process.effSFMuonEventWeightTriggerEffSFNormUp       = process.effSFMuonEventWeight.clone(sysVar = "triggerEffSFNormUp")
process.effSFMuonEventWeightTriggerEffSFNormDown     = process.effSFMuonEventWeight.clone(sysVar = "triggerEffSFNormDown")
process.effSFMuonEventWeightTriggerEffSFShapeUpEta   = process.effSFMuonEventWeight.clone(sysVar = "triggerEffSFShapeUpEta")
process.effSFMuonEventWeightTriggerEffSFShapeDownEta = process.effSFMuonEventWeight.clone(sysVar = "triggerEffSFShapeDownEta")
process.effSFMuonEventWeightTriggerEffSFShapeUpPt    = process.effSFMuonEventWeight.clone(sysVar = "triggerEffSFShapeUpPt")
process.effSFMuonEventWeightTriggerEffSFShapeDownPt  = process.effSFMuonEventWeight.clone(sysVar = "triggerEffSFShapeDownPt")
process.effSFMuonEventWeightTriggerEffSFShapeUpPt40  = process.effSFMuonEventWeight.clone(sysVar = "triggerEffSFShapeUpPt",   shapeVarPtThreshold=40.0)
process.effSFMuonEventWeightTriggerEffSFShapeDownPt40= process.effSFMuonEventWeight.clone(sysVar = "triggerEffSFShapeDownPt", shapeVarPtThreshold=40.0)
process.effSFMuonEventWeightSelectionEffSFNormUp     = process.effSFMuonEventWeight.clone(sysVar = "selectionEffSFNormUp")
process.effSFMuonEventWeightSelectionEffSFNormDown   = process.effSFMuonEventWeight.clone(sysVar = "selectionEffSFNormDown")

process.load("TopAnalysis.TopUtils.EffSFElectronEventWeight_cfi")
process.effSFElectronEventWeight.particles=cms.InputTag("goodElectronsEJ")
process.effSFElectronEventWeight.sysVar   = cms.string("")
process.effSFElectronEventWeight.verbose=cms.int32(0)
process.effSFElectronEventWeight.additionalFactor=1. ## lepton selection eff. SF
process.effSFElectronEventWeight.additionalFactorErr=0.03 ## 3% sys error to account for selection difference Z - ttbar
process.effSFElectronEventWeight.meanTriggerEffSF=1.
process.effSFElectronEventWeight.meanTriggerEffSFErr=0.01
process.effSFElectronEventWeight.shapeDistortionFactor=2.

process.effSFElectronEventWeightFlatTriggerSF            = process.effSFElectronEventWeight.clone(sysVar = "flatTriggerSF")
process.effSFElectronEventWeightTriggerEffSFNormUp       = process.effSFElectronEventWeight.clone(sysVar = "triggerEffSFNormUp")
process.effSFElectronEventWeightTriggerEffSFNormDown     = process.effSFElectronEventWeight.clone(sysVar = "triggerEffSFNormDown")
process.effSFElectronEventWeightTriggerEffSFShapeUpEta   = process.effSFElectronEventWeight.clone(sysVar = "triggerEffSFShapeUpEta")
process.effSFElectronEventWeightTriggerEffSFShapeDownEta = process.effSFElectronEventWeight.clone(sysVar = "triggerEffSFShapeDownEta")
process.effSFElectronEventWeightTriggerEffSFShapeUpPt    = process.effSFElectronEventWeight.clone(sysVar = "triggerEffSFShapeUpPt")
process.effSFElectronEventWeightTriggerEffSFShapeDownPt  = process.effSFElectronEventWeight.clone(sysVar = "triggerEffSFShapeDownPt")
process.effSFElectronEventWeightTriggerEffSFShapeUpPt40  = process.effSFElectronEventWeight.clone(sysVar = "triggerEffSFShapeUpPt", shapeVarPtThreshold=40.)
process.effSFElectronEventWeightTriggerEffSFShapeDownPt40= process.effSFElectronEventWeight.clone(sysVar = "triggerEffSFShapeDownPt", shapeVarPtThreshold=40.)
process.effSFElectronEventWeightSelectionEffSFNormUp     = process.effSFElectronEventWeight.clone(sysVar = "selectionEffSFNormUp")
process.effSFElectronEventWeightSelectionEffSFNormDown   = process.effSFElectronEventWeight.clone(sysVar = "selectionEffSFNormDown")

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
    weightlistPUup                     .append("effSFMuonEventWeight")
    weightlistPUdown                   .append("effSFMuonEventWeight")
    weightlistFlatTriggerSF            .append("effSFMuonEventWeightFlatTriggerSF")
    weightlistTriggerEffSFNormUp       .append("effSFMuonEventWeightTriggerEffSFNormUp")
    weightlistTriggerEffSFNormDown     .append("effSFMuonEventWeightTriggerEffSFNormDown")
    weightlistTriggerEffSFShapeUpEta   .append("effSFMuonEventWeightTriggerEffSFShapeUpEta")
    weightlistTriggerEffSFShapeDownEta .append("effSFMuonEventWeightTriggerEffSFShapeDownEta")
    weightlistTriggerEffSFShapeUpPt    .append("effSFMuonEventWeightTriggerEffSFShapeUpPt")
    weightlistTriggerEffSFShapeDownPt  .append("effSFMuonEventWeightTriggerEffSFShapeDownPt")
    weightlistTriggerEffSFShapeUpPt40  .append("effSFMuonEventWeightTriggerEffSFShapeUpPt40")
    weightlistTriggerEffSFShapeDownPt40.append("effSFMuonEventWeightTriggerEffSFShapeDownPt40")
    weightlistSelectionEffSFNormUp     .append("effSFMuonEventWeightSelectionEffSFNormUp")
    weightlistSelectionEffSFNormDown   .append("effSFMuonEventWeightSelectionEffSFNormDown")
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
    weightlistPUup                     .append("effSFElectronEventWeight")
    weightlistPUdown                   .append("effSFElectronEventWeight")
    weightlistFlatTriggerSF            .append("effSFElectronEventWeightFlatTriggerSF")
    weightlistTriggerEffSFNormUp       .append("effSFElectronEventWeightTriggerEffSFNormUp")
    weightlistTriggerEffSFNormDown     .append("effSFElectronEventWeightTriggerEffSFNormDown")
    weightlistTriggerEffSFShapeUpEta   .append("effSFElectronEventWeightTriggerEffSFShapeUpEta")
    weightlistTriggerEffSFShapeDownEta .append("effSFElectronEventWeightTriggerEffSFShapeDownEta")
    weightlistTriggerEffSFShapeUpPt    .append("effSFElectronEventWeightTriggerEffSFShapeUpPt")
    weightlistTriggerEffSFShapeDownPt  .append("effSFElectronEventWeightTriggerEffSFShapeDownPt")
    weightlistTriggerEffSFShapeUpPt40  .append("effSFElectronEventWeightTriggerEffSFShapeUpPt40")
    weightlistTriggerEffSFShapeDownPt40.append("effSFElectronEventWeightTriggerEffSFShapeDownPt40")
    weightlistSelectionEffSFNormUp     .append("effSFElectronEventWeightSelectionEffSFNormUp")
    weightlistSelectionEffSFNormDown   .append("effSFElectronEventWeightSelectionEffSFNormDown")
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
        print "All reco-modules will use PU event weights"
    if(effSFReweigthing):
        print "All reco-modules will use eff SF event weights"
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
    print "The following reco-modules will use additionally the b-tag event weights:"
    print btagModules1
    print btagModules2
    print btagModules3
    # 'eventWeightFinal' combines the correct combination of 'PUreweigthing' and 'effSFReweigthing' with the b-tag SF
    for module1 in btagModules1:
        getattr(process,module1).weight=cms.InputTag("eventWeightFinal")
    for module2 in btagModules2:
        getattr(process,module2).weight=cms.InputTag("eventWeightFinal")
    for module3 in btagModules3:
        getattr(process,module3).weight=cms.InputTag("eventWeightFinal")
    print
        
# d) Re-weighting of gen-modules - PU reweighting only
if(runningOnData=="MC" and PUreweigthing):
    print
    print "The following gen-modules will only use the PU reweighting:"
    print genModules1
    print genModules2
    for module1 in genModules1:
        getattr(process,module1).weight=PUweight
    for module2 in genModules2:
        getattr(process,module2).weight=PUweight
    genModules3 = process.kinFitGenPhaseSpaceHad.moduleNames()
    print genModules3
    for module3 in genModules3:
        getattr(process,module3).weight=PUweight
    genModules4 = process.hadLvObjectMonitoring.moduleNames()
    print genModules3
    for module4 in genModules4:
        getattr(process,module4).weight=PUweight
    if(additionalEventWeights and eventFilter=='signal only'):
        print "those gen modules are also cloned in order to also use NoPU, PUup and PUdown event weights "
        process.analyzeTopPartonLevelKinematicsNoPUWeight           = process.analyzeTopPartonLevelKinematics.clone(weight="")
	process.analyzeTopPartonLevelKinematicsPhaseSpaceNoPUWeight = process.analyzeTopPartonLevelKinematicsPhaseSpace.clone(weight="")
        process.analyzeTopHadronLevelKinematicsPhaseSpaceNoPUWeight = process.analyzeTopHadronLevelKinematicsPhaseSpace.clone(weight="")
	process.analyzeTopPartonLevelKinematicsPUup = process.analyzeTopPartonLevelKinematics.clone(weight=PUweightUp)
	process.analyzeTopPartonLevelKinematicsPhaseSpacePUup = process.analyzeTopPartonLevelKinematicsPhaseSpace.clone(weight=PUweightUp)
        process.analyzeTopHadronLevelKinematicsPhaseSpacePUup = process.analyzeTopHadronLevelKinematicsPhaseSpace.clone(weight=PUweightUp)
	process.analyzeTopPartonLevelKinematicsPUdown = process.analyzeTopPartonLevelKinematics.clone(weight=PUweightDown)
	process.analyzeTopPartonLevelKinematicsPhaseSpacePUdown = process.analyzeTopPartonLevelKinematicsPhaseSpace.clone(weight=PUweightDown)
      	process.analyzeTopHadronLevelKinematicsPhaseSpacePUdown = process.analyzeTopHadronLevelKinematicsPhaseSpace.clone(weight=PUweightDown)
        process.kinFitGen           *= (process.analyzeTopPartonLevelKinematicsNoPUWeight *
					process.analyzeTopPartonLevelKinematicsPUup       *
					process.analyzeTopPartonLevelKinematicsPUdown)
	process.kinFitGenPhaseSpace *= (process.analyzeTopPartonLevelKinematicsPhaseSpaceNoPUWeight *
	                                process.analyzeTopPartonLevelKinematicsPhaseSpacePUup       *
			                process.analyzeTopPartonLevelKinematicsPhaseSpacePUdown)
        process.kinFitGenPhaseSpaceHad *= (process.analyzeTopHadronLevelKinematicsPhaseSpaceNoPUWeight *
                                           process.analyzeTopHadronLevelKinematicsPhaseSpacePUup       *
                                           process.analyzeTopHadronLevelKinematicsPhaseSpacePUdown)
elif(runningOnData=="MC" and not PUreweigthing):
    for module1 in genModules1:
        getattr(process,module1).weight=cms.InputTag("")
    for module2 in genModules2:
        getattr(process,module2).weight=cms.InputTag("")
    for module3 in genModules3:
        getattr(process,module3).weight=cms.InputTag("")
    for module4 in genModules4:
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
    ## no weight at all
    process.analyzeTopRecoKinematicsKinFitNoWeight           = process.analyzeTopRecoKinematicsKinFit.clone(weight="")
    process.analyzeTopRecoKinematicsKinFitTopAntitopNoWeight = process.analyzeTopRecoKinematicsKinFitTopAntitop.clone(weight="")
    process.analyzeTopRecoKinematicsKinFitTopAntitopNoWeight.analyze.useTree = False
    process.analyzeTopRecoKinematicsKinFitNoWeight.analyze.useTree           = False

    ## only PU weight
    if(PUreweigthing):
        process.analyzeTopRecoKinematicsKinFitOnlyPUWeight           = process.analyzeTopRecoKinematicsKinFit.clone(weight=PUweight)
        process.analyzeTopRecoKinematicsKinFitTopAntitopOnlyPUWeight = process.analyzeTopRecoKinematicsKinFitTopAntitop.clone(weight=PUweight)
    elif(not PUreweigthing):
        process.analyzeTopRecoKinematicsKinFitOnlyPUWeight           = process.analyzeTopRecoKinematicsKinFit.clone(weight="")
        process.analyzeTopRecoKinematicsKinFitTopAntitopOnlyPUWeight = process.analyzeTopRecoKinematicsKinFitTopAntitop.clone(weight="")
    process.analyzeTopRecoKinematicsKinFitTopAntitopOnlyPUWeight.analyze.useTree = False
    process.analyzeTopRecoKinematicsKinFitOnlyPUWeight.analyze.useTree           = False
    
    ## no btag SF weight
    if(PUreweigthing or effSFReweigthing):
        process.analyzeTopRecoKinematicsKinFitNoBtagSFWeight           = process.analyzeTopRecoKinematicsKinFit.clone(weight="eventWeightNoBtagSFWeight")
        process.analyzeTopRecoKinematicsKinFitTopAntitopNoBtagSFWeight = process.analyzeTopRecoKinematicsKinFitTopAntitop.clone(weight="eventWeightNoBtagSFWeight")
    else:
        process.analyzeTopRecoKinematicsKinFitNoBtagSFWeight           = process.analyzeTopRecoKinematicsKinFit.clone(weight="")
        process.analyzeTopRecoKinematicsKinFitTopAntitopNoBtagSFWeight = process.analyzeTopRecoKinematicsKinFitTopAntitop.clone(weight="")
    process.analyzeTopRecoKinematicsKinFitTopAntitopNoBtagSFWeight.analyze.useTree = False
    process.analyzeTopRecoKinematicsKinFitNoBtagSFWeight.analyze.useTree           = False

    ## PU up
    if(PUreweigthing):
        process.analyzeTopRecoKinematicsKinFitPUup           = process.analyzeTopRecoKinematicsKinFit.clone(weight="eventWeightPUup")
        process.analyzeTopRecoKinematicsKinFitTopAntitopPUup = process.analyzeTopRecoKinematicsKinFitTopAntitop.clone(weight="eventWeightPUup")
    elif(not PUreweigthing):
        process.analyzeTopRecoKinematicsKinFitPUup           = process.analyzeTopRecoKinematicsKinFit.clone(weight="")
        process.analyzeTopRecoKinematicsKinFitTopAntitopPUup = process.analyzeTopRecoKinematicsKinFitTopAntitop.clone(weight="")       
    process.analyzeTopRecoKinematicsKinFitTopAntitopPUup.analyze.useTree = False
    process.analyzeTopRecoKinematicsKinFitPUup.analyze.useTree           = False
    
    ## PU down
    if(PUreweigthing):
        process.analyzeTopRecoKinematicsKinFitPUdown           = process.analyzeTopRecoKinematicsKinFit.clone(weight="eventWeightPUdown")
        process.analyzeTopRecoKinematicsKinFitTopAntitopPUdown = process.analyzeTopRecoKinematicsKinFitTopAntitop.clone(weight="eventWeightPUdown")
    elif(not PUreweigthing):
        process.analyzeTopRecoKinematicsKinFitPUdown           = process.analyzeTopRecoKinematicsKinFit.clone(weight="")
        process.analyzeTopRecoKinematicsKinFitTopAntitopPUdown = process.analyzeTopRecoKinematicsKinFitTopAntitop.clone(weight="")  
    process.analyzeTopRecoKinematicsKinFitTopAntitopPUdown.analyze.useTree = False
    process.analyzeTopRecoKinematicsKinFitPUdown.analyze.useTree           = False

    ## flat trigger Eff SF weight
    process.analyzeTopRecoKinematicsKinFitFlatTriggerSF           = process.analyzeTopRecoKinematicsKinFit.clone(weight="eventWeightFlatTriggerSF")
    process.analyzeTopRecoKinematicsKinFitTopAntitopFlatTriggerSF = process.analyzeTopRecoKinematicsKinFitTopAntitop.clone(weight="eventWeightFlatTriggerSF")
    process.analyzeTopRecoKinematicsKinFitTopAntitopFlatTriggerSF.analyze.useTree = False
    process.analyzeTopRecoKinematicsKinFitFlatTriggerSF.analyze.useTree           = False

    ## TriggerEffSFNormUp
    process.analyzeTopRecoKinematicsKinFitTriggerEffSFNormUp           = process.analyzeTopRecoKinematicsKinFit.clone(weight="eventWeightTriggerEffSFNormUp")
    process.analyzeTopRecoKinematicsKinFitTopAntitopTriggerEffSFNormUp = process.analyzeTopRecoKinematicsKinFitTopAntitop.clone(weight="eventWeightTriggerEffSFNormUp")
    process.analyzeTopRecoKinematicsKinFitTopAntitopTriggerEffSFNormUp.analyze.useTree = False
    process.analyzeTopRecoKinematicsKinFitTriggerEffSFNormUp.analyze.useTree           = False

    ## TriggerEffSFNormDown
    process.analyzeTopRecoKinematicsKinFitTriggerEffSFNormDown           = process.analyzeTopRecoKinematicsKinFit.clone(weight="eventWeightTriggerEffSFNormDown")
    process.analyzeTopRecoKinematicsKinFitTopAntitopTriggerEffSFNormDown = process.analyzeTopRecoKinematicsKinFitTopAntitop.clone(weight="eventWeightTriggerEffSFNormDown")
    process.analyzeTopRecoKinematicsKinFitTopAntitopTriggerEffSFNormDown.analyze.useTree = False
    process.analyzeTopRecoKinematicsKinFitTriggerEffSFNormDown.analyze.useTree           = False

    ## TriggerEffSFShapeUpEta
    process.analyzeTopRecoKinematicsKinFitTriggerEffSFShapeUpEta           = process.analyzeTopRecoKinematicsKinFit.clone(weight="eventWeightTriggerEffSFShapeUpEta")
    process.analyzeTopRecoKinematicsKinFitTopAntitopTriggerEffSFShapeUpEta = process.analyzeTopRecoKinematicsKinFitTopAntitop.clone(weight="eventWeightTriggerEffSFShapeUpEta")
    process.analyzeTopRecoKinematicsKinFitTopAntitopTriggerEffSFShapeUpEta.analyze.useTree = False
    process.analyzeTopRecoKinematicsKinFitTriggerEffSFShapeUpEta.analyze.useTree           = False

    ## TriggerEffSFShapeDownEta
    process.analyzeTopRecoKinematicsKinFitTriggerEffSFShapeDownEta           = process.analyzeTopRecoKinematicsKinFit.clone(weight="eventWeightTriggerEffSFShapeDownEta")
    process.analyzeTopRecoKinematicsKinFitTopAntitopTriggerEffSFShapeDownEta = process.analyzeTopRecoKinematicsKinFitTopAntitop.clone(weight="eventWeightTriggerEffSFShapeDownEta")
    process.analyzeTopRecoKinematicsKinFitTopAntitopTriggerEffSFShapeDownEta.analyze.useTree = False
    process.analyzeTopRecoKinematicsKinFitTriggerEffSFShapeDownEta.analyze.useTree           = False
    
    ## TriggerEffSFShapeUpPt
    process.analyzeTopRecoKinematicsKinFitTriggerEffSFShapeUpPt           = process.analyzeTopRecoKinematicsKinFit.clone(weight="eventWeightTriggerEffSFShapeUpPt")
    process.analyzeTopRecoKinematicsKinFitTopAntitopTriggerEffSFShapeUpPt = process.analyzeTopRecoKinematicsKinFitTopAntitop.clone(weight="eventWeightTriggerEffSFShapeUpPt")
    process.analyzeTopRecoKinematicsKinFitTopAntitopTriggerEffSFShapeUpPt.analyze.useTree = False
    process.analyzeTopRecoKinematicsKinFitTriggerEffSFShapeUpPt.analyze.useTree           = False
    
    ## TriggerEffSFShapeDownPt
    process.analyzeTopRecoKinematicsKinFitTriggerEffSFShapeDownPt           = process.analyzeTopRecoKinematicsKinFit.clone(weight="eventWeightTriggerEffSFShapeDownPt")
    process.analyzeTopRecoKinematicsKinFitTopAntitopTriggerEffSFShapeDownPt = process.analyzeTopRecoKinematicsKinFitTopAntitop.clone(weight="eventWeightTriggerEffSFShapeDownPt")
    process.analyzeTopRecoKinematicsKinFitTopAntitopTriggerEffSFShapeDownPt.analyze.useTree = False
    process.analyzeTopRecoKinematicsKinFitTriggerEffSFShapeDownPt.analyze.useTree           = False
    
    ## TriggerEffSFShapeUpPt40
    process.analyzeTopRecoKinematicsKinFitTriggerEffSFShapeUpPt40           = process.analyzeTopRecoKinematicsKinFit.clone(weight="eventWeightTriggerEffSFShapeUpPt40")
    process.analyzeTopRecoKinematicsKinFitTopAntitoPt40riggerEffSFShapeUpPt40 = process.analyzeTopRecoKinematicsKinFitTopAntitop.clone(weight="eventWeightTriggerEffSFShapeUpPt40")
    process.analyzeTopRecoKinematicsKinFitTopAntitoPt40riggerEffSFShapeUpPt40.analyze.useTree = False
    process.analyzeTopRecoKinematicsKinFitTriggerEffSFShapeUpPt40.analyze.useTree           = False
    
    ## TriggerEffSFShapeDownPt40
    process.analyzeTopRecoKinematicsKinFitTriggerEffSFShapeDownPt40           = process.analyzeTopRecoKinematicsKinFit.clone(weight="eventWeightTriggerEffSFShapeDownPt40")
    process.analyzeTopRecoKinematicsKinFitTopAntitoPt40riggerEffSFShapeDownPt40 = process.analyzeTopRecoKinematicsKinFitTopAntitop.clone(weight="eventWeightTriggerEffSFShapeDownPt40")
    process.analyzeTopRecoKinematicsKinFitTopAntitoPt40riggerEffSFShapeDownPt40.analyze.useTree = False
    process.analyzeTopRecoKinematicsKinFitTriggerEffSFShapeDownPt40.analyze.useTree           = False

    ## SelectionEffSFNormUp
    process.analyzeTopRecoKinematicsKinFitSelectionEffSFNormUp           = process.analyzeTopRecoKinematicsKinFit.clone(weight="eventWeightSelectionEffSFNormUp")
    process.analyzeTopRecoKinematicsKinFitTopAntitopSelectionEffSFNormUp = process.analyzeTopRecoKinematicsKinFitTopAntitop.clone(weight="eventWeightSelectionEffSFNormUp")
    process.analyzeTopRecoKinematicsKinFitTopAntitopSelectionEffSFNormUp.analyze.useTree = False
    process.analyzeTopRecoKinematicsKinFitSelectionEffSFNormUp.analyze.useTree           = False

    ## SelectionEffSFNormDown
    process.analyzeTopRecoKinematicsKinFitSelectionEffSFNormDown           = process.analyzeTopRecoKinematicsKinFit.clone(weight="eventWeightSelectionEffSFNormDown")
    process.analyzeTopRecoKinematicsKinFitTopAntitopSelectionEffSFNormDown = process.analyzeTopRecoKinematicsKinFitTopAntitop.clone(weight="eventWeightSelectionEffSFNormDown")
    process.analyzeTopRecoKinematicsKinFitTopAntitopSelectionEffSFNormDown.analyze.useTree = False
    process.analyzeTopRecoKinematicsKinFitSelectionEffSFNormDown.analyze.useTree           = False

    ## BtagSFup
    process.analyzeTopRecoKinematicsKinFitBtagSFup           = process.analyzeTopRecoKinematicsKinFit.clone(weight="eventWeightBtagSFup")
    process.analyzeTopRecoKinematicsKinFitTopAntitopBtagSFup = process.analyzeTopRecoKinematicsKinFitTopAntitop.clone(weight="eventWeightBtagSFup")
    process.analyzeTopRecoKinematicsKinFitTopAntitopBtagSFup.analyze.useTree = False
    process.analyzeTopRecoKinematicsKinFitBtagSFup.analyze.useTree           = False

    ## BtagSFdown
    process.analyzeTopRecoKinematicsKinFitBtagSFdown           = process.analyzeTopRecoKinematicsKinFit.clone(weight="eventWeightBtagSFdown")
    process.analyzeTopRecoKinematicsKinFitTopAntitopBtagSFdown = process.analyzeTopRecoKinematicsKinFitTopAntitop.clone(weight="eventWeightBtagSFdown")
    process.analyzeTopRecoKinematicsKinFitTopAntitopBtagSFdown.analyze.useTree = False
    process.analyzeTopRecoKinematicsKinFitBtagSFdown.analyze.useTree           = False

    ## MisTagSFup
    process.analyzeTopRecoKinematicsKinFitMisTagSFup           = process.analyzeTopRecoKinematicsKinFit.clone(weight="eventWeightMisTagSFup")
    process.analyzeTopRecoKinematicsKinFitTopAntitopMisTagSFup = process.analyzeTopRecoKinematicsKinFitTopAntitop.clone(weight="eventWeightMisTagSFup")
    process.analyzeTopRecoKinematicsKinFitTopAntitopMisTagSFup.analyze.useTree = False
    process.analyzeTopRecoKinematicsKinFitMisTagSFup.analyze.useTree           = False

    ## MisTagSFdown
    process.analyzeTopRecoKinematicsKinFitMisTagSFdown           = process.analyzeTopRecoKinematicsKinFit.clone(weight="eventWeightMisTagSFdown")
    process.analyzeTopRecoKinematicsKinFitTopAntitopMisTagSFdown = process.analyzeTopRecoKinematicsKinFitTopAntitop.clone(weight="eventWeightMisTagSFdown")
    process.analyzeTopRecoKinematicsKinFitTopAntitopMisTagSFdown.analyze.useTree = False
    process.analyzeTopRecoKinematicsKinFitMisTagSFdown.analyze.useTree           = False
    
    ## BTagSFShapeUpPt65
    process.analyzeTopRecoKinematicsKinFitBTagSFShapeUpPt65           = process.analyzeTopRecoKinematicsKinFit.clone(weight="eventWeightBTagSFShapeUpPt65")
    process.analyzeTopRecoKinematicsKinFitTopAntitopBTagSFShapeUpPt65 = process.analyzeTopRecoKinematicsKinFitTopAntitop.clone(weight="eventWeightBTagSFShapeUpPt65")
    process.analyzeTopRecoKinematicsKinFitTopAntitopBTagSFShapeUpPt65.analyze.useTree = False
    process.analyzeTopRecoKinematicsKinFitBTagSFShapeUpPt65.analyze.useTree           = False
    
    ## BTagSFShapeDownPt65
    process.analyzeTopRecoKinematicsKinFitBTagSFShapeDownPt65           = process.analyzeTopRecoKinematicsKinFit.clone(weight="eventWeightBTagSFShapeDownPt65")
    process.analyzeTopRecoKinematicsKinFitTopAntitopBTagSFShapeDownPt65 = process.analyzeTopRecoKinematicsKinFitTopAntitop.clone(weight="eventWeightBTagSFShapeDownPt65")
    process.analyzeTopRecoKinematicsKinFitTopAntitopBTagSFShapeDownPt65.analyze.useTree = False
    process.analyzeTopRecoKinematicsKinFitBTagSFShapeDownPt65.analyze.useTree           = False
    
    ## BTagSFShapeUpEta1p2
    process.analyzeTopRecoKinematicsKinFitBTagSFShapeUpEta1p2           = process.analyzeTopRecoKinematicsKinFit.clone(weight="eventWeightBTagSFShapeUpEta1p2")
    process.analyzeTopRecoKinematicsKinFitTopAntitopBTagSFShapeUpEta1p2 = process.analyzeTopRecoKinematicsKinFitTopAntitop.clone(weight="eventWeightBTagSFShapeUpEta1p2")
    process.analyzeTopRecoKinematicsKinFitTopAntitopBTagSFShapeUpEta1p2.analyze.useTree = False
    process.analyzeTopRecoKinematicsKinFitBTagSFShapeUpEta1p2.analyze.useTree           = False
    
    ## BTagSFShapeDownEta1p2
    process.analyzeTopRecoKinematicsKinFitBTagSFShapeDownEta1p2           = process.analyzeTopRecoKinematicsKinFit.clone(weight="eventWeightBTagSFShapeDownEta1p2")
    process.analyzeTopRecoKinematicsKinFitTopAntitopBTagSFShapeDownEta1p2 = process.analyzeTopRecoKinematicsKinFitTopAntitop.clone(weight="eventWeightBTagSFShapeDownEta1p2")
    process.analyzeTopRecoKinematicsKinFitTopAntitopBTagSFShapeDownEta1p2.analyze.useTree = False
    process.analyzeTopRecoKinematicsKinFitBTagSFShapeDownEta1p2.analyze.useTree           = False
    
    ## BTagSFHalfShapeUpPt65
    process.analyzeTopRecoKinematicsKinFitBTagSFHalfShapeUpPt65           = process.analyzeTopRecoKinematicsKinFit.clone(weight="eventWeightBTagSFHalfShapeUpPt65")
    process.analyzeTopRecoKinematicsKinFitTopAntitopBTagSFHalfShapeUpPt65 = process.analyzeTopRecoKinematicsKinFitTopAntitop.clone(weight="eventWeightBTagSFHalfShapeUpPt65")
    process.analyzeTopRecoKinematicsKinFitTopAntitopBTagSFHalfShapeUpPt65.analyze.useTree = False
    process.analyzeTopRecoKinematicsKinFitBTagSFHalfShapeUpPt65.analyze.useTree           = False
    
    ## BTagSFHalfShapeDownPt65
    process.analyzeTopRecoKinematicsKinFitBTagSFHalfShapeDownPt65           = process.analyzeTopRecoKinematicsKinFit.clone(weight="eventWeightBTagSFHalfShapeDownPt65")
    process.analyzeTopRecoKinematicsKinFitTopAntitopBTagSFHalfShapeDownPt65 = process.analyzeTopRecoKinematicsKinFitTopAntitop.clone(weight="eventWeightBTagSFHalfShapeDownPt65")
    process.analyzeTopRecoKinematicsKinFitTopAntitopBTagSFHalfShapeDownPt65.analyze.useTree = False
    process.analyzeTopRecoKinematicsKinFitBTagSFHalfShapeDownPt65.analyze.useTree           = False
    
    ## BTagSFHalfShapeUpEta0p7
    process.analyzeTopRecoKinematicsKinFitBTagSFHalfShapeUpEta0p7           = process.analyzeTopRecoKinematicsKinFit.clone(weight="eventWeightBTagSFHalfShapeUpEta0p7")
    process.analyzeTopRecoKinematicsKinFitTopAntitopBTagSFHalfShapeUpEta0p7 = process.analyzeTopRecoKinematicsKinFitTopAntitop.clone(weight="eventWeightBTagSFHalfShapeUpEta0p7")
    process.analyzeTopRecoKinematicsKinFitTopAntitopBTagSFHalfShapeUpEta0p7.analyze.useTree = False
    process.analyzeTopRecoKinematicsKinFitBTagSFHalfShapeUpEta0p7.analyze.useTree           = False
    
    ## BTagSFHalfShapeDownEta0p7
    process.analyzeTopRecoKinematicsKinFitBTagSFHalfShapeDownEta0p7           = process.analyzeTopRecoKinematicsKinFit.clone(weight="eventWeightBTagSFHalfShapeDownEta0p7")
    process.analyzeTopRecoKinematicsKinFitTopAntitopBTagSFHalfShapeDownEta0p7 = process.analyzeTopRecoKinematicsKinFitTopAntitop.clone(weight="eventWeightBTagSFHalfShapeDownEta0p7")
    process.analyzeTopRecoKinematicsKinFitTopAntitopBTagSFHalfShapeDownEta0p7.analyze.useTree = False
    process.analyzeTopRecoKinematicsKinFitBTagSFHalfShapeDownEta0p7.analyze.useTree           = False
        
    ## BTagSFShapeUpPt100
    process.analyzeTopRecoKinematicsKinFitBTagSFShapeUpPt100           = process.analyzeTopRecoKinematicsKinFit.clone(weight="eventWeightBTagSFShapeUpPt100")
    process.analyzeTopRecoKinematicsKinFitTopAntitopBTagSFShapeUpPt100 = process.analyzeTopRecoKinematicsKinFitTopAntitop.clone(weight="eventWeightBTagSFShapeUpPt100")
    process.analyzeTopRecoKinematicsKinFitTopAntitopBTagSFShapeUpPt100.analyze.useTree = False
    process.analyzeTopRecoKinematicsKinFitBTagSFShapeUpPt100.analyze.useTree           = False
    
    ## BTagSFShapeDownPt100
    process.analyzeTopRecoKinematicsKinFitBTagSFShapeDownPt100           = process.analyzeTopRecoKinematicsKinFit.clone(weight="eventWeightBTagSFShapeDownPt100")
    process.analyzeTopRecoKinematicsKinFitTopAntitopBTagSFShapeDownPt100 = process.analyzeTopRecoKinematicsKinFitTopAntitop.clone(weight="eventWeightBTagSFShapeDownPt100")
    process.analyzeTopRecoKinematicsKinFitTopAntitopBTagSFShapeDownPt100.analyze.useTree = False
    process.analyzeTopRecoKinematicsKinFitBTagSFShapeDownPt100.analyze.useTree           = False
    
    ## BTagSFShapeUpEta0p7
    process.analyzeTopRecoKinematicsKinFitBTagSFShapeUpEta0p7           = process.analyzeTopRecoKinematicsKinFit.clone(weight="eventWeightBTagSFShapeUpEta0p7")
    process.analyzeTopRecoKinematicsKinFitTopAntitopBTagSFShapeUpEta0p7 = process.analyzeTopRecoKinematicsKinFitTopAntitop.clone(weight="eventWeightBTagSFShapeUpEta0p7")
    process.analyzeTopRecoKinematicsKinFitTopAntitopBTagSFShapeUpEta0p7.analyze.useTree = False
    process.analyzeTopRecoKinematicsKinFitBTagSFShapeUpEta0p7.analyze.useTree           = False
    
    ## BTagSFShapeDownEta0p7
    process.analyzeTopRecoKinematicsKinFitBTagSFShapeDownEta0p7           = process.analyzeTopRecoKinematicsKinFit.clone(weight="eventWeightBTagSFShapeDownEta0p7")
    process.analyzeTopRecoKinematicsKinFitTopAntitopBTagSFShapeDownEta0p7 = process.analyzeTopRecoKinematicsKinFitTopAntitop.clone(weight="eventWeightBTagSFShapeDownEta0p7")
    process.analyzeTopRecoKinematicsKinFitTopAntitopBTagSFShapeDownEta0p7.analyze.useTree = False
    process.analyzeTopRecoKinematicsKinFitBTagSFShapeDownEta0p7.analyze.useTree           = False

    ## add to Sequence
    if(decayChannel=="muon"):
	process.kinFit.replace(process.analyzeTopRecoKinematicsKinFit, 
                               process.analyzeTopRecoKinematicsKinFit*
                               process.effSFMuonEventWeightFlatTriggerSF*           
                               process.effSFMuonEventWeightTriggerEffSFNormUp*      
                               process.effSFMuonEventWeightTriggerEffSFNormDown*    
                               process.effSFMuonEventWeightTriggerEffSFShapeUpEta*  
                               process.effSFMuonEventWeightTriggerEffSFShapeDownEta*
                               process.effSFMuonEventWeightTriggerEffSFShapeUpPt*  
                               process.effSFMuonEventWeightTriggerEffSFShapeDownPt*
			       process.effSFMuonEventWeightTriggerEffSFShapeUpPt40*  
                               process.effSFMuonEventWeightTriggerEffSFShapeDownPt40*
                               process.effSFMuonEventWeightSelectionEffSFNormUp    *
                               process.effSFMuonEventWeightSelectionEffSFNormDown*
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
    elif(decayChannel=="electron"):
        process.kinFit.replace(process.analyzeTopRecoKinematicsKinFit, 
                               process.analyzeTopRecoKinematicsKinFit*
                               process.effSFElectronEventWeightFlatTriggerSF*           
                               process.effSFElectronEventWeightTriggerEffSFNormUp*      
                               process.effSFElectronEventWeightTriggerEffSFNormDown*    
                               process.effSFElectronEventWeightTriggerEffSFShapeUpEta*  
                               process.effSFElectronEventWeightTriggerEffSFShapeDownEta*
                               process.effSFElectronEventWeightTriggerEffSFShapeUpPt*  
                               process.effSFElectronEventWeightTriggerEffSFShapeDownPt*
			       process.effSFElectronEventWeightTriggerEffSFShapeUpPt40*  
                               process.effSFElectronEventWeightTriggerEffSFShapeDownPt40*
                               process.effSFElectronEventWeightSelectionEffSFNormUp    *
                               process.effSFElectronEventWeightSelectionEffSFNormDown*
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
    process.kinFit.replace(process.bTagSFEventWeightBTagSFShapeDownEta0p7,  
                           process.bTagSFEventWeightBTagSFShapeDownEta0p7      *			  
                           process.eventWeightPUup                    *
                           process.eventWeightPUdown                  *
                           process.eventWeightFlatTriggerSF           *
                           process.eventWeightTriggerEffSFNormUp      *
                           process.eventWeightTriggerEffSFNormDown    *
                           process.eventWeightTriggerEffSFShapeUpEta  *
                           process.eventWeightTriggerEffSFShapeDownEta*
                           process.eventWeightTriggerEffSFShapeUpPt   *
                           process.eventWeightTriggerEffSFShapeDownPt *
			   process.eventWeightTriggerEffSFShapeUpPt40   *
                           process.eventWeightTriggerEffSFShapeDownPt40 *
                           process.eventWeightSelectionEffSFNormUp    *
                           process.eventWeightSelectionEffSFNormDown  *
                           process.eventWeightBtagSFup                *
                           process.eventWeightBtagSFdown              *
                           process.eventWeightMisTagSFup              *
                           process.eventWeightMisTagSFdown             *
			   process.eventWeightBTagSFShapeUpPt65                *
                           process.eventWeightBTagSFShapeDownPt65              *
			   process.eventWeightBTagSFShapeUpEta1p2                *
                           process.eventWeightBTagSFShapeDownEta1p2              *
			   process.eventWeightBTagSFHalfShapeUpPt65                *
                           process.eventWeightBTagSFHalfShapeDownPt65              *
			   process.eventWeightBTagSFHalfShapeUpEta0p7                *
                           process.eventWeightBTagSFHalfShapeDownEta0p7              *      
			   process.eventWeightBTagSFShapeUpPt100                *
                           process.eventWeightBTagSFShapeDownPt100              *
			   process.eventWeightBTagSFShapeUpEta0p7                *
                           process.eventWeightBTagSFShapeDownEta0p7              *            
                           process.analyzeTopRecoKinematicsKinFitNoWeight *
                           #process.analyzeTopRecoKinematicsKinFitTopAntitopNoWeight * 
                           process.analyzeTopRecoKinematicsKinFitOnlyPUWeight *
                           #process.analyzeTopRecoKinematicsKinFitTopAntitopOnlyPUWeight * 
                           process.analyzeTopRecoKinematicsKinFitNoBtagSFWeight *
                           #process.analyzeTopRecoKinematicsKinFitTopAntitopNoBtagSFWeight*
                           process.analyzeTopRecoKinematicsKinFitPUup*
                           #process.analyzeTopRecoKinematicsKinFitTopAntitopPUup*
                           process.analyzeTopRecoKinematicsKinFitPUdown*
                           #process.analyzeTopRecoKinematicsKinFitTopAntitopPUdown*
                           process.analyzeTopRecoKinematicsKinFitFlatTriggerSF *
                           #process.analyzeTopRecoKinematicsKinFitTopAntitopFlatTriggerSF *
                           process.analyzeTopRecoKinematicsKinFitTriggerEffSFNormUp *
                           #process.analyzeTopRecoKinematicsKinFitTopAntitopTriggerEffSFNormUp *
                           process.analyzeTopRecoKinematicsKinFitTriggerEffSFNormDown *
                           #process.analyzeTopRecoKinematicsKinFitTopAntitopTriggerEffSFNormDown *
                           process.analyzeTopRecoKinematicsKinFitTriggerEffSFShapeUpEta *
                           #process.analyzeTopRecoKinematicsKinFitTopAntitopTriggerEffSFShapeUpEta *
                           process.analyzeTopRecoKinematicsKinFitTriggerEffSFShapeDownEta *
                           #process.analyzeTopRecoKinematicsKinFitTopAntitopTriggerEffSFShapeDownEta *
                           process.analyzeTopRecoKinematicsKinFitTriggerEffSFShapeUpPt *
                           #process.analyzeTopRecoKinematicsKinFitTopAntitopTriggerEffSFShapeUpPt *
                           process.analyzeTopRecoKinematicsKinFitTriggerEffSFShapeDownPt *
			   #process.analyzeTopRecoKinematicsKinFitTopAntitopTriggerEffSFShapeDownPt *
			   process.analyzeTopRecoKinematicsKinFitTriggerEffSFShapeUpPt40 *
			   process.analyzeTopRecoKinematicsKinFitTriggerEffSFShapeDownPt40 *
                           process.analyzeTopRecoKinematicsKinFitSelectionEffSFNormUp *
			   #process.analyzeTopRecoKinematicsKinFitTopAntitopSelectionEffSFNormUp *
                           process.analyzeTopRecoKinematicsKinFitSelectionEffSFNormDown *
			   #process.analyzeTopRecoKinematicsKinFitTopAntitopSelectionEffSFNormDown *
                           process.analyzeTopRecoKinematicsKinFitBtagSFup *
			   #process.analyzeTopRecoKinematicsKinFitTopAntitopBtagSFup *
                           process.analyzeTopRecoKinematicsKinFitBtagSFdown *
			   #process.analyzeTopRecoKinematicsKinFitTopAntitopBtagSFdown *
                           process.analyzeTopRecoKinematicsKinFitMisTagSFup *
			   #process.analyzeTopRecoKinematicsKinFitTopAntitopMisTagSFup *
                           process.analyzeTopRecoKinematicsKinFitMisTagSFdown *
			   #process.analyzeTopRecoKinematicsKinFitTopAntitopMisTagSFdown
			   process.analyzeTopRecoKinematicsKinFitBTagSFShapeUpPt65 *
                           process.analyzeTopRecoKinematicsKinFitBTagSFShapeDownPt65 *
			   process.analyzeTopRecoKinematicsKinFitBTagSFShapeUpEta1p2 *
                           process.analyzeTopRecoKinematicsKinFitBTagSFShapeDownEta1p2 *
			   #process.analyzeTopRecoKinematicsKinFitBTagSFHalfShapeUpPt65 *
			   #process.analyzeTopRecoKinematicsKinFitBTagSFHalfShapeDownPt65 *
			   #process.analyzeTopRecoKinematicsKinFitBTagSFHalfShapeUpEta0p7 *
			   #process.analyzeTopRecoKinematicsKinFitBTagSFHalfShapeDownEta0p7 *
			   process.analyzeTopRecoKinematicsKinFitBTagSFShapeUpPt100 *
                           process.analyzeTopRecoKinematicsKinFitBTagSFShapeDownPt100 *
			   process.analyzeTopRecoKinematicsKinFitBTagSFShapeUpEta0p7 *
                           process.analyzeTopRecoKinematicsKinFitBTagSFShapeDownEta0p7
                           )

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

## loose selection and monitoring of some basic distributions
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
                      ## loose selection (slightly above mu17TriCentralJet30 Trigger)
                      process.looseCuts                             *
                      ## basic monitoring
                      process.basicMonitoring
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
## switch to SSV btagging
from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
massSearchReplaceAnyInputTag(process.p1, 'tightBottomPFJets', 'simpleSecondaryVertexHighEffBJets')
process.simpleSecondaryVertexHighEffBJets.src="goodJetsPF30"
process.p1.replace(process.semiLeptonicSelection, process.semiLeptonicSelection*process.simpleSecondaryVertexHighEffBJets)

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
    if(MCversion=="Summer11"):
      process.hltFilter.HLTPaths=["HLT_Ele25_CaloIdVT_TrkIdT_CentralTriJet30_v*"]
      process.dummy.HLTPaths=["HLT_Ele25_CaloIdVT_TrkIdT_CentralTriJet30_v*"]
    elif(MCversion=="Fall11"):
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
            process.genAllElectronKinematics.weight=""
        # remove muon monitoring
        path.remove(process.tightMuontightJetsKinematics)
        path.remove(process.tightMuonKinematics)
        path.remove(process.tightMuonQuality)
        path.remove(process.tightMuontightJetsKinematicsTagged)
        path.remove(process.tightMuonKinematicsTagged         )
        path.remove(process.tightMuonQualityTagged            )
        path.remove(process.trackMuontightJetsKinematicsPreSel)
        path.remove(process.kinematicMuonQualityPreSel        )
        path.remove(process.goldenMuonQualityPreSel           )
        path.remove(process.tightMuonKinematicsPreSel         )
        path.remove(process.tightMuonQualityPreSel            )
        # add electron monitoring
        path.replace(process.tightLead_0_JetKinematics      , process.tightElectronKinematics * process.tightElectronQuality * process.tightLead_0_JetKinematics)
        path.replace(process.tightLead_0_JetKinematicsTagged, process.tightElectronKinematicsTagged * process.tightElectronQualityTagged  * process.tightLead_0_JetKinematicsTagged)
        # remove loose muon trigger based selection for muHad trigger
        path.remove(process.looseCentralJets)
        path.remove(process.kinematicMuonsSelection)
        path.remove(process.looseJetSelectionNjets3)
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
        'resolutionsVersion': 'summer11',
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
        'METCorrectionLevel': 0
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
