#ifndef dyScaleFactors_h
#define dyScaleFactors_h
#include <map>

#include "../diLeptonic/utils.h"
#include "samples.h"

class DyScaleFactors{
public:
    typedef std::map<TString, std::map<Sample::Systematic, std::map<Sample::Channel, double> > > DyScaleFactorMap;
    
    DyScaleFactors():fileReader_(RootFileReader::getInstance()){}
    ~DyScaleFactors(){}
    
    DyScaleFactorMap getScaleFactors(Samples& samples, const double luminosity);
private:
    
    void dummyScaleFactors(const std::vector<TString>& v_step, Samples& samples);
    void produceScaleFactors(const TString& step, const Sample::Systematic& systematic, const std::map<Sample::Channel, std::vector<Sample> >& channelSamples);
    
    
    DyScaleFactorMap m_dyScaleFactors_;
    
    
    RootFileReader* fileReader_;
};














#endif //dyScaleFactors_h