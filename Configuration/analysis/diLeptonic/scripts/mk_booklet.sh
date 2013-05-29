#######################################################
# script created to create the .pdf booklet for latex #
# by JOZZE ZOBEC, DESY Summer Student Programme 2012  #
#                                                     #
# mk_booklet.sh                                       #
#######################################################
#                                                     #
# this script accepts two arguments:                  #
# --------------------------------------------------- #
#                                                     #
# $1 - ttbar mass cut at the generator level and the  #
# $2 - ttbar mass cut at the reconstruction level     #
#                                                     #
#######################################################
#                                                     #
#                  BOOKLET USAGE                      #
#                                                     #
# (1) WHERE TO RUN THE BOOKLET FROM                   #
# --------------------------------------------------- #
#                                                     #
# you stay in the folder where you just run your      #
# analysis code. In your current folder you need to   #
# have the 'Plots' folder present, otherwise          #
# the script won't find any of the plots. For now,    #
# it only creates a booklet for the combined channel, #
# but you can change it easily to create it for all   #
# channels with foreach command or something like     #
# that.                                               #
#                                                     #
# (2) HOW TO ADD HISTOGRAMS TO THE BOOKLET            #
# --------------------------------------------------- #
#                                                     #
# Histograms you want to add must have an .eps        #
# extension. The histos you want to include in        #
# your booklet, MUST be added to a steering file,     #
# named 'mk_booklet.lst' without any extensions. If   #
# you want a page break, instead of the histogram     #
# name, you simply type 'NL'. A sample file (the one  #
# I use for myself) is included in the CVS. This      #
# control file has to be present in the same folder   #
# as the script.                                      #
#                                                     #
# (3) SHORT SCRIPT DESCRIPTION                        #
# --------------------------------------------------- #
# * first checkes if the files are present            #
#                                                     #
# * converts them to .pdf files with the 'epstopdf'   #
#   command                                           #
#                                                     #
# * creates a latex file, 6 plots per page using      #
#   the subfigure package                             #
#                                                     #
# * if there is a FILE MISSING, the script will       #
#   insert a blank page (in progress), for now        #
#   it just gives a warning, but does nothing         #
#                                                     #
# * creates a folder for the booklets, compiles the   #
#   .tex with the 'pdflatex' command and moves both   #
#   .tex and .pdf file to the booklets folder.        #
#                                                     #
# * name of the booklets includes a timestamp to      #
#   avoid ambiguities.                                #
#                                                     #
# * deletes the temporary folder with the .pdf        #
#   histos.                                           #
#                                                     #
#######################################################
# Date: Tuesday, 2012-08-21, Time: 16:36              #
#######################################################

#!/bin/zsh

TIME=$(date +%F--%H%M)

CDIR=$(pwd) #current working directory
PDIR=Plots/Nominal/combined #plot dir
PDFPREF=pdf-s #pdf prefix
PDFDIR=$CDIR/$PDIR/$PDFPREF #pdf dir
COUNTER=0 #counter
BSN=booklet-$TIME #base name

BOOKLETSRC=$PDFDIR/$BSN.tex #booklet .tex source file
BOOKLETN=$PDFDIR/$BSN.pdf #self-explainatory

INFILE=$CDIR/scripts/mk_booklet.lst #input control file
BOOKLETDIR=$CDIR/Booklets #directory where we save the stuff

cd $CDIR/$PDIR

if [ -d $PDFDIR ]; then

    rm -R $PDFDIR
    mkdir -p $PDFDIR

else

    mkdir -p $PDFDIR

fi

for EPS_FILES in $( cat $INFILE ); do

    echo $EPS_FILES

    if [ "$EPS_FILES" != "NL" ] && [ -a $EPS_FILES.eps ]; then
        epstopdf $EPS_FILES.eps
    else
        echo "There is no $EPS_FILES.eps ..."
    fi
done

mv *pdf $PDFDIR

cd $PDFDIR

#create the header
cat <<LATEX >> $BOOKLETSRC

\documentclass[12pt, a4paper, titlepage]{article}
\usepackage[utf8]{inputenc}
\usepackage[T1]{fontenc}

%all the graphics will be contained in here
\usepackage{graphicx, float, pdflscape, caption, subfigure, fullpage, fancyhdr}

%setting the plot environments
%work in progress ...
%\newenvironment{pictures}{

%subfigure manual suggested this option ...
%\subfiglabelskip=Opt

%we create the header for the document ... it carries the filename ...
\pagestyle{fancy} 
\lhead{\texttt{"$BSN"}}

\begin{document}

%generic titlepage creation
\begin{titlepage}

\begin{center}
\vspace{6cm}
  \LARGE{Histogram plots -- current}\\\\
  \vspace{5cm}
  \large{Booklet filename -- "$BSN"}
\end{center}
\vfill

\small{Date: \today}

\end{titlepage}

\pagebreak


LATEX

echo "\begin{figure}" >> $BOOKLETSRC



#actual plots start here 
for PLOT_IN_PDF in $( cat $INFILE ); do

	#we want to have 6 plots per page ... ordering doesn't matter (yet)
	if [ "$(( COUNTER % 6 ))" -eq 0 ] && [ "$COUNTER" -ne 0 ] && [ "$PLOT_IN_PDF" != "NL" ]; then

		echo "\end{figure}" >> $BOOKLETSRC
		echo " " >> $BOOKLETSRC
		echo "\pagebreak" >> $BOOKLETSRC
		echo " " >> $BOOKLETSRC
		echo "\begin{figure}" >> $BOOKLETSRC

	fi

	if [ "$PLOT_IN_PDF" == "NL" ]; then

		echo "\end{figure}" >> $BOOKLETSRC
		echo " " >> $BOOKLETSRC
		echo "\pagebreak" >> $BOOKLETSRC
		echo " " >> $BOOKLETSRC
		echo "\begin{figure}" >> $BOOKLETSRC

		#(( COUNTER ++ ))
		COUNTER=0

	else
		if [ -a $PLOT_IN_PDF.pdf ]; then

			echo "   \subfigure" >> $BOOKLETSRC
			echo "   {" >> $BOOKLETSRC
			echo "      \centering" >> $BOOKLETSRC
			echo "      \includegraphics[width=0.47\textwidth, keepaspectratio=1]{"$PLOT_IN_PDF".pdf}" >> $BOOKLETSRC
			echo "   }" >> $BOOKLETSRC

			(( COUNTER ++ ))
		
		else

			echo "Warning! $PLOT_IN_PDF.pdf is missing ... skipping file."
		
		fi
	fi

done

echo "\end{figure}" >> $BOOKLETSRC
echo " " >> $BOOKLETSRC

#here we just close up the document
echo "\end{document}" >> $BOOKLETSRC

#and return to our original dir ...
pdflatex $BOOKLETSRC

#move the booklets into the common folder ...
if [ -d $BOOKLETDIR ]; then
	cp $BOOKLETN $BOOKLETDIR
	cp $BOOKLETSRC $BOOKLETDIR
else
	mkdir $BOOKLETDIR
	cp $BOOKLETN $BOOKLETDIR
	cp $BOOKLETSRC $BOOKLETDIR
fi

rm -Rf $PDFDIR

exit 0
 
