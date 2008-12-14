source = {}
allowedProcs = 'qcd, ttbar, wjets, zjets, dy, test'

## test at cern
source['cern' ] = '\'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/0609A88C-F69A-DD11-AE42-001731AF6A8D.root\''

## test at desy
source['desy' ] = '\'/store/relval/CMSSW_2_1_4/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V6_v1/0004/02EC71C1-7E6C-DD11-9822-000423D944DC.root\','
source['desy' ]+= '\'/store/relval/CMSSW_2_1_4/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V6_v1/0004/145944C5-7E6C-DD11-AC78-001617C3B79A.root\','
source['desy' ]+= '\'/store/relval/CMSSW_2_1_4/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V6_v1/0004/2E1AB0F6-7E6C-DD11-9CBB-0019DB29C614.root\','
source['desy' ]+= '\'/store/relval/CMSSW_2_1_4/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V6_v1/0004/3E0BD034-7F6C-DD11-9882-000423D9A212.root\','
source['desy' ]+= '\'/store/relval/CMSSW_2_1_4/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V6_v1/0004/3E6FD0C6-7E6C-DD11-8258-001617C3B706.root\','
source['desy' ]+= '\'/store/relval/CMSSW_2_1_4/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V6_v1/0004/40A974C8-7E6C-DD11-A9A0-001617E30CE8.root\','
source['desy' ]+= '\'/store/relval/CMSSW_2_1_4/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V6_v1/0004/50F05233-7F6C-DD11-A908-000423D99EEE.root\''

## madgraph samples at desy
source['madgraph' ] = '\'/store/mc/Fall08/TTJets-madgraph/GEN-SIM-RECO/IDEAL_V9_v1_pre-production/0000/249ACBCC-37BF-DD11-A191-00144F2031D4.root\','
source['madgraph' ]+= '\'/store/mc/Fall08/TTJets-madgraph/GEN-SIM-RECO/IDEAL_V9_v1_pre-production/0000/2CF2748D-6BBC-DD11-815C-001EC9DB3AD3.root\','
source['madgraph' ]+= '\'/store/mc/Fall08/TTJets-madgraph/GEN-SIM-RECO/IDEAL_V9_v1_pre-production/0000/30E599BC-66BC-DD11-B985-001E4F3DC624.root\','
source['madgraph' ]+= '\'/store/mc/Fall08/TTJets-madgraph/GEN-SIM-RECO/IDEAL_V9_v1_pre-production/0000/40313322-27BF-DD11-9773-0015C5E9C030.root\','
source['madgraph' ]+= '\'/store/mc/Fall08/TTJets-madgraph/GEN-SIM-RECO/IDEAL_V9_v1_pre-production/0000/B4AE994C-72BF-DD11-9909-001EC9DAED82.root\','
source['madgraph' ]+= '\'/store/mc/Fall08/TTJets-madgraph/GEN-SIM-RECO/IDEAL_V9_v1_pre-production/0000/EAC1080E-65BC-DD11-B8B8-001EC9DB1EF1.root\','
source['madgraph' ]+= '\'/store/mc/Fall08/TTJets-madgraph/GEN-SIM-RECO/IDEAL_V9_v1_pre-production/0000/F25A6622-27BF-DD11-AEA0-0015C5E9C186.root\''

## qcd
source['qcd'  ] = '\'file:qcd1.root\','
source['qcd'  ]+= '\'file:qcd2.root\','
source['qcd'  ]+= '\'file:qcd3.root\''

## ttbar
source['ttbar'] = '\'file:ttbar1.root\','
source['ttbar']+= '\'file:ttbar2.root\','
source['ttbar']+= '\'file:ttbar3.root\''

## wjets
source['wjets'] = '\'file:wjets1.root\','
source['wjets']+= '\'file:wjets2.root\','
source['wjets']+= '\'file:wjets3.root\''

## zjets
source['zjets'] = '\'file:zjets1.root\','
source['zjets']+= '\'file:zjets2.root\','
source['zjets']+= '\'file:zjets3.root\''

## dy
source['dy'   ] = '\'file:dy1.root\','
source['dy'   ]+= '\'file:dy2.root\','
source['dy'   ]+= '\'file:dy3.root\''
