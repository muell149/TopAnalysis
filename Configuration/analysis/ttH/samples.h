#ifndef Samples_h
#define Samples_h

#include <vector>
#include <map>

#include <TString.h>

class RootFileReader;
class TH1D;




/// Class defining a sample for processing keeping all information as needed
class Sample{
    
public:
    
    /// Systematics for analysis
    enum Systematic{nominal, undefinedSystematic};
    
    /// Dileptonic decay channels for analysis
    enum Channel{ee, emu, mumu, combined, undefinedChannel};
    
    /// Specific type of sample as needed to be known for eg. plotting or Drell-Yan scale factor calculation
    enum SampleType{data, dyll, dytautau, higgssignal, dummy};
    
    
    
    /// Default constructor
    Sample();
    
    /// Constructor for setting up a sample
    Sample(const TString legendEntry, const int color, const double crossSection, const SampleType sampleType=dummy);
    
    /// Default destructor
    ~Sample(){};
    
    
    
    /// Return sample legend entry for drawing
    TString legendEntry()const;
    
    /// Return sample colour for drawing (needs to be identical for samples same legendEntry)
    int color()const;
    
    /// Return cross section corresponding to the sample
    double crossSection()const;
    
    /// Return the specific type of sample
    SampleType sampleType()const;
    
    
    
    /// Set real final state of sample, ie. only "ee", "emu", "mumu", but not "combined"
    void setFinalState(const Channel& channel);
    
    /// Get real final state of sample, ie. only "ee", "emu", "mumu", but not "combined"
    Channel finalState()const;
    
    /// Set real systematic assigned to this sample, i.e. either nominal or specific systematic
    void setSystematic(const Systematic& systematic);
    
    /// Get real systematic assigned to this sample, i.e. either nominal or specific systematic
    Systematic systematic()const;
    
    /// Set the path of the input root file
    void setInputFile(const TString& inputFileName);
    
    /// Return the path of the input root file
    TString inputFile()const;
    
    
    
private:
    
    /// Sample legend entry for drawing
    /// Samples will be ordered by legend entry and those with identical ones are merged in certain steps of further processing
    TString legendEntry_;
    
    /// Sample colour for drawing (needs to be identical for samples same legendEntry)
    int color_;
    
    /// Cross section corresponding to the sample
    double crossSection_;
    
    /// Specific type of sample as needed to be known for eg. plotting or Drell-Yan scale factor calculation
    SampleType sampleType_;
    
    /// Real final state of sample, ie. only "ee", "emu", "mumu", but not "combined"
    Channel finalState_;
    
    /// Real systematic of sample, i.e. what should be used for given systematic (nominal or specific systematic)
    Systematic systematic_;
    
    /// Path of the input root file
    TString inputFileName_;
};





/// Storage type of all samples to be used in current analysis
/// These are all samples per dilepton analysis channel and per systematic
typedef std::map<Sample::Systematic, std::map<Sample::Channel, std::vector<Sample> > > SystematicChannelSamples;





/// Class for administration of all samples, all dilepton channels and all systematics
class Samples{
    
public:
    
    /// Default constructor
    Samples();
    
    /// Constructor setting up samples
    Samples(const std::vector<Sample::Channel>& v_channel, const std::vector<Sample::Systematic>& v_systematic);
    
    /// Default destructor
    ~Samples(){};
    
    
    
    /// Get map containing all samples per dilepton analysis channel and per systematic
    const SystematicChannelSamples& getSystematicChannelSamples();
    
    /// Get all samples of specific dilepton analysis channel and specific systematic
    const std::vector<Sample>& getSamples(const Sample::Channel& channel, const Sample::Systematic& systematic);
    
        
    
private:
    
    /// Add samples for specific dilepton analysis channel and specific systematic
    void addSamples(const Sample::Channel& channel, const Sample::Systematic& systematic);
    
    /// Place where to define the samples as they will be used in the analysis
    std::vector<std::pair<TString, Sample> > setSamples(const Sample::Channel& channel, const Sample::Systematic& systematic);
    
    /// Assign options to each sample via its filename
    std::vector<Sample> setSampleOptions(const Sample::Systematic& systematic, const std::vector< std::pair< TString, Sample > >& v_filenameSamplePair);
    
    /// Order samples by their legend
    /// when a legend already exists, the sample is moved directly behind it
    void orderByLegend(std::vector<Sample>& v_sample);
    
    /// Assign the real final state to each sample, ie. only "ee", "emu", "mumu", but not "combined"
    Sample::Channel assignFinalState(const TString& filename);
    
    /// Assign the real systematic to each sample, i.e. what should be used for given systematic (nominal or specific systematic)
    /// and modify filename accordingly
    Sample::Systematic assignSystematic(TString& filename, const Sample::Systematic& systematic);
    
    
    
    /// Map containing all samples per dilepton analysis channel and per systematic
    SystematicChannelSamples m_systematicChannelSample_;
};





/// Type for associating a specific histogram of the input file to the sample
typedef std::pair<Sample, TH1D*> SampleHistPair;

/// Type which maps different samples (and the associated histogram) by same legend entries
typedef std::map<TString, std::vector<SampleHistPair> > SampleHistPairsByLegend;





namespace Tools{
    
    /// Associate different samples (and the associated histogram) by same legend entries
    SampleHistPairsByLegend associateSampleHistPairsByLegend(const std::vector<SampleHistPair>& v_sampleHistPair);
    
    
    
    /// Convert a channel from string to typedef
    Sample::Channel convertChannel(const std::string& channel);
    
    /// Convert a channel from typedef to string
    std::string convertChannel(const Sample::Channel& channel);
    
    /// Return the label of a channel as used for drawing
    std::string channelLabel(const Sample::Channel& channel);
    
    
    
    /// Convert a systematic from string to typedef
    Sample::Systematic convertSystematic(const std::string& systematic);
    
    /// Convert a systematic from typedef to string
    std::string convertSystematic(const Sample::Systematic& systematic);
    
    
    
    /// Assign an output folder depending on the channel
    TString assignFolder(const Sample::Channel& channel);
    
    
    
    /// Get the luminosity weight for a specific sample
    double luminosityWeight(const Sample& sample, const double luminosity, RootFileReader* fileReader);
}






#endif // Samples_h






