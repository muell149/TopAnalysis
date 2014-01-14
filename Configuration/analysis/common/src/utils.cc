#include <iostream>
#include <cstdlib>
#include <algorithm>

#include "utils.h"





const std::string common::CMSSW_BASE()
{
    const char* cmssw_base = std::getenv("CMSSW_BASE");
    if (!cmssw_base) {
        std::cerr << "Error! Environmental variable CMSSW_BASE not set!\n"
                  << "Please run cmsenv first.\n"
                  << "When running without CMSSW, you still need this variable so that the\n"
                  << "certain files can be found.\n";
        exit(1);            
    }
    std::string result(cmssw_base);
    return result;
}



const std::string common::DATA_PATH_COMMON()
{
    std::string result(CMSSW_BASE());
    result.append("/src/TopAnalysis/Configuration/analysis/common/data");
    return result;
}



std::function<bool(const std::string& s)> common::makeStringCheck(const std::vector<std::string> v_string)
{
    return [v_string](const std::string& test){
        return std::find(begin(v_string), end(v_string), test) != end(v_string);
    };
}




