import FWCore.ParameterSet.Config as cms

## ---
##   use this file to derive differential cross section plots
##   on generator niveau,
##   needs genParticle and genJets as input!!!
## ---

## ---
##    eventfilter is to get a special ttbar decay channel from ttbarSample by genmatching
##    decide whether to run on:
# 'background only' # 'all' # 'signal only' # 'semileptonic electron only' # 'dileptonic electron only' # 'dileptonic muon only' # 'fullhadronic' # 'dileptonic muon + electron only' # 'via single tau only' # 'dileptonic via tau only'
##    careful: genmatched selection- might cause problems for specific BG samples like qcd or data - use 'all' for them
##    signal is semileptonic with mu
##    background is ttbar other channels
##    'all' does no selection
## ---

useAntikt5   = False # True
## in new CMSSW-Version(33 or higher) is AK5 standard as selected layer 1 jets, so use !!False!! for these samples to get no error concerning collection names
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
    # '/store/user/rwolf/ttbar09/patTuple_sig_0_ttbarx09.root'
    # '/store/user/henderle/OctEx/SD_Mu9/InclusiveMu15/PATtuple_1.root'
    # '/store/user/henderle/samples/InclusiveMu15_7TeV/PATtuple_100.root'
      '/store/mc/Summer09/TTbar/AODSIM/MC_31X_V3_AODSIM-v1/0024/068F7867-2C88-DE11-B3C2-001F29C9A5AE.root'
    # '/store/user/henderle/samples/TTbar_madgraph_7TeV/PATtuple_1.root'
    # '/store/user/henderle/samples/TTbar_mcatnlo_7TeV/PATtuple_1.root'
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
