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
        '/store/user/dammann/36X/Spring10/WZ/PATtuple_1_3.root',		
	'/store/user/dammann/36X/Spring10/WZ/PATtuple_2_2.root',
	'/store/user/dammann/36X/Spring10/WZ/PATtuple_3_1.root',
	'/store/user/dammann/36X/Spring10/WZ/PATtuple_4_1.root',
        '/store/user/dammann/36X/Spring10/WZ/PATtuple_5_1.root',		
	'/store/user/dammann/36X/Spring10/WZ/PATtuple_6_3.root',
	'/store/user/dammann/36X/Spring10/WZ/PATtuple_7_3.root',
	'/store/user/dammann/36X/Spring10/WZ/PATtuple_8_1.root',	
        '/store/user/dammann/36X/Spring10/WZ/PATtuple_9_1.root',
        '/store/user/dammann/36X/Spring10/WZ/PATtuple_10_2.root',    
        '/store/user/dammann/36X/Spring10/WZ/PATtuple_11_2.root',		
	'/store/user/dammann/36X/Spring10/WZ/PATtuple_12_1.root',
	'/store/user/dammann/36X/Spring10/WZ/PATtuple_13_2.root',
	'/store/user/dammann/36X/Spring10/WZ/PATtuple_14_1.root',
        '/store/user/dammann/36X/Spring10/WZ/PATtuple_15_2.root',		
	'/store/user/dammann/36X/Spring10/WZ/PATtuple_16_3.root',
	'/store/user/dammann/36X/Spring10/WZ/PATtuple_17_1.root',
	'/store/user/dammann/36X/Spring10/WZ/PATtuple_18_3.root',	
        '/store/user/dammann/36X/Spring10/WZ/PATtuple_19_1.root',
        '/store/user/dammann/36X/Spring10/WZ/PATtuple_20_1.root',    
        '/store/user/dammann/36X/Spring10/WZ/PATtuple_21_1.root',		
	'/store/user/dammann/36X/Spring10/WZ/PATtuple_22_1.root',
	'/store/user/dammann/36X/Spring10/WZ/PATtuple_23_1.root',
	'/store/user/dammann/36X/Spring10/WZ/PATtuple_24_1.root'			
       )
)
