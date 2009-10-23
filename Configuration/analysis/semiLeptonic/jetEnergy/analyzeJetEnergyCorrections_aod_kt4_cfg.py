execfile("TopAnalysis/Configuration/analysis/semiLeptonic/jetEnergy/analyzeJetEnergyCorrections_aod_template_cfg.py")

from PhysicsTools.PatAlgos.tools.jetTools import switchJetCollection
switchJetCollection(process, 
                    cms.InputTag('kt4CaloJets'),
                    doJTA            = True,            
                    doBTagging       = True,            
                    jetCorrLabel     = ('KT4','Calo'),  
                    doType1MET       = True,            
                    genJetCollection = cms.InputTag("kt4GenJets")
                    )

myGenJets = "kt4GenJets"
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

process.TFileService.fileName = 'analyzeJetEnergyCorrections_kt4.root'
