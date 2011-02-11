import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# cfg file for writing a tree for template fitting
#-------------------------------------------------
process = cms.Process("TemplateTree")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

#-------------------------------------------------
# process configuration
#-------------------------------------------------

## define input
process.load("TopAnalysis/Configuration/samples/WJetsToLNuD6T_cff")

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

# load tree writer
process.load("TopAnalysis.TopAnalyzer.TemplateTreeWriter_cfi")

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('START38_V14::All')

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('TemplateTree.root')
)

## high level trigger filter
from HLTrigger.HLTfilters.hltHighLevel_cfi import *
process.hltFilter = hltHighLevel.clone(TriggerResultsTag = "TriggerResults::HLT", HLTPaths = ["HLT_Mu9"])

## ---
##    set up vertex filter
## ---
process.PVSelection = cms.EDFilter("PrimaryVertexFilter",
                                   pvSrc   = cms.InputTag('offlinePrimaryVertices'),
                                   minNdof = cms.double(4.0),
                                   maxZ    = cms.double(24.0),
                                   maxRho  = cms.double(2.0)
                                   )

## selection steps
process.load("TopAnalysis.TopFilter.sequences.muonSelection_cff")
from TopAnalysis.TopFilter.sequences.muonSelection_cff import *
process.myNotSoTightMuons = selectedPatMuons.clone(src = 'goldenMuons',
                                                   cut = '(trackIso+caloIso)/pt < 2.0 '
                                                   )
process.load("TopAnalysis.TopFilter.sequences.semiLeptonicSelection_cff")
from TopAnalysis.TopFilter.sequences.semiLeptonicSelection_cff import *
from PhysicsTools.PatAlgos.cleaningLayer1.jetCleaner_cfi import *

process.mytightLeadingPFJets = cleanPatJets.clone(
    src = cms.InputTag("tightLeadingPFJets"), 
    
    # preselection (any string-based cut on pat::Jet)
    preselection = cms.string(''),

    # overlap checking configurables
    checkOverlaps = cms.PSet(
        muons = cms.PSet(
           src       = cms.InputTag("vertexSelectedMuons"),
           algorithm = cms.string("byDeltaR"),
           preselection        = cms.string('pt > 20. & abs(eta) < 2.1 &'
                                            'combinedMuon.isNull = 0 &'
                                            'isTrackerMuon() =1 &'
                                            '(trackIso+caloIso)/pt < 2.0 &'
                                            'innerTrack.numberOfValidHits >= 11 &'
                                            'globalTrack.normalizedChi2 < 10.0 &'
                                            'globalTrack.hitPattern.numberOfValidMuonHits>0 &'
                                            'abs(dB)<0.02 &'
                                            'innerTrack.hitPattern.pixelLayersWithMeasurement>=1 &'
                                            'numberOfMatches>1'),
           deltaR              = cms.double(0.1),
           checkRecoComponents = cms.bool(False), # don't check if they share some AOD object ref
           pairCut             = cms.string(""),
           requireNoOverlaps   = cms.bool(True), # overlaps don't cause the jet to be discared
        )
    ),
    # finalCut (any string-based cut on pat::Jet)
    finalCut = cms.string(''),
)
process.myMuonSelection = countPatMuons.clone(src = 'myNotSoTightMuons',
                                              minNumber = 1
                                              )
process.mygoldenMuonsPf = checkJetOverlapMuons.clone(muons = "trackMuons",
                                                     jets =  "mytightLeadingPFJets" ,
                                                     deltaR  = cms.double(0.3),
                                                     overlap = cms.bool(False)
                                                     )
process.myNotSoTightMuonsPf = selectedPatMuons.clone(src = 'mygoldenMuonsPf',
                                                     cut = '(trackIso+caloIso)/pt < 2.0 '
                                                     )
process.goldenMuonsPf = checkJetOverlapMuons.clone(muons = "trackMuons",
                                                   jets =  "tightLeadingPFJets" ,
                                                   deltaR  = cms.double(0.3),
                                                   overlap = cms.bool(False)
                                                   )
process.myTightMuonsPf = selectedPatMuons.clone(src = 'goldenMuonsPf',
                                                cut = '(trackIso+caloIso)/pt < 0.05 '
                                                )
process.myMuonSelectionPf = countPatMuons.clone(src = 'myNotSoTightMuonsPf',
                                                minNumber = 1
                                                )
process.muonSelectionPf = countPatMuons.clone(src = 'myTightMuonsPf',
                                              minNumber = 1,
                                              maxNumber = 1
                                              )

## get JER/JES-shifting module
process.load("TopAnalysis.TopUtils.JetEnergyScale_cfi")

process.p0 = cms.Path(process.hltFilter * process.scaledJetEnergy * process.semiLeptonicSelection * process.myNotSoTightMuons * process.mytightLeadingPFJets * process.goldenMuonsPf * process.mygoldenMuonsPf * process.myNotSoTightMuonsPf * process.myTightMuonsPf)

## change input collections to JER-shifted collections
from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
massSearchReplaceAnyInputTag(process.p0, 'selectedPatJetsAK5PF', 'scaledJetEnergy:selectedPatJetsAK5PF') 
massSearchReplaceAnyInputTag(process.p0, 'patMETsPF'           , 'scaledJetEnergy:patMETsPF') 

# set input collection- needed while running on pat tuples
process.scaledJetEnergy.inputJets = "selectedPatJetsAK5PF"
process.scaledJetEnergy.inputMETs = "patMETsPF"

# JER +10%
process.scaledJetEnergy.resolutionFactor = 1.1

process.JetSelectionNjetsPf1 = process.leadingJetSelection.clone (src = 'tightLeadingPFJets', minNumber = 1)
process.JetSelectionNjetsPf2 = process.leadingJetSelection.clone (src = 'tightLeadingPFJets', minNumber = 2)
process.JetSelectionNjetsPf3 = process.leadingJetSelection.clone (src = 'tightLeadingPFJets', minNumber = 3)
process.JetSelectionNjetsPf4 = process.leadingJetSelection.clone (src = 'tightLeadingPFJets', minNumber = 4)

process.myJetSelectionNjetsPf1 = process.leadingJetSelection.clone (src = 'mytightLeadingPFJets', minNumber = 1)
process.myJetSelectionNjetsPf2 = process.leadingJetSelection.clone (src = 'mytightLeadingPFJets', minNumber = 2)
process.myJetSelectionNjetsPf3 = process.leadingJetSelection.clone (src = 'mytightLeadingPFJets', minNumber = 3)
process.myJetSelectionNjetsPf4 = process.leadingJetSelection.clone (src = 'mytightLeadingPFJets', minNumber = 4)


## templates
process.TemplateTreeControlPf0 = process.writeTemplateTree.clone(MET = 'scaledJetEnergy:patMETsPF', muons = 'myNotSoTightMuonsPf', allMuons = 'selectedPatMuons' )
process.TemplateTreePf0 = process.writeTemplateTree.clone(MET = 'scaledJetEnergy:patMETsPF', muons = 'myTightMuonsPf', allMuons = 'selectedPatMuons' )

process.TemplateTreeControlPf1 = process.writeTemplateTree.clone(MET = 'scaledJetEnergy:patMETsPF', muons = 'myNotSoTightMuonsPf', allMuons = 'selectedPatMuons' )
process.TemplateTreePf1 = process.writeTemplateTree.clone(MET = 'scaledJetEnergy:patMETsPF', muons = 'myTightMuonsPf', allMuons = 'selectedPatMuons' )

process.TemplateTreeControlPf2 = process.writeTemplateTree.clone(MET = 'scaledJetEnergy:patMETsPF', muons = 'myNotSoTightMuonsPf', allMuons = 'selectedPatMuons' )
process.TemplateTreePf2 = process.writeTemplateTree.clone(MET = 'scaledJetEnergy:patMETsPF', muons = 'myTightMuonsPf', allMuons = 'selectedPatMuons' )

process.TemplateTreeControlPf3 = process.writeTemplateTree.clone(MET = 'scaledJetEnergy:patMETsPF', muons = 'myNotSoTightMuonsPf', allMuons = 'selectedPatMuons' )
process.TemplateTreePf3 = process.writeTemplateTree.clone(MET = 'scaledJetEnergy:patMETsPF', muons = 'myTightMuonsPf', allMuons = 'selectedPatMuons' )

process.TemplateTreeControlPf4 = process.writeTemplateTree.clone(MET = 'scaledJetEnergy:patMETsPF', muons = 'myNotSoTightMuonsPf', allMuons = 'selectedPatMuons' )
process.TemplateTreePf4 = process.writeTemplateTree.clone(MET = 'scaledJetEnergy:patMETsPF', muons = 'myTightMuonsPf', allMuons = 'selectedPatMuons' )

process.p1 = cms.Path(process.hltFilter              *
                      process.PVSelection            *
                      process.myMuonSelectionPf      *
                      process.secondMuonVeto         *
                      process.electronVeto           *
                      process.TemplateTreeControlPf0 *
                      process.myJetSelectionNjetsPf1 *
                      process.TemplateTreeControlPf1 *
                      process.myJetSelectionNjetsPf2 *
                      process.TemplateTreeControlPf2 *
                      process.myJetSelectionNjetsPf3 *
                      process.TemplateTreeControlPf3 *
                      process.myJetSelectionNjetsPf4 *
                      process.TemplateTreeControlPf4
                      )

process.p2 = cms.Path(process.hltFilter            *
                      process.PVSelection          *
                      process.muonSelectionPf      *
                      process.secondMuonVeto       *
                      process.electronVeto         *
                      process.TemplateTreePf0      *
                      process.JetSelectionNjetsPf1 *
                      process.TemplateTreePf1      *
                      process.JetSelectionNjetsPf2 *
                      process.TemplateTreePf2      *
                      process.JetSelectionNjetsPf3 *
                      process.TemplateTreePf3      *
                      process.JetSelectionNjetsPf4 *
                      process.TemplateTreePf4
                      )
