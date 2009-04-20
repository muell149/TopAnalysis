######################################################################
##
## define input vectors for ConfigRunner
##
######################################################################
sizes  = {}  ## sample sizes
source = {}  ## input sources

##
##
## list of allowed processes
##
##

## test slots
allowedProcesses = 'desy'    ## test slot for files at desy
allowedProcesses+= 'cern'    ## test slot for files at desy

## reco samples
allowedProcesses+= 'ttbar0'  ## ttbar madgraph (reco)
allowedProcesses+= 'ttbar1'  ## ttbar tauola   (reco)
allowedProcesses+= 'qcd0'    ## qcd   pythia   (reco)
allowedProcesses+= 'wjets1'  ## wjets madgraph (reco) fullsim
allowedProcesses+= 'zjets1'  ## zjets madgraph (reco) fullsim

## pat  samples
allowedProcesses+= 'ttbarx0' ## ttbar madgraph (pat)
allowedProcesses+= 'ttbarx1' ## ttbar madgraph (pat)
allowedProcesses+= 'qcdx0'   ## qcd   pythia   (pat)
allowedProcesses+= 'wjetsx0' ## wjets madgraph (pat) fastsim
allowedProcesses+= 'wjetsx1' ## wjets madgraph (pat) fullsim
allowedProcesses+= 'zjetsx0' ## zjets madgraph (pat) fastsim
allowedProcesses+= 'zjetsx1' ## zjets madgraph (pat) fullsim
allowedProcesses+= 'wwx0'    ## ww    madgraph (pat) fastsim
allowedProcesses+= 'wzx0'    ## wz    madgraph (pat) fastsim
allowedProcesses+= 'zzx0'    ## zz    madgraph (pat) fastsim
