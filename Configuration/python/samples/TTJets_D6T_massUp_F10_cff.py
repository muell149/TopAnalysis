import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/dammann/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_9_1_GZB.root',
       '/store/user/dammann/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_8_1_fwh.root',
       '/store/user/dammann/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_7_1_ql4.root',
       '/store/user/dammann/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_6_1_olR.root',
       '/store/user/dammann/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_5_1_MpQ.root',
       '/store/user/dammann/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_4_2_2xf.root',
       '/store/user/dammann/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_3_1_yzO.root',
       '/store/user/dammann/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_2_1_v0v.root',
       '/store/user/dammann/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_1_1_Fzs.root',
       '/store/user/dammann/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_13_1_gm7.root',
       '/store/user/dammann/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_12_1_fkU.root',
       '/store/user/dammann/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_11_1_NBL.root',
       '/store/user/dammann/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_10_1_dM2.root' ] );


secFiles.extend( [
               ] )

