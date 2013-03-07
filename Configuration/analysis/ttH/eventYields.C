#include "eventYields.h"
#include "higgsUtils.h"

#include <fstream>
#include "TSystem.h"



EventYields::EventYields(const Samples& samples, const double luminosity):
samples_(samples), luminosity_(luminosity), fileReader_(RootFileReader::getInstance())
{
    this->produceYields();
}


void EventYields::produceYields(){
    std::cout<<"Beginning event yield table processing\n";
    
    // Find all histograms containing information for cutflow table (in systematic Nominal and channel emu, first histogram)
    std::vector<TString> v_eventHistoName;
    v_eventHistoName = fileReader_->findHistos(samples_.getSamples(Sample::emu, Sample::nominal)[0].inputFile(), "step");
    
    // Loop over systematics (exclude all but Nominal) and channels
    for(auto systematicChannelSample : samples_.getSystematicChannelSamples()){
        const Sample::Systematic& systematic(systematicChannelSample.first);
        if(systematic!=Sample::Systematic::nominal)continue;
        for(auto channelSample : systematicChannelSample.second){
            const Sample::Channel& channel(channelSample.first);
            this->writeYields(channel, channelSample.second, v_eventHistoName);
        }
    }
    std::cout<<"Finishing event yield table processing\n";
}


void EventYields::writeYields(const Sample::Channel& channel, const std::vector<Sample>& v_sample, std::vector<TString>& v_eventHistoName){
    // Loop over all selection steps writing out event yields
    for(std::vector<TString>::const_iterator i_eventHistoName = v_eventHistoName.begin(); i_eventHistoName != v_eventHistoName.end(); ++i_eventHistoName){
        
        std::vector<SampleHistPair> v_numhist;
        for(auto sample : v_sample){
            TH1D *temp_hist = fileReader_->GetClone<TH1D>(sample.inputFile(), *i_eventHistoName);
            double lumiWeight = Tools::luminosityWeight(sample, luminosity_, fileReader_);
            Tools::applyFlatWeight(temp_hist, lumiWeight);
            v_numhist.push_back(SampleHistPair(sample, temp_hist));
        }
        
        for(auto sampleHistPair : v_numhist){
            const bool isDyll(sampleHistPair.first.sampleType() == Sample::SampleType::dyll);
            if(isDyll && channel!=Sample::Channel::emu){
                // FIXME: which DY scale factor is here applied, isn't it always the same instead of the step dependent one ?
                sampleHistPair.second->Scale(1.);
                //numhist.first->Scale(dyScaleFactors_(channel));
            }
        }
        
        // Prepare output folder and text file
        ofstream eventFile;
        TString eventFilestring = Tools::assignFolder(channel);
        gSystem->mkdir(eventFilestring, true);
        eventFilestring.Append("/"+*i_eventHistoName+".txt");
        eventFile.open(eventFilestring.Data());
        
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















