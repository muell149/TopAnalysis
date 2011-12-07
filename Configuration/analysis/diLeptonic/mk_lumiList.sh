#!/bin/zsh

for i in mumu emu ee

do 

mkdir -p OriginalRoot/$i

cp naf*$i*/$i_*.root OriginalRoot/$i
cp naf*$i*/$i\_*.txt OriginalRoot/$i

ls OriginalRoot/$i/$i*.root >list_$i.txt
cat list_$i.txt | awk -F $i\_ '{print $NF}' | awk '{sub(/.root/,"");print}'>samples_$i.txt
cat list_$i.txt | awk '{sub(/.root/,".txt");print}' | xargs head -n2 | perl -nle '/Events total =\s*(\d+)/ && print $1' > eventCount_$i.txt
paste list_$i.txt samples_$i.txt eventCount_$i.txt > lumi_$i.txt

done