#ifndef STOP_SIGNALREGIONS_H
#define STOP_SIGNALREGIONS_H

#include <string>
#include "StopAnalysis/CombinedExclusions/interface/AnalysisType.h"

namespace stop
{
    struct SignalRegion
    {
        enum value_type
        {
            // generic names --> specific names are in SignalRegions.cc 
            sr0  = 0, 
            sr1  = 1, 
            sr2  = 2, 
            sr3  = 3, 
            sr4  = 4, 
            sr5  = 5, 
            sr6  = 6, 

            // keep track of the size
            static_size
        };
    };

    // Signal Region Information
    struct SignalRegionInfo
    {
        std::string name;  // short name
        std::string label; // label
        std::string title; // ROOT TLatex title
        std::string latex; // real latex title
    };
    
    // Get the SignalRegion from a string
    SignalRegion::value_type GetSignalRegionFromName
    (
        const std::string& signal_region_name,
        const std::string& analysis_type_name = "bdt"
    );
    
    // Get the SignalRegion from a string
    SignalRegion::value_type GetSignalRegionFromNumber
    (
        const unsigned int signal_region_number,
        const std::string& analysis_type_name = "bdt"
    );
    
    // Get the info for the Signal region
    SignalRegionInfo GetSignalRegionInfo
    (
        const SignalRegion::value_type& signal_region,
        const AnalysisType::value_type& anal_type = AnalysisType::bdt
    );
    
    SignalRegionInfo GetSignalRegionInfo
    (
        const std::string& signal_region_name,
        const std::string& analysis_type_name = "bdt"
    );
    
} // namespace stop

#endif // SIGNALREGIONS_H
