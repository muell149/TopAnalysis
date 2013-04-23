#include <fstream>
#include <sstream>

#include <TH1D.h>
#include <TString.h>

#include "EventYields.h"
#include "../../diLeptonic/src/RootFileReader.h"
#include "higgsUtils.h"
#include "Samples.h"
#include "DyScaleFactors.h"





/// Folder for event yields output
constexpr const char* BaseDIR = "EventYields";





EventYields::EventYields(const Samples& samples, const double& luminosity, const DyScaleFactors& dyScaleFactors):
luminosity_(luminosity),
dyScaleFactors_(dyScaleFactors),
fileReader_(RootFileReader::getInstance())
{
    this->produceYields(samples);
}



void EventYields::produceYields(const Samples& samples)const
{
    std::cout<<"--- Beginning event yield table processing\n\n";
    
    // Find all histograms containing information for cutflow table (in systematic Nominal and channel emu, first histogram)
    const std::vector<TString>& v_eventHistoName = fileReader_->findHistos(samples.getSamples(Channel::emu, Systematic::nominal).at(0).inputFile(), "events_step", false);
    std::vector<std::pair<TString, TString> > v_nameStepPair;
    std::stringstream ss_step;
    for(std::vector<TString>::const_iterator i_eventHistoName = v_eventHistoName.begin(); i_eventHistoName != v_eventHistoName.end(); ++i_eventHistoName){
        const TString& step = Tools::extractSelectionStepAndCategoryBin(*i_eventHistoName);
        v_nameStepPair.push_back(std::make_pair(*i_eventHistoName, step));
        ss_step<<step<<", ";
    }
    std::cout<<"Found selection steps:\n"<<ss_step.str()<<std::endl;
    
    // Loop over systematics (exclude all but Nominal - so outer loop could be removed) and channels
    for(auto systematicChannelSamples : samples.getSystematicChannelSamples()){
        const Systematic::Systematic& systematic(systematicChannelSamples.first);
        if(systematic != Systematic::nominal)continue;
        for(auto channelSample : systematicChannelSamples.second){
            const Channel::Channel& channel(channelSample.first);
            this->writeYields(channel, channelSample.second, v_nameStepPair);
        }
    }
    std::cout<<"\n=== Finishing event yield table processing\n\n";
}



void EventYields::writeYields(const Channel::Channel& channel, const std::vector<Sample>& v_sample,
                              const std::vector<std::pair<TString, TString> >& v_nameStepPair)const
{
    // Loop over all selection steps writing out event yields
    for(std::vector<std::pair<TString, TString> >::const_iterator i_nameStepPair = v_nameStepPair.begin(); i_nameStepPair != v_nameStepPair.end(); ++i_nameStepPair){
        
        // Assign histogram to sample
        std::vector<SampleHistPair> v_numhist;
        for(const auto& sample : v_sample){
            TH1D* temp_hist = fileReader_->GetClone<TH1D>(sample.inputFile(), i_nameStepPair->first);
            double lumiWeight = Tools::luminosityWeight(sample, luminosity_, fileReader_);
            Tools::applyFlatWeight(temp_hist, lumiWeight);
            v_numhist.push_back(SampleHistPair(sample, temp_hist));
        }
        
        // Apply Drell-Yan scaling
        for(auto sampleHistPair : v_numhist){
            const bool isDyll(sampleHistPair.first.sampleType() == Sample::dyee || sampleHistPair.first.sampleType() == Sample::dymumu);
            // FIXME: why not scaling the DYee and DYmumu for each channel ?
            if(isDyll && channel!=Channel::emu){
                // FIXME: which DY scale factor is here applied, isn't it always the same instead of the step dependent one ?
                sampleHistPair.second->Scale(1.);
                //numhist.first->Scale(dyScaleFactors_(channel));
            }
        }
        
        // Prepare output folder and text file
        // At present, event yields are only possible for nominal systematic
        std::ofstream eventFile;
        TString eventFileString = Tools::assignFolder(BaseDIR, channel, Systematic::nominal);
        eventFileString.Append("events_" + i_nameStepPair->second + ".txt");
        eventFile.open(eventFileString.Data());
        
        // Make output for tables
        double tmp_num = 0;
        double bg_num = 0;
        for(auto i_numhist = v_numhist.begin(); i_numhist != v_numhist.end(); ++i_numhist){
            auto iterator = i_numhist;
            ++iterator;
            tmp_num += i_numhist->second->Integral();
            if(i_numhist == --(v_numhist.end())){
                eventFile<<i_numhist->first.legendEntry()<<": "<<tmp_num<<std::endl;
                bg_num += tmp_num;
                tmp_num = 0;
            }
            else if(i_numhist->first.legendEntry() != iterator->first.legendEntry()){
                eventFile<<i_numhist->first.legendEntry()<<": "<<tmp_num<<std::endl;
                if(i_numhist->first.sampleType() != Sample::SampleType::data){
                    bg_num+=tmp_num;
                }
                tmp_num = 0;
            }
        }
        eventFile<<"Total background: "<<bg_num<<std::endl;
        
        // Close text file
        eventFile.close();
        //std::cout<<"\nEvent yields saved in "<<eventFilestring<<"\n"<<std::endl;
     }
}















