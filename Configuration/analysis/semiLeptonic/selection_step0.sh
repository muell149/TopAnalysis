submit --cmd 'configRunner --cfg TopAnalysis/Configuration/analysis/semiLeptonic/selection_step0_ttbar_cfg.py -p ttbarx0 -e 1028322 -o selection_step0 -z patSelection_step0' -n 20 --name step0_ttbar
submit --cmd 'configRunner --cfg TopAnalysis/Configuration/analysis/semiLeptonic/selection_step0_wjets_cfg.py -p wjetsx0 -e 1746727 -o selection_step0 -z patSelection_step0' -n 20 --name step0_wjets
submit --cmd 'configRunner --cfg TopAnalysis/Configuration/analysis/semiLeptonic/selection_step0_zjets_cfg.py -p zjetsx0 -e 1690137 -o selection_step0 -z patSelection_step0' -n 20 --name step0_zjets
submit --cmd 'configRunner --cfg TopAnalysis/Configuration/analysis/semiLeptonic/selection_step0_qcd_cfg.py -p qcdx0 -e 982407 -o selection_step0 -z patSelection_step0' -n 20 --name step0_qcd
