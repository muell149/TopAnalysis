#ifndef eventYields_h
#define eventYields_h


#include "samples.h"
#include "../diLeptonic/utils.h"



class EventYields{
    public:
        EventYields(){};
        EventYields(const Samples& samples, const double luminosity);
        ~EventYields(){};
    private:
        void produceYields();
        void writeYields(const Sample::Channel& channel, const std::vector<Sample>& v_sample, std::vector<TString>& v_eventHistoName);
        Samples samples_;
        double luminosity_;
        
        RootFileReader* fileReader_;
};





#endif //eventYields_h