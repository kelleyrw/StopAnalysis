#include "RootTools.h"
#include "LanguageTools.h"
#include "SignalRegion.h"
#include "StopYields.h"
#include "Sample.h"
#include "TStyle.h"
#include "TChain.h"
#include "TCanvas.h"
#include <iostream>

using namespace std;

stop::Yield::value_t ExtractExpUpperLimit
(
    const std::string& filename
)
{
    TChain chain("T");
    chain.Add(filename.c_str());
    stop::Yield::value_t result;
    chain.SetBranchAddress("rmedian"   , &result.value);
    chain.SetBranchAddress("rmedianErr", &result.error);
    chain.GetEntry(0);
    return result;
}

stop::Yield::value_t ExtractObsUpperLimit
(
    const std::string& filename
)
{
    TChain chain("T");
    chain.Add(filename.c_str());
    stop::Yield::value_t result;
    chain.SetBranchAddress("limit"   , &result.value);
    chain.SetBranchAddress("limitErr", &result.error);
    chain.GetEntry(0);
    return result;
}

void CompareMethods 
(
    const float mass_stop,
    const float mass_lsp
)
{
    // get the original results
    rt::TH1Container hc_orig("/Users/rwk7t/temp/from_ben/exclusion2012_postLHCP_T2bwFixed/rootfiles/T2tt_BDT_histos.root");
    //hc_orig.List();

    int bin = hc_orig["heff_0"]->FindBin(mass_stop, mass_lsp);
    stop::Yield::value_t ul_obs_orig[stop::SignalRegion::static_size] =
    {
        {1000.0*hc_orig["hxsec_0"]->GetBinContent(bin), 0},
        {1000.0*hc_orig["hxsec_1"]->GetBinContent(bin), 0},
        {1000.0*hc_orig["hxsec_2"]->GetBinContent(bin), 0},
        {1000.0*hc_orig["hxsec_3"]->GetBinContent(bin), 0},
        {1000.0*hc_orig["hxsec_4"]->GetBinContent(bin), 0},
        {1000.0*hc_orig["hxsec_5"]->GetBinContent(bin), 0},
    };
    stop::Yield::value_t ul_exp_orig[stop::SignalRegion::static_size] =
    {
        {1000.0*hc_orig["hxsec_exp_0"]->GetBinContent(bin), 1000.0*std::max(hc_orig["hxsec_expp1_0"]->GetBinContent(bin), hc_orig["hxsec_expm1_0"]->GetBinContent(bin))},
        {1000.0*hc_orig["hxsec_exp_1"]->GetBinContent(bin), 1000.0*std::max(hc_orig["hxsec_expp1_1"]->GetBinContent(bin), hc_orig["hxsec_expm1_1"]->GetBinContent(bin))},
        {1000.0*hc_orig["hxsec_exp_2"]->GetBinContent(bin), 1000.0*std::max(hc_orig["hxsec_expp1_2"]->GetBinContent(bin), hc_orig["hxsec_expm1_2"]->GetBinContent(bin))},
        {1000.0*hc_orig["hxsec_exp_3"]->GetBinContent(bin), 1000.0*std::max(hc_orig["hxsec_expp1_3"]->GetBinContent(bin), hc_orig["hxsec_expm1_3"]->GetBinContent(bin))},
        {1000.0*hc_orig["hxsec_exp_4"]->GetBinContent(bin), 1000.0*std::max(hc_orig["hxsec_expp1_4"]->GetBinContent(bin), hc_orig["hxsec_expm1_4"]->GetBinContent(bin))},
        {1000.0*hc_orig["hxsec_exp_5"]->GetBinContent(bin), 1000.0*std::max(hc_orig["hxsec_expp1_5"]->GetBinContent(bin), hc_orig["hxsec_expm1_5"]->GetBinContent(bin))},
    };

    const std::string limit_path = "output/lands/t2tt/";

    // get method1 a posteriori (m1a)
    stop::Yield::value_t ul_obs_m1a[stop::SignalRegion::static_size] =
    {
        ExtractObsUpperLimit(Form("%s/bands_limit_method1_aposteriori_%1.0f_%1.0f_bdt1l_m2lnQ.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_limit_method1_aposteriori_%1.0f_%1.0f_bdt1t_m2lnQ.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_limit_method1_aposteriori_%1.0f_%1.0f_bdt2_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_limit_method1_aposteriori_%1.0f_%1.0f_bdt3_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_limit_method1_aposteriori_%1.0f_%1.0f_bdt4_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_limit_method1_aposteriori_%1.0f_%1.0f_bdt5_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
    };
    stop::Yield::value_t ul_exp_m1a[stop::SignalRegion::static_size] =
    {
        ExtractExpUpperLimit(Form("%s/bands_limit_method1_aposteriori_%1.0f_%1.0f_bdt1l_m2lnQ.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_limit_method1_aposteriori_%1.0f_%1.0f_bdt1t_m2lnQ.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_limit_method1_aposteriori_%1.0f_%1.0f_bdt2_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_limit_method1_aposteriori_%1.0f_%1.0f_bdt3_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_limit_method1_aposteriori_%1.0f_%1.0f_bdt4_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_limit_method1_aposteriori_%1.0f_%1.0f_bdt5_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
    };

    // get method2 a posteriori (m2a)
    stop::Yield::value_t ul_obs_m2a[stop::SignalRegion::static_size] =
    {
        ExtractObsUpperLimit(Form("%s/bands_limit_method2_aposteriori_%1.0f_%1.0f_bdt1l_m2lnQ.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_limit_method2_aposteriori_%1.0f_%1.0f_bdt1t_m2lnQ.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_limit_method2_aposteriori_%1.0f_%1.0f_bdt2_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_limit_method2_aposteriori_%1.0f_%1.0f_bdt3_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_limit_method2_aposteriori_%1.0f_%1.0f_bdt4_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_limit_method2_aposteriori_%1.0f_%1.0f_bdt5_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
    };
    stop::Yield::value_t ul_exp_m2a[stop::SignalRegion::static_size] =
    {
        ExtractExpUpperLimit(Form("%s/bands_limit_method2_aposteriori_%1.0f_%1.0f_bdt1l_m2lnQ.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_limit_method2_aposteriori_%1.0f_%1.0f_bdt1t_m2lnQ.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_limit_method2_aposteriori_%1.0f_%1.0f_bdt2_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_limit_method2_aposteriori_%1.0f_%1.0f_bdt3_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_limit_method2_aposteriori_%1.0f_%1.0f_bdt4_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_limit_method2_aposteriori_%1.0f_%1.0f_bdt5_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
    };

    // get method3 a posteriori (m3a)
    stop::Yield::value_t ul_obs_m3a[stop::SignalRegion::static_size] =
    {
        ExtractObsUpperLimit(Form("%s/bands_limit_method3_aposteriori_%1.0f_%1.0f_bdt1l_m2lnQ.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_limit_method3_aposteriori_%1.0f_%1.0f_bdt1t_m2lnQ.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_limit_method3_aposteriori_%1.0f_%1.0f_bdt2_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_limit_method3_aposteriori_%1.0f_%1.0f_bdt3_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_limit_method3_aposteriori_%1.0f_%1.0f_bdt4_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_limit_method3_aposteriori_%1.0f_%1.0f_bdt5_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
    };
    stop::Yield::value_t ul_exp_m3a[stop::SignalRegion::static_size] =
    {
        ExtractExpUpperLimit(Form("%s/bands_limit_method3_aposteriori_%1.0f_%1.0f_bdt1l_m2lnQ.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_limit_method3_aposteriori_%1.0f_%1.0f_bdt1t_m2lnQ.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_limit_method3_aposteriori_%1.0f_%1.0f_bdt2_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_limit_method3_aposteriori_%1.0f_%1.0f_bdt3_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_limit_method3_aposteriori_%1.0f_%1.0f_bdt4_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_limit_method3_aposteriori_%1.0f_%1.0f_bdt5_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
    };
    

    // output table
    const char* const fmt = "1.3";
    CTable table;
    table.useTitle();
    table.setTitle(Form("Comparison for m_stop = %1.0f and m_lsp = %1.0f", mass_stop, mass_lsp));
    table.setTable()(                  "BDT1L"                , "BDT1T"               , "BDT2"                , "BDT3"                , "BDT4"                , "BDT5"                 )
    ("orig obs UL"                   , ul_obs_orig[0].value   , ul_obs_orig[1].value  , ul_obs_orig[2].value  , ul_obs_orig[3].value  , ul_obs_orig[4].value  , ul_obs_orig[5].value   )
    ("orig exp UL"                   , ul_exp_orig[0].value   , ul_exp_orig[1].value  , ul_exp_orig[2].value  , ul_exp_orig[3].value  , ul_exp_orig[4].value  , ul_exp_orig[5].value   )
    ("method1 obs UL (a posteriori)" , ul_obs_m1a [0].pm(fmt) , ul_obs_m1a [1].pm(fmt), ul_obs_m1a [2].pm(fmt), ul_obs_m1a [3].pm(fmt), ul_obs_m1a [4].pm(fmt), ul_obs_m1a [5].pm(fmt) )
    ("method1 exp UL (a posteriori)" , ul_exp_m1a [0].pm(fmt) , ul_exp_m1a [1].pm(fmt), ul_exp_m1a [2].pm(fmt), ul_exp_m1a [3].pm(fmt), ul_exp_m1a [4].pm(fmt), ul_exp_m1a [5].pm(fmt) )
    ("method2 obs UL (a posteriori)" , ul_obs_m2a [0].pm(fmt) , ul_obs_m2a [1].pm(fmt), ul_obs_m2a [2].pm(fmt), ul_obs_m2a [3].pm(fmt), ul_obs_m2a [4].pm(fmt), ul_obs_m2a [5].pm(fmt) )
    ("method2 exp UL (a posteriori)" , ul_exp_m2a [0].pm(fmt) , ul_exp_m2a [1].pm(fmt), ul_exp_m2a [2].pm(fmt), ul_exp_m2a [3].pm(fmt), ul_exp_m2a [4].pm(fmt), ul_exp_m2a [5].pm(fmt) )
    ("method3 obs UL (a posteriori)" , ul_obs_m3a [0].pm(fmt) , ul_obs_m3a [1].pm(fmt), ul_obs_m3a [2].pm(fmt), ul_obs_m3a [3].pm(fmt), ul_obs_m3a [4].pm(fmt), ul_obs_m3a [5].pm(fmt) )
    ("method3 exp UL (a posteriori)" , ul_exp_m3a [0].pm(fmt) , ul_exp_m3a [1].pm(fmt), ul_exp_m3a [2].pm(fmt), ul_exp_m3a [3].pm(fmt), ul_exp_m3a [4].pm(fmt), ul_exp_m3a [5].pm(fmt) )
    ;

    cout << table << std::endl;
}

stop::Yield::value_t ExtractExpUpperLimitCombine
(
    const std::string& filename
)
{
    TChain chain("limit");
    chain.Add(filename.c_str());
    stop::Yield::value_t result;
    chain.SetBranchAddress("limit"   , &result.value);
    chain.SetBranchAddress("limitErr", &result.error);
    chain.GetEntry(2);
    return result;
}

stop::Yield::value_t ExtractObsUpperLimitCombine
(
    const std::string& filename
)
{
    TChain chain("limit");
    chain.Add(filename.c_str());
    stop::Yield::value_t result;
    chain.SetBranchAddress("limit"   , &result.value);
    chain.SetBranchAddress("limitErr", &result.error);
    chain.GetEntry(5);
    return result;
}

void CompareMethodsCombine
(
    const float mass_stop,
    const float mass_lsp
)
{
    // get the original results
    rt::TH1Container hc_orig("/Users/rwk7t/temp/from_ben/exclusion2012_postLHCP_T2bwFixed/rootfiles/T2tt_BDT_histos.root");
    //hc_orig.List();

    int bin = hc_orig["heff_0"]->FindBin(mass_stop, mass_lsp);
    stop::Yield::value_t ul_obs_orig[stop::SignalRegion::static_size] =
    {
        {1000.0*hc_orig["hxsec_0"]->GetBinContent(bin), 0},
        {1000.0*hc_orig["hxsec_1"]->GetBinContent(bin), 0},
        {1000.0*hc_orig["hxsec_2"]->GetBinContent(bin), 0},
        {1000.0*hc_orig["hxsec_3"]->GetBinContent(bin), 0},
        {1000.0*hc_orig["hxsec_4"]->GetBinContent(bin), 0},
        {1000.0*hc_orig["hxsec_5"]->GetBinContent(bin), 0},
    };
    stop::Yield::value_t ul_exp_orig[stop::SignalRegion::static_size] =
    {
        {1000.0*hc_orig["hxsec_exp_0"]->GetBinContent(bin), 1000.0*std::max(hc_orig["hxsec_expp1_0"]->GetBinContent(bin), hc_orig["hxsec_expm1_0"]->GetBinContent(bin))},
        {1000.0*hc_orig["hxsec_exp_1"]->GetBinContent(bin), 1000.0*std::max(hc_orig["hxsec_expp1_1"]->GetBinContent(bin), hc_orig["hxsec_expm1_1"]->GetBinContent(bin))},
        {1000.0*hc_orig["hxsec_exp_2"]->GetBinContent(bin), 1000.0*std::max(hc_orig["hxsec_expp1_2"]->GetBinContent(bin), hc_orig["hxsec_expm1_2"]->GetBinContent(bin))},
        {1000.0*hc_orig["hxsec_exp_3"]->GetBinContent(bin), 1000.0*std::max(hc_orig["hxsec_expp1_3"]->GetBinContent(bin), hc_orig["hxsec_expm1_3"]->GetBinContent(bin))},
        {1000.0*hc_orig["hxsec_exp_4"]->GetBinContent(bin), 1000.0*std::max(hc_orig["hxsec_expp1_4"]->GetBinContent(bin), hc_orig["hxsec_expm1_4"]->GetBinContent(bin))},
        {1000.0*hc_orig["hxsec_exp_5"]->GetBinContent(bin), 1000.0*std::max(hc_orig["hxsec_expp1_5"]->GetBinContent(bin), hc_orig["hxsec_expm1_5"]->GetBinContent(bin))},
    };

    std::string limit_path = "output/lands/t2tt/";

    // get method3 a posteriori (m3a) -- LandS
    stop::Yield::value_t ul_obs_m3a[stop::SignalRegion::static_size] =
    {
        ExtractObsUpperLimit(Form("%s/bands_limit_method3_aposteriori_%1.0f_%1.0f_bdt1l_m2lnQ.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_limit_method3_aposteriori_%1.0f_%1.0f_bdt1t_m2lnQ.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_limit_method3_aposteriori_%1.0f_%1.0f_bdt2_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_limit_method3_aposteriori_%1.0f_%1.0f_bdt3_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_limit_method3_aposteriori_%1.0f_%1.0f_bdt4_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimit(Form("%s/bands_limit_method3_aposteriori_%1.0f_%1.0f_bdt5_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
    };
    stop::Yield::value_t ul_exp_m3a[stop::SignalRegion::static_size] =
    {
        ExtractExpUpperLimit(Form("%s/bands_limit_method3_aposteriori_%1.0f_%1.0f_bdt1l_m2lnQ.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_limit_method3_aposteriori_%1.0f_%1.0f_bdt1t_m2lnQ.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_limit_method3_aposteriori_%1.0f_%1.0f_bdt2_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_limit_method3_aposteriori_%1.0f_%1.0f_bdt3_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_limit_method3_aposteriori_%1.0f_%1.0f_bdt4_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimit(Form("%s/bands_limit_method3_aposteriori_%1.0f_%1.0f_bdt5_m2lnQ.root" , limit_path.c_str(), mass_stop, mass_lsp)),
    };

    limit_path = "output/combine/t2tt/";

    // get method3 (m3c) -- Combine 
    stop::Yield::value_t ul_obs_m3c[stop::SignalRegion::static_size] =
    {
        ExtractObsUpperLimitCombine(Form("%s/limit_method3_%1.0f_%1.0f_bdt1l.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimitCombine(Form("%s/limit_method3_%1.0f_%1.0f_bdt1t.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimitCombine(Form("%s/limit_method3_%1.0f_%1.0f_bdt2.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimitCombine(Form("%s/limit_method3_%1.0f_%1.0f_bdt3.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimitCombine(Form("%s/limit_method3_%1.0f_%1.0f_bdt4.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractObsUpperLimitCombine(Form("%s/limit_method3_%1.0f_%1.0f_bdt5.root" , limit_path.c_str(), mass_stop, mass_lsp)),
    };
    stop::Yield::value_t ul_exp_m3c[stop::SignalRegion::static_size] =
    {
        ExtractExpUpperLimitCombine(Form("%s/limit_method3_%1.0f_%1.0f_bdt1l.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimitCombine(Form("%s/limit_method3_%1.0f_%1.0f_bdt1t.root", limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimitCombine(Form("%s/limit_method3_%1.0f_%1.0f_bdt2.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimitCombine(Form("%s/limit_method3_%1.0f_%1.0f_bdt3.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimitCombine(Form("%s/limit_method3_%1.0f_%1.0f_bdt4.root" , limit_path.c_str(), mass_stop, mass_lsp)),
        ExtractExpUpperLimitCombine(Form("%s/limit_method3_%1.0f_%1.0f_bdt5.root" , limit_path.c_str(), mass_stop, mass_lsp)),
    };

    // output table
    const char* const fmt = "1.3";
    CTable table;
    table.useTitle();
    table.setTitle(Form("Comparison for m_stop = %1.0f and m_lsp = %1.0f", mass_stop, mass_lsp));
    table.setTable()(             "BDT1L"                , "BDT1T"               , "BDT2"                , "BDT3"                , "BDT4"                , "BDT5"                 )
    ("orig obs UL"              , ul_obs_orig[0].value   , ul_obs_orig[1].value  , ul_obs_orig[2].value  , ul_obs_orig[3].value  , ul_obs_orig[4].value  , ul_obs_orig[5].value   )
    ("orig exp UL"              , ul_exp_orig[0].value   , ul_exp_orig[1].value  , ul_exp_orig[2].value  , ul_exp_orig[3].value  , ul_exp_orig[4].value  , ul_exp_orig[5].value   )
    ("method3 obs UL (LandS)"   , ul_obs_m3a [0].pm(fmt) , ul_obs_m3a [1].pm(fmt), ul_obs_m3a [2].pm(fmt), ul_obs_m3a [3].pm(fmt), ul_obs_m3a [4].pm(fmt), ul_obs_m3a [5].pm(fmt) )
    ("method3 exp UL (LandS)"   , ul_exp_m3a [0].pm(fmt) , ul_exp_m3a [1].pm(fmt), ul_exp_m3a [2].pm(fmt), ul_exp_m3a [3].pm(fmt), ul_exp_m3a [4].pm(fmt), ul_exp_m3a [5].pm(fmt) )
    ("method3 obs UL (Combine)" , ul_obs_m3c [0].pm(fmt) , ul_obs_m3c [1].pm(fmt), ul_obs_m3c [2].pm(fmt), ul_obs_m3c [3].pm(fmt), ul_obs_m3c [4].pm(fmt), ul_obs_m3c [5].pm(fmt) )
    ("method3 exp UL (Combine)" , ul_exp_m3c [0].pm(fmt) , ul_exp_m3c [1].pm(fmt), ul_exp_m3c [2].pm(fmt), ul_exp_m3c [3].pm(fmt), ul_exp_m3c [4].pm(fmt), ul_exp_m3c [5].pm(fmt) )
    ;

    cout << table << std::endl;
}