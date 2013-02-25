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





void Histo(std::vector<std::string> plots, 
           std::vector<std::string> systematics, 
           std::vector<std::string> channels) 
{
    

    const double lumi = 12210;

    HistoListReader histoList("HistoList_control");
    if (histoList.IsZombie()) exit(12);
    for (auto it = histoList.begin(); it != histoList.end(); ++it) {
        const PlotProperties& p = it->second;
        std::cout << "checking " << p.name << std::endl;
        bool found = false;
        for (auto plot : plots) {
            if (plot.size() && plot[0] == '+') {
                if (p.name.CompareTo(&plot[1], TString::kIgnoreCase) == 0) {
                    found = true;
                    break;
                }
            } else if (p.name.Contains(plot, TString::kIgnoreCase)) {
                found = true;
                break;
            }
        }
        if (!found) continue;

        // Create Plotter 
        Plotter h_generalPlot;
        h_generalPlot.setLumi(lumi);
        
        h_generalPlot.setOptions(p.name,p.specialComment,p.ytitle,p.xtitle, 
                                    p.rebin, p.do_dyscale, p.logX, p.logY, 
                                    p.ymin, p.ymax, p.xmin, p.xmax, p.bins, p.xbinbounds, p.bincenters);
        h_generalPlot.DYScaleFactor(p.specialComment);
        
	// here preunfolding is just the default printing step
        for (auto channel : channels) {
            for (auto systematic : systematics) {
                h_generalPlot.preunfolding(channel, systematic);
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
    CLParameter<std::string> opt_plots("p", "Name (pattern) of plot; multiple patterns possible; use '+Name' to match name exactly", false, 1, 100);
    CLParameter<std::string> opt_channel("c", "Specify channel(s), valid: emu, ee, mumu, combined. Default: all channels", false, 1, 4,
        makeStringChecker({"ee", "emu", "mumu", "combined"}));
    CLParameter<std::string> opt_sys("s", "Systematic variation - default is Nominal, use 'all' for all", false, 1, 100,
        makeStringChecker({"Nominal"}));
    CLAnalyser::interpretGlobal(argc, argv);
    
    std::vector<std::string> channels { "emu", "ee", "mumu", "combined" };
    if (opt_channel.isSet()) channels = opt_channel.getArguments();
    std::cout << "Processing channels: "; 
    for (auto ch: channels) std::cout << ch << " "; std::cout << "\n";
        
	// Use only nominal for now
    std::vector<std::string> systematics { "Nominal" };
    std::cout << "Processing systematics (use >>-s all<< to process all knwon systematics): "; 
    for (auto sys: systematics) std::cout << sys << " "; std::cout << "\n";
    
    std::vector<std::string> plots { "" };
    if (opt_plots.isSet()) plots = opt_plots.getArguments();

    Histo(plots, systematics, channels);
}
