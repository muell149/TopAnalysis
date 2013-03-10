#include <iostream>
#include <iomanip>
#include <sstream>

#include <TH1D.h>

#include "dyScaleFactors.h"
#include "../diLeptonic/utils.h"
#include "higgsUtils.h"




DyScaleFactors::DyScaleFactors(Samples& samples, const double& luminosity):
luminosity_(luminosity), fileReader_(RootFileReader::getInstance())
{
    this->produceScaleFactors(samples);
}



void
DyScaleFactors::produceScaleFactors(Samples& samples){
    std::cout<<"--- Beginning production of Drell-Yan scale factors\n\n";
    
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
    std::cout<<"Found selection steps: "<<ss_step.str()<<"\n";
    
    // Loop over selection steps and systematics
    for(TString step : v_step){
        for(auto systematicChannelSamples : m_systematicChannelSamples){
            const Sample::Systematic& systematic(systematicChannelSamples.first);
            this->produceScaleFactors(step, systematic, systematicChannelSamples.second);
        }
    }
    
    //for(auto dyScaleFactorsPerStep : m_dyScaleFactors_){
    //    const TString& step(dyScaleFactorsPerStep.first);
    //    for(auto dyScaleFactorsPerSystematic : dyScaleFactorsPerStep.second){
    //        const Sample::Systematic& systematic(dyScaleFactorsPerSystematic.first);
    //        for(auto dyScaleFactorsPerChannel : dyScaleFactorsPerSystematic.second){
    //            const Sample::Channel& channel(dyScaleFactorsPerChannel.first);
    //            const double& scaleFactor(dyScaleFactorsPerChannel.second);
    //            std::cout<<"DY scale factors: "<<step<<" , "<<Tools::convertSystematic(systematic)<<" , "
    //                     <<Tools::convertChannel(channel)<<" , "<<scaleFactor<<"\n";
    //        }
    //    }
    //}
    std::cout<<"\n=== Finishing production of Drell-Yan scale factors\n\n";
}



DyScaleFactors::DyScaleFactorMap
DyScaleFactors::getScaleFactors()const{return m_dyScaleFactors_;}



void
DyScaleFactors::produceScaleFactors(const TString& step, const Sample::Systematic& systematic, std::map<Sample::Channel, std::vector<Sample> >& channelSamples){
    
    const std::vector<Sample::Channel> v_channel {Sample::ee, Sample::emu, Sample::mumu};
    
    
    double nOut_ee_dy=0, nIn_ee_dy=0, nOut_mumu_dy=0, nIn_mumu_dy=0;//Number of events in/out of z-veto region for the DY MC
    double nIn_ee_data=0, nIn_mumu_data=0, nIn_emu_data=0;//Number of events in z-veto region for data
    double nIn_ee_data_loose=0, nIn_mumu_data_loose=0;//Number of data events in Z-Veto region with MET cut
    double nIn_ee_mc=0, nIn_mumu_mc=0;//All other MC events
    
    
    for(Sample::Channel channel : v_channel){
        const std::vector<Sample>& v_sample(channelSamples[channel]);
        for(Sample sample : v_sample){
            if(sample.sampleType()==Sample::higgssignal)continue;
            
            const double luminosityWeight(Tools::luminosityWeight(sample, luminosity_, fileReader_));
            const double allWeights = luminosityWeight; // calculate here all the flat-weights we apply: Lumi*others*...
            
            TH1D* h_loose = fileReader_->GetClone<TH1D>(sample.inputFile(), "Looseh1");
            TH1D* h_zWindow = fileReader_->GetClone<TH1D>(sample.inputFile(), TString("Zh1_").Append(step));
            TH1D* h_zVeto = fileReader_->GetClone<TH1D>(sample.inputFile(), TString("TTh1_").Append(step));
            TH1D* h_all = fileReader_->GetClone<TH1D>(sample.inputFile(), TString("Allh1_").Append(step));
            
            Tools::applyFlatWeight(h_loose, allWeights);
            Tools::applyFlatWeight(h_zWindow, allWeights);
            Tools::applyFlatWeight(h_zVeto, allWeights);
            Tools::applyFlatWeight(h_all, allWeights);
            
            // FIXME: here Integral() is used, but this does not account for the overflow, so it is wrong !?
            if(sample.sampleType()==Sample::data){
                if(channel==Sample::ee){
                    nIn_ee_data += h_zWindow->Integral();
                    nIn_ee_data_loose += h_loose->Integral();
                }
                else if(channel==Sample::mumu){
                    nIn_mumu_data += h_zWindow->Integral();
                    nIn_mumu_data_loose += h_loose->Integral();
                }
                else if(channel==Sample::emu){
                    nIn_emu_data += h_zWindow->Integral();
                }
                continue;
            }
            if(!channel==Sample::ee && !channel==Sample::mumu)continue;
            
            if(sample.sampleType()==Sample::dyll || sample.sampleType()==Sample::dytautau){
                if(channel==Sample::ee){
                    nIn_ee_dy += h_zWindow->Integral();
                    nOut_ee_dy += h_zVeto->Integral();
                }
                else if(channel==Sample::mumu){
                    nIn_mumu_dy += h_zWindow->Integral();
                    nOut_mumu_dy += h_zVeto->Integral();
                }
            }
            else{
                if(channel==Sample::ee){
                    nIn_ee_mc += h_zWindow->Integral();
                }
                else if(channel==Sample::mumu){
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
    
    m_dyScaleFactors_[step][systematic][Sample::ee] = dyScaleFactor_ee;
    m_dyScaleFactors_[step][systematic][Sample::mumu] = dyScaleFactor_mumu;
}



void
DyScaleFactors::printFullInformation(const double dyScaleFactor_ee, const double dyScaleFactor_mumu, 
                                     const double k_ee, const double k_mumu,
                                     const double rOutIn_ee, const double rOutIn_mumu,
                                     const double nIn_ee_data_loose, const double nIn_mumu_data_loose,
                                     const double nIn_ee_data, const double nIn_mumu_data, const double nIn_emu_data,
                                     const double nIn_ee_mc, const double nIn_mumu_mc,
                                     const double nIn_ee_dy, const double nIn_mumu_dy,
                                     const double nOut_ee_mc, const double nOut_mumu_mc,
                                     const double nOut_ee_dy, const double nOut_mumu_dy,
                                     const TString& step)const{
    
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









