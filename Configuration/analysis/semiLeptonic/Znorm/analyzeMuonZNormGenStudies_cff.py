## Generator Studies of the Z -> mu mu decay

import FWCore.ParameterSet.Config as cms

#******************************************************************************************
#   Filter Modules
#******************************************************************************************

## generator level muon and di-muon filters
from ZmumuAnalysis.Filter.GeneratorZmumuFilter_cfi import *

GeneratorZmumuDiMuFilter = GeneratorZmumuFilter.clone(
    zDecayMode = [13],
)

GeneratorZmumuDiMuMassFilter = GeneratorZmumuDiMuFilter.clone(
    diMuMassIntervals = [60.,120.],
)

GeneratorZmumuEtaFilter = GeneratorZmumuDiMuFilter.clone(
    etaIntervals = [-2.1,2.1],
)

GeneratorZmumuPtFilter = GeneratorZmumuDiMuFilter.clone(
    ptIntervals = [20.,99999.],
)

#******************************************************************************************
#   Analyzer Modules
#******************************************************************************************

## generator level muon and di-muon analyzers
process.load("ZmumuAnalysis.Analyzer.GeneratorZmumuAnalyzer_cfi")
from ZmumuAnalysis.Analyzer.GeneratorZmumuAnalyzer_cfi import *

GeneratorZmumuAnalyzerDiMuFilter     = GeneratorZmumuAnalyzer.clone()
GeneratorZmumuAnalyzerDiMuMassFilter = GeneratorZmumuAnalyzer.clone()
GeneratorZmumuAnalyzerEtaFilter      = GeneratorZmumuAnalyzer.clone()
GeneratorZmumuAnalyzerPtFilter       = GeneratorZmumuAnalyzer.clone()
