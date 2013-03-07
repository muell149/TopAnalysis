#include <TCanvas.h>
#include <TLegend.h>
#include <THStack.h>
#include <TFile.h>
#include <TString.h>
#include <TH1.h>

#include <vector>
#include <iostream>
#include <set>

#include "plotterclass.h"
#include "../diLeptonic/HistoListReader.h"
#include "../diLeptonic/CommandLineParameters.hh"

#include "samples.h"
#include "eventYields.h"


void Histo(Plotter::DrawMode drawMode,
           std::vector<std::string> plots, 
           std::vector<Sample::Channel> v_channel,
           std::vector<Sample::Systematic> v_systematic)
{
    // Set data luminosity
    const double lumi = 12210;
    
    // Access all samples
    Samples samples;
    for (auto systematic : v_systematic) {
        for (auto channel : v_channel) {
            samples.addSamples(channel, systematic);
        }
    }
    
    // Produce Drell-Yan scalings
    // FIXME: need to use these in eventYields and Plotter
    
    // Produce event yields
    EventYields eventYields(samples, lumi);
    
    // Loop over all histograms in histoList
    HistoListReader histoList("HistoList_control");
    if (histoList.IsZombie()) exit(12);
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
        
        
        // Create Plotter 
        Plotter h_generalPlot;
        h_generalPlot.setLumi(lumi);
        
        h_generalPlot.setOptions(plotProperties.name,plotProperties.specialComment,plotProperties.ytitle,plotProperties.xtitle, 
                                 plotProperties.rebin, plotProperties.do_dyscale, plotProperties.logX, plotProperties.logY, 
                                 plotProperties.ymin, plotProperties.ymax, plotProperties.xmin, plotProperties.xmax,
                                 plotProperties.bins, plotProperties.xbinbounds, plotProperties.bincenters);
        h_generalPlot.DYScaleFactor(plotProperties.specialComment);
        
        
        // Loop over all systematics and all channels and write histograms
        const SystematicChannelSamples& m_systematicChannelSample(samples.getSystematicChannelSamples());
        for(auto systematicChannelSamples : m_systematicChannelSample){
            const Sample::Systematic& systematic(systematicChannelSamples.first);
            for(auto channelSample : systematicChannelSamples.second){
                const Sample::Channel& channel(channelSample.first);
                h_generalPlot.write(channel, systematic, drawMode, channelSample.second);
            }
        }
    }
    std::cout << "Done with the plotting\n";
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
    // Get and check configuration parameters
    CLParameter<std::string> opt_drawMode("m", "Specify draw mode of Higgs sample, valid: stacked, overlaid, scaledoverlaid. Default: scaledoverlaid", false, 1, 1,
        makeStringChecker({"stacked", "overlaid", "scaledoverlaid"}));
    CLParameter<std::string> opt_plots("p", "Name (pattern) of plot; multiple patterns possible; use '+Name' to match name exactly", false, 1, 100);
    CLParameter<std::string> opt_channel("c", "Specify channel(s), valid: emu, ee, mumu, combined. Default: all channels", false, 1, 4,
        makeStringChecker({"ee", "emu", "mumu", "combined"}));
    CLParameter<std::string> opt_systematic("s", "Systematic variation - default is Nominal, use 'all' for all", false, 1, 100,
        makeStringChecker({"Nominal"}));
    CLAnalyser::interpretGlobal(argc, argv);
    
    // Set up draw mode
    Plotter::DrawMode drawMode(Plotter::undefined);
    if(opt_drawMode.isSet()){
        if (opt_drawMode[0] == "stacked") drawMode = Plotter::stacked;
        else if (opt_drawMode[0] == "overlaid") drawMode = Plotter::overlaid;
        else if (opt_drawMode[0] == "scaledoverlaid") drawMode = Plotter::scaledoverlaid;
        else drawMode = Plotter::undefined;
    }
    else drawMode = Plotter::scaledoverlaid;
    
    // Set up channels
    std::vector<Sample::Channel> v_channel {Sample::emu, Sample::ee, Sample::mumu, Sample::combined};
    std::vector<std::string> channels = opt_channel.getArguments();
    if(opt_channel.isSet()){
        v_channel.clear();
        for (auto channel: channels) {
            v_channel.push_back(Tools::convertChannel(channel));
        }
    }
    std::cout << "Processing channels: "; 
    for (auto channel: v_channel)std::cout << Tools::convertChannel(channel) << " ";
    std::cout << "\n";
    
	// Set up systematics (use only nominal samples for now)
    std::vector<Sample::Systematic> v_systematic { Sample::Systematic::nominal };
    std::vector<std::string> systematics = opt_systematic.getArguments();
    if(opt_systematic.isSet()){
        v_systematic.clear();
        for(auto systematic : systematics){
            v_systematic.push_back(Tools::convertSystematic(systematic));
        }
    }
    std::cout << "Processing systematics (use >>-s all<< to process all known systematics): "; 
    for (auto systematic: v_systematic) std::cout << Tools::convertSystematic(systematic) << " "; std::cout << "\n";
    
    // Set up plots
    std::vector<std::string> plots { "" };
    if (opt_plots.isSet()) plots = opt_plots.getArguments();

    Histo(drawMode, plots, v_channel, v_systematic);
}
