#!/bin/sh
if [ $# -eq 0 -o $# -eq 1 -a $1 = 'submit' ] 
    then
    submit --cmd 'configRunner --cfg 'TopAnalysis/Configuration/analysis/semiLeptonic/validateTop_cfg.py' -p ttbarx09_nlo7 -e   993455 -o validate' -n   1 --name validateTop
    submit --cmd 'configRunner --cfg 'TopAnalysis/Configuration/analysis/semiLeptonic/validateTop_cfg.py' -p zjets09_pat7  -e  1068735 -o validate' -n   5 --name validateZJet
    submit --cmd 'configRunner --cfg 'TopAnalysis/Configuration/analysis/semiLeptonic/validateTop_cfg.py' -p wjets09_pat7  -e 11377412 -o validate' -n  10 --name validateWJet
    submit --cmd 'configRunner --cfg 'TopAnalysis/Configuration/analysis/semiLeptonic/validateTop_cfg.py' -p qcd09_pat7    -e  5340172 -o validate' -n  10 --name validateQCD
elif [ $# -eq 1 -a $1 = 'harvest' ]
    then
    if [ ! -d 'root' ]
	then
	mkdir 'root'
    fi
    hadd validateQCD/validate_qcd09_pat7.root validateQCD/validate_*_qcd09_pat7.root
    hadd validateWJet/validate_wjets09_pat7.root validateWJet/validate_*_wjets09_pat7.root
    hadd validateZJet/validate_zjets09_pat7.root validateZJet/validate_*_zjets09_pat7.root
    mv validateQCD/validate_qcd09_pat7.root      root/validate_qcd09_pat7.root
    mv validateWJet/validate_wjets09_pat7.root   root/validate_wjets09_pat7.root   
    mv validateZJet/validate_zjets09_pat7.root root/validate_zjets09_pat7.root
    mv validateTop/validate_0_ttbarx09_nlo7.root root/validate_ttbarx09_nlo7.root
else
    echo 'Wrong argument: you may use this script with the following arguments.'
    echo ' -submit : to submit the jobs'
    echo ' -harvest: to hadd and copy the resulting files to the root directory'
fi