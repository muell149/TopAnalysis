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
 $ runallGC.pl [-g] -d directoryName -c configFile.py [-r regexp] [-s]
        [-j NJobs] [-x factor] [-m maxEventsPerJob] [-f files.txt] -h hypernewsName

Run runallGC.pl to run over all data samples given in files.txt using the
configuration file configFile.py - and use GridControl to submit jobs

the grid-control directory must be placed in the folder this script is run from.

-g      run on the grid

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
die "Who are you?\n" unless $hypernewsName;


while(my $line = <$IN>) {
    chomp $line;
    next if $line =~ /^\s*#/; #skip comments
    next if exists $arg{'R'} && $line =~ /$arg{'R'}/;
    next unless $line =~ /\w/; #skip empty lines
    next unless (!exists $arg{'r'} || $line =~ /$arg{'r'}/);
    
    my ($eventsPerJob, $dataset, $outputFile, $options) =
        map { s!\${(\w+)}!$ENV{$1}!g; $_ }
        split / {2,}/, $line;
        
    next unless $options;
    
    my $path = File::Spec->rel2abs("$arg{d}/GC-$outputFile");
    mkpath($path);
    my $jobdirWithSomeTimestamp = "runallGC-$outputFile-" . strftime("%FT%H-%M-%S",localtime);
    
    my $t = getGCtemplate();
    
    for ($t) {
        s/##LOCAL_OR_GRID##/$arg{g} ? "grid" : "local"/eg;
        s/##WORKDIR##/$path/g;
        s/##JOBS##/$arg{j} ? $arg{j} : ''/eg;
        s/##CMSSW_BASE##/$ENV{CMSSW_BASE}/g;
        s/##CMSSWConfigFile##/File::Spec->rel2abs($arg{c})/eg;
        s/##EVENTS_PER_JOB##/$eventsPerJob/g;
        s/##DATASET##/$dataset/g;
        s/##OUTPUTFILE##/$outputFile/g;
        s/##HN_USER##/$hypernewsName/g;
        s/##USER##/$ENV{USER}/g;
        s/##OPTIONS##/$options/g;
        s/##jobdirWithSomeTimestamp##/$jobdirWithSomeTimestamp/g;
        s/##SE_DCACHE##/$arg{g} ? '' : ';'/eg;
        s/##SE_SCRATCH##/$arg{g} ? ';' : ''/eg;        
    }
    my $gcConfig = File::Spec->rel2abs("$arg{d}/GC-$outputFile.conf");
    open my $OUT, '>', $gcConfig or die $!;
    print $OUT $t;
    close $OUT;
    
    if ($arg{g}) {
        push @createDirs, "srmmkdir srm://dcache-se-cms.desy.de:8443/pnfs/desy.de/cms/tier2/store/user/$hypernewsName/$jobdirWithSomeTimestamp\n";
	push @getGCs, "./grid-control/scripts/downloadFromSE.py -m -o /scratch/hh/dust/naf/cms/user/$ENV{USER}/$jobdirWithSomeTimestamp $gcConfig\n";
    } else {
        push @createDirs, "mkdir -p /scratch/hh/dust/naf/cms/user/$ENV{USER}/$jobdirWithSomeTimestamp\n";
    }
    push @runGCs, "echo starting $gcConfig\n./grid-control/go.py -i $gcConfig\n";
    push @checkGCs, "echo checking $gcConfig\n./grid-control/go.py $gcConfig\n";
    push @killGCs, "echo killing $gcConfig\n./grid-control/go.py -d ALL $gcConfig\n";
    push @forHadd, "hadd /scratch/hh/dust/naf/cms/user/$ENV{USER}/${outputFile}.root /scratch/hh/dust/naf/cms/user/$ENV{USER}/$jobdirWithSomeTimestamp/*.root\n";
    push @forJson, "./grid-control/scripts/lumiInfo.py -j $gcConfig\n";

}

open my $OUT, '>', "$arg{d}/createDirsAndRun.sh" or die $!;
print $OUT $_ for @createDirs;
print $OUT "\n" x 3;
print $OUT $_ for @runGCs;
close $OUT;
chmod 0755, "$arg{d}/createDirsAndRun.sh";
print "run ./$arg{d}/createDirsAndRun.sh to create dirs and submit jobs\n";

open my $OUTC, '>', "$arg{d}/checkAllJobs.sh" or die $!;
print $OUTC $_ for @checkGCs;
close $OUTC;
chmod 0755, "$arg{d}/checkAllJobs.sh";
print "run ./$arg{d}/checkAllJobs.sh to check dirs and resubmit jobs\n";

if ($arg{g}) {
    open my $OUTG, '>', "$arg{d}/downloadAllFromSE.sh" or die $!;
    print $OUTG $_ for @getGCs;
    close $OUTG;
    chmod 0755, "$arg{d}/downloadAllFromSE.sh";
    print "run ./$arg{d}/downloadAllFromSE.sh to download from dcache to your sonar user space\n";
}

open my $OUTD, '>', "$arg{d}/killAllJobs.sh" or die $!;
print $OUTD $_ for @killGCs;
close $OUTD;
chmod 0755, "$arg{d}/killAllJobs.sh";
print "run ./$arg{d}/killAllJobs.sh to kill all jobs\n";

open my $OUTR, '>', "$arg{d}/haddAllRoot.sh" or die $!;
print $OUTR $_ for @forHadd;
close $OUTR;
chmod 0755, "$arg{d}/haddAllRoot.sh";
print "run ./$arg{d}/haddAllRoot.sh to hadd all output\n";

open my $OUTL, '>', "$arg{d}/getJsons.sh" or die $!;
print $OUTL $_ for @forJson;
close $OUTL;
chmod 0755, "$arg{d}/getJsons.sh";
print "run ./$arg{d}/getJsons.sh to get all processed Jsons\n";



sub getGCtemplate
{
    return <<'ENDE_TEMPLATE';
[global]
module  = CMSSW
backend = ##LOCAL_OR_GRID## ; (local or grid) ; switch is enough
workdir = ##WORKDIR## ; (when running locally also the sandbox will be placed here ; 

[local]
wms = SGE

[SGE]
site = hh 

[jobs]
##JOBS##
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
events per job     = ##EVENTS_PER_JOB##   ; I think better than to restrict total number of jobs


dataset            = ##DATASET## ; /MuEG/Run2012A-recover-06Aug2012-v1/AOD


[storage]
se output files    = *.root ;
##SE_DCACHE##se path            = srm://dcache-se-cms.desy.de:8443/pnfs/desy.de/cms/tier2/store/user/##HN_USER##/##jobdirWithSomeTimestamp##
##SE_SCRATCH##se path           = dir:///scratch/hh/dust/naf/cms/user/##USER##/##jobdirWithSomeTimestamp##





; $workdir must be created before to avoid script from stopping
; srmmkdir srm://dcache-se-cms.desy.de:8443/pnfs/desy.de/cms/tier2/store/user/${HN_USER}/##jobdirWithSomeTimestamp##
; 
; ./grid-control/go.py -i [gc_configfile]  ; inits working dir, runs the jobs, then quits
; ./grid-control/scripts/downloadFromSE.py -ml --out=$outputdir [gc_configfile]  ; loops in background, checks if files are there and if ok, moves them to outputdir
; ./grid-control/go.py [gc_configfile] ; checks and resubmits
ENDE_TEMPLATE

}

