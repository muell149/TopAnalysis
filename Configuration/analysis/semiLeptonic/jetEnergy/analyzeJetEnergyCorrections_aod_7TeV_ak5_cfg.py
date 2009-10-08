execfile("TopAnalysis/Configuration/analysis/semiLeptonic/jetEnergy/analyzeJetEnergyCorrections_aod_template_cfg.py")

execfile("TopAnalysis/Configuration/analysis/semiLeptonic/jetEnergy/Source_7TeV_cff.py")

process.maxEvents.input = 100

from PhysicsTools.PatAlgos.tools.jetTools import switchJetCollection
switchJetCollection(process, 
                    cms.InputTag('antikt5CaloJets'),   
                    doJTA            = True,            
                    doBTagging       = True,            
                    jetCorrLabel     = ('AK5','Calo'),  
                    doType1MET       = True,            
                    genJetCollection = cms.InputTag("antikt5GenJets")
                    )

process.jetCorrFactors.L2Relative = 'Summer09_7TeV_L2Relative_AK5Calo'
process.jetCorrFactors.L3Absolute = 'Summer09_7TeV_L3Absolute_AK5Calo'

myGenJets = "antikt5GenJets"
process.ttSemiLepGenJetPartonMatch.jets = myGenJets
process.analyzeJetEnergyCorrections_raw .genJets = myGenJets
process.analyzeJetEnergyCorrections_off .genJets = myGenJets
process.analyzeJetEnergyCorrections_rel .genJets = myGenJets
process.analyzeJetEnergyCorrections_abs .genJets = myGenJets
process.analyzeJetEnergyCorrections_emf .genJets = myGenJets
process.analyzeJetEnergyCorrections_had .genJets = myGenJets
process.analyzeJetEnergyCorrections_ue  .genJets = myGenJets
process.analyzeJetEnergyCorrections_part.genJets = myGenJets

process.TFileService.fileName = 'analyzeJetEnergyCorrections_7TeV_ak5.root'
