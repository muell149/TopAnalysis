import FWCore.ParameterSet.Config as cms

###########################################################################################
#  
#  NOT YET COMPLETE!!! SEE COMMENTED FILES!
#
#  Contains the Data of the Jun14th reprocessing and PromptReco_v4 data taken after that
#
#          global tag: GR_R_36X_V12::All
# 
#       input samples: /MinimumBias/Commissioning10-SD_Mu-Jun14thSkim_v1/RECO
#                      /Mu/Run2010A-Jun14thReReco_v1/RECO
#                      /Mu/Run2010A-PromptReco-v4/RECO 
#
#           json file: for Jun14th samples:
#                      Cert_132440-137028_7TeV_June14thReReco_Collisions10_JSON_TopFiltered_July11th.txt
#                      for PromptReco till run 139790:
#                      Cert_132440-139790_7TeV_StreamExpress_Collisions10_JSON_TopFiltered_July11th.txt 
#                      for PromptReco run 139791 - 140076:
#                      subset of: Cert_132440-140076_7TeV_StreamExpress_Collisions10_JSON.txt
#                      for PromptReco run 140077 - 140339:
#		       subset of: Cert_132440-140339_7TeV_StreamExpress_Collisions10_JSON.txt
#															     
#  integrated HF lumi: 98.860/nb (until now, ~180/nb when ready)                                                                                                                  
#
#    number of events: 655722
#
#        preselection: general qualtity cuts (see below)  AND 
#                      ( 1 global muon with pt > 5GeV  OR  2 global muons )
#
#            cut flow:                 
#				  before:		  after:
#	    primVtxFilter:	  5509313		  5114902
#	  beamScrapFilter:	  5114902		  5114897
#	  HBHENoiseFilter:	  5114897		  5113613
#
#	      oneHardMuon:	  5113613		   622643
#	   twoGlobalMuons:	  5113613		    61834
#  	 	   
###########################################################################################

source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(

        ## Commissioning10 Jun14thSkim: 6.959400/nb	
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_naf_1_1.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_naf_2_1.root',	
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_naf_3_1.root',	
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_naf_4_1.root',	
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_naf_5_1.root',	
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_naf_6_1.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_naf_7_1.root',	
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_naf_8_1.root',	
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_naf_9_1.root',	
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_naf_10_1.root',	
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_naf_11_1.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_naf_12_1.root',	
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_naf_13_1.root',	
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_naf_14_1.root',	
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_naf_15_1.root',	
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_naf_16_1.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_naf_17_1.root',	
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_naf_18_1.root',	
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_naf_19_1.root',	
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_naf_20_1.root',	
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_naf_21_1.root',	
	
        ## Jun14thReReco: 3.460186/nb
        '/store/user/dammann/36X/Collisions10/Jun14thReReco_naf_1_1.root',
        '/store/user/dammann/36X/Collisions10/Jun14thReReco_naf_2_1.root',	
        '/store/user/dammann/36X/Collisions10/Jun14thReReco_naf_3_1.root',	
        #'/store/user/dammann/36X/Collisions10/Jun14thReReco_naf_4_2.root',	
        '/store/user/dammann/36X/Collisions10/Jun14thReReco_naf_5_1.root',	
        '/store/user/dammann/36X/Collisions10/Jun14thReReco_naf_6_1.root',	
        #'/store/user/dammann/36X/Collisions10/Jun14thReReco_naf_7_2.root',	
        '/store/user/dammann/36X/Collisions10/Jun14thReReco_naf_8_1.root',	
        '/store/user/dammann/36X/Collisions10/Jun14thReReco_naf_9_1.root',	
        '/store/user/dammann/36X/Collisions10/Jun14thReReco_naf_10_1.root',		

        ## PromptReco till run 139790: 56.875070/nb
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_1_1.root',
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_2_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_3_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_4_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_5_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_6_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_7_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_8_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_9_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_10_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_11_1.root',
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_12_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_13_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_14_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_15_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_16_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_17_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_18_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_19_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_20_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_21_1.root',
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_22_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_23_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_24_2.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_25_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_26_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_27_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_28_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_29_1.root',	
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_30_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_31_1.root',
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_32_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_33_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_34_1.root',	
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_35_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_36_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_37_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_38_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_39_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_40_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_41_2.root',
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_42_1.root',	
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_43_1.root',	
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_44_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_45_1.root',	
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_46_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_47_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_48_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_49_2.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_50_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_51_2.root',
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_52_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_53_1.root',	
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_54_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_55_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_56_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_57_1.root',	
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_58_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_59_1.root',	
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_60_1.root',	
	'/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_61_2.root',
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_62_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_63_1.root',	
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_64_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4_naf_65_1.root',
	
	## PromptReco till run 140076: 31.565489/nb
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4a_naf_1_1.root',
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4a_naf_2_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4a_naf_3_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4a_naf_4_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4a_naf_5_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4a_naf_6_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4a_naf_7_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4a_naf_8_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4a_naf_9_1.root',	
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4a_naf_10_1.root',	
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4a_naf_11_1.root',
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4a_naf_12_1.root',	
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4a_naf_13_1.root'#,	
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4a_naf_14_1.root',	
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4a_naf_15_1.root',	
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4a_naf_16_1.root'	
	
        ## PromptReco till run 140399: 0/nb 
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4b_naf_1_1.root',
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4b_naf_2_1.root',	 
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4b_naf_3_1.root',	 
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4b_naf_4_1.root',	 
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4b_naf_5_1.root',	 
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4b_naf_6_1.root',	 
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4b_naf_7_1.root',	 
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4b_naf_8_1.root',	 
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4b_naf_9_1.root',	 
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4b_naf_10_1.root',	 
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4b_naf_11_1.root',
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4b_naf_12_1.root',	 
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4b_naf_13_1.root',	 
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4b_naf_14_1.root',	 
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4b_naf_15_1.root',	 
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4b_naf_16_1.root',	 
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4b_naf_17_1.root',	 
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4b_naf_18_1.root',	 
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4b_naf_19_1.root',	 
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4b_naf_20_1.root',	 
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4b_naf_21_1.root',
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4b_naf_22_1.root',	 
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4b_naf_23_1.root',	 
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4b_naf_24_1.root',	 
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4b_naf_25_1.root',	 
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4b_naf_26_1.root',	 
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4b_naf_27_1.root',	 
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4b_naf_28_1.root',	 
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4b_naf_29_1.root',	 
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4b_naf_30_1.root',	 
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4b_naf_31_1.root',
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4b_naf_32_1.root',	 
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4b_naf_33_1.root',	 
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4b_naf_34_1.root',	 
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4b_naf_35_1.root',	 
        #'/store/user/dammann/36X/Collisions10/MuRun2010A_v4b_naf_36_1.root',	 
		
       )
)
