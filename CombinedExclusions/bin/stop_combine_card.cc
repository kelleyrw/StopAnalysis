#include <iostream>
#include <fstream>
#include <string>
#include "StopAnalysis/CombinedExclusions/interface/StopYields.h"
#include "StopAnalysis/CombinedExclusions/interface/SignalRegion.h"
#include "AnalysisTools/LanguageTools/interface/LanguageTools.h"
#include "AnalysisTools/RootTools/interface/RootTools.h"
#include <boost/program_options.hpp>


// main program
int main(int argc, char* argv[])
try
{
    using namespace std;
//     using namespace stop;

    // inputs
    // -------------------------------------------------------------------------------------------------//

    std::string syst_file    = "";
    std::string output_file  = "";
    std::string best_sr_file = "from_ben/exclusion2012_postLHCP_T2bwFixed/rootfiles/T2tt_combinePlots_BDT.root";
    std::string best_sr_hist = "hbest";
    double mass_stop         = -999999.0;
    double mass_lsp          = -999999.0;
    double lumi              = 19.5;
    unsigned short type      = 1;
    bool verbose             = false;

    const string type_desc = "1: The first type.";

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"        , "print this menu")
        ("syst"        , po::value<std::string>(&syst_file)->required(), "REQUIRED: file to get the signal yields and systematics")
        ("mass_stop"   , po::value<double>(&mass_stop)->required()     , "REQUIRED: mass stop value"                              )
        ("mass_lsp"    , po::value<double>(&mass_lsp)->required()      , "REQUIRED: mass lsp value"                               )
        ("best_sr_file", po::value<std::string>(&best_sr_file)         , "Best SRs file to run on"                                )
        ("best_sr_hist", po::value<std::string>(&best_sr_hist)         , "Best SRs histogram to run on"                           )
        ("type"        , po::value<unsigned short>(&type)              , Form("Type:\n%s", type_desc.c_str())                     )
        ("output"      , po::value<std::string>(&output_file)          , "name of output file (blank = stdout)"                   )
        ("lumi"        , po::value<double>(&lumi)                      , "luminosity"                                             )
        ("verbose"     , po::value<bool>(&verbose)                     , "verbosity"                                              )
        ;

    // parse it
    try
    {
        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);

        if (vm.count("help")) 
        {
            cout << desc << "\n";
            return 1;
        }

        po::notify(vm);
    }
    catch (const std::exception& e)
    {
        cerr << e.what() << "\nexiting" << endl;
        cout << desc << "\n";
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unknown error!" << "\n";
        return false;
    }

    if (verbose)
    {
        cout << "inputs:" << endl;
        cout << "output_file :\t" << output_file  << endl;
        cout << "syst_file   :\t" << syst_file    << endl;
        cout << "best_sr_file:\t" << best_sr_file << endl;
        cout << "best_sr_hist:\t" << best_sr_hist << endl;
        cout << "lumi        :\t" << lumi         << endl;
        cout << "verbose     :\t" << verbose      << endl;
        cout << "mass_stop   :\t" << mass_stop    << endl;
        cout << "mass_lsp    :\t" << mass_lsp     << endl;
    }

}
catch (std::exception& e)
{
    std::cerr << "[stop_interp_plots] Error: failed..." << std::endl;
    std::cerr << e.what() << std::endl;
    return 1;
}
