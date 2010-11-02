import FWCore.ParameterSet.Config as cms
## module definition, e.g. here: which analyzer is used
tagAndProbeAnalyzer = cms.EDAnalyzer("TagAndProbeAnalyzer", # -> TagAndProbeAnalyzer.cc
    ## input collection for jets                            
    jets   = cms.InputTag("selectedPatJets"),
    ## test collection                    
    tests  = cms.InputTag("selectedPatMuons"),
    ## probe collection                                     
    probes = cms.InputTag("selectedPatMuons"),
    ## variables for cut on pt and eta: pt cut is not applied on pt-histo, eta cut is not applied on eta-histo
    ## both cuts are applied on all other histos
    ptCut =  cms.double(20.),
    etaCut = cms.double(2.1),
    ## bin numbers; in case variable bins are desired: set to -1
    nBinsPt     = cms.int32(15),
    nBinsEta    = cms.int32(30),
    nBinsPhi    = cms.int32(12),
    nBinsMult   = cms.int32(10),
    nBinsMinDR  = cms.int32(25),
    nBinsMuMult = cms.int32(10),
    ## in case of fixed bins: 1st vector entry=xlow, 2nd vector entry=xup (left and right edges of histo)
    ## in case of variable bins: vector of low-edges for each bin
    binsPt     = cms.vdouble(  0.  , 150.  ),
    binsEta    = cms.vdouble( -5.  ,   5.  ),
    binsPhi    = cms.vdouble( -3.14,   3.14),
    binsMult   = cms.vdouble(  0.  ,  10.  ),
    binsMinDR  = cms.vdouble(  0.  ,  10.  ),
    binsMuMult = cms.vdouble(  0.  ,  10.  )
)



