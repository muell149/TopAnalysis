#!/usr/bin/perl -w

use strict;
use warnings;
use Getopt::Std;
use File::Spec;
use File::Path;
use POSIX;

my %arg;
getopts('d:c:r:sj:m:f:R:gh', \%arg);

unless ( $arg{d} && $arg{c} && -f $arg{c}) {
    print <<'USAGE';
Syntax:
 $ runallGC.pl [-g] -d directoryName -c configFile.py [-f files.txt]

Run runallGC.pl to run over all data samples given in files.txt using the
configuration file configFile.py - and use GridControl to submit jobs

A directory on the sonar user space named "GridControl_workingDir" will
be created to contain working directories and output.

Set environment variable HN_USER to your hypernews name!

-g      run on the grid (only then HN_USER must be set)

-r regexp
If a regexp is given only jobs matching regexp will be submitted (case sensitive).

-R regexp
If a regexp is given only jobs NOT matching the regexp will be submitted (case sensitive).

-s                    really submit jobs using GridControl
-j NJobs              submit NJobs for each dataset. 
-m maxEventsPerJob    Overwrites default value from files.txt

-o output            output directory when output is downloaded from dcache

-f files.txt          (default value: files.txt)
files.txt must contain lines of
cff_file root_output number_of_jobs
# comments with # and empty lines are allowed
Variables can be added via ${VAR} and will be replaced with environment variable $VAR

USAGE
    exit;
}

my $source = $arg{f} ? $arg{f} : 'files.txt';
open my $IN, '<', $source or die "Cannot open input file: $!\n";
my @createDirs;
my @runGCs;
my @checkGCs;
my @getGCs;
my @killGCs;
my @forHadd;
my @forJson;

my $hypernewsName = $arg{h} || $ENV{HN_USER};

die "CMS ENV must be set!" unless $ENV{CMSSW_BASE};
if($arg{g}) {
    die "glite must be initialized to run grid jobs!!" unless $ENV{GLITE_LOCATION};
    die "Who are you? Set your hypernews name (HN_USER).\n" unless $hypernewsName;
}

# prepare workingdir

my $globalGcWorkingdir="/scratch/hh/dust/naf/cms/user/$ENV{USER}/GridControl_workingDir";

unless(-e $globalGcWorkingdir){
    print "creating global grid-control working dir at $globalGcWorkingdir...\n";
    mkdir($globalGcWorkingdir);
}
unless(-e "${globalGcWorkingdir}/grid-control"){
    print "checking out stable grid-control version...\n";
    system("svn co -q https://ekptrac.physik.uni-karlsruhe.de/public/grid-control/tags/stable/grid-control ${globalGcWorkingdir}/grid-control");
    print "\n\n";
}

my $workDirWithTime="$arg{d}_" . strftime("%FT%H-%M-%S",localtime);



if ($arg{g}) {
    push @createDirs, "srmmkdir srm://dcache-se-cms.desy.de:8443/pnfs/desy.de/cms/tier2/store/user/$hypernewsName/$workDirWithTime\n";
}
my $fullCMSSWcfpath=File::Spec->rel2abs($arg{c});
my $cfgfilename = ( split m{/}, $arg{c} )[-1];


while(my $line = <$IN>) {
    chomp $line;
    next if $line =~ /^\s*#/; #skip comments
    next if exists $arg{'R'} && $line =~ /$arg{'R'}/;
    next unless $line =~ /\w/; #skip empty lines
    next unless (!exists $arg{'r'} || $line =~ /$arg{'r'}/);
    
    my ($numJobs, $dataset, $outputFile, $options, $jsonFile) =
        map { s!\${(\w+)}!$ENV{$1}!g; $_ }
        split / {2,}/, $line;
        
    next unless $outputFile;

    print "checking dataset $dataset...\n";
    my @dbsquery=`dbs search --query="find sum(file.numevents) where dataset=$dataset"`;

    if($dbsquery[4] eq "\n"){
	print "$dataset not found on dbs. Scipping entry\n";
	next;
    }

    my $eventsPerJob=int($dbsquery[4]/$numJobs); 


    print "running with $eventsPerJob events per Job\n";

    my $path = "${globalGcWorkingdir}/$workDirWithTime/GC-$outputFile";
    mkpath($path);
    my $joboutdir = "output-$outputFile"; #. strftime("%FT%H-%M-%S",localtime);
    
    my $t = getGCtemplate();
    my $json = '';
    if($jsonFile){
	$json = File::Spec->rel2abs($jsonFile);
    }

    for ($t) {
        s/##LOCAL_OR_GRID##/$arg{g} ? "grid" : "local"/eg;
        s/##WORKDIR##/$path/g;
       # s/##JOBS##/$arg{j} ? $arg{j} : ''/eg;
        s/##CMSSW_BASE##/$ENV{CMSSW_BASE}/g;
        s/##CMSSWConfigFile##/$cfgfilename/eg;
        s/##EVENTSPERJOB##/$eventsPerJob/g;
        s/##DATASET##/$dataset/g;
        s/##OUTPUTFILE##/$outputFile/g;
        s/##HN_USER##/$hypernewsName/g;
        s/##GLOBALGCWD##/$globalGcWorkingdir/g;
        if($options){
	    s/##OPTIONS##/$options/g;
	}
	s/##FILTERLUMI##/$jsonFile ? '' : ';'/eg;
        s/##JSON##/$json/g;
	s/##WORKDIRWITHTIME##/$workDirWithTime/g;
        s/##JOBOUTDIR##/$joboutdir/g;
        s/##SE_DCACHE##/$arg{g} ? '' : ';'/eg;
        s/##SE_SCRATCH##/$arg{g} ? ';' : ''/eg;   
	if($arg{g}) {
	    s/##GLITE_LOCATION##/$ENV{GLITE_LOCATION}/g;  
	} 
    }
    my $gcConfig = "${globalGcWorkingdir}/$workDirWithTime/GC-$outputFile.conf";
    open my $OUT, '>', $gcConfig or die $!;
    print $OUT $t;
    close $OUT;
    
    if ($arg{g}) {
        push @createDirs, "srmmkdir srm://dcache-se-cms.desy.de:8443/pnfs/desy.de/cms/tier2/store/user/$hypernewsName/$workDirWithTime/$joboutdir\n";
	push @getGCs, "${globalGcWorkingdir}/grid-control/scripts/downloadFromSE.py -m -o ${globalGcWorkingdir}/$workDirWithTime/$joboutdir $gcConfig\n";
    } else {
        push @createDirs, "mkdir -p ${globalGcWorkingdir}/$workDirWithTime/$joboutdir\n";
    }
    push @runGCs, "echo 'starting $gcConfig'\nif [[ -f \"$path/first_sub\" ]]; \nthen\necho already initialized!\nelse\n${globalGcWorkingdir}/grid-control/go.py -i $gcConfig\ntouch $path/first_sub\nfi\n\n";
    push @checkGCs, "echo 'checking $gcConfig'\nif [[ -f \"$path/first_sub\" ]]; \nthen\n${globalGcWorkingdir}/grid-control/go.py $gcConfig\n\n${globalGcWorkingdir}/grid-control/go.py -s -r -R $gcConfig\nelse\necho not yet submitted\nfi\n\n";
    push @killGCs, "echo 'killing $gcConfig'\n${globalGcWorkingdir}/grid-control/go.py -d ALL $gcConfig\n";
    push @forHadd, "hadd ${globalGcWorkingdir}/$workDirWithTime/${outputFile}.root ${globalGcWorkingdir}/$workDirWithTime/$joboutdir/*.root\n";
    push @forJson, "${globalGcWorkingdir}/grid-control/scripts/lumiInfo.py -j $gcConfig\n";

}

#let submit script write a file after each submitted task(N jobs) and let checkJobs check if file exists (and only then perform a check

open my $OUT, '>', "${globalGcWorkingdir}/$workDirWithTime/createDirsAndRun.sh" or die $!;
print $OUT $_ for @createDirs;
print $OUT "\n" x 3;
print $OUT $_ for @runGCs;
close $OUT;
chmod 0755, "${globalGcWorkingdir}/$workDirWithTime/createDirsAndRun.sh";
print "run ${globalGcWorkingdir}/$workDirWithTime/createDirsAndRun.sh to create dirs and submit jobs\n";

open my $OUTC, '>', "${globalGcWorkingdir}/$workDirWithTime/checkAllJobs.sh" or die $!;
print $OUTC $_ for @checkGCs;
close $OUTC;
chmod 0755, "${globalGcWorkingdir}/$workDirWithTime/checkAllJobs.sh";
print "run ${globalGcWorkingdir}/$workDirWithTime/checkAllJobs.sh to check dirs and resubmit jobs\n";

if ($arg{g}) {
    open my $OUTG, '>', "${globalGcWorkingdir}/$workDirWithTime/downloadAllFromSE.sh" or die $!;
    print $OUTG $_ for @getGCs;
    close $OUTG;
    chmod 0755, "${globalGcWorkingdir}/$workDirWithTime/downloadAllFromSE.sh";
    print "run ${globalGcWorkingdir}/$workDirWithTime/downloadAllFromSE.sh to download from dcache to your sonar user space\n";
}

open my $OUTD, '>', "${globalGcWorkingdir}/$workDirWithTime/killAllJobs.sh" or die $!;
print $OUTD $_ for @killGCs;
close $OUTD;
##chmod 0755, "${globalGcWorkingdir}/$workDirWithTime/killAllJobs.sh";
print "run ${globalGcWorkingdir}/$workDirWithTime/killAllJobs.sh to kill all jobs\n";

open my $OUTR, '>', "${globalGcWorkingdir}/$workDirWithTime/haddAllRoot.sh" or die $!;
print $OUTR $_ for @forHadd;
close $OUTR;
chmod 0755, "${globalGcWorkingdir}/$workDirWithTime/haddAllRoot.sh";
print "run ${globalGcWorkingdir}/$workDirWithTime/haddAllRoot.sh to hadd all output\n";

open my $OUTL, '>', "${globalGcWorkingdir}/$workDirWithTime/getJsons.sh" or die $!;
print $OUTL $_ for @forJson;
close $OUTL;
chmod 0755, "${globalGcWorkingdir}/$workDirWithTime/getJsons.sh";
print "run ${globalGcWorkingdir}/$workDirWithTime/getJsons.sh to get all processed Jsons\n";

system("cp ${fullCMSSWcfpath} ${globalGcWorkingdir}/${workDirWithTime}");

sub getGCtemplate
{
    return <<'ENDE_TEMPLATE';
[global]
module  = CMSSW
backend = ##LOCAL_OR_GRID## ; 
workdir = ##WORKDIR## ; 

[local]
wms = SGE

[SGE]
site = hh 


[glite-wms]
;ce            = ce1.gridka.de ; Select destination CE
;config     =    ##GLOBALGCWD##/grid-control/docs/glite_wms_DESY.conf     ; GliteWMS backend specific configuration (WMS, ...)
config     =    ##GLITE_LOCATION##/etc/cms/glite_wms.conf


[jobs]

; jobs = ##JOBS##
wall time    = 40:59:00 ;queue dingens // thats the 12 hour cue!!!
; in queue     = $maxjobsinqueue ; 1000 -1
memory       = 3700
monitor jobs = dashboard
max retry    = 1


[CMSSW]
project area       = ##CMSSW_BASE##
se runtime         = True
config file        = ##CMSSWConfigFile## ; 
prepare config     = True
arguments          = ##OPTIONS## outputFile=##OUTPUTFILE##  ; 

dataset splitter   = EventBoundarySplitter
events per job     = ##EVENTSPERJOB##;


dataset            = ##DATASET## ;
##FILTERLUMI##lumi filter        = ##JSON## ;

[storage]
se output files    = *.root ;
##SE_DCACHE##se path            = srm://dcache-se-cms.desy.de:8443/pnfs/desy.de/cms/tier2/store/user/##HN_USER##/##WORKDIRWITHTIME##/##JOBOUTDIR##
##SE_SCRATCH##se path           = dir://##GLOBALGCWD##/##WORKDIRWITHTIME##/##JOBOUTDIR##


ENDE_TEMPLATE

}

