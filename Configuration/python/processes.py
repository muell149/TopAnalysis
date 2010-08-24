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

## /WJets-madgraph/Spring10-START3X_V26_S09-v1/AODSIM
from TopAnalysis.Configuration.wjets10_madPAT import *
evts  ['wjets10_madPAT'] = 10068895       ## number of produced events
xsec  ['wjets10_madPAT'] =    28000       ## LO in pb from Twiki
eff   ['wjets10_madPAT'] =      1.0       ## generator efficiency on gen level
sizes ['wjets10_madPAT'] = 'blocks'
source['wjets10_madPAT'] = 'wjets10_madPAT_0,'  + 'wjets10_madPAT_1,'  + 'wjets10_madPAT_2,'
source['wjets10_madPAT']+= 'wjets10_madPAT_3,'  + 'wjets10_madPAT_4,'  + 'wjets10_madPAT_5,'
source['wjets10_madPAT']+= 'wjets10_madPAT_6,'  + 'wjets10_madPAT_7,'  + 'wjets10_madPAT_8,'
source['wjets10_madPAT']+= 'wjets10_madPAT_9,'  + 'wjets10_madPAT_10,' + 'wjets10_madPAT_11,'
source['wjets10_madPAT']+= 'wjets10_madPAT_12,' + 'wjets10_madPAT_13,' + 'wjets10_madPAT_14,'
source['wjets10_madPAT']+= 'wjets10_madPAT_15,' + 'wjets10_madPAT_16,' + 'wjets10_madPAT_17,'
source['wjets10_madPAT']+= 'wjets10_madPAT_18,' + 'wjets10_madPAT_19,' + 'wjets10_madPAT_20'

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

## /InclusiveMu15/Spring10-START3X_V26_S09-v1/AODSIM
from TopAnalysis.Configuration.qcd10_pytPAT import *
evts  ['qcd10_pytPAT'] =   4377187       ## number of produced events
xsec  ['qcd10_pytPAT'] = 296900000       ## LO in pb from Twiki
eff   ['qcd10_pytPAT'] =   0.00037       ## generator efficiency on gen level
sizes ['qcd10_pytPAT'] = 'blocks'
source['qcd10_pytPAT'] = 'qcd10_pytPAT_0,'  + 'qcd10_pytPAT_1,'  + 'qcd10_pytPAT_2,'
source['qcd10_pytPAT']+= 'qcd10_pytPAT_3,'  + 'qcd10_pytPAT_4,'  + 'qcd10_pytPAT_5,'
source['qcd10_pytPAT']+= 'qcd10_pytPAT_6,'  + 'qcd10_pytPAT_7,'  + 'qcd10_pytPAT_8'

## /SingleTop_sChannel-madgraph/Spring10-START3X_V26_S09-v1/AODSIM
from TopAnalysis.Configuration.sTop10_sChannel_madAOD import *
evts  ['sTop10_sChannel_madAOD'] =  412055       ## number of produced events
xsec  ['sTop10_sChannel_madAOD'] =     4.6       ## LO in pb from Twiki
eff   ['sTop10_sChannel_madAOD'] = 0.32442       ## generator efficiency on gen level
sizes ['sTop10_sChannel_madAOD'] = 'blocks'
source['sTop10_sChannel_madAOD'] = 'sTop10_sChannel_madAOD_0,' + 'sTop10_sChannel_madAOD_1,'
source['sTop10_sChannel_madAOD']+= 'sTop10_sChannel_madAOD_2,' + 'sTop10_sChannel_madAOD_3,'
source['sTop10_sChannel_madAOD']+= 'sTop10_sChannel_madAOD_4'

## /SingleTop_sChannel-madgraph/Spring10-START3X_V26_S09-v1/AODSIM
from TopAnalysis.Configuration.sTop10_sChannel_madPAT import *
evts  ['sTop10_sChannel_madPAT'] =  412055       ## number of produced events
xsec  ['sTop10_sChannel_madPAT'] =     4.6       ## LO in pb from Twiki
eff   ['sTop10_sChannel_madPAT'] = 0.32442       ## generator efficiency on gen level
sizes ['sTop10_sChannel_madPAT'] = 'blocks'
source['sTop10_sChannel_madPAT'] = 'sTop10_sChannel_madPAT_0'

## /SingleTop_tChannel-madgraph/Spring10-START3X_V26_S09-v1/AODSIM
from TopAnalysis.Configuration.sTop10_tChannel_madAOD import *
evts  ['sTop10_tChannel_madAOD'] =  528593       ## number of produced events
xsec  ['sTop10_tChannel_madAOD'] =      63       ## LO in pb from Twiki
eff   ['sTop10_tChannel_madAOD'] = 0.32442       ## generator efficiency on gen level
sizes ['sTop10_tChannel_madAOD'] = 'blocks'
source['sTop10_tChannel_madAOD'] = 'sTop10_tChannel_madAOD_0,' + 'sTop10_tChannel_madAOD_1,'
source['sTop10_tChannel_madAOD']+= 'sTop10_tChannel_madAOD_2,' + 'sTop10_tChannel_madAOD_3,'
source['sTop10_tChannel_madAOD']+= 'sTop10_tChannel_madAOD_4'

## /SingleTop_tChannel-madgraph/Spring10-START3X_V26_S09-v1/AODSIM
from TopAnalysis.Configuration.sTop10_tChannel_madPAT import *
evts  ['sTop10_tChannel_madPAT'] =  528593       ## number of produced events
xsec  ['sTop10_tChannel_madPAT'] =      63       ## LO in pb from Twiki
eff   ['sTop10_tChannel_madPAT'] = 0.32442       ## generator efficiency on gen level
sizes ['sTop10_tChannel_madPAT'] = 'blocks'
source['sTop10_tChannel_madPAT'] = 'sTop10_tChannel_madPAT_0,'
source['sTop10_tChannel_madPAT']+= 'sTop10_tChannel_madPAT_1'

## /SingleTop_tWChannel-madgraph/Spring10-START3X_V26_S09-v1/AODSIM
from TopAnalysis.Configuration.sTop10_tWChannel_madAOD import *
evts  ['sTop10_tWChannel_madAOD'] = 466437       ## number of produced events
xsec  ['sTop10_tWChannel_madAOD'] =   10.6       ## LO in pb from Twiki
eff   ['sTop10_tWChannel_madAOD'] =    1.0       ## generator efficiency on gen level
sizes ['sTop10_tWChannel_madAOD'] = 'blocks'
source['sTop10_tWChannel_madAOD'] = 'sTop10_tWChannel_madAOD_0,' + 'sTop10_tWChannel_madAOD_1,'
source['sTop10_tWChannel_madAOD']+= 'sTop10_tWChannel_madAOD_2,' + 'sTop10_tWChannel_madAOD_3,'
source['sTop10_tWChannel_madAOD']+= 'sTop10_tWChannel_madAOD_4,' + 'sTop10_tWChannel_madAOD_5'

## /SingleTop_tWChannel-madgraph/Spring10-START3X_V26_S09-v1/AODSIM
from TopAnalysis.Configuration.sTop10_tWChannel_madPAT import *
evts  ['sTop10_tWChannel_madPAT'] = 466437       ## number of produced events
xsec  ['sTop10_tWChannel_madPAT'] =   10.6       ## LO in pb from Twiki
eff   ['sTop10_tWChannel_madPAT'] =    1.0       ## generator efficiency on gen level
sizes ['sTop10_tWChannel_madPAT'] = 'blocks'
source['sTop10_tWChannel_madPAT'] = 'sTop10_tWChannel_madPAT_0'

## /mc/Spring10/QCD_Pt15/GEN-SIM-RECO/START3X_V26_S09-v1
from TopAnalysis.Configuration.qcd10_pt15_pat import *
evts  ['qcd10_pt15_pat'] = 1086      ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 6190500)
xsec  ['qcd10_pt15_pat'] = 876200000 ## LO in pb from configfile
eff   ['qcd10_pt15_pat'] = 1.0       ## generator efficiency on gen level
sizes ['qcd10_pt15_pat'] = 'blocks'
source['qcd10_pt15_pat'] = 'qcd10_pt15_pat_0,' + 'qcd10_pt15_pat_1,' + 'qcd10_pt15_pat_2,' + 'qcd10_pt15_pat_3,' + 'qcd10_pt15_pat_4,'
source['qcd10_pt15_pat']+= 'qcd10_pt15_pat_5,' + 'qcd10_pt15_pat_6,' + 'qcd10_pt15_pat_7,' + 'qcd10_pt15_pat_8,' + 'qcd10_pt15_pat_9,' + 'qcd10_pt15_pat_10'

## /mc/Spring10/QCD_Pt30/AODSIM/START3X_V26_S09-v1
from TopAnalysis.Configuration.qcd10_pt30_pat import *
evts  ['qcd10_pt30_pat'] = 10481    ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 5269664)
xsec  ['qcd10_pt30_pat'] = 60410000 ## LO in pb from configfile
eff   ['qcd10_pt30_pat'] = 1.0      ## generator efficiency on gen level
sizes ['qcd10_pt30_pat'] = 'blocks'
source['qcd10_pt30_pat'] = 'qcd10_pt30_pat_0,' + 'qcd10_pt30_pat_1,' + 'qcd10_pt30_pat_2,' + 'qcd10_pt30_pat_3,'
source['qcd10_pt30_pat']+= 'qcd10_pt30_pat_4,' + 'qcd10_pt30_pat_5,' + 'qcd10_pt30_pat_6'

## /mc/Spring10/QCD_Pt80/AODSIM/START3X_V26_S09-v1
from TopAnalysis.Configuration.qcd10_pt80_pat import *
evts  ['qcd10_pt80_pat'] = 100318  ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 3221800)
xsec  ['qcd10_pt80_pat'] = 923800  ## LO in pb from configfile
eff   ['qcd10_pt80_pat'] = 1.0     ## generator efficiency on gen level
sizes ['qcd10_pt80_pat'] = 'blocks'
source['qcd10_pt80_pat'] = 'qcd10_pt80_pat_0,' + 'qcd10_pt80_pat_1,' + 'qcd10_pt80_pat_2,' + 'qcd10_pt80_pat_3'

## /mc/Spring10/QCD_Pt170/AODSIM/START3X_V26_S09-v1
from TopAnalysis.Configuration.qcd10_pt170_pat import *
evts  ['qcd10_pt170_pat'] = 329132  ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 3171950)
xsec  ['qcd10_pt170_pat'] = 25470   ## LO in pb from configfile
eff   ['qcd10_pt170_pat'] = 1.0     ## generator efficiency on gen level
sizes ['qcd10_pt170_pat'] = 'blocks'
source['qcd10_pt170_pat'] = 'qcd10_pt170_pat_0,' + 'qcd10_pt170_pat_1,' + 'qcd10_pt170_pat_2,' + 'qcd10_pt170_pat_3,' + 'qcd10_pt170_pat_4,'
source['qcd10_pt170_pat']+= 'qcd10_pt170_pat_5,' + 'qcd10_pt170_pat_6,' + 'qcd10_pt170_pat_7' 

## /mc/Spring10/QCD_Pt300/AODSIM/START3X_V26_S09-v1
from TopAnalysis.Configuration.qcd10_pt300_pat import *
evts  ['qcd10_pt300_pat'] = 541193 ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 3282665)
xsec  ['qcd10_pt300_pat'] = 1256   ## LO in pb from configfile
eff   ['qcd10_pt300_pat'] = 1.0    ## generator efficiency on gen level
sizes ['qcd10_pt300_pat'] = 'blocks'
source['qcd10_pt300_pat'] = 'qcd10_pt300_pat_0,' + 'qcd10_pt300_pat_1,' + 'qcd10_pt300_pat_2,' + 'qcd10_pt300_pat_3,' + 'qcd10_pt300_pat_4,'
source['qcd10_pt300_pat']+= 'qcd10_pt300_pat_5,' + 'qcd10_pt300_pat_6'

## /mc/Spring10/QCD_Pt470/AODSIM/START3X_V26_S09-v1
from TopAnalysis.Configuration.qcd10_pt470_pat import *
evts  ['qcd10_pt470_pat'] = 430842  ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 2159497)
xsec  ['qcd10_pt470_pat'] = 87.98   ## LO in pb from configfile
eff   ['qcd10_pt470_pat'] = 1.0     ## generator efficiency on gen level
sizes ['qcd10_pt470_pat'] = 'blocks'
source['qcd10_pt470_pat'] = 'qcd10_pt470_pat_0,' + 'qcd10_pt470_pat_1,' + 'qcd10_pt470_pat_2,' + 'qcd10_pt470_pat_3,' + 'qcd10_pt470_pat_4'

## /mc/Spring10/QCD_Pt800/AODSIM/START3X_V26_S09-v1
from TopAnalysis.Configuration.qcd10_pt800_pat import *
evts  ['qcd10_pt800_pat'] = 462765  ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 2181700)
xsec  ['qcd10_pt800_pat'] = 2.186   ## LO in pb from configfile
eff   ['qcd10_pt800_pat'] = 1.0     ## generator efficiency on gen level
sizes ['qcd10_pt800_pat'] = 'blocks'
source['qcd10_pt800_pat'] = 'qcd10_pt800_pat_0,' + 'qcd10_pt800_pat_1,' + 'qcd10_pt800_pat_2,' + 'qcd10_pt800_pat_3,'
source['qcd10_pt800_pat']+= 'qcd10_pt800_pat_4,' + 'qcd10_pt800_pat_5,' + 'qcd10_pt800_pat_6'

## /mc/Spring10/QCD_Pt1400/GEN-SIM-RECO/START3X_V26_S09-v1
from TopAnalysis.Configuration.qcd10_pt1400_pat import *
evts  ['qcd10_pt1400_pat'] = 221277   ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 1185024)
xsec  ['qcd10_pt1400_pat'] = 0.01122  ## LO in pb from configfile
eff   ['qcd10_pt1400_pat'] = 1.0      ## generator efficiency on gen level
sizes ['qcd10_pt1400_pat'] = 'blocks'
source['qcd10_pt1400_pat'] = 'qcd10_pt1400_pat_0,' + 'qcd10_pt1400_pat_1,' + 'qcd10_pt1400_pat_2,' + 'qcd10_pt1400_pat_3,'
source['qcd10_pt1400_pat']+= 'qcd10_pt1400_pat_4,' + 'qcd10_pt1400_pat_5,' + 'qcd10_pt1400_pat_6'

## /mc/Spring10/QCD_Pt100to250-madgraph/GEN-SIM-RECO/START3X_V26_S09-v2
from TopAnalysis.Configuration.qcd10_pt100_mad_pat import *
evts  ['qcd10_pt100_mad_pat'] = 46226   ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 10875132)
xsec  ['qcd10_pt100_mad_pat'] = 7000000 ## LO in pb from configfile
eff   ['qcd10_pt100_mad_pat'] = 1.0     ## generator efficiency on gen level
sizes ['qcd10_pt100_mad_pat'] = 'blocks'
source['qcd10_pt100_mad_pat'] = 'qcd10_pt100_mad_pat_0,' + 'qcd10_pt100_mad_pat_1,' + 'qcd10_pt100_mad_pat_2,'  + 'qcd10_pt100_mad_pat_3,'
source['qcd10_pt100_mad_pat']+= 'qcd10_pt100_mad_pat_4,' + 'qcd10_pt100_mad_pat_5,' + 'qcd10_pt100_mad_pat_6,'  + 'qcd10_pt100_mad_pat_7,'
source['qcd10_pt100_mad_pat']+= 'qcd10_pt100_mad_pat_8,' + 'qcd10_pt100_mad_pat_9,' + 'qcd10_pt100_mad_pat_10,' + 'qcd10_pt100_mad_pat_11,' + 'qcd10_pt100_mad_pat_12'

## /mc/Spring10/QCD_Pt250to500-madgraph/GEN-SIM-RECO/START3X_V26_S09-v1
from TopAnalysis.Configuration.qcd10_pt250_mad_pat import *
evts  ['qcd10_pt250_mad_pat'] = 380278  ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 4913036)
xsec  ['qcd10_pt250_mad_pat'] = 171000  ## LO in pb from configfile
eff   ['qcd10_pt250_mad_pat'] = 1.0     ## generator efficiency on gen level
sizes ['qcd10_pt250_mad_pat'] = 'blocks'
source['qcd10_pt250_mad_pat'] = 'qcd10_pt250_mad_pat_0,' + 'qcd10_pt250_mad_pat_1,' + 'qcd10_pt250_mad_pat_2,'  + 'qcd10_pt250_mad_pat_3,'
source['qcd10_pt250_mad_pat']+= 'qcd10_pt250_mad_pat_4,' + 'qcd10_pt250_mad_pat_5,' + 'qcd10_pt250_mad_pat_6,'  + 'qcd10_pt250_mad_pat_7,'
source['qcd10_pt250_mad_pat']+= 'qcd10_pt250_mad_pat_8,' + 'qcd10_pt250_mad_pat_9,' + 'qcd10_pt250_mad_pat_10,' + 'qcd10_pt250_mad_pat_11,' + 'qcd10_pt250_mad_pat_12'

## /mc/Spring10/QCD_Pt500to1000-madgraph/GEN-SIM-RECO/START3X_V26_S09-v1
from TopAnalysis.Configuration.qcd10_pt500_mad_pat import *
evts  ['qcd10_pt500_mad_pat'] = 958891  ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 4234762)
xsec  ['qcd10_pt500_mad_pat'] = 5200    ## LO in pb from configfile
eff   ['qcd10_pt500_mad_pat'] = 1.0     ## generator efficiency on gen level
sizes ['qcd10_pt500_mad_pat'] = 'blocks'
source['qcd10_pt500_mad_pat'] = 'qcd10_pt500_mad_pat_0,' + 'qcd10_pt500_mad_pat_1,' + 'qcd10_pt500_mad_pat_2,'  + 'qcd10_pt500_mad_pat_3,'
source['qcd10_pt500_mad_pat']+= 'qcd10_pt500_mad_pat_4,' + 'qcd10_pt500_mad_pat_5,' + 'qcd10_pt500_mad_pat_6,'  + 'qcd10_pt500_mad_pat_7,'
source['qcd10_pt500_mad_pat']+= 'qcd10_pt500_mad_pat_8,' + 'qcd10_pt500_mad_pat_9,' + 'qcd10_pt500_mad_pat_10'

## /mc/Spring10/QCD_Pt1000toInf-madgraph/GEN-SIM-RECO/START3X_V26_S09-v1
from TopAnalysis.Configuration.qcd10_pt1000_mad_pat import *
evts  ['qcd10_pt1000_mad_pat'] = 538493  ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 1661261)
xsec  ['qcd10_pt1000_mad_pat'] = 83      ## LO in pb from configfile
eff   ['qcd10_pt1000_mad_pat'] = 1.0     ## generator efficiency on gen level
sizes ['qcd10_pt1000_mad_pat'] = 'blocks'
source['qcd10_pt1000_mad_pat'] = 'qcd10_pt1000_mad_pat_0,' + 'qcd10_pt1000_mad_pat_1,' + 'qcd10_pt1000_mad_pat_2,' + 'qcd10_pt1000_mad_pat_3,'
source['qcd10_pt1000_mad_pat']+= 'qcd10_pt1000_mad_pat_4,' + 'qcd10_pt1000_mad_pat_5'

## /mc/Spring10/QCD_Pt15-herwig/GEN-SIM-RECO/START3X_V26_S09-v1
from TopAnalysis.Configuration.qcd10_pt15_her_pat import *
evts  ['qcd10_pt15_her_pat'] = 120       ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 1510649)
xsec  ['qcd10_pt15_her_pat'] = 893300000 ## LO in pb from configfile
eff   ['qcd10_pt15_her_pat'] = 1.0       ## generator efficiency on gen level
sizes ['qcd10_pt15_her_pat'] = 'blocks'
source['qcd10_pt15_her_pat'] = 'qcd10_pt15_her_pat_0,' + 'qcd10_pt15_her_pat_1,' + 'qcd10_pt15_her_pat_2'

## /mc/Spring10/QCD_Pt30-herwig/GEN-SIM-RECO/START3X_V26_S09-v1
from TopAnalysis.Configuration.qcd10_pt30_her_pat import *
evts  ['qcd10_pt30_her_pat'] = 1292     ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 1037467)
xsec  ['qcd10_pt30_her_pat'] = 62290000 ## LO in pb from configfile
eff   ['qcd10_pt30_her_pat'] = 1.0      ## generator efficiency on gen level
sizes ['qcd10_pt30_her_pat'] = 'blocks'
source['qcd10_pt30_her_pat'] = 'qcd10_pt30_her_pat_0,' + 'qcd10_pt30_her_pat_1'

## /mc/Spring10/QCD_Pt80-herwig/GEN-SIM-RECO/START3X_V26_S09-v1
from TopAnalysis.Configuration.qcd10_pt80_her_pat import *
evts  ['qcd10_pt80_her_pat'] = 25301  ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 797413)
xsec  ['qcd10_pt80_her_pat'] = 988700 ## LO in pb from configfile
eff   ['qcd10_pt80_her_pat'] = 1.0    ## generator efficiency on gen level
sizes ['qcd10_pt80_her_pat'] = 'blocks'
source['qcd10_pt80_her_pat'] = 'qcd10_pt80_her_pat_0'

## /mc/Spring10/QCD_Pt170-herwig/GEN-SIM-RECO/START3X_V26_S09-v1
from TopAnalysis.Configuration.qcd10_pt170_her_pat import *
evts  ['qcd10_pt170_her_pat'] = 110065  ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 895212)
xsec  ['qcd10_pt170_her_pat'] = 28030   ## LO in pb from configfile
eff   ['qcd10_pt170_her_pat'] = 1.0     ## generator efficiency on gen level
sizes ['qcd10_pt170_her_pat'] = 'blocks'
source['qcd10_pt170_her_pat'] = 'qcd10_pt170_her_pat_0,' + 'qcd10_pt170_her_pat_1,' + 'qcd10_pt170_her_pat_2'

## /mc/Spring10/QCD_Pt300-herwig/GEN-SIM-RECO/START3X_V26_S09-v1
from TopAnalysis.Configuration.qcd10_pt300_her_pat import *
evts  ['qcd10_pt300_her_pat'] = 151068 ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 730340)
xsec  ['qcd10_pt300_her_pat'] = 1401   ## LO in pb from configfile
eff   ['qcd10_pt300_her_pat'] = 1.0    ## generator efficiency on gen level
sizes ['qcd10_pt300_her_pat'] = 'blocks'
source['qcd10_pt300_her_pat'] = 'qcd10_pt300_her_pat_0,' + 'qcd10_pt300_her_pat_1,' + 'qcd10_pt300_her_pat_2,' + 'qcd10_pt300_her_pat_3,' + 'qcd10_pt300_her_pat_4,'
source['qcd10_pt300_her_pat']+= 'qcd10_pt300_her_pat_5,' + 'qcd10_pt300_her_pat_6'

## /mc/Spring10/QCD_Pt470-herwig/GEN-SIM-RECO/START3X_V26_S09-v1
from TopAnalysis.Configuration.qcd10_pt470_her_pat import *
evts  ['qcd10_pt470_her_pat'] = 90612  ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 360421)
xsec  ['qcd10_pt470_her_pat'] = 98.10  ## LO in pb from configfile
eff   ['qcd10_pt470_her_pat'] = 1.0    ## generator efficiency on gen level
sizes ['qcd10_pt470_her_pat'] = 'blocks'
source['qcd10_pt470_her_pat'] = 'qcd10_pt470_her_pat_0,' + 'qcd10_pt470_her_pat_1,' + 'qcd10_pt470_her_pat_2,' + 'qcd10_pt470_her_pat_3'

## /mc/Spring10/QCD_Pt800-herwig/GEN-SIM-RECO/START3X_V26_S09-v1
from TopAnalysis.Configuration.qcd10_pt800_her_pat import *
evts  ['qcd10_pt800_her_pat'] = 58869  ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 214651)
xsec  ['qcd10_pt800_her_pat'] = 2.374  ## LO in pb from configfile
eff   ['qcd10_pt800_her_pat'] = 1.0    ## generator efficiency on gen level
sizes ['qcd10_pt800_her_pat'] = 'blocks'
source['qcd10_pt800_her_pat'] = 'qcd10_pt800_her_pat_0,' + 'qcd10_pt800_her_pat_1,' + 'qcd10_pt800_her_pat_2,' + 'qcd10_pt800_her_pat_3'

## /mc/Spring10/QCD_Pt1400-herwig/GEN-SIM-RECO/START3X_V26_S09-v1
from TopAnalysis.Configuration.qcd10_pt1400_her_pat import *
evts  ['qcd10_pt1400_her_pat'] = 27288    ## number of produced events (preselected min. 6 jets pt > 20 GeV, before 114280)
xsec  ['qcd10_pt1400_her_pat'] = 0.01176  ## LO in pb from configfile
eff   ['qcd10_pt1400_her_pat'] = 1.0      ## generator efficiency on gen level
sizes ['qcd10_pt1400_her_pat'] = 'blocks'
source['qcd10_pt1400_her_pat'] = 'qcd10_pt1400_her_pat_0'

