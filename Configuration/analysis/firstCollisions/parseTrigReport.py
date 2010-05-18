#####
##### script, originally from Sal Rapp. (https://hypernews.cern.ch/HyperNews/CMS/get/swDevelopment/2276/1/2/1/1/1/1.html),
##### modified to parse different paths separately
##### $Id: parseTrigReport.py,v 1.1 2010/05/18 10:41:05 snaumann Exp $
#####
##### usage: python TopAnalysis/Configuration/analysis/firstCollisions/parseTrigReport.py Run135175/res/CMSSW_*.stdout
#####

import re
import sys
import os.path


p = re.compile(r'\W+')


def parseTrigReport(path, modules):
    print 'Path: ' + path
    for s in modules:
        nvisit = 0
        npass  = 0
        nfail  = 0
        nerror = 0
        for i in range(1,len(sys.argv) ) :
            infile = open(sys.argv[i], 'r')
            foundPath = False
            for line in infile :
                if( not foundPath ) :
                    if( line.find('TrigReport ---------- Modules in Path: ' + path) >= 0 ) :
                        foundPath = True
                else :
                    if ( line.find(s) >= 0 ) :
                        nvisit += int(p.split(line)[3])
                        npass  += int(p.split(line)[4])
                        nfail  += int(p.split(line)[5])
                        nerror += int(p.split(line)[6])
                        break
            infile.close()
        print '%20s' % (s),' : visited %10d' % nvisit,', passed %10d' % npass,', failed %10d' % nfail,', error %10d' % nerror


path = 'looseSelection'
modules = ['step1','step2','step3b','step4','step5','step6a','step6b','step6c']
parseTrigReport(path, modules)

path = 'tightSelection'
modules = ['step1','step2','step3a','step4','step5','step6a','step6b','step6c','step7']
parseTrigReport(path, modules)
