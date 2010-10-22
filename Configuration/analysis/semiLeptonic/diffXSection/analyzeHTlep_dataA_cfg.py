execfile("analyzeHTlep_cfg.py")

process.load("TopAnalysis/Configuration/samples/Run2010A_Sep17ReReco_v2_cff")
process.hltFilter.TriggerResultsTag = "TriggerResults::HLT"
