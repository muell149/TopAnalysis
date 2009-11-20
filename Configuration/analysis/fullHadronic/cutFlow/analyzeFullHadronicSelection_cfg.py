import FWCore.ParameterSet.Config as cms

## ---
##    here we need a general description of what the config id good for and the
##    switches mean. This should be in analogy of the Doxygen commentsin the
##    modules...
## ---

## ---
##    decide whether to run on:  * all *, * signal only *, * background only *
## ---
eventFilter  = 'all' # 'signal only' # 'background only' # 'all'

## NOT YET REIMPLEMENTED
useAntikt5   = True # False
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
    #'/store/relval/CMSSW_3_3_0/RelValTTbar/GEN-SIM-RECO/MC_31X_V9-v1/0009/F651D737-75B7-DE11-BDD4-001D09F2512C.root',
    #'/store/relval/CMSSW_3_3_0/RelValTTbar/GEN-SIM-RECO/MC_31X_V9-v1/0008/D69BE13C-14B7-DE11-BAA5-001D09F28D54.root',
    #'/store/relval/CMSSW_3_3_0/RelValTTbar/GEN-SIM-RECO/MC_31X_V9-v1/0008/CEAAC1F4-0BB7-DE11-93D7-000423D99AA2.root',
    #'/store/relval/CMSSW_3_3_0/RelValTTbar/GEN-SIM-RECO/MC_31X_V9-v1/0008/B2110E48-0DB7-DE11-B6B4-001D09F2906A.root',
    #'/store/relval/CMSSW_3_3_0/RelValTTbar/GEN-SIM-RECO/MC_31X_V9-v1/0008/96EF2E6E-18B7-DE11-A915-0019B9F72D71.root',
    #'/store/relval/CMSSW_3_3_0/RelValTTbar/GEN-SIM-RECO/MC_31X_V9-v1/0008/4EE61B91-0EB7-DE11-B348-000423D944F0.root',
    #'/store/relval/CMSSW_3_3_0/RelValTTbar/GEN-SIM-RECO/MC_31X_V9-v1/0008/405B7A7F-0FB7-DE11-876C-001D09F242EF.root',
    #'/store/relval/CMSSW_3_3_0/RelValTTbar/GEN-SIM-RECO/MC_31X_V9-v1/0008/381C27D2-10B7-DE11-BE8B-001D09F297EF.root',
    #'/store/relval/CMSSW_3_3_0/RelValTTbar/GEN-SIM-RECO/MC_31X_V9-v1/0008/1888F3CF-09B7-DE11-89DC-000423D9890C.root' 
    'file:/afs/naf.desy.de/user/r/rwolf/data/samples/ttbar09/patTuple_all_0_ttbar09.root'
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

## configure geometry & conditions
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('MC_31X_V9::All')

## std sequence for pat
process.load("PhysicsTools.PatAlgos.patSequences_cff")

## register TFileService
process.TFileService = cms.Service("TFileService",  
            fileName = cms.string('analyzeFullHadronicSelection_all.root')
)

## ---
##    decide whether to run on:  * all *, * signal only *, * background only *
## ---

## std sequence to produce the ttGenEvt
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")

## filter for full-hadronic 
process.load("TopQuarkAnalysis.TopEventProducers.producers.TtDecaySelection_cfi")
process.ttFullHadronicFilter = process.ttDecaySelection.clone()

if(not eventFilter=='all'):
    ## adapt output filename
    if(eventFilter=='signal only'):
        process.TFileService.fileName = 'analyzeFullHadronicSelection_sig.root'
    elif(eventFilter=='background only'):
        process.ttFullHadronicFilter.invert = True
        process.TFileService.fileName = 'analyzeFullHadronicSelection_bkg.root'
    else:
        raise NameError, "'"+eventFilter+"' is not a prober eventFilter name choose: 'all', 'signal only' or 'background only'"
    
    ## sequence with filter
    process.filterSequence = cms.Sequence(process.patDefaultSequence *
                                          process.makeGenEvt *
                                          process.ttFullHadronicFilter
                                          )
else:
    ## sequence without filter
    process.filterSequence = cms.Sequence(process.patDefaultSequence *
                                          process.makeGenEvt)

## ---
##    configure the cutflow scenario
## ---

## jet quality analyzer
process.load("TopAnalysis.TopAnalyzer.JetQuality_cfi")
## muon quality analyzer
process.load("TopAnalysis.TopAnalyzer.MuonQuality_cfi")
## jet kinematics analyzer
process.load("TopAnalysis.TopAnalyzer.JetKinematics_cfi")
## muon kinematics analyzer
process.load("TopAnalysis.TopAnalyzer.MuonKinematics_cfi")
## high level trigger filter
process.load("TopAnalysis.TopFilter.sequences.triggerFilter_cff")
## semileptonic selection
process.load("TopAnalysis.TopFilter.sequences.fullHadronicSelection_cff")
## generator matching
process.load("TopAnalysis.TopFilter.sequences.generatorMatching_cff")

## define ordered jets
uds0    = cms.PSet(index = cms.int32(0), correctionLevel = cms.string('abs')   )
uds1    = cms.PSet(index = cms.int32(1), correctionLevel = cms.string('abs')   )
uds2    = cms.PSet(index = cms.int32(2), correctionLevel = cms.string('abs')   )
uds3    = cms.PSet(index = cms.int32(3), correctionLevel = cms.string('abs')   )
uds4    = cms.PSet(index = cms.int32(4), correctionLevel = cms.string('abs')   )
uds5    = cms.PSet(index = cms.int32(5), correctionLevel = cms.string('abs')   )
bottom0 = cms.PSet(index = cms.int32(0), correctionLevel = cms.string('had:b') )
bottom1 = cms.PSet(index = cms.int32(1), correctionLevel = cms.string('had:b') )

## replace sisCone5 by antikt5
#if( useAntikt5 ):
#    process.goodJets.src = 'selectedLayer1JetsAK5'
    
## collect kinematics analyzers
process.tightBottomJetKinematics  = process.analyzeJetKinematics.clone (src = 'tightBottomJets' )
process.tightLeadingJetKinematics = process.analyzeJetKinematics.clone (src = 'tightLeadingJets')
process.tightLead_0_JetKinematics = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds0 )
process.tightLead_1_JetKinematics = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds1 )
process.tightLead_2_JetKinematics = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds2 )
process.tightLead_3_JetKinematics = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds3 )
process.tightLead_4_JetKinematics = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds4 )
process.tightLead_5_JetKinematics = process.analyzeJetKinematics.clone (src = 'tightLeadingJets', analyze = uds5 )
process.tightBJet_0_JetKinematics = process.analyzeJetKinematics.clone (src = 'tightBottomJets' , analyze = bottom0)
process.tightBJet_1_JetKinematics = process.analyzeJetKinematics.clone (src = 'tightBottomJets' , analyze = bottom1)

## to be called with fullHadronicSelection
process.monitorJetsKinematics = cms.Sequence(process.tightBottomJetKinematics  +
                                             process.tightBJet_0_JetKinematics +
                                             process.tightBJet_1_JetKinematics +
                                             process.tightLeadingJetKinematics +
                                             process.tightLead_0_JetKinematics +
                                             process.tightLead_1_JetKinematics +
                                             process.tightLead_2_JetKinematics +
                                             process.tightLead_3_JetKinematics +
                                             process.tightLead_4_JetKinematics +
                                             process.tightLead_5_JetKinematics  
                                             )

## collect quality analyzers for Jets
process.tightBottomJetQuality        = process.analyzeJetQuality.clone (src = 'tightBottomJets'    )
process.tightLeadingJetQuality       = process.analyzeJetQuality.clone (src = 'tightLeadingJets'      )
process.tightMatchedBJetQuality      = process.analyzeJetQuality.clone (src = 'tightMatchedBottomJets')
process.tightMatchedLightQJetQuality = process.analyzeJetQuality.clone (src = 'tightMatchedLightQJets')

## to be called with the *?selectTightJets?* sequence
process.monitorJetsQuality = cms.Sequence(process.tightBottomJetQuality        +
                                          process.tightLeadingJetQuality       +
                                          process.tightMatchedBJetQuality      +
                                          process.tightMatchedLightQJetQuality
                                          )

## ---
##    run the final sequence
## ---
process.p1 = cms.Path(## do the gen evetn selection
                      process.filterSequence        *
                      ## do the trigger selection
                      process.hltMu9                * 
                      ## do the selections
                      process.fullHadronicSelection *
                      ## do the matching
                      process.matchJetsToPartons    *
                      ## do the monitoring
                      process.monitorJetsQuality    *
                      process.monitorJetsKinematics *
                      ## do the event selection
                      process.fullHadronicEvents
                      )

## Output Module Configuration
if(writeOutput):
    process.out = cms.OutputModule("PoolOutputModule",
                                   fileName = cms.untracked.string('patTuple_selected.root'),
                                   # save only events passing the full path
                                   SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p1') ),
                                   # save output (comment to keep everything...)
                                   #outputCommands = cms.untracked.vstring('drop *',) 
                                   )
    process.outpath = cms.EndPath(process.out)
