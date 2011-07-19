import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
    'file:///scratch/hh/current/cms/user/wbehrenh/FE3430A0-BE9C-E011-AF2D-E0CB4E19F972.root'
    #'/store/mc/Summer11/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0001/FE3430A0-BE9C-E011-AF2D-E0CB4E19F972.root'
])
