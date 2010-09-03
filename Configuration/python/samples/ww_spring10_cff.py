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
        '/store/user/dammann/36X/Spring10/WW/PATtuple_1_3.root',		
	'/store/user/dammann/36X/Spring10/WW/PATtuple_2_3.root',
	'/store/user/dammann/36X/Spring10/WW/PATtuple_3_1.root',
	'/store/user/dammann/36X/Spring10/WW/PATtuple_4_1.root',
        '/store/user/dammann/36X/Spring10/WW/PATtuple_5_1.root',		
	'/store/user/dammann/36X/Spring10/WW/PATtuple_6_1.root',
	'/store/user/dammann/36X/Spring10/WW/PATtuple_7_1.root',
	'/store/user/dammann/36X/Spring10/WW/PATtuple_8_1.root',	
        '/store/user/dammann/36X/Spring10/WW/PATtuple_9_3.root',
        '/store/user/dammann/36X/Spring10/WW/PATtuple_10_3.root',    
        '/store/user/dammann/36X/Spring10/WW/PATtuple_11_1.root',		
	'/store/user/dammann/36X/Spring10/WW/PATtuple_12_3.root',
	'/store/user/dammann/36X/Spring10/WW/PATtuple_13_3.root',
	'/store/user/dammann/36X/Spring10/WW/PATtuple_14_1.root',
        '/store/user/dammann/36X/Spring10/WW/PATtuple_15_1.root',		
	'/store/user/dammann/36X/Spring10/WW/PATtuple_16_3.root',
	'/store/user/dammann/36X/Spring10/WW/PATtuple_17_3.root',
	'/store/user/dammann/36X/Spring10/WW/PATtuple_18_1.root',	
        '/store/user/dammann/36X/Spring10/WW/PATtuple_19_1.root',
        '/store/user/dammann/36X/Spring10/WW/PATtuple_20_1.root',    
        '/store/user/dammann/36X/Spring10/WW/PATtuple_21_1.root',		
	'/store/user/dammann/36X/Spring10/WW/PATtuple_22_1.root',
	'/store/user/dammann/36X/Spring10/WW/PATtuple_23_1.root',
	'/store/user/dammann/36X/Spring10/WW/PATtuple_24_1.root',
        '/store/user/dammann/36X/Spring10/WW/PATtuple_25_3.root'			
       )
)
