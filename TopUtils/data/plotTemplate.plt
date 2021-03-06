$ -- configBlockIO -- $
$=====================================================================
$
$ input/output files
$
$=====================================================================

  histInput    = analyzeMuon.hist                                     $ hist file, which contains the names of the 
                                                                      $ histograms to be plottet 
  rootInput    = analyzeSemiLeptonicEvents_test.root                  $ root input file(s) corresponding to samples
$                analyzeSemiLeptonicEvents_sig.root                   $ (separated by blanks);

  inputDirs    = muonSample                                           $ directory in which the histograms are kept
                 muonCutKin                                           $ in within the root file; for edm::Analyzers 
                                                                      $ this  corresponds to the module name of the 
                                                                      $ Analyzer in the cfg file (separated by blanks)
  histFilter   = iso                                                  $ list of filter strings; only histograms con-
                                                                      $ taining this stings as substrings are plotted
                                                                      $ (separated by blanks)
  filterOption = begins                                               $ histogram filter option ('begins', 'ends' & 
                                                                      $ 'contains' are supported
  rootOutput   =                                                      $ root output file to write histograms to
                                                                      $
  outputDir    =                                                      $ output directory in root output file 
                                                                      $
  outputLabels = muonSample                                           $ output labels for multiple ps/eps files 
                 muonCutKin                                           $ (separated by blanks)
                                                                      $
                                                                      $
  writePlotsTo = .                                                    $ directory to save the plottet histograms to;
                                                                      $ '.' is the working directory
  writePlotsAs = ps                                                   $ decide wether to write histograms to [ps] or 
                                                                      $ [eps] 

$ -- configBlockHist -- $
$=====================================================================
$
$ canvas and histogram steering
$
$=====================================================================

  xLog        =                                                       $ logs can be declared for each histogram 
                                                                      $ individually; per default they are  
  yLog        =  1 1 1 1 1                                            $ switched off
                                                                      $
  xGrid       =                                                       $ grids can be declared for each histogram
                                                                      $ individually; per default they are 
  yGrid       =                                                       $ switched off

  histScale   =                                                       $ histogram scale; can be steered for each 
                                                                      $ histogram individually
  histMaximum =                                                       $ histogram maximum; can be steered for 
                                                                      $ each histogram individually
  histMinimum =  0.1  0.1  0.1  0.1  0.1                              $ histogram minimum; can be steered for 
                                                                      $ each histogram individually

  histErrors  =    0    0                                             $ draw histogram errors for given sample?

  histType    =    2    2                                             $ defines wether histogram should be plotted
                                                                      $ as line[0], with poly markers[1] or filled 
                                                                      $ [2]; default is line [0]; can be steered 
                                                                      $ for each sample individually
  histStyle   = 3004 3005                                             $ defines line or fill style for each sample

  histColor   =    2    4                                             $ defines line/marker/fill color for each 
                                                                      $ sample
  lineWidth   =    5    5                                             $ defines line width for each sample

  markerStyle =   20   21                                             $ defines marker style for each sample

  markerSize  =  2.3  2.3                                             $ defines marker size for each sample

                                                                      $ set axes titles of histograms;
  xAxes       =                                                       $ has to be givin in " and has to end with;

  yAxes       =

  legEntries = "all events";                                          $ should contain a legend entry for each 
               "after #mu kin";                                       $ sample in " and separated by ;
                                                                      $
                                                                      $
  legXLeft   = 0.25                                                   $ so far a steering of the legend coord's 
                                                                      $ is only supported globally
  legXRight  = 0.95                                                   $
                                                                      $
  legYLower  = 0.70

  legYUpper  = 0.95

