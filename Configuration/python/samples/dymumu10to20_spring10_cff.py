import FWCore.ParameterSet.Config as cms

######################################################################
#                                                                     
# /DYmumu_M10to20/Spring10-START3X_V26_S09-v1/GEN-SIM-RECO            
#                                                                     
# Events       :                                                                                            
# xsec(pb) NNLO:       3457                                               
# eff          :        1.0                                                    
######################################################################

source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(   
        '/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_1_2.root',		
	'/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_2_1.root',
	'/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_3_1.root',
	'/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_4_1.root',
        '/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_5_1.root',		
	'/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_6_1.root',
	'/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_7_1.root',
	'/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_8_2.root',	
        '/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_9_2.root',
        '/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_10_1.root',    
        '/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_11_1.root',		
	'/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_12_1.root',
	'/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_13_1.root',
	'/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_14_2.root',
        #'/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_15_1.root',		
	#'/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_16_1.root',
	'/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_17_1.root',
	'/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_18_1.root',	
        '/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_19_1.root',
        '/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_20_1.root',    
        '/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_21_1.root',		
	'/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_22_2.root',
	'/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_23_1.root',
	'/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_24_2.root',
        #'/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_25_1.root',		
	'/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_26_1.root',
	'/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_27_1.root',
	'/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_28_2.root',	
        '/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_29_1.root',
        '/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_30_1.root',    
        #'/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_31_1.root',		
	'/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_32_1.root',
	'/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_33_1.root',
	'/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_34_1.root',
        '/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_35_3.root',		
	'/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_36_1.root',
	'/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_37_2.root',
	'/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_38_1.root',	
        '/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_39_1.root',
        #'/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_40_1.root',    
        '/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_41_2.root',		
	'/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_42_3.root',
	'/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_43_1.root',
	'/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_44_1.root',
        '/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_45_1.root',		
	'/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_46_1.root',
	'/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_47_1.root',
	'/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_48_1.root',	
        '/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_49_2.root',        
	'/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_50_1.root',    
        '/store/user/dammann/36X/Spring10/DY_MuMu_M10To20/PATtuple_51_1.root'					
       )
)
