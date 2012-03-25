#!/bin/zsh

mkdir FileLists

#foreach syst (Nominal JESUP JESDOWN RESUP RESDOWN SCALEUP SCALEDOWN MATCHUP MATCHDOWN MASSUP MASSDOWN)
foreach syst (Nominal)

   echo $syst > syst.txt

   foreach channel (ee emu mumu)
      echo Nominal > viaTau.txt

      ls mergedRoot/$syst/$channel/*.root > selectionList.txt
      cp selectionList.txt FileLists/selectionList_$syst\_$channel.txt

      root -l -b -q load_Analysis.C

      rm viaTau.txt
      rm selectionList.txt

   end
   
   foreach channel (ee emu mumu)
      echo viaTau > viaTau.txt

      ls mergedRoot/$syst/$channel/*ttbarsignal*.root > selectionList.txt
      cp selectionList.txt FileLists/selectionList_$syst\_$channel\_viaTau.txt

      root -l -b -q load_Analysis.C

      rm selectionList.txt
      rm viaTau.txt

   end
   
   rm syst.txt

end

#foreach syst (PU_UP PU_DOWN)
foreach syst ()
   echo $syst > syst.txt

   foreach channel (ee emu mumu)
      echo Nominal > viaTau.txt

      ls mergedRoot/Nominal/$channel/*.root > selectionList.txt
      cp selectionList.txt FileLists/selectionList_$syst\_$channel.txt

      root -l -b -q load_Analysis.C

      rm viaTau.txt
      rm selectionList.txt

   end

   foreach channel (ee emu mumu)
      echo viaTau > viaTau.txt

      ls mergedRoot/Nominal/$channel/*ttbarsignal*.root > selectionList.txt
      cp selectionList.txt FileLists/selectionList_$syst\_$channel\_viaTau.txt

      root -l -b -q load_Analysis.C

      rm selectionList.txt
      rm viaTau.txt

   end   
   
   rm syst.txt

end
