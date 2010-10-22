import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# cfg file for the analysis of MET distributions
#-------------------------------------------------
process = cms.Process("HTlep")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

#-------------------------------------------------
# process configuration
#-------------------------------------------------

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(    
    ## add your favourite file here
    '/store/user/henderle/Spring10/TTbar_MAD/PATtuple_1_1.root'
    )
)
#process.load("TopAnalysis/Configuration/ttbar10_madPAT_cff")
## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

#-------------------------------------------------
# MET analysis
#-------------------------------------------------

## analyze MET
process.load("TopAnalysis.TopAnalyzer.HTlepTemplate_cfi")

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('HTlepTemplate.root')
)

## high level trigger filter
from HLTrigger.HLTfilters.hltHighLevel_cfi import *
process.hltFilter = hltHighLevel.clone(TriggerResultsTag = "TriggerResults::REDIGI", HLTPaths = ["HLT_Mu9"])

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
process.myMuonSelection = countPatMuons.clone(src = 'myNotSoTightMuons',
                                              minNumber = 1,
                                              maxNumber = 1
                                              )

process.p0 = cms.Path(process.hltFilter * process.semiLeptonicSelection * process.myNotSoTightMuons)

process.JetSelectionNjets1 = process.leadingJetSelection.clone (src = 'tightLeadingJets', minNumber = 1)
process.JetSelectionNjets2 = process.leadingJetSelection.clone (src = 'tightLeadingJets', minNumber = 2)
process.JetSelectionNjets3 = process.leadingJetSelection.clone (src = 'tightLeadingJets', minNumber = 3)
process.JetSelectionNjets4 = process.leadingJetSelection.clone (src = 'tightLeadingJets', minNumber = 4)


## HTlep templates
process.HTlepTemplate0 = process.analyzeHTlep.clone(srcA = 'patMETs', srcB = 'myNotSoTightMuons' )
process.HTlepTemplatePf0 = process.analyzeHTlep.clone(srcA = 'patMETsPF', srcB = 'myNotSoTightMuons' )
process.HTlep0 = process.analyzeHTlep.clone(srcA = 'patMETs', srcB = 'tightMuons' )
process.HTlepPf0 = process.analyzeHTlep.clone(srcA = 'patMETsPF', srcB = 'tightMuons' )

process.HTlepTemplate1 = process.analyzeHTlep.clone(srcA = 'patMETs', srcB = 'myNotSoTightMuons' )
process.HTlepTemplatePf1 = process.analyzeHTlep.clone(srcA = 'patMETsPF', srcB = 'myNotSoTightMuons' )
process.HTlep1 = process.analyzeHTlep.clone(srcA = 'patMETs', srcB = 'tightMuons' )
process.HTlepPf1 = process.analyzeHTlep.clone(srcA = 'patMETsPF', srcB = 'tightMuons' )

process.HTlepTemplate2 = process.analyzeHTlep.clone(srcA = 'patMETs', srcB = 'myNotSoTightMuons' )
process.HTlepTemplatePf2 = process.analyzeHTlep.clone(srcA = 'patMETsPF', srcB = 'myNotSoTightMuons' )
process.HTlep2 = process.analyzeHTlep.clone(srcA = 'patMETs', srcB = 'tightMuons' )
process.HTlepPf2 = process.analyzeHTlep.clone(srcA = 'patMETsPF', srcB = 'tightMuons' )

process.HTlepTemplate3 = process.analyzeHTlep.clone(srcA = 'patMETs', srcB = 'myNotSoTightMuons' )
process.HTlepTemplatePf3 = process.analyzeHTlep.clone(srcA = 'patMETsPF', srcB = 'myNotSoTightMuons' )
process.HTlep3 = process.analyzeHTlep.clone(srcA = 'patMETs', srcB = 'tightMuons' )
process.HTlepPf3 = process.analyzeHTlep.clone(srcA = 'patMETsPF', srcB = 'tightMuons' )

process.HTlepTemplate4 = process.analyzeHTlep.clone(srcA = 'patMETs', srcB = 'myNotSoTightMuons' )
process.HTlepTemplatePf4 = process.analyzeHTlep.clone(srcA = 'patMETsPF', srcB = 'myNotSoTightMuons' )
process.HTlep4 = process.analyzeHTlep.clone(srcA = 'patMETs', srcB = 'tightMuons' )
process.HTlepPf4 = process.analyzeHTlep.clone(srcA = 'patMETsPF', srcB = 'tightMuons' )

process.p1 = cms.Path(process.hltFilter          *
                      process.PVSelection        *
                      process.myMuonSelection    *
                      process.secondMuonVeto     *
                      process.electronVeto       *
                      process.HTlepTemplate0     *
                      process.HTlepTemplatePf0   *
                      process.JetSelectionNjets1 *
                      process.HTlepTemplate1     *
                      process.HTlepTemplatePf1   *
                      process.JetSelectionNjets2 *
                      process.HTlepTemplate2     *
                      process.HTlepTemplatePf2   *
                      process.JetSelectionNjets3 *
                      process.HTlepTemplate3     *
                      process.HTlepTemplatePf3   *
                      process.JetSelectionNjets4 *
                      process.HTlepTemplate4     *
                      process.HTlepTemplatePf4
                      )

process.p2 = cms.Path(process.hltFilter          *
                      process.PVSelection        *
                      process.muonSelection      *
                      process.secondMuonVeto     *
                      process.electronVeto       *
                      process.HTlep0             *
                      process.HTlepPf0           *
                      process.JetSelectionNjets1 *
                      process.HTlep1             *
                      process.HTlepPf1           *
                      process.JetSelectionNjets2 *
                      process.HTlep2             *
                      process.HTlepPf2           *
                      process.JetSelectionNjets3 *
                      process.HTlep3             *
                      process.HTlepPf3           *
                      process.JetSelectionNjets4 *
                      process.HTlep4             *
                      process.HTlepPf4
                      )
