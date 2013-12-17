#include "StopAnalysis/CombinedExclusions/interface/SignalRegion.h"
#include "TString.h" 
#include <stdexcept>

namespace stop
{
    // hold the information for the signal regions 
    static const SignalRegionInfo s_SignalRegionInfos[AnalysisType::static_size][SignalRegion::static_size] =
    {
        {   // BDT signal regions infos
            // name label    title         latex  
            {"sr0" , "pres"  , "Preselection" , "Preselection"}, 
            {"sr1" , "bdt1l" , "BDT1 Loose"   , "BDT1 Loose"  }, 
            {"sr2" , "bdt1t" , "BDT1 Tight"   , "BDT1 Tight"  }, 
            {"sr3" , "bdt2"  , "BDT2"         , "BDT2"        }, 
            {"sr4" , "bdt3"  , "BDT3"         , "BDT3"        }, 
            {"sr5" , "bdt4"  , "BDT4"         , "BDT4"        }, 
            {"sr6" , "bdt5"  , "BDT5"         , "BDT5"        }
        },
        {   // cut-based signal regions infos (place holder -- not used)
            // name label  title       latex  
            {"sr0", "sr0", "not used", "not used"},
            {"sr1", "sr1", "not used", "not used"},
            {"sr2", "sr2", "not used", "not used"},
            {"sr3", "sr3", "not used", "not used"},
            {"sr4", "sr4", "not used", "not used"},
            {"sr5", "sr5", "not used", "not used"},
            {"sr6", "sr6", "not used", "not used"}
        }
    };

    // wrapper function to get the SignalRegionInfo
    SignalRegion::value_type GetSignalRegionFromName
    (
        const std::string& signal_region_name,
        const std::string& analysis_type_name
    )
    {
        const AnalysisType::value_type analysis_type = GetAnalysisTypeFromName(analysis_type_name); 
        SignalRegion::value_type signal_region       = SignalRegion::static_size;
        for (size_t i = 0; i != SignalRegion::static_size; i++)
        {
            if (std::string(s_SignalRegionInfos[analysis_type][i].name) == signal_region_name)
            {
                signal_region = static_cast<SignalRegion::value_type>(i);
                break;
            }
        }
    
        // throw if not found
        if (signal_region == SignalRegion::static_size)
        {
            throw std::domain_error(Form("[stop::GetSignalRegionFromName] ERROR: signal_region %s not found!", signal_region_name.c_str()));
        }
    
        return signal_region; 
    }

    // wrapper function to get the SignalRegionInfo
    SignalRegionInfo GetSignalRegionInfo
    (
        const SignalRegion::value_type& signal_region,
        const AnalysisType::value_type& analysis_type
    )
    {
        // edge cases 
        if (signal_region == SignalRegion::static_size)
        {
            throw std::domain_error("[stop::GetSignalRegionInfo] ERROR: signal_region not found!");
        }
        if (analysis_type == AnalysisType::static_size)
        {
            throw std::domain_error("[stop::GetSignalRegionInfo] ERROR: analysis_type not found!");
        }

        return s_SignalRegionInfos[analysis_type][signal_region];
    }

    // Get the SignalRegionType from a string
    SignalRegionInfo GetSignalRegionInfo
    (
        const std::string& signal_region_name,
        const std::string& analysis_type_name
    )
    {
        const AnalysisType::value_type analysis_type = GetAnalysisTypeFromName(analysis_type_name); 
        const SignalRegion::value_type signal_region = GetSignalRegionFromName(signal_region_name, analysis_type_name); 
        return GetSignalRegionInfo(signal_region, analysis_type); 
    }

} // namespace stop
