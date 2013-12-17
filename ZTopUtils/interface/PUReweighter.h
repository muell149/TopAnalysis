#ifndef reweightPU_h
#define reweightPU_h

#include "TH1D.h"
#include <vector>
#include "TString.h"

/*
 WHATEVER you add , please don't use exit() in case an error occurs.
 replace it with either:
 - throw an exception (throw std::logic_error("sometext") or std::runtime_error("");)
 - return something (-1 or another int for dubugging)

 */

namespace ztop {

class PUReweighter {

public:
    void setDataTruePUInput(TH1* dataPUdist);
    void setDataTruePUInput(const char * rootfile);
    void setMCTruePUInput(TH1* MCPUdist);
    void setMCTruePUInput(const char * rootfile);
    double getPUweight(size_t trueBX);
    void setMCDistrSum12(TString scenario = "S10");
    void setMCDistrFall11(TString scenario = "S06");
    void clear();

private:
    std::vector<double> datapu_;
    std::vector<double> mcpu_;
    double dataint_;
    double mcint_;
};

}

#endif
