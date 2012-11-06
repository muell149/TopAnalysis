import FWCore.ParameterSet.Config as cms

#from TopQuarkAnalysis.TopObjectResolutions.stringResolutions_etEtaPhi_cff import *
from TopAnalysis.Configuration.stringResolutions_etEtaPhi_Fall11_cff import *

analyzeFullHadEventMixer = cms.EDAnalyzer("FullHadEventMixer",
    ## input collection                             
        
    ## src of jets
    JetSrc      = cms.InputTag("selectedPatJets"),
    ## src of MET
    METSrc      = cms.InputTag("patMETs"),
    ## src of muons
    MuonSrc     = cms.InputTag("selectedPatMuons"),
    ## src of electrons
    ElectronSrc = cms.InputTag("selectedPatElectrons"),
    ## src of jets
    VertexSrc   = cms.InputTag("goodOfflinePrimaryVertices"),
    ## src of multijet mva discriminator
    #MultiJetMVADiscSrc = cms.InputTag("mvaDisc","DiscSel"),

    ## weight of mc sample
    MCweight = cms.double(1.0),

    ## special parameters for 
    ## QCD background estimation for
    ## fully hadronic ttbar events

    ## choose TTree for output instead of histograms, if applicable
    #useTree    = cms.bool(False),
    ## choose b-tagging algorithm and working point to be used
    bTagAlgo = cms.string("trackCountingHighEffBJetTags"),
    minBTagValueBJet    = cms.double(3.3),
    maxBTagValueNonBJet = cms.double(10.2),

    ## jetEnergyCorrectionLevel to be used
    jetCorrectionLevel = cms.string("L3Absolute"),

    ## number of events to be mixed
    nMix = cms.uint32(10),

    ## speed up factor used to randomly selected 1:speedUp_ events
    speedUp = cms.double(1.0),

    # ------------------------------------------------
    # resolutions used for the kinematic fit
    # ------------------------------------------------
    udscResolutions = udscResolutionPF.functions,
    bResolutions    = bjetResolutionPF.functions,
    jetEnergyResolutionScaleFactors = cms.vdouble(1.0),
    jetEnergyResolutionEtaBinning   = cms.vdouble(0,-1.)
)



