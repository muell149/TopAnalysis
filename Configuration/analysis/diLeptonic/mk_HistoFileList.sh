#!/bin/zsh

rm FileLists/Histo*
#note that this order will be the order of the data samples in the stack
foreach sample (run ttbarsignal ttbarbg single ww wz zz dytautau dyee dymumu wtolnu qcd)

   foreach channel (ee emu mumu)
      
      foreach Syst  (Nominal JESUP JESDOWN RESUP RESDOWN PU_UP PU_DOWN)

      ls -1 selectionRoot/$Syst/$channel/$sample*.root >> FileLists/HistoFileList_$Syst\_$channel.txt
      ls -1 selectionRoot/$Syst/$channel/$sample*.root >> FileLists/HistoFileList_$Syst\_combined.txt
      
      end

   end

end
