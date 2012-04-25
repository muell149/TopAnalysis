import FWCore.ParameterSet.Config as cms

mumuTriggers = cms.vstring( 'HLT_DoubleMu6_v*',
                            'HLT_DoubleMu7_v*',
                            'HLT_Mu13_Mu8_v*',
                            'HLT_Mu17_Mu8_v*',
                            'HLT_DoubleMu45_v*'
                            )
emuTriggers  = cms.vstring( 'HLT_Mu10_Ele10_CaloIdL_*',
                            'HLT_Mu8_Ele17_CaloIdL_*',
                            'HLT_Mu17_Ele8_CaloIdL_*',
                            'HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_v*',
                            'HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_v*',
                            'HLT_Mu10_Ele10_CaloIdL_v*'
                            )
eeTriggers   = cms.vstring( 'HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v*',
                            'HLT_Ele17_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_v*',
                            'HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v*',
                            'HLT_DoubleEle45_CaloIdL_v*'
                            )

METTriggers  = cms.vstring( 'HLT_CentralJet80_MET100_v*',
                            'HLT_CentralJet80_MET110_v*',
                            'HLT_CentralJet80_MET160_v*',
                            'HLT_CentralJet80_MET65_v*',
                            'HLT_CentralJet80_MET80_v*',
                            'HLT_CentralJet80_MET95_v*',
                            'HLT_DiCentralJet20_MET100_HBHENoiseFiltered_v*',
                            'HLT_DiCentralJet20_MET80_v*',
                            'HLT_DiJet60_MET45_v*',
                            'HLT_MET100_v*',
                            'HLT_MET120_v*',
                            'HLT_MET200_v*',
                            'HLT_MET400_v*',
                            'HLT_MET65_v*',
                            )


