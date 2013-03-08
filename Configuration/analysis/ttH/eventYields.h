#ifndef eventYields_h
#define eventYields_h


#include "samples.h"
#include "dyScaleFactors.h"
#include "../diLeptonic/utils.h"



class EventYields{
    public:
        EventYields(){};
        EventYields(const Samples& samples, const double luminosity, const DyScaleFactors::DyScaleFactorMap& m_dyScaleFactors);
        ~EventYields(){};
    private:
        void produceYields();
        void writeYields(const Sample::Channel& channel, const std::vector<Sample>& v_sample, std::vector<TString>& v_eventHistoName);
        Samples samples_;
        double luminosity_;
        
        /// Map containing the Drell-Yan scale factors
        DyScaleFactors::DyScaleFactorMap m_dyScaleFactors_;
        
        /// File reader for accessing specific histogram from given file
        RootFileReader* fileReader_;
};





#endif //eventYields_h