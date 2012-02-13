#!/bin/zsh

for i in mumu emu ee
do 

    rm -f eventCount_$i.txt 2>/dev/null
    mkdir -p mergedRoot/$i

    cp naf*$i*/$i_*.root mergedRoot/$i
    cp naf*$i*/$i\_*.txt mergedRoot/$i

    ls mergedRoot/$i/$i*.root >list_$i.txt
    cat list_$i.txt | awk -F $i\_ '{print $NF}' | awk '{sub(/.root/,"");print}'>samples_$i.txt


    for f in $(cat list_$i.txt | awk '{sub(/.root/,".txt");print}'); do 
        kf=`grep 'totalKinematicsFilter' "$f" 2> /dev/null | head -n1`
        if [ ! -z "$kf" ] ; then
            echo "$kf" | awk '{print $5}' >> eventCount_$i.txt
        else
            perl -nle '/Events total =\s*(\d+)/ && print $1' < $f >> eventCount_$i.txt
        fi
    done

    paste list_$i.txt samples_$i.txt eventCount_$i.txt > lumi_$i.txt

done

rm mergedRoot/ee/emu* 
rm mergedRoot/mumu/emu*