## ---
##    this configfile does the same like analyzeTopDiffXSec_cfg.py
##    but for electrons & data - therefore all gen-plots are thrown out 
## ---

## switch to reco plots only
## -----------------------------
## note: it is important to have
## this definitions before the
## execution of the mother file
runningOnData = "data"
eventFilter='all'
removeGenTtbar=True
## output
writeOutput = False
## extend functionality
applyKinFit = True
implement0TagPath = True
## use correct leptons
decayChannel = 'electron'
## use PF2PAT
pfToPAT = True
## no event reweighting for data!
BtagReweigthing = False
PUreweigthing = False
## use L2L3Residual correction in analyzers
corrLevel="L2L3Residual"

## get the mother file
execfile("analyzeTopDiffXSec_cfg.py")

## choose data set
process.load("TopAnalysis/Configuration/samples/Run2011A_ElectronHadPromptRecoV4_AOD_June21_cff")

## choose unprescaled trigger
process.hltFilter.TriggerResultsTag = "TriggerResults::HLT"
process.hltFilter.HLTPaths = ["HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralJet30_v*"]
# Lumi range
process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange('160404:1-999999:1')

## global tag
process.GlobalTag.globaltag = cms.string('GR_R_42_V13::All')

## reduce output
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

## change number of processed events
process.maxEvents.input = -1
process.source.skipEvents = cms.untracked.uint32(0)

## create tuples with events surviving the cuts
## for Njets>=4
if(writeOutput):
    process.out.SelectEvents = cms.untracked.PSet( SelectEvents = cms.vstring('p1') )
    process.out.fileName = cms.untracked.string('patTuple_selectedNjets4Btag2_Run2011PromptReco.root')

## change output name 
process.TFileService.fileName = 'analyzeDiffXData2011_ElectronHad_160404_166861.root'
