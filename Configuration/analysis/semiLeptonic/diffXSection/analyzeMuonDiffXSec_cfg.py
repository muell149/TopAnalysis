import FWCore.ParameterSet.Config as cms

## ---
##   use this file to study different distributions for measurement of differential Cross Section
##   does also a monitoring of the cuts before they are applied
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

eventFilter  = 'signal only'
## choose between # 'background only' # 'all' # 'signal only' # 'semileptonic electron only' # 'dileptonic electron only' # 'dileptonic muon only' # 'fullhadronic' # 'dileptonic muon + electron only' # 'via single tau only' # 'dileptonic via tau only'

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
      '/store/user/rwolf/ttbar09/patTuple_sig_0_ttbarx09.root'
    # '/store/user/rwolf/ttbar09/patTuple_all_0_ttbar09.root'
    # '/store/user/henderle/OctEx/SD_Mu9/InclusiveMu15/PATtuple_1.root'
    # '/store/user/henderle/samples/InclusiveMu15_7TeV/PATtuple_100.root'
    # '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_1.root'
    # '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_10.root'
    )
 )

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeDiffXSec_test.root')
)

## including analysis tools
## std sequence to produce the ttGenEvt
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")
## high level trigger filter
process.load("TopAnalysis.TopFilter.sequences.triggerFilter_cff")
## cross section module
process.load("TopAnalysis.TopAnalyzer.MuonCrossSection_cfi")
## jet kinematics analyzer
process.load("TopAnalysis.TopAnalyzer.JetKinematics_cfi")
## filter for different ttbar decay channels
process.load("TopQuarkAnalysis.TopEventProducers.producers.TtDecaySelection_cfi")
process.ttSemiLeptonicFilter = process.ttDecaySelection.clone()
process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.muon = True
process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchB.muon = False

if(not eventFilter=='all'):
    ## adapt output filename
    if(eventFilter=='signal only'):
        process.TFileService.fileName = 'analyzeDiffXSec_testSig.root'
    elif(eventFilter=='background only'):
        process.ttSemiLeptonicFilter.invert = True
    elif(eventFilter=='semileptonic electron only'):
        process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.muon     = False
        process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.electron = True
    elif(eventFilter=='dileptonic electron only'):
        process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.muon     = False
        process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.electron = True
        process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchB.electron = True
    elif(eventFilter=='dileptonic muon only'):
        process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.muon     = True
        process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchB.muon     = True
    elif(eventFilter=='fullhadronic'):
        process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.muon     = False
    elif(eventFilter=='dileptonic muon + electron only'):
        process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.muon     = True
        process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchB.electron = True
    elif(eventFilter=='dileptonic via tau only'):
        process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.muon     = False
        process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.tau      = True
        process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchB.electron = True
        process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchB.muon     = True
        process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchB.tau      = True
    elif(eventFilter=='via single tau only'):
        process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.muon     = False
        process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.tau      = True
    else:
        raise NameError, "'"+eventFilter+"' is not a prober eventFilter name choose: 'all', 'signal only', 'background only', 'semileptonic electron only', 'dileptonic electron only', 'dileptonic muon only', 'fullhadronic', 'via single tau only', 'dileptonic via tau only' or 'dileptonic muon + electron only'"
    
    ## sequence with filter for decay channel and trigger selection hltMu9
    process.filterSequence = cms.Sequence(process.makeGenEvt *
                                          process.ttSemiLeptonicFilter *
                                          process.hltMu9
                                          )
else:
    ## sequence without filter (only trigger selection hltMu9) - done when 'all' is chosen
    process.filterSequence = cms.Sequence(process.hltMu9)

## ---
##    configure the cutflow scenario
## ---

## semileptonic selection
process.load("TopAnalysis.TopFilter.sequences.semiLeptonicSelection_cff")
## generator matching
process.load("TopAnalysis.TopFilter.sequences.generatorMatching_cff")
## muon selection
process.load("TopAnalysis.TopFilter.sequences.muonSelection_cff")
## jet quality analyzer
process.load("TopAnalysis.TopAnalyzer.JetQuality_cfi")
## muon quality analyzer
process.load("TopAnalysis.TopAnalyzer.MuonQuality_cfi")
## jet kinematics analyzer
process.load("TopAnalysis.TopAnalyzer.JetKinematics_cfi")
## muon kinematics analyzer
process.load("TopAnalysis.TopAnalyzer.MuonKinematics_cfi")
## electron kinematics analyzer
process.load("TopAnalysis.TopAnalyzer.ElectronKinematics_cfi")
## jet selection
process.load("TopAnalysis.TopFilter.sequences.jetSelection_cff")

## including some muon and jet collections
from TopAnalysis.TopFilter.sequences.jetSelection_cff import reliableJets
process.reliableJets = reliableJets
from TopAnalysis.TopFilter.sequences.jetSelection_cff import centralJets
process.centralJets = centralJets
from TopAnalysis.TopFilter.sequences.semiLeptonicSelection_cff import combinedMuons
process.combinedMuons = combinedMuons

## define ordered jets
uds0    = cms.PSet(index = cms.int32(0), correctionLevel = cms.string('abs'    ) )
uds1    = cms.PSet(index = cms.int32(1), correctionLevel = cms.string('abs'    ) )
uds2    = cms.PSet(index = cms.int32(2), correctionLevel = cms.string('abs'    ) )
uds3    = cms.PSet(index = cms.int32(3), correctionLevel = cms.string('abs'    ) )

## jet Kinematic modules
process.unselectedLead_0_JetKinematics = process.analyzeJetKinematics.clone (src = 'selectedPatJets', analyze = uds0 )
process.unselectedLead_1_JetKinematics = process.analyzeJetKinematics.clone (src = 'selectedPatJets', analyze = uds1 )
process.unselectedLead_2_JetKinematics = process.analyzeJetKinematics.clone (src = 'selectedPatJets', analyze = uds2 )
process.unselectedLead_3_JetKinematics = process.analyzeJetKinematics.clone (src = 'selectedPatJets', analyze = uds3 )
process.shiftedLead_0_JetKinematics = process.analyzeJetKinematics.clone (src = 'scaledJetEnergy:selectedPatJets', analyze = uds0 )
process.shiftedLead_1_JetKinematics = process.analyzeJetKinematics.clone (src = 'scaledJetEnergy:selectedPatJets', analyze = uds1 )
process.shiftedLead_2_JetKinematics = process.analyzeJetKinematics.clone (src = 'scaledJetEnergy:selectedPatJets', analyze = uds2 )
process.shiftedLead_3_JetKinematics = process.analyzeJetKinematics.clone (src = 'scaledJetEnergy:selectedPatJets', analyze = uds3 )

process.unshiftedJets = cms.Sequence(process.unselectedLead_0_JetKinematics+
                                     process.unselectedLead_1_JetKinematics+
                                     process.unselectedLead_2_JetKinematics+
                                     process.unselectedLead_3_JetKinematics
                                     )

process.shiftedJets = cms.Sequence(process.shiftedLead_0_JetKinematics+
                                   process.shiftedLead_1_JetKinematics+
                                   process.shiftedLead_2_JetKinematics+
                                   process.shiftedLead_3_JetKinematics
                                   )
process.tightLeadingJetKinematics       = process.analyzeJetKinematics.clone (src = 'tightLeadingJets')
process.tightLeadingJetKinematicsNjets1 = process.analyzeJetKinematics.clone (src = 'tightLeadingJets')
process.tightLeadingJetKinematicsNjets2 = process.analyzeJetKinematics.clone (src = 'tightLeadingJets')
process.tightLeadingJetKinematicsNjets3 = process.analyzeJetKinematics.clone (src = 'tightLeadingJets')
process.tightLeadingJetKinematicsNjets4 = process.analyzeJetKinematics.clone (src = 'tightLeadingJets')
                                   
## set up distribution for cross section measurement
process.analyzeTightMuonCrossSection       = process.analyzeMuonCrossSection.clone(src = 'tightMuons')
process.analyzeTightMuonCrossSectionNjets1 = process.analyzeMuonCrossSection.clone(src = 'tightMuons')
process.analyzeTightMuonCrossSectionNjets2 = process.analyzeMuonCrossSection.clone(src = 'tightMuons')
process.analyzeTightMuonCrossSectionNjets3 = process.analyzeMuonCrossSection.clone(src = 'tightMuons')
process.analyzeTightMuonCrossSectionBtag   = process.analyzeMuonCrossSection.clone(src = 'tightMuons')

## ---
##    Set up selection steps for different jet multiplicities
## ---
process.leadingJetSelectionNjets1 = process.leadingJetSelection.clone (src = 'tightLeadingJets', minNumber = 1)
process.leadingJetSelectionNjets2 = process.leadingJetSelection.clone (src = 'tightLeadingJets', minNumber = 2)
process.leadingJetSelectionNjets3 = process.leadingJetSelection.clone (src = 'tightLeadingJets', minNumber = 3)

## ---
##    collect analyzers to investigate event selection cuts
## ---
process.combinedMuonKinematics = process.analyzeMuonKinematics.clone(src = 'combinedMuons')
process.trackMuonKinematics    = process.analyzeMuonKinematics.clone(src = 'trackMuons'   )
process.tightMuonKinematics    = process.analyzeMuonKinematics.clone(src = 'tightMuons'   )
process.looseVetoMuonKinematics= process.analyzeMuonKinematics.clone(src = 'looseMuons',
                                                                     analyze = cms.PSet(index = cms.int32(-1)))
process.triggerMuonQuality = process.analyzeMuonQuality.clone(src = 'triggerMuons')
process.goodMuonQuality    = process.analyzeMuonQuality.clone(src = 'goodMuons'   )
process.goldenMuonQuality  = process.analyzeMuonQuality.clone(src = 'goldenMuons' )
process.looseVetoElectronKinematics = process.analyzeElectronKinematics.clone(src = 'looseElectrons',
                                                                              analyze = cms.PSet(index = cms.int32(-1)))
process.allUnselectedJetKinematics  = process.analyzeJetKinematics.clone (src = 'selectedPatJets',
                                                                          analyze = cms.PSet(index = cms.int32(-1),
                                                                                             correctionLevel = cms.string('abs')))
process.allTightJetKinematics       = process.analyzeJetKinematics.clone(src = 'tightLeadingJets',
                                                                         analyze = cms.PSet(index = cms.int32(-1),
                                                                                            correctionLevel = cms.string('abs')))
process.centralLead_3_JetKinematics = process.analyzeJetKinematics.clone  (src = 'centralJets', analyze = uds3 )
process.allReliableJetQuality = process.analyzeJetQuality.clone (src = 'reliableJets',
                                                                 analyze = cms.PSet(index = cms.int32(-1) ,
                                                                                    flavor = cms.string("uds")
))

process.monitorCuts = cms.Sequence( process.combinedMuonKinematics  +
                                    process.triggerMuonQuality      +
                                    process.trackMuonKinematics     +
                                    process.goodMuonQuality         +
                                    process.goldenMuonQuality       +
                                    process.tightMuonKinematics     +
                                    process.looseVetoMuonKinematics +                                    
                                    process.looseVetoElectronKinematics + 
                                    process.allUnselectedJetKinematics +
                                    process.allReliableJetQuality   +
                                    process.allTightJetKinematics   +
                                    process.centralLead_3_JetKinematics
                                    )
## ---
##    run the final sequence
## ---

process.p1 = cms.Path(
                      ## do the gen event selection (decay channel) and the trigger selection (hltMu9)
                      process.filterSequence                      *
                      ## introduce some collections
                      process.semiLeptonicSelection               *
                      reliableJets                                *
                      centralJets                                 *
                      combinedMuons                               *
                      ## monitor all cut quantities
                      process.monitorCuts                         *
                      ## monitor jet Kinematics (to see JES effects)
#                      process.unshiftedJets                       *
                      ## do the event selection for muon
                      process.muonSelection                       *
                      ## do event selection veto cuts
                      process.secondMuonVeto                      *
                      process.electronVeto                        *
                      ## monitoring of jet kinematics before jetcuts
                      process.tightLeadingJetKinematics           *
                      ## Selection: N_jets = 1
                      process.leadingJetSelectionNjets1           *
                      ## plots for N_jets = 1
                      process.analyzeTightMuonCrossSectionNjets1  *
                      process.tightLeadingJetKinematicsNjets1     *                      
                      ## Selection: N_jets = 2
                      process.leadingJetSelectionNjets2           *
                      ## plots for N_jets = 2
                      process.analyzeTightMuonCrossSectionNjets2  *
                      process.tightLeadingJetKinematicsNjets2     *
                      ## Selection: N_jets = 3
                      process.leadingJetSelectionNjets3           *
                       ## plots for N_jets = 3
                      process.analyzeTightMuonCrossSectionNjets3  *
                      process.tightLeadingJetKinematicsNjets3     *
                      ## do event selection concerning jets
                      process.leadingJetSelection                 *
                      ## cross section measurement 
                      process.analyzeTightMuonCrossSection        *
                      ## monitoring of jet kinematics after jetcuts
                      process.tightLeadingJetKinematicsNjets4     *    
                      ## btag
                      process.bottomJetSelection                  *
                      process.analyzeTightMuonCrossSectionBtag
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
                                   #save output (comment to keep everything...)
                                   #outputCommands = cms.untracked.vstring('drop *',) 
                                   )
    process.outpath = cms.EndPath(process.out)
