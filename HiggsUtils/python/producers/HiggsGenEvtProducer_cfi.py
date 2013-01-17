# analog to TopQuarkAnalysis/TopEventProducers/python/producers/TtGenEvtProducer_cfi.py

import FWCore.ParameterSet.Config as cms

genEvtHiggs = cms.EDProducer('HiggsGenEventReco',
    # input subset containing the decay chain
    src = cms.InputTag("decaySubsetHiggs"),
)
