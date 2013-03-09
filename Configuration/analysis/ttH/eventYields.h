#ifndef eventYields_h
#define eventYields_h


#include "samples.h"
#include "dyScaleFactors.h"
#include "../diLeptonic/utils.h"



class EventYields{
    
public:
    
    /// Constructor for producing event yield tables
    EventYields(const Samples& samples, const double luminosity, const DyScaleFactors::DyScaleFactorMap& m_dyScaleFactors);
    
    /// Default destructor
    ~EventYields(){};
    
    
    
private:
    
    /// Produce the yields
    void produceYields();
    
    /// Write the yields to txt files
    void writeYields(const Sample::Channel& channel, const std::vector<Sample>& v_sample, const std::vector<TString>& v_eventHistoName)const;
    
    
    
    /// Samples to be analysed
    Samples samples_;
    
    /// Luminosity
    const double luminosity_;
    
    /// Map containing the Drell-Yan scale factors
    const DyScaleFactors::DyScaleFactorMap m_dyScaleFactors_;
    
    /// File reader for accessing specific histogram from given file
    RootFileReader* fileReader_;
};





#endif //eventYields_h