#include <iostream>
#include <iomanip>
#include <sstream>

#include <TH1.h>
#include <TH1D.h>
#include <TMath.h>
#include <TString.h>

#include "DyScaleFactors.h"
#include "higgsUtils.h"
#include "Samples.h"
#include "../../common/include/sampleHelpers.h"
#include "../../common/include/RootFileReader.h"





DyScaleFactors::DyScaleFactors(const Samples& samples, const double& luminosity):
luminosity_(luminosity),
fileReader_(RootFileReader::getInstance())
{
    this->produceScaleFactors(samples);
}



void DyScaleFactors::produceScaleFactors(const Samples& samples)
{
    std::cout<<"--- Beginning production of Drell-Yan scale factors\n\n";
    
    // Extract steps for Drell-Yan scaling from first file in map
    const SystematicChannelSamples& m_systematicChannelSamples = samples.getSystematicChannelSamples();
    const TString& filename = m_systematicChannelSamples.begin()->second.begin()->second.begin()->inputFile();
    const std::vector<std::pair<TString, TString> > v_nameStepPair = tth::nameStepPairs(filename, "dyScaling_Allh1_step");
    
    // Loop over selection steps and systematics
    for(const auto& nameStepPair : v_nameStepPair){
        for(auto systematicChannelSamples : m_systematicChannelSamples){
            const Systematic::Systematic& systematic(systematicChannelSamples.first);
            this->produceScaleFactors(nameStepPair.second, systematic, systematicChannelSamples.second);
        }
    }
    
    // Print table
    std::cout<<"Step\t\tSystematic\tScale factors (ee, mumu)\n";
    std::cout<<"--------\t----------\t------------------------\n";
    for(auto dyScaleFactorsPerStep : m_dyScaleFactors_){
       const TString& step(dyScaleFactorsPerStep.first);
       for(auto dyScaleFactorsPerSystematic : dyScaleFactorsPerStep.second){
           const Systematic::Systematic& systematic(dyScaleFactorsPerSystematic.first);
           double eeScaleFactor(0.);
           double mumuScaleFactor(0.);
           for(auto dyScaleFactorsPerChannel : dyScaleFactorsPerSystematic.second){
               const Channel::Channel& channel(dyScaleFactorsPerChannel.first);
               const double& scaleFactor(dyScaleFactorsPerChannel.second);
               if(channel == Channel::ee) eeScaleFactor = scaleFactor;
               else if(channel == Channel::mumu) mumuScaleFactor = scaleFactor;
               //std::cout<<"DY scale factors: "<<step<<" , "<<Systematic::convertSystematic(systematic)<<" , "
               //         <<Channel::convertChannel(channel)<<" , "<<scaleFactor<<"\n";
           }
           std::cout<<step<<"\t\t"<<Systematic::convertSystematic(systematic)<<"\t\t"
                    <<std::fixed<<std::setprecision(3)<<eeScaleFactor<<" , "<<mumuScaleFactor<<"\n";
       }
    }
    std::cout<<"\n=== Finishing production of Drell-Yan scale factors\n\n";
}



//const DyScaleFactors::DyScaleFactorMap& DyScaleFactors::getScaleFactors()const
//{
//    return m_dyScaleFactors_;
//}



void DyScaleFactors::produceScaleFactors(const TString& step, const Systematic::Systematic& systematic, std::map<Channel::Channel, std::vector<Sample> >& channelSamples)
{
    
    const std::vector<Channel::Channel> v_channel {Channel::ee, Channel::emu, Channel::mumu};
    
    
    double nOut_ee_dy=0, nIn_ee_dy=0, nOut_mumu_dy=0, nIn_mumu_dy=0;//Number of events in/out of z-veto region for the DY MC
    double nIn_ee_data=0, nIn_mumu_data=0, nIn_emu_data=0;//Number of events in z-veto region for data
    double nIn_ee_data_loose=0, nIn_mumu_data_loose=0;//Number of data events in Z-Veto region with MET cut
    double nIn_ee_mc=0, nIn_mumu_mc=0;//All other MC events
    
    
    for(Channel::Channel channel : v_channel){
        const std::vector<Sample>& v_sample(channelSamples[channel]);
        for(Sample sample : v_sample){
            if(sample.sampleType()==Sample::higgssignal)continue;
            
            const double luminosityWeight(Tools::luminosityWeight(sample, luminosity_, fileReader_));
            const double allWeights = luminosityWeight; // calculate here all the flat-weights we apply: Lumi*others*...
            
            TH1D* h_loose = fileReader_->GetClone<TH1D>(sample.inputFile(), "dyScaling_Looseh1");
            TH1D* h_zWindow = fileReader_->GetClone<TH1D>(sample.inputFile(), TString("dyScaling_Zh1").Append(step).Append("zWindow"));
            TH1D* h_zVeto = fileReader_->GetClone<TH1D>(sample.inputFile(), TString("dyScaling_TTh1").Append(step));
            TH1D* h_all = fileReader_->GetClone<TH1D>(sample.inputFile(), TString("dyScaling_Allh1").Append(step));
            
            h_loose->Scale(allWeights);
            h_zWindow->Scale(allWeights);
            h_zVeto->Scale(allWeights);
            h_all->Scale(allWeights);
            
            // FIXME: here Integral() is used, but this does not account for the overflow, so it is wrong !?
            if(sample.sampleType()==Sample::data){
                if(channel==Channel::ee){
                    nIn_ee_data += h_zWindow->Integral();
                    nIn_ee_data_loose += h_loose->Integral();
                }
                else if(channel==Channel::mumu){
                    nIn_mumu_data += h_zWindow->Integral();
                    nIn_mumu_data_loose += h_loose->Integral();
                }
                else if(channel==Channel::emu){
                    nIn_emu_data += h_zWindow->Integral();
                }
                continue;
            }
            if(!channel==Channel::ee && !channel==Channel::mumu)continue;
            
            if(sample.sampleType()==Sample::dyee || sample.sampleType()==Sample::dymumu || sample.sampleType()==Sample::dytautau){
                if(channel==Channel::ee){
                    nIn_ee_dy += h_zWindow->Integral();
                    nOut_ee_dy += h_zVeto->Integral();
                }
                else if(channel==Channel::mumu){
                    nIn_mumu_dy += h_zWindow->Integral();
                    nOut_mumu_dy += h_zVeto->Integral();
                }
            }
            else{
                if(channel==Channel::ee){
                    nIn_ee_mc += h_zWindow->Integral();
                }
                else if(channel==Channel::mumu){
                    nIn_mumu_mc += h_zWindow->Integral();
                }
            }
            
            delete h_loose;
            delete h_zWindow;
            delete h_zVeto;
            delete h_all;
        }
    }
    
    const double k_ee = sqrt(nIn_ee_data_loose/nIn_mumu_data_loose);
    const double k_mumu = sqrt(nIn_mumu_data_loose/nIn_ee_data_loose);
    
    const double rOutIn_ee = nOut_ee_dy/nIn_ee_dy;
    const double rOutIn_mumu = nOut_mumu_dy/nIn_mumu_dy;
    
    const double nOut_ee_mc = rOutIn_ee*(nIn_ee_data - 0.5*nIn_emu_data*k_ee);
    const double nOut_mumu_mc = rOutIn_mumu*(nIn_mumu_data - 0.5*nIn_emu_data*k_mumu);

    const double dyScaleFactor_ee = nOut_ee_mc/nOut_ee_dy;
    const double dyScaleFactor_mumu = nOut_mumu_mc/nOut_mumu_dy;
    
    //this->printFullInformation(dyScaleFactor_ee, dyScaleFactor_mumu, k_ee, k_mumu, rOutIn_ee, rOutIn_mumu,
    //                           nIn_ee_data_loose, nIn_mumu_data_loose, nIn_ee_data, nIn_mumu_data, nIn_emu_data,
    //                           nIn_ee_mc, nIn_mumu_mc, nIn_ee_dy, nIn_mumu_dy,
    //                           nOut_ee_mc, nOut_mumu_mc, nOut_ee_dy, nOut_mumu_dy, step);
    
    m_dyScaleFactors_[step][systematic][Channel::ee] = dyScaleFactor_ee;
    m_dyScaleFactors_[step][systematic][Channel::mumu] = dyScaleFactor_mumu;
}



void DyScaleFactors::printFullInformation(const double dyScaleFactor_ee, const double dyScaleFactor_mumu, 
                                     const double k_ee, const double k_mumu,
                                     const double rOutIn_ee, const double rOutIn_mumu,
                                     const double nIn_ee_data_loose, const double nIn_mumu_data_loose,
                                     const double nIn_ee_data, const double nIn_mumu_data, const double nIn_emu_data,
                                     const double nIn_ee_mc, const double nIn_mumu_mc,
                                     const double nIn_ee_dy, const double nIn_mumu_dy,
                                     const double nOut_ee_mc, const double nOut_mumu_mc,
                                     const double nOut_ee_dy, const double nOut_mumu_dy,
                                     const TString& step)const
{
    std::cout<<"Numbers (out/in) or (ee/mumu/emu) for selection step: "<<step<<"\n\t"
             <<"DY ee (out/in):          "<<std::setw(10)<<nOut_ee_dy<<" "<<std::setw(10)<<nIn_ee_dy<<"\n\t"
             <<"DY mumu (out/in):        "<<std::setw(10)<<nOut_mumu_dy<<" "<<std::setw(10)<<nIn_mumu_dy<<"\n\t"
             <<"Data in (ee/mumu/emu):   "<<std::setw(10)<<nIn_ee_data<<" "<<std::setw(10)<<nIn_mumu_data<<" "<<std::setw(10)<<nIn_emu_data<<"\n\t"
             <<"Data in loose (ee/mumu): "<<std::setw(10)<<nIn_ee_data_loose<<" "<<std::setw(10)<<nIn_mumu_data_loose<<"\n\t"
             <<"Background in (ee/mumu): "<<std::setw(10)<<nIn_ee_mc<<" "<<std::setw(10)<<nIn_mumu_mc<<"\n\n";
    
    std::cout << "<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>" << std::endl;
    std::cout << "Calculation of DY Scale Factors at selection step: " << step << std::endl;
    std::cout<<"DY scale factor (ee):           "<<dyScaleFactor_ee<<std::endl;
    std::cout<<"DY scale factor (mumu):         "<<dyScaleFactor_mumu<<std::endl;
    std::cout<<"Efficiency correction k (ee):   "<<k_ee<<" +- "<<0.5*TMath::Sqrt(1./nIn_mumu_data_loose + 1./nIn_ee_data_loose)<<std::endl;
    std::cout<<"Efficiency correction k (mumu): "<<k_mumu<<" +- "<<0.5*TMath::Sqrt(1./nIn_mumu_data_loose + 1./nIn_ee_data_loose)<<std::endl;
    std::cout<<"Ratio out/in (ee):              "<<rOutIn_ee<<std::endl;
    std::cout<<"Ratio out/in (mumu):            "<<rOutIn_mumu<<std::endl;
    std::cout<<"DY estimate from Data (ee):     "<<nOut_ee_mc<<std::endl;
    std::cout<<"DY estimate from Data (mumu):   "<<nOut_mumu_mc<<std::endl;
    std::cout << "<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>" << std::endl;
    std::cout << std::endl;
}



const double& DyScaleFactors::dyScaleFactor(const TString& step,
                                            const Systematic::Systematic& systematic,
                                            const Channel::Channel& channel)const
{
    if(m_dyScaleFactors_.find(step)==m_dyScaleFactors_.end()){
        std::cerr<<"Drell-Yan scale factor requested, but not existent for Step: "<<step
                 <<"\n...break\n"<<std::endl;
        exit(15);
    }
    if(m_dyScaleFactors_.at(step).find(systematic) == m_dyScaleFactors_.at(step).end()){
        std::cerr<<"Drell-Yan scale factor requested, but not existent for Systematic: "<<Systematic::convertSystematic(systematic)
                 <<"\n...break\n"<<std::endl;
        exit(16);
    }
    if(channel!=Channel::ee && channel!=Channel::mumu){
        std::cerr<<"Drell-Yan scale factor requested for invalid channel: "<<Channel::convertChannel(channel)
                 <<"\n...break\n"<<std::endl;
        exit(17);
    }
    return m_dyScaleFactors_.at(step).at(systematic).at(channel);
}



int DyScaleFactors::applyDyScaleFactor(TH1* histogram, const Sample& sample,
                                       const Systematic::Systematic& systematic,
                                       const bool allowNonexistingStep)const
{
    // Check if step can be extracted from histogram name
    const TString histogramName(histogram->GetName());
    const TString step = tth::extractSelectionStep(histogramName);
    if(step == ""){
        if(allowNonexistingStep){
            // It is allowed that no Drell-Yan scale factor exists for this step, so silently do not apply one
            return -1;
        }
        else{
            std::cerr<<"Drell-Yan scale factor requested, but step could not be extracted from histogram name: "<<histogramName
                     <<"\n...break\n"<<std::endl;
            exit(14);
        }
    }
    
    // Check if Drell-Yan scale factor exists for extracted step
    if(m_dyScaleFactors_.find(step) == m_dyScaleFactors_.end()){
        if(allowNonexistingStep){
            // It is allowed that no Drell-Yan scale factor exists for this step, so silently do not apply one
            return -1;
        }
    }
    
    // Check whether the sample is a Drell-Yan sample and whether it should be scaled
    // FIXME: DY reweighting for all samples (dyee, dymumu) as final state where event is selected in (ee, mumu),
    // FIXME: i.e. using e.g. mumu SF for all or for only correct ones (dyee<-->ee, dymumu<-->mumu)?
    // FIXME: And what about dytautau sample and emu final state?
    const bool isDyll = sample.sampleType()==Sample::dyee || sample.sampleType()==Sample::dymumu;
    if(!isDyll) return 0;
    const Channel::Channel& finalState = sample.finalState();
    if(finalState!=Channel::ee && finalState!=Channel::mumu) return 0;
    
    // Access the Drell-Yan scale factor and apply it to the histogram
    const double& dyScaleFactor = this->dyScaleFactor(step, systematic, finalState);
    histogram->Scale(dyScaleFactor);
    //std::cout<<"\nDY: "<<step<<" , "<<histogramName<<" , "
    //         <<Systematic::convertSystematic(systematic)<<" , "<<Channel::convertChannel(finalState)<<" , "
    //         <<dyScaleFactor<<"\n\n";
    return 1;
}







