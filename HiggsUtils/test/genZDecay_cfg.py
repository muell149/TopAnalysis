import FWCore.ParameterSet.Config as cms


process = cms.Process("ZDecayTest")


process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.categories.append('GenZDecay')
process.MessageLogger.cerr.FwkReport.reportEvery = 10


process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)


#process.load("TopAnalysis.Configuration.Summer12.DYJetsToLL_M_10To50filter_8TeV_madgraph_Summer12_DR53X_PU_S10_START53_V7A_v1_cff")
#process.load("TopAnalysis.Configuration.Summer12.DYJetsToLL_M_50_TuneZ2Star_8TeV_madgraph_tarball_Summer12_DR53X_PU_S10_START53_V7A_v1_cff")
#process.load("TopAnalysis.Configuration.Summer12.GluGluToHToZZTo4L_M_125_8TeV_powheg_pythia6_Summer12_DR53X_PU_S10_START53_V7A_v1_cff")
process.load("TopAnalysis.Configuration.Summer12.VBF_HToZZTo4L_M_125_8TeV_powheg_pythia6_Summer12_DR53X_PU_S10_START53_V7A_v1_cff")
process.maxEvents.input = 101


process.load("TopAnalysis.HiggsUtils.producers.GenZDecay_cfi")


process.p = cms.Path(process.genZDecay)





process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('test_genZDecay.root'),
    outputCommands = cms.untracked.vstring(
        'drop *',
        'keep *_*_*_ZDecayTest',
    ),
)

process.e = cms.EndPath(process.out)
