#ifndef Samples_h
#define Samples_h

#include <vector>
#include <map>
#include "TString.h"
#include "TH1D.h"


class Sample{
    public:
        enum Systematic{nominal, undefinedSystematic};
        
        enum Channel{ee, emu, mumu, combined, undefinedChannel};
        
        enum SampleType{data, dyll, higgssignal, dummy};
        
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


typedef std::map<Sample::Systematic, std::map<Sample::Channel, std::vector<Sample> > > SystematicChannelSamples;


class Samples{
    public:
        Samples(){};
        ~Samples(){};
        const SystematicChannelSamples& getSystematicChannelSamples();
        std::vector<Sample> getSamples(const Sample::Channel& channel, const Sample::Systematic& systematic);
        void addSamples(const Sample::Channel& channel, const Sample::Systematic& systematic);
    private:
        SystematicChannelSamples m_systematicChannelSample_;
};


namespace Tools{
    // FIXME: net yet implemented, only dummy so far
    void orderByLegend(std::vector<std::pair<TString, Sample> >& v_sample);
    
    Sample::Channel convertChannel(const std::string&);
    std::string convertChannel(const Sample::Channel&);
    std::string channelLabel(const Sample::Channel&);
    
    Sample::Systematic convertSystematic(const std::string&);
    std::string convertSystematic(const Sample::Systematic&);
}


typedef std::pair<Sample, TH1D*> SampleHistPair;


#endif // Samples_h




