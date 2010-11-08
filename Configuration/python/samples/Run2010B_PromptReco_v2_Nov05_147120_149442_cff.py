import FWCore.ParameterSet.Config as cms

############################################################################################################################################
#                                                                     
#  Contains the Data of the Run2010B-PromptReco_v2 certified till November 5th 2010 starting at run 147120   
#
#          global tag: GR_R_38X_V13::All
#
#        dataset name: /Mu/wbehrenh-Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442-fef863c8192a8efb8d7e9f5d09b27da1/USER
#             DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
# 
#       input sample: /Mu/Run2010B-PromptReco_v2/AOD
#
#           json file: subset of Cert_132440-148864_7TeV_StreamExpress_Collisions10_JSON.txt
#															     
#  integrated HF lumi: 27.257001402/pb                                                                                     
#
#    number of events: 5402078
#
#        preselection: ( HLT_Mu9  OR  HLT_Mu 11 OR HLT_Mu15 )  AND  (beam scrap and HCAL noise cuts, PV)
#
#            cut flow:  
#TrigReport ---------- Event  Summary ------------
#TrigReport Events total =19995428 passed =5402078 failed =14593350

#TrigReport ---------- Path   Summary ------------
#TrigReport  Trig Bit#        Run     Passed     Failed      Error Name
#TrigReport   218    0   19995428     860261   19135167          0 hltMu9Path
#TrigReport   218  218   19995428    3194050   16801378          0 hltMu11Path
#TrigReport   218  436   19995428    2721959   17273469          0 hltMu15Path

#TrigReport ---------- Modules in Path: hltMu9Path ------------
#TrigReport  Trig Bit#    Visited     Passed     Failed      Error Name
#TrigReport   218    0   19995428     861295   19134133          0 filterHltMu9
#TrigReport   218    0     861295     861291          4          0 beamScrapFilter
#TrigReport   218    0     861291     860639        652          0 HBHENoiseFilter
#TrigReport   218    0     860639     860261        378          0 primaryVertexFilter

#TrigReport ---------- Modules in Path: hltMu11Path ------------
#TrigReport  Trig Bit#    Visited     Passed     Failed      Error Name
#TrigReport   218  218   19995428    3198952   16796476          0 filterHltMu11
#TrigReport   218  218    3198952    3198941         11          0 beamScrapFilter
#TrigReport   218  218    3198941    3195975       2966          0 HBHENoiseFilter
#TrigReport   218  218    3195975    3194050       1925          0 primaryVertexFilter

#TrigReport ---------- Modules in Path: hltMu15Path ------------
#TrigReport  Trig Bit#    Visited     Passed     Failed      Error Name
#TrigReport   218  436   19995428    2728125   17267303          0 filterHltMu15
#TrigReport   218  436    2728125    2728098         27          0 beamScrapFilter
#TrigReport   218  436    2728098    2724628       3470          0 HBHENoiseFilter
#TrigReport   218  436    2724628    2721959       2669          0 primaryVertexFilter

############################################################################################################################################

source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(  
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_9_1_qYD.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_99_1_Vfm.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_98_1_YoU.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_97_1_HJ3.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_96_1_kp0.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_95_1_QGI.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_94_1_4hy.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_93_1_kuD.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_92_1_Kr6.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_91_1_sQN.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_90_1_sh6.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_8_1_bhZ.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_89_1_HOf.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_88_1_35n.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_87_1_Xou.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_86_1_p4n.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_85_1_6XT.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_84_1_R1W.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_83_1_rLd.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_82_1_gqr.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_81_1_0SR.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_80_1_LST.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_7_1_qtT.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_79_1_p0P.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_78_1_f76.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_77_1_8IB.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_76_1_ueE.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_75_1_X3b.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_74_1_3OU.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_73_1_PJs.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_72_1_abg.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_71_1_BvN.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_70_1_lFE.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_6_1_RAg.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_69_1_SgM.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_68_1_d3K.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_67_1_zst.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_66_1_3AM.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_65_1_0Nb.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_64_1_Bi2.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_63_1_h1d.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_62_1_2mM.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_61_1_hIH.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_60_1_v0G.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_5_1_VJC.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_59_1_FPt.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_58_1_XnV.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_57_1_YvH.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_56_1_Lcw.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_55_1_lex.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_54_1_XHx.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_53_1_2bl.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_52_1_Frk.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_51_1_tJY.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_50_1_iKz.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_4_1_jCD.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_49_1_How.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_48_1_7g4.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_47_1_L1h.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_46_1_koC.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_45_1_rNT.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_44_1_MFW.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_43_1_BAb.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_42_1_9cE.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_41_1_4m3.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_40_1_4ed.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_3_1_hKh.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_39_1_64B.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_38_1_U1M.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_37_1_igw.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_36_1_EUi.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_35_1_hTa.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_34_1_6Sk.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_33_1_X2d.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_32_1_uCi.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_31_1_kzQ.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_30_1_lAk.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_2_1_NDn.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_29_1_BgR.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_28_1_iqB.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_27_1_Ggv.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_26_1_8Aj.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_25_1_vq5.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_24_1_HzF.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_23_1_quB.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_22_1_tlq.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_21_1_QkE.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_218_1_X3f.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_217_1_ff1.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_216_1_ynW.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_215_1_ML5.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_214_1_FYh.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_213_1_5kK.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_212_1_pSU.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_211_1_Na7.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_210_1_z5i.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_20_1_tYJ.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_209_1_JQ5.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_208_1_yya.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_207_1_ORN.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_206_1_AIT.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_205_1_GrX.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_204_1_2yr.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_203_1_DaJ.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_202_1_l0e.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_201_1_8Al.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_200_1_fnM.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_1_1_XW1.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_19_1_ZIM.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_199_1_W5O.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_198_1_loL.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_197_1_DwB.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_196_1_4KM.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_195_1_Kj5.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_194_1_HOA.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_193_1_U30.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_192_1_QIo.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_191_1_hEe.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_190_1_F4R.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_18_1_3aW.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_189_1_BVb.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_188_1_Zkx.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_187_1_NLe.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_186_1_3e6.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_185_1_a67.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_184_1_WQR.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_183_1_oNP.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_182_1_qDi.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_181_1_Uhy.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_180_1_bXO.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_17_1_OTA.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_179_1_70H.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_178_1_dpq.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_177_1_2iX.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_176_1_ZJg.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_175_1_TWs.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_174_1_Fj9.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_173_1_Jrq.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_172_1_eX3.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_171_1_LJO.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_170_1_xs5.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_16_1_XLt.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_169_1_Wvu.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_168_1_IB6.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_167_1_qjc.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_166_1_2aQ.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_165_1_P8J.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_164_1_XMC.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_163_1_zca.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_162_1_1ZJ.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_161_1_gZl.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_160_1_NdE.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_15_1_glK.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_159_1_Owr.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_158_1_Kz2.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_157_1_THN.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_156_1_fxn.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_155_1_aM5.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_154_1_d6O.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_153_1_MkL.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_152_1_cHe.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_151_1_mmF.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_150_1_F6C.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_14_1_eSG.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_149_1_ukv.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_148_1_el1.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_147_1_0t0.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_146_1_6Pt.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_145_1_Eqx.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_144_1_SIa.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_143_1_YhJ.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_142_1_tds.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_141_1_mYJ.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_140_1_4Ld.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_13_1_VJG.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_139_2_zPL.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_138_1_PY2.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_137_2_QvH.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_136_2_vJr.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_135_1_yQv.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_134_1_KJ3.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_133_1_tJA.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_132_2_NS2.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_131_1_H2S.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_130_1_Ba3.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_12_1_w8A.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_129_1_iSf.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_128_1_3G7.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_127_2_aOt.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_126_1_l4Q.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_125_1_srs.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_124_1_5pm.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_123_1_TH5.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_122_1_TDM.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_121_1_LJZ.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_120_1_w7d.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_11_1_dFX.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_119_1_K3o.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_118_1_DZe.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_117_1_yVz.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_116_1_83y.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_115_1_yAc.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_114_1_1kC.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_113_1_lIt.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_112_1_GAC.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_111_1_zQR.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_110_1_Hsc.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_10_1_rMT.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_109_1_96Q.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_108_1_QK5.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_107_1_vxJ.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_106_1_36w.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_105_1_MLE.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_104_1_HZP.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_103_1_CDG.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_102_1_TUx.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_101_1_siL.root',
       '/store/user/wbehrenh/Mu/Run2010B-PromptReco-HLT-Nov05-PAT-147120-149442/fef863c8192a8efb8d7e9f5d09b27da1/Run2010B_PromptReco_v2_HLT_100_1_UUd.root'
    )
)
