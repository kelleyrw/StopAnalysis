#ifndef STOP_SAMPLE_H
#define STOP_SAMPLE_H

#include <string>

class TChain;
class TH2F;

namespace stop
{
    // list of available samples
    struct Sample
    {
        enum value_type
        {
            t2tt,
            static_size
        };
    };

    // Sample Infomation
    struct SampleInfo
    {
        std::string name;           // short name
        std::string title;          // ROOT TLatex title
        std::string latex;          // real latex title
        std::string ntuple_path;    // logical name for path
        std::string ngen_file;      // path to "number generated" file 
        std::string ngen_hist_name; // name of the "number generated" histogram 
        Sample::value_type sample;  // redundant process enum
    };

    // Get the Sample from a string
    Sample::value_type GetSampleFromName(const std::string& sample_name);

    // test if a string is on of the samples
    bool IsSample(const std::string& sample_name);

    // wrapper function to get the SampleInfo
    SampleInfo GetSampleInfo(const Sample::value_type& sample);
    SampleInfo GetSampleInfo(const std::string& sample_name);

    // get the chain from the Sample
    // NOTE: user in charge of deleting the TChain*
    TChain* GetSampleTChain(const Sample::value_type& sample); 

    // get the ngen histogram from the Sample
    // NOTE: user in charge of deleting the TH2*
    TH2F* GetSampleNGenHist(const Sample::value_type& sample);

} // namespace stop

#endif // STOP_SAMPLE_H
