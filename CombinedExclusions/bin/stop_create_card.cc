#include <iostream>
#include <fstream>
#include <string>
#include "StopAnalysis/CombinedExclusions/interface/StopYields.h"
#include "StopAnalysis/CombinedExclusions/interface/SignalRegion.h"
#include "AnalysisTools/LanguageTools/interface/LanguageTools.h"
#include "AnalysisTools/RootTools/interface/RootTools.h"
#include <boost/program_options.hpp>

struct card_info_t
{
    card_info_t() {}
    std::string sr_name;
    unsigned int obs;
    float ttdil;
    float ttdil_unc;
    float ttslo;
    float ttslo_unc;
    float wjets;
    float wjets_unc;
    float rare;
    float rare_unc;
    float bkgd;
    float bkgd_unc;
    float acc;
    float trig_unc;
    float lep_unc;
    float isr_unc;
    float lumi_unc;
    float btag_unc;
    float jes_unc;
    float stat_unc;
    float total_unc;
};

void PrintCard(std::ostream &out, const card_info_t& info)
{
    // card string
//     const std::string card = Form("imax 1 number of search regions\n"
// "jmax 4  number of backgrounds ('*' = automatic)\n"
// "kmax 10 number of nuisance parameters (sources of systematical uncertainties)\n"
// "------------\n"
// "       bin      %s\n"
// "observation     %u\n"
// "------------\n"
// "bin                     %-12s%-12s%-12s%-12s%-12s\n"
// "process                 signal      ttdil       ttslo       wjets       rare  \n"
// "process                 0           1           2           3           4     \n"
// "rate                    %-6.3f      %-6.1f      %-6.1f      %-6.1f      %-6.1f\n"
// "### Error Matrix\n"                                                        
// "------------\n"                                                            
// "ttdil_unc        lnN    -           %1.3f       -           -           -     \n"
// "ttslo_unc        lnN    -           -           %1.3f       -           -     \n"
// "wjets_unc        lnN    -           -           -           %1.3f       -     \n"
// "rare_unc         lnN    -           -           -           -           %1.3f \n"
// "trig_unc         lnN    %1.3f       -           -           -           -     \n"
// "lep_unc          lnN    %1.3f       -           -           -           -     \n"
// "lumi_unc         lnN    %1.3f       -           -           -           -     \n"
// "isr_unc          lnN    %1.3f       -           -           -           -     \n"
// "btag_unc         lnN    %1.3f       -           -           -           -     \n"
// "jes_unc          lnN    %1.3f       -           -           -           -     \n"
//         , info.sr_name.c_str() 
//         , info.obs
//         , info.sr_name.c_str() 
//         , info.sr_name.c_str() 
//         , info.sr_name.c_str() 
//         , info.sr_name.c_str() 
//         , info.sr_name.c_str() 
//         , info.acc
//         , info.ttdil
//         , info.ttslo
//         , info.wjets
//         , info.rare
//         , info.ttdil_unc
//         , info.ttslo_unc
//         , info.wjets_unc
//         , info.rare_unc
//         , info.trig_unc
//         , info.lep_unc
//         , info.lumi_unc
//         , info.isr_unc
//         , info.btag_unc
//         , info.jes_unc
//     );

    const std::string card = Form("imax 1 number of search regions\n"
"jmax 1 number of backgrounds ('*' = automatic)\n"
"kmax 7 number of nuisance parameters (sources of systematical uncertainties)\n"
"------------\n"
"       bin      %s\n"
"observation     %u\n"
"------------\n"
"bin                     %-12s%-12s\n"
"process                 signal      bkgd  \n"
"process                 0           1     \n"
"rate                    %-6.3f      %-6.1f\n"
"### Error Matrix\n"                       
"------------\n"                           
"bkgd_unc         lnN    -           %1.3f \n"
"trig_unc         lnN    %1.3f       -     \n"
"lep_unc          lnN    %1.3f       -     \n"
"lumi_unc         lnN    %1.3f       -     \n"
"isr_unc          lnN    %1.3f       -     \n"
"btag_unc         lnN    %1.3f       -     \n"
"jes_unc          lnN    %1.3f       -     \n"
        , info.sr_name.c_str() 
        , info.obs
        , info.sr_name.c_str() 
        , info.sr_name.c_str() 
        , info.acc
        , info.bkgd
        , info.bkgd_unc
        , info.trig_unc
        , info.lep_unc
        , info.lumi_unc
        , info.isr_unc
        , info.btag_unc
        , info.jes_unc
    );

//     const std::string card = Form("imax 1 number of search regions\n"
// "jmax 1 number of backgrounds ('*' = automatic)\n"
// "kmax 2 number of nuisance parameters (sources of systematical uncertainties)\n"
// "------------\n"
// "       bin      %s\n"
// "observation     %u\n"
// "------------\n"
// "bin                     %-12s%-12s\n"
// "process                 signal      bkgd  \n"
// "process                 0           1     \n"
// "rate                    %-6.3f      %-6.1f\n"
// "### Error Matrix\n"                       
// "------------\n"                           
// "bkgd_unc         lnN    -           %1.3f \n"
// "signal_unc       lnN    %1.3f       -     \n"
//         , info.sr_name.c_str() 
//         , info.obs
//         , info.sr_name.c_str() 
//         , info.sr_name.c_str() 
//         , info.acc
//         , info.bkgd
//         , info.bkgd_unc
//         , info.total_unc
//     );

    // print it
    out << card << std::endl;

    // done
    return;
}

const float GetValueFromScanHist(TH1* const hist, const float mass_stop, const float mass_lsp)
{
    TH2* const h2 = dynamic_cast<TH2*>(hist);
    const float value = rt::GetBinContent2D(h2, mass_stop, mass_lsp);
    if (lt::is_zero(value))
    {
        return 1.0;
    }
    else
    {
        return value;
    }
}

// main program
int main(int argc, char* argv[])
try
{
    using namespace std;
//     using namespace stop;

    // inputs
    // -------------------------------------------------------------------------------------------------//

    std::string syst_file   = "";
    std::string output_file = "";
    int sr_num              = -1;
    double mass_stop        = -999999.0;
    double mass_lsp         = -999999.0;
    double lumi             = 19.9;
    bool verbose            = false;

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"      , "print this menu")
        ("syst"      , po::value<std::string>(&syst_file)->required(), "REQUIRED: file to get the signal yields and systematics")
        ("mass_stop" , po::value<double>(&mass_stop)->required()     , "REQUIRED: mass stop value"                              )
        ("mass_lsp"  , po::value<double>(&mass_lsp)->required()      , "REQUIRED: mass lsp value"                               )
        ("sr"        , po::value<int>(&sr_num)->required()           , "REQUIRED: SRs to run on"                                )
        ("output"    , po::value<std::string>(&output_file)          , "name of output file (blank = stdout)"                   )
        ("lumi"      , po::value<double>(&lumi)                      , "luminosity"                                             )
        ("verbose"   , po::value<bool>(&verbose)                     , "verbosity"                                              )
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
        cout << "output_file :\t" << output_file << endl;
        cout << "syst_file   :\t" << syst_file   << endl;
        cout << "sr          :\t" << sr_num      << endl;
        cout << "lumi        :\t" << lumi        << endl;
        cout << "verbose     :\t" << verbose     << endl;
        cout << "mass_stop   :\t" << mass_stop   << endl;
        cout << "mass_lsp    :\t" << mass_lsp    << endl;
    }

    // check that input file exists and is specified
    if (not syst_file.empty() and not lt::file_exists(syst_file))
    {
        cout << "[stop_create_card] ERROR: systematic histogram file " << syst_file << " not found" << endl;
        cout << desc << "\n";
        return 1;
    }

    // create the card
    // -------------------------------------------------------------------------------------------------//

    // extract data and background prediections
    const stop::SignalRegion::value_type signal_region = stop::GetSignalRegionFromName(Form("sr%d", sr_num));
    const stop::SignalRegionInfo signal_region_info    = stop::GetSignalRegionInfo(signal_region);
    const stop::Result& stop_result                    = stop::GetResult(signal_region);

    // open systematic file
    rt::TH1Container hc(syst_file);
    if (verbose)
    {
        hc.List();
    }

    // fill the card info
    card_info_t info;
    info.sr_name   = stop::GetSignalRegionInfo(signal_region).label;
    info.obs       = stop_result.data.lep.value;
    info.ttdil     = stop_result.ttdil.lep.value; 
    info.ttslo     = stop_result.ttslo.lep.value; 
    info.wjets     = stop_result.wjets.lep.value; 
    info.rare      = stop_result.rare.lep.value; 
    info.bkgd      = stop_result.bkgd.lep.value; 
    info.ttdil_unc = 1.0 + stop_result.ttdil.lep.frac_error(); 
    info.ttslo_unc = 1.0 + stop_result.ttslo.lep.frac_error(); 
    info.wjets_unc = 1.0 + stop_result.wjets.lep.frac_error(); 
    info.rare_unc  = 1.0 + stop_result.rare.lep.frac_error(); 
    info.bkgd_unc  = 1.0 + stop_result.bkgd.lep.frac_error(); 

    info.acc       = lumi*GetValueFromScanHist(hc["h_eff_"+signal_region_info.label], mass_stop, mass_lsp);
    info.trig_unc  = 1.030;
    info.lumi_unc  = 1.044;
    info.lep_unc   = 1.050;
    info.isr_unc   = 1.0 + GetValueFromScanHist(hc["h_err_noisr_"+signal_region_info.label], mass_stop, mass_lsp);
    info.btag_unc  = 1.0 + GetValueFromScanHist(hc["h_err_btag_" +signal_region_info.label], mass_stop, mass_lsp);
    info.jes_unc   = 1.0 + GetValueFromScanHist(hc["h_err_jes_"  +signal_region_info.label], mass_stop, mass_lsp);
    info.stat_unc  = 1.0 + GetValueFromScanHist(hc["h_err_stats_"+signal_region_info.label], mass_stop, mass_lsp);
    info.total_unc = 1.0 + GetValueFromScanHist(hc["h_err_total_"+signal_region_info.label], mass_stop, mass_lsp);

    // print the card
    if (output_file.empty())
    {
        PrintCard(std::cout, info);
    }
    else
    {
        lt::mkdir(lt::dirname(output_file), /*force=*/true);
        std::ofstream out(output_file.c_str(), std::ofstream::out);
        PrintCard(out, info);
        out.close();
    }

    // done
    return 0;
}
catch (std::exception& e)
{
    std::cerr << "[stop_interp_plots] Error: failed..." << std::endl;
    std::cerr << e.what() << std::endl;
    return 1;
}
