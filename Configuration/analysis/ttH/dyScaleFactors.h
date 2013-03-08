#ifndef dyScaleFactors_h
#define dyScaleFactors_h

#include <vector>
#include <map>

#include "TString.h"

#include "../diLeptonic/utils.h"
#include "samples.h"

class DyScaleFactors{

public:
    
    /// Typedef for the map containing the Drell-Yan scale factors
    typedef std::map<TString, std::map<Sample::Systematic, std::map<Sample::Channel, double> > > DyScaleFactorMap;
    
    /// Default constructor
    DyScaleFactors():fileReader_(RootFileReader::getInstance()){}
    /// Default destructor
    ~DyScaleFactors(){}
    
    /// Produce and get the map containing the Drell-Yan scale factors
    DyScaleFactorMap getScaleFactors(Samples& samples, const double luminosity);
    
private:
    
    /// Produce the Drell-Yan scale factors
    void produceScaleFactors(const TString& step, const Sample::Systematic& systematic, std::map<Sample::Channel, std::vector<Sample> >& channelSamples, const double luminosity);
    
    /// Print full information about all ingoing numbers (deactivated by default)
    void printFullInformation(const double dyScaleFactor_ee, const double dyScaleFactor_mumu, 
                              const double k_ee, const double k_mumu,
                              const double rOutIn_ee, const double rOutIn_mumu,
                              const double nIn_ee_data_loose, const double nIn_mumu_data_loose,
                              const double nIn_ee_data, const double nIn_mumu_data, const double nIn_emu_data,
                              const double nIn_ee_mc, const double nIn_mumu_mc,
                              const double nIn_ee_dy, const double nIn_mumu_dy,
                              const double nOut_ee_mc, const double nOut_mumu_mc,
                              const double nOut_ee_dy, const double nOut_mumu_dy,
                              const TString& step);
    
    /// Map containing the Drell-Yan scale factors
    DyScaleFactorMap m_dyScaleFactors_;
    
    /// File reader for accessing specific histogram from given file
    RootFileReader* fileReader_;
};














#endif //dyScaleFactors_h