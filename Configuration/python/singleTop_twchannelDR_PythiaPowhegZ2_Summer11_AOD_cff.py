import FWCore.ParameterSet.Config as cms

############################################################################################
# Dataset: /T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM #
# Events : 814390                                                                          #
# xSec   : 5.3 (NLO MCFM)                                                                  #
# eff    : 1.0                                                                             #
############################################################################################

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource", fileNames = cms.untracked.vstring( *(
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/F87AD1D5-BBAB-E011-961F-002354EF3BDA.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/F85EDBBA-D9AB-E011-BB39-0018F34D0D62.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/F4ED3042-BDAB-E011-B9B0-003048678FDE.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/F499193B-CBAB-E011-9F4C-003048678B5E.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/F41E0226-BEAB-E011-9422-002618943920.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/F28A62BE-D3AB-E011-9678-0018F3D096F8.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E82BE278-C6AB-E011-A9E2-00261894395C.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E6C855D1-C3AB-E011-8F1A-002618943896.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/CC705749-E4AB-E011-B01A-0018F3C3E3A6.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/CADD651D-C4AB-E011-B368-00304867BFBC.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/CAA7D268-C4AB-E011-AE25-00261894393F.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C6AEF2FB-DBAB-E011-8729-0018F3D09642.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C4E5FADA-BFAB-E011-966F-002618943973.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/BED94EC7-D7AB-E011-A27D-0018F34D0D62.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/BEB1D0D1-C3AB-E011-AB11-002354EF3BE0.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/BC5AA188-BDAB-E011-A9CA-0026189438D6.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/BA9F5AD1-B9AB-E011-87AD-00261894392C.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B24DCB8C-BFAB-E011-88EB-0026189438DC.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/ACB53F23-BCAB-E011-9388-00304867906C.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/A8A16DAF-BFAB-E011-B81A-002618943856.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/A87E0289-BFAB-E011-8F93-002618FDA248.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/A2A5648B-C6AB-E011-ADD6-002618943964.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/9C699824-BEAB-E011-AA11-002618943877.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/9A8412D7-C3AB-E011-A2F9-0026189438FA.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/96A7FED2-C1AB-E011-AD89-00304867918A.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/90F4C762-C2AB-E011-BEEA-002618943939.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/8ACE2E7E-C6AB-E011-87CD-002618943865.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/7A80CC1C-C0AB-E011-9A05-002618943874.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/6EC6B3F9-BCAB-E011-B5A6-003048678AE4.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/68B1EFB2-BAAB-E011-A7B9-001A92971B16.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/667792D3-BFAB-E011-A908-0026189438DF.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/5E9ECD62-C2AB-E011-A417-00261894385A.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/5E685868-C2AB-E011-90A5-0026189438FA.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/5CFF7295-BDAB-E011-A22B-002618FDA263.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/54303C19-C0AB-E011-800F-002618943849.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/540B79FC-C4AB-E011-A9E2-0026189438DA.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/440960EF-C0AB-E011-9FF6-002354EF3BDA.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/4201A4DF-C8AB-E011-8E5D-002354EF3BDC.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/3C8E14F5-C0AB-E011-A482-00304867918A.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/38447E1C-C4AB-E011-8787-002618943972.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/36B24065-C0AB-E011-B259-00261894387A.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/28A432B7-E3AB-E011-9A58-0018F3D096E6.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/20561485-C1AB-E011-848A-002618943939.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1E6DCF60-C0AB-E011-B29C-002618943916.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/14B7F7FF-B8AB-E011-BAFC-002618943866.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/0A42F04C-BBAB-E011-8BE9-002618943939.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/04EAD4E0-C8AB-E011-A58D-0030486792AC.root',
'/store/mc/Summer11/T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/00D893B1-C2AB-E011-9C56-00261894383F.root'
    ) )
)
