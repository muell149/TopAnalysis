import FWCore.ParameterSet.Config as cms

###########################################################################################
#  
#  NOT YET COMPLETE!!! SEE COMMENTED FILES!
#
#  Contains the Data of the Jun14th reprocessing and PromptReco_v4 data taken after that
#  (+ Jul16thReReco which contains sone duplicate events (not my fault, it's CRAP!))     
#
#          global tag: GR_R_36X_V12::All
# 
#       input samples: /MinimumBias/Commissioning10-SD_Mu-Jun14thSkim_v1/RECO
#                      /Mu/Run2010A-Jun14thReReco_v1/RECO
#                      /Mu/Run2010A-Jul16thReReco-v1/RECO
#                      /Mu/Run2010A-PromptReco-v4/RECO 
#
#           json file: for Jun14th samples:
#                      Cert_132440-137028_7TeV_June14thReReco_Collisions10_JSON_TopFiltered_July11th.txt
#                      for Jul16thReReco:
#                      Cert_139779-1340159_7TeV_July16thReReco_Collisions10_JSON.txt
#                      for PromptReco v4:
#                      Cert_132440-140399_7TeV_StreamExpress_Collisions10_JSON.txt
#															     
#  integrated HF lumi: 212.8/nb (until now, ~253.6/nb when complete)                                                                                                                  
#
#    number of events: 1295110
#
#        preselection: general qualtity cuts (see below)  AND 
#                      ( 1 global muon with pt > 5GeV  OR  2 global muons )
#
#            cut flow:                 
#			  before:		  after:
#    primVtxFilter:       7671920                 7156371
#  beamScrapFilter:       7156371                 7156362
#  HBHENoiseFilter:       7156362                 7154451
#
#      oneHardMuon:       7154451                 1284981
#   twoGlobalMuons:       7154451                 97619
#
###########################################################################################

readFiles = cms.untracked.vstring()

source = cms.Source("PoolSource",
                     fileNames= readFiles
                   )

## Commissioning10 Jun14thSkim: 6.959400/nb

readFiles.extend( [        	
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thSkim_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thSkim_2.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thSkim_3.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thSkim_4.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thSkim_5.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thSkim_6.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thSkim_7.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thSkim_8.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thSkim_9.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thSkim_10.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thSkim_11.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thSkim_12.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thSkim_13.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thSkim_14.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thSkim_15.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thSkim_16.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thSkim_17.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thSkim_18.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thSkim_19.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thSkim_20.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thSkim_21.root'] );


## Jun14thReReco: 4.924282/nb

readFiles.extend( [	        
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thReReco_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thReReco_2.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thReReco_3.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thReReco_4.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thReReco_5.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thReReco_6.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thReReco_7.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thReReco_8.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thReReco_9.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thReReco_10.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thReReco_11.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thReReco_12.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thReReco_13.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thReReco_14.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thReReco_15.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thReReco_16.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thReReco_17.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thReReco_18.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thReReco_19.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thReReco_20.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thReReco_21.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thReReco_22.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thReReco_23.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thReReco_24.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jun14thReReco_25.root'] );	


## Jul16thReReco: 110.701881 (till now) 

readFiles.extend( [	        
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_1_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_2_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_3_2.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_4_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_5_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_6_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_7_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_8_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_9_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_10_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_11_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_12_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_13_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_14_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_15_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_16_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_17_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_18_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_19_1.root',		
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_20_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_21_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_22_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_23_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_24_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_25_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_26_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_27_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_28_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_29_1.root',		
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_30_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_31_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_32_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_33_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_34_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_35_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_36_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_37_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_38_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_39_1.root',		
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_40_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_41_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_42_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_43_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_44_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_45_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_46_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_47_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_48_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_49_1.root',		
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_50_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_51_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_52_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_53_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_54_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_55_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_56_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_57_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_58_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_59_1.root',			
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_60_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_61_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_62_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_63_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_64_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_65_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_66_1.root',	
        #'/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_67_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_68_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_69_1.root',			
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_70_1.root',	
        #'/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_71_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_72_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_73_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_74_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_75_4.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_76_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_77_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_78_1.root',	
        #'/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_79_1.root',			
        #'/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_80_1.root',	
        #'/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_81_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_82_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_83_1.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_84_2.root',	
        '/store/user/dammann/36X/Collisions10/Jul20/Jul16thReReco_85_2.root'] );	


## PromptReco_v4: 90.215801 (till now)

readFiles.extend( [	
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_1_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_2_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_3_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_4_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_5_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_6_1.root',
        #'/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_7_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_8_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_9_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_10_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_11_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_12_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_13_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_14_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_15_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_16_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_17_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_18_1.root',
        #'/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_19_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_20_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_21_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_22_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_23_1.root',
        #'/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_24_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_25_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_26_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_27_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_28_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_29_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_30_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_31_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_32_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_33_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_34_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_35_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_36_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_37_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_38_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_39_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_40_2.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_41_1.root',
        #'/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_42_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_43_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_44_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_45_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_46_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_47_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_48_2.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_49_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_50_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_51_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_52_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_53_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_54_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_55_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_56_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_57_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_58_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_59_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_60_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_61_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_62_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_63_2.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_64_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_65_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_66_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_67_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_68_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_69_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_70_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_71_1.root',
        #'/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_72_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_73_2.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_74_1.root',
        #'/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_75_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_76_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_77_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_78_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_79_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_80_1.root',
        #'/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_81_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_82_1.root',
        #'/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_83_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_84_1.root',
        #'/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_85_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_86_1.root',
        #'/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_87_1.root',
        #'/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_88_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_89_1.root',
        #'/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_90_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_91_1.root',
        #'/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_92_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_93_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_94_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_95_1.root',
        #'/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_96_1.root',
        #'/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_97_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_98_1.root',
        #'/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_99_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_100_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_101_1.root',
        #'/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_102_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_103_1.root',
        #'/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_104_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_105_2.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_106_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_107_1.root',
        #'/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_108_1.root',
        #'/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_109_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_110_1.root',
        #'/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_111_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_112_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_113_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_114_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_115_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_116_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_117_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_118_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_119_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_120_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_121_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_122_1.root',
        #'/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_123_1.root',
        #'/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_124_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_125_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_126_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_127_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_128_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_129_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_130_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_131_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_132_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_133_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_134_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_135_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_136_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_137_2.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_138_1.root',
        #'/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_139_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_140_2.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_141_1.root',
        #'/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_142_1.root',
        #'/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_143_1.root',
        '/store/user/dammann/36X/Collisions10/Jul20/Run2010A_PromptReco_v4aachen_144_1.root'] );            
