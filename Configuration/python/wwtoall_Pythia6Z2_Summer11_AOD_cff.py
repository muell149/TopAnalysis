import FWCore.ParameterSet.Config as cms

################################################################################
# Dataset: /WW_TuneZ2_7TeV_pythia6_tauola/Summer11-PU_S4_START42_V11-v1/AODSIM #
# Events : 4225916                                                             #
# xSec   : 43 (NLO MCFM)                                                       #
# eff    : 1.0                                                                 #
################################################################################

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource", fileNames = cms.untracked.vstring( *(
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/FE59C620-4B9D-E011-B826-002618943882.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/FCE2E826-649D-E011-BDF7-001BFCDBD15E.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/FAD1071C-639D-E011-98C6-003048D3FC94.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/F838EA4B-5F9D-E011-B013-003048678AFA.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/F6D77A2B-989D-E011-A000-001A92971ACC.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/F68C36D7-629D-E011-AD5D-001A92810AA8.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/F632CD31-6C9D-E011-813E-003048D3FC94.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/F4DBC3AF-A09D-E011-9FA5-0018F3D0961E.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/F4A1E270-789D-E011-B0E6-002618943849.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/F47574FF-609D-E011-AEFA-00261894389E.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/F2A93A60-589D-E011-91CB-0026189438FC.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/F2424B6B-769D-E011-BAC2-00304867920C.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/F23E9AF0-5F9D-E011-820F-001A928116DA.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/F224A55F-5A9D-E011-87A1-002618943920.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/F0BC51B1-989D-E011-A5F8-0018F3D096AE.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/F0AB0AD3-749D-E011-A4F9-001A92971B96.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/F0532D08-7F9D-E011-B2FE-001BFCDBD160.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/EE9DE56B-849D-E011-89F2-003048678F78.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/EE506F34-8E9D-E011-99FC-001A92810AE2.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/EC7F1336-849D-E011-90DF-0018F3D095FA.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/EC327EC0-A99D-E011-A7EB-001A92971B8E.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/EADA0B5F-5A9D-E011-BEB2-00261894394F.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/E8F07E8F-899D-E011-B69D-0018F3D09706.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/E6F51987-5D9D-E011-ADB2-00248C0BE014.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/E6AFDF9B-699D-E011-BBB8-001A92810ACA.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/E67AD8CC-8D9D-E011-A9B0-0018F3D0960E.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/E636925F-8A9D-E011-924E-00261894390C.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/E4C75E11-699D-E011-9F38-001A92971B5E.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/E41B180D-9C9D-E011-858D-0026189437FA.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/E2F5AB8A-629D-E011-9104-001A928116C0.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/E2C1A2DE-9B9D-E011-88A8-003048679296.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/E0E55B86-5F9D-E011-BD3E-00261894395C.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/DE5A56DB-979D-E011-B38C-001A928116F2.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/DE0CB799-4E9D-E011-929F-00261894395B.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/DC4CC0A8-7F9D-E011-8096-001A92971B04.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/DC4AC5C9-749D-E011-93CB-001A9281172E.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/DAE08CDD-A59D-E011-92E9-001A928116CE.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/DA04B9D3-879D-E011-A92B-001BFCDBD15E.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/D8626DDA-939D-E011-AC39-0018F3D096AE.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/D842577C-649D-E011-8476-0018F3D09710.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/D66C2FD6-699D-E011-B30B-002354EF3BD2.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/D4372FC3-9F9D-E011-B374-002618943856.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/D2AE183C-789D-E011-B85D-001BFCDBD11E.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/D2A7111A-8A9D-E011-BECC-001A92971B9A.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/CE1F2DEC-879D-E011-A94F-0018F3D09700.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/CE1C6D96-919D-E011-BC5D-001BFCDBD15E.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/CC90A7E3-799D-E011-A2A1-003048678FE0.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/CC874E72-5C9D-E011-99C2-001A92971B38.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/CC358C0F-4C9D-E011-9016-001A92971B9A.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/CAC481E6-A69D-E011-B969-001A92971BB8.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/CABE2786-9E9D-E011-A583-001A92810AD0.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/C8B79999-549D-E011-997F-002354EF3BD0.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/C4FC54D8-7D9D-E011-B5AD-001A92971BD6.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/C4C95841-7B9D-E011-B4A4-003048D3FC94.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/C48E1F92-7B9D-E011-BE94-002618943896.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/C456081D-5E9D-E011-8E67-003048679030.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/C42BA2D1-629D-E011-AC13-001BFCDBD15E.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/C2786E3E-619D-E011-A93B-0026189437E8.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/C0F57973-829D-E011-9D86-001A92971B06.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/BE9132F6-5C9D-E011-AC65-002618943915.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/BE617734-729E-E011-AD10-001A928116DA.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/BCCA4AA7-759D-E011-B864-001A928116FE.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/BC449132-579D-E011-B002-001A92971B7C.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/BAC35D47-A89D-E011-A62C-002618943856.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/BA7E7449-7F9D-E011-998A-001A92971B94.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/BA6431DE-6F9D-E011-948E-0018F3D096DC.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/BA037DAB-8A9D-E011-BAC0-0018F3D09706.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/B6397F41-6B9D-E011-A5E7-002354EF3BDA.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/B4EFBD28-8C9D-E011-AE81-001BFCDBD182.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/B49A739A-879D-E011-BE6A-001A928116F4.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/B48198F9-6C9D-E011-9066-0026189438A9.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/B009E5D3-5D9D-E011-99B4-003048678BE6.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/AE9A5148-6B9D-E011-853C-001A928116C0.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/AE4143EA-7B9D-E011-B8A2-001BFCDBD11E.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/AC6DAED9-B09D-E011-B87F-001A9281170A.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/AAF0C2C6-A19D-E011-B8AB-001A92971B68.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/A8C5ED0B-969D-E011-9590-00261894380B.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/A63C39BF-729D-E011-94D9-0018F3D0970C.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/A2A43F3F-4C9D-E011-AC52-001A92810ACA.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/A250F91E-709D-E011-B6DC-002354EF3BDA.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/A0F9A98A-6B9D-E011-9EEC-002618943843.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/A07C3447-6F9D-E011-8ED9-001A92810ACA.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/9E283E31-869D-E011-84CD-001A92971B68.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/9A8D119B-6F9D-E011-856F-001A92971B20.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/9A542652-AF9D-E011-83F2-00304867BFAE.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/9A013B4A-649D-E011-881F-001A92971AA4.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/98A8A3D2-919D-E011-8FE9-001A928116FE.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/94DBADFA-6C9D-E011-8CF8-003048D42D92.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/94CFC036-7A9D-E011-96FC-0018F3D09624.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/8E89A764-3E9D-E011-A517-001A928116CE.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/8E880479-6E9D-E011-968A-003048679084.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/8E16E6B5-9E9D-E011-BFCB-001A92971B68.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/8CE2E163-8F9D-E011-AB3C-001A92971B36.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/8C35A729-669D-E011-A36C-0018F3D095EA.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/8AB95ACA-8F9D-E011-AB12-001A92810AD2.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/8A4CACFC-829D-E011-A9F4-0018F3D09706.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/889C710D-469D-E011-B887-001A92810ADE.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/882554FF-749D-E011-88FE-0018F3D096DC.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/86F6033F-619D-E011-B31C-003048678B0C.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/84756137-669D-E011-A590-0018F3D096DA.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/841C6909-819D-E011-BA66-001A928116BC.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/82B39162-6A9D-E011-B748-003048679188.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/82AFFDB9-829D-E011-97D0-0018F3D096E4.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/809A78F8-6C9D-E011-9B62-002354EF3BD2.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/7E230E90-9F9D-E011-B013-001A92971B48.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/7CA57F48-6D9E-E011-A0F2-001A92971B62.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/7C718594-5F9D-E011-9636-0018F3D09710.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/7C623CA7-B89D-E011-A802-0018F3D09678.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/7C4EF1B0-5E9D-E011-AF02-003048678B0C.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/7C3C8469-619D-E011-84A6-001A92971AA4.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/7AA7837C-869D-E011-8431-001A92811714.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/7A5DD7BA-4D9D-E011-A762-001A92971BDC.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/78BCE0E1-5B9D-E011-B8FE-0030486792AC.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/781BCBAD-7D9D-E011-AF1E-001A92811732.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/76457BE0-A49D-E011-9401-003048679296.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/761E9142-6D9D-E011-9ADD-002618943975.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/7486C81E-9E9D-E011-944B-0018F3D09612.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/72D827A9-8C9D-E011-96E8-003048678F92.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/72838CF0-589D-E011-8825-002618943983.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/7053D293-799D-E011-9922-003048679182.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/7046D6AC-419D-E011-9179-00304867900C.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/6E8ECFAD-609D-E011-A528-001A92971B8A.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/6C9BF6B1-849D-E011-BAA7-00304867915A.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/6C07B827-789D-E011-828F-003048679182.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/6A7DC463-669D-E011-BA18-0026189438A7.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/6A65BF24-909D-E011-A072-0018F3D096E0.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/666FF6E0-699D-E011-991A-001A92971B3C.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/64DAE9AC-7D9D-E011-B157-001A92971B04.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/64CBB673-8A9D-E011-B040-001A9281170C.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/607FFA7E-CC9D-E011-8136-003048679228.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/60030F7F-939D-E011-B6BC-002618FDA210.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/5E904B90-6F9D-E011-8D16-003048679182.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/5E4354D9-4C9D-E011-82F0-0030486790B0.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/5E281130-869D-E011-A588-0018F3D096AE.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/5AD8F851-719D-E011-AC98-0018F3D096D8.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/5AD34B43-509D-E011-AC5A-001A92811732.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/5AAD4796-779D-E011-AB4B-001A92971B3C.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/5A9CDD5F-929D-E011-BDFC-001BFCDBD15E.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/5A0D660D-7D9D-E011-81CB-001A92971B9A.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/5846DD8F-4C9D-E011-ADA0-0026189438C1.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/560D396B-7D9D-E011-96B1-003048D3FC94.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/54800600-739D-E011-9230-00261894397D.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/52994C4A-719D-E011-BEF1-001A92971B96.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/4CDD8D67-A29D-E011-B61E-0018F3D0970A.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/4C330E58-8B9D-E011-923B-0018F3D096E4.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/4AAB56F3-6D9D-E011-AA1E-0018F3D096BA.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/4677B21B-5E9D-E011-A6E2-00261894383F.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/4260C782-439D-E011-8874-001A92810A98.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/40DD9C6D-809D-E011-B1B5-001A92810AA6.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/406BCA5D-7F9D-E011-B197-0018F3D09612.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/401EA4C0-949D-E011-9373-001A92971B36.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/4004B064-909D-E011-87B6-0018F3D096AE.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/3EAFD9F4-5A9D-E011-8B82-002354EF3BE4.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/3CC4FCF8-5C9D-E011-A351-001A92971BDC.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/3CABE83F-7A9D-E011-9203-001A928116D6.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/3CAA1ABD-769D-E011-8062-001BFCDBD11E.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/3C540515-A39D-E011-8FB5-0018F3D096BA.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/3C51D0D3-5D9D-E011-B66B-00261894394A.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/3C2CD2F4-649D-E011-AD2B-002618943916.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/3A7B2F33-689D-E011-9C03-0018F3D09642.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/38ED8581-4E9D-E011-A43A-001A92810AE0.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/3864DE21-7E9E-E011-8275-0030486792A8.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/369CB37C-559D-E011-8A57-002618943800.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/36650E05-4A9D-E011-84D4-003048678B36.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/349A2AAD-669D-E011-B667-002618943900.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/32B9C41C-819D-E011-9D9D-001A92811730.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/30905763-8C9D-E011-9144-001A92971B9A.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/3034C02B-769D-E011-89A2-0018F3D0968C.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/2EBF567D-649D-E011-91A3-0018F3D09708.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/2E34A0CE-679E-E011-B4B2-002618943986.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/2E085986-AB9D-E011-A439-001A92971B16.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/2CC32DCD-8B9D-E011-BD84-0026189438C1.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/2CA33F81-7C9D-E011-B3A3-0018F3D096D8.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/2C2070CF-539D-E011-B2F6-0018F3D09678.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/2A85F6C0-969D-E011-A667-0018F3D09706.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/28FDD1E6-569D-E011-B4D8-002618943945.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/2852F042-739D-E011-BFC9-002354EF3BD2.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/262C008F-719D-E011-8C13-001A92971B5E.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/249EBDC1-529D-E011-8D45-001A92971BCA.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/2206E9CA-629D-E011-BFB2-001A92971ACE.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/20A3EF66-5C9D-E011-A12F-001A92971B8A.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/20531C58-899D-E011-A1E7-001A92811726.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/1E6FB428-5C9D-E011-990C-0018F3D096AA.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/1CCD74B7-7E9D-E011-A1B6-0018F3D095FA.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/1CC68127-689D-E011-B081-0018F3D096BA.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/1C34CA97-639E-E011-8B44-00304867BF18.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/1C2D63E4-679D-E011-B3F8-003048D3FC94.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/1AB469A4-589D-E011-A3A1-002618943843.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/18FE77CB-999D-E011-8014-001A9281173E.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/18791467-5F9D-E011-8DA3-0018F3D09708.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/1676BC83-599D-E011-94AF-002618943896.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/1651ABE0-739D-E011-8C6C-0026189438AA.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/14BCAC6A-849D-E011-8545-001A92810AB8.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/149CA461-569D-E011-9804-002618943939.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/1479DAFC-709D-E011-AA45-001A92811728.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/1413F74D-559D-E011-9D18-001A92971B7C.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/1264E045-6B9D-E011-9FB2-0018F3D09708.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/1229F2CD-579D-E011-BE70-001A92811728.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/0EFC1083-C89D-E011-B39B-002618943856.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/0CADB7F6-6D9D-E011-96BD-003048D3FC94.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/0C747AA1-9C9E-E011-A11E-001A92811706.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/0C4568BE-AD9D-E011-8C27-001A92971B16.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/0AE58048-959D-E011-BBCF-001A928116DC.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/0AD678EB-779D-E011-A5D0-0018F3D09608.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/06E1E4EC-7B9D-E011-B292-0018F3D096DA.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/0673C834-5A9D-E011-9682-001A928116C0.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/0635F301-739D-E011-BCEA-00304867BFB2.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/060110D1-659D-E011-97A7-002354EF3BE6.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/04DB0E69-889D-E011-A1BC-0030486792B4.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/04959BB9-829D-E011-B485-001BFCDBD182.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/04371B01-519D-E011-AB82-001A92971B72.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/020C45C1-9D9D-E011-A8AE-002618943978.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/020B8D35-519D-E011-9E28-001A92971B80.root',
'/store/mc/Summer11/WW_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/008E825F-9C9D-E011-BE4C-0018F3D096EC.root'
    ) )
)
