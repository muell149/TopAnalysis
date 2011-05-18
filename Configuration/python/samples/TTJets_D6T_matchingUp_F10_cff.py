import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/dammann/TTJets_TuneD6T_matchingup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_9_2_8yf.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_8_1_o5M.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_7_1_NIs.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_6_1_y0T.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_5_2_p7S.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_4_1_yU3.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_3_4_FAd.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_2_4_Ew2.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_23_1_MrM.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_22_1_Vrp.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_21_4_z69.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_20_1_lof.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_1_2_HWR.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_19_2_z7i.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_18_2_Lhn.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_17_1_VJz.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_16_2_P5B.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_15_4_LZm.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_14_4_CzT.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_13_1_zIP.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_12_1_7uc.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_11_1_wg0.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_10_1_KJ3.root' ] );


secFiles.extend( [
               ] )
