import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/FCB9049A-1A43-E211-8733-00248C9BA537.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/FC35D0F8-1943-E211-A630-00259073E36E.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/F6A21927-1D43-E211-9C94-20CF305B0581.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/F4CB6BEB-1B43-E211-9B51-00259073E4BC.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/F0ADF3D4-1C43-E211-9B46-E0CB4E55366C.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/EE0AE7FC-2343-E211-AB86-00259073E4FC.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/E8DA587B-2843-E211-98F3-002618244E15.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/E406636B-3843-E211-8622-001EC9D8B532.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/DC6511E1-3043-E211-A3F3-00259074AE54.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/D40C9196-2543-E211-8E85-90E6BA19A22D.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/D2BCC99B-2F43-E211-8AFB-E0CB4E29C4EC.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/CA1F3693-1B43-E211-B1B7-00259074AE3C.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/C891B18D-1C43-E211-B6C7-20CF3027A60B.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/C49AC51C-3343-E211-8C93-E0CB4E5536EF.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/C21C5AF8-1A43-E211-9487-001EC9D7FA14.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/BAC35B75-1143-E211-ACFD-20CF300E9ECD.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/B83109F3-1A43-E211-8E55-E0CB4E29C4E4.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/AE439F52-1843-E211-8B17-E0CB4E29C4C7.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/AA833BBD-1643-E211-AA8C-20CF3027A5ED.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/A6552208-1743-E211-88C1-E0CB4E1A1144.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/A412C56E-2043-E211-BD9E-00259073E364.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/9C9CDA35-2B43-E211-8190-00259074AEE6.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/9C7D7EF9-2D43-E211-A563-001E4F236DC1.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/98C556A6-1943-E211-81E2-00259073E4B6.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/924E9870-2143-E211-8783-90E6BA19A25D.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/8C557221-3643-E211-B901-001EC9D8B179.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/866B1ABF-2643-E211-9EE3-E0CB4EA0A904.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/841813E4-4943-E211-8227-00259073E516.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/800AAECC-1E43-E211-82E3-002590747E0E.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/7ED60B69-3243-E211-A499-00259073E3D4.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/7E75DE1D-1643-E211-868F-00259074AE28.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/7CF430B6-1743-E211-B5D5-20CF3027A626.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/7C015670-2143-E211-9F12-485B39800B95.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/7850ACFE-2843-E211-A14C-20CF3027A5B6.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/6A73235F-2343-E211-B392-00259077501E.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/68DDBBAA-1843-E211-B615-00259074AEDE.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/66514846-1A43-E211-81A9-20CF305616CC.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/54F9C145-1A43-E211-BB19-001EC9D82BC7.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/4ABCC277-1F43-E211-ABBB-485B39800C14.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/40A61FDF-3443-E211-AF2F-485B39800B95.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/3CBE4FB0-2443-E211-BB6D-002590574604.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/3C01A1B9-2243-E211-B25C-E0CB4E4408DD.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/36A96903-1943-E211-B1FC-00259073E51A.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/2C8DED76-4743-E211-BD3F-E0CB4E4408DE.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/2A4EFA02-1843-E211-B4F6-90E6BA442F15.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/24CC156E-4143-E211-8CDF-002590747D94.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/24C49EF0-3343-E211-B11A-20CF3027A627.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/1CBAEBC6-1D43-E211-92CE-E0CB4E29C502.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/12480ABB-2C43-E211-A607-E0CB4E55367B.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/0C5F7DD8-2B43-E211-8CFC-90E6BA19A20A.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/06031D13-2243-E211-A509-002590747E14.root',
       '/store/data/Run2012C/DoubleMu/AOD/EcalRecover_11Dec2012-v1/10000/00FE59F2-2943-E211-AD69-20CF305B04ED.root' ] );


secFiles.extend( [
               ] )
