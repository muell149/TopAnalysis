import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FEC30D49-49DD-E111-BE97-003048D438EA.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FEBE2BE5-52DD-E111-A697-003048C692D6.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FAD5FEB1-54DD-E111-9692-003048C693EE.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FA9D4B5C-68DD-E111-BF75-003048D37570.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FA350227-5EDD-E111-8133-0030487F1307.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FA2CACEE-59DD-E111-96FC-003048C693F0.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F69E105A-58DD-E111-8059-003048D436B4.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F6181F99-4ADD-E111-82EA-003048C692B4.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F606228E-4BDD-E111-AFEA-003048C662B8.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F4BF2FD5-49DD-E111-9585-0030487E4B8F.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F4360CCD-4EDD-E111-9A24-002481E94BFE.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F2064017-49DD-E111-9F6B-0030487D8633.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/EE65D644-52DD-E111-A7A6-0030487D7105.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/EC76241F-57DD-E111-A29C-003048C692D8.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/EACABFC1-49DD-E111-9F57-003048D439AC.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E8944F1A-49DD-E111-AA47-0030487E5399.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E6D7507F-56DD-E111-8EDD-002481E0D714.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E626C795-61DD-E111-95B0-0030487E52A1.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E60A0540-4ADD-E111-A5A7-00266CFB8D74.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E4CEB01E-49DD-E111-9604-0030487D5E53.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E459BE39-4ADD-E111-92CB-0030487E510B.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E42CB432-15DD-E111-A500-0030487F1659.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E278DF29-49DD-E111-894F-0030487D5EB1.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E0FF3336-4ADD-E111-8753-003048C693C8.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E023DCAF-54DD-E111-95A5-0030487E4B8D.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/DE86AFB4-5CDD-E111-A45D-003048D43960.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/DCF2308F-55DD-E111-9D4C-003048D4DEBC.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/DCB7D12A-4ADD-E111-A3F2-0030487E54B5.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/DA7FE3AD-49DD-E111-B5F6-0030487E5399.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/DA0CEC3F-4ADD-E111-BD57-0030487E5399.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D8738EF8-48DD-E111-A4FE-003048C693C8.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D650F420-49DD-E111-AD62-0030487D43E1.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D0D1562F-4EDD-E111-B6DB-0030487FA607.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D089913C-49DD-E111-AA24-0030487F9381.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D05C2394-4BDD-E111-B85F-003048C69032.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/CE3EFCB4-49DD-E111-A31F-003048C692F2.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/CE384510-65DD-E111-AB98-00266CF32F18.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/CE33C9C9-4FDD-E111-8808-003048C69402.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/CAE25868-67DD-E111-B556-00266CF2718C.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/CAA7A98E-49DD-E111-9446-003048F0E424.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C855F4B0-49DD-E111-8B7B-003048D4DFBA.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C4F82A3B-49DD-E111-888C-003048D436CA.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C4A3CB04-5CDD-E111-A766-003048D43960.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C4179552-49DD-E111-A3D0-003048D439A6.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C2BE7E19-49DD-E111-B9C0-003048F0EBBC.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C095E1B3-49DD-E111-A128-003048C66180.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C00EE685-63DD-E111-8039-0030487D8661.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/BA3028A6-49DD-E111-BC2A-003048D462C8.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B8EC03A2-5DDD-E111-B533-00266CFFA68C.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B8831DC4-53DD-E111-BDD3-003048D4390A.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B8534EEE-55DD-E111-8F2C-002481E0D714.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B66B1AB6-0BDD-E111-8D4C-003048D47746.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B44D95CA-5ADD-E111-9254-003048D3CB3C.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B223EA72-61DD-E111-B5D6-0030487F1665.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B0BE066F-64DD-E111-9EA5-0030487D5EB1.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B06221C1-49DD-E111-B871-0030487E52A5.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B01EEBFD-54DD-E111-8EE8-003048D4DEBC.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B01D0460-53DD-E111-BA39-00266CFFA754.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/AAC4861C-5FDD-E111-B2F0-003048C68A9E.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/AA833285-5EDD-E111-B6B2-003048D4365C.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A6DD646F-5ADD-E111-8D1B-00237DE0BED6.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A6B9C831-49DD-E111-B590-0030487D8151.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A2BF7A23-49DD-E111-9AF1-0030487D5DAF.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A2B3AB17-62DD-E111-8659-0030487D8563.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A2A12BA7-5FDD-E111-BF67-002481E94BFE.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A236F382-5EDD-E111-8DBE-003048F0E824.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A0C0A84F-4ADD-E111-B680-0030487E4EBF.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A09A7C11-49DD-E111-9D1D-003048C68A9E.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A046284F-4ADD-E111-B527-00266CF9C1AC.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A039BADF-48DD-E111-A89E-003048D479C0.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9EF00195-4BDD-E111-B5DF-002481E10B86.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9CB5F4C2-D0DD-E111-8301-003048C69272.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9C6EDAA1-49DD-E111-AB41-0030487F92FF.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9C6464C6-4FDD-E111-AD0D-00266CF32684.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9C14C2E0-59DD-E111-B024-003048C33984.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9A3320A3-49DD-E111-BDC5-003048C69318.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/98F838C2-58DD-E111-8F1C-003048D43642.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/987F9618-55DD-E111-BF9A-00266CFFA3FC.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/986AE620-49DD-E111-B98B-0030487D5E73.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/98089F0E-5FDD-E111-8009-003048C68AA6.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/966E034C-4ADD-E111-867C-003048F0EBBC.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/966A2E48-4ADD-E111-AEB1-0030487D8633.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/94D7205A-49DD-E111-9B49-003048D439A8.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/94C828DA-52DD-E111-95C6-002481E0D69C.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/927CC4BD-49DD-E111-AB06-003048C676E0.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/926A5323-62DD-E111-AF7B-003048C69312.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/924A173E-49DD-E111-8E3E-00266CF9C1AC.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/90DD9CA4-5DDD-E111-88C4-0030487F1A55.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/8A3E2DAC-51DD-E111-8FB9-002481E0DC4E.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/8A370C32-4EDD-E111-B0D6-00266CF2718C.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/8A1EF177-4BDD-E111-BBE7-003048C6903E.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/88804A2F-49DD-E111-BA01-003048D4DEBC.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/86E32225-51DD-E111-A5DC-003048C6763A.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/86DB8E9C-4DDD-E111-A6C0-0030487D7109.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/86562861-5BDD-E111-ADA0-003048D3CB3C.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/86427C5A-4ADD-E111-9293-003048D437EC.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/80651334-4EDD-E111-A7F4-0030487D5E73.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/805C6A9A-49DD-E111-83F1-003048C692F2.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/7EDDE18D-4BDD-E111-B2F5-0030487F16F7.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/7C590D18-62DD-E111-AB8D-0030487F1665.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/76F48A27-4ADD-E111-AB9B-003048C68A88.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/767F44A2-49DD-E111-B4AC-0030487E4EBF.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/74E2442D-49DD-E111-A63C-0030487E52A5.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/74A9EBC2-4FDD-E111-AD82-003048F0E1EE.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/7412791A-6BDD-E111-B448-0030487E55C5.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/724A53C3-57DD-E111-8BC5-003048D436B4.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6E859850-49DD-E111-B6BA-00266CF32CD0.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6E53AA6E-5ADD-E111-9467-003048C33984.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6C835D48-4ADD-E111-B811-003048D479C0.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/66A14CBA-49DD-E111-B3DB-0030487D5E99.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6633D1AB-50DD-E111-9F47-0030487D5DBF.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/64711A88-49DD-E111-AFF0-0030487D5DA9.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/64028D3A-66DD-E111-B6A9-003048F0E3BC.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/5EE2C0B2-49DD-E111-87CA-003048F0EBBC.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/5E50EF42-59DD-E111-8D76-003048C33984.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/5C9ECDA0-5DDD-E111-925B-002590494E34.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/5A9171C5-49DD-E111-890F-003048C68A9E.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/5A78CCF5-68DD-E111-9E8E-003048D462C8.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/58008B30-49DD-E111-B494-00266CF26450.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/54963544-49DD-E111-9E1F-003048D4DFA6.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/5267C1AC-49DD-E111-8B4D-0030487D8633.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/5202AB55-58DD-E111-81BD-002481E0D66C.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4EEF8DC4-4FDD-E111-9235-0030487F1F2F.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4E49EAF6-48DD-E111-853A-0030487D5D8D.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4C1DC911-55DD-E111-A2CD-0030487F1A55.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4ABE91BF-49DD-E111-8176-00266CF9C1AC.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/48FC179E-49DD-E111-8840-003048D479C0.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/484FFC3D-4ADD-E111-A031-0030487F92FF.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/46DF91CF-49DD-E111-9FDF-003048C66180.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/46CBF129-49DD-E111-9DED-00266CF2AACC.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/44FA87BB-49DD-E111-AE9A-0030487D5E73.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/42D870C4-49DD-E111-8D4E-0030487D43E1.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3EBB6C55-5BDD-E111-B5ED-003048C693BC.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3EB26F06-56DD-E111-A07E-003048C693BC.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3E270EE0-59DD-E111-B80D-00237DE0BED6.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3C6EA19E-4ADD-E111-8008-003048C6903E.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3C352357-49DD-E111-96E5-003048C68A88.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3C269C1F-49DD-E111-8E1F-0030487DA061.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/38EF6D2E-53DD-E111-B5C9-0030487F9151.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/38581F27-5EDD-E111-B630-002590494E34.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/38576F66-61DD-E111-A13B-002481E0DC4E.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/36F7CB77-4BDD-E111-A3C5-003048C692DE.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/36DB4513-57DD-E111-9F20-002481E0D714.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/360841C1-49DD-E111-8D52-0030487D5E53.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/34F08E84-61DD-E111-BDC2-003048F02CB6.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/34390BBF-57DD-E111-8F2F-002481E0D66C.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3428482E-4EDD-E111-A102-0030487E4ED3.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/32C5BAE9-48DD-E111-8A14-00266CF32930.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3285CD43-49DD-E111-AE62-0030487D7EB1.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/303D699F-5FDD-E111-9D0A-003048D43982.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/30027534-4ADD-E111-BB7C-0030487D5D5B.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2EE292FE-5BDD-E111-9C18-003048D3CB3C.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2E163E31-4ADD-E111-A17D-003048D436CA.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2E0F9FF6-48DD-E111-BF3B-0030487E4EBF.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2CFDA9A2-50DD-E111-817B-003048D462DC.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2C705991-49DD-E111-9702-003048C693C8.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2ACF3C23-63DD-E111-830B-003048C692D4.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2AA80843-49DD-E111-A4FB-002481E10D3E.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2A7BB0DF-4FDD-E111-A3F1-0030487D811F.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/282DDAB6-49DD-E111-8F5C-0030487D5DAF.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2656AEBE-5ADD-E111-A15A-003048C693BC.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/24FF6751-4EDD-E111-A970-003048C6903E.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/1EB2C636-4EDD-E111-AB2E-003048F02CB2.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/1A7863A0-58DD-E111-8BD0-0025901D4138.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/168768A9-5DDD-E111-AB6E-003048C69402.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/16025F47-49DD-E111-B525-0030487D5DA5.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/12B011A4-49DD-E111-B864-002481E107A8.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/10A55DF2-48DD-E111-8C3E-003048C66180.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0EF3B547-4ADD-E111-901C-0030487DA061.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0E4C33AA-5CDD-E111-8EE3-0030487D857D.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0CF8286A-11DD-E111-B5F1-003048F0EBBC.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0CBCEBB9-49DD-E111-A845-0030487DA061.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0C95DA60-71DD-E111-9AF4-0030487D5E81.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0C715C9A-4DDD-E111-A4BD-0030487D5E73.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0C6A72D6-48DD-E111-BD62-003048D436CA.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/08F89AED-01DD-E111-9225-0030487F937B.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/06BFE784-49DD-E111-A1E4-0030487D5D8D.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/06462B1F-49DD-E111-BEF1-00266CFFA5AC.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/041F21EA-65DD-E111-8000-0030487D5DA9.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0404DE7A-5BDD-E111-ACE7-003048D47776.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/02C912AE-49DD-E111-BACC-0030487EA3DD.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/02A4DE42-4ADD-E111-B30A-003048D4DFBA.root',
       
'/store/mc/Summer12_DR53X/WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/005A1EAA-49DD-E111-8D4C-0030487E510B.root' ] );


secFiles.extend( [
               ] )

