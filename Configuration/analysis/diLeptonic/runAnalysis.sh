#!/bin/zsh

mkdir FileLists

foreach syst (Nominal JESUP JESDOWN RESUP RESDOWN SCALEUP SCALEDOWN MATCHUP MATCHDOWN MASSUP MASSDOWN)

   echo $syst > syst.txt

   foreach channel (ee emu mumu)

      ls mergedRoot/$syst/$channel/*.root > selectionList.txt
      cp selectionList.txt FileLists/selectionList_$syst\_$channel.txt

      root -l -b -q load_Analysis.C

   end
   
   rm syst.txt

end

foreach syst (PU_UP PU_DOWN)

   echo $syst > syst.txt

   foreach channel (ee emu mumu)

      ls mergedRoot/Nominal/$channel/*.root > selectionList.txt
      cp selectionList.txt FileLists/selectionList_$syst\_$channel.txt

      root -l -b -q load_Analysis.C

   end
   
   rm syst.txt

end
