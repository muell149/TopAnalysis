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
        [-j NJobs] [-x factor] [-m maxEventsPerJob] [-f files.txt]

Run runallCrab.pl to run over all data samples given in files.txt using the
configuration file configFile.py - and use Crab to submit jobs

A directory on the sonar user space named "Crab_workingDir" will
be created to contain working directories and output.

Set environment variable HN_USER to your hypernews name!

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
#my @createDirs;
my @runCs;
my @checkCs;
my @getCs;
my @killCs;
my @forHadd;
my @forJson;

my @getOut;


push @runCs, "#!/bin/sh\n";
push @getCs, "#!/bin/sh\n";
push @checkCs, "#!/bin/sh\n";
push @forJson, "#!/bin/sh\n";
push @killCs, "#!/bin/sh\n";
push @forHadd, "#!/bin/sh\n";

my $hypernewsName = $arg{h} || $ENV{HN_USER};
die "Who are you? Set your hypernews name (HN_USER).\n" unless $hypernewsName;
die "glite must be initialized to run grid jobs!!" unless $ENV{GLITE_LOCATION};
die "init proxy first!" unless $ENV{VOMS_USERCONF};
die "crab must be initialized to run crab jobs!!" unless $ENV{CRABDIR};
die "CMS ENV must be set!" unless $ENV{CMSSW_BASE};


# prepare workingdir

my $globalCWorkingdir="/scratch/hh/dust/naf/cms/user/$ENV{USER}/Crab_workingDir";

unless(-e $globalCWorkingdir){
    print "creating global crab working dir at $globalCWorkingdir...\n";
    mkdir($globalCWorkingdir);
}

my $workDirWithTime="$arg{d}_" . strftime("%FT%H-%M-%S",localtime);

my $environmentcheck="if [[ \"\${VOMS_USERCONF}\" != $ENV{VOMS_USERCONF} ]] ;\nthen\necho Need grid proxy\nfi\nif [[ \"\${CRABDIR}\" != $ENV{CRABDIR} ]] ;\nthen\necho Crab env not set\nexit\nfi\nif [[ \"\${CMSSW_BASE}\" != $ENV{CMSSW_BASE} ]] ;\nthen\necho Wrong CMSSW env set. should be $ENV{CMSSW_BASE}\nexit\nfi\n";

push @runCs, $environmentcheck;
push @getCs, $environmentcheck;
push @checkCs, $environmentcheck;
push @forJson, $environmentcheck;
push @killCs, $environmentcheck;

push @runCs, "\nsrmmkdir srm://dcache-se-cms.desy.de:8443/pnfs/desy.de/cms/tier2/store/user/$hypernewsName/$workDirWithTime\n\n";


while(my $line = <$IN>) {
    chomp $line;
    next if $line =~ /^\s*#/; #skip comments
    next if exists $arg{'R'} && $line =~ /$arg{'R'}/;
    next unless $line =~ /\w/; #skip empty lines
    next unless (!exists $arg{'r'} || $line =~ /$arg{'r'}/);
    
    my ($eventsPerJob, $dataset, $outputFile, $options, $jsonFile) =
        map { s!\${(\w+)}!$ENV{$1}!g; $_ }
        split / {2,}/, $line;
        
    next unless $options;
    
    my $wdpath = "${globalCWorkingdir}/$workDirWithTime/C_$outputFile";
    mkpath($wdpath);
    my $joboutdir = "${globalCWorkingdir}/$workDirWithTime/output_$outputFile"; #. strftime("%FT%H-%M-%S",localtime);
    mkpath($joboutdir);
    my $json = '';
    if($jsonFile){
	$json = File::Spec->rel2abs($jsonFile);
    }
    my $cConfig = "${globalCWorkingdir}/$workDirWithTime/C_$outputFile.cfg";

### Prepare template    

    my $t = getCrabtemplate();
    for ($t) {
        s/##LOCAL_OR_GRID##/$arg{g} ? "grid" : "local"/eg;
        s/##WORKDIR##/$wdpath/g;
        s/##JOBS##/$arg{j} ? $arg{j} : ''/eg;
        s/##CMSSW_BASE##/$ENV{CMSSW_BASE}/g;
        s/##CMSSWConfigFile##/File::Spec->rel2abs($arg{c})/eg;
        s/##EVENTS_PER_JOB##/$eventsPerJob/g;
        s/##DATASET##/$dataset/g;
        s/##OUTPUTFILE##/$outputFile/g;
        s/##HN_USER##/$hypernewsName/g;
        s/##GLOBALGCWD##/$globalCWorkingdir/g;
        s/##OPTIONS##/$options/g;
	s/##FILTERLUMI##/$jsonFile ? '' : '#'/eg;
        s/##JSON##/$json/g;
        s/##JOBOUTDIR##/$joboutdir/g;
	s/##SEDIR##/$workDirWithTime\/output_$outputFile/g;
        s/##SE_DCACHE##/$arg{g} ? '' : ';'/eg;
        s/##SE_SCRATCH##/$arg{g} ? ';' : ''/eg; 
	s/##CCONFIG##/$cConfig/g;
    }

    open my $OUT, '>', $cConfig or die $!;
    print $OUT $t;
    close $OUT;
    
    push @runCs, "echo 'starting $cConfig'\nif [[ -f \"$wdpath/first_sub\" ]]; \nthen\necho already initialized!\nelse\ncrab -create -submit -cfg $cConfig\ntouch $wdpath/first_sub\nfi\n\n";
    push @checkCs, "echo 'checking $cConfig'\nif [[ -f \"$wdpath/first_sub\" ]]; \nthen\ncrab -status -c $wdpath\nelse\necho not yet submitted\nfi\n";
    push @getCs, "crab -getoutput -c $wdpath\ncrab -copyData -c $wdpath\n\n";
    push @killCs, "echo 'killing $cConfig'\ncrab -kill all -c $wdpath\nsleep 5\n";
    push @forHadd, "hadd ${globalCWorkingdir}/$workDirWithTime/${outputFile}.root $joboutdir/*.root\n";
    push @forJson, "crab -report -c $wdpath\ncp $wdpath/res/lumiSummary.json ${globalCWorkingdir}/$workDirWithTime/${outputFile}_lumi.json\n\n";

#lumiSummary.json in res

}

#let submit script write a file after each submitted task(N jobs) and let checkJobs check if file exists (and only then perform a check

open my $OUT, '>', "${globalCWorkingdir}/$workDirWithTime/createDirsAndRun.sh" or die $!;
#print $OUT $_ for @createDirs;
#print $OUT "\n" x 3;
print $OUT $_ for @runCs;
close $OUT;
chmod 0755, "${globalCWorkingdir}/$workDirWithTime/createDirsAndRun.sh";
print "run ${globalCWorkingdir}/$workDirWithTime/createDirsAndRun.sh to create dirs and submit jobs\n";

open my $OUTC, '>', "${globalCWorkingdir}/$workDirWithTime/checkAllJobs.sh" or die $!;
print $OUTC $_ for @checkCs;
#print $OUTC $_ for @getOut;
close $OUTC;
chmod 0755, "${globalCWorkingdir}/$workDirWithTime/checkAllJobs.sh";
print "run ${globalCWorkingdir}/$workDirWithTime/checkAllJobs.sh to check dirs and resubmit jobs\n";

open my $OUTG, '>', "${globalCWorkingdir}/$workDirWithTime/downloadAllFromSE.sh" or die $!;
print $OUTG $_ for @getCs;
close $OUTG;
chmod 0755, "${globalCWorkingdir}/$workDirWithTime/downloadAllFromSE.sh";
print "run ${globalCWorkingdir}/$workDirWithTime/downloadAllFromSE.sh to download from dcache to your sonar user space\n";


open my $OUTD, '>', "${globalCWorkingdir}/$workDirWithTime/killAllJobs.sh" or die $!;
print $OUTD $_ for @killCs;
close $OUTD;
##chmod 0755, "${globalCWorkingdir}/$workDirWithTime/killAllJobs.sh";
print "run ${globalCWorkingdir}/$workDirWithTime/killAllJobs.sh to kill all jobs\n";

open my $OUTR, '>', "${globalCWorkingdir}/$workDirWithTime/haddAllRoot.sh" or die $!;
print $OUTR $_ for @forHadd;
close $OUTR;
chmod 0755, "${globalCWorkingdir}/$workDirWithTime/haddAllRoot.sh";
print "run ${globalCWorkingdir}/$workDirWithTime/haddAllRoot.sh to hadd all output\n";

open my $OUTL, '>', "${globalCWorkingdir}/$workDirWithTime/getJsons.sh" or die $!;
print $OUTL $_ for @forJson;
close $OUTL;
chmod 0755, "${globalCWorkingdir}/$workDirWithTime/getJsons.sh";
print "run ${globalCWorkingdir}/$workDirWithTime/getJsons.sh to get all processed Jsons\n";

system("ln -s $ENV{CMSSW_BASE} ${globalCWorkingdir}/$workDirWithTime/CMSSW_BASE");

sub getCrabtemplate
{
    return <<'ENDE_TEMPLATE';
[CRAB]
cfg = 
jobtype = cmssw
scheduler = glite
use_server = 1

[CMSSW]
datasetpath = ##DATASET##
pset = ##CMSSWConfigFile##
pycfg_params = ##OPTIONS## outputFile=##OUTPUTFILE##

##FILTERLUMI##lumi_mask = ##JSON##
total_number_of_lumis = -1
events_per_job = ##EVENTS_PER_JOB##
output_file = ##OUTPUTFILE##.root


#total_number_of_events = 10000
#number_of_jobs = 30
#lumis_per_job = 200

[USER]
ui_working_dir= ##WORKDIR##
return_data = 0
copy_data = 1
storage_element = T2_DE_DESY
user_remote_dir = ##SEDIR##
outputdir = ##JOBOUTDIR##
eMail = ##HN_USER##@cern.ch
thresholdLevel = 90    #threshold for mail
publish_data=0

#logdir= /full/path/yourLogDir # default: workdir/res
#publish_data_name = name_you_prefer
#storage_path = srm://dcache-se-cms.desy.de:8443/pnfs/desy.de/cms/tier2/store

[GRID]

skipwmsauth = 1  # needed to work outside cern

#rb                      = CERN 
#proxy_server            = myproxy.cern.ch 
#virtual_organization    = cms
#retry_count             = 5
#lcg_catalog_type        = lfc
#lfc_host                = lfc-cms-test.cern.ch
#lfc_home                = /grid/cms
#ce_black_list = T2_US_Florida, osg.hpc.ufl.edu,T2_US_MIT
#ce_white_list=ciemat
#ce_black_list=egeece02.ifca.es, rossmann-osg.rcac.purdue.edu #, wisconsin 

ENDE_TEMPLATE

}

