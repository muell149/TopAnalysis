#include <iostream>
#include <cstdlib>

#include <TString.h>

#include "sampleHelpers.h"






// --- Functions defined in namespace Systematic ---


Systematic::Systematic
Systematic::convertSystematic(const std::string& systematic){
    if(systematic == "Nominal")return nominal;
    else{
        std::cout<<"Warning! The following systematic is not implemented: "<<systematic<<std::endl;
        return undefined;
    }
}


std::string
Systematic::convertSystematic(const Systematic& systematic){
    if(systematic == nominal)return "Nominal";
    else if(systematic == undefined)return "";
    else{
        std::cout<<"Error! Systematic is not implemented, break...\n";
        exit(99);
    }
}


std::vector<Systematic::Systematic>
Systematic::convertSystematics(const std::vector<std::string>& systematics){
    std::vector<Systematic> v_systematic;
    for(auto systematic : systematics)v_systematic.push_back(convertSystematic(systematic));
    return v_systematic;
}


std::vector<std::string>
Systematic::convertSystematics(const std::vector<Systematic>& systematics){
    std::vector<std::string> v_systematic;
    for(auto systematic : systematics)v_systematic.push_back(convertSystematic(systematic));
    return v_systematic;
}








// --- Functions defined in namespace Channel ---


Channel::Channel 
Channel::convertChannel(const std::string& channel){
    if(channel == "ee")return ee;
    else if(channel == "emu")return emu;
    else if(channel == "mumu")return mumu;
    else if(channel == "combined")return combined;
    else return undefined;
}


std::string
Channel::convertChannel(const Channel& channel){
    if(channel == ee)return "ee";
    else if(channel == emu)return "emu";
    else if(channel == mumu)return "mumu";
    else if(channel == combined)return "combined";
    else return "";
}


std::string
Channel::channelLabel(const Channel& channel){
    if(channel == ee)return "ee";
    else if(channel == emu)return "e#mu";
    else if(channel == mumu)return "#mu#mu";
    else if(channel == combined)return "Dilepton Combined";
    else return "";
}


std::vector<Channel::Channel>
Channel::convertChannels(const std::vector<std::string>& channels){
    std::vector<Channel> v_channel;
    for(auto channel : channels)v_channel.push_back(convertChannel(channel));
    return v_channel;
}


std::vector<std::string>
Channel::convertChannels(const std::vector<Channel>& channels){
    std::vector<std::string> v_channel;
    for(auto channel : channels)v_channel.push_back(convertChannel(channel));
    return v_channel;
}









// --- Functions defined in namespace Tools ---


TString
Tools::assignFolder(const Channel::Channel& channel){
    const TString outpathPlots = "./Plots";
    TString subfolderChannel = Channel::convertChannel(channel);
    subfolderChannel.Prepend("/");
    return outpathPlots + subfolderChannel;
}


TString
Tools::assignFolder(const Channel::Channel& channel, const Systematic::Systematic& systematic){
    const TString path = assignFolder(channel);
    TString subfolderSystematic = Systematic::convertSystematic(systematic);
    subfolderSystematic.Prepend("/");
    return path + subfolderSystematic;
}














