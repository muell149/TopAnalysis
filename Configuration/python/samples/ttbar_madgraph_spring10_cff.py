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
        '/store/user/henderle/Spring10/TTbar_MAD/PATtuple_1_1.root',		
	'/store/user/henderle/Spring10/TTbar_MAD/PATtuple_2_1.root',
	'/store/user/henderle/Spring10/TTbar_MAD/PATtuple_3_1.root',
	'/store/user/henderle/Spring10/TTbar_MAD/PATtuple_4_1.root',
        '/store/user/henderle/Spring10/TTbar_MAD/PATtuple_5_1.root',		
	'/store/user/henderle/Spring10/TTbar_MAD/PATtuple_6_1.root',
	'/store/user/henderle/Spring10/TTbar_MAD/PATtuple_7_1.root',
	'/store/user/henderle/Spring10/TTbar_MAD/PATtuple_8_1.root',	
        '/store/user/henderle/Spring10/TTbar_MAD/PATtuple_9_1.root',
        '/store/user/henderle/Spring10/TTbar_MAD/PATtuple_10_1.root',    
        '/store/user/henderle/Spring10/TTbar_MAD/PATtuple_11_1.root',		
	'/store/user/henderle/Spring10/TTbar_MAD/PATtuple_12_1.root',
	'/store/user/henderle/Spring10/TTbar_MAD/PATtuple_13_1.root',
	'/store/user/henderle/Spring10/TTbar_MAD/PATtuple_14_1.root',
        '/store/user/henderle/Spring10/TTbar_MAD/PATtuple_15_1.root',		
	'/store/user/henderle/Spring10/TTbar_MAD/PATtuple_16_1.root',
	'/store/user/henderle/Spring10/TTbar_MAD/PATtuple_17_1.root',
	'/store/user/henderle/Spring10/TTbar_MAD/PATtuple_18_1.root',	
        '/store/user/henderle/Spring10/TTbar_MAD/PATtuple_19_1.root',
        '/store/user/henderle/Spring10/TTbar_MAD/PATtuple_20_1.root',    
        '/store/user/henderle/Spring10/TTbar_MAD/PATtuple_21_1.root',		
	'/store/user/henderle/Spring10/TTbar_MAD/PATtuple_22_1.root',
	'/store/user/henderle/Spring10/TTbar_MAD/PATtuple_23_1.root',
	'/store/user/henderle/Spring10/TTbar_MAD/PATtuple_24_1.root',
        '/store/user/henderle/Spring10/TTbar_MAD/PATtuple_25_1.root',		
	'/store/user/henderle/Spring10/TTbar_MAD/PATtuple_26_1.root',
	'/store/user/henderle/Spring10/TTbar_MAD/PATtuple_27_1.root',
	'/store/user/henderle/Spring10/TTbar_MAD/PATtuple_28_1.root',	
        '/store/user/henderle/Spring10/TTbar_MAD/PATtuple_29_1.root',
        '/store/user/henderle/Spring10/TTbar_MAD/PATtuple_30_1.root'							
       )
)
