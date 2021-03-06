#!/bin/sh

SCRIPT=$(readlink -f $0)
SCRIPTPATH=$(dirname "$SCRIPT")
BIN="@CMAKE_INSTALL_PREFIX@/bin"

if [ `hostname | grep "naf.desy.de"` ]; then
    echo "Running on the NAF - so let's submit our jobs, job output will be stored in batch_output/..."
    mkdir -p "batch_output"

    #define wait function - on the NAF, we just qsub. So let's wait until jobs have been submitted
    w() {
        wait
    }

    isNAF=1
    LA="qsub -@ $SCRIPTPATH/qsubParams.txt $BIN/load_Analysis"
    HISTO="qsub -@ $SCRIPTPATH/qsubParams.txt -l h_vmem=6000M $BIN/Histo"
else
    w() {
        while [ `ps ax | grep -E 'load_Analysis|Histo' | wc -l` -gt 10 ]; do
            sleep 1;
        done
    }

    isNAF=0
    LA=$BIN/load_Analysis
    HISTO=$BIN/Histo
fi
