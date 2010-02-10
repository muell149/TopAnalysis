execfile("TopAnalysis/Configuration/analysis/semiLeptonic/jetEnergy/analyzeJetEnergyCorrections_aod_ak5_cfg.py")

process.ttSemiLeptonicFilter.invert = True

process.makeJetEnergyCorrectionsAnalysis.remove(process.makeHypGenMatch)
process.makeJetEnergyCorrectionsAnalysis.remove(process.analyzeJetEnergyGenMatch_multilevel)

process.ttSemiLepEventRaw .hypotheses.remove("ttSemiLepHypGenMatchRaw" )
process.ttSemiLepEventOff .hypotheses.remove("ttSemiLepHypGenMatchOff" )
process.ttSemiLepEventRel .hypotheses.remove("ttSemiLepHypGenMatchRel" )
process.ttSemiLepEventAbs .hypotheses.remove("ttSemiLepHypGenMatchAbs" )
process.ttSemiLepEventEmf .hypotheses.remove("ttSemiLepHypGenMatchEmf" )
process.ttSemiLepEventHad .hypotheses.remove("ttSemiLepHypGenMatchHad" )
process.ttSemiLepEventUe  .hypotheses.remove("ttSemiLepHypGenMatchUe"  )
process.ttSemiLepEventPart.hypotheses.remove("ttSemiLepHypGenMatchPart")

process.TFileService.fileName = 'analyzeJetEnergyCorrections_ak5_ttbarOther.root'
