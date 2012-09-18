import FWCore.ParameterSet.Config as cms

################################################################################
# Dataset: /Zprime_M500GeV_W5GeV-madgraph/Fall11-PU_S6_START42_V14B-v1/AODSIM  #
# Events : 232074                                                              # 
# eff    : 1.0                                                                 #
# files  : 25                                                                  # 
################################################################################

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [

       '/store/mc/Fall11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/F4038754-3410-E111-831C-0030486709FE.root',
       '/store/mc/Fall11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/ECBAA14E-3410-E111-BDE6-0025902009C8.root',
       '/store/mc/Fall11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/DEB80F7D-3410-E111-BF46-984BE1089DFA.root',
       '/store/mc/Fall11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/B6F34174-3410-E111-AE8F-00259021A43E.root',
       '/store/mc/Fall11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/A24FB67B-3410-E111-9A0F-002590200850.root',
       '/store/mc/Fall11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/9A785863-3410-E111-94D4-00E081791735.root',
       '/store/mc/Fall11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/9078D36F-3410-E111-82B1-002590200A94.root',
       '/store/mc/Fall11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/9050EA62-3410-E111-88FD-00E08178C147.root',
       '/store/mc/Fall11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/8EB5B64C-3410-E111-8793-003048D47742.root',
       '/store/mc/Fall11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/8E5C8E87-3410-E111-A199-003048673F9C.root',
       '/store/mc/Fall11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/889B7E4A-3410-E111-949D-003048D46060.root',
       '/store/mc/Fall11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/7AA2F778-3410-E111-A7AA-002481E14F7A.root',
       '/store/mc/Fall11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/506AE088-3410-E111-9C6A-00E081791867.root',
       '/store/mc/Fall11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/34977781-3410-E111-A366-001A64789E5C.root',
       '/store/mc/Fall11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/22EA4E5A-3410-E111-827E-003048670B64.root',
       '/store/mc/Fall11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/20D2F85B-3410-E111-B16B-00E0817917C9.root',
       '/store/mc/Fall11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/18E6366C-3410-E111-8975-003048D4612C.root',
       '/store/mc/Fall11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/140FCF7C-3410-E111-8262-00E0817917A3.root',
       '/store/mc/Fall11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/1001F059-3410-E111-AE2B-003048D4603A.root',
       '/store/mc/Fall11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/0ADBE463-3410-E111-BEBF-002590200914.root',
       '/store/mc/Fall11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/0284FF89-3410-E111-9871-001A64789488.root',
       '/store/mc/Fall11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/F63D4569-3410-E111-BF56-001A64789470.root',
       '/store/mc/Fall11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/E6218776-3410-E111-995C-00304867407E.root',
       '/store/mc/Fall11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/E42DED6F-3410-E111-A1FC-0030486709FE.root',
       '/store/mc/Fall11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S6_START42_V14B-v1/0000/E2D4834D-3410-E111-9AD5-003048D47778.root' 

     ] );

secFiles.extend( [
               ] )

