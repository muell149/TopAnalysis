#!/bin/zsh

foreach channel (ee emu mumu)
     
#   foreach syst (JESDOWN JESUP RESDOWN RESUP MATCHUP MATCHDOWN MASSUP MASSDOWN PU_UP PU_DOWN SCALEUP SCALEDOWN POWHEG)
   foreach syst (JESDOWN JESUP RESDOWN RESUP MATCHUP MASSUP MASSDOWN PU_UP PU_DOWN SCALEUP SCALEDOWN POWHEG)

   rm selectionRoot/$syst/$channel/run*
   cd selectionRoot/$syst/$channel/
   ln -s ../../Nominal/$channel/run* .
   cd ../../..
   end

end
