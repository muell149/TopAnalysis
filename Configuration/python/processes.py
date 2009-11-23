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
