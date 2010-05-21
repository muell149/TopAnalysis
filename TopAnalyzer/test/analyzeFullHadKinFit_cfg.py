import FWCore.ParameterSet.Config as cms

## ---
##   use this file to test the FullHadKinFit.cc module
## ---


# set sequence shortcut
process = cms.Process("Analysis")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 10

## define input
process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring(    
    ## add your favourite file here
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_1.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_2.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_3.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_4.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_5.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_6.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_7.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_8.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_9.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_10.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_11.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_12.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_13.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_14.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_15.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_16.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_17.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_18.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_19.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_20.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_21.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_22.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_23.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_24.root'
   ),
    skipEvents = cms.untracked.uint32(0)
 )

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeFullHadKinFit_test.root')
)

## ---
##    load FullHadKinFit Analyszer
## ---

## get particle content of sample with IDs
process.load("TopAnalysis.TopAnalyzer.FullHadKinFit_cfi")
process.load("TopAnalysis.TopAnalyzer.stringResolutions_etEtaPhi_cff")

process.analyzeFullHadKinFit_S1R1 = process.analyzeFullHadKinFit.clone()
process.analyzeFullHadKinFit_S1R1.udscResolutions = process.udscResolutionPF.functions
process.analyzeFullHadKinFit_S1R1.bResolutions = process.bjetResolutionPF.functions

process.analyzeFullHadKinFit_S1R2 = process.analyzeFullHadKinFit.clone( resol = 2.0 )
process.analyzeFullHadKinFit_S1R2.udscResolutions = process.udscResolutionPF.functions
process.analyzeFullHadKinFit_S1R2.bResolutions = process.bjetResolutionPF.functions

process.analyzeFullHadKinFit_S2R1 = process.analyzeFullHadKinFit.clone( smear = 2.0 )
process.analyzeFullHadKinFit_S2R1.udscResolutions = process.udscResolutionPF.functions
process.analyzeFullHadKinFit_S2R1.bResolutions = process.bjetResolutionPF.functions

process.analyzeFullHadKinFit_S2R2 = process.analyzeFullHadKinFit.clone( smear = 2.0 , resol = 2.0 )
process.analyzeFullHadKinFit_S2R2.udscResolutions = process.udscResolutionPF.functions
process.analyzeFullHadKinFit_S2R2.bResolutions = process.bjetResolutionPF.functions


## ---
##    run the final sequence
## ---

process.p1 = cms.Path(
    ## apply the analyzer
    process.analyzeFullHadKinFit_S1R1 *
    process.analyzeFullHadKinFit_S1R2 *
    process.analyzeFullHadKinFit_S2R1 *
    process.analyzeFullHadKinFit_S2R2
    )
