source = {}
allowedProcs = 'qcd, ttbar, wjets, zjets, dy, test'

## test
source['test' ] = '\'/store/relval/CMSSW_2_1_10/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/STARTUP_V7_v1/0001/0609A88C-F69A-DD11-AE42-001731AF6A8D.root\''

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
