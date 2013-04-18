#ifndef eventYields_h
#define eventYields_h

#include <utility>
#include <vector>

class TString;

#include "sampleHelpers.h"
#include "DyScaleFactors.h"

class RootFileReader;
class Sample;
class Samples;



class EventYields{
    
public:
    
    /// Constructor for producing event yield tables
    EventYields(Samples& samples, const double luminosity, const DyScaleFactors::DyScaleFactorMap& m_dyScaleFactors);
    
    /// Default destructor
    ~EventYields(){};
    
    
    
private:
    
    /// Produce the yields
    void produceYields(Samples& samples);
    
    /// Write the yields to txt files
    void writeYields(const Channel::Channel& channel, const std::vector<Sample>& v_sample,
                     const std::vector<std::pair<TString, TString> >& v_nameStepPair)const;
    
    
    
    /// Luminosity
    const double luminosity_;
    
    /// Map containing the Drell-Yan scale factors
    const DyScaleFactors::DyScaleFactorMap m_dyScaleFactors_;
    
    /// File reader for accessing specific histogram from given file
    RootFileReader* fileReader_;
};





#endif //eventYields_h