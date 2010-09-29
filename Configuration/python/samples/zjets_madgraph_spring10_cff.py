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
        '/store/user/henderle/Spring10/ZJets_MAD/PATtuple_1_1.root',		
	'/store/user/henderle/Spring10/ZJets_MAD/PATtuple_2_2.root',
	'/store/user/henderle/Spring10/ZJets_MAD/PATtuple_3_2.root',
	'/store/user/henderle/Spring10/ZJets_MAD/PATtuple_4_1.root',
        '/store/user/henderle/Spring10/ZJets_MAD/PATtuple_5_2.root',		
	'/store/user/henderle/Spring10/ZJets_MAD/PATtuple_6_1.root',
	'/store/user/henderle/Spring10/ZJets_MAD/PATtuple_7_1.root',
	'/store/user/henderle/Spring10/ZJets_MAD/PATtuple_8_1.root',	
        '/store/user/henderle/Spring10/ZJets_MAD/PATtuple_9_1.root',
        '/store/user/henderle/Spring10/ZJets_MAD/PATtuple_10_2.root',    
        '/store/user/henderle/Spring10/ZJets_MAD/PATtuple_11_2.root',		
	'/store/user/henderle/Spring10/ZJets_MAD/PATtuple_12_2.root',
	'/store/user/henderle/Spring10/ZJets_MAD/PATtuple_13_2.root',
	'/store/user/henderle/Spring10/ZJets_MAD/PATtuple_14_1.root',
        '/store/user/henderle/Spring10/ZJets_MAD/PATtuple_15_2.root',		
	'/store/user/henderle/Spring10/ZJets_MAD/PATtuple_16_1.root',
	'/store/user/henderle/Spring10/ZJets_MAD/PATtuple_17_1.root',
	'/store/user/henderle/Spring10/ZJets_MAD/PATtuple_18_1.root',	
        '/store/user/henderle/Spring10/ZJets_MAD/PATtuple_19_2.root',
        '/store/user/henderle/Spring10/ZJets_MAD/PATtuple_20_1.root',    
        '/store/user/henderle/Spring10/ZJets_MAD/PATtuple_21_2.root',		
	'/store/user/henderle/Spring10/ZJets_MAD/PATtuple_22_1.root'						
       )
)
