import FWCore.ParameterSet.Config as cms

analyzeFullLepPurity = cms.EDAnalyzer("FullLepPurityAnalyzer",
    hypoKey = cms.InputTag("ttFullLepHypKinSolution","Key"),
    FullLepEvent = cms.InputTag("ttFullLepEvent"),
    
    lepEtaBins      = cms.vdouble(-2.5,-1.5,-0.5,0.5,1.5,2.5),
    lepRapidityBins = cms.vdouble(-2.5,-1.5,-0.5,0.5,1.5,2.5),    
    lepPhiBins      = cms.vdouble(-3.14,-1.57,0,1.57,3.14),    
    lepPtBins       = cms.vdouble(20,30,50,80,200,400), 
    
    lepBarEtaBins      = cms.vdouble(-2.5,-1.5,-0.5,0.5,1.5,2.5),
    lepBarRapidityBins = cms.vdouble(-2.5,-1.5,-0.5,0.5,1.5,2.5),    
    lepBarPhiBins      = cms.vdouble(-3.14,-1.57,0,1.57,3.14),    
    lepBarPtBins       = cms.vdouble(20,30,50,80,200,400),     
    
    lepPairEtaBins      = cms.vdouble(-2.5,-1.5,-0.5,0.5,1.5,2.5), 
    lepPairRapidityBins = cms.vdouble(-2.5,-1.5,-0.5,0.5,1.5,2.5),
    lepPairPhiBins      = cms.vdouble(-3.14,-1.57,0,1.57,3.14),
    lepPairPtBins       = cms.vdouble(30,50,80,120,200,400),          
    lepPairMassBins     = cms.vdouble(0,20,50,100,200,400),
    
    bEtaBins      = cms.vdouble(-2.5,-1.5,-0.5,0.5,1.5,2.5),
    bRapidityBins = cms.vdouble(-2.5,-1.5,-0.5,0.5,1.5,2.5),    
    bPhiBins      = cms.vdouble(-3.14,-1.57,0,1.57,3.14),
    bPtBins       = cms.vdouble(30,50,80,120,200,400),    
    
    bBarEtaBins      = cms.vdouble(-2.5,-1.5,-0.5,0.5,1.5,2.5),
    bBarRapidityBins = cms.vdouble(-2.5,-1.5,-0.5,0.5,1.5,2.5),    
    bBarPhiBins      = cms.vdouble(-3.14,-1.57,0,1.57,3.14),
    bBarPtBins       = cms.vdouble(30,50,80,120,200,400),
    
    topEtaBins      = cms.vdouble(-2.5,-1.5,-0.5,0.5,1.5,2.5),
    topRapidityBins = cms.vdouble(-2.5,-1.5,-0.5,0.5,1.5,2.5),    
    topPhiBins      = cms.vdouble(-3.14,-1.57,0,1.57,3.14),
    topPtBins       = cms.vdouble(30,50,80,120,200,400),    
    
    topBarEtaBins      = cms.vdouble(-2.5,-1.5,-0.5,0.5,1.5,2.5),
    topBarRapidityBins = cms.vdouble(-2.5,-1.5,-0.5,0.5,1.5,2.5),    
    topBarPhiBins      = cms.vdouble(-3.14,-1.57,0,1.57,3.14),
    topBarPtBins       = cms.vdouble(30,50,80,120,200,400),
    
    TtBarEtaBins      = cms.vdouble(-2.5,-1.5,-0.5,0.5,1.5,2.5),
    TtBarRapidityBins = cms.vdouble(-2.5,-1.5,-0.5,0.5,1.5,2.5),    
    TtBarPhiBins      = cms.vdouble(-3.14,-1.57,0,1.57,3.14),
    TtBarPtBins       = cms.vdouble(0,20,50,100,200,400),
    TtBarMassBins     = cms.vdouble(350,400,500,700,2000)             
)
