import FWCore.ParameterSet.Config as cms

########################################################################################### 
#
#  Contains PATtuples from Fall 10 MC: TTbar
#  
#  SPECIAL: Reco::muons were matched with genMuons from a t
#           using TopAnalysis.TopUtils.GenCandSelector_cfi 
# 
#  input samples: datasetpath=/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-START38_V12-v2/AODSIM
#
# 
#    number of events: 
#
#
############################################################################################

readFiles = cms.untracked.vstring()

source = cms.Source("PoolSource",
                     fileNames= readFiles
                   )

readFiles.extend( [        	
        '/store/user/jlange/samples/Fall10/Fall10TTbar-madgraph-D6T/PATtuple_10_1_bhc.root',
        '/store/user/jlange/samples/Fall10/Fall10TTbar-madgraph-D6T/PATtuple_11_1_kmi.root',	
        '/store/user/jlange/samples/Fall10/Fall10TTbar-madgraph-D6T/PATtuple_1_1_BwF.root',	
        '/store/user/jlange/samples/Fall10/Fall10TTbar-madgraph-D6T/PATtuple_12_1_wcN.root',	
        '/store/user/jlange/samples/Fall10/Fall10TTbar-madgraph-D6T/PATtuple_13_1_mSd.root',	
        '/store/user/jlange/samples/Fall10/Fall10TTbar-madgraph-D6T/PATtuple_14_1_wXx.root',
        '/store/user/jlange/samples/Fall10/Fall10TTbar-madgraph-D6T/PATtuple_15_1_3ef.root',	
        '/store/user/jlange/samples/Fall10/Fall10TTbar-madgraph-D6T/PATtuple_16_1_qBX.root',	
        '/store/user/jlange/samples/Fall10/Fall10TTbar-madgraph-D6T/PATtuple_17_1_w7D.root',	
        '/store/user/jlange/samples/Fall10/Fall10TTbar-madgraph-D6T/PATtuple_18_1_O7L.root',
        '/store/user/jlange/samples/Fall10/Fall10TTbar-madgraph-D6T/PATtuple_19_1_0p4.root',	
        '/store/user/jlange/samples/Fall10/Fall10TTbar-madgraph-D6T/PATtuple_20_1_CX3.root',	
        '/store/user/jlange/samples/Fall10/Fall10TTbar-madgraph-D6T/PATtuple_21_1_5Yt.root',	
        '/store/user/jlange/samples/Fall10/Fall10TTbar-madgraph-D6T/PATtuple_2_1_UiX.root',	
        '/store/user/jlange/samples/Fall10/Fall10TTbar-madgraph-D6T/PATtuple_22_1_8OH.root',
        '/store/user/jlange/samples/Fall10/Fall10TTbar-madgraph-D6T/PATtuple_23_1_QQn.root',	
        '/store/user/jlange/samples/Fall10/Fall10TTbar-madgraph-D6T/PATtuple_24_1_fhj.root',	
        '/store/user/jlange/samples/Fall10/Fall10TTbar-madgraph-D6T/PATtuple_25_1_Tyg.root',
        '/store/user/jlange/samples/Fall10/Fall10TTbar-madgraph-D6T/PATtuple_26_1_tIj.root',	
        '/store/user/jlange/samples/Fall10/Fall10TTbar-madgraph-D6T/PATtuple_27_1_Gze.root',	
        '/store/user/jlange/samples/Fall10/Fall10TTbar-madgraph-D6T/PATtuple_28_1_QVM.root',	
        '/store/user/jlange/samples/Fall10/Fall10TTbar-madgraph-D6T/PATtuple_29_1_If1.root',	
        '/store/user/jlange/samples/Fall10/Fall10TTbar-madgraph-D6T/PATtuple_30_1_nte.root',
        '/store/user/jlange/samples/Fall10/Fall10TTbar-madgraph-D6T/PATtuple_3_1_jS9.root',	
        '/store/user/jlange/samples/Fall10/Fall10TTbar-madgraph-D6T/PATtuple_4_1_SZ0.root',	
        '/store/user/jlange/samples/Fall10/Fall10TTbar-madgraph-D6T/PATtuple_5_1_vKP.root',	
        '/store/user/jlange/samples/Fall10/Fall10TTbar-madgraph-D6T/PATtuple_6_1_mnu.root',
        '/store/user/jlange/samples/Fall10/Fall10TTbar-madgraph-D6T/PATtuple_7_1_hpf.root',	
        '/store/user/jlange/samples/Fall10/Fall10TTbar-madgraph-D6T/PATtuple_8_1_0dB.root',	
        '/store/user/jlange/samples/Fall10/Fall10TTbar-madgraph-D6T/PATtuple_9_1_yxo.root'
	] );


















