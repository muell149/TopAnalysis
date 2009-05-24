import FWCore.ParameterSet.Config as cms

from TopAnalysis.TopFilter.filters.PtEventFilter_cfi import *

filterJetsPt = ptEventFilter.clone(input=["selectedLayer1Jets",])
filterMuonPt = ptEventFilter.clone(input=["selectedLayer1Muons",])
filterElecPt = ptEventFilter.clone(input=["selectedLayer1Electrons",])

