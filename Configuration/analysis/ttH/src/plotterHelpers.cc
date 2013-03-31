#include <iostream>
#include <cstdlib>

#include "plotterHelpers.h"






DrawMode::DrawMode DrawMode::convertDrawMode(const std::string& drawMode)
{
    if(drawMode == "stacked") return stacked;
    if(drawMode == "overlaid") return overlaid;
    if(drawMode == "scaledoverlaid") return scaledoverlaid;
    if(drawMode == "scaledoverlaidfixed") return scaledoverlaidfixed;
    std::cout<<"Warning! The following draw mode conversion is not implemented: "<<drawMode<<std::endl;
    return undefined;
}



std::string DrawMode::convertDrawMode(const DrawMode& drawMode)
{
    if(drawMode == stacked) return "stacked";
    if(drawMode == overlaid) return "overlaid";
    if(drawMode == scaledoverlaid) return "scaledoverlaid";
    if(drawMode == scaledoverlaidfixed) return "scaledoverlaidfixed";
    if(drawMode == undefined) return "";
    std::cout<<"Error! Draw mode conversion is not implemented, break...\n"<<std::endl;
    exit(97);
}



std::vector<DrawMode::DrawMode> DrawMode::convertDrawModes(const std::vector<std::string>& drawModes)
{
    std::vector<DrawMode> v_drawMode;
    for(auto drawMode : drawModes)v_drawMode.push_back(convertDrawMode(drawMode));
    return v_drawMode;
}



std::vector<std::string> DrawMode::convertDrawModes(const std::vector<DrawMode>& drawModes)
{
    std::vector<std::string> v_drawMode;
    for(auto drawMode : drawModes)v_drawMode.push_back(convertDrawMode(drawMode));
    return v_drawMode;
}









