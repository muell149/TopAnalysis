execfile("TopAnalysis/Configuration/analysis/semiLeptonic/jetEnergy/analyzeJetEnergyCorrections_aod_template_cfg.py")

from PhysicsTools.PatAlgos.tools.jetTools import switchJetCollection
switchJetCollection(process, 
                    cms.InputTag('antikt5CaloJets'),   
                    doJTA            = True,            
                    doBTagging       = True,            
                    jetCorrLabel     = ('AK5','Calo'),  
                    doType1MET       = True,            
                    genJetCollection = cms.InputTag("antikt5GenJets")
                    )

myGenJets = "antikt5GenJets"
process.ttSemiLepGenJetPartonMatch.jets = myGenJets

process.analyzeJetEnergyGenMatch_raw .genJets = myGenJets
process.analyzeJetEnergyGenMatch_off .genJets = myGenJets
process.analyzeJetEnergyGenMatch_rel .genJets = myGenJets
process.analyzeJetEnergyGenMatch_abs .genJets = myGenJets
process.analyzeJetEnergyGenMatch_emf .genJets = myGenJets
process.analyzeJetEnergyGenMatch_had .genJets = myGenJets
process.analyzeJetEnergyGenMatch_ue  .genJets = myGenJets
process.analyzeJetEnergyGenMatch_part.genJets = myGenJets

process.analyzeJetEnergyGeom_raw .genJets = myGenJets
process.analyzeJetEnergyGeom_off .genJets = myGenJets
process.analyzeJetEnergyGeom_rel .genJets = myGenJets
process.analyzeJetEnergyGeom_abs .genJets = myGenJets
process.analyzeJetEnergyGeom_emf .genJets = myGenJets
process.analyzeJetEnergyGeom_had .genJets = myGenJets
process.analyzeJetEnergyGeom_ue  .genJets = myGenJets
process.analyzeJetEnergyGeom_part.genJets = myGenJets

process.TFileService.fileName = 'analyzeJetEnergyCorrections_ak5.root'
