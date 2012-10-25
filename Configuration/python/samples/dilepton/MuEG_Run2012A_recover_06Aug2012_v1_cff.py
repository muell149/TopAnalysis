import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2012A/MuEG/AOD/recover-06Aug2012-v1/0000/F4411E7E-69E0-E111-8E56-E0CB4E1A1183.root',
       '/store/data/Run2012A/MuEG/AOD/recover-06Aug2012-v1/0000/ECF866F9-6EE0-E111-98F5-20CF305616E0.root',
       '/store/data/Run2012A/MuEG/AOD/recover-06Aug2012-v1/0000/EC8B7762-76E0-E111-9DF6-00259073E4D6.root',
       '/store/data/Run2012A/MuEG/AOD/recover-06Aug2012-v1/0000/E233182B-74E0-E111-82C0-00259074AEA6.root',
       '/store/data/Run2012A/MuEG/AOD/recover-06Aug2012-v1/0000/DCDB0E30-7CE0-E111-968A-00259073E4A0.root',
       '/store/data/Run2012A/MuEG/AOD/recover-06Aug2012-v1/0000/D6A2D77F-6BE0-E111-80AE-00259073E3FA.root',
       '/store/data/Run2012A/MuEG/AOD/recover-06Aug2012-v1/0000/D65154F8-71E0-E111-ADB9-E0CB4E553677.root',
       '/store/data/Run2012A/MuEG/AOD/recover-06Aug2012-v1/0000/C294F55E-77E0-E111-B78C-E0CB4E553677.root',
       '/store/data/Run2012A/MuEG/AOD/recover-06Aug2012-v1/0000/BE2DC1A4-71E0-E111-989A-E0CB4E19F9A2.root',
       '/store/data/Run2012A/MuEG/AOD/recover-06Aug2012-v1/0000/BC261777-6BE0-E111-A97A-E0CB4E1A1169.root',
       '/store/data/Run2012A/MuEG/AOD/recover-06Aug2012-v1/0000/A47C568E-68E0-E111-A16F-00259073E32A.root',
       '/store/data/Run2012A/MuEG/AOD/recover-06Aug2012-v1/0000/A43084AE-75E0-E111-BB58-20CF305B04D2.root',
       '/store/data/Run2012A/MuEG/AOD/recover-06Aug2012-v1/0000/8CDF69A5-70E0-E111-AB0A-E0CB4E4408CB.root',
       '/store/data/Run2012A/MuEG/AOD/recover-06Aug2012-v1/0000/823FBD85-73E0-E111-81BD-00259073E4CC.root',
       '/store/data/Run2012A/MuEG/AOD/recover-06Aug2012-v1/0000/7E2CFF9E-70E0-E111-B94F-E0CB4E19F99E.root',
       '/store/data/Run2012A/MuEG/AOD/recover-06Aug2012-v1/0000/4E9BF232-73E0-E111-B99A-E0CB4E29C4FD.root',
       '/store/data/Run2012A/MuEG/AOD/recover-06Aug2012-v1/0000/4C15232A-74E0-E111-B11B-00259073E346.root',
       '/store/data/Run2012A/MuEG/AOD/recover-06Aug2012-v1/0000/4A679B9B-67E0-E111-A2B0-E0CB4E29C4CE.root',
       '/store/data/Run2012A/MuEG/AOD/recover-06Aug2012-v1/0000/381E66F9-71E0-E111-BE8A-E0CB4E1A1180.root',
       '/store/data/Run2012A/MuEG/AOD/recover-06Aug2012-v1/0000/2623786A-6FE0-E111-B6A6-00259073E324.root',
       '/store/data/Run2012A/MuEG/AOD/recover-06Aug2012-v1/0000/0C84A0CD-74E0-E111-BAD1-00259073E398.root',
       '/store/data/Run2012A/MuEG/AOD/recover-06Aug2012-v1/0000/08CFFA32-73E0-E111-AD83-90E6BA19A248.root',
       '/store/data/Run2012A/MuEG/AOD/recover-06Aug2012-v1/0000/0214BC27-6AE0-E111-9C8E-00259073E526.root' ] );


secFiles.extend( [
               ] )

