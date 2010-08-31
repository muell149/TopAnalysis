import FWCore.ParameterSet.Config as cms

######################################################################
#                                                                     
#               
#                                                                     
# Events      :                                                
# xsec(pb) NLO:          4                                                
# eff         :        1.0                                                    
######################################################################

source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(   
        '/store/user/henderle/Spring10/sTopS_MAD_new/PATtuple_1_1.root',		
	'/store/user/henderle/Spring10/sTopS_MAD_new/PATtuple_2_1.root',
	'/store/user/henderle/Spring10/sTopS_MAD_new/PATtuple_3_1.root',
	'/store/user/henderle/Spring10/sTopS_MAD_new/PATtuple_4_1.root',
        '/store/user/henderle/Spring10/sTopS_MAD_new/PATtuple_5_1.root',		
	'/store/user/henderle/Spring10/sTopS_MAD_new/PATtuple_6_1.root',
	'/store/user/henderle/Spring10/sTopS_MAD_new/PATtuple_7_1.root',
	'/store/user/henderle/Spring10/sTopS_MAD_new/PATtuple_8_1.root',	
        '/store/user/henderle/Spring10/sTopS_MAD_new/PATtuple_9_1.root'						
       )
)
