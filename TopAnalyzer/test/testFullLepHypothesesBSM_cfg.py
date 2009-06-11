import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# cfg file for the analysis of new physics in
# ttbar events
#-------------------------------------------------
process = cms.Process("TEST2")

## add message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
#process.MessageLogger.categories.append('TtFullLeptonicEvent')
process.MessageLogger.cerr.FwkReport.reportEvery = 1

process.MessageLogger.cerr.INFO = cms.untracked.PSet(
    default             = cms.untracked.PSet( limit = cms.untracked.int32( 0) ),
    TtFullLeptonicEvent = cms.untracked.PSet( limit = cms.untracked.int32(-1) )
)

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    '/store/mc/Summer08/TauolaTTbar/GEN-SIM-RECO/IDEAL_V9_v2/0009/06B00B4D-2EF7-DD11-8C08-001E0BECB5C0.root'

    #'/store/mc/Fall08/TTJets-madgraph/GEN-SIM-RECO/IDEAL_V11_redigi_v10/0000/06FC3959-4DFC-DD11-B504-00E08178C091.root',
    #'/store/mc/Fall08/TTJets-madgraph/GEN-SIM-RECO/IDEAL_V11_redigi_v10/0000/08126A32-C2FC-DD11-BFF3-00E08178C091.root',
    #'/store/mc/Fall08/TTJets-madgraph/GEN-SIM-RECO/IDEAL_V11_redigi_v10/0000/089F9442-28FC-DD11-803B-0015170AD174.root',
    #'/store/mc/Fall08/TTJets-madgraph/GEN-SIM-RECO/IDEAL_V11_redigi_v10/0000/0A1B6F50-B7FC-DD11-9744-00E08178C091.root',
    #'/store/mc/Fall08/TTJets-madgraph/GEN-SIM-RECO/IDEAL_V11_redigi_v10/0000/0A3AFC80-30FC-DD11-A41B-00E081791807.root'
    )
)

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(False)
)

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('FullLepTest.root')
)

## filter ttbar decay channel on generator level 
process.load("TopAnalysis.TopFilter.filters.TopChannelSelector_cfi")
process.selectChannel.Ttbar_MuonMuon = True

## configure geometry
process.load("Configuration.StandardSequences.Geometry_cff")

## configure conditions
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('IDEAL_V9::All')

## load magnetic field
process.load("Configuration.StandardSequences.MagneticField_cff")

## std sequence for pat
process.load("PhysicsTools.PatAlgos.patSequences_cff")

# filter for kinematics, muon iso and quality
process.load("TopAnalysis.TopFilter.sequences.fullLepMuonSelection_BSM_cff")

## std sequence to produce the ttGenEvt
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")

## std sequence to produce the ttFullLepEvent
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttFullLepEvtBuilder_cff")
process.ttFullLepEvent.verbosity = 1

## add event weight information
process.load("TopAnalysis.TopUtils.EventWeightPlain_cfi")

## analyze hypotheses
process.load("TopAnalysis.TopAnalyzer.FullLepHypothesesAnalyzerBSM_cff")

## process path
process.p = cms.Path(#process.selectChannel *
                     process.patDefaultSequence *
                     process.makeGenEvt *
                     process.makeTtFullLepEvent *
		     process.eventWeight *
                     process.selectFullMuonMuonKinematics *
                     process.selectFullMuonJetsKinematics *
                     process.selectFullMuonMuonIsolation *
		     process.analyzeAllFullLepHypothesesBSM
                    )


