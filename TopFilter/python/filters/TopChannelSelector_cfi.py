import FWCore.ParameterSet.Config as cms

selectChannel = cms.EDFilter("TopChannelSelector",

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

    # if a channel is selected which contains
    # a tau you can choose a specific further
    # tau decay
    Tau_To_Hadron   = cms.bool(True), 
    Tau_To_Electron = cms.bool(True),       
    Tau_To_Muon     = cms.bool(True),
    
    # selection can be inverted
    invert_selection = cms.bool(False)   
)
