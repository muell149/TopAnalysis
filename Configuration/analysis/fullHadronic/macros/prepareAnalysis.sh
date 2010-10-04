mkdir cutFlow
hadd cutFlow/QCD_pt0015.root pt0015/*.root
hadd cutFlow/QCD_pt0030.root pt0030/*.root
hadd cutFlow/QCD_pt0080.root pt0080/*.root
hadd cutFlow/QCD_pt0170.root pt0170/*.root
hadd cutFlow/QCD_pt0300.root pt0300/*.root
hadd cutFlow/QCD_pt0470.root pt0470/*.root
hadd cutFlow/QCD_pt0800.root pt0800/*.root
hadd cutFlow/QCD_pt1400.root pt1400/*.root
hadd cutFlow/QCD_pt0015_her.root pt0015_her/*.root
hadd cutFlow/QCD_pt0030_her.root pt0030_her/*.root
hadd cutFlow/QCD_pt0080_her.root pt0080_her/*.root
hadd cutFlow/QCD_pt0170_her.root pt0170_her/*.root
hadd cutFlow/QCD_pt0300_her.root pt0300_her/*.root
hadd cutFlow/QCD_pt0470_her.root pt0470_her/*.root
hadd cutFlow/QCD_pt0800_her.root pt0800_her/*.root
hadd cutFlow/QCD_pt1400_her.root pt1400_her/*.root
hadd cutFlow/QCD_pt0100_mad.root pt0100_mad/*.root
hadd cutFlow/QCD_pt0250_mad.root pt0250_mad/*.root
hadd cutFlow/QCD_pt0500_mad.root pt0500_mad/*.root
hadd cutFlow/QCD_pt1000_mad.root pt1000_mad/*.root
#hadd cutFlow/QCD_PRIVATE.root pt0015_private/*.root
hadd cutFlow/sig_nlo.root sig_nlo/*.root
hadd cutFlow/bkg_nlo.root bkg_nlo/*.root
hadd cutFlow/sig_mad.root sig_mad/*.root
hadd cutFlow/bkg_mad.root bkg_mad/*.root
hadd cutFlow/QCD_pt0015_pf.root pt0015_pf/*.root
hadd cutFlow/QCD_pt0030_pf.root pt0030_pf/*.root
hadd cutFlow/QCD_pt0080_pf.root pt0080_pf/*.root
hadd cutFlow/QCD_pt0170_pf.root pt0170_pf/*.root
hadd cutFlow/QCD_pt0300_pf.root pt0300_pf/*.root
hadd cutFlow/QCD_pt0470_pf.root pt0470_pf/*.root
hadd cutFlow/QCD_pt0800_pf.root pt0800_pf/*.root
hadd cutFlow/QCD_pt1400_pf.root pt1400_pf/*.root
hadd cutFlow/QCD_pt0015_her_pf.root pt0015_her_pf/*.root
hadd cutFlow/QCD_pt0030_her_pf.root pt0030_her_pf/*.root
hadd cutFlow/QCD_pt0080_her_pf.root pt0080_her_pf/*.root
hadd cutFlow/QCD_pt0170_her_pf.root pt0170_her_pf/*.root
hadd cutFlow/QCD_pt0300_her_pf.root pt0300_her_pf/*.root
hadd cutFlow/QCD_pt0470_her_pf.root pt0470_her_pf/*.root
hadd cutFlow/QCD_pt0800_her_pf.root pt0800_her_pf/*.root
hadd cutFlow/QCD_pt1400_her_pf.root pt1400_her_pf/*.root
hadd cutFlow/QCD_pt0100_mad_pf.root pt0100_mad_pf/*.root
hadd cutFlow/QCD_pt0250_mad_pf.root pt0250_mad_pf/*.root
hadd cutFlow/QCD_pt0500_mad_pf.root pt0500_mad_pf/*.root
hadd cutFlow/QCD_pt1000_mad_pf.root pt1000_mad_pf/*.root
#hadd cutFlow/QCD_PRIVATE_pf.root pt0015_private_pf/*.root
hadd cutFlow/sig_nlo_pf.root sig_nlo_pf/*.root
hadd cutFlow/bkg_nlo_pf.root bkg_nlo_pf/*.root
hadd cutFlow/sig_mad_pf.root sig_mad_pf/*.root
hadd cutFlow/bkg_mad_pf.root bkg_mad_pf/*.root
cd cutFlow
ln -s ../combine.C
#root -l -b -q 'combine.C++("pyt")'
#root -l -b -q 'combine.C++("pyt_pf")'
root -l -b -q 'combine.C++("pyt_offi")'
root -l -b -q 'combine.C++("pyt_offi_pf")'
root -l -b -q 'combine.C++("her")'
root -l -b -q 'combine.C++("her_pf")'
root -l -b -q 'combine.C++("mad")'
root -l -b -q 'combine.C++("mad_pf")'
cd ..
