import FWCore.ParameterSet.Config as cms

writeFullHadTree = cms.EDAnalyzer("FullHadTreeWriter",
   ## jets
   JetSrc = cms.InputTag('selectedPatJets'),
   ## kinematic fit result
   FitSrc = cms.InputTag("ttFullHadEvent"),
   ## GenEventInfoProduct for PDF uncertainties
   GenSrc = cms.InputTag("generator"),
   ## multi-jet MVA discriminator
   MultiJetMVADiscSrc = cms.InputTag("mvaDisc","DiscSel"),
   ## PU info src for MC
   PUSrc = cms.InputTag("addPileupInfo"),
   ## primary vertex info
   VertexSrc = cms.InputTag("goodOfflinePrimaryVertices"),
   ## weight from PU reweighting
   PUWeightSrc = cms.InputTag("eventWeightPU"),
   ## weight of MC sample
   MCweight = cms.double(1.),
   ## information on b-tagging
   bTagParams = cms.uint32( 12 ),
   bTagName = cms.vstring("MCPfTCHEMb"  ,"MCPfTCHEMb"  ,"MCPfTCHEMb"  ,"MCPfTCHEMb"  ,
                          "MCPfTCHEMb"  ,"MCPfTCHEMb"  ,"MCPfTCHEMb"  ,"MCPfTCHEMb"  ,
                          "MISTAGTCHEM" ,"MISTAGTCHEM" ,"MISTAGTCHEM" ,"MISTAGTCHEM" ,
                          "MCPfTCHPTb"  ,"MCPfTCHPTb"  ,"MCPfTCHPTb"  ,"MCPfTCHPTb"  ,
                          "MCPfTCHPTb"  ,"MCPfTCHPTb"  ,"MCPfTCHPTb"  ,"MCPfTCHPTb"  ,
                          "MISTAGTCHPT" ,"MISTAGTCHPT" ,"MISTAGTCHPT" ,"MISTAGTCHPT" ,
                          "MCPfSSVHEMb" ,"MCPfSSVHEMb" ,"MCPfSSVHEMb" ,"MCPfSSVHEMb" ,
                          "MCPfSSVHEMb" ,"MCPfSSVHEMb" ,"MCPfSSVHEMb" ,"MCPfSSVHEMb" ,
                          "MISTAGSSVHEM","MISTAGSSVHEM","MISTAGSSVHEM","MISTAGSSVHEM",
                          "MCPfSSVHPTb" ,"MCPfSSVHPTb" ,"MCPfSSVHPTb" ,"MCPfSSVHPTb" ,
                          "MCPfSSVHPTb" ,"MCPfSSVHPTb" ,"MCPfSSVHPTb" ,"MCPfSSVHPTb" ,
                          "MISTAGSSVHPT","MISTAGSSVHPT","MISTAGSSVHPT","MISTAGSSVHPT"),
   bTagVal  = cms.vstring("BTAGBEFF"    ,"BTAGBERR"    ,"BTAGBEFFCORR","BTAGBERRCORR",
                          "BTAGCEFF"    ,"BTAGCERR"    ,"BTAGCEFFCORR","BTAGCERRCORR",
                          "BTAGLEFF"    ,"BTAGLERR"    ,"BTAGLEFFCORR","BTAGLERRCORR",
                          "BTAGBEFF"    ,"BTAGBERR"    ,"BTAGBEFFCORR","BTAGBERRCORR",
                          "BTAGCEFF"    ,"BTAGCERR"    ,"BTAGCEFFCORR","BTAGCERRCORR",
                          "BTAGLEFF"    ,"BTAGLERR"    ,"BTAGLEFFCORR","BTAGLERRCORR",
                          "BTAGBEFF"    ,"BTAGBERR"    ,"BTAGBEFFCORR","BTAGBERRCORR",
                          "BTAGCEFF"    ,"BTAGCERR"    ,"BTAGCEFFCORR","BTAGCERRCORR",
                          "BTAGLEFF"    ,"BTAGLERR"    ,"BTAGLEFFCORR","BTAGLERRCORR",
                          "BTAGBEFF"    ,"BTAGBERR"    ,"BTAGBEFFCORR","BTAGBERRCORR",
                          "BTAGCEFF"    ,"BTAGCERR"    ,"BTAGCEFFCORR","BTAGCERRCORR",
                          "BTAGLEFF"    ,"BTAGLERR"    ,"BTAGLEFFCORR","BTAGLERRCORR"),
                                  )



