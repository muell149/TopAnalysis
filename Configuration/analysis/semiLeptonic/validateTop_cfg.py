import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# cfg file for the analysis of selected muon
# quantities
#-------------------------------------------------
process = cms.Process("TopVal")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
## process.MessageLogger.cerr.FwkReport.reportEvery = 100

#-------------------------------------------------
# process configuration
#-------------------------------------------------

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(    
    ## add your favourite file here
    "/store/user/rwolf/ttbar/patTuple_PATv2_ttbar_madgraph_1.root"
    )
)

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(False)
)

#-------------------------------------------------
# muon analysis
#-------------------------------------------------

## setup trigger selection
from HLTrigger.HLTfilters.hltHighLevel_cfi import *
process.leptonTrigger = hltHighLevel.clone(
    HLTPaths = ["HLT_Mu9", "HLT_Ele15_SW_EleId_L1R"]
    )

## setup the jet slection
process.load("TopAnalysis.TopFilter.sequences.jetSelection_cff")
##setup the muon selection
from PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi import *
process.combinedMuons = selectedLayer1Muons.clone(src = 'selectedLayer1Muons',
                                                  cut = 'combinedMuon.isNull=0'
                                                  )
process.isolatedMuons = selectedLayer1Muons.clone(src = 'selectedLayer1Muons',
                                                  cut = 'combinedMuon.isNull=0'
                                                        '& trackIso<1.'
                                                  )
##setup the electron selection
from PhysicsTools.PatAlgos.selectionLayer1.electronSelector_cfi import *
process.selectedElecs = selectedLayer1Electrons.clone(src = 'selectedLayer1Electrons', 
                                                      cut = 'electronID(\"eidRobustTight\") > 0.99'
                                                      )
process.isolatedElecs = selectedLayer1Electrons.clone(src = 'selectedLayer1Electrons', 
                                                      cut = 'electronID(\"eidRobustTight\") > 0.99'
                                                            '& trackIso<1.'
                                                      )


process.p1 = cms.Path(process.goodJets      +
                      process.combinedMuons +
                      process.isolatedMuons +
                      process.selectedElecs +
                      process.isolatedElecs
                      )

## jet count filter
from PhysicsTools.PatAlgos.selectionLayer1.jetCountFilter_cfi import *
process.JetMult2 = countLayer1Jets.clone(src='goodJets', minNumber=2)
process.JetMult3 = countLayer1Jets.clone(src='goodJets', minNumber=3)
process.JetMult4 = countLayer1Jets.clone(src='goodJets', minNumber=4)

## muon kinematics
from TopAnalysis.TopAnalyzer.MuonKinematics_cfi import *
process.MuonKinemat2    = analyzeMuonKinematics.clone(src='combinedMuons')
process.MuonKinemat3    = analyzeMuonKinematics.clone(src='combinedMuons')
process.MuonKinemat4    = analyzeMuonKinematics.clone(src='combinedMuons')
process.MuonKinemat2Iso = analyzeMuonKinematics.clone(src='isolatedMuons')
process.MuonKinemat3Iso = analyzeMuonKinematics.clone(src='isolatedMuons')
process.MuonKinemat4Iso = analyzeMuonKinematics.clone(src='isolatedMuons')

## muon quality
from TopAnalysis.TopAnalyzer.MuonQuality_cfi import *
process.MuonQuality2    = analyzeMuonQuality.clone(src='combinedMuons')
process.MuonQuality3    = analyzeMuonQuality.clone(src='combinedMuons')
process.MuonQuality4    = analyzeMuonQuality.clone(src='combinedMuons')

## elec kinematics
from TopAnalysis.TopAnalyzer.ElectronKinematics_cfi import *
process.ElecKinemat2    = analyzeElectronKinematics.clone(src='selectedElecs')
process.ElecKinemat3    = analyzeElectronKinematics.clone(src='selectedElecs')
process.ElecKinemat4    = analyzeElectronKinematics.clone(src='selectedElecs')
process.ElecKinemat2Iso = analyzeElectronKinematics.clone(src='isolatedElecs')
process.ElecKinemat3Iso = analyzeElectronKinematics.clone(src='isolatedElecs')
process.ElecKinemat4Iso = analyzeElectronKinematics.clone(src='isolatedElecs')

## elec quality
from TopAnalysis.TopAnalyzer.ElectronQuality_cfi import *
process.ElecQuality2    = analyzeElectronQuality.clone(src='selectedElecs')
process.ElecQuality3    = analyzeElectronQuality.clone(src='selectedElecs')
process.ElecQuality4    = analyzeElectronQuality.clone(src='selectedElecs')

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('validateTop.root')
)

process.p2 = cms.Path(
    process.leptonTrigger   +
    process.JetMult2        +
    process.MuonQuality2    +
    process.MuonKinemat2    +
    process.MuonKinemat2Iso +
    process.ElecQuality2    +
    process.MuonKinemat2    +
    process.MuonKinemat2Iso
)

process.p3 = cms.Path(
    process.leptonTrigger   +
    process.JetMult3        +
    process.MuonQuality3    +
    process.MuonKinemat3    +
    process.MuonKinemat3Iso +
    process.ElecQuality3    +
    process.ElecKinemat3    +
    process.ElecKinemat3Iso
)

process.p4 = cms.Path(
    process.leptonTrigger   +
    process.JetMult4        +
    process.MuonQuality4    +
    process.MuonKinemat4    +
    process.MuonKinemat4Iso +
    process.ElecQuality4    +
    process.ElecKinemat4    +
    process.ElecKinemat4Iso
)
