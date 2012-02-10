#!/bin/zsh

foreach channel (ee emu mumu)
     
   foreach syst (JESDOWN  MASSDOWN  MATCHDOWN PU_DOWN PU_UP RESUP SCALEUP JESUP MASSUP MATCHUP PUDOWN PUUP RESDOWN SCALEDOWN)

   ln -s ~/Analysis/selectionRoot/Nominal/$channel/* selectionRoot/$syst/$channel
#   rm selectionRoot/$syst/$channel/run*
   end

end
