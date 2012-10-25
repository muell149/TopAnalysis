import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/FA9F9344-1FE0-E111-90D8-003048678B06.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/F868AE6B-25E0-E111-AB85-00261894396D.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/F6BE5A03-2EE0-E111-B5E7-00261894397D.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/F62C2F00-35E0-E111-9415-001A92811742.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/F40913E9-37E0-E111-8216-002618943910.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/F28775E3-2CE0-E111-B566-002618FDA248.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/F03D7483-20E0-E111-93A3-0030486791AA.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/F0356631-38E0-E111-8953-003048FFD76E.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/E6763BE0-36E0-E111-804A-00261894386C.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/E4DEFB58-3DE0-E111-88B5-003048FFD760.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/E2D464CE-33E0-E111-B79C-003048678DD6.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/E25B3423-29E0-E111-AF96-002618943921.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/DE3DFC43-35E0-E111-AC94-003048679166.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/DCF925F6-26E0-E111-8377-003048678FF8.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/DCE3CC82-4FE0-E111-B5F2-003048678A78.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/D4CCF731-30E0-E111-ABE4-002354EF3BD2.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/D0034B3B-28E0-E111-8AC7-0030486792B8.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/D002C07F-3DE0-E111-AA4F-0026189438DC.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/CEE89A81-31E0-E111-865B-003048678BF4.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/CC104171-2AE0-E111-8753-0026189437FC.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/CABEC9C9-33E0-E111-9DB7-002618943939.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/C60FFACE-33E0-E111-851F-003048678FB8.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/C49291E8-2EE0-E111-B0CE-00261894384A.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/C0B84C35-28E0-E111-823F-002618943900.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/BA60B6EB-24E0-E111-B8F5-002618943919.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/A6BF6652-4FE0-E111-A6BD-002618943984.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/94E60C61-3FE0-E111-8769-001A92810AF2.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/943C8AAB-3AE0-E111-928A-00261894391B.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/8E90611D-2BE0-E111-89E0-0026189438AF.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/8631E97D-31E0-E111-9C18-0026189437EB.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/829AC218-3AE0-E111-9193-00304867920C.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/8218C7CC-30E0-E111-B7D5-002618943948.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/7EE5E3E6-35E0-E111-B5C4-002618943944.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/729328E6-2CE0-E111-A879-003048FF9AC6.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/70CD8C03-2DE0-E111-83B5-003048678B36.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/70331DE3-2EE0-E111-B7A4-00261894393B.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/6E8A28F9-35E0-E111-BA63-00261894380D.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/660C543F-3BE0-E111-90C9-001A92971B62.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/6444C527-29E0-E111-AA3F-0026189437EC.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/62AB327F-40E0-E111-B083-002618FDA28E.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/5CF19895-2EE0-E111-9478-003048678C9A.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/58E080BE-32E0-E111-A7DB-003048678DD6.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/588EFCB8-45E0-E111-865B-003048678DD6.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/4870DE21-29E0-E111-AE8D-002618943962.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/467AD221-32E0-E111-9C5E-003048678B36.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/42446D2A-32E0-E111-8DB7-002354EF3BDB.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/40C86C07-33E0-E111-ABF7-001A92810AE4.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/34041F0A-26E0-E111-AFED-002618943862.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/2EC8A511-39E0-E111-BD08-002618943921.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/24809FF6-4CE0-E111-9BFA-001A92810AA6.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/1A3BD2FA-2DE0-E111-AA07-003048678FC4.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/0A6B46A3-3CE0-E111-A223-0018F3D095F8.root',
       '/store/data/Run2012A/DoubleMu/AOD/recover-06Aug2012-v1/0000/0261D2DB-3EE0-E111-B096-002354EF3BDD.root' ] );


secFiles.extend( [
               ] )

