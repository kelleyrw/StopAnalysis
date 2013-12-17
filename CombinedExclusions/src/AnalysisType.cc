#include "StopAnalysis/CombinedExclusions/interface/AnalysisType.h"
#include "TTree.h"
#include <stdexcept>

namespace stop
{
    static const AnalysisTypeInfo s_AnalysisTypeInfos[AnalysisType::static_size] = 
    {
        // name, title       , latex
        {"bdt" , "BDT"       , "BDT"      }, // BDT
        {"cut" , "Cut Based" , "Cut Based"}  // cut based (place holder --> not used)
    };

    // wrapper function to get the AnalysisTypeInfo
    AnalysisType::value_type GetAnalysisTypeFromName(const std::string& analysis_type_name)
    {
        using namespace std;
        AnalysisType::value_type analysis_type = AnalysisType::static_size;
        for (size_t i = 0; i != AnalysisType::static_size; i++)
        {
            if (string(s_AnalysisTypeInfos[i].name) == analysis_type_name)
            {
                analysis_type = static_cast<AnalysisType::value_type>(i);
                break;
            }
        }

        // throw if not found
        if (analysis_type == AnalysisType::static_size)
        {
            throw std::domain_error("[stop::GetAnalysisTypeInfo] ERROR: analysis_type not found!");
        }

        return analysis_type; 
    }

    // wrapper function to get the AnalysisTypeInfo
    AnalysisTypeInfo GetAnalysisTypeInfo(const AnalysisType::value_type& analysis_type)
    {
        return s_AnalysisTypeInfos[analysis_type]; 
    }

    AnalysisTypeInfo GetAnalysisTypeInfo(const std::string& analysis_type_name)
    {
        AnalysisType::value_type analysis_type = GetAnalysisTypeFromName(analysis_type_name); 
        return GetAnalysisTypeInfo(analysis_type); 
    }

    AnalysisTypeInfo GetAnalysisTypeInfo(unsigned int analysis_type_number)
    {
        AnalysisType::value_type analysis_type = static_cast<AnalysisType::value_type>(analysis_type_number); 
        return GetAnalysisTypeInfo(analysis_type); 
    }

} // namespace stop
