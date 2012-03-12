import FWCore.ParameterSet.Config as cms

################################################################################################
# Dataset: T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM  #
# Events : 1032197                                                                             #
# eff    : 1.0                                                                                 #
################################################################################################

import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/04D3F051-675F-E111-9741-00259021A43E.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/068E213C-675F-E111-B149-0025B3E066A4.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/0809FC7E-6D5F-E111-83EC-003048D45FB0.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/0ABAFC35-625F-E111-A19F-003048D45F32.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/0EE76527-595F-E111-BE96-003048673E9A.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1200D49B-545F-E111-8B6C-0025902009D8.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/127B6D3F-0961-E111-9F97-003048D47A56.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/18B2AEB5-4D5F-E111-BC81-0025B3E05BF4.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1AE6BC35-575F-E111-BC7C-0025B3E05E1C.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/20AB2504-735F-E111-8682-003048D45FEE.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/26762049-625F-E111-AC18-003048D479DE.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/2A26AE60-725F-E111-895D-001A64789464.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/2AA50215-0261-E111-8F6C-00E08179173F.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/3832D1A3-0461-E111-8D5A-003048D47A14.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/3AEEFD8D-0761-E111-AAAA-0025B3E06378.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/4091F271-505F-E111-B916-003048D45F9C.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/48C3D489-495F-E111-A3E8-003048D45FDA.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/527FC6AE-0661-E111-B620-0025B3E064F8.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/5C751434-585F-E111-861C-00E08178C159.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/643EFFC8-525F-E111-AFD3-003048670BCC.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/7264968B-FF60-E111-A27D-003048D479F0.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/7425C1BB-515F-E111-9D80-002481E15522.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/8AA19837-6C5F-E111-BBE7-00E08178C0D5.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/8AB92849-4E5F-E111-B9B1-0025902008FC.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/8C9CA13F-4F5F-E111-B1BF-003048D4770E.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/8E550415-615F-E111-8854-0025B3E06612.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/8EB606BD-0D61-E111-8014-003048D46028.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/960E1855-8260-E111-9AE4-00E08178C189.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/9AFEA94A-765F-E111-ABB0-00E08178C0C7.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/A4F5001C-665F-E111-91D3-003048D46250.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/A8B92598-0561-E111-AEBE-00E08179181F.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/AAE8F3A6-625F-E111-A442-002590200934.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/AC4B3E19-465F-E111-9946-003048D46094.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B0A4FE3D-ED61-E111-8AC2-003048635D6A.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B6F76F10-495F-E111-A868-003048673F8A.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/BA0E1E3A-4C5F-E111-90AC-0025B3E06496.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C20D063C-565F-E111-8093-00E08178C065.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C88F2018-695F-E111-AEB0-002590200A98.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/CAAAD161-6F5F-E111-890D-001A6478A7A4.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/CC18E895-735F-E111-9281-0025B3E05BBE.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/CC854058-5A5F-E111-BBA9-003048D47730.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/D441B40C-4B5F-E111-9287-00304866C51E.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/D494D918-715F-E111-879C-002590200B10.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/D85607D9-625F-E111-A0D7-002590200B34.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/DA894F2E-685F-E111-952A-00E081791767.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/DC337BD2-465F-E111-8B66-003048D479FA.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/DC447A29-5D5F-E111-BAA6-001A64789E20.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/DE06EEC2-DE61-E111-8588-00E08178C18D.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/DED3920A-555F-E111-84A4-00E0817918B9.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/DED8EA53-4A5F-E111-A9D1-003048D45F92.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E295E20C-835F-E111-9DB1-00E0817917E7.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E49FF7DA-755F-E111-9ABC-001A647894E8.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E4B9282C-1461-E111-8D00-0030486361BC.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E87C20E9-5D5F-E111-AD95-0025B3E06378.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/EE9B0ACC-435F-E111-B532-001A64789D60.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/F20197CF-6C5F-E111-A694-003048D476B8.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/F2828387-8D5F-E111-96B2-0025B3E05DBE.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/F40E7F5A-775F-E111-BC62-001A64789DC4.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/F4218D9A-5C5F-E111-882D-001A64787064.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/F82FE9FA-795F-E111-B2D7-002481E1501E.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FA0B9219-755F-E111-BC98-00E08178C123.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FC8BEFDF-6A5F-E111-BF2C-00E08178C121.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FE59AB7C-6F5F-E111-9CEB-F04DA23BBCCA.root',
       '/store/mc/Summer11/T_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FED4259D-4A5F-E111-BA96-002590200A40.root' ] );


secFiles.extend( [
               ] )
