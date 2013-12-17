#ifndef STOP_ANALYSISTYPE_H
#define STOP_ANALYSISTYPE_H

#include <string>

class TTree;

namespace stop
{
    struct AnalysisType
    {
        enum value_type
        {
            bdt,
            cut, // place holder --> not used
            static_size
        };
    };

    // Signal Region Infomation
    struct AnalysisTypeInfo
    {
        std::string name;  // short name
        std::string title; // ROOT TLatex title
        std::string latex; // real latex title
    };

    // Get the AnalysisType from a string
    AnalysisType::value_type GetAnalysisTypeFromName(const std::string& analysis_type_name);

    // Get the info for the Signal region
    AnalysisTypeInfo GetAnalysisTypeInfo(const AnalysisType::value_type& analysis_type);
    AnalysisTypeInfo GetAnalysisTypeInfo(const std::string& analysis_type_name);

} // namespace stop

#endif // STOP_ANALYSISTYPE_H
