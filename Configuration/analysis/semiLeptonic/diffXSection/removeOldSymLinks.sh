#!/bin/sh

# check input
if [ -n "$1" ]; then
    # info
    echo "Removing Symlinks latest acessed more than $1 days ago"
    # loop candidates
    for FOLDER in `ls -d naf_*`; do	
	# print the ones matching
	find $FOLDER -type l -ctime +$1 -exec echo {} \;
    done
    # ask for confirmation
    echo "please confirm by typing y [ENTER]"
    read anwser
    if [ $anwser == "y" ]; then
	echo "removing ..."	
	for FOLDER in `ls -d naf_*`; do	
	    find $FOLDER -type l -ctime +$1 -exec rm {} \;
	done
    else
	echo "cancelled..."
    fi
else
    echo "no deletion date given"
fi