#include "fitRvsCLs.C"

std::string remove_root_ext(const std::string& str)
{
    unsigned pos = str.find(".root"); 
    return str.substr(0, pos);
}

void RunLimitsWrapper(const std::string& input_file_name)
{
    const std::string plot_file_name  = remove_root_ext("plots_" + input_file_name);
    const std::string bands_file_name = remove_root_ext("bands_" + input_file_name);
    run(input_file_name.c_str(), plot_file_name.c_str(), bands_file_name.c_str());
}
