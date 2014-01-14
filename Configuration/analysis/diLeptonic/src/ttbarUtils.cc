#include <iostream>
#include <cstdlib>
#include <algorithm>

#include "ttbarUtils.h"
#include "../../common/include/utils.h"




const std::string ttbar::DATA_PATH_DILEPTONIC()
{
    std::string result(common::CMSSW_BASE());
    result.append("/src/TopAnalysis/Configuration/analysis/diLeptonic/data");
    return result;
}




