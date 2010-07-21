#!/bin/sh

if [ ! $1 ]
    then
    echo "Please specify file containing the TrigReport or use --help"
    exit 0
fi

if [ $1 = "--help" ]
    then
    echo "The file containig the TrigReport must be given as parameter to this script."
    echo "Example:"
    echo "[First] cmsRun TopAnalysis/TopFilter/test/testSemiLepMuonSelection_cfg.py > out.txt 2>> out.txt"
    echo "[Then ] TopAnalysis/TopFilter/test/cutFlowFromTrigReport.sh out.txt \
                   > TopAnalysis/TopFilter/test/testSemiLepMuonSelection-reference.txt"
    exit 0
fi

## look for beginning of desired summary table
start="TrigReport............Modules.in.Path:.p1"
a=`sed -ne /$start/= $1`

## determine end of desired summary table from beginning of next table
end="TrigReport............Module.Summary"
z=`sed -ne /$end/= $1`
z=`expr $z - 2`

## output table (from line a to z)
head -n $z $1 | tail -n+$a
