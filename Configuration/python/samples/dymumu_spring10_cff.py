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
        '/store/user/dammann/36X/Spring10/DYMuMu_M5to20/PATtuple_1_1.root',		
	'/store/user/dammann/36X/Spring10/DYMuMu_M5to20/PATtuple_2_2.root',
	'/store/user/dammann/36X/Spring10/DYMuMu_M5to20/PATtuple_3_1.root',
	'/store/user/dammann/36X/Spring10/DYMuMu_M5to20/PATtuple_4_2.root',
        #'/store/user/dammann/36X/Spring10/DYMuMu_M5to20/PATtuple_5_1.root',		
	'/store/user/dammann/36X/Spring10/DYMuMu_M5to20/PATtuple_6_2.root',
	'/store/user/dammann/36X/Spring10/DYMuMu_M5to20/PATtuple_7_1.root',
	'/store/user/dammann/36X/Spring10/DYMuMu_M5to20/PATtuple_8_2.root',	
        '/store/user/dammann/36X/Spring10/DYMuMu_M5to20/PATtuple_9_2.root',
        '/store/user/dammann/36X/Spring10/DYMuMu_M5to20/PATtuple_10_2.root',    
        '/store/user/dammann/36X/Spring10/DYMuMu_M5to20/PATtuple_11_2.root',		
	'/store/user/dammann/36X/Spring10/DYMuMu_M5to20/PATtuple_12_1.root',
	'/store/user/dammann/36X/Spring10/DYMuMu_M5to20/PATtuple_13_1.root',
	'/store/user/dammann/36X/Spring10/DYMuMu_M5to20/PATtuple_14_1.root',
        '/store/user/dammann/36X/Spring10/DYMuMu_M5to20/PATtuple_15_2.root',		
	'/store/user/dammann/36X/Spring10/DYMuMu_M5to20/PATtuple_16_2.root',
	'/store/user/dammann/36X/Spring10/DYMuMu_M5to20/PATtuple_17_2.root',
	'/store/user/dammann/36X/Spring10/DYMuMu_M5to20/PATtuple_18_2.root',	
        '/store/user/dammann/36X/Spring10/DYMuMu_M5to20/PATtuple_19_2.root',
        '/store/user/dammann/36X/Spring10/DYMuMu_M5to20/PATtuple_20_1.root',    
        '/store/user/dammann/36X/Spring10/DYMuMu_M5to20/PATtuple_21_2.root',		
	'/store/user/dammann/36X/Spring10/DYMuMu_M5to20/PATtuple_22_1.root',
	'/store/user/dammann/36X/Spring10/DYMuMu_M5to20/PATtuple_23_2.root',
	'/store/user/dammann/36X/Spring10/DYMuMu_M5to20/PATtuple_24_1.root',
        '/store/user/dammann/36X/Spring10/DYMuMu_M5to20/PATtuple_25_1.root',
	'/store/user/dammann/36X/Spring10/DYMuMu_M5to20/PATtuple_26_2.root',
	'/store/user/dammann/36X/Spring10/DYMuMu_M5to20/PATtuple_27_2.root',
	'/store/user/dammann/36X/Spring10/DYMuMu_M5to20/PATtuple_28_1.root'					
       )
)
