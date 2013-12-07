#!/bin/sh


if [ $# -ge 1 ] && ( [[ "$@" == *"-c"* ]] || [[ "$@" == *"-s"* ]] || [[ "$@" == *"-f"* ]] ) ; then
    echo "Options '-s', '-c', '-f' are not allowed."
    echo "You used options: $@"
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

# Run over sample with Higgs mass 125 GeV
for c in ee emu mumu; do
    $LA -f ttbarH125 -c $c $@ &
done


wait

if [ "$isNAF" = 1 ]; then
    echo "Please check your jobs with qstat -u $USER | grep load_Analysis"
else
    echo "Processing all signal variation samples finished!"
fi





