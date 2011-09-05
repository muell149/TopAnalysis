import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
    '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0004/2E67BEDC-47E2-DF11-89F5-001E68A993EE.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0003/D6137EDA-EBE0-DF11-84F0-E0CB4E1A117F.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0003/9209A241-F0E0-DF11-A086-003048C99F9C.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0003/86BC5748-ECE0-DF11-9313-00D0680BF8C4.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0003/74F2BADA-F0E0-DF11-844B-00151724CE06.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0003/72DC3C20-19E1-DF11-9263-003048F98842.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0003/70C4E9F2-EFE0-DF11-84B3-A4BADB3CEC29.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0003/16892B24-EFE0-DF11-BDF1-001E682F8528.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/8CD3FFA8-FEDF-DF11-9A08-00D0680BF940.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/22D031C3-01E0-DF11-AFCE-0019B9E7C79A.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/02EC7BA8-FEDF-DF11-AFD4-90E6BA19A258.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/FAE59220-A6DF-DF11-8703-00145E5521B9.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/F8673ED0-70DF-DF11-A50F-001E68A99494.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/F44CC38E-6ADF-DF11-9112-003048792CD0.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/EA1A10EF-8ADF-DF11-9BA0-485B39800BD2.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/DEF00423-52DF-DF11-9B7C-001E68A996E8.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/DEED3C55-8BDF-DF11-B1DD-A4BADB3CEBCE.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/D4B6F437-5ADF-DF11-B5BF-90E6BA0D09AA.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/D0A584BB-83DF-DF11-870D-001E0BC18A10.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/C2BC65A5-6EDF-DF11-8D7C-E0CB4E1A116B.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/B6745FAA-82DF-DF11-B80A-001EC9D87221.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/B2A12A6D-7BDF-DF11-8F35-0030487CAA50.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/AE858D2B-57DF-DF11-8D7F-001E0B8D198C.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/AC405E36-5EDF-DF11-ACCF-0030487E4B96.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/9C699AD7-67DF-DF11-8578-E0CB4E19F986.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/9ADE0F6B-55DF-DF11-94A7-E0CB4E1A11A3.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/96423DEE-76DF-DF11-BA7C-90E6BA0D09AD.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/9295107D-89DF-DF11-83B8-00145E5523D8.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/84F7E600-81DF-DF11-8A16-003048C5D65E.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/84991BBE-92DF-DF11-90CE-00D0680BF8D0.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/827B1C72-A8DF-DF11-9C26-0030487DA36C.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/80AF2972-5FDF-DF11-9DE5-0030487DF860.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/801B4FA5-7CDF-DF11-9D39-0015172C051D.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/7CE4497E-9DDF-DF11-AB35-001E6837DFEA.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/6C9ED853-7BDF-DF11-A6B2-485B39800C02.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/6A0CC0DB-6DDF-DF11-BB54-A4BADB3CEBEF.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/68A09209-68DF-DF11-94B8-E0CB4E19F9A4.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/646343CD-5CDF-DF11-BB9C-001A4D5FF45C.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/60F3919F-6EDF-DF11-B724-00D0680BF948.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/5E7DE3C6-63DF-DF11-8498-001F29657434.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/5E5BE4FC-A8DF-DF11-B77B-A4BADB3CEBEF.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/5805A305-A7DF-DF11-884D-001F2965C268.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/503FEA78-6ADF-DF11-B74C-0015172C04A8.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/42AE294C-56DF-DF11-B467-0015172C08F5.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/3E040864-CCDF-DF11-8FDB-00145E55226A.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/16A324FD-63DF-DF11-BFC7-E0CB4E4408DA.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/127AAC46-97DF-DF11-90CD-00D0680BA315.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/1012190A-7CDF-DF11-A235-00145E55682E.root',
        '/store/mc/Fall10/TTJets_TuneD6T_mass166_5_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/0A404858-63DF-DF11-9B65-001E682F273A.root'
    ] );


secFiles.extend( [

    ] )
