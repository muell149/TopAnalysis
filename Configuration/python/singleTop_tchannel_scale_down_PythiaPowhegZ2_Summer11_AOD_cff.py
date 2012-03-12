import FWCore.ParameterSet.Config as cms

#########################################################################################
# Dataset: T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1  #
# Events : 1041924                                                                      #
# eff    : 1.0                                                                          #
#########################################################################################
import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/00AFE1EA-6E5F-E111-83A2-001A64789470.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/0EB4D309-4B5F-E111-8DA1-003048D45F76.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/14CAB079-645F-E111-B3A5-0025902009CC.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1601C77C-715F-E111-83A0-002590200988.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/16DD8701-645F-E111-88B3-001A6478935C.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1A4D7A28-685F-E111-8C4B-003048D45FA8.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1CBAB19D-6A5F-E111-A9FC-00E0817918D3.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/2A6F1454-485F-E111-8278-002590200A40.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/320E1229-655F-E111-911D-002590200814.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/3228045B-6D5F-E111-B15C-00304866C47A.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/3A206B3D-605F-E111-BFB7-00E08178C107.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/429137D0-465F-E111-B723-001A64789E6C.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/44C54868-765F-E111-83C2-003048D45FEA.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/464B381A-755F-E111-A652-002481E75CDE.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/5455EA7E-645F-E111-8BE3-0025902008C4.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/5857B32A-585F-E111-8491-0025902008F4.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/5C89C94A-4B5F-E111-B275-003048D46010.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/6092D7F8-635F-E111-92DC-001A64789E24.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/620A6B87-595F-E111-9A3A-001A64789D14.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/62226AB1-775F-E111-904A-003048D45F5C.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/660CF587-735F-E111-93FF-003048D47742.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/681C9DA3-4D5F-E111-A53B-003048D476AA.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/6A5C63AC-5A5F-E111-8C5C-0025B3E05E1C.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/6E961F35-505F-E111-B40B-002590200A28.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/6EE0BA44-655F-E111-A302-00E08179178D.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/76881927-655F-E111-8589-002590200930.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/7CF8F42D-625F-E111-AB2C-003048D47A42.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/800EEDCE-5E5F-E111-9C64-00E08178C175.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/844398EF-635F-E111-826B-002590200B6C.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/84973D44-525F-E111-B7BA-001A64789E40.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/8AC25AEA-495F-E111-82CE-001A6478A7B0.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/9C020C06-495F-E111-B40A-0025B3E05DCA.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/A612CCAF-565F-E111-B86A-003048D4608C.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/A6B140AC-5A5F-E111-BB77-00304867400E.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/AA806A5F-5A5F-E111-8550-00E08179188F.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/AAC489CA-595F-E111-8E20-001A64789D14.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/AC506D7A-745F-E111-ABB8-002590200978.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/AC8C7BEF-645F-E111-BDC9-0025902009E8.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/AEE115F5-635F-E111-8466-0025B3E063FA.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B04848EB-635F-E111-962E-0025B3E05DB6.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B207A844-535F-E111-AC77-0025B3E06468.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B2D2C6EE-645F-E111-8401-00E08178C12F.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B861CC50-6D5F-E111-B4F1-001A64789D20.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/BAEC72E0-635F-E111-8E6A-002590200938.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/BCC311D1-645F-E111-8078-002481E14F38.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C4AF0FA8-645F-E111-8428-0025902008D0.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C4B3755D-6D5F-E111-B65E-002590200B08.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C6DC7A1B-485F-E111-A161-003048D479FC.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C86A506E-495F-E111-8760-003048D4771E.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C8F5183D-4F5F-E111-B2CC-00E08178C06F.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/D01BB352-675F-E111-85EE-003048D476F0.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/D6A58E9C-705F-E111-A9DF-002590200ADC.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/D85F2609-515F-E111-977B-003048D476BA.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/DA6CF68F-C25F-E111-95CF-00E08178C06B.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/DCBFD179-6C5F-E111-9E7F-001A64789CE8.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E2AF7549-4E5F-E111-8FB1-002481E15522.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/F0B49E79-645F-E111-A699-002481E1501E.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/F8F387AF-535F-E111-952A-00E0817918A7.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FC596342-675F-E111-AD5C-001A64789E20.root',
       '/store/mc/Summer11/T_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FEC67B27-695F-E111-A39C-002590200B34.root' ] );


secFiles.extend( [
               ] )
