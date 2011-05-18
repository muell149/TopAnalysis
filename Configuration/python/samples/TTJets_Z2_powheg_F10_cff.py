import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/dammann/TTTo2L2Nu2B_7TeV-powheg-pythia6/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_9_2_pea.root',
       '/store/user/dammann/TTTo2L2Nu2B_7TeV-powheg-pythia6/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_8_1_Eub.root',
       '/store/user/dammann/TTTo2L2Nu2B_7TeV-powheg-pythia6/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_7_1_u0s.root',
       '/store/user/dammann/TTTo2L2Nu2B_7TeV-powheg-pythia6/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_6_2_f0W.root',
       '/store/user/dammann/TTTo2L2Nu2B_7TeV-powheg-pythia6/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_5_1_tIt.root',
       '/store/user/dammann/TTTo2L2Nu2B_7TeV-powheg-pythia6/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_4_1_BHB.root',
       '/store/user/dammann/TTTo2L2Nu2B_7TeV-powheg-pythia6/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_3_1_6XG.root',
       '/store/user/dammann/TTTo2L2Nu2B_7TeV-powheg-pythia6/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_2_2_cdC.root',
       '/store/user/dammann/TTTo2L2Nu2B_7TeV-powheg-pythia6/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_22_2_1I1.root',
       '/store/user/dammann/TTTo2L2Nu2B_7TeV-powheg-pythia6/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_21_2_m33.root',
       '/store/user/dammann/TTTo2L2Nu2B_7TeV-powheg-pythia6/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_20_1_KZW.root',
       '/store/user/dammann/TTTo2L2Nu2B_7TeV-powheg-pythia6/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_1_1_t4L.root',
       '/store/user/dammann/TTTo2L2Nu2B_7TeV-powheg-pythia6/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_19_1_xko.root',
       '/store/user/dammann/TTTo2L2Nu2B_7TeV-powheg-pythia6/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_18_2_uA0.root',
       '/store/user/dammann/TTTo2L2Nu2B_7TeV-powheg-pythia6/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_17_1_ssy.root',
       '/store/user/dammann/TTTo2L2Nu2B_7TeV-powheg-pythia6/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_16_1_6fQ.root',
       '/store/user/dammann/TTTo2L2Nu2B_7TeV-powheg-pythia6/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_15_1_vts.root',
       '/store/user/dammann/TTTo2L2Nu2B_7TeV-powheg-pythia6/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_14_1_u7U.root',
       '/store/user/dammann/TTTo2L2Nu2B_7TeV-powheg-pythia6/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_13_2_rag.root',
       '/store/user/dammann/TTTo2L2Nu2B_7TeV-powheg-pythia6/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_12_1_APP.root',
       '/store/user/dammann/TTTo2L2Nu2B_7TeV-powheg-pythia6/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_11_1_uOi.root',
       '/store/user/dammann/TTTo2L2Nu2B_7TeV-powheg-pythia6/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_10_2_Mh5.root' ] );


secFiles.extend( [
               ] )

