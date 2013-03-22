#include "plotterHelpers.h"






DrawMode::DrawMode
DrawMode::convertDrawMode(const std::string& drawMode){
    if (drawMode == "stacked") return stacked;
    else if (drawMode == "overlaid") return overlaid;
    else if (drawMode == "scaledoverlaid") return scaledoverlaid;
    else return undefined;
}


std::string
DrawMode::convertDrawMode(const DrawMode& drawMode){
    if (drawMode == stacked) return "stacked";
    else if (drawMode == overlaid) return "overlaid";
    else if (drawMode == scaledoverlaid) return "scaledoverlaid";
    else return "";
}


std::vector<DrawMode::DrawMode>
DrawMode::convertDrawModes(const std::vector<std::string>& drawModes){
    std::vector<DrawMode> v_drawMode;
    for(auto drawMode : drawModes)v_drawMode.push_back(convertDrawMode(drawMode));
    return v_drawMode;
}


std::vector<std::string>
DrawMode::convertDrawModes(const std::vector<DrawMode>& drawModes){
    std::vector<std::string> v_drawMode;
    for(auto drawMode : drawModes)v_drawMode.push_back(convertDrawMode(drawMode));
    return v_drawMode;
}









