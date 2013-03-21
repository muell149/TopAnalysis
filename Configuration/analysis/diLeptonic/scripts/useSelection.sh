#!/bin/sh

set -e

if [ "$1" = "" ]; then
    echo "Please provide a name - your analysis folders will be symlinked"
    echo "For example: ./useSelection.sh testCut"
    echo " this would ln -s selectionRoot_testCut selectionRoot"
    echo " also the BTag, Plots, and Unfolding folders will be symlinked"
    echo ""
    echo "If you provide 'clean' as argument, only the old symlinks will be removed."
    exit
else
    name="$1"
fi

folders="BTagEff Plots selectionRoot SVD  UnfoldingResults"
for i in $folders; do
    if [ -h "$i" ]; then
        rm "$i"
    fi
done

for i in $folders; do
    if [ -e "$i" ]; then
        echo "A file/directory called $i exists. Move it away first (e.g. by calling renameSelection.sh)."
        exit
    fi
done

if [ $name = "clean" ]; then
    echo "Directory has been cleaned"
    exit
fi

for i in $folders; do
    echo "symlinking ${i}_$name to $i"
    ln -s "${i}_$name" "$i"
done
