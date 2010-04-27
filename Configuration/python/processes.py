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

## new ttbar sample...
from TopAnalysis.Configuration.ttbar09_reco import *
evts  ['ttbar09'] =    529750           ## number of produced events
#xsec  ['ttbar09'] =       165           ## LO(?) in pb from configfile
xsec  ['ttbar09'] =       414           ## NLO in pb from https://twiki.cern.ch/twiki/bin/view/CMS/CrossSections_3XSeries
eff   ['ttbar09'] =       1.0           ## generator efficiency on gen level
sizes ['ttbar09'] = 'blocks'
source['ttbar09'] = 'ttbar09_0,' +'ttbar09_1,' +'ttbar09_2,' +'ttbar09_3,' +'ttbar09_4,'
source['ttbar09']+= 'ttbar09_5,' +'ttbar09_6,' +'ttbar09_7,' +'ttbar09_8,' +'ttbar09_9,'
source['ttbar09']+= 'ttbar09_10'


from TopAnalysis.Configuration.ttbar09_pat import *
evts  ['ttbarx09'] =    529750           ## number of produced events
#xsec  ['ttbarx09'] =       165           ## LO(?) in pb from configfile
xsec  ['ttbarx09'] =       414           ## NLO in pb from https://twiki.cern.ch/twiki/bin/view/CMS/CrossSections_3XSeries
eff   ['ttbarx09'] =       1.0           ## generator efficiency on gen level
sizes ['ttbarx09'] = 'blocks'
source['ttbarx09'] = 'ttbarx09_0,' +'ttbarx09_1'


from TopAnalysis.Configuration.ttbar09_sig import *
evts  ['ttbary09'] =     77140           ## number of produced events
#xsec  ['ttbary09'] =       165           ## LO(?) in pb from configfile
xsec  ['ttbary09'] =       414           ## NLO in pb from https://twiki.cern.ch/twiki/bin/view/CMS/CrossSections_3XSeries
eff   ['ttbary09'] =       1.0           ## generator efficiency on gen level
sizes ['ttbary09'] = 'blocks'
source['ttbary09'] = 'ttbary09_0'

from TopAnalysis.Configuration.ttbar09_sel import *
evts  ['ttbarz09'] =     12664           ## number of produced events
#xsec  ['ttbarz09'] =       165           ## LO(?) in pb from configfile
xsec  ['ttbarz09'] =       414           ## NLO in pb from https://twiki.cern.ch/twiki/bin/view/CMS/CrossSections_3XSeries
eff   ['ttbarz09'] =       1.0           ## generator efficiency on gen level
sizes ['ttbarz09'] = 'blocks'
source['ttbarz09'] = 'ttbarz09_0'

from TopAnalysis.Configuration.ttbar09_sel1 import *
evts  ['ttbarzs09']=     10833           ## number of produced events
#xsec  ['ttbarsz09'] =       165           ## LO(?) in pb from configfile
xsec  ['ttbarzs09']=       414           ## NLO in pb from https://twiki.cern.ch/twiki/bin/view/CMS/CrossSections_3XSeries
eff   ['ttbarzs09']=       1.0           ## generator efficiency on gen level
sizes ['ttbarzs09']= 'blocks'
source['ttbarzs09']= 'ttbarzs09_0'

from TopAnalysis.Configuration.inclMu15_SD import *
evts  ['inclMu15_SD'] =     1642742       ## number of produced events
xsec  ['inclMu15_SD'] = 509100000.0       ## NLO in pb from configfile
eff   ['inclMu15_SD'] =         1.0       ## generator efficiency on gen level
sizes ['inclMu15_SD'] = 'blocks'
source['inclMu15_SD'] = 'inclMu15_SD_0,' + 'inclMu15_SD_1,'
source['inclMu15_SD']+= 'inclMu15_SD_2,' + 'inclMu15_SD_3,'
source['inclMu15_SD']+= 'inclMu15_SD_4,' + 'inclMu15_SD_5,'
source['inclMu15_SD']+= 'inclMu15_SD_6'

## /InclusiveMu15/Summer09-MC_31X_V3_SD_Mu9-v1/GEN-SIM-RECO
from TopAnalysis.Configuration.qcd09_pat import *
evts  ['qcd09_pat'] =     6570971         ## number of produced events
xsec  ['qcd09_pat'] = 509100000.0         ## NLO in pb from configfile
eff   ['qcd09_pat'] =         0.0002881   ## generator efficiency on gen level
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
source['qcd09_pat']+= 'qcd09_pat_14'

## /Wmunu/Summer09-MC_31X_V3-v1/GEN-SIM-RECO
from TopAnalysis.Configuration.wmunu09_pat import *
evts  ['wmunu09_pat'] = 2082633           ## number of produced events
#xsec  ['wmunu09_pat'] = 11840.0          ## NLO in pb from configfile
xsec  ['wmunu09_pat'] = 13333             ## LO in pb from https://twiki.cern.ch/twiki/bin/view/CMS/CrossSections_3XSeries
eff   ['wmunu09_pat'] =   0.691           ## generator efficiency on gen level
sizes ['wmunu09_pat'] = 'blocks'
source['wmunu09_pat'] = 'wmunu09_pat_0,'
source['wmunu09_pat']+= 'wmunu09_pat_1,'
source['wmunu09_pat']+= 'wmunu09_pat_2,'
source['wmunu09_pat']+= 'wmunu09_pat_3,'
source['wmunu09_pat']+= 'wmunu09_pat_4,'
source['wmunu09_pat']+= 'wmunu09_pat_5,' + 'wmunu09_pat_6'

## /Zmumu/Summer09-MC_31X_V3-v1/GEN-SIM-RECO
from TopAnalysis.Configuration.zmumu09_pat import *
evts  ['zmumu09_pat'] = 2000500           ## number of produced events
#xsec  ['zmumu09_pat'] =  1944.0          ## NLO in pb from configfile
xsec  ['zmumu09_pat'] =  1833.0           ## LO in pb from https://twiki.cern.ch/twiki/bin/view/CMS/CrossSections_3XSeries
eff   ['zmumu09_pat'] =     1.0           ## generator efficiency on gen level
sizes ['zmumu09_pat'] = 'blocks'
source['zmumu09_pat'] = 'zmumu09_pat_0,'
source['zmumu09_pat']+= 'zmumu09_pat_1,'
source['zmumu09_pat']+= 'zmumu09_pat_2,'
source['zmumu09_pat']+= 'zmumu09_pat_3,'
source['zmumu09_pat']+= 'zmumu09_pat_4,'
source['zmumu09_pat']+= 'zmumu09_pat_5'

## /TTbar/Summer09-MC_31X_V3_7TeV-v1/GEN-SIM-RECO
from TopAnalysis.Configuration.ttbar09_pat7 import *
evts  ['ttbarx09_7'] =  626610           ## number of produced events
xsec  ['ttbarx09_7'] =    94.3           ## NLO in pb from configfile
eff   ['ttbarx09_7'] =     1.0           ## generator efficiency on gen level
sizes ['ttbarx09_7'] = 'blocks'
source['ttbarx09_7'] = 'ttbarx09_7_0,' + 'ttbarx09_7_1,'
source['ttbarx09_7']+= 'ttbarx09_7_2,' + 'ttbarx09_7_3,'
source['ttbarx09_7']+= 'ttbarx09_7_4,' + 'ttbarx09_7_5,'
source['ttbarx09_7']+= 'ttbarx09_7_6,' + 'ttbarx09_7_7'

from TopAnalysis.Configuration.ttbar09_sig7 import *
evts  ['ttbarsig09_7'] =   91752           ## number of produced events
xsec  ['ttbarsig09_7'] =    94.3           ## NLO in pb from configfile
eff   ['ttbarsig09_7'] =     1.0           ## generator efficiency on gen level
sizes ['ttbarsig09_7'] = 'blocks'
source['ttbarsig09_7'] = 'ttbarsig09_7_0'

## /TTbarJets-madgraph/Summer09-MC_31X_V3-v2/GEN-SIM-RECO
from TopAnalysis.Configuration.ttbar09_patMad import *
evts  ['ttbarx09_mad'] =  1075985          ## number of produced events
xsec  ['ttbarx09_mad'] =      414          ## NLO in pb from https://twiki.cern.ch/twiki/bin/view/CMS/CrossSections_3XSeries
eff   ['ttbarx09_mad'] =      1.0          ## generator efficiency on gen level
sizes ['ttbarx09_mad'] = 'blocks'
source['ttbarx09_mad'] = 'ttbarx09_mad_0,' + 'ttbarx09_mad_1,'
source['ttbarx09_mad']+= 'ttbarx09_mad_2,' + 'ttbarx09_mad_3,'
source['ttbarx09_mad']+= 'ttbarx09_mad_4,' + 'ttbarx09_mad_5'

## /TTbar-mcatnlo/Summer09-MC_31X_V3-v1/GEN-SIM-RECO
from TopAnalysis.Configuration.ttbar09_patNLO import *
evts  ['ttbarx09_nlo'] =   994573          ## number of produced events
xsec  ['ttbarx09_nlo'] =      414          ## NLO in pb from https://twiki.cern.ch/twiki/bin/view/CMS/CrossSections_3XSeries
eff   ['ttbarx09_nlo'] =      1.0          ## generator efficiency on gen level
sizes ['ttbarx09_nlo'] = 'blocks'
source['ttbarx09_nlo'] = 'ttbarx09_nlo_0,' + 'ttbarx09_nlo_1,'
source['ttbarx09_nlo']+= 'ttbarx09_nlo_2'

## /TTbarJets-madgraph/Summer09-MC_31X_V3_7TeV-v2/GEN-SIM-RECO
from TopAnalysis.Configuration.ttbar09_patMad7 import *
evts  ['ttbarx09_mad7'] =  1062730         ## number of produced events
xsec  ['ttbarx09_mad7'] =      187         ## NLO in pb from https://twiki.cern.ch/twiki/bin/view/CMS/CrossSections_3XSeries
eff   ['ttbarx09_mad7'] =      1.0         ## generator efficiency on gen level
sizes ['ttbarx09_mad7'] = 'blocks'
source['ttbarx09_mad7'] = 'ttbarx09_mad7_0,' + 'ttbarx09_mad7_1,'
source['ttbarx09_mad7']+= 'ttbarx09_mad7_2,' + 'ttbarx09_mad7_3,'
source['ttbarx09_mad7']+= 'ttbarx09_mad7_4,' + 'ttbarx09_mad7_5'

## /TTbar-mcatnlo/Summer09-MC_31X_V3_7TeV-v2/GEN-SIM-RECO
from TopAnalysis.Configuration.ttbar09_patNLO7 import *
evts  ['ttbarx09_nlo7'] =   993455         ## number of produced events
xsec  ['ttbarx09_nlo7'] =      187         ## NLO in pb from https://twiki.cern.ch/twiki/bin/view/CMS/CrossSections_3XSeries
eff   ['ttbarx09_nlo7'] =      1.0         ## generator efficiency on gen level
sizes ['ttbarx09_nlo7'] = 'blocks'
source['ttbarx09_nlo7'] = 'ttbarx09_nlo7_0,' + 'ttbarx09_nlo7_1,'
source['ttbarx09_nlo7']+= 'ttbarx09_nlo7_2'

## /TTbar-mcatnlo/Summer09-MC_31X_V3_7TeV-v2/GEN-SIM-RECO
from TopAnalysis.Configuration.ttbar09_NLO7_pat import *
evts  ['ttbar09_NLO7_pat'] =   993455  ## number of produced events
xsec  ['ttbar09_NLO7_pat'] =      165  ## NLO in pb from https://twiki.cern.ch/twiki/bin/view/CMS/CrossSections_3XSeries
eff   ['ttbar09_NLO7_pat'] =      1.0  ## generator efficiency on gen level
sizes ['ttbar09_NLO7_pat'] = 'blocks'
source['ttbar09_NLO7_pat'] = 'ttbar09_NLO7_pat_0,' + 'ttbar09_NLO7_pat_1,' + 'ttbar09_NLO7_pat_2'

## /TTbar/Summer09-MC_31X_V3_7TeV-v1/GEN-SIM-RECO
from TopAnalysis.Configuration.ttbar09_PYT7_pat import *
evts  ['ttbar09_PYT7_pat'] =   626610  ## number of produced events
xsec  ['ttbar09_PYT7_pat'] =      165  ## NLO in pb from https://twiki.cern.ch/twiki/bin/view/CMS/CrossSections_3XSeries
eff   ['ttbar09_PYT7_pat'] =      1.0  ## generator efficiency on gen level
sizes ['ttbar09_PYT7_pat'] = 'blocks'
source['ttbar09_PYT7_pat'] = 'ttbar09_PYT7_pat_0,' + 'ttbar09_PYT7_pat_1,' + 'ttbar09_PYT7_pat_2,' + 'ttbar09_PYT7_pat_3,' + 'ttbar09_PYT7_pat_4,' + 'ttbar09_PYT7_pat_5,'
source['ttbar09_PYT7_pat']+= 'ttbar09_PYT7_pat_6,' + 'ttbar09_PYT7_pat_7,' + 'ttbar09_PYT7_pat_8,' + 'ttbar09_PYT7_pat_9,' + 'ttbar09_PYT7_pat_10,' + 'ttbar09_PYT7_pat_11,'
source['ttbar09_PYT7_pat']+= 'ttbar09_PYT7_pat_12,' + 'ttbar09_PYT7_pat_13,' + 'ttbar09_PYT7_pat_14,' + 'ttbar09_PYT7_pat_15,' + 'ttbar09_PYT7_pat_16'

## /WJets-madgraph/Summer09-MC_31X_V3-v1/GEN-SIM-RECO
from TopAnalysis.Configuration.wjets09_patMad import *
evts  ['wjets09_pat'] = 11024540       ## number of produced events
xsec  ['wjets09_pat'] =        1       ## NLO in pb from configfile
eff   ['wjets09_pat'] =      1.0       ## generator efficiency on gen level
sizes ['wjets09_pat'] = 'blocks'
source['wjets09_pat'] = 'wjets09_pat_0,' + 'wjets09_pat_1,'
source['wjets09_pat']+= 'wjets09_pat_2,' + 'wjets09_pat_3,'
source['wjets09_pat']+= 'wjets09_pat_4,' + 'wjets09_pat_5,'
source['wjets09_pat']+= 'wjets09_pat_6,' + 'wjets09_pat_7,'
source['wjets09_pat']+= 'wjets09_pat_8,' + 'wjets09_pat_9,'
source['wjets09_pat']+= 'wjets09_pat_10,' + 'wjets09_pat_11,'
source['wjets09_pat']+= 'wjets09_pat_12,' + 'wjets09_pat_13,'
source['wjets09_pat']+= 'wjets09_pat_14,' + 'wjets09_pat_15,'
source['wjets09_pat']+= 'wjets09_pat_16,' + 'wjets09_pat_17,'
source['wjets09_pat']+= 'wjets09_pat_18,' + 'wjets09_pat_19,'
source['wjets09_pat']+= 'wjets09_pat_20,' + 'wjets09_pat_21,'
source['wjets09_pat']+= 'wjets09_pat_22'

## /WJets-madgraph/Summer09-MC_31X_V3_7TeV-v1/GEN-SIM-RECO
from TopAnalysis.Configuration.wjets09_patMad7 import *
evts  ['wjets09_pat7'] = 11377412       ## number of produced events
xsec  ['wjets09_pat7'] =        1       ## NLO in pb from configfile
eff   ['wjets09_pat7'] =      1.0       ## generator efficiency on gen level
sizes ['wjets09_pat7'] = 'blocks'
source['wjets09_pat7'] = 'wjets09_pat7_0,' + 'wjets09_pat7_1,'
source['wjets09_pat7']+= 'wjets09_pat7_2,' + 'wjets09_pat7_3,'
source['wjets09_pat7']+= 'wjets09_pat7_4,' + 'wjets09_pat7_5,'
source['wjets09_pat7']+= 'wjets09_pat7_6,' + 'wjets09_pat7_7,'
source['wjets09_pat7']+= 'wjets09_pat7_8,' + 'wjets09_pat7_9,'
source['wjets09_pat7']+= 'wjets09_pat7_10,' + 'wjets09_pat7_11,'
source['wjets09_pat7']+= 'wjets09_pat7_12,' + 'wjets09_pat7_13,'
source['wjets09_pat7']+= 'wjets09_pat7_14,' + 'wjets09_pat7_15,'
source['wjets09_pat7']+= 'wjets09_pat7_16,' + 'wjets09_pat7_17,'
source['wjets09_pat7']+= 'wjets09_pat7_18,' + 'wjets09_pat7_19,'
source['wjets09_pat7']+= 'wjets09_pat7_20,' + 'wjets09_pat7_21,'
source['wjets09_pat7']+= 'wjets09_pat7_22,' + 'wjets09_pat7_23,'
source['wjets09_pat7']+= 'wjets09_pat7_24,' + 'wjets09_pat7_25,'
source['wjets09_pat7']+= 'wjets09_pat7_26,' + 'wjets09_pat7_27,'
source['wjets09_pat7']+= 'wjets09_pat7_28,' + 'wjets09_pat7_29,'
source['wjets09_pat7']+= 'wjets09_pat7_30,' + 'wjets09_pat7_31,'
source['wjets09_pat7']+= 'wjets09_pat7_32,' + 'wjets09_pat7_33,'
source['wjets09_pat7']+= 'wjets09_pat7_34,' + 'wjets09_pat7_35,'
source['wjets09_pat7']+= 'wjets09_pat7_36,' + 'wjets09_pat7_37,'
source['wjets09_pat7']+= 'wjets09_pat7_38,' + 'wjets09_pat7_39,'
source['wjets09_pat7']+= 'wjets09_pat7_40,' + 'wjets09_pat7_41,'
source['wjets09_pat7']+= 'wjets09_pat7_42,' + 'wjets09_pat7_43,'
source['wjets09_pat7']+= 'wjets09_pat7_44,' + 'wjets09_pat7_45'

## /ZJets-madgraph/Summer09-MC_31X_V3-v1/GEN-SIM-RECO
from TopAnalysis.Configuration.zjets09_patMad import *
evts  ['zjets09_pat'] =   932532       ## number of produced events
xsec  ['zjets09_pat'] =        1       ## NLO in pb from configfile
eff   ['zjets09_pat'] =      1.0       ## generator efficiency on gen level
sizes ['zjets09_pat'] = 'blocks'
source['zjets09_pat'] = 'zjets09_pat_0,' + 'zjets09_pat_1,'
source['zjets09_pat']+= 'zjets09_pat_2,' + 'zjets09_pat_3,'
source['zjets09_pat']+= 'zjets09_pat_4,' + 'zjets09_pat_5'

## /ZJets-madgraph/Summer09-MC_31X_V3_7TeV-v2/GEN-SIM-RECO
from TopAnalysis.Configuration.zjets09_patMad7 import *
evts  ['zjets09_pat7'] =  1068735       ## number of produced events
xsec  ['zjets09_pat7'] =        1       ## NLO in pb from configfile
eff   ['zjets09_pat7'] =      1.0       ## generator efficiency on gen level
sizes ['zjets09_pat7'] = 'blocks'
source['zjets09_pat7'] = 'zjets09_pat7_0,' + 'zjets09_pat7_1,'
source['zjets09_pat7']+= 'zjets09_pat7_2,' + 'zjets09_pat7_3,'
source['zjets09_pat7']+= 'zjets09_pat7_4,' + 'zjets09_pat7_5'

## /Wmunu/Summer09-MC_31X_V3_7TeV-v1/GEN-SIM-RECO
from TopAnalysis.Configuration.wmunu09_pat7 import *
evts  ['wmunu09_pat7'] =  2073721       ## number of produced events
xsec  ['wmunu09_pat7'] =     7899       ## NLO in pb from configfile
eff   ['wmunu09_pat7'] =    0.742       ## generator efficiency on gen level
sizes ['wmunu09_pat7'] = 'blocks'
source['wmunu09_pat7'] = 'wmunu09_pat7_0,' + 'wmunu09_pat7_1,'
source['wmunu09_pat7']+= 'wmunu09_pat7_2,' + 'wmunu09_pat7_3,'
source['wmunu09_pat7']+= 'wmunu09_pat7_4,' + 'wmunu09_pat7_5,'
source['wmunu09_pat7']+= 'wmunu09_pat7_6,' + 'wmunu09_pat7_7,'
source['wmunu09_pat7']+= 'wmunu09_pat7_8,' + 'wmunu09_pat7_9'

## /Zmumu/Summer09-MC_31X_V3_7TeV-v1/GEN-SIM-RECO
from TopAnalysis.Configuration.zmumu09_pat7 import *
evts  ['zmumu09_pat7'] =  2060340       ## number of produced events
xsec  ['zmumu09_pat7'] =     1300       ## NLO in pb from configfile
eff   ['zmumu09_pat7'] =      1.0       ## generator efficiency on gen level
sizes ['zmumu09_pat7'] = 'blocks'
source['zmumu09_pat7'] = 'zmumu09_pat7_0,' + 'zmumu09_pat7_1,'
source['zmumu09_pat7']+= 'zmumu09_pat7_2,' + 'zmumu09_pat7_3,'
source['zmumu09_pat7']+= 'zmumu09_pat7_4,' + 'zmumu09_pat7_5,'
source['zmumu09_pat7']+= 'zmumu09_pat7_6,' + 'zmumu09_pat7_7,'
source['zmumu09_pat7']+= 'zmumu09_pat7_8,' + 'zmumu09_pat7_9'

## /InclusiveMu15/Summer09-MC_31X_V3_7TeV-v1/GEN-SIM-RECO
from TopAnalysis.Configuration.qcd09_pat7 import *
evts  ['qcd09_pat7'] =    5340172        ## number of produced events
xsec  ['qcd09_pat7'] =  296900000        ## NLO in pb from configfile
eff   ['qcd09_pat7'] =    0.00037        ## generator efficiency on gen level
sizes ['qcd09_pat7'] = 'blocks'
source['qcd09_pat7'] = 'qcd09_pat7_0,' + 'qcd09_pat7_1,'
source['qcd09_pat7']+= 'qcd09_pat7_2,' + 'qcd09_pat7_3,'
source['qcd09_pat7']+= 'qcd09_pat7_4,' + 'qcd09_pat7_5,'
source['qcd09_pat7']+= 'qcd09_pat7_6,' + 'qcd09_pat7_7,'
source['qcd09_pat7']+= 'qcd09_pat7_8,' + 'qcd09_pat7_9,'
source['qcd09_pat7']+= 'qcd09_pat7_10,' + 'qcd09_pat7_11,'
source['qcd09_pat7']+= 'qcd09_pat7_12,' + 'qcd09_pat7_13,'
source['qcd09_pat7']+= 'qcd09_pat7_14,' + 'qcd09_pat7_15,'
source['qcd09_pat7']+= 'qcd09_pat7_16,' + 'qcd09_pat7_17,'
source['qcd09_pat7']+= 'qcd09_pat7_18,' + 'qcd09_pat7_19,'
source['qcd09_pat7']+= 'qcd09_pat7_20,' + 'qcd09_pat7_21,'
source['qcd09_pat7']+= 'qcd09_pat7_22,' + 'qcd09_pat7_23,'
source['qcd09_pat7']+= 'qcd09_pat7_24,' + 'qcd09_pat7_25,'
source['qcd09_pat7']+= 'qcd09_pat7_26,' + 'qcd09_pat7_27,'
source['qcd09_pat7']+= 'qcd09_pat7_28,' + 'qcd09_pat7_29,'
source['qcd09_pat7']+= 'qcd09_pat7_30,' + 'qcd09_pat7_31,'
source['qcd09_pat7']+= 'qcd09_pat7_32,' + 'qcd09_pat7_33,'
source['qcd09_pat7']+= 'qcd09_pat7_34,' + 'qcd09_pat7_35,'
source['qcd09_pat7']+= 'qcd09_pat7_36,' + 'qcd09_pat7_37,'
source['qcd09_pat7']+= 'qcd09_pat7_38,' + 'qcd09_pat7_39,'
source['qcd09_pat7']+= 'qcd09_pat7_40,' + 'qcd09_pat7_41,'
source['qcd09_pat7']+= 'qcd09_pat7_42,' + 'qcd09_pat7_43,'
source['qcd09_pat7']+= 'qcd09_pat7_44'

## /mc/Summer09/QCD_Pt15/GEN-SIM-RECO/MC_31X_V3-v1
from TopAnalysis.Configuration.qcd09_pt15_reco import *
evts  ['qcd09_pt15_reco'] = 5665829           ## number of produced events
xsec  ['qcd09_pt15_reco'] = 1458000000        ## NLO in pb from configfile
eff   ['qcd09_pt15_reco'] =     1.0           ## generator efficiency on gen level
sizes ['qcd09_pt15_reco'] = 'blocks'
source['qcd09_pt15_reco'] = 'qcd09_pt15_reco_0,' + 'qcd09_pt15_reco_1,' + 'qcd09_pt15_reco_2,' + 'qcd09_pt15_reco_3,' + 'qcd09_pt15_reco_4,'
source['qcd09_pt15_reco']+= 'qcd09_pt15_reco_5,' + 'qcd09_pt15_reco_6,' + 'qcd09_pt15_reco_7,' + 'qcd09_pt15_reco_8,' + 'qcd09_pt15_reco_9,'
source['qcd09_pt15_reco']+= 'qcd09_pt15_reco_10,'+ 'qcd09_pt15_reco_11,'+ 'qcd09_pt15_reco_12,'+ 'qcd09_pt15_reco_13,'+ 'qcd09_pt15_reco_14,'
source['qcd09_pt15_reco']+= 'qcd09_pt15_reco_15,'+ 'qcd09_pt15_reco_16,'+ 'qcd09_pt15_reco_17,'+ 'qcd09_pt15_reco_18,'+ 'qcd09_pt15_reco_19,'
source['qcd09_pt15_reco']+= 'qcd09_pt15_reco_20,'+ 'qcd09_pt15_reco_21,'+ 'qcd09_pt15_reco_22,'+ 'qcd09_pt15_reco_23,'+ 'qcd09_pt15_reco_24,'
source['qcd09_pt15_reco']+= 'qcd09_pt15_reco_25,'+ 'qcd09_pt15_reco_26,'+ 'qcd09_pt15_reco_27,'+ 'qcd09_pt15_reco_28,'+ 'qcd09_pt15_reco_29,'
source['qcd09_pt15_reco']+= 'qcd09_pt15_reco_30,'+ 'qcd09_pt15_reco_31,'+ 'qcd09_pt15_reco_32,'+ 'qcd09_pt15_reco_33,'+ 'qcd09_pt15_reco_34,'
source['qcd09_pt15_reco']+= 'qcd09_pt15_reco_35,'+ 'qcd09_pt15_reco_36,'+ 'qcd09_pt15_reco_37,'+ 'qcd09_pt15_reco_38,'+ 'qcd09_pt15_reco_39,'
source['qcd09_pt15_reco']+= 'qcd09_pt15_reco_40,'+ 'qcd09_pt15_reco_41,'+ 'qcd09_pt15_reco_42,'+ 'qcd09_pt15_reco_43,'+ 'qcd09_pt15_reco_44,'
source['qcd09_pt15_reco']+= 'qcd09_pt15_reco_45,'+ 'qcd09_pt15_reco_46,'+ 'qcd09_pt15_reco_47,'+ 'qcd09_pt15_reco_48,'+ 'qcd09_pt15_reco_49,'
source['qcd09_pt15_reco']+= 'qcd09_pt15_reco_50,'+ 'qcd09_pt15_reco_51,'+ 'qcd09_pt15_reco_52,'+ 'qcd09_pt15_reco_53,'+ 'qcd09_pt15_reco_54,'
source['qcd09_pt15_reco']+= 'qcd09_pt15_reco_55,'+ 'qcd09_pt15_reco_56,'+ 'qcd09_pt15_reco_57,'+ 'qcd09_pt15_reco_58,'+ 'qcd09_pt15_reco_59,'
source['qcd09_pt15_reco']+= 'qcd09_pt15_reco_60,'+ 'qcd09_pt15_reco_61,'+ 'qcd09_pt15_reco_62,'+ 'qcd09_pt15_reco_63,'+ 'qcd09_pt15_reco_64,'
source['qcd09_pt15_reco']+= 'qcd09_pt15_reco_65,'+ 'qcd09_pt15_reco_66,'+ 'qcd09_pt15_reco_67,'+ 'qcd09_pt15_reco_68,'+ 'qcd09_pt15_reco_69,'
source['qcd09_pt15_reco']+= 'qcd09_pt15_reco_70,'+ 'qcd09_pt15_reco_71,'+ 'qcd09_pt15_reco_72,'+ 'qcd09_pt15_reco_73,'+ 'qcd09_pt15_reco_74,'
source['qcd09_pt15_reco']+= 'qcd09_pt15_reco_75,'+ 'qcd09_pt15_reco_76,'+ 'qcd09_pt15_reco_77,'+ 'qcd09_pt15_reco_78,'+ 'qcd09_pt15_reco_79,'
source['qcd09_pt15_reco']+= 'qcd09_pt15_reco_80,'+ 'qcd09_pt15_reco_81,'+ 'qcd09_pt15_reco_82,'+ 'qcd09_pt15_reco_83,'+ 'qcd09_pt15_reco_84,'
source['qcd09_pt15_reco']+= 'qcd09_pt15_reco_85,'+ 'qcd09_pt15_reco_86,'+ 'qcd09_pt15_reco_87,'+ 'qcd09_pt15_reco_88,'+ 'qcd09_pt15_reco_89,'
source['qcd09_pt15_reco']+= 'qcd09_pt15_reco_90,'+ 'qcd09_pt15_reco_91,'+ 'qcd09_pt15_reco_92,'+ 'qcd09_pt15_reco_93,'+ 'qcd09_pt15_reco_94,'
source['qcd09_pt15_reco']+= 'qcd09_pt15_reco_95,'+ 'qcd09_pt15_reco_96,'+ 'qcd09_pt15_reco_97,'+ 'qcd09_pt15_reco_98,'+ 'qcd09_pt15_reco_99,'
source['qcd09_pt15_reco']+= 'qcd09_pt15_reco_100,'+'qcd09_pt15_reco_101,'+'qcd09_pt15_reco_102,'+'qcd09_pt15_reco_103,'+'qcd09_pt15_reco_104,'
source['qcd09_pt15_reco']+= 'qcd09_pt15_reco_105,'+'qcd09_pt15_reco_106,'+'qcd09_pt15_reco_107,'+'qcd09_pt15_reco_108,'+'qcd09_pt15_reco_109,'
source['qcd09_pt15_reco']+= 'qcd09_pt15_reco_110,'+'qcd09_pt15_reco_111,'+'qcd09_pt15_reco_112,'+'qcd09_pt15_reco_113,'+'qcd09_pt15_reco_114,'
source['qcd09_pt15_reco']+= 'qcd09_pt15_reco_115,'+'qcd09_pt15_reco_116,'+'qcd09_pt15_reco_117,'+'qcd09_pt15_reco_118,'+'qcd09_pt15_reco_119,'
source['qcd09_pt15_reco']+= 'qcd09_pt15_reco_120,'+'qcd09_pt15_reco_121,'+'qcd09_pt15_reco_122,'+'qcd09_pt15_reco_123,'+'qcd09_pt15_reco_124,'
source['qcd09_pt15_reco']+= 'qcd09_pt15_reco_125,'+'qcd09_pt15_reco_126,'+'qcd09_pt15_reco_127,'+'qcd09_pt15_reco_128,'+'qcd09_pt15_reco_129,'
source['qcd09_pt15_reco']+= 'qcd09_pt15_reco_130,'+'qcd09_pt15_reco_131,'+'qcd09_pt15_reco_132,'+'qcd09_pt15_reco_133,'+'qcd09_pt15_reco_134,'
source['qcd09_pt15_reco']+= 'qcd09_pt15_reco_135,'+'qcd09_pt15_reco_136,'+'qcd09_pt15_reco_137,'+'qcd09_pt15_reco_138,'+'qcd09_pt15_reco_139,'
source['qcd09_pt15_reco']+= 'qcd09_pt15_reco_140,'+'qcd09_pt15_reco_141,'+'qcd09_pt15_reco_142,'+'qcd09_pt15_reco_143,'+'qcd09_pt15_reco_144,'
source['qcd09_pt15_reco']+= 'qcd09_pt15_reco_145,'+'qcd09_pt15_reco_146,'+'qcd09_pt15_reco_147,'+'qcd09_pt15_reco_148,'+'qcd09_pt15_reco_149,'
source['qcd09_pt15_reco']+= 'qcd09_pt15_reco_150,'+'qcd09_pt15_reco_151,'+'qcd09_pt15_reco_152,'+'qcd09_pt15_reco_153,'+'qcd09_pt15_reco_154,'
source['qcd09_pt15_reco']+= 'qcd09_pt15_reco_155,'+'qcd09_pt15_reco_156,'+'qcd09_pt15_reco_157,'+'qcd09_pt15_reco_158,'+'qcd09_pt15_reco_159,'
source['qcd09_pt15_reco']+= 'qcd09_pt15_reco_160,'+'qcd09_pt15_reco_161,'+'qcd09_pt15_reco_162,'+'qcd09_pt15_reco_163,'+'qcd09_pt15_reco_164,'
source['qcd09_pt15_reco']+= 'qcd09_pt15_reco_165,'+'qcd09_pt15_reco_166,'+'qcd09_pt15_reco_167,'+'qcd09_pt15_reco_168,'+'qcd09_pt15_reco_169,'
source['qcd09_pt15_reco']+= 'qcd09_pt15_reco_170,'+'qcd09_pt15_reco_171,'+'qcd09_pt15_reco_172,'+'qcd09_pt15_reco_173'

## /mc/Summer09/QCD_Pt30/GEN-SIM-RECO/MC_31X_V3-v1
from TopAnalysis.Configuration.qcd09_pt30_reco import *
evts  ['qcd09_pt30_reco'] =  13922080 ## number of produced events
xsec  ['qcd09_pt30_reco'] = 109000000 ## NLO in pb from configfile
eff   ['qcd09_pt30_reco'] =       1.0 ## generator efficiency on gen level
sizes ['qcd09_pt30_reco'] = 'blocks'
source['qcd09_pt30_reco'] = 'qcd09_pt30_reco_0,' + 'qcd09_pt30_reco_1,' + 'qcd09_pt30_reco_2,' + 'qcd09_pt30_reco_3,' + 'qcd09_pt30_reco_4,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_5,' + 'qcd09_pt30_reco_6,' + 'qcd09_pt30_reco_7,' + 'qcd09_pt30_reco_8,' + 'qcd09_pt30_reco_9,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_10,'+ 'qcd09_pt30_reco_11,'+ 'qcd09_pt30_reco_12,'+ 'qcd09_pt30_reco_13,'+ 'qcd09_pt30_reco_14,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_15,'+ 'qcd09_pt30_reco_16,'+ 'qcd09_pt30_reco_17,'+ 'qcd09_pt30_reco_18,'+ 'qcd09_pt30_reco_19,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_20,'+ 'qcd09_pt30_reco_21,'+ 'qcd09_pt30_reco_22,'+ 'qcd09_pt30_reco_23,'+ 'qcd09_pt30_reco_24,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_25,'+ 'qcd09_pt30_reco_26,'+ 'qcd09_pt30_reco_27,'+ 'qcd09_pt30_reco_28,'+ 'qcd09_pt30_reco_29,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_30,'+ 'qcd09_pt30_reco_31,'+ 'qcd09_pt30_reco_32,'+ 'qcd09_pt30_reco_33,'+ 'qcd09_pt30_reco_34,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_35,'+ 'qcd09_pt30_reco_36,'+ 'qcd09_pt30_reco_37,'+ 'qcd09_pt30_reco_38,'+ 'qcd09_pt30_reco_39,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_40,'+ 'qcd09_pt30_reco_41,'+ 'qcd09_pt30_reco_42,'+ 'qcd09_pt30_reco_43,'+ 'qcd09_pt30_reco_44,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_45,'+ 'qcd09_pt30_reco_46,'+ 'qcd09_pt30_reco_47,'+ 'qcd09_pt30_reco_48,'+ 'qcd09_pt30_reco_49,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_50,'+ 'qcd09_pt30_reco_51,'+ 'qcd09_pt30_reco_52,'+ 'qcd09_pt30_reco_53,'+ 'qcd09_pt30_reco_54,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_55,'+ 'qcd09_pt30_reco_56,'+ 'qcd09_pt30_reco_57,'+ 'qcd09_pt30_reco_58,'+ 'qcd09_pt30_reco_59,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_60,'+ 'qcd09_pt30_reco_61,'+ 'qcd09_pt30_reco_62,'+ 'qcd09_pt30_reco_63,'+ 'qcd09_pt30_reco_64,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_65,'+ 'qcd09_pt30_reco_66,'+ 'qcd09_pt30_reco_67,'+ 'qcd09_pt30_reco_68,'+ 'qcd09_pt30_reco_69,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_70,'+ 'qcd09_pt30_reco_71,'+ 'qcd09_pt30_reco_72,'+ 'qcd09_pt30_reco_73,'+ 'qcd09_pt30_reco_74,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_75,'+ 'qcd09_pt30_reco_76,'+ 'qcd09_pt30_reco_77,'+ 'qcd09_pt30_reco_78,'+ 'qcd09_pt30_reco_79,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_80,'+ 'qcd09_pt30_reco_81,'+ 'qcd09_pt30_reco_82,'+ 'qcd09_pt30_reco_83,'+ 'qcd09_pt30_reco_84,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_85,'+ 'qcd09_pt30_reco_86,'+ 'qcd09_pt30_reco_87,'+ 'qcd09_pt30_reco_88,'+ 'qcd09_pt30_reco_89,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_90,'+ 'qcd09_pt30_reco_91,'+ 'qcd09_pt30_reco_92,'+ 'qcd09_pt30_reco_93,'+ 'qcd09_pt30_reco_94,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_95,'+ 'qcd09_pt30_reco_96,'+ 'qcd09_pt30_reco_97,'+ 'qcd09_pt30_reco_98,'+ 'qcd09_pt30_reco_99,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_100,'+'qcd09_pt30_reco_101,'+'qcd09_pt30_reco_102,'+'qcd09_pt30_reco_103,'+'qcd09_pt30_reco_104,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_105,'+'qcd09_pt30_reco_106,'+'qcd09_pt30_reco_107,'+'qcd09_pt30_reco_108,'+'qcd09_pt30_reco_109,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_110,'+'qcd09_pt30_reco_111,'+'qcd09_pt30_reco_112,'+'qcd09_pt30_reco_113,'+'qcd09_pt30_reco_114,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_115,'+'qcd09_pt30_reco_116,'+'qcd09_pt30_reco_117,'+'qcd09_pt30_reco_118,'+'qcd09_pt30_reco_119,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_120,'+'qcd09_pt30_reco_121,'+'qcd09_pt30_reco_122,'+'qcd09_pt30_reco_123,'+'qcd09_pt30_reco_124,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_125,'+'qcd09_pt30_reco_126,'+'qcd09_pt30_reco_127,'+'qcd09_pt30_reco_128,'+'qcd09_pt30_reco_129,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_130,'+'qcd09_pt30_reco_131,'+'qcd09_pt30_reco_132,'+'qcd09_pt30_reco_133,'+'qcd09_pt30_reco_134,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_135,'+'qcd09_pt30_reco_136,'+'qcd09_pt30_reco_137,'+'qcd09_pt30_reco_138,'+'qcd09_pt30_reco_139,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_140,'+'qcd09_pt30_reco_141,'+'qcd09_pt30_reco_142,'+'qcd09_pt30_reco_143,'+'qcd09_pt30_reco_144,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_145,'+'qcd09_pt30_reco_146,'+'qcd09_pt30_reco_147,'+'qcd09_pt30_reco_148,'+'qcd09_pt30_reco_149,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_150,'+'qcd09_pt30_reco_151,'+'qcd09_pt30_reco_152,'+'qcd09_pt30_reco_153,'+'qcd09_pt30_reco_154,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_155,'+'qcd09_pt30_reco_156,'+'qcd09_pt30_reco_157,'+'qcd09_pt30_reco_158,'+'qcd09_pt30_reco_159,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_160,'+'qcd09_pt30_reco_161,'+'qcd09_pt30_reco_162,'+'qcd09_pt30_reco_163,'+'qcd09_pt30_reco_164,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_165,'+'qcd09_pt30_reco_166,'+'qcd09_pt30_reco_167,'+'qcd09_pt30_reco_168,'+'qcd09_pt30_reco_169,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_170,'+'qcd09_pt30_reco_171,'+'qcd09_pt30_reco_172,'+'qcd09_pt30_reco_173,'+'qcd09_pt30_reco_174,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_175,'+'qcd09_pt30_reco_176,'+'qcd09_pt30_reco_177,'+'qcd09_pt30_reco_178,'+'qcd09_pt30_reco_179,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_180,'+'qcd09_pt30_reco_181,'+'qcd09_pt30_reco_182,'+'qcd09_pt30_reco_183,'+'qcd09_pt30_reco_184,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_185,'+'qcd09_pt30_reco_186,'+'qcd09_pt30_reco_187,'+'qcd09_pt30_reco_188,'+'qcd09_pt30_reco_189,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_190,'+'qcd09_pt30_reco_191,'+'qcd09_pt30_reco_192,'+'qcd09_pt30_reco_193,'+'qcd09_pt30_reco_194,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_195,'+'qcd09_pt30_reco_196,'+'qcd09_pt30_reco_197,'+'qcd09_pt30_reco_198,'+'qcd09_pt30_reco_199,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_200,'+'qcd09_pt30_reco_201,'+'qcd09_pt30_reco_202,'+'qcd09_pt30_reco_203,'+'qcd09_pt30_reco_204,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_205,'+'qcd09_pt30_reco_206,'+'qcd09_pt30_reco_207,'+'qcd09_pt30_reco_208,'+'qcd09_pt30_reco_209,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_210,'+'qcd09_pt30_reco_211,'+'qcd09_pt30_reco_212,'+'qcd09_pt30_reco_213,'+'qcd09_pt30_reco_214,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_215,'+'qcd09_pt30_reco_216,'+'qcd09_pt30_reco_217,'+'qcd09_pt30_reco_218,'+'qcd09_pt30_reco_219,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_220,'+'qcd09_pt30_reco_221,'+'qcd09_pt30_reco_222,'+'qcd09_pt30_reco_223,'+'qcd09_pt30_reco_224,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_225,'+'qcd09_pt30_reco_226,'+'qcd09_pt30_reco_227,'+'qcd09_pt30_reco_228,'+'qcd09_pt30_reco_229,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_230,'+'qcd09_pt30_reco_231,'+'qcd09_pt30_reco_232,'+'qcd09_pt30_reco_233,'+'qcd09_pt30_reco_234,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_235,'+'qcd09_pt30_reco_236,'+'qcd09_pt30_reco_237,'+'qcd09_pt30_reco_238,'+'qcd09_pt30_reco_239,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_240,'+'qcd09_pt30_reco_241,'+'qcd09_pt30_reco_242,'+'qcd09_pt30_reco_243,'+'qcd09_pt30_reco_244,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_245,'+'qcd09_pt30_reco_246,'+'qcd09_pt30_reco_247,'+'qcd09_pt30_reco_248,'+'qcd09_pt30_reco_249,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_250,'+'qcd09_pt30_reco_251,'+'qcd09_pt30_reco_252,'+'qcd09_pt30_reco_253,'+'qcd09_pt30_reco_254,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_255,'+'qcd09_pt30_reco_256,'+'qcd09_pt30_reco_257,'+'qcd09_pt30_reco_258,'+'qcd09_pt30_reco_259,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_260,'+'qcd09_pt30_reco_261,'+'qcd09_pt30_reco_262,'+'qcd09_pt30_reco_263,'+'qcd09_pt30_reco_264,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_265,'+'qcd09_pt30_reco_266,'+'qcd09_pt30_reco_267,'+'qcd09_pt30_reco_268,'+'qcd09_pt30_reco_269,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_270,'+'qcd09_pt30_reco_271,'+'qcd09_pt30_reco_272,'+'qcd09_pt30_reco_273,'+'qcd09_pt30_reco_274,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_275,'+'qcd09_pt30_reco_276,'+'qcd09_pt30_reco_277,'+'qcd09_pt30_reco_278,'+'qcd09_pt30_reco_279,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_280,'+'qcd09_pt30_reco_281,'+'qcd09_pt30_reco_282,'+'qcd09_pt30_reco_283,'+'qcd09_pt30_reco_284,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_285,'+'qcd09_pt30_reco_286,'+'qcd09_pt30_reco_287,'+'qcd09_pt30_reco_288,'+'qcd09_pt30_reco_289,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_290,'+'qcd09_pt30_reco_291,'+'qcd09_pt30_reco_292,'+'qcd09_pt30_reco_293,'+'qcd09_pt30_reco_294,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_295,'+'qcd09_pt30_reco_296,'+'qcd09_pt30_reco_297,'+'qcd09_pt30_reco_298,'+'qcd09_pt30_reco_299,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_300,'+'qcd09_pt30_reco_301,'+'qcd09_pt30_reco_302,'+'qcd09_pt30_reco_303,'+'qcd09_pt30_reco_304,'
source['qcd09_pt30_reco']+= 'qcd09_pt30_reco_305,'+'qcd09_pt30_reco_306,'+'qcd09_pt30_reco_307,'+'qcd09_pt30_reco_308'

## /mc/Summer09/QCD_Pt80/GEN-SIM-RECO/MC_31X_V3-v1
from TopAnalysis.Configuration.qcd09_pt80_reco import *
evts  ['qcd09_pt80_reco'] = 2147800  ## number of produced events
xsec  ['qcd09_pt80_reco'] = 1936000  ## NLO in pb from configfile
eff   ['qcd09_pt80_reco'] =     1.0  ## generator efficiency on gen level
sizes ['qcd09_pt80_reco'] = 'blocks'
source['qcd09_pt80_reco'] = 'qcd09_pt80_reco_0,' + 'qcd09_pt80_reco_1,' + 'qcd09_pt80_reco_2,' + 'qcd09_pt80_reco_3,' + 'qcd09_pt80_reco_4,'
source['qcd09_pt80_reco']+= 'qcd09_pt80_reco_5,' + 'qcd09_pt80_reco_6,' + 'qcd09_pt80_reco_7,' + 'qcd09_pt80_reco_8,' + 'qcd09_pt80_reco_9,'
source['qcd09_pt80_reco']+= 'qcd09_pt80_reco_10,'+ 'qcd09_pt80_reco_11,'+ 'qcd09_pt80_reco_12,'+ 'qcd09_pt80_reco_13,'+ 'qcd09_pt80_reco_14,'
source['qcd09_pt80_reco']+= 'qcd09_pt80_reco_15,'+ 'qcd09_pt80_reco_16,'+ 'qcd09_pt80_reco_17,'+ 'qcd09_pt80_reco_18,'+ 'qcd09_pt80_reco_19,'
source['qcd09_pt80_reco']+= 'qcd09_pt80_reco_20,'+ 'qcd09_pt80_reco_21,'+ 'qcd09_pt80_reco_22,'+ 'qcd09_pt80_reco_23,'+ 'qcd09_pt80_reco_24,'
source['qcd09_pt80_reco']+= 'qcd09_pt80_reco_25,'+ 'qcd09_pt80_reco_26,'+ 'qcd09_pt80_reco_27,'+ 'qcd09_pt80_reco_28,'+ 'qcd09_pt80_reco_29,'
source['qcd09_pt80_reco']+= 'qcd09_pt80_reco_30,'+ 'qcd09_pt80_reco_31,'+ 'qcd09_pt80_reco_32,'+ 'qcd09_pt80_reco_33,'+ 'qcd09_pt80_reco_34,'
source['qcd09_pt80_reco']+= 'qcd09_pt80_reco_35,'+ 'qcd09_pt80_reco_36,'+ 'qcd09_pt80_reco_37,'+ 'qcd09_pt80_reco_38,'+ 'qcd09_pt80_reco_39,'
source['qcd09_pt80_reco']+= 'qcd09_pt80_reco_40,'+ 'qcd09_pt80_reco_41,'+ 'qcd09_pt80_reco_42,'+ 'qcd09_pt80_reco_43,'+ 'qcd09_pt80_reco_44,'
source['qcd09_pt80_reco']+= 'qcd09_pt80_reco_45,'+ 'qcd09_pt80_reco_46,'+ 'qcd09_pt80_reco_47,'+ 'qcd09_pt80_reco_48,'+ 'qcd09_pt80_reco_49,'
source['qcd09_pt80_reco']+= 'qcd09_pt80_reco_50,'+ 'qcd09_pt80_reco_51,'+ 'qcd09_pt80_reco_52,'+ 'qcd09_pt80_reco_53,'+ 'qcd09_pt80_reco_54,'
source['qcd09_pt80_reco']+= 'qcd09_pt80_reco_55,'+ 'qcd09_pt80_reco_56,'+ 'qcd09_pt80_reco_57,'+ 'qcd09_pt80_reco_58,'+ 'qcd09_pt80_reco_59,'
source['qcd09_pt80_reco']+= 'qcd09_pt80_reco_60,'+ 'qcd09_pt80_reco_61,'+ 'qcd09_pt80_reco_62,'+ 'qcd09_pt80_reco_63,'+ 'qcd09_pt80_reco_64,'
source['qcd09_pt80_reco']+= 'qcd09_pt80_reco_65,'+ 'qcd09_pt80_reco_66,'+ 'qcd09_pt80_reco_67,'+ 'qcd09_pt80_reco_68,'+ 'qcd09_pt80_reco_69,'
source['qcd09_pt80_reco']+= 'qcd09_pt80_reco_70,'+ 'qcd09_pt80_reco_71,'+ 'qcd09_pt80_reco_72,'+ 'qcd09_pt80_reco_73,'+ 'qcd09_pt80_reco_74,'
source['qcd09_pt80_reco']+= 'qcd09_pt80_reco_75,'+ 'qcd09_pt80_reco_76,'+ 'qcd09_pt80_reco_77,'+ 'qcd09_pt80_reco_78,'+ 'qcd09_pt80_reco_79,'
source['qcd09_pt80_reco']+= 'qcd09_pt80_reco_80,'+ 'qcd09_pt80_reco_81,'+ 'qcd09_pt80_reco_82,'+ 'qcd09_pt80_reco_83,'+ 'qcd09_pt80_reco_84,'
source['qcd09_pt80_reco']+= 'qcd09_pt80_reco_85,'+ 'qcd09_pt80_reco_86,'+ 'qcd09_pt80_reco_87,'+ 'qcd09_pt80_reco_88,'+ 'qcd09_pt80_reco_89,'
source['qcd09_pt80_reco']+= 'qcd09_pt80_reco_90,'+ 'qcd09_pt80_reco_91,'+ 'qcd09_pt80_reco_92,'+ 'qcd09_pt80_reco_93,'+ 'qcd09_pt80_reco_94,'
source['qcd09_pt80_reco']+= 'qcd09_pt80_reco_95,'+ 'qcd09_pt80_reco_96,'+ 'qcd09_pt80_reco_97,'+ 'qcd09_pt80_reco_98,'+ 'qcd09_pt80_reco_99'

## /mc/Summer09/QCD_Pt170/GEN-SIM-RECO/MC_31X_V3-v1
from TopAnalysis.Configuration.qcd09_pt170_reco import *
evts  ['qcd09_pt170_reco'] = 2545020 ## number of produced events
xsec  ['qcd09_pt170_reco'] = 62510   ## NLO in pb from configfile
eff   ['qcd09_pt170_reco'] = 1.0     ## generator efficiency on gen level
sizes ['qcd09_pt170_reco'] = 'blocks'
source['qcd09_pt170_reco'] = 'qcd09_pt170_reco_0,' + 'qcd09_pt170_reco_1,' + 'qcd09_pt170_reco_2,' + 'qcd09_pt170_reco_3,' + 'qcd09_pt170_reco_4,'
source['qcd09_pt170_reco']+= 'qcd09_pt170_reco_5,' + 'qcd09_pt170_reco_6,' + 'qcd09_pt170_reco_7,' + 'qcd09_pt170_reco_8,' + 'qcd09_pt170_reco_9,'
source['qcd09_pt170_reco']+= 'qcd09_pt170_reco_10,'+ 'qcd09_pt170_reco_11,'+ 'qcd09_pt170_reco_12,'+ 'qcd09_pt170_reco_13,'+ 'qcd09_pt170_reco_14,'
source['qcd09_pt170_reco']+= 'qcd09_pt170_reco_15,'+ 'qcd09_pt170_reco_16,'+ 'qcd09_pt170_reco_17,'+ 'qcd09_pt170_reco_18,'+ 'qcd09_pt170_reco_19,'
source['qcd09_pt170_reco']+= 'qcd09_pt170_reco_20,'+ 'qcd09_pt170_reco_21,'+ 'qcd09_pt170_reco_22,'+ 'qcd09_pt170_reco_23,'+ 'qcd09_pt170_reco_24,'
source['qcd09_pt170_reco']+= 'qcd09_pt170_reco_25,'+ 'qcd09_pt170_reco_26,'+ 'qcd09_pt170_reco_27,'+ 'qcd09_pt170_reco_28,'+ 'qcd09_pt170_reco_29,'
source['qcd09_pt170_reco']+= 'qcd09_pt170_reco_30,'+ 'qcd09_pt170_reco_31,'+ 'qcd09_pt170_reco_32,'+ 'qcd09_pt170_reco_33,'+ 'qcd09_pt170_reco_34,'
source['qcd09_pt170_reco']+= 'qcd09_pt170_reco_35,'+ 'qcd09_pt170_reco_36,'+ 'qcd09_pt170_reco_37,'+ 'qcd09_pt170_reco_38,'+ 'qcd09_pt170_reco_39,'
source['qcd09_pt170_reco']+= 'qcd09_pt170_reco_40,'+ 'qcd09_pt170_reco_41,'+ 'qcd09_pt170_reco_42,'+ 'qcd09_pt170_reco_43,'+ 'qcd09_pt170_reco_44,'
source['qcd09_pt170_reco']+= 'qcd09_pt170_reco_45,'+ 'qcd09_pt170_reco_46,'+ 'qcd09_pt170_reco_47,'+ 'qcd09_pt170_reco_48,'+ 'qcd09_pt170_reco_49,'
source['qcd09_pt170_reco']+= 'qcd09_pt170_reco_50,'+ 'qcd09_pt170_reco_51,'+ 'qcd09_pt170_reco_52,'+ 'qcd09_pt170_reco_53,'+ 'qcd09_pt170_reco_54,'
source['qcd09_pt170_reco']+= 'qcd09_pt170_reco_55,'+ 'qcd09_pt170_reco_56,'+ 'qcd09_pt170_reco_57,'+ 'qcd09_pt170_reco_58,'+ 'qcd09_pt170_reco_59,'
source['qcd09_pt170_reco']+= 'qcd09_pt170_reco_60,'+ 'qcd09_pt170_reco_61,'+ 'qcd09_pt170_reco_62,'+ 'qcd09_pt170_reco_63,'+ 'qcd09_pt170_reco_64,'
source['qcd09_pt170_reco']+= 'qcd09_pt170_reco_65,'+ 'qcd09_pt170_reco_66,'+ 'qcd09_pt170_reco_67,'+ 'qcd09_pt170_reco_68,'+ 'qcd09_pt170_reco_69,'
source['qcd09_pt170_reco']+= 'qcd09_pt170_reco_70,'+ 'qcd09_pt170_reco_71,'+ 'qcd09_pt170_reco_72,'+ 'qcd09_pt170_reco_73,'+ 'qcd09_pt170_reco_74,'
source['qcd09_pt170_reco']+= 'qcd09_pt170_reco_75,'+ 'qcd09_pt170_reco_76,'+ 'qcd09_pt170_reco_77,'+ 'qcd09_pt170_reco_78,'+ 'qcd09_pt170_reco_79,'
source['qcd09_pt170_reco']+= 'qcd09_pt170_reco_80,'+ 'qcd09_pt170_reco_81,'+ 'qcd09_pt170_reco_82,'+ 'qcd09_pt170_reco_83,'+ 'qcd09_pt170_reco_84,'
source['qcd09_pt170_reco']+= 'qcd09_pt170_reco_85,'+ 'qcd09_pt170_reco_86,'+ 'qcd09_pt170_reco_87,'+ 'qcd09_pt170_reco_88,'+ 'qcd09_pt170_reco_89,'
source['qcd09_pt170_reco']+= 'qcd09_pt170_reco_90,'+ 'qcd09_pt170_reco_91,'+ 'qcd09_pt170_reco_92,'+ 'qcd09_pt170_reco_93,'+ 'qcd09_pt170_reco_94,'
source['qcd09_pt170_reco']+= 'qcd09_pt170_reco_95,'+ 'qcd09_pt170_reco_96,'+ 'qcd09_pt170_reco_97,'+ 'qcd09_pt170_reco_98,'+ 'qcd09_pt170_reco_99,'
source['qcd09_pt170_reco']+= 'qcd09_pt170_reco_100,'+'qcd09_pt170_reco_101,'+'qcd09_pt170_reco_102,'+'qcd09_pt170_reco_103,'+'qcd09_pt170_reco_104,'
source['qcd09_pt170_reco']+= 'qcd09_pt170_reco_105,'+'qcd09_pt170_reco_106,'+'qcd09_pt170_reco_107,'+'qcd09_pt170_reco_108,'+'qcd09_pt170_reco_109,'
source['qcd09_pt170_reco']+= 'qcd09_pt170_reco_110,'+'qcd09_pt170_reco_111,'+'qcd09_pt170_reco_112,'+'qcd09_pt170_reco_113,'+'qcd09_pt170_reco_114,'
source['qcd09_pt170_reco']+= 'qcd09_pt170_reco_115,'+'qcd09_pt170_reco_116,'+'qcd09_pt170_reco_117,'+'qcd09_pt170_reco_118,'+'qcd09_pt170_reco_119,'
source['qcd09_pt170_reco']+= 'qcd09_pt170_reco_120,'+'qcd09_pt170_reco_121,'+'qcd09_pt170_reco_122,'+'qcd09_pt170_reco_123,'+'qcd09_pt170_reco_124,'
source['qcd09_pt170_reco']+= 'qcd09_pt170_reco_125,'+'qcd09_pt170_reco_126,'+'qcd09_pt170_reco_127,'+'qcd09_pt170_reco_128,'+'qcd09_pt170_reco_129,'
source['qcd09_pt170_reco']+= 'qcd09_pt170_reco_130,'+'qcd09_pt170_reco_131,'+'qcd09_pt170_reco_132,'+'qcd09_pt170_reco_133,'+'qcd09_pt170_reco_134,'
source['qcd09_pt170_reco']+= 'qcd09_pt170_reco_135,'+'qcd09_pt170_reco_136,'+'qcd09_pt170_reco_137,'+'qcd09_pt170_reco_138'

## /mc/Summer09/QCD_Pt300/GEN-SIM-RECO/MC_31X_V3-v1
from TopAnalysis.Configuration.qcd09_pt300_reco import *
evts  ['qcd09_pt300_reco'] =  2087000 ## number of produced events
xsec  ['qcd09_pt300_reco'] =  3669    ## NLO in pb from configfile
eff   ['qcd09_pt300_reco'] =  1.0     ## generator efficiency on gen level
sizes ['qcd09_pt300_reco'] = 'blocks'
source['qcd09_pt300_reco'] = 'qcd09_pt300_reco_0,' + 'qcd09_pt300_reco_1,' + 'qcd09_pt300_reco_2,' + 'qcd09_pt300_reco_3,' + 'qcd09_pt300_reco_4,'
source['qcd09_pt300_reco']+= 'qcd09_pt300_reco_5,' + 'qcd09_pt300_reco_6,' + 'qcd09_pt300_reco_7,' + 'qcd09_pt300_reco_8,' + 'qcd09_pt300_reco_9,'
source['qcd09_pt300_reco']+= 'qcd09_pt300_reco_10,'+ 'qcd09_pt300_reco_11,'+ 'qcd09_pt300_reco_12,'+ 'qcd09_pt300_reco_13,'+ 'qcd09_pt300_reco_14,'
source['qcd09_pt300_reco']+= 'qcd09_pt300_reco_15,'+ 'qcd09_pt300_reco_16,'+ 'qcd09_pt300_reco_17,'+ 'qcd09_pt300_reco_18,'+ 'qcd09_pt300_reco_19,'
source['qcd09_pt300_reco']+= 'qcd09_pt300_reco_20,'+ 'qcd09_pt300_reco_21,'+ 'qcd09_pt300_reco_22,'+ 'qcd09_pt300_reco_23,'+ 'qcd09_pt300_reco_24,'
source['qcd09_pt300_reco']+= 'qcd09_pt300_reco_25,'+ 'qcd09_pt300_reco_26,'+ 'qcd09_pt300_reco_27,'+ 'qcd09_pt300_reco_28,'+ 'qcd09_pt300_reco_29,'
source['qcd09_pt300_reco']+= 'qcd09_pt300_reco_30,'+ 'qcd09_pt300_reco_31,'+ 'qcd09_pt300_reco_32,'+ 'qcd09_pt300_reco_33,'+ 'qcd09_pt300_reco_34,'
source['qcd09_pt300_reco']+= 'qcd09_pt300_reco_35,'+ 'qcd09_pt300_reco_36,'+ 'qcd09_pt300_reco_37,'+ 'qcd09_pt300_reco_38,'+ 'qcd09_pt300_reco_39,'
source['qcd09_pt300_reco']+= 'qcd09_pt300_reco_40,'+ 'qcd09_pt300_reco_41,'+ 'qcd09_pt300_reco_42,'+ 'qcd09_pt300_reco_43,'+ 'qcd09_pt300_reco_44,'
source['qcd09_pt300_reco']+= 'qcd09_pt300_reco_45,'+ 'qcd09_pt300_reco_46,'+ 'qcd09_pt300_reco_47,'+ 'qcd09_pt300_reco_48,'+ 'qcd09_pt300_reco_49,'
source['qcd09_pt300_reco']+= 'qcd09_pt300_reco_50,'+ 'qcd09_pt300_reco_51,'+ 'qcd09_pt300_reco_52,'+ 'qcd09_pt300_reco_53,'+ 'qcd09_pt300_reco_54,'
source['qcd09_pt300_reco']+= 'qcd09_pt300_reco_55,'+ 'qcd09_pt300_reco_56,'+ 'qcd09_pt300_reco_57,'+ 'qcd09_pt300_reco_58,'+ 'qcd09_pt300_reco_59,'
source['qcd09_pt300_reco']+= 'qcd09_pt300_reco_60,'+ 'qcd09_pt300_reco_61,'+ 'qcd09_pt300_reco_62,'+ 'qcd09_pt300_reco_63,'+ 'qcd09_pt300_reco_64,'
source['qcd09_pt300_reco']+= 'qcd09_pt300_reco_65,'+ 'qcd09_pt300_reco_66,'+ 'qcd09_pt300_reco_67,'+ 'qcd09_pt300_reco_68,'+ 'qcd09_pt300_reco_69,'
source['qcd09_pt300_reco']+= 'qcd09_pt300_reco_70,'+ 'qcd09_pt300_reco_71,'+ 'qcd09_pt300_reco_72,'+ 'qcd09_pt300_reco_73,'+ 'qcd09_pt300_reco_74,'
source['qcd09_pt300_reco']+= 'qcd09_pt300_reco_75,'+ 'qcd09_pt300_reco_76,'+ 'qcd09_pt300_reco_77,'+ 'qcd09_pt300_reco_78,'+ 'qcd09_pt300_reco_79,'
source['qcd09_pt300_reco']+= 'qcd09_pt300_reco_80,'+ 'qcd09_pt300_reco_81,'+ 'qcd09_pt300_reco_82,'+ 'qcd09_pt300_reco_83,'+ 'qcd09_pt300_reco_84,'
source['qcd09_pt300_reco']+= 'qcd09_pt300_reco_85,'+ 'qcd09_pt300_reco_86,'+ 'qcd09_pt300_reco_87,'+ 'qcd09_pt300_reco_88,'+ 'qcd09_pt300_reco_89,'
source['qcd09_pt300_reco']+= 'qcd09_pt300_reco_90,'+ 'qcd09_pt300_reco_91,'+ 'qcd09_pt300_reco_92'

## /mc/Summer09/QCD_Pt470/GEN-SIM-RECO/MC_31X_V3-v1
from TopAnalysis.Configuration.qcd09_pt470_reco import *
evts  ['qcd09_pt470_reco'] = 2131360  ## number of produced events
xsec  ['qcd09_pt470_reco'] = 315.3    ## NLO in pb from configfile
eff   ['qcd09_pt470_reco'] = 1.0      ## generator efficiency on gen level
sizes ['qcd09_pt470_reco'] = 'blocks'
source['qcd09_pt470_reco'] = 'qcd09_pt470_reco_0,' + 'qcd09_pt470_reco_1,' + 'qcd09_pt470_reco_2,' + 'qcd09_pt470_reco_3,' + 'qcd09_pt470_reco_4,'
source['qcd09_pt470_reco']+= 'qcd09_pt470_reco_5,' + 'qcd09_pt470_reco_6,' + 'qcd09_pt470_reco_7,' + 'qcd09_pt470_reco_8,' + 'qcd09_pt470_reco_9,'
source['qcd09_pt470_reco']+= 'qcd09_pt470_reco_10,'+ 'qcd09_pt470_reco_11,'+ 'qcd09_pt470_reco_12,'+ 'qcd09_pt470_reco_13,'+ 'qcd09_pt470_reco_14,'
source['qcd09_pt470_reco']+= 'qcd09_pt470_reco_15,'+ 'qcd09_pt470_reco_16,'+ 'qcd09_pt470_reco_17,'+ 'qcd09_pt470_reco_18,'+ 'qcd09_pt470_reco_19,'
source['qcd09_pt470_reco']+= 'qcd09_pt470_reco_20,'+ 'qcd09_pt470_reco_21,'+ 'qcd09_pt470_reco_22,'+ 'qcd09_pt470_reco_23,'+ 'qcd09_pt470_reco_24,'
source['qcd09_pt470_reco']+= 'qcd09_pt470_reco_25,'+ 'qcd09_pt470_reco_26,'+ 'qcd09_pt470_reco_27,'+ 'qcd09_pt470_reco_28,'+ 'qcd09_pt470_reco_29,'
source['qcd09_pt470_reco']+= 'qcd09_pt470_reco_30,'+ 'qcd09_pt470_reco_31,'+ 'qcd09_pt470_reco_32,'+ 'qcd09_pt470_reco_33,'+ 'qcd09_pt470_reco_34,'
source['qcd09_pt470_reco']+= 'qcd09_pt470_reco_35,'+ 'qcd09_pt470_reco_36,'+ 'qcd09_pt470_reco_37,'+ 'qcd09_pt470_reco_38,'+ 'qcd09_pt470_reco_39,'
source['qcd09_pt470_reco']+= 'qcd09_pt470_reco_40,'+ 'qcd09_pt470_reco_41,'+ 'qcd09_pt470_reco_42,'+ 'qcd09_pt470_reco_43,'+ 'qcd09_pt470_reco_44,'
source['qcd09_pt470_reco']+= 'qcd09_pt470_reco_45,'+ 'qcd09_pt470_reco_46,'+ 'qcd09_pt470_reco_47,'+ 'qcd09_pt470_reco_48,'+ 'qcd09_pt470_reco_49,'
source['qcd09_pt470_reco']+= 'qcd09_pt470_reco_50,'+ 'qcd09_pt470_reco_51,'+ 'qcd09_pt470_reco_52,'+ 'qcd09_pt470_reco_53,'+ 'qcd09_pt470_reco_54,'
source['qcd09_pt470_reco']+= 'qcd09_pt470_reco_55,'+ 'qcd09_pt470_reco_56,'+ 'qcd09_pt470_reco_57,'+ 'qcd09_pt470_reco_58,'+ 'qcd09_pt470_reco_59,'
source['qcd09_pt470_reco']+= 'qcd09_pt470_reco_60,'+ 'qcd09_pt470_reco_61,'+ 'qcd09_pt470_reco_62,'+ 'qcd09_pt470_reco_63,'+ 'qcd09_pt470_reco_64,'
source['qcd09_pt470_reco']+= 'qcd09_pt470_reco_65,'+ 'qcd09_pt470_reco_66,'+ 'qcd09_pt470_reco_67,'+ 'qcd09_pt470_reco_68,'+ 'qcd09_pt470_reco_69,'
source['qcd09_pt470_reco']+= 'qcd09_pt470_reco_70,'+ 'qcd09_pt470_reco_71,'+ 'qcd09_pt470_reco_72,'+ 'qcd09_pt470_reco_73,'+ 'qcd09_pt470_reco_74,'
source['qcd09_pt470_reco']+= 'qcd09_pt470_reco_75,'+ 'qcd09_pt470_reco_76,'+ 'qcd09_pt470_reco_77,'+ 'qcd09_pt470_reco_78,'+ 'qcd09_pt470_reco_79,'
source['qcd09_pt470_reco']+= 'qcd09_pt470_reco_80,'+ 'qcd09_pt470_reco_81,'+ 'qcd09_pt470_reco_82,'+ 'qcd09_pt470_reco_83,'+ 'qcd09_pt470_reco_84,'
source['qcd09_pt470_reco']+= 'qcd09_pt470_reco_85,'+ 'qcd09_pt470_reco_86,'+ 'qcd09_pt470_reco_87,'+ 'qcd09_pt470_reco_88,'+ 'qcd09_pt470_reco_89,'
source['qcd09_pt470_reco']+= 'qcd09_pt470_reco_90,'+ 'qcd09_pt470_reco_91,'+ 'qcd09_pt470_reco_92,'+ 'qcd09_pt470_reco_93,'+ 'qcd09_pt470_reco_94,'
source['qcd09_pt470_reco']+= 'qcd09_pt470_reco_95,'+ 'qcd09_pt470_reco_96,'+ 'qcd09_pt470_reco_97,'+ 'qcd09_pt470_reco_98,'+ 'qcd09_pt470_reco_99,'
source['qcd09_pt470_reco']+= 'qcd09_pt470_reco_100,'+'qcd09_pt470_reco_101,'+'qcd09_pt470_reco_102,'+'qcd09_pt470_reco_103,'+'qcd09_pt470_reco_104,'
source['qcd09_pt470_reco']+= 'qcd09_pt470_reco_105,'+'qcd09_pt470_reco_106'

## /mc/Summer09/QCD_Pt800/GEN-SIM-RECO/MC_31X_V3-v1
from TopAnalysis.Configuration.qcd09_pt800_reco import *
evts  ['qcd09_pt800_reco'] = 2092640  ## number of produced events
xsec  ['qcd09_pt800_reco'] = 11.94    ## NLO in pb from configfile
eff   ['qcd09_pt800_reco'] = 1.0      ## generator efficiency on gen level
sizes ['qcd09_pt800_reco'] = 'blocks'
source['qcd09_pt800_reco'] = 'qcd09_pt800_reco_0,' + 'qcd09_pt800_reco_1,' + 'qcd09_pt800_reco_2,' + 'qcd09_pt800_reco_3,' + 'qcd09_pt800_reco_4,'
source['qcd09_pt800_reco']+= 'qcd09_pt800_reco_5,' + 'qcd09_pt800_reco_6,' + 'qcd09_pt800_reco_7,' + 'qcd09_pt800_reco_8,' + 'qcd09_pt800_reco_9,'
source['qcd09_pt800_reco']+= 'qcd09_pt800_reco_10,'+ 'qcd09_pt800_reco_11,'+ 'qcd09_pt800_reco_12,'+ 'qcd09_pt800_reco_13,'+ 'qcd09_pt800_reco_14,'
source['qcd09_pt800_reco']+= 'qcd09_pt800_reco_15,'+ 'qcd09_pt800_reco_16,'+ 'qcd09_pt800_reco_17,'+ 'qcd09_pt800_reco_18,'+ 'qcd09_pt800_reco_19,'
source['qcd09_pt800_reco']+= 'qcd09_pt800_reco_20,'+ 'qcd09_pt800_reco_21,'+ 'qcd09_pt800_reco_22,'+ 'qcd09_pt800_reco_23,'+ 'qcd09_pt800_reco_24,'
source['qcd09_pt800_reco']+= 'qcd09_pt800_reco_25,'+ 'qcd09_pt800_reco_26,'+ 'qcd09_pt800_reco_27,'+ 'qcd09_pt800_reco_28,'+ 'qcd09_pt800_reco_29,'
source['qcd09_pt800_reco']+= 'qcd09_pt800_reco_30,'+ 'qcd09_pt800_reco_31,'+ 'qcd09_pt800_reco_32,'+ 'qcd09_pt800_reco_33,'+ 'qcd09_pt800_reco_34,'
source['qcd09_pt800_reco']+= 'qcd09_pt800_reco_35,'+ 'qcd09_pt800_reco_36,'+ 'qcd09_pt800_reco_37,'+ 'qcd09_pt800_reco_38,'+ 'qcd09_pt800_reco_39,'
source['qcd09_pt800_reco']+= 'qcd09_pt800_reco_40,'+ 'qcd09_pt800_reco_41,'+ 'qcd09_pt800_reco_42,'+ 'qcd09_pt800_reco_43,'+ 'qcd09_pt800_reco_44,'
source['qcd09_pt800_reco']+= 'qcd09_pt800_reco_45,'+ 'qcd09_pt800_reco_46,'+ 'qcd09_pt800_reco_47,'+ 'qcd09_pt800_reco_48,'+ 'qcd09_pt800_reco_49,'
source['qcd09_pt800_reco']+= 'qcd09_pt800_reco_50,'+ 'qcd09_pt800_reco_51,'+ 'qcd09_pt800_reco_52,'+ 'qcd09_pt800_reco_53,'+ 'qcd09_pt800_reco_54,'
source['qcd09_pt800_reco']+= 'qcd09_pt800_reco_55,'+ 'qcd09_pt800_reco_56,'+ 'qcd09_pt800_reco_57,'+ 'qcd09_pt800_reco_58,'+ 'qcd09_pt800_reco_59,'
source['qcd09_pt800_reco']+= 'qcd09_pt800_reco_60,'+ 'qcd09_pt800_reco_61,'+ 'qcd09_pt800_reco_62,'+ 'qcd09_pt800_reco_63,'+ 'qcd09_pt800_reco_64,'
source['qcd09_pt800_reco']+= 'qcd09_pt800_reco_65,'+ 'qcd09_pt800_reco_66,'+ 'qcd09_pt800_reco_67,'+ 'qcd09_pt800_reco_68,'+ 'qcd09_pt800_reco_69,'
source['qcd09_pt800_reco']+= 'qcd09_pt800_reco_70,'+ 'qcd09_pt800_reco_71,'+ 'qcd09_pt800_reco_72,'+ 'qcd09_pt800_reco_73,'+ 'qcd09_pt800_reco_74,'
source['qcd09_pt800_reco']+= 'qcd09_pt800_reco_75,'+ 'qcd09_pt800_reco_76,'+ 'qcd09_pt800_reco_77,'+ 'qcd09_pt800_reco_78,'+ 'qcd09_pt800_reco_79,'
source['qcd09_pt800_reco']+= 'qcd09_pt800_reco_80,'+ 'qcd09_pt800_reco_81,'+ 'qcd09_pt800_reco_82,'+ 'qcd09_pt800_reco_83,'+ 'qcd09_pt800_reco_84,'
source['qcd09_pt800_reco']+= 'qcd09_pt800_reco_85,'+ 'qcd09_pt800_reco_86,'+ 'qcd09_pt800_reco_87,'+ 'qcd09_pt800_reco_88,'+ 'qcd09_pt800_reco_89,'
source['qcd09_pt800_reco']+= 'qcd09_pt800_reco_90,'+ 'qcd09_pt800_reco_91,'+ 'qcd09_pt800_reco_92,'+ 'qcd09_pt800_reco_93,'+ 'qcd09_pt800_reco_94,'
source['qcd09_pt800_reco']+= 'qcd09_pt800_reco_95,'+ 'qcd09_pt800_reco_96,'+ 'qcd09_pt800_reco_97,'+ 'qcd09_pt800_reco_98,'+ 'qcd09_pt800_reco_99,'
source['qcd09_pt800_reco']+= 'qcd09_pt800_reco_100,'+'qcd09_pt800_reco_101,'+'qcd09_pt800_reco_102,'+'qcd09_pt800_reco_103,'+'qcd09_pt800_reco_104,'
source['qcd09_pt800_reco']+= 'qcd09_pt800_reco_105'

## /mc/Summer09/QCD_Pt1400/GEN-SIM-RECO/MC_31X_V3-v1
from TopAnalysis.Configuration.qcd09_pt1400_reco import *
evts  ['qcd09_pt1400_reco'] = 1188486  ## number of produced events
xsec  ['qcd09_pt1400_reco'] = 0.1721   ## NLO in pb from configfile
eff   ['qcd09_pt1400_reco'] = 1.0      ## generator efficiency on gen level
sizes ['qcd09_pt1400_reco'] = 'blocks'
source['qcd09_pt1400_reco'] = 'qcd09_pt1400_reco_0,' + 'qcd09_pt1400_reco_1,' + 'qcd09_pt1400_reco_2,' + 'qcd09_pt1400_reco_3,' + 'qcd09_pt1400_reco_4,'
source['qcd09_pt1400_reco']+= 'qcd09_pt1400_reco_5,' + 'qcd09_pt1400_reco_6,' + 'qcd09_pt1400_reco_7,' + 'qcd09_pt1400_reco_8,' + 'qcd09_pt1400_reco_9,'
source['qcd09_pt1400_reco']+= 'qcd09_pt1400_reco_10,'+ 'qcd09_pt1400_reco_11,'+ 'qcd09_pt1400_reco_12,'+ 'qcd09_pt1400_reco_13,'+ 'qcd09_pt1400_reco_14,'
source['qcd09_pt1400_reco']+= 'qcd09_pt1400_reco_15,'+ 'qcd09_pt1400_reco_16,'+ 'qcd09_pt1400_reco_17,'+ 'qcd09_pt1400_reco_18,'+ 'qcd09_pt1400_reco_19,'
source['qcd09_pt1400_reco']+= 'qcd09_pt1400_reco_20,'+ 'qcd09_pt1400_reco_21,'+ 'qcd09_pt1400_reco_22,'+ 'qcd09_pt1400_reco_23,'+ 'qcd09_pt1400_reco_24,'
source['qcd09_pt1400_reco']+= 'qcd09_pt1400_reco_25,'+ 'qcd09_pt1400_reco_26,'+ 'qcd09_pt1400_reco_27,'+ 'qcd09_pt1400_reco_28,'+ 'qcd09_pt1400_reco_29,'
source['qcd09_pt1400_reco']+= 'qcd09_pt1400_reco_30,'+ 'qcd09_pt1400_reco_31,'+ 'qcd09_pt1400_reco_32,'+ 'qcd09_pt1400_reco_33,'+ 'qcd09_pt1400_reco_34,'
source['qcd09_pt1400_reco']+= 'qcd09_pt1400_reco_35,'+ 'qcd09_pt1400_reco_36,'+ 'qcd09_pt1400_reco_37,'+ 'qcd09_pt1400_reco_38,'+ 'qcd09_pt1400_reco_39,'
source['qcd09_pt1400_reco']+= 'qcd09_pt1400_reco_40,'+ 'qcd09_pt1400_reco_41,'+ 'qcd09_pt1400_reco_42,'+ 'qcd09_pt1400_reco_43,'+ 'qcd09_pt1400_reco_44,'
source['qcd09_pt1400_reco']+= 'qcd09_pt1400_reco_45,'+ 'qcd09_pt1400_reco_46,'+ 'qcd09_pt1400_reco_47,'+ 'qcd09_pt1400_reco_48,'+ 'qcd09_pt1400_reco_49,'
source['qcd09_pt1400_reco']+= 'qcd09_pt1400_reco_50,'+ 'qcd09_pt1400_reco_51,'+ 'qcd09_pt1400_reco_52,'+ 'qcd09_pt1400_reco_53,'+ 'qcd09_pt1400_reco_54,'
source['qcd09_pt1400_reco']+= 'qcd09_pt1400_reco_55,'+ 'qcd09_pt1400_reco_56,'+ 'qcd09_pt1400_reco_57,'+ 'qcd09_pt1400_reco_58,'+ 'qcd09_pt1400_reco_59,'
source['qcd09_pt1400_reco']+= 'qcd09_pt1400_reco_60,'+ 'qcd09_pt1400_reco_61,'+ 'qcd09_pt1400_reco_62,'+ 'qcd09_pt1400_reco_63,'+ 'qcd09_pt1400_reco_64,'
source['qcd09_pt1400_reco']+= 'qcd09_pt1400_reco_65,'+ 'qcd09_pt1400_reco_66,'+ 'qcd09_pt1400_reco_67,'+ 'qcd09_pt1400_reco_68,'+ 'qcd09_pt1400_reco_69,'
source['qcd09_pt1400_reco']+= 'qcd09_pt1400_reco_70,'+ 'qcd09_pt1400_reco_71,'+ 'qcd09_pt1400_reco_72,'+ 'qcd09_pt1400_reco_73,'+ 'qcd09_pt1400_reco_74,'
source['qcd09_pt1400_reco']+= 'qcd09_pt1400_reco_75,'+ 'qcd09_pt1400_reco_76,'+ 'qcd09_pt1400_reco_77,'+ 'qcd09_pt1400_reco_78,'+ 'qcd09_pt1400_reco_79,'
source['qcd09_pt1400_reco']+= 'qcd09_pt1400_reco_80,'+ 'qcd09_pt1400_reco_81,'+ 'qcd09_pt1400_reco_82,'+ 'qcd09_pt1400_reco_83,'+ 'qcd09_pt1400_reco_84,'
source['qcd09_pt1400_reco']+= 'qcd09_pt1400_reco_85,'+ 'qcd09_pt1400_reco_86,'+ 'qcd09_pt1400_reco_87,'+ 'qcd09_pt1400_reco_88,'+ 'qcd09_pt1400_reco_89,'
source['qcd09_pt1400_reco']+= 'qcd09_pt1400_reco_90,'+ 'qcd09_pt1400_reco_91,'+ 'qcd09_pt1400_reco_92'

## /mc/Summer09/QCD_Pt2200/GEN-SIM-RECO/MC_31X_V3-v1
from TopAnalysis.Configuration.qcd09_pt2200_reco import *
evts  ['qcd09_pt2200_reco'] = 1198660  ## number of produced events
xsec  ['qcd09_pt2200_reco'] = 0.001422 ## NLO in pb from configfile
eff   ['qcd09_pt2200_reco'] = 1.0      ## generator efficiency on gen level
sizes ['qcd09_pt2200_reco'] = 'blocks'
source['qcd09_pt2200_reco'] = 'qcd09_pt2200_reco_0,' + 'qcd09_pt2200_reco_1,' + 'qcd09_pt2200_reco_2,' + 'qcd09_pt2200_reco_3,' + 'qcd09_pt2200_reco_4,'
source['qcd09_pt2200_reco']+= 'qcd09_pt2200_reco_5,' + 'qcd09_pt2200_reco_6,' + 'qcd09_pt2200_reco_7,' + 'qcd09_pt2200_reco_8,' + 'qcd09_pt2200_reco_9,'
source['qcd09_pt2200_reco']+= 'qcd09_pt2200_reco_10,'+ 'qcd09_pt2200_reco_11,'+ 'qcd09_pt2200_reco_12,'+ 'qcd09_pt2200_reco_13,'+ 'qcd09_pt2200_reco_14,'
source['qcd09_pt2200_reco']+= 'qcd09_pt2200_reco_15,'+ 'qcd09_pt2200_reco_16,'+ 'qcd09_pt2200_reco_17,'+ 'qcd09_pt2200_reco_18,'+ 'qcd09_pt2200_reco_19,'
source['qcd09_pt2200_reco']+= 'qcd09_pt2200_reco_20,'+ 'qcd09_pt2200_reco_21,'+ 'qcd09_pt2200_reco_22,'+ 'qcd09_pt2200_reco_23,'+ 'qcd09_pt2200_reco_24,'
source['qcd09_pt2200_reco']+= 'qcd09_pt2200_reco_25,'+ 'qcd09_pt2200_reco_26,'+ 'qcd09_pt2200_reco_27,'+ 'qcd09_pt2200_reco_28,'+ 'qcd09_pt2200_reco_29,'
source['qcd09_pt2200_reco']+= 'qcd09_pt2200_reco_30,'+ 'qcd09_pt2200_reco_31,'+ 'qcd09_pt2200_reco_32,'+ 'qcd09_pt2200_reco_33,'+ 'qcd09_pt2200_reco_34,'
source['qcd09_pt2200_reco']+= 'qcd09_pt2200_reco_35,'+ 'qcd09_pt2200_reco_36,'+ 'qcd09_pt2200_reco_37,'+ 'qcd09_pt2200_reco_38,'+ 'qcd09_pt2200_reco_39,'
source['qcd09_pt2200_reco']+= 'qcd09_pt2200_reco_40,'+ 'qcd09_pt2200_reco_41,'+ 'qcd09_pt2200_reco_42,'+ 'qcd09_pt2200_reco_43,'+ 'qcd09_pt2200_reco_44,'
source['qcd09_pt2200_reco']+= 'qcd09_pt2200_reco_45,'+ 'qcd09_pt2200_reco_46,'+ 'qcd09_pt2200_reco_47,'+ 'qcd09_pt2200_reco_48,'+ 'qcd09_pt2200_reco_49,'
source['qcd09_pt2200_reco']+= 'qcd09_pt2200_reco_50,'+ 'qcd09_pt2200_reco_51,'+ 'qcd09_pt2200_reco_52,'+ 'qcd09_pt2200_reco_53,'+ 'qcd09_pt2200_reco_54,'
source['qcd09_pt2200_reco']+= 'qcd09_pt2200_reco_55,'+ 'qcd09_pt2200_reco_56,'+ 'qcd09_pt2200_reco_57,'+ 'qcd09_pt2200_reco_58,'+ 'qcd09_pt2200_reco_59,'
source['qcd09_pt2200_reco']+= 'qcd09_pt2200_reco_60,'+ 'qcd09_pt2200_reco_61,'+ 'qcd09_pt2200_reco_62,'+ 'qcd09_pt2200_reco_63,'+ 'qcd09_pt2200_reco_64,'
source['qcd09_pt2200_reco']+= 'qcd09_pt2200_reco_65,'+ 'qcd09_pt2200_reco_66,'+ 'qcd09_pt2200_reco_67,'+ 'qcd09_pt2200_reco_68,'+ 'qcd09_pt2200_reco_69,'
source['qcd09_pt2200_reco']+= 'qcd09_pt2200_reco_70,'+ 'qcd09_pt2200_reco_71,'+ 'qcd09_pt2200_reco_72,'+ 'qcd09_pt2200_reco_73,'+ 'qcd09_pt2200_reco_74,'
source['qcd09_pt2200_reco']+= 'qcd09_pt2200_reco_75,'+ 'qcd09_pt2200_reco_76,'+ 'qcd09_pt2200_reco_77,'+ 'qcd09_pt2200_reco_78,'+ 'qcd09_pt2200_reco_79,'
source['qcd09_pt2200_reco']+= 'qcd09_pt2200_reco_80,'+ 'qcd09_pt2200_reco_81,'+ 'qcd09_pt2200_reco_82,'+ 'qcd09_pt2200_reco_83,'+ 'qcd09_pt2200_reco_84,'
source['qcd09_pt2200_reco']+= 'qcd09_pt2200_reco_85,'+ 'qcd09_pt2200_reco_86,'+ 'qcd09_pt2200_reco_87,'+ 'qcd09_pt2200_reco_88,'+ 'qcd09_pt2200_reco_89,'
source['qcd09_pt2200_reco']+= 'qcd09_pt2200_reco_90,'+ 'qcd09_pt2200_reco_91,'+ 'qcd09_pt2200_reco_92,'+ 'qcd09_pt2200_reco_93,'+ 'qcd09_pt2200_reco_94,'
source['qcd09_pt2200_reco']+= 'qcd09_pt2200_reco_95,'+ 'qcd09_pt2200_reco_96,'+ 'qcd09_pt2200_reco_97'

## /mc/Summer09/QCD_Pt3000/GEN-SIM-RECO/MC_31X_V3-v1
from TopAnalysis.Configuration.qcd09_pt3000_reco import *
evts  ['qcd09_pt3000_reco'] = 1041480      ## number of produced events
xsec  ['qcd09_pt3000_reco'] = 0.000008595  ## NLO in pb from configfile
eff   ['qcd09_pt3000_reco'] = 1.0          ## generator efficiency on gen level
sizes ['qcd09_pt3000_reco'] = 'blocks'
source['qcd09_pt3000_reco'] = 'qcd09_pt3000_reco_0,' + 'qcd09_pt3000_reco_1,' + 'qcd09_pt3000_reco_2,' + 'qcd09_pt3000_reco_3,' + 'qcd09_pt3000_reco_4,'
source['qcd09_pt3000_reco']+= 'qcd09_pt3000_reco_5,' + 'qcd09_pt3000_reco_6,' + 'qcd09_pt3000_reco_7,' + 'qcd09_pt3000_reco_8,' + 'qcd09_pt3000_reco_9,'
source['qcd09_pt3000_reco']+= 'qcd09_pt3000_reco_10,'+ 'qcd09_pt3000_reco_11,'+ 'qcd09_pt3000_reco_12,'+ 'qcd09_pt3000_reco_13,'+ 'qcd09_pt3000_reco_14,'
source['qcd09_pt3000_reco']+= 'qcd09_pt3000_reco_15,'+ 'qcd09_pt3000_reco_16,'+ 'qcd09_pt3000_reco_17,'+ 'qcd09_pt3000_reco_18,'+ 'qcd09_pt3000_reco_19,'
source['qcd09_pt3000_reco']+= 'qcd09_pt3000_reco_20,'+ 'qcd09_pt3000_reco_21,'+ 'qcd09_pt3000_reco_22,'+ 'qcd09_pt3000_reco_23,'+ 'qcd09_pt3000_reco_24,'
source['qcd09_pt3000_reco']+= 'qcd09_pt3000_reco_25,'+ 'qcd09_pt3000_reco_26,'+ 'qcd09_pt3000_reco_27,'+ 'qcd09_pt3000_reco_28,'+ 'qcd09_pt3000_reco_29,'
source['qcd09_pt3000_reco']+= 'qcd09_pt3000_reco_30,'+ 'qcd09_pt3000_reco_31,'+ 'qcd09_pt3000_reco_32,'+ 'qcd09_pt3000_reco_33,'+ 'qcd09_pt3000_reco_34,'
source['qcd09_pt3000_reco']+= 'qcd09_pt3000_reco_35,'+ 'qcd09_pt3000_reco_36,'+ 'qcd09_pt3000_reco_37,'+ 'qcd09_pt3000_reco_38,'+ 'qcd09_pt3000_reco_39,'
source['qcd09_pt3000_reco']+= 'qcd09_pt3000_reco_40,'+ 'qcd09_pt3000_reco_41,'+ 'qcd09_pt3000_reco_42,'+ 'qcd09_pt3000_reco_43,'+ 'qcd09_pt3000_reco_44,'
source['qcd09_pt3000_reco']+= 'qcd09_pt3000_reco_45,'+ 'qcd09_pt3000_reco_46,'+ 'qcd09_pt3000_reco_47,'+ 'qcd09_pt3000_reco_48,'+ 'qcd09_pt3000_reco_49,'
source['qcd09_pt3000_reco']+= 'qcd09_pt3000_reco_50,'+ 'qcd09_pt3000_reco_51,'+ 'qcd09_pt3000_reco_52,'+ 'qcd09_pt3000_reco_53,'+ 'qcd09_pt3000_reco_54,'
source['qcd09_pt3000_reco']+= 'qcd09_pt3000_reco_55'

## /mc/Summer09/QCD_Pt15/GEN-SIM-RECO/MC_31X_V3-v1
from TopAnalysis.Configuration.qcd09_pt15_pat import *
evts  ['qcd09_pt15_pat'] = 2268       ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 5665829)
xsec  ['qcd09_pt15_pat'] = 1458000000 ## NLO in pb from configfile
eff   ['qcd09_pt15_pat'] =     1.0    ## generator efficiency on gen level
sizes ['qcd09_pt15_pat'] = 'blocks'
source['qcd09_pt15_pat'] = 'qcd09_pt15_pat_0,' + 'qcd09_pt15_pat_1,' + 'qcd09_pt15_pat_2,' + 'qcd09_pt15_pat_3,' + 'qcd09_pt15_pat_4,'
source['qcd09_pt15_pat']+= 'qcd09_pt15_pat_5,' + 'qcd09_pt15_pat_6,' + 'qcd09_pt15_pat_7,' + 'qcd09_pt15_pat_8,' + 'qcd09_pt15_pat_9,'
source['qcd09_pt15_pat']+= 'qcd09_pt15_pat_10,'+ 'qcd09_pt15_pat_11'

## /mc/Summer09/QCD_Pt15-herwig/GEN-SIM-RECO/MC_31X_V3-v1
from TopAnalysis.Configuration.qcd09_pt15_pat_her import *
evts  ['qcd09_pt15_pat_her'] = 140        ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 1275377)
xsec  ['qcd09_pt15_pat_her'] = 1476000000 ## NLO in pb from configfile
eff   ['qcd09_pt15_pat_her'] =     1.0    ## generator efficiency on gen level
sizes ['qcd09_pt15_pat_her'] = 'blocks'
source['qcd09_pt15_pat_her'] = 'qcd09_pt15_pat_her_0,' + 'qcd09_pt15_pat_her_1,' + 'qcd09_pt15_pat_her_2'

## /mc/Summer09/QCD_Pt30/GEN-SIM-RECO/MC_31X_V3-v1
from TopAnalysis.Configuration.qcd09_pt30_pat import *
evts  ['qcd09_pt30_pat'] = 49578     ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 13922080)
xsec  ['qcd09_pt30_pat'] = 109000000 ## NLO in pb from configfile
eff   ['qcd09_pt30_pat'] =     1.0   ## generator efficiency on gen level
sizes ['qcd09_pt30_pat'] = 'blocks'
source['qcd09_pt30_pat'] = 'qcd09_pt30_pat_0,' + 'qcd09_pt30_pat_1,' + 'qcd09_pt30_pat_2,' + 'qcd09_pt30_pat_3,' + 'qcd09_pt30_pat_4,'
source['qcd09_pt30_pat']+= 'qcd09_pt30_pat_5,' + 'qcd09_pt30_pat_6,' + 'qcd09_pt30_pat_7,' + 'qcd09_pt30_pat_8,' + 'qcd09_pt30_pat_9,'
source['qcd09_pt30_pat']+= 'qcd09_pt30_pat_10,'+ 'qcd09_pt30_pat_11,'+ 'qcd09_pt30_pat_12,'+ 'qcd09_pt30_pat_13,'+ 'qcd09_pt30_pat_14,'
source['qcd09_pt30_pat']+= 'qcd09_pt30_pat_15,'+ 'qcd09_pt30_pat_16,'+ 'qcd09_pt30_pat_17,'+ 'qcd09_pt30_pat_18,'+ 'qcd09_pt30_pat_19,'
source['qcd09_pt30_pat']+= 'qcd09_pt30_pat_20,'+ 'qcd09_pt30_pat_21,'+ 'qcd09_pt30_pat_22,'+ 'qcd09_pt30_pat_23,'+ 'qcd09_pt30_pat_24,'
source['qcd09_pt30_pat']+= 'qcd09_pt30_pat_25,'+ 'qcd09_pt30_pat_26,'+ 'qcd09_pt30_pat_27,'+ 'qcd09_pt30_pat_28,'+ 'qcd09_pt30_pat_29,'
source['qcd09_pt30_pat']+= 'qcd09_pt30_pat_30,'+ 'qcd09_pt30_pat_31,'+ 'qcd09_pt30_pat_32,'+ 'qcd09_pt30_pat_33,'+ 'qcd09_pt30_pat_34,'
source['qcd09_pt30_pat']+= 'qcd09_pt30_pat_35,'+ 'qcd09_pt30_pat_36,'+ 'qcd09_pt30_pat_37'

## /mc/Summer09/QCD_Pt30-herwig/GEN-SIM-RECO/MC_31X_V3-v1
from TopAnalysis.Configuration.qcd09_pt30_pat_her import *
evts  ['qcd09_pt30_pat_her'] = 1430      ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 1074741)
xsec  ['qcd09_pt30_pat_her'] = 111700000 ## NLO in pb from configfile
eff   ['qcd09_pt30_pat_her'] =     1.0   ## generator efficiency on gen level
sizes ['qcd09_pt30_pat_her'] = 'blocks'
source['qcd09_pt30_pat_her'] = 'qcd09_pt30_pat_her_0,' + 'qcd09_pt30_pat_her_1'

## /mc/Summer09/QCD_Pt80/GEN-SIM-RECO/MC_31X_V3-v1
from TopAnalysis.Configuration.qcd09_pt80_pat import *
evts  ['qcd09_pt80_pat'] = 85562   ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 2147800)
xsec  ['qcd09_pt80_pat'] = 1936000 ## NLO in pb from configfile
eff   ['qcd09_pt80_pat'] =     1.0 ## generator efficiency on gen level
sizes ['qcd09_pt80_pat'] = 'blocks'
source['qcd09_pt80_pat'] = 'qcd09_pt80_pat_0,' + 'qcd09_pt80_pat_1,' + 'qcd09_pt80_pat_2,' + 'qcd09_pt80_pat_3,' + 'qcd09_pt80_pat_4,'
source['qcd09_pt80_pat']+= 'qcd09_pt80_pat_5,' + 'qcd09_pt80_pat_6,' + 'qcd09_pt80_pat_7,' + 'qcd09_pt80_pat_8,' + 'qcd09_pt80_pat_9,'
source['qcd09_pt80_pat']+= 'qcd09_pt80_pat_10,'+ 'qcd09_pt80_pat_11'

## /mc/Summer09/QCD_Pt80-herwig/GEN-SIM-RECO/MC_31X_V3-v1
from TopAnalysis.Configuration.qcd09_pt80_pat_her import *
evts  ['qcd09_pt80_pat_her'] = 28000   ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 848200)
xsec  ['qcd09_pt80_pat_her'] = 2039000 ## NLO in pb from configfile
eff   ['qcd09_pt80_pat_her'] =     1.0 ## generator efficiency on gen level
sizes ['qcd09_pt80_pat_her'] = 'blocks'
source['qcd09_pt80_pat_her'] = 'qcd09_pt80_pat_her_0,' + 'qcd09_pt80_pat_her_1'

## /mc/Summer09/QCD_Pt170/GEN-SIM-RECO/MC_31X_V3-v1
from TopAnalysis.Configuration.qcd09_pt170_pat import *
evts  ['qcd09_pt170_pat'] = 276846 ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 2545020)
xsec  ['qcd09_pt170_pat'] = 62510  ## NLO in pb from configfile
eff   ['qcd09_pt170_pat'] = 1.0    ## generator efficiency on gen level
sizes ['qcd09_pt170_pat'] = 'blocks'
source['qcd09_pt170_pat'] = 'qcd09_pt170_pat_0,' + 'qcd09_pt170_pat_1,' + 'qcd09_pt170_pat_2,' + 'qcd09_pt170_pat_3,' + 'qcd09_pt170_pat_4,'
source['qcd09_pt170_pat']+= 'qcd09_pt170_pat_5,' + 'qcd09_pt170_pat_6,' + 'qcd09_pt170_pat_7,' + 'qcd09_pt170_pat_8,' + 'qcd09_pt170_pat_9,'
source['qcd09_pt170_pat']+= 'qcd09_pt170_pat_10,'+ 'qcd09_pt170_pat_11,'+ 'qcd09_pt170_pat_12,'+ 'qcd09_pt170_pat_13,'+ 'qcd09_pt170_pat_14,'
source['qcd09_pt170_pat']+= 'qcd09_pt170_pat_15,'+ 'qcd09_pt170_pat_16,'+ 'qcd09_pt170_pat_17,'+ 'qcd09_pt170_pat_18,'+ 'qcd09_pt170_pat_19,'
source['qcd09_pt170_pat']+= 'qcd09_pt170_pat_20,'+ 'qcd09_pt170_pat_21,'+ 'qcd09_pt170_pat_22,'+ 'qcd09_pt170_pat_23,'+ 'qcd09_pt170_pat_24'

## /mc/Summer09/QCD_Pt170-herwig/GEN-SIM-RECO/MC_31X_V3-v1
from TopAnalysis.Configuration.qcd09_pt170_pat_her import *
evts  ['qcd09_pt170_pat_her'] = 101396 ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 765631)
xsec  ['qcd09_pt170_pat_her'] = 67860  ## NLO in pb from configfile
eff   ['qcd09_pt170_pat_her'] = 1.0    ## generator efficiency on gen level
sizes ['qcd09_pt170_pat_her'] = 'blocks'
source['qcd09_pt170_pat_her'] = 'qcd09_pt170_pat_her_0,' + 'qcd09_pt170_pat_her_1,' + 'qcd09_pt170_pat_her_2'

## /mc/Summer09/QCD_Pt300/GEN-SIM-RECO/MC_31X_V3-v1
from TopAnalysis.Configuration.qcd09_pt300_pat import *
evts  ['qcd09_pt300_pat'] =  427914  ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 2087000)
xsec  ['qcd09_pt300_pat'] =  3669    ## NLO in pb from configfile
eff   ['qcd09_pt300_pat'] =  1.0     ## generator efficiency on gen level
sizes ['qcd09_pt300_pat'] = 'blocks'
source['qcd09_pt300_pat'] = 'qcd09_pt300_pat_0,' + 'qcd09_pt300_pat_1,' + 'qcd09_pt300_pat_2,' + 'qcd09_pt300_pat_3,' + 'qcd09_pt300_pat_4,'
source['qcd09_pt300_pat']+= 'qcd09_pt300_pat_5,' + 'qcd09_pt300_pat_6,' + 'qcd09_pt300_pat_7,' + 'qcd09_pt300_pat_8,' + 'qcd09_pt300_pat_9,'
source['qcd09_pt300_pat']+= 'qcd09_pt300_pat_10,'+ 'qcd09_pt300_pat_11,'+ 'qcd09_pt300_pat_12,'+ 'qcd09_pt300_pat_13,'+ 'qcd09_pt300_pat_14,'
source['qcd09_pt300_pat']+= 'qcd09_pt300_pat_15,'+ 'qcd09_pt300_pat_16,'+ 'qcd09_pt300_pat_17,'+ 'qcd09_pt300_pat_18,'+ 'qcd09_pt300_pat_19,'
source['qcd09_pt300_pat']+= 'qcd09_pt300_pat_20,'+ 'qcd09_pt300_pat_21'

## /mc/Summer09/QCD_Pt300-herwig/GEN-SIM-RECO/MC_31X_V3-v1
from TopAnalysis.Configuration.qcd09_pt300_pat_her import *
evts  ['qcd09_pt300_pat_her'] =  129429 ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 550000)
xsec  ['qcd09_pt300_pat_her'] =  4062   ## NLO in pb from configfile
eff   ['qcd09_pt300_pat_her'] =  1.0    ## generator efficiency on gen level
sizes ['qcd09_pt300_pat_her'] = 'blocks'
source['qcd09_pt300_pat_her'] = 'qcd09_pt300_pat_her_0,' + 'qcd09_pt300_pat_her_1'

## /mc/Summer09/QCD_Pt470/GEN-SIM-RECO/MC_31X_V3-v1
from TopAnalysis.Configuration.qcd09_pt470_pat import *
evts  ['qcd09_pt470_pat'] = 546095 ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 2131360)
xsec  ['qcd09_pt470_pat'] = 315.3  ## NLO in pb from configfile
eff   ['qcd09_pt470_pat'] = 1.0    ## generator efficiency on gen level
sizes ['qcd09_pt470_pat'] = 'blocks'
source['qcd09_pt470_pat'] = 'qcd09_pt470_pat_0,' + 'qcd09_pt470_pat_1,' + 'qcd09_pt470_pat_2,' + 'qcd09_pt470_pat_3,' + 'qcd09_pt470_pat_4,'
source['qcd09_pt470_pat']+= 'qcd09_pt470_pat_5,' + 'qcd09_pt470_pat_6,' + 'qcd09_pt470_pat_7,' + 'qcd09_pt470_pat_8,' + 'qcd09_pt470_pat_9,'
source['qcd09_pt470_pat']+= 'qcd09_pt470_pat_10,'+ 'qcd09_pt470_pat_11,'+ 'qcd09_pt470_pat_12,'+ 'qcd09_pt470_pat_13,'+ 'qcd09_pt470_pat_14,'
source['qcd09_pt470_pat']+= 'qcd09_pt470_pat_15,'+ 'qcd09_pt470_pat_16,'+ 'qcd09_pt470_pat_17,'+ 'qcd09_pt470_pat_18,'+ 'qcd09_pt470_pat_19,'
source['qcd09_pt470_pat']+= 'qcd09_pt470_pat_20,'+ 'qcd09_pt470_pat_21,'+ 'qcd09_pt470_pat_22'

## /mc/Summer09/QCD_Pt470-herwig/GEN-SIM-RECO/MC_31X_V3-v1
from TopAnalysis.Configuration.qcd09_pt470_pat_her import *
evts  ['qcd09_pt470_pat_her'] = 96631 ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 315451)
xsec  ['qcd09_pt470_pat_her'] = 353.8 ## NLO in pb from configfile
eff   ['qcd09_pt470_pat_her'] = 1.0   ## generator efficiency on gen level
sizes ['qcd09_pt470_pat_her'] = 'blocks'
source['qcd09_pt470_pat_her'] = 'qcd09_pt470_pat_her_0,' + 'qcd09_pt470_pat_her_1'

## /mc/Summer09/QCD_Pt800/GEN-SIM-RECO/MC_31X_V3-v1
from TopAnalysis.Configuration.qcd09_pt800_pat import *
evts  ['qcd09_pt800_pat'] = 606724 ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 2092640)
xsec  ['qcd09_pt800_pat'] = 11.94  ## NLO in pb from configfile
eff   ['qcd09_pt800_pat'] = 1.0    ## generator efficiency on gen level
sizes ['qcd09_pt800_pat'] = 'blocks'
source['qcd09_pt800_pat'] = 'qcd09_pt800_pat_0,' + 'qcd09_pt800_pat_1,' + 'qcd09_pt800_pat_2,' + 'qcd09_pt800_pat_3,' + 'qcd09_pt800_pat_4,'
source['qcd09_pt800_pat']+= 'qcd09_pt800_pat_5,' + 'qcd09_pt800_pat_6,' + 'qcd09_pt800_pat_7,' + 'qcd09_pt800_pat_8,' + 'qcd09_pt800_pat_9,'
source['qcd09_pt800_pat']+= 'qcd09_pt800_pat_10,'+ 'qcd09_pt800_pat_11,'+ 'qcd09_pt800_pat_12,'+ 'qcd09_pt800_pat_13,'+ 'qcd09_pt800_pat_14,'
source['qcd09_pt800_pat']+= 'qcd09_pt800_pat_15,'+ 'qcd09_pt800_pat_16,'+ 'qcd09_pt800_pat_17,'+ 'qcd09_pt800_pat_18,'+ 'qcd09_pt800_pat_19,'
source['qcd09_pt800_pat']+= 'qcd09_pt800_pat_20,'+ 'qcd09_pt800_pat_21'

## /mc/Summer09/QCD_Pt800-herwig/GEN-SIM-RECO/MC_31X_V3-v1
#from TopAnalysis.Configuration.qcd09_pt800_pat_her import *

## /mc/Summer09/QCD_Pt1400/GEN-SIM-RECO/MC_31X_V3-v1
from TopAnalysis.Configuration.qcd09_pt1400_pat import *
evts  ['qcd09_pt1400_pat'] = 336347 ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 1188486)
xsec  ['qcd09_pt1400_pat'] = 0.1721 ## NLO in pb from configfile
eff   ['qcd09_pt1400_pat'] = 1.0    ## generator efficiency on gen level
sizes ['qcd09_pt1400_pat'] = 'blocks'
source['qcd09_pt1400_pat'] = 'qcd09_pt1400_pat_0,' + 'qcd09_pt1400_pat_1,' + 'qcd09_pt1400_pat_2,' + 'qcd09_pt1400_pat_3,' + 'qcd09_pt1400_pat_4,'
source['qcd09_pt1400_pat']+= 'qcd09_pt1400_pat_5,' + 'qcd09_pt1400_pat_6,' + 'qcd09_pt1400_pat_7,' + 'qcd09_pt1400_pat_8,' + 'qcd09_pt1400_pat_9,'
source['qcd09_pt1400_pat']+= 'qcd09_pt1400_pat_10,'+ 'qcd09_pt1400_pat_11,'+ 'qcd09_pt1400_pat_12,'+ 'qcd09_pt1400_pat_13'

## /mc/Summer09/QCD_Pt1400-herwig/GEN-SIM-RECO/MC_31X_V3-v1
from TopAnalysis.Configuration.qcd09_pt1400_pat_her import *
evts  ['qcd09_pt1400_pat_her'] = 46885  ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 134090)
xsec  ['qcd09_pt1400_pat_her'] = 0.1845 ## NLO in pb from configfile
eff   ['qcd09_pt1400_pat_her'] = 1.0    ## generator efficiency on gen level
sizes ['qcd09_pt1400_pat_her'] = 'blocks'
source['qcd09_pt1400_pat_her'] = 'qcd09_pt1400_pat_her_0'

## /mc/Summer09/QCD_Pt2200/GEN-SIM-RECO/MC_31X_V3-v1
from TopAnalysis.Configuration.qcd09_pt2200_pat import *
evts  ['qcd09_pt2200_pat'] = 294949   ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 1198660)
xsec  ['qcd09_pt2200_pat'] = 0.001422 ## NLO in pb from configfile
eff   ['qcd09_pt2200_pat'] = 1.0      ## generator efficiency on gen level
sizes ['qcd09_pt2200_pat'] = 'blocks'
source['qcd09_pt2200_pat'] = 'qcd09_pt2200_pat_0,' + 'qcd09_pt2200_pat_1,' + 'qcd09_pt2200_pat_2,' + 'qcd09_pt2200_pat_3,' + 'qcd09_pt2200_pat_4,'
source['qcd09_pt2200_pat']+= 'qcd09_pt2200_pat_5,' + 'qcd09_pt2200_pat_6,' + 'qcd09_pt2200_pat_7,' + 'qcd09_pt2200_pat_8,' + 'qcd09_pt2200_pat_9,'
source['qcd09_pt2200_pat']+= 'qcd09_pt2200_pat_10,'+ 'qcd09_pt2200_pat_11,'+ 'qcd09_pt2200_pat_12,'+ 'qcd09_pt2200_pat_13'

## /mc/Summer09/QCD_Pt2200-herwig/GEN-SIM-RECO/MC_31X_V3-v1
from TopAnalysis.Configuration.qcd09_pt2200_pat_her import *
evts  ['qcd09_pt2200_pat_her'] = 24148    ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 80175)
xsec  ['qcd09_pt2200_pat_her'] = 0.001493 ## NLO in pb from configfile
eff   ['qcd09_pt2200_pat_her'] = 1.0      ## generator efficiency on gen level
sizes ['qcd09_pt2200_pat_her'] = 'blocks'
source['qcd09_pt2200_pat_her'] = 'qcd09_pt2200_pat_her_0'

## /mc/Summer09/QCD_Pt3000/GEN-SIM-RECO/MC_31X_V3-v1
from TopAnalysis.Configuration.qcd09_pt3000_pat import *
evts  ['qcd09_pt3000_pat'] = 213379      ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 1041480)
xsec  ['qcd09_pt3000_pat'] = 0.000008595 ## NLO in pb from configfile
eff   ['qcd09_pt3000_pat'] = 1.0         ## generator efficiency on gen level
sizes ['qcd09_pt3000_pat'] = 'blocks'
source['qcd09_pt3000_pat'] = 'qcd09_pt3000_pat_0,' + 'qcd09_pt3000_pat_1,' + 'qcd09_pt3000_pat_2,' + 'qcd09_pt3000_pat_3,' + 'qcd09_pt3000_pat_4,'
source['qcd09_pt3000_pat']+= 'qcd09_pt3000_pat_5,' + 'qcd09_pt3000_pat_6,' + 'qcd09_pt3000_pat_7,' + 'qcd09_pt3000_pat_8,' + 'qcd09_pt3000_pat_9,'
source['qcd09_pt3000_pat']+= 'qcd09_pt3000_pat_10'

## /mc/Summer09/QCD_Pt3000-herwig/GEN-SIM-RECO/MC_31X_V3-v1
from TopAnalysis.Configuration.qcd09_pt3000_pat_her import *
evts  ['qcd09_pt3000_pat_her'] = 12881       ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 52965)
xsec  ['qcd09_pt3000_pat_her'] = 0.000009259 ## NLO in pb from configfile
eff   ['qcd09_pt3000_pat_her'] = 1.0         ## generator efficiency on gen level
sizes ['qcd09_pt3000_pat_her'] = 'blocks'
source['qcd09_pt3000_pat_her'] = 'qcd09_pt3000_pat_her_0,' + 'qcd09_pt3000_pat_her_1'

## /mc/Summer09/QCD_Pt15/GEN-SIM-RECO/MC_31X_V3_7TeV-v1
from TopAnalysis.Configuration.qcd09_pt15_PYT7_pat import *
evts  ['qcd09_pt15_PYT7_pat'] = 1132      ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 6256300)
xsec  ['qcd09_pt15_PYT7_pat'] = 876200000 ## NLO in pb from configfile
eff   ['qcd09_pt15_PYT7_pat'] = 1.0       ## generator efficiency on gen level
sizes ['qcd09_pt15_PYT7_pat'] = 'blocks'
source['qcd09_pt15_PYT7_pat'] = 'qcd09_pt15_PYT7_pat_0,' + 'qcd09_pt15_PYT7_pat_1'

## /mc/Summer09/QCD_Pt30/GEN-SIM-RECO/MC_31X_V3_7TeV-v1
from TopAnalysis.Configuration.qcd09_pt30_PYT7_pat import *
evts  ['qcd09_pt30_PYT7_pat'] = 10666    ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 5238992)
xsec  ['qcd09_pt30_PYT7_pat'] = 60410000 ## NLO in pb from configfile
eff   ['qcd09_pt30_PYT7_pat'] = 1.0       ## generator efficiency on gen level
sizes ['qcd09_pt30_PYT7_pat'] = 'blocks'
source['qcd09_pt30_PYT7_pat'] = 'qcd09_pt30_PYT7_pat_0,' + 'qcd09_pt30_PYT7_pat_1,' + 'qcd09_pt30_PYT7_pat_2,' + 'qcd09_pt30_PYT7_pat_3'

## /mc/Summer09/QCD_Pt80/GEN-SIM-RECO/MC_31X_V3_7TeV-v1
from TopAnalysis.Configuration.qcd09_pt80_PYT7_pat import *
evts  ['qcd09_pt80_PYT7_pat'] = 102634  ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 3203440)
xsec  ['qcd09_pt80_PYT7_pat'] = 923800  ## NLO in pb from configfile
eff   ['qcd09_pt80_PYT7_pat'] = 1.0     ## generator efficiency on gen level
sizes ['qcd09_pt80_PYT7_pat'] = 'blocks'
source['qcd09_pt80_PYT7_pat'] = 'qcd09_pt80_PYT7_pat_0,' + 'qcd09_pt80_PYT7_pat_1,' + 'qcd09_pt80_PYT7_pat_2'

## /mc/Summer09/QCD_Pt170/GEN-SIM-RECO/MC_31X_V3_7TeV-v1
from TopAnalysis.Configuration.qcd09_pt170_PYT7_pat import *
evts  ['qcd09_pt170_PYT7_pat'] = 330086  ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 3132800)
xsec  ['qcd09_pt170_PYT7_pat'] = 25470   ## NLO in pb from configfile
eff   ['qcd09_pt170_PYT7_pat'] = 1.0     ## generator efficiency on gen level
sizes ['qcd09_pt170_PYT7_pat'] = 'blocks'
source['qcd09_pt170_PYT7_pat'] = 'qcd09_pt170_PYT7_pat_0,' + 'qcd09_pt170_PYT7_pat_1,' + 'qcd09_pt170_PYT7_pat_2'

## /mc/Summer09/QCD_Pt300/GEN-SIM-RECO/MC_31X_V3_7TeV-v1
from TopAnalysis.Configuration.qcd09_pt300_PYT7_pat import *
evts  ['qcd09_pt300_PYT7_pat'] = 544775 ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 3274202)
xsec  ['qcd09_pt300_PYT7_pat'] = 1256   ## NLO in pb from configfile
eff   ['qcd09_pt300_PYT7_pat'] = 1.0    ## generator efficiency on gen level
sizes ['qcd09_pt300_PYT7_pat'] = 'blocks'
source['qcd09_pt300_PYT7_pat'] = 'qcd09_pt300_PYT7_pat_0,' + 'qcd09_pt300_PYT7_pat_1,' + 'qcd09_pt300_PYT7_pat_2,' + 'qcd09_pt300_PYT7_pat_3,' + 'qcd09_pt300_PYT7_pat_4,'
source['qcd09_pt300_PYT7_pat']+= 'qcd09_pt300_PYT7_pat_5,' + 'qcd09_pt300_PYT7_pat_6,' + 'qcd09_pt300_PYT7_pat_7,' + 'qcd09_pt300_PYT7_pat_8,' + 'qcd09_pt300_PYT7_pat_9,'
source['qcd09_pt300_PYT7_pat']+= 'qcd09_pt300_PYT7_pat_10,' + 'qcd09_pt300_PYT7_pat_11,' + 'qcd09_pt300_PYT7_pat_12,' + 'qcd09_pt300_PYT7_pat_13,' + 'qcd09_pt300_PYT7_pat_14,'
source['qcd09_pt300_PYT7_pat']+= 'qcd09_pt300_PYT7_pat_15,' + 'qcd09_pt300_PYT7_pat_16,' + 'qcd09_pt300_PYT7_pat_17'

## /mc/Summer09/QCD_Pt470/GEN-SIM-RECO/MC_31X_V3_7TeV-v1
from TopAnalysis.Configuration.qcd09_pt470_PYT7_pat import *
evts  ['qcd09_pt470_PYT7_pat'] = 430366  ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 2143390)
xsec  ['qcd09_pt470_PYT7_pat'] = 87.98   ## NLO in pb from configfile
eff   ['qcd09_pt470_PYT7_pat'] = 1.0     ## generator efficiency on gen level
sizes ['qcd09_pt470_PYT7_pat'] = 'blocks'
source['qcd09_pt470_PYT7_pat'] = 'qcd09_pt470_PYT7_pat_0,' + 'qcd09_pt470_PYT7_pat_1,' + 'qcd09_pt470_PYT7_pat_2,' + 'qcd09_pt470_PYT7_pat_3,' + 'qcd09_pt470_PYT7_pat_4,'
source['qcd09_pt470_PYT7_pat']+= 'qcd09_pt470_PYT7_pat_5,' + 'qcd09_pt470_PYT7_pat_6,' + 'qcd09_pt470_PYT7_pat_7,' + 'qcd09_pt470_PYT7_pat_8,' + 'qcd09_pt470_PYT7_pat_9,'
source['qcd09_pt470_PYT7_pat']+= 'qcd09_pt470_PYT7_pat_10,' + 'qcd09_pt470_PYT7_pat_11,' + 'qcd09_pt470_PYT7_pat_12,' + 'qcd09_pt470_PYT7_pat_13,' + 'qcd09_pt470_PYT7_pat_14'

## /mc/Summer09/QCD_Pt800/GEN-SIM-RECO/MC_31X_V3_7TeV-v1
from TopAnalysis.Configuration.qcd09_pt800_PYT7_pat import *
evts  ['qcd09_pt800_PYT7_pat'] = 457296  ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 2143921)
xsec  ['qcd09_pt800_PYT7_pat'] = 2.186   ## NLO in pb from configfile
eff   ['qcd09_pt800_PYT7_pat'] = 1.0     ## generator efficiency on gen level
sizes ['qcd09_pt800_PYT7_pat'] = 'blocks'
source['qcd09_pt800_PYT7_pat'] = 'qcd09_pt800_PYT7_pat_0,' + 'qcd09_pt800_PYT7_pat_1,' + 'qcd09_pt800_PYT7_pat_2'

## /mc/Summer09/QCD_Pt1400/GEN-SIM-RECO/MC_31X_V3_7TeV-v1
from TopAnalysis.Configuration.qcd09_pt1400_PYT7_pat import *
evts  ['qcd09_pt1400_PYT7_pat'] = 222633   ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 1184123)
xsec  ['qcd09_pt1400_PYT7_pat'] = 0.01122  ## NLO in pb from configfile
eff   ['qcd09_pt1400_PYT7_pat'] = 1.0      ## generator efficiency on gen level
sizes ['qcd09_pt1400_PYT7_pat'] = 'blocks'
source['qcd09_pt1400_PYT7_pat'] = 'qcd09_pt1400_PYT7_pat_0,' + 'qcd09_pt1400_PYT7_pat_1,' + 'qcd09_pt1400_PYT7_pat_2'

## /mc/Summer09/QCD_Pt15-herwig/GEN-SIM-RECO/MC_31X_V3_7TeV-v1
from TopAnalysis.Configuration.qcd09_pt15_HER7_pat import *
evts  ['qcd09_pt15_HER7_pat'] = 138       ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 1517806)
xsec  ['qcd09_pt15_HER7_pat'] = 893300000 ## NLO in pb from configfile
eff   ['qcd09_pt15_HER7_pat'] = 1.0       ## generator efficiency on gen level
sizes ['qcd09_pt15_HER7_pat'] = 'blocks'
source['qcd09_pt15_HER7_pat'] = 'qcd09_pt15_HER7_pat_0,' + 'qcd09_pt15_HER7_pat_1'

## /mc/Summer09/QCD_Pt30-herwig/GEN-SIM-RECO/MC_31X_V3_7TeV-v1
#from TopAnalysis.Configuration.qcd09_pt30_HER7_pat import *

## /mc/Summer09/QCD_Pt80-herwig/GEN-SIM-RECO/MC_31X_V3_7TeV-v1
#from TopAnalysis.Configuration.qcd09_pt80_HER7_pat import *

## /mc/Summer09/QCD_Pt170-herwig/GEN-SIM-RECO/MC_31X_V3_7TeV-v1
from TopAnalysis.Configuration.qcd09_pt170_HER7_pat import *
evts  ['qcd09_pt170_HER7_pat'] = 111615  ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 890505)
xsec  ['qcd09_pt170_HER7_pat'] = 28030   ## NLO in pb from configfile
eff   ['qcd09_pt170_HER7_pat'] = 1.0     ## generator efficiency on gen level
sizes ['qcd09_pt170_HER7_pat'] = 'blocks'
source['qcd09_pt170_HER7_pat'] = 'qcd09_pt170_HER7_pat_0,' + 'qcd09_pt170_HER7_pat_1,' + 'qcd09_pt170_HER7_pat_2'

## /mc/Summer09/QCD_Pt300-herwig/GEN-SIM-RECO/MC_31X_V3_7TeV-v1
from TopAnalysis.Configuration.qcd09_pt300_HER7_pat import *
evts  ['qcd09_pt300_HER7_pat'] = 152158 ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 726035)
xsec  ['qcd09_pt300_HER7_pat'] = 1401   ## NLO in pb from configfile
eff   ['qcd09_pt300_HER7_pat'] = 1.0    ## generator efficiency on gen level
sizes ['qcd09_pt300_HER7_pat'] = 'blocks'
source['qcd09_pt300_HER7_pat'] = 'qcd09_pt300_HER7_pat_0,' + 'qcd09_pt300_HER7_pat_1'

## /mc/Summer09/QCD_Pt470-herwig/GEN-SIM-RECO/MC_31X_V3_7TeV-v1
from TopAnalysis.Configuration.qcd09_pt470_HER7_pat import *
evts  ['qcd09_pt470_HER7_pat'] = 91980  ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 361757)
xsec  ['qcd09_pt470_HER7_pat'] = 98.1   ## NLO in pb from configfile
eff   ['qcd09_pt470_HER7_pat'] = 1.0    ## generator efficiency on gen level
sizes ['qcd09_pt470_HER7_pat'] = 'blocks'
source['qcd09_pt470_HER7_pat'] = 'qcd09_pt470_HER7_pat_0,' + 'qcd09_pt470_HER7_pat_1'

## /mc/Summer09/QCD_Pt800-herwig/GEN-SIM-RECO/MC_31X_V3_7TeV-v1
#from TopAnalysis.Configuration.qcd09_pt800_HER7_pat import *

## /mc/Summer09/QCD_Pt1400-herwig/GEN-SIM-RECO/MC_31X_V3_7TeV-v1
#from TopAnalysis.Configuration.qcd09_pt1400_HER7_pat import *

## /TTbarJets-madgraph/Spring10-START3X_V26_S09-v1/AODSIM
from TopAnalysis.Configuration.ttbar10_madAOD import *
evts  ['ttbar10_madAOD'] = 1483404       ## number of produced events
xsec  ['ttbar10_madAOD'] =     165       ## LO in pb from Twiki
eff   ['ttbar10_madAOD'] =     1.0       ## generator efficiency on gen level
sizes ['ttbar10_madAOD'] = 'blocks'
source['ttbar10_madAOD'] = 'ttbar10_madAOD_0,'  + 'ttbar10_madAOD_1,'  + 'ttbar10_madAOD_2,'
source['ttbar10_madAOD']+= 'ttbar10_madAOD_3,'  + 'ttbar10_madAOD_4,'  + 'ttbar10_madAOD_5,'
source['ttbar10_madAOD']+= 'ttbar10_madAOD_6,'  + 'ttbar10_madAOD_7,'  + 'ttbar10_madAOD_8,'
source['ttbar10_madAOD']+= 'ttbar10_madAOD_9,'  + 'ttbar10_madAOD_10,' + 'ttbar10_madAOD_11,'
source['ttbar10_madAOD']+= 'ttbar10_madAOD_12,' + 'ttbar10_madAOD_13,' + 'ttbar10_madAOD_14,'
source['ttbar10_madAOD']+= 'ttbar10_madAOD_15,' + 'ttbar10_madAOD_16'

## /TTbarJets-madgraph/Spring10-START3X_V26_S09-v1/AODSIM
from TopAnalysis.Configuration.ttbar10_madPAT import *
evts  ['ttbar10_madPAT'] = 1483404       ## number of produced events
xsec  ['ttbar10_madPAT'] =     165       ## LO in pb from Twiki
eff   ['ttbar10_madPAT'] =     1.0       ## generator efficiency on gen level
sizes ['ttbar10_madPAT'] = 'blocks'
source['ttbar10_madPAT'] = 'ttbar10_madPAT_0,'  + 'ttbar10_madPAT_1,'  + 'ttbar10_madPAT_2'

## /ZJets-madgraph/Spring10-START3X_V26_S09-v1/AODSIM
from TopAnalysis.Configuration.zjets10_madAOD import *
evts  ['zjets10_madAOD'] = 1084921       ## number of produced events
xsec  ['zjets10_madAOD'] =    3110       ## LO in pb from Twiki
eff   ['zjets10_madAOD'] =     1.0       ## generator efficiency on gen level
sizes ['zjets10_madAOD'] = 'blocks'
source['zjets10_madAOD'] = 'zjets10_madAOD_0,' + 'zjets10_madAOD_1,' + 'zjets10_madAOD_2,'
source['zjets10_madAOD']+= 'zjets10_madAOD_3,' + 'zjets10_madAOD_4,' + 'zjets10_madAOD_5,'
source['zjets10_madAOD']+= 'zjets10_madAOD_6'

## /ZJets-madgraph/Spring10-START3X_V26_S09-v1/AODSIM
from TopAnalysis.Configuration.zjets10_madPAT import *
evts  ['zjets10_madPAT'] = 1084921       ## number of produced events
xsec  ['zjets10_madPAT'] =    3110       ## LO in pb from Twiki
eff   ['zjets10_madPAT'] =     1.0       ## generator efficiency on gen level
sizes ['zjets10_madPAT'] = 'blocks'
source['zjets10_madPAT'] = 'zjets10_madPAT_0,' + 'zjets10_madPAT_1,' + 'zjets10_madPAT_2'

## /WJets-madgraph/Spring10-START3X_V26_S09-v1/AODSIM
from TopAnalysis.Configuration.wjets10_madAOD import *
evts  ['wjets10_madAOD'] = 10068895       ## number of produced events
xsec  ['wjets10_madAOD'] =    28000       ## LO in pb from Twiki
eff   ['wjets10_madAOD'] =      1.0       ## generator efficiency on gen level
sizes ['wjets10_madAOD'] = 'blocks'
source['wjets10_madAOD'] = 'wjets10_madAOD_0,'  + 'wjets10_madAOD_1,'  + 'wjets10_madAOD_2,'
source['wjets10_madAOD']+= 'wjets10_madAOD_3,'  + 'wjets10_madAOD_4,'  + 'wjets10_madAOD_5,'
source['wjets10_madAOD']+= 'wjets10_madAOD_6,'  + 'wjets10_madAOD_7,'  + 'wjets10_madAOD_8,'
source['wjets10_madAOD']+= 'wjets10_madAOD_9,'  + 'wjets10_madAOD_10,' + 'wjets10_madAOD_11,'
source['wjets10_madAOD']+= 'wjets10_madAOD_12,' + 'wjets10_madAOD_13,' + 'wjets10_madAOD_14,'
source['wjets10_madAOD']+= 'wjets10_madAOD_15,' + 'wjets10_madAOD_16,' + 'wjets10_madAOD_17,'
source['wjets10_madAOD']+= 'wjets10_madAOD_18,' + 'wjets10_madAOD_19,' + 'wjets10_madAOD_20,'
source['wjets10_madAOD']+= 'wjets10_madAOD_21,' + 'wjets10_madAOD_22,' + 'wjets10_madAOD_23,'
source['wjets10_madAOD']+= 'wjets10_madAOD_24,' + 'wjets10_madAOD_25,' + 'wjets10_madAOD_26,'
source['wjets10_madAOD']+= 'wjets10_madAOD_27,' + 'wjets10_madAOD_28,' + 'wjets10_madAOD_29,'
source['wjets10_madAOD']+= 'wjets10_madAOD_30,' + 'wjets10_madAOD_31,' + 'wjets10_madAOD_32,'
source['wjets10_madAOD']+= 'wjets10_madAOD_33,' + 'wjets10_madAOD_34,' + 'wjets10_madAOD_35,'
source['wjets10_madAOD']+= 'wjets10_madAOD_36,' + 'wjets10_madAOD_37,' + 'wjets10_madAOD_38,'
source['wjets10_madAOD']+= 'wjets10_madAOD_39,' + 'wjets10_madAOD_40,' + 'wjets10_madAOD_41,'
source['wjets10_madAOD']+= 'wjets10_madAOD_42,' + 'wjets10_madAOD_43,' + 'wjets10_madAOD_44,'
source['wjets10_madAOD']+= 'wjets10_madAOD_45,' + 'wjets10_madAOD_46,' + 'wjets10_madAOD_47,'
source['wjets10_madAOD']+= 'wjets10_madAOD_48,' + 'wjets10_madAOD_49,' + 'wjets10_madAOD_50,'
source['wjets10_madAOD']+= 'wjets10_madAOD_51,' + 'wjets10_madAOD_52,' + 'wjets10_madAOD_53,'
source['wjets10_madAOD']+= 'wjets10_madAOD_54,' + 'wjets10_madAOD_55,' + 'wjets10_madAOD_56'

## /TTbar-mcatnlo/Spring10-START3X_V26_S09-v2/AODSIM
from TopAnalysis.Configuration.ttbar10_nloAOD import *
evts  ['ttbar10_nloAOD'] =  991694       ## number of produced events
xsec  ['ttbar10_nloAOD'] =     165       ## LO in pb from Twiki
eff   ['ttbar10_nloAOD'] =     1.0       ## generator efficiency on gen level
sizes ['ttbar10_nloAOD'] = 'blocks'
source['ttbar10_nloAOD'] = 'ttbar10_nloAOD_0,'  + 'ttbar10_nloAOD_1,'  + 'ttbar10_nloAOD_2,'
source['ttbar10_nloAOD']+= 'ttbar10_nloAOD_3,'  + 'ttbar10_nloAOD_4,'  + 'ttbar10_nloAOD_5,'
source['ttbar10_nloAOD']+= 'ttbar10_nloAOD_6,'  + 'ttbar10_nloAOD_7,'  + 'ttbar10_nloAOD_8,'
source['ttbar10_nloAOD']+= 'ttbar10_nloAOD_9'

## /TTbar-mcatnlo/Spring10-START3X_V26_S09-v2/AODSIM
from TopAnalysis.Configuration.ttbar10_nloPAT import *
evts  ['ttbar10_nloPAT'] =  991694       ## number of produced events
xsec  ['ttbar10_nloPAT'] =     165       ## LO in pb from Twiki
eff   ['ttbar10_nloPAT'] =     1.0       ## generator efficiency on gen level
sizes ['ttbar10_nloPAT'] = 'blocks'
source['ttbar10_nloPAT'] = 'ttbar10_nloPAT_0,'  + 'ttbar10_nloPAT_1'

## /InclusiveMu15/Spring10-START3X_V26_S09-v1/AODSIM
from TopAnalysis.Configuration.qcd10_pytAOD import *
evts  ['qcd10_pytAOD'] =   4377187       ## number of produced events
xsec  ['qcd10_pytAOD'] = 296900000       ## LO in pb from Twiki
eff   ['qcd10_pytAOD'] =   0.00037       ## generator efficiency on gen level
sizes ['qcd10_pytAOD'] = 'blocks'
source['qcd10_pytAOD'] = 'qcd10_pytAOD_0,'  + 'qcd10_pytAOD_1,'  + 'qcd10_pytAOD_2,'
source['qcd10_pytAOD']+= 'qcd10_pytAOD_3,'  + 'qcd10_pytAOD_4,'  + 'qcd10_pytAOD_5,'
source['qcd10_pytAOD']+= 'qcd10_pytAOD_6,'  + 'qcd10_pytAOD_7,'  + 'qcd10_pytAOD_8,'
source['qcd10_pytAOD']+= 'qcd10_pytAOD_9,'  + 'qcd10_pytAOD_10,' + 'qcd10_pytAOD_11,'
source['qcd10_pytAOD']+= 'qcd10_pytAOD_12,' + 'qcd10_pytAOD_13,' + 'qcd10_pytAOD_14,'
source['qcd10_pytAOD']+= 'qcd10_pytAOD_15,' + 'qcd10_pytAOD_16,' + 'qcd10_pytAOD_17,'
source['qcd10_pytAOD']+= 'qcd10_pytAOD_18,' + 'qcd10_pytAOD_19,' + 'qcd10_pytAOD_20,'
source['qcd10_pytAOD']+= 'qcd10_pytAOD_21,' + 'qcd10_pytAOD_22,' + 'qcd10_pytAOD_23,'
source['qcd10_pytAOD']+= 'qcd10_pytAOD_24,' + 'qcd10_pytAOD_25,' + 'qcd10_pytAOD_26,'
source['qcd10_pytAOD']+= 'qcd10_pytAOD_27,' + 'qcd10_pytAOD_28,' + 'qcd10_pytAOD_29,'
source['qcd10_pytAOD']+= 'qcd10_pytAOD_30,' + 'qcd10_pytAOD_31,' + 'qcd10_pytAOD_32,'
source['qcd10_pytAOD']+= 'qcd10_pytAOD_33,' + 'qcd10_pytAOD_34,' + 'qcd10_pytAOD_35,'
source['qcd10_pytAOD']+= 'qcd10_pytAOD_36,' + 'qcd10_pytAOD_37,' + 'qcd10_pytAOD_38,'
source['qcd10_pytAOD']+= 'qcd10_pytAOD_39,' + 'qcd10_pytAOD_40,' + 'qcd10_pytAOD_41,'
source['qcd10_pytAOD']+= 'qcd10_pytAOD_42,' + 'qcd10_pytAOD_43,' + 'qcd10_pytAOD_44,'
source['qcd10_pytAOD']+= 'qcd10_pytAOD_45,' + 'qcd10_pytAOD_46,' + 'qcd10_pytAOD_47,'
source['qcd10_pytAOD']+= 'qcd10_pytAOD_48,' + 'qcd10_pytAOD_49,' + 'qcd10_pytAOD_50,'
source['qcd10_pytAOD']+= 'qcd10_pytAOD_51,' + 'qcd10_pytAOD_52,' + 'qcd10_pytAOD_53,'
source['qcd10_pytAOD']+= 'qcd10_pytAOD_54,' + 'qcd10_pytAOD_55,' + 'qcd10_pytAOD_56,'
source['qcd10_pytAOD']+= 'qcd10_pytAOD_57,' + 'qcd10_pytAOD_58,' + 'qcd10_pytAOD_59,'
source['qcd10_pytAOD']+= 'qcd10_pytAOD_60,' + 'qcd10_pytAOD_61,' + 'qcd10_pytAOD_62,'
source['qcd10_pytAOD']+= 'qcd10_pytAOD_63,' + 'qcd10_pytAOD_64,' + 'qcd10_pytAOD_65,'
source['qcd10_pytAOD']+= 'qcd10_pytAOD_66,' + 'qcd10_pytAOD_67,' + 'qcd10_pytAOD_68,'
source['qcd10_pytAOD']+= 'qcd10_pytAOD_69,' + 'qcd10_pytAOD_70'

