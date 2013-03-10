#include <TCanvas.h>
#include <TLegend.h>
#include <THStack.h>
#include <TFile.h>
#include <TString.h>
#include <TH1.h>

#include <vector>
#include <iostream>
#include <set>
#include <functional>

#include "../diLeptonic/HistoListReader.h"
#include "../diLeptonic/CommandLineParameters.hh"

#include "samples.h"
#include "eventYields.h"
#include "dyScaleFactors.h"
#include "plotterclass.h"


void Histo(Plotter::DrawMode drawMode,
           std::vector<std::string> plots, 
           std::vector<Sample::Channel> v_channel,
           std::vector<Sample::Systematic> v_systematic)
{
    // Set data luminosity
    const double luminosity = 12210;
    
    // Access all samples
    Samples samples(v_channel, v_systematic);
    
    // Produce Drell-Yan scalings and access map containing scale factors
    // Requires Samples for channels "ee" "emu" "mumu", independent of selected channels for analysis
    std::vector<Sample::Channel> v_dyScalingChannel {Sample::ee, Sample::emu, Sample::mumu};
    Samples dyScalingSamples(v_dyScalingChannel, v_systematic);
    DyScaleFactors dyScaleFactors(dyScalingSamples, luminosity);
    DyScaleFactors::DyScaleFactorMap m_dyScaleFactors;
    m_dyScaleFactors = dyScaleFactors.getScaleFactors();
    
    // Produce event yields
    EventYields eventYields(samples, luminosity, m_dyScaleFactors);
    
    // Create Plotter 
    Plotter generalPlot(samples, luminosity, m_dyScaleFactors, drawMode);
    
    // Loop over all histograms in histoList and print them
    HistoListReader histoList("HistoList_control");
    if (histoList.IsZombie()) exit(12);
    std::cout<<"--- Beginning with the plotting\n\n";
    for (auto it = histoList.begin(); it != histoList.end(); ++it) {
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


/**
 * Helper function to create a function which checks if a string found is in the
 * passed vector of string.
 * 
 * @param allowed a vector of allowed strings (char*s)
 * @return a function taking a std::string and returning a bool
 */
std::function<bool(const std::string &s)> makeStringChecker(const std::vector<const char *> allowed) {
    return [allowed](const std::string &test) {
        return std::find(begin(allowed), end(allowed), test) != end(allowed);
    };
}


int main(int argc, char** argv) {
    
    // Set vector of possible Higgs draw mode arguments
    std::vector<std::string> drawModes{"stacked", "overlaid", "scaledoverlaid"};
    // Set vector of possible channel arguments
    std::vector<std::string> channels{"ee", "emu", "mumu", "combined"};
    // Set vector of possible systematic arguments
    std::vector<std::string> systematics{"Nominal"};
    
    // Prepare all StringCheckers
    std::vector<const char*> allowedDrawModes;
    for(auto drawMode : drawModes) allowedDrawModes.push_back(drawMode.data());
    std::vector<const char*> allowedChannels;
    for(auto channel : channels) allowedChannels.push_back(channel.data());
    std::vector<const char*> allowedSystematics;
    for(auto systematic : systematics) allowedSystematics.push_back(systematic.data());
    
    // Get and check configuration parameters
    CLParameter<std::string> opt_drawMode("m", "Specify draw mode of Higgs sample, valid: stacked, overlaid, scaledoverlaid. Default: scaledoverlaid", false, 1, 1,
        makeStringChecker(allowedDrawModes));
    CLParameter<std::string> opt_plots("p", "Name (pattern) of plot; multiple patterns possible; use '+Name' to match name exactly", false, 1, 100);
    CLParameter<std::string> opt_channel("c", "Specify channel(s), valid: emu, ee, mumu, combined. Default: all channels", false, 1, 4,
        makeStringChecker(allowedChannels));
    CLParameter<std::string> opt_systematic("s", "Systematic variation - default is Nominal, use 'all' for all", false, 1, 100,
        makeStringChecker(allowedSystematics));
    CLAnalyser::interpretGlobal(argc, argv);
    
    // Set up draw mode (required)
    Plotter::DrawMode drawMode(Plotter::undefined);
    if(opt_drawMode.isSet()) drawMode = Tools::convertDrawMode(opt_drawMode[0]);
    
    // Set up channels
    if(opt_channel.isSet()) channels = opt_channel.getArguments();
    std::vector<Sample::Channel> v_channel;
    for (auto channel: channels) {
        v_channel.push_back(Tools::convertChannel(channel));
    }
    std::cout << "\n";
    std::cout << "Processing channels: "; 
    for (auto channel : v_channel)std::cout << Tools::convertChannel(channel) << " ";
    std::cout << "\n\n";
    
	// Set up systematics
    if(opt_systematic.isSet()) systematics = opt_systematic.getArguments();
    std::vector<Sample::Systematic> v_systematic;
    for(auto systematic : systematics){
        v_systematic.push_back(Tools::convertSystematic(systematic));
    }
    std::cout << "Processing systematics (use >>-s all<< to process all known systematics): "; 
    for (auto systematic : v_systematic) std::cout << Tools::convertSystematic(systematic) << " ";
    std::cout << "\n\n";
    
    // Set up plots
    std::vector<std::string> plots {""};
    if (opt_plots.isSet()) plots = opt_plots.getArguments();
    
    // Start analysis
    Histo(drawMode, plots, v_channel, v_systematic);
}



