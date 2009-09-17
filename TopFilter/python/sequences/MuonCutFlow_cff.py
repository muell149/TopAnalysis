import FWCore.ParameterSet.Config as cms

## high level trigger filter
from HLTrigger.HLTfilters.hltHighLevel_cfi import *

## muon selector
from PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi import *

from TopAnalysis.TopAnalyzer.MuonQuality_cfi import *
from TopAnalysis.TopAnalyzer.MuonKinematics_cfi import *

## ---
##    setup trigger filter path
## ---
## single-muon trigger, threshold pt > 9 GeV, no isolation requirements
hltHighLevel.HLTPaths = ["HLT_Mu9"]

## ---
##    setup muon cutflow
## ---
## combined muons
combinedMuons = selectedLayer1Muons.clone(src = 'selectedLayer1Muons', cut = 'combinedMuon.isNull = 0')
## high pt muons
highptMuons = selectedLayer1Muons.clone(src = 'combinedMuons', cut = 'pt > 20.')
## central muons
centralMuons = selectedLayer1Muons.clone(src = 'highptMuons', cut = 'abs(eta) < 2.1')
## muons with a minimum number of tracker hits
enoughHitsMuons = selectedLayer1Muons.clone(src = 'centralMuons', cut = 'track.numberOfValidHits >= 11')
## significant muons
significantMuons = selectedLayer1Muons.clone(src = 'enoughHitsMuons', cut = 'abs(track.d0) < 0.2')
## global muon with reliable track fit
reliableFitMuons = selectedLayer1Muons.clone(src = 'significantMuons', cut = 'combinedMuon.normalizedChi2 < 10.0')
## muons with low ECAL energy
lowEcalMuons = selectedLayer1Muons.clone(src = 'reliableFitMuons', cut = 'ecalIsoDeposit.candEnergy < 4')
## muons with low HCAL energy
lowHcalMuons = selectedLayer1Muons.clone(src = 'lowEcalMuons', cut = 'hcalIsoDeposit.candEnergy < 6')
## isolated muons
isolatedMuons = selectedLayer1Muons.clone(src = 'lowHcalMuons', cut = '(trackIso+caloIso)/pt < 0.1')

QualityCombinedMuons = analyzeMuonQuality.clone(src = 'combinedMuons')
QualityHighptMuons = analyzeMuonQuality.clone(src = 'highptMuons')
QualityCentralMuons = analyzeMuonQuality.clone(src = 'centralMuons')
QualityEnoughHitsMuons = analyzeMuonQuality.clone(src = 'enoughHitsMuons')
QualitySignificantMuons = analyzeMuonQuality.clone(src = 'significantMuons')
QualityReliableFitMuons = analyzeMuonQuality.clone(src = 'reliableFitMuons')
QualityLowEcalMuons = analyzeMuonQuality.clone(src = 'lowEcalMuons')
QualityLowHcalMuons = analyzeMuonQuality.clone(src = 'lowHcalMuons')
QualityIsolatedMuons = analyzeMuonQuality.clone(src = 'isolatedMuons')

KinematicsCombinedMuons = analyzeMuonKinematics.clone(src = 'combinedMuons')
KinematicsHighptMuons = analyzeMuonKinematics.clone(src = 'highptMuons')
KinematicsCentralMuons = analyzeMuonKinematics.clone(src = 'centralMuons')
KinematicsEnoughHitsMuons = analyzeMuonKinematics.clone(src = 'enoughHitsMuons')
KinematicsSignificantMuons = analyzeMuonKinematics.clone(src = 'significantMuons')
KinematicsReliableFitMuons = analyzeMuonKinematics.clone(src = 'reliableFitMuons')
KinematicsLowEcalMuons = analyzeMuonKinematics.clone(src = 'lowEcalMuons')
KinematicsLowHcalMuons = analyzeMuonKinematics.clone(src = 'lowHcalMuons')
KinematicsIsolatedMuons = analyzeMuonKinematics.clone(src = 'isolatedMuons')

## ---
##    provide a sequence
## ---
cutFlowSequence = cms.Sequence((hltHighLevel * analyzeMuonQuality * analyzeMuonKinematics)               *
                               (combinedMuons * QualityCombinedMuons * KinematicsCombinedMuons)          *
                               (highptMuons * QualityHighptMuons * KinematicsHighptMuons)                *
                               (centralMuons * QualityCentralMuons * KinematicsCentralMuons)             *
                               (enoughHitsMuons * QualityEnoughHitsMuons * KinematicsEnoughHitsMuons)    *
                               (significantMuons * QualitySignificantMuons * KinematicsSignificantMuons) *
                               (reliableFitMuons * QualityReliableFitMuons * KinematicsReliableFitMuons) *
                               (lowEcalMuons * QualityLowEcalMuons * KinematicsLowEcalMuons)             *
                               (lowHcalMuons * QualityLowHcalMuons * KinematicsLowHcalMuons)             *
                               (isolatedMuons * QualityIsolatedMuons * KinematicsIsolatedMuons)
                              )


