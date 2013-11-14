#!/bin/sh



if [ $# -ge 1 ] && [[ ! "$1" == "-m" ]] ; then
    echo "Option is not allowed here: $1"
    echo "Only '-m OPTION' can be used here with this script"
    exit 1
fi



source $(dirname `readlink -f $0`)/parallelTools.sh


# Run over samples with different Higgs masses (excluding nominal sample with mass 125 GeV)
for systematic in H110 H115 H120 H1225 H1275 H130 H135 H140; do
    for c in ee emu mumu; do
        $LA -f ttbar${systematic} -c $c $@ &
    done
    w
done

for c in ee emu mumu; do
    $LA -f ttbarH125 -c $c $@ &
done


wait

if [ "$isNAF" = 1 ]; then
    echo "Please check your jobs with qstat -u $USER | grep load_Analysis"
else
    echo "Processing all signal variation samples finished!"
fi





