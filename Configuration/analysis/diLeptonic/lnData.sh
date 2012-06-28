#!/bin/zsh

BASEDIR=`pwd`

foreach channel (ee emu mumu)
   
   foreach syst (JESDOWN JESUP RESDOWN RESUP MATCHUP MATCHDOWN MASSUP MASSDOWN PU_UP PU_DOWN SCALEUP SCALEDOWN)   
   #foreach syst (JESDOWN JESUP RESDOWN RESUP MATCHUP MATCHDOWN MASSUP MASSDOWN PU_UP PU_DOWN SCALEUP SCALEDOWN MCNLOUP MCNLODOWN POWHEGUP POWHEGDOWN)
   #foreach syst (MCNLOUP MCNLODOWN POWHEGUP POWHEGDOWN)
   
       cd selectionRoot/$syst/$channel/
       echo
       echo "Creating Links in ... " 
       pwd
       echo 
       ln -s ../../Nominal/$channel/* .
       cd $BASEDIR
   end

end

foreach SignalSyst (MATCHUP MATCHDOWN MASSUP MASSDOWN SCALEUP SCALEDOWN)

   rm selectionRoot/$SignalSyst/*/ttbarbg.root
   rm selectionRoot/$SignalSyst/*/ttbarsignalplustau.root

end
