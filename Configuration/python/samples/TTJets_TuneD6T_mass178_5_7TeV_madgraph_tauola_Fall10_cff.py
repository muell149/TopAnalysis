import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
    '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0009/48C62EFC-11E7-DF11-A32E-0015172560CF.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0008/F6767E71-AEE5-DF11-8DD3-001EC9EB9227.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0008/B68AC277-AEE5-DF11-8AE3-001F2965744C.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0008/641E1E08-AEE5-DF11-809F-0015172C04A8.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0008/5E5CC03F-E2E5-DF11-9CFD-00145E552333.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0008/4E6A5B48-63E6-DF11-8E82-003048792C16.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0008/3294CC25-ADE5-DF11-8C8E-00144F45F56E.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0008/0A059DB5-AEE5-DF11-AA9C-E0CB4E29C4B8.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0006/F6EE7906-56E5-DF11-BEF5-485B39800BD2.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0006/F45E0FB6-3AE4-DF11-A2F5-001EC9DE18E9.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0006/C4DD40C2-58E4-DF11-B7FC-0022191F53D4.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0006/B0187A2A-AEE4-DF11-8DDB-003048CDCCDA.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0006/9024C147-22E4-DF11-A634-00145E552252.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0005/FAAEBA76-65E3-DF11-BFCB-003048CEB13A.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0005/F0F8885E-7EE3-DF11-8CC3-00D0680BF9A2.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0005/D4C86E0F-B6E3-DF11-A1B7-0015172560B1.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0005/C006A529-69E3-DF11-94BE-00145E55167F.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0005/B6ED92AA-72E3-DF11-97CE-003048C5D19A.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0005/A446D2EC-AEE3-DF11-8BFF-0026B95493D6.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0005/841AD8AE-65E3-DF11-93EC-00D0680BF9D2.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0005/4C85DBF3-99E3-DF11-BF78-A4BADB3CEBCE.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0005/3EE92F8F-A4E3-DF11-BD1E-001D09FD0D10.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0005/3E89C627-67E3-DF11-BBAD-0030487BD89E.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0005/3E05BF67-8FE3-DF11-A8C6-A4BADB3CF260.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0005/3C9F5160-7BE3-DF11-993D-001517357DBC.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0005/1EB89252-89E3-DF11-85FF-003048D47639.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0004/F8A44D9C-22E3-DF11-9943-00261834B5F1.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0004/F495759B-63E3-DF11-9D4D-002219205095.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0004/EE1DDB04-3BE3-DF11-A7B2-00261834B5DC.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0004/EC47633D-61E3-DF11-AEF6-0030487DF762.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0004/DC7C81DF-35E3-DF11-AD2C-00145E5523E7.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0004/D4E8B24D-37E3-DF11-8CB1-0030487DF92C.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0004/CCF29FD5-51E3-DF11-9CE0-00248C855FD2.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0004/C6C00154-4FE3-DF11-A441-001517357DFE.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0004/BA95E3EB-48E3-DF11-A07B-00145E5517E7.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0004/B6422DE0-4DE3-DF11-B1EA-00D0680BF9B8.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0004/8027E03E-83E3-DF11-8380-00145E5564FD.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0004/70EB377E-51E3-DF11-BC8C-001F2965744C.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0004/4A616A10-65E3-DF11-A2F8-003048D47662.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0004/44D009E4-60E3-DF11-9E74-00145E55230C.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0004/3893ED68-5FE3-DF11-BFFC-0030487E2D74.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0004/2E66278D-4CE3-DF11-AEBC-00261834B622.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0004/2817EC01-45E3-DF11-9FFA-003048917F4A.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0004/20C0270B-41E3-DF11-82BF-003048917F50.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0004/1C94698D-52E3-DF11-9553-00145E551D30.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0004/1A9C39ED-30E3-DF11-8CBC-003048984835.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0004/10372E98-3CE3-DF11-A537-003048D47662.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0004/0EC94C26-69E3-DF11-8C8C-0015171E6E0B.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass178_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0004/0001A7C8-29E3-DF11-B234-003048CAA6AE.root'
    ] );


secFiles.extend( [

    ] )
