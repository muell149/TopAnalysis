import FWCore.ParameterSet.Config as cms

filterTrigger = cms.EDAnalyzer("TriggerFilter",

    TriggerResults = cms.InputTag('TriggerResults','','HLT'),
    hltPaths       = cms.vstring('HLT_L1MuOpen',
				 'HLT_L1MuOpen_NoBPTX',
				 'HLT_L1Mu',
				 'HLT_L1Mu20',
				 'HLT_L2Mu9',
				 'HLT_L2Mu11',
				 'HLT_IsoMu3',
				 'HLT_Mu3',
				 'HLT_Mu5',
				 'HLT_Mu9',				 
				 'HLT_L1DoubleMuOpen',
				 'HLT_DoubleMu0',
				 'HLT_DoubleMu3',
				 'HLT_Mu0_L1MuOpen',
				 'HLT_Mu3_L1MuOpen',
				 'HLT_Mu5_L1MuOpen'
				)
)
