#include "TopAnalysis/TopFilter/plugins/RunEventFilter.h"

RunEventFilter::RunEventFilter(const ParameterSet& cfg)
{
  runStr_  = cfg.getParameter<string>       ("runs");
  if(cfg.exists("excludedRuns")){
    excludedRuns_  = cfg.getParameter<string>("excludedRuns");    
  }
  if(cfg.exists("selectedEvents")){
    psets_   = cfg.getParameter<vector<ParameterSet> >("selectedEvents");
  } 
}

RunEventFilter::~RunEventFilter()
{
}

void
RunEventFilter::beginJob(const EventSetup&)
{  
  /// parse runlist to vector of ints
  vector<unsigned int> selected_runs = ParseRunString(runStr_);
  vector<unsigned int> excluded_runs = ParseRunString(excludedRuns_);
     
  /// remove excluded runs from runlist  
  if(excludedRuns_!=""){         
    for(size_t i=0; i<selected_runs.size(); ++i){    
      for(size_t j=0; j<excluded_runs.size(); ++j){ 
        if(selected_runs[i]==excluded_runs[j]){  
          selected_runs.erase(selected_runs.begin()+i);
        }      
      }
    }
  }  
  
  /// create runlist from selected runs vector
  for(size_t i=0;i<selected_runs.size();++i){
    runStruct run;
    run.run = selected_runs[i];
    run.reject = false; //set default value 
    cout << "push_back run # " << run.run << endl;
    runlist.push_back(run);    
  }

  // add list of selected or excluded evts to each run
  if(psets_.size()>0){
    for(size_t i=0;i<psets_.size();++i){
      unsigned int runnumber = psets_[i].getParameter<unsigned int>("run_number"); 
      for(size_t j=0;j<runlist.size();++j){
        if(runlist[j].run==runnumber){
          string event_str = psets_[i].getParameter<string>("selected_evts");           
	  if(event_str[0]=='!'){
	    runlist[j].reject=true;
	    event_str=event_str.substr(1);
	  }		
          pair<vector<unsigned int>, vector<pair<unsigned int, unsigned int> > > events = ParseEventString(event_str);  
	  runlist[j].evts       = events.first;
	  runlist[j].evt_ranges = events.second;
        }
      }
    }
  } 
  
  // cout will be removed later
  cout << "RUNLIST:" << endl;
  cout << "selected runs and events: " << endl; 
  for(size_t i=0;i<runlist.size();++i){
    cout << "RUN: " << runlist[i].run << endl;
    cout << "  evts:" << endl;
    for(size_t j=0;j<runlist[i].evts.size();++j){
      cout << "  " << runlist[i].evts[j] << endl;
    }
    cout << "  ranges:" << endl;
    for(size_t j=0;j<runlist[i].evt_ranges.size();++j){
      cout << "  from " << runlist[i].evt_ranges[j].first << " to " << runlist[i].evt_ranges[j].second << endl;
    }    
  }            
}

bool
RunEventFilter::filter(Event& evt, const EventSetup&)
{  
  EventNumber_t event_number = evt.id().event();
  RunNumber_t   run_number   = evt.id().run();
  
  bool run_in_list  = false;
  bool evt_in_list  = false;
  bool reject       = false;
  
  for(size_t i=0;i<runlist.size();++i) {
    if(runlist[i].run==run_number){
      run_in_list = true;
      reject = runlist[i].reject;
      // check if the event is in the event list for the run
      for(size_t j=0;j<runlist[i].evts.size();++j){
        if(runlist[i].evts[j]==event_number){
	  evt_in_list = true;
	}
      }
      // check if the event is in one of the event ranges of this run
      for(size_t j=0;j<runlist[i].evt_ranges.size();++j){
        if(runlist[i].evt_ranges[j].first<=event_number && runlist[i].evt_ranges[j].second>=event_number){
	  evt_in_list = true;
	}
      }      
      break;
    } 
  }  
  
  if(!run_in_list || (evt_in_list && reject) || (!evt_in_list && !reject)) return false;  
  return true;
}

void
RunEventFilter::endJob()
{
}

/// transforms the runlist string into a vector which contains the run numbers as integers
vector<unsigned int>
RunEventFilter::ParseRunString(string instring)
{
  vector<unsigned int> returnlist;

  if(!isValid(instring))
    LogError("RunEventFilter") << "String: " << instring << " contains errors." << endl;  
    
  int          sep1 = -1;
  unsigned int sep2 =  0;
    
  // parse string
  while(sep2 < instring.size()){      
    sep2 = instring.find_first_of(",",sep2+1);  
    if(sep2==string::npos){
      sep2 = instring.size();
    }       
    string substring = instring.substr(sep1+1,sep2-sep1-1);
    // if substring does not contain a '-' it schoud be a number
    if(substring.find_first_of('-')==string::npos){ 
      unsigned int runNumber = atoi(substring.c_str());     
      returnlist.push_back(runNumber);
    }
    else{
      // if substring contains a '-' it schoud consist of two numbers
      int sep3 = substring.find_first_of("-");
      unsigned int start = atoi(substring.substr(0,sep3).c_str());
      unsigned int stop  = atoi(substring.substr(sep3+1).c_str());
      for(unsigned int i = start; i<=stop; ++i){   
        returnlist.push_back(i);	
      }
    }            
    sep1 = sep2;    
  }
  return returnlist;  
}

/// transforms the events string into a pair of vectors
/// the first vector contains single events
/// the second vector contains event ranges as pair: first event, last event
pair<vector<unsigned int>, vector<pair<unsigned int, unsigned int> > >
RunEventFilter::ParseEventString(string instring)
{
  pair<vector<unsigned int>, vector<pair<unsigned int, unsigned int> > > returnlists;

  if(!isValid(instring))
    LogError("RunEventFilter") << "String: " << instring << " contains errors." << endl;  
    
  int          sep1 = -1;
  unsigned int sep2 =  0;
    
  // parse string
  while(sep2 < instring.size()){      
    sep2 = instring.find_first_of(",",sep2+1);  
    if(sep2==string::npos){
      sep2 = instring.size();
    }       
    string substring = instring.substr(sep1+1,sep2-sep1-1);
    // if substring does not contain a '-' it schoud be a number
    if(substring.find_first_of('-')==string::npos){ 
      unsigned int runNumber = atoi(substring.c_str());     
      returnlists.first.push_back(runNumber);
    }
    else{
      // if substring contains a '-' it schoud consist of two numbers
      int sep3 = substring.find_first_of("-");
      unsigned int start = atoi(substring.substr(0,sep3).c_str());
      unsigned int stop  = atoi(substring.substr(sep3+1).c_str());      
      returnlists.second.push_back(make_pair(start,stop));
    }            
    sep1 = sep2;    
  }
  return returnlists;  
}

/// is wrong if the string contains a symble which is not element of {1234567890-,}
bool
RunEventFilter::isValid(const string& str)
{
  string validSigns = "1234567890,-";
  if(str.find_first_not_of(validSigns)!=string::npos){
    LogError("RunEventFilter") << "Invalid sign in run string: " 
      << str[str.find_first_not_of(validSigns)] << endl; 
    return false;       
  }
  
  if(str[0]==',' || str[0]=='-'){
    LogError("RunEventFilter") << "Run string can not start with " 
      << str[0] << endl;
    return false;        
  }
  
  if(str[str.size()-1]==',' || str[str.size()-1]=='-'){
    LogError("RunEventFilter") << "Run string can not end with " 
      << str[str.size()] << endl; 
    return false;  
  } 
  return true;
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( RunEventFilter );
