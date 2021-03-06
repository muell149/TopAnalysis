import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/244/B47B3ECE-876D-E011-9839-000423D98B6C.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/252/84C09974-706E-E011-8505-0030487CD7E0.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/255/1476D645-366E-E011-932B-001D09F252E9.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/255/4E9CCC32-436E-E011-BB0F-001617DBD224.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/164/236/A2789CFF-F179-E011-B326-0030487CD6DA.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/255/72A7DD53-6E6E-E011-95D8-001617DBD5AC.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/255/8A75115B-6470-E011-B2BF-003048F118AA.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/255/8AB257A4-4E6E-E011-913C-0030487CF41E.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/255/A69FC3F6-4370-E011-BDA8-001D09F2525D.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/255/B6F94FA7-446E-E011-898E-001D09F28F11.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/255/BCEB4CC6-3F6E-E011-85EC-003048D37538.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/255/CE96830A-3A6E-E011-9A4A-003048F117B4.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/255/E8F5F344-AC6E-E011-821B-001D09F2932B.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/255/F850CE5F-566E-E011-A31B-0030487CD6D8.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/261/326B1A06-606E-E011-A0F3-0030487CD704.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/269/B0F40BC7-A870-E011-BA47-001D09F2441B.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/270/04D71334-AF6E-E011-866D-001D09F2305C.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/270/1083B9E6-9E6E-E011-8ED9-001D09F24F1F.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/270/16E6C0EF-AC6E-E011-B619-003048F118E0.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/270/32BFFDEF-AC6E-E011-ADC3-001D09F291D2.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/270/3E0EB44B-B36E-E011-97E8-0030487CD6E6.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/270/5E10350F-ED6E-E011-A375-001D09F24303.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/270/844920E0-EF6E-E011-9E8C-001D09F28E80.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/270/B423D23B-F66E-E011-8BB9-003048F024FE.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/270/C2216CF6-B36E-E011-83FD-003048D2C0F2.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/270/C4640D1C-116F-E011-9A18-0030487CD184.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/270/D89DDAE7-9E6E-E011-9817-001D09F29524.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/270/F6C31FD5-AA6E-E011-9017-0030487CD17C.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/275/7047E7A8-446E-E011-B72C-001D09F251D1.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/286/5675F8A9-EB6E-E011-8E2F-001D09F24489.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/286/5CB405FC-E76E-E011-8AE0-003048F11C58.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/296/32FC1601-E56F-E011-B779-00304879EE3E.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/286/EC4EAA1D-7E6F-E011-82C5-001D09F24FEC.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/289/68CD410B-E16E-E011-85E5-001617C3B5D8.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/289/6C6B2D07-5472-E011-9A37-001D09F2841C.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/289/82263A97-E46E-E011-A8F7-001617E30E2C.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/296/96024812-3E6F-E011-995A-001D09F24F65.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/296/A012B67E-3F6F-E011-91C7-001D09F24FBA.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/296/AEEB4780-AF70-E011-8FDB-0030487C90EE.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/296/CE143293-386F-E011-8BE5-001617DBCF6A.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/296/D890F42A-806F-E011-8D3F-003048F11C5C.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/296/EE1E371C-856F-E011-97D1-003048D37514.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/296/F429345B-796F-E011-9649-0030487C5CFA.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/297/8285D686-3D71-E011-B5D2-001D09F252E9.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/297/9258AF93-9E6F-E011-99DC-001D09F253C0.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/297/A0C5A25F-7D6F-E011-9F86-0030487CD14E.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/300/48CB65BC-556F-E011-98B2-0019B9F705A3.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/300/56990665-7570-E011-9F8E-001D09F2432B.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/300/BC5A1DE5-766F-E011-A652-001D09F252DA.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/300/D0B2396D-526F-E011-825E-003048F117B4.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/300/D2CF08E1-776F-E011-AAFC-001D09F28EA3.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/300/DC086E60-7D6F-E011-AAF4-001D09F2AD7F.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/300/F2E079A3-4F6F-E011-84F3-003048D2BE12.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/301/D238D77C-8F70-E011-9396-001617C3B79A.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/332/0E2D9919-4270-E011-820D-0030487CD6DA.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/301/DE5B17E4-AF6F-E011-A684-000423D996C8.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/302/64B3D2E2-776F-E011-8B3D-001D09F2A690.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/332/4441BC88-E86F-E011-9A93-003048D2C16E.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/302/EA694C1C-7D70-E011-AB9A-0030487C2B86.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/308/E45A1740-D16F-E011-8878-003048D37514.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/332/22E59335-E76F-E011-9149-00304879EE3E.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/332/26217E80-C26F-E011-9522-0030487CD718.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/332/8E9761C0-1A70-E011-B103-001D09F241B9.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/332/5E457062-CE6F-E011-8CF2-0030486780B8.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/332/68B42028-6972-E011-9114-001D09F2441B.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/332/68D77C25-D66F-E011-9205-0030486733D8.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/332/86CAC434-F06F-E011-9F1D-003048F118DE.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/332/961334E4-BE6F-E011-8D65-0030486730C6.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/332/C45F932C-2970-E011-8A1D-0019B9F70468.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/332/DCC03041-3070-E011-AF78-001D09F244DE.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/332/F0DE99D6-2270-E011-9BB7-001617C3B76E.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/333/5CA38E26-D66F-E011-A122-0030486780B8.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/334/0A55DB56-FE6F-E011-9FD0-0030487C7E18.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/334/2E58A3CD-1A70-E011-90B2-0019B9F70468.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/334/3EC0545B-EB6F-E011-8041-0030487CD6E6.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/334/56E532D3-EE6F-E011-949C-001D09F24682.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/334/8C7B33EA-F570-E011-9F3B-001D09F2532F.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/337/682036C5-1A70-E011-88BE-001D09F292D1.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/334/A66BE37A-4C70-E011-B0F6-0030487C6090.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/334/C24F2944-F76F-E011-9051-001D09F23A3E.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/337/0895F178-2870-E011-AF5C-003048CFB40C.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/337/5EAB4F38-3070-E011-B4E1-003048F110BE.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/337/6EF6F8D3-1270-E011-8344-001617DBD472.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/339/5E40BD3B-7F70-E011-805B-001D09F26C5C.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/337/F0A480D1-C570-E011-AB6F-0030486780A8.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/338/10EB9194-3670-E011-844D-003048F024C2.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/338/8AFBE28D-C070-E011-837A-001D09F25109.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/339/4E94A105-3870-E011-B142-001617E30F48.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/358/6E9F4451-B970-E011-9324-001617C3B710.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/340/78E4E1BA-5E70-E011-89D3-0030487A195C.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/369/0C8F0EC4-9470-E011-94BA-000423D9890C.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/340/A2790B79-0B72-E011-879A-003048CFB40C.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/370/06BAD0DC-8372-E011-8584-001617DBCF6A.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/340/AAD17798-4970-E011-B4D9-00304879EDEA.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/340/F4550C38-4C70-E011-9230-001D09F29524.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/371/0A0E74D8-6E72-E011-B13F-000423D9A212.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/368/16AE3517-4270-E011-ACFF-003048F11DE2.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/369/62C3BF13-C870-E011-B2F4-003048F024C2.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/370/28EF4FFB-B370-E011-A189-0019B9F704D6.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/370/4E14AE73-B070-E011-9674-00304879FA4C.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/371/0C541996-7872-E011-90D8-003048F118D2.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/371/2669A708-B470-E011-B3E4-001617E30E28.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/371/3CEC9CCD-B070-E011-A55F-003048D2BB58.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/374/24E6B2DC-CC70-E011-97C9-001D09F2527B.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/371/AC2EC7CD-B070-E011-A60D-0030487CD6E6.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/372/48BFCBDB-8372-E011-B799-0030487CD7EA.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/374/8CB6B9F3-DA70-E011-8C40-0019B9F70468.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/372/FEFBAA1B-CD71-E011-9DE1-003048F1BF68.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/374/2004DA65-D070-E011-A48D-001D09F253C0.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/374/46E63F1F-DB70-E011-8CD8-0019B9F704D6.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/374/6AFC6DF5-7272-E011-A7DF-0030487C8CB8.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/375/288F2E18-F070-E011-BA8E-0030486733B4.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/374/8E3E3839-CE70-E011-B6A6-001D09F2924F.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/374/AEE07298-0371-E011-B129-003048F0258C.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/374/D62F508A-D571-E011-9FC6-003048F118C2.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/374/E00F9573-D270-E011-A2F1-001D09F2AD7F.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/376/4619B837-F970-E011-9B90-0030486730C6.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/376/86B252C9-6072-E011-87C4-001D09F2905B.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/377/22DE49DC-CC70-E011-BE00-001D09F2A690.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/378/50AB0623-0571-E011-A59F-001617E30F48.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/378/A03655C6-0A71-E011-9664-001D09F2841C.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/385/68901133-4771-E011-8D22-001D09F290BF.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/378/D4CCF8E2-0C71-E011-BFBC-0016177CA778.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/378/EA720257-4072-E011-9CC9-001617E30D40.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/378/F623BBC7-0A71-E011-9C0A-001D09F24FEC.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/385/6486BA76-3671-E011-97DF-001D09F2514F.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/385/68EE4FC6-3571-E011-8259-001D09F26C5C.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/385/B00041F6-3271-E011-82FA-003048F118AC.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/385/E8B628D7-3071-E011-B245-003048F118AC.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/387/28DDAC9C-3F71-E011-8D95-0030487C6A66.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/387/507783E7-5671-E011-B01F-0030487C6090.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/387/D8F996E1-3E71-E011-9D46-003048F1110E.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/402/28FEC30C-9271-E011-848F-003048F110BE.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/402/5C8CEA6F-8C71-E011-A532-001D09F292D1.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/402/2E6DFD60-8A71-E011-8390-003048F117B6.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/402/300D8E7C-8771-E011-B957-003048F117B4.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/164/232/AEAE3457-B179-E011-B69F-0030487C7E18.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/402/3A6FD695-8271-E011-9910-003048F1C832.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/402/5C28B80B-A571-E011-8F06-003048F1C420.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/402/702EF4FB-0372-E011-9880-001D09F2426D.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/475/1A8F4BC5-3C72-E011-8553-003048F118AC.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/402/7E80037D-8771-E011-AEB8-003048F024C2.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/402/8E5FAB9A-AF71-E011-BFB0-003048F118C6.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/402/C201C012-7F71-E011-A7A5-0019DB29C5FC.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/402/D8F5E107-8B71-E011-B208-001617C3B66C.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/475/56B13754-3B72-E011-AEA4-003048F11942.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/475/8C980DEC-6E72-E011-836F-001D09F26C5C.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/475/CC322D2D-3E72-E011-93A1-001D09F29146.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/475/E68E3E6C-3672-E011-B602-003048F024DE.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/476/82CAC8C5-5272-E011-98D7-001D09F24D67.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/479/E09846C0-6272-E011-96BE-003048D2C0F0.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/476/B6E58C98-3F72-E011-952C-001D09F2906A.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/476/D2AB742A-4372-E011-AC7B-0030487C8E00.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/480/263E0581-8472-E011-AF0B-003048F1BF66.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/476/E20BFABD-4172-E011-A2F3-001D09F251D1.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/480/8C48C6EE-8572-E011-AE65-001D09F23A34.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/478/861F0CFA-4F72-E011-8E0B-0030487CBD0A.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/479/E8DC59A9-6072-E011-8CA7-001D09F2906A.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/479/FA4D034B-7972-E011-A705-0030487CD14E.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/580/223D0233-B772-E011-AAB5-001D09F28F0C.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/480/42CD1F83-3473-E011-8C86-003048D2BB90.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/481/E4553289-9772-E011-9D76-003048F117B4.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/482/562DF29D-9772-E011-A00F-00304879EDEA.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/483/F4C287AC-9772-E011-A6EE-0030487D1BCC.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/581/322EA84F-B772-E011-B338-001D09F23C73.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/582/F8A82B30-0873-E011-8C0B-003048D2C092.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/583/40284094-B873-E011-96C9-001D09F24024.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/583/6E985F2A-FC72-E011-97BD-001D09F28EC1.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/583/7AE16C6B-FE72-E011-9E52-003048D2BE08.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/583/F2504051-FE72-E011-9A71-0030487A3DE0.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/584/5EFCEED7-0173-E011-A171-0030487CD704.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/584/9EAAD119-1273-E011-B70E-0030487A1FEC.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/588/10ED8C5B-2473-E011-ABC1-001617C3B69C.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/585/5A7A9381-E873-E011-B520-003048D2C174.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/586/1202ED9A-0973-E011-B031-0030487CD178.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/586/94CBF41D-1573-E011-9219-001D09F282F5.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/588/AEAB03DB-B174-E011-A080-001D09F2A690.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/587/2AE6484E-0873-E011-BEE4-0030487CD6F2.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/588/1CB19813-2C73-E011-9DE8-0030487C90EE.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/588/742C3F44-2273-E011-939B-0030487CD6F2.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/589/82AFBCA6-3D73-E011-B735-0019DB29C5FC.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/591/285690A0-5073-E011-843D-0030487A1884.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/588/788BCA7C-2D73-E011-AA7D-001617C3B5F4.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/588/CC4B9A2D-1B73-E011-AB51-00304879FC6C.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/588/FA7AEBAD-1E73-E011-BBD5-0030487A1FEC.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/589/80F5B252-3E73-E011-BAE9-0019DB29C614.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/592/3C855D46-4A73-E011-B4C8-000423D996C8.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/592/46A50A61-5873-E011-8D87-003048F117EC.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/593/4A708D6E-5873-E011-93A6-001D09F24DDF.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/596/B0544D61-5B73-E011-9A3F-001D09F2960F.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/657/90439DB5-B573-E011-92D2-001D09F28EC1.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/657/C6184BAF-C673-E011-BAF8-0030486780B4.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/630/1C709739-9D73-E011-8CFD-0030487CD184.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/630/B641ADB2-9373-E011-B5DA-001D09F241F0.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/655/681D9C17-BC73-E011-B2D1-001D09F2B30B.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/659/86D0F965-DA73-E011-9061-003048D2BC30.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/657/8A17EE93-B373-E011-AD79-001D09F253C0.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/658/DE19B9DA-7D73-E011-A69E-0030487CF41E.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/659/0C6C50ED-F873-E011-A9F4-003048F0258C.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/659/6EC329D4-0B74-E011-9B7B-001D09F25456.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/659/8C0E87CA-DB73-E011-AEBA-0030487C8CBE.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/659/B27F8415-D473-E011-8D2D-0030487C5CE2.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/659/9A3E58CA-DB73-E011-BA03-0030487A3DE0.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/659/9A610E1E-FA73-E011-AE5A-001D09F2924F.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/659/EC545744-1275-E011-8E52-001617E30F58.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/659/9AE1C786-D573-E011-9515-003048D2BB58.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/659/A4010788-E873-E011-ACF4-003048D2BCA2.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/659/B6D26F26-D673-E011-B0F7-001D09F241B9.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/659/E296B70D-0274-E011-BDE4-003048F0258C.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/660/50D1DBAC-0E74-E011-BB0E-0030486733B4.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/661/1CB8F9B8-0E74-E011-BAFE-003048F024DC.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/662/7EDD64CE-0674-E011-9B13-001D09F2462D.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/662/B89C1BCE-0674-E011-8125-001D09F24EAC.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/662/D6354F58-6875-E011-B8C5-003048F118D2.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/663/AC1F2B17-1E74-E011-969D-001D09F2B30B.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/663/D6681A4F-DD74-E011-97F5-001617C3B6FE.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/663/DE15B71C-1E74-E011-B24B-001D09F29538.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/664/28033067-3274-E011-91BB-003048F024F6.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/664/3674FF76-2474-E011-9404-000423D33970.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/664/7AA2B936-3374-E011-A73F-0030487CBD0A.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/665/38DC66FA-2974-E011-94CD-003048F01E88.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/665/E2ECE13B-2075-E011-BB87-003048F1183E.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/668/2C898DD8-3374-E011-BA83-001617E30D40.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/668/706C15D9-3374-E011-BA44-001617E30F58.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/668/CC34FFE8-8275-E011-800B-001617E30CC2.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/737/3C2EC0D8-7D74-E011-A7FC-000423D9A2AE.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/738/60BF066B-D174-E011-9631-001D09F25109.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/738/125035E7-CF74-E011-9875-001D09F276CF.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/738/200D116A-D374-E011-8BB6-001D09F2905B.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/738/48C2B9D3-D474-E011-9024-003048F024C2.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/738/543F2A6F-D174-E011-8104-001D09F250AF.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/738/CC20AB01-0075-E011-8A92-003048D3750A.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/751/D205A91D-BF74-E011-9298-001D09F26509.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/753/C80E488A-E174-E011-8E54-003048F024F6.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/754/C41C723E-E574-E011-B05A-0030487CAF5E.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/757/FCA13739-B775-E011-96F0-0030487CD6B4.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/758/003E7DA2-4575-E011-B383-001D09F250AF.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/758/94C13A5A-5E75-E011-9E9B-003048D2BC30.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/758/B6FF9BFA-4B76-E011-9962-0030487A3C92.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/758/1C3B8264-2975-E011-987F-001D09F24600.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/758/1E31FE9C-4575-E011-8D94-0019B9F709A4.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/758/48173979-3C75-E011-BD9C-00304879BAB2.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/758/82610A9D-4575-E011-8E80-001D09F291D2.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/758/B8FBB6A5-4C75-E011-A523-003048F1C420.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/758/C08284E5-5075-E011-9B91-003048F118C6.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/759/A44C72D1-5A75-E011-9EF1-001D09F232B9.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/164/234/824B492E-B479-E011-9317-001D09F2841C.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/759/3C9BE963-6075-E011-8742-0030487CD906.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/759/66E1C296-4875-E011-8C5B-0030487CD6D2.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/759/8EF769D8-8075-E011-84E3-0030487A17B8.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/760/06D45DD8-7475-E011-8E32-0030487CD6D8.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/759/9CD7F8E0-5575-E011-9CBE-003048F118E0.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/759/D2B070AC-5875-E011-B42B-001D09F253C0.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/759/D4B5821B-8075-E011-B9B9-0030487A1884.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/759/F8BCC3FF-6F76-E011-BB76-003048F118E0.root' ] );
readFiles.extend( [

       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/760/72994A36-7675-E011-AEE0-0019DB29C5FC.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/760/A6B82ED8-7475-E011-BD6F-003048F117EA.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/760/C63E84A7-7775-E011-A277-0030487C8E00.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/763/F6481D48-9575-E011-9355-001D09F2545B.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/760/F6D09524-9A75-E011-B214-003048F11C5C.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/761/1C099F21-9F75-E011-A71D-00304879BAB2.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/761/BCDD9603-7E75-E011-BC2E-001D09F25438.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/761/CCD1B74D-7D75-E011-B73F-003048F11CF0.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/765/60A92346-A375-E011-B3A2-003048F118D2.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/765/94999F7A-8D75-E011-8772-0030487CD812.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/765/C237DB21-9375-E011-BB13-003048F1182E.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/164/235/A6D74303-B779-E011-A872-001617C3B706.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/765/E2989423-9375-E011-801E-0030487CD6B4.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/793/484FAF2C-B775-E011-9AF9-003048F118C6.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/795/CE946B5A-0B76-E011-BCDF-001D09F251B8.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/796/182D942D-FB75-E011-B808-0030487CAF5E.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/817/18C09943-C976-E011-9DCB-003048F024DC.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/796/30D6CC0C-1876-E011-AFF1-003048F117EA.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/796/B03E4F3F-FD75-E011-9508-003048F117B6.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/796/F8BE4C2B-FB75-E011-B9F2-0030487CD76A.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/817/1041ADAE-A476-E011-AF28-001617E30F50.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/817/2414785A-C476-E011-BF9C-003048F11C28.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/817/2A4E252A-8076-E011-BC9F-003048F11C58.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/817/440B3D07-BE76-E011-977D-001617E30F48.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/817/74F0197C-7A76-E011-85C3-001D09F24493.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/817/4475BFC6-8576-E011-B633-001D09F25456.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/817/666AE2A7-B076-E011-8988-0030487CD6DA.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/817/66B39923-8076-E011-AA97-003048F0258C.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/817/721135CC-CC76-E011-9F67-003048F024E0.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/817/8457B10D-B276-E011-829A-001617E30F50.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/817/8AA899B8-9F76-E011-81BB-000423D98B6C.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/817/90DC0DFC-D076-E011-BA52-000423D98950.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/817/94CD3F42-7D76-E011-A79B-003048F1182E.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/817/981B72BF-B276-E011-8968-0019DB29C5FC.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/817/AAB8FACB-4077-E011-BC90-003048F118DE.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/817/C826B4A9-C376-E011-8A4C-0030487CD6DA.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/817/D0A9913D-9076-E011-9E6D-003048D375AA.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/817/D2500CAA-C376-E011-9DC8-0030487CD77E.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/817/DEEACA37-9076-E011-9CF5-003048F01E88.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/817/E24ECF21-8076-E011-A20D-003048F024DC.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/817/EA004C0B-7976-E011-9C39-001D09F23174.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/869/B2DA9C9E-D377-E011-B417-000423D9890C.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/164/224/7C0EF2C3-A479-E011-BE06-003048CFB40C.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/243/3A97A3DB-876D-E011-BB22-0030487C6090.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/238/880F8699-C46F-E011-9B81-001D09F27067.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/237/6A9F3BAD-CC6D-E011-8923-003048F1183E.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/235/B6ADB834-536F-E011-9F71-003048D3750A.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/235/A8D07BDA-C26D-E011-B91A-0016177CA778.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/235/A012068B-BC6D-E011-80C8-0030487CD6D8.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/235/52867BF1-C46D-E011-8484-003048F118C4.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/234/0C557339-B66D-E011-982C-003048F01E88.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/233/FCFED3ED-B16D-E011-9A8F-0030487CD7B4.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/233/463A8B58-366F-E011-B2DF-001617E30D0A.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/232/10471B66-CD6D-E011-B2EE-001D09F23D1D.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/078/DACB6EC7-706C-E011-8F62-0030487A1990.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/076/0C41BB84-016C-E011-A356-003048D375AA.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/072/945996D3-726C-E011-B3D3-0030487CD6DA.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/071/98A4B2EC-616C-E011-9BCE-003048F1110E.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/070/44A065F1-2D6E-E011-B0F0-003048F024F6.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/069/94CA4099-C36C-E011-BB1D-003048F1BF68.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/069/7607C219-586C-E011-877B-00304879FA4C.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/069/72D08A86-676C-E011-842C-003048F1C836.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/069/50AAD6D8-666C-E011-AB0E-003048F1C58C.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/069/4EB2C0D6-5F6C-E011-9F38-003048F117EA.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/069/380119BE-646C-E011-AF6C-003048F117B4.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/046/9EE452CE-586C-E011-BCEB-003048F1BF66.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/046/4A478410-186C-E011-A47B-0030487A3DE0.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/046/46624F06-1D6C-E011-893F-001617C3B65A.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/163/045/C69394E8-A86B-E011-9994-001D09F290BF.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/929/C8792AB6-E06A-E011-9DC0-003048F024DE.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/929/C4A8CF29-8C6C-E011-8295-0019B9F704D6.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/929/06EB4C06-E76A-E011-9605-003048F118DE.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/926/EA35254D-DF6A-E011-A7BA-003048F024FE.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/926/BE039E69-BF6C-E011-BD41-003048F024F6.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/926/B6E613BF-646C-E011-BFDC-003048F117EA.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/926/6A65C600-E06A-E011-B0EB-003048F1BF66.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/926/587E03B7-E06A-E011-9835-0030487C7828.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/926/486829B7-E06A-E011-92E8-0030487CD840.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/926/08197C36-E46A-E011-BFAA-003048F110BE.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/925/B4E78AAE-A46C-E011-A103-003048F0258C.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/925/9EC90F8D-126B-E011-8229-000423D9A212.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/925/142F9D62-C06A-E011-ABF0-003048673374.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/925/000F2D6F-526B-E011-82DF-000423D9890C.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/924/065DAD5C-F36C-E011-BC6E-0030487C60AE.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/917/9CE66E9F-276A-E011-A4DF-0030487C635A.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/909/E649C290-716A-E011-8739-001D09F29169.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/909/98AE0819-DA6C-E011-9F2C-00304879EDEA.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/909/0C6CC48F-696A-E011-8FA9-001D09F24EE3.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/902/96B8DB95-CB69-E011-9F30-001D09F29597.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/881/58EC6D63-AD69-E011-BB9F-003048D37456.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/828/E474F1A6-E569-E011-B9FF-001617C3B6FE.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/827/C236491C-F169-E011-91A9-0030487A195C.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/826/08E9E354-DF69-E011-8515-0030487C7E18.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/825/BAA93E3C-F869-E011-8B0E-0019B9F72BFF.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/824/5673EC44-5A69-E011-AF4D-001D09F292D1.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/823/BA49E774-5E69-E011-B61B-003048F117EC.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/822/FE305D1D-DD69-E011-8841-003048F11CF0.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/822/3E6FDE83-D56A-E011-9F59-001D09F27067.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/811/B27778E7-C569-E011-B426-001D09F29169.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/811/5E7D0406-8869-E011-ACBF-0030487CD6D8.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/810/3C66A196-7A69-E011-AEB2-003048F11942.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/808/E4A9742D-9D69-E011-B59A-003048F118DE.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/803/C4847F56-9A69-E011-A414-001617C3B65A.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/801/1C7AB4F2-FE68-E011-9C8E-003048F024C2.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/765/F0CA4834-4569-E011-9969-001D09F2423B.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/762/74DEA351-4E69-E011-9D71-0030487CAF5E.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/760/884B0671-2369-E011-8382-001617E30D12.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/742/B088AB2C-2B69-E011-945C-001D09F2A49C.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/739/2ABF0464-1C69-E011-9F9A-0030487C7828.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/733/14942DE3-3769-E011-AD14-0030487CD6D2.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v2/000/162/718/7AC00302-3869-E011-B165-001D09F23944.root' ] );


secFiles.extend( [
               ] )

