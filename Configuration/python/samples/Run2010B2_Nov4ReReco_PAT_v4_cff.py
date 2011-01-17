<!-- templateTop.tmpl -->
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="en" xml:lang="en">
<head profile="http://www.w3.org/2005/11/profile">
<title>DBS data discovery page</title>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<meta http-equiv="Content-Language" content="en-us" />
<meta name="author" content="Valentin Kuznetsov (vkuznet at gmail dot com)" />
<meta name="MSSmartTagsPreventParsing" content="true" />
<meta name="ROBOTS" content="ALL" />
<meta name="Copyright" content="(CC) 2007, CMS collaboration." />
<meta http-equiv="imagetoolbar" content="no" />
<meta name="Rating" content="General" />
<link rel="icon" 
      type="image/png" 
      href="/dbs_discovery/images/CMSLogo.png" />
<link rel="stylesheet" type="text/css" href="/dbs_discovery/css/dbs.css" />
<link rel="search" type="application/opensearchdescription+xml" href="/dbs_discovery/xml/opensearch_desc.xml" title="CMS DBS" /> 
<!-- YUI CSS -->
<link rel="stylesheet" type="text/css" href="/dbs_discovery/YUI/container/assets/container.css" />
<link rel="stylesheet" type="text/css" href="/dbs_discovery/YUI/treeview/assets/skins/sam/treeview.css " />

<!-- set non-visible display content by default -->
<style type="text/css">div.normalcontent { display:none }</style>
<!-- if JavaScripts enables, turn visiable content on -->

<!-- YUI and WEBTOOLS -->
<script type="text/javascript" src="/dbs_discovery/js/yui_combined.txt.js"></script>

<link rel="stylesheet" type="text/css" href="/base/Common/mastheadcss?site=dbs"/>
<script type="text/javascript" src="/base/Common/masthead"></script>


<!-- DD and its dependencies -->
<script type="text/javascript" src="/dbs_discovery/js/dd_combined.txt.js"></script>
<script type="text/javascript">
function footerMenuText() {
   return _footerMenuText('/dbs_discovery','user');
}
</script>
</head>
<body onload="setGreeting();ajaxInit('cms_dbs_prod_global');loadMasthead();initialize_dhtmlHistory();" id="content">

<noscript>
<h1 class="box_red">Warning:</h1>
<table width="50%" class="main">
<tr>
<td>
<div class="sectionhead_tight">DBS/DLS discovery page
is AJAX enabled and require that your browser have scripting 
enabled and JavaScript support. Your browser either does not support JavaScript, 
or it has JavaScript support disabled. Please enable JavaScript support or 
use a different browser with JavaScript support to use this page.
</div>
</td>
</tr>
</table>
</noscript>

<div id="main" class="hide">
<script type="text/javascript">SetMain()</script>

<div id="view_menu" class="hide" align="right">
<table id="submenu" class="submenu">
<tr>
<td>
<a class="submenu" href="javascript:ChangeUserMode('user')">Physicist</a>
</td>
<td>
<a class="submenu" href="javascript:ChangeUserMode('expert')">Production</a>
</td>
<td>
<a class="submenu" href="javascript:ChangeUserMode('runManager')">Run Manager</a>
</td>
</tr>
</table>
</div>

<!-- end of templateTop.tmpl -->

<!-- templateAdvancedSearchForm.tmpl -->

<span id="defaultPage"></span>
<div align="center">
<form action="aSearch" method="get">
<div>
<input type="hidden" name="caseSensitive" value="on" id="caseSensitive" />
<input type="hidden" name="userMode" id="userMode" value="user" />
<input type="hidden" name="sortOrder" id="sortOrder" value="desc" />
<input type="hidden" name="sortName" id="sortName" value="" />
<input type="hidden" name="grid" id="grid" value="0" />
<input type="hidden" name="method" id="method" value="dbsapi" />
</div>

<table cellpadding="2" cellspacing="2">
<tr>
<td align="right">
<div id="dbsInstDef">
<b>DBS instances</b>
</div>
</td>
<td>
<select name="dbsInst" id="dbsInst" onchange="javascript:ReloadMethod('/dbs_discovery','_advanced','user')" style="">
<option value="cms_dbs_ph_analysis_02">cms_dbs_ph_analysis_02</option>
<option value="cms_dbs_prod_global">cms_dbs_prod_global</option>
<option value="cms_dbs_caf_analysis_01">cms_dbs_caf_analysis_01</option>
<option value="cms_dbs_ph_analysis_01">cms_dbs_ph_analysis_01</option>
</select>
</td>
<td>
<span id="case" name='case' class="hide">
Case-sensitivity:
<a href="javascript:CaseSensitiveOn();"><span id="caseOn" class="td_underline_pad">on</span></a> 
| 
<a href="javascript:CaseSensitiveOff();"><span id="caseOff" class="">off</span></a>
</span>
</td>
<td align="right">
&nbsp;&nbsp;&nbsp;
<b class="yellow_box" style="text-decoration:underline" onclick="javascript:aSearchHelp()">HELP</b>
</td>
</tr>
</table>

<div>
<input type="text" size="80" name="userInput" id="userInput" />
<input type="submit" value="Search" onclick="javascript:SetTagCookie('DBSDD_ainput','userInput')" />
<input type="reset" />
</div>

</form>

<div id="aSearchHELP" class="hide">
<table>
<tr>
<td align="left">
<span class="sectionhead_tight">
Query Language (QL) Help
</span>
</td>
<td align="right">
<a href="javascript:HideTag('aSearchHELP')">close &#8855;</a>
</td>
</tr>

<tr><td colspan="2"><hr class="dbs" /></td></tr>

<tr valign="top">

<td colspan="2">
<div class="sectionhead">INTRODUCTION</div>
The QL was designed to help you find out CMS data quickly. It supports a set of keywords which
specify what you're looking for. For example, run keyword instruct QL that you're looking for
run number. Every keyword followed by constrain operator, such as equal "=". You can combine
any number of constrains by using AND|OR keywords.
<br/>
A full description of the Query Language can be found 
<a href="https://twiki.cern.ch/twiki/bin/view/CMS/QL">here</a>. Please note that
it is still under development.
<br/>
<hr class="dbs"/>
<br/>

<table width="100%"><tr><td align="left">
<a name="SYNTAX">
<span class="sectionhead">SYNTAX</span>
</a>
</td><td align="right">
<a href="javascript:HideTag('aSearchHELP')">close &#8855;</a>
</td></tr></table>
<b>
FIND &lt;keyword&gt; WHERE &lt;keyword&gt; &lt;op&gt; &lt;value&gt; AND | OR  ...
</b>
<br/>
Constrain operators: 
<b>
&lt;=, &lt;, &gt;=, &gt;, =, not like, like, in, between
</b>
<br/>
words FIND,WHERE,AND,OR can be upper or lower case. 
<br/>
<hr class="dbs"/>
<br/>

<table width="100%"><tr><td align="left">
<a name="KEYWORDS">
<span class="sectionhead">KEYWORDS</span>
</a>
</td><td align="right">
<a href="javascript:HideTag('aSearchHELP')">close &#8855;</a>
</td></tr></table>
<!-- templateQLHelp.tmpl -->
<div>

</div>
<hr class="dbs" />
<table class="dbs_table">
<tr>
<th class="th_left">
KEYS
</th>
<th class="th_left">
ATTRIBUTES
</th>
<th class="th_left">
EXAMPLES
</th>
</tr>
<tr valign="top">
<td>
sum
</td>
<td class="td_left">
</td>
<td class="td_left">
<em>I want to find total size of the files in a specified dataset?</em>
<br/>
<b>find sum(file.size) where dataset =/test_primary_001/TestProcessedDS002/GEN-SIM</b>
<br/>
<em>I want to find total size of the files per dataset dataset basis?</em>
<br/>
<b>find sum(file.size), dataset where dataset = *</b>
<br/>
<em>I want to find total size of the files and number of files in all datasets?</em>
<br/>
<b>find sum(file.size), count(file), dataset where dataset = *</b>
<br/>
<em>I want to find number of files per run of a specified dataset?</em>
<br/>
<b>find count(file), run where dataset = /test_primary_001/TestProcessedDS002/GEN-SIM</b>
<br/>
<em>I want to find number of blocks and average size of a block per dataset?</em>
<br/>
<b>find count(block), avg(block.size), dataset where dataset = *RAW</b>
<br/>
<em>I want to find maximum file size and minimum file size in a primary dataset?</em>
<br/>
<b>find max(file.size), min(file.size) where primds =  test_primary_001</b>
<br/>
<em>I want to find maximum file size, minimum file size and average file size in a primary dataset?</em>
<br/>
<b>find max(file.size), min(file.size), avg(file.size) where primds =  test_primary_001</b>
<br/>
<em>I want to find number of files that are invalid?</em>
<br/>
<b>find count(file) where file.status =  INVALID</b>
<br/>
<em>I want to find number of files that are invalid per dataset?</em>
<br/>
<b>find count(file), dataset where file.status =  INVALID</b>
<br/>
<em>I want to find number of file status?</em>
<br/>
<b>find count(file.status)</b>
<br/>
<em>I want to find average start time of all run?</em>
<br/>
<b>find avg(run.starttime)</b>
<br/>
<em>I want to find number of lumi sections in specified runs per dataset?</em>
<br/>
<b>find count(lumi), dataset where run in (1,2,3 )</b>
<br/>
</td>
</tr>
<tr class="zebra" valign="top">
<td>
pset
</td>
<td class="td_left">
</td>
<td class="td_left">
<em>I want to find all dataset with these parameter set values associatorL25PixelTauIsolated.coneSize > 0 ,associatorL25SingleTau.coneSize > 0, associatorL25SingleTau.jets like a?</em>
<br/>
<b>find dataset where pset = associatorL25PixelTauIsolated.coneSize > 0 & associatorL25SingleTau.coneSize > 0 & associatorL25SingleTau.jets < > a</b>
<br/>
<em>I want to find all files, runs with these parameter set values associatorL25PixelTauIsolated.coneSize > 0?</em>
<br/>
<b>find file, runs where pset = associatorL25PixelTauIsolated.coneSize > 0</b>
<br/>
</td>
</tr>
<tr valign="top">
<td>
mcdesc
</td>
<td class="td_left">
def<br/>
content<br/>
parent<br/>
createdate<br/>
moddate<br/>
createby<br/>
modby<br/>
id<br/>
</td>
<td class="td_left">
<em>I want to find MC description used for given  dataset?</em>
<br/>
<b>find mcdesc where dataset = /CSA07Muon/CMSSW_1_6_7-CSA07-Tier0-A1-Chowder/RECO</b>
<br/>
<em>I want to find MC description attributes like its definition, content, and decay chain (parents), creation date, modification date, created by, modified by in a dataset?</em>
<br/>
<b>find mcdesc.def, mcdesc.content, mcdesc.parent, mcdesc.createdate, mcdesc.moddate, mcdesc.createby, mcdesc.modby where dataset = /CSA07Muon/CMSSW_1_6_7-CSA07-Tier0-A1-Chowder/RECO</b>
<br/>
</td>
</tr>
<tr class="zebra" valign="top">
<td>
ads
</td>
<td class="td_left">
name<br/>
version<br/>
dataset<br/>
type<br/>
status<br/>
def<br/>
createdate<br/>
moddate<br/>
createby<br/>
modby<br/>
count<br/>
id<br/>
</td>
<td class="td_left">
<em>I want to find all analysis datasets?</em>
<br/>
<b>find ads</b>
<br/>
<em>I want to find all analysis datasets in a particular dataset (processed)?</em>
<br/>
<b>find ads where dataset = /CSA07Muon/CMSSW_1_6_7-CSA07-Tier0-A1-Chowder/RECO</b>
<br/>
<em>I want to find analysis datasets attributes like its definition, type, status, created by , modified by, creation date, last modification date of a particular analysis dataset?</em>
<br/>
<b>find ads.def, ads.type, ads.status, ads.createby, ads.modby, ads.createdate, ads.moddate where ads.name = MyAds</b>
<br/>
<em>I want to find all files in a particular ads?</em>
<br/>
<b>find file where ads.name = MyAds</b>
<br/>
<em>I want to find files, run and lumi in a particular ads?</em>
<br/>
<b>find file, run, lumi where ads.name = MyAds</b>
<br/>
<em>I want to find files, run and lumi in a set of ads?</em>
<br/>
<b>find file,run,lumi where ads.name in ( MyAds, Myades )</b>
<br/>
</td>
</tr>
<tr valign="top">
<td>
trigdesc
</td>
<td class="td_left">
def<br/>
createdate<br/>
moddate<br/>
createby<br/>
modby<br/>
id<br/>
</td>
<td class="td_left">
<em>I want to find trigger description used for given  dataset?</em>
<br/>
<b>find trigdesc where dataset = /CSA07Muon/CMSSW_1_6_7-CSA07-Tier0-A1-Chowder/RECO</b>
<br/>
<em>I want to find trigger description attributes like its definition, creation date, modification date, created by, modified by in a dataset?</em>
<br/>
<b>find trigdesc.def, trigdesc.createdate, trigdesc.moddate, trigdesc.createby, trigdesc.modby where dataset = /CSA07Muon/CMSSW_1_6_7-CSA07-Tier0-A1-Chowder/RECO</b>
<br/>
</td>
</tr>
<tr class="zebra" valign="top">
<td>
count
</td>
<td class="td_left">
</td>
<td class="td_left">
<em>I want to find total size of the files in a specified dataset?</em>
<br/>
<b>find sum(file.size) where dataset =/test_primary_001/TestProcessedDS002/GEN-SIM</b>
<br/>
<em>I want to find total size of the files per dataset dataset basis?</em>
<br/>
<b>find sum(file.size), dataset where dataset = *</b>
<br/>
<em>I want to find total size of the files and number of files in all datasets?</em>
<br/>
<b>find sum(file.size), count(file), dataset where dataset = *</b>
<br/>
<em>I want to find number of files per run of a specified dataset?</em>
<br/>
<b>find count(file), run where dataset = /test_primary_001/TestProcessedDS002/GEN-SIM</b>
<br/>
<em>I want to find number of blocks and average size of a block per dataset?</em>
<br/>
<b>find count(block), avg(block.size), dataset where dataset = *RAW</b>
<br/>
<em>I want to find maximum file size and minimum file size in a primary dataset?</em>
<br/>
<b>find max(file.size), min(file.size) where primds =  test_primary_001</b>
<br/>
<em>I want to find maximum file size, minimum file size and average file size in a primary dataset?</em>
<br/>
<b>find max(file.size), min(file.size), avg(file.size) where primds =  test_primary_001</b>
<br/>
<em>I want to find number of files that are invalid?</em>
<br/>
<b>find count(file) where file.status =  INVALID</b>
<br/>
<em>I want to find number of files that are invalid per dataset?</em>
<br/>
<b>find count(file), dataset where file.status =  INVALID</b>
<br/>
<em>I want to find number of file status?</em>
<br/>
<b>find count(file.status)</b>
<br/>
<em>I want to find average start time of all run?</em>
<br/>
<b>find avg(run.starttime)</b>
<br/>
<em>I want to find number of lumi sections in specified runs per dataset?</em>
<br/>
<b>find count(lumi), dataset where run in (1,2,3 )</b>
<br/>
</td>
</tr>
<tr valign="top">
<td>
phygrp
</td>
<td class="td_left">
name<br/>
createdate<br/>
moddate<br/>
createby<br/>
modby<br/>
count<br/>
id<br/>
</td>
<td class="td_left">
<em>I want to find all physics groups?</em>
<br/>
<b>find phygrp</b>
<br/>
<em>I want to find physics groups of a particular dataset?</em>
<br/>
<b>find phygrp where dataset = /test_primary_001/TestProcessedDS002/GEN-SIM</b>
<br/>
<em>I want to find all datasets with a particular physics group?</em>
<br/>
<b>find dataset where phygrp = BPositive</b>
<br/>
<em>I want to find all datasets with a particular physics groups pattern?</em>
<br/>
<b>find dataset where phygrp like *BPositive</b>
<br/>
<em>I want to find file and run in two particular physics group?</em>
<br/>
<b>find file,run where phygrp in (BPositive, Any)</b>
<br/>
<em>I want to find attributes like id, creation date, modification date, created by, modified by of a physics group?</em>
<br/>
<b>find phygrp, phygrp.id, phygrp.createdate , phygrp.moddate, phygrp.createby, phygrp.modby</b>
<br/>
<em>I want to count all the physics groups?</em>
<br/>
<b>find count(phygrp)</b>
<br/>
<em>I want to count all the physics groups?</em>
<br/>
<b>find count(phygrp)</b>
<br/>
</td>
</tr>
<tr class="zebra" valign="top">
<td>
block
</td>
<td class="td_left">
name<br/>
size<br/>
dataset<br/>
numfiles<br/>
numevents<br/>
status<br/>
createdate<br/>
moddate<br/>
createby<br/>
modby<br/>
count<br/>
id<br/>
</td>
<td class="td_left">
<em>I want to find blocks in a dataset?</em>
<br/>
<b>find block where dataset = /CSA07Muon/CMSSW_1_6_7-CSA07-Tier0-A1-Chowder/RECO</b>
<br/>
<em>I want to find blocks and its attributes like  its size, number of files, number of events, its status, creation date, modification date, created by, modified by in a dataset?</em>
<br/>
<b>find block, block.size, block.numfiles, block.numevents, block.status, block.createdate, block.moddate, block.createby, block.modby where dataset = /CSA07Muon/CMSSW_1_6_7-CSA07-Tier0-A1-Chowder/RECO</b>
<br/>
<em>I want to find all the  attributes like dataset, size,  creation date, modification date, created by, modified by in a dataset?</em>
<br/>
<b>find block.dataset, block.size,  block.createdate, block.moddate, block.createby, block.modby where block = /CSA07Muon/CMSSW_1_6_7-CSA07-Tier0-A1-Chowder/RECO#01123fd3-5486-41fe-8b90-7dbb8fbe69b8</b>
<br/>
<em>I want to count all the blocks in a dataset?</em>
<br/>
<b>find count(block) where dataset = /CSA07Muon/CMSSW_1_6_7-CSA07-Tier0-A1-Chowder/RECO</b>
<br/>
<em>I want to count all the blocks in a dataset?</em>
<br/>
<b>find count(block) where dataset = /CSA07Muon/CMSSW_1_6_7-CSA07-Tier0-A1-Chowder/RECO</b>
<br/>
<em>I want to sum up the size of all the blocks in a particular dataset?</em>
<br/>
<b>find sum(block.size)  where dataset = /CSA07Muon/CMSSW_1_6_7-CSA07-Tier0-A1-Chowder/RECO</b>
<br/>
</td>
</tr>
<tr valign="top">
<td>
dataset
</td>
<td class="td_left">
parent<br/>
release<br/>
tier<br/>
status<br/>
xsection<br/>
era<br/>
tag<br/>
createdate<br/>
moddate<br/>
createby<br/>
modby<br/>
count<br/>
id<br/>
</td>
<td class="td_left">
<em>I want to find all datasets paths?</em>
<br/>
<b>find dataset</b>
<br/>
<em>I want to find all dataset with name like Online?</em>
<br/>
<b>find dataset where dataset like *Online*</b>
<br/>
<em>I want to find all dataset with name like some pattern?</em>
<br/>
<b>find dataset where dataset like /CSA0*/CMSSW_*/*</b>
<br/>
<em>I want to find parent of a dataset?</em>
<br/>
<b>find dataset.parent where dataset = /CSA07Muon/Skim-zToTauTau_MuTau-Tier0-A1-Chowder/USER</b>
<br/>
<em>I want to find attributes like release, era, cross-section, tag, status, creation date, modification date, created by, modified by of a particular dataset?</em>
<br/>
<b>find dataset.release, dataset.era, dataset.xsection, dataset.tag, dataset.status, dataset.createdate, dataset.moddate, dataset.createby, dataset.modby where dataset = /CSA07Muon/Skim-zToTauTau_MuTau-Tier0-A1-Chowder/USER</b>
<br/>
</td>
</tr>
<tr class="zebra" valign="top">
<td>
ilumi
</td>
<td class="td_left">
</td>
<td class="td_left">
<em>I want to find integrated luminosity of a set of runs?</em>
<br/>
<b>find ilumi where run in (1,2,3)</b>
<br/>
<em>I want to find integrated luminosity of a set of runs on file by file basis?</em>
<br/>
<b>find ilumi, file where run in (1,2,3)</b>
<br/>
<em>I want to find integrated luminosity per file basis of a set of runs?</em>
<br/>
<b>find ilumi, file where run in (1,2,3)</b>
<br/>
<em>I want to find integrated luminosity per file basis of in a particular dataset?</em>
<br/>
<b>find ilumi, file where dataset = /test_primary_001/TestProcessedDS002/GEN-SIM</b>
<br/>
<em>I want to find integrated luminosity per dataset whener run is greater than 2000?</em>
<br/>
<b>find ilumi, dataset where run > 2000</b>
<br/>
</td>
</tr>
<tr valign="top">
<td>
datatype
</td>
<td class="td_left">
type<br/>
createdate<br/>
moddate<br/>
createby<br/>
modby<br/>
id<br/>
</td>
<td class="td_left">
<em>I want to find all datatypes?</em>
<br/>
<b>find datatype</b>
<br/>
<em>I want to find all datatypes and its attribute like type, id,  modified by, created by, create date and modified date?</em>
<br/>
<b>find datatype, datatype.id, datatype.createdate, datatype.moddate, datatype.createby, datatype.modby</b>
<br/>
<em>I want to find all datasets that has a specified datatype?</em>
<br/>
<b>find  dataset where datatype = cosmic</b>
<br/>
<em>I want to find all files that has a specified datatype or whose size is > 1000?</em>
<br/>
<b>find file where datatype = cosmic or file.size > 1000</b>
<br/>
</td>
</tr>
<tr class="zebra" valign="top">
<td>
run
</td>
<td class="td_left">
number<br/>
numevents<br/>
numlss<br/>
totlumi<br/>
store<br/>
starttime<br/>
endtime<br/>
createdate<br/>
moddate<br/>
createby<br/>
modby<br/>
count<br/>
id<br/>
</td>
<td class="td_left">
<em>I want to find all runs in a particular primary dataset?</em>
<br/>
<b>find run where primds = test_primary_001</b>
<br/>
<em>I want to find attributes of like number of events, number of lumi sections, total luminosity, store number, start time and end time of a particular run?</em>
<br/>
<b>find run.numevents, run.numlss, run.totlumi, run.store, run.starttime, run.endtime where run = 23</b>
<br/>
<em>I want to count all the runs in a particular dataset?</em>
<br/>
<b>find count(run) where dataset = /test_primary_001/TestProcessedDS002/GEN-SIM</b>
<br/>
<em>I want to count all the runs in a particular dataset?</em>
<br/>
<b>find count(run) where dataset = /test_primary_001/TestProcessedDS002/GEN-SIM</b>
<br/>
<em>I want to find all runs created exactly between 2008-05-01 12:05 2008-05-01 12:06?</em>
<br/>
<b>find run where run.createdate = 2008-05-01 12:05</b>
<br/>
<em>I want to find all runs created exactly between 2008-05-01 12 2008-05-01 1?</em>
<br/>
<b>find run where run.createdate = 2008-05-01 12</b>
<br/>
<em>I want to find all runs created exactly between 2008-05-01 2008-05-02?</em>
<br/>
<b>find run where run.createdate = 2008-05-01</b>
<br/>
<em>I want to find all runs created exactly between 2008-05 2008-06?</em>
<br/>
<b>find run where run.createdate = 2008-05</b>
<br/>
<em>I want to find all runs created exactly between 2008 2009?</em>
<br/>
<b>find run where run.createdate = 2008</b>
<br/>
<em>I want to sum up the events of all the runs in a particular dataset such that the file have size greater than some value?</em>
<br/>
<b>find sum(run.numevents) where dataset = /test_primary_001/TestProcessedDS002/GEN-SIM and file.size > 20000</b>
<br/>
</td>
</tr>
<tr valign="top">
<td>
site
</td>
<td class="td_left">
name<br/>
</td>
<td class="td_left">
<em>I want to find all storage elements?</em>
<br/>
<b>find site</b>
<br/>
<em>I want to find all storage elements in a dataset?</em>
<br/>
<b>find site where dataset = /CSA07Muon/CMSSW_1_6_7-CSA07-Tier0-A1-Chowder/RECO</b>
<br/>
<em>I want to find all files at a storage element that start with castorsrm.cr?</em>
<br/>
<b>find file where site like castorsrm.cr*</b>
<br/>
<em>I want to find all datasets at a storage element that start with castorsrm.cr?</em>
<br/>
<b>find dataset where site like castorsrm.cr*</b>
<br/>
<em>I want to find all files at a particular storage element?</em>
<br/>
<b>find file where site = T1_FR_CCIN2P3</b>
<br/>
<em>I want to find all files at a set of storage elements?</em>
<br/>
<b>find file where site in ( srm-disk.pic.es, castorsrm.cr, T1_FR_CCIN2P3, T1_TW_ASGC )</b>
<br/>
<em>I want to find all blocks and all datasets at a particular storage element?</em>
<br/>
<b>find block , dataset where site = srm-disk.pic.es</b>
<br/>
<em>I want to find all blocks that are not available on any site?</em>
<br/>
<b>find block where site = null</b>
<br/>
</td>
</tr>
<tr class="zebra" valign="top">
<td>
primds
</td>
<td class="td_left">
name<br/>
createdate<br/>
moddate<br/>
createby<br/>
modby<br/>
count<br/>
id<br/>
</td>
<td class="td_left">
<em>I want to find all primary datasets?</em>
<br/>
<b>find primds</b>
<br/>
<em>I want to find all primary datasets created after 2007-04-20?</em>
<br/>
<b>find primds where primds.createdate > 2007-04-20</b>
<br/>
<em>I want to find all primary datasets created before 2007-04-20?</em>
<br/>
<b>find primds where primds.createdate < 2007-04-20</b>
<br/>
<em>I want to find attributes like creation date, modification date, created by, modified by of a primary datasets?</em>
<br/>
<b>find primds.createdate, primds.moddate, primds.createby, primds.modby where primds = CSA07Muon</b>
<br/>
</td>
</tr>
<tr valign="top">
<td>
avg
</td>
<td class="td_left">
</td>
<td class="td_left">
<em>I want to find total size of the files in a specified dataset?</em>
<br/>
<b>find sum(file.size) where dataset =/test_primary_001/TestProcessedDS002/GEN-SIM</b>
<br/>
<em>I want to find total size of the files per dataset dataset basis?</em>
<br/>
<b>find sum(file.size), dataset where dataset = *</b>
<br/>
<em>I want to find total size of the files and number of files in all datasets?</em>
<br/>
<b>find sum(file.size), count(file), dataset where dataset = *</b>
<br/>
<em>I want to find number of files per run of a specified dataset?</em>
<br/>
<b>find count(file), run where dataset = /test_primary_001/TestProcessedDS002/GEN-SIM</b>
<br/>
<em>I want to find number of blocks and average size of a block per dataset?</em>
<br/>
<b>find count(block), avg(block.size), dataset where dataset = *RAW</b>
<br/>
<em>I want to find maximum file size and minimum file size in a primary dataset?</em>
<br/>
<b>find max(file.size), min(file.size) where primds =  test_primary_001</b>
<br/>
<em>I want to find maximum file size, minimum file size and average file size in a primary dataset?</em>
<br/>
<b>find max(file.size), min(file.size), avg(file.size) where primds =  test_primary_001</b>
<br/>
<em>I want to find number of files that are invalid?</em>
<br/>
<b>find count(file) where file.status =  INVALID</b>
<br/>
<em>I want to find number of files that are invalid per dataset?</em>
<br/>
<b>find count(file), dataset where file.status =  INVALID</b>
<br/>
<em>I want to find number of file status?</em>
<br/>
<b>find count(file.status)</b>
<br/>
<em>I want to find average start time of all run?</em>
<br/>
<b>find avg(run.starttime)</b>
<br/>
<em>I want to find number of lumi sections in specified runs per dataset?</em>
<br/>
<b>find count(lumi), dataset where run in (1,2,3 )</b>
<br/>
</td>
</tr>
<tr class="zebra" valign="top">
<td>
dq
</td>
<td class="td_left">
</td>
<td class="td_left">
<em>I want to find all files with data quality as TIB_DCS=UNKNOWN, Tracker_Global=GOOD and TIB_Local=GOOD?</em>
<br/>
<b>find file where dq = TIB_DCS=UNKNOWN & Tracker_Global=GOOD & TIB_Local=GOOD</b>
<br/>
<em>I want to find all runs with data quality as TIB_DCS=UNKNOWN, Tracker_Global=GOOD and TIB_Local=GOOD?</em>
<br/>
<b>find run where dq = TIB_DCS=UNKNOWN & Tracker_Global=GOOD & TIB_Local=GOOD</b>
<br/>
<em>I want to find all files and runs with data quality as TIB_DCS=UNKNOWN, Tracker_Global=GOOD and TIB_Local=GOOD?</em>
<br/>
<b>find file, run where dq = TIB_DCS=UNKNOWN & Tracker_Global=GOOD & TIB_Local=GOOD</b>
<br/>
<em>I want to find all files and runs with data quality as TIB_DCS=UNKNOWN, Tracker_Global=GOOD and TIB_Local=GOOD and in dataset = /CSA07Muon/CMSSW_1_6_7-CSA07-Tier0-A1-Chowder/RECO?</em>
<br/>
<b>find file, run where dq = TIB_DCS=UNKNOWN & Tracker_Global=GOOD & TIB_Local=GOOD and dataset = /CSA07Muon/CMSSW_1_6_7-CSA07-Tier0-A1-Chowder/RECO</b>
<br/>
</td>
</tr>
<tr valign="top">
<td>
lumi
</td>
<td class="td_left">
evnum<br/>
startevnum<br/>
endevnum<br/>
number<br/>
starttime<br/>
endtime<br/>
createdate<br/>
moddate<br/>
createby<br/>
modby<br/>
count<br/>
id<br/>
</td>
<td class="td_left">
<em>I want to find lumi section of a file?</em>
<br/>
<b>find lumi where file = NEW_TEST0005</b>
<br/>
<em>I want to count lumi section of a file?</em>
<br/>
<b>find lumi.count where file = NEW_TEST0005</b>
<br/>
<em>I want to find lumi section and its attributes like start time, end time, start event number and end event number in a file?</em>
<br/>
<b>find lumi, lumi.starttime, lumi.endtime, lumi.startevnum, lumi.endevnum where file = NEW_TEST0005</b>
<br/>
<em>I want to find lumi section in a set of files?</em>
<br/>
<b>find lumi where file in ( NEW_TEST0005, NEW_TEST0004, NEW_TEST0003 )</b>
<br/>
<em>I want to find lumi section either in a set of files or in a dataset?</em>
<br/>
<b>find lumi where file in ( NEW_TEST0005, NEW_TEST0004, NEW_TEST0003 ) or dataset = /test_primary_001/TestProcessedDS002/GEN-SIM</b>
<br/>
<em>I want to find lumi section either in a set of files or in a dataset or in a set of runs?</em>
<br/>
<b>find lumi where file in ( NEW_TEST0005, NEW_TEST0004, NEW_TEST0003 ) or dataset = /test_primary_001/TestProcessedDS002/GEN-SIM or run in (1,2,3)</b>
<br/>
<em>I want to find lumi section for a particular event number?</em>
<br/>
<b>find lumi where lumi.evnum  = 150</b>
<br/>
<em>I want to find file for a particular event number?</em>
<br/>
<b>find file where lumi.evnum  = 150</b>
<br/>
</td>
</tr>
<tr class="zebra" valign="top">
<td>
min
</td>
<td class="td_left">
</td>
<td class="td_left">
<em>I want to find total size of the files in a specified dataset?</em>
<br/>
<b>find sum(file.size) where dataset =/test_primary_001/TestProcessedDS002/GEN-SIM</b>
<br/>
<em>I want to find total size of the files per dataset dataset basis?</em>
<br/>
<b>find sum(file.size), dataset where dataset = *</b>
<br/>
<em>I want to find total size of the files and number of files in all datasets?</em>
<br/>
<b>find sum(file.size), count(file), dataset where dataset = *</b>
<br/>
<em>I want to find number of files per run of a specified dataset?</em>
<br/>
<b>find count(file), run where dataset = /test_primary_001/TestProcessedDS002/GEN-SIM</b>
<br/>
<em>I want to find number of blocks and average size of a block per dataset?</em>
<br/>
<b>find count(block), avg(block.size), dataset where dataset = *RAW</b>
<br/>
<em>I want to find maximum file size and minimum file size in a primary dataset?</em>
<br/>
<b>find max(file.size), min(file.size) where primds =  test_primary_001</b>
<br/>
<em>I want to find maximum file size, minimum file size and average file size in a primary dataset?</em>
<br/>
<b>find max(file.size), min(file.size), avg(file.size) where primds =  test_primary_001</b>
<br/>
<em>I want to find number of files that are invalid?</em>
<br/>
<b>find count(file) where file.status =  INVALID</b>
<br/>
<em>I want to find number of files that are invalid per dataset?</em>
<br/>
<b>find count(file), dataset where file.status =  INVALID</b>
<br/>
<em>I want to find number of file status?</em>
<br/>
<b>find count(file.status)</b>
<br/>
<em>I want to find average start time of all run?</em>
<br/>
<b>find avg(run.starttime)</b>
<br/>
<em>I want to find number of lumi sections in specified runs per dataset?</em>
<br/>
<b>find count(lumi), dataset where run in (1,2,3 )</b>
<br/>
</td>
</tr>
<tr valign="top">
<td>
max
</td>
<td class="td_left">
</td>
<td class="td_left">
<em>I want to find total size of the files in a specified dataset?</em>
<br/>
<b>find sum(file.size) where dataset =/test_primary_001/TestProcessedDS002/GEN-SIM</b>
<br/>
<em>I want to find total size of the files per dataset dataset basis?</em>
<br/>
<b>find sum(file.size), dataset where dataset = *</b>
<br/>
<em>I want to find total size of the files and number of files in all datasets?</em>
<br/>
<b>find sum(file.size), count(file), dataset where dataset = *</b>
<br/>
<em>I want to find number of files per run of a specified dataset?</em>
<br/>
<b>find count(file), run where dataset = /test_primary_001/TestProcessedDS002/GEN-SIM</b>
<br/>
<em>I want to find number of blocks and average size of a block per dataset?</em>
<br/>
<b>find count(block), avg(block.size), dataset where dataset = *RAW</b>
<br/>
<em>I want to find maximum file size and minimum file size in a primary dataset?</em>
<br/>
<b>find max(file.size), min(file.size) where primds =  test_primary_001</b>
<br/>
<em>I want to find maximum file size, minimum file size and average file size in a primary dataset?</em>
<br/>
<b>find max(file.size), min(file.size), avg(file.size) where primds =  test_primary_001</b>
<br/>
<em>I want to find number of files that are invalid?</em>
<br/>
<b>find count(file) where file.status =  INVALID</b>
<br/>
<em>I want to find number of files that are invalid per dataset?</em>
<br/>
<b>find count(file), dataset where file.status =  INVALID</b>
<br/>
<em>I want to find number of file status?</em>
<br/>
<b>find count(file.status)</b>
<br/>
<em>I want to find average start time of all run?</em>
<br/>
<b>find avg(run.starttime)</b>
<br/>
<em>I want to find number of lumi sections in specified runs per dataset?</em>
<br/>
<b>find count(lumi), dataset where run in (1,2,3 )</b>
<br/>
</td>
</tr>
<tr class="zebra" valign="top">
<td>
release
</td>
<td class="td_left">
createdate<br/>
moddate<br/>
createby<br/>
modby<br/>
count<br/>
id<br/>
</td>
<td class="td_left">
<em>I want to find all releases?</em>
<br/>
<b>find release</b>
<br/>
<em>I want to find all CMSSW_1 release series?</em>
<br/>
<b>find release where release like CMSSW_1*</b>
<br/>
</td>
</tr>
<tr valign="top">
<td>
algo
</td>
<td class="td_left">
version<br/>
exe<br/>
family<br/>
content<br/>
createdate<br/>
moddate<br/>
createby<br/>
modby<br/>
id<br/>
</td>
<td class="td_left">
<em>I want to find all algorithms and its attribute like family, version, executable, modified by, created by, create date and modified date?</em>
<br/>
<b>find algo.family, algo.version, algo.exe, almo.modby, algo.createby, algo.createdate, algo.moddate</b>
<br/>
<em>I want to find all  datasets that has a specified algo version or a specified algo family?</em>
<br/>
<b>find  dataset where algo.version = CMSSW or algo.family = CMS*</b>
<br/>
<em>I want to find algo configuration of a specified file?</em>
<br/>
<b>find algo.family, algo.version, algo.exe, algo.hash where file = MyLogocalFileName</b>
<br/>
</td>
</tr>
<tr class="zebra" valign="top">
<td>
file
</td>
<td class="td_left">
name<br/>
size<br/>
status<br/>
release<br/>
parent<br/>
child<br/>
tier<br/>
type<br/>
numevents<br/>
checksum<br/>
createdate<br/>
moddate<br/>
createby<br/>
modby<br/>
count<br/>
id<br/>
</td>
<td class="td_left">
<em>I want to find files in a dataset?</em>
<br/>
<b>find file where dataset = /CSA07Muon/CMSSW_1_6_7-CSA07-Tier0-A1-Chowder/RECO</b>
<br/>
<em>I want to count all files in a dataset?</em>
<br/>
<b>find file.count where dataset = /CSA07Muon/CMSSW_1_6_7-CSA07-Tier0-A1-Chowder/RECO</b>
<br/>
<em>I want to find files which are invalid  in a dataset?</em>
<br/>
<b>find file where dataset = /CSA07Muon/CMSSW_1_6_7-CSA07-Tier0-A1-Chowder/RECO and file.status= INVALID</b>
<br/>
<em>I want to find file and its release, size, type, tier, status and checksum in a dataset?</em>
<br/>
<b>find file, file.release, file.size, file.type, file.tier, file.status, file.checksum where dataset = /CSA07Muon/CMSSW_1_6_7-CSA07-Tier0-A1-Chowder/RECO</b>
<br/>
<em>I want to find a parent of a file?</em>
<br/>
<b>find file.parent where file = /store/user/ndefilip/Skim-zToTauTau_MuTau-Tier0-A1-Chowder/NicolaDeFilippis/Skim-zToTauTau_MuTau-Tier0-A1-Chowder_85f0790dd16f9aff6ccde9b27395c4d2/zToTauTau_MuTau_372.root</b>
<br/>
<em>I want to find file whose parent I know?</em>
<br/>
<b>find file where file.parent = /store/user/ndefilip/Skim-zToTauTau_MuTau-Tier0-A1-Chowder/NicolaDeFilippis/Skim-zToTauTau_MuTau-Tier0-A1-Chowder_85f0790dd16f9aff6ccde9b27395c4d2/zToTauTau_MuTau_372.root</b>
<br/>
<em>I want to find a child of a file?</em>
<br/>
<b>find file.child where file = /store/user/ndefilip/Skim-zToTauTau_MuTau-Tier0-A1-Chowder/NicolaDeFilippis/Skim-zToTauTau_MuTau-Tier0-A1-Chowder_85f0790dd16f9aff6ccde9b27395c4d2/zToTauTau_MuTau_372.root</b>
<br/>
<em>I want to find a file whose child I know?</em>
<br/>
<b>find file where file.child = /store/user/ndefilip/Skim-zToTauTau_MuTau-Tier0-A1-Chowder/NicolaDeFilippis/Skim-zToTauTau_MuTau-Tier0-A1-Chowder_85f0790dd16f9aff6ccde9b27395c4d2/zToTauTau_MuTau_372.root</b>
<br/>
<em>I want to find all files created between 2007-04-20 and 2007-04-21?</em>
<br/>
<b>find file where  file.createdate = 2007-04-20</b>
<br/>
<em>I want to find all files created exactly at 2007-04-20 11:27:21 CDT or modified in 2008?</em>
<br/>
<b>find file where  file.createdate = 2007-04-20 11:27:21 CDT  or file.moddate > 2008</b>
<br/>
<em>I want to sum up the size of all the files in a particular dataset?</em>
<br/>
<b>find sum(file.size) where dataset = /test_primary_001/TestProcessedDS002/GEN-SIM</b>
<br/>
<em>I want to find those file that do not have any person associated with it?</em>
<br/>
<b>find file where file.createby = null</b>
<br/>
</td>
</tr>
<tr valign="top">
<td>
config
</td>
<td class="td_left">
name<br/>
hash<br/>
content<br/>
version<br/>
type<br/>
annotation<br/>
createdate<br/>
moddate<br/>
createby<br/>
modby<br/>
id<br/>
</td>
<td class="td_left">
<em>I want to find configuration and its attributes like name, hash, content, version, type, annotation, creation date, modification date, created by, modified by in a dataset?</em>
<br/>
<b>find config.name, config.hash, config.content, config.version, config.type, config. annotation, config.createdate, config.moddate, config.createby, config.modby where dataset = /CSA07Muon/CMSSW_1_6_7-CSA07-Tier0-A1-Chowder/RECO</b>
<br/>
</td>
</tr>
<tr class="zebra" valign="top">
<td>
procds
</td>
<td class="td_left">
name<br/>
parent<br/>
release<br/>
tier<br/>
status<br/>
xsection<br/>
era<br/>
tag<br/>
createdate<br/>
moddate<br/>
createby<br/>
modby<br/>
count<br/>
id<br/>
</td>
<td class="td_left">
<em>I want to find all processed datasets?</em>
<br/>
<b>find procds</b>
<br/>
<em>I want to find attributes like release, era, cross-section, tag, status, creation date, modification date, created by, modified by of a processed datasets?</em>
<br/>
<b>find procds.release, procds.era, procds.xsection, procds.tag, procds.status, procds.createdate, procds.moddate, procds.createby, procds.modby where procds = Skim-zToTauTau_MuTau-Tier0-A1-Chowder</b>
<br/>
</td>
</tr>
</table>

<!-- end of templateQLHelp.tmpl -->


<br/>
<hr class="dbs"/>
<br/>

<!--
<table width="100%"><tr><td align="left">
<a name="SHORTCUTS">
<span class="sectionhead">SHORTCUTS</span>
</a>
</td><td align="right">
<a href="javascript:HideTag('aSearchHELP')">close &#8855;</a>
</td></tr></table>
<b>FIND dataset WHERE </b> expression is default and can be skipped.
<br/>
If you type single word, e.g. <span class="box_blue">QCD</span> your look-up will be:
<span class="box_blue">find dataset where dataset=QCD</span>.
<br/>
If you type word with asterisk, e.g. <span class="box_blue">QCD*</span> your look-up will be:
<span class="box_blue">find dataset where dataset like QCD*</span>.
<br/>
You can use <span class="box_blue">=</span> instead of <span class="box_blue">like</span>,
e.g. <span class="box_blue">find run where dataset=/Commissioning2008Ecal-A/*</span>
<br/>
<hr class="dbs"/>
<br/>
-->



</td>
</tr>

</table>
</div>

<input type="hidden" id="checkMethod" checked='checked' />

</div> <!-- end of center -->

<script type="text/javascript">
function ChangeMethod() {
   var id=document.getElementById('method');
   var jd=document.getElementById('checkMethod');
   if (jd && jd.checked==true) {
       id.value='dbsapi';
       SetCookie('DBSDD_method','dbsapi');
       HideTag('case');
   } else {
       id.value='dd';
       SetCookie('DBSDD_method','dd');
       ShowTag('case');
   }
}
SetCookie('DBSDD_method','dbsapi');
SetCookie('DBSDD_ainput','find dataset where dataset like *wbehrenh* and dataset.status like VALID*')
function UpdateCaseSens() {
  if(GetCookie('DBSDD_caseSensitive')=='off') {
     CaseSensitiveOff();
  } else {
     CaseSensitiveOn();
  }
}
UpdateCaseSens();
function UpdateMethodUsage() {
   var mid=document.getElementById('checkMethod');
   var url=window.location.href;
   if(url.search("method=dd")>0) {
      //SetCookie('DBSDD_method','dd');
      if(mid) mid.checked=false;
   } else if(url.search("method=dbsapi")>0) {
      //SetCookie('DBSDD_method','dbsapi');
      if(mid) mid.checked=true;
   } else {
       var method=GetCookie('DBSDD_method');
       if (method) {
          if (method=='dd') {
              if(mid) mid.checked=false;
          } else {
              if(mid) mid.checked=true;
          }
       }  else {
  //        SetCookie('DBSDD_method','dd');
          if(mid) mid.checked=false;
       }
   }
   ChangeMethod();
}
UpdateMethodUsage();
function UpdateUserView() {
   var grid=document.getElementById('grid');
   var url=window.location.href;
   if(url.search("grid=1")>0) {
      SetCookie('DBSDD_view','grid');
      grid.value=1;
   } else if(url.search("grid=0")>0) {
      SetCookie('DBSDD_view','list');
      grid.value=0;
   } else {
       var view=GetCookie('DBSDD_view');
       if (view) {
          if (view=='grid') {
              grid.value=1;
          } else {
              grid.value=0;
          }
       }  else {
          SetCookie('DBSDD_view','list');
          grid.value=0;
       }
   }
}
UpdateUserView();
function UpdateUserInput() {
   var input=GetCookie('DBSDD_ainput');
   if (input) {
      var id=document.getElementById('userInput');
      if (id) {
         id.value=input;
      }
   }
}
UpdateUserInput();
function aSearchHelp(theUrl) {
   ShowTag('aSearchHELP');
   var id=document.getElementById('aSearchHELP');
   id.className="float_aSearch_help";
   if(theUrl) {
      window.location.href='#'+theUrl;
//   } else {
//      window.location.href='#HOME';
   }
}
function aSearchKeys() {
   ShowTag('aSearchKeys');
   var id=document.getElementById('aSearchKeys');
   id.className="float_aSearch_help";
}
//SetDefaultPageMessage('aSearch');
function CheckCaseUsage() {
   var id=document.getElementById('method');
   var cd=document.getElementById('case');
   if (id=='dd') {
       ShowTag('case');
   } else {
       HideTag('case');
   }
}
</script>
<p></p>

<!-- end of templateAdvancedSearchForm.tmpl -->
<!-- templateWhere.tmpl -->
<table class="table_box_white" border="0" width="100%" cellspacing="0" cellpadding="0">
<tr valign="top">
<td class="box_darkblue">
DBS discovery :: Adv. search :: Results
</td>
<td align="right" class="box_darkblue">Physicist</td>
</tr>
</table>
<p></p>


<!-- end of templateWhere.tmpl -->
<!-- templateSortBar -->
<div align="center">
<table border="0" width="100%" cellspacing="0" cellpadding="0">
<tr>
<td align="left">
Found 5 results.
Show <a href="aSearchShowAll?case=on&amp;cff=0&amp;caseSensitive=on&amp;userInput=find%20dataset%20where%20dataset%20like%20%2Awbehrenh%2A%20and%20dataset.status%20like%20VALID%2A&amp;grid=0&amp;fromRow=0&amp;xml=0&amp;sortName=&amp;dbsInst=cms_dbs_ph_analysis_02&amp;html=1&amp;limit=-1&amp;sortOrder=desc&amp;userMode=user&amp;method=dbsapi">all</a>
</td>
<td align="center">
View results: 
<span id="gridView" class="">
<a href="javascript:GridView()">grid</a> 
</span>
 |
<span id="listView" class="td_underline_pad">
<a href="javascript:ListView()">list</a>
</span>
 mode
</td>

<td align="right">
<table>
<tr>
<td>
<select id="sel_sortName" onchange="javascript:ReloadASearch('dbsapi');">
<option value="">Sort by</option>
<option value="DATASET">Sort by DATASET</option>
</select>
</td>
<td>
<a href="javascript:SortDesc();ReloadASearch('dbsapi');">
<span id="sortDesc" class="td_underline_pad">desc</span></a>
|
<a href="javascript:SortAsc();ReloadASearch('dbsapi');">
<span id="sortAsc" class="">asc</span></a>
</td>
</tr>
</table>
</td>

</tr>
</table>
</div>


<script type="text/javascript">
function SetSorting() {
   var input=GetCookie('DBSDD_ainput');
   if (input.search(' asc')>0) {
       SetCookie('DBSDD_sortOrder', 'asc');
   } else {
       SetCookie('DBSDD_sortOrder', 'desc');
   }
   //input = input.strip()
   var oby = input.search(' by');
   if (oby>0) {
       var slist = input.substring(oby,input.length).split(" ");
       SetCookie('DBSDD_sortName',slist[2]);
   }
}
SetSorting();
function Update_aSearchForm() {
   var sortName=GetCookie('DBSDD_sortName');
   var sortOrder=GetCookie('DBSDD_sortOrder');
   var id=document.getElementById('sortOrder');
   id.value=sortOrder;
   id=document.getElementById('sortName');
   id.value=sortName;
}
function UpdateSortOrder() {
   var view=GetCookie('DBSDD_view');
   if (view) {
      var l_view=document.getElementById('listView');
      var g_view=document.getElementById('gridView');
      if (view=='grid') {
          g_view.className='td_underline_pad';
          l_view.className='';
      } else {
          l_view.className='td_underline_pad';
          g_view.className='';
      }
   }
   var sort=GetCookie('DBSDD_sortOrder');
   if (sort=='asc') {
       SortAsc();
   } else if (sort=='desc') {
       SortDesc();
   } else {
       SortDesc();
   }
   var sortName=GetCookie('DBSDD_sortName');
   var sel=document.getElementById('sel_sortName');
   var found=null;
   if (sortName) {
       for(i=0;i<sel.length;i++) {
           if(sel[i].value==sortName) {
              sel[i].selected="selected";
              found=1;
           //} else {
           //   sel[i].selected="";
           }
       }
       if(!found) {
          SetCookie('DBSDD_sortName','DATASET');
       }
   } else {
       SetCookie('DBSDD_sortName','DATASET');
   }
   //Update_aSearchForm();
}
UpdateSortOrder();
function ReloadASearch(iface) {
   var dbsInst=$('dbsInst').value;
   var caseSens=$('caseSensitive').value;
   var userMode=$('userMode').value;
   var userInput=$('userInput').value;
   var sortName=$('sel_sortName').value;
   var sortOrder=$('sortOrder').value;
/*
   if (iface=='dbsapi') {
      if (userInput.search('order by')>0) {
         //alert('Your input excepression contains order by, ignore GUI sorting');
         //return;
         userInput=userInput.substr(0,userInput.search('order by'))+' order by '+sortName+' '+sortOrder;
      } else {
         userInput=userInput+' order by '+sortName+' '+sortOrder;
      }
   }
*/
   var view=GetCookie('DBSDD_view');
   var grid=0;
   if(view=='grid') {
     grid=1;
   }
   SetCookie('DBSDD_sortName',sortName);
   SetCookie('DBSDD_sortOrder',sortOrder);
   var url='aSearch?dbsInst='+dbsInst+'&caseSensitive='+caseSens+'&userMode='+userMode+'&userInput='+userInput+'&sortName='+sortName+'&sortOrder='+sortOrder+'&grid='+grid;
   load(url);
}
function GridView() {
   var url=window.location.href;
   var newurl;
   if(url.search("grid=0")>0) {
      newurl=url.replace(/grid=0/g,'grid=1');
   } else if(url.search("grid=1")>0) {
      newurl=url;
   } else {
      newurl=url+"&grid=1";
   } 
   SetCookie('DBSDD_view','grid');
   load(newurl);
}
function ListView() {
   var url=window.location.href;
   var newurl;
   if(url.search("grid=1")>0) {
      newurl=url.replace(/grid=1/g,'grid=0');
   } else if(url.search("grid=0")>0) {
      newurl=url;
   } else {
      newurl=url+"&grid=0";
   } 
   SetCookie('DBSDD_view','list');
   load(newurl);
}
</script>

<!-- end of templateSortBar -->
<!-- templateProcessedDatasetsLite.tmpl -->
<hr class="dbs" />
<table width="100%">
<tr>
<td align="left" width="78%">
<b>/Mu/wbehrenh-Run2010A-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER</b>
</td>
<td>
<div id="___Mu___wbehrenh-Run2010A-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d___USER"></div>
</td>

<td align="right">
</td>

</tr>
</table>


Created 17 Jan 2011 08:54:00 GMT,
contains 404879 events, 259 files, 1 block(s), 21.2GB, located at 
1
site
(<a href="javascript:ShowTag('table____Mu___wbehrenh-Run2010A-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d___USER')">show</a>, 
<a href="javascript:HideTag('table____Mu___wbehrenh-Run2010A-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d___USER')">hide</a>), 
LFNs:
<a href="/dbs_discovery/getLFNsForSite?dbsInst=cms_dbs_ph_analysis_02&amp;site=all&amp;datasetPath=/Mu/wbehrenh-Run2010A-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;what=cff&amp;userMode=user&amp;run=*">cff</a>,
<a href="/dbs_discovery/getLFNsForSite?dbsInst=cms_dbs_ph_analysis_02&amp;site=all&amp;datasetPath=/Mu/wbehrenh-Run2010A-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;what=py&amp;userMode=user&amp;run=*">py</a>,
<a href="/dbs_discovery/getLFNsForSite?dbsInst=cms_dbs_ph_analysis_02&amp;site=all&amp;datasetPath=/Mu/wbehrenh-Run2010A-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;what=txt&amp;userMode=user&amp;run=*">plain</a>
, &#8747;<em>L</em>=<span id="intLumi___Mu___wbehrenh-Run2010A-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d___USER"></span>
<br/>
<a href="/dbs_discovery/aSearch?dbsInst=cms_dbs_ph_analysis_02&amp;userInput=find+release+where+dataset=/Mu/wbehrenh-Run2010A-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;userMode=user&amp;caseSensitive=on">
Release info
</a>
,
<a href="/dbs_discovery/getBlocksInfo?dbsInst=cms_dbs_ph_analysis_02&amp;dataset=/Mu/wbehrenh-Run2010A-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;userMode=user">
Block info
</a>
,
<a href="/dbs_discovery/getRuns?dbsInst=cms_dbs_ph_analysis_02&amp;dataset=/Mu/wbehrenh-Run2010A-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;_idx=0&amp;ajax=0&amp;userMode=user">
Run info
</a>
,
<a href="/dbs_discovery/getAppConfigs?dbsInst=cms_dbs_ph_analysis_02&amp;appPath=*&amp;procPath=/Mu/wbehrenh-Run2010A-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;ajax=0&amp;userMode=user">
Conf. files
</a>
,
<a href="/dbs_discovery/getDatasetProvenance?dbsInst=cms_dbs_ph_analysis_02&amp;dataset=/Mu/wbehrenh-Run2010A-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;ajax=0&amp;userMode=user">
Parents
</a>
,
<a href="/dbs_discovery/getDatasetChildren?dbsInst=cms_dbs_ph_analysis_02&amp;dataset=/Mu/wbehrenh-Run2010A-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;ajax=0&amp;userMode=user">
Children
</a>
,
<a href="/dbs_discovery/getDataDescription?dbsInst=cms_dbs_ph_analysis_02&amp;processedDataset=/Mu/wbehrenh-Run2010A-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;userMode=user">
Description
</a>
,
<a href="https://cmsweb.cern.ch/phedex/prod/Request::Create?type=xfer&amp;dbschoice=known&amp;dbs=https%3A//cmsdbsprod.cern.ch%3A8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet&amp;data=/Mu/wbehrenh-Run2010A-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;priority=1">
PhEDEx
</a>
,
<a href="/dbs_discovery/createAnalysisDS?dbsInst=cms_dbs_ph_analysis_02&amp;dataset=/Mu/wbehrenh-Run2010A-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER">
Create ADS
</a>
,
<a href="/dbs_discovery/getAnalysisDS?dbsInst=cms_dbs_ph_analysis_02&amp;dataset=/Mu/wbehrenh-Run2010A-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;ajax=0&amp;userMode=user">
ADS
</a>
,
<a href="/dbs_discovery/crabCfg?dbsInst=cms_dbs_ph_analysis_02&amp;dataset=/Mu/wbehrenh-Run2010A-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;totEvt=-1&amp;userMode=user">
crab.cfg
</a>
<p>
</p>


<!-- Summary -->
<div id="table____Mu___wbehrenh-Run2010A-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d___USER" name="summaryTables" class="hide">
<table cellspacing="0" cellpadding="0" border="1">
  <tr valign="top" align="center">
     <th>Location</th>
     <th>Events</th>
     <th>Files</th>
     <th>size</th>
     <th>LFNs</th>
  </tr>


  <tr valign="top" class="sortable_yellow">
     <td><div class="dbs_cell_warmred">T2_DE_DESY : dcache-se-cms.desy.de</div></td>
     <td align="right"><div class="dbs_cell">400037</div></td>
     <td align="right"><div class="dbs_cell">258</div></td>
     <td align="right"><div class="dbs_cell">20.9GB</div></td>
     <td align="center">
     <a href="/dbs_discovery/getLFNsForSite?dbsInst=cms_dbs_ph_analysis_02&amp;site=dcache-se-cms.desy.de&amp;datasetPath=/Mu/wbehrenh-Run2010A-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;what=cff&amp;userMode=user&amp;run=*">cff</a>
     <a href="/dbs_discovery/getLFNsForSite?dbsInst=cms_dbs_ph_analysis_02&amp;site=dcache-se-cms.desy.de&amp;datasetPath=/Mu/wbehrenh-Run2010A-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;what=txt&amp;userMode=user&amp;run=*">plain</a>
     </td>
  </tr>
</table>
</div>
<!-- End of Summary table -->


<script type="text/javascript">
ajaxEngine.registerRequest('ajaxGetIntegratedLumi','getIntegratedLumi');
ajaxEngine.registerAjaxElement('intLumi___Mu___wbehrenh-Run2010A-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d___USER');
ajaxGetIntegratedLumi('cms_dbs_ph_analysis_02','/Mu/wbehrenh-Run2010A-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER');
</script>
<!-- end of templateProcessedDatasetsLite.tmpl -->
<!-- templateProcessedDatasetsLite.tmpl -->
<hr class="dbs" />
<table width="100%">
<tr>
<td align="left" width="78%">
<b>/Mu/wbehrenh-Run2010B1-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff/USER</b>
</td>
<td>
<div id="___Mu___wbehrenh-Run2010B1-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff___USER"></div>
</td>

<td align="right">
</td>

</tr>
</table>


Created 30 Nov 2010 21:39:18 GMT,
contains 3120984 events, 105 files, 1 block(s), 184.4GB, located at 
1
site
(<a href="javascript:ShowTag('table____Mu___wbehrenh-Run2010B1-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff___USER')">show</a>, 
<a href="javascript:HideTag('table____Mu___wbehrenh-Run2010B1-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff___USER')">hide</a>), 
LFNs:
<a href="/dbs_discovery/getLFNsForSite?dbsInst=cms_dbs_ph_analysis_02&amp;site=all&amp;datasetPath=/Mu/wbehrenh-Run2010B1-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff/USER&amp;what=cff&amp;userMode=user&amp;run=*">cff</a>,
<a href="/dbs_discovery/getLFNsForSite?dbsInst=cms_dbs_ph_analysis_02&amp;site=all&amp;datasetPath=/Mu/wbehrenh-Run2010B1-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff/USER&amp;what=py&amp;userMode=user&amp;run=*">py</a>,
<a href="/dbs_discovery/getLFNsForSite?dbsInst=cms_dbs_ph_analysis_02&amp;site=all&amp;datasetPath=/Mu/wbehrenh-Run2010B1-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff/USER&amp;what=txt&amp;userMode=user&amp;run=*">plain</a>
, &#8747;<em>L</em>=<span id="intLumi___Mu___wbehrenh-Run2010B1-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff___USER"></span>
<br/>
<a href="/dbs_discovery/aSearch?dbsInst=cms_dbs_ph_analysis_02&amp;userInput=find+release+where+dataset=/Mu/wbehrenh-Run2010B1-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff/USER&amp;userMode=user&amp;caseSensitive=on">
Release info
</a>
,
<a href="/dbs_discovery/getBlocksInfo?dbsInst=cms_dbs_ph_analysis_02&amp;dataset=/Mu/wbehrenh-Run2010B1-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff/USER&amp;userMode=user">
Block info
</a>
,
<a href="/dbs_discovery/getRuns?dbsInst=cms_dbs_ph_analysis_02&amp;dataset=/Mu/wbehrenh-Run2010B1-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff/USER&amp;_idx=0&amp;ajax=0&amp;userMode=user">
Run info
</a>
,
<a href="/dbs_discovery/getAppConfigs?dbsInst=cms_dbs_ph_analysis_02&amp;appPath=*&amp;procPath=/Mu/wbehrenh-Run2010B1-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff/USER&amp;ajax=0&amp;userMode=user">
Conf. files
</a>
,
<a href="/dbs_discovery/getDatasetProvenance?dbsInst=cms_dbs_ph_analysis_02&amp;dataset=/Mu/wbehrenh-Run2010B1-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff/USER&amp;ajax=0&amp;userMode=user">
Parents
</a>
,
<a href="/dbs_discovery/getDatasetChildren?dbsInst=cms_dbs_ph_analysis_02&amp;dataset=/Mu/wbehrenh-Run2010B1-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff/USER&amp;ajax=0&amp;userMode=user">
Children
</a>
,
<a href="/dbs_discovery/getDataDescription?dbsInst=cms_dbs_ph_analysis_02&amp;processedDataset=/Mu/wbehrenh-Run2010B1-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff/USER&amp;userMode=user">
Description
</a>
,
<a href="https://cmsweb.cern.ch/phedex/prod/Request::Create?type=xfer&amp;dbschoice=known&amp;dbs=https%3A//cmsdbsprod.cern.ch%3A8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet&amp;data=/Mu/wbehrenh-Run2010B1-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff/USER&amp;priority=1">
PhEDEx
</a>
,
<a href="/dbs_discovery/createAnalysisDS?dbsInst=cms_dbs_ph_analysis_02&amp;dataset=/Mu/wbehrenh-Run2010B1-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff/USER">
Create ADS
</a>
,
<a href="/dbs_discovery/getAnalysisDS?dbsInst=cms_dbs_ph_analysis_02&amp;dataset=/Mu/wbehrenh-Run2010B1-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff/USER&amp;ajax=0&amp;userMode=user">
ADS
</a>
,
<a href="/dbs_discovery/crabCfg?dbsInst=cms_dbs_ph_analysis_02&amp;dataset=/Mu/wbehrenh-Run2010B1-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff/USER&amp;totEvt=-1&amp;userMode=user">
crab.cfg
</a>
<p>
</p>


<!-- Summary -->
<div id="table____Mu___wbehrenh-Run2010B1-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff___USER" name="summaryTables" class="hide">
<table cellspacing="0" cellpadding="0" border="1">
  <tr valign="top" align="center">
     <th>Location</th>
     <th>Events</th>
     <th>Files</th>
     <th>size</th>
     <th>LFNs</th>
  </tr>


  <tr valign="top" class="sortable_yellow">
     <td><div class="dbs_cell">T2_DE_DESY : dcache-se-cms.desy.de</div></td>
     <td align="right"><div class="dbs_cell">3120984</div></td>
     <td align="right"><div class="dbs_cell">105</div></td>
     <td align="right"><div class="dbs_cell">184.4GB</div></td>
     <td align="center">
     <a href="/dbs_discovery/getLFNsForSite?dbsInst=cms_dbs_ph_analysis_02&amp;site=dcache-se-cms.desy.de&amp;datasetPath=/Mu/wbehrenh-Run2010B1-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff/USER&amp;what=cff&amp;userMode=user&amp;run=*">cff</a>
     <a href="/dbs_discovery/getLFNsForSite?dbsInst=cms_dbs_ph_analysis_02&amp;site=dcache-se-cms.desy.de&amp;datasetPath=/Mu/wbehrenh-Run2010B1-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff/USER&amp;what=txt&amp;userMode=user&amp;run=*">plain</a>
     </td>
  </tr>
</table>
</div>
<!-- End of Summary table -->


<script type="text/javascript">
ajaxEngine.registerRequest('ajaxGetIntegratedLumi','getIntegratedLumi');
ajaxEngine.registerAjaxElement('intLumi___Mu___wbehrenh-Run2010B1-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff___USER');
ajaxGetIntegratedLumi('cms_dbs_ph_analysis_02','/Mu/wbehrenh-Run2010B1-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff/USER');
</script>
<!-- end of templateProcessedDatasetsLite.tmpl -->
<!-- templateProcessedDatasetsLite.tmpl -->
<hr class="dbs" />
<table width="100%">
<tr>
<td align="left" width="78%">
<b>/Mu/wbehrenh-Run2010B1-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER</b>
</td>
<td>
<div id="___Mu___wbehrenh-Run2010B1-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d___USER"></div>
</td>

<td align="right">
</td>

</tr>
</table>


Created 16 Jan 2011 15:53:07 GMT,
contains 3120984 events, 104 files, 1 block(s), 184.8GB, located at 
1
site
(<a href="javascript:ShowTag('table____Mu___wbehrenh-Run2010B1-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d___USER')">show</a>, 
<a href="javascript:HideTag('table____Mu___wbehrenh-Run2010B1-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d___USER')">hide</a>), 
LFNs:
<a href="/dbs_discovery/getLFNsForSite?dbsInst=cms_dbs_ph_analysis_02&amp;site=all&amp;datasetPath=/Mu/wbehrenh-Run2010B1-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;what=cff&amp;userMode=user&amp;run=*">cff</a>,
<a href="/dbs_discovery/getLFNsForSite?dbsInst=cms_dbs_ph_analysis_02&amp;site=all&amp;datasetPath=/Mu/wbehrenh-Run2010B1-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;what=py&amp;userMode=user&amp;run=*">py</a>,
<a href="/dbs_discovery/getLFNsForSite?dbsInst=cms_dbs_ph_analysis_02&amp;site=all&amp;datasetPath=/Mu/wbehrenh-Run2010B1-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;what=txt&amp;userMode=user&amp;run=*">plain</a>
, &#8747;<em>L</em>=<span id="intLumi___Mu___wbehrenh-Run2010B1-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d___USER"></span>
<br/>
<a href="/dbs_discovery/aSearch?dbsInst=cms_dbs_ph_analysis_02&amp;userInput=find+release+where+dataset=/Mu/wbehrenh-Run2010B1-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;userMode=user&amp;caseSensitive=on">
Release info
</a>
,
<a href="/dbs_discovery/getBlocksInfo?dbsInst=cms_dbs_ph_analysis_02&amp;dataset=/Mu/wbehrenh-Run2010B1-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;userMode=user">
Block info
</a>
,
<a href="/dbs_discovery/getRuns?dbsInst=cms_dbs_ph_analysis_02&amp;dataset=/Mu/wbehrenh-Run2010B1-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;_idx=0&amp;ajax=0&amp;userMode=user">
Run info
</a>
,
<a href="/dbs_discovery/getAppConfigs?dbsInst=cms_dbs_ph_analysis_02&amp;appPath=*&amp;procPath=/Mu/wbehrenh-Run2010B1-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;ajax=0&amp;userMode=user">
Conf. files
</a>
,
<a href="/dbs_discovery/getDatasetProvenance?dbsInst=cms_dbs_ph_analysis_02&amp;dataset=/Mu/wbehrenh-Run2010B1-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;ajax=0&amp;userMode=user">
Parents
</a>
,
<a href="/dbs_discovery/getDatasetChildren?dbsInst=cms_dbs_ph_analysis_02&amp;dataset=/Mu/wbehrenh-Run2010B1-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;ajax=0&amp;userMode=user">
Children
</a>
,
<a href="/dbs_discovery/getDataDescription?dbsInst=cms_dbs_ph_analysis_02&amp;processedDataset=/Mu/wbehrenh-Run2010B1-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;userMode=user">
Description
</a>
,
<a href="https://cmsweb.cern.ch/phedex/prod/Request::Create?type=xfer&amp;dbschoice=known&amp;dbs=https%3A//cmsdbsprod.cern.ch%3A8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet&amp;data=/Mu/wbehrenh-Run2010B1-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;priority=1">
PhEDEx
</a>
,
<a href="/dbs_discovery/createAnalysisDS?dbsInst=cms_dbs_ph_analysis_02&amp;dataset=/Mu/wbehrenh-Run2010B1-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER">
Create ADS
</a>
,
<a href="/dbs_discovery/getAnalysisDS?dbsInst=cms_dbs_ph_analysis_02&amp;dataset=/Mu/wbehrenh-Run2010B1-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;ajax=0&amp;userMode=user">
ADS
</a>
,
<a href="/dbs_discovery/crabCfg?dbsInst=cms_dbs_ph_analysis_02&amp;dataset=/Mu/wbehrenh-Run2010B1-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;totEvt=-1&amp;userMode=user">
crab.cfg
</a>
<p>
</p>


<!-- Summary -->
<div id="table____Mu___wbehrenh-Run2010B1-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d___USER" name="summaryTables" class="hide">
<table cellspacing="0" cellpadding="0" border="1">
  <tr valign="top" align="center">
     <th>Location</th>
     <th>Events</th>
     <th>Files</th>
     <th>size</th>
     <th>LFNs</th>
  </tr>


  <tr valign="top" class="sortable_yellow">
     <td><div class="dbs_cell">T2_DE_DESY : dcache-se-cms.desy.de</div></td>
     <td align="right"><div class="dbs_cell">3120984</div></td>
     <td align="right"><div class="dbs_cell">104</div></td>
     <td align="right"><div class="dbs_cell">184.8GB</div></td>
     <td align="center">
     <a href="/dbs_discovery/getLFNsForSite?dbsInst=cms_dbs_ph_analysis_02&amp;site=dcache-se-cms.desy.de&amp;datasetPath=/Mu/wbehrenh-Run2010B1-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;what=cff&amp;userMode=user&amp;run=*">cff</a>
     <a href="/dbs_discovery/getLFNsForSite?dbsInst=cms_dbs_ph_analysis_02&amp;site=dcache-se-cms.desy.de&amp;datasetPath=/Mu/wbehrenh-Run2010B1-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;what=txt&amp;userMode=user&amp;run=*">plain</a>
     </td>
  </tr>
</table>
</div>
<!-- End of Summary table -->


<script type="text/javascript">
ajaxEngine.registerRequest('ajaxGetIntegratedLumi','getIntegratedLumi');
ajaxEngine.registerAjaxElement('intLumi___Mu___wbehrenh-Run2010B1-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d___USER');
ajaxGetIntegratedLumi('cms_dbs_ph_analysis_02','/Mu/wbehrenh-Run2010B1-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER');
</script>
<!-- end of templateProcessedDatasetsLite.tmpl -->
<!-- templateProcessedDatasetsLite.tmpl -->
<hr class="dbs" />
<table width="100%">
<tr>
<td align="left" width="78%">
<b>/Mu/wbehrenh-Run2010B2-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff/USER</b>
</td>
<td>
<div id="___Mu___wbehrenh-Run2010B2-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff___USER"></div>
</td>

<td align="right">
</td>

</tr>
</table>


Created 01 Dec 2010 08:10:51 GMT,
contains 5498448 events, 227 files, 1 block(s), 345.1GB, located at 
1
site
(<a href="javascript:ShowTag('table____Mu___wbehrenh-Run2010B2-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff___USER')">show</a>, 
<a href="javascript:HideTag('table____Mu___wbehrenh-Run2010B2-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff___USER')">hide</a>), 
LFNs:
<a href="/dbs_discovery/getLFNsForSite?dbsInst=cms_dbs_ph_analysis_02&amp;site=all&amp;datasetPath=/Mu/wbehrenh-Run2010B2-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff/USER&amp;what=cff&amp;userMode=user&amp;run=*">cff</a>,
<a href="/dbs_discovery/getLFNsForSite?dbsInst=cms_dbs_ph_analysis_02&amp;site=all&amp;datasetPath=/Mu/wbehrenh-Run2010B2-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff/USER&amp;what=py&amp;userMode=user&amp;run=*">py</a>,
<a href="/dbs_discovery/getLFNsForSite?dbsInst=cms_dbs_ph_analysis_02&amp;site=all&amp;datasetPath=/Mu/wbehrenh-Run2010B2-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff/USER&amp;what=txt&amp;userMode=user&amp;run=*">plain</a>
, &#8747;<em>L</em>=<span id="intLumi___Mu___wbehrenh-Run2010B2-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff___USER"></span>
<br/>
<a href="/dbs_discovery/aSearch?dbsInst=cms_dbs_ph_analysis_02&amp;userInput=find+release+where+dataset=/Mu/wbehrenh-Run2010B2-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff/USER&amp;userMode=user&amp;caseSensitive=on">
Release info
</a>
,
<a href="/dbs_discovery/getBlocksInfo?dbsInst=cms_dbs_ph_analysis_02&amp;dataset=/Mu/wbehrenh-Run2010B2-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff/USER&amp;userMode=user">
Block info
</a>
,
<a href="/dbs_discovery/getRuns?dbsInst=cms_dbs_ph_analysis_02&amp;dataset=/Mu/wbehrenh-Run2010B2-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff/USER&amp;_idx=0&amp;ajax=0&amp;userMode=user">
Run info
</a>
,
<a href="/dbs_discovery/getAppConfigs?dbsInst=cms_dbs_ph_analysis_02&amp;appPath=*&amp;procPath=/Mu/wbehrenh-Run2010B2-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff/USER&amp;ajax=0&amp;userMode=user">
Conf. files
</a>
,
<a href="/dbs_discovery/getDatasetProvenance?dbsInst=cms_dbs_ph_analysis_02&amp;dataset=/Mu/wbehrenh-Run2010B2-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff/USER&amp;ajax=0&amp;userMode=user">
Parents
</a>
,
<a href="/dbs_discovery/getDatasetChildren?dbsInst=cms_dbs_ph_analysis_02&amp;dataset=/Mu/wbehrenh-Run2010B2-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff/USER&amp;ajax=0&amp;userMode=user">
Children
</a>
,
<a href="/dbs_discovery/getDataDescription?dbsInst=cms_dbs_ph_analysis_02&amp;processedDataset=/Mu/wbehrenh-Run2010B2-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff/USER&amp;userMode=user">
Description
</a>
,
<a href="https://cmsweb.cern.ch/phedex/prod/Request::Create?type=xfer&amp;dbschoice=known&amp;dbs=https%3A//cmsdbsprod.cern.ch%3A8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet&amp;data=/Mu/wbehrenh-Run2010B2-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff/USER&amp;priority=1">
PhEDEx
</a>
,
<a href="/dbs_discovery/createAnalysisDS?dbsInst=cms_dbs_ph_analysis_02&amp;dataset=/Mu/wbehrenh-Run2010B2-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff/USER">
Create ADS
</a>
,
<a href="/dbs_discovery/getAnalysisDS?dbsInst=cms_dbs_ph_analysis_02&amp;dataset=/Mu/wbehrenh-Run2010B2-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff/USER&amp;ajax=0&amp;userMode=user">
ADS
</a>
,
<a href="/dbs_discovery/crabCfg?dbsInst=cms_dbs_ph_analysis_02&amp;dataset=/Mu/wbehrenh-Run2010B2-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff/USER&amp;totEvt=-1&amp;userMode=user">
crab.cfg
</a>
<p>
</p>


<!-- Summary -->
<div id="table____Mu___wbehrenh-Run2010B2-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff___USER" name="summaryTables" class="hide">
<table cellspacing="0" cellpadding="0" border="1">
  <tr valign="top" align="center">
     <th>Location</th>
     <th>Events</th>
     <th>Files</th>
     <th>size</th>
     <th>LFNs</th>
  </tr>


  <tr valign="top" class="sortable_yellow">
     <td><div class="dbs_cell">T2_DE_DESY : dcache-se-cms.desy.de</div></td>
     <td align="right"><div class="dbs_cell">5498448</div></td>
     <td align="right"><div class="dbs_cell">227</div></td>
     <td align="right"><div class="dbs_cell">345.1GB</div></td>
     <td align="center">
     <a href="/dbs_discovery/getLFNsForSite?dbsInst=cms_dbs_ph_analysis_02&amp;site=dcache-se-cms.desy.de&amp;datasetPath=/Mu/wbehrenh-Run2010B2-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff/USER&amp;what=cff&amp;userMode=user&amp;run=*">cff</a>
     <a href="/dbs_discovery/getLFNsForSite?dbsInst=cms_dbs_ph_analysis_02&amp;site=dcache-se-cms.desy.de&amp;datasetPath=/Mu/wbehrenh-Run2010B2-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff/USER&amp;what=txt&amp;userMode=user&amp;run=*">plain</a>
     </td>
  </tr>
</table>
</div>
<!-- End of Summary table -->


<script type="text/javascript">
ajaxEngine.registerRequest('ajaxGetIntegratedLumi','getIntegratedLumi');
ajaxEngine.registerAjaxElement('intLumi___Mu___wbehrenh-Run2010B2-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff___USER');
ajaxGetIntegratedLumi('cms_dbs_ph_analysis_02','/Mu/wbehrenh-Run2010B2-Nov4ReReco-PAT-v3-267a23dfb7d045a9a0ecfb5f145848ff/USER');
</script>
<!-- end of templateProcessedDatasetsLite.tmpl -->
<!-- templateProcessedDatasetsLite.tmpl -->
<hr class="dbs" />
<table width="100%">
<tr>
<td align="left" width="78%">
<b>/Mu/wbehrenh-Run2010B2-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER</b>
</td>
<td>
<div id="___Mu___wbehrenh-Run2010B2-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d___USER"></div>
</td>

<td align="right">
</td>

</tr>
</table>


Created 17 Jan 2011 09:01:23 GMT,
contains 5498448 events, 225 files, 1 block(s), 346.0GB, located at 
1
site
(<a href="javascript:ShowTag('table____Mu___wbehrenh-Run2010B2-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d___USER')">show</a>, 
<a href="javascript:HideTag('table____Mu___wbehrenh-Run2010B2-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d___USER')">hide</a>), 
LFNs:
<a href="/dbs_discovery/getLFNsForSite?dbsInst=cms_dbs_ph_analysis_02&amp;site=all&amp;datasetPath=/Mu/wbehrenh-Run2010B2-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;what=cff&amp;userMode=user&amp;run=*">cff</a>,
<a href="/dbs_discovery/getLFNsForSite?dbsInst=cms_dbs_ph_analysis_02&amp;site=all&amp;datasetPath=/Mu/wbehrenh-Run2010B2-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;what=py&amp;userMode=user&amp;run=*">py</a>,
<a href="/dbs_discovery/getLFNsForSite?dbsInst=cms_dbs_ph_analysis_02&amp;site=all&amp;datasetPath=/Mu/wbehrenh-Run2010B2-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;what=txt&amp;userMode=user&amp;run=*">plain</a>
, &#8747;<em>L</em>=<span id="intLumi___Mu___wbehrenh-Run2010B2-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d___USER"></span>
<br/>
<a href="/dbs_discovery/aSearch?dbsInst=cms_dbs_ph_analysis_02&amp;userInput=find+release+where+dataset=/Mu/wbehrenh-Run2010B2-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;userMode=user&amp;caseSensitive=on">
Release info
</a>
,
<a href="/dbs_discovery/getBlocksInfo?dbsInst=cms_dbs_ph_analysis_02&amp;dataset=/Mu/wbehrenh-Run2010B2-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;userMode=user">
Block info
</a>
,
<a href="/dbs_discovery/getRuns?dbsInst=cms_dbs_ph_analysis_02&amp;dataset=/Mu/wbehrenh-Run2010B2-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;_idx=0&amp;ajax=0&amp;userMode=user">
Run info
</a>
,
<a href="/dbs_discovery/getAppConfigs?dbsInst=cms_dbs_ph_analysis_02&amp;appPath=*&amp;procPath=/Mu/wbehrenh-Run2010B2-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;ajax=0&amp;userMode=user">
Conf. files
</a>
,
<a href="/dbs_discovery/getDatasetProvenance?dbsInst=cms_dbs_ph_analysis_02&amp;dataset=/Mu/wbehrenh-Run2010B2-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;ajax=0&amp;userMode=user">
Parents
</a>
,
<a href="/dbs_discovery/getDatasetChildren?dbsInst=cms_dbs_ph_analysis_02&amp;dataset=/Mu/wbehrenh-Run2010B2-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;ajax=0&amp;userMode=user">
Children
</a>
,
<a href="/dbs_discovery/getDataDescription?dbsInst=cms_dbs_ph_analysis_02&amp;processedDataset=/Mu/wbehrenh-Run2010B2-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;userMode=user">
Description
</a>
,
<a href="https://cmsweb.cern.ch/phedex/prod/Request::Create?type=xfer&amp;dbschoice=known&amp;dbs=https%3A//cmsdbsprod.cern.ch%3A8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet&amp;data=/Mu/wbehrenh-Run2010B2-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;priority=1">
PhEDEx
</a>
,
<a href="/dbs_discovery/createAnalysisDS?dbsInst=cms_dbs_ph_analysis_02&amp;dataset=/Mu/wbehrenh-Run2010B2-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER">
Create ADS
</a>
,
<a href="/dbs_discovery/getAnalysisDS?dbsInst=cms_dbs_ph_analysis_02&amp;dataset=/Mu/wbehrenh-Run2010B2-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;ajax=0&amp;userMode=user">
ADS
</a>
,
<a href="/dbs_discovery/crabCfg?dbsInst=cms_dbs_ph_analysis_02&amp;dataset=/Mu/wbehrenh-Run2010B2-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;totEvt=-1&amp;userMode=user">
crab.cfg
</a>
<p>
</p>


<!-- Summary -->
<div id="table____Mu___wbehrenh-Run2010B2-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d___USER" name="summaryTables" class="hide">
<table cellspacing="0" cellpadding="0" border="1">
  <tr valign="top" align="center">
     <th>Location</th>
     <th>Events</th>
     <th>Files</th>
     <th>size</th>
     <th>LFNs</th>
  </tr>


  <tr valign="top" class="sortable_yellow">
     <td><div class="dbs_cell">T2_DE_DESY : dcache-se-cms.desy.de</div></td>
     <td align="right"><div class="dbs_cell">5498448</div></td>
     <td align="right"><div class="dbs_cell">225</div></td>
     <td align="right"><div class="dbs_cell">346.0GB</div></td>
     <td align="center">
     <a href="/dbs_discovery/getLFNsForSite?dbsInst=cms_dbs_ph_analysis_02&amp;site=dcache-se-cms.desy.de&amp;datasetPath=/Mu/wbehrenh-Run2010B2-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;what=cff&amp;userMode=user&amp;run=*">cff</a>
     <a href="/dbs_discovery/getLFNsForSite?dbsInst=cms_dbs_ph_analysis_02&amp;site=dcache-se-cms.desy.de&amp;datasetPath=/Mu/wbehrenh-Run2010B2-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER&amp;what=txt&amp;userMode=user&amp;run=*">plain</a>
     </td>
  </tr>
</table>
</div>
<!-- End of Summary table -->


<script type="text/javascript">
ajaxEngine.registerRequest('ajaxGetIntegratedLumi','getIntegratedLumi');
ajaxEngine.registerAjaxElement('intLumi___Mu___wbehrenh-Run2010B2-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d___USER');
ajaxGetIntegratedLumi('cms_dbs_ph_analysis_02','/Mu/wbehrenh-Run2010B2-Nov4ReReco-PAT-v4-62d3d5a35c304813a2f4074b31f5939d/USER');
</script>
<!-- end of templateProcessedDatasetsLite.tmpl -->
<hr class="dbs" />
<!-- templatePagerStep.tmpl -->
<table width="100%">
<tr><td align="left">
Number of results per page

<select id="pagerStep1" name="pagerStep" onchange="javascript:LoadASearch('cms_dbs_ph_analysis_02','user','0','0','1','find dataset where dataset like *wbehrenh* and dataset.status like VALID*')">

<option selected="selected">10</option>


<option>25</option>


<option>50</option>


<option>100</option>


<option value="0">All</option>

</select>
</td><td align="right">
Result page:<a href="aSearch?dbsInst=cms_dbs_ph_analysis_02&amp;userMode=user&amp;_idx=0&amp;pagerStep=10&amp;sortName=&amp;caseSensitive=on&amp;userInput=find%20dataset%20where%20dataset%20like%20%2Awbehrenh%2A%20and%20dataset.status%20like%20VALID%2A&amp;grid=0&amp;sortOrder=desc&amp;method=dbsapi"> <span class="gray_box">1</span> </a> 
</td></tr></table>
<!-- end of templatePagerStep.tmpl -->
<!-- templateBottom.tmpl -->
</div> <!-- end of div with class="main" -->
</body>
</html>
<!-- end of templateBottom.tmpl -->
