import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# cfg file creating histograms needed for the
# determination of the charge asymmetry parameter
#-------------------------------------------------
process = cms.Process("p1")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1

#-------------------------------------------------
# process configuration
#-------------------------------------------------

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(    
    ## add your favourite file here
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_1.root'
    '/store/user/henderle/Spring10/WJets_MAD/PATtuple_1.root'
    )
)

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

#-------------------------------------------------
# charge asymmetry analysis
#-------------------------------------------------

## module to create plots for calculation of charge asymmetry parameter
process.load("TopAnalysis.TopAnalyzer.ChargeAsymmetry_cfi")
## module that contains gen lepton collections and cutflows
process.load("TopAnalysis.TopFilter.sequences.genSelection_cff")
## cross section module to plot gen niveau selected events
process.load("TopAnalysis.TopAnalyzer.MuonCrossSection_cfi")

from TopAnalysis.TopFilter.sequences.genSelection_cff import isolatedGenMuons
process.isolatedGenMuons = isolatedGenMuons

process.analyzeChargeAsymmetryLeptons    = process.analyzeChargeAsymmetry.clone(src = 'genParticles',
                                           analyze = cms.PSet(index = cms.int32(-1),
                                                              lepton= cms.int32(-1)))
process.analyzeChargeAsymmetryMuons      = process.analyzeChargeAsymmetry.clone(src = 'isolatedGenMuons',
                                           analyze = cms.PSet(index = cms.int32(-1),
                                                              lepton= cms.int32(13)))
process.analyzeChargeAsymmetryWMuons     = process.analyzeChargeAsymmetry.clone(src = 'simpleGenWMuons',
                                           analyze = cms.PSet(index = cms.int32(-1),
                                                              lepton= cms.int32(13)))
process.analyzeChargeAsymmetryWElectrons = process.analyzeChargeAsymmetry.clone(src = 'simpleGenWElectrons',
                                           analyze = cms.PSet(index = cms.int32(-1),
                                                              lepton= cms.int32(11)))
process.analyzeChargeAsymmetryWTaus      = process.analyzeChargeAsymmetry.clone(src = 'simpleGenWTaus',
                                           analyze = cms.PSet(index = cms.int32(-1),
                                                              lepton= cms.int32(15)))
 
process.analyzeMuon     = process.analyzeCrossSectionGenMuon.clone(srcA = 'simpleGenWMuons'    ,analyze= cms.PSet(index = cms.int32(-1)))
process.analyzeElectron = process.analyzeCrossSectionGenMuon.clone(srcA = 'simpleGenWElectrons',analyze= cms.PSet(index = cms.int32(-1)))
process.analyzeTau      = process.analyzeCrossSectionGenMuon.clone(srcA = 'simpleGenWTaus'     ,analyze= cms.PSet(index = cms.int32(-1)))

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeChargeAsymmetry.root')
)

process.p1 = cms.Path(process.introduceGenWCollections        *
                      isolatedGenMuons                        *
                      process.analyzeMuon                     *
                      process.analyzeElectron                 *
                      process.analyzeTau                      *
                      process.analyzeChargeAsymmetryLeptons   *
                      process.analyzeChargeAsymmetryMuons     *
                      process.analyzeChargeAsymmetryWMuons    *  
                      process.analyzeChargeAsymmetryWElectrons*
                      process.analyzeChargeAsymmetryWTaus     
                      )
