import FWCore.ParameterSet.Config as cms

##### ##########################25 files#####################################
# for production details see section "Semilept.Mu in CMSSW 4_1_4"           #
# of https://twiki.cern.ch/twiki/bin/view/CMS/HamburgWikiAnalysisTop2011pat #
#############################################################################

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
    '/store/user/mgoerner/MuHad/PAT_Data2011_PrompReco160404-161312_UHH/5785c65a23fd81127760168aceffdb6c/Data2011_PrompReco160404-161312_10_1_Fdu.root',
    '/store/user/mgoerner/MuHad/PAT_Data2011_PrompReco160404-161312_UHH/5785c65a23fd81127760168aceffdb6c/Data2011_PrompReco160404-161312_18_1_8Mv.root',
    '/store/user/mgoerner/MuHad/PAT_Data2011_PrompReco160404-161312_UHH/5785c65a23fd81127760168aceffdb6c/Data2011_PrompReco160404-161312_3_1_aYM.root',
    '/store/user/mgoerner/MuHad/PAT_Data2011_PrompReco160404-161312_UHH/5785c65a23fd81127760168aceffdb6c/Data2011_PrompReco160404-161312_11_1_5K7.root',
    '/store/user/mgoerner/MuHad/PAT_Data2011_PrompReco160404-161312_UHH/5785c65a23fd81127760168aceffdb6c/Data2011_PrompReco160404-161312_19_1_shz.root',
    '/store/user/mgoerner/MuHad/PAT_Data2011_PrompReco160404-161312_UHH/5785c65a23fd81127760168aceffdb6c/Data2011_PrompReco160404-161312_4_1_fXO.root',
    '/store/user/mgoerner/MuHad/PAT_Data2011_PrompReco160404-161312_UHH/5785c65a23fd81127760168aceffdb6c/Data2011_PrompReco160404-161312_1_1_VxM.root',
    '/store/user/mgoerner/MuHad/PAT_Data2011_PrompReco160404-161312_UHH/5785c65a23fd81127760168aceffdb6c/Data2011_PrompReco160404-161312_20_1_TDL.root',
    '/store/user/mgoerner/MuHad/PAT_Data2011_PrompReco160404-161312_UHH/5785c65a23fd81127760168aceffdb6c/Data2011_PrompReco160404-161312_5_1_YBb.root',
    '/store/user/mgoerner/MuHad/PAT_Data2011_PrompReco160404-161312_UHH/5785c65a23fd81127760168aceffdb6c/Data2011_PrompReco160404-161312_12_1_0TE.root',
    '/store/user/mgoerner/MuHad/PAT_Data2011_PrompReco160404-161312_UHH/5785c65a23fd81127760168aceffdb6c/Data2011_PrompReco160404-161312_21_1_4eJ.root',
    '/store/user/mgoerner/MuHad/PAT_Data2011_PrompReco160404-161312_UHH/5785c65a23fd81127760168aceffdb6c/Data2011_PrompReco160404-161312_6_1_1y8.root',
    '/store/user/mgoerner/MuHad/PAT_Data2011_PrompReco160404-161312_UHH/5785c65a23fd81127760168aceffdb6c/Data2011_PrompReco160404-161312_13_1_Jot.root',
    '/store/user/mgoerner/MuHad/PAT_Data2011_PrompReco160404-161312_UHH/5785c65a23fd81127760168aceffdb6c/Data2011_PrompReco160404-161312_2_1_hS6.root',
    '/store/user/mgoerner/MuHad/PAT_Data2011_PrompReco160404-161312_UHH/5785c65a23fd81127760168aceffdb6c/Data2011_PrompReco160404-161312_7_1_PSP.root',
    '/store/user/mgoerner/MuHad/PAT_Data2011_PrompReco160404-161312_UHH/5785c65a23fd81127760168aceffdb6c/Data2011_PrompReco160404-161312_14_1_kMQ.root',
    '/store/user/mgoerner/MuHad/PAT_Data2011_PrompReco160404-161312_UHH/5785c65a23fd81127760168aceffdb6c/Data2011_PrompReco160404-161312_22_1_A08.root',
    '/store/user/mgoerner/MuHad/PAT_Data2011_PrompReco160404-161312_UHH/5785c65a23fd81127760168aceffdb6c/Data2011_PrompReco160404-161312_8_1_NcF.root',
    '/store/user/mgoerner/MuHad/PAT_Data2011_PrompReco160404-161312_UHH/5785c65a23fd81127760168aceffdb6c/Data2011_PrompReco160404-161312_15_1_q90.root',
    '/store/user/mgoerner/MuHad/PAT_Data2011_PrompReco160404-161312_UHH/5785c65a23fd81127760168aceffdb6c/Data2011_PrompReco160404-161312_23_1_cWp.root',
    '/store/user/mgoerner/MuHad/PAT_Data2011_PrompReco160404-161312_UHH/5785c65a23fd81127760168aceffdb6c/Data2011_PrompReco160404-161312_9_1_Asy.root',
    '/store/user/mgoerner/MuHad/PAT_Data2011_PrompReco160404-161312_UHH/5785c65a23fd81127760168aceffdb6c/Data2011_PrompReco160404-161312_16_1_R6r.root',
    '/store/user/mgoerner/MuHad/PAT_Data2011_PrompReco160404-161312_UHH/5785c65a23fd81127760168aceffdb6c/Data2011_PrompReco160404-161312_24_1_N3j.root',
    '/store/user/mgoerner/MuHad/PAT_Data2011_PrompReco160404-161312_UHH/5785c65a23fd81127760168aceffdb6c/Data2011_PrompReco160404-161312_17_1_lOd.root',
    '/store/user/mgoerner/MuHad/PAT_Data2011_PrompReco160404-161312_UHH/5785c65a23fd81127760168aceffdb6c/Data2011_PrompReco160404-161312_25_1_9tD.root'
    ] );
        
secFiles.extend( [
               ] );

