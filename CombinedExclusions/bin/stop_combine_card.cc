#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include "AnalysisTools/LanguageTools/interface/LanguageTools.h"
#include "AnalysisTools/RootTools/interface/RootTools.h"
#include <boost/program_options.hpp>

// heper functions 
// -------------------------------------------------------------------------------------------------//

// get line from the file and stip the extra whitespace
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

// Stop result helper classes and function
// -------------------------------------------------------------------------------------------------//

// class to hold the stop result data
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

// print the stop card in its original format
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

// parse the stop card in its original format
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

    // done
    return info;
}

// Razor result helper classes and function
// -------------------------------------------------------------------------------------------------//

// class to hold the razor result data
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

// print the razor card in its original format
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

// print the razor card in its original format
// This is hard coded and assumes the format produced by Javier 
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

    // done
    return info;
}

// print the combined card
// -------------------------------------------------------------------------------------------------//

void PrintCombinedCard(std::ostream &out, const stop_card_info_t& stop_info, const razor_card_info_t& razor_info)
{
    // card string
    const std::string card = Form(
        "imax %u number of bins\n"
        "jmax %u number of processeses - 1\n"
        "kmax %u number of nuisance parameters\n"
        "------------------------------------------------------------------------------------------------------------------------------------------\n"
        "shapes *         Jet2b     razor_combine_Jet2b_T2tt_MG_725.000000_MCHI_25.000000.root wJet2b:$PROCESS wJet2b:$PROCESS_$SYSTEMATIC\n"
        "shapes *         MultiJet  razor_combine_MultiJet_T2tt_MG_725.000000_MCHI_25.000000.root wMultiJet:$PROCESS wMultiJet:$PROCESS_$SYSTEMATIC\n"
        "------------------------------------------------------------------------------------------------------------------------------------------\n"
        "bin          MultiJet  Jet2b     STOP    \n"
        "observation  %-11u%-11u%-11u\n"
        "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n"
        "bin                                MultiJet        MultiJet        MultiJet        MultiJet        Jet2b           Jet2b           Jet2b           STOP            STOP            STOP            STOP            STOP          \n"
        "process                            MultiJet_T2tt   MultiJet_TTj3b  MultiJet_TTj1b  MultiJet_TTj2b  Jet2b_T2tt      Jet2b_TTj2b     Jet2b_TTj3b     signal          rare            wjets           ttslo           ttdil         \n"
        "process                            -2              1               2               3               -1              4               5               0               6               7               8               9             \n"
        "rate                               %-16.4f%-16.4f%-16.4f%-16.4f%-16.4f%-16.4f%-16.4f%-16.4f%-16.4f%-16.4f%-16.4f%-16.4f\n"
        "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n"
        "btag                    shape      %-6.1f          -               -               -               %-6.1f          -               -               %-6.3f          -               -               -               -             \n"
        "isr                     shape      %-6.1f          -               -               -               %-6.1f          -               -               %-6.3f          -               -               -               -             \n"
        "jes                     shape      %-6.1f          -               -               -               %-6.1f          -               -               %-6.3f          -               -               -               -             \n"
        "pdf                     shape      %-6.1f          -               -               -               %-6.1f          -               -               -               -               -               -               -             \n"
        "lep                     lnN        -               -               -               -               -               -               -               %-6.2f          -               -               -               -             \n"
        "lumi                    lnN        %-6.3f          1.0             1.0             1.0             %-6.3f          1.0             1.0             %-6.3f          -               -               -               -             \n"
        "trigger                 lnN        %-6.2f          1.0             1.0             1.0             %-6.2f          1.0             1.0             %-6.2f          -               -               -               -             \n"
        "rare                    lnN        -               -               -               -               -               -               -               -               %-6.3f          -               -               -             \n"
        "wjets                   lnN        -               -               -               -               -               -               -               -               -               %-6.3f          -               -             \n"
        "ttslo                   lnN        -               -               -               -               -               -               -               -               -               -               %-6.3f          -             \n"
        "ttdil                   lnN        -               -               -               -               -               -               -               -               -               -               -               %-6.3f        \n"
        "n_TTj1b_MultiJet     flatParam\n"
        "MR0_TTj1b_MultiJet   flatParam\n"
        "b_TTj2b_MultiJet     flatParam\n"
        "MR0_TTj2b_MultiJet   flatParam\n"
        "MultiJet_TTj3b_norm  flatParam\n"
        "MultiJet_TTj2b_norm  flatParam\n"
        "n_TTj2b_Jet2b        flatParam\n"
        "Jet2b_TTj3b_norm     flatParam\n"
        "R0_TTj2b_Jet2b       flatParam\n"
        "b_TTj2b_Jet2b        flatParam\n"
        "R0_TTj2b_MultiJet    flatParam\n"
        "MR0_TTj2b_Jet2b      flatParam\n"
        "MultiJet_TTj1b_norm  flatParam\n"
        "R0_TTj1b_MultiJet    flatParam\n"
        "Jet2b_TTj2b_norm     flatParam\n"
        "n_TTj2b_MultiJet     flatParam\n"
        "b_TTj1b_MultiJet     flatParam\n"
        , stop_info.num_srs   + razor_info.num_srs
        , stop_info.num_bkgds + razor_info.num_bkgds
        , stop_info.num_nuis  + razor_info.num_nuis
        , razor_info.obs_mj
        , razor_info.obs_j2
        , stop_info.obs
        , razor_info.acc_mj
        , razor_info.mj_ttj3b
        , razor_info.mj_tt1jb
        , razor_info.mj_ttj2b
        , razor_info.acc_j2
        , razor_info.j2_ttj2b
        , razor_info.j2_ttj3b
        , stop_info.acc
        , stop_info.rare
        , stop_info.wjets
        , stop_info.ttslo
        , stop_info.ttdil
        , razor_info.btag_unc
        , razor_info.btag_unc
        , stop_info.btag_unc
        , razor_info.isr_unc
        , razor_info.isr_unc
        , stop_info.isr_unc
        , razor_info.jes_unc
        , razor_info.jes_unc
        , stop_info.jes_unc
        , razor_info.pdf_unc
        , razor_info.pdf_unc
        , stop_info.lep_unc
        , razor_info.lumi_unc
        , razor_info.lumi_unc
        , stop_info.lumi_unc
        , razor_info.trig_unc
        , razor_info.trig_unc
        , stop_info.trig_unc
        , stop_info.rare_unc
        , stop_info.wjets_unc
        , stop_info.ttslo_unc
        , stop_info.ttdil_unc
    );

    // print it
    out << card;

    // done
    return;
}


// main program
int main(int argc, char* argv[])
try
{
    using namespace std;

    // inputs
    // -------------------------------------------------------------------------------------------------//

    std::string syst_file    = "";
    std::string output_file  = "";
    std::string stop_card    = "";
    std::string razor_card   = "";
    unsigned short type      = 1; // hard coded for now
    bool verbose             = false;

    const string type_desc = "1: The first type.";

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"       , "print this menu")
        ("stop_card"  , po::value<std::string>(&stop_card)->required() , "REQUIRED: name of stop input card"  )
        ("razor_card" , po::value<std::string>(&razor_card)->required(), "REQUIRED: name of razor input card" )
        ("output"     , po::value<std::string>(&output_file), "name of output file (blank = stdout)"          )
        ("verbose"    , po::value<bool>(&verbose)           , "verbosity"                                     )
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
        cout << "stop_card   :\t" << stop_card   << endl;
        cout << "razor_card  :\t" << razor_card  << endl;
        cout << "type        :\t" << type        << endl;
    }

    // check that input file exists and is specified
    if (not syst_file.empty() and not lt::file_exists(syst_file))
    {
        cout << "[stop_combine_card] ERROR: systematic histogram file " << syst_file << " not found" << endl;
        cout << desc << "\n";
        return 1;
    }

    // check that stop card exists and is specified
    if (not stop_card.empty() and not lt::file_exists(stop_card))
    {
        cout << "[stop_combine_card] ERROR: stop_card file " << stop_card << " not found" << endl;
        cout << desc << "\n";
        return 1;
    }

    // check that razor card exists and is specified
    if (not razor_card.empty() and not lt::file_exists(razor_card))
    {
        cout << "[stop_combine_card] ERROR: razor_card file " << razor_card << " not found" << endl;
        cout << desc << "\n";
        return 1;
    }

    // Get information from the analysis 
    // -------------------------------------------------------------------------------------------------//

    stop_card_info_t stop_info = ParseStopCard(stop_card);
    if (verbose)
    {
        cout << "\n[stop_combine_card] Verifying stop card:\n";
        PrintStopCard(std::cout, stop_info, type);
    }

    razor_card_info_t razor_info = ParseRazorCard(razor_card);
    if (verbose)
    {
        cout << "\n[stop_combine_card] Verifying razor card:\n";
        PrintRazorCard(std::cout, razor_info, type);
    }

    // print the combined result 
    // -------------------------------------------------------------------------------------------------//

    if (output_file.empty())
    {
        PrintCombinedCard(std::cout, stop_info, razor_info);
    }
    else
    {
        lt::mkdir(lt::dirname(output_file), /*force=*/true);
        std::ofstream out(output_file.c_str(), std::ofstream::out);
        PrintCombinedCard(out, stop_info, razor_info);
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
