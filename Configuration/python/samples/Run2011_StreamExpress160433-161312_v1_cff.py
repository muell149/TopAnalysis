import FWCore.ParameterSet.Config as cms

###################################### 67 files ############################

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_10_1_amd.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_11_1_r6a.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_1_1_sJi.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_12_1_tpN.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_13_1_BlL.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_14_1_VwU.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_15_1_MRy.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_16_1_P5H.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_17_1_Bmk.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_18_1_cP5.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_19_1_dym.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_20_1_AxZ.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_21_1_doV.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_2_1_oYq.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_22_1_D1J.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_23_1_V30.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_24_1_w4U.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_25_1_JIy.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_26_1_OoC.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_27_1_U2l.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_28_1_VUf.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_29_1_wKv.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_30_1_OiS.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_31_1_OQx.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_3_1_QTS.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_32_1_JP0.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_33_1_Bn0.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_34_1_VV6.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_35_1_enq.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_36_1_Jr2.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_37_1_YFE.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_38_1_YrI.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_39_1_gsz.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_40_1_iyb.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_41_1_9ok.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_4_1_b4Y.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_42_1_ss9.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_43_1_GPz.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_44_1_Z87.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_45_1_3ZQ.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_46_1_mJv.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_47_1_fnk.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_48_1_6Pm.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_49_1_K8H.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_50_1_YOs.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_51_1_cG2.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_5_1_j2d.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_52_1_ARw.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_53_1_52S.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_54_1_ulI.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_55_1_FB4.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_56_1_YZ1.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_57_1_5o0.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_58_1_m3X.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_59_1_Z1f.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_60_1_l7k.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_61_1_s1i.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_6_1_Rn3.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_62_1_066.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_63_1_ffL.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_64_1_YwE.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_65_1_HjP.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_66_1_ysD.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_67_1_1Pm.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_7_1_w5r.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_8_1_At4.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_StreamExpress160433-161312_UHH/c56830c11acaa6362ec2acabbafea440/Data2011_StreamExpress160433-161312_9_1_iJQ.root'
        ] );


secFiles.extend( [
               ] )

