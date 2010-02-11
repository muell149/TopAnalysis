import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# cfg file for the production of PAT tuple
#-------------------------------------------------
process = cms.Process("PAT")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 100

#-------------------------------------------------
# process configuration
#-------------------------------------------------

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring()
)
execfile("TopAnalysis/Configuration/analysis/semiLeptonic/jetEnergy/Source_7TeV_cff.py")

## define maximal number of events to loop over
## ----------------------
## 50/pb at  7 TeV :  8,250
## 50/pb at 10 TeV : 20,750
## ----------------------
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

## configure geometry & conditions
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('MC_3XY_V18::All')

#-------------------------------------------------
# pat configuration
#-------------------------------------------------

## std sequence for pat
process.load("PhysicsTools.PatAlgos.patSequences_cff")

from PhysicsTools.PatAlgos.tools.coreTools import *
removeSpecificPATObjects(process,
                         ['Photons', 'Taus'],
                         outputInProcess=False)
removeCleaning(process,
               outputInProcess=False)

from PhysicsTools.PatAlgos.tools.jetTools import *
switchJetCollection(process, 
                    cms.InputTag('antikt5CaloJets'),   
                    doJTA            = True,            
                    doBTagging       = True,            
                    jetCorrLabel     = ('AK5','Calo'),  
                    doType1MET       = True,
                    genJetCollection = cms.InputTag("antikt5GenJets"),
                    doJetID          = False,
                    jetIdLabel       = "antikt5"
                    )

process.jetCorrFactors.corrSample = 'Summer09_7TeV'
## choose sample type for flavor dependent JEC
process.jetCorrFactors.sampleType = "ttbar" ## dijet or ttbar

#-------------------------------------------------
# event selection
#-------------------------------------------------

## apply realistic event selection
process.load("TopAnalysis.TopFilter.sequences.triggerFilter_cff")
process.load("TopAnalysis.TopFilter.sequences.semiLeptonicSelection_cff")
from TopAnalysis.TopFilter.sequences.semiLeptonicSelection_cff import disableCountFilter
disableCountFilter(process.bottomJetSelection)

#-------------------------------------------------
# output
#-------------------------------------------------

process.p1 = cms.Path(process.hltMu9 *
                      process.patDefaultSequence *
                      process.semiLeptonicSelection *
                      process.semiLeptonicEvents
                      )

## define event selection
process.EventSelection = cms.PSet(
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('p1')
    )
)

## configure output module
process.out = cms.OutputModule("PoolOutputModule",
    process.EventSelection,
    outputCommands = cms.untracked.vstring('drop *'),
    dropMetaDataForDroppedData = cms.untracked.bool(True),                                     
    fileName = cms.untracked.string('SemiLepPatTuple.root')
)

## save pat output
from PhysicsTools.PatAlgos.patEventContent_cff import *
process.out.outputCommands = patExtraAodEventContent
process.out.outputCommands += patEventContentNoLayer1Cleaning
process.out.outputCommands += ["keep *_*GenJets_*_*"]
process.out.outputCommands += ["drop *_towerMaker_*_*"]

process.outpath = cms.EndPath(process.out)
