#!/bin/sh

w() { while [ `ps ax | grep load_HiggsAnalysis | wc -l` -gt 10 ]; do sleep 1; done }

for c in ee emu mumu; do
    ./load_HiggsAnalysis -f dy -d 11 -c $c &
    ./load_HiggsAnalysis -f dy -d 13 -c $c &
    ./load_HiggsAnalysis -f dy -d 15 -c $c &
    ./load_HiggsAnalysis -f ttbarsignalplustau.root -c $c &
    ./load_HiggsAnalysis -f ttbarH -c $c &
done

#wait


for c in ee emu mumu; do
    w
    ./load_HiggsAnalysis -f ${c}_run2012A -c $c &
    ./load_HiggsAnalysis -f ${c}_run2012B -c $c &
    ./load_HiggsAnalysis -f ${c}_run2012C -c $c &
done 

for i in qcd single ttbarbg wtol ww wz zz; do
    w
    ./load_HiggsAnalysis -f $i &
done

wait

echo "Processing all nominal samples finished!"

