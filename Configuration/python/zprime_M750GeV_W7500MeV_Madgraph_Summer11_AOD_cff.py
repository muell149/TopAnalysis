import FWCore.ParameterSet.Config as cms

##########################################################################
# Dataset: Zprime_M750GeV_W7500MeV-madgraph/AODSIM/PU_S4_START42_V11-v2/ #
# Events : 206525                                                        # 
# eff    : 1.0                                                           # 
##########################################################################

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [

"/store/mc/Summer11/Zprime_M750GeV_W7500MeV-madgraph/AODSIM/PU_S4_START42_V11-v2/0000/04D161F0-209E-E011-B8B0-00E08178C16B.root",
"/store/mc/Summer11/Zprime_M750GeV_W7500MeV-madgraph/AODSIM/PU_S4_START42_V11-v2/0000/0E6B17AD-059E-E011-AAA3-003048673F2C.root",
"/store/mc/Summer11/Zprime_M750GeV_W7500MeV-madgraph/AODSIM/PU_S4_START42_V11-v2/0000/16B31B12-0B9E-E011-A2C1-001A6478AB90.root",
"/store/mc/Summer11/Zprime_M750GeV_W7500MeV-madgraph/AODSIM/PU_S4_START42_V11-v2/0000/3494C055-289E-E011-B6C6-00E08178C14D.root",
"/store/mc/Summer11/Zprime_M750GeV_W7500MeV-madgraph/AODSIM/PU_S4_START42_V11-v2/0000/441AABF9-089E-E011-97BF-003048D45F7C.root",
"/store/mc/Summer11/Zprime_M750GeV_W7500MeV-madgraph/AODSIM/PU_S4_START42_V11-v2/0000/44759A67-149E-E011-8425-0025B3E0656C.root",
"/store/mc/Summer11/Zprime_M750GeV_W7500MeV-madgraph/AODSIM/PU_S4_START42_V11-v2/0000/483D4EB3-0C9E-E011-83D1-003048C8ECE0.root",
"/store/mc/Summer11/Zprime_M750GeV_W7500MeV-madgraph/AODSIM/PU_S4_START42_V11-v2/0000/6E881735-239E-E011-8AB9-00E08179187F.root",
"/store/mc/Summer11/Zprime_M750GeV_W7500MeV-madgraph/AODSIM/PU_S4_START42_V11-v2/0000/96471D18-089E-E011-9B6B-003048D47794.root",
"/store/mc/Summer11/Zprime_M750GeV_W7500MeV-madgraph/AODSIM/PU_S4_START42_V11-v2/0000/98E53E99-069E-E011-BCB1-003048D476DA.root",
"/store/mc/Summer11/Zprime_M750GeV_W7500MeV-madgraph/AODSIM/PU_S4_START42_V11-v2/0000/A2877B44-099E-E011-A1B3-0025B3E05C32.root",
"/store/mc/Summer11/Zprime_M750GeV_W7500MeV-madgraph/AODSIM/PU_S4_START42_V11-v2/0000/C258643D-1D9E-E011-BBB5-00E0817917D7.root",
"/store/mc/Summer11/Zprime_M750GeV_W7500MeV-madgraph/AODSIM/PU_S4_START42_V11-v2/0000/C4DD733F-119E-E011-AFB8-003048D46124.root",
"/store/mc/Summer11/Zprime_M750GeV_W7500MeV-madgraph/AODSIM/PU_S4_START42_V11-v2/0000/CA71E724-969E-E011-B5BE-00E08178C0B3.root",
"/store/mc/Summer11/Zprime_M750GeV_W7500MeV-madgraph/AODSIM/PU_S4_START42_V11-v2/0000/E23D3483-079E-E011-9343-003048D47A48.root",
"/store/mc/Summer11/Zprime_M750GeV_W7500MeV-madgraph/AODSIM/PU_S4_START42_V11-v2/0000/F2F51022-0A9E-E011-9CDB-0025B3E05DFA.root"

     ] );

secFiles.extend( [
               ] )

