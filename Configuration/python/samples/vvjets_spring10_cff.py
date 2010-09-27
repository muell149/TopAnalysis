import FWCore.ParameterSet.Config as cms

######################################################################
#                                                                     
#  /VVJets-madgraph/Spring10-START3X_V26_S09-v1/GEN-SIM-RECO             
#                                                                     
# Events       :        4.8                                                                                     
# xsec(pb) NNLO:                                                      
# eff          :        1.0                                                    
######################################################################

source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(   
        '/store/user/dammann/36X/Spring10/VVjets_MadGraph/PATtuple_1_1.root',		
	'/store/user/dammann/36X/Spring10/VVjets_MadGraph/PATtuple_2_1.root',
	'/store/user/dammann/36X/Spring10/VVjets_MadGraph/PATtuple_3_1.root',
	'/store/user/dammann/36X/Spring10/VVjets_MadGraph/PATtuple_4_1.root',
        '/store/user/dammann/36X/Spring10/VVjets_MadGraph/PATtuple_5_1.root',		
	'/store/user/dammann/36X/Spring10/VVjets_MadGraph/PATtuple_6_1.root',
	'/store/user/dammann/36X/Spring10/VVjets_MadGraph/PATtuple_7_1.root',
	'/store/user/dammann/36X/Spring10/VVjets_MadGraph/PATtuple_8_1.root',	
        '/store/user/dammann/36X/Spring10/VVjets_MadGraph/PATtuple_9_1.root',
        '/store/user/dammann/36X/Spring10/VVjets_MadGraph/PATtuple_10_1.root',    
        '/store/user/dammann/36X/Spring10/VVjets_MadGraph/PATtuple_11_1.root'			
       )
)
