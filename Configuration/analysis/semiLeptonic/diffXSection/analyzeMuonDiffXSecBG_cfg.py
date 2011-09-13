## ---
##    this configfile does the same like analyzeMuonDiffXSecCorrected_cfg.py
##    but for ttbar BG
## ---

sample="ttbar"
decayChannel = 'muon'

## change gen level event filter to ttbarBG
eventFilter='background only'
print "ttbar decay subset filter is inverted semileptonic muon decay"

## get the mother file
execfile("analyzeMuonDiffXSecCorrected_cfg.py")

#process.hltFilter.HLTPaths = ["HLT_Ele25_CaloIdVT_TrkIdT_CentralTriJet30_v*"]
#process.hltFilter.HLTPaths = ["HLT_Mu17_TriCentralJet30_v*"]

## reduce output
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

## change number of processed events
process.maxEvents.input = 100

## change output name 
process.TFileService.fileName = 'analyzeMuonDiffXSecCorr_testBkg.root'
