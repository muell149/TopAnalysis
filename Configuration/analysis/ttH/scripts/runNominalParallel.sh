#!/bin/sh



if [ $# -ge 1 ] && [[ ! "$1" == "-m" ]] ; then
    echo "Option is not allowed here: $1"
    echo "Only '-m OPTION' can be used here with this script"
    exit 1
fi



source $(dirname `readlink -f $0`)/parallelTools.sh


for c in ee emu mumu; do
    w
    $LA -f dy -d 11 -c $c $@ &
    $LA -f dy -d 13 -c $c $@ &
    $LA -f dy -d 15 -c $c $@ &
    $LA -f ttbarsignalplustau.root -c $c $@ &
    $LA -f ttbarH125 -c $c $@ &
done

for c in ee emu mumu; do
    w
    $LA -f ${c}_run2012A -c $c $@ &
    $LA -f ${c}_run2012B -c $c $@ &
    $LA -f ${c}_run2012C -c $c $@ &
    $LA -f ${c}_run2012D -c $c $@ &
done 

for i in qcd single ttbarbg.root wtol wwtoall wztoall zztoall ttbarW ttbarZ; do
    w
    $LA -f $i -c ee $@ &
    $LA -f $i -c emu $@ &
    $LA -f $i -c mumu $@ &
done

wait

if [ "$isNAF" = 1 ]; then
    echo "Please check your jobs with qstat -u $USER | grep load_Analysis"
else
    echo "Processing all nominal samples finished!"
fi





