#include "AnalysisTools/LanguageTools/interface/LanguageTools.h"
#include "fitRvsCLs.C"
/* #include "/usr/local/lands/03.06.07/test/fitRvsCLs.C" */
//#include "/home/users/rwkelley/code/LandS/03.06.07/test/fitRvsCLs.C"

void RunLimitsWrapper(const std::string& input_file_name)
{
    const std::string plot_file_name  = lt::dirname(input_file_name) + "/plots_" + lt::basename(input_file_name);
    const std::string bands_file_name = lt::dirname(input_file_name) + "/bands_" + lt::basename(input_file_name);
    run(input_file_name.c_str(), plot_file_name.c_str(), bands_file_name.c_str());
}
