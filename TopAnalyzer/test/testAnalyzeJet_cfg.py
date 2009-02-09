import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# test cfg file for tqaflayer1 & 2 production from
# fullsim for semi-leptonic ttbar events 
#-------------------------------------------------
process = cms.Process("HH")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
#process.MessageLogger.cerr.FwkReport.reportEvery = 100

#-------------------------------------------------
# process configuration
#-------------------------------------------------

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    ## PAT test sample
    #'file:/afs/cern.ch/cms/PRS/top/cmssw-data/relval200-for-pat-testing/FullSimTTBar-2_1_X_2008-07-08_STARTUP_V4-AODSIM.100.root'
    ## RelVal sample
    #'/store/relval/CMSSW_2_1_4/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V6_v1/0004/02EC71C1-7E6C-DD11-9822-000423D944DC.root',
    #'/store/relval/CMSSW_2_1_4/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V6_v1/0004/145944C5-7E6C-DD11-AC78-001617C3B79A.root',
    #'/store/relval/CMSSW_2_1_4/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V6_v1/0004/2E1AB0F6-7E6C-DD11-9CBB-0019DB29C614.root',
    #'/store/relval/CMSSW_2_1_4/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V6_v1/0004/3E0BD034-7F6C-DD11-9882-000423D9A212.root',
    #'/store/relval/CMSSW_2_1_4/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V6_v1/0004/3E6FD0C6-7E6C-DD11-8258-001617C3B706.root',
    #'/store/relval/CMSSW_2_1_4/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V6_v1/0004/40A974C8-7E6C-DD11-A9A0-001617E30CE8.root',
    #'/store/relval/CMSSW_2_1_4/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V6_v1/0004/50F05233-7F6C-DD11-A908-000423D99EEE.root'
    ## QCD PAT-tuples: Pt15 (1589532 events, 71 files)
    '/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/047C614C-53EA-DD11-AEF1-001EC9D8B532.root',
    '/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/0660A788-40EA-DD11-83CA-001EC9D8222A.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/06C98E2E-C9E8-DD11-9216-001EC9D7F20F.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/0CA5F3AA-40EA-DD11-B2D1-001EC9D8D98F.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/122ECA6B-51EA-DD11-9343-001EC9D7FF4F.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/1AD11465-C8E8-DD11-934F-001EC9D8B16D.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/20CAAE8D-3CEA-DD11-BA6A-0030487CDA68.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/227A5ED6-CAE8-DD11-8F0F-001EC9D83141.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/24F1E2E8-C9E8-DD11-97FB-001EC9D8BDE7.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/26A41C27-CAE8-DD11-BAA9-0030487CDAC6.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/281E3DD6-4FEA-DD11-B8B3-001EC9D825CD.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/2C896EDB-4FEA-DD11-9963-001EC9D81A1E.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/3062A035-CAE8-DD11-8799-001EC9D7F1FF.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/30D57D5C-CBE8-DD11-8487-001E4F3F353A.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/32CC66C2-C9E8-DD11-BE3A-001EC9D2887E.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/34C593D7-C8E8-DD11-882C-001EC9D8B55E.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/3C26B7D2-3FEA-DD11-858B-001EC9D7F68B.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/4461F3EC-CAE8-DD11-8162-001EC9D7F20F.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/44AA826F-CAE8-DD11-AE74-001EC9D80FAE.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/4E19358A-3CEA-DD11-88C5-001EC9D81D54.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/4E51727A-C9E8-DD11-855A-001EC9D278EC.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/4E560444-C8E8-DD11-A5C5-001EC9D81A52.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/4EF468E9-50EA-DD11-8C65-00093D120E04.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/546A41A9-50EA-DD11-903A-001EC9D82BC3.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/5831880A-51EA-DD11-B659-00093D112E2A.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/5CBA9840-CAE8-DD11-AB4C-001EC9D7F21B.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/5E8C06D2-C9E8-DD11-BE6B-0030487CB568.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/6008AAE6-CAE8-DD11-860C-001EC9D81454.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/62DAC833-52EA-DD11-8278-001EC9D28288.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/64E84E53-51EA-DD11-A254-001EC9D28298.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/6A3397ED-C9E8-DD11-A9E0-001EC9D7FA2C.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/70DBFB3E-50EA-DD11-A0BF-001EC9D825B5.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/72296855-50EA-DD11-B67C-001E4F3F165E.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/761CAB6D-C8E8-DD11-B2E2-001EC9D26C2C.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/78DC2B1C-C8E8-DD11-8953-001EC9D81D54.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/78FACAB1-50EA-DD11-89F3-001EC9D81D54.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/7E2496CF-CAE8-DD11-A1E5-001EC9D7FA24.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/7E6EC777-50EA-DD11-A852-001EC9D7F65F.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/7EFCFE11-CAE8-DD11-B398-001EC9D7F663.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/8090B70D-51EA-DD11-9B90-001EC9D825B5.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/82707CB7-CAE8-DD11-91C2-001EC9D53243.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/82F9FFBD-51EA-DD11-8F93-001EC9D7F68B.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/860E9183-50EA-DD11-873E-001EC9D7F697.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/863B3E1D-CAE8-DD11-A850-001EC9D2422F.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/864E7437-51EA-DD11-A2CD-001EC9D7FA0C.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/86AA7FD6-4FEA-DD11-84B8-0030487C6A1E.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/8CAFF6CC-C9E8-DD11-8E67-001EC9D82BC3.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/8E44B65B-3DEA-DD11-AEDA-001EC9D28288.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/9A0294F8-C7E8-DD11-B6F7-001EC9D26F7D.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/9A528CFC-51EA-DD11-BBCA-001EC9D7FA28.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/9AA510F9-50EA-DD11-A590-001E4F3F165E.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/A0D5AA38-50EA-DD11-A17E-001EC9D2577D.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/AC5FDE3E-C8E8-DD11-8329-001EC9D8B992.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/AE827A3B-40EA-DD11-8481-001EC9D80AB9.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/B4758FD1-50EA-DD11-8D01-001EC9D825CD.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/B86AE390-C8E8-DD11-9FCB-0030487CDAC6.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/BA6DEEA2-C9E8-DD11-BFEF-0030487C6A2C.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/BA7E72CC-C9E8-DD11-B285-001EC9D7F1FB.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/C025ABD8-3FEA-DD11-A478-001EC9D7F21B.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/C20AF18B-CAE8-DD11-A06C-001EC9D7F68B.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/DC582342-CAE8-DD11-9E27-001EC9D81A3E.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/DCCF01EC-50EA-DD11-961A-001EC9D53243.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/E2B1BB17-51EA-DD11-91DA-001EC9D8D993.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/E2D6BAAC-51EA-DD11-8DCE-001EC9D7F213.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/E4D3C264-3DEA-DD11-B12E-001EC9D8B155.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/F818A386-CAE8-DD11-9095-001EC9D8B16D.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/F819440E-40EA-DD11-B27F-0030487CB568.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/F8EFD65A-C8E8-DD11-8162-001EC9D8A8A0.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/FAC63AD7-C8E8-DD11-BE8A-001EC9D7FA38.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/FAC730CA-CAE8-DD11-BD5E-001EC9D2BCD7.root',
    #'/store/mc/Summer08/HerwigQCDPt15/USER/IDEAL_V9_PAT_v1/0000/FE95C5D1-50EA-DD11-88F4-0030487CDAF6.root'
    ## Z+Jets PAT-tuples (1151897 events, 35 files)
    #'/store/mc/Summer08/ZJets-madgraph/USER/IDEAL_V9_PAT_v3/0000/04561ADB-38E3-DD11-AA7D-00E08178C035.root',
    #'/store/mc/Summer08/ZJets-madgraph/USER/IDEAL_V9_PAT_v3/0000/04D426DD-38E3-DD11-8EAF-00E08178C08F.root',
    #'/store/mc/Summer08/ZJets-madgraph/USER/IDEAL_V9_PAT_v3/0000/0C034BD2-38E3-DD11-9636-00E08178C119.root',
    #'/store/mc/Summer08/ZJets-madgraph/USER/IDEAL_V9_PAT_v3/0000/1402F759-5EE7-DD11-ADE5-0015170AB26C.root',
    #'/store/mc/Summer08/ZJets-madgraph/USER/IDEAL_V9_PAT_v3/0000/1CAD1093-34E3-DD11-BDEB-00E08178C02F.root',
    #'/store/mc/Summer08/ZJets-madgraph/USER/IDEAL_V9_PAT_v3/0000/1E7D9992-34E3-DD11-85F4-00E08178C069.root',
    #'/store/mc/Summer08/ZJets-madgraph/USER/IDEAL_V9_PAT_v3/0000/24C1925D-5EE7-DD11-9E7B-00151715BB94.root',
    #'/store/mc/Summer08/ZJets-madgraph/USER/IDEAL_V9_PAT_v3/0000/26F755E6-38E3-DD11-B9E0-00E08178C051.root',
    #'/store/mc/Summer08/ZJets-madgraph/USER/IDEAL_V9_PAT_v3/0000/2E06DD92-34E3-DD11-9818-00E08178C0F7.root',
    #'/store/mc/Summer08/ZJets-madgraph/USER/IDEAL_V9_PAT_v3/0000/3C75B191-34E3-DD11-8484-00E08178C0E9.root',
    #'/store/mc/Summer08/ZJets-madgraph/USER/IDEAL_V9_PAT_v3/0000/4230209E-34E3-DD11-9E5E-00E08178C0C7.root',
    #'/store/mc/Summer08/ZJets-madgraph/USER/IDEAL_V9_PAT_v3/0000/4833B2E0-38E3-DD11-8F45-00E08178C12C.root',
    #'/store/mc/Summer08/ZJets-madgraph/USER/IDEAL_V9_PAT_v3/0000/52E918E2-38E3-DD11-AFFF-00E08178C059.root',
    #'/store/mc/Summer08/ZJets-madgraph/USER/IDEAL_V9_PAT_v3/0000/5CA8F2DF-38E3-DD11-B99F-00E08178C0C1.root',
    #'/store/mc/Summer08/ZJets-madgraph/USER/IDEAL_V9_PAT_v3/0000/60FC718F-34E3-DD11-B2B2-00E08178C0EF.root',
    #'/store/mc/Summer08/ZJets-madgraph/USER/IDEAL_V9_PAT_v3/0000/62FC368B-30E3-DD11-9C44-00161725E47D.root',
    #'/store/mc/Summer08/ZJets-madgraph/USER/IDEAL_V9_PAT_v3/0000/64113AE1-38E3-DD11-A109-00E08178C01F.root',
    #'/store/mc/Summer08/ZJets-madgraph/USER/IDEAL_V9_PAT_v3/0000/6458118F-30E3-DD11-9981-0015170AC798.root',
    #'/store/mc/Summer08/ZJets-madgraph/USER/IDEAL_V9_PAT_v3/0000/70AA01E3-38E3-DD11-80FD-00E08178C183.root',
    #'/store/mc/Summer08/ZJets-madgraph/USER/IDEAL_V9_PAT_v3/0000/744CBFDE-38E3-DD11-90EF-00E08179189F.root',
    #'/store/mc/Summer08/ZJets-madgraph/USER/IDEAL_V9_PAT_v3/0000/782DE5D8-38E3-DD11-AB4A-00E08178C18F.root',
    #'/store/mc/Summer08/ZJets-madgraph/USER/IDEAL_V9_PAT_v3/0000/86386599-34E3-DD11-8C4D-00E08178C143.root',
    #'/store/mc/Summer08/ZJets-madgraph/USER/IDEAL_V9_PAT_v3/0000/8E5C339A-34E3-DD11-9D2E-00E0817918B5.root',
    #'/store/mc/Summer08/ZJets-madgraph/USER/IDEAL_V9_PAT_v3/0000/9678AA9A-34E3-DD11-98E4-00E0817917E7.root',
    #'/store/mc/Summer08/ZJets-madgraph/USER/IDEAL_V9_PAT_v3/0000/98953EE8-38E3-DD11-9096-00E08178C191.root',
    #'/store/mc/Summer08/ZJets-madgraph/USER/IDEAL_V9_PAT_v3/0000/9C2A5AB0-34E3-DD11-B1CA-00E081B08CC7.root',
    #'/store/mc/Summer08/ZJets-madgraph/USER/IDEAL_V9_PAT_v3/0000/A02D55D2-38E3-DD11-BF64-00E08179176B.root',
    #'/store/mc/Summer08/ZJets-madgraph/USER/IDEAL_V9_PAT_v3/0000/A43C7151-5EE7-DD11-9D75-0015170AC780.root',
    #'/store/mc/Summer08/ZJets-madgraph/USER/IDEAL_V9_PAT_v3/0000/AAF21A9C-34E3-DD11-BD4E-00E08178C031.root',
    #'/store/mc/Summer08/ZJets-madgraph/USER/IDEAL_V9_PAT_v3/0000/BE98449A-34E3-DD11-AE64-00E08178C157.root',
    #'/store/mc/Summer08/ZJets-madgraph/USER/IDEAL_V9_PAT_v3/0000/C07F3ADA-38E3-DD11-8066-00E08178C111.root',
    #'/store/mc/Summer08/ZJets-madgraph/USER/IDEAL_V9_PAT_v3/0000/C2A7E897-34E3-DD11-B0BF-00E08178C129.root',
    #'/store/mc/Summer08/ZJets-madgraph/USER/IDEAL_V9_PAT_v3/0000/EEB1DBD8-38E3-DD11-9DDF-00E081791815.root',
    #'/store/mc/Summer08/ZJets-madgraph/USER/IDEAL_V9_PAT_v3/0000/F6716392-34E3-DD11-94CB-00E08178C0C1.root',
    #'/store/mc/Summer08/ZJets-madgraph/USER/IDEAL_V9_PAT_v3/0000/FA80BCE0-38E3-DD11-A4FE-00E08178C093.root'
    )
)

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(False)
)

## configure geometry
process.load("Configuration.StandardSequences.Geometry_cff")

## configure conditions
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('STARTUP_V4::All')

## Magnetic field now needs to be in the high-level py
process.load("Configuration.StandardSequences.MagneticField_cff")

#-------------------------------------------------
# tqaf configuration; if you want just to produce 
# tqafLayer2 on top of an already existing
# tqafLayer1 just comment the standard tqafLayer1
# production sequence
#-------------------------------------------------

## std sequence for tqaf layer1
#process.load("TopQuarkAnalysis.TopObjectProducers.tqafLayer1_cff")

## necessary fixes to run 2.2.X on 2.1.X data
## comment this when running on samples produced
## with 22X
#from PhysicsTools.PatAlgos.tools.cmsswVersionTools import run22XonSummer08AODSIM
#run22XonSummer08AODSIM(process)

#process.p0 = cms.Path(process.tqafLayer1)

#-------------------------------------------------
# private uni Hamburg analysis code
#-------------------------------------------------

## add event weight information
from TopAnalysis.TopUtils.EventWeightPlain_cfi import *
process.eventWeight = eventWeight

# analyze jets
from TopAnalysis.TopAnalyzer.JetAnalyzer_cfi import analyzeJets
process.analyzeJets = analyzeJets

#process.analyzeAllJets = process.analyzeJets.clone()
process.analyzeSelJets = process.analyzeJets.clone()

## reconfigure
#process.analyzeAllJets.input = 'allLayer1Jets'
process.analyzeSelJets.input = 'selectedLayer1Jets'

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeJets.root')
)

process.p1 = cms.Path(process.eventWeight    *
#                      process.analyzeAllJets +
                      process.analyzeSelJets
                      )
