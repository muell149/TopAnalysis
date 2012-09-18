import FWCore.ParameterSet.Config as cms

####################################################################################
# Dataset:  /Zprime_M750GeV_W7500MeV-madgraph/Fall11-PU_S6_START42_V14B-v1/AODSIM  #
# Events : 206525                                                                  # 
# eff    : 1.0                                                                     #
# files  : 19                                                                      #  
####################################################################################

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [

       '/store/mc/Fall11/Zprime_M750GeV_W7500MeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/FC09457D-3510-E111-86E7-003048D46060.root',
       '/store/mc/Fall11/Zprime_M750GeV_W7500MeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/EC86756C-3510-E111-A003-00E08178C0B1.root',
       '/store/mc/Fall11/Zprime_M750GeV_W7500MeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/DCCF0D5F-3510-E111-8F68-003048D4608C.root',
       '/store/mc/Fall11/Zprime_M750GeV_W7500MeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/D6CF9582-3510-E111-A25F-003048D46060.root',
       '/store/mc/Fall11/Zprime_M750GeV_W7500MeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/CAE0216A-3510-E111-9FC2-003048D45F24.root',
       '/store/mc/Fall11/Zprime_M750GeV_W7500MeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/C099A965-3510-E111-85EA-003048D4774E.root',
       '/store/mc/Fall11/Zprime_M750GeV_W7500MeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/B0E44F75-3510-E111-89FF-002590200938.root',
       '/store/mc/Fall11/Zprime_M750GeV_W7500MeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/B078906E-3510-E111-B25C-003048D45F7E.root',
       '/store/mc/Fall11/Zprime_M750GeV_W7500MeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/7029037C-3510-E111-8E7A-001A64789CE4.root',
       '/store/mc/Fall11/Zprime_M750GeV_W7500MeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/686B448D-3510-E111-82E3-001A64789470.root',
       '/store/mc/Fall11/Zprime_M750GeV_W7500MeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/5AF62E62-3510-E111-83B3-0025902008FC.root',
       '/store/mc/Fall11/Zprime_M750GeV_W7500MeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/5AD8D367-3510-E111-BC04-002481E14F8C.root',
       '/store/mc/Fall11/Zprime_M750GeV_W7500MeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/48E47B7A-3510-E111-ABD2-00E08178C10B.root',
       '/store/mc/Fall11/Zprime_M750GeV_W7500MeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/4207327A-3510-E111-B9F7-003048D47796.root',
       '/store/mc/Fall11/Zprime_M750GeV_W7500MeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/2874476C-3510-E111-91AB-0025B3E05E0A.root',
       '/store/mc/Fall11/Zprime_M750GeV_W7500MeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/1AFAA96E-3510-E111-987E-003048635F0C.root',
       '/store/mc/Fall11/Zprime_M750GeV_W7500MeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/1460E186-3510-E111-9D7E-003048D46012.root',
       '/store/mc/Fall11/Zprime_M750GeV_W7500MeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/12470D8F-3510-E111-8517-0025902009C8.root',
       '/store/mc/Fall11/Zprime_M750GeV_W7500MeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/B4C16E66-3510-E111-885E-003048670BF8.root'

     ] );

secFiles.extend( [
               ] )

