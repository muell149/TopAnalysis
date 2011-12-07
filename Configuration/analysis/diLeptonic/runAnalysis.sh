#!/bin/zsh

ls mergedRoot/mumu/mumu*.root > selectionlist_mumu.txt
ls mergedRoot/emu/emu*.root > selectionlist_emu.txt
ls mergedRoot/ee/ee*.root > selectionlist_ee.txt

root -l -q load_Analysis.C