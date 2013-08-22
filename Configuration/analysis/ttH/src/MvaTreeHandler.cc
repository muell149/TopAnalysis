#include <iostream>
#include <cstdlib>
#include <algorithm>

#include <TTree.h>
#include <TFile.h>
#include <TString.h>
#include <TSelectorList.h>
#include <Rtypes.h>

#include "MvaTreeHandler.h"
#include "mvaStructs.h"
#include "analysisStructs.h"
#include "JetCategories.h"
#include "higgsUtils.h"
#include "../../diLeptonic/src/sampleHelpers.h"
#include "../../diLeptonic/src/analysisObjectStructs.h"







// For plotting
#include <TIterator.h>
#include <TObject.h>
#include <TH1.h>
#include <TH1D.h>








MvaTreeHandler::MvaTreeHandler(const char* mvaInputDir,
                               const std::vector<TString>& selectionStepsNoCategories,
                               const std::vector<TString>& stepsForCategories,
                               const JetCategories* jetCategories):
selectorList_(0),
t_mvaInput_(0),
selectionSteps_(selectionStepsNoCategories),
stepsForCategories_(stepsForCategories),
jetCategories_(jetCategories),
mvaInputDir_(mvaInputDir),
plotExclusively_(false)
{
    std::cout<<"--- Beginning setting up MVA input tree handler\n";
    
    if(!jetCategories_ && stepsForCategories_.size()>0){
        std::cerr<<"ERROR in constructor for MvaTreeHandler! "
                 <<"No jet categories passed, but request for category-wise selection steps\n...break\n"<<std::endl;
        exit(236);
    }
    if(jetCategories_ && stepsForCategories_.size()==0){
        std::cerr<<"ERROR in constructor for MvaTreeHandler! "
                 <<"Jet categories passed, but no category-wise selection steps defined\n...break\n"<<std::endl;
        exit(237);
    }
    
    std::cout<<"=== Finishing setting up MVA input tree handler\n\n";
}



void MvaTreeHandler::book()
{
    for(const auto& stepShort : selectionSteps_){
        const TString step = tth::stepName(stepShort);
        this->addStep(step);
    }
    
    for(const auto& stepShort : stepsForCategories_){
        for(int category = 0; category<jetCategories_->numberOfCategories(); ++category){
            const TString step = tth::stepName(stepShort, category);
            this->addStep(step);
        }
    }
    
    std::cout<<"\n\nBooked: ";
    for(const auto& stepMvaVariables : m_stepMvaVariables_){
        std::cout<<stepMvaVariables.first<<" , ";
    }
    std::cout<<"\n\n\n";
}



void MvaTreeHandler::addStep(const TString& step)
{
    // Check whether step already exists
    if(this->checkExistence(step)){
        std::cout<<"Warning in addStep()! Selection step already contained: "<<step
                 <<"\n...skip this one\n";
        return;
    }

    // Book the step
    m_stepMvaVariables_[step] = std::vector<MvaTopJetsVariables>();
}



bool MvaTreeHandler::checkExistence(const TString& step)const
{
    return m_stepMvaVariables_.find(step) != m_stepMvaVariables_.end();
}



void MvaTreeHandler::fill(const RecoObjects& recoObjects,
                          const tth::GenObjectIndices& genObjectIndices, const tth::RecoObjectIndices& recoObjectIndices,
                          const double& weight, const TString& stepShort)
{
    // Number of selected jets and bjets
    const int numberOfJets = recoObjectIndices.jetIndices_.size();
    const int numberOfBjets = recoObjectIndices.bjetIndices_.size();
    
    // Set up step name and check if step exists
    const bool stepInCategory = stepShort.Contains("_cate");
    const TString step = stepInCategory ? stepShort : tth::stepName(stepShort);
    const bool stepExists(this->checkExistence(step));
    if(!stepInCategory && jetCategories_){
        // Here check the individual jet categories
        const int categoryId = jetCategories_->categoryId(numberOfJets, numberOfBjets);
        const TString fullStepName = tth::stepName(stepShort, categoryId);
        this->fill(recoObjects, genObjectIndices, recoObjectIndices, weight, fullStepName);
    }
    if(!stepExists) return;
    
    // Loop over all jet combinations and get MVA input variables
    const std::vector<MvaTopJetsVariables>& v_mvaTopJetsVariables = 
            MvaTopJetsVariables::fillVariables(recoObjectIndices, genObjectIndices, recoObjects, weight);
    
    // Fill the MVA variables
    m_stepMvaVariables_.at(step).insert(m_stepMvaVariables_.at(step).end(), v_mvaTopJetsVariables.begin(), v_mvaTopJetsVariables.end());
}



void MvaTreeHandler::writeTrees(const std::string& outputFilename,
                                const Channel::Channel& channel, const Systematic::Systematic& systematic)
{
    std::cout<<"\n\nValues:\n";
    for(auto vars : m_stepMvaVariables_){
        std::cout<<"\t"<<vars.first<<" , "<<vars.second.size()<<"\n";
    }
    std::cout<<"\n\n\n";
    
    
    // Create output file for MVA tree
    std::string f_savename = static_cast<std::string>(ttbar::assignFolder(mvaInputDir_, channel, systematic));
    f_savename.append(outputFilename);
    TFile outputFile(f_savename.c_str(),"RECREATE");
    std::cout<<"\nOutput file for MVA input trees: "<<f_savename<<"\n";
    
    // Produce MVA input TTree and store it in output
    TSelectorList* output = new TSelectorList();
    this->writeTrees(output);
    
    // Write file and cleanup
    TIterator* it = output->MakeIterator();
    while(TObject* obj = it->Next()){
        obj->Write();
    }
    outputFile.Close();
    output->SetOwner();
    output->Clear();
}



void MvaTreeHandler::writeTrees(TSelectorList* output)
{
    std::cout<<"--- Beginning production of MVA input trees\n";
    
    // Set pointer to output, so that TTree is owned by it
    selectorList_ = output;
    
    std::map<TString, TTree*> m_stepTree;
    for(const auto& stepMvaVariables : m_stepMvaVariables_){
        const TString& step = stepMvaVariables.first;
        const std::vector<MvaTopJetsVariables>& v_mvaVariables = stepMvaVariables.second;
        TTree* tree = m_stepTree[step];
        tree = this->store(new TTree("mvaInputTopJets"+step, "mvaInputTopJets"));
        this->createMvaInputBranches(tree);
        this->fillMvaInputBranches(v_mvaVariables);
    }
    
    std::cout<<"Dijet combinations per step (step, no. of combinations):\n";
    for(auto vars : m_stepMvaVariables_){
        std::cout<<"\t"<<vars.first<<" , "<<vars.second.size()<<"\n";
    }
    
    std::cout<<"=== Finishing production of MVA input trees\n\n";
}














void MvaTreeHandler::fillForInputProduction(const RecoObjects& recoObjects,
                                            const tth::GenObjectIndices& genObjectIndices,
                                            const tth::RecoObjectIndices& recoObjectIndices,
                                            const double& weight,
                                            const TString& selectionStep)
{
    // Check if step exists
    if(std::find(selectionSteps_.begin(), selectionSteps_.end(), selectionStep) == selectionSteps_.end()) return;
    
    // FIXME: which events exactly to fill? For now all with at least 4 jets
    const int numberOfJets = recoObjectIndices.jetIndices_.size();
    if(numberOfJets<4) return;
    
    // Loop over all jet combinations and get MVA input variables
    const std::vector<MvaTopJetsVariables>& v_mvaTopJetsVariables = 
            MvaTopJetsVariables::fillVariables(recoObjectIndices, genObjectIndices, recoObjects, weight);
    
    // Fill the MVA TTree
    v_mvaTopJetsVariables_.insert(v_mvaTopJetsVariables_.end(), v_mvaTopJetsVariables.begin(), v_mvaTopJetsVariables.end());
}



void MvaTreeHandler::createMvaInputBranches(TTree* tree)
{
    t_mvaInput_ = tree;
    
    this->createBranch(mvaTopJetsVariables_.eventWeight_);
    this->createBranch(mvaTopJetsVariables_.bQuarkRecoJetMatched_);
    this->createBranch(mvaTopJetsVariables_.correctCombination_);
    this->createBranch(mvaTopJetsVariables_.swappedCombination_);
    this->createBranch(mvaTopJetsVariables_.jetChargeDiff_);
    this->createBranch(mvaTopJetsVariables_.meanDeltaPhi_b_met_);
    this->createBranch(mvaTopJetsVariables_.massDiff_recoil_bbbar_);
    this->createBranch(mvaTopJetsVariables_.pt_b_antiLepton_);
    this->createBranch(mvaTopJetsVariables_.pt_antiB_lepton_);
    this->createBranch(mvaTopJetsVariables_.deltaR_b_antiLepton_);
    this->createBranch(mvaTopJetsVariables_.deltaR_antiB_lepton_);
    this->createBranch(mvaTopJetsVariables_.btagDiscriminatorSum_);
    this->createBranch(mvaTopJetsVariables_.deltaPhi_antiBLepton_bAntiLepton_);
    this->createBranch(mvaTopJetsVariables_.massDiff_fullBLepton_bbbar_);
    this->createBranch(mvaTopJetsVariables_.meanMt_b_met_);
    this->createBranch(mvaTopJetsVariables_.massSum_antiBLepton_bAntiLepton_);
    this->createBranch(mvaTopJetsVariables_.massDiff_antiBLepton_bAntiLepton_);
}



void MvaTreeHandler::createBranch(const MvaVariableInt& variable)
{
    std::string name(variable.name());
    std::string nameType(name);
    nameType.append("/").append(variable.type());
    t_mvaInput_->Branch(name.data(), (Long_t)&variable.value_, nameType.data());
}



void MvaTreeHandler::createBranch(const MvaVariableFloat& variable)
{
    std::string name(variable.name());
    std::string nameType(name);
    nameType.append("/").append(variable.type());
    t_mvaInput_->Branch(name.c_str(), (Long_t)&variable.value_, nameType.data());
}



void MvaTreeHandler::clear()
{
    v_mvaTopJetsVariables_.clear();
    t_mvaInput_ = 0;
    selectorList_ = 0;
    
    for(auto& stepMvaVariables : m_stepMvaVariables_){
        stepMvaVariables.second.clear();
    }
    m_stepMvaVariables_.clear();
    
    // For plotting
    for(auto stepHistograms : m_stepHistograms_){
        stepHistograms.second.m_histogram_.clear();
    }
    m_stepHistograms_.clear();
}



void MvaTreeHandler::fillMvaInputBranches(const std::vector<MvaTopJetsVariables>& v_mvaTopJetsVariables)
{
    for(const auto& mvaTopJetsVariables : v_mvaTopJetsVariables){
        mvaTopJetsVariables_ = mvaTopJetsVariables;
        t_mvaInput_->Fill();
    }
}



void MvaTreeHandler::produceMvaInputTree(const std::string& outputFilename,
                                         const Channel::Channel& channel, const Systematic::Systematic& systematic)
{
    std::cout<<"\n\nValues:\n";
    for(auto vars : m_stepMvaVariables_){
        std::cout<<"\t"<<vars.first<<" , "<<vars.second.size()<<"\n";
    }
    std::cout<<"\n\n\n";
    
    
    // Create output file for MVA tree
    std::string f_savename = static_cast<std::string>(ttbar::assignFolder(mvaInputDir_, channel, systematic));
    f_savename.append(outputFilename);
    TFile outputFile(f_savename.c_str(),"RECREATE");
    std::cout<<"\nOutput file for MVA input tree: "<<f_savename<<"\n";
    
    // Produce MVA input TTree and store it in output
    TSelectorList* output = new TSelectorList();
    this->produceMvaInputTree(output);
    
    // Write file and cleanup
    TIterator* it = output->MakeIterator();
    while(TObject* obj = it->Next()){
        obj->Write();
    }
    outputFile.Close();
    output->SetOwner();
    output->Clear();
}



void MvaTreeHandler::produceMvaInputTree(TSelectorList* output)
{
    std::cout<<"--- Beginning production of MVA input tree\n";
    
    // Set pointer to output, so that TTree is owned by it
    selectorList_ = output;
    
    // TTree for MVA input
    TTree* tree(0);
    tree = store(new TTree("mvaInputTopJets", "mvaInputTopJets"));
    //tree = dynamic_cast<TTree*>(output->FindObject("mvaInputTopJets"));
    
    // Create branches and fill tree
    this->createMvaInputBranches(tree);
    this->fillMvaInputBranches(v_mvaTopJetsVariables_);
    
    std::cout<<"Number of dijet combinations for MVA: "<<v_mvaTopJetsVariables_.size()<<"\n";
    std::cout<<"=== Finishing production of MVA input tree\n\n";
}



void MvaTreeHandler::importTree(const std::string& f_savename, const std::string& treeName)
{
    std::cout<<"--- Beginning import of TTree for MVA variables\n";
    
    TFile* inputFile = TFile::Open(f_savename.c_str());
    if(inputFile->IsZombie()){
        std::cerr<<"ERROR! Cannot open input file to import TTree, filename is: "<<f_savename<<"\n...break\n"<<std::endl;
        exit(77);
    }
    
    TTree* tree(0);
    tree = dynamic_cast<TTree*>(inputFile->Get(treeName.c_str()));
    if (!tree){
        std::cerr << "ERROR: TTree not found in file, tree name is: "<<treeName<<"\n...break\n"<<std::endl;
        exit(78);
    }
    
    this->importBranches(tree);
    
    tree = 0;
    inputFile->Close();
    std::cout<<"\nNumber of entries: "<<v_mvaTopJetsVariables_.size()<<"\n\n";
    std::cout<<"=== Finishing import of TTree for MVA variables\n\n";
}



void MvaTreeHandler::importBranches(TTree* tree)
{
    // Set up variables struct and branches
    MvaTopJetsVariables mvaTopJetsVariables;
    
    // Set branch addresses
    this->importBranch(tree, mvaTopJetsVariables.eventWeight_);
    this->importBranch(tree, mvaTopJetsVariables.bQuarkRecoJetMatched_);
    this->importBranch(tree, mvaTopJetsVariables.correctCombination_);
    this->importBranch(tree, mvaTopJetsVariables.swappedCombination_);
    this->importBranch(tree, mvaTopJetsVariables.jetChargeDiff_);
    this->importBranch(tree, mvaTopJetsVariables.meanDeltaPhi_b_met_);
    this->importBranch(tree, mvaTopJetsVariables.massDiff_recoil_bbbar_);
    this->importBranch(tree, mvaTopJetsVariables.pt_b_antiLepton_);
    this->importBranch(tree, mvaTopJetsVariables.pt_antiB_lepton_);
    this->importBranch(tree, mvaTopJetsVariables.deltaR_b_antiLepton_);
    this->importBranch(tree, mvaTopJetsVariables.deltaR_antiB_lepton_);
    this->importBranch(tree, mvaTopJetsVariables.btagDiscriminatorSum_);
    this->importBranch(tree, mvaTopJetsVariables.deltaPhi_antiBLepton_bAntiLepton_);
    this->importBranch(tree, mvaTopJetsVariables.massDiff_fullBLepton_bbbar_);
    this->importBranch(tree, mvaTopJetsVariables.meanMt_b_met_);
    this->importBranch(tree, mvaTopJetsVariables.massSum_antiBLepton_bAntiLepton_);
    this->importBranch(tree, mvaTopJetsVariables.massDiff_antiBLepton_bAntiLepton_);
    
    // Loop over all tree entries and fill vector of structs
    v_mvaTopJetsVariables_.clear();
    for(Long64_t iEntry = 0; iEntry < tree->GetEntries(); ++iEntry){
        tree->GetEntry(iEntry);
        v_mvaTopJetsVariables_.push_back(mvaTopJetsVariables);
    }
}



void MvaTreeHandler::importBranch(TTree* tree, MvaVariableInt& variable)
{
    tree->SetBranchAddress(variable.name().data(), &variable.value_, &variable.branch_);
}



void MvaTreeHandler::importBranch(TTree* tree, MvaVariableFloat& variable)
{
    tree->SetBranchAddress(variable.name().data(), &variable.value_, &variable.branch_);
}











// For plotting
void MvaTreeHandler::plotVariables(const std::string& f_savename, const bool separationPowerPlots)
{
    // Output file
    TFile outputFile(f_savename.c_str(),"RECREATE");
    std::cout<<"\nOutput file for MVA input control plots: "<<f_savename<<"\n";
    
    // Produce MVA input control plots and store them in output
    TSelectorList* output = new TSelectorList();
    this->plotVariables(output, separationPowerPlots);
    
    // Write file and cleanup
    TIterator* it = output->MakeIterator();
    while(TObject* obj = it->Next()){
        obj->Write();
    }
    outputFile.Close();
    output->SetOwner();
    output->Clear();
}



void MvaTreeHandler::plotVariables(TSelectorList* output, const bool separationPowerPlots)
{
    std::cout<<"--- Beginning control plots for MVA variables\n";
    
    // Set bool for inclusive or exclusive plotting
    plotExclusively_ = separationPowerPlots;
    
    // Set pointer to output, so that histograms are owned by it
    selectorList_ = output;
    
    // FIXME: needs generalisation for different selection steps, but this is already needed for TTree itself (produce several trees, assigned to steps)
    // FIXME: same is valid for different categories
    const TString step("_step8");
    
    constexpr const char* prefix = "mvaP_";
    std::map<TString, TH1*>& m_histogram = m_stepHistograms_[step].m_histogram_;
    TString name;
    
    // Book histograms
    TH1* h_trueStatus_step8 = store(new TH1D("trueStatus"+step, "True status of matched jets;Status;# jet pairs",2,0,2));
    h_trueStatus_step8->GetXaxis()->SetBinLabel(1, "swapped");
    h_trueStatus_step8->GetXaxis()->SetBinLabel(2, "correct");
    
    name = mvaTopJetsVariables_.jetChargeDiff_.name();
    this->bookHistosInclExcl(m_histogram, prefix, step, name, name+";#Deltac_{rel}^{jet};# jet pairs",50,0,2);
    
    name = mvaTopJetsVariables_.meanDeltaPhi_b_met_.name();
    this->bookHistosInclExcl(m_histogram, prefix, step, name, name+";0.5(|#Delta#phi(b,MET)|+|#Delta#phi(#bar{b},MET)|)  [rad];# jet pairs",20,0,3.2);
    
    name = mvaTopJetsVariables_.massDiff_recoil_bbbar_.name();
    this->bookHistosInclExcl(m_histogram, prefix, step, name, name+"; m_{recoil}^{jets}-m^{b#bar{b}}  [GeV];# jet pairs",16,-600,600);
    
    name = mvaTopJetsVariables_.pt_b_antiLepton_.name();
    this->bookHistosInclExcl(m_histogram, prefix, step, name, name+"; p_{T}^{bl^{+}}  [GeV];# jet pairs",20,0,500);
    
    name = mvaTopJetsVariables_.pt_antiB_lepton_.name();
    this->bookHistosInclExcl(m_histogram, prefix, step, name, name+"; p_{T}^{#bar{b}l^{-}}  [GeV];# jet pairs",20,0,500);
    
    name = mvaTopJetsVariables_.deltaR_b_antiLepton_.name();
    this->bookHistosInclExcl(m_histogram, prefix, step, name, name+"; #DeltaR(b,l^{+});# jet pairs",25,0,5);
    
    name = mvaTopJetsVariables_.deltaR_antiB_lepton_.name();
    this->bookHistosInclExcl(m_histogram, prefix, step, name, name+"; #DeltaR(#bar{b},l^{-});# jet pairs",25,0,5);
    
    name = mvaTopJetsVariables_.btagDiscriminatorSum_.name();
    this->bookHistosInclExcl(m_histogram, prefix, step, name, name+"; d^{b}+d^{#bar{b}};# jet pairs",20,0,2);
    
    name = mvaTopJetsVariables_.deltaPhi_antiBLepton_bAntiLepton_.name();
    this->bookHistosInclExcl(m_histogram, prefix, step, name, name+"; |#Delta#phi(bl^{+},#bar{b}l^{-})|  [rad];# jet pairs",10,0,3.2);
    
    name = mvaTopJetsVariables_.massDiff_fullBLepton_bbbar_.name();
    this->bookHistosInclExcl(m_histogram, prefix, step, name, name+"; m^{b#bar{b}l^{+}l^{-}}-m^{b#bar{b}}  [GeV];# jet pairs",13,0,1050);
    
    name = mvaTopJetsVariables_.meanMt_b_met_.name();
    this->bookHistosInclExcl(m_histogram, prefix, step, name, name+"; 0.5(m_{T}^{b,MET}+m_{T}^{#bar{b},MET)}  [GeV];# jet pairs",21,0,630);
    
    name = mvaTopJetsVariables_.massSum_antiBLepton_bAntiLepton_.name();
    this->bookHistosInclExcl(m_histogram, prefix, step, name, name+"; m^{#bar{b}l^{-}}+m^{bl^{+}}  [GeV];# jet pairs",21,0,840);
    
    name = mvaTopJetsVariables_.massDiff_antiBLepton_bAntiLepton_.name();
    this->bookHistosInclExcl(m_histogram, prefix, step, name, name+"; m^{#bar{b}l^{-}}-m^{bl^{+}}  [GeV];# jet pairs",41,-400,420);
    
    
    
    // Fill histograms
    for(const MvaTopJetsVariables& mvaTopJetsVariables : v_mvaTopJetsVariables_){
        
        //const bool bQuarkRecoJetMatched = mvaInputTopJetsStruct.bQuarkRecoJetMatched_;
        const double weight(mvaTopJetsVariables.eventWeight_.value_);
        if(mvaTopJetsVariables.swappedCombination_.value_) h_trueStatus_step8->Fill(0., weight);
        if(mvaTopJetsVariables.correctCombination_.value_) h_trueStatus_step8->Fill(1., weight);
        
        double value;
        
        name = mvaTopJetsVariables.jetChargeDiff_.name();
        value = mvaTopJetsVariables.jetChargeDiff_.value_;
        this->fillHistosInclExcl(m_histogram, name, value, mvaTopJetsVariables, weight);
        
        name = mvaTopJetsVariables.meanDeltaPhi_b_met_.name();
        value = mvaTopJetsVariables.meanDeltaPhi_b_met_.value_;
        this->fillHistosInclExcl(m_histogram, name, value, mvaTopJetsVariables, weight);
        
        name = mvaTopJetsVariables.massDiff_recoil_bbbar_.name();
        value = mvaTopJetsVariables.massDiff_recoil_bbbar_.value_;
        this->fillHistosInclExcl(m_histogram, name, value, mvaTopJetsVariables, weight);
        
        name = mvaTopJetsVariables.pt_b_antiLepton_.name();
        value = mvaTopJetsVariables.pt_b_antiLepton_.value_;
        this->fillHistosInclExcl(m_histogram, name, value, mvaTopJetsVariables, weight);
        
        name = mvaTopJetsVariables.pt_antiB_lepton_.name();
        value = mvaTopJetsVariables.pt_antiB_lepton_.value_;
        this->fillHistosInclExcl(m_histogram, name, value, mvaTopJetsVariables, weight);
        
        name = mvaTopJetsVariables.deltaR_b_antiLepton_.name();
        value = mvaTopJetsVariables.deltaR_b_antiLepton_.value_;
        this->fillHistosInclExcl(m_histogram, name, value, mvaTopJetsVariables, weight);
        
        name = mvaTopJetsVariables.deltaR_antiB_lepton_.name();
        value = mvaTopJetsVariables.deltaR_antiB_lepton_.value_;
        this->fillHistosInclExcl(m_histogram, name, value, mvaTopJetsVariables, weight);
        
        name = mvaTopJetsVariables.btagDiscriminatorSum_.name();
        value = mvaTopJetsVariables.btagDiscriminatorSum_.value_;
        this->fillHistosInclExcl(m_histogram, name, value, mvaTopJetsVariables, weight);
        
        name = mvaTopJetsVariables.deltaPhi_antiBLepton_bAntiLepton_.name();
        value = mvaTopJetsVariables.deltaPhi_antiBLepton_bAntiLepton_.value_;
        this->fillHistosInclExcl(m_histogram, name, value, mvaTopJetsVariables, weight);
        
        name = mvaTopJetsVariables.massDiff_fullBLepton_bbbar_.name();
        value = mvaTopJetsVariables.massDiff_fullBLepton_bbbar_.value_;
        this->fillHistosInclExcl(m_histogram, name, value, mvaTopJetsVariables, weight);
        
        name = mvaTopJetsVariables.meanMt_b_met_.name();
        value = mvaTopJetsVariables.meanMt_b_met_.value_;
        this->fillHistosInclExcl(m_histogram, name, value, mvaTopJetsVariables, weight);
        
        name = mvaTopJetsVariables.massSum_antiBLepton_bAntiLepton_.name();
        value = mvaTopJetsVariables.massSum_antiBLepton_bAntiLepton_.value_;
        this->fillHistosInclExcl(m_histogram, name, value, mvaTopJetsVariables, weight);
        
        name = mvaTopJetsVariables.massDiff_antiBLepton_bAntiLepton_.name();
        value = mvaTopJetsVariables.massDiff_antiBLepton_bAntiLepton_.value_;
        this->fillHistosInclExcl(m_histogram, name, value, mvaTopJetsVariables, weight);
    }
    
    std::cout<<"=== Finishing control plots for MVA variables\n\n";
}



void MvaTreeHandler::bookHistosInclExcl(std::map<TString, TH1*>& m_histogram, const TString& prefix, const TString& step,
                                        const TString& name, const TString& title,
                                        const int& nBinX, const double& xMin, const double& xMax)
{
    const TString correct("correct_");
    const TString swapped("swapped_");
    const TString wrong("wrong_");
    
    if(!plotExclusively_){
        m_histogram[name] = this->store(new TH1D(prefix+name+step, title, nBinX, xMin, xMax));
    }
    else{
        m_histogram[correct+name] = this->store(new TH1D(correct+prefix+name+step, title, nBinX, xMin, xMax));
        m_histogram[swapped+name] = this->store(new TH1D(swapped+prefix+name+step, title, nBinX, xMin, xMax));
        m_histogram[wrong+name] = this->store(new TH1D(wrong+prefix+name+step, title, nBinX, xMin, xMax));
    }
}



void MvaTreeHandler::fillHistosInclExcl(std::map<TString, TH1*>& m_histogram, const TString& name,
                                        const double& variable,
                                        const MvaTopJetsVariables& mvaTopJetsVariables, const double& weight)
{
    const TString correct("correct_");
    const TString swapped("swapped_");
    const TString wrong("wrong_");
    
    if(!plotExclusively_){
        m_histogram[name]->Fill(variable, weight);
    }
    else{
        if(mvaTopJetsVariables.correctCombination_.value_) m_histogram[correct+name]->Fill(variable, weight);
        else if(mvaTopJetsVariables.swappedCombination_.value_) m_histogram[swapped+name]->Fill(variable, weight);
        else m_histogram[wrong+name]->Fill(variable, weight);
    }
}















