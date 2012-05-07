#!/bin/zsh
#
# make_CP_booklet.sh
#
# Call this script to make nice booklets with 
# unfolding control plots.
#
# As an argument, give it the name of a steering file, i.e.
# make_CP_booklet.sh steering.steer
#
# The steering file should contain a line for each control plot
# you want to make a booklet from.
#
# Each line in the steering file should have the following
# syntax:
#
# <PageInPSBooklet> <Descriptive Title in Latex>
# 
# Example:
#
# 8 Generralized Efficiency $\epsilon_{gen}$
#
#
###############################################################



###############################################################
############## S T E E R I N G ################################
###############################################################

OUTPUTFOLDER="./newBooklets"
STEERINGFILE="./Steering/steering_dilep.steer"
SNIPPETFOLDER="./TexSnippets"
INPUTFOLDER="../../diLeptonic/SVD"

LIST_SYST="RES"
LIST_DISTa="Leptons_Eta Leptons_Pt LepPair_Pt LepPair_Mass BJets_Rapidity BJets_Pt"
LIST_DISTb="TopQuarks_Rapidity TopQuarks_Pt TtBar_Rapidity TtBar_Pt TtBar_Mass"
LIST_CHANNEL="mumu emu ee combined"

EPSTOPDF="false" 
COPYIMG="false"
COMPILE="true"

###############################################################
###############################################################
###############################################################


# Prepare Folder
mkdir $OUTPUTFOLDER 2> /dev/null
if [ "$COPYIMG" = "true" ]; then
    mkdir $OUTPUTFOLDER/Images 2> /dev/null ;
fi

# Loop over booklets
NUMSTEERINGLINES=`cat $STEERINGFILE | wc -l`
STEERINGLINECNT=0
TOKENCNT=0
while [ "$STEERINGLINECNT" -lt "$NUMSTEERINGLINES" ] ; do
    let "STEERINGLINECNT = $STEERINGLINECNT + 1"

    # Read Steering, ingore lines containing whitespaces only
    STEERINGLINE=`cat $STEERINGFILE | head -${STEERINGLINECNT} | tail -1`
    if [ "$STEERINGLINE" = "" ] ; then
        continue;
    fi
    
    # Read tokens
    let "TOKENCNT = $TOKENCNT + 1"
    if [ "$TOKENCNT" = "1" ]; then
        for i in `echo $STEERINGLINE` ; do
             PAGENUMBER=$i;
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
        for i in `echo $STEERINGLINE` ; do
             OUTPUTFILENAME=$i;
        done        
        continue;
    elif [ "$TOKENCNT" = "5" ]; then
        LINETITLE="$STEERINGLINECNT"
        TOKENCNT=0 ;
    else
        TOKENCNT=0 ;
    fi ;


    # Loop over systematics or not
    ALLSYST=$LIST_SYST
    if [ "$DOSYST" = "false" ] ; then
        ALLSYST="" ;
    fi


    # Screen Output
    echo "Creating Booklet ${OUTPUTFOLDER}/${OUTPUTFILENAME}..."

	# Create a new Booklet
    OUTPUTFILE=$OUTPUTFOLDER/$OUTPUTFILENAME
    rm $OUTPUTFILE.tex 2> /dev/null
	touch $OUTPUTFILE.tex

    # Make Title Page
    cat $SNIPPETFOLDER/CP_booklet_titlepageheader.tex >> $OUTPUTFILE.tex
    cat $STEERINGFILE | head -${STEERINGLINECNT} | tail -1 >> $OUTPUTFILE.tex
    cat $SNIPPETFOLDER/CP_booklet_titlepagefooter.tex >> $OUTPUTFILE.tex

    # Make first Nominal Plots if needed
    if [ "$DONOM" = "true" ]; then

        # First Page for nominal plots
        cat $SNIPPETFOLDER/CP_booklet_floatheader.tex >> $OUTPUTFILE.tex
        for dist in `echo $LIST_DISTa` ; do
            cat $SNIPPETFOLDER/CP_booklet_rowheader.tex >> $OUTPUTFILE.tex
            for cc in `echo $LIST_CHANNEL` ; do
                cat $SNIPPETFOLDER/CP_booklet_plotheader.tex >> $OUTPUTFILE.tex
                PLOTNAME="Unfolding_${cc}_${dist}_${PAGENUMBER}"
                PLOTLOC="../${INPUTFOLDER}"
                OUTEXT="eps"
                if [ ! -e ${INPUTFOLDER}/${PLOTNAME}.eps ] ; then
                    echo "File ${INPUTFOLDER}/${PLOTNAME}.eps not found. Exiting ..."
                    exit;
                fi
                if [ "$COPYIMG" = "true" ]; then
                     PLOTLOC="./Images"
                     cp ${INPUTFOLDER}/${PLOTNAME}.eps ${OUTPUTFOLDER}/Images/${PLOTNAME}.eps ;
                fi
                if [ "$EPSTOPDF" = "true" ]; then
                    epstopdf "${OUTPUTFOLDER}/${PLOTLOC}/${PLOTNAME}.eps"
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
                PLOTNAME="Unfolding_${cc}_${dist}_${PAGENUMBER}"
                PLOTLOC="../${INPUTFOLDER}"
                OUTEXT="eps"
                if [ ! -e ${INPUTFOLDER}/${PLOTNAME}.eps ] ; then
                    echo "File ${INPUTFOLDER}/${PLOTNAME}.eps not found. Exiting ..."
                    exit;
                fi
                if [ "$COPYIMG" = "true" ]; then
                    PLOTLOC="./Images"
                    cp ${INPUTFOLDER}/${PLOTNAME}.eps ${OUTPUTFOLDER}/Images/${PLOTNAME}.eps ;
                fi
                if [ "$EPSTOPDF" = "true" ]; then
                    epstopdf "${OUTPUTFOLDER}/${PLOTLOC}/${PLOTNAME}.eps"
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
                PLOTNAME="Unfolding_${cc}_${dist}_${syst}_${PAGENUMBER}"
                PLOTLOC="../${INPUTFOLDER}"
                OUTEXT="eps"
                if [ ! -e ${INPUTFOLDER}/${PLOTNAME}.eps ] ; then
                    echo "File ${INPUTFOLDER}/${PLOTNAME}.eps not found. Exiting ..."
                    exit;
                fi
                if [ "$COPYIMG" = "true" ]; then
                     PLOTLOC="./Images"
                     cp ${INPUTFOLDER}/${PLOTNAME}.eps ${OUTPUTFOLDER}/Images/${PLOTNAME}.eps ;
                fi
                if [ "$EPSTOPDF" = "true" ]; then
                    epstopdf "${OUTPUTFOLDER}/${PLOTLOC}/${PLOTNAME}.eps"
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
                PLOTNAME="Unfolding_${cc}_${dist}_${syst}_${PAGENUMBER}"
                PLOTLOC="../${INPUTFOLDER}"
                OUTEXT="eps"
                if [ ! -e ${INPUTFOLDER}/${PLOTNAME}.eps ] ; then
                    echo "File ${INPUTFOLDER}/${PLOTNAME}.eps not found. Exiting ..."
                    exit;
                fi
                if [ "$COPYIMG" = "true" ]; then
                     PLOTLOC="./Images"
                     cp ${INPUTFOLDER}/${PLOTNAME}.eps ${OUTPUTFOLDER}/Images/${PLOTNAME}.eps ;
                fi
                if [ "$EPSTOPDF" = "true" ]; then
                    epstopdf "${OUTPUTFOLDER}/${PLOTLOC}/${PLOTNAME}.eps"
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


    # Finish off your little booklet
    cat $SNIPPETFOLDER/CP_booklet_bookletfooter.tex >> $OUTPUTFILE.tex
    echo "Done." 

    # Compilation
    if [ "$COMPILE" = "true" ] ; then
        echo "...converting to ${OUTPUTFILENAME}.pdf!"
        THEPWD=`pwd`
        cd $OUTPUTFOLDER
        rm $OUTPUTFILENAME.pdf &> /dev/null
        rm $OUTPUTFILENAME.log &> /dev/null
        latex $OUTPUTFILENAME.tex &> /dev/null
        dvipdf $OUTPUTFILENAME.dvi &> /dev/null
        rm $OUTPUTFILENAME.dvi &> /dev/null
        rm $OUTPUTFILENAME.aux &> /dev/null
        cd $THEPWD 
        echo "...converted!";
    fi  ;

done

