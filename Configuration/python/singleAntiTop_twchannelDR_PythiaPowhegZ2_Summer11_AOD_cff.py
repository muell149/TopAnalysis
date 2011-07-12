import FWCore.ParameterSet.Config as cms

###############################################################################################
# Dataset: /Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM #
# Events : 809984                                                                             #
# xSec   : 5.3 (NLO MCFM)                                                                     #
# eff    : 1.0                                                                                #
###############################################################################################

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource", fileNames = cms.untracked.vstring( *(
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FEEC7CA0-1EAB-E011-8969-003048678B34.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/F884E20E-40AB-E011-B9B8-002618943954.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/F2A3712E-82AB-E011-9D4F-00261894398A.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/EA6F3245-19AB-E011-99C9-002618943954.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E8DCD5DC-22AB-E011-B615-0018F3D096D4.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/DE25DDDD-21AB-E011-A8E8-001A92811716.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/DAA0D6BC-1DAB-E011-87A2-003048678A6A.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/DA04458F-1EAB-E011-8501-00261894391C.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/D4F8F87B-3FAB-E011-B9A4-002618943948.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/CC248E02-23AB-E011-8926-0026189438DA.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C452175B-3EAB-E011-9A70-0026189438E1.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C00BE1DF-21AB-E011-82E9-002618FDA279.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B81CB9E0-21AB-E011-8CB8-002354EF3BDD.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B4C52AF7-21AB-E011-A5D6-003048678BE6.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/9CD29E93-26AB-E011-8FD1-001A92971B54.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/9211D865-40AB-E011-8C3A-001A92971B0C.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/8A6393F0-14AB-E011-9C35-00304867BEDE.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/8A1165A4-1DAB-E011-8ABA-00248C55CC4D.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/887D8E41-88AB-E011-B639-003048678F8E.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/843695AF-1DAB-E011-B97C-0026189437FA.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/80E456CB-1DAB-E011-A053-0026189437EB.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/7857BEDB-21AB-E011-A88E-00261894393D.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/7660F204-22AB-E011-87B1-001A9281170C.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/70E3B5E6-40AB-E011-A46F-002618943896.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/702758AB-1DAB-E011-8EEB-003048678B0C.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/6EB8BA52-1BAB-E011-97EA-003048679048.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/6EA87712-40AB-E011-8AB7-0026189438D2.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/64EA84B5-89AB-E011-8993-0026189438AA.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/64926A8E-1EAB-E011-B264-003048678B0A.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/6071648C-1EAB-E011-876F-00248C55CC97.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/5E44FD9E-1FAB-E011-87A5-002618943976.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/58F701FD-87AB-E011-93E6-002618943981.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/583E177E-41AB-E011-9E3D-002618943949.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/56F4B3F7-21AB-E011-85D5-001A928116DC.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/4C91DA69-87AB-E011-B77F-00261894386D.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/46696A9D-1FAB-E011-8624-003048679294.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/440926B4-1DAB-E011-96E1-002618943940.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/42E080B1-1DAB-E011-980C-001A92971BB4.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/3C605EAA-1DAB-E011-8E81-003048D42D92.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/3A8AC6CA-94AB-E011-9DFC-0026189438EB.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/36517800-22AB-E011-A68E-003048B95B30.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/28A9EC26-1AAB-E011-8409-003048678BB2.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/2863CDD8-22AB-E011-932E-00261894398D.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1CE9C09D-7CAB-E011-BD2C-002618FDA211.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1CE47DFF-21AB-E011-AF1B-001A92810ABA.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1C2E2C97-1EAB-E011-844C-001BFCDBD154.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/18BBE18A-1EAB-E011-961A-00261894387E.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/0CA5F8B9-27AB-E011-998E-002618943985.root',
'/store/mc/Summer11/Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/0079198F-1EAB-E011-A557-003048679164.root'
    ) )
)
