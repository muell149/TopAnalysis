#ifndef SamplesFwd_h
#define SamplesFwd_h

#include <vector>
#include <map>
#include <utility>

class TH1;

#include "../../common/include/sampleHelpers.h"





// Here only forward declaration to define typedefs
class Sample;

/// Storage type of all samples to be used in current analysis
/// These are all samples per dilepton analysis channel and per systematic
typedef std::map<Systematic::Systematic, std::map<Channel::Channel, std::vector<Sample> > > SystematicChannelSamples;

/// Type for associating a specific histogram of the input file to the sample
typedef std::pair<Sample, TH1*> SampleHistPair;





// Here only forward declaration to define typedefs
class Samples;





#endif // SamplesFwd_h






