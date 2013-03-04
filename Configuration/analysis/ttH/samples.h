#ifndef Samples_h
#define Samples_h

#include <vector>
#include <map>
#include "TString.h"


class Sample{
    public:
        enum SampleType{data, dyll, higgssignal, dummy};
        
        enum Channel{ee, emu, mumu, combined, undefined};
        //Channel convertChannel(const std::string&)const;
        //std::string convertChannel(const Channel&)const;
        
        Sample(){};
        Sample(TString legendEntry, int color, double crossSection, SampleType sampleType=dummy);
        ~Sample(){};
        
        void setInputFile(const TString& inputFile);
        TString inputFile()const;
        
    private:
        TString legendEntry_;
        int color_;
        double crossSection_;
        SampleType sampleType_;
        
        TString inputFile_;
        
        Channel channel_;
        TString systematic_;
        
};


namespace Tools{
    Sample::Channel convertChannel(const std::string&);
    std::string convertChannel(const Sample::Channel&);
    void orderByLegend(std::vector<std::pair<TString, Sample> >& v_sample);
}


class Samples{
    public:
        Samples():m_systematicChannelSample_(0){};
        ~Samples(){};
        std::vector<Sample> getSamples(Sample::Channel channel, TString systematic);
        void addSamples(Sample::Channel channel, TString systematic);
    private:
        std::map<TString, std::map<Sample::Channel, std::vector<Sample> > >* m_systematicChannelSample_;
};



#endif // Samples_h



