#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include "StopAnalysis/CombinedExclusions/interface/StopYields.h"
#include "StopAnalysis/CombinedExclusions/interface/SignalRegion.h"
#include "AnalysisTools/LanguageTools/interface/LanguageTools.h"
#include "AnalysisTools/RootTools/interface/RootTools.h"
#include <boost/program_options.hpp>
#include "TH2F.h"

struct stop_card_info_t
{
    stop_card_info_t() : sr_name("") {}
    std::string sr_name;
    unsigned int num_srs;
    unsigned int num_bkgds;
    unsigned int num_nuis;
    unsigned int obs;
    unsigned int ngen;
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

const float GetValueFromScanHist(TH1* const hist, const float mass_stop, const float mass_lsp)
{
    TH2* const h2 = dynamic_cast<TH2*>(hist);
    const float value = rt::GetBinContent2D(h2, mass_stop, mass_lsp);
    if (lt::is_zero(value))
    {
        return 0.0;
    }
    else
    {
        return value;
    }
}

std::vector<std::string> GetLineSplit(std::ifstream& in)
{
    // get a line from in
    std::string line;
    getline(in, line);

    // split it on the spaces
    std::vector<std::string> result = lt::string_split(line, " "); 

    // remove blank strings
    result.erase(std::remove(result.begin(), result.end(), ""), result.end());

    // done
    return result;
}


void PrintStopCard(std::ostream &out, const stop_card_info_t& info, const unsigned short type = 1)
{
    std::string card;
    switch (type)
    {
        case 1:
            // card string
            card = Form("imax %u number of search regions\n"
                    "jmax %u  number of backgrounds ('*' = automatic)\n"
                    "kmax %u number of nuisance parameters (sources of systematical uncertainties)\n"
                    "------------\n"
                    "       bin      %s\n"
                    "observation     %u\n"
                    "------------\n"
                    "bin                     %-12s%-12s%-12s%-12s%-12s\n"
                    "process                 signal      ttdil       ttslo       wjets       rare  \n"
                    "process                 0           1           2           3           4     \n"
                    "rate                    %-12.4e%-6.1f      %-6.1f      %-6.1f      %-6.1f\n"
                    "### Error Matrix\n"                                                        
                    "------------\n"                                                            
                    "ttdil            lnN    -           %1.3f       -           -           -     \n"
                    "ttslo            lnN    -           -           %1.3f       -           -     \n"
                    "wjets            lnN    -           -           -           %1.3f       -     \n"
                    "rare             lnN    -           -           -           -           %1.3f \n"
                    "trigger          lnN    %1.3f       -           -           -           -     \n"
                    "lep              lnN    %1.3f       -           -           -           -     \n"
                    "lumi             lnN    %1.3f       -           -           -           -     \n"
                    "Isr              lnN    %1.3f       -           -           -           -     \n"
                    "Btag             lnN    %1.3f       -           -           -           -     \n"
                    "Jes              lnN    %1.3f       -           -           -           -     \n"
                    , info.num_srs
                    , info.num_bkgds
                    , info.num_nuis
                    , info.sr_name.c_str() 
                    , info.obs
                    , info.sr_name.c_str() 
                    , info.sr_name.c_str() 
                    , info.sr_name.c_str() 
                    , info.sr_name.c_str() 
                    , info.sr_name.c_str() 
                    , (lt::is_zero(info.acc) ? 1.0/static_cast<float>(info.ngen) : info.acc)
                    , info.ttdil
                    , info.ttslo
                    , info.wjets
                    , info.rare
                    , info.ttdil_unc
                    , info.ttslo_unc
                    , info.wjets_unc
                    , info.rare_unc
                    , info.trig_unc
                    , info.lep_unc
                    , info.lumi_unc
                    , info.isr_unc
                    , info.btag_unc
                    , info.jes_unc
                    );
            break;
        default:
            throw std::runtime_error("[PrintStopCard] Error: method not supported");
    }

    // print it
    out << card;

    // done
    return;
}

// This is hard coded and assumes the format produced using method 1 from
// https://github.com/kelleyrw/StopAnalysis/blob/master/CombinedExclusions/bin/stop_create_card.cc
stop_card_info_t ParseStopCard(const std::string& stop_card_filename)
{
// 1  imax 1 number of search regions
// 2  jmax 4  number of backgrounds ('*' = automatic)
// 3  kmax 10 number of nuisance parameters (sources of systematical uncertainties)
// 4  ------------
// 5         bin      bdt4
// 6  observation     2
// 7  ------------
// 8  bin                     bdt4        bdt4        bdt4        bdt4        bdt4        
// 9  process                 signal      ttdil       ttslo       wjets       rare  
// 10 process                 0           1           2           3           4     
// 11 rate                    4.0001e-01  0.3         0.8         0.8         1.0   
// 12 ### Error Matrix
// 13 ------------
// 14 ttdil            lnN    -           2.000       -           -           -     
// 15 ttslo            lnN    -           -           2.125       -           -     
// 16 wjets            lnN    -           -           -           1.375       -     
// 17 rare             lnN    -           -           -           -           1.500 
// 18 trigger          lnN    1.030       -           -           -           -     
// 19 lep              lnN    1.050       -           -           -           -     
// 20 lumi             lnN    1.044       -           -           -           -     
// 21 Isr              lnN    1.060       -           -           -           -     
// 22 Btag             lnN    1.022       -           -           -           -     
// 23 Jes              lnN    1.042       -           -           -           -   

    std::ifstream fin;
    fin.open(stop_card_filename.c_str(), std::ifstream::in);
    if (!fin.is_open())
    {
        throw std::runtime_error(Form("[ParseStopCard] file %s not found", stop_card_filename.c_str()));
    }
    using namespace std;

    stop_card_info_t info;
    std::string line; 
    std::vector<std::string> line_split; 

    // lines 1-3
    line_split = GetLineSplit(fin); info.num_srs   = boost::lexical_cast<unsigned int>(line_split[1]);
    line_split = GetLineSplit(fin); info.num_bkgds = boost::lexical_cast<unsigned int>(line_split[1]);
    line_split = GetLineSplit(fin); info.num_nuis  = boost::lexical_cast<unsigned int>(line_split[1]);

    // lines 4-7
    getline(fin, line); // skip
    line_split = GetLineSplit(fin); info.sr_name = line_split[1];
    line_split = GetLineSplit(fin); info.obs     = boost::lexical_cast<unsigned int>(line_split[1]);
    getline(fin, line); // skip

    // lines 8-11
    getline(fin, line); // skip
    getline(fin, line); // skip
    getline(fin, line); // skip
    line_split     = GetLineSplit(fin);
    info.acc       = boost::lexical_cast<float>(line_split[1]);
    info.ttdil     = boost::lexical_cast<float>(line_split[2]);
    info.ttslo     = boost::lexical_cast<float>(line_split[3]);
    info.wjets     = boost::lexical_cast<float>(line_split[4]);
    info.rare      = boost::lexical_cast<float>(line_split[5]);

    // lines 12-17
    getline(fin, line); // skip
    getline(fin, line); // skip
    line_split = GetLineSplit(fin); info.ttdil_unc = boost::lexical_cast<float>(line_split[3]);
    line_split = GetLineSplit(fin); info.ttslo_unc = boost::lexical_cast<float>(line_split[4]);
    line_split = GetLineSplit(fin); info.wjets_unc = boost::lexical_cast<float>(line_split[5]);
    line_split = GetLineSplit(fin); info.rare_unc  = boost::lexical_cast<float>(line_split[6]);

    // lines 18-23
    line_split = GetLineSplit(fin); info.trig_unc = boost::lexical_cast<float>(line_split[2]);
    line_split = GetLineSplit(fin); info.lep_unc  = boost::lexical_cast<float>(line_split[2]);
    line_split = GetLineSplit(fin); info.lumi_unc = boost::lexical_cast<float>(line_split[2]);
    line_split = GetLineSplit(fin); info.isr_unc  = boost::lexical_cast<float>(line_split[2]);
    line_split = GetLineSplit(fin); info.btag_unc = boost::lexical_cast<float>(line_split[2]);
    line_split = GetLineSplit(fin); info.jes_unc  = boost::lexical_cast<float>(line_split[2]);

//     std::copy(line_split.begin(), line_split.end(), std::ostream_iterator<std::string>(std::cout, ","));

    return info;
}

struct razor_card_info_t
{
    razor_card_info_t() {}
    unsigned int num_srs;
    unsigned int num_bkgds;
    unsigned int num_nuis;
    unsigned int obs_mj;
    unsigned int obs_j2;
    float acc_mj;
    float acc_j2;
    float mj_ttj3b;
    float mj_tt1jb;
    float mj_ttj2b;
    float j2_ttj2b;
    float j2_ttj3b;
    float btag_unc;
    float isr_unc;
    float jes_unc;
    float pdf_unc;
    float lumi_unc;
    float trig_unc;
};

void PrintRazorCard(std::ostream &out, const razor_card_info_t& info, const unsigned short type = 1)
{
    // card string
    const std::string card = Form("Combination of MultiJet=razor_combine_MultiJet_T2tt_MG_725.000000_MCHI_25.000000.txt  Jet2b=razor_combine_Jet2b_T2tt_MG_725.000000_MCHI_25.000000.txt\n"
        "imax %u number of bins\n"
        "jmax %u number of processes minus 1\n"
        "kmax %u number of nuisance parameters\n"
        "----------------------------------------------------------------------------------------------------------------------------------\n"
        "shapes *         Jet2b     razor_combine_Jet2b_T2tt_MG_725.000000_MCHI_25.000000.root wJet2b:$PROCESS wJet2b:$PROCESS_$SYSTEMATIC\n"
        "shapes *         MultiJet  razor_combine_MultiJet_T2tt_MG_725.000000_MCHI_25.000000.root wMultiJet:$PROCESS wMultiJet:$PROCESS_$SYSTEMATIC\n"
        "----------------------------------------------------------------------------------------------------------------------------------\n"
        "bin          MultiJet  Jet2b\n"
        "observation  %-11u%-11u\n"
        "----------------------------------------------------------------------------------------------------------------------------------\n"
        "bin                               MultiJet        MultiJet        MultiJet        MultiJet        Jet2b           Jet2b           Jet2b         \n"
        "process                           MultiJet_T2tt   MultiJet_TTj3b  MultiJet_TTj1b  MultiJet_TTj2b  Jet2b_T2tt      Jet2b_TTj2b     Jet2b_TTj3b   \n"
        "process                           -1              1               2               3               0               4               5             \n"
        "rate                              %-16.4f%-16.4f%-16.4f%-16.4f%-16.4f%-16.4f%-16.4f\n"
        "----------------------------------------------------------------------------------------------------------------------------------\n"
        "Btag                    shape     %-6.1f             -               -               -             %-6.1f             -               -           \n"
        "Isr                     shape     %-6.1f             -               -               -             %-6.1f             -               -           \n"
        "Jes                     shape     %-6.1f             -               -               -             %-6.1f             -               -           \n"
        "Pdf                     shape     %-6.1f             -               -               -             %-6.1f             -               -           \n"
        "lumi                    lnN       %-6.3f           1.0             1.0             1.0             %-6.3f           1.0             1.0           \n"
        "trigger                 lnN       %-6.3f           1.0             1.0             1.0             %-6.3f           1.0             1.0           \n"
        "n_TTj1b_MultiJet      flatParam \n"
        "MR0_TTj1b_MultiJet    flatParam \n"
        "b_TTj2b_MultiJet      flatParam \n"
        "MR0_TTj2b_MultiJet    flatParam \n"
        "MultiJet_TTj3b_norm   flatParam \n"
        "MultiJet_TTj2b_norm   flatParam \n"
        "n_TTj2b_Jet2b         flatParam \n"
        "Jet2b_TTj3b_norm      flatParam \n"
        "R0_TTj2b_Jet2b        flatParam \n"
        "b_TTj2b_Jet2b         flatParam \n"
        "R0_TTj2b_MultiJet     flatParam \n"
        "MR0_TTj2b_Jet2b       flatParam \n"
        "MultiJet_TTj1b_norm   flatParam \n"
        "R0_TTj1b_MultiJet     flatParam \n"
        "Jet2b_TTj2b_norm      flatParam \n"
        "n_TTj2b_MultiJet      flatParam \n"
        "b_TTj1b_MultiJet      flatParam \n"
        , info.num_srs
        , info.num_bkgds
        , info.num_nuis
        , info.obs_mj
        , info.obs_j2
        , info.acc_mj
        , info.mj_ttj3b
        , info.mj_tt1jb
        , info.mj_ttj2b
        , info.acc_j2
        , info.j2_ttj2b
        , info.j2_ttj3b
        , info.btag_unc
        , info.btag_unc
        , info.isr_unc
        , info.isr_unc
        , info.jes_unc
        , info.jes_unc
        , info.pdf_unc
        , info.pdf_unc
        , info.lumi_unc
        , info.lumi_unc
        , info.trig_unc
        , info.trig_unc
    );

    // print it
    out << card;

    // done
    return;
}

// This is hard coded and assumes the format produced using method 1 from
// https://github.com/kelleyrw/StopAnalysis/blob/master/CombinedExclusions/bin/stop_create_card.cc
razor_card_info_t ParseRazorCard(const std::string& razor_card_filename)
{
// 1  Combination of MultiJet=razor_combine_MultiJet_T2tt_MG_725.000000_MCHI_25.000000.txt  Jet2b=razor_combine_Jet2b_T2tt_MG_725.000000_MCHI_25.000000.txt
// 2  imax 2 number of bins
// 3  jmax 6 number of processes minus 1
// 4  kmax 6 number of nuisance parameters
// 5  ----------------------------------------------------------------------------------------------------------------------------------
// 6  shapes *         Jet2b     razor_combine_Jet2b_T2tt_MG_725.000000_MCHI_25.000000.root wJet2b:$PROCESS wJet2b:$PROCESS_$SYSTEMATIC
// 7  shapes *         MultiJet  razor_combine_MultiJet_T2tt_MG_725.000000_MCHI_25.000000.root wMultiJet:$PROCESS wMultiJet:$PROCESS_$SYSTEMATIC
// 8  ----------------------------------------------------------------------------------------------------------------------------------
// 9  bin          MultiJet  Jet2b   
// 10 observation  2589.0    728.0   
// 11 ----------------------------------------------------------------------------------------------------------------------------------
// 12 bin                               MultiJet        MultiJet        MultiJet        MultiJet        Jet2b           Jet2b           Jet2b         
// 13 process                           MultiJet_T2tt   MultiJet_TTj3b  MultiJet_TTj1b  MultiJet_TTj2b  Jet2b_T2tt      Jet2b_TTj2b     Jet2b_TTj3b   
// 14 process                           -1              1               2               3               0               4               5             
// 15 rate                              24.7600         85.0150         1754.9450       833.9740        2.5870          726.7210        24.8270       
// 16 ----------------------------------------------------------------------------------------------------------------------------------
// 17 Btag                    shape     1.0             -               -               -               1.0             -               -             
// 18 Isr                     shape     1.0             -               -               -               1.0             -               -             
// 19 Jes                     shape     1.0             -               -               -               1.0             -               -             
// 20 Pdf                     shape     1.0             -               -               -               1.0             -               -             
// 21 lumi                    lnN       1.026           1.0             1.0             1.0             1.026           1.0             1.0           
// 22 trigger                 lnN       1.05            1.0             1.0             1.0             1.05            1.0             1.0           
// 23 n_TTj1b_MultiJet      flatParam 
// 24 MR0_TTj1b_MultiJet    flatParam 
// 25 b_TTj2b_MultiJet      flatParam 
// 26 MR0_TTj2b_MultiJet    flatParam 
// 27 MultiJet_TTj3b_norm   flatParam 
// 28 MultiJet_TTj2b_norm   flatParam 
// 29 n_TTj2b_Jet2b         flatParam 
// 30 Jet2b_TTj3b_norm      flatParam 
// 31 R0_TTj2b_Jet2b        flatParam 
// 32 b_TTj2b_Jet2b         flatParam 
// 33 R0_TTj2b_MultiJet     flatParam 
// 34 MR0_TTj2b_Jet2b       flatParam 
// 35 MultiJet_TTj1b_norm   flatParam 
// 36 R0_TTj1b_MultiJet     flatParam 
// 38 Jet2b_TTj2b_norm      flatParam 
// 39 n_TTj2b_MultiJet      flatParam 
// 40 b_TTj1b_MultiJet      flatParam 
   
    std::ifstream fin;
    fin.open(razor_card_filename.c_str(), std::ifstream::in);
    if (!fin.is_open())
    {
        throw std::runtime_error(Form("[ParseRazorCard] file %s not found", razor_card_filename.c_str()));
    }
    using namespace std;

    razor_card_info_t info;
    std::string line; 
    std::vector<std::string> line_split; 

    // lines 1-9
    getline(fin, line); // skip
    line_split = GetLineSplit(fin); info.num_srs   = boost::lexical_cast<unsigned int>(line_split[1]);
    line_split = GetLineSplit(fin); info.num_bkgds = boost::lexical_cast<unsigned int>(line_split[1]);
    line_split = GetLineSplit(fin); info.num_nuis  = boost::lexical_cast<unsigned int>(line_split[1]);
    getline(fin, line); // skip
    getline(fin, line); // skip
    getline(fin, line); // skip
    getline(fin, line); // skip
    getline(fin, line); // skip

    // lines 10 
    line_split = GetLineSplit(fin);
    info.obs_mj = static_cast<unsigned int>(boost::lexical_cast<float>(line_split[1]));
    info.obs_j2 = static_cast<unsigned int>(boost::lexical_cast<float>(line_split[2]));

    // lines 11-16
    getline(fin, line); // skip
    getline(fin, line); // skip
    getline(fin, line); // skip
    getline(fin, line); // skip
    line_split    = GetLineSplit(fin);
    info.acc_mj   = boost::lexical_cast<float>(line_split[1]);
    info.mj_ttj3b = boost::lexical_cast<float>(line_split[2]);
    info.mj_tt1jb = boost::lexical_cast<float>(line_split[3]);
    info.mj_ttj2b = boost::lexical_cast<float>(line_split[4]);
    info.acc_j2   = boost::lexical_cast<float>(line_split[5]);
    info.j2_ttj2b = boost::lexical_cast<float>(line_split[6]);
    info.j2_ttj3b = boost::lexical_cast<float>(line_split[7]);
    getline(fin, line); // skip

    // lines 17-40
    line_split = GetLineSplit(fin); info.btag_unc = boost::lexical_cast<float>(line_split[2]);
    line_split = GetLineSplit(fin); info.isr_unc  = boost::lexical_cast<float>(line_split[2]);
    line_split = GetLineSplit(fin); info.jes_unc  = boost::lexical_cast<float>(line_split[2]);
    line_split = GetLineSplit(fin); info.pdf_unc  = boost::lexical_cast<float>(line_split[2]);
    line_split = GetLineSplit(fin); info.lumi_unc = boost::lexical_cast<float>(line_split[2]);
    line_split = GetLineSplit(fin); info.trig_unc = boost::lexical_cast<float>(line_split[2]);
    getline(fin, line); // skip
    getline(fin, line); // skip
    getline(fin, line); // skip
    getline(fin, line); // skip
    getline(fin, line); // skip
    getline(fin, line); // skip
    getline(fin, line); // skip
    getline(fin, line); // skip
    getline(fin, line); // skip
    getline(fin, line); // skip
    getline(fin, line); // skip
    getline(fin, line); // skip
    getline(fin, line); // skip
    getline(fin, line); // skip
    getline(fin, line); // skip
    getline(fin, line); // skip
    getline(fin, line); // skip
    getline(fin, line); // skip

//  std::copy(line_split.begin(), line_split.end(), std::ostream_iterator<std::string>(std::cout, ",")); std::cout << std::endl;

    return info;
}

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

    // check that input file exists and is specified
    if (not syst_file.empty() and not lt::file_exists(syst_file))
    {
        cout << "[stop_combine_card] ERROR: systematic histogram file " << syst_file << " not found" << endl;
        cout << desc << "\n";
        return 1;
    }

    // check that best SR file exists and is specified
    if (not best_sr_file.empty() and not lt::file_exists(best_sr_file))
    {
        cout << "[stop_combine_card] ERROR: best SR histogram file " << best_sr_file << " not found" << endl;
        cout << desc << "\n";
        return 1;
    }

    // Get information from STOP analysis 
    // -------------------------------------------------------------------------------------------------//

//     stop_card_info_t stop_info = ParseStopCard("cards/t2tt_method1/t2tt_725_25_bdt4.txt");
//     PrintStopCard(std::cout, stop_info, type);

    razor_card_info_t stop_info = ParseRazorCard("/Users/rwk7t/Development/CMSSW_6_1_2_Analysis/src/RazorCMS/RazorCombinedFit/cards/razor_combine_Had_T2tt_MG_725.000000_MCHI_25.000000.txt");
    PrintRazorCard(std::cout, stop_info, type);

//     // extract the best signal region 
//     TH2F* const h_best_sr                              = rt::GetHistFromRootFile<TH2F>(best_sr_file, best_sr_hist);
//     const int sr_num                                   = rt::GetBinContent2D(h_best_sr, mass_stop, mass_lsp);
//     delete h_best_sr;
//     const stop::SignalRegion::value_type signal_region = stop::GetSignalRegionFromName(Form("sr%d", sr_num));
//     const stop::SignalRegionInfo signal_region_info    = stop::GetSignalRegionInfo(signal_region);
//     const stop::Result& stop_result                    = stop::GetResult(signal_region);

//     // open systematic file
//     rt::TH1Container hc(syst_file);
//     if (verbose)
//     {
//         hc.List();
//     }
//     
//     // fill the card info
//     stop_card_info_t info;
//     info.sr_name   = stop::GetSignalRegionInfo(signal_region).label;
//     info.obs       = stop_result.data.lep.value;
//     info.ttdil     = stop_result.ttdil.lep.value; 
//     info.ttslo     = stop_result.ttslo.lep.value; 
//     info.wjets     = stop_result.wjets.lep.value; 
//     info.rare      = stop_result.rare.lep.value; 
//     info.bkgd      = stop_result.bkgd.lep.value; 
//     info.ttdil_unc = 1.0 + stop_result.ttdil.lep.frac_error(); 
//     info.ttslo_unc = 1.0 + stop_result.ttslo.lep.frac_error(); 
//     info.wjets_unc = 1.0 + stop_result.wjets.lep.frac_error(); 
//     info.rare_unc  = 1.0 + stop_result.rare.lep.frac_error(); 
//     info.bkgd_unc  = 1.0 + stop_result.bkgd.lep.frac_error(); 
// 
//     info.acc       = lumi*GetValueFromScanHist(hc["h_eff_"+signal_region_info.label], mass_stop, mass_lsp);
//     info.ngen      = GetValueFromScanHist(hc["h_ngen"], mass_stop, mass_lsp);
//     info.trig_unc  = 1.030;
//     info.lumi_unc  = 1.044;
//     info.lep_unc   = 1.050;
//     info.isr_unc   = 1.0 + GetValueFromScanHist(hc["h_err_noisr_"+signal_region_info.label], mass_stop, mass_lsp);
//     info.btag_unc  = 1.0 + GetValueFromScanHist(hc["h_err_btag_" +signal_region_info.label], mass_stop, mass_lsp);
//     info.jes_unc   = 1.0 + GetValueFromScanHist(hc["h_err_jes_"  +signal_region_info.label], mass_stop, mass_lsp);
//     info.stat_unc  = 1.0 + GetValueFromScanHist(hc["h_err_stats_"+signal_region_info.label], mass_stop, mass_lsp);
//     info.total_unc = 1.0 + GetValueFromScanHist(hc["h_err_total_"+signal_region_info.label], mass_stop, mass_lsp);
// 
//     // print the card
//     // -------------------------------------------------------------------------------------------------//
// 
//     if (output_file.empty())
//     {
//         PrintStopCard(std::cout, info, type);
//     }
//     else
//     {
//         lt::mkdir(lt::dirname(output_file), /*force=*/true);
//         std::ofstream out(output_file.c_str(), std::ofstream::out);
//         PrintStopCard(out, info, type);
//         out.close();
//     }

    // done
    return 0;
}
catch (std::exception& e)
{
    std::cerr << "[stop_interp_plots] Error: failed..." << std::endl;
    std::cerr << e.what() << std::endl;
    return 1;
}
