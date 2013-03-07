#include "higgsUtils.h"

#include <iostream>


#include "TObjArray.h"


void
Tools::applyFlatWeight(TH1* hist, const double weight){
    if(weight == 0) {std::cout<<"Warning! The weight your applying is 0. This will remove your distribution."<<std::endl;}
    //if(weight >=1e3){std::cout<<"Warning: the weight your applying is >= 1e3. This will enlarge too much your distribution."<<std::endl;}
    hist->Scale(weight);
}


double
Tools::luminosityWeight(const Sample& sample, const double luminosity, RootFileReader* fileReader){
    double luminosityWeight=0;
    if(sample.sampleType() == Sample::SampleType::data)return 1;
    const TString& inputFile(sample.inputFile());
    const double crossSection(sample.crossSection());
    if(crossSection<=0.){
        std::cout<<"Sample XSection is <0. Can't calculate luminosity weight!! returning\n";
        return 0;
    }
    const TH1* h_weightedEvents = fileReader->Get<TH1>(inputFile, "weightedEvents");
    const double weightedEvents(h_weightedEvents->GetBinContent(1));
    luminosityWeight = luminosity*crossSection/weightedEvents;
    //std::cout<<"Input file: "<<inputFile<<std::endl;
    //std::cout<<"Luminosity, Xsection, weighted events, lumi weight: "
    //         <<luminosity<<" , "<<crossSection<<" , "<<weightedEvents<<" , "<<luminosityWeight<<std::endl;
    
    return luminosityWeight;
}



TString
Tools::assignFolder(const Sample::Channel& channel){
    TString outpathPlots = "./Plots";
    outpathPlots.Append("/");
    TString subfolderChannel = Tools::convertChannel(channel);
    return outpathPlots+subfolderChannel;
}



TString
Tools::stepFragmentByToken(const TString& filenameFragment, const TString& token){
    TString stepFragment;
    TObjArray* a_nameFragment = TString(filenameFragment).Tokenize(token);
    bool stepAlreadyFound(false);
    for(Int_t iFragment= 0; iFragment < a_nameFragment->GetEntriesFast(); ++iFragment){
        const TString& fragment = a_nameFragment->At(iFragment)->GetName();
        if(fragment.Contains("step")){
            if(stepAlreadyFound){
                std::cerr<<"Ambiguous string, file name contains \"step\" more than once in fragment: "<<filenameFragment
                         <<"\n...cannot extract selection step, so break\n";
                exit(33);
            }
            stepAlreadyFound = true;
            stepFragment = fragment;
        }
    }
    return stepFragment;
}


TString
Tools::extractSelectionStep(const TString& histogramName){
    TString step(histogramName);
    // Remove .root
    step = Tools::stepFragmentByToken(step, ".");
    // Further separation by "_" to find string containing step
    step = Tools::stepFragmentByToken(step, "_");
    //std::cout<<"The extracted selection step is (step/histogram name): "<<step<<" / "<<histogramName<<std::endl;
    return step;
}








