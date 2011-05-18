import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/dammann/TTJets_TuneD6T_smallerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_9_2_16I.root',
       '/store/user/dammann/TTJets_TuneD6T_smallerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_8_1_Sq7.root',
       '/store/user/dammann/TTJets_TuneD6T_smallerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_7_1_CBW.root',
       '/store/user/dammann/TTJets_TuneD6T_smallerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_6_2_uBC.root',
       '/store/user/dammann/TTJets_TuneD6T_smallerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_5_1_pkz.root',
       '/store/user/dammann/TTJets_TuneD6T_smallerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_4_1_l4d.root',
       '/store/user/dammann/TTJets_TuneD6T_smallerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_3_1_RH2.root',
       '/store/user/dammann/TTJets_TuneD6T_smallerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_2_1_NtD.root',
       '/store/user/dammann/TTJets_TuneD6T_smallerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_27_1_bgy.root',
       '/store/user/dammann/TTJets_TuneD6T_smallerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_26_1_QAw.root',
       '/store/user/dammann/TTJets_TuneD6T_smallerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_25_1_w00.root',
       '/store/user/dammann/TTJets_TuneD6T_smallerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_24_1_tip.root',
       '/store/user/dammann/TTJets_TuneD6T_smallerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_23_2_8oy.root',
       '/store/user/dammann/TTJets_TuneD6T_smallerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_22_1_gvc.root',
       '/store/user/dammann/TTJets_TuneD6T_smallerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_21_1_uAY.root',
       '/store/user/dammann/TTJets_TuneD6T_smallerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_20_1_h6P.root',
       '/store/user/dammann/TTJets_TuneD6T_smallerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_1_1_KB4.root',
       '/store/user/dammann/TTJets_TuneD6T_smallerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_19_1_6Tu.root',
       '/store/user/dammann/TTJets_TuneD6T_smallerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_18_1_1Uu.root',
       '/store/user/dammann/TTJets_TuneD6T_smallerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_17_1_hqg.root',
       '/store/user/dammann/TTJets_TuneD6T_smallerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_16_1_6bE.root',
       '/store/user/dammann/TTJets_TuneD6T_smallerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_15_1_4br.root',
       '/store/user/dammann/TTJets_TuneD6T_smallerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_14_2_Ssp.root',
       '/store/user/dammann/TTJets_TuneD6T_smallerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_13_2_L2g.root',
       '/store/user/dammann/TTJets_TuneD6T_smallerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_12_1_9os.root',
       '/store/user/dammann/TTJets_TuneD6T_smallerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_11_1_Yh8.root',
       '/store/user/dammann/TTJets_TuneD6T_smallerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_10_1_tIv.root' ] );


secFiles.extend( [
               ] )

