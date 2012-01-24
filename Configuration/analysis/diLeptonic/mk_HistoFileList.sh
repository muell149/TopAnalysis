#!/bin/zsh

rm FileLists/Histo*

foreach sample (run ttbarsignal ttbarbg single ww wz zz dytautau dyee dymumu wtolnu qcd)

   foreach channel (ee emu mumu)
      
      foreach Syst  (Nominal JESUP JESDOWN RESUP RESDOWN)

      ls -1 selectionRoot/$Syst/$channel/$sample*.root >> FileLists/HistoFileList_$Syst\_$channel.txt
      ls -1 selectionRoot/$Syst/$channel/$sample*.root >> FileLists/HistoFileList_$Syst\_combined.txt
      
      end

   end

end
