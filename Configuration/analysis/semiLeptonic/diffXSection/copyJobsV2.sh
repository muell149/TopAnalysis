#!/bin/sh

merged=''

if [ -n "$1" ]; then
    echo "Files are copied to $1"
    for FOLDER in `ls -d naf_*`; do
	
	if [[ "${FOLDER}" == *Elqcd* ]] || [[ "${FOLDER}" == *WW* ]] || [[ "${FOLDER}" == *WZ* ]] || [[ "${FOLDER}" == *ZZ* ]] || [[ "${FOLDER}" == *Top* ]]; then
	    merged='MergedFiles/'
	else
	    merged=''
	fi

	if [[ "${FOLDER}" == *JERDn* ]]; then
	    cp -vu ${FOLDER}/????DiffXSec*JERDown*.root     /afs/naf.desy.de/group/cms/scratch/tophh/$1/JERDown/${merged}
	    cp -vu ${FOLDER}/????DiffXSec*JERDown*.txt      /afs/naf.desy.de/group/cms/scratch/tophh/$1/JERDown/TriggerReports/
	elif [[ "${FOLDER}" == *JERUp* ]]; then
	    cp -vu ${FOLDER}/????DiffXSec*JERUp*.root	     /afs/naf.desy.de/group/cms/scratch/tophh/$1/JERUp/${merged}
	    cp -vu ${FOLDER}/????DiffXSec*JERUp*.txt	     /afs/naf.desy.de/group/cms/scratch/tophh/$1/JERUp/TriggerReports/
	elif [[ "${FOLDER}" == *JESDn* ]]; then
	    cp -vu ${FOLDER}/????DiffXSec*JESDown*.root     /afs/naf.desy.de/group/cms/scratch/tophh/$1/JESDown/${merged}
	    cp -vu ${FOLDER}/????DiffXSec*JESDown*.txt     /afs/naf.desy.de/group/cms/scratch/tophh/$1/JESDown/TriggerReports/
	elif [[ "${FOLDER}" == *JESUp* ]]; then
	    cp -vu ${FOLDER}/????DiffXSec*JESUp*.root	     /afs/naf.desy.de/group/cms/scratch/tophh/$1/JESUp/${merged}
	    cp -vu ${FOLDER}/????DiffXSec*JESUp*.txt	     /afs/naf.desy.de/group/cms/scratch/tophh/$1/JESUp/TriggerReports/
	elif [[ "${FOLDER}" == *Mass*Dn* ]]; then
	    cp -vu ${FOLDER}/????DiffXSec*TopMassDown*.root /afs/naf.desy.de/group/cms/scratch/tophh/$1/TopMassDown/${merged}
	    cp -vu ${FOLDER}/????DiffXSec*TopMassDown*.txt /afs/naf.desy.de/group/cms/scratch/tophh/$1/TopMassDown/TriggerReports/
	elif [[ "${FOLDER}" == *Mass*Up* ]]; then
	    cp -vu ${FOLDER}/????DiffXSec*TopMassUp*.root   /afs/naf.desy.de/group/cms/scratch/tophh/$1/TopMassUp/${merged}
	    cp -vu ${FOLDER}/????DiffXSec*TopMassUp*.txt   /afs/naf.desy.de/group/cms/scratch/tophh/$1/TopMassUp/TriggerReports/
	elif [[ "${FOLDER}" == *MatchDn* ]]; then
	    cp -vu ${FOLDER}/????DiffXSec*MatchDown*.root   /afs/naf.desy.de/group/cms/scratch/tophh/$1/MatchDown/${merged}
	    cp -vu ${FOLDER}/????DiffXSec*MatchDown*.txt   /afs/naf.desy.de/group/cms/scratch/tophh/$1/MatchDown/TriggerReports/
	elif [[ "${FOLDER}" == *MatchUp* ]]; then
	    cp -vu ${FOLDER}/????DiffXSec*MatchUp*.root     /afs/naf.desy.de/group/cms/scratch/tophh/$1/MatchUp/${merged}
	    cp -vu ${FOLDER}/????DiffXSec*MatchUp*.txt     /afs/naf.desy.de/group/cms/scratch/tophh/$1/MatchUp/TriggerReports/
	elif [[ "${FOLDER}" == *ScaleDn* ]]; then
	    cp -vu ${FOLDER}/????DiffXSec*ScaleDown*.root   /afs/naf.desy.de/group/cms/scratch/tophh/$1/ScaleDown/${merged}
	    cp -vu ${FOLDER}/????DiffXSec*ScaleDown*.txt   /afs/naf.desy.de/group/cms/scratch/tophh/$1/ScaleDown/TriggerReports/
	elif [[ "${FOLDER}" == *ScaleUp* ]]; then
	    cp -vu ${FOLDER}/????DiffXSec*ScaleUp*.root     /afs/naf.desy.de/group/cms/scratch/tophh/$1/ScaleUp/${merged}
	    cp -vu ${FOLDER}/????DiffXSec*ScaleUp*.txt     /afs/naf.desy.de/group/cms/scratch/tophh/$1/ScaleUp/TriggerReports/
	else
	    cp -vu ${FOLDER}/????DiffXSec*.root             /afs/naf.desy.de/group/cms/scratch/tophh/$1/${merged}
	    cp -vu ${FOLDER}/????DiffXSec*.txt             /afs/naf.desy.de/group/cms/scratch/tophh/$1/TriggerReports/
	fi

    done

else
    echo "no destination folder given!"
fi