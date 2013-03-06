#include "samples.h"

#include <iostream>
#include <fstream>
#include "TString.h"




Sample::Sample():
legendEntry_(""), color_(0), crossSection_(0), sampleType_(dummy), inputFileName_("")
{}


Sample::Sample(TString legendEntry, int color, double crossSection, SampleType sampleType):
legendEntry_(legendEntry), color_(color), crossSection_(crossSection),
sampleType_(sampleType), inputFileName_("")
{}


void
Samples::addSamples(const Sample::Channel& channel, const Sample::Systematic& systematic){
    
    // Define all samples as they are needed
    Sample data("Data", kBlack, 1., Sample::SampleType::data);
    Sample ttbarsignal("t#bar{t} Signal", kRed+1, 253.849);
    Sample ttbarbkg("t#bar{t} Other", kRed-7, 253.849);
    Sample singletop("Single Top", kMagenta, 11.1);
    Sample ww("Diboson", 10, 54.838);
    Sample wz("Diboson", 10, 33.21);
    Sample zz("Diboson", 10, 17.654);
    Sample dytautau1050("Z / #gamma* #rightarrow #tau#tau", kAzure+8, 860.5);
    Sample dytautau50inf("Z / #gamma* #rightarrow #tau#tau", kAzure+8, 3532.8);
    Sample dyll1050("Z / #gamma* #rightarrow ee/#mu#mu", kAzure-2, 860.5, Sample::SampleType::dyll);
    Sample dyll50inf("Z / #gamma* #rightarrow ee/#mu#mu", kAzure-2, 3532.8, Sample::SampleType::dyll);
    Sample wlnu("W+Jets", kGreen-3, 36257.2);
    Sample qcdmu15("QCD Multijet", kYellow, 3.640E8*3.7E-4);
    Sample qcdmu2030("QCD Multijet", kYellow, 2.870E8*6.500E-3);
    Sample qcdmu3050("QCD Multijet", kYellow, 6.609E7*12.20E-3);
    Sample qcdmu5080("QCD Multijet", kYellow, 8.802E6*21.80E-3);
    Sample qcdmu80120("QCD Multijet", kYellow, 1.024E6*39.50E-3);
    Sample qcdmu120170("QCD Multijet", kYellow, 1.578E5*47.30E-3);
    Sample qcdem2030("QCD Multijet", kYellow, 2.886E8*10.10E-3);
    Sample qcdem3080("QCD Multijet", kYellow, 7.433E7*62.10E-3);
    Sample qcdem80170("QCD Multijet", kYellow, 1.191E6*153.9E-3);
    Sample qcdbcem2030("QCD Multijet", kYellow, 2.886E8*5.800E-4);
    Sample qcdbcem3080("QCD Multijet", kYellow, 7.424E7*2.250E-3);
    Sample qcdbcem80170("QCD Multijet", kYellow, 1.191E6*10.90E-3);
    //Sample ttbarHincl("t#bar{t}H (incl.)", kSpring, 0.1302, Sample::SampleType::higgssignal);
    Sample ttbarHincl("t#bar{t}H (incl.)", kSpring, 0.1302);
    Sample ttbarHtobbbar("t#bar{t}H (b#bar{b})", kOrange-7, 0.1302*0.577, Sample::SampleType::higgssignal);
    
    
    // Access FileList containing list of input root files
    const TString histoListName("FileLists/HistoFileList_" + Tools::convertSystematic(systematic) + "_" + Tools::convertChannel(channel) + ".txt");
    std::cout << "Reading file: " << histoListName << std::endl;
    ifstream fileList(histoListName);
    if (fileList.fail()) {
        std::cerr << "Error reading file: " << histoListName << std::endl;
        exit(1);
    }
    
    
    // Fill vector with samples defined above
    std::vector<std::pair<TString, Sample> > v_sample;
    while(!fileList.eof()){
        TString filename;
        fileList>>filename;
        if(filename==""){continue;} // Skip empty lines
        if(filename.BeginsWith("#")){continue;} // Comment lines in FileList with '#'
        if(filename.Contains("run"))
            v_sample.push_back(std::pair<TString, Sample>(filename, data));
        else if(filename.Contains("ttbarsignal"))
            v_sample.push_back(std::pair<TString, Sample>(filename, ttbarsignal));
        else if(filename.Contains("ttbarbg"))
            v_sample.push_back(std::pair<TString, Sample>(filename, ttbarbkg));
        else if(filename.Contains("single"))
            v_sample.push_back(std::pair<TString, Sample>(filename, singletop));
        else if(filename.Contains("ww"))
            v_sample.push_back(std::pair<TString, Sample>(filename, ww));
        else if(filename.Contains("wz"))
            v_sample.push_back(std::pair<TString, Sample>(filename, wz));
        else if(filename.Contains("zz"))
            v_sample.push_back(std::pair<TString, Sample>(filename, zz));
        else if(filename.Contains("dytautau") && filename.Contains("1050"))
            v_sample.push_back(std::pair<TString, Sample>(filename, dytautau1050));
        else if(filename.Contains("dytautau") && filename.Contains("50inf"))
            v_sample.push_back(std::pair<TString, Sample>(filename, dytautau50inf));
        else if((filename.Contains("dymumu") || filename.Contains("dyee")) && filename.Contains("1050"))
            v_sample.push_back(std::pair<TString, Sample>(filename, dyll1050));
        else if((filename.Contains("dymumu") || filename.Contains("dyee")) && filename.Contains("50inf"))
            v_sample.push_back(std::pair<TString, Sample>(filename, dyll50inf));
        else if(filename.Contains("wtolnu"))
            v_sample.push_back(std::pair<TString, Sample>(filename, wlnu));
        
        else if(filename.Contains("qcdmu15"))
            v_sample.push_back(std::pair<TString, Sample>(filename, qcdmu15));
        else if(filename.Contains("qcdmu2030"))
            v_sample.push_back(std::pair<TString, Sample>(filename, qcdmu2030));
        else if(filename.Contains("qcdmu3050"))
            v_sample.push_back(std::pair<TString, Sample>(filename, qcdmu3050));
        else if(filename.Contains("qcdmu5080"))
            v_sample.push_back(std::pair<TString, Sample>(filename, qcdmu5080));
        else if(filename.Contains("qcdmu80120"))
            v_sample.push_back(std::pair<TString, Sample>(filename, qcdmu80120));
        else if(filename.Contains("qcdmu120170"))
            v_sample.push_back(std::pair<TString, Sample>(filename, qcdmu120170));
        else if(filename.Contains("qcdem2030"))
            v_sample.push_back(std::pair<TString, Sample>(filename, qcdem2030));
        else if(filename.Contains("qcdem3080"))
            v_sample.push_back(std::pair<TString, Sample>(filename, qcdem3080));
        else if(filename.Contains("qcdem80170"))
            v_sample.push_back(std::pair<TString, Sample>(filename, qcdem80170));
        else if(filename.Contains("qcdbcem2030"))
            v_sample.push_back(std::pair<TString, Sample>(filename, qcdbcem2030));
        else if(filename.Contains("qcdbcem3080"))
            v_sample.push_back(std::pair<TString, Sample>(filename, qcdbcem3080));
        else if(filename.Contains("qcdbcem80170"))
            v_sample.push_back(std::pair<TString, Sample>(filename, qcdbcem80170));
        
        else if(filename.Contains("ttbarH125inclusive"))
            v_sample.push_back(std::pair<TString, Sample>(filename, ttbarHincl));
        else if(filename.Contains("ttbarH125tobbbar"))
            v_sample.push_back(std::pair<TString, Sample>(filename, ttbarHtobbbar));
        else{
            std::cout<<"Sample of FileList ("<<filename<<") is not defined in default samples, skip it...\n";
            continue;
        }
    }
    
    // Order files by legendEntry
    Tools::orderByLegend(v_sample);
    
    // Create map of maps, containing Sample per channel per systematic
    for(auto sample : v_sample){
        sample.second.setInputFile(sample.first);
        m_systematicChannelSample_[systematic][channel].push_back(sample.second);
        //std::cout<<"\n\t\tInput file: "<<(--(m_systematicChannelSample[systematic][channel].end()))->inputFile()<<"\n";
    }
    //for(auto systematicChannelSample : m_systematicChannelSample_){
    //    for(auto channelSample : systematicChannelSample.second){
    //        for(auto sample : channelSample.second){
    //            std::cout<<"We have samples: "<<Tools::convertSystematic(systematic)<<" , "<<Tools::convertChannel(channel)
    //                <<" , "<<sample.inputFile()<<"\n";
    //        }
    //    }
    //}
}


TString
Sample::legendEntry()const{return legendEntry_;}


int
Sample::color()const{return color_;}


double
Sample::crossSection()const{return crossSection_;}


Sample::SampleType
Sample::sampleType()const{return sampleType_;}


void 
Sample::setInputFile(const TString& inputFileName){
    inputFileName_ = inputFileName;
}


TString
Sample::inputFile()const{
    return inputFileName_;
}


const std::map<Sample::Systematic, std::map<Sample::Channel, std::vector<Sample> > >&
Samples::getSystematicChannelSamples(){
    return m_systematicChannelSample_;
}


std::vector<Sample>
Samples::getSamples(const Sample::Channel& channel, const Sample::Systematic& systematic){
    return m_systematicChannelSample_[systematic][channel];
}





void
Tools::orderByLegend(std::vector<std::pair<TString, Sample> >& v_sample){
    // FIXME: place here automated ordering by legendEntry
}


Sample::Channel 
Tools::convertChannel(const std::string& channel){
    if(channel == "ee")return Sample::Channel::ee;
    else if(channel == "emu")return Sample::Channel::emu;
    else if(channel == "mumu")return Sample::Channel::mumu;
    else if(channel == "combined")return Sample::Channel::combined;
    else return Sample::Channel::undefinedChannel;
}


std::string
Tools::convertChannel(const Sample::Channel& channel){
    if(channel == Sample::Channel::ee)return "ee";
    else if(channel == Sample::Channel::emu)return "emu";
    else if(channel == Sample::Channel::mumu)return "mumu";
    else if(channel == Sample::Channel::combined)return "combined";
    else return "";
}


std::string
Tools::channelLabel(const Sample::Channel& channel){
    if(channel == Sample::Channel::ee)return "ee";
    else if(channel == Sample::Channel::emu)return "e#mu";
    else if(channel == Sample::Channel::mumu)return "#mu#mu";
    else if(channel == Sample::Channel::combined)return "Dilepton Combined";
    else return "";
}


Sample::Systematic
Tools::convertSystematic(const std::string& systematic){
    if(systematic == "Nominal")return Sample::Systematic::nominal;
    else{
        std::cout<<"Warning! The following systematic is not implemented: "<<systematic<<std::endl;
        return Sample::Systematic::undefinedSystematic;
    }
}


std::string
Tools::convertSystematic(const Sample::Systematic& systematic){
    if(systematic == Sample::Systematic::nominal)return "Nominal";
    else if(systematic == Sample::Systematic::undefinedSystematic)return "";
    else{
        std::cout<<"Error! Systematic is not implemented, break...\n";
        exit(99);
    }
}









