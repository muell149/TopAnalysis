import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/04724B69-4156-E111-8DF8-90E6BA19A25D.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/0A93CE27-5156-E111-9B07-E0CB4E55363A.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/0ACCD376-4656-E111-BB30-20CF3027A626.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/0E043653-5356-E111-8506-0030487CDA4C.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/10B6F724-5756-E111-A31E-0030487CDA4C.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/120CDC17-5556-E111-B421-0030487CDA66.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/162353E2-4856-E111-95D9-0030487CDAC2.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/220BF6F6-3856-E111-A991-20CF3056171D.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/2A285D61-4756-E111-B357-90E6BA19A25D.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/2C1F541E-4F56-E111-A0A6-E0CB4E55363A.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/2C6C958A-4056-E111-A053-90E6BA19A257.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/323A7F6D-3B56-E111-8C79-BCAEC53F6D4E.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/3631923D-6756-E111-826F-20CF305B0534.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/36CF12E2-3F56-E111-A6B1-BCAEC5097203.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/383EAD2A-4656-E111-9321-90E6BA19A257.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/389F6A1D-4456-E111-86C7-001EC9D8B992.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/3ABB9340-4856-E111-83B1-001EC9D8D49F.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/3CC57311-4A56-E111-89C8-0030487CDAC2.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/3E2677AC-4D56-E111-8A25-001EC9D7F683.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/42A44FA2-6156-E111-96D6-001E4F3F228E.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/484EDD61-5056-E111-BA53-0030487CDA66.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/4C4E0A4C-4E56-E111-854C-0030487CDA66.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/521B0E25-2B56-E111-859C-E0CB4E1A1185.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/52E5D409-4756-E111-85AE-001EC9D7F1E7.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/58815F73-4C56-E111-8AB3-E0CB4EA0A934.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/5C099FB7-4156-E111-A534-001EC9D8B992.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/5E0F5FDB-3756-E111-BC6F-20CF3056171D.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/7CAB5856-4A56-E111-B662-485B39800C34.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/7E3C9AE3-4256-E111-BAF2-BCAEC5097203.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/92F40B08-3156-E111-890C-20CF3027A5C9.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/948FAE22-4F56-E111-BCE9-001EC9D7FA1C.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/A0B07C16-3356-E111-9BE4-20CF30561711.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/AA1F712A-4356-E111-B9EA-90E6BA19A257.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/AA48BEA3-4456-E111-A63C-E0CB4E29C4D2.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/B6F885AE-3356-E111-8E98-20CF3027A626.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/BA4C8E96-4556-E111-85EA-485B39800BFB.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/C0585F49-4B56-E111-B8AB-485B39800C15.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/CC3ACD2F-5456-E111-AFDC-001E4F2F0D1E.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/CE075D73-4356-E111-B35C-E0CB4E29C4D2.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/CE44D0E7-3C56-E111-B9C1-485B39800B8D.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/E8361FD3-4B56-E111-8FFA-90E6BA0D09AD.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/EC780FAF-5256-E111-843A-E0CB4E55363A.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/F02EB055-4256-E111-8A3A-485B39800BFB.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/F055630B-3F56-E111-B9C1-BCAEC5097203.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/F2744395-5956-E111-8533-0030487CDA4C.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/FA1BA834-3D56-E111-A4F2-BCAEC5097203.root' ] );


secFiles.extend( [
               ] )

