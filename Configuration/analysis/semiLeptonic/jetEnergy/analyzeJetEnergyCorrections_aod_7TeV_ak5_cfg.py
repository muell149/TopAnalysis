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

process.jetCorrFactors.corrSample = 'Summer09_7TeV'

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

process.TFileService.fileName = 'analyzeJetEnergyCorrections_7TeV_ak5.root'
