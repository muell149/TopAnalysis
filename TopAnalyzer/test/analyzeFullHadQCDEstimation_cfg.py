import FWCore.ParameterSet.Config as cms

## ---
##   use this file to test the FullHadQCDEstimation.cc module
## ---


# set sequence shortcut
process = cms.Process("Analysis")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

# use only when PATTrigger is needed on data to suppress useless error messages
process.MessageLogger.cerr.default.limit = 0

## define input
process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring(    
    ## add your favourite file here
    #'/store/mc/Fall10/TT_7TeV-mcatnlo/AODSIM/START38_V12-v1/0000/68A868AD-F7EB-DF11-AD08-00221982AF2D.root'
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_1_1_490.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_2_1_qOs.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_3_1_vl4.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_4_1_ZFj.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_5_1_OCm.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_6_1_ygq.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_7_1_xLe.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_8_1_eCK.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_9_1_AuC.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_10_1_yXT.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_11_1_lO4.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_12_1_fav.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_13_1_5Kh.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_14_1_68T.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_15_1_okI.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_16_1_52z.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_17_1_9oP.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_18_1_XhT.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_19_1_xh6.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_20_1_EKK.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_21_1_qmQ.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_22_1_lR6.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_23_1_WXc.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_24_1_qHx.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_25_1_kIX.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_26_1_RCZ.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_27_1_c7D.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_28_1_tng.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_29_1_3PR.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_30_1_qSl.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_31_1_AyH.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_32_1_Ilb.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_33_1_x9P.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_34_1_R4O.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_35_1_7p6.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_36_1_gte.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_37_1_rq6.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_38_1_Nw4.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_39_1_jQU.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_40_1_s83.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_41_1_5dw.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_42_1_k6d.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_43_1_2Nf.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_44_1_nj6.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_45_1_X2l.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_46_1_gJp.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_47_1_tE4.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_48_1_Nyx.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_49_1_mPa.root',
    '/store/user/eschliec/MultiJet/PAT_6Jets/43119039b9fcde150ae447ded48bf16e/patTuple_6jets_50_1_QLm.root',
    ),
    skipEvents = cms.untracked.uint32(0)
 )

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeFullHadQCDEstimation_test.root')
)

## do event filtering on generator level
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEventFilters_cff")

## configure geometry & conditions
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = cms.string('START38_V14::All')
process.GlobalTag.globaltag = cms.string('GR_R_38X_V15::All')

## std sequence for pat
process.load("PhysicsTools.PatAlgos.patSequences_cff")

from PhysicsTools.PatAlgos.tools.jetTools import *
addJetCollection(process,cms.InputTag('ak5PFJets'),'AK5','PF',
                 doJTA        = True,
                 doBTagging   = True,
                 jetCorrLabel = ('AK5PF', ['L2Relative', 'L3Absolute', 'L2L3Residual']),
                 doType1MET   = False,
                 doL1Cleaning = False,
                 doL1Counters = False,
                 genJetCollection=cms.InputTag('ak5GenJets'),
                 doJetID      = True,
                 )

process.patJets.addTagInfos = False
process.patJetsAK5PF.addTagInfos = False

## get trigger module to be added to the path
process.load('TopAnalysis.TopUtils.patTriggerEvent_cff')
from TopAnalysis.TopFilter.filters.NewTriggerTestFilter_cfi import *

## the QuadJet25U trigger itself
process.hltQJ25U = filterTrigger.clone( whichTrigger="QuadJet25U" )

process.trigger = cms.Sequence(process.patTriggerDefaultSequence *
                               process.hltQJ25U
                               )

## select events with at least 6 jets
process.load("PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi")
process.tightLeadingJets = process.selectedPatJets.clone(src = 'selectedPatJetsAK5PF',
                                                         cut = 'abs(eta) < 2.4 & pt > 40. &'
                                                               'chargedHadronEnergyFraction > 0.0  &'
                                                               'neutralHadronEnergyFraction < 0.9  &'
                                                               'chargedEmEnergyFraction     < 0.99 &'
                                                               'neutralEmEnergyFraction     < 0.9  &'
                                                               'chargedMultiplicity > 0            &'
                                                               'nConstituents > 1'
                                                         )

process.tightBottomJets = process.selectedPatJets.clone(src = 'tightLeadingJets',
                                                        cut = 'bDiscriminator(\"trackCountingHighPurBJetTags\") > 3.41'
                                                        )
#process.tightBottomJets = process.selectedPatJets.clone(src = 'tightLeadingJets',
#                                                        cut = 'bDiscriminator(\"trackCountingHighEffBJetTags\") > 3.3'
#                                                        )

process.load("PhysicsTools.PatAlgos.selectionLayer1.jetCountFilter_cfi")
process.leadingJetSelection = process.countPatJets.clone( src = 'tightLeadingJets',
                                                          minNumber = 6
                                                          )
process.bottomJetSelection = process.countPatJets.clone( src = 'tightBottomJets',
                                                         minNumber = 0,
                                                         maxNumber = 0
                                                         )

## ---
##    load FullHadQCDEstimation Analyzer
## ---

## analyze the QCD estimation for fully hadronic ttbar events
process.load("TopAnalysis.TopAnalyzer.FullHadQCDEstimation_cfi")
process.analyzeFullHadQCDEstimation = process.analyzeFullHadQCDEstimation.clone(src = "tightLeadingJets")
process.analyzeFullHadQCDEstimation.analyze.bTagAlgoWP = "TCHPT"
#process.analyzeFullHadQCDEstimation.analyze.bTagAlgoWP = "TCHEM"

from TopQuarkAnalysis.TopObjectResolutions.stringResolutions_etEtaPhi_cff import *
process.analyzeFullHadQCDEstimation.analyze.udscResolutions = udscResolutionPF.functions
process.analyzeFullHadQCDEstimation.analyze.bResolutions    = bjetResolutionPF.functions

## ---
##    run the final sequence
## ---

process.p1 = cms.Path(
    ## do the filtering
    #process.makeGenEvt           *
    #process.ttFullHadronicFilter *
    #process.patDefaultSequence   *
    process.trigger              *
    process.tightLeadingJets     *
    process.leadingJetSelection  *
    process.tightBottomJets      *
    process.bottomJetSelection   *
    ## apply the analyzer
    process.analyzeFullHadQCDEstimation
    )
