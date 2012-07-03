#!/bin/zsh
#
# make_CP_booklet.sh
#
# Read the README file for instructions.
#
###############################################################



###############################################################
############## S T E E R I N G ################################
###############################################################

OUTPUTFOLDER="/afs/desy.de/user/d/dfischer/www/TopUnfolding/CP_Booklets"
STEERINGFILE="/afs/desy.de/user/d/dfischer/workspace/TopUnfolding/CMSSW/CMSSW_4_2_5/src/unfolding/CP_booklet/Steering/steering_test.steer"
SNIPPETFOLDER="/afs/desy.de/user/d/dfischer/workspace/TopUnfolding/CMSSW/CMSSW_4_2_5/src/unfolding/CP_booklet/TexSnippets"
INPUTFOLDER="/afs/desy.de/user/d/dfischer/workspace/TopUnfolding/CMSSW/CMSSW_4_2_5/src/diLeptonic/SVD"
TEXFILE="SelectedControlPlots"

#LIST_SYST="RES JES MASS MATCH SCALE PU_ DY_ BG_ HAD"
LIST_SYST="HAD"
LIST_DISTa="Leptons_Eta Leptons_Pt LepPair_Pt LepPair_Mass BJets_Eta BJets_Pt"
LIST_DISTb="TopQuarks_Rapidity TopQuarks_Pt TtBar_Rapidity TtBar_Pt TtBar_Mass"
LIST_CHANNEL="mumu emu ee combined"

EPSTOPDF="false" 
COPYIMG="false"
COMPILE="true"
COMBINEBOOKLETS="false"
DEBUGTEX="false"

###############################################################
###############################################################
###############################################################


# Prepare Folder
mkdir $OUTPUTFOLDER 2> /dev/null
if [ "$COPYIMG" = "true" ]; then
    mkdir $OUTPUTFOLDER/Images 2> /dev/null ;
fi

# Real Input Folder
REALINPUTFOLDER=$INPUTFOLDER

# Loop over booklets
NUMSTEERINGLINES=`cat $STEERINGFILE | wc -l`
STEERINGLINECNT=0
TOKENCNT=0
FIRSTBOOKLET=true
while [ "$STEERINGLINECNT" -lt "$NUMSTEERINGLINES" ] ; do
    let "STEERINGLINECNT = $STEERINGLINECNT + 1"

    # Read Steering, ingore lines containing whitespaces only
    STEERINGLINE=`cat $STEERINGFILE | head -${STEERINGLINECNT} | tail -1`
    TRUNCSTEERLINE=""
    for i in `echo $STEERINGLINE` ; do
        TRUNCSTEERLINE=$i ; 
    done
    if [ "$TRUNCSTEERLINE" = "" ] ; then
        continue;
    fi
    
    # Read tokens
    let "TOKENCNT = $TOKENCNT + 1"
    if [ "$TOKENCNT" = "1" ]; then
        for i in `echo $STEERINGLINE` ; do
             PLOTKEY=$i;
        done
        continue;
    elif [ "$TOKENCNT" = "2" ]; then
        for i in `echo $STEERINGLINE` ; do
             DONOM=$i;
        done
        continue;
    elif [ "$TOKENCNT" = "3" ]; then
        for i in `echo $STEERINGLINE` ; do
             DOSYST=$i;
        done
        continue;
    elif [ "$TOKENCNT" = "4" ]; then
        LINETITLE="$STEERINGLINECNT"
        TOKENCNT=0 ;
    else
        TOKENCNT=0 ;
    fi ;

    # Debug Tokens
    DEBUGTOKENS=false
    if [ "$DEBUGTOKENS" = "true" ]; then
        echo "PLOTKEY         = $PLOTKEY"
        echo "DONOM           = $DONOM"
        echo "DOSYST          = $DOSYST"
        echo "LINETITLE       = $LINETITLE" 
        continue;
    fi

    # Loop over systematics or not
    ALLSYST=$LIST_SYST
    if [ "$DOSYST" = "false" ] ; then
        ALLSYST="" ;
    fi

    # Which Outputfile
    if [ "$COMBINEBOOKLETS" = "true" ]; then
        OUTPUTFILENAME=$TEXFILE ;
    else 
        OUTPUTFILENAME=$PLOTKEY ; 
    fi

    # Open Booklet?
    OPENBOOKLET=false
    if [ "$COMBINEBOOKLETS" = "false" ]; then
        OPENBOOKLET=true ;
    fi
    if [ "$FIRSTBOOKLET" = "true" ]; then
        OPENBOOKLET=true ;
    fi
    
    # Open Booklet!
    if [ "$OPENBOOKLET" = "true" ]; then
        echo "Creating Booklet ${OUTPUTFOLDER}/${OUTPUTFILENAME}.tex..."
        OUTPUTFILE=$OUTPUTFOLDER/$OUTPUTFILENAME
        rm $OUTPUTFILE.tex 2> /dev/null
    	touch $OUTPUTFILE.tex
        cat $SNIPPETFOLDER/CP_booklet_titlepageheader.tex >> $OUTPUTFILE.tex
        if [ "$COMBINEBOOKLETS" = "true" ]; then
             echo "Selected Unfolding Control Plots" >> $OUTPUTFILE.tex ;
        else 
             cat $STEERINGFILE | head -${STEERINGLINECNT} | tail -1 >> $OUTPUTFILE.tex ;
        fi
        cat $SNIPPETFOLDER/CP_booklet_titlepagefooter.tex >> $OUTPUTFILE.tex ; 
    fi

    # Make first Nominal Plots if needed
    if [ "$DONOM" = "true" ]; then

        # First Page for nominal plots
        cat $SNIPPETFOLDER/CP_booklet_floatheader.tex >> $OUTPUTFILE.tex
        for dist in `echo $LIST_DISTa` ; do
            cat $SNIPPETFOLDER/CP_booklet_rowheader.tex >> $OUTPUTFILE.tex
            for cc in `echo $LIST_CHANNEL` ; do
                cat $SNIPPETFOLDER/CP_booklet_plotheader.tex >> $OUTPUTFILE.tex
                PLOTNAME="Unfolding_${cc}_${dist}_${PLOTKEY}"
                PLOTLOC="${INPUTFOLDER}"
                OUTEXT="eps"
                if [ ! -e ${REALINPUTFOLDER}/${PLOTNAME}.eps ] ; then
                    echo "File ${REALINPUTFOLDER}/${PLOTNAME}.eps not found. Exiting ..."
                    exit;
                fi
                if [ "$COPYIMG" = "true" ]; then
                     PLOTLOC="${OUTPUTFOLDER}/Images"
                     cp ${REALINPUTFOLDER}/${PLOTNAME}.eps ${OUTPUTFOLDER}/Images/${PLOTNAME}.eps ;
                fi
                if [ "$EPSTOPDF" = "true" ]; then
                    epstopdf "${PLOTLOC}/${PLOTNAME}.eps"
                    OUTEXT="pdf" ;
                fi
                echo "${PLOTLOC}/${PLOTNAME}.${OUTEXT}%" >> $OUTPUTFILE.tex
                echo "    Adding Plot for ... Nominal / ${dist} / ${cc}" 
                cat $SNIPPETFOLDER/CP_booklet_plotfooter.tex >> $OUTPUTFILE.tex ; 
            done 
            cat $SNIPPETFOLDER/CP_booklet_rowfooter.tex >> $OUTPUTFILE.tex ;
        done
        cat $SNIPPETFOLDER/CP_booklet_floatfooter.tex >> $OUTPUTFILE.tex
    
        # Second Page for nominal plots
        cat $SNIPPETFOLDER/CP_booklet_floatheader.tex >> $OUTPUTFILE.tex
        for dist in `echo $LIST_DISTb` ; do
            cat $SNIPPETFOLDER/CP_booklet_rowheader.tex >> $OUTPUTFILE.tex
            for cc in `echo $LIST_CHANNEL` ; do
                cat $SNIPPETFOLDER/CP_booklet_plotheader.tex >> $OUTPUTFILE.tex
                PLOTNAME="Unfolding_${cc}_${dist}_${PLOTKEY}"
                PLOTLOC="${INPUTFOLDER}"
                OUTEXT="eps"
                if [ ! -e ${REALINPUTFOLDER}/${PLOTNAME}.eps ] ; then
                    echo "File ${REALINPUTFOLDER}/${PLOTNAME}.eps not found. Exiting ..."
                    exit;
                fi
                if [ "$COPYIMG" = "true" ]; then
                    PLOTLOC="${OUTPUTFOLDER}/Images"
                    cp ${REALINPUTFOLDER}/${PLOTNAME}.eps ${OUTPUTFOLDER}/Images/${PLOTNAME}.eps ;
                fi
                if [ "$EPSTOPDF" = "true" ]; then
                    epstopdf "${PLOTLOC}/${PLOTNAME}.eps"
                    OUTEXT="pdf" ;
                fi
                echo "${PLOTLOC}/${PLOTNAME}.${OUTEXT}%" >> $OUTPUTFILE.tex
                echo "    Adding Plot for ... Nominal / ${dist} / ${cc}"
                cat $SNIPPETFOLDER/CP_booklet_plotfooter.tex >> $OUTPUTFILE.tex ;
            done
            cat $SNIPPETFOLDER/CP_booklet_rowfooter.tex >> $OUTPUTFILE.tex ;
        done
        cat $SNIPPETFOLDER/CP_booklet_floatfooter.tex >> $OUTPUTFILE.tex  ;
    fi
      
    # Loop over all systematics
    for syst in `echo $ALLSYST` ; do

        # First Page for systematic plots
        cat $SNIPPETFOLDER/CP_booklet_floatheader.tex >> $OUTPUTFILE.tex
        for dist in `echo $LIST_DISTa` ; do
            cat $SNIPPETFOLDER/CP_booklet_rowheader.tex >> $OUTPUTFILE.tex
            for cc in `echo $LIST_CHANNEL` ; do
                cat $SNIPPETFOLDER/CP_booklet_plotheader.tex >> $OUTPUTFILE.tex
                PLOTNAME="Unfolding_${cc}_${dist}_${syst}_${PLOTKEY}"
                PLOTLOC="${INPUTFOLDER}"
                OUTEXT="eps"
                if [ ! -e ${REALINPUTFOLDER}/${PLOTNAME}.eps ] ; then
                    echo "File ${REALINPUTFOLDER}/${PLOTNAME}.eps not found. Exiting ..."
                    exit;
                fi
                if [ "$COPYIMG" = "true" ]; then
                     PLOTLOC="${OUTPUTFOLDER}/Images"
                     cp ${REALINPUTFOLDER}/${PLOTNAME}.eps ${OUTPUTFOLDER}/Images/${PLOTNAME}.eps ;
                fi
                if [ "$EPSTOPDF" = "true" ]; then
                    epstopdf "${PLOTLOC}/${PLOTNAME}.eps"
                    OUTEXT="pdf" ;
                fi
                echo "${PLOTLOC}/${PLOTNAME}.${OUTEXT}%" >> $OUTPUTFILE.tex
                echo "    Adding Plot for ... ${syst} / ${dist} / ${cc}"
                cat $SNIPPETFOLDER/CP_booklet_plotfooter.tex >> $OUTPUTFILE.tex ;
            done
            cat $SNIPPETFOLDER/CP_booklet_rowfooter.tex >> $OUTPUTFILE.tex ;
        done
        cat $SNIPPETFOLDER/CP_booklet_floatfooter.tex >> $OUTPUTFILE.tex

        
        # Second page for systematic plots
        cat $SNIPPETFOLDER/CP_booklet_floatheader.tex >> $OUTPUTFILE.tex
        for dist in `echo $LIST_DISTb` ; do
            cat $SNIPPETFOLDER/CP_booklet_rowheader.tex >> $OUTPUTFILE.tex
            for cc in `echo $LIST_CHANNEL` ; do
                cat $SNIPPETFOLDER/CP_booklet_plotheader.tex >> $OUTPUTFILE.tex
                PLOTNAME="Unfolding_${cc}_${dist}_${syst}_${PLOTKEY}"
                PLOTLOC="${INPUTFOLDER}"
                OUTEXT="eps"
                if [ ! -e ${REALINPUTFOLDER}/${PLOTNAME}.eps ] ; then
                    echo "File ${REALINPUTFOLDER}/${PLOTNAME}.eps not found. Exiting ..."
                    exit;
                fi
                if [ "$COPYIMG" = "true" ]; then
                     PLOTLOC="${OUTPUTFOLDER}/Images"
                     cp ${REALINPUTFOLDER}/${PLOTNAME}.eps ${OUTPUTFOLDER}/Images/${PLOTNAME}.eps ;
                fi
                if [ "$EPSTOPDF" = "true" ]; then
                    epstopdf "${PLOTLOC}/${PLOTNAME}.eps"
                    OUTEXT="pdf" ;
                fi
                echo "${PLOTLOC}/${PLOTNAME}.${OUTEXT}%" >> $OUTPUTFILE.tex
                echo "    Adding Plot for ... ${syst} / ${dist} / ${cc}"
                cat $SNIPPETFOLDER/CP_booklet_plotfooter.tex >> $OUTPUTFILE.tex ;
            done
            cat $SNIPPETFOLDER/CP_booklet_rowfooter.tex >> $OUTPUTFILE.tex ;
        done
        cat $SNIPPETFOLDER/CP_booklet_floatfooter.tex >> $OUTPUTFILE.tex ;
    
    done

    # Close Booklet?
    CLOSEBOOKLET=false;
    if [ "$COMBINEBOOKLETS" = "false" ]; then
        CLOSEBOOKLET=true ;
    fi

    # Close Booklet
    if [ "$CLOSEBOOKLET" = "true" ]; then
        cat $SNIPPETFOLDER/CP_booklet_bookletfooter.tex >> $OUTPUTFILE.tex
        echo "Done." 
        if [ "$COMPILE" = "true" ] ; then
            echo "    Converting ${OUTPUTFILENAME}.tex to ${OUTPUTFILENAME}.dvi!"
            echo "            (If this runs for ages, try 'X ENTER' and"
            echo "            check the latex logfile ${OUTPUTFILENAME}.log)"
            THEPWD=`pwd`
            cd $OUTPUTFOLDER
            rm $OUTPUTFILENAME.pdf &> /dev/null
            rm $OUTPUTFILENAME.log &> /dev/null
            if [ "$DEBUGTEX" = "true" ]; then
                latex $OUTPUTFILENAME.tex
            else
                latex $OUTPUTFILENAME.tex &> /dev/null
            fi
            echo "    Converting ${OUTPUTFILENAME}.dvi to ${OUTPUTFILENAME}.pdf!"
            echo "            (This may take some time, too.)"
            if [ "$DEBUGTEX" = "true" ]; then
                dvipdf $OUTPUTFILENAME.dvi ;
            else
                dvipdf $OUTPUTFILENAME.dvi &> /dev/null ;
            fi

            rm $OUTPUTFILENAME.dvi &> /dev/null
            rm $OUTPUTFILENAME.aux &> /dev/null
            cd $THEPWD
            echo "    Converted!";            
        fi  ;
    fi

    FIRSTBOOKLET=false ;
done


# Close Booklet if combined plots need to be made
if [ "$COMBINEBOOKLETS" = "true" ] ; then
    cat $SNIPPETFOLDER/CP_booklet_bookletfooter.tex >> $OUTPUTFILE.tex
    echo "Done."
    if [ "$COMPILE" = "true" ] ; then
        echo "    Converting ${OUTPUTFILENAME}.tex to ${OUTPUTFILENAME}.dvi!"
        echo "        (If this runs for ages, try 'X ENTER' and"
        echo "        check the latex logfile ${OUTPUTFILENAME}.log)"
        THEPWD=`pwd`
        cd $OUTPUTFOLDER
        rm $OUTPUTFILENAME.pdf &> /dev/null
        rm $OUTPUTFILENAME.log &> /dev/null
        if [ "$DEBUGTEX" = "true" ]; then
            latex $OUTPUTFILENAME.tex
        else
            latex $OUTPUTFILENAME.tex &> /dev/null
        fi
        echo "    Converting ${OUTPUTFILENAME}.dvi to ${OUTPUTFILENAME}.pdf!"
        echo "        (This may take some time, too.)"        
        if [ "$DEBUGTEX" = "true" ]; then
            dvipdf $OUTPUTFILENAME.dvi ;
        else
            dvipdf $OUTPUTFILENAME.dvi &> /dev/null ;
        fi

        rm $OUTPUTFILENAME.dvi &> /dev/null
        rm $OUTPUTFILENAME.aux &> /dev/null
        cd $THEPWD
        echo "    Converted!";
    fi ;
fi

