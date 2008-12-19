$ -- configBlockIO -- $
$=====================================================================
$
$ input/output files
$
$=====================================================================

  histInput    = analyzeMuon.hist                                     $ hist file, which contains the names of the 
                                                                      $ histograms to be plottet 
                                                                      $
  rootInput    = analyzeMuon.Madgraph.root                            $ root input file(s) corresponding to samples
                 analyzeMuon.RelVal.root                              $ (separated by blanks)
                                                                      $
  inputDirs    = analyzeSelMuon                                       $ directory in which the histograms are kept
                                                                      $ within the root file; for edm::Analyzers 
                                                                      $ this  corresponds to the module name of the 
                                                                      $ Analyzer in the cfg file (separated by blanks)
                                                                      $
  histFilter   = id kin iso_                                          $ list of filter strings; only histograms con-
                                                                      $ taining these stings as substrings are loaded
                                                                      $ (separated by blanks); empty means everything
                                                                      $ is plotted 
                                                                      $
  plotFilter   =                                                      $ list of filter strings; only histograms con-
                                                                      $ taining these stings as substrings are plotted
                                                                      $ (separated by blanks); empty means everything
                                                                      $ is plotted
                                                                      $
  filterOption = begins                                               $ histogram filter option ('begins', 'ends' & 
                                                                      $ 'contains' are supported
                                                                      $
  rootOutput   =                                                      $ root output file to write histograms to
                                                                      $
  outputDir    =                                                      $ output directory in root output file 
                                                                      $
  outputLabels =                                                      $ output labels for multiple ps/eps files 
                                                                      $ (separated by blanks)
                                                                      $
  writePlotsTo = .                                                    $ directory to save the plottet histograms to;
                                                                      $ '.' is the working directory
                                                                      $
  writePlotsAs = ps                                                   $ decide wether to write histograms to [ps] or 
                                                                      $ [eps] files
  outputFileName = analyzeMuonCompare				      $ gives the filename of the ps-output
	   						   	      $ the filename is 'inspect' in the case of left blank

$ -- configBlockHist -- $
$=====================================================================
$
$ canvas and histogram steering
$
$=====================================================================

  xLog         =                                                      $ logs can be declared for each histogram 
                                                                      $ individually; per default they are  
  yLog         =                                                      $ switched off
                                                                      $
                                                                      $ grids can be declared for each histogram
                                                                      $ individually; per default they are 
                                                                      $ switched off
  xGrid        = 1 1 1 1 1 1 1 1 1 1 
                 1 1 1 1 1 1 1 1 1 1   
                 1 1 1 1 1 1 1 1 1 1   
                 1 1 1 1 1 1 1 1 1 1

  yGrid        = 1 1 1 1 1 1 1 1 1 1
                 1 1 1 1 1 1 1 1 1 1   
                 1 1 1 1 1 1 1 1 1 1   
                 1 1 1 1 1 1 1 1 1 1 
                                                                      $
  histScale    = 1 1 1 1 1 1 1 1 1 1                                  $ histogram scale; can be steered for each 
                 1 1 1 1 1 1 1 1 1 1                                  $ histogram individually; empty means scale
                 1 1 1 1 1 1                                          $ is _1_
                                                                      $
  histMinimum  = 0 0 0 0 0 0 0 0 0 0                                  $ histogram minimum; can be steered for 
                 0 0 0 0 0 0 0 0 0 0                                  $ each histogram individually; empty means 
                 0 0 0 0 0 0                                          $ set to _0_
                                                                      $
  histMaximum  = .4  .3  .3  .1  .1  1.  .7  .3  .3  .1               $ histogram maximum; can be steered for 
                 .1  .6  .6  .5  .4  .4  .4  .4  .4  .4               $ each histogram individually; empty means
                 .8  .6  .2  .4  .3  .6                               $ set automatically
                                                                      $
  histErrors   =                                                      $ draw histogram errors; can be steered for 
                                                                      $ each sample; empty means no errors
                                                                      $
  histType     =    2     2                                           $ defines wether histogram should be plotted
                                                                      $ as line[0], with poly markers[1] or filled 
                                                                      $ [2]; default is line [0]; can be steered 
                                                                      $ for each sample individually
                                                                      $
  histStyle    = 3004  3005                                           $ defines line or fill style for each sample
                                                                      $
  histColor    =    2     4                                           $ defines line/marker/fill color for each 
                                                                      $ sample
                                                                      $
  lineWidth    =    5     5                                           $ defines line width for each sample
                                                                      $
  markerStyle  =   20    21                                           $ defines marker style for each sample
                                                                      $
  markerSize   =  2.3   2.3                                           $ defines marker size for each sample
                                                                      $
                                                                      $ set axes titles for each histograms;
                                                                      $ has to be givin in '"' and end with ';'
  xAxes        =

  yAxes        = "a.u.";
                 "a.u.";
                 "a.u.";
                 "a.u.";
                 "a.u.";
                 "a.u.";
                 "a.u.";
                 "a.u.";
                 "a.u.";
                 "a.u.";
                 "a.u.";
                 "a.u.";
                 "a.u.";
                 "a.u.";
                 "a.u.";
                 "a.u.";
                 "a.u.";
                 "a.u.";
                 "a.u.";
                 "a.u.";
                 "a.u.";
                 "a.u.";
                 "a.u.";
                 "a.u.";
                 "a.u.";
                 "a.u.";
                 "1/N_{muon} #Sigma (p_{t}(track)) [GeV]";
                 "1/N_{muon} #Sigma (N_{track})";
                 "1/N_{muon} #Sigma (E_{t}(tower)) [GeV]";
                 "1/N_{muon} #Sigma (N_{tower})";
                 "1/N_{muon} #Sigma (E_{t}(tower)) [GeV]";
                 "1/N_{muon} #Sigma (N_{tower})";

                                                                      $
                                                                      $ should contain a legend entry for each 
                                                                      $ sample in '"' and separated by ';'
  legEntries   = "Madgraph";                                     
                 "RelVal";
                                                                      $
  legXLeft     = 0.30                                                 $ so far a steering of the legend coord's 
                                                                      $ is only supported globally
  legXRight    = 0.90                                                 $
                                                                      $
  legYLower    = 0.80                                                 $
                                                                      $
  legYUpper    = 0.95                                                 $
