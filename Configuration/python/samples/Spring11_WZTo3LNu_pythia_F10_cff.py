import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/wbehrenh/WZTo3LNu_TuneZ2_7TeV-pythia6/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_9_1_8Nn.root',
       '/store/user/wbehrenh/WZTo3LNu_TuneZ2_7TeV-pythia6/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_8_1_aOM.root',
       '/store/user/wbehrenh/WZTo3LNu_TuneZ2_7TeV-pythia6/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_7_1_g5k.root',
       '/store/user/wbehrenh/WZTo3LNu_TuneZ2_7TeV-pythia6/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_6_1_d3s.root',
       '/store/user/wbehrenh/WZTo3LNu_TuneZ2_7TeV-pythia6/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_5_1_iEo.root',
       '/store/user/wbehrenh/WZTo3LNu_TuneZ2_7TeV-pythia6/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_4_1_inR.root',
       '/store/user/wbehrenh/WZTo3LNu_TuneZ2_7TeV-pythia6/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_3_1_pWb.root',
       '/store/user/wbehrenh/WZTo3LNu_TuneZ2_7TeV-pythia6/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_2_1_fvP.root',
       '/store/user/wbehrenh/WZTo3LNu_TuneZ2_7TeV-pythia6/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_1_1_o5v.root',
       '/store/user/wbehrenh/WZTo3LNu_TuneZ2_7TeV-pythia6/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_11_1_Jom.root',
       '/store/user/wbehrenh/WZTo3LNu_TuneZ2_7TeV-pythia6/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_10_1_gLb.root' ] );


secFiles.extend( [
               ] )

