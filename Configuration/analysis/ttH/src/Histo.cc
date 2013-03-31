#include <vector>
#include <iostream>
#include <string>

#include <TString.h>

#include "../../diLeptonic/src/HistoListReader.h"
#include "../../diLeptonic/src/CommandLineParameters.h"
#include "sampleHelpers.h"
#include "Samples.h"
#include "DyScaleFactors.h"
#include "EventYields.h"
#include "plotterHelpers.h"
#include "Plotter.h"
#include "higgsUtils.h"





// Set data luminosity in pb-1
constexpr double Luminosity = 12210;





void Histo(const std::vector<std::string> plots, 
           const std::vector<Channel::Channel> v_channel,
           const std::vector<Systematic::Systematic> v_systematic,
           const DrawMode::DrawMode drawMode)
{
    
    // Access all samples
    Samples samples(v_channel, v_systematic);
    
    // Produce Drell-Yan scalings and access map containing scale factors
    // Requires Samples for channels "ee" "emu" "mumu", independent of selected channels for analysis
    const std::vector<Channel::Channel> v_dyScalingChannel {Channel::ee, Channel::emu, Channel::mumu};
    Samples dyScalingSamples(v_dyScalingChannel, v_systematic);
    const DyScaleFactors dyScaleFactors(dyScalingSamples, Luminosity);
    const DyScaleFactors::DyScaleFactorMap m_dyScaleFactors(dyScaleFactors.getScaleFactors());
    
    // Produce event yields
    const EventYields eventYields(samples, Luminosity, m_dyScaleFactors);
    
    // Create Plotter
    Plotter generalPlot(samples, Luminosity, m_dyScaleFactors, drawMode);
    
    // Loop over all histograms in histoList and print them
    HistoListReader histoList("HistoList_control");
    if (histoList.IsZombie()){
        std::cerr<<"Cannot find HistoList_control, ... break\n\n"<<std::endl;
        exit(12);
    }
    std::cout<<"--- Beginning with the plotting\n\n";
    for (auto it = histoList.begin(); it != histoList.end(); ++it) {
        
        // Access plot properties from histoList and check whether histogram name contains name pattern
        const PlotProperties& plotProperties = it->second;
        std::cout << "\nchecking " << plotProperties.name << std::endl;
        bool found = false;
        for (auto plot : plots) {
            if (plot.size() && plot[0] == '+') {
                if (plotProperties.name.CompareTo(&plot[1], TString::kIgnoreCase) == 0) {
                    found = true;
                    break;
                }
            } else if (plotProperties.name.Contains(plot, TString::kIgnoreCase)) {
                found = true;
                break;
            }
        }
        if (!found){
            std::cout<<"... no histograms found, continue with next\n";
            continue;
        }
        
        // Set plot properties
        generalPlot.setOptions(plotProperties.name,plotProperties.specialComment,plotProperties.ytitle,plotProperties.xtitle, 
                               plotProperties.rebin, plotProperties.do_dyscale, plotProperties.logX, plotProperties.logY, 
                               plotProperties.ymin, plotProperties.ymax, plotProperties.xmin, plotProperties.xmax,
                               plotProperties.bins, plotProperties.xbinbounds, plotProperties.bincenters);
        
        // Loop over all systematics and all channels and write histograms
        generalPlot.producePlots();
    }
    std::cout<<"\n=== Finishing with the plotting\n\n";
}



int main(int argc, char** argv) {
    
    // Get and check configuration parameters
    CLParameter<std::string> opt_plots("p", "Name (pattern) of plot; multiple patterns possible; use '+Name' to match name exactly", false, 1, 100);
    CLParameter<std::string> opt_channel("c", "Specify channel(s), valid: emu, ee, mumu, combined. Default: all channels", false, 1, 4,
        Tools::makeStringCheck(Channel::convertChannels(Channel::allowedChannelsAnalysis)));
    CLParameter<std::string> opt_systematic("s", "Systematic variation - default is Nominal, use 'all' for all", false, 1, 100,
        Tools::makeStringCheck(Systematic::convertSystematics(Systematic::allowedSystematicsPlotting)));
    CLParameter<std::string> opt_drawMode("m", "Specify draw mode of Higgs sample, valid: stacked, overlaid, scaledoverlaid. Default: scaledoverlaid", false, 1, 1,
        Tools::makeStringCheck(DrawMode::convertDrawModes(DrawMode::allowedDrawModes)));
    CLAnalyser::interpretGlobal(argc, argv);
    
    // Set up plots
    std::vector<std::string> plots {""};
    if (opt_plots.isSet()){
        plots = opt_plots.getArguments();
        std::cout<< "Processing only histograms containing in name: ";
        for(auto plot : plots)std::cout<< plot << " ";
        std::cout << "\n\n";
    }
    
    // Set up channels
    std::vector<Channel::Channel> v_channel(Channel::allowedChannelsPlotting);
    if(opt_channel.isSet()) v_channel = Channel::convertChannels(opt_channel.getArguments());
    std::cout << "Processing channels: ";
    for (auto channel : v_channel)std::cout << Channel::convertChannel(channel) << " ";
    std::cout << "\n\n";
    
    // Set up systematics
    std::vector<Systematic::Systematic> v_systematic(Systematic::allowedSystematicsPlotting);
    if(opt_systematic.isSet() && opt_systematic[0]!="all") v_systematic = Systematic::convertSystematics(opt_systematic.getArguments());
    else if(opt_systematic.isSet() && opt_systematic[0]=="all"); // do nothing
    else {v_systematic.clear(); v_systematic.push_back(Systematic::nominal);}
    std::cout << "Processing systematics (use >>-s all<< to process all known systematics): "; 
    for (auto systematic : v_systematic) std::cout << Systematic::convertSystematic(systematic) << " ";
    std::cout << "\n\n";
    
    // Set up draw mode (default is scaledOverlaid)
    DrawMode::DrawMode drawMode(DrawMode::undefined);
    if(opt_drawMode.isSet()) drawMode = DrawMode::convertDrawMode(opt_drawMode[0]);
    else drawMode = DrawMode::scaledoverlaid;
    std::cout << "\n";
    std::cout << "Draw mode of Higgs sample: "<<DrawMode::convertDrawMode(drawMode);
    std::cout << "\n\n";
    
    // Start analysis
    Histo(plots, v_channel, v_systematic, drawMode);
}



