import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Summer12_DR53X/VBF_HToZZTo4L_M-125_8TeV-powheg-pythia6/AODSIM/PU_S10_START53_V7A-v1/0000/E0A936BB-73FA-E111-A3B2-003048678FE4.root',
       '/store/mc/Summer12_DR53X/VBF_HToZZTo4L_M-125_8TeV-powheg-pythia6/AODSIM/PU_S10_START53_V7A-v1/0000/DAB67839-66FA-E111-8E01-002618943900.root',
       '/store/mc/Summer12_DR53X/VBF_HToZZTo4L_M-125_8TeV-powheg-pythia6/AODSIM/PU_S10_START53_V7A-v1/0000/A4C793E2-76FA-E111-9DB7-003048678F8A.root',
       '/store/mc/Summer12_DR53X/VBF_HToZZTo4L_M-125_8TeV-powheg-pythia6/AODSIM/PU_S10_START53_V7A-v1/0000/9A71BD58-6EFA-E111-876E-00304867901A.root',
       '/store/mc/Summer12_DR53X/VBF_HToZZTo4L_M-125_8TeV-powheg-pythia6/AODSIM/PU_S10_START53_V7A-v1/0000/4228BABE-70FA-E111-941B-001A92971B26.root',
       '/store/mc/Summer12_DR53X/VBF_HToZZTo4L_M-125_8TeV-powheg-pythia6/AODSIM/PU_S10_START53_V7A-v1/0000/4080AF84-73FA-E111-BE2E-003048FFD756.root',
       '/store/mc/Summer12_DR53X/VBF_HToZZTo4L_M-125_8TeV-powheg-pythia6/AODSIM/PU_S10_START53_V7A-v1/0000/2E558BF3-74FA-E111-B683-003048678B44.root' ] );


secFiles.extend( [
               ] )

