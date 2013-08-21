import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Summer12_DR53X/TTGJets_8TeV-madgraph/AODSIM/PU_S10_START53_V7A-v1/0000/02F29E4D-76D9-E111-A9DC-003048C6763A.root',
       '/store/mc/Summer12_DR53X/TTGJets_8TeV-madgraph/AODSIM/PU_S10_START53_V7A-v1/0000/1ADB00A8-8BD9-E111-BEFD-0030487F1C4F.root',
       '/store/mc/Summer12_DR53X/TTGJets_8TeV-madgraph/AODSIM/PU_S10_START53_V7A-v1/0000/34E1A566-7BD9-E111-8066-0030487F1653.root',
       '/store/mc/Summer12_DR53X/TTGJets_8TeV-madgraph/AODSIM/PU_S10_START53_V7A-v1/0000/484D8D18-6CD9-E111-9060-003048C693EA.root',
       '/store/mc/Summer12_DR53X/TTGJets_8TeV-madgraph/AODSIM/PU_S10_START53_V7A-v1/0000/70B61CCF-8FD9-E111-999D-0030487F1661.root',
       '/store/mc/Summer12_DR53X/TTGJets_8TeV-madgraph/AODSIM/PU_S10_START53_V7A-v1/0000/7CF0B6CB-80D9-E111-9CFC-0030487F9295.root',
       '/store/mc/Summer12_DR53X/TTGJets_8TeV-madgraph/AODSIM/PU_S10_START53_V7A-v1/0000/A828D515-4BD9-E111-A9D8-003048C68A90.root',
       '/store/mc/Summer12_DR53X/TTGJets_8TeV-madgraph/AODSIM/PU_S10_START53_V7A-v1/0000/CE8C87CD-33D9-E111-A1E2-0030487F6A8B.root',
       '/store/mc/Summer12_DR53X/TTGJets_8TeV-madgraph/AODSIM/PU_S10_START53_V7A-v1/0000/D2089E1D-84D9-E111-A10D-0030487D5E73.root',
       '/store/mc/Summer12_DR53X/TTGJets_8TeV-madgraph/AODSIM/PU_S10_START53_V7A-v1/0000/DC631BDA-B7D9-E111-87B8-003048C692B4.root',
       '/store/mc/Summer12_DR53X/TTGJets_8TeV-madgraph/AODSIM/PU_S10_START53_V7A-v1/0000/E808A11D-7FD9-E111-A61B-003048D3C880.root',
       '/store/mc/Summer12_DR53X/TTGJets_8TeV-madgraph/AODSIM/PU_S10_START53_V7A-v1/0000/F0E9B201-78D9-E111-9C25-003048C693DA.root' ] );


secFiles.extend( [
               ] )

