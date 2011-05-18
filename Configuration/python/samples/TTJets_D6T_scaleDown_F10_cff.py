import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/dammann/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_9_1_1Eg.root',
       '/store/user/dammann/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_8_1_0bZ.root',
       '/store/user/dammann/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_7_2_tm6.root',
       '/store/user/dammann/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_6_1_0x4.root',
       '/store/user/dammann/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_5_2_EwF.root',
       '/store/user/dammann/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_4_1_Kr4.root',
       '/store/user/dammann/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_3_4_qGI.root',
       '/store/user/dammann/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_2_1_xPA.root',
       '/store/user/dammann/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_26_2_CPU.root',
       '/store/user/dammann/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_25_1_97Y.root',
       '/store/user/dammann/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_24_1_DYq.root',
       '/store/user/dammann/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_23_2_z6O.root',
       '/store/user/dammann/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_22_1_aX1.root',
       '/store/user/dammann/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_21_1_FQM.root',
       '/store/user/dammann/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_20_1_dm6.root',
       '/store/user/dammann/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_1_2_0sP.root',
       '/store/user/dammann/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_19_1_0Gf.root',
       '/store/user/dammann/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_18_1_d4P.root',
       '/store/user/dammann/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_17_1_HzY.root',
       '/store/user/dammann/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_16_1_aJ7.root',
       '/store/user/dammann/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_15_2_zyT.root',
       '/store/user/dammann/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_14_1_7n2.root',
       '/store/user/dammann/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_13_1_Jkt.root',
       '/store/user/dammann/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_12_1_XkJ.root',
       '/store/user/dammann/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_11_1_cvp.root',
       '/store/user/dammann/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_10_2_DAq.root' ] );


secFiles.extend( [
               ] )

