# analog to TopQuarkAnalysis/TopEventProducers/python/sequences/ttGenEvent_cff.py

import FWCore.ParameterSet.Config as cms


#
# produce Higgs genEvent with all necessary ingredients
#
from TopAnalysis.HiggsUtils.producers.HiggsDecaySubset_cfi import *
from TopAnalysis.HiggsUtils.producers.HiggsGenEvtProducer_cfi import *


makeGenEvtHiggs = cms.Sequence(decaySubsetHiggs*genEvtHiggs)



