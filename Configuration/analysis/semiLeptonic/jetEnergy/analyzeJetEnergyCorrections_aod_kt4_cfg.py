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
process.analyzeJetEnergyCorrections_raw .genJets = myGenJets
process.analyzeJetEnergyCorrections_off .genJets = myGenJets
process.analyzeJetEnergyCorrections_rel .genJets = myGenJets
process.analyzeJetEnergyCorrections_abs .genJets = myGenJets
process.analyzeJetEnergyCorrections_emf .genJets = myGenJets
process.analyzeJetEnergyCorrections_had .genJets = myGenJets
process.analyzeJetEnergyCorrections_ue  .genJets = myGenJets
process.analyzeJetEnergyCorrections_part.genJets = myGenJets

process.ttSemiLepJetPartonMatch   .maxDist = 0.4
process.ttSemiLepGenJetPartonMatch.maxDist = 0.4

process.TFileService.fileName = 'analyzeJetEnergyCorrections_kt4.root'
