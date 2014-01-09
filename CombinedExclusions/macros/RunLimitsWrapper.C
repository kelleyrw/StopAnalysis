#include "AnalysisTools/LanguageTools/interface/LanguageTools.h"
#include "fitRvsCLs.C"

void RunLimitsWrapper(const std::string& input_file_name)
{
    const std::string plot_file_name  = lt::dirname(input_file_name) + "/plots_" + lt::basename(input_file_name);
    const std::string bands_file_name = lt::dirname(input_file_name) + "/bands_" + lt::basename(input_file_name);
    run(input_file_name.c_str(), plot_file_name.c_str(), bands_file_name.c_str());
}
