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
        
        Sample();
        Sample(TString legendEntry, int color, double crossSection, SampleType sampleType=dummy);
        ~Sample(){};
        
        TString legendEntry()const;
        int color()const;
        double crossSection()const;
        SampleType sampleType()const;
        
        void setInputFile(const TString& inputFileName);
        TString inputFile()const;
        
    private:
        TString legendEntry_;
        int color_;
        double crossSection_;
        SampleType sampleType_;
        
        TString inputFileName_;
};


namespace Tools{
    Sample::Channel convertChannel(const std::string&);
    std::string convertChannel(const Sample::Channel&);
    // FIXME: net yet implemented, only dummy so far
    void orderByLegend(std::vector<std::pair<TString, Sample> >& v_sample);
}


class Samples{
    public:
        Samples(){};
        ~Samples(){};
        const std::map<TString, std::map<Sample::Channel, std::vector<Sample> > >& getSystematicChannelSamples();
        std::vector<Sample> getSamples(const Sample::Channel& channel, const TString& systematic);
        void addSamples(const Sample::Channel& channel, const TString& systematic);
    private:
        std::map<TString, std::map<Sample::Channel, std::vector<Sample> > > m_systematicChannelSample_;
};



#endif // Samples_h



