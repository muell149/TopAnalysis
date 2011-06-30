jetType="PF"
dataSelector = 14
jetMinNumber = 3
jetMaxNumber = 3
leptonTypeId = 11
triggerPathSelector1 = "HLT_Ele25_CaloIdVT_TrkIdT_CentralJet30_v*"
triggerPathSelector2 = "HLT_Ele25_CaloIdVT_TrkIdT_CentralTriJet30_v*"
cutflowSelector = "effAndCutflow"
jetMinPt1 = '50'

#execfile("TopAnalysis/Configuration/analysis/fullLeptonic/analyzeZMuMuTagAndProbe_cfg.py")
execfile("analyzeCrossTriggerRatios_cfg.py")

process.load("TopAnalysis.Configuration.samples.Run2011A_ElectronHadPromptRecoV1and2combined_JsonMay13_newJEC_cff")
process.TFileService.fileName = 'analyzeCrossTriggerRatios_Ele25Jet-Ele25TriJet_JetEq3_Pt1-50.root'
process.maxEvents.input = -1
process.MessageLogger.cerr.FwkReport.reportEvery = 5000

## to dump cfg file in one big file dumping all the includes -> only in case of error with batch systems,
## otherwise comment it!!!
#file=open("analyzeCrossTriggerRatios_Ele25Jet-Ele25TriJet_JetEq3_Pt1-50_cfg_resolved.py","w")
#file.write(str(process.dumpPython()))
#file.close()