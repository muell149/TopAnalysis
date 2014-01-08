#ifndef EventYields_h
#define EventYields_h

#include <utility>
#include <vector>

class TString;

#include "../../common/include/sampleHelpers.h"

class RootFileReader;
class Sample;
class Samples;
class DyScaleFactors;





class EventYields{
    
public:
    
    /// Constructor for producing event yield tables
    EventYields(const Samples& samples, const double& luminosity, const DyScaleFactors& m_dyScaleFactors);
    
    /// Default destructor
    ~EventYields(){};
    
    
    
private:
    
    /// Produce the yields
    void produceYields(const Samples& samples)const;
    
    /// Write the yields to txt files, either without or with additional corrections (e.g. Drell-Yan scaling)
    void writeYields(const Channel::Channel& channel, const std::vector<Sample>& v_sample,
                     const std::vector<std::pair<TString, TString> >& v_nameStepPair,
                     const bool useCorrections =false)const;
    
    
    
    /// Luminosity
    const double& luminosity_;
    
    /// Map containing the Drell-Yan scale factors
    const DyScaleFactors& dyScaleFactors_;
    
    /// File reader for accessing specific histogram from given file
    RootFileReader* fileReader_;
};





#endif // EventYields_h





