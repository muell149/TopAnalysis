#!/bin/zsh

foreach channel (ee emu mumu)
     
   foreach syst (JESDOWN JESUP RESDOWN RESUP MATCHUP MATCHDOWN MASSUP MASSDOWN PU_UP PU_DOWN SCALEUP SCALEDOWN)

   cd selectionRoot/$syst/$channel/
   ln -s ../../Nominal/$channel/* .
   cd ../../..
   end

end

foreach SignalSyst (MATCHUP MATCHDOWN MASSUP MASSDOWN SCALEUP SCALEDOWN)

   rm selectionRoot/$SignalSyst/*/ttbarbg.root
   rm selectionRoot/$SignalSyst/*/ttbarsignalplustau.root

end