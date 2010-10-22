execfile("analyzeHTlep_cfg.py")

process.load("TopAnalysis/Configuration/samples/Run2010B_PromptReco_v2_Oct15_cff")
process.hltFilter.TriggerResultsTag = "TriggerResults::HLT"
process.hltFilter.HLTPaths = ["HLT_Mu11"]

## lumi section for synchronisation
#process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange('146644:96-146644:117')
## use HLT_Mu9 for Synchronisation
#process.hltFilter.HLTPaths = ["HLT_Mu9"]
