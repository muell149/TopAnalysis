#!/bin/zsh

foreach channel (ee emu mumu)
     
   foreach syst (JESDOWN  MASSDOWN  MATCHDOWN PU_DOWN PU_UP RESUP SCALEUP JESUP MASSUP MATCHUP RESDOWN SCALEDOWN)

   rm selectionRoot/$syst/$channel/run*
   cd selectionRoot/$syst/$channel/
   ln -s ../../Nominal/$channel/* .
   cd ../../..
   end

end

rm selectionRoot/MATCHUP/*/ttbarbg.root
rm selectionRoot/MATCHDOWN/*/ttbarbg.root
rm selectionRoot/MASSUP/*/ttbarbg.root
rm selectionRoot/MASSDOWN/*/ttbarbg.root
rm selectionRoot/SCALEUP/*/ttbarbg.root
rm selectionRoot/SCALEDOWN/*/ttbarbg.root

rm selectionRoot/MATCHUP/*/ttbarsignalplustau.root
rm selectionRoot/MATCHDOWN/*/ttbarsignalplustau.root
rm selectionRoot/MASSUP/*/ttbarsignalplustau.root
rm selectionRoot/MASSDOWN/*/ttbarsignalplustau.root
rm selectionRoot/SCALEUP/*/ttbarsignalplustau.root
rm selectionRoot/SCALEDOWN/*/ttbarsignalplustau.root


