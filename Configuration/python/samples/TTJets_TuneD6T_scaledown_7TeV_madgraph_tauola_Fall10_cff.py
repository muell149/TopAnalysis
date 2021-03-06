import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
    '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0003/EEF9F477-8BDE-DF11-B274-001EC9EB9223.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0003/D42CE2B5-C0DD-DF11-8313-A4BADB3CF272.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0003/CCA90DC7-DCDD-DF11-803D-E0CB4E29C4E0.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0003/BA5F27D7-8BDE-DF11-8DC2-0019B9E7CD1E.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0003/A683B96E-ADDD-DF11-A8B4-003048D3E452.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0003/74B1F858-28DE-DF11-A43C-00261834B602.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0003/5E3D074E-27DE-DF11-97AA-001F29651428.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0003/506DFC4B-C7DD-DF11-9F78-001E68A9934C.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0003/4E34334B-B3DD-DF11-AC04-00D0680BF95A.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0003/46991F8B-29DE-DF11-AF42-00D0680BF90E.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0003/46175F22-CFDE-DF11-9BCC-00145E551FC4.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0003/3CF41B62-28DE-DF11-8ABA-001517357E56.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0003/36B5240B-ADDD-DF11-B0D9-90E6BA19A21C.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0003/36131AA2-26DE-DF11-BC27-485B39800B65.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0002/FC21334D-70DD-DF11-AB15-90E6BA19A24A.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0002/D21072D1-7EDD-DF11-9EDE-485B39800C1A.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0002/C6CD5A01-47DD-DF11-9F59-001D09675143.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0002/B87E9498-73DD-DF11-9DB5-001A4BA5ABE2.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0002/AE18A022-49DD-DF11-A95A-00D0680BF8EE.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0002/AA35F77E-86DD-DF11-9421-001E682F84DE.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0002/A2F54936-51DD-DF11-9BF9-00D0680BF8F0.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0002/A295ADBD-7ADD-DF11-BADF-00145E5516DC.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0002/9261FCB0-4ADD-DF11-A4B0-485B39800BBF.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0002/7C5B2026-5FDD-DF11-888D-0030487DF85C.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0002/7612EAB0-A9DD-DF11-A9D1-001517357DFE.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0002/7031BC7A-72DD-DF11-8466-0019BB3C2FB8.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0002/6CF96EB5-A7DD-DF11-B7F2-003048D3E454.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0002/4E333FD6-45DD-DF11-B87D-00D0680BF96E.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0002/42B7FCA2-7ADD-DF11-9DE8-A4BADB3CEBEF.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0002/32AA9764-45DD-DF11-B08D-00145E5520F3.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0002/2EF82854-5CDD-DF11-B378-00D0680BF984.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0002/26A3811A-30DE-DF11-A220-E0CB4E1A118C.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0002/24E3C421-A8DD-DF11-A5BE-00151725625B.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0002/1EDBBE21-A8DD-DF11-A152-001517255D36.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0002/1ECB9E50-59DD-DF11-B261-001E682F25C8.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0002/08C97131-63DD-DF11-B3D4-003048642BAD.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0002/080A3706-6ADD-DF11-8AE9-E0CB4E29C4BF.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/FAE849AF-1EDD-DF11-B02D-90E6BA442F0B.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/F23480EC-2ADD-DF11-9FE0-90E6BA442F3E.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/EE720672-1CDD-DF11-A7BC-E0CB4E1A116B.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/EC2192ED-E0DC-DF11-8C88-485B39800B74.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/EA9BA5CC-1BDD-DF11-B417-001A4D5FE3D0.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/E8F39A96-29DD-DF11-8FBD-001E0B8D1954.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/E67C67C6-0ADD-DF11-AC6D-E0CB4EA0A91C.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/E6370DF1-DEDC-DF11-A8A0-E0CB4E1A1186.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/E48005C3-22DD-DF11-BF1A-E0CB4E29C4EE.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/E0B0E818-EBDC-DF11-82FA-E0CB4E19F969.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/E03D10DD-12DD-DF11-B79F-90E6BAE8CC20.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/D81071A9-0BDD-DF11-90AC-E0CB4E29C4EE.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/D29504E0-26DD-DF11-9AD8-00145E552147.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/C8DB3999-01DD-DF11-BEB9-485B39800C15.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/C858E747-05DD-DF11-B6A4-001F296564C6.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/C65CEA85-08DD-DF11-87FA-90E6BA19A24C.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/C0E939F5-17DD-DF11-B9A3-E0CB4E553659.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/BE78D7F7-EADC-DF11-9893-0015172560CF.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/BA8DABC4-D4DC-DF11-AC34-E0CB4E1A1149.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/B69BDF34-D1DC-DF11-A960-E0CB4E29C515.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/B48AABE4-12DD-DF11-AF95-E0CB4EA0A932.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/B40A6142-39DD-DF11-922E-003048C99F9C.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/B29A9CD7-25DD-DF11-ACDA-90E6BA442F06.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/B004329C-E1DC-DF11-8875-001E682F87E6.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/AC504A99-51DD-DF11-B615-A4BADB3CF260.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/A6603F52-17DD-DF11-A031-001E68A993AA.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/A0A34554-18DD-DF11-82C3-E0CB4E29C4D6.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/9A778676-46DD-DF11-9997-00145E552378.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/96B8AFC8-3DDD-DF11-9E42-00237DA1FBE8.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/8EA3043C-0BDD-DF11-A685-00D0680BF99E.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/8E6249FB-06DD-DF11-979F-0030487DF856.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/8E0BF3DB-46DD-DF11-8EAE-001E68A993EE.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/8C398D31-D1DC-DF11-8476-90E6BA19A20E.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/8C1D8F37-21DD-DF11-9229-E0CB4E29C4F9.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/867703B0-12DD-DF11-819A-90E6BA442F32.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/84E349A3-F6DC-DF11-8BAE-485B39800B8A.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/7EA4782C-FCDC-DF11-9A95-00145E551E68.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/7C7D208C-F0DC-DF11-90A9-E0CB4E19F972.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/7C0CB986-0ADD-DF11-9325-003048CDC92E.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/7012C1E2-E3DC-DF11-98F0-90E6BA442F06.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/688A1C87-FBDC-DF11-B14C-485B39800BC8.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/62C015DE-0CDD-DF11-A8EB-001A4D5FEA4A.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/623A3AEC-28DD-DF11-93ED-E0CB4E29C516.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/5E958417-16DD-DF11-9D8E-0030487E4B96.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/58EDC317-07DD-DF11-A71F-003048D47661.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/58A6DDC7-E8DC-DF11-9FBA-E0CB4E553672.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/4A83A3B7-E6DC-DF11-A913-E0CB4E4408DB.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/46BD3092-52DD-DF11-B617-001E68A993D6.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/42DD3CD1-1DDD-DF11-8425-003048792C12.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/3E3BADA9-43DD-DF11-8E0D-00145E5519C0.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/3ADED824-21DD-DF11-A083-00D0680BF94A.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/2C556F98-2BDD-DF11-BC6B-E0CB4E29C4B8.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/2A2E356F-35DD-DF11-9DB0-00248CB320A5.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/28CAC9A3-0EDD-DF11-A0E7-E0CB4E29C4BF.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/26322BD9-16DD-DF11-B06A-E0CB4E553656.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/24BB145E-EFDC-DF11-BE89-001A4BA87394.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/18921016-2FDD-DF11-BBC2-001517256102.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/188B5D0B-F4DC-DF11-827D-0030487CDAC6.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/1882B4D8-05DD-DF11-9F95-E0CB4E55366C.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/16EC0F8E-41DD-DF11-B47B-001E68A9949E.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/10786E97-D6DC-DF11-A5D2-E0CB4E553641.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/0AF8D2EE-40DD-DF11-B59E-00D0680BF908.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0001/088C4690-FEDC-DF11-A46C-0030487CB568.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/E4544E40-DEDC-DF11-B159-003048D47670.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/D452DAA7-C0DC-DF11-8AA2-90E6BA0D09CA.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/88B6364C-CBDC-DF11-A6D4-E0CB4E19F9A6.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/38DC4731-CDDC-DF11-8435-E0CB4E19F9B7.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/2ACD6DD3-C2DC-DF11-A862-0019BB3F834E.root',
        '/store/mc/Fall10/TTJets_TuneD6T_scaledown_7TeV-madgraph-tauola/AODSIM/START38_V12-v1/0000/02D0D081-B8DC-DF11-AD79-90E6BA19A257.root'
    ] );


secFiles.extend( [

    ] )
