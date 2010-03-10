import FWCore.ParameterSet.Config as cms

from TopAnalysis.TopFilter.filters.EtaEventFilter_cfi import *

filterJetsEta = etaEventFilter.clone(input=["selectedPatJets",])
filterMuonEta = etaEventFilter.clone(input=["selectedPatMuons",])
filterElecEta = etaEventFilter.clone(input=["selectedPatElectrons",])

