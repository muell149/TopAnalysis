#ifndef higgsUtils_h
#define higgsUtils_h

#include "samples.h"
#include "../diLeptonic/utils.h"

#include "TH1.h"




namespace Tools{
    void applyFlatWeight(TH1* hist, const double weight);
    double luminosityWeight(const Sample& sample, const double luminosity, RootFileReader* fileReader);
}


















#endif //higgsUtils_h