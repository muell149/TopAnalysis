import FWCore.ParameterSet.Config as cms

from TopAnalysis.TopFilter.filters.EtaEventFilter_cfi import *

filterJetsEta = etaEventFilter.clone(input=["selectedLayer1Jets",])
filterMuonEta = etaEventFilter.clone(input=["selectedLayer1Muons",])
filterElecEta = etaEventFilter.clone(input=["selectedLayer1Electrons",])

