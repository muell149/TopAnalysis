import FWCore.ParameterSet.Config as cms

######################################################################
#                                                                     
#              
#                                                                     
# Events       :                                               
# xsec(pb) NNLL:        165                                               
# eff          :        1.0                                                    
######################################################################

source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(   
        '/store/user/dammann/36X/Spring10/TTbar/PATtuple_1_1.root',		
	'/store/user/dammann/36X/Spring10/TTbar/PATtuple_2_1.root',
	'/store/user/dammann/36X/Spring10/TTbar/PATtuple_3_1.root',
	'/store/user/dammann/36X/Spring10/TTbar/PATtuple_4_1.root',
        '/store/user/dammann/36X/Spring10/TTbar/PATtuple_5_1.root',		
	'/store/user/dammann/36X/Spring10/TTbar/PATtuple_6_1.root',
	'/store/user/dammann/36X/Spring10/TTbar/PATtuple_7_1.root',
	'/store/user/dammann/36X/Spring10/TTbar/PATtuple_8_1.root',	
        '/store/user/dammann/36X/Spring10/TTbar/PATtuple_9_1.root',
        '/store/user/dammann/36X/Spring10/TTbar/PATtuple_10_1.root',    
        '/store/user/dammann/36X/Spring10/TTbar/PATtuple_11_1.root',		
	'/store/user/dammann/36X/Spring10/TTbar/PATtuple_12_1.root',
	'/store/user/dammann/36X/Spring10/TTbar/PATtuple_13_1.root',
	'/store/user/dammann/36X/Spring10/TTbar/PATtuple_14_1.root',
        '/store/user/dammann/36X/Spring10/TTbar/PATtuple_15_1.root',		
	'/store/user/dammann/36X/Spring10/TTbar/PATtuple_16_1.root',
	'/store/user/dammann/36X/Spring10/TTbar/PATtuple_17_1.root',
	'/store/user/dammann/36X/Spring10/TTbar/PATtuple_18_1.root',	
        '/store/user/dammann/36X/Spring10/TTbar/PATtuple_19_1.root',
        '/store/user/dammann/36X/Spring10/TTbar/PATtuple_20_1.root',    
        '/store/user/dammann/36X/Spring10/TTbar/PATtuple_21_1.root',		
	'/store/user/dammann/36X/Spring10/TTbar/PATtuple_22_1.root'						
       )
)
