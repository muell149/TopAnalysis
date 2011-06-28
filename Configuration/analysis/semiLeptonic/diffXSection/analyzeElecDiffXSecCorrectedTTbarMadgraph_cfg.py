## ---
##    this configfile does the same like analyzeMuonDiffXSecCorrected_cfg.py
##    loads file for nafJobSplitter; sets smaple to ttbar -> runAOD to false
## ---

sample="ttbar"
decayChannel = 'electron'

## get the mother file
execfile("analyzeMuonDiffXSecCorrected_cfg.py")

## choose data set
process.load("TopAnalysis/Configuration/samples/TTJets_madgraph_Summer11_cff")

process.hltFilter.HLTPaths = ["HLT_Ele25_CaloIdVT_TrkIdT_CentralTriJet30_v*"]

## reduce output
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

## change number of processed events
process.maxEvents.input = 5000

## change output name 
process.TFileService.fileName = 'analyzeElecDiffXSecCorr_testSig.root'