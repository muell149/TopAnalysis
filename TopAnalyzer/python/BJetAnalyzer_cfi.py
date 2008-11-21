import FWCore.ParameterSet.Config as cms

analyzeJets = cms.EDAnalyzer("BJetAnalyzer",
    
    # sources    
    jets = cms.InputTag("selectedLayer1Jets"),    
    
    # histfile        
    hist = cms.string('jets.hist'),
        
    # domains    
    show_kinematics  = cms.bool(True), 
    show_energyscale = cms.bool(True),    
    show_btagging    = cms.bool(True),
     
    # take only leading jets    
    only_leading = cms.int32(999),
        
    # which b-tagging algorithm do you want to contemplate?
    # (only algos with a discriminator from 0 to 1)
    algorithm = cms.string('combinedSecondaryVertexMVABJetTags'),
    
    # b-tagging discriminator cut
    b_dis_cut = cms.double(0.5),
    
    # bins for b-tagging
    eta_bins = cms.vdouble(0, 0.5, 1., 1.5, 2.0, 2.5, 3.0),
    pt_bins  = cms.vdouble(20., 30., 40., 50., 60., 70., 85., 100., 120., 150., 200.)
) 

