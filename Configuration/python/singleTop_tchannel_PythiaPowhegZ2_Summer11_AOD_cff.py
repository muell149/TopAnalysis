import FWCore.ParameterSet.Config as cms

########################################################################################
# Dataset: /T_TuneZ2_t-channel_7TeV-powheg-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM # 
# Events : 3900171                                                                     #
# xSec   : 42.6  (NLO MCFM)                                                            #
# eff    : 1.0                                                                         #
########################################################################################

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource", fileNames = cms.untracked.vstring( *(
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FEB7D5EB-40AB-E011-81FC-0026189438D2.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FE7A074D-22AB-E011-B528-0018F3D096B6.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FE4EF257-A3AB-E011-9698-00304867915A.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FCDA2218-1FAB-E011-8270-0026189437F9.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FC8556CC-86AB-E011-BB00-00248C0BE018.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/F6F0E413-1FAB-E011-97E2-003048678F6C.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/F63FCCC0-1DAB-E011-81EB-0026189438FC.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/F43F20BA-1DAB-E011-92C8-00304867920A.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/F264D284-1EAB-E011-9168-003048679084.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/F0374000-23AB-E011-A221-001BFCDBD1BC.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/EC3E0DC2-1DAB-E011-B76C-003048678E8A.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/EAFFAEED-22AB-E011-9CC7-003048B95B30.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E8F5DF8C-22AB-E011-815B-003048678A76.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E819D876-3FAB-E011-89A0-001A92971BB8.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E635DA77-22AB-E011-9DCC-0018F3D09608.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E471B9C7-22AB-E011-9F84-0030486790A6.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E464A514-1FAB-E011-A77B-002618943961.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E411477C-22AB-E011-9C0C-002618943833.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E0BFD1AA-87AB-E011-A9B0-001A928116DA.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E0797ECB-14AB-E011-A3DD-002618943944.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E0708CD5-14AB-E011-B361-003048678FA0.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E01E367F-22AB-E011-A81C-001A928116D8.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/DC833F10-40AB-E011-A5A1-00261894387C.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/DAD72BA2-42AB-E011-8C91-00261894397E.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/DA411470-22AB-E011-B636-002354EF3BDD.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/DA3B5E80-1EAB-E011-A076-001A92971BB8.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/D8CDEC55-7AAB-E011-9B78-0026189438F6.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/D69895BE-1DAB-E011-81C1-0026189438BC.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/D6021878-22AB-E011-811C-001A928116CE.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/D46283B3-1DAB-E011-ADF6-003048678A88.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/D291177B-3FAB-E011-8562-003048D42D92.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/D04EF745-1BAB-E011-8124-003048678FA0.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/CEFF234A-22AB-E011-9665-00248C55CC4D.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/CECDCCC7-14AB-E011-B0B4-0026189438A0.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/CE618818-1FAB-E011-A1F9-00304867920A.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/CAF77FEF-40AB-E011-86DA-0026189438C4.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/CAD81AD3-22AB-E011-BE93-003048678C06.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/CA1F2DB6-1DAB-E011-9153-0018F3D096EC.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C8539381-82AB-E011-BBDE-002618943946.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C6FA7946-19AB-E011-BB3C-0026189438D9.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C675B8F1-13AB-E011-B1BB-002618FDA216.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C46D6FE2-1BAB-E011-9340-003048678FAE.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C2EE9AD5-14AB-E011-8EA7-003048D15DCA.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C24EACB0-1DAB-E011-96D4-0026189438C1.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C21FEED6-1BAB-E011-81A7-003048678B70.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C024ED46-22AB-E011-B6CB-00304867BEDE.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/BC629F18-14AB-E011-9290-002618943918.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/BC064ACA-22AB-E011-A20A-0026189438C1.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B8366E61-22AB-E011-8277-0026189438E1.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B81A6681-3FAB-E011-912C-001BFCDBD130.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B6A36B7C-3FAB-E011-B998-002618943886.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B6298576-1EAB-E011-B245-002618943954.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B4E454DC-1BAB-E011-B081-003048678F06.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B4854B29-23AB-E011-98C8-003048678D6C.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B44BAF7C-1EAB-E011-BDD7-003048679030.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B42D847F-1EAB-E011-BC68-0030486790B0.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B4181FF0-13AB-E011-AE2C-00248C55CC3C.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B2A6BAEB-40AB-E011-86D4-003048678B3C.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B294CB05-14AB-E011-8649-002618943944.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/AEC3AC4C-1BAB-E011-BF03-002618943901.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/AEB80B6A-27AB-E011-8E3F-001A92810AE6.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/AE1A6C7F-22AB-E011-85F9-00261894380D.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/ACEDECA9-87AB-E011-BEF2-00304867902E.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/A647407B-1EAB-E011-9717-003048679080.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/A6047911-1FAB-E011-91E9-00304867BEE4.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/A29E484B-1BAB-E011-B78B-002618943976.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/A0702E59-3EAB-E011-ADE7-001A928116D6.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/A045E29C-12AB-E011-B6AC-00304867902E.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/A03B5E46-88AB-E011-A2DC-003048679046.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/A01B016B-27AB-E011-9B01-0018F3D09614.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/9EBD77CC-22AB-E011-8FCB-0018F3D095F6.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/9CD64CF4-13AB-E011-BA76-00304867BFA8.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/9C190D75-3FAB-E011-95C5-002618FDA248.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/9C087981-1EAB-E011-B61B-003048D15D04.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/9AFDEB43-19AB-E011-A642-002618943940.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/9AE23DCC-22AB-E011-A0ED-002618943905.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/98E43B83-22AB-E011-8441-0026189438E4.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/98CE0610-40AB-E011-BA51-002618943896.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/98642A78-1EAB-E011-96BE-001A92971B3C.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/98032042-88AB-E011-9EFE-003048678A80.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/96407D65-40AB-E011-96C0-001A92971B06.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/961A9859-3EAB-E011-BC57-002618943833.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/90DEDB0E-14AB-E011-861C-003048678E8A.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/9034A0FE-13AB-E011-9063-00248C55CC62.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/8EC13A7E-1EAB-E011-8CE2-003048D42D92.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/8AD26846-1BAB-E011-B52F-00304867BED8.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/8AD0E0C3-1DAB-E011-AD35-003048678FAE.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/8A463C75-22AB-E011-80F2-003048678A7E.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/8A0CFC77-80AB-E011-B888-001A92971B84.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/88FA5864-87AB-E011-932B-003048678FB4.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/8827C37D-22AB-E011-A4E8-002618FDA279.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/840AFB1E-1AAB-E011-8553-002618943948.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/82A7F9BC-14AB-E011-94D4-00248C55CC62.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/82A26CB3-41AB-E011-BF25-001A92971B8E.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/8221EF76-22AB-E011-8756-002618943962.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/8027B749-88AB-E011-9404-00261894382A.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/7A382C95-26AB-E011-8A38-001A92810AF2.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/787209BB-1DAB-E011-85E7-0030486790C0.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/786D0579-22AB-E011-81C0-003048678BB8.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/783E65AB-87AB-E011-BA46-00261894396E.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/74C0D84E-1BAB-E011-ACE1-003048679010.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/748C297B-22AB-E011-BA29-003048D15DDA.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/748887A7-87AB-E011-879E-002618FDA237.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/72C6F68A-12AB-E011-933D-0026189438F9.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/6E141B1F-1AAB-E011-8EAF-003048679162.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/6A83E6B2-1DAB-E011-9700-0026189438BF.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/6A7783B3-1DAB-E011-878A-002618FDA248.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/6A748ABE-1DAB-E011-9736-0026189438DA.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/6A2CB43C-22AB-E011-861C-0026189437E8.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/6A039786-41AB-E011-B241-001A928116CC.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/682C950D-40AB-E011-AEF8-003048678B3C.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/6808235A-3EAB-E011-91CD-0026189438F5.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/66B7677A-22AB-E011-B914-002618FDA26D.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/667D427A-40AB-E011-B3DE-002618943924.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/64C973F9-40AB-E011-B641-003048678FC6.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/62165866-40AB-E011-AE28-002618943924.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/620B9CF5-22AB-E011-B500-001A92810A9A.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/62009D69-22AB-E011-8B91-0026189438A9.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/6091AC63-7FAB-E011-9943-003048D42D92.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/605361A5-26AB-E011-ADCA-002354EF3BDD.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/6043E1AB-87AB-E011-80EF-0026189438E6.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/5AA1A97C-1EAB-E011-8D80-002618943940.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/5A700C58-1BAB-E011-A317-003048678D9A.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/58803082-41AB-E011-A0FD-002618943826.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/56C8617E-1EAB-E011-80A5-003048678BF4.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/56C627E8-40AB-E011-AA6E-00261894383E.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/549D55CC-22AB-E011-A93E-00261894393F.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/54351BD8-22AB-E011-A1E3-003048679048.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/52762AB7-1DAB-E011-B1EE-003048678B70.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/5249CECC-22AB-E011-A3B0-0018F34D0D62.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/50BED083-1EAB-E011-B09B-00304867BFA8.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/50A31B1A-8AAB-E011-835B-0026189438F5.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/50289862-22AB-E011-A188-0030486792B4.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/5020C244-1EAB-E011-9915-0030486790B8.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/5014EA45-88AB-E011-B749-00248C55CC62.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/4E03C583-41AB-E011-B8E2-0026189437F2.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/4C500364-87AB-E011-BD94-00304867BF18.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/4C30E444-22AB-E011-BDDB-003048678F02.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/4C04674A-1BAB-E011-BC55-002618943879.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/4ACB0978-3FAB-E011-A6C9-003048678FA0.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/4A86EB01-14AB-E011-9E62-00304867BFB2.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/4A3B6A88-22AB-E011-98F1-0026189438F3.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/48FA1151-22AB-E011-B412-003048678F78.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/48CDAC6F-40AB-E011-ACD5-001A92971B0C.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/486BBEE9-1BAB-E011-AC8C-003048679044.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/46B073DD-1BAB-E011-88EB-003048679162.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/46790E79-3FAB-E011-BA4F-001BFCDBD11E.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/466F0F7B-1EAB-E011-921B-00304867C04E.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/42990549-1BAB-E011-A4B7-0026189438E3.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/4292677A-89AB-E011-9C63-002618943932.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/3E59D57D-1EAB-E011-A786-002618943880.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/3E3CE123-89AB-E011-816A-0026189438BA.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/3C67F880-1EAB-E011-8CB3-0026189438C1.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/3C11AE4E-19AB-E011-B3BD-003048678FB2.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/363DCA5A-1BAB-E011-A3C2-003048678B34.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/3613FF7E-7DAB-E011-8516-002618943833.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/32B4177F-22AB-E011-B5AE-00261894393D.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/32263BC0-14AB-E011-A38D-002618FDA216.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/305A8115-1FAB-E011-9C88-002618943948.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/2A18D914-1FAB-E011-87E8-0026189438B8.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/28BE5E7D-1EAB-E011-9975-0026189438DF.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/283128EC-40AB-E011-80FB-002618943854.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/283057D7-22AB-E011-83B4-00248C55CC3C.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/26BD5CF6-13AB-E011-8EC3-0030486792BA.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/26724F2D-7BAB-E011-AFEA-00248C55CC97.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/26108718-1FAB-E011-B1C8-0026189438AE.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/24EFC55A-1BAB-E011-812C-00304867C04E.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/24B0851C-7EAB-E011-8E61-001A92811708.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/24A99ECA-22AB-E011-81F8-001A92811708.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/2245D27E-1EAB-E011-9741-003048678C62.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/220341C1-1DAB-E011-BAA5-003048D42DC8.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1EEB8E85-22AB-E011-A8A6-00304867BF18.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1EEA0842-8DAB-E011-AEC1-00261894396B.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1CC6A649-22AB-E011-B169-00261894398D.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1C54DDC0-22AB-E011-A16F-003048679000.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1C540606-14AB-E011-8432-003048678FA0.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1AD5A877-3FAB-E011-83C1-002618943960.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1A759256-7CAB-E011-8E47-002618943882.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/18EB8260-40AB-E011-9845-003048678EE2.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/18D26728-89AB-E011-B76E-003048678F1C.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/14B1472C-89AB-E011-92E5-0026189438B9.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/14078BAE-1DAB-E011-BEEB-003048678B34.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/12B5C1F8-13AB-E011-9158-00304867BEDE.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/10FA40F0-22AB-E011-B4B7-003048678F8A.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/105C350E-40AB-E011-BEB6-00261894383E.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/0E57307D-1EAB-E011-A377-002618FDA248.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/0E3AF4D8-1BAB-E011-A933-0030486790FE.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/0C795CE5-14AB-E011-A2B8-003048678DD6.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/0C676C2F-40AB-E011-B333-002618943833.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/0852D2C3-1DAB-E011-9C44-002618FDA262.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/06B15110-40AB-E011-8C69-0026189438A9.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/0670E5B2-1DAB-E011-B7B3-001A928116FA.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/06199DCF-22AB-E011-807F-0026189438BC.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/0401F271-22AB-E011-850F-00261894394B.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/02BA935F-40AB-E011-854C-00261894397A.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/02423245-1BAB-E011-984F-003048678A7E.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/00738CEB-22AB-E011-A622-001A92810AAE.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/0044C4C4-1DAB-E011-A6FD-002618FDA216.root',
'/store/mc/Summer11/T_TuneZ2_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/00026023-1AAB-E011-99D1-003048678AFA.root'
    ) )
)
