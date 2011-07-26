import FWCore.ParameterSet.Config as cms

process = cms.Process("USER")

# ================
#  Message Logger
# ================

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 50000

# ==========================
#  Configuration of Process
# ==========================

process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

process.TFileService = cms.Service("TFileService", fileName = cms.string("MC_PUDist.root") )

#### Input Files

#process.load("TopAnalysis.Configuration.samples.Spring11_WJets_PATtuple_cff")

process.load("TopAnalysis.Configuration.samples.Summer11_TTJets_TuneZ2_7TeV_madgraph_tauola_cff")
#process.load("TopAnalysis.Configuration.samples.Summer11_WJetsToLNu_TuneZ2_7TeV_madgraph_tauola_cff")
#process.load("TopAnalysis.Configuration.samples.Summer11_DYJetsToLL_TuneZ2_M_50_7TeV_madgraph_tauola_cff")
#process.load("TopAnalysis.Configuration.samples.Summer11_QCD_Pt_20_MuEnrichedPt_15_TuneZ2_7TeV_pythia6_cff")
#process.load("TopAnalysis.Configuration.samples.Summer11_QCD_Pt_20to30_BCtoE_TuneZ2_7TeV_pythia6_cff")
#process.load("TopAnalysis.Configuration.samples.Summer11_QCD_Pt_20to30_EMEnriched_TuneZ2_7TeV_pythia6_cff")
#process.load("TopAnalysis.Configuration.samples.Summer11_QCD_Pt_30to80_BCtoE_TuneZ2_7TeV_pythia6_cff")
#process.load("TopAnalysis.Configuration.samples.Summer11_QCD_Pt_30to80_EMEnriched_TuneZ2_7TeV_pythia_cff")
#process.load("TopAnalysis.Configuration.samples.Summer11_QCD_Pt_80to170_BCtoE_TuneZ2_7TeV_pythia_cff")
#process.load("TopAnalysis.Configuration.samples.Summer11_QCD_Pt_80to170_EMEnriched_TuneZ2_7TeV_pythia6_cff")

#process.source = cms.Source("PoolSource",fileNames = cms.untracked.vstring())

#### Number of Events

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

#### Load default configuration

process.load("TopAnalysis.TopAnalyzer.MCPileUp_cfi")

#### Define path

process.p = cms.Path(process.MCPUDistribution)
