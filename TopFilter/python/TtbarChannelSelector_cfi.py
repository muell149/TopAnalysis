import FWCore.ParameterSet.Config as cms

selectChannel = cms.EDFilter("TtbarChannelSelector",

    src = cms.InputTag("genParticles"),
    
    #how many event do you want to select?
    n_events = cms.int32(-1),
    
    #which channel do you want to select?
    SingleTop_Hadronic = cms.bool(False),
    SingleTop_Electron = cms.bool(False),
    SingleTop_Muon     = cms.bool(False),
    SingleTop_Tau      = cms.bool(False),
    
    Ttbar_Hadronic = cms.bool(False),
    
    Ttbar_SemiElec = cms.bool(False),
    Ttbar_SemiMuon = cms.bool(False),
    Ttbar_SemiTau  = cms.bool(False),
    
    Ttbar_ElecElec = cms.bool(False),
    Ttbar_MuonMuon = cms.bool(False),
    Ttbar_TauTau   = cms.bool(False),
        
    Ttbar_ElecMuon = cms.bool(False),    
    Ttbar_ElecTau  = cms.bool(False),         
    Ttbar_MuonTau  = cms.bool(False),

    #if a tau channel is choosen select a special tau decay?
    Tau_Hadronic = cms.bool(False), 
    Tau_Elec     = cms.bool(False),       
    Tau_Muon     = cms.bool(False),
    
    # selection can be inverted
    invert_selection = cms.bool(False)   

)
