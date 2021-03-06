import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/00030E47-401B-E111-81D6-001A928116DA.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/001CB752-401B-E111-9CE3-00304867900C.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/00EF38EE-401B-E111-8F8C-001A928116BE.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/020E8D50-411B-E111-8C96-0018F3D096B4.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/024BFE25-401B-E111-AACC-0018F3D0962A.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/025F952D-421B-E111-9B26-003048FFCB8C.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/028EC0E8-401B-E111-923F-003048FFD740.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/02C6273F-411B-E111-BA76-003048678FC4.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/02C8C5C7-401B-E111-ACF6-002618943908.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/0423B29C-401B-E111-8D9D-003048678E94.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/0499BF32-401B-E111-B321-003048678B0E.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/04B235B2-401B-E111-BE06-001A92811730.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/04C770E9-401B-E111-87EE-0026189438EB.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/06C73B2B-411B-E111-A6BB-00261894395C.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/06EEFF08-411B-E111-97FE-0018F3D09654.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/0885B514-411B-E111-A63A-002354EF3BD2.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/08898A54-411B-E111-B137-001BFCDBD1B6.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/08BD5D80-401B-E111-A2E1-00261894386B.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/08F07E90-401B-E111-9E74-003048678B0A.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/0A522CB1-401B-E111-89E9-003048678BAA.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/0A90BD50-401B-E111-ACE8-0018F3D0970C.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/0A9F9023-401B-E111-8353-0026189438BC.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/0C103822-401B-E111-93C4-00261894383F.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/0C1958D5-401B-E111-878F-0026189438DC.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/0CDF929D-401B-E111-96E7-002618943832.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/10067FB3-401B-E111-9960-001BFCDBD154.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/103B6F52-401B-E111-8B61-002618943849.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/1064CA87-401B-E111-9516-0026189438F3.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/10EFED1E-411B-E111-AFCB-002618943860.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/125D348C-401B-E111-B96E-00261894393B.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/14D53453-401B-E111-A076-0018F3D09664.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/14F17E00-411B-E111-80B2-002618943810.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/189FA4E2-401B-E111-B639-0026189438C9.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/18A06E12-411B-E111-B144-003048FFD7A2.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/1AA5BF0F-411B-E111-8446-003048678EE2.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/1ADDC305-411B-E111-A884-002618943868.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/1C06EEB5-401B-E111-94F1-0026189438CE.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/1C2983F9-3F1B-E111-AC7E-00304867BEC0.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/1E0D5EE8-3F1B-E111-9730-00261894388F.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/1E395F00-411B-E111-A2CC-003048D15D04.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/1EAB66A0-401B-E111-99DC-002618B27F8A.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/20ABC90D-411B-E111-810B-002618FDA277.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/224A743B-401B-E111-A4AF-00261894391B.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/2610FAC7-401B-E111-B53D-001A92810AEE.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/267565F2-401B-E111-AAFD-002618FDA262.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/267E869B-401B-E111-88EB-0018F3D09692.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/26D9846A-401B-E111-ABBE-002618943921.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/28D1D8EA-3F1B-E111-9589-00304867C1BC.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/2A0E6727-401B-E111-84DF-002354EF3BDC.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/2A711E94-401B-E111-89A4-00304867BFAE.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/2ACB0666-401B-E111-BAFC-001A92971B04.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/2C0A792B-401B-E111-974E-002618943861.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/2CC4E7C0-401B-E111-8664-003048FFD744.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/2CE58AD9-401B-E111-A8D9-002618943877.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/2E04A24C-401B-E111-A7DC-001A92811718.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/2E10BBAE-401B-E111-BCBD-00261894394B.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/2E587340-401B-E111-8143-002618943951.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/2EFE6AF8-3F1B-E111-9C39-002618943982.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/30A94013-431B-E111-BADA-003048FFD71E.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/327C1774-401B-E111-8924-002354EF3BD2.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/34B66FA3-401B-E111-BAB0-0018F3D09636.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/34BEC3CF-3F1B-E111-9A4A-003048678B86.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/368590D9-401B-E111-8438-003048FF9AC6.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/383208AE-401B-E111-87CF-0018F3D096FE.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/38AD38C6-401B-E111-A760-0026189438B1.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/38B8F26A-401B-E111-B8CD-002618FDA237.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/38F04958-411B-E111-B355-003048FFD7BE.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/3CBE1209-411B-E111-879C-003048FFD76E.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/3CE70F9D-401B-E111-BCDF-002618943925.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/3CF8B801-401B-E111-98C2-003048678B0A.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/3EC9B1AD-401B-E111-B5A1-002618943832.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/40FB2CC7-401B-E111-9F92-002618943880.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/4232E6B1-401B-E111-A980-003048678BC6.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/424CCF45-401B-E111-89D6-00304867C034.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/426E21B8-401B-E111-92F3-003048FFD754.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/428C2AAF-401B-E111-81DF-0018F3D095EC.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/42A6E2C3-401B-E111-9FC6-003048678D86.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/44192918-401B-E111-9675-00248C55CC9D.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/44ABE0B9-401B-E111-93D1-0026189438C9.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/463D0AFC-401B-E111-8E56-002618943943.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/4660E161-401B-E111-B0EE-00304867BFF2.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/4699BDC4-401B-E111-89F5-002618943833.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/46CD50EE-401B-E111-87DE-001A92811742.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/487F6F67-401B-E111-9DD8-0026189438D6.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/4AD523B5-401B-E111-852A-0018F3D095EA.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/4E9F18AC-401B-E111-BD20-0018F3D096D4.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/4EB27022-411B-E111-926B-002618943964.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/4ED5F20E-411B-E111-9C00-002618943914.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/5282A42E-411B-E111-AC04-00248C0BE013.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/528D60A4-401B-E111-8F68-0026189438C4.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/5424E58B-401B-E111-9ADE-0018F3D09690.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/54917B29-401B-E111-A4D4-003048678AFA.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/54962713-411B-E111-8F1B-00261894385D.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/549CE405-401B-E111-8C70-00261894388A.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/54BA7D35-401B-E111-9B6C-001A92971BDC.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/54F5BC42-401B-E111-8C16-002618943953.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/56A0ADDC-3F1B-E111-9689-002618943923.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/56AEC394-401B-E111-9E2E-003048679248.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/580A6BC1-401B-E111-BC40-002618943868.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/5A45F4B4-401B-E111-8346-003048FFCB9E.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/5A9EAA28-401B-E111-AE82-002618943937.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/5AE9CFB2-401B-E111-98F4-002354EF3BD2.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/5CECDF24-411B-E111-86EB-002618943973.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/5E173E9A-401B-E111-B6A2-002618943856.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/5E23B364-401B-E111-BE70-001BFCDBD184.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/5E368EDF-401B-E111-8888-0026189438FE.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/5E40C214-411B-E111-B9E1-003048679168.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/5E5BD0DD-3F1B-E111-AD98-001A92971B0C.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/605F7702-411B-E111-A1EB-002618943884.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/620FA05A-401B-E111-93AC-0026189437FA.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/62106D2D-401B-E111-BFD6-002618943977.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/6439B243-411B-E111-BFEE-00261894387D.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/6468AB3A-401B-E111-91D7-00261894389D.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/663A6EC1-401B-E111-BAAD-002354EF3BE0.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/665A05AB-401B-E111-9CF1-002354EF3BE2.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/66C24C3D-401B-E111-8E56-003048678FEA.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/66D7FCD1-401B-E111-924C-003048679046.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/6A0905A3-401B-E111-93D3-00304867900C.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/6AA48EFB-401B-E111-8B10-001A92971B36.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/6AFC2525-411B-E111-828B-001A928116C6.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/6AFF58D6-401B-E111-AB4D-00261894389A.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/6C57A0D0-401B-E111-A8D2-001A92971B9C.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/6CC0F8B4-401B-E111-928A-003048FFCB9E.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/6CC648EB-401B-E111-A317-003048678AC0.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/6CCCC842-401B-E111-B1CF-0026189438C1.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/6E1F0F57-401B-E111-B8FB-0026189438AC.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/6E3735A0-401B-E111-9E78-0026189438DF.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/701740D1-401B-E111-A77C-002618943896.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/70786DF2-401B-E111-8078-001A92810AF4.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/70970A91-401B-E111-9689-001A92810AD8.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/70D6B849-401B-E111-9E23-001A9281171E.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/72123684-401B-E111-A2A2-00261894391D.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/72E3A7BD-411B-E111-97D7-0018F3D095F0.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/743FA8F1-401B-E111-AA79-0026189437E8.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/74669EA2-401B-E111-8810-0018F3D096A6.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/7696A6C2-401B-E111-82DD-003048FFD752.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/78387027-411B-E111-8348-0026189438E1.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/78449E10-411B-E111-A118-003048678E92.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/784E2896-401B-E111-8C21-00261894386E.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/78E400AF-401B-E111-8307-003048FFD776.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/78EE533D-411B-E111-8FF1-001A928116DA.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/7A365C9B-401B-E111-8C3F-003048678ADA.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/7A55DA02-411B-E111-B035-002618943971.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/7C6AE969-401B-E111-93E5-001A928116BE.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/7C9F535B-411B-E111-B421-0018F3D09636.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/7E606550-401B-E111-855A-0026189438C4.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/7E8DB04B-401B-E111-9FC2-003048678F26.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/7EF69321-411B-E111-8FF3-003048678C9A.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/800A852E-411B-E111-8420-0026189438FF.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/82103969-401B-E111-B692-0018F3D0961E.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/821BBF27-411B-E111-A3C1-003048678F62.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/823C55A8-401B-E111-BF45-003048679006.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/82970241-401B-E111-A945-0026189437FC.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/82F68595-401B-E111-9CB3-002618FDA237.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/842F6AB2-401B-E111-A33E-001A92971B72.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/843F2498-401B-E111-B966-0026189438BA.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/8458CDDF-401B-E111-86E0-00304867C1BA.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/84F5FB8C-401B-E111-BDF5-00304867C1B0.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/866CDDF0-401B-E111-8157-001A92971B84.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/8A33C07A-401B-E111-8D5A-0018F3D095EE.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/8C6A8BB1-411B-E111-B432-002354EF3BD0.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/8C9056BC-401B-E111-B3E1-0018F3D096DA.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/8CA8CB24-411B-E111-A331-003048FFCB74.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/8CC348FB-401B-E111-9B2B-002618943916.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/8E046A2D-411B-E111-8CA0-002618FDA277.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/8E3F68B3-401B-E111-ACEA-002618943970.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/8E4A902A-411B-E111-A785-002618943971.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/8E67B4C1-401B-E111-9F7A-001BFCDBD1BA.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/908B66D0-401B-E111-AE7C-00261894397A.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/90A3D0D5-401B-E111-B41D-0018F3D095F8.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/90F65DAF-401B-E111-8CF9-002618943944.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/90F791A2-401B-E111-BF91-003048678B04.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/94299B03-411B-E111-81EA-002618943960.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/94A0D1DD-401B-E111-9CE7-0018F3D09692.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/9626E899-401B-E111-9E29-0018F3D09644.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/96B8AC56-411B-E111-BCAF-0026189438B1.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/96BB9A2E-411B-E111-89D4-001A92971B64.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/96E09F0E-411B-E111-B104-003048678BB2.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/96E70CD2-401B-E111-A2DB-002618943870.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/96EF88AD-401B-E111-8884-00261894388A.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/986A492D-421B-E111-B15B-003048FFD776.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/98C22F22-411B-E111-AE5D-0026189437EC.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/98CD3369-401B-E111-8A4E-003048FFCB74.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/9A0682B7-401B-E111-8761-0026189438EF.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/9A88EC06-411B-E111-B865-00304867C0C4.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/9AFC5AD0-3F1B-E111-80D9-002618943932.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/9C411EE9-3F1B-E111-B381-0026189438A2.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/9CC0D890-401B-E111-AF57-00248C0BE018.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/9EE767BF-401B-E111-8A5F-003048679296.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/A0629F9C-401B-E111-9E19-003048678B26.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/A0C07CBB-401B-E111-91D0-002618943963.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/A0FC972C-411B-E111-ADD3-003048FFD770.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/A2115C01-411B-E111-9AB3-00261894387A.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/A462220B-411B-E111-804E-002354EF3BE0.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/A467457F-401B-E111-9000-0030486790C0.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/A4978A91-401B-E111-BC8E-001A9281173A.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/A6043B44-411B-E111-9CA0-00304867C04E.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/A606B36B-401B-E111-95EC-00261894388F.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/A61A490C-411B-E111-B915-003048678FC4.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/A66BFD86-431B-E111-AABD-003048FFCC2C.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/A6AF6ABF-401B-E111-A094-0026189438B1.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/A8DFB5D8-401B-E111-921E-003048FF9AA6.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/AA192EE3-401B-E111-BB04-002618943826.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/AA3CFED6-401B-E111-8E55-002618943943.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/AA5411C0-401B-E111-AF87-003048678BE6.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/AA7B4033-401B-E111-898E-0026189438ED.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/AAAA84EC-401B-E111-AAC3-003048FF9AA6.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/AC2F5AEA-401B-E111-AE82-003048678B1A.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/ACEB53AD-401B-E111-9423-003048678AE4.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/AE255F2F-401B-E111-B0B3-001A92810AA0.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/AE6CB9EC-401B-E111-9357-001A928116E0.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/AE7B5C90-401B-E111-9686-00304867C1BC.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/AEFEAC02-411B-E111-B088-0026189437E8.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/B0B7E52D-401B-E111-9D8F-003048678B72.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/B0F39DD8-411B-E111-ABAC-003048FFD740.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/B2661240-411B-E111-9F36-003048FFCB6A.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/B41E6340-401B-E111-AFEB-0018F3D0961E.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/B48353A4-401B-E111-A328-001A92971B64.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/B483D7DE-401B-E111-8A97-003048FFD79C.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/B4C29B2C-401B-E111-9965-002618FDA237.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/B6351E76-401B-E111-A3AD-001A92811742.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/B68BEACB-401B-E111-8CFE-003048FFD720.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/B6E7C6C0-401B-E111-9FCB-002618943900.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/B82CB86F-401B-E111-9227-00261894397F.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/B8934148-401B-E111-91FD-003048678B06.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/BA3C1097-401B-E111-9CE8-001A92971BD6.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/BA5B76B2-401B-E111-98A9-003048FFCB8C.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/BA8700D9-401B-E111-8D18-001BFCDBD160.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/BAB46FD8-401B-E111-B61A-002618FDA208.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/BACCC4D9-401B-E111-B0AA-003048FFCC1E.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/BC38804C-401B-E111-BC9A-001A92971B9A.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/BCA2408B-401B-E111-8EF7-0018F3D09652.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/BCEE5AB6-401B-E111-A61A-002618943875.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/BCFA32AA-401B-E111-88B9-00261894392F.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/BE93892C-401B-E111-942D-003048678F74.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/BEAB831E-411B-E111-B757-002618943943.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/BEFA00BC-401B-E111-A4D0-002354EF3BDA.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/C03DABA4-401B-E111-A9E5-00261894395C.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/C07A9F50-401B-E111-A019-003048678B0C.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/C22C2125-401B-E111-B574-003048678FA6.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/C2BAE846-411B-E111-A670-00261894386D.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/C44123E8-401B-E111-A9E6-003048678FE0.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/C61AC925-411B-E111-AEAC-003048FF9AA6.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/C6253BB3-401B-E111-B650-002618943973.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/C6E5517D-401B-E111-A8DE-00261894397F.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/C80310DB-401B-E111-9476-001A92811706.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/C89D38DC-401B-E111-9E91-003048FFCBA8.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/C8B4FDCD-401B-E111-BDE2-00261894396A.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/CA48562B-401B-E111-9245-002618943829.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/CA8CDC14-411B-E111-BD21-001A92810ADC.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/CAEA7C2B-401B-E111-8C6C-003048FFD730.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/CC941091-401B-E111-8924-0026189438D7.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/CEE53D48-401B-E111-B5DD-0026189437F0.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/D00509B0-401B-E111-969D-0018F3D096C8.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/D02CF2EF-401B-E111-9187-001A9281170C.root' ] );
readFiles.extend( [

       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/D062CA87-401B-E111-B346-00261894393A.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/D2AC03DF-401B-E111-AEC9-0026189438A7.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/D4712051-401B-E111-9AF8-0018F3D0969A.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/D4ABEF56-401B-E111-91D0-003048FFCB9E.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/D64E8ABC-401B-E111-A914-003048678F8A.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/D87D6CD6-401B-E111-AC88-0018F3D096E0.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/D884D2A5-401B-E111-9145-003048FF9AC6.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/D8BDC3D5-401B-E111-97E5-00304867C026.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/D8EC2496-401B-E111-BD10-00261894390A.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/D8F95C1E-411B-E111-B958-0026189438B1.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/DA167CB8-401B-E111-8DCC-002618943920.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/DA95FCD1-401B-E111-876A-001A92810AD8.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/DC137F52-401B-E111-8F5E-003048678F8C.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/DC1DC024-411B-E111-9FB3-003048D15D22.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/DC3A5A8C-401B-E111-925F-002618943956.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/DC544CAD-401B-E111-AACA-0018F3D09684.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/DC961344-411B-E111-B1FF-003048FFD730.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/DCA4990A-411B-E111-98A9-003048678B0C.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/DE0A75B8-401B-E111-9574-0026189438F6.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/DE7A5AEF-401B-E111-B28D-003048FFCBF0.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/DEABB225-401B-E111-A6D7-002618943964.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/DED37DAA-401B-E111-937C-0026189438E2.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/E054B865-401B-E111-8B38-00248C0BE016.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/E06A85A5-401B-E111-92F9-001A92971BDA.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/E21A593E-401B-E111-8126-002618943915.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/E45D0029-411B-E111-A30F-002618943865.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/E4D567BD-401B-E111-BBA9-0030486791F2.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/E67B1829-401B-E111-92E9-003048D3C010.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/E6A58393-401B-E111-9FC0-0018F3D09686.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/E8255CDE-401B-E111-A3DE-001A92810AB2.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/E83C0306-421B-E111-A438-003048FFCB84.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/E86E663F-411B-E111-B5F0-003048FFD740.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/EA21CEAF-401B-E111-ABDB-003048D3FC94.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/EAA3268F-401B-E111-A927-001A92971B1A.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/EAFB1420-411B-E111-805E-002618943856.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/EAFE8868-401B-E111-80A2-003048FFCBA4.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/EC4DE433-411B-E111-BD3A-001A928116DA.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/ECCB6EDB-401B-E111-AE2A-002618943838.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/EE27BCD6-3F1B-E111-8715-003048678FFE.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/EE90672A-411B-E111-BD4F-002618943882.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/F038AD27-401B-E111-96FC-0026189438F3.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/F04468C4-401B-E111-BE5C-0018F3D096A2.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/F21090FB-401B-E111-B3B5-001A92971B36.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/F470EDF0-401B-E111-A47E-003048678B72.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/F49D263B-401B-E111-BEAA-0026189438A7.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/F4D4EBD4-401B-E111-91A8-00261894392F.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/F8D05696-411B-E111-AED2-001BFCDBD19E.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/FAEB0EBD-401B-E111-B183-001A92811732.root',
       '/store/data/Run2011A/METBTag/AOD/08Nov2011-v1/0000/FEB327A6-401B-E111-ADE8-003048678FB2.root' ] );


secFiles.extend( [
               ] )

