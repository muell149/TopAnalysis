#ifndef mvaSetup_h
#define mvaSetup_h

#include <vector>
#include <string>
#include <utility>

#include <TMVA/Types.h>

#include "../../diLeptonic/src/sampleHelpers.h"
#include "MvaFactory.h"






namespace mvaSetups{
    const std::vector<Channel::Channel> allChannels = {Channel::ee, Channel::emu, Channel::mumu, Channel::combined};
    
    const MvaFactory::MvaConfig config1("!H:!V:NTrees=600:nEventsMin=400:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.45:UseRandomisedTrees=False:UseNVars=13:nCuts=1000:PruneMethod=CostComplexity:PruneStrength=-1",
                                        "c1");
    const MvaFactory::MvaConfig config2("!H:!V:NTrees=400:nEventsMin=400:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.45:UseRandomisedTrees=False:UseNVars=13:nCuts=1000:PruneMethod=CostComplexity:PruneStrength=-1",
                                        "c2");
    const MvaFactory::MvaConfig config3("!H:!V:NTrees=200:nEventsMin=400:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.45:UseRandomisedTrees=False:UseNVars=13:nCuts=1000:PruneMethod=CostComplexity:PruneStrength=-1",
                                        "c3");
    
    // Apply set of categories
    const MvaFactory::MvaSet set1 = MvaFactory::MvaSet({config1, config2, config3},
                                                       {1, 3, 4, 5},
                                                       allChannels);
    
    // Apply no categories
    const MvaFactory::MvaSet set2 = MvaFactory::MvaSet({config1, config2, config3},
                                                       {},
                                                       allChannels);
    
    
    const std::vector<MvaFactory::MvaSet> v_mvaSetCorrect = std::vector<MvaFactory::MvaSet>({set1, set2});
    
    const std::vector<MvaFactory::MvaSet> v_mvaSetSwapped = std::vector<MvaFactory::MvaSet>({set1});
}




#endif







