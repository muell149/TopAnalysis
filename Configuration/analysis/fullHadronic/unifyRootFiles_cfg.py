import FWCore.ParameterSet.Config as cms

# analyse muon quantities
process = cms.Process("test")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(    
    ## add your favourite file here
     '/store/user/eschliec/Run2010/135/149/patTuple_fullHad_looseSelection_10_1.root',
     '/store/user/eschliec/Run2010/135/149/patTuple_fullHad_looseSelection_11_1.root',
     '/store/user/eschliec/Run2010/135/149/patTuple_fullHad_looseSelection_12_1.root',
     '/store/user/eschliec/Run2010/135/149/patTuple_fullHad_looseSelection_13_1.root',
     '/store/user/eschliec/Run2010/135/149/patTuple_fullHad_looseSelection_14_1.root',
     '/store/user/eschliec/Run2010/135/149/patTuple_fullHad_looseSelection_15_1.root',
     '/store/user/eschliec/Run2010/135/149/patTuple_fullHad_looseSelection_16_1.root',
     '/store/user/eschliec/Run2010/135/149/patTuple_fullHad_looseSelection_17_1.root',
     '/store/user/eschliec/Run2010/135/149/patTuple_fullHad_looseSelection_18_1.root',
     '/store/user/eschliec/Run2010/135/149/patTuple_fullHad_looseSelection_19_1.root',
     '/store/user/eschliec/Run2010/135/149/patTuple_fullHad_looseSelection_1_1.root',
     '/store/user/eschliec/Run2010/135/149/patTuple_fullHad_looseSelection_20_1.root',
     '/store/user/eschliec/Run2010/135/149/patTuple_fullHad_looseSelection_21_1.root',
     '/store/user/eschliec/Run2010/135/149/patTuple_fullHad_looseSelection_22_1.root',
     '/store/user/eschliec/Run2010/135/149/patTuple_fullHad_looseSelection_23_1.root',
     '/store/user/eschliec/Run2010/135/149/patTuple_fullHad_looseSelection_24_1.root',
     '/store/user/eschliec/Run2010/135/149/patTuple_fullHad_looseSelection_25_1.root',
     '/store/user/eschliec/Run2010/135/149/patTuple_fullHad_looseSelection_26_1.root',
     '/store/user/eschliec/Run2010/135/149/patTuple_fullHad_looseSelection_2_1.root',
     '/store/user/eschliec/Run2010/135/149/patTuple_fullHad_looseSelection_3_1.root',
     '/store/user/eschliec/Run2010/135/149/patTuple_fullHad_looseSelection_4_1.root',
     '/store/user/eschliec/Run2010/135/149/patTuple_fullHad_looseSelection_5_1.root',
     '/store/user/eschliec/Run2010/135/149/patTuple_fullHad_looseSelection_6_1.root',
     '/store/user/eschliec/Run2010/135/149/patTuple_fullHad_looseSelection_7_1.root',
     '/store/user/eschliec/Run2010/135/149/patTuple_fullHad_looseSelection_8_1.root',
     '/store/user/eschliec/Run2010/135/149/patTuple_fullHad_looseSelection_9_1.root',
     '/store/user/eschliec/Run2010/135/175/patTuple_fullHad_looseSelection_1_1.root',
     '/store/user/eschliec/Run2010/135/175/patTuple_fullHad_looseSelection_2_1.root',
     '/store/user/eschliec/Run2010/135/175/patTuple_fullHad_looseSelection_3_1.root',
     '/store/user/eschliec/Run2010/135/175/patTuple_fullHad_looseSelection_4_1.root',
     '/store/user/eschliec/Run2010/135/175/patTuple_fullHad_looseSelection_5_1.root',
     '/store/user/eschliec/Run2010/135/175/patTuple_fullHad_looseSelection_6_1.root',
     '/store/user/eschliec/Run2010/135/175/patTuple_fullHad_looseSelection_7_1.root',
     '/store/user/eschliec/Run2010/135/175/patTuple_fullHad_looseSelection_8_1.root',
     '/store/user/eschliec/Run2010/135/175/patTuple_fullHad_looseSelection_9_1.root',
     '/store/user/eschliec/Run2010/135/445/patTuple_fullHad_looseSelection_10_1.root',
     '/store/user/eschliec/Run2010/135/445/patTuple_fullHad_looseSelection_11_1.root',
     '/store/user/eschliec/Run2010/135/445/patTuple_fullHad_looseSelection_12_1.root',
     '/store/user/eschliec/Run2010/135/445/patTuple_fullHad_looseSelection_13_1.root',
     '/store/user/eschliec/Run2010/135/445/patTuple_fullHad_looseSelection_14_1.root',
     '/store/user/eschliec/Run2010/135/445/patTuple_fullHad_looseSelection_15_1.root',
     '/store/user/eschliec/Run2010/135/445/patTuple_fullHad_looseSelection_16_1.root',
     '/store/user/eschliec/Run2010/135/445/patTuple_fullHad_looseSelection_17_1.root',
     '/store/user/eschliec/Run2010/135/445/patTuple_fullHad_looseSelection_18_1.root',
     '/store/user/eschliec/Run2010/135/445/patTuple_fullHad_looseSelection_19_1.root',
     '/store/user/eschliec/Run2010/135/445/patTuple_fullHad_looseSelection_1_1.root',
     '/store/user/eschliec/Run2010/135/445/patTuple_fullHad_looseSelection_20_1.root',
     '/store/user/eschliec/Run2010/135/445/patTuple_fullHad_looseSelection_21_1.root',
     '/store/user/eschliec/Run2010/135/445/patTuple_fullHad_looseSelection_22_1.root',
     '/store/user/eschliec/Run2010/135/445/patTuple_fullHad_looseSelection_23_1.root',
     '/store/user/eschliec/Run2010/135/445/patTuple_fullHad_looseSelection_24_1.root',
     '/store/user/eschliec/Run2010/135/445/patTuple_fullHad_looseSelection_25_1.root',
     '/store/user/eschliec/Run2010/135/445/patTuple_fullHad_looseSelection_26_1.root',
     '/store/user/eschliec/Run2010/135/445/patTuple_fullHad_looseSelection_27_1.root',
     '/store/user/eschliec/Run2010/135/445/patTuple_fullHad_looseSelection_28_1.root',
     '/store/user/eschliec/Run2010/135/445/patTuple_fullHad_looseSelection_29_1.root',
     '/store/user/eschliec/Run2010/135/445/patTuple_fullHad_looseSelection_2_1.root',
     '/store/user/eschliec/Run2010/135/445/patTuple_fullHad_looseSelection_3_1.root',
     '/store/user/eschliec/Run2010/135/445/patTuple_fullHad_looseSelection_4_1.root',
     '/store/user/eschliec/Run2010/135/445/patTuple_fullHad_looseSelection_5_1.root',
     '/store/user/eschliec/Run2010/135/445/patTuple_fullHad_looseSelection_6_1.root',
     '/store/user/eschliec/Run2010/135/445/patTuple_fullHad_looseSelection_7_1.root',
     '/store/user/eschliec/Run2010/135/445/patTuple_fullHad_looseSelection_8_1.root',
     '/store/user/eschliec/Run2010/135/445/patTuple_fullHad_looseSelection_9_1.root',
     '/store/user/eschliec/Run2010/135/521/patTuple_fullHad_looseSelection_1_1.root',
     '/store/user/eschliec/Run2010/135/521/patTuple_fullHad_looseSelection_2_1.root',
     '/store/user/eschliec/Run2010/135/521/patTuple_fullHad_looseSelection_3_1.root',
     '/store/user/eschliec/Run2010/135/523/patTuple_fullHad_looseSelection_2_1.root',
     '/store/user/eschliec/Run2010/135/525/patTuple_fullHad_looseSelection_1_1.root',
     '/store/user/eschliec/Run2010/135/525/patTuple_fullHad_looseSelection_2_1.root',
     '/store/user/eschliec/Run2010/135/525/patTuple_fullHad_looseSelection_3_1.root',
     '/store/user/eschliec/Run2010/135/528/patTuple_fullHad_looseSelection_1_1.root',
     '/store/user/eschliec/Run2010/135/528/patTuple_fullHad_looseSelection_2_1.root',
     '/store/user/eschliec/Run2010/135/528/patTuple_fullHad_looseSelection_3_1.root',
     '/store/user/eschliec/Run2010/135/528/patTuple_fullHad_looseSelection_4_1.root',
     '/store/user/eschliec/Run2010/135/528/patTuple_fullHad_looseSelection_5_1.root',
     '/store/user/eschliec/Run2010/135/528/patTuple_fullHad_looseSelection_6_1.root',
     '/store/user/eschliec/Run2010/135/528/patTuple_fullHad_looseSelection_7_1.root',
     '/store/user/eschliec/Run2010/135/528/patTuple_fullHad_looseSelection_8_1.root',
     '/store/user/eschliec/Run2010/135/534/patTuple_fullHad_looseSelection_1_1.root',
     '/store/user/eschliec/Run2010/135/535/patTuple_fullHad_looseSelection_1_1.root',
     '/store/user/eschliec/Run2010/135/535/patTuple_fullHad_looseSelection_2_1.root',
     '/store/user/eschliec/Run2010/135/575/patTuple_fullHad_looseSelection_1_1.root',
     '/store/user/eschliec/Run2010/135/575/patTuple_fullHad_looseSelection_2_1.root',
     '/store/user/eschliec/Run2010/135/575/patTuple_fullHad_looseSelection_3_1.root',
     '/store/user/eschliec/Run2010/135/575/patTuple_fullHad_looseSelection_4_1.root',
     '/store/user/eschliec/Run2010/135/575/patTuple_fullHad_looseSelection_5_1.root',
     '/store/user/eschliec/Run2010/135/735/patTuple_fullHad_looseSelection_1_1.root',
     '/store/user/eschliec/Run2010/136/033/patTuple_fullHad_looseSelection_1_1.root',
     '/store/user/eschliec/Run2010/136/035/patTuple_fullHad_looseSelection_1_1.root',
     '/store/user/eschliec/Run2010/136/066/patTuple_fullHad_looseSelection_1_1.root',
     '/store/user/eschliec/Run2010/136/080/patTuple_fullHad_looseSelection_1_1.root',
     '/store/user/eschliec/Run2010/136/082/patTuple_fullHad_looseSelection_1_1.root',
     '/store/user/eschliec/Run2010/136/087/patTuple_fullHad_looseSelection_1_1.root',
     '/store/user/eschliec/Run2010/136/088/patTuple_fullHad_looseSelection_1_1.root',
     '/store/user/eschliec/Run2010/136/097/patTuple_fullHad_looseSelection_1_1.root',
     '/store/user/eschliec/Run2010/136/098/patTuple_fullHad_looseSelection_1_1.root',
     '/store/user/eschliec/Run2010/136/100/patTuple_fullHad_looseSelection_1_1.root',
     '/store/user/eschliec/Run2010/136/119/patTuple_fullHad_looseSelection_1_1.root',
     '/store/user/eschliec/Run2010/136/294/patTuple_fullHad_looseSelection_1_1.root',
     '/store/user/eschliec/Run2010/136/297/patTuple_fullHad_looseSelection_1_1.root',
     '/store/user/eschliec/Run2010/137/027/patTuple_fullHad_looseSelection_1_1.root',
     '/store/user/eschliec/Run2010/137/028/patTuple_fullHad_looseSelection_1_1.root'
    )
)

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

## Output Module Configuration
process.out = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string('patTuple_selected.root'),
                               # save only events passing the full path
                               #SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p1') ),
                               # save output (comment to keep everything...)
                               #outputCommands = cms.untracked.vstring('drop *',) 
                               )
process.outpath = cms.EndPath(process.out)
