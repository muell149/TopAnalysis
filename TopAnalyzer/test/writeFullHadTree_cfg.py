import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing
import sys,os

# setup 'standard' options
options = VarParsing.VarParsing ('standard')
## decide whether to run on:  * data *, * sig *, * bkg *, * qcd *, * allRedigi * or * all *
options.register('eventFilter', 'data', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "kind of data to be processed")
## choose whether to use PF or not
options.register('usePF'      , True , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.bool , "use PF for processing")
## set the jet energy scale variation type (abs, jes)
options.register('jesType'  ,  'jes' , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "jet energy scale type")
## set the jet energy scale factor for MC
options.register('jesFactor'  ,  1.0 , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.float, "jet energy scale factor for MC")
## set the jet energy resolution smear factors for MC (-1,0,+1,9,10,11) (down,default,up,now down,new default, new up)
options.register('jetEResol', 10 , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "jet energy resol smear for MC")
## set the resolution fractor for the kinematic fit
options.register('fitResol'   ,  10 , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "kinFit resolution factor")
## choose whether to write output to disk or not
options.register('writeOutput', False , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.bool, "write events surviving all cuts to disk")
## setup the ptHatFilter in case 'eventFilter' is chosen to be qcd
options.register('maxPtHat', 999999., VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.float, "maxPtHat to be processed")
options.register('minPtHat', 0.     , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.float, "minPtHat to be processed")
## include PDF uncertainty histograms / tree
options.register('pdfUn'   , 1 , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "include hists/tree for pdf uncertainty")
## choose which background estimate should be done (0: no estimate, 1: b-tag weighting, 2: event mixing)
options.register('backgroundEstimation', 0 , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "decide which background estimate should be done")
## run directly on AOD, do everything on the fly
options.register('runOnAOD', False , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.bool, "run on AOD, do everything on the fly")
## which b-tag algo and WP should be used
options.register('bTagAlgoWP', 'CSVT', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "which b-tag algo and WP should be used")
## do mva selection instead of old style selection
options.register('mvaSelection', True , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.bool, "mva selection")
## weight of events (should be used only for MC samples)
options.register('mcWeight', -1.0 , VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.float, "MC sample event weight")
## which PU scenario for PU reweighting
options.register('PUscenario', '11_178078', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "PU distribution used for MC PUweight calculation")
## trigger results tag
options.register('triggerTag', 'HLT', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "tag of trigger Results")

# get and parse the command line arguments
if hasattr(sys, "argv") :
    for args in sys.argv :
        arg = args.split(',')
        for val in arg:
            val = val.split('=')
            if len(val)==2 :
                setattr(options, val[0], val[1])

print "eventFilter . . . . :", options.eventFilter
print "usePF . . . . . . . :", options.usePF
print "jesType . . . . . . :", options.jesType
print "jesFactor . . . . . :", options.jesFactor
print "jetEResol . . . . . :", options.jetEResol
print "fitResol  . . . . . :", options.fitResol
print "writeOutput . . . . :", options.writeOutput
print "maxPtHat  . . . . . :", options.maxPtHat
print "minPtHat  . . . . . :", options.minPtHat
print "pdfUncertainty  . . :", options.pdfUn
print "backgroundEstimation:", options.backgroundEstimation
print "runOnAOD  . . . . . :", options.runOnAOD
print "bTagAlgoWP  . . . . :", options.bTagAlgoWP
print "mvaSelection  . . . :", options.mvaSelection
print "mcWeight  . . . . . :", options.mcWeight
print "PUscenario  . . . . :", options.PUscenario
print "triggerTag  . . . . :", options.triggerTag

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
        #'file:patTuple_selected.root',
        #'file:/tmp/eschliec/tmp.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_100_1_tD3.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_102_1_Ckt.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_103_1_ZEY.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_105_1_DLF.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_106_1_RH3.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_107_1_zib.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_108_1_Frn.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_101_1_zkj.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_111_1_6Ki.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_104_1_4ye.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_109_1_gDj.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_114_1_HuE.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_10_1_fFx.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_110_1_A49.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_117_1_QwS.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_118_1_4wm.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_11_1_yCb.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_12_3_XC1.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_13_1_MZO.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_112_1_s3Z.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_113_1_QbL.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_16_1_UNX.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_17_1_CYE.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_115_2_SbK.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_19_8_F3X.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_116_1_lym.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_14_1_U4g.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_21_1_Mqx.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_15_1_24A.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_23_3_kFA.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_24_1_h10.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_18_3_Hl0.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_1_1_xVJ.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_27_1_32t.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_28_1_0hk.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_20_3_JQc.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_22_1_7fL.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_25_8_8Gk.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_31_1_Z15.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_26_1_kgC.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_29_1_2kq.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_34_2_eSt.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_2_1_lLz.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_36_1_9aN.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_37_1_3mZ.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_30_1_tiw.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_39_1_Cne.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_3_1_RCs.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_32_1_gQ7.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_41_1_n72.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_33_1_rUu.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_43_1_L2e.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_35_1_tnB.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_38_1_Bw3.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_40_3_0yO.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_42_1_zxh.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_48_1_PRK.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_44_1_x5M.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_45_1_Ky0.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_50_1_zra.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_46_1_XgK.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_52_1_lAm.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_53_1_TMH.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_54_1_xmE.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_55_1_dv5.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_56_1_0WT.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_57_1_pWz.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_47_1_K9G.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_59_1_mL2.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_5_1_k6m.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_60_3_rJv.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_61_3_ixs.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_62_1_8Hq.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_49_1_wEn.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_64_1_Drj.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_65_1_AW8.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_4_1_MFu.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_51_1_3N9.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_68_1_43r.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_58_1_AaL.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_6_3_rnn.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_70_1_Lap.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_71_1_ihL.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_63_3_KeJ.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_73_1_8Qo.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_74_1_Wyu.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_66_1_ylZ.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_76_1_L9v.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_67_1_a1n.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_69_1_HEx.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_79_1_nCY.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_7_1_y8Z.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_80_1_804.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_81_1_i6b.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_72_1_6SA.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_83_3_4LK.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_84_1_UGb.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_85_1_SQL.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_75_1_ZCk.root',
        #'/store/user/eschliec/MultiJet/Run2011B_v11_PATWithPF_v4/6a10ecb4d7010b1a5a33c1afedbebe5b/patTuple_87_1_str.root',
        #'/store/user/eschliec/MultiJet/Run2011A_v42_PATWithPF_v4/9610e89f650df43cf8a89da2e1021a9c/patTuple_9_1_LMr.root',
        #'/store/user/eschliec/MultiJet/Run2011A_v42_PATWithPF_v4/9610e89f650df43cf8a89da2e1021a9c/patTuple_8_1_OjE.root',
        #'/store/mc/Fall10/TTJets_TuneD6T_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0022/2A4828B2-FCE3-DF11-ABDD-0015C5E673AE.root',
        #'/store/user/eschliec/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/PATWithPF_v4/e59efddd8a1547799dca5b47d5556447/patTuple_21_1_rkC.root',
        #'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/8A5EC185-0098-E011-BAEE-0018F3D0968A.root',
        #'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/4AA93931-0498-E011-8542-001A928116F2.root',
        #'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/4C123530-8098-E011-81AF-002618943896.root',
        #'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/4CA5D2CB-EB97-E011-9049-002618943918.root',
        #'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/50A22F5C-5C98-E011-A2F0-00304867915A.root',
        #'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/50E84A29-7E98-E011-BE33-003048679076.root',
        #'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/52F85166-F197-E011-A69C-0026189437F9.root',
        #'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/54CE112F-0E98-E011-BF35-0030486790B0.root',
        #'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/566A92D3-8198-E011-B00A-00261894391F.root',
        #'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/56B5966B-8698-E011-80E2-001A92810ACA.root',
        #'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/58080F8B-FB9A-E011-9961-001A92810AE0.root',
        #'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/58147179-0698-E011-8F48-0030486790B0.root',
        #'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/5835C219-F497-E011-9654-0026189438F3.root',
        #'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/5A71E3FA-8098-E011-9985-0026189438C0.root',
        #'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/5AC5BEBF-E797-E011-AF5F-00261894397A.root',
        #'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/5AF8B0C6-E897-E011-AD4C-003048679214.root',
        #'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/74733820-F097-E011-9F9A-002618943975.root',
        #'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/7650FAF5-9B98-E011-90C7-001A92971B94.root',
        #'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/76A12412-5098-E011-8FC9-001A92971B80.root',
        #'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/76E7B7AC-9F98-E011-AAAA-0018F3D096AE.root',
        #'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/78436557-0D98-E011-8881-001A9281170A.root',
        #'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/78AA6168-8498-E011-B586-00261894387E.root',
        #'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/7A12CB9B-E297-E011-BCBD-0018F3D0961E.root',
        #'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/7AA6A623-8198-E011-AB19-003048679076.root',
        #'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/7C571269-FF97-E011-BAA7-001A92810AEC.root',
        #'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/7C66C165-EF97-E011-B33B-003048678FFA.root',
        #'file:/scratch/hh/dust/naf/cms/user/gosseli/alljets/bbbar_6jets_7TeV_pythia6_GEN/bbbar_6jets_7TeV_pythia6_GEN_0.root',
        #'file:/scratch/hh/dust/naf/cms/user/gosseli/alljets/bbbar_6jets_7TeV_pythia6_GEN/bbbar_6jets_7TeV_pythia6_GEN_100.root',
        #'file:/scratch/hh/dust/naf/cms/user/gosseli/alljets/bbbar_6jets_7TeV_pythia6_GEN/bbbar_6jets_7TeV_pythia6_GEN_101.root',
        #'file:/scratch/hh/dust/naf/cms/user/gosseli/alljets/bbbar_6jets_7TeV_pythia6_GEN/bbbar_6jets_7TeV_pythia6_GEN_102.root',
        #'file:/scratch/hh/dust/naf/cms/user/gosseli/alljets/bbbar_6jets_7TeV_pythia6_GEN/bbbar_6jets_7TeV_pythia6_GEN_103.root',
        #'file:/scratch/hh/dust/naf/cms/user/gosseli/alljets/bbbar_6jets_7TeV_pythia6_GEN/bbbar_6jets_7TeV_pythia6_GEN_104.root',
        #'file:/scratch/hh/dust/naf/cms/user/gosseli/alljets/bbbar_6jets_7TeV_pythia6_GEN/bbbar_6jets_7TeV_pythia6_GEN_105.root',
        #'file:/scratch/hh/dust/naf/cms/user/gosseli/alljets/bbbar_6jets_7TeV_pythia6_GEN/bbbar_6jets_7TeV_pythia6_GEN_106.root',
        #'file:/scratch/hh/dust/naf/cms/user/gosseli/alljets/bbbar_6jets_7TeV_pythia6_GEN/bbbar_6jets_7TeV_pythia6_GEN_107.root',
        #'file:/scratch/hh/dust/naf/cms/user/gosseli/alljets/bbbar_6jets_7TeV_pythia6_GEN/bbbar_6jets_7TeV_pythia6_GEN_108.root',
        #'file:/scratch/hh/dust/naf/cms/user/gosseli/alljets/bbbar_6jets_7TeV_pythia6_GEN/bbbar_6jets_7TeV_pythia6_GEN_109.root',
        #'file:/scratch/hh/dust/naf/cms/user/gosseli/alljets/bbbar_6jets_7TeV_pythia6_GEN/bbbar_6jets_7TeV_pythia6_GEN_10.root',
        #'file:/scratch/hh/dust/naf/cms/user/gosseli/alljets/bbbar_6jets_7TeV_pythia6_GEN/bbbar_6jets_7TeV_pythia6_GEN_110.root',
        #'file:/scratch/hh/dust/naf/cms/user/gosseli/alljets/bbbar_6jets_7TeV_pythia6_GEN/bbbar_6jets_7TeV_pythia6_GEN_111.root',
        #'file:/scratch/hh/dust/naf/cms/user/gosseli/alljets/bbbar_6jets_7TeV_pythia6_GEN/bbbar_6jets_7TeV_pythia6_GEN_112.root',
        #'file:/scratch/hh/dust/naf/cms/user/gosseli/alljets/bbbar_6jets_7TeV_pythia6_GEN/bbbar_6jets_7TeV_pythia6_GEN_113.root',
        #'file:/scratch/hh/dust/naf/cms/user/gosseli/alljets/bbbar_6jets_7TeV_pythia6_GEN/bbbar_6jets_7TeV_pythia6_GEN_114.root',
        #'file:/scratch/hh/dust/naf/cms/user/gosseli/alljets/bbbar_6jets_7TeV_pythia6_GEN/bbbar_6jets_7TeV_pythia6_GEN_115.root',
        #'file:/scratch/hh/dust/naf/cms/user/gosseli/alljets/bbbar_6jets_7TeV_pythia6_GEN/bbbar_6jets_7TeV_pythia6_GEN_116.root',
        #'file:/scratch/hh/dust/naf/cms/user/gosseli/alljets/bbbar_6jets_7TeV_pythia6_GEN/bbbar_6jets_7TeV_pythia6_GEN_117.root',
        #'file:/scratch/hh/dust/naf/cms/user/gosseli/alljets/bbbar_6jets_7TeV_pythia6_GEN/bbbar_6jets_7TeV_pythia6_GEN_118.root',
        #'file:/scratch/hh/dust/naf/cms/user/gosseli/alljets/bbbar_6jets_7TeV_pythia6_GEN/bbbar_6jets_7TeV_pythia6_GEN_119.root',
        #'file:/scratch/hh/dust/naf/cms/user/gosseli/alljets/bbbar_6jets_7TeV_pythia6_GEN/bbbar_6jets_7TeV_pythia6_GEN_11.root',
        #'/store/mc/Fall11/TT_TuneZ2_7TeV-mcatnlo/AODSIM/PU_S6_START42_V14B-v1/0000/C8F655E6-242A-E111-9138-002618943959.root',
        #'/store/mc/Fall11/QCD_Pt-1800_TuneZ2_7TeV_pythia6/AODSIM/PU_S6_START42_V14B-v1/0000/3E5BE6DC-A407-E111-8CE7-00261894391B.root',
        #'/store/mc/Fall11/QCD_Pt-1800_TuneZ2_7TeV_pythia6/AODSIM/PU_S6_START42_V14B-v1/0000/9A058174-A807-E111-B212-002618943971.root',
        #'/store/mc/Fall11/QCD_Pt-1800_TuneZ2_7TeV_pythia6/AODSIM/PU_S6_START42_V14B-v1/0000/1ED5B8A4-D807-E111-B4C4-0026189438E9.root',
        #'/store/mc/Fall11/QCD_Pt-1800_TuneZ2_7TeV_pythia6/AODSIM/PU_S6_START42_V14B-v1/0000/F46D6B0A-C007-E111-AC42-0026189438FE.root',
        #'/store/mc/Fall11/QCD_Pt-1800_TuneZ2_7TeV_pythia6/AODSIM/PU_S6_START42_V14B-v1/0000/AE505B03-6D07-E111-943A-003048678B70.root',
        #'/store/mc/Fall11/QCD_Pt-1800_TuneZ2_7TeV_pythia6/AODSIM/PU_S6_START42_V14B-v1/0000/7C1177BF-CE07-E111-8F41-001A92971B84.root',
        #'/store/mc/Fall11/QCD_Pt-1800_TuneZ2_7TeV_pythia6/AODSIM/PU_S6_START42_V14B-v1/0000/B8AE9828-CA07-E111-A278-00261894386B.root',
        #'/store/mc/Fall11/QCD_Pt-1800_TuneZ2_7TeV_pythia6/AODSIM/PU_S6_START42_V14B-v1/0000/0A61134D-FD08-E111-8EB6-003048678F9C.root',
        #'/store/mc/Summer11/QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6/AODSIM/PU_S3_START42_V11-v2/0000/70D2C5F9-5B7E-E011-863E-00261894384A.root',
        #'/store/mc/Summer11/QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6/AODSIM/PU_S3_START42_V11-v2/0000/A4454F2E-657E-E011-B2F9-00304867D836.root',
        #'/store/mc/Summer11/QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6/AODSIM/PU_S3_START42_V11-v2/0000/06729103-837E-E011-9C68-00261894396A.root',
        #'/store/mc/Summer11/QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6/AODSIM/PU_S3_START42_V11-v2/0000/DA7E0F7C-477E-E011-A5B1-002618943910.root',
        #'/store/mc/Summer11/QCD_Pt-15to3000_Tune23_Flat_7TeV_herwigpp/AODSIM/PU_S3_START42_V11-v2/0000/0270B432-F682-E011-81D9-003048D437E4.root',
        #'/store/mc/Summer11/QCD_Pt-15to3000_Tune23_Flat_7TeV_herwigpp/AODSIM/PU_S3_START42_V11-v2/0000/3213CDB1-F982-E011-B8B8-003048D437DA.root',
        #'/store/mc/Summer11/QCD_Pt-15to3000_Tune23_Flat_7TeV_herwigpp/AODSIM/PU_S3_START42_V11-v2/0000/6E01A1B3-F982-E011-AA05-002481E0D500.root',
        #'/store/mc/Summer11/QCD_Pt-15to3000_Tune23_Flat_7TeV_herwigpp/AODSIM/PU_S3_START42_V11-v2/0000/A45BCF02-1983-E011-B9C6-0030487E55BB.root',
        #'/store/mc/Summer11/QCD_Pt-15to3000_Tune4C_Flat_7TeV_pythia8/AODSIM/PU_S3_START42_V11-v2/0000/06A76BA6-FB80-E011-AB94-0030487F1A73.root',
        #'/store/mc/Summer11/QCD_Pt-15to3000_Tune4C_Flat_7TeV_pythia8/AODSIM/PU_S3_START42_V11-v2/0000/44F38536-0381-E011-A170-0030487F929B.root',
        #'/store/mc/Summer11/QCD_Pt-15to3000_Tune4C_Flat_7TeV_pythia8/AODSIM/PU_S3_START42_V11-v2/0000/844976AF-1C81-E011-926A-0030487F1309.root',
        #'/store/mc/Summer11/QCD_Pt-15to3000_Tune4C_Flat_7TeV_pythia8/AODSIM/PU_S3_START42_V11-v2/0000/B0EAC171-3C81-E011-8640-003048D436B2.root',
        '/store/mc/Fall11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/966C784E-990F-E111-B38E-0026189438C0.root',
        ),
                            skipEvents = cms.untracked.uint32(0)
)

## process / skip specific events
#process.source.eventsToProcess = cms.untracked.VEventRange('1:1-1:6','2:100-3:max')
#process.source.eventsToSkip = cms.untracked.VEventRange('1:1-1:6','2:100-3:max')
#process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange('1:1-1:6','2:100-3:max')
#process.source.lumisToSkip = cms.untracked.VLuminosityBlockRange('1:1-1:6','2:100-3:max')

## print memory infos to check for modules with memory leaks
#process.SimpleMemoryCheck = cms.Service("SimpleMemoryCheck", ignoreTotal = cms.untracked.int32(0))

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
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
#process.load("Configuration.StandardSequences.Geometry_cff")
#process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")

if(options.eventFilter=='data'):
    #process.GlobalTag.globaltag = cms.string('GR_R_38X_V15::All')
    #process.GlobalTag.globaltag = cms.string('GR_R_42_V14::All')
    #process.GlobalTag.globaltag = cms.string('FT_R_42_V18A::All')
    #process.GlobalTag.globaltag = cms.string('GR_R_42_V19::All')
    #process.GlobalTag.globaltag = cms.string('GR_R_42_V21A::All')
    process.GlobalTag.globaltag = cms.string('GR_R_42_V23::All')
else:
    if os.getenv('CMSSW_VERSION').startswith('CMSSW_4_2_'):
        #process.GlobalTag.globaltag = cms.string('START42_V12::All')
        #process.GlobalTag.globaltag = cms.string('START42_V13::All')
        #process.GlobalTag.globaltag = cms.string('START42_V15B::All')
        process.GlobalTag.globaltag = cms.string('START42_V17::All')
    elif os.getenv('CMSSW_VERSION').startswith('CMSSW_4_1_'):
        #process.GlobalTag.globaltag = cms.string('START38_V14::All')
        process.GlobalTag.globaltag = cms.string('START41_V0::All')

### save JEC and uncertainties to files
#process.readAK5PF = cms.EDAnalyzer( 'JetCorrectorDBReader'
#                                    # below is the communication to the database 
#                                  , payloadName    = cms.untracked.string('AK5PFchs')
#                                    # this is used ONLY for the name of the printed txt files. You can use any name that you like, 
#                                    # but it is recommended to use the GT name that you retrieved the files from.
#                                  , globalTag      = cms.untracked.string('GR_R_42_V23')
#                                  , printScreen    = cms.untracked.bool(False)
#                                  , createTextFile = cms.untracked.bool(True)
#                                  )

## std sequence to produce the ttGenEvt
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")

## filter for full-hadronic 
process.load("TopQuarkAnalysis.TopEventProducers.producers.TtDecaySelection_cfi")
process.ttFullHadronicFilter = process.ttDecaySelection.clone()

## ptHat filter
process.load("TopAnalysis.TopFilter.filters.PtHatFilter_cfi")
process.filterPtHat = process.filterPtHat.clone()

## additional jet energy smearing for MC
if options.jetEResol == 0:
    resolutions = [1.1, 1.1, 1.1]
    etaRanges = [0.0,1.5,1.5,2.0,2.0,-1.]
elif options.jetEResol == 1:
    resolutions = [1.2, 1.25, 1.3]
    etaRanges = [0.0,1.5,1.5,2.0,2.0,-1.]
elif options.jetEResol == -1:
    resolutions = [1.0, 0.95, 0.9]
    etaRanges = [0.0,1.5,1.5,2.0,2.0,-1.]
elif options.jetEResol == 9:
    resolutions = [0.990, 1.001, 1.032, 1.042, 1.089]
    etaRanges = [0.0,0.5,0.5,1.1,1.1,1.7,1.7,2.3,2.3,-1.]
elif options.jetEResol == 10:
    resolutions = [1.052, 1.057, 1.096, 1.134, 1.288]
    etaRanges = [0.0,0.5,0.5,1.1,1.1,1.7,1.7,2.3,2.3,-1.]
elif options.jetEResol == 11:
    resolutions = [1.115, 1.114, 1.161, 1.228, 1.488]
    etaRanges = [0.0,0.5,0.5,1.1,1.1,1.7,1.7,2.3,2.3,-1.]
else:
    exit('jetEResol: ' + str(options.jetEResol) + ' not supported, choose -1/0/+1/9/10/11')

process.load("TopAnalysis.TopUtils.JetEnergyScale_cfi")
process.scaledJetEnergy = process.scaledJetEnergy.clone( inputJets            = cms.InputTag("selectedPatJetsAK5PF"),
                                                         inputMETs            = cms.InputTag("patMETsPF"),
                                                         payload              = cms.string("AK5PFchs"),
                                                         scaleFactor          = cms.double(options.jesFactor),
                                                         scaleType            = cms.string("abs"), #abs, rel, top:up, top:down, jes:up, jes:down
                                                         jetPTThresholdForMET = cms.double(20.),
                                                         jetEMLimitForMET     = cms.double(0.9),
                                                         resolutionFactors    = cms.vdouble(resolutions),
                                                         resolutionEtaRanges  = cms.vdouble(etaRanges)
                                                       )

## set set energy scaling factors
if options.jesType == 'jes' :
    if options.jesFactor > 1.0 :
        process.scaledJetEnergy.scaleType = "jes:up"
    elif options.jesFactor < 1.0 :
        process.scaledJetEnergy.scaleType = "jes:down"
## set set energy scaling factors for flavor ONLY
elif options.jesType == 'flavor' :
    if options.jesFactor > 1.0 :
        process.scaledJetEnergy.scaleType = "flavor:up"
    elif options.jesFactor < 1.0 :
        process.scaledJetEnergy.scaleType = "flavor:down"

## residual jet corrector for data
process.load("TopAnalysis.TopUtils.ResidualJetCorrector_cfi")
process.residualCorrectedJets = process.residualCorrectedJets.clone()

if options.eventFilter=='data' :
    ## sequence with jet energy corrections specially suited for data
    process.filterSequence = cms.Sequence(process.residualCorrectedJets
                                          )
    
elif options.eventFilter=='sig' :
    ## sequence with fullHad ttbar filter
    process.filterSequence = cms.Sequence(process.makeGenEvt *
                                          process.ttFullHadronicFilter *
                                          process.scaledJetEnergy
                                          )

elif options.eventFilter=='bkg' :
    ## invert fullHad filter
    process.ttFullHadronicFilter.invert = True
    ## sequence with non-fullHad ttbar filter
    process.filterSequence = cms.Sequence(process.makeGenEvt *
                                          process.ttFullHadronicFilter *
                                          process.scaledJetEnergy
                                          )

elif options.eventFilter=='qcd' :
    if options.maxPtHat<999999. :
        ## ptHat filter
        process.filterPtHat.maxPtHat = options.maxPtHat
        print "included ptHatFilter with 'maxPtHat' =",
        print process.filterPtHat.maxPtHat

    if options.minPtHat>0. :
        process.filterPtHat.minPtHat = options.minPtHat
        print "included ptHatFilter with 'minPtHat' =",
        print process.filterPtHat.minPtHat

    ## sequence with ptHat filter
    process.filterSequence = cms.Sequence(process.filterPtHat *
                                          process.scaledJetEnergy)

elif options.eventFilter=='all' :
    process.filterSequence = cms.Sequence(process.scaledJetEnergy)
    
elif options.eventFilter=='toyMC' :
    ## convert GenJets to PatJets
    process.load("TopAnalysis.TopUtils.convertGenToPatJets_cff")
    process.filterSequence = cms.Sequence(process.fullHadGenJetSelection*process.convertGenToPatJets)
    
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

if not options.eventFilter=='sig' :
    removeTtFullHadHypGenMatch(process)

runAsBackgroundEstimation(process, options.backgroundEstimation)

## changing bTagger, possible are: TCHEL, TCHEM, TCHPM, TCHPT, SSVHEM, SSVHPT, CSVM, CSVT, CSVMVA
## CSVMVA has NO officialy blessed WP
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
elif options.bTagAlgoWP == "CSVM" :
    switchToCSVM(process)
elif options.bTagAlgoWP == "CSVT" :
    switchToCSVT(process)
elif options.bTagAlgoWP == "CSVTSysUp" :
    switchToCSVTSysUp(process)
elif options.bTagAlgoWP == "CSVTSysDown" :
    switchToCSVTSysDown(process)
elif options.bTagAlgoWP == "CSVMVA" :
    switchToCSVMVA(process)
else :
    exit('bTagAlgoWP * ' + options.bTagAlgoWP + " * NOT SUPPORTED, STOP PROCESSING")
    
## selection should be run on PFJets instead of caloJets
if not options.usePF: 
    runOnCalo(process)

## if running on real data, do everything needed for this
if options.eventFilter=='data' :
    runOnData(process)
    ## needed because the patTriggerEvent is to chatty to be used and
    ## data is already skimmed with trigger requirement
    #removeTrigger(process)

## increase the resolution of the kinematic fit
if options.fitResol == 1 :
    fitEtaRages = [0.0,-1.0]
    fitResolutions = [1.1]
elif options.fitResol == 10 :
    fitEtaRages = [0.0,0.5,1.1,1.7,2.3,-1.]
    fitResolutions = [1.052, 1.057, 1.096, 1.134, 1.288]
else:
    exit('fitResol: ' + str(options.fitResol) + ' not supported, choose 1/10')
increaseKinFitResolution(process, fitEtaRages, fitResolutions)

## remove cutflow monitoring
removeMonitoringOfCutflow(process)

## THE treeWriter itself
process.load("TopAnalysis.TopAnalyzer.FullHadTreeWriter_cfi")

## switch tree writer to appropriate jet source
process.FullHadTreeWriter = process.writeFullHadTree.clone(JetSrc = "tightLeadingJets")

## set correct MC weight
process.FullHadTreeWriter.MCweight = options.mcWeight

process.load("TopAnalysis.TopUtils.EventWeightPU_cfi")
if os.getenv('CMSSW_VERSION').startswith('CMSSW_4_2_'):
    #process.eventWeightPU = process.eventWeightPU.clone(MCSampleFile = "TopAnalysis/TopUtils/data/MC_PUDist_Summer11_TTJets_TuneZ2_7TeV_madgraph_tauola.root")
    #process.eventWeightPU = process.eventWeightPU.clone(MCSampleFile = "TopAnalysis/TopUtils/data/Fall11/MC_PUDist_Fall11_TTJets_TuneZ2_7TeV_MadGraph.root")
    #rocess.eventWeightPU = process.eventWeightPU.clone(MCSampleFile = "TopAnalysis/TopUtils/data/MC_PUDist_Default2011.root", MCSampleHistoName = "histoSummer11_flat_observed")
     process.eventWeightPU = process.eventWeightPU.clone(MCSampleFile = "TopAnalysis/TopUtils/data/MC_PUDist_Default2011.root", MCSampleHistoName = "histo_Fall11_true")
    #process.eventWeightPU = process.eventWeightPU.clone(MCSampleFile = "TopAnalysis/TopUtils/data/MC_PUDist_WJets_Spring11.root", MCSampleHistoName = "pileup")
elif os.getenv('CMSSW_VERSION').startswith('CMSSW_4_1_'):
    process.eventWeightPU = process.eventWeightPU.clone(MCSampleFile = "TopAnalysis/TopUtils/data/MC_PUDist_WJets_Spring11.root", MCSampleHistoName = "pileup")
if options.PUscenario == '11_178078':
    #process.eventWeightPU.DataFile = "TopAnalysis/TopUtils/data/MyDataPileupHistogram_precaleWeighted_new.root"
    #process.eventWeightPU.DataFile = "TopAnalysis/TopUtils/data/MyDataPileupHistogram_precaleWeighted_3545fb-1.root"
    #process.eventWeightPU.DataFile = "TopAnalysis/TopUtils/data/MyDataPileupHistogram_precaleWeighted_3545fb-1_-8.root"
    #process.eventWeightPU.DataFile = "TopAnalysis/TopUtils/data/MyDataPileupHistogram_precaleWeighted_3545fb-1_+8.root"
    #process.eventWeightPU.DataFile = "TopAnalysis/TopUtils/data/MyDataPileupHistogram_observed.root"
    process.eventWeightPU.DataFile = "TopAnalysis/TopUtils/data/MyDataPileupHistogram_true.root"
    process.eventWeightPU.DataHistoName = "pileup"
elif options.PUscenario == '11_167913':
#if options.PUscenario == '11_167913':
    process.eventWeightPU.DataFile = "TopAnalysis/TopUtils/data/Data_PUDist_160404-163869_7TeV_May10ReReco_Collisions11_v2_and_165088-167913_7TeV_PromptReco_Collisions11.root"
elif options.PUscenario == '11_166861':
    process.eventWeightPU.DataFile = "TopAnalysis/TopUtils/data/Data_PUDist_160404-166861_7TeV_PromptReco_Collisions11.root"
elif options.PUscenario == '11_166502':
    process.eventWeightPU.DataFile = "TopAnalysis/TopUtils/data/Data_PUDist_160404-166502_7TeV_PromptReco_Collisions11.root"
elif options.PUscenario == '11_May10':
    process.eventWeightPU.DataFile = "TopAnalysis/TopUtils/data/Data_PUDist_160404-163869_7TeV_May10ReReco_Collisions11.root"
elif options.PUscenario == '10_Apr21':
    process.eventWeightPU.DataFile = "TopAnalysis/TopUtils/data/Data_PUDist_136033-149442_7TeV_Apr21ReReco_Collisions10.root"
elif options.PUscenario == 'EPS':
    process.eventWeightPU.DataFile = "TopAnalysis/TopUtils/data/Data_PUDist_160404-163869_7TeV_May10ReReco_Collisions11_v2_and_165088-167913_7TeV_PromptReco_Collisions11.root"
elif not options.eventFilter == 'data':
    exit('PU SCENARIO * ' + options.PUscenario + " * NOT SUPPORTED, STOP PROCESSING")

## remove PDF uncertainties
removePDFUncertainties(process)
if not options.pdfUn==0 :
    process.FullHadTreeWriter.DoPDFUncertainty = True

## get b-tag efficiency infos
process.load ("RecoBTag.PerformanceDB.PoolBTagPerformanceDB1107")
process.load ("RecoBTag.PerformanceDB.BTagPerformanceDB1107")

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

if options.backgroundEstimation != 0:
    if options.backgroundEstimation == 1:
        process.p1.remove(process.makeTtFullHadEvent)
        process.p1.remove(process.FullHadTreeWriter)
        if not options.eventFilter=='data' :
            process.analyzeFullHadQCDEstimation.bTagAlgoWP = "TCHEM40MC"
            process.analyzeFullHadQCDEstimation.MCweight = options.mcWeight
        
        if options.usePF:
            getattr(process, process.tightBottomJets.src.getModuleLabel()).src = cms.InputTag("goodJetsPF")
                     
        process.p1 += cms.Sequence( getattr(process, process.tightBottomJets.src.getModuleLabel())
                                  * process.tightBottomJets
                                  * process.tightBottomJetSelection
                                  * process.analyzeFullHadQCDEstimation
                                  )

        process.TFileService.fileName = 'QCDEstimation_1_'+options.eventFilter+'.root'

    if options.backgroundEstimation == 2:
        process.p1.remove(process.FullHadTreeWriter)
        if options.usePF:
            getattr(process, process.tightBottomJets.src.getModuleLabel()).src = cms.InputTag("goodJetsPF")
                     
        if(options.eventFilter=='toyMC'):
            process.analyzeFullHadEventMixer.speedUp = 10.0
        process.p1 += cms.Sequence( getattr(process, process.tightBottomJets.src.getModuleLabel())
                                  * process.tightBottomJets
                                  * process.tightBottomJetSelection
                                  * process.analyzeFullHadEventMixer
                                  )

        process.TFileService.fileName = 'QCDEstimation_2_'+options.eventFilter+'.root'

if(options.pdfUn==2):
    print "Writing TTree for all", options.eventFilter, "events, no further selection done!"
    #process.p1.remove(process.analyseFullHadronicSelection)
    process.p1 = cms.Path(process.FullHadTreeWriter)
    process.FullHadTreeWriter.MultiJetMVADiscSrc = ""
    process.FullHadTreeWriter.PUweightSrc        = ""
    process.FullHadTreeWriter.ElectronSrc        = ""
    process.FullHadTreeWriter.FitSrc             = ""
    process.FullHadTreeWriter.METSrc             = ""
    process.FullHadTreeWriter.PUSrc              = ""
    process.FullHadTreeWriter.VertexSrc          = ""
    process.FullHadTreeWriter.MuonSrc            = ""
    process.FullHadTreeWriter.JetSrc             = ""
    process.FullHadTreeWriter.bTagVal            = cms.vstring()
    process.FullHadTreeWriter.bTagName           = cms.vstring()
    

if options.eventFilter=='data':
    process.p1.remove(process.filterSequence)
    process.p1.remove(process.eventWeightPU)
else:
    # different energy resolution of jets in simulation
    if(hasattr(process, 'goodJets') & hasattr(process, 'scaledJetEnergy')):
        process.goodJets.src   = cms.InputTag('scaledJetEnergy', 'selectedPatJets', process.name_())
    if(hasattr(process, 'goodJetsPF') & hasattr(process, 'scaledJetEnergy')):
        process.goodJetsPF.src = cms.InputTag('scaledJetEnergy', 'selectedPatJetsAK5PF', process.name_())
    # change input for toyMC
    if(options.eventFilter=='toyMC'):
        from TopAnalysis.TopUtils.convertGenToPatJets_cff import selectedPatJets as mySelectedPatJets
        process.selectedPatJets = mySelectedPatJets
        process.goodJetsPF.src = cms.InputTag('selectedPatJets', '', process.name_())
        process.goodJetsPF.cut = "abs(eta) < 2.4 & pt > 20."
        process.p1.remove(process.eventWeightPU)
        #process.p1.remove(process.FullHadTreeWriter)
        process.FullHadTreeWriter.MultiJetMVADiscSrc = ""
        process.FullHadTreeWriter.PUweightSrc        = ""
        process.FullHadTreeWriter.ElectronSrc        = ""
        #process.FullHadTreeWriter.FitSrc             = ""
        process.FullHadTreeWriter.METSrc             = ""
        process.FullHadTreeWriter.PUSrc              = ""
        process.FullHadTreeWriter.VertexSrc          = ""
        process.FullHadTreeWriter.MuonSrc            = ""
        #process.FullHadTreeWriter.bTagVal            = cms.vstring()
        #process.FullHadTreeWriter.bTagName           = cms.vstring()


if(not options.pdfUn==2 and not options.eventFilter=='toyMC'):
    
     ## prepend the sequence needed to run on the NEW PAT tuples
    from TopAnalysis.TopUtils.usePatTupleWithParticleFlow_cff import prependPF2PATSequence
    pf2patOptions = {'runOnOLDcfg': True}
    pf2patOptions['pfIsoConeMuon'] = 0.3
    pf2patOptions['pfIsoConeElec'] = 0.3
    pf2patOptions['pfIsoValMuon'] = 0.2
    pf2patOptions['pfIsoValElec'] = 0.2
    pf2patOptions['electronIDs'] = ''
    pf2patOptions['excludeElectronsFromWsFromGenJets'] = True
    #pf2patOptions['noMuonTopProjection'] = True
    #pf2patOptions['noElecTopProjection'] = True
    pf2patOptions['METCorrectionLevel'] = 1 
    pf2patOptions['addResolutions'] = True
    pf2patOptions['resolutionsVersion'] = 'fall11'
    pf2patOptions['JECEra'] = 'Jec11_V10'
    pf2patOptions['JECFile'] = 'TopAnalysis/TopUtils/data/Jec11_V10_L7PartonPrivate.db'
    pf2patOptions['additionalJECLevels'] = ['L7Parton']
    if options.eventFilter=='data':
        pf2patOptions['runOnMC'] = False
    if options.runOnAOD:
        pf2patOptions['runOnAOD'] = True
    if options.writeOutput:
        pf2patOptions['switchOffEmbedding'] = False
    prependPF2PATSequence(process, options = pf2patOptions)

    ## load bugfix for wrongly generated MC files (MadGraph / Powheg + Pythia6)
    process.load("GeneratorInterface.GenFilters.TotalKinematicsFilter_cfi")
    ## test higher threshold to avoid bias
    process.totalKinematicsFilter.tolerance = 5.0

    ## adaptions (re-aranging of modules) to speed up processing
    pathnames = process.paths_().keys()
    for pathname in pathnames:
        ## move the ttGenEvent filter to the beginning of the sequence
        if options.eventFilter=='sig' or options.eventFilter=='bkg' :
            getattr(process, pathname).remove(process.ttFullHadronicFilter)
            #getattr(process, pathname).insert(0,process.ttFullHadronicFilter)
            getattr(process, pathname).remove(process.genEvt)
            getattr(process, pathname).insert(0,process.genEvt)
            getattr(process, pathname).remove(process.decaySubset)
            getattr(process, pathname).insert(0,process.decaySubset)
            getattr(process, pathname).remove(process.initSubset)
            getattr(process, pathname).insert(0,process.initSubset)
        ## move the trigger to the beginning of the sequence
        getattr(process, pathname).remove(process.trigger)
        getattr(process, pathname).insert(0,process.trigger)
        if hasattr(process,'readAK5PF') :
            getattr(process, pathname).insert(0,process.readAK5PF)
        
        ## add bugfix for wrongly generated MC files
        if not options.eventFilter == 'data' :
            getattr(process, pathname).insert(0,process.totalKinematicsFilter)


        ## change tag of triggerResults
        if not options.triggerTag=='HLT' :
            from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
            massSearchReplaceAnyInputTag(getattr(process, pathname), cms.InputTag("TriggerResults","","HLT"), cms.InputTag("TriggerResults","",options.triggerTag))
            process.patTrigger.processName      = options.triggerTag
            process.patTriggerEvent.processName = options.triggerTag

        ## adaption for 38X MC files, they don't have PUSummaryInfo
        if os.getenv('CMSSW_VERSION').startswith('CMSSW_4_1_') and (options.triggerTag=='HLT' or options.triggerTag=='REDIGI38X') :
            getattr(process, pathname).remove(process.eventWeightPU)
         
## Output Module Configuration
if options.writeOutput:
    process.outModule = cms.OutputModule("PoolOutputModule",
                                         fileName = cms.untracked.string('patTuple_selected.root'),
                                         # save only events passing the full path
                                         SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p1') ),
                                         # drop meta data for dropped events
                                         dropMetaData = cms.untracked.string('DROPPED'),
                                         # save output (comment to keep everything...)
                                         outputCommands = cms.untracked.vstring('drop *',
                                                                                'keep *_generator_*_*',
                                                                                'keep *_TriggerResults_*_HLT',
                                                                                'keep *_addPileupInfo_*_*',
                                                                                'keep *_genEvt_*_FullHadTreeWriter',
                                                                                'keep *_decaySubset_*_FullHadTreeWriter',
                                                                                'keep *_initSubset_*_FullHadTreeWriter',
                                                                                'keep *_ttFullHadEvent_*_FullHadTreeWriter',
                                                                                'keep *_mvaDisc_*_*',
                                                                                'keep *_eventWeightPU_*_*',
                                                                                'keep *_selectedPatJets_*_*',
                                                                                'keep *_selectedPatElectrons_*_*',
                                                                                'keep *_selectedPatMuons_*_*',
                                                                                'keep *_patMETs_*_*',
                                                                                ) 
                                         )
    process.outpath = cms.EndPath(process.outModule)

