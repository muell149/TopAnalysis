#!/bin/sh

source $(dirname `readlink -f $0`)/parallelTools.sh

# #start the longest job first
# for syst in FullLeptMadgraphWithSpinCorrelation SemiLeptMadgraphWithSpinCorrelation HadronicMadgraphWithSpinCorrelation; do
#     for ch in ee emu mumu; do
#         $LA -f $syst -c $ch &
#         w
#     done
# done

for chann in ee emu mumu; do
    $LA -f powhegHerwig -c ${chann} -s POWHEGHERWIG &
    w
done

#these have rather low statistics, don't need to split them into ee/emu/mumu
for Syst in match mass scale powheg.root mcatnlo; do
    $LA -f $Syst &
    w
done

wait

echo "Done!"

