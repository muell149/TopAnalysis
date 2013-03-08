
#include "dyScaleFactors.h"

#include <sstream>

#include "TString.h"

#include "higgsUtils.h"

DyScaleFactors::DyScaleFactorMap
DyScaleFactors::getScaleFactors(Samples& samples, const double luminosity){
    std::cout<<"Beginning production of Drell-Yan scale factors\n";
    
    // Get histograms for Drell-Yan scaling from first file in map
    std::vector<TString> v_eventHistoName;
    const SystematicChannelSamples& m_systematicChannelSamples = samples.getSystematicChannelSamples();
    const TString& filename = m_systematicChannelSamples.begin()->second.begin()->second.begin()->inputFile();
    v_eventHistoName = fileReader_->findHistos(filename, "Allh1_step");
    
    // Extract selection steps
    std::vector<TString> v_step;
    std::stringstream ss_step;
    for(std::vector<TString>::const_iterator i_eventHistoName = v_eventHistoName.begin(); i_eventHistoName != v_eventHistoName.end(); ++i_eventHistoName){
        const TString& step = Tools::extractSelectionStep(*i_eventHistoName);
        v_step.push_back(step);
        ss_step<<step<<", ";
    }
    std::cout<<"Found selection steps: "<<ss_step.str()<<std::endl;
    
    // Loop over selection steps and systematics
    for(TString step : v_step){
        for(auto systematicChannelSamples : m_systematicChannelSamples){
            const Sample::Systematic& systematic(systematicChannelSamples.first);
            this->produceScaleFactors(step, systematic, systematicChannelSamples.second);
        }
    }
    
    
    std::cout<<"Finishing production of Drell-Yan scale factors\n";
    return m_dyScaleFactors_;
}



void
DyScaleFactors::dummyScaleFactors(const std::vector<TString>& v_step, Samples& samples){
    for(auto systematicChannelSamples : samples.getSystematicChannelSamples()){
        const Sample::Systematic& systematic(systematicChannelSamples.first);
        for(auto channelSample : systematicChannelSamples.second){
            const Sample::Channel& channel(channelSample.first);
            for(auto step : v_step){
                m_dyScaleFactors_[step][systematic][channel] = 1.;
            }
        }
    }
}



void
DyScaleFactors::produceScaleFactors(const TString& step, const Sample::Systematic& systematic, const std::map<Sample::Channel, std::vector<Sample> >& channelSamples){
    
}









