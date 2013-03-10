#ifndef sampleHelpers_h
#define sampleHelpers_h

#include <string>
#include <vector>

#include <TString.h>






namespace Systematic{
    
    /// Systematics for analysis
    enum Systematic{nominal, undefined};
    
    
    
    /// All systematics allowed for analysis
    const std::vector<Systematic> allowedSystematics
        {nominal};
    
    
    
    /// Convert a systematic from string to typedef
    Systematic convertSystematic(const std::string& systematic);
    
    /// Convert a systematic from typedef to string
    std::string convertSystematic(const Systematic& systematic);
    
    /// Convert a vector of systematics from string to typedef
    std::vector<Systematic> convertSystematics(const std::vector<std::string>& systematics);
    
    /// Convert a vector of systematics from string to typedef
    std::vector<std::string> convertSystematics(const std::vector<Systematic>& systematics);
}






namespace Channel{
    
    /// Dileptonic decay channels for analysis
    enum Channel{ee, emu, mumu, combined, undefined};
    
    
    
    /// All dileptonic decay channels allowed for analysis
    const std::vector<Channel> allowedChannels
        {ee, emu, mumu, combined};
    
    
    
    /// Convert a channel from string to typedef
    Channel convertChannel(const std::string& channel);
    
    /// Convert a channel from typedef to string
    std::string convertChannel(const Channel& channel);
    
    /// Return the label of a channel as used for drawing
    std::string channelLabel(const Channel& channel);
    
    /// Convert a vector of channels from string to typedef
    std::vector<Channel> convertChannels(const std::vector<std::string>& channels);
    
    /// Convert a vector of channels from string to typedef
    std::vector<std::string> convertChannels(const std::vector<Channel>& channels);
    
    
}








namespace Tools{
    
    /// Assign an output folder depending on the channel
    TString assignFolder(const Channel::Channel& channel);
    
}






#endif // sampleHelpers_h






