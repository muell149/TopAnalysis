import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0272859E-ACE6-E111-B8EE-003048D43980.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/16732E33-A0E6-E111-90FE-0025904B0F92.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/187C67AE-A9E6-E111-8A86-00266CF422D8.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/1AB7AE70-B8E6-E111-8A17-0025904B12DE.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2A1E5876-B5E6-E111-BCCD-0025901D42BC.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2A93B3A6-AAE6-E111-B4C6-0025901D4C32.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2A965514-BBE6-E111-AB10-00266CF326A8.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2CB41DF1-AFE6-E111-ABA8-0025901D4D54.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3098DE32-A2E6-E111-A9BD-0025901D4936.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/349BA2DF-B1E6-E111-B96D-002590494C92.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3CA76302-ABE6-E111-A777-00266CF32F00.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/1688E379-A3E6-E111-9E70-00266CFFA780.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/448ECD03-ABE6-E111-A52B-003048F0E528.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2E32143E-B0E6-E111-900D-003048F02CB6.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/301B128D-AFE6-E111-ADEC-0025901D4D6C.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/302C5C1D-B5E6-E111-95B2-00266CF3336C.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/54E5CB16-C4E6-E111-990E-00266CFFA204.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/56519CE0-B6E6-E111-B29F-003048F0E828.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/56E49176-B1E6-E111-B6AE-00266CF9C1AC.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/5A6BD770-B9E6-E111-BABA-003048F0E824.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/5C425575-BDE6-E111-BF3A-00266CF3322C.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/5E5DBC47-ADE6-E111-8E2F-0025901D4A0E.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4215A375-B1E6-E111-8E8A-0025904B1426.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/64E2DAD3-B3E6-E111-A916-00266CF327C4.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/44EE2408-A9E6-E111-837B-0030487E4D11.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/685A999B-9DE6-E111-BC18-003048F0E3BA.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/46DB1FD7-B3E6-E111-9794-0025904B1452.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/78234BCD-B3E6-E111-B854-0025901D4AFE.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/78734036-B0E6-E111-82BF-0025901D4B06.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/7A522744-ADE6-E111-92F4-0025901D4124.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/540F9318-B3E6-E111-9EC7-003048F0E18C.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/7CE45DD2-C7E6-E111-A31E-0025901D4B04.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/62EA35DC-B3E6-E111-ACBC-003048CF6332.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/82F89E87-A8E6-E111-BA65-0030487E4D11.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6847735C-C0E6-E111-8AB8-003048D437C4.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/767ADC70-B6E6-E111-B7DB-0025904B12DE.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9AB3759E-ABE6-E111-B8CD-0025901D4936.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/AC52AEAD-ADE6-E111-9FDD-00266CFFA7C0.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/7C613C71-B9E6-E111-86AB-00266CF2D5C4.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B86A8735-B0E6-E111-849F-002590494CB2.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B8AF5132-AEE6-E111-90E9-00266CF25E44.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C22B5612-BCE6-E111-8318-00266CF330D8.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C27B27C4-A7E6-E111-9D25-002590494C94.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/7E59DFBC-99E6-E111-843C-0030487F1BD7.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/CE230C1F-A5E6-E111-A87C-002481E76052.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/92BEBE15-A7E6-E111-ADCC-003048C69024.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D6F7CCF2-B1E6-E111-8017-0030487D7103.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E68141F0-AFE6-E111-9549-0030487D5E49.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/98DDB876-B8E6-E111-B9CB-0025904B0F96.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/AC954D82-A6E6-E111-8CB7-0025901D4B06.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C8687A84-B5E6-E111-94DD-0030487F1655.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D4E08186-AFE6-E111-8B7E-0025901D4ADE.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FC59CCE1-B3E6-E111-806B-0025904B12F0.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FC63FFA0-ADE6-E111-A5D2-0025901D4844.root' ] );


secFiles.extend( [
               ] )

