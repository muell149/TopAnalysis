import FWCore.ParameterSet.Config as cms

## -------------------------------------------------------------------------
##   use this file to calculate the Z cross section with the tools of the semileptonic ttbar selection
##   goal: to normalize the ttbar cross section to the Z cross section
## -------------------------------------------------------------------------

## -------------------------------------------------------------------------
##    options
## -------------------------------------------------------------------------

## choose jet collection and corresponding MET
jetType =  'particleFlow' # 'Calo'
print 'jetType: ', jetType

## geneventfilter is to select a special Z decay channel from ZSample
## options: 'ZMuMu', 'ZTauTau', 'ZEE' and 'all' (default) for all other samples and data
if(not globals().has_key('genEventFilter')):
    #genEventFilter  = 'all'
    genEventFilter  = 'ZMuMu'
    #genEventFilter  = 'ZTauTau'
    #genEventFilter  = 'ZEE'
print 'chosen genEvent filter:' , genEventFilter

## choose whether generator studies of Z-> mu mu events should be performed
if(not globals().has_key('genStudies')):
    genStudies = "no"
    #genStudies = "additonally"
    #genStudies = "only"
print 'Z -> mu mu gen Studies performed:' , genStudies

## trigger details
if(not globals().has_key('triggerResultsTagName')):
    triggerResultsTagName = "TriggerResults::HLT"
if(not globals().has_key('hltPathsName')):
    hltPathsName = ["HLT_Mu9"]

# analyze muon quantities
process = cms.Process("Selection")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.MessageLogger.cerr.FwkReport.reportEvery = 1

## define input
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(    
    ## add your favourite file here
    '/store/user/mgoerner/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/PAT_FALL10HH/148435cd71339b79cc0025730c13472a/fall10MC_1_1_LCp.root'
    #'/store/user/wbehrenh/DYToMuMu_M-20_CT10_TuneZ2_7TeV-powheg-pythia/Fall10-START38_V12_PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_9_2_mDf.root'
    )
)
#process.load("TopAnalysis.Configuration.samples.DYJetsToLL_M50_D6T_madgraph_F10_cff")

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)
process.maxEvents.input=10

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeMuonZNorm.root')
)
process.TFileService.fileName='analyzeMuonZNorm_DYAll_test2.root'
#process.TFileService.fileName='analyzeMuonZNorm_DYMuMu_test.root'
#process.TFileService.fileName='analyzeMuonZNorm_DYTauTau_test.root'
#process.TFileService.fileName='analyzeMuonZNorm_DYEE_test.root'

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('START38_V14::All')

## -------------------------------------------------------------------------
## -------------------------------------------------------------------------
##    Filters and Selection
## -------------------------------------------------------------------------
## -------------------------------------------------------------------------

## -------------------------------------------------------------------------
## high level trigger filter
## -------------------------------------------------------------------------

#(use "TriggerResults::REDIGI38X" for fall10 QCD, WW, ZZ and WZ and "TriggerResults::HLT" for the other ones)
# for all PileUp sample use "TriggerResults::REDIGI38XPU"
from HLTrigger.HLTfilters.hltHighLevel_cfi import *
#process.hltFilter = hltHighLevel.clone(TriggerResultsTag = "TriggerResults::HLT", HLTPaths = ["HLT_Mu9"])
#process.hltFilter = hltHighLevel.clone(TriggerResultsTag = "TriggerResults::REDIGI38X", HLTPaths = ["HLT_Mu9"])
#process.hltFilter = hltHighLevel.clone(TriggerResultsTag = "TriggerResults::REDIGI38XPU", HLTPaths = ["HLT_Mu9"])
process.hltFilter = hltHighLevel.clone(TriggerResultsTag = triggerResultsTagName, HLTPaths = hltPathsName)
print "TriggerResultsTag=", process.hltFilter.TriggerResultsTag
print "HLTPaths=", process.hltFilter.HLTPaths

## -------------------------------------------------------------------------
## genEvent filter
## -------------------------------------------------------------------------

## generator filter for Z sample
process.load("TopAnalysis.TopFilter.filters.GeneratorZFilter_cfi")
process.genFilterZMuMu   = process.generatorZFilter.clone( zDecayModes = cms.vint32(13) )
process.genFilterZTauTau = process.generatorZFilter.clone( zDecayModes = cms.vint32(15) )
process.genFilterZEE     = process.generatorZFilter.clone( zDecayModes = cms.vint32(11) )
#process.generatorZFilter.zDecayModes = cms.vint32(15)
#process.generatorZFilter.diLeptonMassIntervals = cms.vdouble(20.,50.)


## -------------------------------------------------------------------------
## Vertex filter
## -------------------------------------------------------------------------

process.PVSelection = cms.EDFilter("PrimaryVertexFilter",
                                   pvSrc   = cms.InputTag('offlinePrimaryVertices'),
                                   minNdof = cms.double(4.0),
                                   maxZ    = cms.double(24.0),
                                   maxRho  = cms.double(2.0)
                                   )

## -------------------------------------------------------------------------
## Filter Sequence
## -------------------------------------------------------------------------

if(genEventFilter=="all"):
     ## sequence without genFilter (only trigger and PV Filter)
     process.filterSequence = cms.Sequence(
                                           process.hltFilter      * 
                                           process.PVSelection
                                          )
elif(genEventFilter=="ZMuMu"):
     ## sequence with genFilter
     process.filterSequence = cms.Sequence(
                                          process.genFilterZMuMu   *
                                          process.hltFilter        * 
                                          process.PVSelection
                                         )
elif(genEventFilter=="ZTauTau"):
     ## sequence with genFilter
     process.filterSequence = cms.Sequence(
                                          process.genFilterZTauTau   *
                                          process.hltFilter        * 
                                          process.PVSelection
                                         )
elif(genEventFilter=="ZEE"):
     ## sequence with genFilter
     process.filterSequence = cms.Sequence(
                                          process.genFilterZEE     *
                                          process.hltFilter        * 
                                          process.PVSelection
                                         )
else:
     print "ERROR!!! Non-valid input for genEvenFilter! No process.filterSequence defined!"

## -------------------------------------------------------------------------
## -------------------------------------------------------------------------
## Muon Selection
## -------------------------------------------------------------------------
## -------------------------------------------------------------------------

## semileptonic selection
process.load("TopAnalysis.TopFilter.sequences.semiLeptonicSelection_cff")
## muon selection
process.load("TopAnalysis.TopFilter.sequences.muonSelection_cff")
## jet selection
process.load("TopAnalysis.TopFilter.sequences.jetSelection_cff")
## redefine veto jets to be sure it is also replaced when running on PF
from TopAnalysis.TopFilter.sequences.jetSelection_cff import goodJets
process.vetoJets.src="goodJets"
process.vetoJets.cut=''
## filter for dimuon mass (leading two muons ONLY!!!!!!)
from TopAnalysis.TopFilter.filters.DiMuonFilter_cfi import *

## -------------------------------------------------------------------------
##    Set up selection steps for muon selection
## -------------------------------------------------------------------------

process.combinedMuonsSelection        = process.muonSelection.clone (src = 'combinedMuons'       , minNumber = 1, maxNumber = 99999999)
process.kinematicMuonsSelection       = process.muonSelection.clone (src = 'kinematicMuons'      , minNumber = 1, maxNumber = 99999999)
process.trackMuonsSelection           = process.muonSelection.clone (src = 'trackMuons'          , minNumber = 1, maxNumber = 99999999)
process.highPtMuonsSelection          = process.muonSelection.clone (src = 'highPtMuons'         , minNumber = 1, maxNumber = 99999999)
process.goldenMuonsSelection          = process.muonSelection.clone (src = 'goldenMuons'         , minNumber = 1, maxNumber = 99999999)
process.tightMuonsSelection           = process.muonSelection.clone (src = 'tightMuons'          , minNumber = 1, maxNumber = 99999999)
process.atLeastTwoTightMuonsSelection = process.muonSelection.clone (src = 'tightMuons'          , minNumber = 2, maxNumber = 99999999)
process.twoTightMuonsSelection        = process.muonSelection.clone (src = 'tightMuons'          , minNumber = 2, maxNumber = 2)

## select events in Z window (60-120 GeV) with unlike charge 
process.filterDiMuonMassZselectionRc	  = filterMuonPair.clone( muons  = cms.InputTag("tightMuons"),
                                                                  Cut    = cms.vdouble(60.,120.),
                                                                  isVeto = cms.bool(False),
                                                                  filterCharge = -1
                                                                 )
## select events in Z window (60-120 GeV) with like charge 
process.filterDiMuonMassZselectionWc	  = process.filterDiMuonMassZselectionRc.clone( filterCharge = 1 )

## General selection of all muons before cut on 2 muons
process.generalMuonSelection = cms.Sequence(process.combinedMuonsSelection        *
                                            process.highPtMuonsSelection          *
					    process.kinematicMuonsSelection       *
                                            process.trackMuonsSelection           *
                                            process.goldenMuonsSelection          *
                                            process.tightMuonsSelection
                                            )


## -------------------------------------------------------------------------
## Load Analysis tools for Cut Monitoring
## -------------------------------------------------------------------------

## plot primary vertex
process.load("TopAnalysis.TopAnalyzer.VertexAnalyzer_cfi") 
process.analyzePrimaryVertex.muons = cms.InputTag("tightMuons")

## jet kinematics analyzer
process.load("TopAnalysis.TopAnalyzer.JetKinematics_cfi")
## muon kinematics analyzer
process.load("TopAnalysis.TopAnalyzer.MuonKinematics_cfi")
process.analyzeLeadingMuonKinematics    =process.analyzeMuonKinematics.clone(analyze=cms.PSet(index=cms.int32(0)))
#process.analyzeLeadingMuonKinematics.analyze.index=0
process.analyze2ndLeadingMuonKinematics =process.analyzeMuonKinematics.clone(analyze=cms.PSet(index=cms.int32(1)))
#print "analyze2ndLeadingMuonKinematics.analyze.index=", process.analyze2ndLeadingMuonKinematics.analyze.index
#print "analyze2ndLeadingMuonKinematics.index=", process.analyze2ndLeadingMuonKinematics.index
process.analyze2ndLeadingMuonKinematics.analyze.index=1
#print "analyze2ndLeadingMuonKinematics.analyze.index=", process.analyze2ndLeadingMuonKinematics.analyze.index
#print "analyze2ndLeadingMuonKinematics.index=", process.analyze2ndLeadingMuonKinematics.index
process.analyzeAllMuonKinematics        =process.analyzeMuonKinematics.clone(analyze=cms.PSet(index=cms.int32(-1)))
#print "analyzeAllMuonKinematics.analyze.index=", process.analyzeAllMuonKinematics.analyze.index
#print "analyzeAllMuonKinematics.index=", process.analyzeAllMuonKinematics.index
## jet quality analyzer
process.load("TopAnalysis.TopAnalyzer.JetQuality_cfi")
## muon quality analyzer
process.load("TopAnalysis.TopAnalyzer.MuonQuality_cfi")
process.analyzeLeadingMuonQuality    =process.analyzeMuonQuality.clone(analyze=cms.PSet(index=cms.int32(0)))
process.analyze2ndLeadingMuonQuality =process.analyzeMuonQuality.clone(analyze=cms.PSet(index=cms.int32(1)))
process.analyzeAllMuonQuality        =process.analyzeMuonQuality.clone(analyze=cms.PSet(index=cms.int32(-1)))
## muon jet kinematics analyzer
process.load("TopAnalysis.TopAnalyzer.MuonJetKinematics_cfi")
## muon vertex analyzer
process.load("TopAnalysis.TopAnalyzer.MuonVertexKinematics_cfi")
## dimuon analyzer
process.load("TopAnalysis.TopAnalyzer.DimuonAnalyzer_cfi")
process.analyzeMuonPair.massBins=cms.vdouble(60.,120.)

## -------------------------------------------------------------------------
## Cut monitoring
## -------------------------------------------------------------------------

## N-1 muon collections
## --------------------
## Leading muons
process.noDbLeadingMuonQuality           = process.analyzeLeadingMuonQuality.clone   (src = 'noDbMuons'      )
process.noChi2LeadingMuonQuality         = process.analyzeLeadingMuonQuality.clone   (src = 'noChi2Muons'    )
process.noTrkHitsLeadingMuonQuality      = process.analyzeLeadingMuonQuality.clone   (src = 'noTrkHitsMuons' )
process.noIsoLeadingMuonQuality          = process.analyzeLeadingMuonQuality.clone   (src = 'noIsoMuons'     )
process.noEtaLeadingMuonKinematics       = process.analyzeLeadingMuonKinematics.clone(src = 'noEtaMuons'     )
process.noPtLeadingMuonKinematics        = process.analyzeLeadingMuonKinematics.clone(src = 'noPtMuons'      )
process.noDRMuonVetoJetsKinematics       = process.analyzeMuonJetKinematics.clone(srcA = 'noDRMuons',
                                                                                         srcB = 'goodJets'  )
## All muons
process.noDbAllMuonQuality           = process.analyzeAllMuonQuality.clone   (src = 'noDbMuons'      )
process.noChi2AllMuonQuality         = process.analyzeAllMuonQuality.clone   (src = 'noChi2Muons'    )
process.noTrkHitsAllMuonQuality      = process.analyzeAllMuonQuality.clone   (src = 'noTrkHitsMuons' )
process.noIsoAllMuonQuality          = process.analyzeAllMuonQuality.clone   (src = 'noIsoMuons'     )
process.noEtaAllMuonKinematics       = process.analyzeAllMuonKinematics.clone(src = 'noEtaMuons'     )
process.noPtAllMuonKinematics        = process.analyzeAllMuonKinematics.clone(src = 'noPtMuons'      )

## --------------------
## muon cutflow
## --------------------
process.combinedAllMuonKinematics         = process.analyzeAllMuonKinematics.clone(src = 'combinedMuons')
process.highPtAllMuonKinematics           = process.analyzeAllMuonKinematics.clone(src = 'highPtMuons')
process.kinematicAllMuonQuality           = process.analyzeAllMuonQuality.clone   (src = 'kinematicMuons')
process.kinematicMuonVertexKinematics     = process.analyzeMuonVertex.clone(srcA = 'kinematicMuons',
                                                                            srcB = 'offlinePrimaryVertices',
                                                                            analyze = cms.PSet(index = cms.int32(0)) )
process.trackMuonVetoJetsKinematics       = process.analyzeMuonJetKinematics.clone(srcA = 'trackMuons',
                                                                                   srcB = 'goodJets'  )
process.goldenAllMuonQuality              = process.analyzeAllMuonQuality.clone   	(src = 'goldenMuons'  )
process.tightAllMuonKinematics            = process.analyzeAllMuonKinematics.clone	 (src = 'tightMuons'   )
process.tightAllMuonKinematicsAtLeast2    = process.analyzeAllMuonKinematics.clone   	 (src = 'tightMuons'   )
process.tightAllMuonKinematics2           = process.analyzeAllMuonKinematics.clone   	 (src = 'tightMuons'   )
process.tightLeadingMuonKinematics2       = process.analyzeLeadingMuonKinematics.clone   (src = 'tightMuons'   )
process.tight2ndLeadingMuonKinematics2    = process.analyze2ndLeadingMuonKinematics.clone(src = 'tightMuons'   )
process.tightAllMuonKinematics2ZRes       = process.analyzeAllMuonKinematics.clone   	 (src = 'tightMuons'   )
process.tightLeadingMuonKinematics2ZRes   = process.analyzeLeadingMuonKinematics.clone   (src = 'tightMuons'   )
process.tight2ndLeadingMuonKinematics2ZRes= process.analyze2ndLeadingMuonKinematics.clone(src = 'tightMuons'   )
process.tightAllMuonQuality               = process.analyzeAllMuonQuality.clone   	 (src = 'tightMuons'   )
process.tightAllMuonQuality2ZRes          = process.analyzeAllMuonQuality.clone   	 (src = 'tightMuons'   )

## Dimuon analyzers
process.combinedMuonPair                  = process.analyzeMuonPair.clone(muons = 'combinedMuons') 
process.kinematicMuonPair                 = process.analyzeMuonPair.clone(muons = 'kinematicMuons') 
process.trackMuonPair                     = process.analyzeMuonPair.clone(muons = 'trackMuons')
process.tightMuonPair                     = process.analyzeMuonPair.clone(muons = 'tightMuons')
process.tightMuonPair2                    = process.analyzeMuonPair.clone(muons = 'tightMuons')
process.tightMuonPair2ZRes                = process.analyzeMuonPair.clone(muons = 'tightMuons')
## in case of wrong charge
process.tightMuonPairWc                   = process.analyzeMuonPair.clone(muons = 'tightMuons')
process.tightMuonPair2ZResWc              = process.analyzeMuonPair.clone(muons = 'tightMuons')

## --------------------
## N-1 jet collections
## --------------------
process.noEtaJetKinematics  = process.analyzeJetKinematics.clone(src = 'noEtaJets' )
process.noPtJetKinematics   = process.analyzeJetKinematics.clone(src = 'noPtJets'  )
if(jetType!="particleFlow"):
    process.noEmJetQuality      = process.analyzeJetQuality.clone(src = 'noEmJets'     )
    process.noN90HitsJetQuality = process.analyzeJetQuality.clone(src = 'noN90HitsJets')
    process.nofHPDJetQuality    = process.analyzeJetQuality.clone(src = 'nofHPDJets'   )

## --------------------
## jet cutflow
## --------------------
if(jetType=="particleFlow"):
    process.patJetKinematics = process.analyzeJetKinematics.clone(src = 'selectedPatJetsAK5PF')
elif(jetType=="Calo"):
    process.patJetKinematics = process.analyzeJetKinematics.clone(src = 'selectedPatJets')
else:
    print "unknown jetType"
process.centralJetKinematics    = process.analyzeJetKinematics.clone(src = 'centralJets'    )
process.reliableJetQuality      = process.analyzeJetQuality.clone   (src = 'reliableJets'   )
## tightLeadingJets==goodJets, i.e. final jet to be cut on
process.tightJetKinematics      = process.analyzeJetKinematics.clone(src = 'tightLeadingJets')
process.tightJetQuality         = process.analyzeJetQuality.clone   (src = 'tightLeadingJets')
process.bottomJetKinematics     = process.analyzeJetKinematics.clone(src = 'tightBottomJets' )
## after selection of Z resonance
process.tightJetKinematicsZRes  = process.analyzeJetKinematics.clone(src = 'tightLeadingJets')
process.tightJetQualityZRes     = process.analyzeJetQuality.clone   (src = 'tightLeadingJets')
process.bottomJetKinematicsZRes = process.analyzeJetKinematics.clone(src = 'tightBottomJets' )

## --------------------
## cutflow analyzer sequences
## --------------------
## muons N-1
process.monitorNMinusOneMuonCuts = cms.Sequence(
                                                process.noDbLeadingMuonQuality            +
                                                process.noChi2LeadingMuonQuality          +
                                                process.noTrkHitsLeadingMuonQuality       +
                                                process.noIsoLeadingMuonQuality           +
                                                process.noEtaLeadingMuonKinematics        +
                                                process.noPtLeadingMuonKinematics         +
                                                process.noDRMuonVetoJetsKinematics
                                                )
## jets N-1
if(jetType=="Calo"):
    process.monitorNMinusOneJetCuts = cms.Sequence(process.noEtaJetKinematics        +
                                                   process.noPtJetKinematics         +
                                                   process.noEmJetQuality            +
                                                   process.noN90HitsJetQuality       +
                                                   process.nofHPDJetQuality       
                                                   )
elif(jetType=="particleFlow"):
    process.monitorNMinusOneJetCuts = cms.Sequence(process.noEtaJetKinematics        +
                                                   process.noPtJetKinematics
                                                   )
else:
    print "unknown jetType"

## cutflow before cut on muon numbers
process.monitorGeneralCutflow = cms.Sequence(    ## muons
                                                 process.combinedAllMuonKinematics        +
                                                 process.highPtAllMuonKinematics          +
                                                 process.kinematicAllMuonQuality          +
                                                 process.kinematicMuonVertexKinematics    +
                                                 process.trackMuonVetoJetsKinematics      +
                                                 process.goldenAllMuonQuality             +
                                                 process.tightAllMuonKinematics            +
                                                 process.tightAllMuonQuality              +
                                                 ## muon pairs
                                                 process.combinedMuonPair                 +
                                                 process.kinematicMuonPair                +
                                                 process.trackMuonPair                    +
                                                 process.tightMuonPair                    +
                                                 ## jets
                                                 process.patJetKinematics                 +
                                                 process.centralJetKinematics             +
                                                 process.reliableJetQuality               +
                                                 process.tightJetKinematics
                                                )

## at least 2 tight muons:
process.monitorCutflowAtLeast2Muons = cms.Sequence(
                                                   process.tightAllMuonKinematicsAtLeast2
                                                   )
## 2 tight muons:
process.monitorCutflow2Muons        = cms.Sequence(
                                                   process.tightAllMuonKinematics2         +
                                                   process.tightLeadingMuonKinematics2     +
                                                   process.tight2ndLeadingMuonKinematics2  +
                                                   process.tightMuonPair2
                                                   )
## 2 tight muons on Z resonance (60-120 GeV):
process.monitorCutflow2MuonsZRes     = cms.Sequence(
                                                   process.tightAllMuonKinematics2ZRes         +
                                                   process.tightLeadingMuonKinematics2ZRes     +
                                                   process.tight2ndLeadingMuonKinematics2ZRes  +
                                                   process.tightAllMuonQuality2ZRes            +
                                                   process.tightMuonPair2ZRes                  +
                                                   process.tightJetKinematicsZRes              +
                                                   process.tightJetQualityZRes                 +
                                                   process.bottomJetKinematicsZRes
                                                   )


## -------------------------------------------------------------------------
## -------------------------------------------------------------------------
##    run the final sequences
## -------------------------------------------------------------------------
## -------------------------------------------------------------------------

if(genStudies!='only'):
     ## standard sequence for Z cross section analysis and detailed cut monitoring
     ## right charge path:
     process.pRc = cms.Path(
                      ## gen event selection (decay channel), trigger selection (hltFilter), PV selection
                      process.filterSequence                        *
                      ## introduce some collections
                      process.semiLeptonicSelection                 *
                      process.selectNMinusOneMuons                  *
                      process.selectNMinusOneJets                   *
                      ## monitor all muon and jet quantities before cut on muon numbers
                      process.analyzePrimaryVertex                  * # attention: after PV cut!
                      process.monitorNMinusOneMuonCuts              *
                      process.monitorNMinusOneJetCuts               *
                      process.monitorGeneralCutflow                 *
                      ## cut on different muon quantities
                      process.generalMuonSelection                  *
                      ## cut on at least 2 tight muons
                      process.atLeastTwoTightMuonsSelection         * # all these cuts not necessary as all needed info in tightMuonPair
                      process.monitorCutflowAtLeast2Muons           *
                      ## cut on exactly 2 tight muons
                      process.twoTightMuonsSelection                *
                      process.monitorCutflow2Muons                  *
                      ## cut on dimuon mass [60-120 GeV]
                      process.filterDiMuonMassZselectionRc          *
                      process.monitorCutflow2MuonsZRes
                      )
     ## wrong charge path:
     process.pWc = cms.Path(
                       ## gen event selection (decay channel), trigger selection (hltFilter), PV selection
                       process.filterSequence                        *
                       ## introduce some collections
                       process.semiLeptonicSelection                 *
                       ## analyze muon pairs
                       process.tightMuonPairWc                       *
                       ## cut on different muon quantities
                       process.generalMuonSelection                  *
                       ## cut on exactly 2 tight muons (just to have the number in the cutflow triggerReport)
                       process.twoTightMuonsSelection                *
                       ## cut on dimuon mass [60-120 GeV]
                       process.filterDiMuonMassZselectionWc          *
                       ## analyze muon pairs
                       process.tightMuonPair2ZResWc
                      )
     print "pRc and pWc included"
else:
     print "pRc and pWc not included"

## -------------------------------------------------------------------------
##  Generator Studies of the Z -> mu mu decay
## -------------------------------------------------------------------------

if(genEventFilter=='ZMuMu' and genStudies!='no'):
     ## Generator Studies of the Z -> mu mu decay

     ## generator level muon and di-muon filters
     from ZmumuAnalysis.Filter.GeneratorZmumuFilter_cfi import *

     process.GeneratorZmumuDiMuFilter     = GeneratorZmumuFilter.clone(
         zDecayMode = [13],
     )

     process.GeneratorZmumuDiMuMassFilter = process.GeneratorZmumuDiMuFilter.clone(
         diMuMassIntervals = [60.,120.],
     )

     process.GeneratorZmumuEtaFilter      = process.GeneratorZmumuDiMuFilter.clone(
         etaIntervals = [-2.1,2.1],
     )

     process.GeneratorZmumuPtFilter       = process.GeneratorZmumuDiMuFilter.clone(
         ptIntervals = [20.,99999.],
     )

     ## generator level muon and di-muon analyzers
     process.load("ZmumuAnalysis.Analyzer.GeneratorZmumuAnalyzer_cfi")
     from ZmumuAnalysis.Analyzer.GeneratorZmumuAnalyzer_cfi import *

     process.GeneratorZmumuAnalyzerDiMuFilter     = GeneratorZmumuAnalyzer.clone()
     process.GeneratorZmumuAnalyzerDiMuMassFilter = GeneratorZmumuAnalyzer.clone()
     process.GeneratorZmumuAnalyzerEtaFilter      = GeneratorZmumuAnalyzer.clone()
     process.GeneratorZmumuAnalyzerPtFilter       = GeneratorZmumuAnalyzer.clone()

     #process.load("TopAnalysis.Configuration.analysis.semiLeptonic.ZNorm.analyzeMuonZNormGenStudies_cff")
     process.pGenStudies = cms.Path(
             process.GeneratorZmumuDiMuFilter                                *
             process.GeneratorZmumuAnalyzerDiMuFilter                        *
             process.GeneratorZmumuDiMuMassFilter                            *
             process.GeneratorZmumuAnalyzerDiMuMassFilter                    *
             process.GeneratorZmumuEtaFilter                                 *
             process.GeneratorZmumuAnalyzerEtaFilter                         *
             process.GeneratorZmumuPtFilter                                  *
             process.GeneratorZmumuAnalyzerPtFilter
     )
     print "pGenStudies included"
else:
     print "pGenStudies not included"

## -------------------------------------------------------------------------
## Technicalities for switching to PF
## -------------------------------------------------------------------------

if(genStudies!='only' and jetType=="particleFlow"):
    from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
    pathlist = [process.pRc, process.pWc]
    for path in pathlist:  
        massSearchReplaceAnyInputTag(path, 'tightLeadingJets', 'tightLeadingPFJets')
        massSearchReplaceAnyInputTag(path, 'tightBottomJets' , 'tightBottomPFJets')
        massSearchReplaceAnyInputTag(path, 'goodJets'        , 'goodJetsPF30')
        massSearchReplaceAnyInputTag(path, 'centralJets'     , 'centralJetsPF30')
        massSearchReplaceAnyInputTag(path, 'reliableJets'    , 'reliableJetsPF30')
        massSearchReplaceAnyInputTag(path, 'noEtaJets'       , 'noEtaJetsPF30')
        massSearchReplaceAnyInputTag(path, 'noPtJets'        , 'noPtJetsPF')
        massSearchReplaceAnyInputTag(path, 'patMETs'         , 'patMETsPF')
