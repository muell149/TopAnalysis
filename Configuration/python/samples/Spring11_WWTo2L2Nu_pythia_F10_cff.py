import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/wbehrenh/WWTo2L2Nu_TuneZ2_7TeV-pythia6/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_9_3_HXg.root',
       '/store/user/wbehrenh/WWTo2L2Nu_TuneZ2_7TeV-pythia6/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_8_6_W0z.root',
       '/store/user/wbehrenh/WWTo2L2Nu_TuneZ2_7TeV-pythia6/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_7_3_0yZ.root',
       '/store/user/wbehrenh/WWTo2L2Nu_TuneZ2_7TeV-pythia6/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_6_3_kO6.root',
       '/store/user/wbehrenh/WWTo2L2Nu_TuneZ2_7TeV-pythia6/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_5_4_rgO.root',
       '/store/user/wbehrenh/WWTo2L2Nu_TuneZ2_7TeV-pythia6/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_4_3_IGx.root',
       '/store/user/wbehrenh/WWTo2L2Nu_TuneZ2_7TeV-pythia6/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_3_3_xAU.root',
       '/store/user/wbehrenh/WWTo2L2Nu_TuneZ2_7TeV-pythia6/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_2_3_Wrn.root',
       '/store/user/wbehrenh/WWTo2L2Nu_TuneZ2_7TeV-pythia6/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_1_5_Qo8.root',
       '/store/user/wbehrenh/WWTo2L2Nu_TuneZ2_7TeV-pythia6/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_11_6_Wb4.root',
       '/store/user/wbehrenh/WWTo2L2Nu_TuneZ2_7TeV-pythia6/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_10_3_UhN.root' ] );


secFiles.extend( [
               ] )

