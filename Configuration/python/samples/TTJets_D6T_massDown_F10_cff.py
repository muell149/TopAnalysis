import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/dammann/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_9_1_Zxa.root',
       '/store/user/dammann/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_8_1_woz.root',
       '/store/user/dammann/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_7_1_r2E.root',
       '/store/user/dammann/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_6_1_Nyy.root',
       '/store/user/dammann/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_5_1_OM4.root',
       '/store/user/dammann/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_4_1_lta.root',
       '/store/user/dammann/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_3_1_Qd9.root',
       '/store/user/dammann/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_2_1_cYj.root',
       '/store/user/dammann/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_1_1_5Zg.root',
       '/store/user/dammann/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_14_1_tC9.root',
       '/store/user/dammann/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_13_1_5B6.root',
       '/store/user/dammann/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_12_1_Or7.root',
       '/store/user/dammann/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_11_1_Sn8.root',
       '/store/user/dammann/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_10_1_8Sx.root' ] );


secFiles.extend( [
               ] )

