#!/bin/zsh


#do the b-Tag per-jet efficiency and median calculation

echo
echo "**********************************************************************"
echo "Processing B-Tag Efficiencies ..."
echo "**********************************************************************"
echo

root -l -b -q load_BTagEff.C

echo
echo "**********************************************************************"
echo "... Finished processing B-Tag Efficiencies ..."
echo "**********************************************************************"
echo


mkdir FileLists

foreach syst (Nominal JESUP JESDOWN RESUP RESDOWN SCALEUP SCALEDOWN MATCHUP MATCHDOWN MASSUP MASSDOWN POWHEG MCATNLO)

   echo $syst > syst.txt

   foreach channel (ee emu mumu)
      echo Nominal > viaTau.txt

      ls mergedRoot/$syst/$channel/*.root > selectionList.txt
      cp selectionList.txt FileLists/selectionList_$syst\_$channel.txt

      echo
      echo "**********************************************************************"
      echo "Processing $syst / $channel ... " 
      echo "**********************************************************************"
      echo
 
      root -l -b -q load_Analysis.C

      echo
      echo "**********************************************************************"
      echo "... Finished processing $syst / $channel ... "
      echo "**********************************************************************"
      echo

      rm viaTau.txt
      rm selectionList.txt

   end
   
   foreach channel (ee emu mumu)
      echo viaTau > viaTau.txt

      ls mergedRoot/$syst/$channel/*ttbarsignal*.root > selectionList.txt
      cp selectionList.txt FileLists/selectionList_$syst\_$channel\_viaTau.txt
      
      echo 
      echo "**********************************************************************"
      echo "Processing $syst / $channel ... "
      echo "**********************************************************************"
      echo

      root -l -b -q load_Analysis.C

      echo
      echo "**********************************************************************"
      echo "... Finished processing $syst / $channel ... "
      echo "**********************************************************************"
      echo

      rm selectionList.txt
      rm viaTau.txt

   end
   
   rm syst.txt

end

foreach syst (PU_UP PU_DOWN BTAG_PT_UP BTAG_PT_DOWN BTAG_ETA_UP BTAG_ETA_DOWN BTAG_UP BTAG_DOWN)
#foreach syst ()
   echo $syst > syst.txt

   foreach channel (ee emu mumu)
      echo Nominal > viaTau.txt

      ls mergedRoot/Nominal/$channel/*.root > selectionList.txt
      cp selectionList.txt FileLists/selectionList_$syst\_$channel.txt

      echo
      echo "**********************************************************************"
      echo "Processing $syst / $channel ... "
      echo "**********************************************************************"
      echo
      
      root -l -b -q load_Analysis.C

      echo
      echo "**********************************************************************"
      echo "... Finished processing $syst / $channel ... "
      echo "**********************************************************************"
      echo

      rm viaTau.txt
      rm selectionList.txt

   end

   foreach channel (ee emu mumu)
      echo viaTau > viaTau.txt

      ls mergedRoot/Nominal/$channel/*ttbarsignal*.root > selectionList.txt
      cp selectionList.txt FileLists/selectionList_$syst\_$channel\_viaTau.txt

      echo
      echo "**********************************************************************"
      echo "Processing $syst / $channel ... "
      echo "**********************************************************************"
      echo


      root -l -b -q load_Analysis.C

      echo
      echo "**********************************************************************"
      echo "... Finished processing $syst / $channel ... "
      echo "**********************************************************************"
      echo

      rm selectionList.txt
      rm viaTau.txt

   end   
   
   rm syst.txt

end
