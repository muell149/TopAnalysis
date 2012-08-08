import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/0011FD0C-AFD4-E111-B912-003048D479CC.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/005C23A9-A6D4-E111-AE40-001E67396D4C.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/06CA8FCC-C0D4-E111-8DF8-001E672CC1E7.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/08B93A9F-9DD4-E111-B139-001E67398110.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/08D27203-ACD4-E111-AC7B-001E67396C9D.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/0A50EA7D-A8D4-E111-B5A8-003048D47720.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/0EB01412-B3D4-E111-812E-003048D46018.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/1011AE47-C2D4-E111-85F7-001E67398DE5.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/182D1D44-C4D4-E111-9E7D-003048D47A42.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/18B26C71-B8D4-E111-88D9-001E673985E3.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/18BE88E1-ACD4-E111-8F3A-003048673F24.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/1E76B230-9ED4-E111-A880-003048D45FF4.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/1EF45621-AED4-E111-A4A0-001E67397698.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/244D307D-9CD4-E111-8492-001E673986A6.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/24F74D49-C2D4-E111-B8B5-001E67396A22.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/2A279C16-C1D4-E111-AFA4-001E673989DF.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/2AF4ECB7-A2D4-E111-B52D-003048D46084.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/0270C3C6-AAD4-E111-A16E-001E673984C1.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/301A052E-BBD4-E111-9D98-003048D47A28.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/306CF828-BCD4-E111-8C71-001E67398CA0.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/085D0C6B-FCD4-E111-9BED-00259020097C.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/3A55FFB4-BDD4-E111-AD22-001E673973EB.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/3C60A4EF-A3D4-E111-B1DF-001E67396793.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/2688152F-A5D4-E111-BEC8-0025B31E3C1C.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/3ED57E80-A8D4-E111-96F1-001E673986B5.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/40401B71-A9D4-E111-96C2-003048D47A46.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/406B5D03-B4D4-E111-ADFA-001E67397053.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/42C23C49-C2D4-E111-B443-001E673989DF.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/2CCED31A-AAD4-E111-9C54-001E673968A6.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/447FE949-C4D4-E111-8435-001E67396C9D.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/3269B116-C1D4-E111-877F-001E6739702B.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/4635B5C8-BCD4-E111-BBF2-001E67396A1D.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/4659DB09-AFD4-E111-B2CD-003048D477B8.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/4A9F7210-B3D4-E111-A502-001E673984C1.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/4AA3551A-B8D4-E111-A984-001E673969FF.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/3A11E9CF-B1D4-E111-AE83-003048D476F8.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/521C0775-B7D4-E111-B46F-001E67398E12.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/5285181D-B8D4-E111-BF29-001E67396707.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/5689D887-ADD4-E111-9607-001E673984C1.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/3E25FF88-C5D4-E111-98D0-001E67398052.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/5AF8E50A-AFD4-E111-8BD4-001E67397747.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/446FF795-B6D4-E111-A6E6-001E67397396.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/6469ECD5-C6D4-E111-8FF7-001E673971C5.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/6475C2FC-B3D4-E111-8AC9-001E67397035.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/44B31246-A7D4-E111-9EB4-001E6739722E.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/6CC4E389-A9D4-E111-ADC4-002481E14D46.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/4E37DE42-C4D4-E111-B25E-003048D45FCC.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/7403D82D-C0D4-E111-88AF-001E67398052.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/74CDC3EA-A7D4-E111-B797-001E673972E2.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/5A57F075-B7D4-E111-A2B4-003048D476B0.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/763FA8E3-B0D4-E111-9F09-001E673969FA.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/5E79238D-BAD4-E111-AEBF-001E673968BA.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/6A93C5F2-BED4-E111-A89E-002481E150EA.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/82589545-B5D4-E111-9D7F-001E67396C52.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/8861D892-B6D4-E111-87C3-001E67397035.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/72E49096-BFD4-E111-9C9F-002481E150F0.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/88FF39C2-AAD4-E111-AD53-001E67396793.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/7626890F-B3D4-E111-BE6E-001E67396973.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/8AE7E4B5-BDD4-E111-80E6-001E6739713E.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/8C93A352-C3D4-E111-B6D1-002590200964.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/7A1159CE-BCD4-E111-9FB0-001E673975F8.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/7E8192E0-ACD4-E111-9A6B-001E67398633.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/90ADD8EF-B9D4-E111-8DC3-001E67397391.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/8874E6B5-BDD4-E111-90BF-001E6739834A.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/94818E18-B8D4-E111-93BD-001E67398CB9.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/96534970-B8D4-E111-A603-001E6739675C.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/8A3F7747-B0D4-E111-93AE-001E67398C37.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/901F6674-B8D4-E111-8A45-001E67398C05.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/902DC8A4-C2D4-E111-A69D-0025B3E05CF2.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/9425F3FE-BED4-E111-9AA8-00259020097C.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/AC539692-BFD4-E111-B84D-001E67396A18.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/98C1751E-AAD4-E111-9411-0025B31E3CBE.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/B68803FB-B9D4-E111-AC58-001E67398683.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/9E3EA245-B0D4-E111-BA3B-001E67396644.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/BAE9F805-B9D4-E111-9A22-001E6739732D.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/BC59A00F-AFD4-E111-98CF-001E67397698.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/BC73F589-B6D4-E111-80C0-0025B3E05D34.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/BCE1902B-C0D4-E111-B40F-001E67397F71.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/A2E64AD5-9ED4-E111-A1B3-003048D460C0.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/A834C688-ADD4-E111-BF33-001E67398C87.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/C21ED3CD-C0D4-E111-A1E8-003048D476DA.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/B2825F94-BFD4-E111-AE92-001E67396653.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/C646F5B4-BDD4-E111-94A9-001E6739839A.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/B69F698C-BAD4-E111-852E-003048D462C4.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/CAA20845-B0D4-E111-BCF8-001E67397008.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/BE66A347-B5D4-E111-81D8-001E67396A40.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/C0DE3E00-BAD4-E111-83F6-0025B3E05BFC.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/CCEEBDFF-ABD4-E111-8285-003048D460D4.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/D085D875-B7D4-E111-A092-001E67397C79.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/D640C22A-BCD4-E111-9547-001E6739722E.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/D6905688-B6D4-E111-8148-003048D46102.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/D6D0E6D0-C0D4-E111-8A3E-001E673970C1.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/D6D39F2E-C0D4-E111-AC68-001E67397B25.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/C4A6558B-BAD4-E111-9CF5-001E67396D5B.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/D82FA441-C3D4-E111-B788-001E67396AC2.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/C853E685-A1D4-E111-AC28-0025B3E05E1C.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/D8C6AECF-B1D4-E111-A083-001E67396653.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/D87DD404-B9D4-E111-B25A-003048D46110.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/EA653890-B6D4-E111-BAE7-001E67396C9D.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/E29FF52D-BBD4-E111-8CA2-001E67396F9A.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/EEABED2B-BCD4-E111-A76C-001E673972DD.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/F00120A8-A6D4-E111-B6BD-001E673972E7.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/EA8A3B06-B9D4-E111-B068-0025B3E05D3E.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/F28CD12C-BBD4-E111-8F5F-001E67397021.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/F8251F17-C1D4-E111-856D-001E67397035.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/CAEB4348-B5D4-E111-8324-001E67397F26.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/FCA098B8-BDD4-E111-8AD7-001E673970C1.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/FE76ABB9-BDD4-E111-84E6-001E67397CCE.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/FE848CCB-BCD4-E111-B603-001E673968A6.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/FEDA39C1-AAD4-E111-AA79-001E673985E3.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/CC23E910-B3D4-E111-A28E-002481E14F1E.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/F0C83E00-B4D4-E111-9E06-001E67396775.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/F86C1342-C4D4-E111-9FB8-003048D45FDC.root',
       '/store/mc/Fall11/TTjets_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v2/0000/D6E450A1-C2D4-E111-8772-001E673985E3.root' ] );


secFiles.extend( [
               ] )