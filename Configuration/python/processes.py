## automatic lumi calculationlumi 
from TopAnalysis.Configuration.defines import eff
from TopAnalysis.Configuration.defines import evts
from TopAnalysis.Configuration.defines import xsec
## automatic input & size estimation
from TopAnalysis.Configuration.defines import sizes
from TopAnalysis.Configuration.defines import source

## test sample at cern
sizes ['cern'] = 0
source['cern'] = ''

## test sample at desy
sizes ['desy'] = ''
source['desy'] = ''

## /TTJets-madgraph/Fall08_IDEAL_V9_v2/GEN-SIM-RECO
from TopAnalysis.Configuration.ttbar0_reco import *
evts  ['ttbar0' ] =   1028322           ## number of produced events
xsec  ['ttbar0' ] =       414           ## NLO in pb
eff   ['ttbar0' ] =       1.0           ## generator efficiency on gen level
sizes ['ttbar0' ] = 'blocks'
source['ttbar0' ] = 'ttbar0_0,' +'ttbar0_1,' +'ttbar0_2,' +'ttbar0_3,' +'ttbar0_4,'
source['ttbar0' ]+= 'ttbar0_5,' +'ttbar0_6,' +'ttbar0_7,' +'ttbar0_8,' +'ttbar0_9,'
source['ttbar0' ]+= 'ttbar0_10,'+'ttbar0_11,'+'ttbar0_12,'+'ttbar0_13,'+'ttbar0_14,'
source['ttbar0' ]+= 'ttbar0_15,'+'ttbar0_16,'+'ttbar0_17,'+'ttbar0_18,'+'ttbar0_19,'
source['ttbar0' ]+= 'ttbar0_20,'+'ttbar0_21,'+'ttbar0_22,'+'ttbar0_23,'+'ttbar0_24,'
source['ttbar0' ]+= 'ttbar0_25,'+'ttbar0_26,'+'ttbar0_27,'+'ttbar0_28,'+'ttbar0_29,'
source['ttbar0' ]+= 'ttbar0_30,'+'ttbar0_31,'+'ttbar0_32,'+'ttbar0_33,'+'ttbar0_34,'
source['ttbar0' ]+= 'ttbar0_35,'+'ttbar0_36,'+'ttbar0_37,'+'ttbar0_38,'+'ttbar0_39,'
source['ttbar0' ]+= 'ttbar0_40,'+'ttbar0_41,'+'ttbar0_42,'+'ttbar0_43,'+'ttbar0_44,'
source['ttbar0' ]+= 'ttbar0_45,'+'ttbar0_46,'+'ttbar0_47,'+'ttbar0_48,'+'ttbar0_49,'
source['ttbar0' ]+= 'ttbar0_50,'+'ttbar0_51,'+'ttbar0_52,'+'ttbar0_53'

## /TTJets-madgraph/Fall08_IDEAL_V9_v2/GEN-SIM-RECO
from TopAnalysis.Configuration.ttbar0_pat import *
evts  ['ttbarx0'] =   1028322           ## number of produced events
xsec  ['ttbarx0'] =       414           ## NLO in pb
eff   ['ttbarx0'] =       1.0           ## generator efficiency on gen level
sizes ['ttbarx0'] = 'blocks'
source['ttbarx0'] = 'ttbarx0_0,'+'ttbarx0_1,'+'ttbarx0_2'

## /TauolaTTbar/Summer08_IDEAL_V9_v1/GEN-SIM-RECO
from TopAnalysis.Configuration.ttbar1_reco import *
evts  ['ttbar1' ] =    146996           ## number of produced events
xsec  ['ttbar1' ] =       414           ## NLO in pb
eff   ['ttbar1' ] =       1.0           ## generator efficiency on gen level
sizes ['ttbar1' ] = 'blocks'
source['ttbar1' ] = 'ttbar1_0,' +'ttbar1_1,' +'ttbar1_2,' +'ttbar1_3,' +'ttbar1_4,'
source['ttbar1' ]+= 'ttbar1_5'

## /TauolaTTbar/Summer08_IDEAL_V9_v1/GEN-SIM-DIGI-RECO
from TopAnalysis.Configuration.ttbar1_pat import *
evts  ['ttbarx1'] =    146996           ## number of produced events
xsec  ['ttbarx1'] =       414           ## NLO in pb
eff   ['ttbarx1'] =       1.0           ## generator efficiency on gen level
sizes ['ttbarx1'] = 'blocks'
source['ttbarx1'] = 'ttbarx1_0'

## new ttbar sample...
from TopAnalysis.Configuration.ttbar09_reco import *
evts  ['ttbar09'] =    529750           ## number of produced events
xsec  ['ttbar09'] =       165           ## NLO in pb
eff   ['ttbar09'] =       1.0           ## generator efficiency on gen level
sizes ['ttbar09'] = 'blocks'
source['ttbar09'] = 'ttbar09_0,' +'ttbar09_1,' +'ttbar09_2,' +'ttbar09_3,' +'ttbar09_4,'
source['ttbar09']+= 'ttbar09_5,' +'ttbar09_6,' +'ttbar09_7,' +'ttbar09_8,' +'ttbar09_9,'
source['ttbar09']+= 'ttbar09_10'


from TopAnalysis.Configuration.ttbar09_pat import *
evts  ['ttbarx09'] =    529750           ## number of produced events
xsec  ['ttbarx09'] =       165           ## NLO in pb
eff   ['ttbarx09'] =       1.0           ## generator efficiency on gen level
sizes ['ttbarx09'] = 'blocks'
source['ttbarx09'] = 'ttbarx09_0,' +'ttbarx09_1'


from TopAnalysis.Configuration.ttbar09_sig import *
evts  ['ttbary09'] =     77140           ## number of produced events
xsec  ['ttbary09'] =       165           ## NLO in pb
eff   ['ttbary09'] =       1.0           ## generator efficiency on gen level
sizes ['ttbary09'] = 'blocks'
source['ttbary09'] = 'ttbary09_0'

from TopAnalysis.Configuration.ttbar09_sel import *
evts  ['ttbarz09'] =     12664           ## number of produced events
xsec  ['ttbarz09'] =       165           ## NLO in pb
eff   ['ttbarz09'] =       1.0           ## generator efficiency on gen level
sizes ['ttbarz09'] = 'blocks'
source['ttbarz09'] = 'ttbarz09_0'

from TopAnalysis.Configuration.ttbar09_sel1 import *
evts  ['ttbarzs09']=     10833           ## number of produced events
xsec  ['ttbarzs09']=       165           ## NLO in pb
eff   ['ttbarzs09']=       1.0           ## generator efficiency on gen level
sizes ['ttbarzs09']= 'blocks'
source['ttbarzs09']= 'ttbarzs09_0'


## /InclusiveMuPt15/Summer08_IDEAL_V9_v1/GEN-SIM-RECO
from TopAnalysis.Configuration.qcd0_reco import *
evts  ['qcd0'   ] =   6238383           ## number of produced events
xsec  ['qcd0'   ] = 509100000           ## LO in pb
eff   ['qcd0'   ] =  0.000239           ## generator efficiency on gen level
sizes ['qcd0'   ] = 'blocks'
source['qcd0'   ] = 'qcd0_0,' +'qcd0_1,' +'qcd0_2,' +'qcd0_3,' +'qcd0_4,'
source['qcd0'   ]+= 'qcd0_5,' +'qcd0_6,' +'qcd0_7,' +'qcd0_8,' +'qcd0_9,'
source['qcd0'   ]+= 'qcd0_10,'+'qcd0_11,'+'qcd0_12,'+'qcd0_13,'+'qcd0_14,'
source['qcd0'   ]+= 'qcd0_15,'+'qcd0_16,'+'qcd0_17,'+'qcd0_18,'+'qcd0_19,'
source['qcd0'   ]+= 'qcd0_20,'+'qcd0_21,'+'qcd0_22,'+'qcd0_23,'+'qcd0_24,'
source['qcd0'   ]+= 'qcd0_25,'+'qcd0_26,'+'qcd0_27,'+'qcd0_28,'+'qcd0_29,'
source['qcd0'   ]+= 'qcd0_30,'+'qcd0_31,'+'qcd0_32,'+'qcd0_33,'+'qcd0_34,'
source['qcd0'   ]+= 'qcd0_35,'+'qcd0_36,'+'qcd0_37,'+'qcd0_38,'+'qcd0_39,'
source['qcd0'   ]+= 'qcd0_40,'+'qcd0_41,'+'qcd0_42,'+'qcd0_43,'+'qcd0_44,'
source['qcd0'   ]+= 'qcd0_45,'+'qcd0_46,'+'qcd0_47,'+'qcd0_48'

## /InclusiveMuPt15/Summer08_IDEAL_V9_v1/GEN-SIM-RECO
from TopAnalysis.Configuration.qcd0_pat import *
evts  ['qcdx0'  ] =   6238383           ## number of produced events
xsec  ['qcdx0'  ] = 509100000           ## LO in pb
eff   ['qcdx0'  ] =  0.000239           ## generator efficiency on gen level
sizes ['qcdx0'  ] = 'blocks'
source['qcdx0'  ] = 'qcdx0_0,' +'qcdx0_1,' +'qcdx0_2,' +'qcdx0_3,' +'qcdx0_4,'
source['qcdx0'  ]+= 'qcdx0_5,' +'qcdx0_6,' +'qcdx0_7,' +'qcdx0_8,' +'qcdx0_9,'
source['qcdx0'  ]+= 'qcdx0_10,'+'qcdx0_11,'+'qcdx0_12,'+'qcdx0_13,'+'qcdx0_14,'
source['qcdx0'  ]+= 'qcdx0_15,'+'qcdx0_16'

## /InclusiveMuPt15/Summer08_IDEAL_V11_redigi_v1/GEN-SIM-RECO
evts  ['qcd0'   ] = 1                   ## number of produced events
xsec  ['qcd0'   ] = 1                   ## LO in pb
eff   ['qcd0'   ] = 1                   ## generator efficiency on gen level
sizes ['qcd1'   ] = 0
source['qcd1'   ] = ''

## /Wjets-madgraph/Winter09_IDEAL_V11_FastSim_v1/GEN-SIM-DIGI-RECO
from TopAnalysis.Configuration.wjets0_pat import *
evts  ['wjetsx0'] = 101467739           ## number of produced events
xsec  ['wjetsx0'] =     35000           ## NLO in pb
eff   ['wjetsx0'] =       1.0           ## generator efficiency on gen level
sizes ['wjetsx0'] = 'blocks'
source['wjetsx0'] = 'wjetsx0_0,' +'wjetsx0_1,' +'wjetsx0_2,' +'wjetsx0_3,' +'wjetsx0_4,'
source['wjetsx0']+= 'wjetsx0_5,' +'wjetsx0_6,' +'wjetsx0_7,' +'wjetsx0_8,' +'wjetsx0_9,'
source['wjetsx0']+= 'wjetsx0_10,'+'wjetsx0_11,'+'wjetsx0_12,'+'wjetsx0_13,'+'wjetsx0_14,'
source['wjetsx0']+= 'wjetsx0_15,'+'wjetsx0_16,'+'wjetsx0_17,'+'wjetsx0_18,'+'wjetsx0_19,'
source['wjetsx0']+= 'wjetsx0_20,'+'wjetsx0_21,'+'wjetsx0_22,'+'wjetsx0_23,'+'wjetsx0_24,'
source['wjetsx0']+= 'wjetsx0_25,'+'wjetsx0_26,'+'wjetsx0_27,'+'wjetsx0_28,'+'wjetsx0_29,'
source['wjetsx0']+= 'wjetsx0_30,'+'wjetsx0_31,'+'wjetsx0_32,'+'wjetsx0_33,'+'wjetsx0_34,'
source['wjetsx0']+= 'wjetsx0_35,'+'wjetsx0_36,'+'wjetsx0_37,'+'wjetsx0_38,'+'wjetsx0_39,'
source['wjetsx0']+= 'wjetsx0_40,'+'wjetsx0_41,'+'wjetsx0_42,'+'wjetsx0_43,'+'wjetsx0_44'

## /WJets-madgraph/Fall08_IDEAL_V9_v1/GEN-SIM-RECO
from TopAnalysis.Configuration.wjets1_reco import *
evts  ['wjets1' ] =  10079826           ## number of produced events
xsec  ['wjets1' ] =     35000           ## NLO in pb
eff   ['wjets1' ] =       1.0           ## generator efficiency on gen level
sizes ['wjets1' ] = 'blocks'
source['wjets1' ] = 'wjets1_0,'  +'wjets1_1,'  +'wjets1_2,'  +'wjets1_3,'  +'wjets1_4,'
source['wjets1' ]+= 'wjets1_5,'  +'wjets1_6,'  +'wjets1_7,'  +'wjets1_8,'  +'wjets1_9,'
source['wjets1' ]+= 'wjets1_10,' +'wjets1_11,' +'wjets1_12,' +'wjets1_13,' +'wjets1_14,'
source['wjets1' ]+= 'wjets1_15,' +'wjets1_16,' +'wjets1_17,' +'wjets1_18,' +'wjets1_19,'
source['wjets1' ]+= 'wjets1_20,' +'wjets1_21,' +'wjets1_22,' +'wjets1_23,' +'wjets1_24,'
source['wjets1' ]+= 'wjets1_25,' +'wjets1_26,' +'wjets1_27,' +'wjets1_28,' +'wjets1_29,'
source['wjets1' ]+= 'wjets1_30,' +'wjets1_31,' +'wjets1_32,' +'wjets1_33,' +'wjets1_34,'
source['wjets1' ]+= 'wjets1_35,' +'wjets1_36,' +'wjets1_37,' +'wjets1_38,' +'wjets1_39,'
source['wjets1' ]+= 'wjets1_40,' +'wjets1_41,' +'wjets1_42,' +'wjets1_43,' +'wjets1_44,'
source['wjets1' ]+= 'wjets1_45,' +'wjets1_46,' +'wjets1_47,' +'wjets1_48,' +'wjets1_49,'
source['wjets1' ]+= 'wjets1_50,' +'wjets1_51,' +'wjets1_52,' +'wjets1_53,' +'wjets1_54,'
source['wjets1' ]+= 'wjets1_55,' +'wjets1_56,' +'wjets1_57,' +'wjets1_58,' +'wjets1_59,'
source['wjets1' ]+= 'wjets1_60,' +'wjets1_61,' +'wjets1_62,' +'wjets1_63,' +'wjets1_64,'
source['wjets1' ]+= 'wjets1_65,' +'wjets1_66,' +'wjets1_67,' +'wjets1_68,' +'wjets1_69,'
source['wjets1' ]+= 'wjets1_70,' +'wjets1_71,' +'wjets1_72,' +'wjets1_73,' +'wjets1_74,'
source['wjets1' ]+= 'wjets1_75,' +'wjets1_76,' +'wjets1_77,' +'wjets1_78,' +'wjets1_79,'
source['wjets1' ]+= 'wjets1_80,' +'wjets1_81,' +'wjets1_82,' +'wjets1_83,' +'wjets1_84,'
source['wjets1' ]+= 'wjets1_85,' +'wjets1_86,' +'wjets1_87,' +'wjets1_88,' +'wjets1_89,'
source['wjets1' ]+= 'wjets1_90,' +'wjets1_91,' +'wjets1_92,' +'wjets1_93,' +'wjets1_94,'
source['wjets1' ]+= 'wjets1_95,' +'wjets1_96,' +'wjets1_97,' +'wjets1_98,' +'wjets1_99,'
source['wjets1' ]+= 'wjets1_100,' +'wjets1_101,' +'wjets1_102,' +'wjets1_103,' +'wjets1_104,'
source['wjets1' ]+= 'wjets1_105,' +'wjets1_106,' +'wjets1_107,' +'wjets1_108,' +'wjets1_109,'
source['wjets1' ]+= 'wjets1_110,' +'wjets1_111,' +'wjets1_112,' +'wjets1_113,' +'wjets1_114,'
source['wjets1' ]+= 'wjets1_115,' +'wjets1_116,' +'wjets1_117,' +'wjets1_118'

## /WJets-madgraph/Fall08_IDEAL_V9_v1/GEN-SIM-RECO
from TopAnalysis.Configuration.wjets1_pat import *
evts  ['wjetsx1'] =  10079826           ## number of produced events
xsec  ['wjetsx1'] =     35000           ## NLO in pb
eff   ['wjetsx1'] =       1.0           ## generator efficiency on gen level
sizes ['wjetsx1'] ='blocks'
source['wjetsx1'] ='wjetsx1_0,' +'wjetsx1_1,' +'wjetsx1_2,' +'wjetsx1_3,' +'wjetsx1_4,'
source['wjetsx1']+='wjetsx1_5,' +'wjetsx1_6,' +'wjetsx1_7,' +'wjetsx1_8,' +'wjetsx1_9,'
source['wjetsx1']+='wjetsx1_10,' +'wjetsx1_11,' +'wjetsx1_12,' +'wjetsx1_13,' +'wjetsx1_14,'
source['wjetsx1']+='wjetsx1_15,' +'wjetsx1_16,' +'wjetsx1_17,' +'wjetsx1_18,' +'wjetsx1_19,'
source['wjetsx1']+='wjetsx1_20'

## /Zjets-madgraph/Winter09_IDEAL_V11_FastSim_v1/GEN-SIM-DIGI-RECO
from TopAnalysis.Configuration.zjets0_pat import *
evts  ['zjetsx0'] =   9964055           ## number of produced events
xsec  ['zjetsx0'] =      3700           ## NLO in pb
eff   ['zjetsx0'] =       1.0           ## generator efficiency on gen level
sizes ['zjetsx0'] = 'blocks'
source['zjetsx0'] = 'zjetsx0_0,'+'zjetsx0_1,'+'zjetsx0_2,'+'zjetsx0_3,'
source['zjetsx0']+= 'zjetsx0_4,'+'zjetsx0_5,'+'zjetsx0_6,'+'zjetsx0_7'

## /ZJets-madgraph/Fall08_IDEAL_V9_reco-v2/GEN-SIM-RECO
from TopAnalysis.Configuration.zjets1_reco import *
evts  ['zjets1' ] =   1163479           ## number of produced events
xsec  ['zjets1' ] =      3700           ## NLO in pb
eff   ['zjets1' ] =       1.0           ## generator efficiency on gen level
sizes ['zjets1' ] = 'blocks'
source['zjets1' ] = 'zjets1_0,'  +'zjets1_1,'  +'zjets1_2,'  +'zjets1_3,'  +'zjets1_4,'
source['zjets1' ]+= 'zjets1_5,'  +'zjets1_6,'  +'zjets1_7,'  +'zjets1_8,'  +'zjets1_9'
source['zjets1' ]+= 'zjets1_10,' +'zjets1_11,' +'zjets1_12,' +'zjets1_13,' +'zjets1_14'
source['zjets1' ]+= 'zjets1_15,' +'zjets1_16,' +'zjets1_17,' +'zjets1_18,' +'zjets1_19'
source['zjets1' ]+= 'zjets1_20,' +'zjets1_21,' +'zjets1_22,' +'zjets1_23,' +'zjets1_24'
source['zjets1' ]+= 'zjets1_25,' +'zjets1_26,' +'zjets1_27,' +'zjets1_28,' +'zjets1_29'
source['zjets1' ]+= 'zjets1_30,' +'zjets1_31'

## /ZJets-madgraph/Fall08_IDEAL_V9_reco-v2/GEN-SIM-RECO
from TopAnalysis.Configuration.zjets1_pat import *
evts  ['zjetsx1'] =   1163479           ## number of produced events
xsec  ['zjetsx1'] =      3700           ## NLO in pb
eff   ['zjetsx1'] =       1.0           ## generator efficiency on gen level
sizes ['zjetsx1'] = 'blocks'
source['zjetsx1'] = 'zjetsx1_0,'+'zjetsx1_1'

## /WW/Winter09_IDEAL_V12_FastSim_v1/GEN-SIM-DIGI-RECO
from TopAnalysis.Configuration.wwjets_pat import *
evts  ['wwx0'   ] =    200000           ## number of produced events
xsec  ['wwx0'   ] =      44.8           ## NLO in pb
eff   ['wwx0'   ] =       1.0           ## generator efficiency on gen level
sizes ['wwx0'   ] = 'blocks'
source['wwx0'   ] = 'wwx0_0'

## /WZ/Winter09_IDEAL_V12_FastSim_v1/GEN-SIM-DIGI-RECO
from TopAnalysis.Configuration.wzjets_pat import *
evts  ['wzx0'   ] =    200000           ## number of produced events
xsec  ['wzx0'   ] =      17.4           ## NLO in pb
eff   ['wzx0'   ] =       1.0           ## generator efficiency on gen level
sizes ['wzx0'   ] = 'blocks'
source['wzx0'   ] = 'wzx0_0'

## /ZZ/Winter09_IDEAL_V12_FastSim_v1/GEN-SIM-DIGI-RECO
from TopAnalysis.Configuration.zzjets_pat import *
evts  ['zzx0'   ] =    200000           ## number of produced events
xsec  ['zzx0'   ] =       7.1           ## NLO in pb
eff   ['zzx0'   ] =       1.0           ## generator efficiency on gen level
sizes ['zzx0'   ] = 'blocks'
source['zzx0'   ] = 'zzx0_0'

## /Zprime_semi_m750_w7_10TeV_GEN_RAW_HLT_CMSSW225-v3/sperries-Zprime_semi_m750_w7_10TeV_RECO_CMSSW225-v3-7194a034bc413eedae0ebe7ee022de30/USER
from TopAnalysis.Configuration.zprime0_pat import *
evts  ['zprimex0'] =        1           ## number of produced events
xsec  ['zprimex0'] =        1           ## NLO in pb
eff   ['zprimex0'] =        1           ## generator efficiency on gen level
sizes ['zprimex0'] = 'blocks'
source['zprimex0'] = 'zprimex0_0,'+'zprimex0_1,'+'zprimex0_2,'+'zprimex0_3,'+'zprimex0_4'

## semi-leptonic preselected samples
from TopAnalysis.Configuration.qcdsxs0   import *
evts  ['qcdsxs0'  ] =   6238383         ## number of produced events
xsec  ['qcdsxs0'  ] = 509100000         ## LO in pb
eff   ['qcdsxs0'  ] =  0.000239         ## generator efficiency on gen level
sizes ['qcdsxs0'  ] = 'blocks'
source['qcdsxs0'  ] = 'qcdsxs0_0,'   +'qcdsxs0_1,'   +'qcdsxs0_2,'   +'qcdsxs0_3,'   +'qcdsxs0_4,'
source['qcdsxs0'  ]+= 'qcdsxs0_5,'   +'qcdsxs0_6,'   +'qcdsxs0_7,'   +'qcdsxs0_8,'   +'qcdsxs0_9,'
source['qcdsxs0'  ]+= 'qcdsxs0_10,'  +'qcdsxs0_11,'  +'qcdsxs0_12,'  +'qcdsxs0_13,'  +'qcdsxs0_14,'
source['qcdsxs0'  ]+= 'qcdsxs0_15,'  +'qcdsxs0_16,'  +'qcdsxs0_17,'  +'qcdsxs0_18,'  +'qcdsxs0_19'


from TopAnalysis.Configuration.wjetssxs0 import *
evts  ['wjetssxs0'] = 101467739         ## number of produced events
xsec  ['wjetssxs0'] =     35000         ## NLO in pb
eff   ['wjetssxs0'] =       1.0         ## generator efficiency on gen level
sizes ['wjetssxs0'] = 'blocks'
source['wjetssxs0'] = 'wjetssxs0_0,' +'wjetssxs0_1,' +'wjetssxs0_2,' +'wjetssxs0_3,' +'wjetssxs0_4,'
source['wjetssxs0']+= 'wjetssxs0_5,' +'wjetssxs0_6,' +'wjetssxs0_7,' +'wjetssxs0_8,' +'wjetssxs0_9,'
source['wjetssxs0']+= 'wjetssxs0_10,'+'wjetssxs0_11,'+'wjetssxs0_12,'+'wjetssxs0_13,'+'wjetssxs0_14,'
source['wjetssxs0']+= 'wjetssxs0_15,'+'wjetssxs0_16,'+'wjetssxs0_17,'+'wjetssxs0_18,'+'wjetssxs0_19'

from TopAnalysis.Configuration.zjetssxs0 import *
evts  ['zjetssxs0'] =   9964055         ## number of produced events
xsec  ['zjetssxs0'] =      3700         ## NLO in pb
eff   ['zjetssxs0'] =       1.0         ## generator efficiency on gen level
sizes ['zjetssxs0'] = 'blocks'
source['zjetssxs0'] = 'zjetssxs0_0,' +'zjetssxs0_1,' +'zjetssxs0_2,' +'zjetssxs0_3,' +'zjetssxs0_4,'
source['zjetssxs0']+= 'zjetssxs0_5,' +'zjetssxs0_6,' +'zjetssxs0_7,' +'zjetssxs0_8,' +'zjetssxs0_9,'
source['zjetssxs0']+= 'zjetssxs0_10,'+'zjetssxs0_11,'+'zjetssxs0_12,'+'zjetssxs0_13,'+'zjetssxs0_14,'
source['zjetssxs0']+= 'zjetssxs0_15,'+'zjetssxs0_16,'+'zjetssxs0_17,'+'zjetssxs0_18,'+'zjetssxs0_19'

from TopAnalysis.Configuration.ttbarsxs0 import *
evts  ['ttbarsxs0'] =   1028322         ## number of produced events
xsec  ['ttbarsxs0'] =       414         ## NLO in pb
eff   ['ttbarsxs0'] =       1.0         ## generator efficiency on gen level
sizes ['ttbarsxs0'] = 'blocks'
source['ttbarsxs0'] = 'ttbarsxs0_0,' +'ttbarsxs0_1,' +'ttbarsxs0_2,' +'ttbarsxs0_3,' +'ttbarsxs0_4,'
source['ttbarsxs0']+= 'ttbarsxs0_5,' +'ttbarsxs0_6,' +'ttbarsxs0_7,' +'ttbarsxs0_8,' +'ttbarsxs0_9,'
source['ttbarsxs0']+= 'ttbarsxs0_10,'+'ttbarsxs0_11,'+'ttbarsxs0_12,'+'ttbarsxs0_13,'+'ttbarsxs0_14,'
source['ttbarsxs0']+= 'ttbarsxs0_15,'+'ttbarsxs0_16,'+'ttbarsxs0_17,'+'ttbarsxs0_18,'+'ttbarsxs0_19'

## /InclusiveMu15/Summer09-MC_31X_V3_SD_Mu9-v1/GEN-SIM-RECO (prescale 4, 1.2M events after HLT_Mu9)
from TopAnalysis.Configuration.inclMu15_SD import *
evts  ['inclMu15_SD'] =     1642742       ## number of produced events
xsec  ['inclMu15_SD'] = 509100000.0       ## NLO in pb
eff   ['inclMu15_SD'] =         1.0       ## generator efficiency on gen level
sizes ['inclMu15_SD'] = 'blocks'
source['inclMu15_SD'] = 'inclMu15_SD_0,' + 'inclMu15_SD_1,'
source['inclMu15_SD']+= 'inclMu15_SD_2,' + 'inclMu15_SD_3,'
source['inclMu15_SD']+= 'inclMu15_SD_4,' + 'inclMu15_SD_5,'
source['inclMu15_SD']+= 'inclMu15_SD_6,'

## /InclusiveMu15/Summer09-MC_31X_V3_SD_Mu9-v1/GEN-SIM-RECO
from TopAnalysis.Configuration.qcd09_pat import *
evts  ['qcd09_pat'] =     6570971         ## number of produced events
xsec  ['qcd09_pat'] = 509100000.0         ## NLO in pb
eff   ['qcd09_pat'] =         1.0         ## generator efficiency on gen level
sizes ['qcd09_pat'] = 'blocks'
source['qcd09_pat'] = 'qcd09_pat_0,'
source['qcd09_pat']+= 'qcd09_pat_1,'
source['qcd09_pat']+= 'qcd09_pat_2,'
source['qcd09_pat']+= 'qcd09_pat_3,'
source['qcd09_pat']+= 'qcd09_pat_4,'
source['qcd09_pat']+= 'qcd09_pat_5,'
source['qcd09_pat']+= 'qcd09_pat_6,'
source['qcd09_pat']+= 'qcd09_pat_7,'
source['qcd09_pat']+= 'qcd09_pat_8,'
source['qcd09_pat']+= 'qcd09_pat_9,'
source['qcd09_pat']+= 'qcd09_pat_10,'
source['qcd09_pat']+= 'qcd09_pat_11,'
source['qcd09_pat']+= 'qcd09_pat_12,'
source['qcd09_pat']+= 'qcd09_pat_13,'
source['qcd09_pat']+= 'qcd09_pat_14,'

## /Wmunu/Summer09-MC_31X_V3-v1/GEN-SIM-RECO
from TopAnalysis.Configuration.wmunu09_pat import *
evts  ['wmunu09_pat'] = 2082633           ## number of produced events
xsec  ['wmunu09_pat'] = 11840.0           ## NLO in pb
eff   ['wmunu09_pat'] =     1.0           ## generator efficiency on gen level
sizes ['wmunu09_pat'] = 'blocks'
source['wmunu09_pat'] = 'wmunu09_pat_0,'
source['wmunu09_pat']+= 'wmunu09_pat_1,'
source['wmunu09_pat']+= 'wmunu09_pat_2,'
source['wmunu09_pat']+= 'wmunu09_pat_3,'
source['wmunu09_pat']+= 'wmunu09_pat_4,'
source['wmunu09_pat']+= 'wmunu09_pat_5,' + 'wmunu09_pat_6,'

## /Zmumu/Summer09-MC_31X_V3-v1/GEN-SIM-RECO
from TopAnalysis.Configuration.zmumu09_pat import *
evts  ['zmumu09_pat'] = 2000500           ## number of produced events
xsec  ['zmumu09_pat'] =  1944.0           ## NLO in pb
eff   ['zmumu09_pat'] =     1.0           ## generator efficiency on gen level
sizes ['zmumu09_pat'] = 'blocks'
source['zmumu09_pat'] = 'zmumu09_pat_0,'
source['zmumu09_pat']+= 'zmumu09_pat_1,'
source['zmumu09_pat']+= 'zmumu09_pat_2,'
source['zmumu09_pat']+= 'zmumu09_pat_3,'
source['zmumu09_pat']+= 'zmumu09_pat_4,'
source['zmumu09_pat']+= 'zmumu09_pat_5,'
