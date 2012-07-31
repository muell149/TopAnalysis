#!/bin/zsh

rm FileLists/Histo*

foreach sample (run qcd dyee dymumu dytautau ww wz zz wtolnu single ttbarbg ttbarsignal)

   foreach channel (ee emu mumu)
     
       
      foreach Syst  (Nominal JESUP JESDOWN RESUP RESDOWN PU_UP PU_DOWN SCALEUP SCALEDOWN MATCHUP MATCHDOWN MASSUP MASSDOWN POWHEG MCATNLO HADUP HADDOWN BTAG_PT_UP BTAG_PT_DOWN BTAG_ETA_UP BTAG_ETA_DOWN)
      

      ls -1 selectionRoot/$Syst/$channel/$sample*.root >> FileLists/HistoFileList_$Syst\_$channel.txt
      ls -1 selectionRoot/$Syst/$channel/$sample*.root >> FileLists/HistoFileList_$Syst\_combined.txt
      
      end

   end

end
