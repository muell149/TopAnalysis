#!/bin/sh
if [ $# -eq 0 -o $# -eq 1 -a $1 = 'submit' ] 
    then
    submit --cmd 'configRunner --cfg 'TopAnalysis/Configuration/analysis/semiLeptonic/validateTop_cfg.py' -p ttbarx09_nlo7 -e    200 -o validate' -n  1 --name validateTop
    submit --cmd 'configRunner --cfg 'TopAnalysis/Configuration/analysis/semiLeptonic/validateTop_cfg.py' -p zjets09_pat7  -e   3100 -o validate' -n  1 --name validateZJet
    submit --cmd 'configRunner --cfg 'TopAnalysis/Configuration/analysis/semiLeptonic/validateTop_cfg.py' -p wjets09_pat7  -e  28000 -o validate' -n  3 --name validateWJet
    submit --cmd 'configRunner --cfg 'TopAnalysis/Configuration/analysis/semiLeptonic/validateTop_cfg.py' -p qcd09_pat7    -e 110000 -o validate' -n 10 --name validateQCD
elif [ $# -eq 1 -a $1 = 'harvest' ]
    then
    if [ ! -d 'root' ]
	then
	mkdir 'root'
    fi
    hadd validateQCD/validate_qcd09_pat7.root validateQCD/validate_*_qcd09_pat7.root
    hadd validateWJet/validate_wjets09_pat7.root validateWJet/validate_*_wjets09_pat7.root
    mv validateQCD/validate_qcd09_pat7.root      root/validate_qcd09_pat7.root
    mv validateWJet/validate_wjets09_pat7.root   root/validate_wjets09_pat7.root   
    mv validateZJet/validate_0_zjets09_pat7.root root/validate_zjets09_pat7.root
    mv validateTop/validate_0_ttbarx09_nlo7.root root/validate_ttbarx09_nlo7.root
else
    echo 'Wrong argument: you may use this script with the following arguments.'
    echo ' -submit : to submit the jobs'
    echo ' -harvest: to hadd and copy the resulting files to the root directory'
fi