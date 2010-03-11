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
    "/store/user/henderle/samples/TTbar_mcatnlo_7TeV/PATtuple_1.root"
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
process.isoTrkMuons   = selectedLayer1Muons.clone(src = 'selectedLayer1Muons',
                                                  cut = 'combinedMuon.isNull=0'
                                                        '& trackIso<1.'
                                                  )
process.isoCalMuons   = selectedLayer1Muons.clone(src = 'selectedLayer1Muons',
                                                  cut = 'combinedMuon.isNull=0'
                                                        '& caloIso<1.'
                                                  )
process.isoRelMuons   = selectedLayer1Muons.clone(src = 'selectedLayer1Muons',
                                                  cut = 'combinedMuon.isNull=0'
                                                        '& (trackIso+caloIso)/pt < 0.1'
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
                      process.isoTrkMuons   +
                      process.isoCalMuons   +
                      process.isoRelMuons   +
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
process.MuonKinemat2       = analyzeMuonKinematics.clone(src='combinedMuons')
process.MuonKinemat3       = analyzeMuonKinematics.clone(src='combinedMuons')
process.MuonKinemat4       = analyzeMuonKinematics.clone(src='combinedMuons')
process.MuonKinemat2IsoTrk = analyzeMuonKinematics.clone(src='isoTrkMuons'  )
process.MuonKinemat3IsoTrk = analyzeMuonKinematics.clone(src='isoTrkMuons'  )
process.MuonKinemat4IsoTrk = analyzeMuonKinematics.clone(src='isoTrkMuons'  )
process.MuonKinemat2IsoCal = analyzeMuonKinematics.clone(src='isoCalMuons'  )
process.MuonKinemat3IsoCal = analyzeMuonKinematics.clone(src='isoCalMuons'  )
process.MuonKinemat4IsoCal = analyzeMuonKinematics.clone(src='isoCalMuons'  )
process.MuonKinemat2IsoRel = analyzeMuonKinematics.clone(src='isoRelMuons'  )
process.MuonKinemat3IsoRel = analyzeMuonKinematics.clone(src='isoRelMuons'  )
process.MuonKinemat4IsoRel = analyzeMuonKinematics.clone(src='isoRelMuons'  )

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
    process.leptonTrigger      +
    process.JetMult2           +
    process.MuonQuality2       +
    process.MuonKinemat2       +
    process.MuonKinemat2IsoTrk +
    process.MuonKinemat2IsoCal +
    process.MuonKinemat2IsoRel +
    process.ElecQuality2       +
    process.ElecKinemat2       +
    process.ElecKinemat2Iso
)

process.p3 = cms.Path(
    process.leptonTrigger      +
    process.JetMult3           +
    process.MuonQuality3       +
    process.MuonKinemat3       +
    process.MuonKinemat3IsoTrk +
    process.MuonKinemat3IsoCal +
    process.MuonKinemat3IsoRel +
    process.ElecQuality3       +
    process.ElecKinemat3       +
    process.ElecKinemat3Iso
)

process.p4 = cms.Path(
    process.leptonTrigger      +
    process.JetMult4           +
    process.MuonQuality4       +
    process.MuonKinemat4       +
    process.MuonKinemat4IsoTrk +
    process.MuonKinemat4IsoCal +
    process.MuonKinemat4IsoRel +
    process.ElecQuality4       +
    process.ElecKinemat4       +
    process.ElecKinemat4Iso
)
