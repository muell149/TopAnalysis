import FWCore.ParameterSet.Config as cms

######################################################################
#                                                                     
#  
#                                                                     
# Events       :                                                                                             
# xsec(pb) NNLO:                                                    
# eff          :       1.0                                                    
######################################################################

source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(   
        '/store/user/dammann/36X/Spring10/ZZ/PATtuple_1_3.root',		
	'/store/user/dammann/36X/Spring10/ZZ/PATtuple_2_1.root',
	'/store/user/dammann/36X/Spring10/ZZ/PATtuple_3_1.root',
	'/store/user/dammann/36X/Spring10/ZZ/PATtuple_4_1.root',
        '/store/user/dammann/36X/Spring10/ZZ/PATtuple_5_1.root',		
	'/store/user/dammann/36X/Spring10/ZZ/PATtuple_6_1.root',
	'/store/user/dammann/36X/Spring10/ZZ/PATtuple_7_2.root',
	'/store/user/dammann/36X/Spring10/ZZ/PATtuple_8_3.root',	
        '/store/user/dammann/36X/Spring10/ZZ/PATtuple_9_1.root',
        '/store/user/dammann/36X/Spring10/ZZ/PATtuple_10_1.root',    
        '/store/user/dammann/36X/Spring10/ZZ/PATtuple_11_1.root',		
	'/store/user/dammann/36X/Spring10/ZZ/PATtuple_12_1.root',
	'/store/user/dammann/36X/Spring10/ZZ/PATtuple_13_3.root',
	'/store/user/dammann/36X/Spring10/ZZ/PATtuple_14_2.root',
        '/store/user/dammann/36X/Spring10/ZZ/PATtuple_15_2.root',		
	'/store/user/dammann/36X/Spring10/ZZ/PATtuple_16_3.root',
	'/store/user/dammann/36X/Spring10/ZZ/PATtuple_17_1.root',
	'/store/user/dammann/36X/Spring10/ZZ/PATtuple_18_2.root',	
        '/store/user/dammann/36X/Spring10/ZZ/PATtuple_19_1.root',
        '/store/user/dammann/36X/Spring10/ZZ/PATtuple_20_1.root',    
        '/store/user/dammann/36X/Spring10/ZZ/PATtuple_21_1.root',		
	'/store/user/dammann/36X/Spring10/ZZ/PATtuple_22_1.root',
	'/store/user/dammann/36X/Spring10/ZZ/PATtuple_23_2.root',
	'/store/user/dammann/36X/Spring10/ZZ/PATtuple_24_1.root',
        '/store/user/dammann/36X/Spring10/ZZ/PATtuple_25_1.root',
	'/store/user/dammann/36X/Spring10/ZZ/PATtuple_26_3.root',
	'/store/user/dammann/36X/Spring10/ZZ/PATtuple_27_1.root',
	'/store/user/dammann/36X/Spring10/ZZ/PATtuple_28_1.root',
        '/store/user/dammann/36X/Spring10/ZZ/PATtuple_29_3.root',					
       )
)
