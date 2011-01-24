import FWCore.ParameterSet.Config as cms

########################################################################################### 
#
#  Contains PATtuples from Fall 10 MC: Z+Jets
#  
#  SPECIAL: Reco::muons were matched with genMuons from a Z
#           using TopAnalysis.TopUtils.GenCandSelector_cfi 
# 
#  input samples: datasetpath=/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-START38_V12-v2/AODSIM
#
#    57 files
#    number of events: 
#
#
############################################################################################

readFiles = cms.untracked.vstring()

source = cms.Source("PoolSource",
                     fileNames= readFiles
                   )

readFiles.extend( [        	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_10_3_g60.root',
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_11_2_VNr.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_1_1_G8l.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_12_1_ePI.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_13_1_FK6.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_14_1_vOg.root',
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_15_1_0j4.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_16_1_Tf2.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_17_1_yCy.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_18_1_sQ7.root',
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_19_1_Qn4.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_20_1_gqF.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_21_1_TSS.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_2_1_XWo.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_22_1_ZSS.root',
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_23_1_tIT.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_24_1_xeq.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_25_2_gx6.root',
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_26_2_B8H.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_27_1_pHz.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_28_2_eaz.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_29_2_Nj9.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_30_2_eRT.root',
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_31_1_Aow.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_3_1_Dpm.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_32_1_jiu.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_33_1_TkG.root',
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_34_1_v0C.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_35_1_g9V.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_36_1_rif.root',
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_37_1_Dcx.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_38_1_fv4.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_39_1_4sz.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_40_2_c4U.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_41_1_x5c.root',
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_4_1_d19.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_42_1_OFz.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_43_1_dPn.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_44_1_slF.root',
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_45_1_7PU.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_46_1_q5V.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_47_1_1c7.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_48_1_Vhj.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_49_1_Vig.root',
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_50_1_Ns4.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_51_1_d4u.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_5_1_REf.root',
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_52_1_Yi0.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_53_1_Rvy.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_54_1_eOj.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_55_1_ajX.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_56_1_iQ7.root',
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_57_3_GSw.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_6_1_wgX.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_7_2_qmI.root',	
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_8_2_OlW.root',
        '/store/user/jlange/samples/Fall10/DYLLM50D6T/PATtuple_9_2_GDN.root'
	] );   
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
                                                                