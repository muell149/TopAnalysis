import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/000610C6-87EF-E111-AE0A-001EC9D8A8A0.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/028EC2E4-4AEF-E111-9816-485B39897219.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/02AE8E3E-A0EF-E111-8DD7-00259073E44E.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/02FCCF18-50EF-E111-A0F3-00259073E376.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/02FE1BB7-41F3-E111-80FF-00261834B577.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/04314D61-49EF-E111-9521-00261834B569.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/063BAEF7-BDEF-E111-81EB-00259073E406.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/0842B21D-F4EF-E111-8434-001EC9D2BCD7.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/086AC513-7DEF-E111-9F66-00259073E504.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/08D4729D-59EF-E111-826C-001EC9D7F207.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/0AB11D7C-71F1-E111-A89C-00259073E502.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/0C25A992-CEEF-E111-855F-00259073E3A8.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/0C76DB5A-60EF-E111-B96B-001EC9D52DF4.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/0E1B4EC6-49EF-E111-8793-00259073E35A.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/0E5D7F2A-B8EF-E111-867C-90E6BA19A1FD.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/1011E974-57F5-E111-993E-001E4F3F1E86.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/108E58EF-6EEF-E111-87D8-00259073E4A2.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/10E3B0FA-B0EF-E111-BCFD-E0CB4E553665.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/10F3141F-48F7-E111-B47F-485B39800C3B.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/12B24111-4DEF-E111-A080-00259073E536.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/1610694B-DEEF-E111-97E6-00259074AE8A.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/16369F16-62EF-E111-BFA7-002590747E14.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/1C6965F7-FEEF-E111-A99B-00259073E3A8.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/1CACD1EC-4BEF-E111-BF37-E0CB4E553688.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/1ED49CB5-7EEF-E111-90B5-E0CB4E553639.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/20280A07-9FF6-E111-90C7-90E6BA0D099E.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/24B5C0E6-5BEF-E111-B859-00259073E346.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/24ED552B-90EF-E111-9859-BCAEC54B302A.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/26E9AF5A-0BF2-E111-B92D-90E6BA0D09AD.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/26EDD6A3-A7F0-E111-8DDD-90E6BAE8CC08.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/28ED0E55-72EF-E111-97AA-002618FDA194.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/2A16643B-66EF-E111-961E-001EC9D825B5.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/2A52E0A6-A1EF-E111-9819-00259074AEA6.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/2A67C2F4-61EF-E111-A013-20CF305B0508.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/2A7B1750-75EF-E111-ACC8-00259073E450.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/2EEE993E-D3EF-E111-9C77-20CF3027A560.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/2EF238DA-DCF2-E111-A26A-E0CB4E29C4E0.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/3293FEFB-5DEF-E111-BB40-E0CB4E29C4D9.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/3450FD72-65EF-E111-B514-001EC9D81A4E.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/3634FC7D-93EF-E111-8959-0030487C73D4.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/3663238F-D1EF-E111-8209-0030487CDAC2.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/36B231D6-C8EF-E111-A289-E0CB4E19F9A5.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/36EA174B-63EF-E111-9FFA-20CF3027A5B7.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/38AFA3B5-5AEF-E111-8C93-485B39800B86.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/38F22EF1-78EF-E111-AE6A-00259073E41E.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/3AD7BCD3-D5EF-E111-B0AA-E0CB4E19F9B2.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/3AF91275-6CEF-E111-A9F1-00259073E44E.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/3EEEFBED-98EF-E111-907C-90E6BA442EF7.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/40D087F2-6FEF-E111-85C7-90E6BA19A24C.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/447617B0-BEEF-E111-B8D8-00259073E406.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/44CAEBD0-66EF-E111-8719-00259073E3A0.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/44D100D8-89EF-E111-8116-485B39800BFB.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/46C54337-35F2-E111-9E02-0030487C6A32.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/48A5BA51-56EF-E111-893B-00261834B520.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/4CE886B7-55EF-E111-8A23-E0CB4E55367D.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/4EB0EB27-52EF-E111-A6A6-00259073E526.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/50E25006-9EEF-E111-B55F-E0CB4E29C4F1.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/52853A04-ADEF-E111-A654-00259074AE54.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/5285AAE5-56EF-E111-8A21-E0CB4EA0A932.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/54016B76-A5EF-E111-A3B3-001EC9D79318.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/567011E5-56EF-E111-AF41-E0CB4EA0A8D7.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/58BEBAD4-86EF-E111-A012-E0CB4E19F973.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/58DFC411-A6EF-E111-97EB-001EC9D79318.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/603360E1-7FEF-E111-BB8E-00259073E51A.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/60837C22-69EF-E111-9322-E0CB4E19F9BB.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/646288B6-9AEF-E111-8521-00259073E382.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/64C44CFA-09F3-E111-9077-00259073E364.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/684ADC65-3DEF-E111-993A-E0CB4EA0A929.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/6872F10C-DBEF-E111-A3D6-00261834B51D.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/688EFC00-7FEF-E111-8A44-E0CB4E553656.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/6ADC8AB5-96EF-E111-B928-20CF3027A5D5.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/6E9C98C1-E0EF-E111-AEA4-E0CB4E55363A.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/70172239-45EF-E111-B1BF-00259073E44E.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/7288530C-B9EF-E111-A9E1-00261834B529.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/7289DA23-38EF-E111-B1DF-E0CB4E1A116D.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/72BD3AFC-70EF-E111-8135-001EC9D8D081.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/72D2648C-92EF-E111-A8EE-00259073E336.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/745ACCBA-77EF-E111-932B-003048D28EB2.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/745BA0AD-8CEF-E111-9E3B-001EC9D8B992.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/74C40F23-71EF-E111-81FE-20CF305B052C.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/74D3E637-80EF-E111-BFE8-00259073E488.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/7649ECE2-C0EF-E111-AD0B-00259073E3A6.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/76C69A72-6FEF-E111-B687-00259073E3E4.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/7A21B4C6-5CEF-E111-AC15-90E6BA442F36.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/7A5A76A7-62EF-E111-A90B-00259073E370.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/7AAAE57B-68F1-E111-B548-485B39800B94.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/7CEAB352-47EF-E111-A9D4-00259074AE80.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/7E92DD3E-73EF-E111-8C1D-00259073E3D2.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/80A3BE29-BCEF-E111-AD31-00259073E3F2.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/842FB1EB-A9EF-E111-8968-00259073E37C.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/88D1676E-43EF-E111-B2DA-485B39897225.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/88D358D0-57EF-E111-8A20-E0CB4EA0A8DB.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/8A5380EC-50EF-E111-8B10-E0CB4E29C4DD.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/8ACAEB5E-4AF1-E111-A272-00259073E450.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/8E82E432-50EF-E111-8384-00259074AEE6.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/9231CF17-FAEF-E111-83DD-00259073E3E6.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/9416E3E1-4EEF-E111-9453-00259073E526.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/9609A06C-11F0-E111-9A70-00259073E496.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/96554253-60EF-E111-9982-485B39800BBA.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/989CD14B-53EF-E111-9550-20CF3027A5B0.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/9A415AC8-84F3-E111-AD24-20CF305616DC.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/9A5E9659-5DEF-E111-A36F-00259073E37C.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/9A634BC9-84F3-E111-B4CF-00259073E516.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/9AD0B646-CEEF-E111-BD1D-00259073E406.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/9C151F99-4AEF-E111-BDAE-E0CB4E29C4BF.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/9C3E5772-9CEF-E111-A0A5-20CF3027A614.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/9E7B9722-40EF-E111-8EBD-00259073E46C.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/9E985829-7EEF-E111-AF91-00259073E316.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/A0253797-6BEF-E111-A22F-00259073E4A2.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/A2BF19E2-97EF-E111-AE12-0030487C73D4.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/A45AA2CD-8BEF-E111-BB81-E0CB4E19F96B.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/A4B2B787-91EF-E111-A05A-00259074AEAC.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/A6136686-9FEF-E111-97A4-00259074AEA6.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/A62DFD50-92EF-E111-9E6A-001EC9D825C9.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/A649A506-78EF-E111-BA78-E0CB4E19F985.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/A67748A5-58EF-E111-8954-001EC9D7F21F.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/A68BE79C-DAEF-E111-9352-0030487CDB2C.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/A6FD7D6F-3CEF-E111-B7F2-00259073E3D6.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/A8B9E36D-D8EF-E111-B937-00259073E4C2.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/A8DF8CB8-46EF-E111-B300-001EC9D278CC.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/AA691062-4CEF-E111-9544-00259073E536.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/ACD2C381-BCF0-E111-A5D8-001E4F3F1E86.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/AE1AA272-EFEF-E111-B2F8-E0CB4E19F9B9.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/B02A56E8-6DEF-E111-A322-001EC9E7BF79.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/B05A599D-53EF-E111-908B-485B39897259.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/B098A630-6CEF-E111-B302-00259073E4CA.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/B0DA0DB8-A4EF-E111-B4F8-00259073E3CA.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/B23C9A7A-79EF-E111-8E29-00259073E44E.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/B2DF5C80-54EF-E111-BA81-00261834B586.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/B2DFF6BA-7AEF-E111-B285-20CF3019DEE9.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/B2F3F698-5BEF-E111-9ADB-002590747E28.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/B4D59818-83EF-E111-80C5-001EC9D7F667.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/B62F35F2-6AEF-E111-A93E-00259073E4A2.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/B644A53A-35F3-E111-A899-00259073E304.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/B676FB37-54EF-E111-8457-00259073E4E6.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/B8A0A7A1-ADEF-E111-94BE-00259074AE54.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/BA6437AD-6FEF-E111-82AD-E0CB4E29C4CE.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/BA947E40-6AEF-E111-8CF8-00259074AE3C.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/BCDFDE54-8FEF-E111-8D6E-00259073E47E.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/C0CE478B-84EF-E111-AC0F-00261834B561.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/C0F530B5-95EF-E111-AD21-20CF305B0556.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/C2C4B789-EBEF-E111-A342-002590747E1C.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/C43A8233-64EF-E111-8C25-00259073E390.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/C6AFF3FA-29F2-E111-807A-485B39897219.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/C880AF88-51EF-E111-B32A-485B39800C14.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/CA4763F9-81EF-E111-88E8-E0CB4E1A1197.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/CA901FD1-54EF-E111-A6FA-0030487C6A1E.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/CC410627-DDEF-E111-A179-E0CB4E19F995.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/CCA390AA-6DEF-E111-89E2-00259073E534.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/D2031269-7CEF-E111-A98E-90E6BA19A215.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/D28C1035-51EF-E111-8253-E0CB4E19F999.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/D6D65622-8EEF-E111-B20C-E0CB4E1A1187.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/D6D70DFD-8CEF-E111-9C34-90E6BA442EF7.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/D81A5795-3EEF-E111-ABAF-002590747DE2.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/D83DC2E4-88EF-E111-B21D-001EC9D8B98A.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/D8E7FC33-DCEF-E111-868B-00259074AE6A.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/DA14C4C6-76EF-E111-84F9-20CF305B0524.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/DA9B65AF-8CF0-E111-B143-E0CB4E1A11A3.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/DCF558BC-D6EF-E111-8FE7-485B39800BB9.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/DE27EE67-58EF-E111-9242-00259073E526.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/E0D284BC-0DF2-E111-B9CB-0030487C73D4.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/E0DC1C92-B6EF-E111-BB96-00259073E406.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/E40CB314-65EF-E111-97CB-00259073E4E8.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/E4EE409F-F6EF-E111-A3C6-20CF3019DEFB.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/E82ABD98-E6EF-E111-B0A2-0030487CDAC2.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/EAE0F607-72EF-E111-8F7B-00259073E446.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/EE3CD53F-6AEF-E111-AB09-001EC9D8D081.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/EE483C0B-9EF0-E111-9843-F46D043B4216.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/EEB8A071-5FEF-E111-A47A-00261834B520.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/EEE4B5CD-7BEF-E111-8709-90E6BA19A215.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/F00F1992-5EEF-E111-8FF5-00259073E388.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/F0F9FF8A-85EF-E111-8DAA-00261834B575.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/F20233EA-F6EF-E111-A60A-90E6BA442EEE.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/F2478235-4FEF-E111-BC67-00259073E466.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/F2644055-AEEF-E111-BCBC-001EC9D81460.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/F28CCADF-3AEF-E111-A876-90E6BAE8CC1C.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/F2DF5478-C4EF-E111-96BD-90E6BA19A24A.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/F415F037-CDEF-E111-9B12-00259073E4EA.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/F430436B-C2EF-E111-B3D9-90E6BA19A24A.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/F4AEEFF2-47EF-E111-80F2-E0CB4E29C4DB.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/F4F2B6D0-59EF-E111-AB6D-90E6BA19A1F9.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/F6132050-4EEF-E111-A6B1-00259074AE28.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/F63E6722-9BEF-E111-B8E6-20CF3027A57C.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/F8B1A2AC-00F0-E111-A815-E0CB4E1A1172.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/F8E3B7D2-5CF4-E111-92C0-20CF305B052C.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/F8EDFBB0-67EF-E111-9BB9-00259073E3E0.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/FC7546D1-CAEF-E111-854B-00259073E4CC.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/FC76BAE1-EAEF-E111-B9AA-002590747E1C.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/FE2746F7-5AEF-E111-8B40-E0CB4E29C4E5.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/FE6CA0FB-4DEF-E111-A99D-00259074AEAE.root',
       '/store/data/Run2012C/DoubleMu/AOD/24Aug2012-v1/00000/FEA502BC-74EF-E111-938B-00259073E53C.root' ] );


secFiles.extend( [
               ] )

