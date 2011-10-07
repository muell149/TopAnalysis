import FWCore.ParameterSet.Config as cms

#######################################################################
# Dataset: Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S4_START42_V11-v2/ #
# Events : 232074                                                     # 
# eff    : 1.0                                                        # 
#######################################################################

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [

"/store/mc/Summer11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S4_START42_V11-v2/0000/22A8DCB1-1C9E-E011-ABCE-00E08178C069.root",
"/store/mc/Summer11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S4_START42_V11-v2/0000/2CA8EEAB-2E9E-E011-89D0-002590200858.root",
"/store/mc/Summer11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S4_START42_V11-v2/0000/3A6E3FC7-259E-E011-936F-002590200A94.root",
"/store/mc/Summer11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S4_START42_V11-v2/0000/3ABF47D4-199E-E011-BE97-00E08178C10F.root",
"/store/mc/Summer11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S4_START42_V11-v2/0000/4AD88A2D-279E-E011-908B-00E08179173B.root",
"/store/mc/Summer11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S4_START42_V11-v2/0000/7E9260E9-249E-E011-BBB1-00E08178C18B.root",
"/store/mc/Summer11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S4_START42_V11-v2/0000/801AFFF3-1E9E-E011-8D42-002481E15008.root",
"/store/mc/Summer11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S4_START42_V11-v2/0000/9479DA44-1B9E-E011-A268-0025B31E3C1C.root",
"/store/mc/Summer11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S4_START42_V11-v2/0000/C869075D-169E-E011-8665-00E08178C079.root",
"/store/mc/Summer11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S4_START42_V11-v2/0000/DC1D998E-179E-E011-9B98-00E08179174D.root",
"/store/mc/Summer11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S4_START42_V11-v2/0000/DE0F4643-219E-E011-88D9-00E08179173B.root",
"/store/mc/Summer11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S4_START42_V11-v2/0000/DEDD71F5-339E-E011-8360-00E08178C0A5.root",
"/store/mc/Summer11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S4_START42_V11-v2/0000/E2F1A76C-969E-E011-A177-001A64789D80.root",
"/store/mc/Summer11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S4_START42_V11-v2/0000/EC78F644-1B9E-E011-9807-00E081791735.root",
"/store/mc/Summer11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S4_START42_V11-v2/0000/F8856C8B-1D9E-E011-985F-00E08178C069.root",
"/store/mc/Summer11/Zprime_M500GeV_W5GeV-madgraph/AODSIM/PU_S4_START42_V11-v2/0000/FE7B1A81-239E-E011-8878-0025B3E06658.root"

     ] );

secFiles.extend( [
               ] )

