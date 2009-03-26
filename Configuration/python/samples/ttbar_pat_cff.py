import FWCore.ParameterSet.Config as cms

source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        '/store/user/rwolf/ttbar/patTuple_ttbar_madgraph_1.root',
        '/store/user/rwolf/ttbar/patTuple_ttbar_madgraph_2.root',
        '/store/user/rwolf/ttbar/patTuple_ttbar_madgraph_3.root',
        '/store/user/rwolf/ttbar/patTuple_ttbar_madgraph_4.root',	
        '/store/user/rwolf/ttbar/patTuple_ttbar_madgraph_5.root',
        '/store/user/rwolf/ttbar/patTuple_ttbar_madgraph_6.root',	
        '/store/user/rwolf/ttbar/patTuple_ttbar_madgraph_7.root',
        '/store/user/rwolf/ttbar/patTuple_ttbar_madgraph_8.root',	
        '/store/user/rwolf/ttbar/patTuple_ttbar_madgraph_9.root',
        '/store/user/rwolf/ttbar/patTuple_ttbar_madgraph_10.root',
        '/store/user/rwolf/ttbar/patTuple_ttbar_madgraph_11.root',
        '/store/user/rwolf/ttbar/patTuple_ttbar_madgraph_12.root',	
        '/store/user/rwolf/ttbar/patTuple_ttbar_madgraph_13.root',
        '/store/user/rwolf/ttbar/patTuple_ttbar_madgraph_14.root',	
        '/store/user/rwolf/ttbar/patTuple_ttbar_madgraph_15.root'		
    )
)
