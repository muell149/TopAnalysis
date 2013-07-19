#include "analysisStructs.h"





tth::GenLevelWeights::GenLevelWeights(const double& weightMadgraphCorrection, const double& weightPileup, const double& weightGenerator,
                                      const double& trueLevelWeightNoPileup, const double& trueLevelWeight):
weightMadgraphCorrection_(weightMadgraphCorrection),
weightPileup_(weightPileup),
weightGenerator_(weightGenerator),
trueLevelWeightNoPileup_(trueLevelWeightNoPileup),
trueLevelWeight_(trueLevelWeight)
{}



tth::RecoLevelWeights::RecoLevelWeights(const double& weightLeptonSF, const double& weightTriggerSF, const double& weightBtagSF,
                                        const double& weightNoPileup, double& weight):
weightLeptonSF_(weightLeptonSF),
weightTriggerSF_(weightTriggerSF),
weightBtagSF_(weightBtagSF),
weightNoPileup_(weightNoPileup),
weight_(weight)
{}



tth::ObjectIndices::ObjectIndices(const std::vector<int>& allLeptonIndices,
                                  const std::vector<int>& leptonIndices, const std::vector<int>& antiLeptonIndices,
                                  const int& leptonIndex, const int& antiLeptonIndex,
                                  const int& leadingLeptonIndex, const int& nLeadingLeptonIndex,
                                  const int& leptonXIndex, const int& leptonYIndex,
                                  const std::vector<int>& jetIndices, const std::vector<int>& bjetIndices):
allLeptonIndices_(allLeptonIndices),
leptonIndices_(leptonIndices),
antiLeptonIndices_(antiLeptonIndices),
leptonIndex_(leptonIndex),
antiLeptonIndex_(antiLeptonIndex),
leadingLeptonIndex_(leadingLeptonIndex),
nLeadingLeptonIndex_(nLeadingLeptonIndex),
leptonXIndex_(leptonXIndex),
leptonYIndex_(leptonYIndex),
jetIndices_(jetIndices),
bjetIndices_(bjetIndices)
{}





