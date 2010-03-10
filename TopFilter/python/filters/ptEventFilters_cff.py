import FWCore.ParameterSet.Config as cms

from TopAnalysis.TopFilter.filters.PtEventFilter_cfi import *

filterJetsPt = ptEventFilter.clone(input=["selectedPatJets",])
filterMuonPt = ptEventFilter.clone(input=["selectedPatMuons",])
filterElecPt = ptEventFilter.clone(input=["selectedPatElectrons",])

