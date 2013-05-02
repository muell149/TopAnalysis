#ifndef ttbar_utils_h
#define ttbar_utils_h

#include <string>
#include <functional>
#include <vector>





namespace ttbar{

    /// return CMSSW_BASE environment variable as string, with error checking
    const std::string CMSSW_BASE();

    /// Return the path where relevant input data (e.g. histograms for scale factors) is stored
    const std::string DATA_PATH();
    
    
    
    /**
     * Helper function to create a function which checks if a string found is in the
     * passed vector of string.
     * 
     * @param v_string a vector of allowed strings (std::string)
     * @return a function taking a std::string and returning a bool
     */
    #ifndef __CINT__
    std::function<bool(const std::string& s)> makeStringCheck(const std::vector<std::string> v_string);
    #endif
    
}







#endif




