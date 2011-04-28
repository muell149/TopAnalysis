import FWCore.ParameterSet.Config as cms

writeFullHadTree = cms.EDAnalyzer("FullHadTreeWriter",
   ## jets
   JetSrc = cms.InputTag('selectedPatJets'),
   ## kinematic fit result
   FitSrc = cms.InputTag("ttFullHadEvent"),
   ## GenEventInfoProduct for PDF uncertainties
   GenSrc = cms.InputTag("generator"),
   ## information on b-tagging
   bTagParams = cms.uint32( 8 ),
   bTagName = cms.vstring("MCPfTCHEMb"  ,"MCPfTCHEMb"  ,"MCPfTCHEMb"  ,"MCPfTCHEMb"  ,
                          "MISTAGTCHEM" ,"MISTAGTCHEM" ,"MISTAGTCHEM" ,"MISTAGTCHEM" ,
                          "MCPfTCHPTb"  ,"MCPfTCHPTb"  ,"MCPfTCHPTb"  ,"MCPfTCHPTb"  ,
                          "MISTAGTCHPT" ,"MISTAGTCHPT" ,"MISTAGTCHPT" ,"MISTAGTCHPT" ,
                          "MCPfSSVHEMb" ,"MCPfSSVHEMb" ,"MCPfSSVHEMb" ,"MCPfSSVHEMb" ,
                          "MISTAGSSVHEM","MISTAGSSVHEM","MISTAGSSVHEM","MISTAGSSVHEM",
                          "MCPfSSVHPTb" ,"MCPfSSVHPTb" ,"MCPfSSVHPTb" ,"MCPfSSVHPTb" ,
                          "MISTAGSSVHPT","MISTAGSSVHPT","MISTAGSSVHPT","MISTAGSSVHPT"),
   bTagVal  = cms.vstring("BTAGBEFF"    ,"BTAGBERR"    ,"BTAGBEFFCORR","BTAGBERRCORR",
                          "BTAGLEFF"    ,"BTAGLERR"    ,"BTAGLEFFCORR","BTAGLERRCORR",
                          "BTAGBEFF"    ,"BTAGBERR"    ,"BTAGBEFFCORR","BTAGBERRCORR",
                          "BTAGLEFF"    ,"BTAGLERR"    ,"BTAGLEFFCORR","BTAGLERRCORR",
                          "BTAGBEFF"    ,"BTAGBERR"    ,"BTAGBEFFCORR","BTAGBERRCORR",
                          "BTAGLEFF"    ,"BTAGLERR"    ,"BTAGLEFFCORR","BTAGLERRCORR",
                          "BTAGBEFF"    ,"BTAGBERR"    ,"BTAGBEFFCORR","BTAGBERRCORR",
                          "BTAGLEFF"    ,"BTAGLERR"    ,"BTAGLEFFCORR","BTAGLERRCORR"),
                                  )



