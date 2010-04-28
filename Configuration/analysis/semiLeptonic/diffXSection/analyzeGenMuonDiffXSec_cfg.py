
import FWCore.ParameterSet.Config as cms

## ---
##   use this file to derive differential cross section plots
##   on generator niveau,
##   needs genParticle and genJets as input!!!
## ---

writeOutput  = False # True

# analyse muon quantities
process = cms.Process("Selection")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 100

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(    

## add your favourite file here

    # '/store/user/henderle/samples/Zjets_madgraph_10TeV/PATtuple_11.root'
    # '/store/user/henderle/samples/Wjets_madgraph_10TeV/PATtuple_1.root'
    # '/store/user/henderle/OctEx/SD_Mu9/InclusiveMu15/PATtuple_1.root'
    # '/store/user/henderle/samples/TTbar_madgraph_7TeV/PATtuple_1.root'
    # '/store/user/henderle/samples/TTbar_mcatnlo_7TeV/PATtuple_1.root'
    # '/store/mc/Summer09/TTbar/AODSIM/MC_31X_V3_AODSIM-v1/0024/068F7867-2C88-DE11-B3C2-001F29C9A5AE.root'
      '/store/mc/Spring10/TTbarJets-madgraph/AODSIM/START3X_V26_S09-v1/0005/0210B899-9C46-DF11-A10F-003048C69294.root'     
    # '/store/mc/Spring10/TTbar-mcatnlo/AODSIM/START3X_V26_S09-v2/0048/0AFCE331-684A-DF11-A9D0-002618943810.root'
    # '/store/mc/Spring10/InclusiveMu15/AODSIM/START3X_V26_S09-v1/0003/0092FE15-E844-DF11-AFCD-001A92811736.root'
    # '/store/mc/Spring10/WJets-madgraph/AODSIM/START3X_V26_S09-v1/0000/0EA3694A-FC44-DF11-90A6-001D0967D5A3.root'
    # '/store/mc/Spring10/ZJets-madgraph/AODSIM/START3X_V26_S09-v1/0013/00EFC4EA-3847-DF11-A194-003048D4DF80.root'
    )
 )

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(200)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeGENDiffXSec_test.root')
)

## including analysis tools
## tool to create ak5GenJets
process.load("RecoJets.Configuration.GenJetParticles_cff")
process.load("RecoJets.Configuration.RecoGenJets_cff") 
## cross section module
process.load("TopAnalysis.TopAnalyzer.MuonCrossSection_cfi")
## tool to select muons from gen Particles and save them as new collection
process.load("TopAnalysis.TopUtils.GenCandSelector_cfi")

## ---
##    configure the cutflow scenario
## ---

## generator level based semileptonic selection (muon and jets)
process.load("TopAnalysis.TopFilter.sequences.genSelection_cff")

## ---
##    DQM for top
## ---

# process.load("Validation.Generator.TopDecayChannelDQM_cfi")
# process.load("DQMServices.Core.DQM_cfg")
# process.load("DQMServices.Components.DQMEnvironment_cfi")
# process.DQM.collectorHost = ''
# process.dqmSaver.workflow = cms.untracked.string('/Test/TopDecayChannelDQM/DataSet')

## ---                                   
##    set up distribution for cross section measurement
## ---

## on reconstruction Niveau
process.analyzeTightMuonCrossSectionGenNjets1 = process.analyzeCrossSectionGenMuon.clone(srcA = 'selectedGenMuonCollection')
process.analyzeTightMuonCrossSectionGenNjets2 = process.analyzeCrossSectionGenMuon.clone(srcA = 'selectedGenMuonCollection')
process.analyzeTightMuonCrossSectionGenNjets3 = process.analyzeCrossSectionGenMuon.clone(srcA = 'selectedGenMuonCollection')
process.analyzeTightMuonCrossSectionGenNjets4 = process.analyzeCrossSectionGenMuon.clone(srcA = 'selectedGenMuonCollection')
process.analyzeTightMuonCrossSectionGenBtag   = process.analyzeCrossSectionGenMuon.clone(srcA = 'selectedGenMuonCollection')

## ---
##    Set up selection steps for different (gen)-jet multiplicities
## ---
process.leadingJetSelectionNjets1 = process.leadingGenJetSelection.clone (src = 'selectedGenJetCollection', minNumber = 1)
process.leadingJetSelectionNjets2 = process.leadingGenJetSelection.clone (src = 'selectedGenJetCollection', minNumber = 2)
process.leadingJetSelectionNjets3 = process.leadingGenJetSelection.clone (src = 'selectedGenJetCollection', minNumber = 3)
process.leadingJetSelectionNjets4 = process.leadingGenJetSelection.clone (src = 'selectedGenJetCollection', minNumber = 4)

## ---
##    run the final sequence
## ---

process.p1 = cms.Path(
                      ## introduce some collections
                      process.genJetParticles                       * 
                      process.ak5GenJets                            *
                      process.isolatedGenMuons                      *
                      process.semiLeptGenCollections                *
#                      selectedGenMuonCollection                     *
#                      selectedGenJetCollection                      *
                      ## do the event selection for muon
                      process.genMuonSelection                      *
                      ## for N_jets = 1+
                      process.leadingJetSelectionNjets1             *
                      process.analyzeTightMuonCrossSectionGenNjets1 *
                      ## for N_jets = 2+
                      process.leadingJetSelectionNjets2             *
                      process.analyzeTightMuonCrossSectionGenNjets2 *
                      ## for N_jets = 3+
                      process.leadingJetSelectionNjets3             *
                      process.analyzeTightMuonCrossSectionGenNjets3 *
                      ##  for N_jets = 4+
                      process.leadingJetSelectionNjets4             *
                      process.analyzeTightMuonCrossSectionGenNjets4 
                      ## DQM
#                      process.topDecayChannelDQM                    *
#                      process.dqmSaver                              
                      )

# replace label names when running on old (3_4_X) MC samples
inputs = ['Electrons','Jets','Taus','Muons','Photons']
from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
for input in inputs:
    massSearchReplaceAnyInputTag(process.p1, 'selectedPat'+input, 'selectedLayer1'+input)


## Output Module Configuration
if(writeOutput):
    process.out = cms.OutputModule("PoolOutputModule",
                                   fileName = cms.untracked.string('patTuple_selected.root'),
                                   # save only events passing the full path
                                   SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p1') ),
                                   )
    process.outpath = cms.EndPath(process.out)
